#pragma once

#include <cstdint>
#include <cstdlib>

#include "PerformanceModel.h"

namespace Vicuna2_DS {

class VectorFixedDelayV1 : public ResourceModel {
public:
  VectorFixedDelayV1(PerformanceModel *parent_)
      : ResourceModel("VectorFixedDelayV1", parent_) {
    vlen_ = std::stoi(std::getenv("VLEN"));
    vlane_width_ = 32;
  };

  // V1 (storage/LSU) unpack delay. The storage pipeline is VREG_W/PIPE_W wide
  // (128/32 = 4 element-group cycles to stream one register through the 32-bit
  // lane), and this is constant for SEW<=32 because the 32-bit lane packs
  // multiple sub-32 elements per cycle. So the per-group (per-LMUL register)
  // latency is exactly vlen/vlane, NOT the byte element count.
  int getDelay(void) {
    uint64_t const vlen_vlane = vlen_ / vlane_width_;
    return (int)vlen_vlane; // 4 @ zvl128b (throughput = VREG_W/PIPE_W)
  }

private:
  uint64_t vlen_;
  uint64_t vlane_width_;
};

} // namespace Vicuna2_DS
