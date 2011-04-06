#include "users_manager.h"

#include <iostream>
#include <fstream>

#include "support/date_time.h"
#include "support/crc32.h"
#include "components/admin/admin.h"
#include "support/string_codec.h"
#include "support/map.hpp"
#include "support/re/RegExp.h"



users_manager* users_manager::ms_instance = 0;



struct user_info
{
    std::string         name;
    std::string         passwordcrc32;
    std::string         client_code;
    mtk::DateTime       created_on;
    std::string         requested_by;
    std::string         notes;
    mtk::DateTime       last_access;
    int                 check_pass_ok;
    int                 check_pass_wrong;
    
    user_info(const std::string& encoded_user_info, bool minimum_params)
        :
                name(""),
                passwordcrc32(""),
                client_code(""),
                created_on(mtk::dtNowLocal()),
                requested_by(""),
                notes(""),
                last_access(mtk::dtNowLocal()),
                check_pass_ok(0),
                check_pass_wrong(0)
    {
        mtk::CodecStringProperties csp;
        mtk::CountPtr<std::map<std::string, std::string> >  properties = csp.Decode(encoded_user_info);

        if(minimum_params)
        {
            #define  CHECK_FIELD(__FIELD_NAME__) \
                if(__FIELD_NAME__=="")    throw mtk::Alarm(MTK_HERE, "userinfo", "mising " #__FIELD_NAME__, mtk::alPriorError);
            CHECK_FIELD((*properties)["name"])
            CHECK_FIELD((*properties)["client_code"])
            CHECK_FIELD((*properties)["requested_by"])
            name            = mtk::s_toUpper((*properties)["name"]);
            client_code     = mtk::s_toUpper((*properties)["client_code"]);
            requested_by    = (*properties)["requested_by"];
            notes           = (*properties)["notes"];
        }
        else
        {
            name            = mtk::s_toUpper((*properties)["name"]);
            client_code     = mtk::s_toUpper((*properties)["client_code"]);
            requested_by    = (*properties)["requested_by"];
            passwordcrc32   = (*properties)["passwordcrc32"];
            notes           = (*properties)["notes"];
            
            bool converted_ok=false;
            mtk::DateTime  converted(mtk::dtNowLocal());
            mtk::s_TRY_stodt((*properties)["created_on"], mtk::dtNowLocal()).assign(converted, converted_ok);
            if(converted_ok==false)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "userinfo", MTK_SS("error converting created_on " << (*properties)["created_on"]), mtk::alPriorError));
            created_on = converted;
            
            mtk::s_TRY_stodt((*properties)["last_access"], mtk::dtNowLocal()).assign(converted, converted_ok);
            if(converted_ok==false)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "userinfo", MTK_SS("error converting last_access " << (*properties)["last_access"]), mtk::alPriorError));
            last_access = converted;
            
            int converted_int=0;
            mtk::s_TRY_stoi((*properties)["check_pass_ok"], 0).assign(converted_int, converted_ok);
            if(converted_ok==false)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "userinfo", MTK_SS("error converting check_pass_ok " << (*properties)["check_pass_ok"]), mtk::alPriorError));
            check_pass_ok = converted_int;

            mtk::s_TRY_stoi((*properties)["check_pass_wrong"], 0).assign(converted_int, converted_ok);
            if(converted_ok==false)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "userinfo", MTK_SS("error converting check_pass_wrong " << (*properties)["check_pass_wrong"]), mtk::alPriorError));
            check_pass_wrong = converted_int;
        }
    }
    
        
    std::string encode(void)
    {
        mtk::CodecStringProperties csp;
        csp.AddProperty("name", name);
        csp.AddProperty("passwordcrc32", passwordcrc32);
        csp.AddProperty("client_code", client_code);
        csp.AddProperty("created_on", MTK_SS(created_on));
        csp.AddProperty("requested_by", requested_by);
        csp.AddProperty("notes", notes);
        csp.AddProperty("last_access", MTK_SS(last_access));
        csp.AddProperty("check_pass_ok", MTK_SS(check_pass_ok));
        csp.AddProperty("check_pass_wrong", MTK_SS(check_pass_wrong));
        return csp.Encode();
    }
};


mtk::CountPtr<mtk::map<std::string, user_info> >  map_user_info;
void save_user_list(void);
bool delayed_save=false;
void check_delayed_save(void);


namespace
{

    const char*   VER           = "2011-03-28";
    const char*   MODIFICATIONS = "           2011-03-28     first version\n";
    
    
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
        
        users_manager::Instance();      //  create instance and it will register aditional commands on constructor  (tick)
    }
    
    
    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)    
}








users_manager::users_manager()
  : num_check_passwords(0)
{
    map_user_info = mtk::make_cptr(new mtk::map<std::string, user_info>);
    
    //user_info ex("name", "cli_code", "requested by", "notes");
    std::string format = "name=name,client_code=cli_code,notes=notes,requested_by=requested by";
    
    MTK_CONNECT_THIS(*mtk::admin::register_command("users", "add", format),   command_add_user)
    MTK_CONNECT_THIS(*mtk::admin::register_command("users", "list", "return the full user list"),   command_user_list)
    MTK_CONNECT_THIS(*mtk::admin::register_command("users", "del", "<user_name>  remove the user", true),   command_remove_user)
    MTK_CONNECT_THIS(*mtk::admin::register_command("users", "find", "<substring> look for users on all fields"),   command_user_find)
    MTK_CONNECT_THIS(*mtk::admin::register_command("users", "resetpwd", "<user_name> create a new password", true),   command_resetpwd)
    MTK_CONNECT_THIS(*mtk::admin::register_command("users", "modif", "modif user data (client_code, notes or requested by)", true),   command_modif_user)
    MTK_CONNECT_THIS(*mtk::admin::register_command("__GLOBAL__", "stats", ""),   command_stats)
    MTK_CONNECT_THIS(*mtk::admin::register_command("users", "stats", ""),   command_stats)
    
    
    
    std::ifstream fusers(mtk::admin::get_config_property("MISC.data").Get().c_str(), std::ios::in );
    int counter = 0;
    char line[2048];
    while(fusers.eof() == false)
    {
        fusers.getline(line, 2048);
        std::string sline = mtk::s_trim(std::string(line), " \t");
        if(sline != "")
        {
            try
            {
                user_info ui(sline, false);
                map_user_info->insert(std::make_pair(ui.name, ui));
                ++counter;
            }
            catch (const mtk::Alarm& error)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "usersmanager", MTK_SS("error reading... "  << line), mtk::alPriorCritic));
            }
        }
    }
    fusers.close();
    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "usersmanager", MTK_SS("readed "  << counter << " users from file"), mtk::alPriorDebug));
    
    MTK_TIMER_1SF(check_delayed_save);
}

users_manager::~users_manager()
{
    save_user_list();
}

users_manager* users_manager::Instance()
{
	if(ms_instance == 0){
		ms_instance = new users_manager();
	}
	return ms_instance;
}

void users_manager::Release()
{
	if(ms_instance){
		delete ms_instance;
	}
	ms_instance = 0;
}


bool   users_manager::check_user_password(const std::string& _user_name, const std::string& key, const std::string& password)
{
    ++num_check_passwords;
    
    std::string user_name = mtk::s_toUpper(_user_name);
    if(exists_user(user_name))
    {
        if(password == mtk::crc32_as_string(MTK_SS(user_name <<  get_passwordcrc32(user_name) << key)))
        {
            map_user_info->find(user_name)->second.check_pass_ok += 1;
            map_user_info->find(user_name)->second.last_access = mtk::dtNowLocal();
            delayed_save = true;
            return true;
        }
        else
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "checkpassw", MTK_SS(user_name << " trying to connect with invalid password"), mtk::alPriorWarning));
            map_user_info->find(user_name)->second.check_pass_wrong += 1;
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

bool   users_manager::check_user_client_code  (const std::string& user_name, const std::string& client_code)
{
    mtk::map<std::string, user_info>::iterator it = map_user_info->find(mtk::s_toUpper(user_name));
    
    if(it !=  map_user_info->end())
    {
        if(it->second.client_code ==  client_code)
            return true;
        else
            return false;
    }
    else
        return false;
}


std::string users_manager::get_passwordcrc32(const std::string& user_name)
{
    if(map_user_info->find(mtk::s_toUpper(user_name)) !=  map_user_info->end())
        return map_user_info->find(mtk::s_toUpper(user_name))->second.passwordcrc32;
    else
        throw mtk::Alarm(MTK_HERE, "getpwd32", MTK_SS(user_name << "  doesn't exists"), mtk::alPriorError);
}

bool users_manager::exists_user(const std::string& user_name)
{
    if(map_user_info->find(mtk::s_toUpper(user_name)) !=  map_user_info->end())
        return true;
    else
        return false;
}

void users_manager::command_user_list(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    //mtk::CountPtr<mtk::map<std::string, user_info> >  map_user_info;    
    for(mtk::map<std::string, user_info>::iterator it= map_user_info->begin(); it != map_user_info->end(); ++it)
    {
        response_lines.push_back(it->second.encode());
    }
}

void users_manager::command_user_find(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    std::string look_for = mtk::s_trim(mtk::s_toUpper(params), " \t");
    if(look_for=="")
    {
        response_lines.push_back(MTK_SS("Empty string on find param. Ignoring command"));
        return;
    }
    
    //mtk::CountPtr<mtk::map<std::string, user_info> >  map_user_info;    
    for(mtk::map<std::string, user_info>::iterator it= map_user_info->begin(); it != map_user_info->end(); ++it)
    {
        std::string encoded_user = it->second.encode();
        if(mtk::s_toUpper(encoded_user).find(look_for) != std::string::npos)
            response_lines.push_back(encoded_user);
    }
    response_lines.push_back(MTK_SS("\nend of find command looking for:  " << params));
}


std::string  get_new_password(void)
{
    static int counter=0;
    ++counter;
    
    return mtk::crc32_as_string(MTK_SS(counter << mtk::rand() << mtk::dtNowLocal()));
}

void users_manager::command_add_user(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    try
    {
        user_info ui(MTK_SS ("\\P" << params), true);
    
        //  check user name format
        mtk::RegExp re("^[a-zA-Z0-9_.]+@[a-zA-Z0-9_.]+$");
        if (re.Match(ui.name))
        {
            response_lines.push_back(MTK_SS("adding user:  " << ui.encode()));
        }
        else
            response_lines.push_back(MTK_SS("error adding user, invalid user format  " <<  ui.name));
        
        //  check that user doesn't exists
        if(map_user_info->find(ui.name) !=  map_user_info->end())
        {
            response_lines.push_back(MTK_SS("error adding user, the user already exists  " <<  ui.name));
            return;
        }
        //add user
        std::string password = get_new_password();
        ui.passwordcrc32 = mtk::crc32_as_string(password);
        map_user_info->insert(std::make_pair(ui.name, ui));
        
        save_user_list();
        
        response_lines.push_back(MTK_SS("name: "  << ui.name));
        response_lines.push_back(MTK_SS("password: "  << password));
    }
    catch(const mtk::Alarm& alarm)
    {
        response_lines.push_back(MTK_SS("error inserting user, check format  "  << alarm));
    }
}

void users_manager::command_modif_user(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    try
    {
        //  mtk::CountPtr<mtk::map<std::string, user_info> >  map_user_info;    
        user_info ui_temp(MTK_SS ("\\P" << params), false);

        mtk::map<std::string, user_info>::iterator it = map_user_info->find(ui_temp.name);
        if(it == map_user_info->end())
        {
            response_lines.push_back(MTK_SS("user not found on request user info  "  << ui_temp.name));
            return;
        }

        if(ui_temp.client_code != "")
            it->second.client_code = ui_temp.client_code;
        if(ui_temp.requested_by != "")
            it->second.requested_by = ui_temp.requested_by;
std::cout << ui_temp.notes << " hhh" << std::endl;
        if(ui_temp.notes != "")
            it->second.notes = ui_temp.notes;
        save_user_list();
        response_lines.push_back(MTK_SS("user modified  "  << it->second.encode()));
    }
    catch(const mtk::Alarm& alarm)
    {
        response_lines.push_back(MTK_SS("error modifying user info  "  << alarm));
    }
}


void save_user_list(void)
{
    std::ofstream fusers(mtk::admin::get_config_property("MISC.data").Get().c_str(), std::ios::out | std::ios::trunc);
    for(mtk::map<std::string, user_info>::iterator it= map_user_info->begin(); it != map_user_info->end(); ++it)
    {
        fusers  << it->second.encode() << std::endl;
    }
    fusers.close();
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


void users_manager::command_remove_user(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    std::string  user_name = mtk::s_toUpper(mtk::s_trim(params, " \t"));
    if(map_user_info->find(user_name)== map_user_info->end())
    {
        response_lines.push_back(MTK_SS("error deleting user:  " << user_name << "   user not found"));
        return;
    }
    else
    {
        map_user_info->erase(user_name);
        response_lines.push_back(MTK_SS("deleted user:  " << user_name));
    }
}

void users_manager::command_resetpwd(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    std::string  user_name = mtk::s_toUpper(mtk::s_trim(params, " \t"));
    if(map_user_info->find(user_name)== map_user_info->end())
    {
        response_lines.push_back(MTK_SS("error reseting password    " << user_name << "   user not found"));
        return;
    }
    else
    {
        std::string  new_password = get_new_password();
        map_user_info->find(user_name)->second.passwordcrc32 = mtk::crc32_as_string(new_password);
        response_lines.push_back(MTK_SS("new passowrd:  " << new_password << "  for user  " << user_name));
        save_user_list();
    }
}


std::string  users_manager::decode_modif_password   (const std::string& user_name, const std::string& key, const mtk::list<int>& new_password)
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

void    users_manager::save_new_password       (const std::string& name, const std::string& password)
{
    std::string  user_name = mtk::s_toUpper(mtk::s_trim(name, " \t"));
    if(map_user_info->find(user_name)== map_user_info->end())
        throw mtk::Alarm(MTK_HERE, "savenewpassw", MTK_SS("Error saving new password. Unknown user " << user_name), mtk::alPriorCritic, mtk::alTypeNoPermisions);
    else
    {
        map_user_info->find(user_name)->second.passwordcrc32 = password;
        mtk::Alarm(mtk::Alarm(MTK_HERE, "savenewpassw", MTK_SS("modif password for " << user_name), mtk::alPriorDebug));
        save_user_list();
    }
}


void users_manager::command_stats      (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(MTK_SS("users: " << map_user_info->size()));
    response_lines.push_back(MTK_SS("rqlogin: " << num_check_passwords));
}
