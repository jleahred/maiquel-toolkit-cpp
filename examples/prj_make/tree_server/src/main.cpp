#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"



namespace
{
    
    const char*   APP_NAME          = "GEN_TREESERVER";
    const char*   APP_VER           = "0.1";
    const char*   APP_DESCRIPTION   = "This process will send, the markets and groups.\n"
                                      "It also check the permisions\n"
                                      "It doesn't have the full information, there are others specific THREESERVERS cooperating."
}




int main(int argc, char ** argv)
{
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION);


        //  suscription to request
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::command>            > hqpid_tree_request;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_tree_request,
                                mtk::admin::get_url("client"),
                                "GENCLI",
                                mtk::admin::msg::command::get_in_subject(temp_process_location.location, 
                                                                         temp_process_location.machine,
                                                                         temp_process_location.process_name,
                                                                         temp_process_location.process_uuid),
                                mtk::admin::msg::command,
                                on_command_received)
        
    
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
 
