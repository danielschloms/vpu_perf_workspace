#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define MATCH_BEGIN_DEF                                                        \
  int __attribute__((noinline)) address_match_start() {                        \
    volatile int r = 1;                                                        \
    return r;                                                                  \
  }

#define MATCH_END_DEF                                                          \
  int __attribute__((noinline)) address_match_end() {                          \
    volatile int r = 2;                                                        \
    return r;                                                                  \
  }

#define MATCH_BEGIN volatile int hello = address_match_start()
#define MATCH_END volatile int bye = address_match_end()

#ifdef VERILATOR

#ifdef __cplusplus
// void *__dso_handle = (void *)&__dso_handle;
#endif

static inline void terminate_success() {
  __asm__ volatile(
      "jalr x0, 124(x0)"); // jump to 0x7c to signal success (Custom use
                           // interrupt, will not be called). Jumps to these
                           // addresses are handled by verilator_main.cpp
}

static inline void terminate_failure() {
  __asm__ volatile(
      "jalr x0, 120(x0)"); // jump to 0x78 to signal failure caused by
                           // mismatched test output  Other interrupts are
                           // caught by 0x74 to signal a problem
}

#define EXIT_SIM_SUCCESS                                                       \
  terminate_success();                                                         \
  return hello + bye;

#define EXIT_SIM_FAILURE                                                       \
  terminate_failure();                                                         \
  return hello + bye;

#else
#include <stdio.h>
#define EXIT_SIM_SUCCESS                                                       \
  printf("Success\n");                                                         \
  return hello + bye;

#define EXIT_SIM_FAILURE                                                       \
  printf("Fail\n");                                                            \
  return hello + bye;

#endif

#ifdef __cplusplus
}
#endif