cmake_minimum_required(VERSION 3.10)


set(RISCV_ARCH "rv32im_zve32x" CACHE STRING "RISC-V architecture (-march)")
set(VLEN "64" CACHE STRING "The VLEN")
set(ZVL_SUFFIX "_zvl${VLEN}b")
set(FULL_ARCH "${RISCV_ARCH}${ZVL_SUFFIX}")
set(RISCV_ABI "ilp32" CACHE STRING "RISC-V ABI (-mabi)")
# set(AUTOVEC_FLAGS "-fvectorize -fslp-vectorize")
set(AUTOVEC_FLAGS "")

set(RISCV_TOOLCHAIN_PREFIX "" CACHE STRING "optional prefix for the riscv toolchain in case it is not on the path")
# set(RISCV_TOOLCHAIN_PREFIX "$ENV{RISCV_GCC_DIR}/${RISCV_ARCH}")
set(RISCV_TOOLCHAIN_BASENAME "riscv32-unknown-elf" CACHE STRING "base name of the toolchain executables")

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_ASM_COMPILER clang)

set(CMAKE_OBJCOPY llvm-objcopy)
set(CMAKE_OBJDUMP llvm-objdump)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__riscv__ -march=${FULL_ARCH} -mabi=${RISCV_ABI} --target=riscv32")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --gcc-toolchain=${RISCV_TOOLCHAIN_PREFIX} --sysroot=${RISCV_TOOLCHAIN_PREFIX}/${RISCV_TOOLCHAIN_BASENAME}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__riscv__ -march=${FULL_ARCH} -mabi=${RISCV_ABI} --target=riscv32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --gcc-toolchain=${RISCV_TOOLCHAIN_PREFIX} --sysroot=${RISCV_TOOLCHAIN_PREFIX}/${RISCV_TOOLCHAIN_BASENAME}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -D__riscv__ -march=${FULL_ARCH} -mabi=${RISCV_ABI} --target=riscv32")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} --gcc-toolchain=${RISCV_TOOLCHAIN_PREFIX} --sysroot=${RISCV_TOOLCHAIN_PREFIX}/${RISCV_TOOLCHAIN_BASENAME}")
set(CMAKE_EXE_LINKER_FLAGS "-march=${FULL_ARCH} -mabi=${RISCV_ABI} -fuse-ld=lld")

# set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 ${AUTOVEC_FLAGS}")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 ${AUTOVEC_FLAGS}")


set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ${FULL_ARCH})

SET(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
