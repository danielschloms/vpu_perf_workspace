#!/usr/bin/env bash
#
# Build the tflite-micro static library (libtensorflow-microlite.a) for the
# RISC-V target, using the riscv32-unknown-elf GNU toolchain.
#
# This drives tflite-micro's own Makefile build (TARGET=riscv32_generic), which
# cross-compiles the framework + reference kernels and downloads a couple of
# small third-party deps (flatbuffers, kissfft, eyalroz_printf) into the
# submodule.  The resulting archive is copied to TFLM_OUT so the CMake target
# can link it from a fixed, stable path.
#
# Env (set by CMake):
#   TFLM_DIR     path to the tflite-micro submodule
#   TFLM_OUT     full path of the libtensorflow-microlite.a to produce
#   TFLM_MARCH   RISC-V -march (e.g. rv32im_zve32x_zvl128b)
#   TFLM_MABI    RISC-V -mabi  (e.g. ilp32)
#
# Idempotent: if TFLM_OUT already exists, no-op.

set -euo pipefail

TFLM_DIR="${TFLM_DIR:?TFLM_DIR not set}"
TFLM_OUT="${TFLM_OUT:?TFLM_OUT not set}"
TFLM_MARCH="${TFLM_MARCH:?TFLM_MARCH not set}"
TFLM_MABI="${TFLM_MABI:-ilp32}"

if [ -f "${TFLM_OUT}" ]; then
  echo "tflite-micro already built: ${TFLM_OUT}"
  exit 0
fi

GC="${TFLM_MARKER_CC:-$(command -v riscv32-unknown-elf-gcc)}"
if [ -z "${GC}" ]; then
  echo "error: riscv32-unknown-elf-gcc not found on PATH" >&2
  exit 1
fi
TOOLCHAIN_BIN="$(dirname "${GC}")/"
echo "tflite-micro: toolchain dir = ${TOOLCHAIN_BIN}"

cd "${TFLM_DIR}"

MAKE_BASE=(make -f tensorflow/lite/micro/tools/make/Makefile)
COMMON=(
  TARGET=riscv32_generic
  TARGET_ARCH=riscv32
  TARGET_TOOLCHAIN_PREFIX=riscv32-unknown-elf-
  TARGET_TOOLCHAIN_ROOT="${TOOLCHAIN_BIN}"
  SKIP_DOWNLOADS=1
  RISCV_ARCH="${TFLM_MARCH}"
  RISCV_ABI="${TFLM_MABI}"
)

echo "tflite-micro: third_party_downloads"
"${MAKE_BASE[@]}" "${COMMON[@]}" third_party_downloads

echo "tflite-micro: libtflm"
"${MAKE_BASE[@]}" "${COMMON[@]}" -j"$(nproc)" libtflm

LIB="$(find gen -name libtensorflow-microlite.a -print -quit)"
if [ -z "${LIB}" ]; then
  echo "error: libtensorflow-microlite.a not produced" >&2
  exit 1
fi

mkdir -p "$(dirname "${TFLM_OUT}")"
cp "${LIB}" "${TFLM_OUT}"
echo "tflite-micro: ${LIB} -> ${TFLM_OUT}"
