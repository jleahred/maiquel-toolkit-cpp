#include "prodinfo_grant_db.h"

#include "msg_prodinfo_grant_db.h"


#include "components/admin/admin.h"
#include "support/configfile.h"
#include "support/re/RegExp.h"
#include "components/acs/serv/acs_synchr.h"
#include "components/prices/msg_prices.h"


#include <fstream>




namespace prodinfo_grant { 
    namespace db {


/////////////////////////////////////////
        
    std::string                     data_filename;
    


    mtk::CountPtr<mtk::map<prodinfo_grant::db::msg::sub_client__pattern_users::key_type, prodinfo_grant::db::msg::sub_client__pattern_users> >   
    /////////////////////////
    get_map_grants(void)
    /////////////////////////
    {
        static   auto   result = mtk::make_cptr(new  mtk::map<prodinfo_grant::db::msg::sub_client__pattern_users::key_type, prodinfo_grant::db::msg::sub_client__pattern_users>);
        return   result;
    }

/////////////////////////////////////////



        


        
void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_load(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_save(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_check(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);


void command_client_add(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_client_del(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_client_fulldell(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_client_find(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_check(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_re_user_add(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_re_user_del(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_re_user_full_del(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_user_grants(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_client_list_names(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);



void register_global_commands (void)
{
    mtk::admin::register_command("__GLOBAL__",  "stats",     "")->connect(command_stats);
    mtk::admin::register_command("db",  "stats",     "")->connect(command_stats);
    
    mtk::admin::register_command("db",  "client.add",       "<client_code>")->connect(command_client_add);
    mtk::admin::register_command("db",  "client.del",       "<client_code>")->connect(command_client_del);
    mtk::admin::register_command("db",  "client.fulldel",   "<client_code>  it will delete the client even if it has grants configured", true)->connect(command_client_fulldell);
    mtk::admin::register_command("db",  "client.find",      "<reg-expr>")->connect(command_client_find);
    mtk::admin::register_command("db",  "client.list_names","list all client names configured")->connect(command_client_list_names);

    mtk::admin::register_command("db",  "client.user.add",       "<client_code> <re-user>  <re-market> <re-prod_code>")->connect(command_re_user_add);
    mtk::admin::register_command("db",  "client.user.del",       "<client_code> <re-user>  <re-market> <re-prod_code>")->connect(command_re_user_del);
    mtk::admin::register_command("db",  "client.user.fulldel",   "<client_code> <re-user>  ", true)->connect(command_re_user_full_del);
    mtk::admin::register_command("db",  "client.user.grants",    "<client_code> <user>")->connect(command_user_grants);


    mtk::admin::register_command("db",  "load",        "DANGEROUS delete current info and load from file", true)->connect(command_load);
    mtk::admin::register_command("db",  "save",        "save filters to db", true)->connect(command_save);

    mtk::admin::register_command("db",  "check",        "it will look for inconsistent info configured in db", true)->connect(command_check);

}





void init(const std::string&   _data_filename)
{   
    register_global_commands();
    data_filename = _data_filename;
    load(); 
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



void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(MTK_SS("map_grants: " << get_map_grants()->size()));
}



void command_load(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 0, vparams)  == false)     return;
        
        response_lines.push_back("loading...");
        load();
        command_stats("", "", response_lines);
}

void command_save(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 0, vparams)  == false)     return;
        
        response_lines.push_back("saving...");
        save();
        command_stats("", "", response_lines);
}


void command_check(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back("pending...");
}
        


        
        
void save(void)
{
    std::ofstream file;
    file.open (data_filename.c_str(), std::ios::out | std::ios::trunc);


    try
    {
        YAML::Emitter out;
        out  <<  YAML::BeginMap;

        out  << YAML::Key << "version"   <<  YAML::Value << 1;

        out  << YAML::Key << "grants"   <<  YAML::Value  <<  *get_map_grants();


        out <<  YAML::EndMap;

        file << out.c_str();
        file.close();
    }
    MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "accmgr_db", "error saving db")
}
void load(void)
{
    get_map_grants()->clear();
    std::ifstream file(data_filename.c_str());

    try
    {
        YAML::Parser parser(file);

        YAML::Node doc;
        parser.GetNextDocument(doc);
        std::string config_version;
        
        doc["grants"] >> *get_map_grants();
        file.close();
    }
    MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "accmgr_db", "error loading db")
}
    
        
        
        


void command_client_add(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    mtk::vector<std::string>  vparams;
    if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;
    std::string  client_code(vparams[0]);
    
    auto it_find = get_map_grants()->find(client_code);
    if(it_find != get_map_grants()->end())
    {
        response_lines.push_back("alreay exists a client with this code");
        response_lines.push_back(YAML::string_from_yaml(it_find->second));
    }
    else
    {
        auto  emtpy_list = prodinfo_grant::db::msg::sub_client__pattern_users(client_code, mtk::list<prodinfo_grant::db::msg::sub_pattern_users_grants>());
        auto  it_inserted = get_map_grants()->insert(std::make_pair(client_code, emtpy_list)).first;
        response_lines.push_back(YAML::string_from_yaml(it_inserted->second));
    }
    save();
}
void command_client_del(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    mtk::vector<std::string>  vparams;
    if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;
    std::string  client_code(vparams[0]);
    
    auto it_find = get_map_grants()->find(client_code);
    if(it_find == get_map_grants()->end())
    {
        response_lines.push_back(MTK_SS("client code not located  " << client_code));
        return;
    }
    else
    {
        if(it_find->second.users_pattern.size() != 0)
        {
            response_lines.push_back(MTK_SS("client is not empty  " << client_code));
            response_lines.push_back(YAML::string_from_yaml(it_find->second));
            return;
        }
        get_map_grants()->erase(it_find);
        response_lines.push_back(MTK_SS("deleted " << client_code));
        save();
    }
}
void command_client_fulldell(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    mtk::vector<std::string>  vparams;
    if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;
    std::string  client_code(vparams[0]);
    
    auto it_find = get_map_grants()->find(client_code);
    if(it_find == get_map_grants()->end())
    {
        response_lines.push_back(MTK_SS("client code not located  " << client_code));
        return;
    }
    else
    {
        get_map_grants()->erase(it_find);
        save();
        response_lines.push_back(MTK_SS("deleted " << client_code));
    }
}
void command_client_find(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    mtk::vector<std::string>  vparams;
    if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;
    mtk::RegExp  re_client_code(vparams[0]);
    

    for(auto it = get_map_grants()->begin(); it!= get_map_grants()->end(); ++it)
    {
        if(re_client_code.Match(it->first))
            response_lines.push_back(YAML::string_from_yaml(it->second));
    }
    response_lines.push_back("end of command");
}
void command_client_list_names(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    mtk::vector<std::string>  vparams;
    if(check_and_split_params__converting2upper(params, response_lines, 0, vparams)  == false)     return;

    for(auto it = get_map_grants()->begin(); it!= get_map_grants()->end(); ++it)
    {
        response_lines.push_back(it->first);
    }
    response_lines.push_back("end of command");
}
void command_re_user_add(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    //  mtk::admin::register_command("db",  "puser.add",       "<client_code> <re-user>  <re-market> <re-prod_code>")->connect(command_re_user_add);

    mtk::vector<std::string>  vparams;
    if(check_and_split_params__converting2upper(params, response_lines, 4, vparams)  == false)     return;
    std::string  client_code = vparams[0];
    std::string  re_user = vparams[1];
    mtk::msg::sub_product_code  pc_pattern (vparams[2], vparams[3]);
    
    auto it_find = get_map_grants()->find(client_code);
    if(it_find == get_map_grants()->end())
    {
        response_lines.push_back(MTK_SS("client code not located  " << client_code));
        response_lines.push_back(MTK_SS("ignoring command"));
        return;
    }
    else
    {
        for(auto it = it_find->second.users_pattern.begin(); it != it_find->second.users_pattern.end(); ++it)
        {
            if(it->user_pattern == re_user)
            {
                //  look for repeated product code pattern
                for(auto it_pc= it->re_product_code_list.begin(); it_pc != it->re_product_code_list.end(); ++it_pc)
                {
                    if(*it_pc == pc_pattern)
                    {
                        response_lines.push_back(MTK_SS("patter already registered on this user patter  "));
                        response_lines.push_back(MTK_SS("ignoring command"));
                        response_lines.push_back(YAML::string_from_yaml(it_find->second));
                        return;
                    }
                }
                it->re_product_code_list.push_back(pc_pattern);
                response_lines.push_back(YAML::string_from_yaml(it_find->second));
                return;
            }
        }
        //  not located
        //  insert empty and push
        auto   list_product_code = mtk::list<mtk::msg::sub_product_code>();
        list_product_code.push_back(pc_pattern);
        prodinfo_grant::db::msg::sub_pattern_users_grants  new_user_grants_pattern(re_user, list_product_code, mtk::dtNowLocal());
        it_find->second.users_pattern.push_back(new_user_grants_pattern);
        response_lines.push_back(YAML::string_from_yaml(it_find->second));
    }
    save();
}
void command_re_user_del(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    //  mtk::admin::register_command("db",  "puser.del",       "<client_code> <re-user>  <re-market> <re-prod_code>")->connect(command_re_user_del);

    mtk::vector<std::string>  vparams;
    if(check_and_split_params__converting2upper(params, response_lines, 4, vparams)  == false)     return;
    std::string  client_code = vparams[0];
    std::string  re_user = vparams[1];
    mtk::msg::sub_product_code  pc_pattern (vparams[2], vparams[3]);
    
    auto it_find = get_map_grants()->find(client_code);
    if(it_find == get_map_grants()->end())
    {
        response_lines.push_back(MTK_SS("client code not located  " << client_code));
        response_lines.push_back(MTK_SS("ignoring command"));
        return;
    }
    else
    {
        for(auto it = it_find->second.users_pattern.begin(); it != it_find->second.users_pattern.end(); ++it)
        {
            if(it->user_pattern == re_user)
            {
                for(auto it2 = it->re_product_code_list.begin(); it2 != it->re_product_code_list.end(); ++it2)
                {
                    if(*it2 == pc_pattern)
                    {
                        response_lines.push_back("deleting...\n");
                        it->re_product_code_list.erase(it2);
                        if(it->re_product_code_list.size() == 0)
                        {
                            response_lines.push_back("empty user patter,  deleting...\n");
                            it_find->second.users_pattern.erase(it);
                        }
                        response_lines.push_back(YAML::string_from_yaml(it_find->second));
                        save();
                        return;
                    }
                }
            }
        }
        //  not located
        //  insert empty and push
        response_lines.push_back(MTK_SS("pattern  not located  "));
        response_lines.push_back(YAML::string_from_yaml(it_find->second));
        response_lines.push_back(MTK_SS("ignoring command"));
    }
}
void command_re_user_full_del(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    //  mtk::admin::register_command("db",  "puser.del",       "<client_code> <re-user>  <re-market> <re-prod_code>")->connect(command_re_user_del);

    mtk::vector<std::string>  vparams;
    if(check_and_split_params__converting2upper(params, response_lines, 4, vparams)  == false)     return;
    std::string  client_code = vparams[0];
    std::string  re_user = vparams[1];
    mtk::msg::sub_product_code  pc_pattern (vparams[2], vparams[3]);
    
    auto it_find = get_map_grants()->find(client_code);
    if(it_find == get_map_grants()->end())
    {
        response_lines.push_back(MTK_SS("client code not located  " << client_code));
        response_lines.push_back(MTK_SS("ignoring command"));
        return;
    }
    else
    {
        for(auto it = it_find->second.users_pattern.begin(); it != it_find->second.users_pattern.end(); ++it)
        {
            if(it->user_pattern == re_user)
            {
                it_find->second.users_pattern.erase(it);
                response_lines.push_back(YAML::string_from_yaml(it_find->second));
                save();
                return;
            }
        }
        //  not located
        //  insert empty and push
        response_lines.push_back(MTK_SS("pattern  not located  "));
        response_lines.push_back(YAML::string_from_yaml(it_find->second));
        response_lines.push_back(MTK_SS("ignoring command"));
    }
}
        
void command_user_grants(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    //mtk::admin::register_command("db",  "client.user.grants",    "<client_code> <user>")->connect(command_user_grants);

    mtk::vector<std::string>  vparams;
    if(check_and_split_params__converting2upper(params, response_lines, 2, vparams)  == false)     return;
    std::string  client_code = vparams[0];
    std::string  user = vparams[1];
    
    auto it_find = get_map_grants()->find(client_code);
    if(it_find == get_map_grants()->end())
    {
        response_lines.push_back(MTK_SS("client code not located  " << client_code));
        response_lines.push_back(MTK_SS("ignoring command"));
        return;
    }
    else
    {
        for(auto it = it_find->second.users_pattern.begin(); it != it_find->second.users_pattern.end(); ++it)
        {
            mtk::RegExp  re(it->user_pattern);
            if(re.Match(user))
            {
                response_lines.push_back(YAML::string_from_yaml(*it));
            }
        }
        response_lines.push_back(MTK_SS("end of command"));
    }
}
        
        


bool has_grants(const mtk::prices::msg::req_product_info&  pi_request)
{
    mtk::acs::msg::res_login::IC_session_info  sessinfo = mtk::acs_server::synchr::get_session_info_for_session_id(pi_request.request_info.req_id.session_id);

    std::string  user_name = sessinfo.user_name;
    std::string  client_code = sessinfo.client_code;
    
    
    
    auto it_find = get_map_grants()->find(client_code);
    if(it_find == get_map_grants()->end())
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "prodinf_grants", MTK_SS("received request on non valid client  " << client_code << std::endl << pi_request),
                            mtk::alPriorError, mtk::alTypeNoPermisions));
    }
    else
    {
        for(auto it = it_find->second.users_pattern.begin(); it != it_find->second.users_pattern.end(); ++it)
        {
            mtk::RegExp  re(it->user_pattern);
            if(re.Match(user_name))
            {
                it->last_applied_rule = mtk::dtNowLocal();
                return true;
            }
        }
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "prodinf_grants", MTK_SS("received request on non valid user_name  " << user_name << std::endl << pi_request),
                            mtk::alPriorError, mtk::alTypeNoPermisions));
    }
    return false;
}        
        
        
        
    };  //      namespace   db {
};      //  namespace prodinfo_grant { 
