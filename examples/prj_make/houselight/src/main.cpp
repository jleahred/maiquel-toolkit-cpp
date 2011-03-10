#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"



namespace
{
    
    const char*   APP_NAME          = "ADM_HOUSELIGHT";
    const char*   APP_VER           = "0.1";
    const char*   APP_DESCRIPTION   = "This process will send the keep alive to servers and clients\n"
                                      "It will be checked by admin component";
}


void send_central_keep_alive(void)
{
    
    MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(3))
        static  mtk::CountPtr< mtk::qpid_session >  adm_client_session = mtk::admin::get_qpid_session("admin_cli", "ADMCLI");
        static  mtk::CountPtr< mtk::qpid_session >  adm_server_session = mtk::admin::get_qpid_session("admin_srv", "ADMSRV");
        
        
        
        mtk::admin::msg::central_keep_alive msg(mtk::admin::get_process_location(), mtk::dtSeconds(3), mtk::dtSeconds(5));
        
        mtk::send_message(adm_client_session, msg);
        mtk::send_message(adm_server_session , msg);
    MTK_END_EXEC_MAX_FREC
}


int main(int argc, char ** argv)
{
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION);
        
    

        MTK_TIMER_1SF(send_central_keep_alive);

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
