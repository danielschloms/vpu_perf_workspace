#pragma once

#include <cstdint>
#include <cstdlib>

#include "PerformanceModel.h"

namespace Vicuna2_DS {

class VectorFixedDelayV2 : public ResourceModel {
public:
  VectorFixedDelayV2(PerformanceModel *parent_)
      : ResourceModel("VectorFixedDelayV2", parent_) {
    vlen_ = std::stoi(std::getenv("VLEN"));
    vlane_width_ = std::stoi(std::getenv("VLANE_WIDTH"));
  };

  uint64_t *vtype_ptr;

  // V2 (compute/ALU/MUL/DIV/permute) unpack delay. Same as V1: the execution
  // pipelines are VREG_W/PIPE_W = 32-bit wide, so one register (LMUL group)
  // costs vlen/vlane = 4 element-group cycles to stream through, constant for
  // SEW<=32 (the lane packs multiple sub-32 elements/cycle). SEW does NOT add
  // cycles here.
  int getDelay(void) {
    uint64_t const vlen_vlane = vlen_ / vlane_width_;
    return (int)vlen_vlane; // 4 @ zvl128b (throughput = VREG_W/PIPE_W)
  }

private:
  uint64_t vlen_;
  uint64_t vlane_width_;

  auto getSew() -> uint64_t {
    uint64_t const vtype = vtype_ptr[getInstrIndex()];
    uint64_t const vsew = (vtype >> 3) & 0b11;
    return 8 << vsew;
  }
};

} // namespace Vicuna2_DS
