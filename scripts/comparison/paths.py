import pathlib
from util import check_path

SRC_DIR = pathlib.Path(__file__).parent.resolve()
COMPARISON_PRJ_DIR = SRC_DIR.parent
PROJECT_ROOT_DIR = COMPARISON_PRJ_DIR.parent.parent

PERFSIM_PRJ_SRC = PROJECT_ROOT_DIR / "toolchain/etiss_base/etiss_perfsim"
VERILATOR_PRJ_SRC = PROJECT_ROOT_DIR / "processor_models/verilator"
TEST_BUILD_BASE_DIR = PROJECT_ROOT_DIR / "build_programs" / "build"
COMPARISON_DIR = COMPARISON_PRJ_DIR / "comparison"
TABLE_DIR = COMPARISON_PRJ_DIR / "table"

check_path(PERFSIM_PRJ_SRC)
check_path(VERILATOR_PRJ_SRC)
# check_path(TEST_BUILD_BASE_DIR)
check_path(COMPARISON_DIR)
check_path(TABLE_DIR)

# Base directory for timing and instruction traces
ETISS_TRACES_DIR = COMPARISON_PRJ_DIR / "traces_etiss"
VERILATOR_TRACES_DIR = COMPARISON_PRJ_DIR / "traces_verilator"

check_path(ETISS_TRACES_DIR)
check_path(VERILATOR_TRACES_DIR)

# Base directory for dump files
ETISS_DUMP_DIR = TEST_BUILD_BASE_DIR
VERILATOR_DUMP_DIR = ETISS_DUMP_DIR

# check_path(ETISS_DUMP_DIR)
# check_path(VERILATOR_DUMP_DIR)
