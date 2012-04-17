#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"
#include "components/prices/msg_prices.h"
#include "components/prices/msg_ps_prices.h"
#include "components/prices/prices_support.h"
#include "components/prices/prices_publication.h"



namespace
{

    const char*   APP_NAME          = "TEST_REPUBLIC_PRICES";
    const char*   APP_VER           = "2012-04-02 d";
    const char*   APP_DESCRIPTION   = "receive compacted prices and publish on old non compacted\n"
                                        ;

    const char*   APP_MODIFICATIONS =   "           2012-03-22     first version\n"
                                        "           2012-04-02     now it receives compacted and republish non compacted\n"
                                        ;

}





    //  COMMANDS


    //  status



void on_price__or__last__update             (const mtk::prices::msg::ppc&  ppc);
void suscribe_publisher_updates  (void);





//      M A I N


int main(int argc, char ** argv)
{
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);






        suscribe_publisher_updates();


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




void suscribe_publisher_updates(void)
{
    typedef  mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ppc> >               type_cptrhandle;
    static mtk::list< type_cptrhandle >  hqpid_update_best_prices_list_by_market;

    typedef  mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::pub_last_mk_execs_ticker> >      type_cptrhandle_last_mk_execs_ticker;
    static mtk::list< type_cptrhandle_last_mk_execs_ticker >  hqpid_update_last_mk_execs_ticker_list_by_market;


    static  std::string  MARKET = mtk::admin::get_config_mandatory_property("REPUBLIC.market");

    hqpid_update_best_prices_list_by_market.push_back(type_cptrhandle{});
    MTK_QPID_RECEIVER_CONNECT_F__WITH_ADDRESS(
                            hqpid_update_best_prices_list_by_market.back(),
                            mtk::admin::get_url("admin"),
                            mtk::prices::msg::ppc::static_get_qpid_address(MARKET),
                            mtk::prices::msg::ppc::get_in_subject("*"),
                            mtk::prices::msg::ppc,
                            on_price__or__last__update)
}







void on_price__or__last__update (const mtk::prices::msg::ppc&  ppc)
{
    mtk::tuple<mtk::nullable<mtk::prices::msg::sub_best_prices>, mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker> >
    decompacted = mtk::prices::publ::decompact_prices(ppc.compacted_data);

    mtk::msg::sub_product_code          product_code    (ppc.market, ppc.product);
    mtk::msg::sub_control_fluct         control_fluct   (ppc.key, ppc.datetime);

    if(decompacted._0.HasValue())
    {
        mtk::prices::msg::pub_best_prices   pub_best_prices (product_code, decompacted._0.Get(), control_fluct);
        mtk_send_message("admin", pub_best_prices);
    }
    if(decompacted._1.HasValue())
    {
        mtk::prices::msg::pub_last_mk_execs_ticker   last_mk_execs_ticker (product_code, decompacted._1.Get(), control_fluct);
        mtk_send_message("admin", last_mk_execs_ticker);
    }
}


