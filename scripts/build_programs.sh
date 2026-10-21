#!/usr/bin/env bash
#
# Build the benchmark / program suites under programs/ (embench-iot, and
# optionally MLPerfTiny) with the RISC-V cross toolchain.
#
# Source:   programs/
# Build dir: <repo>/programs/build            (override with --build-root)
#
# The hardware configuration is forwarded to CMake so that the generated
# simulator paths (e.g. the Verilator model under rtl/vicuna2/build/<core>/...)
# match the simulator built by scripts/build_verilator.sh / build_etiss.sh.
#
# Usage:
#   scripts/build_programs.sh [options]
#
# Options:
#   --scalar-core <name>   Scalar core (cv32e40x | cv32a60x)   [default: cv32a60x]
#   --arch <isa>           RISC-V architecture config          [default: rv32im_zve32x]
#   --vlen <bits>          Vector register width / VLEN        [default: 128]
#   --lane-width <bits>    Vector lane width (VLANE_W)         [default: 32]
#   --vmem-w <bits>        Vector memory interface width       [default: 32]
#   --vmem-ports <n>       Number of vector memory ports       [default: 1]
#   --mem-w <bits>         Data memory interface width         [default: 32]
#   --mem-ports <n>        Number of data memory ports         [default: 1]
#   --mem-latency <n>      Data memory latency (cycles)        [default: 1]
#   --march <isa>          Emb-iot machine arch   [default: <riscv_arch>_zvl<vlen>b, e.g. rv32im_zve32x_zvl128b]
#   --mabi <abi>           Emb-iot machine ABI                 [default: ilp32]
#   --opt <flags>          Emb-iot optimisation level          [default: -O3]
#   --only <list>          Build only these benchmarks (semicolon list, e.g. "crc32;md5sum")
#   --etiss                Build ETISS targets                 [default: ON]
#   --no-etiss             Skip ETISS targets
#   --verilator            Build Verilator targets             [default: ON]
#   --no-verilator         Skip Verilator targets
#   --mlperftiny           Also build the MLPerfTiny suite (WIP)
#   -d, --debug            Use a Debug build type (default: none)
#   --build-type <t>       CMake build type (Release | Debug | ...)
#   --build-root <path>    Build directory                  [default: <repo>/programs/build]
#   --configure-only       Only run the CMake configure step
#   --jobs <n>             Parallel build jobs              [default: nproc]
#   --help|-h              Show this help
#
# Parameters may also be set via environment variables, e.g. SCALAR_CORE,
# RISCV_ARCH, VREG_W, VLANE_W, EMBENCH_ONLY, EMBENCH_MARCH.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
SOURCE_DIR="${REPO_ROOT}/programs"

# Defaults (must match programs/CMakeLists.txt and rtl/vicuna2/vector_config.cmake)
SCALAR_CORE="${SCALAR_CORE:-cv32a60x}"
RISCV_ARCH="${RISCV_ARCH:-rv32im_zve32x}"
VREG_W="${VREG_W:-128}"
VLANE_W="${VLANE_W:-32}"
VMEM_W="${VMEM_W:-32}"
VMEM_PORTS="${VMEM_PORTS:-1}"
MEM_W="${MEM_W:-32}"
MEM_PORTS="${MEM_PORTS:-1}"
MEM_LATENCY="${MEM_LATENCY:-1}"
# Derived from the HW config below (after arg parsing) unless overridden by
# --march/--mabi or the EMBENCH_MARCH/EMBENCH_MABI environment variables.
EMBENCH_MARCH="${EMBENCH_MARCH:-}"
EMBENCH_MABI="${EMBENCH_MABI:-}"
EMBENCH_OPT="${EMBENCH_OPT:--O3}"
EMBENCH_ETISS="${EMBENCH_ETISS:-ON}"
EMBENCH_VERILATOR="${EMBENCH_VERILATOR:-ON}"
EMBENCH_MLPERFTINY="${EMBENCH_MLPERFTINY:-OFF}"
EMBENCH_ONLY="${EMBENCH_ONLY:-}"

BUILD_TYPE="${BUILD_TYPE:-}"
BUILD_DIR="${BUILD_DIR:-${SOURCE_DIR}/build}"
JOBS="$(nproc 2>/dev/null || echo 1)"
CONFIGURE_ONLY=0

usage() {
    sed -n '2,80p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'
}

# --- argument parsing -------------------------------------------------------
while [[ $# -gt 0 ]]; do
    case "$1" in
        --scalar-core)  SCALAR_CORE="$2"; shift 2 ;;
        --arch)         RISCV_ARCH="$2"; shift 2 ;;
        --vlen)         VREG_W="$2"; shift 2 ;;
        --lane-width)   VLANE_W="$2"; shift 2 ;;
        --vmem-w)       VMEM_W="$2"; shift 2 ;;
        --vmem-ports)   VMEM_PORTS="$2"; shift 2 ;;
        --mem-w)        MEM_W="$2"; shift 2 ;;
        --mem-ports)    MEM_PORTS="$2"; shift 2 ;;
        --mem-latency)  MEM_LATENCY="$2"; shift 2 ;;
        --march)        EMBENCH_MARCH="$2"; shift 2 ;;
        --mabi)         EMBENCH_MABI="$2"; shift 2 ;;
        --opt)          EMBENCH_OPT="$2"; shift 2 ;;
        --only)         EMBENCH_ONLY="$2"; shift 2 ;;
        --etiss)        EMBENCH_ETISS=ON; shift ;;
        --no-etiss)     EMBENCH_ETISS=OFF; shift ;;
        --verilator)    EMBENCH_VERILATOR=ON; shift ;;
        --no-verilator) EMBENCH_VERILATOR=OFF; shift ;;
        --mlperftiny)   EMBENCH_MLPERFTINY=ON; shift ;;
        -d|--debug)     BUILD_TYPE="Debug"; shift ;;
        --build-type)   BUILD_TYPE="$2"; shift 2 ;;
        --build-root)   BUILD_DIR="$2"; shift 2 ;;
        --configure-only) CONFIGURE_ONLY=1; shift ;;
        --jobs)         JOBS="$2"; shift 2 ;;
        --help|-h)      usage; exit 0 ;;
        *)
            echo "Unknown option: $1" >&2
            usage >&2
            exit 1
            ;;
    esac
done

# Derive the default machine flags from the (possibly overridden) HW config.
if [[ -z "${EMBENCH_MARCH}" ]]; then
    EMBENCH_MARCH="${RISCV_ARCH}_zvl${VREG_W}b"
fi
if [[ -z "${EMBENCH_MABI}" ]]; then
    EMBENCH_MABI="ilp32"
fi

if [[ ! -f "${SOURCE_DIR}/CMakeLists.txt" ]]; then
    echo "ERROR: programs CMake project not found at ${SOURCE_DIR}" >&2
    exit 1
fi

echo "=============================================="
echo "  programs build"
echo "  source dir  : ${SOURCE_DIR}"
echo "  build dir   : ${BUILD_DIR}"
echo "  build type  : ${BUILD_TYPE:-none}"
echo "  scalar_core : ${SCALAR_CORE}"
echo "  arch        : ${RISCV_ARCH}"
echo "  vlen (VREG) : ${VREG_W}"
echo "  lane width  : ${VLANE_W}"
echo "  march/mabi  : ${EMBENCH_MARCH} / ${EMBENCH_MABI}"
echo "  etiss       : ${EMBENCH_ETISS}"
echo "  verilator   : ${EMBENCH_VERILATOR}"
echo "  mlperftiny  : ${EMBENCH_MLPERFTINY}"
echo "=============================================="

mkdir -p "${BUILD_DIR}"

CMAKE_ARGS=(
    -S "${SOURCE_DIR}"
    -B "${BUILD_DIR}"
    # Always set the build type (passing empty clears any cached value) so the
    # default matches a fresh configure (no -DNDEBUG / -O3 from the build type).
    "-DCMAKE_BUILD_TYPE=${BUILD_TYPE}"
    "-DSCALAR_CORE=${SCALAR_CORE}"
    "-DRISCV_ARCH=${RISCV_ARCH}"
    "-DVREG_W=${VREG_W}"
    "-DVLANE_W=${VLANE_W}"
    "-DVMEM_W=${VMEM_W}"
    "-DVMEM_PORTS=${VMEM_PORTS}"
    "-DMEM_W=${MEM_W}"
    "-DMEM_PORTS=${MEM_PORTS}"
    "-DMEM_LATENCY=${MEM_LATENCY}"
    "-DEMBENCH_MARCH=${EMBENCH_MARCH}"
    "-DEMBENCH_MABI=${EMBENCH_MABI}"
    "-DEMBENCH_OPT=${EMBENCH_OPT}"
    "-DEMBENCH_ETISS=${EMBENCH_ETISS}"
    "-DEMBENCH_VERILATOR=${EMBENCH_VERILATOR}"
    "-DEMBENCH_MLPERFTINY=${EMBENCH_MLPERFTINY}"
)
if [[ -n "${EMBENCH_ONLY}" ]]; then
    CMAKE_ARGS+=("-DEMBENCH_ONLY=${EMBENCH_ONLY}")
fi

echo "--> cmake ${CMAKE_ARGS[*]}"
cmake "${CMAKE_ARGS[@]}"

if [[ "${CONFIGURE_ONLY}" -eq 1 ]]; then
    echo "Configure done (skipping build)."
    exit 0
fi

echo "--> cmake --build \"${BUILD_DIR}\" --parallel ${JOBS}"
cmake --build "${BUILD_DIR}" --parallel "${JOBS}"

echo "Programs built in ${BUILD_DIR}"
