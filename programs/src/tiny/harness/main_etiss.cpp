/*
 * MLPerf Tiny (e.g. KWS/IC/AD) harness entry point for ETISS.
 *
 * The ETISS crt0 (programs/runtime/etiss/crt0.S) runs the C++ runtime's static
 * initializers (__libc_init_array), then calls main() and finally jumps to
 * exit(main_ret), which reaches the semihosting SYS_EXIT_EXTENDED (sh_exit.c).
 * Returning 0 from main() therefore reports a passing run to the ETISS host.
 *
 * The benchmark under test is selected at build time through the RUNNER_FN
 * macro (the C symbol returning 0 on success): run_kws / run_ic / run_ad.
 */
#ifndef RUNNER_FN
#define RUNNER_FN run_kws
#endif

#ifdef __cplusplus
extern "C"
#endif
int RUNNER_FN(void);

int main(void) {
  return RUNNER_FN() == 0 ? 0 : 1;
}
