if(VERILATOR)
    add_executable_verilator(load_alu_vv_store load_alu_vv_store.S)
    add_executable_verilator(load_mul_vv_store load_mul_vv_store.S)
    add_executable_verilator(load_div_vv_store load_div_vv_store.S)
    add_executable_verilator(load_red_store load_red_store.S)
    add_executable_verilator(load_store load_store.S)
    add_executable_verilator(vmv_v_i_store vmv_v_i_store.S)
    add_executable_verilator(vmv_red_vmv vmv_red_vmv.S)

    add_executable_verilator(basic_asm basic_asm.S)
    add_executable_verilator(tests tests.S)
    add_executable_verilator(loadstores loadstores.S)
    add_executable_verilator(store_unpack_interleave store_unpack_interleave.S)
    add_executable_verilator(alu_vv alu_vv.S)
    add_executable_verilator(load_alu_vx_store load_alu_vx_store.S)
    add_executable_verilator(load_macc_vv_store load_macc_vv_store.S)

    add_executable_verilator(addloop addloop.c)
    add_executable_verilator(longloop longloop.c)

    add_executable_verilator(thesis_addstore thesis_addstore.S)
    add_executable_verilator(thesis_divstore thesis_divstore.S)
    add_executable_verilator(thesis_divstore_error thesis_divstore_error.S)
    add_executable_verilator(crit_toy crit_toy.S)

    add_dependencies(sanitycheck
        load_alu_vv_store
        load_mul_vv_store
        load_div_vv_store
        load_red_store
        load_store
        vmv_v_i_store
        vmv_red_vmv
    )

elseif(ETISS)
    add_executable_etiss(load_alu_vv_store load_alu_vv_store.S)
    add_executable_etiss(load_mul_vv_store load_mul_vv_store.S)
    add_executable_etiss(load_div_vv_store load_div_vv_store.S)
    add_executable_etiss(load_red_store load_red_store.S)
    add_executable_etiss(load_store load_store.S)
    add_executable_etiss(vmv_v_i_store vmv_v_i_store.S)
    add_executable_etiss(vmv_red_vmv vmv_red_vmv.S)

    add_executable_etiss(basic_asm basic_asm.S)
    add_executable_etiss(tests tests.S)
    add_executable_etiss(loadstores loadstores.S)
    add_executable_etiss(store_unpack_interleave store_unpack_interleave.S)
    add_executable_etiss(alu_vv alu_vv.S)
    add_executable_etiss(load_alu_vx_store load_alu_vx_store.S)
    add_executable_etiss(load_macc_vv_store load_macc_vv_store.S)
    add_executable_etiss(addloop addloop.c)
    add_executable_etiss(matrix matrix.c)
    add_executable_etiss(longloop longloop.c)

    add_executable_etiss(thesis_addstore thesis_addstore.S)
    add_executable_etiss(thesis_divstore thesis_divstore.S)
    add_executable_etiss(thesis_divstore_error thesis_divstore_error.S)
    add_executable_etiss(crit_toy crit_toy.S)

    add_dependencies(sanitycheck
        load_alu_vv_store
        load_mul_vv_store
        load_div_vv_store
        load_red_store
        load_store
        vmv_v_i_store
        vmv_red_vmv
    )

else()
    add_executable_qemu(load_alu_vv_store load_alu_vv_store.S)
    add_executable_qemu(load_mul_vv_store load_mul_vv_store.S)
    add_executable_qemu(load_div_vv_store load_div_vv_store.S)
    add_executable_qemu(load_red_store load_red_store.S)
    add_executable_qemu(load_store load_store.S)
    add_executable_qemu(vmv_v_i_store vmv_v_i_store.S)
    add_executable_qemu(vmv_red_vmv vmv_red_vmv.S)

    add_executable_qemu(basic_asm basic_asm.S)
    add_executable_qemu(tests tests.S)
    add_executable_qemu(loadstores loadstores.S)
    add_executable_qemu(store_unpack_interleave store_unpack_interleave.S)
    add_executable_qemu(alu_vv alu_vv.S)
    add_executable_qemu(load_alu_vx_store load_alu_vx_store.S)
    add_executable_qemu(load_macc_vv_store load_macc_vv_store.S)
    add_executable_qemu(addloop addloop.c)
    add_executable_qemu(longloop longloop.c)

    add_dependencies(sanitycheck
        load_alu_vv_store
        load_mul_vv_store
        load_div_vv_store
        load_red_store
        load_store
        vmv_v_i_store
        vmv_red_vmv
    )
endif()

