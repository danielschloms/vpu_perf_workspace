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
  li            s1, 3
  li            s2, 5
  li            s3, 7

  # Fire-and-forget data-move (vsext) whose widened result FANS OUT to several
  # consumers: one independent ALU chain (should retire at source-readiness) plus
  # a completion-gated accumulator chain (vmacc, should retire at vector rate).
  # This separates the "producer retires early" behavior from the "consumer
  # follows the vector pipeline" behavior for a single source register.
  vsetvli       t1, t0, e32, m2, ta, ma
  vle8.v        v10,(a0)
  vsext.vf4     v12,v10            # fire-and-forget producer
  # consumer A: independent ALU (source-ready consumers)
  vadd.vx       v14,v12,s1
  vadd.vx       v16,v12,s2
  # consumer B: completion-gated accumulator
  vmacc.vv      v18,v12,v14
  vmul.vx       v20,v12,s3
  NOP_16

  vsetvli       t1, t0, e16, m2, ta, ma
  vle16.v       v10,(a0)
  vsext.vf2     v12,v10
  vadd.vx       v14,v12,s1
  vadd.vx       v16,v12,s2
  vmacc.vv      v18,v12,v14
  vmul.vx       v20,v12,s3
  NOP_16

  vsetvli       t1, t0, e32, m4, ta, ma
  vle8.v        v8,(a0)
  vsext.vf4     v12,v8
  vadd.vx       v16,v12,s1
  vadd.vx       v20,v12,s2
  vmacc.vv      v24,v12,v16
  vmul.vx       v28,v12,s3
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
