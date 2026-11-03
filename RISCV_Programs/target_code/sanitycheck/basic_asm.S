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
	la            a3, data
	la            a4, data
	la            s5, data
	la            a5, data
	MATCH_START
	vsetvli       zero,zero,e32,m2,ta,mu
	vle8.v        v10,(a3)
	vle8.v        v11,(a2)
	vsext.vf4     v12,v10
	vsext.vf4     v14,v11
	vadd.vx       v10,v14,s10
	vadd.vx       v12,v12,s9
	vmacc.vv      v8,v10,v12
	NOP_4
	vle8.v        v10,(a3)
	vle8.v        v11,(a2)
	vsext.vf4     v12,v10
	vsext.vf4     v14,v11
	vadd.vx       v10,v14,s10
	vadd.vx       v12,v12,s9
	vmacc.vv      v8,v10,v12
	NOP_4
	vle8.v        v10,(a3)
	vle8.v        v11,(a2)
	vsext.vf4     v12,v10
	vsext.vf4     v14,v11
	vadd.vx       v10,v14,s10
	vadd.vx       v12,v12,s9
	vmacc.vv      v8,v10,v12
	NOP_64
	vle32.v       v0, (a2)
	NOP_32
	vsext.vf4     v12,v10
	NOP_32
	vadd.vx       v10,v14,s10
# vmv.s.x v10,zero
# vredsum.vs v8,v8,v10
# vmv.x.s a3,v8
	NOP_32
	vse32.v       v8, (a0)
	NOP_64
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
