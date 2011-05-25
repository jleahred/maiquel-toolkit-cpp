#include "acs_synchr.h"

#include "components/admin/admin.h"



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

    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)

}       //  anonymous namespace  to register "static" commnads




namespace
{
    void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void  request_session_list(void);
    void  send_partial_sessions_list(void);
    void  suscribe_acs_syncr_add_del_users(void);
    std::string  __get_user_for_session_id(const std::string& session_id);
};




namespace mtk{namespace adm{

    
    
namespace  acs_synchr {

    void  init(void)
    {
        request_session_list();
        MTK_TIMER_1SF(send_partial_sessions_list);
        suscribe_acs_syncr_add_del_users();
    }


    std::string  get_user_for_session_id (const std::string& session_id)
    {
        return __get_user_for_session_id(session_id);
    }




};//    namespace  acs_synchr {

};   //  namespace adm
};   //  namespace trd





namespace   //anonymous
{
    void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back("acs_synchr_____________________");
        response_lines.push_back(MTK_SS("#sessions :  pending" ));
    }

    void  request_session_list(void)
    {
        
    }
    
    void  send_partial_sessions_list(void)
    {
        
    }
    
    void  suscribe_acs_syncr_add_del_users(void)
    {
        
    }
    
    std::string  __get_user_for_session_id(const std::string& session_id)
    {
        return "";
    }
}
