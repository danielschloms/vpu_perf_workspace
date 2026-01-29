#!/usr/bin/bash

########################
# Set up the workspace #
########################

# Terminal color
MAGENTA='\033[0;35m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

PROJECT_ROOT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SCRIPTS_DIR=$PROJECT_ROOT_DIR/Scripts
PERFSIM_DIR=$PROJECT_ROOT_DIR/Perfsim
VICUNA_DIR=$PROJECT_ROOT_DIR/Vicuna2

# Create Third_Party & Third_Party_Sources Directory
mkdir -p $PROJECT_ROOT_DIR/Third_Party
mkdir -p $PROJECT_ROOT_DIR/Third_Party_Sources

$SCRIPTS_DIR/clone-repos.sh
$SCRIPTS_DIR/install-thirdparty.sh

echo -e "${BLUE}Init Perfsim Submodules${NC}"
cd $PERFSIM_DIR
git submodule update --init --recursive

echo -e "${BLUE}Init Vicuna 2.0 Submodules${NC}"
cd $VICUNA_DIR
git submodule update --init --recursive

echo -e "${BLUE}Check out known working RTL commits${NC}"
VPROC_COMMIT="068a61cc88cf18cbc16df88d0dff667216a303e8"
FPU_COMMIT="1450626ec0b82e303327ce941cad1e9057d5781a"
CV32E40X_COMMIT="ecab818f27a9c4fb08a6c36a315f0743cec05b18"

cd $VICUNA_DIR/rtl/cv32e40x
git checkout $CV32E40X_COMMIT
cd $VICUNA_DIR/rtl/fpu_ss
git checkout $FPU_COMMIT
cd $VICUNA_DIR/rtl/vproc_rtl
git checkout $VPROC_COMMIT

echo -e "${BLUE}Init Perfsim Workspace${NC}"
$PERFSIM_DIR/scripts/setup_workspace.sh