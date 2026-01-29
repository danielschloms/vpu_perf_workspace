#!/usr/bin/bash

###################################################################
# Builds RTL simulators and simple example programs, runs them on #         
# Verilator and ETISS, and performs an accuracy comparison.       #
###################################################################

# Terminal color
MAGENTA='\033[0;35m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${MAGENTA}Running simple tests${NC}"

SCRIPTS_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_ROOT_DIR="$(dirname "$SCRIPTS_DIR")"
VICUNA_DIR_NAME=Vicuna2
VICUNA_DIR=$PROJECT_ROOT_DIR/$VICUNA_DIR_NAME
TESTING_DIR=$PROJECT_ROOT_DIR/Perf_Comparison

python3 $TESTING_DIR/testing/run-test-matrix.py --build_tests --run_both --compare --ctarget sanitycheck