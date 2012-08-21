#include "swm_calculator.h"


#include <QObject>


#undef emit    //   esto es una chapu necesaria para compilar con qt que en el resto no molesta




//   variation_effective_origin  ==  variation_effective_destiny



namespace {


    mtk::Double   effective_market(swm_config::en_side  side, const  swm_config::s_product_info&  product_info)
    {
        mtk::Double  unit_cost = product_info.price_manager->get_additional_info().Get().unit_cost;

        /*mtk::Double  price     =   side == swm_config::sell_buy
                                   ?  product_info.price_manager->get_best_prices().Get().bids.level0.price.GetDouble()
                                   :  product_info.price_manager->get_best_prices().Get().asks.level0.price.GetDouble();*/

        mtk::prices::msg::sub_price_level  level =
                (side == swm_config::sell_buy  ?
                            product_info.price_manager->get_best_prices().Get().bids.level0
                                :
                            product_info.price_manager->get_best_prices().Get().asks.level0);

        mtk::Double  price  =  level.quantity.GetIntCode() == 0  ?  mtk::Double::InvalidValue() : level.price.GetDouble();


        mtk::Double  quantity  = product_info.config_qty.Get().GetDouble();

        return  unit_cost * price * quantity;
    }

    mtk::Double   effective_config(const  swm_config::s_product_info&  product_info)
    {
        mtk::Double  unit_cost = product_info.price_manager->get_additional_info().Get().unit_cost;
        mtk::Double  price     = product_info.config_price.Get().GetDouble();
        mtk::Double  quantity  = product_info.config_qty.Get().GetDouble();

        return  unit_cost * price * quantity;
    }


    mtk::Double   variation_effective_origin(const swm_config&  config)
    {
        return  effective_market(config.side, config.origin)  -  effective_config(config.origin);
    }


    swm_calculator::s_price_update     calculate_destiny(const swm_config& config)
    {
        if(config.side !=  swm_config::buy_sell   &&   config.side !=  swm_config::sell_buy)
        {
            MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(30))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "swm", MTK_SS("invalid config side " << config.side), mtk::alPriorError, mtk::alTypeNoPermisions));
            MTK_END_EXEC_MAX_FREC

            return swm_calculator::s_price_update{  mtk::trd::msg::buy,  mtk::nullable<mtk::FixedNumber>{},  mtk::nullable<mtk::FixedNumber>{}, QLatin1String("")  };
        }

        mtk::Double                 unit_cost_destiny =     config.destiny.price_manager->get_additional_info().Get().unit_cost;
        mtk::trd::msg::enBuySell    side              =     config.side == swm_config::buy_sell  ?  mtk::trd::msg::sell  :  mtk::trd::msg::buy;


        //  qty
        mtk::FixedNumber  dest_qty = config.destiny.config_qty.Get();
        mtk::Double  qty = dest_qty.GetDouble();
        dest_qty.SetIntCode(1);      //  provisional


        //  Price
        //  dest_price  =   (variation_effective_origin + effective_configured_destiny)  / (qty * unit_cost_destiny);

        mtk::Double         dest_price      =   (variation_effective_origin(config) + effective_config(config.destiny)) / (qty * unit_cost_destiny);
        mtk::FixedNumber    fn_dest_price   =   config.destiny.config_price.Get();
        if(dest_price.IsValid())
        {
            fn_dest_price.SetDouble(dest_price);
            return  swm_calculator::s_price_update  {  side, mtk::make_nullable(fn_dest_price),  mtk::make_nullable(dest_qty), QLatin1String("")  };
        }
        else
            return  swm_calculator::s_price_update  {  side, mtk::nullable<mtk::FixedNumber>(),  mtk::nullable<mtk::FixedNumber>(), QLatin1String("")  };

    }


};







swm_calculator::swm_calculator()
{
}



void  swm_calculator::on_config_changed(const swm_config&  new_config)
{
    config = new_config;

    //  connect price update receptors
    if(new_config.origin.price_manager.isValid())
    {
        MTK_CONNECT_THIS(new_config.origin.price_manager->signal_additional_info_update,  on_additional_info_update);
        MTK_CONNECT_THIS(new_config.origin.price_manager->signal_best_prices_update,      on_best_prices_update);
        MTK_CONNECT_THIS(new_config.origin.price_manager->signal_last_mk_execs_ticker,    on_last_mk_execs_ticker);
    }

    if(new_config.destiny.price_manager.isValid())
    {
        MTK_CONNECT_THIS(new_config.destiny.price_manager->signal_additional_info_update,  on_additional_info_update);
        MTK_CONNECT_THIS(new_config.destiny.price_manager->signal_best_prices_update,      on_best_prices_update);
        MTK_CONNECT_THIS(new_config.destiny.price_manager->signal_last_mk_execs_ticker,    on_last_mk_execs_ticker);
    }

    calculate();
}



void    swm_calculator::on_best_prices_update       (const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_best_prices&)
{
    calculate();
}

void    swm_calculator::on_last_mk_execs_ticker     (const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_last_mk_execs_ticker&)
{
    calculate();
}

void    swm_calculator::on_additional_info_update   (const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_additional_info&)
{
    calculate();
}



namespace {

    void  send_invalid_result(QString message,  mtk::Signal<const swm_calculator::s_price_update&>&   signal_price_update)
    {
        static  swm_calculator::s_price_update  static_invalid_result {  mtk::trd::msg::buy, mtk::nullable<mtk::FixedNumber>(),  mtk::nullable<mtk::FixedNumber>(), QLatin1String("")  };

        swm_calculator::s_price_update  invalid_result {static_invalid_result};
        invalid_result.message = message;

        signal_price_update.emit(invalid_result);
    }

};

void   swm_calculator::calculate(void)
{
    auto config_status = config.check_config();

    if(config_status._0)
    {
        try {
            signal_price_update.emit(calculate_destiny(config));
            return;
        } catch (const mtk::Alarm& __alarm__) {
              mtk::Alarm  mtkError(
                          MTK_HERE,
                          "swm calculate",
                          MTK_SS(" mtk exception  "  << __alarm__.message),
                          __alarm__.priority,
                          __alarm__.type
                  );
              mtkError.Add(__alarm__);
              signal_ERROR.emit(mtkError);
              send_invalid_result(QLatin1String(__alarm__.message.c_str()), signal_price_update);
          } catch (std::exception& e) {
              signal_ERROR.emit(mtk::Alarm(
                          MTK_HERE,
                          "swm calculate",
                          std::string("c++ exception ") + e.what(),
                          mtk::alPriorCritic));
              send_invalid_result(QLatin1String(e.what()), signal_price_update);
          } catch (...) {
              signal_ERROR.emit(mtk::Alarm(
                          MTK_HERE,
                          "swm calculate",
                          std::string("c++ exception"),
                          mtk::alPriorCritic));
              send_invalid_result(QObject::tr("unknown error (...)"), signal_price_update);
          }
    }
    else
        send_invalid_result(config_status._1, signal_price_update);
}



