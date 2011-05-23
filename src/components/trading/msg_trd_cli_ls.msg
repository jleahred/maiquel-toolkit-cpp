BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "msg_trd_common.h"']

END_INIT








//  QUEUES
//  SUBJ:RQ.client.market.product_code
//  SUBJ:CONF.client.market.product_code



//---------------------------------------------------------------------
//    COMMON ORDERS LS
//---------------------------------------------------------------------


sub_position_ls   [<V:0>]
{ 
    price    (pr)   :   fix_num
    quantity (qt)   :   fix_num
}






//---------------------------------------------------------------------
//	request LS


RQ_XX_LS  [<V:0,   I:RQ_XX   >]
{
    request_pos         (rp)   :   sub_position_ls      
}



RQ_NW_LS  [< V:0, I:RQ_XX_LS,    SUBJ:RQ.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.product_code.product} >]   {}


RQ_MD_LS  [< V:0, I:RQ_XX_LS,    SUBJ:RQ.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.product_code.product} >]   {}


RQ_CC_LS  [< V:0, I:RQ_XX_LS,    SUBJ:RQ.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.product_code.product} >]   {}



//---------------------------------------------------------------------
//	confirmations  LS

CF_XX_LS  [< V:0,  I:CF_XX >]
{
    market_pos     (mp)   :   sub_position_ls      
}


CF_NW_LS  [< V:0,  I:CF_XX_LS,  SUBJ:CONF.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}   >]   {}


CF_MD_LS  [< V:0,  I:CF_XX_LS,  SUBJ:CONF.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}   >]   {}


CF_CC_LS  [< V:0,  I:CF_XX_LS,  SUBJ:CONF.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}   >]   {}




//---------------------------------------------------------------------
//	executions  LS

CF_EX_LS  [< V:0, I:CF_XX_LS,  SUBJ:CONF.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}   >]
{
    executed_pos  (exc)   :  sub_exec_conf
}





//---------------------------------------------------------------------
//	rejects  LS


RJ_NW_LS  [< V:0, I:CF_XX_LS,   SUBJ:CONF.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}  >]  
{
    reject_description  (rd)    :   string
}


RJ_MD_LS  [< V:0, I:CF_XX_LS,   SUBJ:CONF.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}  >]
{
    reject_description  (rd)    :   string
}


RJ_CC_LS  [< V:0, I:CF_XX_LS,   SUBJ:CONF.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}  >]
{
    reject_description  (rd)    :   string
}


