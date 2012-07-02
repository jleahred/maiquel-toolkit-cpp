BEGIN_INIT

NAMESPACES = ['mtk', 'prices', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "support/mtk_double.h"', '#include "components/trading/msg_trd_common_support.h"']


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

pub_best_prices [< QE:PRICES.${product_code.market}, RT:0, SUBJ:BP.${product_code.market}.${product_code.product}  >]
{
    product_code        (pc)    :   mtk::msg::sub_product_code
    best_prices         (bp)    :   sub_best_prices
    orig_control_fluct  (ocf)   :   mtk::msg::sub_control_fluct
}





pub_new_products [< QE:CLI_MK, RT:2, SUBJ:CLI.ALL.${market}.NP  >]
{
    market              (mk)    :   string
}





//---------------------------------------------------------------------
//    sub_additional_info
//---------------------------------------------------------------------

sub_additional_info [< >]
{
    group               (gr)        :       string
    maturity            (mat)       :       date_time       [optional]
    value_date          (vd)        :       date_time       [optional]
    unit_cost           (uc)        :       double
    last_trading_dt     (ltdt)      :       date_time       [optional]


    yaml_misc           (ym)        :       string
}




//---------------------------------------------------------------------
//    sub_last_mk_execs_ticker
//---------------------------------------------------------------------

sub_last_mk_execs_ticker [< >]
{
    last_price           (lp)    :   fix_num
    last_quantity        (lq)    :   fix_num

    max_last_price       (lmin)  :   fix_num          //  max and min price on interval
    min_last_price       (lmax)  :   fix_num

    opened_price         (op)    :   fix_num          //  it could be open price, prev session open price
}


//---------------------------------------------------------------------
//    pub_last_mk_execs_ticker
//---------------------------------------------------------------------

pub_last_mk_execs_ticker [< QE:PRICES.${product_code.market}, RT:0, SUBJ:EXTK.${product_code.market}.${product_code.product}  >]
{
    product_code         (pc)    :   mtk::msg::sub_product_code


    last_mk_execs_ticker (lme)   :   sub_last_mk_execs_ticker

    orig_control_fluct   (ocf)   :   mtk::msg::sub_control_fluct
}




//---------------------------------------------------------------------
//    pub_additional_info
//---------------------------------------------------------------------
pub_additional_info [< QE:PRICES.${product_code.market}, RT:0, SUBJ:ADDI.${product_code.product}  >]
{
    product_code         (pc)    :   mtk::msg::sub_product_code


    additional_info      (ainf)  :   sub_additional_info

    orig_control_fluct   (ocf)   :   mtk::msg::sub_control_fluct
}






//---------------------------------------------------------------------
//    sub_full_product_info
//---------------------------------------------------------------------
sub_full_product_info [< >]
{
    product_code        (pc)       :       mtk::msg::sub_product_code

    best_prices         (bp)       :       sub_best_prices
    additional_info     (ainf)     :       sub_additional_info
    last_mk_execs_ticker(lme)      :       sub_last_mk_execs_ticker        [recomended]
    //  ...
}






sub_full_product_info_optionals [< >]
{
    initialized         (init)      :       bool
    product_code        (pc)        :       mtk::msg::sub_product_code

    best_prices         (bp)        :       sub_best_prices                 [optional]
    additional_info     (ainf)      :       sub_additional_info             [optional]
    last_mk_execs_ticker(lme)       :       sub_last_mk_execs_ticker        [optional]
    //  ...
}




//---------------------------------------------------------------------
//    REQUEST/RESPONSE
//---------------------------------------------------------------------

req_product_info [< QE:ALL_GS, RT:1, SUBJ:GS.${request_info.process_info.location.broker_code}.${product_code.market}.REQPI >]
{
    request_info        (rqi)       :   mtk::msg::sub_request_info

    product_code        (pc)        :   mtk::msg::sub_product_code
}



res_product_info   [< QE:CLI_MK, RT:2, SUBJ:CLI.${response_info.request_info.process_info.location.broker_code}.${response_info.request_info.process_info.location.machine}.${response_info.request_info.process_info.process_uuid}.${response_info.request_info.req_id.session_id}.${response_info.request_info.req_id.req_code}.PRC.RESPI >]
{
    response_info   (rsi)       :   mtk::msg::sub_r_response

    response        (rs)  [<  >]
    {
        full_product_info     (bp)    :   sub_full_product_info
    }
}



//---------------------------------------------------------------------
//    COMPACTED
//---------------------------------------------------------------------


ppc [< QE:PRICES.${market}, RT:0, SUBJ:PPC.${product}  >]
{
    market              (mk)   :  string
    product             (pr)   :  string

    compacted_data      (cd)   :  string

    //  fluct control
    key                 (k)    :  string
    datetime            (dt)   :  date_time
}
