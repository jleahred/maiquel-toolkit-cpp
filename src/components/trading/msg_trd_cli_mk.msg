BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "msg_trd_common.h"', '#include "components/acs/msg_acs.h"']

END_INIT








//  rejects has to be private for terminal who makes the request
//  then, we have to add session_id in confirm subject
//  remember that all subjects has to be the same in order to
//  guarranty the order
//  confirmation suscriptions has to suscribe to all session_id
//  and reject suscriptions only for their session_id



//---------------------------------------------------------------------
//    COMMON ORDERS MK
//---------------------------------------------------------------------

sub_position_mk   [< >]
{
    quantity (qt)   :   fix_num
}




//---------------------------------------------------------------------
//	request MK


RQ_XX_MK  [< I:RQ_XX , QE:CLI_MK >]
{
    request_pos         (rqp)   :   sub_position_mk
}



RQ_NW_MK  [< I:RQ_XX_MK,    QE:CLI_MK, SUBJ:MK.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}.TRD >]   {}


RQ_MD_MK  [< I:RQ_XX_MK,    QE:CLI_MK, SUBJ:MK.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}.TRD >]   {}


RQ_CC_MK  [< I:RQ_XX_MK,    QE:CLI_MK, SUBJ:MK.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product}.TRD >]   {}



//---------------------------------------------------------------------
//	confirmations  MK

CF_XX_MK  [< I:CF_XX >]
{
    market_pos     (mkp)   :   sub_position_mk
}


CF_NW_MK  [< I:CF_XX_MK,  QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${req_id.session_id}.TRD   >]   {}


CF_MD_MK  [< I:CF_XX_MK,  QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${req_id.session_id}.TRD   >]   {}


CF_CC_MK  [< I:CF_XX_MK,  QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${req_id.session_id}.TRD   >]   {}




//---------------------------------------------------------------------
//	executions  MK

CF_EX_MK  [< I:CF_XX_MK,  QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${req_id.session_id}.TRD   >]
{
    executed_pos  (exp)   :  sub_exec_conf
}





//---------------------------------------------------------------------
//	rejects  MK
RJ_XX_MK  [< I:CF_XX_MK  >]
{
    reject_description  (rjd)    :   string
    request_pos         (rqp)    :   sub_position_mk
}


RJ_NW_MK  [< I:RJ_XX_MK,   QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${req_id.session_id}.TRD  >]
{
}


RJ_MD_MK  [< I:RJ_XX_MK,   QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${req_id.session_id}.TRD  >]
{
}


RJ_CC_MK  [< I:RJ_XX_MK,   QE:CLI_MK, SUBJ:CLI.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${req_id.session_id}.TRD  >]
{
}


//---------------------------------------------------------------------
//	STATUS MESSAGES

    //  if the order is canceled, remaining quantity will be 0

CF_ST_MK  [< I:CF_XX_MK,  QE:CLI_MK, SUBJ:CLI.${gen_response_location.broker_code}.${gen_response_location.session_id}.STATUS_CF  >]
    //  this "generic" subject let us send order status with no request from user
    //  it's possible receive order status several times
{
    gen_response_location    (grl)    :   mtk::msg::sub_gen_response_location
}
