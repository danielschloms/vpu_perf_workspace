
#include <algorithm>
#include <cstdint>
#include "PerformanceModel.h"
#include "Vicuna_zvl128b_PerformanceModel.h"

namespace Vicuna_zvl128b {
void Arith_Ra_Rb(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// uA_ID_Req_SReg_A
uint64_t n_uA_ID_Req_SReg_A;
n_uA_ID_Req_SReg_A = std::max({n_IF_stg, perfModel->regModel.getXa()});
// uA_ID_Req_SReg_B
uint64_t n_uA_ID_Req_SReg_B;
n_uA_ID_Req_SReg_B = std::max({n_IF_stg, perfModel->regModel.getXb()});
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, n_uA_ID_Req_SReg_A, n_uA_ID_Req_SReg_B, perfModel->EX_stg});
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

void Arith_Ra(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// uA_ID_Req_SReg_A
uint64_t n_uA_ID_Req_SReg_A;
n_uA_ID_Req_SReg_A = std::max({n_IF_stg, perfModel->regModel.getXa()});
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, n_uA_ID_Req_SReg_A, perfModel->EX_stg});
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

void Arith_X(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
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

void Mul_Ra_Rb(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// uA_ID_Req_SReg_A
uint64_t n_uA_ID_Req_SReg_A;
n_uA_ID_Req_SReg_A = std::max({n_IF_stg, perfModel->regModel.getXa()});
// uA_ID_Req_SReg_B
uint64_t n_uA_ID_Req_SReg_B;
n_uA_ID_Req_SReg_B = std::max({n_IF_stg, perfModel->regModel.getXb()});
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, n_uA_ID_Req_SReg_A, n_uA_ID_Req_SReg_B, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_MUL
uint64_t n_EX_MUL;
n_EX_MUL = n_ID_stg + 1;
perfModel->regModel.setXd(n_EX_MUL);
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_MUL, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;

}

void MulH_Ra_Rb(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// uA_ID_Req_SReg_A
uint64_t n_uA_ID_Req_SReg_A;
n_uA_ID_Req_SReg_A = std::max({n_IF_stg, perfModel->regModel.getXa()});
// uA_ID_Req_SReg_B
uint64_t n_uA_ID_Req_SReg_B;
n_uA_ID_Req_SReg_B = std::max({n_IF_stg, perfModel->regModel.getXb()});
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, n_uA_ID_Req_SReg_A, n_uA_ID_Req_SReg_B, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_MULH
uint64_t n_EX_MULH;
n_EX_MULH = n_ID_stg + 4;
perfModel->regModel.setXd(n_EX_MULH);
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_MULH, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;

}

void Div_Ra_Rb(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// uA_ID_Req_SReg_A
uint64_t n_uA_ID_Req_SReg_A;
n_uA_ID_Req_SReg_A = std::max({n_IF_stg, perfModel->regModel.getXa()});
// uA_ID_Req_SReg_B
uint64_t n_uA_ID_Req_SReg_B;
n_uA_ID_Req_SReg_B = std::max({n_IF_stg, perfModel->regModel.getXb()});
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, n_uA_ID_Req_SReg_A, n_uA_ID_Req_SReg_B, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_DIV
uint64_t n_EX_DIV;
n_EX_DIV = n_ID_stg + perfModel->divider.getDelay();
perfModel->regModel.setXd(n_EX_DIV);
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_DIV, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;

}

void DivU_Ra_Rb(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// uA_ID_Req_SReg_A
uint64_t n_uA_ID_Req_SReg_A;
n_uA_ID_Req_SReg_A = std::max({n_IF_stg, perfModel->regModel.getXa()});
// uA_ID_Req_SReg_B
uint64_t n_uA_ID_Req_SReg_B;
n_uA_ID_Req_SReg_B = std::max({n_IF_stg, perfModel->regModel.getXb()});
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, n_uA_ID_Req_SReg_A, n_uA_ID_Req_SReg_B, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_DIVU
uint64_t n_EX_DIVU;
n_EX_DIVU = n_ID_stg + perfModel->divider_u.getDelay();
perfModel->regModel.setXd(n_EX_DIVU);
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_DIVU, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;

}

void Csr_Ra(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// uA_ID_Req_SReg_A
uint64_t n_uA_ID_Req_SReg_A;
n_uA_ID_Req_SReg_A = std::max({n_IF_stg, perfModel->regModel.getXa()});
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, n_uA_ID_Req_SReg_A, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// WB_CSR
uint64_t n_WB_CSR;
n_WB_CSR = n_EX_stg + 1;
perfModel->regModel.setXd(n_WB_CSR);
// WB_stg
uint64_t n_WB_stg = n_WB_CSR;
perfModel->WB_stg = n_WB_stg;

}

void Csr_X(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// WB_CSR
uint64_t n_WB_CSR;
n_WB_CSR = n_EX_stg + 1;
perfModel->regModel.setXd(n_WB_CSR);
// WB_stg
uint64_t n_WB_stg = n_WB_CSR;
perfModel->WB_stg = n_WB_stg;

}

void Store(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// uA_ID_Req_SReg_A
uint64_t n_uA_ID_Req_SReg_A;
n_uA_ID_Req_SReg_A = std::max({n_IF_stg, perfModel->regModel.getXa()});
// uA_ID_Req_SReg_B
uint64_t n_uA_ID_Req_SReg_B;
n_uA_ID_Req_SReg_B = std::max({n_IF_stg, perfModel->regModel.getXb()});
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, n_uA_ID_Req_SReg_A, n_uA_ID_Req_SReg_B, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_LSU
uint64_t n_EX_LSU;
n_EX_LSU = n_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_LSU, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// DPort_W
uint64_t n_DPort_W;
n_DPort_W = n_EX_stg + 1;
// WB_stg
uint64_t n_WB_stg = n_DPort_W;
perfModel->WB_stg = n_WB_stg;

}

void Load(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// uA_ID_Req_SReg_A
uint64_t n_uA_ID_Req_SReg_A;
n_uA_ID_Req_SReg_A = std::max({n_IF_stg, perfModel->regModel.getXa()});
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, n_uA_ID_Req_SReg_A, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_LSU
uint64_t n_EX_LSU;
n_EX_LSU = n_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_LSU, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// DPort_R
uint64_t n_DPort_R;
n_DPort_R = n_EX_stg + 1;
perfModel->regModel.setXd(n_DPort_R);
// WB_stg
uint64_t n_WB_stg = n_DPort_R;
perfModel->WB_stg = n_WB_stg;

}

void Branch_Ra_Rb(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// uA_ID_Req_SReg_A
uint64_t n_uA_ID_Req_SReg_A;
n_uA_ID_Req_SReg_A = std::max({n_IF_stg, perfModel->regModel.getXa()});
// uA_ID_Req_SReg_B
uint64_t n_uA_ID_Req_SReg_B;
n_uA_ID_Req_SReg_B = std::max({n_IF_stg, perfModel->regModel.getXb()});
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, n_uA_ID_Req_SReg_A, n_uA_ID_Req_SReg_B, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// EX_ALU
uint64_t n_EX_ALU;
n_EX_ALU = n_ID_stg + 1;
perfModel->staBranchPredModel.setPc_np(n_EX_ALU);
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

void V_Load(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroupLoad
uint64_t n_uA_V_DISP_Req_MaxVdGroupLoad;
n_uA_V_DISP_Req_MaxVdGroupLoad = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroupLoad()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroupLoad, perfModel->V1_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V1_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V1_Unpack_Fixed;
uint64_t n_V1_Unpack_stg;
uint64_t n_V1_LSU_BUF_REQ;
uint64_t n_V1_LSU_BUF_REQ_stg;
uint64_t n_V1_MemAccess;
uint64_t n_V1_LSU_MemAccess_stg;
uint64_t n_V1_LSU_BUF_RESP;
uint64_t n_V1_Subpipe;
uint64_t n_V1_Pack_Write;
uint64_t n_V1_Pack_FreeWb;
uint64_t n_V1_Pack_stg;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLoadStoreEmul(); batch_i++) {
n_V1_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V1_Unpack_stg);
// V1_Unpack_stg
n_V1_Unpack_stg = std::max({n_V1_Unpack_Fixed, (batch_i == 0) * (perfModel->V1_Subpipe + 1), perfModel->V1_LSU_BUF_REQ_stg});
perfModel->V1_Unpack_stg = n_V1_Unpack_stg;
// V1_LSU_BUF_REQ
n_V1_LSU_BUF_REQ = n_V1_Unpack_stg + perfModel->vectorFixedDelayV1.getDelay();
// V1_LSU_BUF_REQ_stg
n_V1_LSU_BUF_REQ_stg = std::max({n_V1_LSU_BUF_REQ, perfModel->V1_LSU_MemAccess_stg});
perfModel->V1_LSU_BUF_REQ_stg = n_V1_LSU_BUF_REQ_stg;
// V1_MemAccess
n_V1_MemAccess = n_V1_LSU_BUF_REQ_stg + 1;
// V1_LSU_MemAccess_stg
n_V1_LSU_MemAccess_stg = std::max({n_V1_MemAccess, perfModel->V1_LSU_BUF_RESP_stg});
perfModel->V1_LSU_MemAccess_stg = n_V1_LSU_MemAccess_stg;
// V1_LSU_BUF_RESP
n_V1_LSU_BUF_RESP = n_V1_LSU_MemAccess_stg + 4;
// V1_Subpipe
n_V1_Subpipe = std::max({n_V1_LSU_BUF_RESP, perfModel->V1_Pack_stg});
perfModel->V1_Subpipe = n_V1_Subpipe;
perfModel->V1_LSU_BUF_RESP_stg = n_V1_Subpipe;
// V1_Pack_Write
n_V1_Pack_Write = n_V1_Subpipe + 2;
// The load's vector-DATA lands at V1_Pack_Write (consumers see the real
// producer latency), but the in-order RETIRE chain only needs to advance to
// V1_Pack_FreeWb (where the register write slot is free). Without this split,
// setVd's vectorBusyUntil = V1_Pack_Write+1 over-gates the next in-order op
// (dE 17 vs RTL 15 for back-to-back vle8). Keep the +1 data-ready convention
// consistent with the 2-arg setVd, but pass the retire barrier separately.
perfModel->vectorBatchHandModel.setVd(batch_i,n_V1_Pack_Write + 1,n_V1_Pack_FreeWb);
// V1_Pack_FreeWb
n_V1_Pack_FreeWb = n_V1_Subpipe + 1;
// setWbFreeSignal adds +1, so pass V1_Subpipe so wbFreeSignal lands exactly on
// V1_Pack_FreeWb (the retire/slot-free point), not one cycle late.
perfModel->vectorBatchHandModel.setWbFreeSignal(n_V1_Subpipe);
// V1_Pack_stg
n_V1_Pack_stg = std::max({n_V1_Pack_Write, n_V1_Pack_FreeWb});
perfModel->V1_Pack_stg = n_V1_Pack_stg;
}
// End Batch Loop
}

void V_Load_Registers(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroupNf
uint64_t n_uA_V_DISP_Req_MaxVdGroupNf;
n_uA_V_DISP_Req_MaxVdGroupNf = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroupNf()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroupNf, perfModel->V1_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V1_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V1_Unpack_Fixed;
uint64_t n_V1_Unpack_stg;
uint64_t n_V1_LSU_BUF_REQ;
uint64_t n_V1_LSU_BUF_REQ_stg;
uint64_t n_V1_MemAccess;
uint64_t n_V1_LSU_MemAccess_stg;
uint64_t n_V1_LSU_BUF_RESP;
uint64_t n_V1_Subpipe;
uint64_t n_V1_Pack_Write;
uint64_t n_V1_Pack_FreeWb;
uint64_t n_V1_Pack_stg;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getNf(); batch_i++) {
n_V1_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V1_Unpack_stg);
// V1_Unpack_stg
n_V1_Unpack_stg = std::max({n_V1_Unpack_Fixed, (batch_i == 0) * (perfModel->V1_Subpipe + 1), perfModel->V1_LSU_BUF_REQ_stg});
perfModel->V1_Unpack_stg = n_V1_Unpack_stg;
// V1_LSU_BUF_REQ
n_V1_LSU_BUF_REQ = n_V1_Unpack_stg + perfModel->vectorFixedDelayV1.getDelay();
// V1_LSU_BUF_REQ_stg
n_V1_LSU_BUF_REQ_stg = std::max({n_V1_LSU_BUF_REQ, perfModel->V1_LSU_MemAccess_stg});
perfModel->V1_LSU_BUF_REQ_stg = n_V1_LSU_BUF_REQ_stg;
// V1_MemAccess
n_V1_MemAccess = n_V1_LSU_BUF_REQ_stg + 1;
// V1_LSU_MemAccess_stg
n_V1_LSU_MemAccess_stg = std::max({n_V1_MemAccess, perfModel->V1_LSU_BUF_RESP_stg});
perfModel->V1_LSU_MemAccess_stg = n_V1_LSU_MemAccess_stg;
// V1_LSU_BUF_RESP
n_V1_LSU_BUF_RESP = n_V1_LSU_MemAccess_stg + 4;
// V1_Subpipe
n_V1_Subpipe = std::max({n_V1_LSU_BUF_RESP, perfModel->V1_Pack_stg});
perfModel->V1_Subpipe = n_V1_Subpipe;
perfModel->V1_LSU_BUF_RESP_stg = n_V1_Subpipe;
// V1_Pack_Write
n_V1_Pack_Write = n_V1_Subpipe + 2;
// Load data lands at V1_Pack_Write, but retire chain advances to V1_Pack_FreeWb.
perfModel->vectorBatchHandModel.setVd(batch_i,n_V1_Pack_Write + 1,n_V1_Pack_FreeWb);
// V1_Pack_FreeWb
n_V1_Pack_FreeWb = n_V1_Subpipe + 1;
// load's retires at exactly V1_Pack_FreeWb (setWbFreeSignal adds +1).
perfModel->vectorBatchHandModel.setWbFreeSignal(n_V1_Subpipe);
// V1_Pack_stg
n_V1_Pack_stg = std::max({n_V1_Pack_Write, n_V1_Pack_FreeWb});
perfModel->V1_Pack_stg = n_V1_Pack_stg;
}
// End Batch Loop
}

void V_Store(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbSignal()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, perfModel->V1_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V1_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V1_Unpack_Fixed;
uint64_t n_uA_V1_Unpack_Req_Vs3;
uint64_t n_V1_Unpack_stg;
uint64_t n_V1_LSU_BUF_REQ;
uint64_t n_V1_LSU_BUF_REQ_stg;
uint64_t n_V1_MemAccess;
uint64_t n_V1_LSU_MemAccess_stg;
uint64_t n_V1_LSU_BUF_RESP;
uint64_t n_V1_Subpipe;
uint64_t n_V1_Pack_FreeWb;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLoadStoreEmul(); batch_i++) {
n_V1_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V1_Unpack_stg);
// uA_V1_Unpack_Req_Vs3
n_uA_V1_Unpack_Req_Vs3 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs3(batch_i)});
// V1_Unpack_stg
// A V1 store may read a V2-compute result (reduction/ALU produced in the V2 pipe);
// wait for the producer's V2 pipe drain (source-register barrier) in addition to
// the source data, else the drain to the following scalar op is under-modeled
// (RTL dV 19-26 after vse8). Data-move producers leave the barrier 0 -> no gate.
n_V1_Unpack_stg = std::max({n_V1_Unpack_Fixed, n_uA_V1_Unpack_Req_Vs3, (batch_i == 0) * (perfModel->V1_Subpipe + 1), perfModel->V1_LSU_BUF_REQ_stg, perfModel->vectorBatchHandModel.getVs3ComputeReady()});
perfModel->V1_Unpack_stg = n_V1_Unpack_stg;
// V1_LSU_BUF_REQ
n_V1_LSU_BUF_REQ = n_V1_Unpack_stg + perfModel->vectorFixedDelayV1.getDelay();
// V1_LSU_BUF_REQ_stg
n_V1_LSU_BUF_REQ_stg = std::max({n_V1_LSU_BUF_REQ, perfModel->V1_LSU_MemAccess_stg});
perfModel->V1_LSU_BUF_REQ_stg = n_V1_LSU_BUF_REQ_stg;
// V1_MemAccess
n_V1_MemAccess = n_V1_LSU_BUF_REQ_stg + 1;
// V1_LSU_MemAccess_stg
n_V1_LSU_MemAccess_stg = std::max({n_V1_MemAccess, perfModel->V1_LSU_BUF_RESP_stg});
perfModel->V1_LSU_MemAccess_stg = n_V1_LSU_MemAccess_stg;
// V1_LSU_BUF_RESP
n_V1_LSU_BUF_RESP = n_V1_LSU_MemAccess_stg + 4;
// V1_Subpipe
n_V1_Subpipe = std::max({n_V1_LSU_BUF_RESP, perfModel->V1_Pack_stg});
perfModel->V1_Subpipe = n_V1_Subpipe;
perfModel->V1_LSU_BUF_RESP_stg = n_V1_Subpipe;
// V1_Pack_FreeWb
n_V1_Pack_FreeWb = n_V1_Subpipe + 1;
perfModel->vectorBatchHandModel.setWbFreeSignal(n_V1_Pack_FreeWb);
// V1_Pack_stg
uint64_t n_V1_Pack_stg = n_V1_Pack_FreeWb;
perfModel->V1_Pack_stg = n_V1_Pack_stg;
}
// End Batch Loop
}

void V_Store_Registers(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbSignal()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, perfModel->V1_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V1_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V1_Unpack_Fixed;
uint64_t n_uA_V1_Unpack_Req_Vs3;
uint64_t n_V1_Unpack_stg;
uint64_t n_V1_LSU_BUF_REQ;
uint64_t n_V1_LSU_BUF_REQ_stg;
uint64_t n_V1_MemAccess;
uint64_t n_V1_LSU_MemAccess_stg;
uint64_t n_V1_LSU_BUF_RESP;
uint64_t n_V1_Subpipe;
uint64_t n_V1_Pack_FreeWb;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getNf(); batch_i++) {
n_V1_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V1_Unpack_stg);
// uA_V1_Unpack_Req_Vs3
n_uA_V1_Unpack_Req_Vs3 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs3(batch_i)});
// V1_Unpack_stg
// wait for the producer's V2 pipe drain for store reading a V2-compute result (see V_Store).
n_V1_Unpack_stg = std::max({n_V1_Unpack_Fixed, n_uA_V1_Unpack_Req_Vs3, (batch_i == 0) * (perfModel->V1_Subpipe + 1), perfModel->V1_LSU_BUF_REQ_stg, perfModel->vectorBatchHandModel.getVs3ComputeReady()});
perfModel->V1_Unpack_stg = n_V1_Unpack_stg;
// V1_LSU_BUF_REQ
n_V1_LSU_BUF_REQ = n_V1_Unpack_stg + perfModel->vectorFixedDelayV1.getDelay();
// V1_LSU_BUF_REQ_stg
n_V1_LSU_BUF_REQ_stg = std::max({n_V1_LSU_BUF_REQ, perfModel->V1_LSU_MemAccess_stg});
perfModel->V1_LSU_BUF_REQ_stg = n_V1_LSU_BUF_REQ_stg;
// V1_MemAccess
n_V1_MemAccess = n_V1_LSU_BUF_REQ_stg + 1;
// V1_LSU_MemAccess_stg
n_V1_LSU_MemAccess_stg = std::max({n_V1_MemAccess, perfModel->V1_LSU_BUF_RESP_stg});
perfModel->V1_LSU_MemAccess_stg = n_V1_LSU_MemAccess_stg;
// V1_LSU_BUF_RESP
n_V1_LSU_BUF_RESP = n_V1_LSU_MemAccess_stg + 4;
// V1_Subpipe
n_V1_Subpipe = std::max({n_V1_LSU_BUF_RESP, perfModel->V1_Pack_stg});
perfModel->V1_Subpipe = n_V1_Subpipe;
perfModel->V1_LSU_BUF_RESP_stg = n_V1_Subpipe;
// V1_Pack_FreeWb
n_V1_Pack_FreeWb = n_V1_Subpipe + 1;
perfModel->vectorBatchHandModel.setWbFreeSignal(n_V1_Pack_FreeWb);
// V1_Pack_stg
uint64_t n_V1_Pack_stg = n_V1_Pack_FreeWb;
perfModel->V1_Pack_stg = n_V1_Pack_stg;
}
// End Batch Loop
}

void V_Ext(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
// vsext is a pure data-movement/extension op: the scalar does not consume the
// widened result immediately, so its enter-WB advances at the SOURCE operand's
// readiness (fire-and-forget) rather than the vector completion watermark. This
// is what lets back-to-back vsexts retire at dV=1 while the arithmetic
// accumulator ops stay completion-gated.
perfModel->vectorBatchHandModel.setWbRetireAnyway(true);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroup
uint64_t n_uA_V_DISP_Req_MaxVdGroup;
n_uA_V_DISP_Req_MaxVdGroup = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroup()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroup, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_ALU_BUF_OP;
uint64_t n_V2_ALU_BUF_OP_stg;
uint64_t n_V2_ALU_BUF_INT;
uint64_t n_V2_ALU_BUF_INT_stg;
uint64_t n_V2_ALU_BUF_RES;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul(); batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_ALU_BUF_OP_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_ALU_BUF_OP
n_V2_ALU_BUF_OP = n_V2_Unpack_stg + perfModel->vectorFixedDelayV2.getDelay();
// V2_ALU_BUF_OP_stg
n_V2_ALU_BUF_OP_stg = std::max({n_V2_ALU_BUF_OP, perfModel->V2_ALU_BUF_INT_stg});
perfModel->V2_ALU_BUF_OP_stg = n_V2_ALU_BUF_OP_stg;
// V2_ALU_BUF_INT
n_V2_ALU_BUF_INT = n_V2_ALU_BUF_OP_stg + 1;
// V2_ALU_BUF_INT_stg
n_V2_ALU_BUF_INT_stg = std::max({n_V2_ALU_BUF_INT, perfModel->V2_ALU_BUF_RES_stg});
perfModel->V2_ALU_BUF_INT_stg = n_V2_ALU_BUF_INT_stg;
// V2_ALU_BUF_RES
n_V2_ALU_BUF_RES = n_V2_ALU_BUF_INT_stg + 1;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_ALU_BUF_RES, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_ALU_BUF_RES_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, (n_V2_Unpack_stg < n_EX_stg) ? (n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()) : n_V2_Unpack_stg));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
// Restore the default (completion-gated) retire policy for the next op.
perfModel->vectorBatchHandModel.setWbRetireAnyway(false);
}

void V_vmv_v_i(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
// vmv.v.i is a data-move op: the scalar does not consume the result at its
// enter-WB, so advance at source readiness (fire-and-forget) rather than the
// vector completion watermark, matching RTL (retires d1 back-to-back).
perfModel->vectorBatchHandModel.setWbRetireAnyway(true);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroup
uint64_t n_uA_V_DISP_Req_MaxVdGroup;
n_uA_V_DISP_Req_MaxVdGroup = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroup()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroup, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_SET;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul(); batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_SET_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_SET
n_V2_SET = n_V2_Unpack_stg + 5;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_SET, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_SET_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, (n_V2_Unpack_stg < n_EX_stg) ? (n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()) : n_V2_Unpack_stg));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
// Restore the default (completion-gated) retire policy for the next op.
perfModel->vectorBatchHandModel.setWbRetireAnyway(false);
}

void V_vmv_regs(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
// Register-to-register vector move is a data move: fire-and-forget retire.
perfModel->vectorBatchHandModel.setWbRetireAnyway(true);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroup
uint64_t n_uA_V_DISP_Req_MaxVdGroup;
n_uA_V_DISP_Req_MaxVdGroup = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroup()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroup, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_ALU_BUF_OP;
uint64_t n_V2_ALU_BUF_OP_stg;
uint64_t n_V2_ALU_BUF_INT;
uint64_t n_V2_ALU_BUF_INT_stg;
uint64_t n_V2_ALU_BUF_RES;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getNfSimm5(); batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_ALU_BUF_OP_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_ALU_BUF_OP
n_V2_ALU_BUF_OP = n_V2_Unpack_stg + perfModel->vectorFixedDelayV2.getDelay();
// V2_ALU_BUF_OP_stg
n_V2_ALU_BUF_OP_stg = std::max({n_V2_ALU_BUF_OP, perfModel->V2_ALU_BUF_INT_stg});
perfModel->V2_ALU_BUF_OP_stg = n_V2_ALU_BUF_OP_stg;
// V2_ALU_BUF_INT
n_V2_ALU_BUF_INT = n_V2_ALU_BUF_OP_stg + 1;
// V2_ALU_BUF_INT_stg
n_V2_ALU_BUF_INT_stg = std::max({n_V2_ALU_BUF_INT, perfModel->V2_ALU_BUF_RES_stg});
perfModel->V2_ALU_BUF_INT_stg = n_V2_ALU_BUF_INT_stg;
// V2_ALU_BUF_RES
n_V2_ALU_BUF_RES = n_V2_ALU_BUF_INT_stg + 1;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_ALU_BUF_RES, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_ALU_BUF_RES_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, (n_V2_Unpack_stg < n_EX_stg) ? (n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()) : n_V2_Unpack_stg));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
perfModel->vectorBatchHandModel.setWbRetireAnyway(false);
}

void V_vmv_s_x(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
// Scalar-to-vector move is a data move: fire-and-forget retire.
perfModel->vectorBatchHandModel.setWbRetireAnyway(true);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroup
uint64_t n_uA_V_DISP_Req_MaxVdGroup;
n_uA_V_DISP_Req_MaxVdGroup = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroup()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroup, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_ALU_BUF_OP;
uint64_t n_V2_ALU_BUF_OP_stg;
uint64_t n_V2_ALU_BUF_INT;
uint64_t n_V2_ALU_BUF_INT_stg;
uint64_t n_V2_ALU_BUF_RES;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.one(); batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_ALU_BUF_OP_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_ALU_BUF_OP
n_V2_ALU_BUF_OP = n_V2_Unpack_stg + perfModel->vectorFixedDelayV2.getDelay();
// V2_ALU_BUF_OP_stg
n_V2_ALU_BUF_OP_stg = std::max({n_V2_ALU_BUF_OP, perfModel->V2_ALU_BUF_INT_stg});
perfModel->V2_ALU_BUF_OP_stg = n_V2_ALU_BUF_OP_stg;
// V2_ALU_BUF_INT
n_V2_ALU_BUF_INT = n_V2_ALU_BUF_OP_stg + 1;
// V2_ALU_BUF_INT_stg
n_V2_ALU_BUF_INT_stg = std::max({n_V2_ALU_BUF_INT, perfModel->V2_ALU_BUF_RES_stg});
perfModel->V2_ALU_BUF_INT_stg = n_V2_ALU_BUF_INT_stg;
// V2_ALU_BUF_RES
n_V2_ALU_BUF_RES = n_V2_ALU_BUF_INT_stg + 1;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_ALU_BUF_RES, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_ALU_BUF_RES_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, (n_V2_Unpack_stg < n_EX_stg) ? (n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()) : n_V2_Unpack_stg));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
perfModel->vectorBatchHandModel.setWbRetireAnyway(false);
}

void V_vmv_x_s(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_XRESULT;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack_FreeWb;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.one(); batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_XRESULT_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_XRESULT
n_V2_XRESULT = n_V2_Unpack_stg + 1;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_XRESULT, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_XRESULT_stg = n_V2_Subpipe;
// V2_Pack_FreeWb
n_V2_Pack_FreeWb = n_V2_Subpipe + 1;
// vector->scalar write-back: the scalar X-reg result crosses the vector/scalar
// boundary, so the scalar WB port is not free until V2_Pack (V2_Pack_FreeWb+6,
// where V2_Pack_FreeWb = Unpack+2). setWbFreeSignal adds +1, so pass +5. RTL
// ground truth: an independent op after vmv.x.s retires d+12 (=Unpack+8) and a
// dependent consumer sees the scalar value at the same V2_Pack point (d+6).
perfModel->vectorBatchHandModel.setWbFreeSignal(n_V2_Pack_FreeWb + 5);
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack_FreeWb;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_Div_vv(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getVectorRetireGate()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroup
uint64_t n_uA_V_DISP_Req_MaxVdGroup;
n_uA_V_DISP_Req_MaxVdGroup = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroup()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroup, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_DIV
// Batched Pipeline Variables
uint64_t n_V2_Unpack_DIV;
uint64_t n_uA_V2_Unpack_Req_Vs1;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_DIV;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul(); batch_i++) {
n_V2_Unpack_DIV = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs1
n_uA_V2_Unpack_Req_Vs1 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs1(batch_i)});
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_DIV, n_uA_V2_Unpack_Req_Vs1, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_DIV_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_DIV
n_V2_DIV = n_V2_Unpack_stg + 5;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_DIV, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_DIV_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()),std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_Div_vx(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getVectorRetireGate()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroup
uint64_t n_uA_V_DISP_Req_MaxVdGroup;
n_uA_V_DISP_Req_MaxVdGroup = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroup()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroup, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_DIV
// Batched Pipeline Variables
uint64_t n_V2_Unpack_DIV;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_DIV;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul(); batch_i++) {
n_V2_Unpack_DIV = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_DIV, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_DIV_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_DIV
n_V2_DIV = n_V2_Unpack_stg + 5;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_DIV, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_DIV_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()),std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_ALU_vv(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getVectorRetireGate()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroup
uint64_t n_uA_V_DISP_Req_MaxVdGroup;
n_uA_V_DISP_Req_MaxVdGroup = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroup()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroup, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs1;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_ALU_BUF_OP;
uint64_t n_V2_ALU_BUF_OP_stg;
uint64_t n_V2_ALU_BUF_INT;
uint64_t n_V2_ALU_BUF_INT_stg;
uint64_t n_V2_ALU_BUF_RES;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul(); batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs1
n_uA_V2_Unpack_Req_Vs1 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs1(batch_i)});
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs1, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_ALU_BUF_OP_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_ALU_BUF_OP
n_V2_ALU_BUF_OP = n_V2_Unpack_stg + perfModel->vectorFixedDelayV2.getDelay();
// V2_ALU_BUF_OP_stg
n_V2_ALU_BUF_OP_stg = std::max({n_V2_ALU_BUF_OP, perfModel->V2_ALU_BUF_INT_stg});
perfModel->V2_ALU_BUF_OP_stg = n_V2_ALU_BUF_OP_stg;
// V2_ALU_BUF_INT
n_V2_ALU_BUF_INT = n_V2_ALU_BUF_OP_stg + 1;
// V2_ALU_BUF_INT_stg
n_V2_ALU_BUF_INT_stg = std::max({n_V2_ALU_BUF_INT, perfModel->V2_ALU_BUF_RES_stg});
perfModel->V2_ALU_BUF_INT_stg = n_V2_ALU_BUF_INT_stg;
// V2_ALU_BUF_RES
n_V2_ALU_BUF_RES = n_V2_ALU_BUF_INT_stg + 1;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_ALU_BUF_RES, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_ALU_BUF_RES_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()),std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_ALU_vx(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getVectorRetireGate()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroup
uint64_t n_uA_V_DISP_Req_MaxVdGroup;
n_uA_V_DISP_Req_MaxVdGroup = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroup()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroup, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_ALU_BUF_OP;
uint64_t n_V2_ALU_BUF_OP_stg;
uint64_t n_V2_ALU_BUF_INT;
uint64_t n_V2_ALU_BUF_INT_stg;
uint64_t n_V2_ALU_BUF_RES;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul(); batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_ALU_BUF_OP_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_ALU_BUF_OP
n_V2_ALU_BUF_OP = n_V2_Unpack_stg + perfModel->vectorFixedDelayV2.getDelay();
// V2_ALU_BUF_OP_stg
n_V2_ALU_BUF_OP_stg = std::max({n_V2_ALU_BUF_OP, perfModel->V2_ALU_BUF_INT_stg});
perfModel->V2_ALU_BUF_OP_stg = n_V2_ALU_BUF_OP_stg;
// V2_ALU_BUF_INT
n_V2_ALU_BUF_INT = n_V2_ALU_BUF_OP_stg + 1;
// V2_ALU_BUF_INT_stg
n_V2_ALU_BUF_INT_stg = std::max({n_V2_ALU_BUF_INT, perfModel->V2_ALU_BUF_RES_stg});
perfModel->V2_ALU_BUF_INT_stg = n_V2_ALU_BUF_INT_stg;
// V2_ALU_BUF_RES
n_V2_ALU_BUF_RES = n_V2_ALU_BUF_INT_stg + 1;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_ALU_BUF_RES, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_ALU_BUF_RES_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()),std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_MUL_vv(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getVectorRetireGate()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroup
uint64_t n_uA_V_DISP_Req_MaxVdGroup;
n_uA_V_DISP_Req_MaxVdGroup = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroup()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroup, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs1;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_MUL_BUF_OP;
uint64_t n_V2_MUL_BUF_OP_stg;
uint64_t n_V2_MUL_BUF_IN;
uint64_t n_V2_MUL_BUF_IN_stg;
uint64_t n_V2_MUL_BUF_OUT;
uint64_t n_V2_MUL_BUF_OUT_stg;
uint64_t n_V2_MUL_BUF_RES;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul(); batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs1
n_uA_V2_Unpack_Req_Vs1 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs1(batch_i)});
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs1, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_MUL_BUF_OP_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_MUL_BUF_OP
n_V2_MUL_BUF_OP = n_V2_Unpack_stg + perfModel->vectorFixedDelayV2.getDelay();
// V2_MUL_BUF_OP_stg
n_V2_MUL_BUF_OP_stg = std::max({n_V2_MUL_BUF_OP, perfModel->V2_MUL_BUF_IN_stg});
perfModel->V2_MUL_BUF_OP_stg = n_V2_MUL_BUF_OP_stg;
// V2_MUL_BUF_IN
n_V2_MUL_BUF_IN = n_V2_MUL_BUF_OP_stg + 1;
// V2_MUL_BUF_IN_stg
n_V2_MUL_BUF_IN_stg = std::max({n_V2_MUL_BUF_IN, perfModel->V2_MUL_BUF_OUT_stg});
perfModel->V2_MUL_BUF_IN_stg = n_V2_MUL_BUF_IN_stg;
// V2_MUL_BUF_OUT
n_V2_MUL_BUF_OUT = n_V2_MUL_BUF_IN_stg + 1;
// V2_MUL_BUF_OUT_stg
n_V2_MUL_BUF_OUT_stg = std::max({n_V2_MUL_BUF_OUT, perfModel->V2_MUL_BUF_RES_stg});
perfModel->V2_MUL_BUF_OUT_stg = n_V2_MUL_BUF_OUT_stg;
// V2_MUL_BUF_RES
n_V2_MUL_BUF_RES = n_V2_MUL_BUF_OUT_stg + 1;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_MUL_BUF_RES, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_MUL_BUF_RES_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()),std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_ALU_Widening_vv(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getVectorRetireGate()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroupWide
uint64_t n_uA_V_DISP_Req_MaxVdGroupWide;
n_uA_V_DISP_Req_MaxVdGroupWide = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroupWide()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroupWide, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs1;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_ALU_BUF_OP;
uint64_t n_V2_ALU_BUF_OP_stg;
uint64_t n_V2_ALU_BUF_INT;
uint64_t n_V2_ALU_BUF_INT_stg;
uint64_t n_V2_ALU_BUF_RES;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul() * 2; batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs1
n_uA_V2_Unpack_Req_Vs1 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs1(batch_i)});
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs1, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_ALU_BUF_OP_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_ALU_BUF_OP
n_V2_ALU_BUF_OP = n_V2_Unpack_stg + perfModel->vectorFixedDelayV2.getDelay();
// V2_ALU_BUF_OP_stg
n_V2_ALU_BUF_OP_stg = std::max({n_V2_ALU_BUF_OP, perfModel->V2_ALU_BUF_INT_stg});
perfModel->V2_ALU_BUF_OP_stg = n_V2_ALU_BUF_OP_stg;
// V2_ALU_BUF_INT
n_V2_ALU_BUF_INT = n_V2_ALU_BUF_OP_stg + 1;
// V2_ALU_BUF_INT_stg
n_V2_ALU_BUF_INT_stg = std::max({n_V2_ALU_BUF_INT, perfModel->V2_ALU_BUF_RES_stg});
perfModel->V2_ALU_BUF_INT_stg = n_V2_ALU_BUF_INT_stg;
// V2_ALU_BUF_RES
n_V2_ALU_BUF_RES = n_V2_ALU_BUF_INT_stg + 1;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_ALU_BUF_RES, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_ALU_BUF_RES_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()),std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_MUL_Widening_vv(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getVectorRetireGate()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroupWide
uint64_t n_uA_V_DISP_Req_MaxVdGroupWide;
n_uA_V_DISP_Req_MaxVdGroupWide = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroupWide()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroupWide, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs1;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_MUL_BUF_OP;
uint64_t n_V2_MUL_BUF_OP_stg;
uint64_t n_V2_MUL_BUF_IN;
uint64_t n_V2_MUL_BUF_IN_stg;
uint64_t n_V2_MUL_BUF_OUT;
uint64_t n_V2_MUL_BUF_OUT_stg;
uint64_t n_V2_MUL_BUF_RES;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul() * 2; batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs1
n_uA_V2_Unpack_Req_Vs1 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs1(batch_i)});
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs1, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_MUL_BUF_OP_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_MUL_BUF_OP
n_V2_MUL_BUF_OP = n_V2_Unpack_stg + perfModel->vectorFixedDelayV2.getDelay();
// V2_MUL_BUF_OP_stg
n_V2_MUL_BUF_OP_stg = std::max({n_V2_MUL_BUF_OP, perfModel->V2_MUL_BUF_IN_stg});
perfModel->V2_MUL_BUF_OP_stg = n_V2_MUL_BUF_OP_stg;
// V2_MUL_BUF_IN
n_V2_MUL_BUF_IN = n_V2_MUL_BUF_OP_stg + 1;
// V2_MUL_BUF_IN_stg
n_V2_MUL_BUF_IN_stg = std::max({n_V2_MUL_BUF_IN, perfModel->V2_MUL_BUF_OUT_stg});
perfModel->V2_MUL_BUF_IN_stg = n_V2_MUL_BUF_IN_stg;
// V2_MUL_BUF_OUT
n_V2_MUL_BUF_OUT = n_V2_MUL_BUF_IN_stg + 1;
// V2_MUL_BUF_OUT_stg
n_V2_MUL_BUF_OUT_stg = std::max({n_V2_MUL_BUF_OUT, perfModel->V2_MUL_BUF_RES_stg});
perfModel->V2_MUL_BUF_OUT_stg = n_V2_MUL_BUF_OUT_stg;
// V2_MUL_BUF_RES
n_V2_MUL_BUF_RES = n_V2_MUL_BUF_OUT_stg + 1;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_MUL_BUF_RES, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_MUL_BUF_RES_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()),std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_MUL_vx(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getVectorRetireGate()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroup
uint64_t n_uA_V_DISP_Req_MaxVdGroup;
n_uA_V_DISP_Req_MaxVdGroup = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroup()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroup, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_MUL_BUF_OP;
uint64_t n_V2_MUL_BUF_OP_stg;
uint64_t n_V2_MUL_BUF_IN;
uint64_t n_V2_MUL_BUF_IN_stg;
uint64_t n_V2_MUL_BUF_OUT;
uint64_t n_V2_MUL_BUF_OUT_stg;
uint64_t n_V2_MUL_BUF_RES;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul(); batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_MUL_BUF_OP_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_MUL_BUF_OP
n_V2_MUL_BUF_OP = n_V2_Unpack_stg + perfModel->vectorFixedDelayV2.getDelay();
// V2_MUL_BUF_OP_stg
n_V2_MUL_BUF_OP_stg = std::max({n_V2_MUL_BUF_OP, perfModel->V2_MUL_BUF_IN_stg});
perfModel->V2_MUL_BUF_OP_stg = n_V2_MUL_BUF_OP_stg;
// V2_MUL_BUF_IN
n_V2_MUL_BUF_IN = n_V2_MUL_BUF_OP_stg + 1;
// V2_MUL_BUF_IN_stg
n_V2_MUL_BUF_IN_stg = std::max({n_V2_MUL_BUF_IN, perfModel->V2_MUL_BUF_OUT_stg});
perfModel->V2_MUL_BUF_IN_stg = n_V2_MUL_BUF_IN_stg;
// V2_MUL_BUF_OUT
n_V2_MUL_BUF_OUT = n_V2_MUL_BUF_IN_stg + 1;
// V2_MUL_BUF_OUT_stg
n_V2_MUL_BUF_OUT_stg = std::max({n_V2_MUL_BUF_OUT, perfModel->V2_MUL_BUF_RES_stg});
perfModel->V2_MUL_BUF_OUT_stg = n_V2_MUL_BUF_OUT_stg;
// V2_MUL_BUF_RES
n_V2_MUL_BUF_RES = n_V2_MUL_BUF_OUT_stg + 1;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_MUL_BUF_RES, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_MUL_BUF_RES_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()),std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_ALU_Widening_vx(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getVectorRetireGate()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroupWide
uint64_t n_uA_V_DISP_Req_MaxVdGroupWide;
n_uA_V_DISP_Req_MaxVdGroupWide = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroupWide()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroupWide, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_ALU_BUF_OP;
uint64_t n_V2_ALU_BUF_OP_stg;
uint64_t n_V2_ALU_BUF_INT;
uint64_t n_V2_ALU_BUF_INT_stg;
uint64_t n_V2_ALU_BUF_RES;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul() * 2; batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_ALU_BUF_OP_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_ALU_BUF_OP
n_V2_ALU_BUF_OP = n_V2_Unpack_stg + perfModel->vectorFixedDelayV2.getDelay();
// V2_ALU_BUF_OP_stg
n_V2_ALU_BUF_OP_stg = std::max({n_V2_ALU_BUF_OP, perfModel->V2_ALU_BUF_INT_stg});
perfModel->V2_ALU_BUF_OP_stg = n_V2_ALU_BUF_OP_stg;
// V2_ALU_BUF_INT
n_V2_ALU_BUF_INT = n_V2_ALU_BUF_OP_stg + 1;
// V2_ALU_BUF_INT_stg
n_V2_ALU_BUF_INT_stg = std::max({n_V2_ALU_BUF_INT, perfModel->V2_ALU_BUF_RES_stg});
perfModel->V2_ALU_BUF_INT_stg = n_V2_ALU_BUF_INT_stg;
// V2_ALU_BUF_RES
n_V2_ALU_BUF_RES = n_V2_ALU_BUF_INT_stg + 1;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_ALU_BUF_RES, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_ALU_BUF_RES_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()),std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_MUL_Widening_vx(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getVectorRetireGate()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroupWide
uint64_t n_uA_V_DISP_Req_MaxVdGroupWide;
n_uA_V_DISP_Req_MaxVdGroupWide = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroupWide()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroupWide, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_MUL_BUF_OP;
uint64_t n_V2_MUL_BUF_OP_stg;
uint64_t n_V2_MUL_BUF_IN;
uint64_t n_V2_MUL_BUF_IN_stg;
uint64_t n_V2_MUL_BUF_OUT;
uint64_t n_V2_MUL_BUF_OUT_stg;
uint64_t n_V2_MUL_BUF_RES;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul() * 2; batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_MUL_BUF_OP_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_MUL_BUF_OP
n_V2_MUL_BUF_OP = n_V2_Unpack_stg + perfModel->vectorFixedDelayV2.getDelay();
// V2_MUL_BUF_OP_stg
n_V2_MUL_BUF_OP_stg = std::max({n_V2_MUL_BUF_OP, perfModel->V2_MUL_BUF_IN_stg});
perfModel->V2_MUL_BUF_OP_stg = n_V2_MUL_BUF_OP_stg;
// V2_MUL_BUF_IN
n_V2_MUL_BUF_IN = n_V2_MUL_BUF_OP_stg + 1;
// V2_MUL_BUF_IN_stg
n_V2_MUL_BUF_IN_stg = std::max({n_V2_MUL_BUF_IN, perfModel->V2_MUL_BUF_OUT_stg});
perfModel->V2_MUL_BUF_IN_stg = n_V2_MUL_BUF_IN_stg;
// V2_MUL_BUF_OUT
n_V2_MUL_BUF_OUT = n_V2_MUL_BUF_IN_stg + 1;
// V2_MUL_BUF_OUT_stg
n_V2_MUL_BUF_OUT_stg = std::max({n_V2_MUL_BUF_OUT, perfModel->V2_MUL_BUF_RES_stg});
perfModel->V2_MUL_BUF_OUT_stg = n_V2_MUL_BUF_OUT_stg;
// V2_MUL_BUF_RES
n_V2_MUL_BUF_RES = n_V2_MUL_BUF_OUT_stg + 1;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_MUL_BUF_RES, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_MUL_BUF_RES_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()),std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_ALU_vi(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getVectorRetireGate()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroup
uint64_t n_uA_V_DISP_Req_MaxVdGroup;
n_uA_V_DISP_Req_MaxVdGroup = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroup()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroup, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_ALU_BUF_OP;
uint64_t n_V2_ALU_BUF_OP_stg;
uint64_t n_V2_ALU_BUF_INT;
uint64_t n_V2_ALU_BUF_INT_stg;
uint64_t n_V2_ALU_BUF_RES;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul(); batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_ALU_BUF_OP_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_ALU_BUF_OP
n_V2_ALU_BUF_OP = n_V2_Unpack_stg + perfModel->vectorFixedDelayV2.getDelay();
// V2_ALU_BUF_OP_stg
n_V2_ALU_BUF_OP_stg = std::max({n_V2_ALU_BUF_OP, perfModel->V2_ALU_BUF_INT_stg});
perfModel->V2_ALU_BUF_OP_stg = n_V2_ALU_BUF_OP_stg;
// V2_ALU_BUF_INT
n_V2_ALU_BUF_INT = n_V2_ALU_BUF_OP_stg + 1;
// V2_ALU_BUF_INT_stg
n_V2_ALU_BUF_INT_stg = std::max({n_V2_ALU_BUF_INT, perfModel->V2_ALU_BUF_RES_stg});
perfModel->V2_ALU_BUF_INT_stg = n_V2_ALU_BUF_INT_stg;
// V2_ALU_BUF_RES
n_V2_ALU_BUF_RES = n_V2_ALU_BUF_INT_stg + 1;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_ALU_BUF_RES, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_ALU_BUF_RES_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()),std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_ELEM(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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

void V_REDSUM(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getVectorRetireGate()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroup
uint64_t n_uA_V_DISP_Req_MaxVdGroup;
n_uA_V_DISP_Req_MaxVdGroup = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroup()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroup, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs1;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_REDSUM;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul(); batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs1
n_uA_V2_Unpack_Req_Vs1 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs1(batch_i)});
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs1, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_REDSUM_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_REDSUM
n_V2_REDSUM = n_V2_Unpack_stg + 5;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_REDSUM, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_REDSUM_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency(),n_EX_stg + 4 + 4 * perfModel->vectorBatchHandModel.getLmul() - perfModel->vectorBatchHandModel.getSewByteShift());
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_REDMINMAX(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getVectorRetireGate()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroup
uint64_t n_uA_V_DISP_Req_MaxVdGroup;
n_uA_V_DISP_Req_MaxVdGroup = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroup()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroup, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs1;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_REDMINMAX;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul(); batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs1
n_uA_V2_Unpack_Req_Vs1 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs1(batch_i)});
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs1, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_REDMINMAX_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_REDMINMAX
n_V2_REDMINMAX = n_V2_Unpack_stg + 5;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_REDMINMAX, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_REDMINMAX_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency(),n_EX_stg + 4 + 4 * perfModel->vectorBatchHandModel.getLmul() - perfModel->vectorBatchHandModel.getSewByteShift());
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_XRESULT(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbFreeSignal()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_XRESULT;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack_FreeWb;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.one(); batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_XRESULT_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_XRESULT
n_V2_XRESULT = n_V2_Unpack_stg + 1;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_XRESULT, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_XRESULT_stg = n_V2_Subpipe;
// V2_Pack_FreeWb
n_V2_Pack_FreeWb = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setWbFreeSignal(n_V2_Pack_FreeWb);
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack_FreeWb;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_INDEX(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg;
n_V_ID_stg = std::max({n_V_ID_Decoder, perfModel->V_IQ_stg.get(2)});
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getVectorRetireGate()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// V_IQ_Queue
uint64_t n_V_IQ_Queue;
n_V_IQ_Queue = n_V_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// V_IQ_stg
uint64_t n_V_IQ_stg;
n_V_IQ_stg = std::max({n_V_IQ_Queue, perfModel->V_IQ_stg.get(1), perfModel->V_DISP_stg});
perfModel->V_IQ_stg.set(n_V_IQ_stg);
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// Dispatcher
uint64_t n_Dispatcher;
n_Dispatcher = n_V_IQ_stg + 1;
// uA_V_DISP_Req_MaxVdGroup
uint64_t n_uA_V_DISP_Req_MaxVdGroup;
n_uA_V_DISP_Req_MaxVdGroup = std::max({n_V_IQ_stg, perfModel->vectorBatchHandModel.getMaxVdGroup()});
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;
// V_DISP_stg
uint64_t n_V_DISP_stg;
n_V_DISP_stg = std::max({n_Dispatcher, n_uA_V_DISP_Req_MaxVdGroup, perfModel->V2_Unpack_stg});
perfModel->V_DISP_stg = n_V_DISP_stg;
// V2_Unpack_Fixed
// Batched Pipeline Variables
uint64_t n_V2_Unpack_Fixed;
uint64_t n_uA_V2_Unpack_Req_Vs2;
uint64_t n_V2_Unpack_stg;
uint64_t n_V2_INDEX;
uint64_t n_V2_Subpipe;
uint64_t n_V2_Pack;
// Batched Pipeline Calculation Loop
for (size_t batch_i = 0; batch_i < perfModel->vectorBatchHandModel.getLmul(); batch_i++) {
n_V2_Unpack_Fixed = (batch_i == 0 ? n_V_DISP_stg : n_V2_Unpack_stg);
// uA_V2_Unpack_Req_Vs2
n_uA_V2_Unpack_Req_Vs2 = std::max({n_V_DISP_stg, perfModel->vectorBatchHandModel.getVs2(batch_i)});
// V2_Unpack_stg
n_V2_Unpack_stg = std::max({n_V2_Unpack_Fixed, n_uA_V2_Unpack_Req_Vs2, (batch_i == 0) * (perfModel->V2_Subpipe + 1), perfModel->V2_INDEX_stg});
perfModel->V2_Unpack_stg = n_V2_Unpack_stg;
// V2_INDEX
n_V2_INDEX = n_V2_Unpack_stg + 5;
// V2_Subpipe
n_V2_Subpipe = std::max({n_V2_INDEX, perfModel->V2_Pack_stg});
perfModel->V2_Subpipe = n_V2_Subpipe;
perfModel->V2_INDEX_stg = n_V2_Subpipe;
// V2_Pack
n_V2_Pack = n_V2_Subpipe + 1;
perfModel->vectorBatchHandModel.setVd(batch_i,n_V2_Pack + 1,std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()),std::max(n_V2_Unpack_stg, n_EX_stg + perfModel->vectorBatchHandModel.getRetireLatency()));
// V2_Pack_stg
uint64_t n_V2_Pack_stg = n_V2_Pack;
perfModel->V2_Pack_stg = n_V2_Pack_stg;
}
// End Batch Loop
}

void V_SLD(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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

void V_vsetivli(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg = n_V_ID_Decoder;
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbSignal()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;

}

void V_vsetvli(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg = n_V_ID_Decoder;
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbSignal()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;

}

void V_vsetvl(PerformanceModel *perfModel_) {
Vicuna_zvl128b_PerformanceModel *perfModel = static_cast<Vicuna_zvl128b_PerformanceModel *>(perfModel_);
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
// uA_IF_Req_VsetSignal
uint64_t n_uA_IF_Req_VsetSignal;
n_uA_IF_Req_VsetSignal = std::max({n_Enter, perfModel->vectorBatchHandModel.getVsetSignal()});
// IF_stg
uint64_t n_IF_stg;
n_IF_stg = std::max({n_IPort_R, n_PCGen, n_uA_IF_Req_VsetSignal, perfModel->ID_stg, perfModel->V_ID_stg});
perfModel->IF_stg = n_IF_stg;
// Decoder
uint64_t n_Decoder;
n_Decoder = n_IF_stg + 1;
// V_ID_Decoder
uint64_t n_V_ID_Decoder;
n_V_ID_Decoder = n_IF_stg + 1;
// ID_stg
uint64_t n_ID_stg;
n_ID_stg = std::max({n_Decoder, perfModel->EX_stg});
perfModel->ID_stg = n_ID_stg;
// V_ID_stg
uint64_t n_V_ID_stg = n_V_ID_Decoder;
perfModel->V_ID_stg = n_V_ID_stg;
// uA_EX_Req_WbFreeSignal
uint64_t n_uA_EX_Req_WbFreeSignal;
n_uA_EX_Req_WbFreeSignal = std::max({n_ID_stg, perfModel->vectorBatchHandModel.getWbSignal()});
// EX_Nop
uint64_t n_EX_Nop;
n_EX_Nop = n_ID_stg + 1;
// EX_stg
uint64_t n_EX_stg;
n_EX_stg = std::max({n_uA_EX_Req_WbFreeSignal, n_EX_Nop, perfModel->WB_stg});
perfModel->EX_stg = n_EX_stg;
// WB_Nop
uint64_t n_WB_Nop;
n_WB_Nop = n_EX_stg + 1;
// WB_stg
uint64_t n_WB_stg = n_WB_Nop;
perfModel->WB_stg = n_WB_stg;

}

} // Namespace