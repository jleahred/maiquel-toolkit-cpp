BEGIN_INIT

NAMESPACES = ['mtk', 'prices', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "support/mtk_double.h"' , '#include "msg_prices.h"']

END_INIT




//  ps_req_product_info   is generated from  req_product_info  on client
ps_req_product_info  [< V:0, I:req_product_info, SUBJ:RQ.${product_code.market}.PRC.PI.${from} >]
{
    from        (from) :  string   //  id from process who send the message, or   pigrant   on last step, when request is granted
}






ps_pub_prod_info_mtk_ready  [< V:0, SUBJ:PUB.${market}.PS.START_INIT >]
{
    market      (mk)    :       string
}



ps_req_init_prod_info  [< V:0, SUBJ:RQ.${market}.PS.RQINIT >]
{
    market              (mk)    :       string
    process_info        (pi)    :       mtk::msg::sub_process_info      //  necessary to send the response to the specific process
}


ps_conf_full_product_info_init [< V:0, SUBJ:CONF.${market}.PS.START_INIT.${to_process_info.process_name}.${to_process_info.process_uuid} >]
{
    market              (mk)    :       string
    to_process_info     (tpi)   :       mtk::msg::sub_process_info
}

ps_conf_full_product_info  [< V:0, SUBJ:CONF.${full_prod_info.product_code.market}.PS.FPI.${to_process_info.process_name}.${to_process_info.process_uuid} >]
{
    full_prod_info      (fpi)   :       sub_full_product_info

    to_process_info     (tpi)   :       mtk::msg::sub_process_info
    seq_number          (sqn)   :       int
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      same message but specific to speak with  market publisher adaptor
//      a  market publisher adaptor  has to receive request just from a product_loader not from other processes
//
//      using diferent messages, it's more dificult to have errors
//

ps_pub_prod_info_mtk_ready__from_publisher  [< V:0, I: ps_pub_prod_info_mtk_ready,  SUBJ:PUB.${market}.PS.START_INIT.PUBLISHER >]
{
}



ps_req_init_prod_info__to_publisher [< V:0, I:ps_req_init_prod_info,  SUBJ:RQ.${market}.PS.RQINIT.PUBLISHER >]
{
}


ps_conf_full_product_info_init__from_publisher [< V:0, I:ps_conf_full_product_info_init,  SUBJ:CONF.${market}.PS.START_INIT.PUBLISHER.${to_process_info.process_name}.${to_process_info.process_uuid} >]
{
}

ps_conf_full_product_info__from_publisher [< V:0, I:ps_conf_full_product_info, SUBJ:CONF.${full_prod_info.product_code.market}.PS.FPI.PUBLISHER.${to_process_info.process_name}.${to_process_info.process_uuid} >]
{
}
