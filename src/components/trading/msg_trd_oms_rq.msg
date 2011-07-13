BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "msg_trd_common.h"', '#include "msg_trd_cli_ls.h"' , '#include "msg_trd_cli_mk.h"']

END_INIT








oms_RQ_NW_LS  [< V:0, I:RQ_NW_LS ,  SUBJ:RQ.OMS.${invariant.product_code.market}.${invariant.product_code.product} >]
{
    reject_description   (rjd)  :  string  //  empty means ok
}

oms_RQ_MD_LS  [< V:0, I:RQ_MD_LS ,  SUBJ:RQ.OMS.${invariant.product_code.market}.${invariant.product_code.product} >]
{
    reject_description   (rjd)  :  string  //  empty means ok
}

oms_RQ_CC_LS  [< V:0, I:RQ_CC_LS ,  SUBJ:RQ.OMS.${invariant.product_code.market}.${invariant.product_code.product} >]
{
    reject_description   (rjd)  :  string  //  empty means ok
}





oms_RQ_NW_MK  [< V:0, I:RQ_NW_MK,  SUBJ:RQ.OMS.${invariant.product_code.market}.${invariant.product_code.product} >]
{
    reject_description   (rjd)  :  string  //  empty means ok
}

oms_RQ_MD_MK  [< V:0, I:RQ_MD_MK,  SUBJ:RQ.OMS.${invariant.product_code.market}.${invariant.product_code.product} >]
{
    reject_description   (rjd)  :  string  //  empty means ok
}

oms_RQ_CC_MK  [< V:0, I:RQ_CC_MK,  SUBJ:RQ.OMS.${invariant.product_code.market}.${invariant.product_code.product} >]
{
    reject_description   (rjd)  :  string  //  empty means ok
}



//---------------------------------------------------------------------
//	REQUEST ORDERS STATUS

oms_RQ_ORDERS_STATUS  [< V:0, I:RQ_ORDERS_STATUS,  SUBJ:RQ.OMS.${account.client_code}.${market} >]   
{
    reject_description   (rjd)  :  string  //  empty means ok
}
