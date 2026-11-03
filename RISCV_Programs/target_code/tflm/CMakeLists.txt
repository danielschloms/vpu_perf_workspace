set(TFLM_EMULATE_FLOAT ON CACHE BOOL "Emulate floating point instructions")

if(SCALAR_FLOAT)
    set(TFLM_EMULATE_FLOAT OFF)
endif()

add_subdirectory(toy)
add_subdirectory(aww)
add_subdirectory(vww)
# add_subdirectory(ic)

add_dependencies(ml_bench
    tflm_toy
    tflm_aww
    tflm_vww
)

# IF(MURISCVNN)
#   if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/muriscv-nn)
#     add_subdirectory(toy_muriscvnn)
#     add_subdirectory(aww_muriscvnn)
#     add_subdirectory(vww_muriscvnn)
#     add_subdirectory(ic_muriscvnn)
#   else()
#     message(WARNING "Skipping muriscvnn programs due to missing sources")
#   endif()
# ENDIF(MURISCVNN)
