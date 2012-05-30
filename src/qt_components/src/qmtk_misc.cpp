#include "qmtk_misc.h"

#include "support/mtk_string.h"

#include "support/string_codec.h"

#include <QLocale>
#include <QApplication>
#include <QClipboard>

#include "components/trading/trd_cli_ord_book.h"


namespace qtmisc {

QString fn_as_QString(const mtk::FixedNumber& fn)
{
    if(fn.GetExt().GetInc() == 0)       return QLatin1String(0);
    else    return QLocale::system().toString(fn.GetDouble().get()._0, 'f', fn.GetExt().GetDec());
}

QString     nullable_fn_as_QString(const mtk::nullable<mtk::FixedNumber>& fn)
{
    if(fn.HasValue() == false)      return QLatin1String("");
    else                            return fn_as_QString(fn.Get());
}





QString  dragProductText (const mtk::msg::sub_product_code& product)
{
    mtk::CodecStringProperties csp;

    csp.AddProperty("product.market", product.market);
    csp.AddProperty("product.product", product.product);

    return QLatin1String(csp.Encode().c_str());
}


QString   dragProductText__ext    (const mtk::msg::sub_product_code& product, const mtk::list<mtk::tuple<QString, QString> >&  ext_info)
{
    mtk::CodecStringProperties csp;

    csp.AddProperty("product.market", product.market);
    csp.AddProperty("product.product", product.product);

    for(auto it=ext_info.begin(); it!=ext_info.end(); ++it)
    {
        csp.AddProperty(it->_0.toStdString(), it->_1.toStdString());
    }

    return QLatin1String(csp.Encode().c_str());
}





mtk::msg::sub_product_code  get_product_code(QDropEvent *event)
{
    mtk::CodecStringProperties csp;
    mtk::CountPtr<std::map<std::string, std::string> > cptr_map_decoded =  csp.Decode(event->mimeData()->text().toStdString());
    if(cptr_map_decoded.isValid()== false)
        throw mtk::Alarm(MTK_HERE, "mtkmisc", MTK_SS("invalid product code received on event" << event->mimeData()->text().toStdString()), mtk::alPriorError);

    std::map<std::string, std::string>& map_decoded = *cptr_map_decoded;
    mtk::msg::sub_product_code product_code("", "");

    product_code.market     = map_decoded["product.market"];
    product_code.product    = map_decoded["product.product"];

    return product_code;
}

QString  get_property_value(QDropEvent *event, const QString&  prop_name)
{
    mtk::CodecStringProperties csp;
    mtk::CountPtr<std::map<std::string, std::string> > cptr_map_decoded =  csp.Decode(event->mimeData()->text().toStdString());
    if(cptr_map_decoded.isValid()== false)
        throw mtk::Alarm(MTK_HERE, "mtkmisc", MTK_SS("invalid drop info format" << event->mimeData()->text().toStdString()), mtk::alPriorError);

    std::map<std::string, std::string>& map_decoded = *cptr_map_decoded;

    return  QLatin1String(map_decoded[prop_name.toStdString()].c_str());
}




namespace {
    int base_font_size=13;
};

int get_base_font_size(void)
{
    return base_font_size;
}

void set_base_font_size(int new_size)
{
    base_font_size = new_size;
}








//  by order type   access   ****************************************************************************************
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_ls_dangerous_signals_not_warped& order)
{
    if(order.has_pending_rq())
        return mtk::make_nullable(order.last_request().Get().request_pos.price);
    else
        return mtk::make_nullable(order.last_confirmation().Get().market_pos.price);
}
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_ls& order)
{
    if(order.has_pending_rq())
        return mtk::make_nullable(order.last_request().Get().request_pos.price);
    else
        return mtk::make_nullable(order.last_confirmation().Get().market_pos.price);
}



mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_mk_dangerous_signals_not_warped& /*order*/)
{
    return mtk::nullable<mtk::FixedNumber>();
}
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_mk& /*order*/)
{
    return mtk::nullable<mtk::FixedNumber>();
}


mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_sm_dangerous_signals_not_warped& /*order*/)
{
    return mtk::nullable<mtk::FixedNumber>();
}
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_sm& /*order*/)
{
    return mtk::nullable<mtk::FixedNumber>();
}


mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_sl_dangerous_signals_not_warped& order)
{
    if(order.has_pending_rq())
        return mtk::make_nullable(order.last_request().Get().request_pos.price);
    else
        return mtk::make_nullable(order.last_confirmation().Get().market_pos.price);
}
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_sl& order)
{
    if(order.has_pending_rq())
        return mtk::make_nullable(order.last_request().Get().request_pos.price);
    else
        return mtk::make_nullable(order.last_confirmation().Get().market_pos.price);
}










QString   side_as_text(mtk::trd::msg::enBuySell side)
{
    if(side  == mtk::trd::msg::buy)             return QObject::tr("buy");
    else  if(side  == mtk::trd::msg::sell)      return QObject::tr("sell");
    else                                        return QLatin1String("???");
}


mtk::dtDateTime   QDate_as_mtk_DateTime(const  QDate&  qdate)
{
    return  mtk::DateTime(mtk::dtYear(qdate.year()),  mtk::dtMonth(qdate.month()), mtk::dtDay(qdate.day()));
}



void  copy_execs_clipboard(const mtk::list<mtk::trd::msg::CF_EXLK>&  execs)
{
    QString  result;
    result += QObject::tr("ORDER");     result += QLatin1String("\t");
    result += QObject::tr("CLI_CODE");  result += QLatin1String("\t");
    result += QObject::tr("ACCOUNT");   result += QLatin1String("\t");
    result += QObject::tr("MARKET");    result += QLatin1String("\t");
    result += QObject::tr("PRODUCT");   result += QLatin1String("\t");
    result += QObject::tr("SIDE");      result += QLatin1String("\t");
    result += QObject::tr("QUANTITY");  result += QLatin1String("\t");
    result += QObject::tr("PRICE");     result += QLatin1String("\t");
    result += QLatin1String("\n");



    typedef  mtk::tuple<
            std::string,                                    //  order by
            mtk::trd::msg::sub_account_info,
            mtk::msg::sub_product_code,
            mtk::trd::msg::enBuySell,
            mtk::FixedNumber                   //  price
            >  t_exec_key;
    typedef mtk::tuple< mtk::Double, mtk::trd::msg::sub_order_id>   t_data;

    mtk::map<t_exec_key, t_data>                            map_execs_grouped;
    mtk::map<mtk::trd::msg::sub_order_id, mtk::DateTime>    map_first_exec_per_order;


    for(auto it=execs.begin(); it!=execs.end(); ++it)
    {
        mtk::trd::msg::sub_invariant_order_info  invariant = it->invariant;


        auto it_first_exec = map_first_exec_per_order.find(invariant.order_id);
        if(it_first_exec==map_first_exec_per_order.end())
            it_first_exec = map_first_exec_per_order.insert(std::make_pair(invariant.order_id, it->orig_control_fluct.datetime)).first;


        t_exec_key   key = mtk::make_tuple(     MTK_SS(it_first_exec->second <<  invariant.order_id),
                                                invariant.account,
                                                invariant.product_code,
                                                invariant.side,
                                                it->executed_pos.price);

        auto find_exec_grouped = map_execs_grouped.find(key);
        if(find_exec_grouped == map_execs_grouped.end())
            map_execs_grouped.insert(std::make_pair(key,   mtk::make_tuple(it->executed_pos.quantity.GetDouble(), invariant.order_id)));
        else
            find_exec_grouped->second._0 =  find_exec_grouped->second._0 + it->executed_pos.quantity.GetDouble();
    }

    int counter=0;
    mtk::trd::msg::sub_order_id  prev_ord_id(mtk::msg::sub_request_id("", ""));
    for(auto it=map_execs_grouped.begin(); it!=map_execs_grouped.end(); ++it)
    {
        if(prev_ord_id != it->second._1)
            ++counter;
        prev_ord_id = it->second._1;
        result += QString::number(counter);
        result += QLatin1String("\t");

        result += QLatin1String(it->first._1.client_code.c_str());
        result += QLatin1String("\t");

        result += QLatin1String(it->first._1.name.c_str());
        result += QLatin1String("\t");

        result += QLatin1String(it->first._2.market.c_str());
        result += QLatin1String("\t");

        result += QLatin1String(it->first._2.product.c_str());
        result += QLatin1String("\t");

        result += qtmisc::side_as_text(it->first._3);
        result += QLatin1String("\t");


        result += QLocale::system().toString(it->second._0.get2(), 'f', 3);
        result += QLatin1String("\t");


        result += qtmisc::fn_as_QString(it->first._4);

        result += QLatin1String("\n");
    }

    QApplication::clipboard()->setText(result);
}


};      //      namespace qtmisc {


