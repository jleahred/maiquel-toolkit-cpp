#ifndef __trd_cli_support_h__
#define __trd_cli_support_h__




#include "trd_cli_ls.h"





namespace mtk{namespace trd{



template<typename ORDER_TYPE>       //  mtk::trd::trd_cli_ls
mtk::msg::sub_product_code   get_product_code(const ORDER_TYPE& order)
{
    if(order.last_request().HasValue())
        return order.last_request().Get().invariant.product_code;
    else if (order.last_confirmation().HasValue())
        return order.last_confirmation().Get().invariant.product_code;
    else
        throw mtk::Alarm(MTK_HERE, "trd_cli_support", MTK_SS("no request no confirmation on order"), mtk::alPriorCritic, mtk::alTypeNoPermisions);
}




};   //  namespace trd
};   //  namespace mtk


#endif // __trd_cli_support_h__


