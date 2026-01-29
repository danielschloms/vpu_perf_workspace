#!/usr/bin/env bash

########################
# Build RTL simulators #
########################

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

# VLANE_WIDTH must be <= VLEN / 2, at least 32, and a power of 2
$VICUNA_DIR/build_rtl.sh --arch rv32im_zve32x --vlen 64 --vlane_width 32
$VICUNA_DIR/build_rtl.sh --arch rv32im_zve32x --vlen 128 --vlane_width 32
$VICUNA_DIR/build_rtl.sh --arch rv32im_zve32x --vlen 128 --vlane_width 64

