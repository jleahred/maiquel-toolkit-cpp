BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "msg_trd_common.h"']

END_INIT








//  QUEUES
//  SUBJ:RQ.client.market.product_code
//  SUBJ:RS.client.market.product_code



//---------------------------------------------------------------------
//    COMMON ORDERS LS
//---------------------------------------------------------------------

sub_position_ls   [<V:0>]
{ 
    price    (pr)   :   fix_num
    quantity (qt)   :   fix_num
    side     (sd)   :   enBuySell
}



sub_order_ls_confirmated [<  V:0, I:sub_order_xx_confirmated  >]
{
    market_pos     (mp)   :   sub_position_ls      
}



//---------------------------------------------------------------------
//	request LS


RQ_XX_LS  [<V:0,   I:RQ_XX   >]
{
    request_pos         (rp)   :   sub_position_ls      
}



RQ_NW_LS  [< V:0, I:RQ_XX_LS,    SUBJ:RQ.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product} >]   {}


RQ_MD_LS  [< V:0, I:RQ_XX_LS,    SUBJ:RQ.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product} >]   {}


RQ_CC_LS  [< V:0, I:RQ_XX_LS,    SUBJ:RQ.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product} >]   {}



//---------------------------------------------------------------------
//	confirmations  LS

CF_XX_LS  [< V:0,  I:CF_XX,      SUBJ:RS.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product} >]
{
    confirmated_info    (ci)   :   sub_order_ls_confirmated
}


CF_NW_LS  [< V:0,  I:CF_XX_LS,  SUBJ:RS.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product}   >]   {}


CF_MD_LS  [< V:0,  I:CF_XX_LS,  SUBJ:RS.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product}   >]   {}


CF_CC_LS  [< V:0,  I:CF_XX_LS,  SUBJ:RS.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product}   >]   {}




//---------------------------------------------------------------------
//	executions  LS

CF_EX_LS  [< V:0, I:CF_XX_LS,  SUBJ:RS.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product}   >]
{
    executed_pos  (exp)   :  sub_position_ls
}





//---------------------------------------------------------------------
//	rejects  LS

RJ_XX_LS  [< V:0, I:RJ_XX,   SUBJ:RS.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product}   >]
{
    confirmated_info    (ci)   :   sub_order_ls_confirmated
}


RJ_NW_LS  [< V:0, I:RJ_XX_LS,   SUBJ:RS.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product}  >]  {}


RJ_MD_LS  [< V:0, I:RJ_XX_LS,   SUBJ:RS.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product}  >]  {}


RJ_CC_LS  [< V:0, I:RJ_XX_LS,   SUBJ:RS.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product}  >]  {}


