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



sub_order_ls_confirmated [<V:0>]
{
    order_id       (oid)  :   sub_order_id
    product_code   (pc)   :   mtk::msg::sub_product_code
    market_pos     (mp)   :   sub_position_ls      
    total_execs    (exp)  :   sub_total_executions      
    
    cli_ref        (cr)   :   string
}



//---------------------------------------------------------------------
//	request LS


RQ_XX_LS  [<V:0,   SUBJ:RQ.${req_info.process_info.location.client_code}.${product_code.market}.${product_code.product} >]
{
    req_info            (rqid) :   mtk::msg::sub_request_info
    order_id            (oid)  :   sub_order_id
    product_code        (pc)   :   mtk::msg::sub_product_code     
    request_pos         (rp)   :   sub_position_ls      
    
    cli_ref             (cr)   :   string
    
    orig_control_fluct  (ocf)  :   mtk::msg::sub_control_fluct
}



RQ_NW_LS  [< V:0, I:RQ_XX_LS >]   {}


RQ_MD_LS  [< V:0, I:RQ_XX_LS  >]   {}


RQ_CC_LS  [< V:0, I:RQ_XX_LS  >]   {}



//---------------------------------------------------------------------
//	confirmations  LS

CF_XX_LS  [< V:0,  SUBJ:RS.${req_info.process_info.location.client_code}.${confirmated_info.product_code.market}.${confirmated_info.product_code.product}  >]
{
    req_info            (rqid) :   mtk::msg::sub_request_info    
    confirmated_info    (ci)   :   sub_order_ls_confirmated

    orig_control_fluct  (ocf)  :   mtk::msg::sub_control_fluct
}


CF_NW_LS  [< V:0,  I:CF_XX_LS  >]  {}


CF_MD_LS  [< V:0,  I:CF_XX_LS  >]  {}


CF_CC_LS  [< V:0,  I:CF_XX_LS  >]  {}




//---------------------------------------------------------------------
//	executions  LS

CF_EX_LS  [< V:0, I:CF_XX_LS   >]
{
    executed_pos  (exp)   :  sub_position_ls
}





//---------------------------------------------------------------------
//	rejects  LS

RJ_XX_LS  [< V:0, SUBJ:RS.${req_info.process_info.location.client_code}.${confirmated_info.product_code.market}.${confirmated_info.product_code.product} >]
{
    req_info            (rqid) :   mtk::msg::sub_request_info    
    confirmated_info    (ci)   :   sub_order_ls_confirmated
    description         (ds)   :   string
    
    orig_control_fluct  (ocf)  :   mtk::msg::sub_control_fluct
}


RJ_NW_LS  [< V:0, I:RJ_XX_LS  >]  {}


RJ_MD_LS  [< V:0, I:RJ_XX_LS  >]  {}


RJ_CC_LS  [< V:0, I:RJ_XX_LS  >]  {}


