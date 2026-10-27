/*
 * Board support package for embench-iot running under ETISS.
 *
 * embench-iot (support/main.c) calls initialise_board(), start_trigger(),
 * stop_trigger() and warm_caches() (the latter is provided per-benchmark).
 * This file is where you implement the ETISS-specific pieces.
 *
 * start_trigger() / stop_trigger() bracket the timed region.  On ETISS we
 * measure elapsed time with the RISC-V `cycle`/`cycleh` CSRs (see csr.h).
 * Linkage is done via semihosting (see the etiss-semihost.specs specs file),
 * so the usual libc syscalls (write, exit, ...) are provided by the toolchain
 * libsemihost library.
 */

#include <stdint.h>

#include "csr.h"

void __attribute__((noinline)) address_match_start() { volatile int a = 1; }
void __attribute__((noinline)) address_match_end() { volatile int a = 1; }

void initialise_board(void) {
  /* ETISS needs no board initialisation before main(). */
}

void __attribute__((noinline, externally_visible)) start_trigger(void) {
  address_match_start();
}

void __attribute__((noinline, externally_visible)) stop_trigger(void) {
  address_match_end();
}
