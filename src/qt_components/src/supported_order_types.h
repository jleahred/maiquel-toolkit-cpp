#ifndef SUPPORTED_ORDERS_TYPE__H__
#define SUPPORTED_ORDERS_TYPE__H__



#include "components/msg_common.h"


namespace  supported_order_types
{

    bool  has_market        (const mtk::msg::sub_product_code&  product_code);
    bool  has_stop_market   (const mtk::msg::sub_product_code&  product_code);
    bool  has_stop_limit    (const mtk::msg::sub_product_code&  product_code);
}




#endif // SUPPORTED_ORDERS_TYPE__H__
