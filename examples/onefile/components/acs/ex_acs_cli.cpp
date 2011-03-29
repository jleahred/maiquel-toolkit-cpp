#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"

#include "components/acs/cli/fsm_cli_acs.h"



namespace
{

    const char*   APP_NAME          = "ex_acs";
    const char*   APP_VER           = "2011-03-25";
    const char*   APP_DESCRIPTION   = "small example of ACS/CLIENT component";
    const char*   APP_MODIFICATIONS = "example, no modifications info";
    
    
}



mtk::CountPtr<mtk::acs_cli::fsm_cli_acs>   login_manager;


void stop(const int&)
{
    mtk::stop_timer();
}




void received_login_ok(const mtk::acs::msg::res_login::IC_login_response_info& log_conf)
{
    std::cout << "received login ok  "  << log_conf << std::endl;
    //login_manager->user_rq_logout();
}
void received_logout(const std::string& description)
{
    std::cout << "received logout  with description... " << description << std::endl;
}
void rejected_login_request(const std::string&  description)
{
    std::cout << "login rejected  " << description << std::endl;
}

int main(int /*argc*/, char ** /*argv*/)
{
    try
    {
        mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        

        //mtk::CountPtr<mtk::acs_cli::fsm_cli_acs>   login_manager;
        login_manager = mtk::make_cptr(new mtk::acs_cli::fsm_cli_acs);

        
        login_manager->user_rq_login("joseluis.esteban@desarrollo", "FE159856");
        login_manager->sig_confirm_login_ok.connect(received_login_ok);
        login_manager->sig_logout_login.connect(received_logout);
        login_manager->sig_reject_login.connect(rejected_login_request);
        
    

        MTK_CALL_LATER1S_F(mtk::dtSeconds(1000), 0, stop);
        
        

        mtk::start_timer_wait_till_end();
        

        std::cout << "FIN..... " << std::endl;
        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION (std::cout<< , "main", "nothing more")

    std::cout << "MAL..... " << std::endl;
    #include "support/release_on_exit.hpp"
    return -1;

}
