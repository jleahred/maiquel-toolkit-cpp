#ifndef SWM_CONFIG_H
#define SWM_CONFIG_H



#include<QString>

#include "components/prices/cli/price_manager.h"
#include "support/nullable.hpp"
#include "support/count_ptr.hpp"
#include "support/fixed_number.h"




class swm_config
{
public:
    enum        en_side { buy_sell, sell_buy  };
    struct      s_product_info {
        mtk::CountPtr<mtk::prices::price_manager>     price_manager;
        mtk::nullable<mtk::FixedNumber>               config_price;
        mtk::nullable<mtk::FixedNumber>               config_qty;
    };


    en_side                                       side;

    s_product_info                                origin;
    s_product_info                                destiny;


    mtk::nullable<mtk::FixedNumber>               total_quantity;
    mtk::nullable<mtk::FixedNumber>               min_quantity;
    mtk::nullable<mtk::FixedNumber>               max_quantity;



    //swm_config();     let automatic to allow list initialization

    mtk::tuple<bool, QString>         check_config(void) const;


private:

};

#endif // SWM_CONFIG_H
