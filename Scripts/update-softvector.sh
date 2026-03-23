#!/usr/bin/env bash

SCRIPTS_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
PROJECT_ROOT_DIR="$(dirname "$SCRIPTS_DIR")"

ETISS_SV_DIR="$PROJECT_ROOT_DIR/Perfsim/etiss-perf-sim/etiss/build_dir/_deps/softvector_srcs-src"
ETISS_SV_INCLUDE="$ETISS_SV_DIR/include/"
ETISS_SV_SRC="$ETISS_SV_DIR/src/"
ETISS_SV_MR="$ETISS_SV_DIR/mr-sv/"

SV_DIR="$PROJECT_ROOT_DIR/Softvector"
SV_INCLUDE="$SV_DIR/include/"
SV_SRC="$SV_DIR/src/"
SV_MR="$SV_DIR/mr-sv/"

rsync -a $SV_INCLUDE $ETISS_SV_INCLUDE
rsync -a $SV_SRC $ETISS_SV_SRC
# rsync -a $SV_MR $ETISS_SV_MR

cp $SV_DIR/CMakeLists.txt $ETISS_SV_DIR

$PROJECT_ROOT_DIR/Perfsim/etiss-perf-sim/rebuild.sh
