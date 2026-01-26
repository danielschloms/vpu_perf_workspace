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

# Create Third_Party & Third_Party_Sources Directory
mkdir -p $PROJECT_ROOT_DIR/Third_Party
mkdir -p $PROJECT_ROOT_DIR/Third_Party_Sources

$SCRIPTS_DIR/clone-repos.sh
$SCRIPTS_DIR/install-thirdparty.sh

echo -e "${BLUE}Init Perfsim Submodules${NC}"
cd $PERFSIM_DIR
git submodule update --init --recursive

echo -e "${BLUE}Init Perfsim Workspace${NC}"
$PERFSIM_DIR/scripts/setup_workspace.sh