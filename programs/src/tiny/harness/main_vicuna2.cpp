/*
 * Harness entry point for MLPerf Tiny (KWS int8) on the Vicuna2 Verilator model.
 *
 * The Vicuna2 crt0 (crt0.S: "la ra, _start") sends a main() return back to
 * _start, which would clear BSS and re-run forever, so the model would never
 * see the result.  Instead, run the KWS inference once and signal the host
 * through the Vicuna2 MMIO termination address (0x408): write 0x0 for success,
 * 0xF for failure, then spin (never return).
 *
 * The Vicuna2 crt0 does not run the C++ runtime's static constructors (the
 * .init_array section), so we invoke them here before using any C++ objects.
 */

#include <cstdint>

#ifdef __cplusplus
extern "C"
#endif
int run_kws(void);

/* Vicuna2 MMIO termination address (see lib/terminate_benchmark.h). */
static volatile unsigned int *const signal_addr =
    (volatile unsigned int *)0x00000408;

/* C++ static constructors live in .init_array (placed in RAM by link.ld). */
extern "C" {
typedef void (*init_fn_t)(void);
extern init_fn_t __init_array_start[];
extern init_fn_t __init_array_end[];
}

static void run_cxx_constructors(void) {
  init_fn_t *fn = __init_array_start;
  for (; fn != __init_array_end; ++fn) {
    if (*fn) (*fn)();
  }
}

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  run_cxx_constructors();

  const int ok = run_kws();

  /* Signal pass/fail to the host: 0x0 = success, 0xF = failure. */
  *signal_addr = ok == 0 ? 0x0U : 0xFU;

  /* Never return: the caller (crt0) would restart _start. */
  for (;;) {
  }
}
