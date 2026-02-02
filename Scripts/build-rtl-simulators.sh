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

echo -e "${MAGENTA}Building RTL Simulators${NC}"

SCRIPTS_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_ROOT_DIR="$(dirname "$SCRIPTS_DIR")"
TESTING_DIR=$PROJECT_ROOT_DIR/Perf_Comparison

# Using --target dummy because either --target or --ctarget is currently required
python3 $TESTING_DIR/testing/run-test-matrix.py --build_rtl --target dummy