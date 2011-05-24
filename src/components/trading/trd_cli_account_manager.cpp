#include "trd_cli_account_manager.h"

#include "support/mtk_string.h"
#include "components/admin/admin.h"



namespace {
    const char*   VERSION = "2011-05-24";
    
    const char*   MODIFICATIONS =
                        "           2011-05-24     first version\n";


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
void command_list   (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines);



void register_global_commands (void)
{
    mtk::admin::register_command("__GLOBAL__",    "ver",   "")->connect(command_version);
    mtk::admin::register_command("__GLOBAL__",    "modifs","")->connect(command_modifications);
    mtk::admin::register_command("__GLOBAL__",    "stats", "")->connect(command_stats);
    mtk::admin::register_command("account_manager",  "stats", "")->connect(command_stats);
    mtk::admin::register_command("account_manager",  "list", "")->connect(command_list);
}

    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)

}       //  anonymous namespace  to register "static" commnads





namespace mtk{namespace trd{

    
    
namespace  account_manager {


    mtk::list<mtk::trd::msg::sub_account_info>      get_accounts(void)
    {
        mtk::list<mtk::trd::msg::sub_account_info> result ;
        
        result.push_back(mtk::trd::msg::sub_account_info("CIMD", "pr1@fut"));
        result.push_back(mtk::trd::msg::sub_account_info("CIMD", "pr2@fut"));
        result.push_back(mtk::trd::msg::sub_account_info("CIMD", "pr3@fut"));
        
        return result;
    }






};//    namespace  trd_cli_account_manager {

};   //  namespace mtk
};   //  namespace trd


namespace   //anonymous
{
    void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back("trd_cli_account_manager_____________________");
        response_lines.push_back(MTK_SS("#accounts :" <<  "pending"));
    }
    
    void command_list(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back("trd_cli_account_manager_____________________");
        response_lines.push_back(MTK_SS("pending"));
    }
}