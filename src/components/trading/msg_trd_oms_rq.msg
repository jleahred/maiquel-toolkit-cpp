BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'msg']
INCLUDES = ['#include "components/msg_common.h"',
            '#include "msg_trd_common.h"',
            '#include "msg_trd_cli_ls.h"' ,
            '#include "msg_trd_cli_mk.h"',
            '#include "msg_trd_cli_sm.h"']

END_INIT








oms_RQ_NW_LS  [< I:RQ_NW_LS ,  QE:CLI_MK, SUBJ:MK.OMS.${invariant.product_code.market}.${invariant.product_code.product}.${from}.TRD >]
{
    reject_description   (rjd)  :  string   //  empty means ok
    from                 (from) :  string   //  id from process who sends the message
}

oms_RQ_MD_LS  [< I:RQ_MD_LS ,  QE:CLI_MK, SUBJ:MK.OMS.${invariant.product_code.market}.${invariant.product_code.product}.${from}.TRD >]
{
    reject_description   (rjd)  :  string   //  empty means ok
    from                 (from) :  string   //  id from process who sends the message
}

oms_RQ_CC_LS  [< I:RQ_CC_LS ,  QE:CLI_MK, SUBJ:MK.OMS.${invariant.product_code.market}.${invariant.product_code.product}.${from}.TRD >]
{
    reject_description   (rjd)  :  string   //  empty means ok
    from                 (from) :  string   //  id from process who sends the message
}





oms_RQ_NW_MK  [< I:RQ_NW_MK,  QE:CLI_MK, SUBJ:MK.OMS.${invariant.product_code.market}.${invariant.product_code.product}.${from}.TRD >]
{
    reject_description   (rjd)  :  string   //  empty means ok
    from                 (from) :  string   //  id from process who sends the message
}

oms_RQ_MD_MK  [< I:RQ_MD_MK,  QE:CLI_MK, SUBJ:MK.OMS.${invariant.product_code.market}.${invariant.product_code.product}.${from}.TRD >]
{
    reject_description   (rjd)  :  string   //  empty means ok
    from                 (from) :  string   //  id from process who sends the message
}

oms_RQ_CC_MK  [< I:RQ_CC_MK,  QE:CLI_MK, SUBJ:MK.OMS.${invariant.product_code.market}.${invariant.product_code.product}.${from}.TRD >]
{
    reject_description   (rjd)  :  string   //  empty means ok
    from                 (from) :  string   //  id from process who sends the message
}


oms_RQ_NW_SM  [< I:RQ_NW_SM,  QE:CLI_MK, SUBJ:MK.OMS.${invariant.product_code.market}.${invariant.product_code.product}.${from}.TRD >]
{
    reject_description   (rjd)  :  string   //  empty means ok
    from                 (from) :  string   //  id from process who sends the message
}

oms_RQ_MD_SM  [< I:RQ_MD_SM,  QE:CLI_MK, SUBJ:MK.OMS.${invariant.product_code.market}.${invariant.product_code.product}.${from}.TRD >]
{
    reject_description   (rjd)  :  string   //  empty means ok
    from                 (from) :  string   //  id from process who sends the message
}

oms_RQ_CC_SM  [< I:RQ_CC_SM,  QE:CLI_MK, SUBJ:MK.OMS.${invariant.product_code.market}.${invariant.product_code.product}.${from}.TRD >]
{
    reject_description   (rjd)  :  string   //  empty means ok
    from                 (from) :  string   //  id from process who sends the message
}



//---------------------------------------------------------------------
//	REQUEST ORDERS STATUS

oms_RQ_ORDERS_STATUS  [< I:RQ_ORDERS_STATUS,  QE:CLI_MK,  SUBJ:MK.OMS.${market}.${from}.RQORDST >]
{
    reject_description   (rjd)  :  string   //  empty means ok
    from                 (from) :  string   //  id from process who sends the message
}
