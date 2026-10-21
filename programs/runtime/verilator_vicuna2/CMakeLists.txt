
####
#Add bsp library for Vicuna
####
add_library(bsp_Vicuna STATIC)

target_include_directories(bsp_Vicuna PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(bsp_Vicuna PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/crt0.S
)


add_library(UART_Vicuna STATIC)

target_include_directories(UART_Vicuna PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

target_sources(UART_Vicuna PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/uart.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/uart.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/vicuna_crt.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/vicuna_crt.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/terminate_benchmark.h
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/terminate_benchmark.c
)
