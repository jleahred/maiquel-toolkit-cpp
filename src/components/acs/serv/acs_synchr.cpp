#include "acs_synchr.h"

#include "components/admin/admin.h"
#include "msg_acs_server.h"
#include "components/request_response.hpp"



namespace {
    const char*   VERSION = "2011-05-25";
    
    const char*   MODIFICATIONS =
                        "           2011-05-25     first version\n";


void command_version(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(MTK_SS(__FILE__ << ":  " << VERSION));
}

void command_modifications  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(__FILE__);
    response_lines.push_back(".......................................");
    response_lines.push_back(MODIFICATIONS);
}
void command_stats  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines);



void register_global_commands (void)
{
    mtk::admin::register_command("__GLOBAL__",    "ver",   "")->connect(command_version);
    mtk::admin::register_command("__GLOBAL__",    "modifs","")->connect(command_modifications);
    mtk::admin::register_command("__GLOBAL__",    "stats", "")->connect(command_stats);
    mtk::admin::register_command("acs_synchr",  "stats",   "")->connect(command_stats);
}

    //MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)

}       //  anonymous namespace  to register "static" commnads




namespace
{
    void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void  request_session_list(void);
    void  send_partial_sessions_list(void);
    void  suscribe_acs_syncr_add_del_users(void);
    void  suscribe_acs_partial_sessions_list(void);
    std::string  __get_user_for_session_id(const std::string& session_id);
};




namespace mtk{namespace acs_server{

    
    
namespace  synchr {

    void  init(void)
    {
        register_global_commands();
        request_session_list();
        MTK_TIMER_1SF(send_partial_sessions_list);
        suscribe_acs_syncr_add_del_users();
        suscribe_acs_partial_sessions_list();
    }


    std::string  get_user_for_session_id (const std::string& session_id)
    {
        return __get_user_for_session_id(session_id);
    }




};//    namespace  synchr {

};   //  namespace acs_server
};   //  namespace trd







//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************



namespace   //anonymous
{


    mtk::CountPtr<mtk::map<std::string/*session_id*/, std::string/*user_name*/> >    get_map_sessionid_username(void)
    {
        static mtk::CountPtr<mtk::map<std::string/*session_id*/, std::string/*user_name*/> >    result;
        if(result.isValid() == false)
        {
            result = mtk::make_cptr(new mtk::map<std::string/*session_id*/, std::string/*user_name*/>);
        }
        return result;
    }
    
    void add_sessionid_username(const std::string&  session_id, const std::string& user_name)
    {
        mtk::CountPtr<mtk::map<std::string/*session_id*/, std::string/*user_name*/> >    map_sessionid_user_name = get_map_sessionid_username();
        mtk::map<std::string/*session_id*/, std::string/*user_name*/>::const_iterator  it =  map_sessionid_user_name->find(session_id);
        if(it != map_sessionid_user_name->end())
        {
            if(it->second != user_name)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "acssynchr", MTK_SS("adding> received session id already registered with a diferent user   " << session_id 
                                << "  received user " << user_name  << "  registered user: " << it->second), mtk::alPriorError, mtk::alTypeLogicError));
        }
        else
        {
            map_sessionid_user_name->insert(std::make_pair(session_id, user_name));
        }
    }

    void del_sessionid_username(const std::string&  session_id, const std::string& user_name)
    {
        mtk::CountPtr<mtk::map<std::string/*session_id*/, std::string/*user_name*/> >    map_sessionid_user_name = get_map_sessionid_username();
        mtk::map<std::string/*session_id*/, std::string/*user_name*/>::iterator  it =  map_sessionid_user_name->find(session_id);
        if(it != map_sessionid_user_name->end())
        {
            if(it->second != user_name)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "acssynchr", MTK_SS("deleting> received session id already registered with a diferent user  " << session_id 
                                << "  received user " << user_name  << "  registered user: " << it->second), mtk::alPriorError, mtk::alTypeLogicError));
            else
                map_sessionid_user_name->erase(it);
        }
        else
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "acssynchr", MTK_SS("deleting> received session not registered   " << session_id), mtk::alPriorError, mtk::alTypeLogicError));
        }
    }



    mtk::CountPtr<mtk::qpid_session>  get_server_qpid_session(void)
    {
        static mtk::CountPtr<mtk::qpid_session>  result;
        if(result.isValid() == false)
        {
            result = mtk::admin::get_qpid_session("server", "SRVTESTING");
        }
        return result;
    }






    void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back("acs_synchr_____________________");
        response_lines.push_back(MTK_SS("#sessions :  "  <<   get_map_sessionid_username()->size()));
    }



    void  on_res_user_list(const mtk::list<mtk::acs_server::msg::res_user_list> &  res_user_list)
    {
        mtk::list<mtk::acs_server::msg::res_user_list>::const_iterator it = res_user_list.begin();
        while(it != res_user_list.end())
        {
            mtk::list<mtk::acs::msg::res_login::IC_login_response_info>::const_iterator it2 = it->list_login_confirmation.begin();
            while(it2 != it->list_login_confirmation.end())
            {
                add_sessionid_username(it2->session_id, it2->user_name);
                ++it2;
            }
            ++it;
        }
        
    }
    void  request_session_list(void)
    {
        mtk::acs_server::msg::req_user_list    msg_request_user_list (mtk::admin::get_request_info());
        mtk::send_message(get_server_qpid_session(), msg_request_user_list);
        mtk::msg::sub_request_info  request_info = mtk::admin::get_request_info();
        MTK_RECEIVE_MULTI_RESPONSE_F(   mtk::acs_server::msg::res_user_list,
                                        mtk::list<mtk::acs::msg::res_login::IC_login_response_info>,
                                        get_server_qpid_session(),
                                        mtk::acs_server::msg::res_user_list::get_in_subject(request_info.process_info.location.client_code, 
                                                msg_request_user_list.request_info.process_info.location.machine, 
                                                msg_request_user_list.request_info.process_info.process_uuid,
                                                msg_request_user_list.request_info.req_id.sess_id,
                                                msg_request_user_list.request_info.req_id.req_code),
                                        on_res_user_list,
                                        "request user list to acs")
    }


    
    std::string  __get_user_for_session_id(const std::string& session_id)
    {
        mtk::CountPtr<mtk::map<std::string/*session_id*/, std::string/*user_name*/> >    map_sessionid_user_name = get_map_sessionid_username();
        mtk::map<std::string/*session_id*/, std::string/*user_name*/>::const_iterator  it =  map_sessionid_user_name->find(session_id);
        if(it != map_sessionid_user_name->end())
        {
            return it->second;
        }
        else
        {
            mtk::acs_server::msg::req_session_id_conf  msg(session_id);
            mtk::send_message(get_server_qpid_session(), msg);
            return "";
        }
    }
    
    

    void __received_add_session(const mtk::acs_server::msg::pub_add_user&  pub_add_user)
    {
        add_sessionid_username(pub_add_user.login_confirmation.session_id, pub_add_user.login_confirmation.user_name)  ;
    }
    void __received_del_session(const mtk::acs_server::msg::pub_del_user& pub_del_user)
    {
        del_sessionid_username(pub_del_user.login_confirmation.session_id, pub_del_user.login_confirmation.user_name)  ;
    }
    
    void  suscribe_acs_syncr_add_del_users(void)
    {
        static mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::acs_server::msg::pub_add_user> > handle_pub_add_user;
        MTK_QPID_RECEIVER_CONNECT_F(
                                handle_pub_add_user,
                                mtk::admin::get_url("server"),
                                "SRVTESTING",
                                mtk::acs_server::msg::pub_add_user::get_in_subject(),
                                mtk::acs_server::msg::pub_add_user,
                                __received_add_session)
        static mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::acs_server::msg::pub_del_user> > handle_pub_del_user;
        MTK_QPID_RECEIVER_CONNECT_F(
                                handle_pub_del_user,
                                mtk::admin::get_url("server"),
                                "SRVTESTING",
                                mtk::acs_server::msg::pub_del_user::get_in_subject(),
                                mtk::acs_server::msg::pub_del_user,
                                __received_del_session)
    }


    void  send_partial_sessions_list(void)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(5))
            mtk::CountPtr<mtk::map<std::string/*session_id*/, std::string/*user_name*/> >    map_sessionid_user_name = get_map_sessionid_username();
            if(map_sessionid_user_name.isValid()  &&  map_sessionid_user_name->size() > 0)
            {
                static int static_skip = 0;
                int current_skip = static_skip;
                    
                int count_prepared2send=0;
                mtk::list<mtk::acs::msg::res_login::IC_login_response_info>   partial_list_users;
                for(mtk::map<std::string/*session_id*/, std::string/*user_name*/>::iterator it=map_sessionid_user_name->begin(); it!=map_sessionid_user_name->end(); ++it)
                {
                    if(--current_skip > 0)      continue;
                    
                    if(count_prepared2send < 10)
                    {
                        partial_list_users.push_back(mtk::acs::msg::res_login::IC_login_response_info(it->second, it->first));
                        ++count_prepared2send;
                    }
                    else        break;
                    
                }
                static_skip += 10;
                if(unsigned(static_skip) >= map_sessionid_user_name->size())
                    static_skip = 0;
                
                if(partial_list_users.size()>0)
                {
                    mtk::acs_server::msg::pub_partial_user_list_serv2acs msg(partial_list_users);
                    mtk::send_message(get_server_qpid_session(), msg);
                }
                
            }
        MTK_END_EXEC_MAX_FREC
    }


    void __received_partial_session_list(const mtk::acs_server::msg::pub_partial_user_list_acs2serv& partial_session_list)
    {
        const mtk::list<mtk::acs::msg::res_login::IC_login_response_info>&   list_sessions = partial_session_list.list_login_confirmation;
        for(mtk::list<mtk::acs::msg::res_login::IC_login_response_info>::const_iterator it = list_sessions.begin(); it!=list_sessions.end(); ++it)
            add_sessionid_username(it->session_id, it->user_name);
    }
    
    void suscribe_acs_partial_sessions_list()
    {
        static mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::acs_server::msg::pub_partial_user_list_acs2serv> > handle_pub_partial_user_list_acs2serv;
        MTK_QPID_RECEIVER_CONNECT_F(
                                handle_pub_partial_user_list_acs2serv,
                                mtk::admin::get_url("server"),
                                "SRVTESTING",
                                mtk::acs_server::msg::pub_partial_user_list_acs2serv::get_in_subject(),
                                mtk::acs_server::msg::pub_partial_user_list_acs2serv,
                                __received_partial_session_list)
    }
    
}
