
#include "PerformanceModel.h"

namespace Vicuna_zvl128b {
void Arith_Ra_Rb(PerformanceModel *perfModel_);

void Arith_Ra(PerformanceModel *perfModel_);

void Arith_X(PerformanceModel *perfModel_);

void Mul_Ra_Rb(PerformanceModel *perfModel_);

void MulH_Ra_Rb(PerformanceModel *perfModel_);

void Div_Ra_Rb(PerformanceModel *perfModel_);

void DivU_Ra_Rb(PerformanceModel *perfModel_);

void Csr_Ra(PerformanceModel *perfModel_);

void Csr_X(PerformanceModel *perfModel_);

void Store(PerformanceModel *perfModel_);

void Load(PerformanceModel *perfModel_);

void Branch_Ra_Rb(PerformanceModel *perfModel_);

void V_Load(PerformanceModel *perfModel_);

void V_Load_Registers(PerformanceModel *perfModel_);

void V_Store(PerformanceModel *perfModel_);

void V_Store_Registers(PerformanceModel *perfModel_);

void V_Ext(PerformanceModel *perfModel_);

void V_vmv_v_i(PerformanceModel *perfModel_);

void V_vmv_regs(PerformanceModel *perfModel_);

void V_vmv_s_x(PerformanceModel *perfModel_);

void V_vmv_x_s(PerformanceModel *perfModel_);

void V_Div_vv(PerformanceModel *perfModel_);

void V_Div_vx(PerformanceModel *perfModel_);

void V_ALU_vv(PerformanceModel *perfModel_);

void V_ALU_vx(PerformanceModel *perfModel_);

void V_MUL_vv(PerformanceModel *perfModel_);

void V_ALU_Widening_vv(PerformanceModel *perfModel_);

void V_MUL_Widening_vv(PerformanceModel *perfModel_);

void V_MUL_vx(PerformanceModel *perfModel_);

void V_ALU_Widening_vx(PerformanceModel *perfModel_);

void V_MUL_Widening_vx(PerformanceModel *perfModel_);

void V_ALU_vi(PerformanceModel *perfModel_);

void V_ELEM(PerformanceModel *perfModel_);

void V_REDSUM(PerformanceModel *perfModel_);

void V_REDMINMAX(PerformanceModel *perfModel_);

void V_XRESULT(PerformanceModel *perfModel_);

void V_INDEX(PerformanceModel *perfModel_);

void V_SLD(PerformanceModel *perfModel_);

void V_vsetivli(PerformanceModel *perfModel_);

void V_vsetvli(PerformanceModel *perfModel_);

void V_vsetvl(PerformanceModel *perfModel_);

} // Namespace