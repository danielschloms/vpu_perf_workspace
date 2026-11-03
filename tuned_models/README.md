# Hand-tuned ETISS Vicuna_zvl128b model (cv32e40x converged)

Snapshot of the currently-converged hand-tuned `Vicuna_zvl128b` performance model.
All results below are for **cv32e40x**, `rv32im_zve32x`, `--hw-config 128,32`,
metric = "enter WB" (`EX_stg`).

Target: simple-patterns CPI error < 2.5%, ADI < 0.1.

| benchmark              | CPI err (%) | ADI    |
|------------------------|-------------|--------|
| crit_toy               | +5.06       | 0.1860 |
| load_alu_vv_store      | +0.00       | 0.1304 |
| load_alu_vx_store      | +0.00       | 0.1304 |
| load_macc_vv_store     | -1.06       | 0.1406 |
| load_mul_vv_store      | -1.06       | 0.1406 |
| load_red_store         | -1.34       | 0.0815 |
| load_store             | +0.31       | 0.0097 |
| loadstores             | -2.44       | 0.2484 |
| store_unpack_interleave| -4.76       | 0.0500 |
| vmv_red_vmv            | +2.69       | 0.1236 |
| vmv_v_i_store          | +1.28       | 0.1134 |

> Note: `vmacc_inplace_ilp` (ADI 0.7294) and `vsext_fanout_ilp` (ADI 0.4667)
> are pre-existing baselines, not regressions introduced by the store-gate change.

## Files

These mirror the live model at:
`etiss-pe/etiss-perf-sim/etiss_plugins/SoftwareEvalLib/libs/backends/`:

- `Vicuna_zvl128b_GroupSchedulingFunction.cpp` — the batched group scheduling
  functions (the file actually compiled into the plugin). Contains the
  hand-tuned reduction store-gate (`EX+4+4*LMUL-sewByteShift`), fire-forget
  `setWbRetireAnyway`, load-path 3-arg `setVd` decoupling, and the 4-arg
  compute `setVd` barrier.
- `Vicuna_zvl128b_GroupSchedulingFunction.hpp`
- `Vicuna_zvl128b_ResultSchedulingFunction.cpp`
- `Vicuna_zvl128b_PerformanceModel.cpp`
- `Vicuna2_DS/*.h` — external model headers:
  - `VectorBatchHandModel.h`: dual-signal `getWbFreeSignal`/`getWbSignal`/
    `getVectorRetireGate`, `getRetireLatency`=11, `vectorBusyUntil`,
    `wbRetireAnyway`, `vectorComputeWrites`+`getVs3ComputeReady`, 4-arg
    `setVd`, `getSewByteShift()`.
  - `VectorFixedDelayV1.h`, `VectorFixedDelayV2.h`, `VectorDivDelay.h`,
    `VectorElmDelay.h`, `VectorConfig.h`.

## Codegen capability (verified)

The M2-ISA-R-Perf codegen pipeline **works and reproduces faithfully**, but it
cannot express the converged timing semantics. Verified facts:

- `gen_vicuna.sh` → `cpp -E -P` expands `#define` macros / `#include` into
  `code_gen/descriptions/core_perf_dsl/out.corePerfDsl`, then
  `scripts/support/code_gen_helper.py` runs `m2isar_perf/run.py -c`.
- Running the real pipeline on `out.corePerfDsl` yields a folder under `out/`
  whose `Vicuna_zvl128b_..._SchedulingFunction.cpp` is **byte-identical** to the
  checked-in codegen-source `Vicuna_zvl128b_SchedulingFunction.cpp`.
- That codegen output is a **per-instruction, non-batched** model:
  - `setVd(n_V1_Pack_Write)` (1-arg), `setWbFreeSignal(n_V1_Pack_FreeWb)`
  - No `getLmul()`, no batch `for` loop, no 4-arg `setVd`, no
    `vectorBatchHandModel.getSewByteShift()`, no `setWbRetireAnyway`, no
    `getVs3ComputeReady`.
- The **built plugin compiles `GroupSchedulingFunction.cpp`** (not the
  codegen-source `SchedulingFunction.cpp` — see the variant CMakeLists).
  `GroupSchedulingFunction.cpp` is produced from the codegen output by
  `scripts/compact-schedule_DS.py`, which only does textual batching
  (`setVd(` → `setVd(batch_i,`, `getVsN()` → `getVsN(batch_i)`). It does **not**
  introduce any of the behavioral tuning.
- The CorePerfDSL grammar (`Vicuna2_uAMapping_DS.corePerfDsl` +
  `Vicuna2_Pipeline_DS.corePerfDsl`) only wires a **single** scalar
  `WbFreeSignal` retirement. It has no model for: dual-signal WB split,
  fire-forget (`wbRetireAnyway`), per-source V1 barrier (`vectorComputeWrites`
  / `getVs3ComputeReady`), 4-arg `setVd(...,v1Barrier)`, or the
  SEW-dependent reduction store-gate.

**Conclusion:** the CV32E40X `_DS` CorePerfDSL **cannot** reproduce the
converged timing model on its own. The convergence depends on hand-written
semantics in `VectorBatchHandModel.h` and the derived batched
`GroupSchedulingFunction.cpp`. Any further tuning (e.g. the per-core a60x
store-drain knob) must go into that header + derived `.cpp`, not the DSL.

## Key hand-tuned mechanisms

- **Dual-signal WB**: `getWbFreeSignal()` returns
  `max(wbFreeSignal, vectorBusyUntil)` for general in-order ops AND the
  fire-forget branch `max(wbFreeSignal, src)` when `wbRetireAnyway`.
  `getWbSignal()` = `wbFreeSignal` only (stores/vsetvli fast retire).
  `getVectorRetireGate()` = `max(wbFreeSignal, vectorBusyUntil)`.
- **Fire-forget**: `V_Ext`, `V_vmv_v_i`, `V_vmv_regs`, `V_vmv_s_x` wrap
  `setWbRetireAnyway(true)/(false)`.
- **Load-path decoupling**: `V_Load`/`V_Load_Registers` use 3-arg
  `setVd(batch_i, n_V1_Pack_Write+1, n_V1_Pack_FreeWb)` plus
  `setWbFreeSignal(n_V1_Subpipe)`.
- **Compute vs data-move split**: compute `setVd` passes 4th arg `v1Barrier`;
  data-move (fire-forget) keeps 3-arg `(V2_Unpack < EX ? EX+11 : V2_Unpack)`.
- **Per-source V1 barrier**: `vectorComputeWrites[32]` + `getVs3ComputeReady()`;
  V1 stores gate `V1_Unpack` on it.
- **Reduction store-gate**: reduction `v1Barrier` =
  `EX + 4 + 4*LMUL - getSewByteShift()` (derived from RTL drain
  `10 + 8*LMUL - log2(sew/8)`). Only `V_REDSUM`/`V_REDMINMAX`.
