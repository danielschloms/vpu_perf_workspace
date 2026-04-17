#!/usr/bin/env bash

SCRIPTS_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
PROJECT_ROOT_DIR="$(dirname "$SCRIPTS_DIR")"

CODE_GEN_DIR="$PROJECT_ROOT_DIR/Perfsim/code_gen"
M2ISAR_DIR="$CODE_GEN_DIR/generators/M2-ISA-R"

ETISS_ARCH_RV_DIR="$CODE_GEN_DIR/descriptions/core_dsl/etiss_arch_riscv"
CDSL_TOP="$ETISS_ARCH_RV_DIR/top.core_desc"
M2ISARMODEL_TOP="$ETISS_ARCH_RV_DIR/gen_model/top.m2isarmodel"

source $M2ISAR_DIR/venv/bin/activate

python3 -m m2isar.frontends.coredsl2.parser $CDSL_TOP
python3 -m m2isar.backends.etiss.writer $M2ISARMODEL_TOP --separate --static-scalars

ETISS_ARCH_DIR="$PROJECT_ROOT_DIR/Perfsim/etiss-perf-sim/etiss/ArchImpl"

cp -r $ETISS_ARCH_RV_DIR/gen_output/top/* $ETISS_ARCH_DIR

declare -a VLENS=("64" "128" "256" "512" "1024")

cd $ETISS_ARCH_DIR
for VLEN in "${VLENS[@]}"
do
    git restore RV32IMACFDV_zvl${VLEN}b/RV32IMACFDV_zvl${VLEN}b.h
    git restore RV32IMACFDV_zvl${VLEN}b/RV32IMACFDV_zvl${VLEN}bArch.cpp
    git restore RV32IMACFDV_zvl${VLEN}b/RV32IMACFDV_zvl${VLEN}bArchSpecificImp.cpp
    git restore RV32IMACFDV_zvl${VLEN}b/RV32IMACFDV_zvl${VLEN}bArchSpecificImp.h
    git restore RV32IMACFDV_zvl${VLEN}b/RV32IMACFDV_zvl${VLEN}bFuncs.h
    git restore RV32IMACFDV_zvl${VLEN}b/RV32IMACFDV_zvl${VLEN}bGDBCore.h
done

$PROJECT_ROOT_DIR/Perfsim/etiss-perf-sim/rebuild.sh
