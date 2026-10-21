#!/usr/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
CODEGEN_DIR="$PROJECT_ROOT/etiss-pe/code_gen"
M2ISAR_DIR="$CODEGEN_DIR/generators/M2-ISA-R"
RVV_COREDSL_DIR="$CODEGEN_DIR/descriptions/core_dsl/etiss_arch_riscv"

source "$M2ISAR_DIR/venv/bin/activate"
coredsl2_parser "$RVV_COREDSL_DIR/top.core_desc"
etiss_writer "$RVV_COREDSL_DIR/gen_model/top.m2isarmodel" --fill-mode auto