if(VERILATOR)
    add_executable_verilator(rvv_asm_bench rvv_asm_bench.S)
else()
    add_executable_etiss(rvv_asm_bench rvv_asm_bench.S)
endif()

add_dependencies(simple_bench rvv_asm_bench)