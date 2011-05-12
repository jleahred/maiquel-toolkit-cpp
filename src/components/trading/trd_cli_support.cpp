#include "trd_cli_support.h"


namespace mtk{namespace trd{


    
mtk::msg::sub_product_code   get_product_code(const mtk::trd::trd_cli_ls& order)
{
    if(order.last_request().HasValue())
        return order.last_request().Get().product_code;
    else if (order.last_confirmation().HasValue())
        return order.last_confirmation().Get().product_code;
    else
        throw mtk::Alarm(MTK_HERE, "trd_cli_support", MTK_SS("no request no confirmation on order"), mtk::alPriorCritic, mtk::alTypeNoPermisions);
}
    
    
    
    
    
    
    
    
    
    
    
    
    
};   //  namespace trd
};   //  namespace mtk
    