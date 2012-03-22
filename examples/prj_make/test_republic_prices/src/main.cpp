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

    const char*   APP_NAME          = "TESTING_PRICE_CONTENT";
    const char*   APP_VER           = "2012-03-22";
    const char*   APP_DESCRIPTION   = "receive eu prices and publish on fake message with contention\n"
                                        ;

    const char*   APP_MODIFICATIONS =   "           2012-03-22     first version\n"
                                        ;

}





    //  COMMANDS


    //  status



void on_price_update             (const mtk::prices::msg::pub_best_prices& msg_update_price);
void on_mk_last_ex_ticher_update (const mtk::prices::msg::pub_last_mk_execs_ticker& msg_mk_last_ex_ticker);
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
    typedef  mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::pub_best_prices> >               type_cptrhandle;
    static mtk::list< type_cptrhandle >  hqpid_update_best_prices_list_by_market;

    typedef  mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::pub_last_mk_execs_ticker> >      type_cptrhandle_last_mk_execs_ticker;
    static mtk::list< type_cptrhandle_last_mk_execs_ticker >  hqpid_update_last_mk_execs_ticker_list_by_market;


    static  std::string  MARKET = mtk::admin::get_config_mandatory_property("REPUBLIC.market");

    hqpid_update_best_prices_list_by_market.push_back(type_cptrhandle{});
    MTK_QPID_RECEIVER_CONNECT_F__WITH_ADDRESS(
                            hqpid_update_best_prices_list_by_market.back(),
                            mtk::admin::get_url("admin"),
                            mtk::prices::msg::pub_best_prices::static_get_qpid_address(MARKET),
                            mtk::prices::msg::pub_best_prices::get_in_subject(MARKET, "*"),
                            mtk::prices::msg::pub_best_prices,
                            on_price_update)

    hqpid_update_last_mk_execs_ticker_list_by_market.push_back(type_cptrhandle_last_mk_execs_ticker{});
    MTK_QPID_RECEIVER_CONNECT_F__WITH_ADDRESS(
                            hqpid_update_last_mk_execs_ticker_list_by_market.back(),
                            mtk::admin::get_url("admin"),
                            mtk::prices::msg::pub_last_mk_execs_ticker::static_get_qpid_address(MARKET),
                            mtk::prices::msg::pub_last_mk_execs_ticker::get_in_subject(MARKET, "*"),
                            mtk::prices::msg::pub_last_mk_execs_ticker,
                            on_mk_last_ex_ticher_update)
}







void on_price_update (const mtk::prices::msg::pub_best_prices& msg_update_price)
{
    mtk::prices::publ::send_best_prices(msg_update_price.product_code, msg_update_price.best_prices);
}


void on_mk_last_ex_ticher_update (const mtk::prices::msg::pub_last_mk_execs_ticker& msg_mk_last_ex_ticker)
{
    mtk::prices::publ::send_last_exec_ticker(msg_mk_last_ex_ticker.product_code, msg_mk_last_ex_ticker.last_mk_execs_ticker);
}
