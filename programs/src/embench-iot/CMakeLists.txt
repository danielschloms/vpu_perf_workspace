# Builds the embench-iot benchmark suite for two simulators:
#   * ETISS
#   * Vicuna2 (Verilator model)
#
# This is the embench-iot *integration* (CMake + harness runtime). The actual
# embench-iot sources are the third-party submodule embench-iot/embench-iot,
# which is intentionally left untouched -- this directory only references it as
# a path (EMBENCH_ROOT).
#
# The per-simulator *shared runtime* (crt0, linker script, device libraries)
# lives in programs/runtime/<sim> (provided by the parent). The embench-iot
# harness (board support / triggers + the Verilator main) lives here, and the
# hardware configuration / simulator paths are provided by the parent
# programs/CMakeLists.txt.
#
# Variables (command line / inherited):
#   EMBENCH_MARCH      machine arch       [default: rv32im_zicsr_zicntr]
#   EMBENCH_MABI       machine ABI        [default: ilp32]
#   EMBENCH_OPT        -O level           [default: -O3]
#   EMBENCH_ETISS      build ETISS target [default: ON]
#   EMBENCH_VERILATOR  build verilator    [default: ON]
#   EMBENCH_ONLY       build only these benchmarks (semicolon list, e.g. "crc32;md5sum")
#
# Inherited (from programs/CMakeLists.txt):
#   ETISS_PROCESSOR, VERILATOR_MODEL, SCALAR_CORE, RISCV_ARCH, VREG_W,
#   MEM_W, MEM_PORTS, MEM_LATENCY

# ---- configuration --------------------------------------------------------
# The compiler march is derived from the hardware vector configuration so code
# generation matches the simulated ISA (RV32IM + zve32x + zvl<VLEN>) and stays
# consistent with the simulator (the Verilator arch <RISCV_ARCH>_zvl<VREG_W> and
# the ETISS arch RV32IMACFDV_zvl<VREG_W>b). Override with -DEMBENCH_MARCH=...
if(NOT DEFINED RISCV_ARCH OR RISCV_ARCH STREQUAL "")
    set(RISCV_ARCH "rv32im_zve32x")
endif()
if(NOT DEFINED VREG_W OR VREG_W STREQUAL "")
    set(VREG_W "128")
endif()
set(EMBENCH_MARCH "${RISCV_ARCH}_zvl${VREG_W}b" CACHE STRING "RISC-V machine arch")
set(EMBENCH_MABI "ilp32" CACHE STRING "RISC-V machine ABI")
set(EMBENCH_OPT "-O3" CACHE STRING "Optimisation level")
option(EMBENCH_ETISS "Build ETISS targets" ON)
option(EMBENCH_VERILATOR "Build Vicuna2/Verilator targets" ON)

# embench-iot sources are the third-party submodule (leave it untouched).
set(EMBENCH_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/embench-iot")
if(NOT EXISTS "${EMBENCH_ROOT}/support/main.c")
    message(FATAL_ERROR "embench-iot submodule not populated at ${EMBENCH_ROOT}")
endif()

# ---- embench-iot-specific harness -----------------------------------------
# The shared per-simulator runtime (crt0, linker script, device libraries,
# semihost `_exit`) lives in programs/runtime/<sim> and is provided by the
# parent scope (ETISS_RUNTIME / VICUNA_RUNTIME / ETISS_INI).  Only the
# embench-iot-specific harness functions live here in this folder:
#   boardsupport_etiss.c          (harness for the ETISS sim)
#   boardsupport_vicuna2.c        (harness for the Vicuna2/Verilator sim)
#   main_vicuna2.c                (Verilator main() that writes the 0x408 signal)

# ---- common compile settings ----------------------------------------------
set(EMBENCH_CFLAGS
    "-march=${EMBENCH_MARCH}"
    "-mabi=${EMBENCH_MABI}"
    "${EMBENCH_OPT}"
    "-g"
    "-ffreestanding"
    "-Wall"
)

# Directory of each benchmark in src/<name>.
file(GLOB EMBENCH_BENCH_DIRS LIST_DIRECTORIES true
    "${EMBENCH_ROOT}/src/*")

# ---------- function to add one benchmark for one simulator ---------------
function(add_embench_benchmark bench sim)
    set(bench_dir "${EMBENCH_ROOT}/src/${bench}")
    set(target "${bench}_${sim}")

    # All .c files of the benchmark plus the shared harness + board support.
    set(bench_srcs)
    file(GLOB bench_c "${bench_dir}/*.c")
    list(APPEND bench_srcs ${bench_c})
    list(APPEND bench_srcs
        "${EMBENCH_ROOT}/support/beebsc.c"
    )

    # The generic support/main.c returns from main(), which the Vicuna2 crt0
    # redirects back to _start (restart loop) so the model never sees the
    # result.  Verilator therefore gets its own main() that writes the MMIO
    # termination signal (0x408: 0x0 pass / 0xF fail) instead of returning.
    if(sim STREQUAL "verilator")
        list(APPEND bench_srcs "${CMAKE_CURRENT_SOURCE_DIR}/main_vicuna2.c")
    else()
        list(APPEND bench_srcs "${EMBENCH_ROOT}/support/main.c")
    endif()

    if(sim STREQUAL "etiss")
        list(APPEND bench_srcs "${CMAKE_CURRENT_SOURCE_DIR}/boardsupport_etiss.c")
        set(sim_inc "${ETISS_RUNTIME}")
    elseif(sim STREQUAL "verilator")
        list(APPEND bench_srcs "${CMAKE_CURRENT_SOURCE_DIR}/boardsupport_vicuna2.c")
        set(sim_inc "${VICUNA_RUNTIME}")
    else()
        message(FATAL_ERROR "Unknown simulator: ${sim}")
    endif()

    add_executable(${target} ${bench_srcs})

    target_include_directories(${target} PRIVATE
        "${EMBENCH_ROOT}/support"
        "${bench_dir}"
        "${sim_inc}"
    )

    target_compile_options(${target} PRIVATE ${EMBENCH_CFLAGS})
    if(bench STREQUAL "wikisort")
        # libwikisort.c declares `typedef uint8_t bool;`, which is invalid under
        # C23 (bool becomes a keyword). Force C17 for this benchmark only.
        target_compile_options(${target} PRIVATE -std=gnu17)
    endif()
    target_compile_definitions(${target} PRIVATE
        WARMUP_HEAT=1
        GLOBAL_SCALE_FACTOR=1
    )

    if(sim STREQUAL "etiss")
        add_dependencies(${target} etiss_crt0)
        target_link_directories(${target} PRIVATE "${CMAKE_BINARY_DIR}/runtime/etiss")
        target_link_options(${target} PRIVATE
            "-nostartfiles"
            "--specs=${ETISS_RUNTIME}/etiss-semihost.specs"
            "-T${ETISS_RUNTIME}/etiss.ld"
        )
        target_link_libraries(${target} PRIVATE m)
    else()
        target_compile_options(${target} PRIVATE -Wno-array-bounds)
        target_link_options(${target} PRIVATE
            "-nostartfiles"
            "-T${VICUNA_RUNTIME}/link.ld"
        )
        target_link_libraries(${target} PRIVATE bsp_Vicuna UART_Vicuna)
    endif()

    if(sim STREQUAL "verilator")
        add_custom_command(TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -O binary "${CMAKE_CURRENT_BINARY_DIR}/${target}" "${CMAKE_CURRENT_BINARY_DIR}/${target}.bin"
            COMMAND srec_cat "${CMAKE_CURRENT_BINARY_DIR}/${target}.bin" -binary -offset 0x0000 -byte-swap 4 -o "${CMAKE_CURRENT_BINARY_DIR}/${target}.vmem" -vmem
            COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_CURRENT_BINARY_DIR}/${target}.vmem /dev/null 0 0 /dev/null 0 0" > prog_${target}.txt
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        )
    endif()

    # Disassemble the linked ELF for inspection.
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND "${CMAKE_OBJDUMP}" -d "${CMAKE_CURRENT_BINARY_DIR}/${target}"
        > "${bench}_${sim}_dump.txt"
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

    # Short timeout: the simulated benchmarks can hang on RTL bugs, so cap each
    # test at 10 seconds and let ctest report the ones that don't complete.
    set_tests_properties(${target} PROPERTIES TIMEOUT 100)

    message(STATUS "embench: added ${target}")
endfunction()

# ---------- add the requested benchmarks -----------------------------------
foreach(bench_dir ${EMBENCH_BENCH_DIRS})
    get_filename_component(bench "${bench_dir}" NAME)
    # skip the dummy benchmark
    if(bench STREQUAL "dummy-benchmark")
        continue()
    endif()

    if(DEFINED EMBENCH_ONLY AND NOT ";${EMBENCH_ONLY};" MATCHES ";${bench};")
        continue()
    endif()

    if(EMBENCH_ETISS)
        add_embench_benchmark("${bench}" "etiss")
    endif()
    if(EMBENCH_VERILATOR)
        add_embench_benchmark("${bench}" "verilator")
    endif()
endforeach()
