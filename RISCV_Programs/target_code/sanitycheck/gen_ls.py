#!/usr/bin/env python3


def main():
    header_str = """\
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
"""
    print(header_str)
    lmuls = [1, 2, 4, 8]
    sews = [8, 16, 32]
    ls_widths = [8, 16, 32]
    n_instrs = 5

    # Non-overlapping
    for instr in ["vle", "vse"]:
        for lmul in lmuls:
            for sew in sews:
                for ls_width in ls_widths:
                    if sew > ls_width:
                        continue
                    print(f"    vsetvli zero, zero, e{sew}, m{lmul}, ta, ma")
                    emul = int(lmul * (max(sew / ls_width, ls_width / sew)))
                    emul = int(sew / 8) if emul < sew / 8 else emul
                    emul = 8
                    for i in range(n_instrs):
                        print(f"    {instr}{ls_width}.v v{(i*emul) % 32}, (a2)")
                    print(f"    NOP_4")

    # Overlapping
    for instr in ["vle", "vse"]:
        for lmul in lmuls:
            for sew in sews:
                for ls_width in ls_widths:
                    if sew > ls_width:
                        continue
                    print(f"    vsetvli zero, zero, e{sew}, m{lmul}, ta, ma")
                    for i in range(n_instrs):
                        print(f"    {instr}{ls_width}.v v0, (a2)")
                    print(f"    NOP_4")

    end_str = """\
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
"""
    print(end_str)


if __name__ == "__main__":
    main()
