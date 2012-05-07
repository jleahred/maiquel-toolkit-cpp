#include "ecimd_config.h"
#include "components/admin/admin.h"


namespace
{

    struct  config
    {
        bool blinking;
        bool market_orders;
        bool historic_execs;
    };


    config*  get_config(void)
    {
        static config* __config =  0;


        if(__config == 0)
        {
            __config = new config{true, false, false};

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

                __config->historic_execs        = true;
            }

        }


        return  __config;
    }


}



namespace  config
{



#define  IMPLEMENT_CONFIG(__CONFIG_NAME__)  \
    bool __CONFIG_NAME__(void)  \
    {  \
        return get_config()->__CONFIG_NAME__;  \
    }


IMPLEMENT_CONFIG(blinking)
IMPLEMENT_CONFIG(market_orders)
IMPLEMENT_CONFIG(historic_execs)



}
