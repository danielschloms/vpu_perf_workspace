# Cross-compiles the benchmark / program suites under programs/ for two
# simulators:
#   * ETISS
#   * Vicuna2 (Verilator model)
#
# The suites are collected under programs/src (see programs/src/CMakeLists.txt).
# Each suite owns its harness runtime (crt0 + linker script + board support),
# e.g. embench-iot has programs/src/embench-iot/runtime/<sim>.  The common
# hardware configuration and simulator paths are defined below.
#
# Cross-compiles for RV32 using the riscv32-unknown-elf toolchain.
#
# Usage:
#   cmake -S programs -B programs/build -DCMAKE_TOOLCHAIN_FILE=...   # or pass -DCMAKE_C_COMPILER=riscv32-unknown-elf-gcc
#   cmake --build programs/build
#
# Variables:
#   SCALAR_CORE       scalar core (cv32e40x | cv32a60x)   [default: cv32e40x]
#   RISCV_ARCH        RISC-V architecture config          [default: rv32im_zve32x]
#   VREG_W            vector register width / VLEN (bits) [default: 128]
#   VLANE_W           vector lane width (bits)            [default: 32]
#   VMEM_W / VMEM_PORTS   vector memory interface config
#   MEM_W / MEM_PORTS / MEM_LATENCY   data memory interface config
#   EMBENCH_MLPERFTINY  build the MLPerfTiny suite (WIP)  [default: OFF]
#
# Suite-specific options (e.g. EMBENCH_MARCH / EMBENCH_ONLY) live in the
# respective suite CMakeLists under programs/src.

cmake_minimum_required(VERSION 3.16)

# Cross-compile for RISC-V 32 (unless a toolchain file / -DCMAKE_C_COMPILER was given).
if(NOT CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER "riscv32-unknown-elf-gcc" CACHE STRING "C compiler")
endif()
if(NOT CMAKE_ASM_COMPILER)
    set(CMAKE_ASM_COMPILER "riscv32-unknown-elf-gcc" CACHE STRING "Assembler")
endif()
if(NOT CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER "riscv32-unknown-elf-g++" CACHE STRING "C++ compiler")
endif()

project(embench_iot C CXX ASM)

enable_testing()

# ---- hardware configuration (must match rtl/vicuna2/vector_config.cmake) ---
# The simulators and the ctest invocation are built per hardware configuration.
# The Verilator simulator lives in a build directory named after the core, the
# RISC-V arch and the vector micro-architecture:
#   rtl/vicuna2/build/<SCALAR_CORE>/<RISCV_ARCH>_zvl<VREG_W>_vl<VLANE_W>
# where VREG_W is the vector register width (VLEN) and VLANE_W the lane width.
set(SCALAR_CORE "cv32a60x" CACHE STRING "Scalar core: cv32e40x | cv32a60x")
set(RISCV_ARCH "rv32im_zve32x" CACHE STRING "RISC-V architecture config")
set(VREG_W "128" CACHE STRING "Vector register width (VLEN) in bits")
set(VLANE_W "32" CACHE STRING "Vector lane width in bits")
set(VMEM_W "32" CACHE STRING "Vector memory interface width (bits)")
set(VMEM_PORTS "1" CACHE STRING "Number of vector memory ports")
set(MEM_W "32" CACHE STRING "Data memory interface width (bits)")
set(MEM_PORTS "1" CACHE STRING "Number of data memory ports")
set(MEM_LATENCY "1" CACHE STRING "Data memory latency (cycles)")
option(EMBENCH_MLPERFTINY "Build the MLPerfTiny suite (WIP)" OFF)

# ---- shared per-simulator runtime (crt0 + linker, reused by suites) --------
set(ETISS_RUNTIME  "${CMAKE_CURRENT_SOURCE_DIR}/runtime/etiss")
set(VICUNA_RUNTIME "${CMAKE_CURRENT_SOURCE_DIR}/runtime/verilator_vicuna2")

# ---- simulator locations (paths depend on hardware configuration) ---------
set(REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")

# ETISS processor + config (built by scripts/build_etiss.sh).
set(ETISS_PROCESSOR "${REPO_ROOT}/etiss-pe/etiss-perf-sim/etiss/build/bin/bare_etiss_processor")
set(ETISS_INI "${ETISS_RUNTIME}/ini/etiss.ini")

# Verilator model, at a path that encodes the HW configuration
# (<core>/<arch>_zvl<vlen>_vl<lane_width>). Built by scripts/build_verilator.sh.
set(VERILATOR_SIM_BUILD
    "${REPO_ROOT}/rtl/vicuna2/build/${SCALAR_CORE}/${RISCV_ARCH}_zvl${VREG_W}_vl${VLANE_W}")
set(VERILATOR_MODEL "${VERILATOR_SIM_BUILD}/verilated_model")

# ---- runtime libraries (shared by all suites) -----------------------------
add_subdirectory(runtime/etiss)
add_subdirectory(runtime/verilator_vicuna2)

# ---- benchmark / program suites -------------------------------------------
add_subdirectory(src)
