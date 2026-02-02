# VPU Performance Workspace

### Prerequisites

Prerequisites for various programs can be found in `Docker/Dockerfile`.
The image can be built with `Docker/build.sh` and be used as a development container with `.devcontainer/devcontainer.json` in VSCode.

### Installation

There is a single script that will clone and install all relevant tools (`init-workspace.sh`).
Check `install-thirdparty.sh` to see for which architectures GCC is built (`build_and_install_rv_gcc()`), and to add/remove architectures.

### Running

Simply run `Scripts/simple-examples.sh` to run some simple RISC-V Vector examples.
Hardware configurations are specified in `Perf_Comparison/testing/config.py`.
Here one can specify then used VLENs and VLANE_WIDTHs for each architecture, and one can specify custom targets that include multiple tests.
When adding new custom targets, they need to have a corresponding CMake target in RISCV_Programs, e.g. `ml_bench` is a target that has `toycar, aww, vww` as dependencies.