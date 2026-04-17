## Matrix Extensions

### Introduction
The RISC-V specification including matrix extensions can be found under [the releases page for the related GitHub repository](https://github.com/riscv/integrated-matrix-extension/releases/).

Apart from relevant load/store and transposition instructions, the matrix extensions `Zvvmm`, `Zvvfmm`, `Zvvmtls`, and `Zvvmttls`
provide variations of the matrix multiply-accumulate.
```
C := C + A * transpose(B)
```

The multiplication- and tile geometry is defined by:
+ Lambda(`λ`), encoded in `vtype`
+ Widening(`W`), encoded in the instruction
+ Vector parameters `LMUL`, `SEW`, and `VLEN`

New `vtype` fields:
+ `lambda[2:0]` at `vtype[XLEN-2:XLEN-4]` is the selected Lambda
+ `altfmt_A` at `vtype[XLEN-5]` is the Alternate Format for input A
+ `altfmt_B` at `vtype[XLEN-6]` is the Alternate Format for input B
+ `bs` at `vtype[XLEN-7]` is the Block Size selector for microscaling

### Lambda λ
Defines the shared multiplication dimension `K` together with `W` and `LMUL`, meaning a result element is the sum of `K` multiplications, with
```
K_eff = λ * W * LMUL
```


### Widening W (Sub-dot-products)
For widening instructions (W = 2 or W = 4), the W narrow input-element pairs packed within one
accumulator-width (SEW-bit) position form a natural computational unit called a *sub-dot-product*.
The W multiplications of (SEW / W)-bit elements are performed and their products summed.

### Zvvmm: Extension for matrix multiplication on vector registers interpreted as 2D integer matrix tiles
+ `vmmacc.vv vd, vs1, vs2` 