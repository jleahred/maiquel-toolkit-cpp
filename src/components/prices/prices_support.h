#ifndef  __mtk_prices_support__
#define  __mtk_prices_support__


#include "msg_prices.h"



namespace mtk {
namespace prices {

    
    mtk::prices::msg::sub_full_product_info             get_full_product_info_from_optional     (const mtk::prices::msg::sub_full_product_info_optionals&  pio);
    mtk::prices::msg::sub_full_product_info_optionals   get_empty_full_product_info_optional    (const mtk::msg::sub_product_code&  pc);

    mtk::prices::msg::sub_full_product_info_optionals   get_full_product_info_optional_from__full_product_info
                                                                                                (const mtk::prices::msg::sub_full_product_info&  pi);
    void                                                merge_full_product_info_optionals__with_full_product_info
                                    (mtk::prices::msg::sub_full_product_info_optionals&  pio, const mtk::prices::msg::sub_full_product_info&  pi);
    
          
          
};  //  namespace prices {
};  //  namespace mtk {


#endif 
