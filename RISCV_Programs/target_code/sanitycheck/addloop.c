#define N_ITERATIONS 1000000000
#include <riscv_vector.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void __attribute__((noinline)) fail() {
  printf("fail\n");
  exit(0);
}

void __attribute__((noinline)) success() {
  printf("success\n");
  exit(0);
}

int main() {
  asm volatile("li t0, 128");
  asm volatile("vsetvli zero,t0,e8,m1,ta,ma");
  asm volatile("vmv.v.i	v8, 1");
  asm volatile("vmv.v.i	v16, 2");
  for (size_t i = 0; i < N_ITERATIONS; ++i) {
    asm volatile("vadd.vv v0, v8, v16");
    // volatile vint8m1_t va;
    // volatile vint8m1_t vb;
    // volatile vint8m1_t vc = __riscv_vadd_vv_i8m1(va, vb, 128);
  }

  asm volatile("vmv.x.s	t1, v0");
  asm volatile("li t2, 3");
  asm volatile("bne t2, t1, fail");
  success();

  return 0;
}