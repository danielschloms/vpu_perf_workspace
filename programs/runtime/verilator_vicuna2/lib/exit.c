#include "terminate_benchmark.h"

void _exit(int status) {
  SIG_ADDR = 0xF * (status != 0);
  while (1) {
  }
}