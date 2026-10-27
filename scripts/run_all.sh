#!/usr/bin/env bash
#
# Run every built benchmark (embench-iot + optional MLPerfTiny) against the
# configured simulators and report pass/fail per test, per core.
#
# Two simulators are exercised:
#   * Verilator RTL models of the scalar cores (cv32e40x / cv32a60x), built by
#     scripts/build_verilator.sh under rtl/vicuna2/build/<core>/<arch>_zvl<VREG_W>_vl<VLANE_W>/.
#   * ETISS (RV32IMACFDV_zvl<VREG_W>b), built by scripts/build_etiss.sh.
#
# The host binaries are shared across cores and simulators (they are position
# independent RISC-V ELF / vmem images); only the simulator binary changes.
#
# Pass/fail rules (identical to the ctest registrations in programs/CMakeLists.txt):
#   * Verilator: model exit code 0 == PASS -- the harness writes 0x0 to the
#                pass/fail MMIO (0x408).  Non-zero == FAIL (0xf fail / stall /
#                interrupt / bad args).
#   * ETISS:     the semihosted SYS_EXIT_EXTENDED makes the process exit with
#                the harness main() return value: 0 == PASS, non-zero == FAIL.
#
# NOTE: neither simulator is instructed to trace instructions.  Verilator only
# traces with --itrace/-i; ETISS only with etiss.log_pc=true or the (here
# commented-out) [Plugin PrintInstruction].  Both are OFF in this script.
#
# Usage:
#   scripts/run_all.sh [options]
#
# Options:
#   --cores <list>      Comma separated scalar cores   [default: cv32a60x,cv32e40x]
#   --vlen <bits>       Vector register width / VLEN   [default: 128]
#   --lane-width <bits> Vector lane width (VLANE_W)    [default: 32]
#   --mem-w <bits>      Data memory interface width    [default: 32]
#   --mem-ports <n>     Number of data memory ports    [default: 1]
#   --mem-latency <n>   Data memory latency (cycles)   [default: 1]
#   --result-dir <path> Where logs/CSVs are written    [default: <build>/tiny_run_results]
#   --etiss             Run the ETISS suite            [default: ON]
#   --no-etiss          Skip ETISS
#   --verilator         Run the Verilator suite        [default: ON]
#   --no-verilator      Skip Verilator
#   --mlperftiny        Include the MLPerfTiny suite   [default: ON if built]
#   --no-mlperftiny     Skip MLPerfTiny
#   --jobs <n>          Max parallel test processes    [default: nproc]
#   --help|-h           Show this help
#
# Parameters may also be set via environment variables: VREG_W, MEM_W,
# MEM_PORTS, MEM_LATENCY, RESULT_DIR, ETISS=ON/OFF, VERILATOR=ON/OFF,
# MLPERFTINY=ON/OFF, JOBS.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${BUILD_DIR:-${REPO_ROOT}/programs/build}"
EMBENCH_DIR="${BUILD_DIR}/src/embench-iot"
TINY_DIR="${BUILD_DIR}/src/tiny"
RTL_MODELS="${RTL_MODELS:-${REPO_ROOT}/rtl/vicuna2/build}"
ETISS_BIN="${ETISS_BIN:-${REPO_ROOT}/etiss-pe/etiss-perf-sim/etiss/build/bin/bare_etiss_processor}"
ETISS_INI="${ETISS_INI:-${REPO_ROOT}/programs/runtime/etiss/ini/etiss.ini}"

# Defaults (must match programs/CMakeLists.txt and rtl/vicuna2/vector_config.cmake).
VREG_W="${VREG_W:-128}"
VLANE_W="${VLANE_W:-32}"
MEM_W="${MEM_W:-32}"
MEM_PORTS="${MEM_PORTS:-1}"
MEM_LATENCY="${MEM_LATENCY:-1}"

CORES="${CORES:-cv32a60x,cv32e40x}"
RUN_ETISS="${ETISS:-ON}"
RUN_VERILATOR="${VERILATOR:-ON}"
RUN_MLPERFTINY="${MLPERFTINY:-ON}"
JOBS="${JOBS:-$(nproc 2>/dev/null || echo 1)}"
RESULT_DIR="${RESULT_DIR:-${BUILD_DIR}/tiny_run_results}"

usage() {
    # Print the leading comment banner (skip the shebang, stop at the first
    # non-comment / blank line), stripping the trailing '# ' prefix.
    awk '
        NR > 1 {
            if ($0 ~ /^#/) { sub(/^# ?/, ""); print }
            else { exit }
        }' "${BASH_SOURCE[0]}"
}

# --- argument parsing -------------------------------------------------------
while [[ $# -gt 0 ]]; do
    case "$1" in
        --cores)        CORES="$2"; shift 2 ;;
        --vlen)         VREG_W="$2"; shift 2 ;;
        --lane-width)   VLANE_W="$2"; shift 2 ;;
        --mem-w)        MEM_W="$2"; shift 2 ;;
        --mem-ports)    MEM_PORTS="$2"; shift 2 ;;
        --mem-latency)  MEM_LATENCY="$2"; shift 2 ;;
        --result-dir)   RESULT_DIR="$2"; shift 2 ;;
        --etiss)        RUN_ETISS=ON; shift ;;
        --no-etiss)     RUN_ETISS=OFF; shift ;;
        --verilator)    RUN_VERILATOR=ON; shift ;;
        --no-verilator) RUN_VERILATOR=OFF; shift ;;
        --mlperftiny)   RUN_MLPERFTINY=ON; shift ;;
        --no-mlperftiny) RUN_MLPERFTINY=OFF; shift ;;
        --jobs)         JOBS="$2"; shift 2 ;;
        --help|-h)      usage; exit 0 ;;
        *)
            echo "Unknown option: $1" >&2
            usage >&2
            exit 1
            ;;
    esac
done

# --- resolve the Verilator model per core ----------------------------------
declare -A MODEL_BIN
model_for_core() {
    local core="$1" d
    for d in "${RTL_MODELS}/${core}"/*"zvl${VREG_W}_vl${VLANE_W}"*; do
        [[ -x "${d}/verilated_model" ]] && { MODEL_BIN[$core]="${d}/verilated_model"; return 0; }
    done
    echo "ERROR: no Verilator model for core '${core}' under ${RTL_MODELS}/${core}/ (run scripts/build_verilator.sh)" >&2
    return 1
}

# --- sanity checks ----------------------------------------------------------
[[ -d "${EMBENCH_DIR}" ]] || { echo "ERROR: embench build dir not found: ${EMBENCH_DIR} (run scripts/build_programs.sh)" >&2; exit 1; }
if [[ "${RUN_ETISS}" == "ON" && ! -x "${ETISS_BIN}" ]]; then
    echo "WARNING: ETISS processor not found (${ETISS_BIN}); disabling ETISS suite." >&2
    RUN_ETISS=OFF
fi
if [[ "${RUN_ETISS}" == "ON" && ! -f "${ETISS_INI}" ]]; then
    echo "WARNING: ETISS ini not found (${ETISS_INI}); disabling ETISS suite." >&2
    RUN_ETISS=OFF
fi

# --- collect targets --------------------------------------------------------
veri_targets=()
etiss_targets=()

find_prog_files() {
    local dir="$1"
    if [[ -d "${dir}" ]]; then ls "${dir}"/prog_*_verilator.txt 2>/dev/null; fi
}

find_etiss_bins() {
    local dir="$1"
    if [[ -d "${dir}" ]]; then ls "${dir}"/*_etiss 2>/dev/null; fi
}

if [[ "${RUN_VERILATOR}" == "ON" ]]; then
    veri_targets=( $(find_prog_files "${EMBENCH_DIR}"
                     if [[ "${RUN_MLPERFTINY}" == "ON" ]]; then find_prog_files "${TINY_DIR}"; fi) )
    # Strip '<path>/prog_' prefix and '_verilator.txt' suffix -> base target name.
    veri_targets=( $(printf '%s\n' "${veri_targets[@]}" | sed -E 's#^.*/prog_##; s#_verilator\.txt$##' | sort -u) )
fi

if [[ "${RUN_ETISS}" == "ON" ]]; then
    etiss_targets=( $(find_etiss_bins "${EMBENCH_DIR}"
                      if [[ "${RUN_MLPERFTINY}" == "ON" ]]; then find_etiss_bins "${TINY_DIR}"; fi) )
    etiss_targets=( $(printf '%s\n' "${etiss_targets[@]}" | xargs -n1 basename | sort -u) )
fi

# --- run harness ------------------------------------------------------------
mkdir -p "${RESULT_DIR}"
veri_csv="${RESULT_DIR}/verilator_results.csv"
etiss_csv="${RESULT_DIR}/etiss_results.csv"
printf 'core,target,verdict,code\n' > "${veri_csv}"
printf 'core,target,verdict,code\n' > "${etiss_csv}"

VERI_ARGS="${MEM_PORTS} ${MEM_W} 4194304 ${MEM_LATENCY} 1"

veri_timeout() {
    # MLPerfTiny IC/KWS are far longer than the embench kernels.
    case "$1" in kws|ic) echo 5400 ;; *) echo 900 ;; esac
}

run_veri() {
    local core="$1" tgt="$2" model="${MODEL_BIN[$core]}" dir progfile out exitcode
    if [[ -f "${EMBENCH_DIR}/prog_${tgt}_verilator.txt" ]]; then dir="${EMBENCH_DIR}"; else dir="${TINY_DIR}"; fi
    progfile="${dir}/prog_${tgt}_verilator.txt"
    out="${RESULT_DIR}/${core}_${tgt}.log"
    (
        cd "${dir}"
        timeout "$(veri_timeout "${tgt}")" \
            "${model}" "${progfile}" ${VERI_ARGS} "${tgt}" "${VREG_W}" 0 \
            > "${out}" 2>&1
    )
    exitcode=$?
    if [[ ${exitcode} -eq 0 ]]; then local verdict=PASS; else verdict=FAIL; fi
    echo "${core},${tgt},${verdict},exit=${exitcode}" >> "${veri_csv}"
}

run_etiss() {
    local tgt="$1" dir out exitcode
    if [[ -x "${EMBENCH_DIR}/${tgt}" ]]; then dir="${EMBENCH_DIR}"; else dir="${TINY_DIR}"; fi
    out="${RESULT_DIR}/etiss_${tgt}.log"
    (
        cd "${dir}"
        timeout 300 "${ETISS_BIN}" -i"${ETISS_INI}" \
            --vp.elf_file="./${tgt}" --arch.cpu=RV32IMACFDV_zvl${VREG_W}b \
            > "${out}" 2>&1
    )
    exitcode=$?
    if [[ ${exitcode} -eq 0 ]]; then local verdict=PASS; else verdict=FAIL; fi
    echo "${tgt},${verdict},exit=${exitcode}" >> "${etiss_csv}"
}

# Resolve models up front so we can report (and fail fast on) any missing core.
cores=()
for core in ${CORES//,/ }; do
    if [[ "${RUN_VERILATOR}" == "ON" ]]; then
        model_for_core "${core}" || { echo "ERROR: cannot resolve core ${core}" >&2; exit 1; }
    fi
    cores+=("${core}")
done

echo "=== benchmark run summary ==="
echo "verilator models : $(printf '%s -> %s; ' "${cores[@]}" "${MODEL_BIN[@]}")"
echo "etiss processor  : ${ETISS_BIN}"
echo "verilator tests  : ${#veri_targets[@]} (per core)"
echo "etiss tests      : ${#etiss_targets[@]}"
echo "result dir       : ${RESULT_DIR}"
echo "tracing          : OFF (Verilator: no --itrace; ETISS: log_pc=false / no PrintInstruction)"
if [[ ${#veri_targets[@]} -eq 0 && "${RUN_VERILATOR}" == "ON" ]]; then
    echo "WARNING: no Verilator targets found (rebuild with the Verilator suite enabled)." >&2
fi

# --- launch, throttled to JOBS parallel ------------------------------------
pids=()
launch_wait() {
    local first
    if [[ ${#pids[@]} -ge ${JOBS} ]]; then
        first="${pids[0]}"; unset 'pids[0]'; pids=("${pids[@]}")
        wait "${first}"
    fi
}

if [[ "${RUN_VERILATOR}" == "ON" ]]; then
    for core in "${cores[@]}"; do
        for tgt in "${veri_targets[@]}"; do
            run_veri "${core}" "${tgt}" &
            pids+=($!)
            launch_wait
        done
    done
fi

if [[ "${RUN_ETISS}" == "ON" ]]; then
    for tgt in "${etiss_targets[@]}"; do
        run_etiss "${tgt}" &
        pids+=($!)
        launch_wait
    done
fi

for p in "${pids[@]}"; do wait "${p}"; done

echo "=== done ==="
echo "  verilator results: ${veri_csv}"
echo "  etiss results    : ${etiss_csv}"
