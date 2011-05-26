#include "components/admin/admin.h"

#include "components/acs/serv/acs_synchr.h"
#include "support/call_later.h"




namespace
{

    const char*   APP_NAME          = "ex_acs_server_sync";
    const char*   APP_VER           = "2011-05-25";
    const char*   APP_DESCRIPTION   = "small example";
    const char*   APP_MODIFICATIONS = "example, no modifications info";
};




void stop (const int&)
{
    mtk::stop_timer();
}



int main(void)
{
    try
    {
        mtk::admin::init("./config_server.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);


        mtk::acs_server::synchr::init();
     
     
        MTK_CALL_LATER1S_F(mtk::dtSeconds(10), 0, stop);
        
        mtk::start_timer_wait_till_end();
        

        std::cout << "FIN..... " << std::endl;
        #include "support/release_on_exit.hpp"
        return 0;
    } MTK_CATCH_CALLFUNCION(std::cout << , "main", "nm")
    
    std::cout << std::endl;
    return -1;
}


 
