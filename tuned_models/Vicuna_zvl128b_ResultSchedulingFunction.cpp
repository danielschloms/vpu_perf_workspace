/*
* Copyright 2026 Chair of EDA, Technical University of Munich
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*	 http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/********************* AUTO GENERATE FILE (create by M2-ISA-R-Perf) *********************/


#include <algorithm>
#include <cstdint>

#include "PerformanceModel.h"

#include "Vicuna_zvl128b_PerformanceModel.h"

#include "Vicuna_zvl128b_GroupSchedulingFunction.hpp"

namespace Vicuna_zvl128b{

SchedulingFunctionSet* Vicuna_zvl128b_SchedulingFunctionSet = new SchedulingFunctionSet("Vicuna_zvl128b_SchedulingFunctionSet");

static SchedulingFunction *schedulingFunction_add = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "add",
  0,
  [](PerformanceModel* perfModel_){
	Arith_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_sub = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "sub",
  1,
  [](PerformanceModel* perfModel_){
	Arith_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_xor = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "xor",
  2,
  [](PerformanceModel* perfModel_){
	Arith_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_or = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "or",
  3,
  [](PerformanceModel* perfModel_){
	Arith_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_and = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "and",
  4,
  [](PerformanceModel* perfModel_){
	Arith_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_slt = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "slt",
  5,
  [](PerformanceModel* perfModel_){
	Arith_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_sltu = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "sltu",
  6,
  [](PerformanceModel* perfModel_){
	Arith_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_sll = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "sll",
  7,
  [](PerformanceModel* perfModel_){
	Arith_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_srl = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "srl",
  8,
  [](PerformanceModel* perfModel_){
	Arith_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_sra = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "sra",
  9,
  [](PerformanceModel* perfModel_){
	Arith_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_addi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "addi",
  10,
  [](PerformanceModel* perfModel_){
	Arith_Ra(perfModel_);
});

static SchedulingFunction *schedulingFunction_xori = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "xori",
  11,
  [](PerformanceModel* perfModel_){
	Arith_Ra(perfModel_);
});

static SchedulingFunction *schedulingFunction_ori = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "ori",
  12,
  [](PerformanceModel* perfModel_){
	Arith_Ra(perfModel_);
});

static SchedulingFunction *schedulingFunction_andi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "andi",
  13,
  [](PerformanceModel* perfModel_){
	Arith_Ra(perfModel_);
});

static SchedulingFunction *schedulingFunction_slti = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "slti",
  14,
  [](PerformanceModel* perfModel_){
	Arith_Ra(perfModel_);
});

static SchedulingFunction *schedulingFunction_sltiu = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "sltiu",
  15,
  [](PerformanceModel* perfModel_){
	Arith_Ra(perfModel_);
});

static SchedulingFunction *schedulingFunction_slli = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "slli",
  16,
  [](PerformanceModel* perfModel_){
	Arith_Ra(perfModel_);
});

static SchedulingFunction *schedulingFunction_srli = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "srli",
  17,
  [](PerformanceModel* perfModel_){
	Arith_Ra(perfModel_);
});

static SchedulingFunction *schedulingFunction_srai = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "srai",
  18,
  [](PerformanceModel* perfModel_){
	Arith_Ra(perfModel_);
});

static SchedulingFunction *schedulingFunction_auipc = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "auipc",
  19,
  [](PerformanceModel* perfModel_){
	Arith_X(perfModel_);
});

static SchedulingFunction *schedulingFunction_lui = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "lui",
  20,
  [](PerformanceModel* perfModel_){
	Arith_X(perfModel_);
});

static SchedulingFunction *schedulingFunction_mul = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "mul",
  21,
  [](PerformanceModel* perfModel_){
	Mul_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_mulh = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "mulh",
  22,
  [](PerformanceModel* perfModel_){
	MulH_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_mulhu = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "mulhu",
  23,
  [](PerformanceModel* perfModel_){
	MulH_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_mulhsu = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "mulhsu",
  24,
  [](PerformanceModel* perfModel_){
	MulH_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_div = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "div",
  25,
  [](PerformanceModel* perfModel_){
	Div_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_rem = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "rem",
  26,
  [](PerformanceModel* perfModel_){
	Div_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_divu = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "divu",
  27,
  [](PerformanceModel* perfModel_){
	DivU_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_remu = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "remu",
  28,
  [](PerformanceModel* perfModel_){
	DivU_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_csrrw = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "csrrw",
  29,
  [](PerformanceModel* perfModel_){
	Csr_Ra(perfModel_);
});

static SchedulingFunction *schedulingFunction_csrrs = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "csrrs",
  30,
  [](PerformanceModel* perfModel_){
	Csr_Ra(perfModel_);
});

static SchedulingFunction *schedulingFunction_csrrc = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "csrrc",
  31,
  [](PerformanceModel* perfModel_){
	Csr_Ra(perfModel_);
});

static SchedulingFunction *schedulingFunction_csrrwi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "csrrwi",
  32,
  [](PerformanceModel* perfModel_){
	Csr_X(perfModel_);
});

static SchedulingFunction *schedulingFunction_csrrsi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "csrrsi",
  33,
  [](PerformanceModel* perfModel_){
	Csr_X(perfModel_);
});

static SchedulingFunction *schedulingFunction_csrrci = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "csrrci",
  34,
  [](PerformanceModel* perfModel_){
	Csr_X(perfModel_);
});

static SchedulingFunction *schedulingFunction_sb = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "sb",
  35,
  [](PerformanceModel* perfModel_){
	Store(perfModel_);
});

static SchedulingFunction *schedulingFunction_sh = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "sh",
  36,
  [](PerformanceModel* perfModel_){
	Store(perfModel_);
});

static SchedulingFunction *schedulingFunction_sw = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "sw",
  37,
  [](PerformanceModel* perfModel_){
	Store(perfModel_);
});

static SchedulingFunction *schedulingFunction_lw = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "lw",
  38,
  [](PerformanceModel* perfModel_){
	Load(perfModel_);
});

static SchedulingFunction *schedulingFunction_lh = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "lh",
  39,
  [](PerformanceModel* perfModel_){
	Load(perfModel_);
});

static SchedulingFunction *schedulingFunction_lhu = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "lhu",
  40,
  [](PerformanceModel* perfModel_){
	Load(perfModel_);
});

static SchedulingFunction *schedulingFunction_lb = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "lb",
  41,
  [](PerformanceModel* perfModel_){
	Load(perfModel_);
});

static SchedulingFunction *schedulingFunction_lbu = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "lbu",
  42,
  [](PerformanceModel* perfModel_){
	Load(perfModel_);
});

static SchedulingFunction *schedulingFunction_beq = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "beq",
  43,
  [](PerformanceModel* perfModel_){
	Branch_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_bne = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "bne",
  44,
  [](PerformanceModel* perfModel_){
	Branch_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_blt = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "blt",
  45,
  [](PerformanceModel* perfModel_){
	Branch_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_bge = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "bge",
  46,
  [](PerformanceModel* perfModel_){
	Branch_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_bltu = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "bltu",
  47,
  [](PerformanceModel* perfModel_){
	Branch_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_bgeu = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "bgeu",
  48,
  [](PerformanceModel* perfModel_){
	Branch_Ra_Rb(perfModel_);
});

static SchedulingFunction *schedulingFunction_vle32_v = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vle32_v",
  49,
  [](PerformanceModel* perfModel_){
	V_Load(perfModel_);
});

static SchedulingFunction *schedulingFunction_vle16_v = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vle16_v",
  50,
  [](PerformanceModel* perfModel_){
	V_Load(perfModel_);
});

static SchedulingFunction *schedulingFunction_vle8_v = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vle8_v",
  51,
  [](PerformanceModel* perfModel_){
	V_Load(perfModel_);
});

static SchedulingFunction *schedulingFunction_vl8r_v = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vl8r_v",
  52,
  [](PerformanceModel* perfModel_){
	V_Load_Registers(perfModel_);
});

static SchedulingFunction *schedulingFunction_vl16r_v = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vl16r_v",
  53,
  [](PerformanceModel* perfModel_){
	V_Load_Registers(perfModel_);
});

static SchedulingFunction *schedulingFunction_vl32r_v = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vl32r_v",
  54,
  [](PerformanceModel* perfModel_){
	V_Load_Registers(perfModel_);
});

static SchedulingFunction *schedulingFunction_vse32_u = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vse32_u",
  55,
  [](PerformanceModel* perfModel_){
	V_Store(perfModel_);
});

static SchedulingFunction *schedulingFunction_vse16_u = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vse16_u",
  56,
  [](PerformanceModel* perfModel_){
	V_Store(perfModel_);
});

static SchedulingFunction *schedulingFunction_vse8_u = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vse8_u",
  57,
  [](PerformanceModel* perfModel_){
	V_Store(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsr_v = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsr_v",
  58,
  [](PerformanceModel* perfModel_){
	V_Store_Registers(perfModel_);
});

static SchedulingFunction *schedulingFunction_vzext_vf2 = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vzext_vf2",
  59,
  [](PerformanceModel* perfModel_){
	V_Ext(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsext_vf2 = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsext_vf2",
  60,
  [](PerformanceModel* perfModel_){
	V_Ext(perfModel_);
});

static SchedulingFunction *schedulingFunction_vzext_vf4 = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vzext_vf4",
  61,
  [](PerformanceModel* perfModel_){
	V_Ext(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsext_vf4 = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsext_vf4",
  62,
  [](PerformanceModel* perfModel_){
	V_Ext(perfModel_);
});

static SchedulingFunction *schedulingFunction_vzext_vf8 = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vzext_vf8",
  63,
  [](PerformanceModel* perfModel_){
	V_Ext(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsext_vf8 = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsext_vf8",
  64,
  [](PerformanceModel* perfModel_){
	V_Ext(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmv_v_i = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmv_v_i",
  65,
  [](PerformanceModel* perfModel_){
	V_vmv_v_i(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmvr_v = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmvr_v",
  66,
  [](PerformanceModel* perfModel_){
	V_vmv_regs(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmv_s_x = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmv_s_x",
  67,
  [](PerformanceModel* perfModel_){
	V_vmv_s_x(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmv_x_s = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmv_x_s",
  68,
  [](PerformanceModel* perfModel_){
	V_vmv_x_s(perfModel_);
});

static SchedulingFunction *schedulingFunction_vdiv_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vdiv_vv",
  69,
  [](PerformanceModel* perfModel_){
	V_Div_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vdivu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vdivu_vv",
  70,
  [](PerformanceModel* perfModel_){
	V_Div_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vremu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vremu_vv",
  71,
  [](PerformanceModel* perfModel_){
	V_Div_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vrem_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vrem_vv",
  72,
  [](PerformanceModel* perfModel_){
	V_Div_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vdiv_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vdiv_vx",
  73,
  [](PerformanceModel* perfModel_){
	V_Div_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vdivu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vdivu_vx",
  74,
  [](PerformanceModel* perfModel_){
	V_Div_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vremu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vremu_vx",
  75,
  [](PerformanceModel* perfModel_){
	V_Div_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vrem_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vrem_vx",
  76,
  [](PerformanceModel* perfModel_){
	V_Div_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vadd_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vadd_vv",
  77,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsub_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsub_vv",
  78,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vadc_vvm = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vadc_vvm",
  79,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmadc_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmadc_vv",
  80,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsbc_vvm = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsbc_vvm",
  81,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsbc_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsbc_vv",
  82,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vand_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vand_vv",
  83,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vor_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vor_vv",
  84,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vxor_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vxor_vv",
  85,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsll_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsll_vv",
  86,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsrl_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsrl_vv",
  87,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsra_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsra_vv",
  88,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmseq_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmseq_vv",
  89,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsne_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsne_vv",
  90,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsltu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsltu_vv",
  91,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmslt_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmslt_vv",
  92,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsleu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsleu_vv",
  93,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsle_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsle_vv",
  94,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vminu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vminu_vv",
  95,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmin_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmin_vv",
  96,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmaxu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmaxu_vv",
  97,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmax_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmax_vv",
  98,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmerge_vvm = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmerge_vvm",
  99,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsaddu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsaddu_vv",
  100,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsadd_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsadd_vv",
  101,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vssubu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vssubu_vv",
  102,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vssub_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vssub_vv",
  103,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vaaddu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vaaddu_vv",
  104,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vaadd_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vaadd_vv",
  105,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vasubu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vasubu_vv",
  106,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vasub_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vasub_vv",
  107,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsmul_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsmul_vv",
  108,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vssrl_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vssrl_vv",
  109,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vssra_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vssra_vv",
  110,
  [](PerformanceModel* perfModel_){
	V_ALU_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vadd_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vadd_vx",
  111,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsub_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsub_vx",
  112,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vrsub_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vrsub_vx",
  113,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vadc_vxm = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vadc_vxm",
  114,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmadc_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmadc_vx",
  115,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsbc_vxm = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsbc_vxm",
  116,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsbc_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsbc_vx",
  117,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vand_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vand_vx",
  118,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vor_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vor_vx",
  119,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vxor_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vxor_vx",
  120,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsll_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsll_vx",
  121,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsrl_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsrl_vx",
  122,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsra_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsra_vx",
  123,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmseq_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmseq_vx",
  124,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsne_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsne_vx",
  125,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsltu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsltu_vx",
  126,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmslt_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmslt_vx",
  127,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsleu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsleu_vx",
  128,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsle_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsle_vx",
  129,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsgtu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsgtu_vx",
  130,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsgt_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsgt_vx",
  131,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vminu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vminu_vx",
  132,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmin_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmin_vx",
  133,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmaxu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmaxu_vx",
  134,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmax_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmax_vx",
  135,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmerge_vxm = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmerge_vxm",
  136,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsaddu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsaddu_vx",
  137,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsadd_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsadd_vx",
  138,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vssubu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vssubu_vx",
  139,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vssub_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vssub_vx",
  140,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vaaddu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vaaddu_vx",
  141,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vaadd_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vaadd_vx",
  142,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vasubu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vasubu_vx",
  143,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vasub_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vasub_vx",
  144,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsmul_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsmul_vx",
  145,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vssrl_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vssrl_vx",
  146,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vssra_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vssra_vx",
  147,
  [](PerformanceModel* perfModel_){
	V_ALU_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmul_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmul_vv",
  148,
  [](PerformanceModel* perfModel_){
	V_MUL_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmulh_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmulh_vv",
  149,
  [](PerformanceModel* perfModel_){
	V_MUL_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmulhu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmulhu_vv",
  150,
  [](PerformanceModel* perfModel_){
	V_MUL_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmulhsu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmulhsu_vv",
  151,
  [](PerformanceModel* perfModel_){
	V_MUL_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmacc_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmacc_vv",
  152,
  [](PerformanceModel* perfModel_){
	V_MUL_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vnmsac_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vnmsac_vv",
  153,
  [](PerformanceModel* perfModel_){
	V_MUL_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmadd_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmadd_vv",
  154,
  [](PerformanceModel* perfModel_){
	V_MUL_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vnmsub_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vnmsub_vv",
  155,
  [](PerformanceModel* perfModel_){
	V_MUL_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwaddu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwaddu_vv",
  156,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwsubu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwsubu_vv",
  157,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwadd_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwadd_vv",
  158,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwsub_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwsub_vv",
  159,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwaddu_w_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwaddu_w_vv",
  160,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwsubu_w_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwsubu_w_vv",
  161,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwadd_w_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwadd_w_vv",
  162,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwsub_w_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwsub_w_vv",
  163,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwmul_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwmul_vv",
  164,
  [](PerformanceModel* perfModel_){
	V_MUL_Widening_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwmulu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwmulu_vv",
  165,
  [](PerformanceModel* perfModel_){
	V_MUL_Widening_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwmulsu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwmulsu_vv",
  166,
  [](PerformanceModel* perfModel_){
	V_MUL_Widening_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwmaccu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwmaccu_vv",
  167,
  [](PerformanceModel* perfModel_){
	V_MUL_Widening_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwmacc_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwmacc_vv",
  168,
  [](PerformanceModel* perfModel_){
	V_MUL_Widening_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwmaccsu_vv = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwmaccsu_vv",
  169,
  [](PerformanceModel* perfModel_){
	V_MUL_Widening_vv(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmul_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmul_vx",
  170,
  [](PerformanceModel* perfModel_){
	V_MUL_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmulh_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmulh_vx",
  171,
  [](PerformanceModel* perfModel_){
	V_MUL_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmulhu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmulhu_vx",
  172,
  [](PerformanceModel* perfModel_){
	V_MUL_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmulhsu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmulhsu_vx",
  173,
  [](PerformanceModel* perfModel_){
	V_MUL_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmacc_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmacc_vx",
  174,
  [](PerformanceModel* perfModel_){
	V_MUL_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vnmsac_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vnmsac_vx",
  175,
  [](PerformanceModel* perfModel_){
	V_MUL_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmadd_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmadd_vx",
  176,
  [](PerformanceModel* perfModel_){
	V_MUL_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vnmsub_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vnmsub_vx",
  177,
  [](PerformanceModel* perfModel_){
	V_MUL_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwaddu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwaddu_vx",
  178,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwsubu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwsubu_vx",
  179,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwadd_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwadd_vx",
  180,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwsub_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwsub_vx",
  181,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwaddu_w_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwaddu_w_vx",
  182,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwsubu_w_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwsubu_w_vx",
  183,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwadd_w_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwadd_w_vx",
  184,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwsub_w_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwsub_w_vx",
  185,
  [](PerformanceModel* perfModel_){
	V_ALU_Widening_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwmul_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwmul_vx",
  186,
  [](PerformanceModel* perfModel_){
	V_MUL_Widening_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwmulu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwmulu_vx",
  187,
  [](PerformanceModel* perfModel_){
	V_MUL_Widening_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwmulsu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwmulsu_vx",
  188,
  [](PerformanceModel* perfModel_){
	V_MUL_Widening_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwmaccu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwmaccu_vx",
  189,
  [](PerformanceModel* perfModel_){
	V_MUL_Widening_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwmacc_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwmacc_vx",
  190,
  [](PerformanceModel* perfModel_){
	V_MUL_Widening_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwmaccsu_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwmaccsu_vx",
  191,
  [](PerformanceModel* perfModel_){
	V_MUL_Widening_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vwmaccus_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vwmaccus_vx",
  192,
  [](PerformanceModel* perfModel_){
	V_MUL_Widening_vx(perfModel_);
});

static SchedulingFunction *schedulingFunction_vadd_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vadd_vi",
  193,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vrsub_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vrsub_vi",
  194,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vadc_vim = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vadc_vim",
  195,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmadc_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmadc_vi",
  196,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vand_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vand_vi",
  197,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vor_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vor_vi",
  198,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vxor_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vxor_vi",
  199,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsll_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsll_vi",
  200,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsrl_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsrl_vi",
  201,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsra_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsra_vi",
  202,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmseq_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmseq_vi",
  203,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsne_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsne_vi",
  204,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsleu_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsleu_vi",
  205,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsle_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsle_vi",
  206,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsgtu_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsgtu_vi",
  207,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmsgt_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmsgt_vi",
  208,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vmerge_vim = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vmerge_vim",
  209,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsaddu_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsaddu_vi",
  210,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsadd_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsadd_vi",
  211,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vssrl_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vssrl_vi",
  212,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vssra_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vssra_vi",
  213,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vcompress_vm = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vcompress_vm",
  214,
  [](PerformanceModel* perfModel_){
	V_ELEM(perfModel_);
});

static SchedulingFunction *schedulingFunction_vredsum_vs = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vredsum_vs",
  215,
  [](PerformanceModel* perfModel_){
	V_REDSUM(perfModel_);
});

static SchedulingFunction *schedulingFunction_vredand_vs = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vredand_vs",
  216,
  [](PerformanceModel* perfModel_){
	V_REDSUM(perfModel_);
});

static SchedulingFunction *schedulingFunction_vredor_vs = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vredor_vs",
  217,
  [](PerformanceModel* perfModel_){
	V_REDSUM(perfModel_);
});

static SchedulingFunction *schedulingFunction_vredxor_vs = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vredxor_vs",
  218,
  [](PerformanceModel* perfModel_){
	V_REDSUM(perfModel_);
});

static SchedulingFunction *schedulingFunction_vredmaxu_vs = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vredmaxu_vs",
  219,
  [](PerformanceModel* perfModel_){
	V_REDMINMAX(perfModel_);
});

static SchedulingFunction *schedulingFunction_vredmax_vs = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vredmax_vs",
  220,
  [](PerformanceModel* perfModel_){
	V_REDMINMAX(perfModel_);
});

static SchedulingFunction *schedulingFunction_vredminu_vs = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vredminu_vs",
  221,
  [](PerformanceModel* perfModel_){
	V_REDMINMAX(perfModel_);
});

static SchedulingFunction *schedulingFunction_vredmin_vs = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vredmin_vs",
  222,
  [](PerformanceModel* perfModel_){
	V_REDMINMAX(perfModel_);
});

static SchedulingFunction *schedulingFunction_vcpop_m = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vcpop_m",
  223,
  [](PerformanceModel* perfModel_){
	V_XRESULT(perfModel_);
});

static SchedulingFunction *schedulingFunction_vfirst_m = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vfirst_m",
  224,
  [](PerformanceModel* perfModel_){
	V_XRESULT(perfModel_);
});

static SchedulingFunction *schedulingFunction_vid_v = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vid_v",
  225,
  [](PerformanceModel* perfModel_){
	V_INDEX(perfModel_);
});

static SchedulingFunction *schedulingFunction_viota_m = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "viota_m",
  226,
  [](PerformanceModel* perfModel_){
	V_INDEX(perfModel_);
});

static SchedulingFunction *schedulingFunction_vslideup_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vslideup_vx",
  227,
  [](PerformanceModel* perfModel_){
	V_SLD(perfModel_);
});

static SchedulingFunction *schedulingFunction_vslidedown_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vslidedown_vx",
  228,
  [](PerformanceModel* perfModel_){
	V_SLD(perfModel_);
});

static SchedulingFunction *schedulingFunction_vslide1up_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vslide1up_vx",
  229,
  [](PerformanceModel* perfModel_){
	V_SLD(perfModel_);
});

static SchedulingFunction *schedulingFunction_vslide1down_vx = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vslide1down_vx",
  230,
  [](PerformanceModel* perfModel_){
	V_SLD(perfModel_);
});

static SchedulingFunction *schedulingFunction_vslideup_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vslideup_vi",
  231,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vslidedown_vi = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vslidedown_vi",
  232,
  [](PerformanceModel* perfModel_){
	V_ALU_vi(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsetivli = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsetivli",
  233,
  [](PerformanceModel* perfModel_){
	V_vsetivli(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsetvli = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsetvli",
  234,
  [](PerformanceModel* perfModel_){
	V_vsetvli(perfModel_);
});

static SchedulingFunction *schedulingFunction_vsetvl = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "vsetvl",
  235,
  [](PerformanceModel* perfModel_){
	V_vsetvl(perfModel_);
});

static SchedulingFunction *schedulingFunction__def = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "_def",
  236,
  [](PerformanceModel* perfModel_){
  Vicuna_zvl128b_PerformanceModel* perfModel = static_cast<Vicuna_zvl128b_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->IF_stg;
// IPort_R
uint64_t n_IPort_R;
uint64_t n_IPort_R_max;
n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
n_IPort_R = n_IPort_R_max + 1;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->staBranchPredModel.setPc_p(n_PCGen);
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen});
perfModel->IF_stg = n_IF_stg;

  }
);

static SchedulingFunction *schedulingFunction_jal = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "jal",
  237,
  [](PerformanceModel* perfModel_){
  Vicuna_zvl128b_PerformanceModel* perfModel = static_cast<Vicuna_zvl128b_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->IF_stg;
// IPort_R
uint64_t n_IPort_R;
uint64_t n_IPort_R_max;
n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
n_IPort_R = n_IPort_R_max + 1;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->staBranchPredModel.setPc_p(n_PCGen);
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, perfModel->ID_stg});
perfModel->IF_stg = n_IF_stg;
// JumpDecoder
uint64_t n_JumpDecoder;
n_JumpDecoder = n_IF_stg + 1;
perfModel->staBranchPredModel.setPc_np(n_JumpDecoder);
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_JumpDecoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// EX_ALU
uint64_t n_EX_ALU;
n_EX_ALU = n_ID_stg + 1;
perfModel->regModel.setXd(n_EX_ALU);
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_EX_ALU, n_uA_EX_Req_WbFreeSignal, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;

  }
);

static SchedulingFunction *schedulingFunction_jalr = new SchedulingFunction(
  Vicuna_zvl128b_SchedulingFunctionSet,
  "jalr",
  238,
  [](PerformanceModel* perfModel_){
  Vicuna_zvl128b_PerformanceModel* perfModel = static_cast<Vicuna_zvl128b_PerformanceModel*>(perfModel_);
  // Enter
uint64_t n_Enter = perfModel->IF_stg;
// IPort_R
uint64_t n_IPort_R;
uint64_t n_IPort_R_max;
n_IPort_R_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
n_IPort_R = n_IPort_R_max + 1;
// PCGen
uint64_t n_PCGen;
uint64_t n_PCGen_max;
n_PCGen_max = std::max({n_Enter, perfModel->staBranchPredModel.getPc()});
n_PCGen = n_PCGen_max + 1;
perfModel->staBranchPredModel.setPc_p(n_PCGen);
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, perfModel->ID_stg});
perfModel->IF_stg = n_IF_stg;
// JumpDecoder
uint64_t n_JumpDecoder;
uint64_t n_JumpDecoder_max;
n_JumpDecoder_max = std::max({n_IF_stg, perfModel->regModel.getXa()});
n_JumpDecoder = n_JumpDecoder_max + 1;
perfModel->staBranchPredModel.setPc_np(n_JumpDecoder);
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_JumpDecoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// EX_ALU
uint64_t n_EX_ALU;
n_EX_ALU = n_ID_stg + 1;
perfModel->regModel.setXd(n_EX_ALU);
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_EX_ALU, n_uA_EX_Req_WbFreeSignal, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;

  }
);


} // namespace Vicuna_zvl128b