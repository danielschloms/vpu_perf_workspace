#!/usr/bin/env bash
#
# Build ETISS (Extendable Translating Instruction Set Simulator).
#
# Source:   etiss-pe/etiss-perf-sim/etiss
# Build dir: <etiss>/build (override with --build-root)
#
# Usage:
#   scripts/build_etiss.sh [options]
#
# Options:
#   -d, --debug          Build a Debug version (default: Release)
#   --build-root <path>  Build directory                  [default: <etiss>/build]
#   --install            Also run 'cmake --build ... --target install'
#   --configure-only     Only run the CMake configure step
#   --jobs <n>           Parallel build jobs              [default: nproc]
#   --help|-h            Show this help
#
# The build type may also be set via the ETISS_BUILD_TYPE environment variable.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
SOURCE_DIR="${REPO_ROOT}/etiss-pe/etiss-perf-sim/etiss"

# Defaults
BUILD_TYPE="${ETISS_BUILD_TYPE:-Release}"
BUILD_DIR="${BUILD_DIR:-${SOURCE_DIR}/build}"
INSTALL_PREFIX="${BUILD_DIR}/installed"
JOBS="$(nproc 2>/dev/null || echo 1)"
DO_INSTALL=0
CONFIGURE_ONLY=0

usage() {
    cat <<'EOF'
Build ETISS (Extendable Translating Instruction Set Simulator).

Source:   etiss-pe/etiss-perf-sim/etiss
Build dir: <etiss>/build (override with --build-root)

Usage:
  scripts/build_etiss.sh [options]

Options:
  -d, --debug          Build a Debug version (default: Release)
  --build-root <path>  Build directory                  [default: <etiss>/build]
  --install            Also run 'cmake --build ... --target install'
  --configure-only     Only run the CMake configure step
  --jobs <n>           Parallel build jobs              [default: nproc]
  --help|-h            Show this help

The build type may also be set via the ETISS_BUILD_TYPE environment variable.
EOF
}

# --- argument parsing -------------------------------------------------------
while [[ $# -gt 0 ]]; do
    case "$1" in
        -d|--debug)         BUILD_TYPE="Debug"; shift ;;
        --build-root)       BUILD_DIR="$2"; shift 2 ;;
        --install)          DO_INSTALL=1; shift ;;
        --configure-only)   CONFIGURE_ONLY=1; shift ;;
        --jobs)             JOBS="$2"; shift 2 ;;
        --help|-h)          usage; exit 0 ;;
        *)
            echo "Unknown option: $1" >&2
            usage >&2
            exit 1
            ;;
    esac
done

if [[ ! -f "${SOURCE_DIR}/CMakeLists.txt" ]]; then
    echo "ERROR: ETISS source not found at ${SOURCE_DIR}" >&2
    exit 1
fi

INSTALL_PREFIX="${BUILD_DIR}/installed"

echo "=============================================="
echo "  ETISS build"
echo "  source dir : ${SOURCE_DIR}"
echo "  build type : ${BUILD_TYPE}"
echo "  build dir  : ${BUILD_DIR}"
echo "  install    : ${INSTALL_PREFIX}"
echo "=============================================="

mkdir -p "${BUILD_DIR}"

CMAKE_ARGS=(
    -S "${SOURCE_DIR}"
    -B "${BUILD_DIR}"
    "-DCMAKE_BUILD_TYPE=${BUILD_TYPE}"
    "-DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX}"
)

echo "--> cmake ${CMAKE_ARGS[*]}"
cmake "${CMAKE_ARGS[@]}"

if [[ "${CONFIGURE_ONLY}" -eq 1 ]]; then
    echo "Configure done (skipping build)."
    exit 0
fi

echo "--> cmake --build \"${BUILD_DIR}\" --parallel ${JOBS}"
cmake --build "${BUILD_DIR}" --parallel "${JOBS}"

if [[ "${DO_INSTALL}" -eq 1 ]]; then
    echo "--> cmake --build \"${BUILD_DIR}\" --target install"
    cmake --build "${BUILD_DIR}" --target install
    echo "ETISS installed to ${INSTALL_PREFIX}"
else
    echo "ETISS built in ${BUILD_DIR} (pass --install to install to ${INSTALL_PREFIX})."
fi
