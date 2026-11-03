#include <stdint.h>
#include <stdio.h>

#define N_ITERATIONS 1000000000

int main() {
  volatile uint64_t cnt = 0;

  for (uint64_t i = 0; i < N_ITERATIONS; i++) {
    cnt += 2;
  }

  printf("%llu\n", cnt);
  return 0;
}