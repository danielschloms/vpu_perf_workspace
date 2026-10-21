#!/usr/bin/env bash
#
# Build the Verilated simulator for the CV32E40X/CV32A60X + Vicuna system.
#
# The simulator is built in a directory named after the hardware configuration,
# placed under rtl/vicuna2/build (override with --build-root):
#   <repo>/rtl/vicuna2/build/<scalar_core>/<riscv_arch>_zvl<vlen>_vl<lane_width>
#   e.g. rtl/vicuna2/build/cv32a60x/rv32im_zve32x_zvl128_vl32
#
# where <vlen> = VREG_W (vector register width) and <lane_width> = VLANE_W.
#
# All parameters can be passed on the command line (or exported as environment
# variables) and are forwarded to CMake as cached variables.
#
# Usage:
#   scripts/build_verilator.sh [options]
#
# Options:
#   --scalar-core <name>   Scalar core (cv32e40x | cv32a60x)      [default: cv32a60x]
#   --arch <isa>           RISC-V architecture config (RISCV_ARCH) [default: rv32im_zve32x]
#   --vlen <bits>          Vector register width / VLEN (VREG_W)   [default: 128]
#   --lane-width <bits>    Vector lane width (VLANE_W)             [default: 32]
#   --vmem-w <bits>        Vector memory interface width (VMEM_W)  [default: 32]
#   --vmem-ports <n>       Number of vector memory ports (VMEM_PORTS) [default: 1]
#   --build-root <path>    Base build directory            [default: <repo>/rtl/vicuna2/build]
#   --trace                Enable VCD traces (passes -DTRACE=ON)
#   --configure-only       Only run the CMake configure step
#   --jobs <n>             Parallel build jobs                     [default: nproc]
#   --help|-h              Show this help
#
# The same parameters may be set via environment variables:
#   SCALAR_CORE, RISCV_ARCH, VREG_W, VLANE_W, VMEM_W, VMEM_PORTS, TRACE

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
SOURCE_DIR="${REPO_ROOT}/rtl/vicuna2"

# Defaults (must match rtl/vicuna2/vector_config.cmake)
SCALAR_CORE="${SCALAR_CORE:-cv32a60x}"
RISCV_ARCH="${RISCV_ARCH:-rv32im_zve32x}"
VREG_W="${VREG_W:-128}"
VLANE_W="${VLANE_W:-32}"
VMEM_W="${VMEM_W:-32}"
VMEM_PORTS="${VMEM_PORTS:-1}"
TRACE="${TRACE:-OFF}"
BUILD_ROOT="${BUILD_ROOT:-${SOURCE_DIR}/build}"
JOBS="$(nproc 2>/dev/null || echo 1)"
CONFIGURE_ONLY=0

usage() {
    sed -n '2,40p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'
}

# --- argument parsing -------------------------------------------------------
while [[ $# -gt 0 ]]; do
    case "$1" in
        --scalar-core) SCALAR_CORE="$2"; shift 2 ;;
        --arch)        RISCV_ARCH="$2"; shift 2 ;;
        --vlen)        VREG_W="$2"; shift 2 ;;
        --lane-width)  VLANE_W="$2"; shift 2 ;;
        --vmem-w)      VMEM_W="$2"; shift 2 ;;
        --vmem-ports)  VMEM_PORTS="$2"; shift 2 ;;
        --build-root)  BUILD_ROOT="$2"; shift 2 ;;
        --trace)       TRACE=ON; shift ;;
        --configure-only) CONFIGURE_ONLY=1; shift ;;
        --jobs)        JOBS="$2"; shift 2 ;;
        --help|-h)     usage; exit 0 ;;
        *)
            echo "Unknown option: $1" >&2
            usage >&2
            exit 1
            ;;
    esac
done

# --- derive the configuration-specific build directory ----------------------
VPROC_CONFIG_NAME="${RISCV_ARCH}_zvl${VREG_W}_vl${VLANE_W}"
BUILD_DIR="${BUILD_ROOT}/${SCALAR_CORE}/${VPROC_CONFIG_NAME}"

echo "=============================================="
echo "  Verilator simulator build"
echo "  scalar_core : ${SCALAR_CORE}"
echo "  arch        : ${RISCV_ARCH}"
echo "  vlen (VREG) : ${VREG_W}"
echo "  lane width  : ${VLANE_W}"
echo "  vmem_w      : ${VMEM_W}"
echo "  vmem_ports  : ${VMEM_PORTS}"
echo "  trace       : ${TRACE}"
echo "  build dir   : ${BUILD_DIR}"
echo "=============================================="

mkdir -p "${BUILD_DIR}"

CMAKE_ARGS=(
    -S "${SOURCE_DIR}"
    -B "${BUILD_DIR}"
    "-DSCALAR_CORE=${SCALAR_CORE}"
    "-DRISCV_ARCH=${RISCV_ARCH}"
    "-DVREG_W=${VREG_W}"
    "-DVLANE_W=${VLANE_W}"
    "-DVMEM_W=${VMEM_W}"
    "-DVMEM_PORTS=${VMEM_PORTS}"
    "-DTRACE=${TRACE}"
)

echo "--> cmake ${CMAKE_ARGS[*]}"
cmake "${CMAKE_ARGS[@]}"

if [[ "${CONFIGURE_ONLY}" -eq 1 ]]; then
    echo "Configure done (skipping build)."
    exit 0
fi

echo "--> cmake --build \"${BUILD_DIR}\" --parallel ${JOBS}"
cmake --build "${BUILD_DIR}" --parallel "${JOBS}"

echo "Simulator built in ${BUILD_DIR}"
