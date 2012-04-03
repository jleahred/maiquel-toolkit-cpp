BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "msg_trd_common.h"', '#include "components/acs/msg_acs.h"' ]

END_INIT











//---------------------------------------------------------------------
//    COMMON ORDERS   STOP MARKET
//---------------------------------------------------------------------


sub_position_sl   [< >]
{
    stop_price  (spr)  :   fix_num
    price       (pri)  :   fix_num      //  limit price
    quantity    (qt)   :   fix_num
    cli_ref     (clr)  :   string
}






//---------------------------------------------------------------------
//	request STOP LIMIT


RQ_XX_SL  [< I:RQ_XX   >]
{
    request_pos         (rqp)   :   sub_position_sl
}



RQ_NW_SL  [< I:RQ_XX_SL,  QE:CLI_MK, RT:0, SUBJ:MK.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}.TRD >]   {}


RQ_MD_SL  [< I:RQ_XX_SL,  QE:CLI_MK, RT:0, SUBJ:MK.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}.TRD >]   {}


RQ_CC_SL  [< I:RQ_XX_SL,  QE:CLI_MK, RT:0, SUBJ:MK.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}.TRD >]   {}



//---------------------------------------------------------------------
//	confirmations  SL

CF_XX_SL  [< I:CF_XX >]
{
    market_pos     (mkp)   :   sub_position_sl
}


CF_NW_SL  [< I:CF_XX_SL,  QE:CLI_MK, RT:0, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD   >]   {}


CF_MD_SL  [< I:CF_XX_SL,  QE:CLI_MK, RT:0, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD   >]   {}


CF_CC_SL  [< I:CF_XX_SL,  QE:CLI_MK, RT:0, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD   >]   {}



//---------------------------------------------------------------------
//	CONFIRM TRIGGERED

CF_TR_SL  [< I:CF_XX_SL,  QE:CLI_MK, RT:0, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD   >]
{
}




//---------------------------------------------------------------------
//	rejects  SL

RJ_XX_SL  [< I:CF_XX_SL >]
{
    request_pos         (rqp)    :   sub_position_sl
}




RJ_NW_SL  [< I:RJ_XX_SL,   QE:CLI_MK, RT:0, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD  >]
{
}


RJ_MD_SL  [< I:RJ_XX_SL,   QE:CLI_MK, RT:0, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD  >]
{
}


RJ_CC_SL  [< I:RJ_XX_SL,   QE:CLI_MK, RT:0, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.TRD  >]
{
}




//---------------------------------------------------------------------
//	STATUS MESSAGES

    //  if the order is canceled, remaining quantity will be 0

CF_ST_SL  [< I:CF_XX_SL,  QE:ALL_GS, RT:2, SUBJ:CLI.${gen_response_location.broker_code}.${gen_response_location.session_id}.STATUS_CF  >]
    //  this "generic" subject let us send order status with no request from user
    //  it's possible receive order status several times
{
    gen_response_location    (grl)    :   mtk::msg::sub_gen_response_location
}
