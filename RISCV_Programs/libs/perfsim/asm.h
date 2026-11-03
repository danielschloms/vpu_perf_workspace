#pragma once

/* Verilator simulation uses a different mechanism for "returning" */
#ifdef VERILATOR
#define RET_INSTR jalr x0, 124(x0)
#else
#define RET_INSTR jr ra
#endif

/* Start-, and end label for address matching */
#define MATCH_START address_match_start:

#define MATCH_END address_match_end:

/* Macros for generating memory */
#define MEM_WORDS_1 .word 0x12345678

#define MEM_WORDS_2                                                            \
  MEM_WORDS_1;                                                                 \
  MEM_WORDS_1;

#define MEM_WORDS_4                                                            \
  MEM_WORDS_2;                                                                 \
  MEM_WORDS_2;

#define MEM_WORDS_8                                                            \
  MEM_WORDS_4;                                                                 \
  MEM_WORDS_4;

#define MEM_WORDS_16                                                           \
  MEM_WORDS_8;                                                                 \
  MEM_WORDS_8;

#define MEM_WORDS_32                                                           \
  MEM_WORDS_16;                                                                \
  MEM_WORDS_16;

#define MEM_WORDS_64                                                           \
  MEM_WORDS_32;                                                                \
  MEM_WORDS_32;

#define MEM_WORDS_128                                                          \
  MEM_WORDS_64;                                                                \
  MEM_WORDS_64;

#define MEM_WORDS_256                                                          \
  MEM_WORDS_128;                                                               \
  MEM_WORDS_128;

/* Macros for generating NOPs */
#define NOP_1 nop

#define NOP_2                                                                  \
  NOP_1;                                                                       \
  NOP_1;

#define NOP_4                                                                  \
  NOP_2;                                                                       \
  NOP_2;

#define NOP_8                                                                  \
  NOP_4;                                                                       \
  NOP_4;

#define NOP_16                                                                 \
  NOP_8;                                                                       \
  NOP_8;

#define NOP_32                                                                 \
  NOP_16;                                                                      \
  NOP_16;

#define NOP_64                                                                 \
  NOP_32;                                                                      \
  NOP_32;

#define NOP_128                                                                \
  NOP_64;                                                                      \
  NOP_64;

#define NOP_256                                                                \
  NOP_128;                                                                     \
  NOP_128;

#define NOP_512                                                                \
  NOP_256;                                                                     \
  NOP_256;

#define NOP_1024                                                               \
  NOP_512;                                                                     \
  NOP_512;

#define NOP_2048                                                               \
  NOP_1024;                                                                    \
  NOP_1024;

#define NOP_4096                                                               \
  NOP_2048;                                                                    \
  NOP_2048;
