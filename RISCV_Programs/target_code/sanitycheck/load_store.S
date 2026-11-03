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
	la            a0, data
	addi          a1, a0, 128
	addi          a2, a1, 128
	li            a3, 10
	li            a4, 128

	MATCH_START
	li            t0, 10
	vsetvli       t1, t0, e8, m1, ta, ma
	NOP_4
	vle32.v       v0, (a2)
	vse32.v       v0, (a1)
	NOP_16
	vsetvli       t1, t0, e8, m2, ta, ma
	NOP_4
	vle32.v       v0, (a2)
	vse32.v       v0, (a1)
	NOP_16
	vsetvli       t1, t0, e16, m1, ta, ma
	NOP_4
	vle32.v       v0, (a2)
	vse32.v       v0, (a1)
	NOP_16
	vsetvli       t1, t0, e16, m2, ta, ma
	NOP_4
	vle32.v       v0, (a2)
	vse32.v       v0, (a1)
	NOP_16
	vsetvli       t1, t0, e16, m4, ta, ma
	NOP_4
	vle32.v       v0, (a2)
	vse32.v       v0, (a1)
	NOP_16
	vsetvli       t1, t0, e32, m1, ta, ma
	NOP_4
	vle32.v       v0, (a2)
	vse32.v       v0, (a1)
	NOP_16
	vsetvli       t1, t0, e32, m2, ta, ma
	NOP_4
	vle32.v       v0, (a2)
	vse32.v       v0, (a1)
	NOP_16
	vsetvli       t1, t0, e32, m4, ta, ma
	NOP_4
	vle32.v       v0, (a2)
	vse32.v       v0, (a1)
	NOP_16
	vsetvli       t1, t0, e32, m8, ta, ma
	NOP_4
	vle32.v       v0, (a2)
	vse32.v       v0, (a1)
	NOP_16
	MATCH_END

	andi          a0,a0,0
	lw            ra,28(sp)
	lw            s0,24(sp)
	addi          sp,sp,32
	RET_INSTR
	.size         main, .-main

	.data
data:
	MEM_WORDS_256
	MEM_WORDS_256

	.size         main, .-data
.ident "GCC:
	14.2.0"
	.section      .note.GNU-stack,"",@progbits

