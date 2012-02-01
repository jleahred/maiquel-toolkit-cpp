#include <iostream>
#include <iomanip>


#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"
#include "support/configfile.h"
#include "support/crc32.h"

#include "components/acs/msg_acs.h"

#include "users_manager.h"
#include "components/acs/serv/msg_acs_server.h"



namespace
{

    const char*   APP_NAME          = "GEN_ACS";
    const char*   APP_VER           = "2011-05-24";
    const char*   APP_DESCRIPTION   = "Access Control Server";

    const char*   APP_MODIFICATIONS = "           2011-03-25     first version\n"
                                      "           2011-05-24     servers synchronization\n";



    void command_list_sessions(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_logout(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_lock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_unlock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);


    void register_global_commands (void)
    {
        //mtk::admin::register_command("__GLOBAL__",  "ver",   "")->connect(command_version);
        mtk::admin::register_command("__GLOBAL__",  "stats",     "")->connect(command_stats);
        mtk::admin::register_command("sessions",  "stats",     "")->connect(command_stats);
        mtk::admin::register_command("sessions",  "list",       "list of valid sessions")->connect(command_list_sessions);
        mtk::admin::register_command("sessions",  "logout",     "generate a logout for a specific session", true)->connect(command_logout);
        mtk::admin::register_command("sessions",  "lock_logings",     "lock new login request", true)->connect(command_lock);
        mtk::admin::register_command("sessions",  "unlock_logings",     "lock new login request", true)->connect(command_unlock);
    }


    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)
}



void on_request_key_received(const mtk::acs::msg::req_login_key& req_login_key);
void on_request_login_received(const mtk::acs::msg::req_login& req_login);
void on_request_logout_received(const mtk::acs::msg::req_logout& req_logout);
void on_request_change_password_received(const mtk::acs::msg::req_change_password& req_change_password);
void on_client_keep_alive_received(const mtk::admin::msg::pub_keep_alive_cli&  client_keep_alive);
void on_server_req_session_id_conf(const mtk::acs_server::msg::req_session_id_conf&  req_session_id_conf);
void on_server_pub_partial_user_list_serv2acs(const mtk::acs_server::msg::pub_partial_user_list_serv2acs&);
void on_server_req_user_list(const mtk::acs_server::msg::req_user_list&);
void clean_timeout_requests(void);
void timer_send_partial_login_confirmation(void);



mtk::CountPtr<mtk::DateTime>            start_application;


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
    sessions_login_info(const mtk::admin::msg::pub_keep_alive_cli _keep_alive_client_info)
    :   keep_alive_client_info(_keep_alive_client_info), last_keep_alive_received(mtk::dtNowLocal())  {}

    mtk::admin::msg::pub_keep_alive_cli             keep_alive_client_info;

    mtk::DateTime                                   last_keep_alive_received;
};
mtk::CountPtr<mtk::list<sessions_login_info> >   list_sessions_login_info;

static bool   rq_login_locked = false;




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

        users_manager::init();

        list_key_sent               =   mtk::make_cptr(new mtk::list<keys_sent_info>);
        list_sessions_login_info    =   mtk::make_cptr(new mtk::list<sessions_login_info>);


        //  suscription to request key
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::acs::msg::req_login_key> >    hqpid_key_request;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_key_request,
                                mtk::admin::get_url("client"),
                                mtk::acs::msg::req_login_key::get_in_subject("*"),
                                mtk::acs::msg::req_login_key,
                                on_request_key_received)

        //  suscription to request login
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::acs::msg::req_login> >    hqpid_request_login;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_request_login,
                                mtk::admin::get_url("client"),
                                mtk::acs::msg::req_login::get_in_subject("*"),
                                mtk::acs::msg::req_login,
                                on_request_login_received)

        //  suscription to request logout
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::acs::msg::req_logout> >    hqpid_request_logout;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_request_logout,
                                mtk::admin::get_url("client"),
                                mtk::acs::msg::req_logout::get_in_subject("*"),
                                mtk::acs::msg::req_logout,
                                on_request_logout_received)

        //  suscription to change password
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::acs::msg::req_change_password> >    hqpid_request_change_password;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_request_change_password,
                                mtk::admin::get_url("client"),
                                mtk::acs::msg::req_change_password::get_in_subject("*"),
                                mtk::acs::msg::req_change_password,
                                on_request_change_password_received)


        //  suscription to keep alives
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_keep_alive_cli> >    hqpid_clients_keep_alive;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_clients_keep_alive,
                                mtk::admin::get_url("client"),
                                mtk::admin::msg::pub_keep_alive_cli::get_in_subject("*"),
                                mtk::admin::msg::pub_keep_alive_cli,
                                on_client_keep_alive_received)

        //  suscription to req_session_id_conf
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::acs_server::msg::req_session_id_conf> >    hqpid_serv_req_session_id_conf;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_serv_req_session_id_conf,
                                mtk::admin::get_url("server"),
                                mtk::acs_server::msg::req_session_id_conf::get_in_subject("*"),
                                mtk::acs_server::msg::req_session_id_conf,
                                on_server_req_session_id_conf)

        //  suscription to  pub_partial_user_list_serv2acs
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::acs_server::msg::pub_partial_user_list_serv2acs> >    hqpid_serv_pub_partial_user_list_serv2acs;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_serv_pub_partial_user_list_serv2acs,
                                mtk::admin::get_url("server"),
                                mtk::acs_server::msg::pub_partial_user_list_serv2acs::get_in_subject("*"),
                                mtk::acs_server::msg::pub_partial_user_list_serv2acs,
                                on_server_pub_partial_user_list_serv2acs)

        //  suscription to  req_session_id_conf
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::acs_server::msg::req_user_list> >    hqpid_serv_req_user_list;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_serv_req_user_list,
                                mtk::admin::get_url("server"),
                                mtk::acs_server::msg::req_user_list::get_in_subject("*"),
                                mtk::acs_server::msg::req_user_list,
                                on_server_req_user_list)



        MTK_TIMER_1SF(clean_timeout_requests)
        MTK_TIMER_1SF(timer_send_partial_login_confirmation)

        mtk::start_timer_wait_till_end();


        users_manager::save_user_list();

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
    if(rq_login_locked==true)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "rqkeyrec", MTK_SS("System locked  " << req_login_key.user_name << "/" << req_login_key.request_info.process_info.location.broker_code), mtk::alPriorError, mtk::alTypeNoPermisions));
        return;
    }


    //  check the client code
    if(users_manager::check_user_client_code(req_login_key.user_name, req_login_key.request_info.process_info.location.broker_code) == false)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "rqkeyrec", MTK_SS("received invalid  user_name/client_code  " << req_login_key.user_name << "/" << req_login_key.request_info.process_info.location.broker_code), mtk::alPriorError, mtk::alTypeNoPermisions));
        return;
    }


    mtk::list<std::string>  data_list;

    std::string generated_key = mtk::crc32_as_string(MTK_SS(req_login_key << mtk::rand()));
    data_list.push_back( generated_key );

    keys_sent_info ksi(req_login_key.user_name, generated_key);
    list_key_sent->push_back(ksi);

    //  sending multiresponses in asyncronous way
    MTK_SEND_MULTI_RESPONSE(        mtk::acs::msg::res_login_key,
                                    std::string,
                                    mtk::admin::get_url("client"),
                                    req_login_key.request_info,
                                    data_list)
}


void on_request_login_received(const mtk::acs::msg::req_login& req_login)
{
    if(rq_login_locked==true)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "rqlogrec", MTK_SS("System locked  " << req_login.user_name << "/" << req_login.request_info.process_info.location.broker_code), mtk::alPriorError, mtk::alTypeNoPermisions));
        return;
    }

    //  check the client code
    if(users_manager::check_user_client_code(req_login.user_name, req_login.request_info.process_info.location.broker_code) == false)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "rqlogrec", MTK_SS("received invalid  user_name/client_code  " << req_login.user_name << "/" << req_login.request_info.process_info.location.broker_code), mtk::alPriorError, mtk::alTypeNoPermisions));
        return;
    }


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
        if(users_manager::check_user_password(req_login.user_name, req_login.key, req_login.coded_pass))
        {
            static int counter=0;
            ++counter;
            counter %= 100;
            static int duplicated_session_id_prefix=0;
            mtk::DateTime  dt_now(mtk::dtNowLocal());
            static std::string prev_session_id_prefix;
            std::string  session_id_prefix = MTK_SS(   dt_now.GetYear().WarningDontDoThisGetInternal()
                                                << std::setw(2)  << std::setfill('0')
                                                <<dt_now.GetMonth().WarningDontDoThisGetInternal()
                                                << std::setw(2)  << std::setfill('0')
                                                <<dt_now.GetDay().WarningDontDoThisGetInternal()
                                                << std::setw(2)  << std::setfill('0')
                                                <<dt_now.GetHours().WarningDontDoThisGetInternal()
                                                << std::setw(2)  << std::setfill('0')
                                                <<dt_now.GetMinutes().WarningDontDoThisGetInternal()
                                                << std::setw(2)  << std::setfill('0')
                                                <<dt_now.GetSeconds().WarningDontDoThisGetInternal());
            if(prev_session_id_prefix  ==  session_id_prefix)
            {
                ++duplicated_session_id_prefix;
                duplicated_session_id_prefix %=100;
            }
            std::string  session_id = MTK_SS(   session_id_prefix
                                            << std::setw(2)  << std::setfill('0')
                                            <<  counter
                                            << std::setw(2)  << std::setfill('0')
                                            << duplicated_session_id_prefix  );


            mtk::acs::msg::res_login::IC_session_info session_info(req_login.user_name, req_login.request_info.process_info.location.broker_code,  session_id);
                    //  yes, we respond with request info. It was checked previusly

            list_sessions_login_info->push_back(
                        sessions_login_info(
                                mtk::admin::msg::pub_keep_alive_cli(
                                        mtk::admin::msg::pub_keep_alive_srv(
                                                    mtk::msg::sub_process_info( req_login.request_info.process_info),
                                                    mtk::dtSeconds(90),
                                                    mtk::dtSeconds(90)),
                                                    session_info)));

            mtk::list<mtk::acs::msg::res_login::IC_session_info>  data_list;
            data_list.push_back(session_info);


	    //	notify servers before sending the confirmation to client
            mtk::acs_server::msg::pub_add_user  msg_add_user  (mtk::admin::get_process_info().location.broker_code, session_info);
            mtk_send_message("server", msg_add_user);


            //  sending multiresponses in asyncronous way
            MTK_SEND_MULTI_RESPONSE(        mtk::acs::msg::res_login,
                                            mtk::acs::msg::res_login::IC_session_info,
                                            mtk::admin::get_url("server"),
                                            req_login.request_info,
                                            data_list)

            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "rqlogrec", MTK_SS("created session "  << list_sessions_login_info->back().keep_alive_client_info << " for  " << req_login.request_info), mtk::alPriorDebug));
        }
        else
        {
            mtk::list<mtk::acs::msg::res_login::IC_session_info>  data_list;
            data_list.push_back(mtk::acs::msg::res_login::IC_session_info("", "", ""));

            //  sending multiresponses in asyncronous way
            MTK_SEND_MULTI_RESPONSE(        mtk::acs::msg::res_login,
                                            mtk::acs::msg::res_login::IC_session_info,
                                            mtk::admin::get_url("server"),
                                            req_login.request_info,
                                            data_list)
        }
    }
    else
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "rqlogrec", MTK_SS(req_login.key << " for " << req_login.user_name << "  not located. Ignoring request"),
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
            if(it->keep_alive_client_info.login_confirmation.session_id ==  req_logout.request_info.req_id.session_id)
            {
                mtk::acs_server::msg::pub_del_user msg_del_user(mtk::admin::get_process_info().location.broker_code, it->keep_alive_client_info.login_confirmation);
                it = list_sessions_login_info->erase(it);
                mtk_send_message("server", msg_del_user);
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "rqlogoutrec", MTK_SS("deleting session " << req_logout.request_info.req_id.session_id), mtk::alPriorDebug));
                located = true;
                break;
            }
            else
                ++it;
        }

        if(located==false)
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "rqlogoutrec", MTK_SS("received logout with invalid session " << req_logout.request_info.req_id.session_id), mtk::alPriorCritic));
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
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "cleantimeout",  MTK_SS("timeout on request key for... " << it->user_name), mtk::alPriorError));
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
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE,"cleantimeout", MTK_SS("generated logout by timeout on session... " << it->keep_alive_client_info), mtk::alPriorError));
                    //  remove from sessionid list
                    //  send logout messages to other servers
                    mtk::acs_server::msg::pub_del_user msg_del_user(mtk::admin::get_process_info().location.broker_code, it->keep_alive_client_info.login_confirmation);
                    mtk_send_message("server", msg_del_user);
                    it = list_sessions_login_info->erase(it);
                }
                else
                    ++it;
            }
        }

    MTK_END_EXEC_MAX_FREC
}

void on_client_keep_alive_received(const mtk::admin::msg::pub_keep_alive_cli&  client_keep_alive)
{
        if(     (client_keep_alive.login_confirmation.session_id==""
            ||  client_keep_alive.login_confirmation.client_code == ""
            ||  client_keep_alive.login_confirmation.user_name == "")
            &&  MTK_SS(client_keep_alive.login_confirmation.session_id
                    <<  client_keep_alive.login_confirmation.client_code
                    <<  client_keep_alive.login_confirmation.user_name) != "")
        {
            MTK_EXEC_MAX_FREC_NO_FIRST_S(mtk::dtMinutes(1))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "clikeepaliverec", MTK_SS("received keep alive with empty session id " << client_keep_alive), mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
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
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE,"clikeepaliverec", MTK_SS("user doesn't match on keep alive (user/ka) " << it->keep_alive_client_info  << "  /  " << client_keep_alive),
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
            if(located==false  &&  client_keep_alive.login_confirmation.session_id!="")
            {
                //  if application started few minutes ago, let this keep alive to be registered (but not notified to other processes)
                if(*start_application + mtk::dtMinutes(3) > mtk::dtNowLocal())
                {
                    list_sessions_login_info->push_back(sessions_login_info(client_keep_alive));
                    mtk::acs_server::msg::pub_add_user  msg_add_user (mtk::admin::get_process_info().location.broker_code, client_keep_alive.login_confirmation);
                    mtk_send_message("server", msg_add_user);
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE,"clikeepaliverec", MTK_SS("hot register keep alive for  " << client_keep_alive), mtk::alPriorWarning));
                }
                else
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE,"clikeepaliverec", MTK_SS("received keep alive with not registered sessionid. It will be ignored" << client_keep_alive), mtk::alPriorCritic));
            }
        }
}


mtk::acs::msg::res_login::IC_session_info  get_session_info__from_session_id(const std::string& session_id)
{
    //    struct sessions_login_info
    //    {
    //        sessions_login_info(const mtk::admin::msg::pub_keep_alive_clients _keep_alive_client_info)
    //        :   keep_alive_client_info(_keep_alive_client_info), last_keep_alive_received(mtk::dtNowLocal())  {}
    //
    //        mtk::admin::msg::pub_keep_alive_clients         keep_alive_client_info;
    //
    //        mtk::DateTime                                   last_keep_alive_received;
    //    };
    //    mtk::CountPtr<mtk::list<sessions_login_info> >   list_sessions_login_info;
    for(mtk::list<sessions_login_info>::iterator it = list_sessions_login_info->begin(); it!=list_sessions_login_info->end(); ++it)
    {
        if(it->keep_alive_client_info.login_confirmation.session_id == session_id)
            return it->keep_alive_client_info.login_confirmation;
    }
    throw mtk::Alarm(MTK_HERE, "clikeepaliverec", MTK_SS("session not found for sessionid " << session_id), mtk::alPriorError);
}




void on_server_req_session_id_conf(const mtk::acs_server::msg::req_session_id_conf&  req_session_id_conf)
{
    //  notif alarm
    //  look for session id
    //  send partial list with this session id

    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "acs request sessid conf", MTK_SS("Requested session confirmation for...  " << req_session_id_conf.session_id
                    << std::endl << req_session_id_conf), mtk::alPriorError, mtk::alTypeNoPermisions));
    if(list_sessions_login_info.isValid()  &&  list_sessions_login_info->size() > 0)
    {
        std::string session_id = req_session_id_conf.session_id;
        mtk::acs::msg::res_login::IC_session_info  session_info = get_session_info__from_session_id(session_id);

        mtk::list<mtk::acs::msg::res_login::IC_session_info>   partial_list_users;
        mtk::acs::msg::res_login::IC_session_info  login_response_info(session_info);
        partial_list_users.push_back(login_response_info);
        mtk::acs_server::msg::pub_partial_user_list_acs2serv msg(mtk::admin::get_process_info().location.broker_code, partial_list_users);
        mtk_send_message("server", msg);
    }
}


void on_request_change_password_received(const mtk::acs::msg::req_change_password& req_change_password)
{
    //  look for key and remove if located
    bool located=false;
    for(mtk::list<keys_sent_info>::iterator it = list_key_sent->begin(); it!=list_key_sent->end(); ++it)
    {
        if(it->key == req_change_password.key  &&  it->user_name==req_change_password.user_name)
        {
            located=true;
            list_key_sent->erase(it);
            break;
        }
    }


    //
    if(located)
    {
        mtk::acs::msg::res_login::IC_session_info  session_info = get_session_info__from_session_id(req_change_password.request_info.req_id.session_id);
        if(session_info.user_name !=  req_change_password.user_name  ||  req_change_password.user_name=="")
            throw mtk::Alarm(MTK_HERE, "rqchangpwd", MTK_SS("user name doesn't match  " << req_change_password  << "   "  << session_info.user_name), mtk::alPriorError, mtk::alTypeNoPermisions);
        else if (session_info.client_code !=  req_change_password.request_info.process_info.location.broker_code)
            throw mtk::Alarm(MTK_HERE, "rqchangpwd", MTK_SS("client code name doesn't match  " << req_change_password  << "   "  << session_info.user_name), mtk::alPriorError, mtk::alTypeNoPermisions);

        std::string decoded_new_password = users_manager::decode_modif_password(    req_change_password.user_name,
                                                                                                req_change_password.key,
                                                                                                req_change_password.new_password);
        //  verify password
        if(users_manager::check_user_password(req_change_password.user_name, req_change_password.key, req_change_password.old_password))
        {
            users_manager::save_new_password(req_change_password.user_name, decoded_new_password);

            mtk::list<mtk::acs::msg::res_change_password::IC_change_password_info>  data_list;
            data_list.push_back(mtk::acs::msg::res_change_password::IC_change_password_info(true));

            //  sending multiresponses in asyncronous way
            MTK_SEND_MULTI_RESPONSE(        mtk::acs::msg::res_change_password,
                                            mtk::acs::msg::res_change_password::IC_change_password_info,
                                            mtk::admin::get_url("server"),
                                            req_change_password.request_info,
                                            data_list)

            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,"rqchangpwd", MTK_SS("password modified to:  " << req_change_password.user_name), mtk::alPriorDebug));
        }
        else
        {
            mtk::list<mtk::acs::msg::res_change_password::IC_change_password_info>  data_list;
            data_list.push_back(mtk::acs::msg::res_change_password::IC_change_password_info(false));

            //  sending multiresponses in asyncronous way
            MTK_SEND_MULTI_RESPONSE(        mtk::acs::msg::res_change_password,
                                            mtk::acs::msg::res_change_password::IC_change_password_info,
                                            mtk::admin::get_url("server"),
                                            req_change_password.request_info,
                                            data_list)

            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,"rqchangpwd", MTK_SS("rejected password modif to:  " << req_change_password.user_name), mtk::alPriorDebug));
        }
    }
    else
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE,"rqchangpwd", MTK_SS(req_change_password.key << " for " << req_change_password.user_name << "  not located. Ignoring request"),
                                            mtk::alPriorError, mtk::alTypeNoPermisions));

}



void timer_send_partial_login_confirmation(void)
{
    //    struct sessions_login_info
    //    {
    //        sessions_login_info(const mtk::admin::msg::pub_keep_alive_clients _keep_alive_client_info)
    //        :   keep_alive_client_info(_keep_alive_client_info), last_keep_alive_received(mtk::dtNowLocal())  {}
    //
    //        mtk::admin::msg::pub_keep_alive_clients         keep_alive_client_info;
    //
    //        mtk::DateTime                                   last_keep_alive_received;
    //    };
    //    mtk::CountPtr<mtk::list<sessions_login_info> >   list_sessions_login_info;

    MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(5))
        if(list_sessions_login_info.isValid()  &&  list_sessions_login_info->size() > 0)
        {
            static int static_skip = 0;
            int skip = static_skip;

            int count_prepared2send=0;
            mtk::list<mtk::acs::msg::res_login::IC_session_info>   partial_list_users;
            for(mtk::list<sessions_login_info>::iterator it=list_sessions_login_info->begin(); it!=list_sessions_login_info->end(); ++it)
            {
                if(--skip > 0)      continue;

                if(count_prepared2send < 10)
                {
                    partial_list_users.push_back(it->keep_alive_client_info.login_confirmation);
                    ++count_prepared2send;
                }
                else        break;

            }
	    static_skip += 10;
	    if(unsigned(static_skip) >= list_sessions_login_info->size())
		static_skip = 0;

            if(partial_list_users.size()>0)
            {
                mtk::acs_server::msg::pub_partial_user_list_acs2serv msg(mtk::admin::get_process_info().location.broker_code, partial_list_users);
                mtk_send_message("server", msg);
            }

        }
    MTK_END_EXEC_MAX_FREC
}




void on_server_pub_partial_user_list_serv2acs(const mtk::acs_server::msg::pub_partial_user_list_serv2acs&  pub_partial_user_list_serv2acs)
{
    //  iterate all user-sessions
    //  notify and send delete message on non valid sessions

    mtk::list<mtk::acs::msg::res_login::IC_session_info>   partial_list_users = pub_partial_user_list_serv2acs.list_login_confirmation;
    for(mtk::list<mtk::acs::msg::res_login::IC_session_info>::const_iterator it = partial_list_users.begin(); it!= partial_list_users.end(); ++it)
    {
        mtk::acs::msg::res_login::IC_session_info  session_info = *it;

        bool located = false;
        for(mtk::list<sessions_login_info>::iterator it2 = list_sessions_login_info->begin(); it2!=list_sessions_login_info->end(); ++it2)
        {
            if(it2->keep_alive_client_info.login_confirmation.session_id == session_info.session_id  &&  it2->keep_alive_client_info.login_confirmation.user_name == session_info.user_name)
                located = true;
        }
        if(!located)
        {
            mtk::acs_server::msg::pub_del_user msg_del_user(mtk::admin::get_process_info().location.broker_code, session_info);
            mtk_send_message("server",  msg_del_user);
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,"acs_user_list_serv2acs", MTK_SS("Not registered sessionid, could be a concurrency behaviour sending delete  "
                                                << session_info), mtk::alPriorError, mtk::alTypeNoPermisions));
        }
    }
}


void on_server_req_user_list(const mtk::acs_server::msg::req_user_list& req_user_list)
{
    mtk::list< mtk::list<mtk::acs::msg::res_login::IC_session_info> >   full_response;
    int counter=0;
    mtk::list<mtk::acs::msg::res_login::IC_session_info>  list_items;
    for(mtk::list<sessions_login_info>::iterator it = list_sessions_login_info->begin(); it!=list_sessions_login_info->end(); ++it)
    {
        list_items.push_back(it->keep_alive_client_info.login_confirmation);
        ++counter;
        if(counter%10 == 0)
        {
            full_response.push_back(list_items);
            list_items.clear();
        }
    }
    if(list_items.size() > 0)
        full_response.push_back(list_items);


    MTK_SEND_MULTI_RESPONSE(        mtk::acs_server::msg::res_user_list,
                                    mtk::list<mtk::acs::msg::res_login::IC_session_info>,
                                    mtk::admin::get_url("server"),
                                    req_user_list.request_info,
                                    full_response)
}











namespace {  //  commands

void command_list_sessions(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    //    struct sessions_login_info
    //    {
    //        sessions_login_info(const mtk::admin::msg::pub_keep_alive_clients _keep_alive_client_info)
    //        :   keep_alive_client_info(_keep_alive_client_info), last_keep_alive_received(mtk::dtNowLocal())  {}
    //
    //        mtk::admin::msg::pub_keep_alive_clients         keep_alive_client_info;
    //
    //        mtk::DateTime                                   last_keep_alive_received;
    //    };
    //    mtk::CountPtr<mtk::list<sessions_login_info> >   list_sessions_login_info;
    for(mtk::list<sessions_login_info>::iterator it = list_sessions_login_info->begin(); it!=list_sessions_login_info->end(); ++it)
            response_lines.push_back(MTK_SS(it->keep_alive_client_info));
    response_lines.push_back("end response sessions list");
}

void command_logout(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    std::string  session_id = mtk::s_trim(params, " \t");
    for(mtk::list<sessions_login_info>::iterator it = list_sessions_login_info->begin(); it!=list_sessions_login_info->end(); ++it)
    {
        if(it->keep_alive_client_info.login_confirmation.session_id == session_id)
        {
            mtk::acs::msg::conf_logout conf_logout(it->keep_alive_client_info.process_info.location, session_id, "requested by command");
            mtk_send_message("client", conf_logout);

            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,"rqchangpwd", MTK_SS("logout command processed for " << session_id << "  user " << it->keep_alive_client_info.login_confirmation.user_name), mtk::alPriorWarning));
            response_lines.push_back(MTK_SS("logout command processed for " << session_id << "  user " << it->keep_alive_client_info.login_confirmation.user_name));
            mtk::acs_server::msg::pub_del_user msg_del_user(mtk::admin::get_process_info().location.broker_code, it->keep_alive_client_info.login_confirmation);
            list_sessions_login_info->erase(it);
            mtk_send_message("server", msg_del_user);
            return;
        }
    }
    response_lines.push_back(MTK_SS("logout command ignored for " << session_id << "  user  unknown"));
}


void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    static int max_sessions=0;
    int current_sessions = list_sessions_login_info->size();
    if(max_sessions < current_sessions)
        max_sessions = current_sessions;
    response_lines.push_back(MTK_SS("max_sessions:" << max_sessions));
    response_lines.push_back(MTK_SS("current_sessions:" << current_sessions));
}


void command_lock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    if(rq_login_locked)
    {
        response_lines.push_back(MTK_SS("Do you know what do you want???"));
        response_lines.push_back(MTK_SS("The system was already locked"));
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "acs", "received command to lock request on status already locked", mtk::alPriorError, mtk::alTypeNoPermisions));
    }
    else
    {
        rq_login_locked = true;
        response_lines.push_back(MTK_SS("Locked. New login requests will be ignored or rejected"));
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "acs", "Locked by command", mtk::alPriorWarning, mtk::alTypeNoPermisions));
    }
}

void command_unlock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    if(rq_login_locked==false)
    {
        response_lines.push_back(MTK_SS("Do you know what do you want???"));
        response_lines.push_back(MTK_SS("The system was already unlocked"));
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "acs", "received command to unlock request on status already unlocked", mtk::alPriorError, mtk::alTypeNoPermisions));
    }
    else
    {
        rq_login_locked = false;
        response_lines.push_back(MTK_SS("Unlocked. New login requests will be attended"));
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "acs", "Locked by command", mtk::alPriorWarning, mtk::alTypeNoPermisions));
    }
}


};  //  commands
