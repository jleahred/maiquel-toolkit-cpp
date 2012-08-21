#include "swm_config.h"

#include <QObject>



/*
swm_config::swm_config()
    : side(buy_sell)
{
}*/


mtk::tuple<bool, QString>         swm_config::check_config(void) const
{
    //  checking product subscription
    if(origin.price_manager.isValid() == false  ||   destiny.price_manager.isValid() == false)
    {
        return mtk::make_tuple(false, QObject::tr("Missing product."));
    }

    //  checking product info
    if(   origin.price_manager->get_additional_info().HasValue() == false  ||   destiny.price_manager->get_additional_info().HasValue() == false
       || origin.price_manager->get_best_prices().HasValue()     == false  ||   destiny.price_manager->get_best_prices().HasValue()     == false)
        return mtk::make_tuple(false, QObject::tr("Missing product information."));

    else if(origin.price_manager->get_additional_info().Get().unit_cost== mtk::Double(0.))
        return mtk::make_tuple(false, QObject::tr("Invalid unit cost on %1.").arg(QLatin1String(origin.price_manager->get_product_code().product.c_str())));
    else if(destiny.price_manager->get_additional_info().Get().unit_cost== mtk::Double(0.))
        return mtk::make_tuple(false, QObject::tr("Invalid unit cost on %1.").arg(QLatin1String(origin.price_manager->get_product_code().product.c_str())));

    //  checking price and quantity configuration
    else if(origin.config_price.HasValue()==false  ||  destiny.config_price.HasValue()==false)
        return mtk::make_tuple(false, QObject::tr("Missing price on config."));

    else if(origin.config_qty.HasValue()==false  ||  destiny.config_qty.HasValue()==false)
        return mtk::make_tuple(false, QObject::tr("Missing qty on config."));


    else
        return mtk::make_tuple(true, QString(QLatin1String("")));
}
