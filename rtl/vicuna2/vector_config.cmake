###
# System configuration. This file is imported by the top-level CMakeLists.txt.
#
# All parameters may be overridden on the CMake command line, e.g.
#   cmake -S . -B build/cv32a60x/rv32im_zve32x_zvl128_vl32 \
#         -DSCALAR_CORE=cv32a60x -DRISCV_ARCH=rv32im_zve32x \
#         -DVREG_W=128 -DVLANE_W=32
#
# The build directory layout is:
#   build/<scalar_core>/<riscv_arch>_zvl<vlen>_vl<lane_width>
# where <vlen> is VREG_W and <lane_width> is VLANE_W.
###

# Scalar core to instantiate the vector unit with.
# Currently supported: cv32e40x, cv32a60x
set(SCALAR_CORE "cv32a60x" CACHE STRING "Scalar core: cv32e40x | cv32a60x")

# RISC-V architecture / extension configuration.
# Currently supported: rv32im, rv32im_zve32x, rv32imf, rv32imf_zfh,
#   rv32imf_zve32f, rv32imf_zve32x, rv32imf_zfh_zve32f_zvfh,
#   rv32im_zve32x_zvbb, rv32im_zve32x_zvbc, rv32im_zve32x_zvbb_zvbc
set(RISCV_ARCH "rv32im_zve32x" CACHE STRING "RISC-V architecture configuration")

# Vector register width (VLEN) in bits.
set(VREG_W "128" CACHE STRING "Vector register width (VLEN) in bits")

# Vector lane (functional-unit pipeline) width in bits.
set(VLANE_W "32" CACHE STRING "Vector lane width in bits")

# Vector memory interface parameters.
set(VMEM_W "32" CACHE STRING "Vector memory interface width in bits")
set(VMEM_PORTS "1" CACHE STRING "Number of vector memory ports")

math(EXPR VMEM_TOTAL_W "${VMEM_PORTS} * ${VMEM_W}")

set(VPROC_PIPELINES "${VMEM_TOTAL_W}:VLSU ${VLANE_W}:VALU,VMUL,VSLD,VXRESULT,VDIV,VREDSUM,VREDMINMAX,VINDEX,VELEM,VGATHER")
