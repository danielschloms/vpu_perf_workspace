# Simple vector functional-unit patterns (pure-ASM) for performance-model tuning.
#
# Each .S test under src/ isolates one (or a couple) of the Vicuna2 functional
# unit groups (LSU / ALU / MUL / DIV / SLD / ELEM / INDEX / XRESULT / REDSUM /
# REDMINMAX) so the ETISS model can be calibrated per group. The tests use the
# asm.h macros:
#   MATCH_START / MATCH_END   -> address_match_start/end symbols used by the
#                                comparison for address matching
#   RET_INSTR                 -> returns (jr ra) for ETISS, or writes the 0x408
#                                termination signal for the Verilator model.
#
# The shared per-simulator runtime (crt0, linker script, device libs) is
# provided by the parent (ETISS_RUNTIME / VICUNA_RUNTIME).

if(NOT DEFINED RISCV_ARCH OR RISCV_ARCH STREQUAL "")
    set(RISCV_ARCH "rv32im_zve32x")
endif()
if(NOT DEFINED VREG_W OR VREG_W STREQUAL "")
    set(VREG_W "128")
endif()
set(SIMPLE_MARCH "${RISCV_ARCH}_zvl${VREG_W}b" CACHE STRING "RISC-V machine arch")
set(SIMPLE_MABI "ilp32" CACHE STRING "RISC-V machine ABI")
set(SIMPLE_OPT "-O0" CACHE STRING "Optimisation level")
option(SIMPLE_ETISS "Build ETISS targets" ON)
option(SIMPLE_VERILATOR "Build Vicuna2/Verilator targets" ON)

set(SIMPLE_CFLAGS
    "-march=${SIMPLE_MARCH}"
    "-mabi=${SIMPLE_MABI}"
    "${SIMPLE_OPT}"
    "-g"
    "-Wall"
)

# ---- each .S test, built for each simulator ------------------------------
function(add_simple_pattern src_path sim)
    get_filename_component(name "${src_path}" NAME_WE)
    set(target "${name}_${sim}")

    if(sim STREQUAL "etiss")
        set(sim_inc "${ETISS_RUNTIME}")
    elseif(sim STREQUAL "verilator")
        set(sim_inc "${VICUNA_RUNTIME}")
    else()
        message(FATAL_ERROR "Unknown simulator: ${sim}")
    endif()

    add_executable(${target} ${src_path})
    target_include_directories(${target} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${sim_inc}"
    )
    target_compile_options(${target} PRIVATE ${SIMPLE_CFLAGS})

    if(sim STREQUAL "etiss")
        add_dependencies(${target} etiss_crt0)
        target_link_directories(${target} PRIVATE "${CMAKE_BINARY_DIR}/runtime/etiss")
        target_link_options(${target} PRIVATE
            "-nostartfiles"
            "--specs=${ETISS_RUNTIME}/etiss-semihost.specs"
            "-T${ETISS_RUNTIME}/etiss.ld"
        )
    else()
        target_compile_definitions(${target} PRIVATE VERILATOR=1)
        target_compile_options(${target} PRIVATE -Wno-array-bounds)
        target_link_options(${target} PRIVATE
            "-nostartfiles"
            "-T${VICUNA_RUNTIME}/link.ld"
        )
        target_link_libraries(${target} PRIVATE bsp_Vicuna UART_Vicuna)
    endif()

    # ---------- post build: verilator .bin -> .vmem -> prog_<target>.txt ----
    if(sim STREQUAL "verilator")
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -O binary "${CMAKE_CURRENT_BINARY_DIR}/${target}" "${CMAKE_CURRENT_BINARY_DIR}/${target}.bin"
            COMMAND srec_cat "${CMAKE_CURRENT_BINARY_DIR}/${target}.bin" -binary -offset 0x0000 -byte-swap 4 -o "${CMAKE_CURRENT_BINARY_DIR}/${target}.vmem" -vmem
            COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_CURRENT_BINARY_DIR}/${target}.vmem /dev/null 0 0 /dev/null 0 0" > prog_${target}.txt
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
    endif()

    # ---------- post build: disassembly for address matching ---------------
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND "${CMAKE_OBJDUMP}" -d "${CMAKE_CURRENT_BINARY_DIR}/${target}"
        > "${name}_${sim}_dump.txt"
    )

    if(sim STREQUAL "etiss")
        add_test(NAME ${target}
            COMMAND ${ETISS_PROCESSOR}
                -i${ETISS_INI}
                --vp.elf_file=${CMAKE_CURRENT_BINARY_DIR}/${target}
                --arch.cpu=RV32IMACFDV_zvl${VREG_W}b
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    else()
        add_test(NAME ${target}
            COMMAND ${VERILATOR_MODEL}
                ${CMAKE_CURRENT_BINARY_DIR}/prog_${target}.txt
                ${MEM_PORTS} ${MEM_W} 4194304 ${MEM_LATENCY} 1 ${target} ${VREG_W} 0
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    set_tests_properties(${target} PROPERTIES TIMEOUT 100)

    message(STATUS "simple-patterns: added ${target}")
endfunction()

file(GLOB SIMPLE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.S")

foreach(src_path ${SIMPLE_SRC})
    get_filename_component(name "${src_path}" NAME_WE)
    if(DEFINED SIMPLE_ONLY AND NOT ";${SIMPLE_ONLY};" MATCHES ";${name};")
        continue()
    endif()
    if(SIMPLE_ETISS)
        add_simple_pattern("${src_path}" "etiss")
    endif()
    if(SIMPLE_VERILATOR)
        add_simple_pattern("${src_path}" "verilator")
    endif()
endforeach()
