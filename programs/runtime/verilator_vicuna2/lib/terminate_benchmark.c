#include "terminate_benchmark.h"

void benchmark_success()
{
    *signal_addr = 0x0; //Write 0x0 to signal success
}

void benchmark_failure()
{
    *signal_addr = 0xF; //Write 0xF to signal failure
}
