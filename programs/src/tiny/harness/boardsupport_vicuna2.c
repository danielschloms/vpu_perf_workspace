/*
 * Board support package for the MLPerf Tiny KWS harness on the Vicuna2
 * Verilator model.
 *
 * The Vicuna2 model has no semihosting, so newlib's libc needs bare-metal
 * syscall stubs (write/read/... and the heap brk).  The runtime libs
 * (UART_Vicuna) provide uart_putc/uart_printf via MMIO.  The benchmark result
 * is observed by the host RTL through the 0x408 MMIO signal written by main().
 */

#include <stdint.h>

/* newlib defines _reent in <reent.h>; forward-declare it to keep the malloc
 * lock prototypes below self-contained. */
struct _reent;

/* Vicuna2 MMIO (see lib/uart.{hpp,cpp} and lib/terminate_benchmark.h). */
static volatile uint32_t *const uart_data   = (volatile uint32_t *)0x00000400;
static volatile uint32_t *const uart_status = (volatile uint32_t *)0x00000404;
static volatile uint32_t *const signal_addr = (volatile uint32_t *)0x00000408;

static void
uart_putc_ (char c)
{
  while (*uart_status & 1u)
    ;
  *uart_data = (uint32_t)c;
}

/* Low-level single-character output hook required by the eyalroz printf that
 * tflite-micro's error reporting links in (tensorflow/lite/micro/tools/make/
 * downloads/eyalroz_printf).  The runtime itself prints via uart_printf, but a
 * stray reference to printf_/putchar_ from the tflite archive must be satisfied. */
void
putchar_ (char c)
{
  uart_putc_ (c);
}

int
_write (int fd, const char *buf, int len)
{
  (void)fd;
  for (int i = 0; i < len; ++i)
    uart_putc_ (buf[i]);
  return len;
}

int
_read (int fd, char *buf, int len)
{
  (void)fd;
  (void)buf;
  (void)len;
  return -1;
}

int
_close (int fd)
{
  (void)fd;
  return -1;
}

int
_lseek (int fd, int off, int whence)
{
  (void)fd;
  (void)off;
  (void)whence;
  return -1;
}

int
_fstat (int fd, void *st)
{
  (void)fd;
  (void)st;
  return -1;
}

int
_isatty (int fd)
{
  (void)fd;
  return 1;
}

extern char _bss_end;

void *
_sbrk (int incr)
{
  static char *heap = &_bss_end;
  char *prev = heap;
  heap += incr;
  return prev;
}

void
_exit (int code)
{
  /* Record the result for the host, then stop.  Map any failure to 0xF. */
  *signal_addr = code ? 0xFU : 0x0U;
  __asm__ volatile ("unimp");
  for (;;)
    ;
}

/* newlib reentrant malloc/free locks (single-threaded: no-ops). */
void
__malloc_lock (struct _reent *r)
{
  (void)r;
}

void
__malloc_unlock (struct _reent *r)
{
  (void)r;
}
