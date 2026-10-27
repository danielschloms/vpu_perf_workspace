/*
 * MLPerf Tiny (KWS int8) harness entry point for ETISS.
 *
 * The ETISS crt0 (programs/runtime/etiss/crt0.S) runs the C++ runtime's static
 * initializers (__libc_init_array), then calls main() and finally jumps to
 * exit(main_ret), which reaches the semihosting SYS_EXIT_EXTENDED (sh_exit.c).
 * Returning 0 from main() therefore reports a passing run to the ETISS host.
 */
#ifdef __cplusplus
extern "C"
#endif
int run_kws(void);

int main(void) {
  return run_kws() == 0 ? 0 : 1;
}
