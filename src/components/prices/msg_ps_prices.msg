BEGIN_INIT

NAMESPACES = ['mtk', 'prices', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "support/mtk_double.h"' , '#include "msg_prices.h"']

END_INIT




//  ps_req_product_info   is generated from  req_product_info  on client
ps_req_product_info  [< QE:ALL_GS, I:req_product_info, SUBJ:MK.${product_code.market}.REQ.PI.${from} >]
{
    from        (from) :  string   //  id from process who send the message, or   pigrant   on last step, when request is granted
}






ps_pub_prod_info_mtk_ready  [< QE:ALL_GS, SUBJ:MK.${market}.PS.START_INIT >]
{
    market      (mk)    :       string
}



ps_req_init_prod_info  [< QE:CLI_MK, SUBJ:MK.PS.${market}.RQINIT >]
{
    market              (mk)    :       string
    process_info        (pi)    :       mtk::msg::sub_process_info      //  necessary to send the response to the specific process
}


ps_conf_full_product_info_init [< QE:ALL_GS, SUBJ:MK.${market}.PS.START_INIT.${to_process_info.process_name}.${to_process_info.process_uuid}.CONFFULLPI >]
{
    market              (mk)    :       string
    to_process_info     (tpi)   :       mtk::msg::sub_process_info
}

ps_conf_full_product_info  [< QE:ALL_GS, SUBJ:MK.${full_prod_info.product_code.market}.PS.FPI.${to_process_info.process_name}.${to_process_info.process_uuid}.CONFPI >]
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

ps_pub_prod_info_mtk_ready__from_publisher  [< QE:CLI_MK, I: ps_pub_prod_info_mtk_ready,  SUBJ:MK.PS.${market}.START_INIT.PUBLISHER >]
{
}



ps_req_init_prod_info__to_publisher [< QE:ALL_GS, I:ps_req_init_prod_info,  SUBJ:MK.${market}.PS.RQINIT.PUBLISHER >]
{
}


ps_conf_full_product_info_init__from_publisher [< QE:CLI_MK, I:ps_conf_full_product_info_init,  SUBJ:MK.PS.${market}.${to_process_info.process_name}.${to_process_info.process_uuid}.START_INIT.PUBLISHER >]
{
}

ps_conf_full_product_info__from_publisher [< QE:ALL_GS, I:ps_conf_full_product_info, SUBJ:MK.${full_prod_info.product_code.market}.PS.FPI.${to_process_info.process_name}.${to_process_info.process_uuid}.CONFFPI_FMK >]
{
}
