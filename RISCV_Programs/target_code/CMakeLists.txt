macro(add_executable_etiss TARGET)
    set(SRC_FILES "${ARGN}")

    add_executable(${TARGET} ${SRC_FILES})
    add_dependencies(${TARGET} etiss_crt0)
    target_link_libraries(${TARGET} PRIVATE etiss_crt0)
    target_include_directories(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/riscv_crt0 ${LIBS_DIR})

    configure_file(${ETISS_ELFINI} ${TARGET}.ini @ONLY)

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}.ini DESTINATION ini OPTIONAL)
    install(TARGETS ${TARGET} DESTINATION bin OPTIONAL)
endmacro()

macro(add_executable_qemu TARGET)
    set(SRC_FILES "${ARGN}")

    add_executable(${TARGET} ${SRC_FILES})
    target_include_directories(${TARGET} PRIVATE ${LIBS_DIR})

    install(TARGETS ${TARGET} DESTINATION bin OPTIONAL)
endmacro()

macro(add_executable_verilator TARGET)
    set(SRC_FILES "${ARGN}")

    add_executable(${TARGET} ${SRC_FILES})
    add_dependencies(${TARGET} bsp_Vicuna)
    target_compile_definitions(${TARGET} PRIVATE VERILATOR)
	target_link_options(${TARGET} PRIVATE "-nostartfiles")
    target_link_libraries(${TARGET} PRIVATE bsp_Vicuna UART_Vicuna)
    target_include_directories(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/verilator_bsp/lib ${LIBS_DIR})
	set(DUMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/dump")
	set(PROG_DIR "${CMAKE_CURRENT_BINARY_DIR}/prog")
	set(PROG_FILE "${PROG_DIR}/prog_${TARGET}.txt")

    add_custom_command(TARGET ${TARGET}
        POST_BUILD
		COMMAND mkdir -p ${DUMP_DIR}
		COMMAND mkdir -p ${PROG_DIR}
        COMMAND ${CMAKE_OBJCOPY} -O binary ${TARGET} ${TARGET}.bin
        COMMAND srec_cat ${TARGET}.bin -binary -offset 0x0000 -byte-swap 4 -o ${TARGET}.vmem -vmem
        COMMAND rm -f ${PROG_FILE}
        COMMAND echo -n "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}.vmem ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}_unused.txt " > ${PROG_FILE}
        COMMAND readelf -s ${TARGET} | sed '2,13 s/ //1' | grep vref_start | cut -d " " -f 6 | tr [=["\n"]=] " " >> ${PROG_FILE}
        COMMAND readelf -s ${TARGET} | sed '2,13 s/ //1' | grep vref_end | cut -d " " -f 6 | tr [=["\n"]=] " " >> ${PROG_FILE}
        COMMAND echo -n "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}_vicuna_sim_out.txt " >> ${PROG_FILE}
        COMMAND readelf -s ${TARGET} | sed '2,13 s/ //1' | grep vdata_start | cut -d " " -f 6 | tr [=["\n"]=] " " >> ${PROG_FILE}
        COMMAND readelf -s ${TARGET} | sed '2,13 s/ //1' | grep vdata_end | cut -d " " -f 6 | tr [=["\n"]=] " " >> ${PROG_FILE}
        COMMAND ${CMAKE_OBJDUMP} -D ${TARGET} > ${DUMP_DIR}/${TARGET}_dump.txt
    )
endmacro()

option(EMBENCH "EMBENCH" ON)
option(MURISCVNN "MURISCVNN" ON)
option(TVM "MURISCVNN" ON)
option(TFLM "MURISCVNN" ON)

# add_subdirectory(hello_world)
# add_subdirectory(test_cases)
# add_subdirectory(interactive)
# add_subdirectory(semihosting_cpp)
# add_subdirectory(cpp)
# add_subdirectory(c)
# add_subdirectory(dhry)
# if(TVM)
#   add_subdirectory(tvm)
# endif()
add_custom_target(ml_bench)
add_custom_target(sanitycheck)
add_custom_target(simple_bench)

add_subdirectory(sanitycheck)
add_subdirectory(simple_bench)
if(TFLM)
    add_subdirectory(tflm)
endif()

add_custom_target(thesis_results)
add_dependencies(thesis_results
    sanitycheck
    ml_bench
)

add_custom_target(embench_iot)

if(EMBENCH)
  add_subdirectory(embench)
endif()
