#include "users_manager.h"

#include <iostream>
#include <fstream>

#include "support/date_time.h"
#include "support/crc32.h"
#include "components/admin/admin.h"
#include "support/string_codec.h"
#include "support/map.hpp"
#include "support/re/RegExp.h"

#include "msg_users_manager.h"





namespace
{

    const char*   VER           =   "2011-03-28";
    const char*   MODIFICATIONS =   "           2011-03-28     first version\n"
                                    "           2011-08-08     working with YAML\n";
    
    
    void command_version(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(MTK_SS(__FILE__ << ":  " << VER));
    }

    void command_modifications  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(__FILE__);
        response_lines.push_back(".......................................");
        response_lines.push_back(MODIFICATIONS);
    }


    
    void register_global_commands (void)
    {
        mtk::admin::register_command("__GLOBAL__",  "ver",   "")->connect(command_version);
        mtk::admin::register_command("__GLOBAL__",  "modifs",   "")->connect(command_modifications);
        mtk::admin::register_command("users",  "ver",   "")->connect(command_version);
        mtk::admin::register_command("users",  "modifs",   "")->connect(command_modifications);
    }
    
    
    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)    
}





namespace users_manager  {



int  num_check_passwords  = 0;
mtk::CountPtr<mtk::map<sub_user_acs_info::key_type, sub_user_acs_info> >  get_map_user_info(void)
{
    static auto result = mtk::make_cptr(new mtk::map<sub_user_acs_info::key_type, sub_user_acs_info>);
    return result;
}



void load_user_list(void);
void save_user_list(void);
bool delayed_save=false;
void check_delayed_save(void);






bool         exists_user        (const std::string& user_name);
std::string  get_passwordcrc32  (const std::string& user_name);

void command_add_user   (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_remove_user(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_user_find  (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_resetpwd   (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_modif_user (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_stats      (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);




void        init                    (void)
{
    std::string format = YAML::string_from_yaml(sub_user_info("_", "_", "_", "_"), true);
    
    mtk::admin::register_command("users", "add", format)                                        ->connect(&command_add_user);
    mtk::admin::register_command("users", "find", "<reg-expr> look for users on all fields")    ->connect(&command_user_find);
    mtk::admin::register_command("users", "modif", "modif user data (same format as add user)", true)->connect(&command_modif_user);
    mtk::admin::register_command("users", "resetpwd", "<user_name> create a new password", true)->connect(&command_resetpwd);
    mtk::admin::register_command("users", "del", "<user_name>  remove the user", true)          ->connect(&command_remove_user);
    mtk::admin::register_command("__GLOBAL__", "stats", "")                                     ->connect(&command_stats);
    mtk::admin::register_command("users", "stats", "")                                          ->connect(&command_stats);

    load_user_list();
    
    MTK_TIMER_1SF(check_delayed_save);
}






bool   check_user_password(const std::string& _user_name, const std::string& key, const std::string& password)
{
    ++num_check_passwords;
    std::string user_name = mtk::s_toUpper(_user_name);
    if(exists_user(user_name))
    {
        if(password == mtk::crc32_as_string(MTK_SS(user_name <<  get_passwordcrc32(user_name) << key)))
        {
            get_map_user_info()->find(user_name)->second.check_pass_ok += 1;
            get_map_user_info()->find(user_name)->second.last_access = mtk::dtNowLocal();
            delayed_save = true;
            return true;
        }
        else
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "checkpassw", MTK_SS(user_name << " trying to connect with invalid password"), mtk::alPriorWarning));
            get_map_user_info()->find(user_name)->second.check_pass_wrong += 1;
            delayed_save = true;
            return false;
        }
    }
    else
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "checkpassw", MTK_SS(user_name << " doesn't exist"), mtk::alPriorWarning));
        return false;
    }
}

bool   check_user_client_code  (const std::string& user_name, const std::string& client_code)
{
    mtk::map<std::string, sub_user_acs_info>::iterator it = get_map_user_info()->find(mtk::s_toUpper(user_name));
    
    if(it !=  get_map_user_info()->end())
    {
        if(it->second.user_info.client_code ==  client_code)
            return true;
        else
            return false;
    }
    else
        return false;
}


std::string  get_passwordcrc32(const std::string& user_name)
{
    if(get_map_user_info()->find(mtk::s_toUpper(user_name)) !=  get_map_user_info()->end())
        return get_map_user_info()->find(mtk::s_toUpper(user_name))->second.passwordcrc32;
    else
        throw mtk::Alarm(MTK_HERE, "getpwd32", MTK_SS(user_name << "  doesn't exists"), mtk::alPriorError);
}

bool   exists_user(const std::string& user_name)
{
    if(get_map_user_info()->find(mtk::s_toUpper(user_name)) !=  get_map_user_info()->end())
        return true;
    else
        return false;
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


void   command_user_find(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    mtk::RegExp re(mtk::s_toUpper(params));
    
    int located=0;
    for(auto it= get_map_user_info()->begin(); it != get_map_user_info()->end(); ++it)
    {
        std::string encoded_user = YAML::string_from_yaml(it->second);
        if (re.Match(mtk::s_toUpper(encoded_user)))
        {
            response_lines.push_back(encoded_user);
            response_lines.push_back("");
            ++located;
            if(located > 10)
            {
                response_lines.push_back("...  truncating response  ...");
                return;
            }
        }
    }
    response_lines.push_back(MTK_SS("\nend of find command looking for:  " << params));
}


std::string  get_new_password(void)
{
    static int counter=0;
    ++counter;
    
    return mtk::crc32_as_string(MTK_SS(counter << mtk::rand() << mtk::dtNowLocal()));
}


bool  check_user_format(const sub_user_info& ui, mtk::list<std::string>&  response_lines)
{
    {
        std::string  format("^[a-zA-Z0-9_.]+@[a-zA-Z0-9_.]+$");
        mtk::RegExp re(format);
        if (re.Match(ui.name)==false)
        {
            response_lines.push_back(MTK_SS("error adding user, invalid user format  " <<  ui.name  << "  "  << format));
            return false;
        }
    }
    {
        std::string  format("^[a-zA-Z0-9_]+$");
        mtk::RegExp re(format);
        if (re.Match(ui.client_code)==false)
        {
            response_lines.push_back(MTK_SS("error adding user, invalid client format  " <<  ui.client_code  << "  "  << format));
            return false;
        }
    }
    return true;
}


void   command_add_user(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    try
    {
        sub_user_info  ui   =  YAML::parse_from_yaml_string<sub_user_info>(params);
        ui.name = mtk::s_toUpper(ui.name);
        ui.client_code = mtk::s_toUpper(ui.client_code);

        if (check_user_format(ui, response_lines) == false)
            return;
        
        //  check that user doesn't exists
        if(get_map_user_info()->find(ui.name) !=  get_map_user_info()->end())
        {
            response_lines.push_back(MTK_SS("error adding user, the user already exists  " <<  ui.name));
            return;
        }

        response_lines.push_back(MTK_SS("adding user_______________\n" << YAML::string_from_yaml(ui)));
        //add user
        std::string password = get_new_password();
        sub_user_acs_info  ui_acs(ui, mtk::crc32_as_string(password), mtk::dtNowLocal(), mtk::dtNowLocal(), 0, 0);
        get_map_user_info()->insert(std::make_pair(ui.name, ui_acs));
        
        save_user_list();
        
        response_lines.push_back(MTK_SS("name: "  << ui.name));
        response_lines.push_back(MTK_SS("password: "  << password));
    }
    catch(const mtk::Alarm& alarm)
    {
        response_lines.push_back(MTK_SS("error inserting user, check format  "  << alarm));
    }
}

void   command_modif_user(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    try
    {
        sub_user_info  ui_temp   =  YAML::parse_from_yaml_string<sub_user_info>(params);
        ui_temp.name = mtk::s_toUpper(ui_temp.name);
        ui_temp.client_code = mtk::s_toUpper(ui_temp.client_code);

        mtk::map<std::string, sub_user_acs_info>::iterator it = get_map_user_info()->find(ui_temp.name);
        if(it == get_map_user_info()->end())
        {
            response_lines.push_back(MTK_SS("user not found on request modif  user info  "  << ui_temp.name));
            return;
        }

        if (check_user_format(ui_temp, response_lines) == false)
            return;
        it->second.user_info = ui_temp;
            
        save_user_list();
        response_lines.push_back(MTK_SS("user modified  .....................\n" << YAML::string_from_yaml(it->second)));
    }
    catch(const mtk::Alarm& alarm)
    {
        response_lines.push_back(MTK_SS("error modifying user info  "  << alarm));
    }
}


void save_user_list(void)
{
    std::ofstream file(mtk::admin::get_config_property("MISC.data").Get().c_str(), std::ios::out | std::ios::trunc);


    try
    {
        YAML::Emitter out;
        out  <<  YAML::BeginMap;

        out  << YAML::Key << "version"   <<  YAML::Value << 1;

        out  << YAML::Key << "data"   <<  YAML::Value  <<  *get_map_user_info();

        out <<  YAML::EndMap;

        file << out.c_str();
        file.close();
    }
    MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "users_manager", "error saving db")
    
}


void load_user_list(void)
{
    get_map_user_info()->clear();
    
    std::ifstream file(mtk::admin::get_config_property("MISC.data").Get().c_str());

    try
    {
        YAML::Parser parser(file);

        YAML::Node doc;
        parser.GetNextDocument(doc);
        //std::string config_version;
        
        doc["data"] >> *get_map_user_info();

        file.close();
    }
    MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "users_manager", "error loading db")
}


void check_delayed_save(void)
{
    //bool delayed_save=false;
    MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(2))
    
        if(delayed_save)
        {
           delayed_save=false; 
           save_user_list();
        }
        
    MTK_END_EXEC_MAX_FREC
}


void   command_remove_user(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    std::string  user_name = mtk::s_toUpper(mtk::s_trim(params, " \t"));
    if(get_map_user_info()->find(user_name)== get_map_user_info()->end())
    {
        response_lines.push_back(MTK_SS("error deleting user:  " << user_name << "   user not found"));
        return;
    }
    else
    {
        get_map_user_info()->erase(user_name);
        save_user_list();
        response_lines.push_back(MTK_SS("deleted user:  " << user_name));
    }
}

void   command_resetpwd(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    std::string  user_name = mtk::s_toUpper(mtk::s_trim(params, " \t"));
    if(get_map_user_info()->find(user_name)== get_map_user_info()->end())
    {
        response_lines.push_back(MTK_SS("error reseting password    " << user_name << "   user not found"));
        return;
    }
    else
    {
        std::string  new_password = get_new_password();
        get_map_user_info()->find(user_name)->second.passwordcrc32 = mtk::crc32_as_string(new_password);
        response_lines.push_back(MTK_SS("new passowrd:  " << new_password << "  for user  " << user_name));
        save_user_list();
    }
}


std::string    decode_modif_password   (const std::string& user_name, const std::string& key, const mtk::list<int>& new_password)
{
    std::string decoded_new_password;
    std::string old_password_crc32 = get_passwordcrc32(user_name);

    int contador=0;
    for(mtk::list<int>::const_iterator it= new_password.begin(); it!= new_password.end(); ++it)
    {
        decoded_new_password += char(*it    - old_password_crc32[contador%(old_password_crc32.size()-1)]
                                            - key[contador%(key.size()-1)]);
        ++contador;
    }
        
    return decoded_new_password;
}

void    save_new_password       (const std::string& name, const std::string& password)
{
    std::string  user_name = mtk::s_toUpper(mtk::s_trim(name, " \t"));
    if(get_map_user_info()->find(user_name)== get_map_user_info()->end())
        throw mtk::Alarm(MTK_HERE, "savenewpassw", MTK_SS("Error saving new password. Unknown user " << user_name), mtk::alPriorCritic, mtk::alTypeNoPermisions);
    else
    {
        get_map_user_info()->find(user_name)->second.passwordcrc32 = password;
        mtk::Alarm(mtk::Alarm(MTK_HERE, "savenewpassw", MTK_SS("modif password for " << user_name), mtk::alPriorDebug));
        save_user_list();
    }
}


void   command_stats      (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(MTK_SS("users: " << get_map_user_info()->size()));
    response_lines.push_back(MTK_SS("rqlogin: " << num_check_passwords));
}




};   //  namespace users_manager  {