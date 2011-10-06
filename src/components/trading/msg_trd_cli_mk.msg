BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "msg_trd_common.h"', '#include "components/acs/msg_acs.h"']

END_INIT








//  QUEUES  subjects
//  SUBJ:RQ.client.market.account.product_code
//  SUBJ:CONF.client.market.account.session_id

//  rejects has to be private for terminal who makes the request
//  then, we have to add session_id in confirm subject
//  remember that all subjects has to be the same in order to
//  guarranty the order
//  confirmation suscriptions has to suscribe to all session_id
//  and reject suscriptions only for their session_id



//---------------------------------------------------------------------
//    COMMON ORDERS MK
//---------------------------------------------------------------------

sub_position_mk   [<V:0>]
{
    quantity (qt)   :   fix_num
}




//---------------------------------------------------------------------
//	request MK


RQ_XX_MK  [<V:0,   I:RQ_XX   >]
{
    request_pos         (rqp)   :   sub_position_mk
}



RQ_NW_MK  [< V:0, I:RQ_XX_MK,    SUBJ:RQ.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product} >]   {}


RQ_MD_MK  [< V:0, I:RQ_XX_MK,    SUBJ:RQ.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product} >]   {}


RQ_CC_MK  [< V:0, I:RQ_XX_MK,    SUBJ:RQ.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${invariant.product_code.product} >]   {}



//---------------------------------------------------------------------
//	confirmations  MK

CF_XX_MK  [< V:0,  I:CF_XX >]
{
    market_pos     (mkp)   :   sub_position_mk
}


CF_NW_MK  [< V:0,  I:CF_XX_MK,  SUBJ:CONF.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${req_id.session_id}   >]   {}


CF_MD_MK  [< V:0,  I:CF_XX_MK,  SUBJ:CONF.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${req_id.session_id}   >]   {}


CF_CC_MK  [< V:0,  I:CF_XX_MK,  SUBJ:CONF.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${req_id.session_id}   >]   {}




//---------------------------------------------------------------------
//	executions  MK

CF_EX_MK  [< V:0, I:CF_XX_MK,  SUBJ:CONF.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${req_id.session_id}   >]
{
    executed_pos  (exp)   :  sub_exec_conf
}





//---------------------------------------------------------------------
//	rejects  MK
RJ_XX_MK  [< V:0, I:CF_XX_MK  >]
{
    reject_description  (rjd)    :   string
    request_pos         (rqp)    :   sub_position_mk
}


RJ_NW_MK  [< V:0, I:RJ_XX_MK,   SUBJ:CONF.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${req_id.session_id}  >]
{
}


RJ_MD_MK  [< V:0, I:RJ_XX_MK,   SUBJ:CONF.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${req_id.session_id}  >]
{
}


RJ_CC_MK  [< V:0, I:RJ_XX_MK,   SUBJ:CONF.${invariant.account.client_code}.${invariant.product_code.market}.${invariant.account.name}.${req_id.session_id}  >]
{
}


//---------------------------------------------------------------------
//	STATUS MESSAGES

    //  if the order is canceled, remaining quantity will be 0

CF_ST_MK  [< V:0,  I:CF_XX_MK,  SUBJ:CONF.${gen_response_location.client_code}.STATUS_CF.${gen_response_location.session_id}  >]
    //  this "generic" subject let us send order status with no request from user
    //  it's possible receive order status several times
{
    gen_response_location    (grl)    :   mtk::msg::sub_gen_response_location
}
