/*
// Copyright 2017 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the “License”); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

// This file was modified by the Chair of Electronic Design Automation, TUM
*/

OUTPUT_ARCH(riscv)
ENTRY(_start)
SEARCH_DIR(.)
__DYNAMIC = 0;

MEMORY
{
  BOOT (rx) : ORIGIN = 0x00000000, LENGTH = 0x00002000
  ROM  (rx) : ORIGIN = 0x00100000, LENGTH = 0x00100000
  RAM  (rw) : ORIGIN = 0x00200000, LENGTH = 0x00100000
}

/* minimum sizes for heap and stack. It will be checked that they can fit on the RAM */
__stack_size     = 0x1000;
__heap_size      = 0x1000;


SECTIONS
{

  /* ================ BOOT ================ */
  .vectors 0 : {
      *(.vectors)
  } > BOOT

  /* ================ ROM ================ */

  .text : {
    *(.text .text.* )
  }  > ROM

  .rodata : {
    *(.rodata .rodata.*)
  } > ROM
  .srodata : {
    *(.srodata .srodata.*)
  } > ROM



  /* ================ RAM ================ */

  /* Anchor the location counter to the start of RAM.  The RAM output sections
     (init_array, eh_frame, ...) can be empty for minimal programs, in which case
     GNU ld leaves the counter at the ROM end; that would make __data_start /
     __sdata_start / __global_pointer$ resolve to a ROM address and force the
     linker to relax gp-relative accesses into (absolute) lui+offset sequences.
     Resetting to ORIGIN(RAM) keeps the data base symbols in RAM so the small-
     data (gp-relative) addressing is used consistently. */
  . = ORIGIN(RAM);

  .init_array : {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(.init_array .init_array.*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } > RAM
  .fini_array : {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(.fini_array .fini_array.*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } > RAM

  .gcc_except_table : {
    *(.gcc_except_table .gcc_except_table.*)
  } > RAM

  .eh_frame : {
    KEEP (*(.eh_frame))
  } > RAM

  __data_start = .;
  .data : {
      *(.data .data.*)
  } > RAM
  __sdata_start = .;
  .sdata : {
      *(.sdata .sdata.*)
  } > RAM

  _bss_start = .;
  .sbss : {
      *(.sbss .sbss.*)
  } > RAM
  .bss : {
      *(.bss .bss.*)
  } > RAM
  _bss_end = .;

  /* do not place anything after this address, because the heap starts here! */

  /* point the global pointer so it can access sdata, sbss, data and bss */
  __global_pointer$ = MIN(__sdata_start + 0x800, MAX(__data_start + 0x800, _bss_end - 0x800));

  /* stack pointer starts at the top of the ram */
  _stack = ORIGIN(RAM) + LENGTH(RAM);
  .stack : {
    ASSERT ((_stack > (_bss_end + __heap_size + __stack_size)), "Error: RAM too small for heap and stack");
  } > RAM
}
