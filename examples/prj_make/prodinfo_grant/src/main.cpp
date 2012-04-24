#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"
#include "components/gen/msg_tree_server.h"
#include "support/configfile.h"
#include "components/prices/msg_prices.h"
#include "components/prices/msg_ps_prices.h"
#include "components/acs/serv/acs_synchr.h"

#include "db/prodinfo_grant_db.h"


namespace
{

    const char*   APP_NAME          = "GEN_PRODUCTINFO_GRANT";
    const char*   APP_VER           = "2012-04-24";
    const char*   APP_DESCRIPTION   = "Checking grants for productinfo request\n";


    const char*   APP_MODIFICATIONS =   "           2011-08-10     first version\n"
                                        "           2012-04-24     Non case sensitive user check\n"
                                        ;
                                        ;
}




void on_request_prodinf_received(const mtk::prices::msg::req_product_info&  pi_request);






int main(int argc, char ** argv)
{
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);

        prodinfo_grant::db::init(mtk::admin::get_config_property("MISC.data").Get());
        mtk::acs_server::synchr::init();



        //  suscription to request product information
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::req_product_info> >    hqpid_prodinf_request;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_prodinf_request,
                                mtk::admin::get_url("client"),
                                mtk::prices::msg::req_product_info::get_in_subject("*", "*"),     //  from anyone, for any market
                                mtk::prices::msg::req_product_info,
                                on_request_prodinf_received)


        mtk::start_timer_wait_till_end();


        prodinfo_grant::db::save();
        std::cout << "FIN..... " << std::endl;
        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION (std::cout<< , "main", "nothing more")

    std::cout << "MAL..... " << std::endl;
    #include "support/release_on_exit.hpp"
    return -1;

}


void on_request_prodinf_received(const mtk::prices::msg::req_product_info&  pi_request)
{
    if(prodinfo_grant::db::has_grants(pi_request))      //  it will generate an alarm message if there is no grants
    {
        mtk::prices::msg::ps_req_product_info  granted_msg (pi_request, "pigrant");
        mtk_send_message("server", granted_msg);
    }
}
