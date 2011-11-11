#include "prices_support.h"




namespace mtk {
namespace prices {


mtk::prices::msg::sub_full_product_info   get_full_product_info_from_optional(const mtk::prices::msg::sub_full_product_info_optionals&  pio)
{
    if(pio.initialized==false)
        throw mtk::Alarm(MTK_HERE, "prices_support", MTK_SS("get_full_product_info_from_optional  with no initialized   " << pio),
                                        mtk::alPriorCritic, mtk::alTypeLogicError);

    if(pio.best_prices.HasValue() == false)
        throw mtk::Alarm(MTK_HERE, "prices_support", MTK_SS("get_full_product_info_from_optional  with no best prices   " << pio),
                                        mtk::alPriorCritic, mtk::alTypeLogicError);
    if(pio.aditional_info.HasValue() == false)
        throw mtk::Alarm(MTK_HERE, "prices_support", MTK_SS("get_full_product_info_from_optional  with no  aditional info   " << pio),
                                        mtk::alPriorCritic, mtk::alTypeLogicError);

    return  mtk::prices::msg::sub_full_product_info (pio.product_code, pio.best_prices.Get(), pio.aditional_info.Get());
}


mtk::prices::msg::sub_full_product_info_optionals   get_empty_full_product_info_optional    (const mtk::msg::sub_product_code&  pc)
{
    return mtk::prices::msg::sub_full_product_info_optionals(false, pc, mtk::nullable<mtk::prices::msg::sub_best_prices>(),
                                                                        mtk::nullable<mtk::prices::msg::sub_aditional_info>());
}


mtk::prices::msg::sub_full_product_info_optionals   get_full_product_info_optional_from__full_product_info
                                                                                            (const mtk::prices::msg::sub_full_product_info&  pi)
{
    return mtk::prices::msg::sub_full_product_info_optionals(true, pi.product_code, mtk::make_nullable(pi.best_prices), mtk::make_nullable(pi.aditional_info));
}


void      merge_full_product_info_optionals__with_full_product_info
                                    (mtk::prices::msg::sub_full_product_info_optionals&  pio, const mtk::prices::msg::sub_full_product_info&  pi)
{
    if(pio.best_prices.HasValue() == false)
        pio.best_prices = pi.best_prices;
}


};  //  namespace prices {
};  //  namespace mtk {
