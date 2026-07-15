SCRIPTS_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_ROOT_DIR="$(dirname "$SCRIPTS_DIR")"

$PROJECT_ROOT_DIR/Perfsim/gen_vicuna.sh
$SCRIPTS_DIR/compact-sched.py
$PROJECT_ROOT_DIR/Perfsim/etiss-perf-sim/rebuild.sh
