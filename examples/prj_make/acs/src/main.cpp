#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"
#include "support/configfile.h"
#include "support/crc32.h"

#include "components/acs/msg_acs.h"

#include "users_manager.h"



namespace
{
    
    const char*   APP_NAME          = "GEN_ACS";
    const char*   APP_VER           = "2011-03-25";
    const char*   APP_DESCRIPTION   = "Access Control Server";

    const char*   APP_MODIFICATIONS = "           2011-03-25     first version\n";
    
    
    
    
}



void on_request_key_received(const mtk::acs::msg::req_login_key& req_login_key);
void on_request_login_received(const mtk::acs::msg::req_login& req_login);
void on_request_logout_received(const mtk::acs::msg::req_logout& req_logout);
void on_client_keep_alive_received(const mtk::admin::msg::pub_keep_alive_clients&  client_keep_alive);
void clean_timeout_requests(void);



mtk::CountPtr< mtk::qpid_session >  qpid_cli_session;
mtk::CountPtr<mtk::DateTime>        start_application;


//////////////////////////////////////////////////////////////////////////////
//
//  Data structures
//
//////////////////////////////////////////////////////////////////////////////

struct keys_sent_info
{
    keys_sent_info(const std::string& _user_name, const std::string& _key)
    :   user_name(_user_name), key(_key), dt_sent(mtk::dtNowLocal())  {}
    
    const std::string       user_name;
    const std::string       key;
    
    const mtk::DateTime     dt_sent;
};
mtk::CountPtr<mtk::list<keys_sent_info> >   list_key_sent;


struct sessions_login_info
{
    sessions_login_info(const mtk::admin::msg::pub_keep_alive_clients _keep_alive_client_info)
    :   keep_alive_client_info(_keep_alive_client_info), last_keep_alive_received(mtk::dtNowLocal())  {}
    
    mtk::admin::msg::pub_keep_alive_clients         keep_alive_client_info;
    
    mtk::DateTime                                   last_keep_alive_received;
};
mtk::CountPtr<mtk::list<sessions_login_info> >   list_sessions_login_info;




//---------------------------------------------------------------------------------------------------------
//      main
//---------------------------------------------------------------------------------------------------------

int main(int argc, char ** argv)
{
    
    
    
    try
    {
        start_application = mtk::make_cptr(new mtk::dtDateTime(mtk::dtNowLocal()));
        
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);

        qpid_cli_session =  mtk::admin::get_qpid_session("client", "CLITESTING");
        
        list_key_sent               =   mtk::make_cptr(new mtk::list<keys_sent_info>);
        list_sessions_login_info    =   mtk::make_cptr(new mtk::list<sessions_login_info>);
    

        //  suscription to request key
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::acs::msg::req_login_key> >    hqpid_key_request;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_key_request,
                                mtk::admin::get_url("client"),
                                "CLITESTING",
                                mtk::acs::msg::req_login_key::get_in_subject("*"),
                                mtk::acs::msg::req_login_key,
                                on_request_key_received)

        //  suscription to request login
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::acs::msg::req_login> >    hqpid_request_login;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_request_login,
                                mtk::admin::get_url("client"),
                                "CLITESTING",
                                mtk::acs::msg::req_login::get_in_subject("*"),
                                mtk::acs::msg::req_login,
                                on_request_login_received)

        //  suscription to request logout
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::acs::msg::req_logout> >    hqpid_request_logout;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_request_logout,
                                mtk::admin::get_url("client"),
                                "CLITESTING",
                                mtk::acs::msg::req_logout::get_in_subject("*"),
                                mtk::acs::msg::req_logout,
                                on_request_logout_received)

        //  suscription to keep alives
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_keep_alive_clients> >    hqpid_clients_keep_alive;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_clients_keep_alive,
                                mtk::admin::get_url("client"),
                                "CLITESTING",
                                mtk::admin::msg::pub_keep_alive_clients::get_in_subject(),
                                mtk::admin::msg::pub_keep_alive_clients,
                                on_client_keep_alive_received)


        MTK_TIMER_1SF(clean_timeout_requests)
    
        mtk::start_timer_wait_till_end();
        

        qpid_cli_session = mtk::CountPtr< mtk::qpid_session > ();
        std::cout << "FIN..... " << std::endl;
        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION (std::cout<< , "main", "nothing more")

    std::cout << "MAL..... " << std::endl;
    #include "support/release_on_exit.hpp"
    return -1;

}


//---------------------------------------------------------------------------------------------------------
//      end main
//---------------------------------------------------------------------------------------------------------







void on_request_key_received(const mtk::acs::msg::req_login_key& req_login_key)
{
    mtk::list<std::string>  data_list;
    
    std::string generated_key = mtk::crc32_as_string(MTK_SS(req_login_key << mtk::rand()));
    data_list.push_back( generated_key );
    
    keys_sent_info ksi(req_login_key.user_name, generated_key);
    list_key_sent->push_back(ksi);
    
    //  sending multiresponses in asyncronous way
    MTK_SEND_MULTI_RESPONSE(        mtk::acs::msg::res_login_key,
                                    std::string, 
                                    qpid_cli_session,
                                    req_login_key.request_info,
                                    data_list)
}


void on_request_login_received(const mtk::acs::msg::req_login& req_login)
{
    //  look for key and remove if located
    bool located=false;
    for(mtk::list<keys_sent_info>::iterator it = list_key_sent->begin(); it!=list_key_sent->end(); ++it)
    {
        if(it->key == req_login.key  &&  it->user_name==req_login.user_name)
        {
            located=true;
            list_key_sent->erase(it);
            break;
        }
    }
    
    
    //
    if(located)
    {
        //  verify password
        /*
        if(users_manager::Instance()->exists_user(req_login.user_name)  
                                &&  req_login.coded_pass== mtk::crc32_as_string(MTK_SS(req_login.user_name <<  users_manager::Instance()->get_passwordcrc32(req_login.user_name) << req_login.key)))
                                 */
        if(users_manager::Instance()->check_user_password(req_login.user_name, req_login.key, req_login.coded_pass))
        {
            static int counter=1;
            mtk::DateTime  dt_now(mtk::dtNowLocal());
            std::string  session_id = MTK_SS(   dt_now.GetYear().WarningDontDoThisGetInternal()
                                                <<dt_now.GetMonth().WarningDontDoThisGetInternal()
                                                <<dt_now.GetDay().WarningDontDoThisGetInternal()
                                                <<dt_now.GetHours().WarningDontDoThisGetInternal()
                                                <<dt_now.GetMinutes().WarningDontDoThisGetInternal()
                                                <<dt_now.GetSeconds().WarningDontDoThisGetInternal()
                                                <<counter);

            list_sessions_login_info->push_back(
                        sessions_login_info(
                                mtk::admin::msg::pub_keep_alive_clients(
                                        mtk::admin::msg::pub_keep_alive_srv(
                                                    mtk::msg::sub_process_info( req_login.request_info.process_location, 
                                                                                "."),
                                                    mtk::dtSeconds(90), 
                                                    mtk::dtSeconds(90)), 
                                        mtk::acs::msg::res_login::IC_login_response_info(req_login.user_name, session_id))));
            
            mtk::list<mtk::acs::msg::res_login::IC_login_response_info>  data_list;
            data_list.push_back(mtk::acs::msg::res_login::IC_login_response_info(req_login.user_name, session_id));
            
            //  sending multiresponses in asyncronous way
            MTK_SEND_MULTI_RESPONSE(        mtk::acs::msg::res_login,
                                            mtk::acs::msg::res_login::IC_login_response_info, 
                                            qpid_cli_session,
                                            req_login.request_info,
                                            data_list)
                                            
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS("created session "  << list_sessions_login_info->back().keep_alive_client_info << " for  " << req_login.request_info), mtk::alPriorDebug));
        }
        else
        {
            mtk::list<mtk::acs::msg::res_login::IC_login_response_info>  data_list;
            data_list.push_back(mtk::acs::msg::res_login::IC_login_response_info("", ""));
            
            //  sending multiresponses in asyncronous way
            MTK_SEND_MULTI_RESPONSE(        mtk::acs::msg::res_login,
                                            mtk::acs::msg::res_login::IC_login_response_info, 
                                            qpid_cli_session,
                                            req_login.request_info,
                                            data_list)
        }
    }
    else
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS(req_login.key << " for " << req_login.user_name << "  not located. Ignoring request"), 
                                            mtk::alPriorError, mtk::alTypeNoPermisions));
        

    
}


void on_request_logout_received(const mtk::acs::msg::req_logout& req_logout)
{
    //  look  in  sessions  and remove the item
    //  mtk::CountPtr<mtk::list<sessions_login_info> >   list_sessions_login_info;
    {
        mtk::list<sessions_login_info>::iterator it = list_sessions_login_info->begin();
        bool located = false;
        while(it!=list_sessions_login_info->end())
        {
            if(it->keep_alive_client_info.login_confirmation.session_id ==  req_logout.request_info.req_id.sess_id)
            {
                list_sessions_login_info->erase(it);
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS("deleting session " << req_logout.request_info.req_id.sess_id), mtk::alPriorError));
                located = true;
                break;
            }
            else
                ++it;
        }
        
        if(located==false)
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS("received logout with invalid session " << req_logout.request_info.req_id.sess_id), mtk::alPriorCritic));
    }
    
}



void clean_timeout_requests(void)
{
    MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(1))
        mtk::DateTime  now (mtk::dtNowLocal());
        
        
        //  look for timeout on request key
        //  mtk::CountPtr<mtk::list<keys_sent_info> >   list_key_sent;
        {
            mtk::list<keys_sent_info>::iterator it = list_key_sent->begin();
            while(it!=list_key_sent->end())
            {
                if(it->dt_sent + mtk::dtSeconds(40) < now)
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS("timeout on request key for... " << it->user_name), mtk::alPriorError));
                    it = list_key_sent->erase(it);
                }
                else
                    ++it;
            }
        }

        //  look for timeout on sessions
        //  mtk::CountPtr<mtk::list<sessions_login_info> >   list_sessions_login_info;
        {
            mtk::list<sessions_login_info>::iterator it = list_sessions_login_info->begin();
            while(it!=list_sessions_login_info->end())
            {
                if(it->last_keep_alive_received + it->keep_alive_client_info.ka_interval_check < now)
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS("generated logout by timeout on session... " << it->keep_alive_client_info), mtk::alPriorError));
                    //  remove from sessionid list
                    it = list_sessions_login_info->erase(it);
                    //  send logout messages to other servers
                }
                else
                    ++it;
            }
        }

    MTK_END_EXEC_MAX_FREC
}

void on_client_keep_alive_received(const mtk::admin::msg::pub_keep_alive_clients&  client_keep_alive)
{
        if(client_keep_alive.login_confirmation.session_id=="")     
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS("received keep alive with invalid session id " << client_keep_alive), mtk::alPriorError));
            return;
        }
    
        //  look  in  sessions
        //  mtk::CountPtr<mtk::list<sessions_login_info> >   list_sessions_login_info;
        {
            bool located=false;
            mtk::list<sessions_login_info>::iterator it = list_sessions_login_info->begin();
            while(it!=list_sessions_login_info->end())
            {
                if(it->keep_alive_client_info.login_confirmation.session_id ==  client_keep_alive.login_confirmation.session_id)
                {
                    if(it->keep_alive_client_info.login_confirmation.user_name !=  client_keep_alive.login_confirmation.user_name)
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS("user doesn't match on keep alive (user/ka) " << it->keep_alive_client_info  << "  /  " << client_keep_alive),
                                        mtk::alPriorCritic));
                    else
                    {
                        it->last_keep_alive_received = mtk::dtNowLocal();
                        it->keep_alive_client_info = client_keep_alive;
                    }
                    located = true;
                    break;
                }
                else
                    ++it;
            }
            if(located==false)
            {
                //  if application started few minutes ago, let this keep alive to be registered (but not notified to other processes)
                if(*start_application + mtk::dtMinutes(3) > mtk::dtNowLocal())
                {
                    list_sessions_login_info->push_back(sessions_login_info(client_keep_alive));
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS("hot register keep alive for  " << client_keep_alive), mtk::alPriorWarning));
                }
                else
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS("received keep alive with invalid session id " << client_keep_alive), mtk::alPriorCritic));
            }
        }
}
