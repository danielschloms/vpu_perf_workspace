#!/usr/bin/env python3
"""
v3-run.py
=========

Per-target, disk-free comparison of ETISS and the Verilator RTL simulator,
running the simulators *directly* (no ctest).

Why v3 / what it changes
------------------------
* Runs each simulator once per (target, HW config) and compares immediately,
  then moves on to the next target. No full test matrix, no ctest orchestration.
* All instruction traces are redirected into a tmpfs (RAM) filesystem at
  runtime, so hundreds of GB of trace data is never written to the SSD.
* Simulator source/binary is untouched. We only:
    - generate a temporary ETISS dyn.ini that points the perf-estimator and
      trace-printer plugins at a tmpfs directory, and
    - pass `--itrace <tmpfs>/...` to verilator so its instruction trace lands
      in tmpfs.

The comparator (`fastcomparison.compare_fast`) is reused unchanged.

====================================
PREREQUISITE: a tmpfs mount
====================================
Create and mount a RAM-backed filesystem sized for your largest trace, then
pass its path via `--trace-root` (default /mnt/traces_ram):

    sudo mkdir -p /mnt/traces_ram
    sudo mount -t tmpfs -o size=64G tmpfs /mnt/traces_ram

To make it permanent:
    echo "/mnt/traces_ram tmpfs defaults,size=64G 0 0" | sudo tee -a /etc/fstab

v3-run.py verifies (best-effort) that the trace root is actually tmpfs and
aborts with a warning if it looks like it lives on a real filesystem.

====================================
USAGE
====================================
    python3 v3-run.py                       # all targets @ 128/32
    python3 v3-run.py -t aha-mont64 -t edn  # specific targets
    python3 v3-run.py --hw-config 128,32 --hw-config 256,64
    python3 v3-run.py --dry-run             # print commands, don't run
    python3 v3-run.py --keep-traces         # don't rm tmpfs traces

Notable ASSUMPTIONS (verify once against your build layout):
  * a perf-enabled build already exists under
        <repo>/build_programs/build/<arch>_zvl<vlen>b/benchmark_sources/<suite>/
    producing the ELF / .vmem / *_dump.txt / prog_*.txt artifacts.
  * ETISS binary:
        <repo>/toolchain/etiss_base/etiss_perfsim/etiss-perf-sim/etiss/build/bin/bare_etiss_processor
  * Verilator model:
        <repo>/processor_models/verilator/build/verilated_model
  * framework ETISS base ini:
        <repo>/benchmark_sources/framework/etiss/ini/etiss.ini
"""

import argparse
import os
import pathlib
import re
import shutil
import subprocess
import sys

import fastcomparison
import paths
from util import check_path, error, info, success, warn

# --------------------------------------------------------------------------
# Configuration (defaults; override via CLI)
# --------------------------------------------------------------------------
ARCH = "rv32im_zve32x"
BENCHMARK_SUITE = "embench_iot"

# The Verilator model is built per scalar core in this repo; the comparison
# uses one core (the one the programs were built against / the default).
SCALAR_CORE = os.environ.get("SCALAR_CORE", "cv32a60x")

# Map the logical suite name to the actual build subdirectory under
# <repo>/programs/build/src/.
SUITE_DIR_NAMES = {
    "embench_iot": "embench-iot",
    "mlperftiny": "tiny",
}

# (VLEN, VLANE_WIDTH). For now only 128/32 is exercised.
DEFAULT_HW_CONFIGS = [(128, 32)]

# Memory model parameters passed as positional args to the Verilator model.
# These are usually baked at build time; edited below if your build differs.
VERILATOR_MEM_PORTS = 1
VERILATOR_MEM_W = 32
VERILATOR_MEM_SZ = 4194304
VERILATOR_MEM_LATENCY = 1
VERILATOR_EXTRA_CYCLES = 1

VERILATOR_INSTR_TRACE_ARG = "--itrace"
ETISS_TRACE_ROTATE_BYTES = 0x10000

# The cv32a60x Verilator model records committed PCs on the physical address
# bus, whose DRAM base is 0x80000000. The objdump/ELF addresses (used by
# read_addresses) are logical, so the model's --itrace PCs are `logical +
# VERILATOR_ADDR_OFFSET`. Override if the model base changes.
VERILATOR_ADDR_OFFSET = int(os.environ.get("VERILATOR_ADDR_OFFSET", "0x80000000"), 0)

# EMBENCH IOT baselines (target names refer to the benchmark, NOT the
# simulator-specific suffix). Override with --target.
EMBENCH_IOT_TESTS = [
    # "aha-mont64",
    # "edn",
    # "md5sum",
    # "nsichneu",
    # "sglib-combined",
    # "tarfind",
    # "xgboost",
    "crc32",
    # "huffbench",
    # "slre",
    # "ud",
    # "depthconv",
    # "matmult-int",
    # "statemate",
    # "wikisort",
    # "qrduino",
    # "picojpeg",
    # "nettle-sha256",
    # "nettle-aes",
]

MAX_TRACE_LINES_DIAG = 20  # extra debug lines shown on mismatch


def hw_config_strs(configs):
    return [f"{vlen}x{vlane}" for vlen, vlane in configs]


# --------------------------------------------------------------------------
# Paths derived from the project layout
# --------------------------------------------------------------------------
def etiss_binary() -> pathlib.Path:
    return paths.PERFSIM_PRJ_SRC / "etiss-perf-sim/etiss/build/bin/bare_etiss_processor"


def etiss_base_ini() -> pathlib.Path:
    # This repo's ETISS framework ini.
    return paths.PROJECT_ROOT_DIR / "programs/runtime/etiss/ini/etiss.ini"


def verilator_binary(vlen: int = 128, vlane: int = 32) -> pathlib.Path:
    # Model path: <rtl>/build/<core>/<arch>_zvl<vlen>_vl<vlane>/verilated_model
    model = (
        paths.VERILATOR_PRJ_SRC
        / "build"
        / SCALAR_CORE
        / f"{ARCH}_zvl{vlen}_vl{vlane}"
        / "verilated_model"
    )
    if not model.exists():
        # Fall back to a glob in case the core sub-dir name differs slightly.
        cands = list((paths.VERILATOR_PRJ_SRC / "build" / SCALAR_CORE).glob(f"*zvl{vlen}_vl{vlane}*/verilated_model"))
        if cands:
            model = cands[0]
    return model


def suite_dir(arch: str, vlen: int) -> pathlib.Path:
    # This repo nests built benchmarks under <repo>/programs/build/src/<suite>/.
    return paths.TEST_BUILD_BASE_DIR / "src" / SUITE_DIR_NAMES.get(BENCHMARK_SUITE, BENCHMARK_SUITE)


def target_paths(arch: str, vlen: int, target: str) -> dict:
    """Locate the build artefacts for one target."""
    d = suite_dir(arch, vlen)

    etiss_name = f"{target}_etiss"
    verilator_name = f"{target}_verilator"

    paths_map = {
        # ETISS ELF has no `.elf` suffix in this repo.
        "etiss_elf": d / etiss_name,
        "etiss_dump": d / f"{etiss_name}_dump.txt",
        "verilator_dump": d / f"{verilator_name}_dump.txt",
        "verilator_prog": d / f"prog_{verilator_name}.txt",
        # where the verilator model writes its instruction trace (tmpfs)
        "verilator_trace": None,  # filled later when trace root known
    }
    return paths_map


# --------------------------------------------------------------------------
# tmpfs
# --------------------------------------------------------------------------
def fs_type(path: pathlib.Path) -> str:
    """Best-effort filesystem type of a mount point (e.g. 'tmpfs')."""
    try:
        out = subprocess.run(
            ["stat", "-f", "-c", "%T", str(path)],
            capture_output=True,
            text=True,
            check=True,
        ).stdout.strip()
        return out
    except Exception:
        return "?"


def ensure_trace_root(trace_root: pathlib.Path) -> None:
    try:
        trace_root.mkdir(parents=True, exist_ok=True)
    except OSError as exc:
        error("ensure_trace_root", f"Cannot create {trace_root}: {exc}")
        sys.exit(1)

    ftype = fs_type(trace_root)
    if ftype != "tmpfs":
        warn(
            "ensure_trace_root",
            f"{trace_root} is on a '{ftype}' filesystem, NOT tmpfs. "
            "Traces would hit the disk! Run the setup script to create a tmpfs: "
            f"{pathlib.Path(__file__).with_name('v3-setup.sh').name}",
        )
        raise SystemExit(1)
    info("ensure_trace_root", f"Trace root is tmpfs: {trace_root}")


def natural_key(name: str):
    return [int(t) if t.isdigit() else t for t in re.split(r"(\d+)", name)]


# --------------------------------------------------------------------------
# ETISS runtime dyn.ini + invocation
# --------------------------------------------------------------------------
def write_etiss_dyn_ini(
    trace_dir: pathlib.Path, vlen: int, target: str
) -> pathlib.Path:
    """Generate a temp ETISS dyn.ini pointing trace output at tmpfs."""
    trace_dir.mkdir(parents=True, exist_ok=True)
    ini = trace_dir / f"dyn_{target}_zvl{vlen}.ini"
    # Mirrors benchmark_sources/framework/etiss/ini/dyn.ini.in
    # (TRACE_NAME uses the *_etiss target so combined name is stable).
    trace_name = f"{target}_etiss_trace"
    ini.write_text(
        "[Plugin PerformanceEstimatorPlugin]\n"
        f"plugin.perfEst.uArch=Vicuna_zvl{vlen}b\n"
        "plugin.perfEst.print=1\n"
        f"plugin.perfEst.printDir={trace_dir}\n"
        "\n"
        "[Plugin TracePrinterPlugin]\n"
        "plugin.tracePrinter.trace=AssemblyTrace\n"
        "plugin.tracePrinter.stream.toFile=1\n"
        f"plugin.tracePrinter.stream.fileName={trace_name}\n"
        f"plugin.tracePrinter.stream.rotateSize={ETISS_TRACE_ROTATE_BYTES:#x}\n"
        f"plugin.tracePrinter.stream.outDir={trace_dir}\n",
        encoding="utf-8",
    )
    return ini


def build_etiss_cmd(
    paths_map: dict, vlen: int, trace_dir: pathlib.Path, target: str
) -> list[str]:
    dyn_ini = write_etiss_dyn_ini(trace_dir, vlen, target)
    cmd = [
        str(etiss_binary()),
        f"-i{etiss_base_ini()}",
        f"-i{dyn_ini}",
        f"--vp.elf_file={paths_map['etiss_elf']}",
        f"--arch.cpu=RV32IMACFDV_zvl{vlen}b",
    ]
    return cmd


def build_verilator_cmd(
    paths_map: dict, verilator_trace: pathlib.Path, target: str, vlen: int, vlane: int
) -> list[str]:
    cmd = [
        str(verilator_binary(vlen=vlen, vlane=vlane)),
        str(paths_map["verilator_prog"]),
        str(VERILATOR_MEM_PORTS),
        str(VERILATOR_MEM_W),
        str(VERILATOR_MEM_SZ),
        str(VERILATOR_MEM_LATENCY),
        str(VERILATOR_EXTRA_CYCLES),
        f"{target}_verilator",  # TEST_NAME
        str(vlen),  # VREG_W
        "0",  # NUM_TEST_CASES
        VERILATOR_INSTR_TRACE_ARG,
        str(verilator_trace),
    ]
    return cmd


# --------------------------------------------------------------------------
# Run both simulators for one (target, hw-config)
# --------------------------------------------------------------------------
def run_simulators(cmds: dict, cwd: pathlib.Path | None = None) -> bool:
    """Run every (name -> (cmd, extra_env)) command; True if all succeed."""
    failed = []
    for name, (cmd, extra_env) in cmds.items():
        info(f"run {name}", " ".join(str(c) for c in cmd))
        env = os.environ.copy()
        env.update(extra_env)
        try:
            proc = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                env=env,
                cwd=str(cwd) if cwd else None,
                timeout=None,
            )
            if proc.returncode != 0:
                error(f"run {name}", f"exited {proc.returncode}")
                if proc.stderr:
                    error(f"run {name}", proc.stderr.strip().splitlines()[-1])
                failed.append(name)
        except FileNotFoundError as exc:
            error(f"run {name}", f"binary not found: {exc}")
            error(f"run {name}", str(cmd[0]))
            failed.append(name)
    if failed:
        error("run_simulators", f"failed: {', '.join(failed)}")
        return False
    return True


def combine_etiss_traces(
    trace_dir: pathlib.Path, target: str, root: pathlib.Path
) -> tuple:
    """Assemble the combined ETISS timing.csv and asm trace.txt in tmpfs."""
    # Timing: the perf-estimator's cycle CSV.
    timing_files = sorted(
        trace_dir.glob("Vicuna*_timing_*"), key=lambda p: natural_key(p.name)
    )
    # ASM: the AssemblyTrace (.txt). The perf-estimator also writes a separate
    # `Vicuna*_trace_*.csv` (pipe-delimited) which parse_etiss_line does NOT
    # consume, so restrict the glob to the assembly trace name we configured.
    asm_files = sorted(
        trace_dir.glob(f"{target}_etiss_trace*.txt"),
        key=lambda p: natural_key(p.name),
    )

    timing_out = root / f"{target}_etiss_timing.csv"
    trace_out = root / f"{target}_etiss_trace.txt"

    with timing_out.open("w", encoding="utf-8") as tf:
        for f in timing_files:
            tf.write(f.read_text(encoding="utf-8"))
    with trace_out.open("w", encoding="utf-8") as a_out:
        for f in asm_files:
            for line in f.read_text(encoding="utf-8").splitlines():
                if line.startswith("0x"):  # matches `sed -i '/^0x/!d'`
                    a_out.write(line + "\n")
    info(
        "combine_etiss_traces",
        f"timing files={len(timing_files)} asm files={len(asm_files)}",
    )
    return timing_out, trace_out


# --------------------------------------------------------------------------
# One full target comparison
# --------------------------------------------------------------------------
def compare_target(
    target: str,
    vlen: int,
    vlane: int,
    trace_root: pathlib.Path,
    keep_traces: bool,
    dry_run: bool,
    match_dir: pathlib.Path,
) -> bool:
    fname = f"compare {target}@{vlen}x{vlane}"
    p = target_paths(ARCH, vlen, target)

    # tmpfs locations unique to this target
    etiss_dir = trace_root / "etiss" / f"{target}_etiss"
    verilator_trace = trace_root / "verilator" / f"{target}_Verilator_trace.txt"
    # The verilator model opens its `--itrace` ofstream directly; the parent
    # directory must already exist or it silently produces no file.
    verilator_trace.parent.mkdir(parents=True, exist_ok=True)

    etiss_cmd = build_etiss_cmd(p, vlen, etiss_dir, target)
    verilator_cmd = build_verilator_cmd(p, verilator_trace, target, vlen, vlane)

    # Preview commands even without a build, so the invocation can be vetted.
    if dry_run:
        info(fname, "(dry-run) ETISS: " + " ".join(etiss_cmd))
        info(fname, "(dry-run) VERILATOR: " + " ".join(verilator_cmd))
        return True

    for key in ("etiss_dump", "verilator_dump", "verilator_prog"):
        check_path(p[key])
    check_path(etiss_binary())
    check_path(verilator_binary(vlen=vlen, vlane=vlane))
    match_dir.mkdir(parents=True, exist_ok=True)
    match_file = match_dir / f"{target}_{vlen}x{vlane}_match.txt"

    # Run both simulators from a scratch CWD. The cv32a60x Verilator model's RTL
    # unconditionally $fopens `trace_hart_<id>.dasm` into the process CWD (see
    # rtl/vicuna2/rtl/cv32a60x/core/cva6_pipeline.sv). Running from a scratch
    # dir under the (tmpfs) trace root keeps that file out of the workspace.
    run_cwd = trace_root / "run_cwd"
    run_cwd.mkdir(parents=True, exist_ok=True)

    # ETISS expects VLEN/VLANE_WIDTH in its environment (as ctest set them).
    cmds = {
        "etiss": (etiss_cmd, {"VLEN": str(vlen), "VLANE_WIDTH": str(vlane)}),
        "verilator": (verilator_cmd, {}),
    }
    ok = run_simulators(cmds, cwd=run_cwd)
    if not ok:
        return False

    # Assemble combined ETISS timing + trace (fastcomparison reads these).
    etiss_timing, etiss_trace = combine_etiss_traces(etiss_dir, target, trace_root)

    info(fname, "Comparing...")
    ok_run = False
    try:
        ret = fastcomparison.compare_fast(
            p["etiss_dump"],
            p["verilator_dump"],
            etiss_timing,
            etiss_trace,
            verilator_trace,
            match_file,
            verilator_addr_offset=VERILATOR_ADDR_OFFSET,
        )
        # compare_fast returns (CmpResult, bool) on success, but a 6-tuple
        # (0,0,0,0,0,False) when address matching fails; handle both.
        result, ok_run = ret[0], ret[1]
        if not isinstance(result, fastcomparison.CmpResult):
            raise ValueError(f"comparison returned unexpected shape: {ret!r}")
    except fastcomparison.ParseException as exc:
        error(fname, f"Parse failure: {exc}")
        ok_run = False
        # Surface a few raw lines to help debug without dumping the trace.
        for path in (etiss_timing, etiss_trace, verilator_trace):
            if path.exists():
                with path.open(encoding="utf-8", errors="replace") as fh:
                    head = [next(fh, "").rstrip() for _ in range(MAX_TRACE_LINES_DIAG)]
                error(fname, f"First lines of {path.name}: {head}")
    except Exception as exc:  # noqa: BLE001 - report anything and keep going
        error(fname, f"comparison error: {exc}")
        ok_run = False

    if ok_run:
        result.printout(target)
    else:
        error(fname, "comparison failed")

    if not keep_traces:
        shutil.rmtree(etiss_dir, ignore_errors=True)
        for tmp in (etiss_timing, etiss_trace, verilator_trace, match_file):
            tmp.unlink(missing_ok=True)
        # Drop the scratch CWD (it holds the model's `trace_hart_*.dasm`).
        shutil.rmtree(run_cwd, ignore_errors=True)
    return ok_run


# --------------------------------------------------------------------------
# CLI / driver
# --------------------------------------------------------------------------
def parse_hw_configs(values):
    parsed = []
    for v in values:
        try:
            vlen, vlane = (int(x) for x in v.split(","))
            parsed.append((vlen, vlane))
        except ValueError:
            error(
                "parse_hw_configs", f"bad --hw-config '{v}' (expect VLEN,VLANE_WIDTH)"
            )
            sys.exit(1)
    return parsed


# --------------------------------------------------------------------------
# Build orchestration (build a perf-trace suite if not already built)
# --------------------------------------------------------------------------
def read_cmake_cache(build_dir: pathlib.Path) -> dict:
    """Parse `KEY:TYPE=value` lines from a build dir's CMakeCache.txt."""
    cache = build_dir / "CMakeCache.txt"
    if not cache.exists():
        return {}
    vals = {}
    for line in cache.read_text(encoding="utf-8", errors="ignore").splitlines():
        line = line.strip()
        if line and ":" in line and "=" in line:
            key, _, value = line.partition("=")
            key = key.partition(":")[0]
            vals[key] = value
    return vals


def is_suite_built(arch: str, vlen: int, vlane: int, suite: str) -> bool:
    """True iff the suite has built artefacts for this repo's layout."""
    d = suite_dir(arch, vlen)
    if not d.exists():
        return False
    # Any objdump dump means the build finished its POST_BUILD steps.
    if not any(d.glob("*_dump.txt")):
        return False
    return True


def build_suite(arch: str, vlen: int, vlane: int, suite: str) -> bool:
    """Build the suite in this repo via scripts/build_programs.sh.

    Note: this repo does not ship the original repo's `build-tests.sh --pperf`
    (perf-trace) build.  The suite is normally built with scripts/build_programs.sh
    (which already produces the objdump `*_dump.txt` artefacts the comparison
    needs).  If it is not built yet, we trigger that build once.
    """
    script = pathlib.Path(__file__).parent.parent / "build_programs.sh"
    if not script.exists():
        error(
            "build",
            f"build helper not found ({script}); build the suite first via scripts/build_programs.sh",
        )
        return False
    info("build", f"Building {suite} via {script} ...")
    proc = subprocess.run([str(script), "--mlperftiny", "--scalar-core", SCALAR_CORE])
    if proc.returncode != 0:
        error("build", f"build_programs.sh failed with code {proc.returncode}")
        return False
    if not is_suite_built(arch, vlen, vlane, suite):
        error("build", "build reported success but artifacts missing")
        return False
    return True


def ensure_suite_built(
    arch: str,
    vlen: int,
    vlane: int,
    suite: str,
    rebuild: bool,
    no_build: bool,
    dry_run: bool,
) -> bool:
    """Default: build with --pperf only if not already built for this config."""
    if rebuild:
        if dry_run:
            info("build", f"(dry-run) would rebuild {suite} @ zvl{vlen}b/vlane{vlane}")
            return True
        return build_suite(arch, vlen, vlane, suite)

    if is_suite_built(arch, vlen, vlane, suite):
        info("build", f"{suite} already built @ zvl{vlen}b/vlane{vlane}")
        return True

    if no_build:
        error(
            "build", f"{suite} not built for zvl{vlen}b/vlane{vlane} and --no-build set"
        )
        return False

    if dry_run:
        info("build", f"(dry-run) would build {suite} @ zvl{vlen}b/vlane{vlane}")
        return True

    return build_suite(arch, vlen, vlane, suite)


def main() -> None:
    global ARCH, BENCHMARK_SUITE
    global VERILATOR_MEM_PORTS, VERILATOR_MEM_W, VERILATOR_MEM_LATENCY

    parser = argparse.ArgumentParser(
        prog="v3-run",
        description="Per-target disk-free ETISS vs Verilator comparison (tmpfs traces).",
    )
    parser.add_argument("--arch", default=ARCH)
    parser.add_argument("--suite", default=BENCHMARK_SUITE)
    parser.add_argument(
        "--hw-config",
        action="append",
        dest="hw_configs",
        help="VLEN,VLANE_WIDTH (repeatable). Default 128,32",
    )
    parser.add_argument("-t", "--target", action="append", help="target (repeatable)")
    parser.add_argument(
        "--trace-root", default="/mnt/traces_ram", help="tmpfs mount root"
    )
    parser.add_argument(
        "--keep-traces", action="store_true", help="don't delete tmpfs traces"
    )
    parser.add_argument(
        "--dry-run", action="store_true", help="print commands, don't run"
    )
    parser.add_argument("--mem-ports", type=int, default=VERILATOR_MEM_PORTS)
    parser.add_argument("--mem-w", type=int, default=VERILATOR_MEM_W)
    parser.add_argument("--mem-latency", type=int, default=VERILATOR_MEM_LATENCY)
    build_group = parser.add_mutually_exclusive_group()
    build_group.add_argument(
        "--rebuild", action="store_true", help="always (re)build the suite with --pperf"
    )
    build_group.add_argument(
        "--no-build",
        action="store_true",
        help="never build; fail if the suite is not built",
    )
    args = parser.parse_args()

    ARCH, BENCHMARK_SUITE = args.arch, args.suite

    # Override memory model params if provided.
    VERILATOR_MEM_PORTS = args.mem_ports
    VERILATOR_MEM_W = args.mem_w
    VERILATOR_MEM_LATENCY = args.mem_latency

    configs = (
        parse_hw_configs(args.hw_configs) if args.hw_configs else DEFAULT_HW_CONFIGS
    )
    targets = args.target if args.target else EMBENCH_IOT_TESTS

    trace_root = pathlib.Path(args.trace_root).resolve()
    ensure_trace_root(trace_root)
    match_dir = trace_root / "match"

    ok_total = True
    for vlen, vlane in configs:
        info("v3-run", f"HW config zvl{vlen}b / vlane{vlane} ({len(targets)} targets)")
        # Build the suite (with traces) if it isn't already built for this config.
        if not ensure_suite_built(
            ARCH,
            vlen,
            vlane,
            BENCHMARK_SUITE,
            rebuild=args.rebuild,
            no_build=args.no_build,
            dry_run=args.dry_run,
        ):
            warn(
                "v3-run",
                f"skipping {BENCHMARK_SUITE} @ zvl{vlen}b/vlane{vlane}: build failed",
            )
            ok_total = False
            continue
        for target in targets:
            success(
                "v3-run",
                f"=== {target} @ zvl{vlen}b / vlane{vlane} ===",
            )
            ok = compare_target(
                target,
                vlen,
                vlane,
                trace_root,
                keep_traces=args.keep_traces,
                dry_run=args.dry_run,
                match_dir=match_dir,
            )
            ok_total &= ok
            if not ok:
                warn("v3-run", f"{target} failed")

    # Clean the match/near-empty dirs unless keeping traces (best effort).
    if not args.keep_traces and match_dir.exists():
        try:
            match_dir.rmdir()
        except OSError:
            pass

    if ok_total:
        success("v3-run", "All comparisons completed")
    else:
        sys.exit(1)


if __name__ == "__main__":
    main()
