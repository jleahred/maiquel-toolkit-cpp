BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "support/mtk_double.h"', '#include "msg_trd_common_support.h"']

END_INIT






//---------------------------------------------------------------------
//    COMMON TRADING
//---------------------------------------------------------------------


sub_order_id   [< I:mtk::msg::sub_request_id  >]   {}




sub_exec_conf   [< >]
{
    exec_id  (eid)  :   string
    price    (pri)  :   fix_num
    quantity (qt)   :   fix_num
}


sub_total_executions [< >]
{
    sum_price_by_qty    (spq)   :  double
    acc_quantity        (aqt)   :  fix_num
    remaining_qty       (rmq)   :  fix_num      //  on confirm cancelation and reject new, it's 0
}



sub_account_info [< LessOP:1, KEY:name >]
{
    name                (nm)    :   string
    client_code         (cc)    :   string
}




sub_invariant_order_info  [< >]
{
    order_id            (oid)  :   sub_order_id
    product_code        (pc)   :   mtk::msg::sub_product_code
    side                (sd)   :   enBuySell
    account             (acc)  :   sub_account_info
    time_in_force       (tf)   :   string       //      DAY  at the moment.   GTC, OPG, IOC, FOK, GTD, ... for future versions
    automatic           (au)   :   bool
}





//  QUEUES
//  SUBJ:RQ.client.market.product_code
//  SUBJ:RS.client.market.product_code




//---------------------------------------------------------------------
//	request XX


RQ_XX  [<  >]
{
    invariant           (inv)  :   sub_invariant_order_info

    request_info        (rqi)  :   mtk::msg::sub_request_info

    orig_control_fluct  (ocf)  :   mtk::msg::sub_control_fluct
}




//---------------------------------------------------------------------
//	confirmations  XX

CF_XX  [< >]
{
    invariant           (inv)  :   sub_invariant_order_info
    market_order_id     (moi)  :   string

    req_id              (rqid) :   mtk::msg::sub_request_id
    total_execs         (ext)  :   sub_total_executions

    description         (desc) :   string       //      on rejects, it will be the reject reason

    orig_control_fluct  (ocf)  :   mtk::msg::sub_control_fluct
}




//---------------------------------------------------------------------
//	REQUEST ORDERS STATUS

RQ_ORDERS_STATUS  [< QE:CLI_MK, SUBJ:MK.${account.client_code}.${market}.RQORDST >]
{
    request_info        (rqi)   :   mtk::msg::sub_request_info

    market              (mk)    :    string
    account             (acc)   :    sub_account_info
}




//---------------------------------------------------------------------
//	LINKED EXECUTION

//  THIS IS NOT AN ORDER CONFIRMATION
//  on this executions the invariant will not be checked. Generally, the product code, side... will be diferent
//  total execs has to be empty

CF_EXLK  [< I:CF_XX,  QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD   >]
{
    executed_pos  (exp)   :  sub_exec_conf
}
