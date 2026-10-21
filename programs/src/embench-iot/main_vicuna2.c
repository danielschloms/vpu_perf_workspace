/*
 * Harness entry point for embench-iot on the Vicuna2 Verilator model.
 *
 * embench-iot's generic support/main.c returns from main().  The Vicuna2 crt0
 * (crt0.S: "la ra, _start") sends that return back to _start, which would
 * clear BSS and re-run the benchmark forever, so the model would never see the
 * result.  Instead, run the benchmark once and signal the host through the
 * Vicuna2 MMIO termination address (0x408): write 0x0 for success, 0xF for
 * failure, then spin (never return).
 */

#include "support.h"

/* Vicuna2 MMIO termination address (see lib/terminate_benchmark.h). */
static volatile unsigned int *const signal_addr =
    (volatile unsigned int *)0x00000408;

int
main (int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  volatile int result;
  int correct;

  initialise_board ();
  initialise_benchmark ();
  warm_caches (WARMUP_HEAT);

  start_trigger ();
  result = benchmark ();
  stop_trigger ();

  /* benchmarks that use arrays check a global array rather than int result */
  correct = verify_benchmark (result);

  /* Signal pass/fail to the host: 0x0 = success, 0xF = failure. */
  *signal_addr = correct ? 0x0U : 0xFU;

  /* Never return: the caller (crt0) would restart _start. */
  for (;;)
    ;
}
