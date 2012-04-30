#include "ecimd_config.h"
#include "components/admin/admin.h"


namespace
{

    struct  config
    {
        bool blinking;
        bool market_orders;
    };


    config*  get_config(void)
    {
        static config* __config =  0;


        if(__config == 0)
        {
            __config = new config{true, false};

            if(mtk::admin::get_process_info().location.broker_code ==  "CANDORRA")
            {
                __config->blinking              = false;
                __config->market_orders         = true;
            }

            else if(mtk::admin::get_process_info().location.broker_code ==  "CIMD")
            {
                if(mtk::admin::is_production() == false)
                {
                    __config->market_orders         = true;
                }
            }

        }


        return  __config;
    }


}



namespace  config
{



bool blinking(void)
{
    return get_config()->blinking;
}

bool market_orders(void)
{
    return get_config()->market_orders;
}



}
