cmake_minimum_required(VERSION 3.10)

project(bsp_Vicuna C CXX ASM)

set(VICUNA_LINKER "${CMAKE_CURRENT_SOURCE_DIR}/link.ld" CACHE STRING "The Vicuna linker")
set(VICUNA_CRT_LIB ${CMAKE_CURRENT_BINARY_DIR} CACHE STRING "The Vicuna crt0 library search path")

add_library(${PROJECT_NAME} STATIC 
  crt0.S
  # fixes.c
  # trap_handler.c
  lib/exit.c
)

target_link_options(${PROJECT_NAME} PRIVATE "-T${VICUNA_LINKER}")


add_library(UART_Vicuna STATIC)

target_include_directories(UART_Vicuna PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

target_sources(UART_Vicuna PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/uart.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/uart.cpp
)

