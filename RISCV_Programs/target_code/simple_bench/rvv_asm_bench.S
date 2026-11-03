#include "perfsim/asm.h"
	.option       nopic
	.attribute    arch, "rv32i2p1_m2p0_f2p2_zicsr2p0_zve32f1p0_zve32x1p0_zvl32b1p0"
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
  
  li        t1, 128
  vadd_vv_e8_m1_128:
  mv        t0, t1
  vsetvli   t1, t0, e8, m1, ta, ma
  vle8.v   v1,(a0)
  vle8.v   v2,(a1)
  vadd.vv   v0, v1, v2
  vse8.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vv_e8_m1_128

  
  li        t1, 128
  vadd_vv_e8_m2_128:
  mv        t0, t1
  vsetvli   t1, t0, e8, m2, ta, ma
  vle8.v   v2,(a0)
  vle8.v   v4,(a1)
  vadd.vv   v0, v2, v4
  vse8.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vv_e8_m2_128

  
  li        t1, 128
  vadd_vv_e8_m4_128:
  mv        t0, t1
  vsetvli   t1, t0, e8, m4, ta, ma
  vle8.v   v4,(a0)
  vle8.v   v8,(a1)
  vadd.vv   v0, v4, v8
  vse8.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vv_e8_m4_128

  
  li        t1, 128
  vadd_vv_e16_m1_128:
  mv        t0, t1
  vsetvli   t1, t0, e16, m1, ta, ma
  vle16.v   v1,(a0)
  vle16.v   v2,(a1)
  vadd.vv   v0, v1, v2
  vse16.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vv_e16_m1_128

  
  li        t1, 128
  vadd_vv_e16_m2_128:
  mv        t0, t1
  vsetvli   t1, t0, e16, m2, ta, ma
  vle16.v   v2,(a0)
  vle16.v   v4,(a1)
  vadd.vv   v0, v2, v4
  vse16.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vv_e16_m2_128

  
  li        t1, 128
  vadd_vv_e16_m4_128:
  mv        t0, t1
  vsetvli   t1, t0, e16, m4, ta, ma
  vle16.v   v4,(a0)
  vle16.v   v8,(a1)
  vadd.vv   v0, v4, v8
  vse16.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vv_e16_m4_128

  
  li        t1, 128
  vadd_vv_e32_m1_128:
  mv        t0, t1
  vsetvli   t1, t0, e32, m1, ta, ma
  vle32.v   v1,(a0)
  vle32.v   v2,(a1)
  vadd.vv   v0, v1, v2
  vse32.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vv_e32_m1_128

  
  li        t1, 128
  vadd_vv_e32_m2_128:
  mv        t0, t1
  vsetvli   t1, t0, e32, m2, ta, ma
  vle32.v   v2,(a0)
  vle32.v   v4,(a1)
  vadd.vv   v0, v2, v4
  vse32.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vv_e32_m2_128

  
  li        t1, 128
  vadd_vv_e32_m4_128:
  mv        t0, t1
  vsetvli   t1, t0, e32, m4, ta, ma
  vle32.v   v4,(a0)
  vle32.v   v8,(a1)
  vadd.vv   v0, v4, v8
  vse32.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vv_e32_m4_128

  
  li        t1, 128
  vadd_vx_e8_m1_128:
  mv        t0, t1
  vsetvli   t1, t0, e8, m1, ta, ma
  vle8.v   v1,(a0)
  vadd.vx   v0, v1, t5
  vse8.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vx_e8_m1_128

  
  li        t1, 128
  vadd_vx_e8_m2_128:
  mv        t0, t1
  vsetvli   t1, t0, e8, m2, ta, ma
  vle8.v   v2,(a0)
  vadd.vx   v0, v2, t5
  vse8.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vx_e8_m2_128

  
  li        t1, 128
  vadd_vx_e8_m4_128:
  mv        t0, t1
  vsetvli   t1, t0, e8, m4, ta, ma
  vle8.v   v4,(a0)
  vadd.vx   v0, v4, t5
  vse8.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vx_e8_m4_128

  
  li        t1, 128
  vadd_vx_e16_m1_128:
  mv        t0, t1
  vsetvli   t1, t0, e16, m1, ta, ma
  vle16.v   v1,(a0)
  vadd.vx   v0, v1, t5
  vse16.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vx_e16_m1_128

  
  li        t1, 128
  vadd_vx_e16_m2_128:
  mv        t0, t1
  vsetvli   t1, t0, e16, m2, ta, ma
  vle16.v   v2,(a0)
  vadd.vx   v0, v2, t5
  vse16.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vx_e16_m2_128

  
  li        t1, 128
  vadd_vx_e16_m4_128:
  mv        t0, t1
  vsetvli   t1, t0, e16, m4, ta, ma
  vle16.v   v4,(a0)
  vadd.vx   v0, v4, t5
  vse16.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vx_e16_m4_128

  
  li        t1, 128
  vadd_vx_e32_m1_128:
  mv        t0, t1
  vsetvli   t1, t0, e32, m1, ta, ma
  vle32.v   v1,(a0)
  vadd.vx   v0, v1, t5
  vse32.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vx_e32_m1_128

  
  li        t1, 128
  vadd_vx_e32_m2_128:
  mv        t0, t1
  vsetvli   t1, t0, e32, m2, ta, ma
  vle32.v   v2,(a0)
  vadd.vx   v0, v2, t5
  vse32.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vx_e32_m2_128

  
  li        t1, 128
  vadd_vx_e32_m4_128:
  mv        t0, t1
  vsetvli   t1, t0, e32, m4, ta, ma
  vle32.v   v4,(a0)
  vadd.vx   v0, v4, t5
  vse32.v   v0, (a0)
  sub       t1, t0, t1
  bnez      t1, vadd_vx_e32_m4_128

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

.ident "GCC:
	()            14.2.0"
	.section      .note.GNU-stack,"",@progbits
