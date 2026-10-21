/*
 * Board support package for embench-iot running on the Vicuna2 Verilator model.
 *
 * embench-iot (support/main.c) calls initialise_board(), start_trigger(),
 * stop_trigger().  This file is where you implement the Vicuna2-specific pieces.
 *
 * start_trigger()/stop_trigger() bracket the timed region and measure elapsed
 * time with the RISC-V machine cycle counter (mcycle), which the Verilator
 * model provides (also see lib/runtime.cpp: get_mcycle()).
 *
 * Unlike ETISS the Vicuna2 model has no semihosting, so the minimal newlib
 * syscall stubs at the bottom keep things like printf(), exit() and malloc()
 * linking.  The model observes the benchmark result through the MMIO signal
 * address (signal_addr), which the host RTL monitors for pass/fail.
 */

#include <stdint.h>

/* Vicuna2 MMIO (see lib/uart.{hpp,cpp} and lib/terminate_benchmark.h). */
static volatile uint32_t *const uart_data   = (volatile uint32_t *)0x00000400;
static volatile uint32_t *const uart_status = (volatile uint32_t *)0x00000404;
static volatile uint32_t *const signal_addr = (volatile uint32_t *)0x00000408;

/* Cycle counts captured by the start/stop triggers. */
volatile uint64_t g_start_cycles;
volatile uint64_t g_stop_cycles;

static uint64_t
read_mcycle (void)
{
  uint32_t lo, hi0, hi1;

  do
    {
      asm volatile ("csrr %0, mcycleh" : "=r" (hi0));
      asm volatile ("csrr %0, mcycle" : "=r" (lo));
      asm volatile ("csrr %0, mcycleh" : "=r" (hi1));
    }
  while (hi0 != hi1);

  return ((uint64_t)hi1 << 32) | lo;
}

void
initialise_board (void)
{
}

void __attribute__ ((noinline, externally_visible))
start_trigger (void)
{
  g_start_cycles = read_mcycle ();
}

void __attribute__ ((noinline, externally_visible))
stop_trigger (void)
{
  g_stop_cycles = read_mcycle ();
}

/*
 * ---- Minimal newlib syscall stubs -----------------------------------------
 * Vicuna2 has no semihosting, so provide the bare-metal stubs that stdio /
 * malloc / exit need.  Tune or replace these to match the model.
 */

static void
uart_putc_ (char c)
{
  while (*uart_status & 1u)
    ;
  *uart_data = (uint32_t)c;
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
  /* Record the result for the host, then stop. */
  *signal_addr = (uint32_t)code;
  __asm__ volatile ("unimp");
  for (;;)
    ;
}
