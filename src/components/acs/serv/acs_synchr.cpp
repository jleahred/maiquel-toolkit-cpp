#include "acs_synchr.h"

#include "components/admin/admin.h"
#include "components/request_response.hpp"
#include "components/trading/accounts/msg_account_manager.h"



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
    void  command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void  request_session_list(void);
    void  send_partial_sessions_list(void);
    void  suscribe_acs_syncr_add_del_users(void);
    void  suscribe_acs_partial_sessions_list(void);
    mtk::acs::msg::res_login::IC_session_info               __get_session_info_for_session_id(const std::string& session_id);
    mtk::list<mtk::acs::msg::res_login::IC_session_info>    __bad_performance_get_sessions_info( const std::string& user_name); 
    
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


    mtk::acs::msg::res_login::IC_session_info   get_session_info_for_session_id (const std::string& session_id)
    {
        return __get_session_info_for_session_id(session_id);
    }
    
    mtk::list<mtk::acs::msg::res_login::IC_session_info>    bad_performance_get_sessions_info( const std::string& user_name)
    {
        return __bad_performance_get_sessions_info(user_name);
    }
    
    

    mtk::CountPtr<mtk::Signal<> >   get_signal_received_user_list()
    {
        static mtk::CountPtr<mtk::Signal<> >  result;
        if(result.isValid() == false)
        {
            result = mtk::make_cptr(new mtk::Signal<>);
        }
        return result;
    }



};//    namespace  synchr {

};   //  namespace acs_server
};   //  namespace trd







//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************



namespace   //anonymous
{


    mtk::CountPtr<mtk::map<std::string/*session_id*/, mtk::acs::msg::res_login::IC_session_info> >    get_map_session_id__session_info(void)
    {
        static mtk::CountPtr<mtk::map<std::string/*session_id*/, mtk::acs::msg::res_login::IC_session_info> >    result;
        if(result.isValid() == false)
        {
            result = mtk::make_cptr(new mtk::map<std::string/*session_id*/, mtk::acs::msg::res_login::IC_session_info>);
        }
        return result;
    }
    
    void add_session_info(const mtk::acs::msg::res_login::IC_session_info& session_info)
    {
        mtk::CountPtr<mtk::map<std::string/*session_id*/, mtk::acs::msg::res_login::IC_session_info> >    map_session_id__session_info = get_map_session_id__session_info();
        mtk::map<std::string/*session_id*/, mtk::acs::msg::res_login::IC_session_info>::const_iterator  it =  map_session_id__session_info->find(session_info.session_id);
        if(it != map_session_id__session_info->end())
        {
            if(it->second.user_name != session_info.user_name   ||  it->second.client_code != session_info.client_code)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "acssynchr", MTK_SS("adding> received session id already registered with a diferent user or client_code  rec/reg "
                                << session_info << " / " << it->second), mtk::alPriorError, mtk::alTypeLogicError));
        }
        else
        {
            map_session_id__session_info->insert(std::make_pair(session_info.session_id, session_info));
        }
    }

    void del_session_info(const mtk::acs::msg::res_login::IC_session_info& session_info)
    {
        mtk::CountPtr<mtk::map<std::string/*session_id*/, mtk::acs::msg::res_login::IC_session_info> >    map_session_id__session_info = get_map_session_id__session_info();
        mtk::map<std::string/*session_id*/, mtk::acs::msg::res_login::IC_session_info>::iterator  it =  map_session_id__session_info->find(session_info.session_id);
        if(it != map_session_id__session_info->end())
        {
            if(it->second.user_name != session_info.user_name   ||  it->second.client_code != session_info.client_code)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "acssynchr", MTK_SS("deleting> received session id already registered with a diferent user or client_code  rec/reg "
                                << session_info << " / " << it->second), mtk::alPriorError, mtk::alTypeLogicError));
            else
                map_session_id__session_info->erase(it);
        }
        else
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "acssynchr", MTK_SS("deleting> received session not registered   " << session_info), mtk::alPriorError, mtk::alTypeLogicError));
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
        response_lines.push_back(MTK_SS("#sessions :  "  <<   get_map_session_id__session_info()->size()));
    }



    void  on_res_user_list(const mtk::list<mtk::acs_server::msg::res_user_list> &  res_user_list)
    {
        mtk::list<mtk::acs_server::msg::res_user_list>::const_iterator it = res_user_list.begin();
        while(it != res_user_list.end())
        {
            mtk::list<mtk::acs::msg::res_login::IC_session_info>::const_iterator it2 = it->list_login_confirmation.begin();
            while(it2 != it->list_login_confirmation.end())
            {
                add_session_info(*it2);
                ++it2;
            }
            ++it;
        }
        mtk::acs_server::synchr::get_signal_received_user_list()->emit();
    }
    void  request_session_list(void)
    {
        mtk::acs_server::msg::req_user_list    msg_request_user_list (mtk::admin::get_request_info());
        mtk::send_message(get_server_qpid_session(), msg_request_user_list);
        mtk::msg::sub_request_info  request_info = mtk::admin::get_request_info();
        MTK_RECEIVE_MULTI_RESPONSE_F(   mtk::acs_server::msg::res_user_list,
                                        mtk::list<mtk::acs::msg::res_login::IC_session_info>,
                                        get_server_qpid_session(),
                                        mtk::acs_server::msg::res_user_list::get_in_subject(request_info.process_info.location.client_code, 
                                                msg_request_user_list.request_info.process_info.location.machine, 
                                                msg_request_user_list.request_info.process_info.process_uuid,
                                                msg_request_user_list.request_info.req_id.session_id,
                                                msg_request_user_list.request_info.req_id.req_code),
                                        on_res_user_list,
                                        "request user list to acs")
    }


    
    mtk::acs::msg::res_login::IC_session_info  __get_session_info_for_session_id(const std::string& session_id)
    {
        if(session_id == ""  ||  session_id == "provisional")
            return  mtk::acs::msg::res_login::IC_session_info("", "", "");
            
        
        mtk::CountPtr<mtk::map<std::string/*session_id*/, mtk::acs::msg::res_login::IC_session_info> >    map_session_id__session_info = get_map_session_id__session_info();
        mtk::map<std::string/*session_id*/, mtk::acs::msg::res_login::IC_session_info>::const_iterator  it =  map_session_id__session_info->find(session_id);
        if(it != map_session_id__session_info->end())
        {
            return it->second;
        }
        else
        {
            mtk::acs_server::msg::req_session_id_conf  msg(session_id, mtk::admin::get_process_info());
            mtk::send_message(get_server_qpid_session(), msg);
            return  mtk::acs::msg::res_login::IC_session_info("", "", "");
        }
    }
    mtk::list<mtk::acs::msg::res_login::IC_session_info>  __bad_performance_get_sessions_info( const std::string& user_name)
    {
        mtk::list<mtk::acs::msg::res_login::IC_session_info>   result;
        mtk::CountPtr<mtk::map<std::string/*session_id*/, mtk::acs::msg::res_login::IC_session_info> >    map_session_id__session_info = get_map_session_id__session_info();
        for(auto it=map_session_id__session_info->begin(); it!=map_session_id__session_info->end(); ++it)
        //  for(auto it : *map_session_id__session_info)        supported on gcc4.6
        {
            if (mtk::s_toUpper(it->second.user_name) == mtk::s_toUpper(user_name))
                result.push_back(it->second);
        }
        return result;
    }
    
    

    void __received_add_session(const mtk::acs_server::msg::pub_add_user&  pub_add_user)
    {
        add_session_info(pub_add_user.login_confirmation);
    }
    void __received_del_session(const mtk::acs_server::msg::pub_del_user& pub_del_user)
    {
        del_session_info(pub_del_user.login_confirmation);
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
            mtk::CountPtr<mtk::map<std::string/*session_id*/, mtk::acs::msg::res_login::IC_session_info> >    map_session_id__session_info = get_map_session_id__session_info();
            if(map_session_id__session_info.isValid()  &&  map_session_id__session_info->size() > 0)
            {
                static int static_skip = 0;
                int current_skip = static_skip;
                    
                int count_prepared2send=0;
                mtk::list<mtk::acs::msg::res_login::IC_session_info>   partial_list_users;
                for(mtk::map<std::string/*session_id*/, mtk::acs::msg::res_login::IC_session_info>::iterator it=map_session_id__session_info->begin(); it!=map_session_id__session_info->end(); ++it)
                {
                    if(--current_skip > 0)      continue;
                    
                    if(count_prepared2send < 10)
                    {
                        partial_list_users.push_back(mtk::acs::msg::res_login::IC_session_info(it->second));
                        ++count_prepared2send;
                    }
                    else        break;
                    
                }
                static_skip += 10;
                if(unsigned(static_skip) >= map_session_id__session_info->size())
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
        const mtk::list<mtk::acs::msg::res_login::IC_session_info>&   list_sessions = partial_session_list.list_login_confirmation;
        for(mtk::list<mtk::acs::msg::res_login::IC_session_info>::const_iterator it = list_sessions.begin(); it!=list_sessions.end(); ++it)
            add_session_info(*it);
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
