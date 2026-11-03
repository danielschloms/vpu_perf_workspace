set(EMBENCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/embench-iot/)

macro(add_embench_program PROGRAM)
	set(SRC_FILES "${ARGN}")


  if (VERILATOR)
    add_executable_verilator(embench_${PROGRAM} ${SRC_FILES})
  elseif (ETISS)
    add_executable_etiss(embench_${PROGRAM} ${SRC_FILES})
  endif()

  target_include_directories(embench_${PROGRAM} PRIVATE
    ${EMBENCH_DIR}/support
  )
  file(GLOB BENCH_FILES ${EMBENCH_DIR}/src/${PROGRAM}/*.c )

  target_sources(embench_${PROGRAM} PRIVATE
    ${BENCH_FILES}
    ${EMBENCH_DIR}/support/main.c
    ${EMBENCH_DIR}/support/beebsc.c
    # ${EMBENCH_DIR}/config/native/boards/default/boardsupport.c
  )

  target_link_libraries(embench_${PROGRAM} PRIVATE m)
  add_dependencies(embench_iot embench_${PROGRAM})
  if (VERILATOR)
    target_compile_definitions(embench_${PROGRAM} PRIVATE LSF_ONE=1 GLOBAL_SCALE_FACTOR=1 WARMUP_HEAT=1 VERILATOR)
  elseif (ETISS)
    target_compile_definitions(embench_${PROGRAM} PRIVATE LSF_ONE=1 GLOBAL_SCALE_FACTOR=1 WARMUP_HEAT=1)
  endif()
endmacro()

if(EXISTS ${EMBENCH_DIR}/src)
  add_embench_program(aha-mont64)
  add_embench_program(edn)
  add_embench_program(md5sum)
  add_embench_program(nsichneu)
  add_embench_program(sglib-combined)
  add_embench_program(tarfind)
  add_embench_program(xgboost)
  add_embench_program(crc32)
  add_embench_program(huffbench)
  add_embench_program(nettle-aes)
  add_embench_program(picojpeg)
  add_embench_program(slre)
  add_embench_program(ud)
  add_embench_program(depthconv)
  add_embench_program(matmult-int)
  add_embench_program(nettle-sha256)
  add_embench_program(qrduino)
  add_embench_program(statemate)
  add_embench_program(wikisort)
else()
  message(WARNING "Skipping embench programs due to missing sources")
endif()
