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

echo -e "${BLUE}Build RTL simulators${NC}"
# Using --target dummy because either --target or --ctarget is currently required
# python3 $TESTING_DIR/testing/run-test-matrix.py --build_rtl --target dummy

echo -e "${Blue}Build, run, and compare tests${NC}"

# Toycar only
python3 $TESTING_DIR/testing/run-test-matrix.py --build_tests --run_both --compare --target tflm_toy

# All ML benchmarks (AWW and VWW take a *long* time in HW simulation)
# python3 $TESTING_DIR/testing/run-test-matrix.py --build_tests --run_both --compare --ctarget ml_bench

# Simple examples
python3 $TESTING_DIR/testing/run-test-matrix.py --build_tests --run_both --compare --ctarget sanitycheck