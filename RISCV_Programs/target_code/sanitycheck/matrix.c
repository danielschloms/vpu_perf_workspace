#include <riscv_vector.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "perfsim/matrix.h"

uint32_t matrix_vsetvl_32(unsigned lmul, unsigned sew, unsigned lambda,
                          bool altfmt_A, bool altfmt_B, bool bs, unsigned avl) {
  bool vill = (lmul >= 0b100) || (sew >> 2) || (!lambda);
  uint32_t vtype = (vill << 31) | (sew << 3) | (lmul) | (lambda << 28) |
                   (altfmt_A << 27) | (altfmt_B << 26) | (bs << 25);
  // printf("SET VTYPE %x\n", vtype);
  // printf("SET LAMBDA %x\n", vtype >> 28);
  uint32_t vl = 0;
  asm volatile("vsetvl %[rd], %[rs1], %[rs2]"
               : [rd] "=r"(vl)
               : [rs1] "r"(avl), [rs2] "r"(vtype));
  return vl;
}

void __attribute__((noinline)) fail() {
  printf("fail\n");
  exit(0);
}

void __attribute__((noinline)) success() {
  printf("success\n");
  exit(0);
}

int mmacc() {
  unsigned vlenb = 0;
  asm volatile("csrr %0, %1"
               : "=r"(vlenb)
               : "n"(CSR_VLENB)
               : /* clobbers: none */);

  // printf("VLENB %u, VLEN %u\n", vlenb, vlenb << 3);
  matrix_vsetvl_32(LMUL_M1, SEW_E8, LAMBDA_1, false, false, false, 16);
  asm volatile("vid.v v0");
  asm volatile("vid.v v8");

  // vuint8m1_t resi;
  // asm volatile("vmv.v.v %[vres], v8" : [vres] "=vr"(resi));
  // uint8_t buff[8];
  // __riscv_vse8_v_u8m1(buff, resi, 8);
  // for (size_t col = 0; col < 8; ++col) {
  //   printf("hi\n");
  //   printf("%u | ", buff[col]);
  // }

  // MMACC_INSTR;
  MMACC_INSTR_R(V16, V0, V8);

  matrix_vsetvl_32(LMUL_M8, SEW_E8, LAMBDA_1, false, false, false, 128);

  // vuint8m8_t result_1;
  // vuint8m8_t result_2;
  // asm volatile("vmv.v.v %[vres], v16" : [vres] "=vr"(result_1));
  // asm volatile("vmv.v.v %[vres], v16" : [vres] "=vr"(result_1));
  uint8_t buffer[128];
  uint8_t buffer2[128];
  // __riscv_vse8_v_u8m8(buffer, result_1, 128);
  asm volatile("vse8.v v16, (%[rs1])" ::[rs1] "r"(buffer));
  asm volatile("vse8.v v24, (%[rs1])" ::[rs1] "r"(buffer2));

  for (int i = 0; i < 16; i++) {
    // printf("i %i\n", i);
    for (int j = 0; j < 8; j++) {
      printf("%3u | ", buffer[j * 16 + i]);
    }
    for (int j = 0; j < 8; j++) {
      // printf("ai\n");
      printf("%3u | ", buffer2[j * 16 + i]);
    }
    printf("\n");
  }
  return 0;
}

int main() {
  size_t const N_TIMES = 3;
  volatile int r;
  for (size_t i = 0; i < N_TIMES; ++i) {
    printf("RUN %lu\n", i + 1);
    mmacc();
  }
  success();
  return r;
}
