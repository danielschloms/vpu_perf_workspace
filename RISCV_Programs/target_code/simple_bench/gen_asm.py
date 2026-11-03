#!/usr/bin/env python3

import pathlib
import math

from test_config import TEST_FUNCS, INSTR_TYPES

LMUL_TABLE = {
    "mf8": {
        "mul": {2: "mf4", 4: "mf2", 8: "m1"},
        "div": {2: "Illegal", 4: "Illegal", 8: "Illegal"},
        "n_regs": 1,
    },
    "mf4": {
        "mul": {2: "mf2", 4: "m1", 8: "m2"},
        "div": {2: "mf8", 4: "Illegal", 8: "Illegal"},
        "n_regs": 1,
    },
    "mf2": {
        "mul": {2: "m1", 4: "m2", 8: "m4"},
        "div": {2: "mf4", 4: "mf8", 8: "Illegal"},
        "n_regs": 1,
    },
    "m1": {
        "mul": {2: "m2", 4: "m4", 8: "m8"},
        "div": {2: "mf2", 4: "mf4", 8: "mf8"},
        "n_regs": 1,
    },
    "m2": {
        "mul": {2: "m4", 4: "m8", 8: "Illegal"},
        "div": {2: "m1", 4: "mf2", 8: "mf4"},
        "n_regs": 2,
    },
    "m4": {
        "mul": {2: "m8", 4: "Illegal", 8: "Illegal"},
        "div": {2: "m2", 4: "m1", 8: "mf2"},
        "n_regs": 4,
    },
    "m8": {
        "mul": {2: "Illegal", 4: "Illegal", 8: "Illegal"},
        "div": {2: "m4", 4: "m2", 8: "m1"},
        "n_regs": 8,
    },
}


def clamp(val: int, min_val: int, max_val: int) -> int:
    return max(min_val, min(val, max_val))


SCRIPT_DIR = pathlib.Path(__file__).parent
TEST_NAME = "rvv_asm_bench"
TEST_PATH = pathlib.Path(f"{SCRIPT_DIR}/{TEST_NAME}.S")

# USE_TEST_FUNCS = TEST_FUNCS.keys()
USE_TEST_FUNCS = ["vadd"]

TEST_CONFIG = {
    # TODO _wx gets compiled to non-widening _vx
    # "modes": ["vv", "vx", "vi", "vm", "wvv", "wwv", "wvx", "wwx", "ext"],
    "modes": ["vv", "vm", "xv"],
    "lmuls": ["m1", "m2", "m4"],
    "widths": [8, 16, 32],
    "n_elements": [128],
}

LEGAL_FRAC_LMULS = {
    # TODO: compiler errors for sew 8 mf8, sew 16 mf4, sew 32
    8: ["mf4", "mf2"],
    16: ["mf2"],
    32: [],
    64: [],
}

VS2_DATA_ADDR_REG = "a0"
VS1_DATA_ADDR_REG = "a1"
RUNNING_DATA_ADDR_REG = "a2"
RS1_REG = "t5"
RS1_VAL = 15

ASM_HEADER = f"""\
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
  li            {RS1_REG}, {RS1_VAL}
"""

ASM_FOOTER = """\
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
"""


# Mode vv
def asm_vv(func: str, n_elements: int, lmul: str, width: int, mode="vv") -> str:
    lmul_regs = LMUL_TABLE[lmul]["n_regs"]
    label = f"{func}_{mode}_e{width}_{lmul}_{n_elements}"
    vs2 = f"v{lmul_regs}"
    vs1 = f"v{2 * lmul_regs}"
    vd = "v0"
    vs3 = vd
    asm_str = f"""
  li        t1, {n_elements}
  {label}:
  mv        t0, t1
  vsetvli   t1, t0, e{width}, {lmul}, ta, ma
  vle{width}.v   {vs2},({VS2_DATA_ADDR_REG})
  vle{width}.v   {vs1},({VS1_DATA_ADDR_REG})
  {func}.{mode}   {vd}, {vs2}, {vs1}
  vse{width}.v   {vs3}, (a0)
  sub       t1, t0, t1
  bnez      t1, {label}
"""
    return asm_str


def asm_wvv(func: str, n_elements: int, lmul: str, width: int, mode="vv") -> str:
    lmul_regs = LMUL_TABLE[lmul]["n_regs"]
    label = f"{func}_{mode}_e{width}_{lmul}_{n_elements}"
    vs2 = f"v{lmul_regs}"
    vs1 = f"v{2 * lmul_regs}"
    vd = "v0"
    vs3 = vd
    asm_str = f"""
  li        t1, {n_elements}
  {label}:
  mv        t0, t1
  vsetvli   t1, t0, e{width}, {lmul}, ta, ma
  vle{width}.v   {vs2},({VS2_DATA_ADDR_REG})
  vle{width}.v   {vs1},({VS1_DATA_ADDR_REG})
  {func}.{mode}   {vd}, {vs2}, {vs1}
  vse{width}.v   {vs3}, (a0)
  sub       t1, t0, t1
  bnez      t1, {label}
"""
    return asm_str


def asm_vx(func: str, n_elements: int, lmul: str, width: int, mode="vx") -> str:
    lmul_regs = LMUL_TABLE[lmul]["n_regs"]
    label = f"{func}_vx_e{width}_{lmul}_{n_elements}"
    vs2 = f"v{lmul_regs}"
    rs1 = RS1_REG
    vd = "v0"
    vs3 = vd
    asm_str = f"""
  li        t1, {n_elements}
  {label}:
  mv        t0, t1
  vsetvli   t1, t0, e{width}, {lmul}, ta, ma
  vle{width}.v   {vs2},({VS2_DATA_ADDR_REG})
  {func}.{mode}   {vd}, {vs2}, {rs1}
  vse{width}.v   {vs3}, (a0)
  sub       t1, t0, t1
  bnez      t1, {label}
"""
    return asm_str


MODE_FUNCS = {"vv": asm_vv, "vm": asm_vv, "vx": asm_vx}


def write_test() -> None:
    with open(TEST_PATH, "w", encoding="utf-8") as asm_file:
        asm_file.write(ASM_HEADER)
        for instr_type in INSTR_TYPES:
            mode = instr_type["mode"]
            for func in instr_type["instrs"]:
                if func not in USE_TEST_FUNCS:
                    continue
                for width in instr_type["widths"]:
                    if width not in TEST_CONFIG["widths"]:
                        continue
                    for lmul in instr_type["lmuls"]:
                        if lmul not in TEST_CONFIG["lmuls"]:
                            continue
                        if (
                            lmul.startswith("mf")
                            and lmul not in LEGAL_FRAC_LMULS[width]
                        ):
                            continue

                        for n_elements in TEST_CONFIG["n_elements"]:
                            if mode == "ext":
                                for frac in [2, 4, 8]:
                                    if LMUL_TABLE[lmul]["div"][frac] == "Illegal":
                                        continue
                                    if int(width / frac) < 8:
                                        continue
                                # EXT Instrs
                                continue

                            asm_file.write(
                                f"  {MODE_FUNCS[mode](
                                        func, n_elements, lmul, width, mode
                                    )}\n"
                            )

        asm_file.write(ASM_FOOTER)


def main():
    write_test()


if __name__ == "__main__":
    main()
