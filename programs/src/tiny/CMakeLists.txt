# Builds the MLPerf Tiny benchmark suite (Keyword Spotting, int8, first) for the
# Vicuna2 Verilator model.
#
# The mlcommons/tiny sources are the third-party submodule tiny/tiny and are
# left untouched -- we only reference the pretrained KWS int8 model + settings.
# The tflite-micro framework is the tflite-micro submodule, cross-compiled for
# RISC-V into a static library by build_tflm.sh.  The per-simulator *shared
# runtime* (crt0, linker script, device libraries) lives in
# programs/runtime/<sim>, provided by the parent programs/CMakeLists.txt.
#
# Inherited from programs/CMakeLists.txt:
#   RISCV_ARCH, VREG_W, VICUNA_RUNTIME, VERILATOR_MODEL, MEM_W, MEM_PORTS,
#   MEM_LATENCY

# ---- configuration --------------------------------------------------------
if(NOT DEFINED RISCV_ARCH OR RISCV_ARCH STREQUAL "")
    set(RISCV_ARCH "rv32im_zve32x")
endif()
if(NOT DEFINED VREG_W OR VREG_W STREQUAL "")
    set(VREG_W "128")
endif()
set(TINY_MARCH "${RISCV_ARCH}_zvl${VREG_W}b")
set(TINY_MABI "ilp32")
set(TINY_OPT "-O3")

# ctest timeout (seconds) for the (very slow) KWS inference under the scalar
# cycle-accurate Verilator model.
set(TINY_KWS_TIMEOUT "1800" CACHE STRING
    "Timeout (seconds) for the MLPerf Tiny KWS Verilator test.")

# mlcommons/tiny submodule (pretrained models + reference settings).  Untouched.
set(TINY_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/tiny")
set(KWS_DIR "${TINY_ROOT}/benchmark/reference_submissions/keyword_spotting")
if(NOT EXISTS "${KWS_DIR}/kws/kws_model_data.cc")
    message(FATAL_ERROR "mlcommons/tiny submodule not populated at ${TINY_ROOT}")
endif()

# tflite-micro submodule.
set(TFLM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tflite-micro")
if(NOT EXISTS "${TFLM_DIR}/tensorflow/lite/micro/micro_interpreter.h")
    message(FATAL_ERROR "tflite-micro submodule not populated at ${TFLM_DIR}")
endif()

# ---- build libtensorflow-microlite.a (one-time, cached) -------------------
set(TFLM_LIB "${CMAKE_CURRENT_BINARY_DIR}/libtensorflow-microlite.a")
add_custom_command(OUTPUT "${TFLM_LIB}"
    COMMAND "${CMAKE_COMMAND}" -E env
        "TFLM_DIR=${TFLM_DIR}"
        "TFLM_OUT=${TFLM_LIB}"
        "TFLM_MARCH=${TINY_MARCH}"
        "TFLM_MABI=${TINY_MABI}"
        bash "${CMAKE_CURRENT_SOURCE_DIR}/build_tflm.sh"
    DEPENDS "${TFLM_DIR}/tensorflow/lite/micro/micro_interpreter.h"
    COMMENT "Building tflite-micro for RISC-V"
    VERBATIM)
add_custom_target(tflm_microlite DEPENDS "${TFLM_LIB}")

# tflite-micro include dirs (framework + downloaded third-party headers).
set(TFLM_DL "${TFLM_DIR}/tensorflow/lite/micro/tools/make/downloads")
set(TFLM_INC
    "${TFLM_DIR}"
    "${TFLM_DL}/flatbuffers/include"
    "${TFLM_DL}/kissfft"
    "${TFLM_DL}/eyalroz_printf/src"
)

# ---- add one KWS harness target for one simulator -------------------------
#   harness/main_<sim>.cpp      entry point (per-simulator)
#   harness/boardsupport_<sim>  newlib/device stubs (per-simulator)
#   harness/kws_runner.cpp      shared tflite-micro KWS inference
# The runner picks its diagnostic sink via KWS_UART: Verilator uses the
# runtime's limited uart_printf, ETISS uses hosted stdio (printf).
function(add_tiny_kws target sim)
    if(sim STREQUAL "verilator")
        set(main_src "${CMAKE_CURRENT_SOURCE_DIR}/harness/main_vicuna2.cpp")
        set(bs_src   "${CMAKE_CURRENT_SOURCE_DIR}/harness/boardsupport_vicuna2.c")
    elseif(sim STREQUAL "etiss")
        set(main_src "${CMAKE_CURRENT_SOURCE_DIR}/harness/main_etiss.cpp")
        set(bs_src   "${CMAKE_CURRENT_SOURCE_DIR}/harness/boardsupport_etiss.cc")
    else()
        message(FATAL_ERROR "add_tiny_kws: unsupported sim '${sim}'")
    endif()

    add_executable(${target}
        "${main_src}"
        "${bs_src}"
        "${CMAKE_CURRENT_SOURCE_DIR}/harness/kws_runner.cpp"
        "${KWS_DIR}/kws/kws_model_data.cc"
        "${KWS_DIR}/kws/kws_model_settings.cc"
    )

    add_dependencies(${target} tflm_microlite)

    target_include_directories(${target} PRIVATE
        "${KWS_DIR}"               # kws/kws_model_*.h
        ${TFLM_INC}
    )
    if(sim STREQUAL "verilator")
        target_include_directories(${target} PRIVATE
            "${VICUNA_RUNTIME}"        # uart.hpp etc.
            "${VICUNA_RUNTIME}/lib"
        )
    endif()

    # Common flags for both C and C++.
    # NOTE: do NOT add -ffreestanding here.  This toolchain's libstdc++
    # (GCC 16.1.0) refuses to provide its hosted headers (vector, etc.) in
    # freestanding mode, which breaks the downloaded flatbuffers headers that
    # the tflite schema pulls in.  C++ is built hosted; the C board-support file
    # needs nothing special.
    target_compile_options(${target} PRIVATE
        "-march=${TINY_MARCH}"
        "-mabi=${TINY_MABI}"
        "${TINY_OPT}"
        "-g"
        "-Wall"
        "-Wno-array-bounds"
    )
    # C++-only flags (the harness pulls in tflite-micro, which is C++).
    target_compile_options(${target} PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
        $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
        $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
        $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
    )

    if(sim STREQUAL "verilator")
        target_compile_definitions(${target} PRIVATE KWS_UART)

        target_link_options(${target} PRIVATE
            "-nostartfiles"
            "-T${VICUNA_RUNTIME}/link.ld"
        )
        target_link_libraries(${target} PRIVATE
            bsp_Vicuna UART_Vicuna "${TFLM_LIB}" m
        )

        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -O binary
                "${CMAKE_CURRENT_BINARY_DIR}/${target}"
                "${CMAKE_CURRENT_BINARY_DIR}/${target}.bin"
            COMMAND srec_cat "${CMAKE_CURRENT_BINARY_DIR}/${target}.bin" -binary
                -offset 0x0000 -byte-swap 4
                -o "${CMAKE_CURRENT_BINARY_DIR}/${target}.vmem" -vmem
            COMMAND ${CMAKE_COMMAND} -E echo
                "${CMAKE_CURRENT_BINARY_DIR}/${target}.vmem /dev/null 0 0 /dev/null 0 0"
                > prog_${target}.txt
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        )

        add_test(NAME ${target}
            COMMAND ${VERILATOR_MODEL}
                ${CMAKE_CURRENT_BINARY_DIR}/prog_${target}.txt
                ${MEM_PORTS} ${MEM_W} 4194304 ${MEM_LATENCY} 1 ${target} ${VREG_W} 0
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    else()
        # ETISS: semihosting runtime (etiss_crt0 / newlib / libsemihost) provides
        # _exit,_write,_sbrk,...; the harness only adds putchar_ for the eyalroz
        # printf pulled in by tflite-micro's logging.
        add_dependencies(${target} etiss_crt0)
        target_link_directories(${target} PRIVATE "${CMAKE_BINARY_DIR}/runtime/etiss")
        target_link_options(${target} PRIVATE
            "-nostartfiles"
            "--specs=${ETISS_RUNTIME}/etiss-semihost.specs"
            "-T${ETISS_RUNTIME}/etiss.ld"
        )
        target_link_libraries(${target} PRIVATE "${TFLM_LIB}" m)

        add_test(NAME ${target}
            COMMAND ${ETISS_PROCESSOR}
                -i${ETISS_INI}
                --vp.elf_file=${CMAKE_CURRENT_BINARY_DIR}/${target}
                --arch.cpu=RV32IMACFDV_zvl${VREG_W}b
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    # The int8 DS-CNN KWS inference is compute-heavy, so a full forward pass is
    # far slower than the embench kernels under the scalar cycle-accurate
    # Verilator model.  Give it a generous, configurable window.
    set_tests_properties(${target} PROPERTIES TIMEOUT ${TINY_KWS_TIMEOUT})

    message(STATUS "mlperftiny: added ${target}")
endfunction()

add_tiny_kws("kws_verilator" "verilator")
add_tiny_kws("kws_etiss" "etiss")
