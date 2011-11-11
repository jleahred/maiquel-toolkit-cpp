BEGIN_INIT

NAMESPACES = ['mtk', 'prices', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "support/mtk_double.h"']

END_INIT




//---------------------------------------------------------------------
//    COMMON PRICES
//---------------------------------------------------------------------

sub_price_level [< >]
{
   price           (pri) : fix_num
   quantity        (qt)  : fix_num
}

sub_price_deph5 [< >]
{
    level0          (b0)    :  sub_price_level
    level1          (b1)    :  sub_price_level
    level2          (b2)    :  sub_price_level
    level3          (b3)    :  sub_price_level
    level4          (b4)    :  sub_price_level
}



sub_best_prices [< >]
{
    bids                (bids)  :  sub_price_deph5
    asks                (asks)  :  sub_price_deph5
}


//---------------------------------------------------------------------
//    pub_best_prices
//---------------------------------------------------------------------

pub_best_prices [< QE:PRICES.${product_code.market}, SUBJ:BP.${product_code.market}.${product_code.product}  >]
{
    product_code        (pc)    :   mtk::msg::sub_product_code
    best_prices         (bp)    :   sub_best_prices
    orig_control_fluct  (ocf)   :   mtk::msg::sub_control_fluct
}


pub_new_products [< QE:CLI_MK, SUBJ:CLI.ALL.${market}.NP  >]
{
    market              (mk)    :   string
}





//---------------------------------------------------------------------
//    sub_aditional_info
//---------------------------------------------------------------------

sub_aditional_info [< >]
{
    group               (gr)        :       string
    maturity            (mat)       :       date_time       [optional]
    value_date          (vd)        :       date_time       [optional]
    unit_cost           (uc)        :       double
    last_trading_dt     (ltdt)      :       date_time       [optional]


    yaml_misc           (ym)        :       string
}






//---------------------------------------------------------------------
//    sub_full_product_info
//---------------------------------------------------------------------
sub_full_product_info [< >]
{
    product_code        (pc)        :       mtk::msg::sub_product_code

    best_prices         (bp)        :       sub_best_prices
    aditional_info      (ai)        :       sub_aditional_info
    //  ...
}


sub_full_product_info_optionals [< >]
{
    initialized         (init)      :       bool
    product_code        (pc)        :       mtk::msg::sub_product_code

    best_prices         (bp)        :       sub_best_prices                 [optional]
    aditional_info      (ai)        :       sub_aditional_info              [optional]
    //  ...
}




//---------------------------------------------------------------------
//    REQUEST/RESPONSE
//---------------------------------------------------------------------

req_product_info [< QE:ALL_GS, SUBJ:GS.${request_info.process_info.location.broker_code}.${product_code.market}.REQPI >]
{
    request_info        (rqi)       :   mtk::msg::sub_request_info

    product_code        (pc)        :   mtk::msg::sub_product_code
}



res_product_info   [< QE:CLI_MK, SUBJ:CLI.${response_info.request_info.process_info.location.broker_code}.${response_info.request_info.process_info.location.machine}.${response_info.request_info.process_info.process_uuid}.${response_info.request_info.req_id.session_id}.${response_info.request_info.req_id.req_code}.PRC.RESPI >]
{
    response_info   (rsi)       :   mtk::msg::sub_r_response

    response        (rs)  [<  >]
    {
        full_product_info     (bp)    :   sub_full_product_info
    }
}


