#!/usr/bin/env bash

#######################################
# Clone and install third party tools #
#######################################

# Terminal color
MAGENTA='\033[0;35m'
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${MAGENTA}Cloning & Installing Third Party Repositories${NC}"

SCRIPTS_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_ROOT_DIR="$(dirname "$SCRIPTS_DIR")"

THIRD_PARTY_SRC_DIR="$PROJECT_ROOT_DIR/Third_Party_Sources"
THIRD_PARTY_INSTALL_DIR="$PROJECT_ROOT_DIR/Third_Party"

mkdir -p $THIRD_PARTY_SRC_DIR
mkdir -p $THIRD_PARTY_INSTALL_DIR

# Clone Verilator
echo -e "${BLUE}Cloning Verilator${NC}"
VERILATOR_DIR_NAME=Verilator
VERILATOR_SRC_PATH=$THIRD_PARTY_SRC_DIR/$VERILATOR_DIR_NAME
VERILATOR_INSTALL_PATH=$THIRD_PARTY_INSTALL_DIR/$VERILATOR_DIR_NAME
git clone https://github.com/verilator/verilator $VERILATOR_SRC_PATH

# Install Verilator
echo -e "${BLUE}Installing Verilator to ${VERILATOR_INSTALL_PATH}${NC}"
# unsetenv VERILATOR_ROOT   # For csh; ignore error if on bash
unset VERILATOR_ROOT        # For bash
cd $VERILATOR_SRC_PATH
# git pull                    # Make sure git repository is up-to-date
# git tag                   # See what versions exist
# git checkout master       # Use development branch (e.g. recent bug fixes)
# git checkout stable       # Use most recent stable release
git checkout v5.030         # Switch to specified release version

autoconf                                        # Create ./configure script
./configure --prefix $VERILATOR_INSTALL_PATH    # Configure and create Makefile
make -j$(nproc)                                 # Build Verilator itself (if error, try just 'make')
make install

# Clone RISC-V GNU Toolchain
echo -e "${BLUE}Cloning RISC-V GCC Toolchain${NC}"
RV_TOOLCHAIN_DIR_NAME=RISCV_GCC
RV_TOOLCHAIN_SRC_PATH=$THIRD_PARTY_SRC_DIR/$RV_TOOLCHAIN_DIR_NAME
RV_TOOLCHAIN_BASE_PATH=$THIRD_PARTY_INSTALL_DIR/$RV_TOOLCHAIN_DIR_NAME
git clone git@github.com:riscv-collab/riscv-gnu-toolchain.git $RV_TOOLCHAIN_SRC_PATH

build_and_install_rv_gcc() {
    if [ "$#" -ne 2 ]; then
        echo "Error, build_and_install_rv_gcc() requires ARCH and ABI, skipping"
    else
        cd $RV_TOOLCHAIN_SRC_PATH
        make clean
        INSTALL_PATH=$RV_TOOLCHAIN_BASE_PATH/$1
        echo -e "${BLUE}Building with ARCH = $1, ABI = $2${NC}"
        echo -e "${BLUE}Installing to $INSTALL_PATH${NC}"
        ./configure --prefix=$INSTALL_PATH --with-arch=$1 --with-abi=$2 --enable-tui
        make -j$(nproc)
        make install
        echo -e "${GREEN}Done${NC}"
    fi
}

# 32 bit scalar integer
build_and_install_rv_gcc rv32im_zicsr ilp32

# 32 bit scalar float
# build_and_install_rv_gcc rv32imf ilp32f

# 32 bit scalar float + half precision float
# build_and_install_rv_gcc rv32imf_zfh ilp32f

# 32 bit vector integer
build_and_install_rv_gcc rv32im_zve32x ilp32

# 32 bit vector float
# build_and_install_rv_gcc rv32imf_zve32f ilp32f

# 32 bit vector float + vector half precision float
# build_and_install_rv_gcc rv32imf_zfh_zve32f_zvfh ilp32f


