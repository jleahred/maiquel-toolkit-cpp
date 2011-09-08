#include   "db.h"

#include "support/count_ptr.hpp"
#include "support/map.hpp"
#include "msg_structs.h"
#include "components/admin/admin.h"
#include "support/re/RegExp.h"
#include "components/acs/serv/acs_synchr.h"

#include <fstream>


namespace accmgr { 
namespace db {

    std::string  db_file_name;
    
    

    mtk::CountPtr<mtk::list<std::string> >   get_list_markets(void)
    {
        static mtk::CountPtr<mtk::list<std::string> >  result;
        if(result.isValid() == false)
            result = mtk::make_cptr(new  mtk::list<std::string>);
        return result;
    }
    

    mtk::CountPtr<mtk::map<std::string  /*user_name*/, msg::sub_user_info> >   get_map_user_info(void)
    {
        static mtk::CountPtr<mtk::map<std::string  /*user_name*/, msg::sub_user_info> >  result;
        if(result.isValid() == false)
            result = mtk::make_cptr(new  mtk::map<std::string  /*user_name*/, msg::sub_user_info>);
        return result;
    }

    mtk::CountPtr<mtk::map<std::string  /*acc_name*/, mtk::trd::msg::sub_account_info > >   get_map_registered_accounts(void)
    {
        static mtk::CountPtr<mtk::map<std::string, mtk::trd::msg::sub_account_info >  > result;
        if(result.isValid() == false)
            result = mtk::make_cptr(new  mtk::map<std::string, mtk::trd::msg::sub_account_info >);
        return result;
    }

    
    
    
    void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_lock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_unlock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

    void command_add_market(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_del_market(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_add_account(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_del_account(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_add_user(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_del_user(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_grant(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_revoke(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

    void command_load(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_save(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_purge(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

    void command_get_effective_user_grants(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_get_effective_user_grants_yaml(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_get_effective_client_grants(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_get_effective_client_grants_yaml(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_get_all_effective_grants(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

    void command_get_raw_user_grants(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_get_raw_user_grants_yaml(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_get_raw_client_grants(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_get_raw_client_grants_yaml(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_get_all_raw_grants(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

    
    void register_global_commands (void)
    {
        //mtk::admin::register_command("__GLOBAL__",  "ver",   "")->connect(command_version);
        mtk::admin::register_command("__GLOBAL__",  "stats",     "")->connect(command_stats);
        mtk::admin::register_command("sessions",  "stats",     "")->connect(command_stats);
        //mtk::admin::register_command("emr",  "lock_all",     "lock all requests", true)->connect(command_lock);
        //mtk::admin::register_command("emr",  "unlock_all",   "unlock all requests", true)->connect(command_unlock);
        
        mtk::admin::register_command("accmgr",  "add_market",  "<market_name>", true)->connect(command_add_market);
        mtk::admin::register_command("accmgr",  "del_market",  "<market_name>", true)->connect(command_del_market);

        mtk::admin::register_command("accmgr",  "add_account",  "<account-name> <cli-code>")->connect(command_add_account);
        mtk::admin::register_command("accmgr",  "del_account",  "<account-name> <cli-code>")->connect(command_del_account);
        
        mtk::admin::register_command("accmgr",  "add_user",     "<user_name> <client-code>")->connect(command_add_user);
        mtk::admin::register_command("accmgr",  "del_user",     "<user_name> <client-code>")->connect(command_del_user);

        mtk::admin::register_command("accmgr",  "grant",        "<market> <user_name>  <cli-code-reg-expr> <account-name-reg-expr>  <grant_type__F|C|V>")->connect(command_grant);
        mtk::admin::register_command("accmgr",  "revoke",       "<market> <user_name>  <cli-code-reg-expr> <account-name-reg-expr>  <grant_type__F|C|V>")->connect(command_revoke);
        
        mtk::admin::register_command("accmgr",  "load",        "DANGEROUS delete current accounts and load from file", true)->connect(command_load);
        mtk::admin::register_command("accmgr",  "save",        "save accounts configuration to file", true)->connect(command_save);
        mtk::admin::register_command("accmgr",  "purge",       "remove all deleted grants", true)->connect(command_purge);

        mtk::admin::register_command("accmgr",  "get_effective_user_grants",        "<user_name-re-pattern>")->connect(command_get_effective_user_grants);
        mtk::admin::register_command("accmgr",  "get_effective_user_grants.yaml",        "<user_name-re-pattern>")->connect(command_get_effective_user_grants_yaml);
        mtk::admin::register_command("accmgr",  "get_effective_client_grants",      "<client_code-re-pattern>")->connect(command_get_effective_client_grants);
        mtk::admin::register_command("accmgr",  "get_effective_client_grants.yaml",      "<client_code-re-pattern>")->connect(command_get_effective_client_grants_yaml);
        mtk::admin::register_command("accmgr",  "get_all_effective_grants",      "depreciated", true)->connect(command_get_all_effective_grants);

        mtk::admin::register_command("accmgr",  "get_raw_user_grants",        "<user_name-re-pattern>")->connect(command_get_raw_user_grants);
        mtk::admin::register_command("accmgr",  "get_raw_user_grants.yaml",        "<user_name-re-pattern>")->connect(command_get_raw_user_grants_yaml);
        mtk::admin::register_command("accmgr",  "get_raw_client_grants",      "<client_code-re-pattern>")->connect(command_get_raw_client_grants);
        mtk::admin::register_command("accmgr",  "get_raw_client_grants.yaml",      "<client_code-re-pattern>")->connect(command_get_raw_client_grants_yaml);
        mtk::admin::register_command("accmgr",  "get_all_raw_grants",      "depreciated", true)->connect(command_get_all_raw_grants);
    }
    
    


    
    void init(const std::string& _db_file_name)
    {   
        register_global_commands(); 
        db_file_name  =  _db_file_name;   
        load(); 
    }

    mtk::list<std::string>                              get_market_list(void)
    {
        return *get_list_markets();
    }


    bool  check_and_split_params__converting2upper(const std::string& params, mtk::list<std::string>&  response_lines, int number_of_params, mtk::vector<std::string>& vparams)
    {
        mtk::vector<std::string> temp_vparams = mtk::s_split(mtk::s_trim(params, ' '), " ");
        //  remove empty params
        vparams.clear();
        for(unsigned i=0; i<temp_vparams.size(); ++i)
        {
            std::string param = mtk::s_trim(temp_vparams[i], ' ');
            if(param != "")
                vparams.push_back(mtk::s_toUpper(param));
        }
        if(vparams.size() != unsigned(number_of_params))
        {
            response_lines.push_back(MTK_SS("invalid number of params. There is needed "  <<  number_of_params  <<  "  params:   "  << params));
            return  false;
        }
        return true;
    }



    std::string     __get_grant_type(const std::string& market, const msg::sub_user_info& user_info, const mtk::trd::msg::sub_account_info& account_info);
    std::string     get_grant_type (    const mtk::msg::sub_request_id          rid,
                                        const std::string&                      market, 
                                        const mtk::trd::msg::sub_account_info&  account_info)
    {
        mtk::acs::msg::res_login::IC_session_info  session_info = mtk::acs_server::synchr::get_session_info_for_session_id(rid.session_id);
        std::string  user_name = session_info.user_name;
        
        if(session_info.client_code != "CIMD"   &&   session_info.client_code != account_info.client_code)
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "looking grants", MTK_SS("request with account client code "<< account_info.client_code 
                                                    << "for session with client code... " << session_info.client_code), mtk::alPriorError, mtk::alTypeLogicError));
            return "";
        }
        
        mtk::map<std::string  /*user_name*/, msg::sub_user_info>::iterator  it_user_info = get_map_user_info()->find(mtk::s_toUpper(user_name));
        if(it_user_info != get_map_user_info()->end())
            return __get_grant_type(market, it_user_info->second, account_info);
        else
            return "";
    }
    
    

    void command_stats(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 0, vparams)  == false)     return;

        response_lines.push_back(MTK_SS("[account_manager] ________________________________ " << get_map_user_info()->size()));
        response_lines.push_back(MTK_SS("#users: " << get_map_user_info()->size()));
        response_lines.push_back(MTK_SS("#accounts: " << get_map_registered_accounts()->size()));
    }

    void command_lock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  /*response_lines*/)
    {
    }

    void command_unlock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  /*response_lines*/)
    {
    }



    bool check_user_name(const std::string& user_name)
    {
        mtk::RegExp re ("^[A-Z_@\\.]+$");
        return re.Match(user_name);
    }

    bool check_account_name(const std::string& account_name)
    {
        mtk::RegExp re("^[A-Z_0-9@]+$");
        return re.Match(account_name);
    }

    bool check_client_code(const std::string& client_code)
    {
        mtk::RegExp re ("^[A-Z_]+$");
        return re.Match(client_code);
    }


    std::string try_add_market(const std::string& market)
    {
        for(mtk::list<std::string>::const_iterator it=get_list_markets()->begin(); it!= get_list_markets()->end(); ++it)
        {
            if(*it == market)
                return MTK_SS("market " << market << " already exists");
        }
        get_list_markets()->push_back(market);
        return "";
    }

    void command_add_market(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;
        
        response_lines.push_back(MTK_SS("before adding ... " << get_list_markets()->size()));
        std::string result = try_add_market(vparams[0]);
        response_lines.push_back(result);
        response_lines.push_back(MTK_SS("after adding ... " << get_list_markets()->size()));
    }

    std::string try_del_market(const std::string& market)
    {
        for(mtk::list<std::string>::iterator it=get_list_markets()->begin(); it!= get_list_markets()->end(); ++it)
        {
            if(*it == market)
            {
                it = get_list_markets()->erase(it);
                if(it == get_list_markets()->end())
                    return "";
            }
        }
        return "";
    }

    void command_del_market(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        response_lines.push_back(MTK_SS("before deleting ... " << get_list_markets()->size()));
        std::string result = try_del_market(vparams[0]);
        response_lines.push_back(result);
        response_lines.push_back(MTK_SS("after adding ... " << get_list_markets()->size()));
    }


    std::string  try_add_account(const mtk::trd::msg::sub_account_info& account)
    {
        std::string result; 
        //  check format fields
        //  check if previusly exists



        //  check format fields
        if (check_account_name(account.name) == false)
        {
            std::string message = MTK_SS("invalid account name " << account);
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", message, mtk::alPriorError, mtk::alTypeLogicError));
            return message;
        }
        if (check_client_code(account.client_code) == false)
        {
            std::string message = MTK_SS("invalid account client code [" << account.client_code << "]");
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", message, mtk::alPriorError, mtk::alTypeLogicError));
            return message;
        }
        
        
        
        
        //  check if previusly exists
        mtk::CountPtr<mtk::map<std::string, mtk::trd::msg::sub_account_info> > map_accounts = get_map_registered_accounts();
        result += MTK_SS("before adding account... " << map_accounts->size());
        mtk::map<std::string, mtk::trd::msg::sub_account_info>::iterator it = map_accounts->find(account.name);
        if(it!=map_accounts->end())
        {
            std::string  message = MTK_SS("account name already registered " << account);
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", message, mtk::alPriorError, mtk::alTypeLogicError));
            return   message;
        }
        map_accounts->insert(std::make_pair(account.name, account));
        
        result += MTK_SS("   after adding  account... " << map_accounts->size());
        result += MTK_SS("   Account added ok."); 
        return result;
    }
    void command_add_account(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 2, vparams)  == false)     return;

        mtk::trd::msg::sub_account_info account(mtk::s_toUpper(vparams[0]), mtk::s_toUpper(vparams[1]));
        std::string result = try_add_account(account);
        response_lines.push_back(result);
    }
    
    std::string  try_del_account(const mtk::trd::msg::sub_account_info& account)
    {
        std::string result; 
        //  check if previusly exists
        mtk::CountPtr<mtk::map<std::string, mtk::trd::msg::sub_account_info> > map_accounts = get_map_registered_accounts();
        result += MTK_SS("before removing account... " << map_accounts->size());
        mtk::map<std::string, mtk::trd::msg::sub_account_info>::iterator it = map_accounts->find(account.name);
        if(it==map_accounts->end())
        {
            std::string  message = MTK_SS("account doesn't exists " << account);
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", message, mtk::alPriorError, mtk::alTypeLogicError));
            return   message;
        }
        map_accounts->erase(account.name);
        
        //result += MTK_SS("   after removing account... " << map_accounts->size());
        result += MTK_SS("   Account deleted ok."); 
        return result;
    }
    void command_del_account(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 2, vparams)  == false)     return;

        mtk::trd::msg::sub_account_info account(mtk::s_toUpper(vparams[0]), mtk::s_toUpper(vparams[1]));
        std::string result = try_del_account(account);
        response_lines.push_back(result);
    }
    
    std::string  try_add_user(const std::string& user_name, const std::string& client_code)
    {
        std::string result; 
        //  check format fields
        if (check_user_name(user_name) == false)
        {
            std::string message = MTK_SS("invalid user name " << user_name);
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", message, mtk::alPriorError, mtk::alTypeLogicError));
            return message;
        }
        if (check_client_code(client_code) == false)
        {
            std::string message = MTK_SS("invalid client code [" << client_code << "]");
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", message, mtk::alPriorError, mtk::alTypeLogicError));
            return message;
        }
        //  check if previusly exists
        mtk::CountPtr<mtk::map<std::string, msg::sub_user_info> > map_users = get_map_user_info();
        result += MTK_SS("before adding user... " << map_users->size());
        mtk::map<std::string, msg::sub_user_info>::iterator it = map_users->find(user_name);
        if(it!=map_users->end())
        {
            std::string  message = MTK_SS("user name already exists " << user_name);
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", message, mtk::alPriorError, mtk::alTypeLogicError));
            return   message;
        }
        msg::sub_user_info user_info(user_name, mtk::dtNowLocal(), client_code, mtk::list<mtk::trd::account::msg::sub_grant>());
        map_users->insert(std::make_pair(user_name, user_info));
        
        result += MTK_SS("   after adding user... " << map_users->size());
        result += MTK_SS("   User added ok."); 
        return result;
    }
    void command_add_user(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 2, vparams)  == false)     return;

        std::string result = try_add_user(mtk::s_toUpper(vparams[0]), mtk::s_toUpper(vparams[1]));
        response_lines.push_back(result);
    }
    

    std::string  try_del_user(const std::string& user_name, const std::string& /*client_code*/)
    {
        std::string result; 
        //  check if previusly exists
        mtk::CountPtr<mtk::map<std::string, msg::sub_user_info> > map_users = get_map_user_info();
        result += MTK_SS("before deleting user... " << map_users->size());
        mtk::map<std::string, msg::sub_user_info>::iterator it = map_users->find(user_name);
        if(it==map_users->end())
        {
            std::string  message = MTK_SS("user doesn't exists " << user_name);
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", message, mtk::alPriorError, mtk::alTypeLogicError));
            return   message;
        }
        map_users->erase(user_name);
        
        result += MTK_SS("   after deleting user... " << map_users->size());
        result += MTK_SS("   User deleted ok."); 
        return result;
    }
    void command_del_user(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 2, vparams)  == false)     return;

        std::string result = try_del_user(mtk::s_toUpper(vparams[0]), mtk::s_toUpper(vparams[1]));
        response_lines.push_back(result);
    }
    
    void command_grant(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 5, vparams)  == false)     return;
        
        std::string market = mtk::s_toUpper(vparams[0]);
        std::string user_name = mtk::s_toUpper(vparams[1]);
        std::string client_code = mtk::s_toUpper(vparams[2]);
        std::string account_name = mtk::s_toUpper(vparams[3]);
        std::string grant_type = mtk::s_toUpper(vparams[4]);
        
        {
            //  check if market exists
            bool blocated=false;
            for(mtk::list<std::string>::iterator it=get_list_markets()->begin(); it!=get_list_markets()->end(); ++it)
            {
                if(*it == market)
                    blocated=true;
            }
            if(blocated == false)
            {
                std::string  message = MTK_SS("market doesn't exists " << user_name);
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", message, mtk::alPriorError, mtk::alTypeLogicError));
                response_lines.push_back(message);
                return;
            }
        }
        
        //  mtk::admin::register_command("accmgr",  "grant",        "<user_name>  <cli-code-reg-expr> <account-name-reg-expr>  <grant_type__F|C|V>")->connect(command_grant);
        mtk::CountPtr<mtk::map<std::string  /*user_name*/, msg::sub_user_info> >   map_user_info = get_map_user_info();
        mtk::map<std::string  /*user_name*/, msg::sub_user_info>::iterator located = map_user_info->find(user_name);
        
        if(located == map_user_info->end())
        {
            std::string  message = MTK_SS("user doesn't exists " << user_name);
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", message, mtk::alPriorError, mtk::alTypeLogicError));
            response_lines.push_back(message);
            return;
        }
        
        //  mtk::CountPtr<mtk::map<std::string  /*acc_name*/, mtk::trd::msg::sub_account_info > >   get_map_registered_accounts(void)
//        if(get_map_registered_accounts()->find(account_name) == get_map_registered_accounts()->end())
//        {
//            std::string  message = MTK_SS("account  doesn't exists " << account_name);
//            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", message, mtk::alPriorError, mtk::alTypeLogicError));
//            response_lines.push_back(message);
//            return;
//        }

        mtk::trd::msg::sub_account_info account(account_name, client_code);
        msg::sub_user_info& user_info = located->second;
        mtk::trd::account::msg::sub_grant::IC_key grant_key(market, account);
        mtk::trd::account::msg::sub_grant grant (grant_key, grant_type);
        {
            bool blocated=false;
            for (mtk::list<mtk::trd::account::msg::sub_grant>::iterator it = user_info.grant_list.begin(); it != user_info.grant_list.end(); ++it)
            {
                if(it->key.account == account  &&  it->type != "<deleted>")
                    blocated = true;
            }
            if(blocated)
            {
                std::string  message = MTK_SS("this account already has grant " << account);
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", message, mtk::alPriorError, mtk::alTypeLogicError));
                response_lines.push_back(message);
                return;
            }
        }
        if(user_info.client_code != "CIMD"  &&  client_code != user_info.client_code)
        {
            std::string  message = MTK_SS("invalid client code " << client_code);
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", message, mtk::alPriorError, mtk::alTypeLogicError));
            response_lines.push_back(message);
            return;
        }
        
        response_lines.push_back(MTK_SS("before grant... " << user_info.grant_list.size()));
        user_info.grant_list.push_back(grant);
        response_lines.push_back(MTK_SS(grant));
        response_lines.push_back(MTK_SS("after grant... " << user_info.grant_list.size()));
    }
    
    void command_revoke(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 5, vparams)  == false)     return;
        
        std::string market = mtk::s_toUpper(vparams[0]);
        std::string user_name = mtk::s_toUpper(vparams[1]);
        std::string client_code = mtk::s_toUpper(vparams[2]);
        std::string account_name = mtk::s_toUpper(vparams[3]);
        std::string grant_type = mtk::s_toUpper(vparams[4]);
        mtk::CountPtr<mtk::map<std::string  /*user_name*/, msg::sub_user_info> >   map_user_info = get_map_user_info();
        mtk::map<std::string  /*user_name*/, msg::sub_user_info>::iterator located = map_user_info->find(user_name);
        
        if(located == map_user_info->end())
        {
            std::string  message = MTK_SS("user doesn't exists " << user_name);
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", message, mtk::alPriorError, mtk::alTypeLogicError));
            response_lines.push_back(message);
            return;
        }
        
        mtk::trd::msg::sub_account_info account(account_name, client_code);
        msg::sub_user_info& user_info = located->second;
        mtk::trd::account::msg::sub_grant::IC_key grant_key(market, account);
        mtk::trd::account::msg::sub_grant grant (grant_key, grant_type);

        //response_lines.push_back(MTK_SS("before revoke... " << user_info.grant_list.size()));
        int deleted=0;
        for (mtk::list<mtk::trd::account::msg::sub_grant>::iterator it = user_info.grant_list.begin(); it != user_info.grant_list.end(); ++it)
        {
            if(*it == grant)
            {
                response_lines.push_back(MTK_SS("deleting... " << grant));
                it->type = "<deleted>";          //      will be purged later. It allow to send deletes to client
                ++deleted;
                //it = user_info.grant_list.erase(it);
                //if(it==user_info.grant_list.end())
                //    break;
            }
        }
        response_lines.push_back(MTK_SS(grant));
        response_lines.push_back(MTK_SS("#deleted: " << deleted));
        //response_lines.push_back(MTK_SS("after revoke... " << user_info.grant_list.size()));
    }
    
    
   

    
    void load(void)
    {
        get_list_markets()->clear();
        get_map_registered_accounts()->clear();
        get_map_user_info()->clear();

        std::ifstream file(db_file_name.c_str());
        try
        {
            YAML::Parser parser(file);

            YAML::Node doc;
            parser.GetNextDocument(doc);
            //std::string config_version;

            doc["markets"] >> *get_list_markets();
            doc["accounts"] >> *get_map_registered_accounts();
            doc["user_info"] >> *get_map_user_info();

            file.close();
        }
        MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "accmgr_db", "error loading db")
    }
    
    void save(void)
    {
        std::ofstream file;
        file.open (db_file_name.c_str(), std::ios::out | std::ios::trunc);


        try
        {
            YAML::Emitter out;
            out  <<  YAML::BeginMap;

            out  << YAML::Key << "version"   <<  YAML::Value << 1;

            out  << YAML::Key << "markets"   <<  YAML::Value  <<  *get_list_markets();

            out  << YAML::Key << "accounts"  <<  YAML::Value  <<  *get_map_registered_accounts();

            out  << YAML::Key << "user_info" <<  YAML::Value  <<  *get_map_user_info();

            out <<  YAML::EndMap;

            file << out.c_str();
            file.close();
        }
        MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "accmgr_db", "error saving db")
    }
    void purge(void)
    {
        for(mtk::list<std::string>::const_iterator it_markets=get_list_markets()->begin(); it_markets != get_list_markets()->end(); ++it_markets)
        {
            std::string market = *it_markets;
            for(mtk::map<std::string  /*user_name*/, msg::sub_user_info>::iterator it_user_info = get_map_user_info()->begin(); 
                                it_user_info != get_map_user_info()->end(); ++it_user_info)
            {
                //  [grant_list](gl)    : mtk::trd::account::msg::sub_grant
                for (auto it_grant=it_user_info->second.grant_list.begin(); it_grant!=it_user_info->second.grant_list.end(); ++it_grant)
                {
                    if(it_grant->type=="<deleted>"  ||  it_grant->type==""  ||  it_grant->type=="~")
                    {
                        it_grant = it_user_info->second.grant_list.erase(it_grant);
                        if(it_grant == it_user_info->second.grant_list.end())
                            break;
                    }
                }
            }
        }
    }
    
    void command_load(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back("loading...");
        load();
        command_stats("", "", response_lines);
    }
    void command_save(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back("saving...");
        save();
        command_stats("", "", response_lines);
    }
    void command_purge(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        purge();
        response_lines.push_back("purged db");
    }
    
    
    
    bool is_less_or_equal_restrictive(char first, char second)
    {
        if(first == 'F')
            return true;
        else if(first == 'V')
            return false;
        else /*first is 'C'*/
        {
            if(second == 'V')
                return false;
            else
                return true;
        }
        
    }
    
    std::string     __get_grant_type(const std::string& market, const msg::sub_user_info& user_info, const mtk::trd::msg::sub_account_info& account_info)
    {
        std::string  result;
        bool deleted=false;
        {
            //  iterate from grants and put in a string all grants from more restrictive to less
            for (mtk::list<mtk::trd::account::msg::sub_grant>::const_iterator it = user_info.grant_list.begin(); it != user_info.grant_list.end(); ++it)
            {
                std::string pattern_client_code;
                std::string pattern_account;
                if(user_info.client_code == "CIMD")
                {
                    pattern_client_code = account_info.client_code;
                }
                else
                {
                    if(user_info.client_code  !=  it->key.account.client_code)
                    {
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", MTK_SS("client code doesn't match " << user_info << "  "  << it->key), mtk::alPriorError, mtk::alTypeLogicError));
                        return "";
                    }
                    pattern_client_code = user_info.client_code;
                }
                if(market == it->key.market)
                {
                    mtk::RegExp re_client_code ("^" + pattern_client_code + "$");
                    if(re_client_code.Match(it->key.account.client_code))
                    {
                        std::string grant_type = it->type;
                        mtk::RegExp re_account_name ("^" + it->key.account.name + "$");
                        if(re_account_name.Match(account_info.name))
                        {
                            if(grant_type != "<deleted>")
                            {
                                if(result == ""  ||  is_less_or_equal_restrictive(result[0], grant_type[0]))
                                {
                                    result = std::string(grant_type) + result;
                                }
                                else
                                {
                                    result += std::string(grant_type);
                                }
                            }
                            else
                                deleted = true;
                        }
                    }
                }
            }
        }
        if(deleted &&  result =="")
            return "<deleted>";
        return result;
    }
    
    
    
    void command_get_effective_user_grants(const std::string& command, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        std::string filter_user = vparams[0];
        for(mtk::list<std::string>::const_iterator it_markets=get_list_markets()->begin(); it_markets != get_list_markets()->end(); ++it_markets)
        {
            std::string market = *it_markets;
            for(mtk::map<std::string  /*user_name*/, msg::sub_user_info>::iterator it_user_info = get_map_user_info()->begin(); 
                                it_user_info != get_map_user_info()->end(); ++it_user_info)
            {
                if(mtk::RegExp(filter_user).Match(it_user_info->second.name))
                //if(it_user_info->second.name == filter_user)
                {
                    response_lines.push_back("");
                    response_lines.push_back("");
                    response_lines.push_back(it_user_info->second.name);
                    response_lines.push_back(MTK_SS(it_user_info->second.client_code << "  "  <<  market));
                    response_lines.push_back("--------------------------------");
                    mtk::CountPtr<mtk::map<std::string  /*acc_name*/, mtk::trd::msg::sub_account_info > >  map_accounts = get_map_registered_accounts();
                    for(mtk::map<std::string  /*acc_name*/, mtk::trd::msg::sub_account_info >::iterator it_accounts= map_accounts->begin(); it_accounts != map_accounts->end(); ++it_accounts)
                    {
                        auto  account_info = it_accounts->second;
                        std::string  grants = __get_grant_type(market, it_user_info->second, account_info);
                        if(grants != "")
                            response_lines.push_back(MTK_SS(account_info  << " ["  << grants << "]"));
                    }
                }
            }
        }
        response_lines.push_back(MTK_SS(std::endl << "<<<  end of command  " << command));
    }
    
    
    void   fill_yaml_with_user_info  (YAML::Emitter&  yo,  const  msg::sub_user_info&  user_info, const std::string& market)
    {
        yo << YAML::BeginMap;
            yo << YAML::Key << "name"  <<  YAML::Value <<  user_info.name;
            yo << YAML::Key << "cli_code"  <<  YAML::Value <<  user_info.client_code;
            yo << YAML::Key << "market"  <<  YAML::Value <<  market;

            yo << YAML::Key << "accounts"  <<  YAML::Value;
            mtk::CountPtr<mtk::map<std::string  /*acc_name*/, mtk::trd::msg::sub_account_info > >  map_accounts = get_map_registered_accounts();
            yo << YAML::BeginSeq;
            for(mtk::map<std::string  /*acc_name*/, mtk::trd::msg::sub_account_info >::iterator it_accounts= map_accounts->begin(); it_accounts != map_accounts->end(); ++it_accounts)
            {
                auto  account_info = it_accounts->second;
                std::string  grants = __get_grant_type(market, user_info, account_info);
                if(grants != "")
                {
                    yo << YAML::BeginMap;
                        yo << YAML::Key << "account" <<  YAML::Value <<  account_info;
                        yo << YAML::Key << "grants"  <<  YAML::Value <<  grants;
                    yo << YAML::EndMap;
                }
            }
            yo << YAML::EndSeq;
        yo << YAML::EndMap;
    }
    
    void command_get_effective_user_grants_yaml(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        YAML::Emitter yo;
        yo << YAML::BeginSeq;

        std::string filter_user = vparams[0];
        for(mtk::list<std::string>::const_iterator it_markets=get_list_markets()->begin(); it_markets != get_list_markets()->end(); ++it_markets)
        {
            std::string market = *it_markets;
            for(mtk::map<std::string  /*user_name*/, msg::sub_user_info>::iterator it_user_info = get_map_user_info()->begin(); 
                                it_user_info != get_map_user_info()->end(); ++it_user_info)
            {
                if(mtk::RegExp(filter_user).Match(it_user_info->second.name))
                    fill_yaml_with_user_info(yo, it_user_info->second, market);
            }
        }
        yo << YAML::EndSeq;
        response_lines.push_back(yo.c_str());
    }
    


    void command_get_effective_client_grants(const std::string& command, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        std::string filter_client = vparams[0];
        for(mtk::list<std::string>::const_iterator it_markets=get_list_markets()->begin(); it_markets != get_list_markets()->end(); ++it_markets)
        {
            std::string market = *it_markets;
            for(mtk::map<std::string  /*user_name*/, msg::sub_user_info>::iterator it_user_info = get_map_user_info()->begin(); 
                                it_user_info != get_map_user_info()->end(); ++it_user_info)
            {
                //if(it_user_info->second.client_code == filter_client)
                if(mtk::RegExp(filter_client).Match(it_user_info->second.client_code))
                {
                    response_lines.push_back("");
                    response_lines.push_back("");
                    response_lines.push_back(it_user_info->second.name);
                    response_lines.push_back(MTK_SS(it_user_info->second.client_code << "  "  <<  market));
                    response_lines.push_back("--------------------------------");
                    mtk::CountPtr<mtk::map<std::string  /*acc_name*/, mtk::trd::msg::sub_account_info > >  map_accounts = get_map_registered_accounts();
                    for(mtk::map<std::string  /*acc_name*/, mtk::trd::msg::sub_account_info >::iterator it_accounts= map_accounts->begin(); it_accounts != map_accounts->end(); ++it_accounts)
                    {
                        std::string  grants = __get_grant_type(market, it_user_info->second, it_accounts->second);
                        if(grants != "")
                            response_lines.push_back(MTK_SS(it_accounts->second  << " ["  << grants << "]"));
                    }
                }
            }
        }
        response_lines.push_back(MTK_SS(std::endl << "<<<  end of command  " << command));
    }

    void command_get_effective_client_grants_yaml(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        YAML::Emitter yo;
        yo << YAML::BeginSeq;

        std::string filter_client = vparams[0];
        for(mtk::list<std::string>::const_iterator it_markets=get_list_markets()->begin(); it_markets != get_list_markets()->end(); ++it_markets)
        {
            std::string market = *it_markets;
            for(mtk::map<std::string  /*user_name*/, msg::sub_user_info>::iterator it_user_info = get_map_user_info()->begin(); 
                                it_user_info != get_map_user_info()->end(); ++it_user_info)
            {
                if(mtk::RegExp(filter_client).Match(it_user_info->second.client_code))
                    fill_yaml_with_user_info(yo, it_user_info->second, market);
            }
        }
        yo << YAML::EndSeq;
        response_lines.push_back(yo.c_str());
    }

    
    void command_get_all_effective_grants(const std::string& command, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 0, vparams)  == false)     return;

        for(mtk::list<std::string>::const_iterator it_markets=get_list_markets()->begin(); it_markets != get_list_markets()->end(); ++it_markets)
        {
            std::string market = *it_markets;
            for(mtk::map<std::string  /*user_name*/, msg::sub_user_info>::iterator it_user_info = get_map_user_info()->begin(); 
                                it_user_info != get_map_user_info()->end(); ++it_user_info)
            {
                response_lines.push_back("");
                response_lines.push_back("");
                response_lines.push_back(it_user_info->second.name);
                response_lines.push_back(MTK_SS(it_user_info->second.client_code << "  "  <<  market));
                response_lines.push_back("--------------------------------");
                mtk::CountPtr<mtk::map<std::string  /*acc_name*/, mtk::trd::msg::sub_account_info > >  map_accounts = get_map_registered_accounts();
                for(mtk::map<std::string  /*acc_name*/, mtk::trd::msg::sub_account_info >::iterator it_accounts= map_accounts->begin(); it_accounts != map_accounts->end(); ++it_accounts)
                {
                    std::string  grants = __get_grant_type(market, it_user_info->second, it_accounts->second);
                    if(grants != "")
                        response_lines.push_back(MTK_SS(it_accounts->second  << " ["  << grants << "]"));
                }
            }
        }
        response_lines.push_back(MTK_SS(std::endl << "<<<  end of command  " << command));
    }



    void command_get_raw_user_grants(const std::string& command, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        std::string filter_user = vparams[0];
        for(mtk::list<std::string>::const_iterator it_markets=get_list_markets()->begin(); it_markets != get_list_markets()->end(); ++it_markets)
        {
            std::string market = *it_markets;
            for(mtk::map<std::string  /*user_name*/, msg::sub_user_info>::iterator it_user_info = get_map_user_info()->begin(); 
                                it_user_info != get_map_user_info()->end(); ++it_user_info)
            {
                if(mtk::RegExp(filter_user).Match(it_user_info->second.name))
                //if(it_user_info->second.name == filter_user)
                {
                    response_lines.push_back("");
                    response_lines.push_back("");
                    response_lines.push_back(it_user_info->second.name);
                    response_lines.push_back(MTK_SS(it_user_info->second.client_code << "  "  <<  market));
                    response_lines.push_back("--------------------------------");
                    
                    for(auto it_grant = it_user_info->second.grant_list.begin(); it_grant != it_user_info->second.grant_list.end(); ++it_grant)
                    {
                        if(it_grant->key.market == market)
                            response_lines.push_back(MTK_SS(*it_grant));
                    }
                }
            }
        }
        response_lines.push_back(MTK_SS(std::endl << "<<<  end of command  " << command));
    }

    void command_get_raw_user_grants_yaml(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        YAML::Emitter yo;
        yo << YAML::BeginSeq;
        
        std::string filter_user = vparams[0];
        for(mtk::list<std::string>::const_iterator it_markets=get_list_markets()->begin(); it_markets != get_list_markets()->end(); ++it_markets)
        {
            std::string market = *it_markets;
            for(mtk::map<std::string  /*user_name*/, msg::sub_user_info>::iterator it_user_info = get_map_user_info()->begin(); 
                                it_user_info != get_map_user_info()->end(); ++it_user_info)
            {
                if(mtk::RegExp(filter_user).Match(it_user_info->second.name))
                    yo << it_user_info->second;
            }
        }
        yo << YAML::EndSeq;
        response_lines.push_back(yo.c_str());
    }
    
    void command_get_raw_client_grants(const std::string& command, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        std::string filter_client = vparams[0];
        for(mtk::list<std::string>::const_iterator it_markets=get_list_markets()->begin(); it_markets != get_list_markets()->end(); ++it_markets)
        {
            std::string market = *it_markets;
            for(mtk::map<std::string  /*user_name*/, msg::sub_user_info>::iterator it_user_info = get_map_user_info()->begin(); 
                                it_user_info != get_map_user_info()->end(); ++it_user_info)
            {
                //if(it_user_info->second.client_code == filter_client)
                if(mtk::RegExp(filter_client).Match(it_user_info->second.client_code))
                {
                    response_lines.push_back("");
                    response_lines.push_back("");
                    response_lines.push_back(it_user_info->second.name);
                    response_lines.push_back(MTK_SS(it_user_info->second.client_code << "  "  <<  market));
                    response_lines.push_back("--------------------------------");
                    for(auto it_grant = it_user_info->second.grant_list.begin(); it_grant != it_user_info->second.grant_list.end(); ++it_grant)
                    {
                        if(it_grant->key.market == market)
                            response_lines.push_back(MTK_SS(*it_grant));
                    }
                }
            }
        }
        response_lines.push_back(MTK_SS(std::endl << "<<<  end of command  " << command));
    }

    void command_get_raw_client_grants_yaml(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        YAML::Emitter yo;
        yo << YAML::BeginSeq;

        std::string filter_client = vparams[0];
        for(mtk::map<std::string  /*user_name*/, msg::sub_user_info>::iterator it_user_info = get_map_user_info()->begin(); 
                            it_user_info != get_map_user_info()->end(); ++it_user_info)
        {
            if(mtk::RegExp(filter_client).Match(it_user_info->second.client_code))
                yo << it_user_info->second;
        }
        yo << YAML::EndSeq;
        response_lines.push_back(yo.c_str());
    }
    
    void command_get_all_raw_grants(const std::string& command, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 0, vparams)  == false)     return;

        for(mtk::list<std::string>::const_iterator it_markets=get_list_markets()->begin(); it_markets != get_list_markets()->end(); ++it_markets)
        {
            std::string market = *it_markets;
            for(mtk::map<std::string  /*user_name*/, msg::sub_user_info>::iterator it_user_info = get_map_user_info()->begin(); 
                                it_user_info != get_map_user_info()->end(); ++it_user_info)
            {
                response_lines.push_back("");
                response_lines.push_back("");
                response_lines.push_back(it_user_info->second.name);
                response_lines.push_back(MTK_SS(it_user_info->second.client_code << "  "  <<  market));
                response_lines.push_back("--------------------------------");
                for(auto it_grant = it_user_info->second.grant_list.begin(); it_grant != it_user_info->second.grant_list.end(); ++it_grant)
                {
                        if(it_grant->key.market == market)
                            response_lines.push_back(MTK_SS(*it_grant));
                }
            }
        }
        response_lines.push_back(MTK_SS(std::endl << "<<<  end of command  " << command));
    }




    
    
    mtk::list<mtk::trd::account::msg::sub_grant>        get_user_grants(const std::string& user_name, const std::string& client_code)
    {
        mtk::list<mtk::trd::account::msg::sub_grant>   result;
        mtk::map<std::string, msg::sub_user_info>::iterator it_user_info = get_map_user_info()->find(user_name);
        if(it_user_info != get_map_user_info()->end())
        {
            for(mtk::list<std::string>::const_iterator it_markets=get_list_markets()->begin(); it_markets != get_list_markets()->end(); ++it_markets)
            {
                std::string market = *it_markets;
                if(it_user_info->second.client_code != client_code)
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "accmgr", MTK_SS("received client code doesn't macth with user client code " 
                                << client_code << it_user_info->second), mtk::alPriorError, mtk::alTypeLogicError));
                    return result;
                }
                
                mtk::CountPtr<mtk::map<std::string  /*acc_name*/, mtk::trd::msg::sub_account_info > >  map_accounts = get_map_registered_accounts();
                for(mtk::map<std::string  /*acc_name*/, mtk::trd::msg::sub_account_info >::iterator it_accounts= map_accounts->begin(); it_accounts != map_accounts->end(); ++it_accounts)
                {
                    std::string  grants = __get_grant_type(market, it_user_info->second, it_accounts->second);
                    if(grants != "")
                    {
                        mtk::trd::account::msg::sub_grant::IC_key grant_key(market, it_accounts->second);
                        if(grants != "<deleted>")
                        {
                            mtk::trd::account::msg::sub_grant  grant (grant_key, MTK_SS(grants[0]));
                            result.push_back(grant);
                        }
                        else
                        {
                            mtk::trd::account::msg::sub_grant  grant (grant_key, MTK_SS(grants));
                            result.push_back(grant);
                        }
                    }
                }
            }
        }
        return result;
    }
    
    
    
};  //  namespace db {
};  //  namespace accmgr { 
