BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "msg_trd_common.h"', '#include "components/acs/msg_acs.h"' ]

END_INIT











//---------------------------------------------------------------------
//    COMMON ORDERS   STOP MARKET
//---------------------------------------------------------------------


sub_position_sm   [< >]
{
    stop_price  (pri)  :   fix_num
    quantity    (qt)   :   fix_num
    cli_ref     (clr)  :   string
}






//---------------------------------------------------------------------
//	request STOP MARKET


RQ_XX_SM  [< I:RQ_XX   >]
{
    request_pos         (rqp)   :   sub_position_sm
}



RQ_NW_SM  [< I:RQ_XX_SM,  QE:CLI_MK, SUBJ:MK.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}.TRD >]   {}


RQ_MD_SM  [< I:RQ_XX_SM,  QE:CLI_MK, SUBJ:MK.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}.TRD >]   {}


RQ_CC_SM  [< I:RQ_XX_SM,  QE:CLI_MK, SUBJ:MK.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}.TRD >]   {}



//---------------------------------------------------------------------
//	confirmations  SM

CF_XX_SM  [< I:CF_XX >]
{
    market_pos     (mkp)   :   sub_position_sm
}


CF_NW_SM  [< I:CF_XX_SM,  QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD   >]   {}


CF_MD_SM  [< I:CF_XX_SM,  QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD   >]   {}


CF_CC_SM  [< I:CF_XX_SM,  QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD   >]   {}



//---------------------------------------------------------------------
//	CONFIRM TRIGGERED

CF_TR_SM  [< I:CF_XX_SM,  QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD   >]
{
}




//---------------------------------------------------------------------
//	rejects  SM

RJ_XX_SM  [< I:CF_XX_SM >]
{
    request_pos         (rqp)    :   sub_position_sm
}




RJ_NW_SM  [< I:RJ_XX_SM,   QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD  >]
{
}


RJ_MD_SM  [< I:RJ_XX_SM,   QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD  >]
{
}


RJ_CC_SM  [< I:RJ_XX_SM,   QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD  >]
{
}




//---------------------------------------------------------------------
//	STATUS MESSAGES

    //  if the order is canceled, remaining quantity will be 0

CF_ST_SM  [< I:CF_XX_SM,  QE:ALL_GS, SUBJ:CLI.${gen_response_location.broker_code}.${gen_response_location.session_id}.STATUS_CF  >]
    //  this "generic" subject let us send order status with no request from user
    //  it's possible receive order status several times
{
    gen_response_location    (grl)    :   mtk::msg::sub_gen_response_location
}
