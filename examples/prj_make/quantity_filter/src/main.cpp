#include <iostream>

#include "components/admin/admin.h"
//#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"
#include "db/db.h"
#include "components/acs/serv/acs_synchr.h"
#include "components/trading/msg_trd_oms_rq.h"




namespace
{
    
    const char*   APP_NAME          = "GEN_PRICE_FILTER";
    const char*   APP_VER           = "2011-07-14";
    const char*   APP_DESCRIPTION   = "Fat fingers filters \n"
                                      "I will check the order quantity with filter configuration\n"
                                      "\n";
                                      
    const char*   APP_MODIFICATIONS = "           2011-07-14     first version\n";
    


    void suscribe_order_request(void);      //  included orders status
}





int main(int argc, char ** argv)
{
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        
    
        qfmgr::db::init(mtk::admin::get_config_property("MISC.db_file").Get());    //  if property doesn't exists program it will finish with exception
        
        
        mtk::acs_server::synchr::init();
        suscribe_order_request();

        mtk::start_timer_wait_till_end();
    
        
        qfmgr::db::save();
    

        std::cout << "FIN..... " << std::endl;
        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION (std::cout<< , "main", "nothing more")

    std::cout << "MAL..... " << std::endl;
    #include "support/release_on_exit.hpp"
    return -1;

}














namespace
{
    template<typename  OT>   //     ex:  mtk::trd::msg::oms_RQ_NW_LS
    std::string   check_request_quantity_filter (const OT&  oms_rq)
    {
        if(oms_rq.reject_description != "")
            return  oms_rq.reject_description;
            
        mtk::FixedNumber  request_quantity = oms_rq.request_pos.quantity;
        mtk::acs::msg::res_login::IC_session_info  sessinfo = mtk::acs_server::synchr::get_session_info_for_session_id(oms_rq.request_info.req_id.session_id);
        
        auto  filters = qfmgr::db::get_user_filters____tpl_cli_user(   sessinfo.client_code, 
                                                            mtk::s_toUpper(sessinfo.user_name), 
                                                            oms_rq.invariant.product_code.market, 
                                                            oms_rq.invariant.product_code.product);
        if(request_quantity.GetIntCode() > filters._0)
            return MTK_SS(sessinfo.client_code  << " filter: " << filters._0  <<  "  on  "  <<  oms_rq.invariant.product_code  << "   order qty " << request_quantity);
        else if(request_quantity.GetIntCode() > filters._1)
            return MTK_SS(sessinfo.user_name  << " filter: " << filters._1  <<  "  on  "  <<  oms_rq.invariant.product_code<<  "order qty " << request_quantity);
        else
            return "";
    }
    
    
    //      ORDER FILTER ..........................................................................

    #define ON_RQ_XX_XX(__MESSAGE_TYPE__) \
            void on_##__MESSAGE_TYPE__(const mtk::trd::msg::__MESSAGE_TYPE__& rq)   \
            {   \
                static mtk::CountPtr<mtk::qpid_session>  server_session  = mtk::admin::get_qpid_session ("server", "SRVTESTING");   \
                static std::string  oms_current = mtk::admin::get_config_property("OMS_CHAIN.current").Get();        \
                std::string description = rq.reject_description;   \
                if(description =="")    \
                    description = check_request_quantity_filter(rq);   \
                mtk::trd::msg::__MESSAGE_TYPE__ msg (rq, description, oms_current);   \
                mtk::send_message(server_session, msg);   \
            }
            
    #define ON_RQ_PASS(__MESSAGE_TYPE__) \
            void on_##__MESSAGE_TYPE__(const mtk::trd::msg::__MESSAGE_TYPE__& rq)   \
            {   \
                static mtk::CountPtr<mtk::qpid_session>  server_session  = mtk::admin::get_qpid_session ("server", "SRVTESTING");   \
                mtk::trd::msg::__MESSAGE_TYPE__ msg (rq);   \
                mtk::send_message(server_session, msg);   \
            }
            



    ON_RQ_XX_XX(oms_RQ_NW_LS);
    ON_RQ_XX_XX(oms_RQ_MD_LS);
    ON_RQ_PASS(oms_RQ_CC_LS);

    ON_RQ_XX_XX(oms_RQ_NW_MK);
    ON_RQ_XX_XX(oms_RQ_MD_MK);
    ON_RQ_PASS(oms_RQ_CC_MK);

    //ON_RQ_PASS(oms_RQ_ORDERS_STATUS);





    struct  hqpid_rq_orders
    {
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::oms_RQ_NW_LS> >  oms_RQ_NW_LS;
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::oms_RQ_MD_LS> >  oms_RQ_MD_LS;
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::oms_RQ_CC_LS> >  oms_RQ_CC_LS;

        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::oms_RQ_NW_MK> >  oms_RQ_NW_MK;
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::oms_RQ_MD_MK> >  oms_RQ_MD_MK;
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::oms_RQ_CC_MK> >  oms_RQ_CC_MK;
        
        //mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::oms_RQ_ORDERS_STATUS> >  oms_RQ_ORDERS_STATUS;
    };
    
    void suscribe_order_request()
    {
        static  mtk::map<std::string /*map*/, hqpid_rq_orders >  map_hqpid_rqnwls;
        static std::string  oms_from = mtk::admin::get_config_property("OMS_CHAIN.from").Get();        \
        
        
        mtk::list<std::string>    markets = qfmgr::db::get_market_list();
        for(auto it= markets.begin(); it!=markets.end(); ++it)
        {
            hqpid_rq_orders  current_hqpid_orders;
            #define  CONNECT_RECEIVER_ORDER(__ORDER_TYPE__)   \
                MTK_QPID_RECEIVER_CONNECT_F(   \
                                        current_hqpid_orders.__ORDER_TYPE__,   \
                                        mtk::admin::get_url("server"),   \
                                        "SRVTESTING",   \
                                        mtk::trd::msg::__ORDER_TYPE__::get_in_subject(*it, "*", oms_from),   \
                                        mtk::trd::msg::__ORDER_TYPE__,   \
                                        on_##__ORDER_TYPE__)
            
            CONNECT_RECEIVER_ORDER(oms_RQ_NW_LS)
            CONNECT_RECEIVER_ORDER(oms_RQ_MD_LS)
            CONNECT_RECEIVER_ORDER(oms_RQ_CC_LS)

            CONNECT_RECEIVER_ORDER(oms_RQ_NW_MK)
            CONNECT_RECEIVER_ORDER(oms_RQ_MD_MK)
            CONNECT_RECEIVER_ORDER(oms_RQ_CC_MK)
            
//	    MTK_QPID_RECEIVER_CONNECT_F(
//				  current_hqpid_orders.oms_RQ_ORDERS_STATUS,
//				  mtk::admin::get_url("client"),
//				  "CLITESTING",
//				  mtk::trd::msg::oms_RQ_ORDERS_STATUS::get_in_subject("*", *it, oms_from),
//				  mtk::trd::msg::oms_RQ_ORDERS_STATUS,
//				  on_oms_RQ_ORDERS_STATUS)

	    map_hqpid_rqnwls.insert(std::make_pair(*it, current_hqpid_orders));
        }
    }
    
    //      ORDER FILTER ..........................................................................

 
};