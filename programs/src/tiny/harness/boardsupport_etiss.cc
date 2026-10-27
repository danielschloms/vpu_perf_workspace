/*
 * Board support for the MLPerf Tiny KWS harness under ETISS.
 *
 * ETISS runs the firmware through semihosting, so the libc syscall stubs
 * (_write, _read, _sbrk, _exit, ...) come from the toolchain's libsemihost +
 * etiss_crt0 (see programs/runtime/etiss) -- nothing extra is needed here.
 *
 * tflite-micro's error reporting pulls in the eyalroz printf (printf_, etc.),
 * which references a low-level putchar_() hook.  We satisfy it by forwarding
 * each character to newlib's write() -> _write() (semihosting stdout).
 */

#include <stdint.h>
#include <unistd.h>

extern "C" void putchar_(char c) {
  char ch = c;
  (void)::write(STDOUT_FILENO, &ch, 1);
}
