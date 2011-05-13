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
    side     (sd)   :   enBuySell
}



sub_order_mk_confirmated [<  V:0, I:sub_order_xx_confirmated  >]
{
    market_pos     (mp)   :   sub_position_mk
}



//---------------------------------------------------------------------
//	request MK


RQ_XX_MK  [<V:0,   I:RQ_XX   >]
{
    request_pos         (rp)   :   sub_position_mk
}



RQ_NW_MK  [< V:0, I:RQ_XX_MK,    SUBJ:RQ.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product} >]   {}


RQ_MD_MK  [< V:0, I:RQ_XX_MK,    SUBJ:RQ.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product} >]   {}


RQ_CC_MK  [< V:0, I:RQ_XX_MK,    SUBJ:RQ.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product} >]   {}



//---------------------------------------------------------------------
//	confirmations  MK

CF_XX_MK  [< V:0,  I:CF_XX >]
{
    confirmated_info    (ci)   :   sub_order_mk_confirmated
}


CF_NW_MK  [< V:0,  I:CF_XX_MK,  SUBJ:CONF.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product}   >]   {}


CF_MD_MK  [< V:0,  I:CF_XX_MK,  SUBJ:CONF.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product}   >]   {}


CF_CC_MK  [< V:0,  I:CF_XX_MK,  SUBJ:CONF.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product}   >]   {}




//---------------------------------------------------------------------
//	executions  MK

CF_EX_MK  [< V:0, I:CF_XX_MK,  SUBJ:CONF.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product}   >]
{
    executed_pos  (exp)   :  sub_exec_conf
}





//---------------------------------------------------------------------
//	rejects  MK

RJ_XX_MK  [< V:0, I:RJ_XX  >]
{
    confirmated_info    (ci)   :   sub_order_mk_confirmated
}


RJ_NW_MK  [< V:0, I:RJ_XX_MK,   SUBJ:CONF.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product}  >]  {}


RJ_MD_MK  [< V:0, I:RJ_XX_MK,   SUBJ:CONF.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product}  >]  {}


RJ_CC_MK  [< V:0, I:RJ_XX_MK,   SUBJ:CONF.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product}  >]  {}


