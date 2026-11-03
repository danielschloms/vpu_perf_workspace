#!/usr/bin/bash

PROGRAMS_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_ROOT_DIR="$(dirname "$PROGRAMS_DIR")"

VICUNA_DIR="$PROJECT_ROOT_DIR/Vicuna2"
PERFSIM_DIR="$PROJECT_ROOT_DIR/Perfsim"
ETISS_BUILD_BASE_DIR="$PROGRAMS_DIR/build"
VERILATOR_BUILD_BASE_DIR="$VICUNA_DIR/build_from_other"
RISCV_GCC_DIR="$PROJECT_ROOT_DIR/Third_Party/RISCV_GCC"

export RISCV_GCC_DIR=$RISCV_GCC_DIR
POSITIONAL_ARGS=()

# Default arguments
BUILD_TYPE="Release"
COMPILER="llvm"
ARCH="rv32im_zve32x"
ABI="ilp32"
VLEN="64"
GENERATOR="Ninja"
CMAKE_TARGET="all"
CLEAN_BEFORE="false"
while [[ $# -gt 0 ]]; do
  case $1 in
    --arch)
      ARCH="$2"
      shift # past argument
      shift # past value
      ;;
    --abi)
      ABI="$2"
      shift # past argument
      shift # past value
      ;;
    --vlen)
      VLEN="$2"
      shift # past argument
      shift # past value
      ;;
    --compiler)
      COMPILER="$2"
      shift # past argument
      shift # past value
      ;;
    --target)
      CMAKE_TARGET="$2"
      shift # past argument
      shift # past value
      ;;
    --debug)
      BUILD_TYPE="Debug"
      shift # past argument
      ;;
    --clean)
      CLEAN_BEFORE="true"
      shift # past argument
      ;;
    --ml)
      CMAKE_TARGET="ml_bench"
      shift # past argument
      ;;
    --sanity)
      CMAKE_TARGET="sanitycheck"
      shift # past argument
      ;;
    -*|--*)
      >&2 echo "Unknown option $1"
      exit 1
      ;;
    *)
      POSITIONAL_ARGS+=("$1") # save positional arg
      shift # past argument
      ;;
  esac
done

set -- "${POSITIONAL_ARGS[@]}" # restore positional parameters

ZVL_STRING="zvl${VLEN}b"
ETISS_BUILD_DIR=$PROGRAMS_DIR/build/etiss/$ARCH/$ZVL_STRING
QEMU_BUILD_DIR=$PROGRAMS_DIR/build/qemu/$ARCH/$ZVL_STRING
VERILATOR_BUILD_DIR=$VICUNA_DIR/build/verilator/$ARCH/$ZVL_STRING
TOOLCHAIN="$PROGRAMS_DIR/toolchain_files/${COMPILER}-toolchain.cmake"
INSTALL_PATH_ETISS=$PERFSIM_DIR/target_sw/examples/Vicuna/custom/$ARCH/$ZVL_STRING
INSTALL_PATH_QEMU=$PROJECT_ROOT_DIR/qemu-testing/bins/$ARCH/$ZVL_STRING

RV_GCC_PREFIX="$HOME/opt/riscv"

if [[ "$CLEAN_BEFORE" = "true" ]]; then
  rm -rf $ETISS_BUILD_DIR
  rm -rf $VERILATOR_BUILD_DIR
fi

cmake -S $PROGRAMS_DIR -B $ETISS_BUILD_DIR \
  -DETISS=On \
  -DVERILATOR=Off \
  -DQEMU=Off \
  -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN \
  -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH_ETISS \
  -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
  -DRISCV_ARCH=$ARCH \
  -DRISCV_ABI=$ABI \
  -DRISCV_TOOLCHAIN_PREFIX=$RV_GCC_PREFIX \
  -DVLEN=$VLEN \
  -G "$GENERATOR"

# cmake -S $PROGRAMS_DIR -B $QEMU_BUILD_DIR \
#   -DETISS=Off \
#   -DVERILATOR=Off \
#   -DQEMU=On \
#   -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN \
#   -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH_QEMU \
#   -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
#   -DRISCV_ARCH=$ARCH \
#   -DRISCV_ABI=$ABI \
#   -DVLEN=$VLEN \
#   -G "$GENERATOR"

cmake -S $PROGRAMS_DIR -B $VERILATOR_BUILD_DIR \
  -DETISS=Off \
  -DVERILATOR=On \
  -DQEMU=Off \
  -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN \
  -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH_VERILATOR \
  -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
  -DRISCV_ARCH=$ARCH \
  -DRISCV_ABI=$ABI \
  -DRISCV_TOOLCHAIN_PREFIX=$RV_GCC_PREFIX \
  -DVLEN=$VLEN \
  -G "$GENERATOR"

cmake --build $ETISS_BUILD_DIR --target $CMAKE_TARGET -j$(nproc)
# cmake --build $QEMU_BUILD_DIR --target $CMAKE_TARGET -j$(nproc)
cmake --build $VERILATOR_BUILD_DIR --target $CMAKE_TARGET -j$(nproc)
cmake --install $ETISS_BUILD_DIR
# cmake --install $QEMU_BUILD_DIR

GCC_ARCH_DIR=$RISCV_GCC_DIR/$ARCH
GCC_PREFIX="riscv32-unknown-elf"
OBJDUMP="$GCC_ARCH_DIR/bin/$GCC_PREFIX-objdump"

mkdir -p "$INSTALL_PATH_ETISS/dump"

for f in $(find $INSTALL_PATH_ETISS/bin -type f -mmin -5); do
    echo "objdump $(basename $f)"
    $OBJDUMP -D "$f" > $INSTALL_PATH_ETISS/dump/$(basename $f).dump
done

