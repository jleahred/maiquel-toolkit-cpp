#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"



namespace
{

    const char*   APP_NAME          = "ADM_HOUSELIGHT";
    const char*   APP_VER           = "2011-03-16";
    const char*   APP_DESCRIPTION   = "This process will send the keep alive to servers and clients\n"
                                      "It will be checked by admin component";

    const char*   APP_MODIFICATIONS = "           2011-03-16     first version\n";

}


void send_central_keep_alive(void)
{

    MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(3))
        mtk::admin::msg::pub_central_keep_alive msg(mtk::admin::get_process_info(), mtk::dtSeconds(3), mtk::dtSeconds(5), "GS1");

        mtk_send_message("admin_cli", msg);
        mtk_send_message("admin_srv", msg);
    MTK_END_EXEC_MAX_FREC
}


int main(int argc, char ** argv)
{
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);



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
