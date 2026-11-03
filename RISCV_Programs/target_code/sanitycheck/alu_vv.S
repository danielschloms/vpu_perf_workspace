#include "perfsim/asm.h"
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
  li            t5, 15

  li            t0, 32
  vsetvli       t1, t0, e8, m1, ta, ma
  vadd.vv       v0, v1, v2
  vadd.vv       v0, v1, v2
  vadd.vv       v0, v1, v2
  vadd.vv       v0, v1, v2
  vadd.vv       v0, v1, v2
  vadd.vv       v0, v1, v2
  vadd.vv       v0, v1, v2
  vadd.vv       v0, v1, v2
  vadd.vv       v0, v1, v2
  vadd.vv       v0, v1, v2
  vadd.vv       v0, v1, v2
  vadd.vv       v0, v1, v2
  vse8.v        v0, (a0)
  NOP_16
  # vadd.vv       v2, v1, v1
  vadd.vv       v3, v1, v2
  vadd.vv       v4, v1, v2
  vadd.vv       v5, v1, v2
  vadd.vv       v6, v1, v2
  vadd.vv       v7, v1, v2
  vadd.vv       v8, v1, v2
  vadd.vv       v9, v1, v2
  vadd.vv       v10, v1, v2
  vadd.vv       v11, v1, v2
  vadd.vv       v12, v1, v2
  vadd.vv       v13, v1, v2
  vse8.v        v13, (a0)
  NOP_16
  vsetvli       t1, t0, e8, m2, ta, ma
  vadd.vv       v0, v4, v2
  vadd.vv       v0, v4, v2
  vadd.vv       v0, v4, v2
  vadd.vv       v0, v4, v2
  vadd.vv       v0, v4, v2
  vadd.vv       v0, v4, v2
  vadd.vv       v0, v4, v2
  vadd.vv       v0, v4, v2
  vadd.vv       v0, v4, v2
  vadd.vv       v0, v4, v2
  vadd.vv       v0, v4, v2
  vadd.vv       v0, v4, v2
  vse8.v        v0, (a0)
  NOP_16
  vadd.vv       v4, v0, v2
  vadd.vv       v6, v0, v2
  vadd.vv       v8, v0, v2
  vadd.vv       v10, v0, v2
  vadd.vv       v12, v0, v2
  vadd.vv       v14, v0, v2
  vadd.vv       v16, v0, v2
  vadd.vv       v18, v0, v2
  vadd.vv       v20, v0, v2
  vadd.vv       v22, v0, v2
  vadd.vv       v24, v0, v2
  vadd.vv       v26, v0, v2
  vse8.v        v26, (a0)
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
