BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "msg_trd_common.h"', '#include "components/acs/msg_acs.h"' ]

END_INIT











//---------------------------------------------------------------------
//    COMMON ORDERS LS
//---------------------------------------------------------------------


sub_position_ls   [< >]
{
    price    (pri)  :   fix_num
    quantity (qt)   :   fix_num
    cli_ref  (clr)  :   string
}






//---------------------------------------------------------------------
//	request LS


RQ_XX_LS  [< I:RQ_XX   >]
{
    request_pos         (rqp)   :   sub_position_ls
}



RQ_NW_LS  [< I:RQ_XX_LS,  QE:CLI_MK, SUBJ:MK.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}.TRD >]   {}


RQ_MD_LS  [< I:RQ_XX_LS,  QE:CLI_MK, SUBJ:MK.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}.TRD >]   {}


RQ_CC_LS  [< I:RQ_XX_LS,  QE:CLI_MK, SUBJ:MK.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}.TRD >]   {}



//---------------------------------------------------------------------
//	confirmations  LS

CF_XX_LS  [< I:CF_XX >]
{
    market_pos     (mkp)   :   sub_position_ls
}


CF_NW_LS  [< I:CF_XX_LS,  QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD   >]   {}


CF_MD_LS  [< I:CF_XX_LS,  QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD   >]   {}


CF_CC_LS  [< I:CF_XX_LS,  QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD   >]   {}




//---------------------------------------------------------------------
//	executions  LS

CF_EX_LS  [< I:CF_XX_LS,  QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD   >]
{
    executed_pos  (exp)   :  sub_exec_conf
}





//---------------------------------------------------------------------
//	rejects  LS

RJ_XX_LS  [< I:CF_XX_LS >]
{
    reject_description  (rjd)    :   string
    request_pos         (rqp)    :   sub_position_ls
}




RJ_NW_LS  [< I:RJ_XX_LS,   QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD  >]
{
}


RJ_MD_LS  [< I:RJ_XX_LS,   QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD  >]
{
}


RJ_CC_LS  [< I:RJ_XX_LS,   QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD  >]
{
}




//---------------------------------------------------------------------
//	STATUS MESSAGES

    //  if the order is canceled, remaining quantity will be 0

CF_ST_LS  [< I:CF_XX_LS,  QE:ALL_GS, SUBJ:CLI.${gen_response_location.broker_code}.${gen_response_location.session_id}.STATUS_CF  >]
    //  this "generic" subject let us send order status with no request from user
    //  it's possible receive order status several times
{
    gen_response_location    (grl)    :   mtk::msg::sub_gen_response_location
}
