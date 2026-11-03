project(tflm_aww)

if(VERILATOR)
  add_executable_verilator(${PROJECT_NAME})
elseif(ETISS)
  add_executable_etiss(${PROJECT_NAME})
else()
  add_executable_qemu(${PROJECT_NAME})
endif()

# Needed to run TensorFlow code with RISC-V toolchain

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/aww_data/aww_input_data.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/aww_data/aww_model_data.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/aww_data/aww_model_settings.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/aww_data/aww_output_data_ref.cc
)

target_link_libraries(${PROJECT_NAME} PRIVATE m)

find_package(tflm REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC tflm::tflm)
target_include_directories(${PROJECT_NAME} PRIVATE ${TFLM_INCLUDE_DIRS})

target_compile_definitions(${PROJECT_NAME} PRIVATE
  -DTF_LITE_USE_GLOBAL_MAX
  -DTF_LITE_USE_GLOBAL_MIN
  -DTF_LITE_USE_GLOBAL_CMATH_FUNCTIONS
  -DTF_LITE_STATIC_MEMORY
  -DTF_LITE_STRIP_ERROR_STRINGS
  -DTF_LITE_EMULATE_FLOAT
)

# if(TFLM_EMULATE_FLOAT)
#   target_compile_definitions(${PROJECT_NAME} PRIVATE -DTFLITE_EMULATE_FLOAT)
# endif()
