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
    price    (pri)  :   fix_num
    quantity (qt)   :   fix_num
    side     (sd)   :   enBuySell
}


sub_total_executions [<V:0>]
{
    sum_price_by_qty    (spq)   :  double
    acc_quantity        (aqt)   :  fix_num
    remaining_qty       (rmq)   :  fix_num
}



sub_account_info [< V:0, LessOP:1 >]
{
    client_code         (cc)    :   string
    name                (nm)    :   string
}




sub_invariant_order_info  [<V:0>]
{
    order_id            (oid)  :   sub_order_id
    product_code        (pc)   :   mtk::msg::sub_product_code     
    side                (sd)   :   enBuySell
    account             (acc)  :   sub_account_info
}





//  QUEUES
//  SUBJ:RQ.client.market.product_code
//  SUBJ:RS.client.market.product_code




//---------------------------------------------------------------------
//	request XX


RQ_XX  [< V:0 >]
{
    invariant           (inv)  :   sub_invariant_order_info

    req_info            (rqin) :   mtk::msg::sub_request_info
    cli_ref             (clr)  :   string
    
    orig_control_fluct  (ocf)  :   mtk::msg::sub_control_fluct
}




//---------------------------------------------------------------------
//	confirmations  XX

CF_XX  [<  V:0  >]
{
    invariant           (inv)  :   sub_invariant_order_info
    market_order_id     (moi)  :   string
    
    req_id              (rqid) :   mtk::msg::sub_request_id
    cli_ref             (clr)  :   string
    total_execs         (ext)  :   sub_total_executions      

    orig_control_fluct  (ocf)  :   mtk::msg::sub_control_fluct
}




