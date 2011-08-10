#include "tree_db.h"

#include "msg_tree_server_db.h"

#include "components/admin/admin.h"
#include "support/configfile.h"
#include "support/re/RegExp.h"
#include "components/acs/serv/acs_synchr.h"


#include <fstream>




namespace tree_server2 { 
    namespace db {


/////////////////////////////////////////
        
    mtk::CountPtr<mtk::ConfigFile>  data_tree;
    std::string                     data_grants_filename;
    


    mtk::CountPtr<mtk::map<tree_server2::msg::sub_path_grants::key_type, tree_server2::msg::sub_path_grants> >   
    /////////////////////////
    get_map_path_grants(void)
    /////////////////////////
    {
        static   auto   result = mtk::make_cptr(new  mtk::map<tree_server2::msg::sub_path_grants::key_type, tree_server2::msg::sub_path_grants>);
        return   result;
    }

/////////////////////////////////////////



        


        
void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

void command_add_bypass(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_del_bypass(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_find_bypass(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

void command_add_grant(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_del_grant(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_find_grant_path(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_find_grant_user(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

void command_load(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
void command_save(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);


void command_check(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);




void register_global_commands (void)
{
    mtk::admin::register_command("__GLOBAL__",  "stats",     "")->connect(command_stats);
    mtk::admin::register_command("db",  "stats",     "")->connect(command_stats);
    
    mtk::admin::register_command("db",  "bypass.add",  "<re-path>", true)->connect(command_add_bypass);
    mtk::admin::register_command("db",  "bypass.del",  "<re-path>", true)->connect(command_del_bypass);
    mtk::admin::register_command("db",  "bypass.find", "<reg-expr>")->connect(command_find_bypass);

    mtk::admin::register_command("db",  "grant.add",  "<re-user_name>  <re-path>")->connect(command_add_grant);
    mtk::admin::register_command("db",  "grant.del",  "<re-user_name>  <re-path>")->connect(command_del_grant);
    mtk::admin::register_command("db",  "grant.find.path", "<reg-expr>")->connect(command_find_grant_path);
    mtk::admin::register_command("db",  "grant.find.user", "<reg-expr>")->connect(command_find_grant_user);


    mtk::admin::register_command("db",  "load",        "DANGEROUS delete current info and load from file", true)->connect(command_load);
    mtk::admin::register_command("db",  "save",        "save filters to db", true)->connect(command_save);

    mtk::admin::register_command("db",  "check",        "it will look for inconsistent info configured in db", true)->connect(command_check);

}





void init(const std::string&   _data_tree_filename, const std::string&  _data_grants_filename)
{   
    register_global_commands();
    data_tree = mtk::make_cptr(new mtk::ConfigFile(_data_tree_filename));
    data_grants_filename = _data_grants_filename;
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

bool  insert_if_not_duplicated(const std::string& item2insert, mtk::list<std::string>& list2insert, mtk::list<std::string>&  response_lines)
{
    for(auto it=list2insert.begin(); it!=list2insert.end(); ++it)
    {
        if(*it == item2insert)
        {
            response_lines.push_back(MTK_SS("duplicated item  " << item2insert  << "   ignoring request"));
            return false;
        }
    }
    list2insert.push_back(item2insert);
    return true;
}


void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(MTK_SS("map_grants: " << get_map_path_grants()->size()));
}

void command_add_bypass(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back("pending...");
}

void command_del_bypass(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back("pending...");
}

void command_find_bypass(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back("pending...");
}

void command_add_grant(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    mtk::vector<std::string>  vparams;
    if(check_and_split_params__converting2upper(params, response_lines, 2, vparams)  == false)     return;
    std::string  re_user_name(vparams[0]);
    std::string  re_path(vparams[1]);
    
    
    auto it = get_map_path_grants()->find(re_path);
    if (it==get_map_path_grants()->end())
        it = get_map_path_grants()->insert(std::make_pair(re_path, tree_server2::msg::sub_path_grants(re_path, mtk::list<std::string>()))).first;
    insert_if_not_duplicated(re_user_name, it->second.users, response_lines);

    save();
    response_lines.push_back(MTK_SS("......."  << std::endl  <<  YAML::string_from_yaml(it->second)));
}

void command_del_grant(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    mtk::vector<std::string>  vparams;
    if(check_and_split_params__converting2upper(params, response_lines, 2, vparams)  == false)     return;
    std::string  re_user_name(vparams[0]);
    std::string  re_path(vparams[1]);
    
    
    auto it = get_map_path_grants()->find(re_path);
    if (it==get_map_path_grants()->end())
        response_lines.push_back(MTK_SS(re_path << "   not found"));
    else
    {
        auto ituser = it->second.users.begin();
        while(ituser != it->second.users.end())
        {
            if(*ituser == re_user_name)
                ituser = it->second.users.erase(ituser);
            else
                ++ituser;
        }
        response_lines.push_back(MTK_SS("......."  << std::endl  <<  YAML::string_from_yaml(it->second)));
        if(it->second.users.size() == 0)
        {
            get_map_path_grants()->erase(re_path);
            response_lines.push_back(MTK_SS(re_path << "  is empty, deleting..."));
        }
    }
    save();
    response_lines.push_back("end of command");
}

void command_find_grant_path(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    mtk::vector<std::string>  vparams;
    if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;
    mtk::RegExp  re(vparams[0]);
    
    for(auto it=get_map_path_grants()->begin(); it!=get_map_path_grants()->end(); ++it)
    {
        if(re.Match(it->second.re_path))
        {
            response_lines.push_back(YAML::string_from_yaml(it->second));
        }
    }
    response_lines.push_back("end of command");
}

void command_find_grant_user(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    mtk::vector<std::string>  vparams;
    if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;
    mtk::RegExp  re(vparams[0]);


    for(auto it=get_map_path_grants()->begin(); it!=get_map_path_grants()->end(); ++it)
    {
        for(auto ituser = it->second.users.begin(); ituser != it->second.users.end(); ++ituser)
        {
            if(re.Match(*ituser))
                response_lines.push_back(MTK_SS(it->first << " , " << *ituser));
        }
    }
    response_lines.push_back("end of command");
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
        


        
        
bool  check_if_user_has_grants_for_request(const mtk::gen::msg::req_tree_items&  tree_request)
{
    mtk::acs::msg::res_login::IC_session_info  sessinfo = mtk::acs_server::synchr::get_session_info_for_session_id(tree_request.request_info.req_id.session_id);

    std::string  user_name = sessinfo.user_name;
    
    for(auto it=get_map_path_grants()->begin(); it!=get_map_path_grants()->end(); ++it)
    {
        mtk::RegExp  re_path(it->first);
        if(re_path.Match(tree_request.branch))
        {
            for(auto ituser = it->second.users.begin(); ituser != it->second.users.end(); ++ituser)
            {
                mtk::RegExp  re(*ituser);
                if(re.Match(user_name))
                    return true;
            }
        }
    }
    return false;
}        
        
mtk::list<mtk::gen::msg::sub_tree_item>   get_items_for_branch__ifso(const mtk::gen::msg::req_tree_items&  tree_request)
{
    auto result  =  mtk::list<mtk::gen::msg::sub_tree_item>();
    
    if(check_if_user_has_grants_for_request(tree_request) == false)
        return result;
    
    mtk::list<std::string>  nodes = data_tree->GetNodes(tree_request.branch);
    
    mtk::list<std::string>::iterator it = nodes.begin();
    int counter=0;
    while(it != nodes.end())
    {
        std::string name = *it;
        std::string description = data_tree->GetValue(MTK_SS(tree_request.branch<<"."<<*it<<".description")).Get();
        std::string market_code = data_tree->GetValue(MTK_SS(tree_request.branch<<"."<<*it<<".market")).Get();
        std::string full_branch = MTK_SS(tree_request.branch << "." <<*it);
        if(market_code != "")
        {
            mtk::msg::sub_product_code pc ( mtk::msg::sub_product_code(market_code, *it));
            result.push_back(mtk::gen::msg::sub_tree_item(full_branch, description, mtk::make_nullable(pc)));
        }
        else
            result.push_back(mtk::gen::msg::sub_tree_item(full_branch, description, mtk::nullable<mtk::msg::sub_product_code>()));
        
        ++it;
        if(++counter  > 100)
        {
            MTK_EXEC_MAX_FREC_NO_FIRST_S(mtk::dtSeconds(40))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "tree_server", MTK_SS("too long response for  \n" << tree_request), mtk::alPriorError, mtk::alTypeNoPermisions));
            MTK_END_EXEC_MAX_FREC
            break;
        }
    }
    return  result;
}
        
        

void save(void)
{
    std::ofstream file;
    file.open (data_grants_filename.c_str(), std::ios::out | std::ios::trunc);


    try
    {
        YAML::Emitter out;
        out  <<  YAML::BeginMap;

        out  << YAML::Key << "version"   <<  YAML::Value << 1;

        out  << YAML::Key << "grants"   <<  YAML::Value  <<  *get_map_path_grants();


        out <<  YAML::EndMap;

        file << out.c_str();
        file.close();
    }
    MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "accmgr_db", "error saving db")
}
void load(void)
{
    get_map_path_grants()->clear();
    std::ifstream file(data_grants_filename.c_str());

    try
    {
        YAML::Parser parser(file);

        YAML::Node doc;
        parser.GetNextDocument(doc);
        std::string config_version;
        
        doc["grants"] >> *get_map_path_grants();
        file.close();
    }
    MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "accmgr_db", "error loading db")
}
    
        
        
        
        
        
        
        
        
        
        
        
    };  //      namespace   db {
};      //  namespace tree_server2 { 
