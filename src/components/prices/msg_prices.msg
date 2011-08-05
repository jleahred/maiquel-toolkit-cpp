BEGIN_INIT

NAMESPACES = ['mtk', 'prices', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "support/mtk_double.h"']

END_INIT




//---------------------------------------------------------------------
//    COMMON PRICES
//---------------------------------------------------------------------

sub_price_level [<V:0>]
{
   price           (pri) : fix_num
   quantity        (qt)  : fix_num
}

sub_price_deph5 [<V:0>]
{
    level0          (b0)    :  sub_price_level
    level1          (b1)    :  sub_price_level
    level2          (b2)    :  sub_price_level
    level3          (b3)    :  sub_price_level
    level4          (b4)    :  sub_price_level
}



sub_best_prices [< V:0  >]
{
    bids                (bids)  :  sub_price_deph5
    asks                (asks)  :  sub_price_deph5
}


pub_best_prices [<V:0,  SUBJ:PUB.${product_code.market}.${product_code.product}.BP  >]
{
    product_code        (pc)    :   mtk::msg::sub_product_code     
    best_prices         (bp)    :   sub_best_prices
    orig_control_fluct  (ocf)   :   mtk::msg::sub_control_fluct
}


pub_new_products [<V:0,  SUBJ:PUB.${market}.NP  >]
{
    market              (mk)    :   string
}



sub_full_product_info [< V:0  >]
{
    product_code        (pc)        :       mtk::msg::sub_product_code     
    
    best_prices         (bp)        :       sub_best_prices
    //  ...
}


sub_full_product_info_optionals [< V:0  >]
{
    initialized         (init)      :       bool
    product_code        (pc)        :       mtk::msg::sub_product_code     
    
    best_prices         (bp)        :       sub_best_prices                 [optional]
    //  ...
}




//---------------------------------------------------------------------
//    REQUEST/RESPONSE
//---------------------------------------------------------------------

req_product_info [< V:0, SUBJ:RQ.${request_info.process_info.location.client_code}.${product_code.market}.PRC.PI >]
{
    request_info        (rqi)       :   mtk::msg::sub_request_info
    
    product_code        (pc)        :   mtk::msg::sub_product_code
}



res_product_info   [< V:0 , SUBJ:RS.${response_info.request_info.process_info.location.client_code}.${response_info.request_info.process_info.location.machine}.${response_info.request_info.process_info.process_uuid}.${response_info.request_info.req_id.session_id}.${response_info.request_info.req_id.req_code}.PRC.PI >]
{
    response_info   (rsi)       :   mtk::msg::sub_r_response
    
    response        (rs)  [< V:0 >]
    {
        full_product_info     (bp)    :   sub_full_product_info
    }
}


