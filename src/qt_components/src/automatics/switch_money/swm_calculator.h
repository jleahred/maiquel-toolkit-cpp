#ifndef SWM_CALCULATOR_H
#define SWM_CALCULATOR_H



#include "components/prices/cli/price_manager.h"
#include "swm_config.h"







class swm_calculator   :   public  mtk::SignalReceptor
{
public:
    swm_calculator();


    struct  s_price_update
    {
        mtk::trd::msg::enBuySell            side;

        mtk::nullable<mtk::FixedNumber>     price;
        mtk::nullable<mtk::FixedNumber>     qty;

        QString                             message;
    };



    //**********************************************************************
    //----------------------------------------------------------------------
    //......................................................................



    //  INPUT
    void  on_config_changed(const swm_config&  new_config);


    //  OUTPUT
    mtk::Signal<const s_price_update&>          signal_price_update;
    mtk::Signal<const mtk::Alarm&>              signal_ERROR;



    //......................................................................
    //----------------------------------------------------------------------
    //**********************************************************************


private:
    swm_config    config;

    void   calculate(void);

    //  INPUT
    void    on_best_prices_update       (const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_best_prices&);
    void    on_last_mk_execs_ticker     (const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_last_mk_execs_ticker&);
    void    on_additional_info_update   (const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_additional_info&);
};

#endif // SWM_CALCULATOR_H
