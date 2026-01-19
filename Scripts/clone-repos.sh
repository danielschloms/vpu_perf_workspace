#!/usr/bin/bash

#############################################################################
# Clone repositories used for performance simulation & comparison with RTL. #
# Third party tools are cloned and installed in "install-thirdparty.sh".    #
#############################################################################

# Terminal color
MAGENTA='\033[0;35m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${MAGENTA}Cloning Repositories${NC}"

SCRIPTS_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_ROOT_DIR="$(dirname "$SCRIPTS_DIR")"
THIRD_PARTY_SRC_DIR="$PROJECT_ROOT_DIR/Third_Party_Sources"

mkdir -p $THIRD_PARTY_SRC_DIR

echo "Project Root Directory: $PROJECT_ROOT_DIR"
echo "Scripts Directory: $SCRIPTS_DIR"
echo "Third Party Sources Directory: $THIRD_PARTY_SRC_DIR"

# Vicuna 2.0 RTL Repository
echo -e "${BLUE}Cloning Vicuna${NC}"
VICUNA_DIR_NAME=Vicuna2
VICUNA_PATH=$PROJECT_ROOT_DIR/$VICUNA_DIR_NAME

if [ -d "$VICUNA_PATH" ]; then
    echo "$VICUNA_PATH already exists, skipping."
else
    git clone git@github.com:danielschloms/vicuna2_tinyml_benchmarking.git -b daniel-dev $VICUNA_PATH
fi

# Target RISC-V Program Repository
echo -e "${BLUE}Cloning RISC-V Programs${NC}"
PROGRAM_DIR_NAME=RISCV_Programs
PROGRAM_PATH=$PROJECT_ROOT_DIR/$PROGRAM_DIR_NAME

if [ -d "$PROGRAM_PATH" ]; then
    echo "$PROGRAM_PATH already exists, skipping."
else
    git clone git@github.com:danielschloms/etiss_riscv_examples.git -b daniel-dev $PROGRAM_PATH
fi

# Performance Simulator Workspace Repository
echo -e "${BLUE}Cloning Performance Simulator Workspace${NC}"
PERFSIM_DIR_NAME=Perfsim
PERFSIM_PATH=$PROJECT_ROOT_DIR/$PERFSIM_DIR_NAME

if [ -d "$PERFSIM_PATH" ]; then
    echo "$PERFSIM_PATH already exists, skipping."
else
    git clone git@github.com:danielschloms/perfsim_workspace.git -b daniel-dev $PERFSIM_PATH
fi

# Comparison Repository
echo -e "${BLUE}Cloning Performance Comparison Workspace${NC}"
COMP_DIR_NAME=Perf_Comparison
COMP_PATH=$PROJECT_ROOT_DIR/$COMP_DIR_NAME

if [ -d "$COMP_PATH" ]; then
    echo "$COMP_PATH already exists, skipping."
else
    git clone git@github.com:danielschloms/rvv_testing.git $COMP_PATH
fi