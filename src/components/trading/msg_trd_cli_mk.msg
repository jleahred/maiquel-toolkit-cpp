BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "msg_trd_common.h"']

END_INIT








//  QUEUES
//  SUBJ:RQ.client.market.product_code
//  SUBJ:CONF.client.market.product_code



//---------------------------------------------------------------------
//    COMMON ORDERS MK
//---------------------------------------------------------------------

sub_position_mk   [<V:0>]
{ 
    quantity (qt)   :   fix_num
}




//---------------------------------------------------------------------
//	request MK


RQ_XX_MK  [<V:0,   I:RQ_XX   >]
{
    request_pos         (rp)   :   sub_position_mk
}



RQ_NW_MK  [< V:0, I:RQ_XX_MK,    SUBJ:RQ.${req_info.process_info.location.client_code}.${invariant.product_code.market}.${invariant.product_code.product} >]   {}


RQ_MD_MK  [< V:0, I:RQ_XX_MK,    SUBJ:RQ.${req_info.process_info.location.client_code}.${invariant.product_code.market}.${invariant.product_code.product} >]   {}


RQ_CC_MK  [< V:0, I:RQ_XX_MK,    SUBJ:RQ.${req_info.process_info.location.client_code}.${invariant.product_code.market}.${invariant.product_code.product} >]   {}



//---------------------------------------------------------------------
//	confirmations  MK

CF_XX_MK  [< V:0,  I:CF_XX >]
{
    market_pos     (mp)   :   sub_position_mk
}


CF_NW_MK  [< V:0,  I:CF_XX_MK,  SUBJ:CONF.${req_info.process_info.location.client_code}.${invariant.product_code.market}.${invariant.product_code.product}   >]   {}


CF_MD_MK  [< V:0,  I:CF_XX_MK,  SUBJ:CONF.${req_info.process_info.location.client_code}.${invariant.product_code.market}.${invariant.product_code.product}   >]   {}


CF_CC_MK  [< V:0,  I:CF_XX_MK,  SUBJ:CONF.${req_info.process_info.location.client_code}.${invariant.product_code.market}.${invariant.product_code.product}   >]   {}




//---------------------------------------------------------------------
//	executions  MK

CF_EX_MK  [< V:0, I:CF_XX_MK,  SUBJ:CONF.${req_info.process_info.location.client_code}.${invariant.product_code.market}.${invariant.product_code.product}   >]
{
    executed_pos  (exc)   :  sub_exec_conf
}





//---------------------------------------------------------------------
//	rejects  MK


RJ_NW_MK  [< V:0, I:CF_XX_MK,   SUBJ:CONF.${req_info.process_info.location.client_code}.${invariant.product_code.market}.${invariant.product_code.product}  >]
{
    reject_description  (rd)    :   string
}


RJ_MD_MK  [< V:0, I:CF_XX_MK,   SUBJ:CONF.${req_info.process_info.location.client_code}.${invariant.product_code.market}.${invariant.product_code.product}  >]
{
    reject_description  (rd)    :   string
}


RJ_CC_MK  [< V:0, I:CF_XX_MK,   SUBJ:CONF.${req_info.process_info.location.client_code}.${invariant.product_code.market}.${invariant.product_code.product}  >]
{
    reject_description  (rd)    :   string
}


