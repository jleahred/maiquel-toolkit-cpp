#include "qmtk_misc.h"

#include "support/mtk_string.h"

#include "support/string_codec.h"

#include <QLocale>


QString fn_as_QString(const mtk::FixedNumber& fn)
{
    return QLocale::system().toString(fn.GetDouble().get()._0, 'f', fn.GetExt().GetDec());
}




QString  dragProductText (const mtk::msg::sub_product_code& product)
{
    mtk::CodecStringProperties csp;

    csp.AddProperty("product.market", product.market);
    csp.AddProperty("product.product", product.product);

    return QLatin1String(csp.Encode().c_str());
}

mtk::msg::sub_product_code  get_product_code(QDropEvent *event)
{
    mtk::CodecStringProperties csp;
    mtk::CountPtr<std::map<std::string, std::string> > cptr_map_decoded =  csp.Decode(event->mimeData()->text().toStdString());
    if(cptr_map_decoded.isValid()== false)
        throw mtk::Alarm(MTK_HERE, "mtkmisc", MTK_SS("invalid product code received on event" << event->mimeData()->text().toStdString()), mtk::alPriorWarning);

    std::map<std::string, std::string>& map_decoded = *cptr_map_decoded;
    mtk::msg::sub_product_code product_code("", "");

    product_code.market     = map_decoded["product.market"];
    product_code.product    = map_decoded["product.product"];

    return product_code;

}



namespace {
    int base_font_size=10;
};

int get_base_font_size(void)
{
    return base_font_size;
}

void set_base_font_size(int new_size)
{
    base_font_size = new_size;
}
