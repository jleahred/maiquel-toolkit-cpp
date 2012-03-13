#include "qmtk_misc.h"

#include "support/mtk_string.h"

#include "support/string_codec.h"

#include <QLocale>

#include "components/trading/trd_cli_ord_book.h"


namespace qtmisc {

QString fn_as_QString(const mtk::FixedNumber& fn)
{
    if(fn.GetExt().GetInc() == 0)       return QLatin1String("");
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










QString   side_as_text(mtk::trd::msg::enBuySell side)
{
    if(side  == mtk::trd::msg::buy)             return QObject::tr("buy");
    else  if(side  == mtk::trd::msg::sell)      return QObject::tr("sell");
    else                                        return QLatin1String("???");
}




};      //      namespace qtmisc {


