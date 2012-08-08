#include "supported_order_types.h"

#include "components/admin/admin.h"



namespace  supported_order_types
{


    bool  check_all_orders_trick(void);



    bool  has_market(const mtk::msg::sub_product_code&  product_code)
    {
        if(check_all_orders_trick())        return true;


        if(product_code.market == "MARKET"  ||  product_code.market == "EU")
            return true;
        else
            return false;
    }

    bool  has_stop_market(const mtk::msg::sub_product_code&  product_code)
    {
        if(check_all_orders_trick())        return true;

        if(product_code.market == "MARKET"  ||  product_code.market == "EU")
            return true;
        else
            return false;
    }

    bool  has_stop_limit    (const mtk::msg::sub_product_code&  product_code)
    {
        if(check_all_orders_trick())        return true;

        if(product_code.market == "MARKET"  ||  product_code.market == "M3")
            return true;
        else
            return false;
    }







    bool  check_all_orders_trick(void)
    {
        static mtk::Nullable<std::string>  all_orders_trick = mtk::admin::get_config_property("TESTING.all_orders_types");
        if(all_orders_trick.HasValue())
        {
            if(mtk::admin::is_production())
            {
                MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(30))
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_all_orders_trick", "invalid configuration on production", mtk::alPriorError));
                MTK_END_EXEC_MAX_FREC
                return false;
            }
            else if(all_orders_trick.Get() == "true")
                return true;    /////
        }
        return false;
    }

}
