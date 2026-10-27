import pathlib
from util import check_path

# This file lives at <repo>/scripts/comparison/paths.py.
SRC_DIR = pathlib.Path(__file__).parent.resolve()
# The comparison project dir is <repo>/scripts (it holds comparison/, table/, ...).
COMPARISON_PRJ_DIR = SRC_DIR.parent
# Repository root: <repo>/scripts/.. = <repo>.
PROJECT_ROOT_DIR = COMPARISON_PRJ_DIR.parent

# --- Paths for THIS repository (perf-est-v2) -------------------------------
# ETISS perf-sim lives under <repo>/etiss-pe/etiss-perf-sim.
PERFSIM_PRJ_SRC = PROJECT_ROOT_DIR / "etiss-pe"
# The Verilator (Vicuna) model lives under <repo>/rtl/vicuna2/build/<core>/...
VERILATOR_PRJ_SRC = PROJECT_ROOT_DIR / "rtl/vicuna2"
# Built benchmark artefacts live under <repo>/programs/build/src/<suite>/.
TEST_BUILD_BASE_DIR = PROJECT_ROOT_DIR / "programs/build"
COMPARISON_DIR = SRC_DIR
TABLE_DIR = COMPARISON_PRJ_DIR / "table"

check_path(PERFSIM_PRJ_SRC)
check_path(VERILATOR_PRJ_SRC)
# check_path(TEST_BUILD_BASE_DIR)
check_path(COMPARISON_DIR)

# Output directories are created on demand rather than required to pre-exist.
TABLE_DIR.mkdir(parents=True, exist_ok=True)

# Base directory for timing and instruction traces
ETISS_TRACES_DIR = COMPARISON_PRJ_DIR / "traces_etiss"
VERILATOR_TRACES_DIR = COMPARISON_PRJ_DIR / "traces_verilator"

ETISS_TRACES_DIR.mkdir(parents=True, exist_ok=True)
VERILATOR_TRACES_DIR.mkdir(parents=True, exist_ok=True)

# Base directory for dump files
ETISS_DUMP_DIR = TEST_BUILD_BASE_DIR
VERILATOR_DUMP_DIR = ETISS_DUMP_DIR

# check_path(ETISS_DUMP_DIR)
# check_path(VERILATOR_DUMP_DIR)
