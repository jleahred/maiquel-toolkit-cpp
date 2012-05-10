#include "ecimd_config.h"
#include "components/admin/admin.h"


namespace
{

    struct  config
    {
        bool blinking;
        bool market_orders;
        bool historic_execs;
        bool loss_win;
    };



    std::string&  get_user_name(void)
    {
        static  std::string*  result = new std::string;
        return *result;
    }



    void  timer_send_ecimd_config(void);

    config*  get_config(void)
    {
        static config* __config =  0;


        if(__config == 0)
        {
            __config = new config{true, false, false, false};

            if(mtk::admin::get_process_info().location.broker_code ==  "CANDORRA")
            {
                __config->blinking              = false;
                __config->market_orders         = true;
                __config->loss_win              = true;
            }

            else if(mtk::admin::get_process_info().location.broker_code ==  "CIMD")
            {
                if(mtk::admin::is_production() == false)
                {
                    __config->market_orders     = true;
                }

                __config->historic_execs        = true;
                __config->loss_win              = true;
            }

            MTK_TIMER_1SF(timer_send_ecimd_config)
        }


        return  __config;
    }




    std::string  get_config_string(void)
    {
        config*  _config = get_config();
        return  MTK_SS(
                       "blingkin:      "  <<  int(_config->blinking)        << std::endl
                    << "market_orders: "  <<  int(_config->market_orders)   << std::endl
                    << "historic_execs:"  <<  int(_config->historic_execs)  << std::endl
                    << "loss_win:      "  <<  int(_config->loss_win)

            );

    }

    //  COMMANDS
    void command_get_ecimd_config(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(get_config_string());
    }


    void register_global_commands (void)
    {
        mtk::admin::register_command("ecimd",          "get_ecimd_options",   "gets specific eCimd customization")->connect(command_get_ecimd_config);
    }

    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)


    void  timer_send_ecimd_config(void)
    {
        static mtk::dtMinutes  minutes  (mtk::rand()%30 + 60);
        MTK_EXEC_MAX_FREC_NO_FIRST_S(minutes)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "ecimd_config", get_config_string(), mtk::alPriorDebug));
        MTK_END_EXEC_MAX_FREC
    }

}



namespace  ecimd_config
{


    void  set_user_name(const std::string&  user_name)
    {
        get_user_name() = mtk::s_toUpper(user_name);
    }



#define  IMPLEMENT_CONFIG(__CONFIG_NAME__)  \
    bool __CONFIG_NAME__(void)  \
    {  \
        return get_config()->__CONFIG_NAME__;  \
    }


IMPLEMENT_CONFIG(blinking)
IMPLEMENT_CONFIG(market_orders)
IMPLEMENT_CONFIG(historic_execs)
IMPLEMENT_CONFIG(loss_win)



}
