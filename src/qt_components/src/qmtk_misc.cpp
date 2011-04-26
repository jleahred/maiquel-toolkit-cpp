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

    csp.AddProperty("product.sys_code.market", product.sys_code.market);
    csp.AddProperty("product.sys_code.product", product.sys_code.product);

    if(product.aditional_code.HasValue())
    {
        csp.AddProperty("product.aditional_code.market", product.aditional_code.Get().market);
        csp.AddProperty("product.aditional_code.product", product.aditional_code.Get().product);
        csp.AddProperty("product.aditional_code.adictional_code", product.aditional_code.Get().aditional_code_type);
    }
    else
    {
        csp.AddProperty("product.aditional_code.market", "<null>");
    }

    csp.AddProperty("user_name", product.sys_code.user_name);

    return csp.Encode().c_str();
}

mtk::msg::sub_product_code  get_product_code(QDropEvent *event)
{
    mtk::CodecStringProperties csp;
    mtk::CountPtr<std::map<std::string, std::string> > cptr_map_decoded =  csp.Decode(event->mimeData()->text().toStdString());
    if(cptr_map_decoded.isValid()== false)
        throw mtk::Alarm(MTK_HERE, "mtkmisc", MTK_SS("invalid product code received on event" << event->mimeData()->text().toStdString()), mtk::alPriorWarning);

    std::map<std::string, std::string>& map_decoded = *cptr_map_decoded;
    mtk::msg::sub_sys_product_code sys_code(mtk::msg::sub_single_product_code("", ""), "");

    mtk::msg::sub_adic_product_code aditional_code(mtk::msg::sub_single_product_code("", ""), "");

    sys_code.market     = map_decoded["product.sys_code.market"];
    sys_code.product    = map_decoded["product.sys_code.product"];
    sys_code.user_name  = map_decoded["user_name"];

    if(map_decoded["product.aditional_code.market"] != "<null>")
    {
        aditional_code.market     = map_decoded["product.aditional_code.market"];
        aditional_code.product    = map_decoded["product.aditional_code.product"];
        return mtk::msg::sub_product_code(sys_code, mtk::make_nullable(aditional_code));
    }
    else
        return mtk::msg::sub_product_code(sys_code, mtk::nullable<mtk::msg::sub_adic_product_code>());

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
