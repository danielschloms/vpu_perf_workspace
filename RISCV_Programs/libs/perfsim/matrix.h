#pragma once

#include <stdbool.h>
#include <stdint.h>

#define LMUL_M1 0b000
#define LMUL_M2 0b001
#define LMUL_M4 0b010
#define LMUL_M8 0b011

#define SEW_E8 0b000
#define SEW_E16 0b001
#define SEW_E32 0b010
#define SEW_E64 0b011

#define LAMBDA_1 0b001
#define LAMBDA_2 0b010
#define LAMBDA_4 0b011
#define LAMBDA_8 0b100
#define LAMBDA_16 0b101
#define LAMBDA_32 0b110
#define LAMBDA_64 0b111

#define CSR_VLENB 0xC22

#define V0 "00000"
#define V1 "00001"
#define V2 "00010"
#define V3 "00011"
#define V4 "00100"
#define V5 "00101"
#define V6 "00110"
#define V7 "00111"
#define V8 "01000"
#define V9 "01001"
#define V10 "01010"
#define V11 "01011"
#define V12 "01100"
#define V13 "01101"
#define V14 "01110"
#define V15 "01111"
#define V16 "10000"
#define V17 "10001"
#define V18 "10010"
#define V19 "10011"
#define V20 "10100"
#define V21 "10101"
#define V22 "10110"
#define V23 "10111"
#define V24 "11000"
#define V25 "11001"
#define V26 "11010"
#define V27 "11011"
#define V28 "11100"
#define V29 "11101"
#define V30 "11110"
#define V31 "11111"

#define MMACC_INSTR_R(vd, vs1, vs2)                                            \
  asm volatile(".word 0b1110001" vs2 vs1 "000" vd "1010111")