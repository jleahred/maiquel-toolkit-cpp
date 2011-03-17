BEGIN_INIT

NAMESPACES = ['mtk', 'prices', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "support/mtk_double.h"']

END_INIT




//---------------------------------------------------------------------
//    COMMON PRICES
//---------------------------------------------------------------------

sub_price_level [<V:0>]
{
   price           (pr)  : fix_num
   quantity        (qt)  : fix_num
}

sub_price_deph5 [<V:0>]
{
    level0          (b0)    :  sub_price_level
    level1          (b1)    :  sub_price_level
    level2          (b2)    :  sub_price_level
    level3          (b3)    :  sub_price_level
    level4          (b4)    :  sub_price_level
}



pub_best_prices [<V:0,  SUBJ:PUB.${product_code.sys_code.market}.${product_code.sys_code.product}  >]
{
    product_code        (pc)    :   mtk::msg::sub_product_code     

    bids                (bid)   :  sub_price_deph5
    asks                (ask)   :  sub_price_deph5
}


