# Cross-compile the programs/ suite for bare-metal RV32 with LLVM/Clang.
#
# Only the compiler front-end changes: Clang is pointed at the project's normal
# RISC-V GCC toolchain via --gcc-toolchain (which also selects its --sysroot:
# newlib headers, crt, libc, libgcc) and uses that toolchain's binutils for the
# post-build objcopy/objdump and for ar/ranlib.  This keeps ABI / libc / tooling
# identical to the default GCC build so the ELF, .vmem and *_dump.txt artefacts
# are directly comparable.
#
# The -march / -mabi flags are intentionally NOT set here: each suite derives
# them from the hardware config (e.g. EMBENCH_MARCH / EMBENCH_MABI in
# programs/src/embench-iot/CMakeLists.txt) and adds them in the SUITE's flag
# list, so injecting them here would duplicate / fight with those.
#
# Usage:
#   cmake -S programs -B programs/build-llvm \
#         -DCMAKE_TOOLCHAIN_FILE=programs/cmake/toolchain-llvm.cmake \
#         [-DRISCV_GCC_TOOLCHAIN=/path/to/rv32im_zve32x] \
#         [<other options, e.g. -DEMBENCH_ONLY=huffbench>]
#
# The RISC-V GCC toolchain is resolved from, in order:
#   1. -DRISCV_GCC_TOOLCHAIN=<path> (or the CMAKE_RISCV_GCC_TOOLCHAIN var)
#   2. the $RISCV_GCC_TOOLCHAIN environment variable
#   3. $HOME/opt/rv32im_zve32x   (the path used by scripts/build_programs.sh)

# ---- locate the RISC-V GCC toolchain used as sysroot / gcc-toolchain ---------
# Respect an explicit -DRISCV_GCC_TOOLCHAIN=<path> (cache) on the first pass.
if(NOT DEFINED RISCV_GCC_TOOLCHAIN)
    if(DEFINED CMAKE_RISCV_GCC_TOOLCHAIN AND NOT CMAKE_RISCV_GCC_TOOLCHAIN STREQUAL "")
        set(RISCV_GCC_TOOLCHAIN "${CMAKE_RISCV_GCC_TOOLCHAIN}")
    elseif(DEFINED ENV{RISCV_GCC_TOOLCHAIN} AND NOT "$ENV{RISCV_GCC_TOOLCHAIN}" STREQUAL "")
        set(RISCV_GCC_TOOLCHAIN "$ENV{RISCV_GCC_TOOLCHAIN}")
    else()
        set(RISCV_GCC_TOOLCHAIN "$ENV{HOME}/opt/rv32im_zve32x")
    endif()
    set(RISCV_GCC_TOOLCHAIN "${RISCV_GCC_TOOLCHAIN}" CACHE PATH
        "RISC-V GCC toolchain used by Clang as sysroot/gcc-toolchain (binutils source)")
endif()

if(NOT EXISTS "${RISCV_GCC_TOOLCHAIN}/bin/riscv32-unknown-elf-gcc")
    message(FATAL_ERROR
        "RISC-V GCC toolchain not found at '${RISCV_GCC_TOOLCHAIN}'.\n"
        "Pass -DRISCV_GCC_TOOLCHAIN=<path> (or set RISCV_GCC_TOOLCHAIN) to a "
        "riscv32-unknown-elf GCC toolchain containing bin/riscv32-unknown-elf-gcc.")
endif()

# ---- target machine ----------------------------------------------------------
set(CMAKE_SYSTEM_NAME     Generic)   # bare-metal: CMake must not try to run target binaries
set(CMAKE_SYSTEM_PROCESSOR riscv32)
set(CMAKE_CROSSCOMPILING  ON)

# ---- compiler front-ends (LLVM/Clang) ----------------------------------------
# Plain (non-cache) set() is the idiomatic toolchain-file form: it shadows the
# per-suite fallback compiler set in programs/CMakeLists.txt *before* project().
# (A bare `CACHE` without FORCE loses to that fallback; FORCE is only needed if
# you want to deliberately clobber an explicit user -D.)  The `clang`/`clang++`
# names are resolved via PATH; point these at a different Clang by editing them.
set(CMAKE_C_COMPILER   clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_ASM_COMPILER clang)

# Emit bare-metal RV32 ELF.
set(CMAKE_C_COMPILER_TARGET   riscv32-unknown-elf)
set(CMAKE_CXX_COMPILER_TARGET riscv32-unknown-elf)
set(CMAKE_ASM_COMPILER_TARGET riscv32-unknown-elf)

# ---- use the RISC-V GCC toolchain as sysroot + binutils ----------------------
# --gcc-toolchain makes Clang search <toolchain>/riscv32-unknown-elf/{include,lib}
# and <toolchain>/lib/gcc/riscv32-unknown-elf/<ver> for newlib headers, crt and
# libgcc, and drive the toolchain's riscv32-unknown-elf-ld (bfd) at link time.
set(_gcc_toolchain_flag "--gcc-toolchain=${RISCV_GCC_TOOLCHAIN}")
set(CMAKE_C_FLAGS_INIT            "${_gcc_toolchain_flag}")
set(CMAKE_CXX_FLAGS_INIT          "${_gcc_toolchain_flag}")
set(CMAKE_ASM_FLAGS_INIT          "${_gcc_toolchain_flag}")
set(CMAKE_EXE_LINKER_FLAGS_INIT   "${_gcc_toolchain_flag}")

# Pin the binutils to the same GCC toolchain. CMake's auto-detection
# (clang -print-prog-name=...) may drop --target/--gcc-toolchain and fall back
# to host objcopy, which cannot read RISC-V ELF. The verilator POST_BUILD and
# the *_dump.txt generation rely on these.
if(NOT CMAKE_OBJCOPY)
    set(CMAKE_OBJCOPY "${RISCV_GCC_TOOLCHAIN}/bin/riscv32-unknown-elf-objcopy" CACHE FILEPATH "objcopy")
endif()
if(NOT CMAKE_OBJDUMP)
    set(CMAKE_OBJDUMP "${RISCV_GCC_TOOLCHAIN}/bin/riscv32-unknown-elf-objdump" CACHE FILEPATH "objdump")
endif()
if(NOT CMAKE_AR)
    set(CMAKE_AR "${RISCV_GCC_TOOLCHAIN}/bin/riscv32-unknown-elf-ar" CACHE FILEPATH "archiver")
endif()
if(NOT CMAKE_RANLIB)
    set(CMAKE_RANLIB "${RISCV_GCC_TOOLCHAIN}/bin/riscv32-unknown-elf-ranlib" CACHE FILEPATH "ranlib")
endif()
if(NOT CMAKE_NM)
    set(CMAKE_NM "${RISCV_GCC_TOOLCHAIN}/bin/riscv32-unknown-elf-nm" CACHE FILEPATH "nm")
endif()

# ---- bare-metal cross-build workarounds --------------------------------------
# Don't link+run a probe executable to validate the compiler; there is no host
# crt0/entry point for riscv32-unknown-elf, so just compile a static lib.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# find_* should only resolve the RISC-V sysroot for target content, but keep
# host tools findable for find_program (srec_cat, host python, etc.).
set(CMAKE_FIND_ROOT_PATH "${RISCV_GCC_TOOLCHAIN}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
add_link_options("-fuse-ld=lld")

message(STATUS "LLVM toolchain: clang --target=riscv32-unknown-elf, gcc-toolchain=${RISCV_GCC_TOOLCHAIN}")

# NOTE: programs/runtime/etiss links with --specs=<etiss-semihost.specs>
# (expanding to -lc -letiss_crt0 -lsemihost). Clang does *not* honour GCC's
# --specs, so ETISS targets linked through this toolchain will not pull in
# etiss_crt0/libsemihost automatically. Build the verilator targets with this
# toolchain, or link etiss_crt0 + libsemihost explicitly when using Clang.
