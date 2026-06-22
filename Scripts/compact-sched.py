#!/usr/bin/env python3

import pathlib

group_mapping = {
    "V_vmv_v_i": ["vmv_v_i"],
    "V_vmv_regs": ["vmvr_v"],
    "V_vmv_x_s": ["vmv_x_s"],
    "V_vmv_s_x": ["vmv_s_x"],
    "V_Load": ["vle32_v", "vle16_v", "vle8_v"],
    "V_Load_Registers": ["vl8r_v", "vl16r_v", "l32r_v"],
    "V_Store": ["vse32_u", "vse16_u", "vse8_u"],
    "V_Div_vv": ["vdiv_vv", "vdivu_vv", "vremu_vv", "vrem_vv"],
    "V_Div_vx": ["vdiv_vx", "vdivu_vx", "vremu_vx", "vrem_vx"],
    "V_Ext": [
        "vzext_vf2",
        "vsext_vf2",
        "vzext_vf4",
        "vsext_vf4",
        "vzext_vf8",
        "vsext_vf8",
    ],
    "V_RED_vv": [
        "vcompress_vm",
        "vredsum_vs",
        "vredmaxu_vs",
        "vredmax_vs",
        "vredminu_vs",
        "vredmin_vs",
        "vredand_vs",
        "vredor_vs",
        "vredxor_v",
    ],
    "V_ALU_vv": [
        "vadd_vv",
        "vsub_vv",
        "vadc_vvm",
        "vmadc_vv",
        "vsbc_vvm",
        "vmsbc_vv",
        "vand_vv",
        "vor_vv",
        "vxor_vv",
        "vsll_vv",
        "vsrl_vv",
        "vsra_vv",
        "vmseq_vv",
        "vmsne_vv",
        "vmsltu_vv",
        "vmslt_vv",
        "vmsleu_vv",
        "vmsle_vv",
        "vminu_vv",
        "vmin_vv",
        "vmaxu_vv",
        "vmax_vv",
        "vmerge_vvm",
        "vsaddu_vv",
        "vsadd_vv",
        "vssubu_vv",
        "vssub_vv",
        "vaaddu_vv",
        "vaadd_vv",
        "vasubu_vv",
        "vasub_vv",
        "vsmul_vv",
        "vssrl_vv",
        "vssra_vv",
    ],
    "V_MUL_vv": [
        "vmul_vv",
        "vmulh_vv",
        "vmulhu_vv",
        "vmulhsu_vv",
        "vmacc_vv",
        "vnmsac_vv",
        "vmadd_vv",
        "vnmsub_vv",
    ],
    "V_ALU_Widening_vv": [
        "vwaddu_vv",
        "vwsubu_vv",
        "vwadd_vv",
        "vwsub_vv",
        "vwaddu_w_vv",
        "vwsubu_w_vv",
        "vwadd_w_vv",
        "vwsub_w_vv",
    ],
    "V_MUL_Widening_vv": [
        "vwmul_vv",
        "vwmulu_vv",
        "vwmulsu_vv",
        "vwmaccu_vv",
        "vwmacc_vv",
        "vwmaccsu_vv",
    ],
    "V_ALU_vx": [
        "vadd_vx",
        "vsub_vx",
        "vrsub_vx",
        "vadc_vxm",
        "vmadc_vx",
        "vsbc_vxm",
        "vmsbc_vx",
        "vand_vx",
        "vor_vx",
        "vxor_vx",
        "vsll_vx",
        "vsrl_vx",
        "vsra_vx",
        "vmseq_vx",
        "vmsne_vx",
        "vmsltu_vx",
        "vmslt_vx",
        "vmsleu_vx",
        "vmsle_vx",
        "vmsgtu_vx",
        "vmsgt_vx",
        "vminu_vx",
        "vmin_vx",
        "vmaxu_vx",
        "vmax_vx",
        "vmerge_vxm",
        "vsaddu_vx",
        "vsadd_vx",
        "vssubu_vx",
        "vssub_vx",
        "vaaddu_vx",
        "vaadd_vx",
        "vasubu_vx",
        "vasub_vx",
        "vsmul_vx",
        "vssrl_vx",
        "vssra_vx",
        "vslideup_vx",
        "vslidedown_vx",
        "vslide1up_vx",
        "vslide1down_vx",
    ],
    "V_MUL_vx": [
        "vmul_vx",
        "vmulh_vx",
        "vmulhu_vx",
        "vmulhsu_vx",
        "vmacc_vx",
        "vnmsac_vx",
        "vmadd_vx",
        "vnmsub_vx",
    ],
    "V_ALU_Widening_vx": [
        "vwaddu_vx",
        "vwsubu_vx",
        "vwadd_vx",
        "vwsub_vx",
        "vwaddu_w_vx",
        "vwsubu_w_vx",
        "vwadd_w_vx",
        "vwsub_w_vx",
    ],
    "V_MUL_Widening_vx": [
        "vwmul_vx",
        "vwmulu_vx",
        "vwmulsu_vx",
        "vwmaccu_vx",
        "vwmacc_vx",
        "vwmaccsu_vx",
        "vwmaccus_vx",
    ],
    "V_ALU_vi": [
        "vadd_vi",
        "vrsub_vi",
        "vadc_vim",
        "vmadc_vi",
        "vand_vi",
        "vor_vi",
        "vxor_vi",
        "vsll_vi",
        "vsrl_vi",
        "vsra_vi",
        "vmseq_vi",
        "vmsne_vi",
        "vmsleu_vi",
        "vmsle_vi",
        "vmsgtu_vi",
        "vmsgt_vi",
        "vmerge_vim",
        "vsaddu_vi",
        "vsadd_vi",
        "vssrl_vi",
        "vssra_vi",
        "vslideup_vi",
        "vslidedown_vi",
    ],
}

PROJECT_ROOT = pathlib.Path(__file__).parent.parent
VARIANTS_DIR = (
    PROJECT_ROOT
    / "Perfsim/etiss-perf-sim/etiss_plugins/SoftwareEvalLib/libs/backends/variants"
)
VLENS = [128]


def get_header_cpp(vlen: int):
    return f"""
#include <algorithm>
#include <cstdint>
#include "PerformanceModel.h"
#include "Vicuna_zvl{vlen}b_PerformanceModel.h"

namespace Vicuna_zvl{vlen}b {{
"""

def get_header_cpp_vector(vlen: int):
    zvl = f"Vicuna_zvl{vlen}b"
    return f"""
#include "PerformanceModel.h"
#include "{zvl}_PerformanceModel.h"
#include "{zvl}_GroupSchedulingFunction.hpp"

namespace {zvl} {{
"""


def get_header_hpp(vlen: int):
    return f"""
#include "PerformanceModel.h"

namespace Vicuna_zvl{vlen}b {{
"""


def main():

    extraction_mapping: dict = {
        igroup: insns[0] for igroup, insns in group_mapping.items()
    }

    vicuna_prefix = "Vicuna_zvl"

    for vlen in VLENS:
        zvl = f"{vicuna_prefix}{vlen}b"
        src_dir = VARIANTS_DIR / f"{zvl}/src"
        orig_sched_cpp = src_dir / f"{zvl}_SchedulingFunction.cpp"
        scalar_sched_cpp = src_dir / f"{zvl}_ScalarSchedulingFunction.cpp"
        group_sched_cpp = src_dir / f"{zvl}_GroupSchedulingFunction.cpp"
        group_sched_hpp = src_dir / f"{zvl}_GroupSchedulingFunction.hpp"
        vector_sched_cpp = src_dir / f"{zvl}_VectorSchedulingFunction.cpp"

        with open(orig_sched_cpp, "r", encoding="utf-8") as orig_cpp, open(
            group_sched_cpp, "w", encoding="utf-8"
        ) as group_cpp, open(
            scalar_sched_cpp, "w", encoding="utf-8"
        ) as scalar_cpp, open(
            group_sched_hpp, "w", encoding="utf-8"
        ) as group_hpp, open(
            vector_sched_cpp, "w", encoding="utf-8"
        ) as vector_cpp:
            group_cpp.write(get_header_cpp(vlen))
            group_hpp.write(get_header_hpp(vlen))
            vector_cpp.write(get_header_cpp_vector(vlen))

            active = False
            printout = False
            scalar_copy = True
            vlevel = 0
            level = 0
            current_vinsn = ""
            current_grp = ""
            for i, line in enumerate(orig_cpp):
                # Greedily update vector instruction
                for grp, grp_insns in group_mapping.items():
                    for insn in grp_insns:
                        if f"\"{insn}\"" in line:
                            current_vinsn = insn
                            current_grp = grp

                # Scalar & vector copying
                if "static SchedulingFunction *schedulingFunction_vle32_v" in line:
                    scalar_copy = False
                if "static SchedulingFunction *schedulingFunction__def" in line:
                    scalar_copy = True

                if f"{zvl}_PerformanceModel *perfModel" in line or f"{zvl}_PerformanceModel* perfModel" in line:
                    # Insert call in vector scheduling function
                    if not scalar_copy:
                        vector_cpp.write(f"\t{current_grp}(perfModel_);\n")
                    vector_copy = False
                    vlevel = 1
                
                vlevel += line.count("(")
                vlevel -= line.count(")")

                if vlevel <= 0:
                    vector_copy = True
                    if not scalar_copy and not "}" in line and line.strip():
                        vector_cpp.write("}")


                if scalar_copy:
                    scalar_cpp.write(line)
                elif vector_copy:
                    vector_cpp.write(line)

                # Vector extracting
                if not active:
                    for group, single in extraction_mapping.items():
                        if f'"{single}"' in line:
                            group_cpp.write(
                                f"void {group}(PerformanceModel *perfModel_) {{\n{zvl}_PerformanceModel *perfModel = static_cast<{zvl}_PerformanceModel *>(perfModel_);\n"
                            )
                            group_hpp.write(
                                f"void {group}(PerformanceModel *perfModel_);\n\n"
                            )
                            active = True
                            # print(f"Found Line {i}")
                else:
                    if not printout:
                        if "// Enter" in line:
                            # print(f"Print Line {i}")
                            level = 1
                            printout = True
                    else:
                        level += line.count("{")
                        level -= line.count("}")
                        if level <= 0:
                            # print(f"Done Line {i}")
                            active = False
                            printout = False
                            group_cpp.write("}\n\n")
                            continue
                        group_cpp.write(line)

            group_cpp.write("} // Namespace")
            group_hpp.write("} // Namespace")
            vector_cpp.write("} // Namespace")


if __name__ == "__main__":
    main()
