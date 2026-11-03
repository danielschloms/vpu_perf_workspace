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


#include "Vicuna_zvl128b_PerformanceModel.h"

#include <stdbool.h>
#include <string>
#include <sstream>
#include <algorithm>

#include "Channel.h"

#include "Vicuna_zvl128b_Channel.h"

#include "models/common/StandardRegisterModel.h"
#include "models/Vicuna2_DS/VectorBatchHandModel.h"
#include "models/common/StaticBranchPredictModel.h"
#include "models/Vicuna2_DS/VectorFixedDelayV1.h"
#include "models/Vicuna2_DS/VectorFixedDelayV2.h"
#include "models/Vicuna2_DS/VectorElmDelay.h"
#include "models/Vicuna2_DS/VectorDivDelay.h"
#include "models/cv32e40p/DividerModel.h"
#include "models/cv32e40p/DividerUnsignedModel.h"

namespace Vicuna_zvl128b{

void Vicuna_zvl128b_PerformanceModel::connectChannel(Channel* channel_)
{
  Vicuna_zvl128b_Channel* channel = static_cast<Vicuna_zvl128b_Channel*>(channel_);

  regModel.rs1_ptr = channel->rs1;
  regModel.rs2_ptr = channel->rs2;
  regModel.rd_ptr = channel->rd;

  vectorBatchHandModel.vs1_ptr = channel->vs1;
  vectorBatchHandModel.vs2_ptr = channel->vs2;
  vectorBatchHandModel.vs3_ptr = channel->vs3;
  vectorBatchHandModel.vd_ptr = channel->vd;
  vectorBatchHandModel.vtype_ptr = channel->vtype;
  vectorBatchHandModel.lsWidth_ptr = channel->lsWidth;
  vectorBatchHandModel.nf_ptr = channel->nf;
  vectorBatchHandModel.simm5_ptr = channel->simm5;

  staBranchPredModel.pc_ptr = channel->pc;
  staBranchPredModel.brTarget_ptr = channel->brTarget;



  vectorElmDelay.vtype_ptr = channel->vtype;

  vectorDivDelay.vtype_ptr = channel->vtype;

  divider.rs2_data_ptr = channel->rs2_data;

  divider_u.rs2_data_ptr = channel->rs2_data;

}

uint64_t Vicuna_zvl128b_PerformanceModel::getCycleCount(void)
{
  
  return std::max({
    IF_stg 
    ,ID_stg
    ,EX_stg
    ,WB_stg
    ,V_ID_stg
    ,V_IQ_stg.get(1)
    ,V_DISP_stg
    ,V1_Unpack_stg
    ,V1_Subpipe
    ,V1_LSU_BUF_REQ_stg
    ,V1_LSU_MemAccess_stg
    ,V1_LSU_BUF_RESP_stg
    ,V1_Pack_stg
    ,V2_Unpack_stg
    ,V2_Subpipe
    ,V2_ALU_BUF_OP_stg
    ,V2_ALU_BUF_INT_stg
    ,V2_ALU_BUF_RES_stg
    ,V2_MUL_BUF_OP_stg
    ,V2_MUL_BUF_IN_stg
    ,V2_MUL_BUF_OUT_stg
    ,V2_MUL_BUF_RES_stg
    ,V2_DIV_stg
    ,V2_ELEM_stg
    ,V2_REDSUM_stg
    ,V2_REDMINMAX_stg
    ,V2_INDEX_stg
    ,V2_XRESULT_stg
    ,V2_SLD_stg
    ,V2_SET_stg
    ,V2_Pack_stg
  });
}

std::string Vicuna_zvl128b_PerformanceModel::getPipelineStream(void)
{
  std::stringstream ret_strs;
  
  ret_strs << IF_stg; 
  ret_strs << "," << ID_stg;
  ret_strs << "," << EX_stg;
  ret_strs << "," << WB_stg;
  ret_strs << "," << V_ID_stg;
  ret_strs << "," << V_IQ_stg.get(1);
  ret_strs << "," << V_DISP_stg;
  ret_strs << "," << V1_Unpack_stg;
  ret_strs << "," << V1_Subpipe;
  ret_strs << "," << V1_Pack_stg;
  ret_strs << "," << V2_Unpack_stg;
  ret_strs << "," << V2_Subpipe;
  ret_strs << "," << V2_Pack_stg;
  ret_strs << std::endl;
  return ret_strs.str();
}

std::string Vicuna_zvl128b_PerformanceModel::getPrintHeader(void)
{
  std::stringstream ret_strs;
  
  ret_strs << "IF_stg"; 
  ret_strs << "," << "ID_stg";
  ret_strs << "," << "EX_stg";
  ret_strs << "," << "WB_stg";
  ret_strs << "," << "V_ID_stg";
  ret_strs << "," << "V_IQ_stg";
  ret_strs << "," << "V_DISP_stg";
  ret_strs << "," << "V1_Unpack_stg";
  ret_strs << "," << "V1_Subpipe";
  ret_strs << "," << "V1_Pack_stg";
  ret_strs << "," << "V2_Unpack_stg";
  ret_strs << "," << "V2_Subpipe";
  ret_strs << "," << "V2_Pack_stg";
  ret_strs << std::endl;
  return ret_strs.str();
}

} // namespace Vicuna_zvl128b