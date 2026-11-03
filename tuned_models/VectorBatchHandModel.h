/*
 * Copyright 2022 Chair of EDA, Technical University of Munich
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	 http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <string>

#include "PerformanceModel.h"

#define PRINT_REG_COMMITS

#ifdef PRINT_REG_COMMITS
#define CPRINT(...) std::printf(__VA_ARGS__)
#else
#define CPRINT(...)
#endif

namespace Vicuna2_DS {

class VectorBatchHandModel : public ConnectorModel {
private:
  // Vector register timestamps
  // std::array<uint64_t, 32> vectorRegisterReads{0};
  std::array<uint64_t, 32> vectorRegisterWrites{0};
  // V1-consumer barrier: for a V2-COMPUTE op, the V2 pipe must fully drain before a
  // V1 pipe op (load/store) that reads its result issues. Set only by compute ops
  // (dataReady for V2 consumers) to the op's retire barrier. Data-move (fire-forget)
  // producers leave this 0 so a store reading them is NOT gated by the V2 drain.
  std::array<uint64_t, 32> vectorComputeWrites{0};

  // Vector signal timestamps
  uint64_t vsetSignal = 0;
  uint64_t wbFreeSignal = 0;
  // In-order retire watermark: the most recent vector pipeline completion (op's
  // Vd write-back at its V2_Pack/V1_Pack). The NEXT instruction's scalar EX is
  // blocked on this so the retire chain advances at the vector rate in program
  // order. This is register-independent (handles in-place accumulators where the
  // source register is stale at retire time) and does NOT hold the op itself in
  // WB (ALU is fire-and-forget; only XRESULT stalls).
  uint64_t vectorBusyUntil = 0;
  // Retire-chain latency: the fixed number of cycles a vector op's enter-WB sits
  // behind the previous op's enter-WB in an in-order program order when the vector
  // pipe (VLEN/VLANE streaming depth) is the bottleneck. This is the "rate" at
  // which the in-order retire watermark advances for completion-gated ops. It is
  // decoupled from the op's own DATA start (V2_Unpack): a cheap data-move op
  // (vmv/vsext) has a V2_Unpack earlier than its EX, so using V2_Unpack as the
  // retire watermark under-paces the downstream chain.
  static constexpr uint64_t retireLatency = 11;

  // Fire-and-forget flag for the CURRENT op (set by its scheduling function just
  // before the EX/WB computation). When true the op's scalar enter-WB advances at
  // its source-register readiness (the producer's data), NOT the global completion
  // watermark. Used for pure data-movement/extension ops (vsext, vmv, ...) whose
  // result is a temp the scalar does not consume immediately; arithmetic/accumulate
  // ops (vadd, vmacc, ...) stay completion-gated to match the RTL. Reset at the end
  // of the scheduling function so it never leaks to the next op.
  bool wbRetireAnyway = false;
  uint64_t memArbiterSignal = 0;
  uint64_t commitSignal = 0;

  // Dispatch OK times
  uint64_t dispatch_1_ready = 0;
  uint64_t dispatch_2_ready = 0;

  auto getVs1Index() -> uint64_t { return vs1_ptr[getInstrIndex()]; }

  auto getVs2Index() -> uint64_t { return vs2_ptr[getInstrIndex()]; }

  auto getVs3Index() -> uint64_t { return vs3_ptr[getInstrIndex()]; }

  auto getVdIndex() -> uint64_t { return vd_ptr[getInstrIndex()]; }

  auto getSew() -> uint64_t {
    uint64_t const vtype = vtype_ptr[getInstrIndex()];
    uint64_t const vsew = (vtype >> 3) & 0b11;
    // SEW can be calculated by shifting 8 left by the register value (vsew)
    return 8 << vsew;
  }

  auto log2(uint64_t value) -> uint64_t {
    auto result = 0;
    value >>= 1;
    while (value) {
      result++;
      value >>= 1;
    }
    return result;
  }

  auto decodeMultiplicativeLmul(uint64_t const encodedLmul) -> uint64_t {
    static constexpr auto lmulValueBitmask = 0b11;
    return 1 << (encodedLmul & lmulValueBitmask);
  }

  auto getEncodedLmul() -> uint64_t {
    uint64_t const vtype = vtype_ptr[getInstrIndex()];
    static constexpr auto vlmulBitmask = 0b111;
    return vtype & vlmulBitmask;
  }

  auto lmulIsFractional(uint64_t const lmul) -> bool {
    static constexpr auto fractionalLmulBitmask = 0b100;
    return (lmul & fractionalLmulBitmask) != 0;
  }

  auto lmulIsFractional() -> bool {
    uint64_t const vtype = vtype_ptr[getInstrIndex()];
    static constexpr auto fractionalLmulBitmask = 0b100;
    auto const isFractionalLmul = vtype & fractionalLmulBitmask;
    return isFractionalLmul != 0;
  }

public:
  VectorBatchHandModel(PerformanceModel *parent_)
      : ConnectorModel("VectorBatchHandModel", parent_){
            // vlen_ = std::stoi(std::getenv("VLEN"));
            // vlane_width_ = std::stoi(std::getenv("VLANE_WIDTH"));
            // if (vlane_width_ * 2 >= vlen_) {
            //   unpack_2_depth--;
            // }
            // if (VectorConfig::vMemWidth * 2 >= vlen_) {
            //   unpack_1_depth--;
            // }
        };

  uint64_t *vs1_ptr;
  uint64_t *vs2_ptr;
  uint64_t *vs3_ptr;
  uint64_t *vd_ptr;
  uint64_t *vm_ptr;
  uint64_t *vtype_ptr;

  // Loads
  uint64_t *lsWidth_ptr;

  // Whole register loads
  uint64_t *nf_ptr;
  // Whole register moves
  uint64_t *simm5_ptr;

  auto getLmul() -> uint64_t {
    uint64_t const vtype = vtype_ptr[getInstrIndex()];
    static constexpr auto fractionalLmulBitmask = 0b100;
    auto const isFractionalLmul = vtype & fractionalLmulBitmask;
    auto lmul = 1;

    if (!isFractionalLmul && ((vtype & 0b11) != 0)) {
      static constexpr auto lmulValueBitmask = 0b11;
      lmul = 1 << (vtype & lmulValueBitmask);
    }

    return lmul;
  }

  constexpr auto one() -> uint64_t { return 1; }

  auto getLoadStoreEmul() -> uint64_t {
    auto const loadWidth = lsWidth_ptr[getInstrIndex()];
    auto const sew = getSew();

    // EMUL = LMUL >= m1 if loadWidth == sew
    auto emul = getLmul();

    if (loadWidth > sew) {
      // EMUL = multiple of LMUL
      // Calculate by adding log2(loadWidth / sew) to vlmul
      // If the fractional bit is still 1, EMUL = 1
      // otherwise just the decoded multiplicative LMUL of that new value.
      // m8 overflowing should result in an illegal instruction anyway, so it is
      // not checked. See spec.
      auto const encodedEmul = getEncodedLmul() + log2(loadWidth / sew);
      emul = lmulIsFractional(encodedEmul)
                 ? 1
                 : decodeMultiplicativeLmul(encodedEmul);
    } else if (loadWidth < sew) {
      // EMUL = fraction of LMUL
      // If LMUL fractional, or log2(loadWidth / sew) >= vlmul, EMUL = 1
      // otherwise subtract log2(loadWidth / sew) from vlmul and decode.
      // See spec.
      auto const vlmul = getEncodedLmul();
      auto const decrement = log2(sew / loadWidth);
      if (lmulIsFractional() || decrement > vlmul) {
        emul = 1;
      } else {
        emul = decodeMultiplicativeLmul(vlmul - decrement);
      }
    }
    return emul;
  }

  // NF = encodedNF + 1
  auto getNf() -> uint64_t { return nf_ptr[getInstrIndex()] + 1; }
  auto getNfSimm5() -> uint64_t { return simm5_ptr[getInstrIndex()] + 1; }

  auto getVs1() -> uint64_t { return vectorRegisterWrites[getVs1Index()]; }
  auto getVs2() -> uint64_t { return vectorRegisterWrites[getVs2Index()]; }
  auto getVs3() -> uint64_t { return vectorRegisterWrites[getVs3Index()]; }
  auto getVs1(unsigned lmulIndex) -> uint64_t {
    auto const reg = getVs1Index();
    auto const val = vectorRegisterWrites[reg + lmulIndex];
    // std::printf("(Vs1) Get t_v%lu = %lu\n", reg + lmulIndex, val);
    return val;
  }
  auto getVs2(unsigned lmulIndex) -> uint64_t {
    auto const reg = getVs2Index();
    auto const val = vectorRegisterWrites[reg + lmulIndex];
    // std::printf("(Vs2) Get t_v%lu = %lu\n", reg + lmulIndex, val);
    return val;
  }
  auto getVs3(unsigned lmulIndex) -> uint64_t {
    auto const reg = getVs3Index();
    auto const val = vectorRegisterWrites[reg + lmulIndex];
    // std::printf("(Vs3) Get t_v%lu = %lu\n", reg + lmulIndex, val);
    return val;
  }

  // V1-consumer barrier for the source register read by this op (vs3). For a
  // store reading a V2-compute result this is the producer's V2 pipe-drain
  // barrier; 0 for data-move producers (no extra V2->V1 coupling to gate on).
  auto getVs3ComputeReady() -> uint64_t {
    uint64_t const vs3 = getVs3Index();
    return (vs3 < 32) ? vectorComputeWrites[vs3] : 0;
  }

  auto setVd(uint64_t timestamp) {
    vectorRegisterWrites[getVdIndex()] = timestamp;
    vectorBusyUntil = std::max(vectorBusyUntil, timestamp + 1);
  }
  auto setVd(unsigned lmulIndex, uint64_t timestamp) {
    auto const reg = getVdIndex();
    vectorRegisterWrites[reg + lmulIndex] = timestamp + 1;
    vectorBusyUntil = std::max(vectorBusyUntil, timestamp + 1);
    // std::printf("Set t_v%lu = %lu\n", reg + lmulIndex, timestamp + 1);
  }
  // Two-stage vector write: the destination register DATA is not ready until its
  // V2_Pack (completion, so dependent vector ops / vector->scalar reads get the
  // real producer latency), but the in-order scalar RETIRE chain (vectorBusyUntil)
  // only needs to advance to the op's V2_Unpack (where the vector pipeline starts
  // streaming). This decouples the RTL's two behaviors: arithmetic/accumulator ops
  // retire at the vector-progression watermark (V2_Unpack) while their data lands
  // at V2_Pack. Without this split, a fire-and-forget vsext's V2_Pack (which is
  // later than the vadd's V2_Unpack) over-serializes the downstream vadd chain.
  auto setVd(unsigned lmulIndex, uint64_t dataReady, uint64_t busyUntil,
             uint64_t v1Barrier = 0) {
    auto const reg = getVdIndex();
    vectorRegisterWrites[reg + lmulIndex] = dataReady;
    vectorBusyUntil = std::max(vectorBusyUntil, busyUntil);
    if (v1Barrier) vectorComputeWrites[reg + lmulIndex] = v1Barrier;
  }

  auto getWbFreeSignal(void) -> uint64_t {
    if (wbRetireAnyway) {
      // Fire-and-forget data-movement op (vsext/vmv...): retire at the source
      // operand's readiness (its producer's data write), so the scalar enter-WB is
      // NOT held by the vector completion watermark. Source register may be out of
      // modeled range during setup -> guard.
      uint64_t const vs2 = getVs2Index();
      uint64_t const src = (vs2 < 32) ? vectorRegisterWrites[vs2] : 0;
      return std::max(wbFreeSignal, src);
    }
    // General in-order retire: blocked by both the scalar WB slot (wbFreeSignal)
    // and the vector pipeline occupancy watermark (vectorBusyUntil). Vector
    // compute ops AND scalar arithmetic that sits behind a vector op must wait for
    // the vector pipe to drain before retiring (d+11), while the vectorBusyUntil
    // is low (no active vector pipe) it reduces to the plain in-order WB slot.
    return std::max(wbFreeSignal, vectorBusyUntil);
  }
  auto getWbSignal() const -> uint64_t { return wbFreeSignal; }
  auto getVectorBusyUntil() const -> uint64_t { return vectorBusyUntil; }
  auto getVectorRetireGate() const -> uint64_t {
    return std::max(wbFreeSignal, vectorBusyUntil);
  }
  auto setWbFreeSignal(uint64_t timestamp) -> void {
    wbFreeSignal = timestamp + 1;
  }
  auto setWbRetireAnyway(bool f) -> void { wbRetireAnyway = f; }
  auto getRetireLatency() const -> uint64_t { return retireLatency; }

  // SEW-dependent store-drain term = log2(sew/8) (0 for e8, 1 for e16, 2 for e32).
  // A reduction-fed store's drain to the following scalar op is (10 - this) + 8*LMUL
  // in the RTL, so the reduction's V1 store-gate barrier subtracts this term.
  auto getSewByteShift() -> uint64_t {
    uint64_t const vtype = vtype_ptr[getInstrIndex()];
    uint64_t const vsew = (vtype >> 3) & 0b11;
    return (vsew > 0) ? vsew : 0;
  }

  void setVsetSignal(uint64_t timestamp) { vsetSignal = timestamp - 1; }
  auto getVsetSignal() -> uint64_t { return vsetSignal; };

  auto setMemArbiterSignal(uint64_t timestamp) -> void {
    memArbiterSignal = timestamp;
  }
  auto getMemArbiterSignal() -> uint64_t { return memArbiterSignal; };

  auto setCommitSignal(uint64_t timestamp) -> void { commitSignal = timestamp; }
  auto getCommitSignal() -> uint64_t { return commitSignal; }

  auto setDispatch1Ready(uint64_t timestamp) -> void {
    dispatch_1_ready = timestamp;
  }

  auto setDispatch2Ready(uint64_t timestamp) -> void {
    dispatch_2_ready = timestamp;
  }

  // Get the max. timestamp for a target register group
  uint64_t getMaxVdGroup(void) {
    auto const emul = getLmul();
    auto const registerBaseIndex = getVdIndex();
    auto const start = vectorRegisterWrites.begin() + registerBaseIndex;
    // Ready 1 cycle after register done
    auto const max_elm = *(std::max_element(start, start + emul));
    // std::printf("WAW: Max. v%lu - v%lu = %lu\n", registerBaseIndex,
    //             registerBaseIndex + emul - 1, max_elm);
    return max_elm;
  }

  uint64_t getMaxVdGroupWide(void) {
    auto const emul = 2 * getLmul();
    auto const registerBaseIndex = getVdIndex();
    auto start = vectorRegisterWrites.begin() + registerBaseIndex;
    // Ready 1 cycle after register done
    return (*(std::max_element(start, start + emul)));
  }

  // Get the max. timestamp for a register group based on nf
  uint64_t getMaxVdGroupNf(void) {
    auto const nFields = getNf();
    auto const registerBaseIndex = getVdIndex();
    auto start = vectorRegisterWrites.begin() + registerBaseIndex;
    // Ready 1 cycle after register done
    return std::max((*(std::max_element(start, start + nFields))),
                    dispatch_1_ready);
  }

  uint64_t getDispatch1Ready(void) { return dispatch_1_ready; }

  uint64_t getDispatch2Ready(void) { return dispatch_2_ready; }

  // Get the max. timestamp for a register group for load instructions
  uint64_t getMaxVdGroupLoad(void) {
    auto const emul = getLoadStoreEmul();
    auto const registerBaseIndex = getVdIndex();
    auto start = vectorRegisterWrites.begin() + registerBaseIndex;
    // Ready 1 cycle after register done
    return std::max((*(std::max_element(start, start + emul))),
                    dispatch_1_ready);
  }

  // auto getWaitTime(uint64_t emul) -> uint64_t {
  //   return emul * (vlen_ / vlane_width_);
  // }

  // auto getWaitTimeLsu(uint64_t emul) -> uint64_t {
  //   return emul * (vlen_ / VectorConfig::vMemWidth);
  // }
};

} // namespace Vicuna2_DS