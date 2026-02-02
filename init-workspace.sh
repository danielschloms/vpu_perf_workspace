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

# Clone TUM repos and install Verilator + RISC-V GCC
$SCRIPTS_DIR/clone-repos.sh
$SCRIPTS_DIR/install-thirdparty.sh

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

echo -e "${BLUE}Init Perfsim Submodules${NC}"
cd $PERFSIM_DIR
git submodule update --init --recursive

echo -e "${BLUE}Check out known working Perfsim commits${NC}"
M2_ISA_R_COMMIT="178cc2395a6155ec3955a83fbc2ba09586500f77"
M2_ISA_R_PERF_COMMIT="b0336e9125230833566b8b9bfac6bcf09df40234"
GENERATORS_DIR="$PERFSIM_DIR/code_gen/generators"
M2_ISA_R_DIR="$GENERATORS_DIR/M2-ISA-R"
M2_ISA_R_PERF_DIR="$GENERATORS_DIR/M2-ISA-R-Perf"

cd $M2_ISA_R_PERF_DIR
git checkout $M2_ISA_R_PERF_COMMIT

cd $M2_ISA_R_DIR
git checkout $M2_ISA_R_COMMIT

echo -e "${BLUE}Replacing M2-ISA-R CoreDSL2 Parser${NC}"
# TODO: could change .g4 grammar and rebuild it instead
PARSER_FILE="$M2_ISA_R_DIR/m2isar/frontends/coredsl2/parser_gen/CoreDSL2Parser.py"
rm $PARSER_FILE
cp $SCRIPTS_DIR/CoreDSL2Parser.py $PARSER_FILE

echo -e "${BLUE}Init Perfsim Workspace${NC}"
$PERFSIM_DIR/scripts/setup_workspace.sh