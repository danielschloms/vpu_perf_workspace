#include "asm.h"
  .option       nopic
  .attribute    unaligned_access, 0
  .attribute    stack_align, 16
  .text
  .align        2
  .globl        main
  .type         main, @function
main:
  addi          sp,sp,-32
  sw            ra,28(sp)
  sw            s0,24(sp)
  addi          s0,sp,32
  MATCH_START
  la            a0, data
  addi          a1, a0, 256
  li            t0, 32
  li            s10, 9

  # In-place accumulator chain (vmacc.vv with the SAME dest as source) interleaved
  # with a SECOND independent vector chain. Stresses:
  #  - WAW on the accumulator register (in-place, source is stale at retire), and
  #  - ILP: independent chains should NOT be over-serialized by one another.
  vsetvli       t1, t0, e32, m2, ta, ma
  vle8.v        v10,(a0)
  vle8.v        v12,(a1)
  vmv.v.i       v14, 1
  vmv.v.i       v16, 2
  # accumulator chain reads/writes v14 in place
  vmacc.vv      v8, v10, v14
  vmacc.vv      v8, v12, v14
  vmacc.vv      v8, v10, v14
  # independent chain on v16
  vadd.vv       v16, v16, v10
  vadd.vv       v16, v16, v12
  vadd.vx       v18, v16, s10
  NOP_16

  vsetvli       t1, t0, e16, m2, ta, ma
  vle16.v       v10,(a0)
  vle16.v       v12,(a1)
  vmv.v.i       v14, 1
  vmv.v.i       v16, 2
  vmacc.vv      v8, v10, v14
  vmacc.vv      v8, v12, v14
  vmacc.vv      v8, v10, v14
  vadd.vv       v16, v16, v10
  vadd.vv       v16, v16, v12
  vadd.vx       v18, v16, s10
  NOP_16

  vsetvli       t1, t0, e8, m4, ta, ma
  vle8.v        v8,(a0)
  vle8.v        v12,(a1)
  vmv.v.i       v16, 1
  vmv.v.i       v20, 2
  vmacc.vv      v24, v8, v16
  vmacc.vv      v24, v12, v16
  vmacc.vv      v24, v8, v16
  vadd.vv       v20, v20, v8
  vadd.vv       v20, v20, v12
  vadd.vx       v28, v20, s10
  NOP_16

  MATCH_END
  lw            ra,28(sp)
  lw            s0,24(sp)
  addi          sp,sp,32
  RET_INSTR
  .size         main, .-main

  .data
data:
  MEM_WORDS_256
  MEM_WORDS_256
  MEM_WORDS_256
  MEM_WORDS_256

  .size         main, .-data
.ident "GCC:
  14.2.0"
  .section      .note.GNU-stack,"",@progbits
