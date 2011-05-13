BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "support/mtk_double.h"', '#include "msg_trd_common_support.h"']

END_INIT






//---------------------------------------------------------------------
//    COMMON TRADING
//---------------------------------------------------------------------


sub_order_id   [< V:0, I:mtk::msg::sub_request_id  >]   {}




sub_exec_conf   [<V:0>]
{ 
    exec_id  (eid)  :   string
    price    (pr)   :   fix_num
    quantity (qt)   :   fix_num
    side     (sd)   :   enBuySell
}


sub_total_executions [<V:0>]
{
    sum_price_by_qty    (spq)   :  double
    quantity            (aqt)   :  fix_num
    remaining_qty       (rq)    :  fix_num
}






sub_order_xx_confirmated [<V:0>]
{
    order_id       (oid)  :   sub_order_id
    total_execs    (exp)  :   sub_total_executions      
    
    cli_ref        (cr)   :   string
}




//  QUEUES
//  SUBJ:RQ.client.market.product_code
//  SUBJ:RS.client.market.product_code




//---------------------------------------------------------------------
//	request XX


RQ_XX  [< V:0 >]
{
    req_info            (rqid) :   mtk::msg::sub_request_info
    order_id            (oid)  :   sub_order_id
    product_code        (pc)   :   mtk::msg::sub_product_code     
    
    cli_ref             (cr)   :   string
    
    orig_control_fluct  (ocf)  :   mtk::msg::sub_control_fluct
}




//---------------------------------------------------------------------
//	confirmations  XX

CF_XX  [<  V:0  >]
{
    req_info            (rqid) :   mtk::msg::sub_request_info    
    product_code        (pc)   :   mtk::msg::sub_product_code

    orig_control_fluct  (ocf)  :   mtk::msg::sub_control_fluct
}






//---------------------------------------------------------------------
//	rejects  XX

RJ_XX  [< V:0 >]
{
    req_info            (rqid) :   mtk::msg::sub_request_info    
    product_code        (pc)   :   mtk::msg::sub_product_code
    description         (ds)   :   string
    
    orig_control_fluct  (ocf)  :   mtk::msg::sub_control_fluct
}


