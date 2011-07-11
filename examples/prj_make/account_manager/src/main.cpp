#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"
#include "db/db.h"
#include "components/acs/serv/acs_synchr.h"
#include "components/trading/msg_trd_cli_ls.h"
#include "components/trading/msg_trd_oms_rq.h"




namespace
{
    
    const char*   APP_NAME          = "GEN_ACCOUNT_MANAGER";
    const char*   APP_VER           = "2011-05-30";
    const char*   APP_DESCRIPTION   = "I can do two things\n"
                                      "I can send check all order request from client in order to verify the user is logged and account is valid, \n"
                                      "filling the reject_description if necessary and sending the request to order flow control\n"
                                      "\n"
                                      "I can also receive and response to request accounts\n"
                                      "Generally I will work with one of the possibilities. I will be configured with both, only in case of problems\n"
                                      "\n";
                                      
    const char*   APP_MODIFICATIONS = "           2011-05-30     first version\n";
    


    void command_send_user_accounts(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    
    void register_global_commands (void)
    {
        mtk::admin::register_command("accmgr",  "send_user_accounts",     "<user-name>")->connect(command_send_user_accounts);
    }
    
    
    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)    
    
    
    void susbcribe_request_accounts(void);
    void suscribe_recovery_subject(void);
    void suscribe_order_request();
}







int main(int argc, char ** argv)
{
    try
    {
        if(argc==1)
            mtk::admin::init("./config_acc_filter.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        
    
        accmgr::db::init(mtk::admin::get_config_property("MISC.db_file").Get());    //  if property doesn't exists program it will finish with exception
        
        
        if(mtk::admin::get_config_property("MISC.account_loader").Get() == "true")
        {
            mtk::acs_server::synchr::get_signal_received_user_list()->connect(suscribe_recovery_subject);
            mtk::acs_server::synchr::init();
            susbcribe_request_accounts();
        }

        if(mtk::admin::get_config_property("MISC.account_filter").Get() == "true")
        {
            mtk::acs_server::synchr::init();
            suscribe_order_request();
        }



        mtk::start_timer_wait_till_end();
    
        
        accmgr::db::purge();
        accmgr::db::save();
    

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
    
    void on_request_accounts(const mtk::trd::account::msg::rq_accounts&  rq_accounts);
    void on_rq_accounts_oninit(const mtk::trd::account::msg::rq_accounts_oninit&  rqinit)
    {
        on_request_accounts(mtk::trd::account::msg::rq_accounts(rqinit.request_info));
    }
    
    void suscribe_recovery_subject(void)
    {
        std::string  request_sufix_subject = mtk::admin::get_process_info().process_uuid;
        
        //  suscription to request key
        static mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::account::msg::rq_accounts_oninit> >    hqpid_rq_accounts_oninit;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_rq_accounts_oninit,
                                mtk::admin::get_url("client"),
                                "CLITESTING",
                                mtk::trd::account::msg::rq_accounts_oninit::get_in_subject(request_sufix_subject),
                                mtk::trd::account::msg::rq_accounts_oninit,
                                on_rq_accounts_oninit)



        mtk::trd::account::msg::pub_accmgr_init msg_init(mtk::admin::get_process_info(), request_sufix_subject);
        mtk::send_message(mtk::admin::get_qpid_session("client", "CLITESTING"), msg_init);
    }
    


    void add_accounts_fragmenting(const mtk::acs::msg::res_login::IC_session_info& session_info, const mtk::list<mtk::trd::account::msg::sub_grant>& user_grants)
    {
        static mtk::CountPtr<mtk::qpid_session>  qpid_session = mtk::admin::get_qpid_session("client", "CLITESTING");
        const unsigned  max_grants_per_message = 8;
        mtk::list<mtk::trd::account::msg::sub_grant>  partial_user_grants;
        unsigned  grants_in_packet = 0;
        for(auto it_grants = user_grants.begin(); it_grants != user_grants.end(); ++it_grants)
        {
            partial_user_grants.push_back(*it_grants);
            ++grants_in_packet;
            if(grants_in_packet == max_grants_per_message)
            {
                mtk::trd::account::msg::add_accounts msg(session_info, partial_user_grants);
                mtk::send_message(qpid_session, msg);
                grants_in_packet = 0;
                partial_user_grants.clear();
            }
        }
        if(partial_user_grants.size() > 0)
        {
            mtk::trd::account::msg::add_accounts msg(session_info, partial_user_grants);
            mtk::send_message(qpid_session, msg);
        }
    }
    
    void on_request_accounts(const mtk::trd::account::msg::rq_accounts&  rq_accounts)
    {
        mtk::msg::sub_location      location    =   rq_accounts.request_info.process_info.location;
        std::string                 session_id  =   rq_accounts.request_info.req_id.session_id;
        std::string                 client_code =   location.client_code;
        
        mtk::acs::msg::res_login::IC_session_info  session_info =  mtk::acs_server::synchr::get_session_info_for_session_id(session_id);
        std::string                 user_name   =  mtk::s_toUpper(session_info.user_name);
        if(rq_accounts.request_info.process_info.location.client_code != "CIMD")
        {
            if(rq_accounts.request_info.process_info.location.client_code !=  session_info.client_code)
                throw mtk::Alarm(MTK_HERE, "accmgr", MTK_SS("Received account doesn't match with session_info account " <<
                                            rq_accounts << "   " << session_info), mtk::alPriorCritic, mtk::alTypeLogicError);
        }
        add_accounts_fragmenting(session_info, accmgr::db::get_user_grants(user_name, client_code));
    }
    
    
    void susbcribe_request_accounts(void)
    {
        //  suscription to request key
        static mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::account::msg::rq_accounts> >    hqpid_rq_accounts;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_rq_accounts,
                                mtk::admin::get_url("client"),
                                "CLITESTING",
                                mtk::trd::account::msg::rq_accounts::get_in_subject("*"),
                                mtk::trd::account::msg::rq_accounts,
                                on_request_accounts)
        
    }
    
  

    void command_send_user_accounts(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        std::string user_name = mtk::s_toUpper(mtk::s_split(mtk::s_trim(params, ' '), " ")[0]);
        //mtk::list<mtk::trd::account::msg::sub_grant>        get_user_grants(const std::string& user_name, const std::string& client_code);
        static mtk::CountPtr<mtk::qpid_session>  qpid_session = mtk::admin::get_qpid_session("client", "CLITESTING");

        mtk::list<mtk::acs::msg::res_login::IC_session_info>   list_sessions =  mtk::acs_server::synchr::bad_performance_get_sessions_info(user_name);
        for(auto it_session_info = list_sessions.begin(); it_session_info!=list_sessions.end(); ++it_session_info)
        {
            std::string                 client_code =  it_session_info->client_code;

            add_accounts_fragmenting(*it_session_info, accmgr::db::get_user_grants(user_name, client_code));
            
            response_lines.push_back(MTK_SS ("sent accounts to " << user_name << "  " << *it_session_info));
        }
        response_lines.push_back("  <<< end of command");
    }
  


    
    
    //      ORDER FILTER ..........................................................................
    std::string   get_order_grant_type (const mtk::trd::msg::RQ_XX&  rq)
    {
        return  accmgr::db::get_grant_type(rq.request_info.req_id, rq.invariant.product_code.market, rq.invariant.account);
    }


    #define ON_RQ_XX_XX(__MESSAGE_TYPE__, __GRANT_TYPE__) \
            void on_##__MESSAGE_TYPE__(const mtk::trd::msg::__MESSAGE_TYPE__& rq)   \
            {   \
                static mtk::CountPtr<mtk::qpid_session>  server_session  = mtk::admin::get_qpid_session ("server", "SRVTESTING");   \
                   \
                std::string description;   \
                bool granted=false;   \
                if(get_order_grant_type(rq) == "F")   \
                    granted = true;   \
                else if (get_order_grant_type(rq) == "C"  &&  std::string(__GRANT_TYPE__) == std::string("C"))   \
                    granted = true;   \
                if(!granted)   \
                    description = "account not granted";   \
                mtk::trd::msg::oms_##__MESSAGE_TYPE__ msg (rq, description);   \
                mtk::send_message(server_session, msg);   \
            }

    ON_RQ_XX_XX(RQ_NW_LS, "F");
    ON_RQ_XX_XX(RQ_MD_LS, "F");
    ON_RQ_XX_XX(RQ_CC_LS, "C");

    ON_RQ_XX_XX(RQ_NW_MK, "F");
    ON_RQ_XX_XX(RQ_MD_MK, "F");
    ON_RQ_XX_XX(RQ_CC_MK, "C");



    struct  hqpid_rq_orders
    {
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RQ_NW_LS> >  RQ_NW_LS;
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RQ_MD_LS> >  RQ_MD_LS;
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RQ_CC_LS> >  RQ_CC_LS;

        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RQ_NW_MK> >  RQ_NW_MK;
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RQ_MD_MK> >  RQ_MD_MK;
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RQ_CC_MK> >  RQ_CC_MK;
    };
    
    void suscribe_order_request()
    {
        static  mtk::map<std::string /*map*/, hqpid_rq_orders >  map_hqpid_rqnwls;
        
        mtk::list<std::string>    markets = accmgr::db::get_market_list();
        for(auto it= markets.begin(); it!=markets.end(); ++it)
        {
            hqpid_rq_orders  current_hqpid_orders;
            #define  CONNECT_RECEIVER_ORDER(__ORDER_TYPE__)   \
                MTK_QPID_RECEIVER_CONNECT_F(   \
                                        current_hqpid_orders.__ORDER_TYPE__,   \
                                        mtk::admin::get_url("client"),   \
                                        "CLITESTING",   \
                                        mtk::trd::msg::__ORDER_TYPE__::get_in_subject("*", *it, "*", "*"),   \
                                        mtk::trd::msg::__ORDER_TYPE__,   \
                                        on_##__ORDER_TYPE__)
            
            CONNECT_RECEIVER_ORDER(RQ_NW_LS)
            CONNECT_RECEIVER_ORDER(RQ_MD_LS)
            CONNECT_RECEIVER_ORDER(RQ_CC_LS)

            CONNECT_RECEIVER_ORDER(RQ_NW_MK)
            CONNECT_RECEIVER_ORDER(RQ_MD_MK)
            CONNECT_RECEIVER_ORDER(RQ_CC_MK)
            map_hqpid_rqnwls.insert(std::make_pair(*it, current_hqpid_orders));
        }
    }
    //      ORDER FILTER ..........................................................................

 
};