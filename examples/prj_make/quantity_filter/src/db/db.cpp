#include   "db.h"

#include "support/count_ptr.hpp"
#include "support/map.hpp"
#include "msg_structs.h"
#include "components/admin/admin.h"
#include "support/re/RegExp.h"
#include "components/acs/serv/acs_synchr.h"

#include <fstream>
#include <set>


namespace qfmgr { 
namespace db {

    std::string  db_file_name;
    
    

    mtk::CountPtr<mtk::list<std::string> >   ref_list_markets(void)
    {
        static mtk::CountPtr<mtk::list<std::string> >  result;
        if(result.isValid() == false)
            result = mtk::make_cptr(new  mtk::list<std::string>);
        return result;
    }
    mtk::list<std::string>&   get_market_list(void)
    {
        return *ref_list_markets();
    }
    


    mtk::CountPtr<mtk::map<std::string, msg::sub_product > >   ref_map_registered_products(void)
    {
        static mtk::CountPtr<mtk::map<std::string, msg::sub_product >  > result;
        if(result.isValid() == false)
            result = mtk::make_cptr(new  mtk::map<std::string, msg::sub_product >);
        return result;
    }

    mtk::CountPtr<mtk::map<std::string  /*client_name*/, msg::sub_client_info> >   ref_map_client_info(void)
    {
        static mtk::CountPtr<mtk::map<std::string, msg::sub_client_info> >  result;
        if(result.isValid() == false)
            result = mtk::make_cptr(new  mtk::map<std::string, msg::sub_client_info>);
        return result;
    }

    mtk::CountPtr<mtk::map<std::string  /*user_name*/, msg::sub_user_info> >   ref_map_user_info(void)
    {
        static mtk::CountPtr<mtk::map<std::string  /*user_name*/, msg::sub_user_info> >  result;
        if(result.isValid() == false)
            result = mtk::make_cptr(new  mtk::map<std::string  /*user_name*/, msg::sub_user_info>);
        return result;
    }


    
    
    
    void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_lock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_unlock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

    void command_market_add(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_market_del(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_market_list(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

    void command_product_add(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_product_del(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_product_list(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);



    void command_client_add(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_client_del(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_client_list(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

    void command_client_filter_add(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_client_filter_del(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_client_filter_modif(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

    void command_client_find(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);



    void command_user_add(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_user_del(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

    void command_user_filter_add(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_user_filter_del(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_user_filter_modif(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

    void command_user_find(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);


    void command_load(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_save(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);


    void command_debug_get_filter(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    
    void command_check(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void timer_check(void);



    
    void register_global_commands (void)
    {
        mtk::admin::register_command("__GLOBAL__",  "stats",     "")->connect(command_stats);
        mtk::admin::register_command("sessions",  "stats",     "")->connect(command_stats);
        //mtk::admin::register_command("emr",  "lock_all",     "lock all requests", true)->connect(command_lock);
        //mtk::admin::register_command("emr",  "unlock_all",   "unlock all requests", true)->connect(command_unlock);
        
        mtk::admin::register_command("qf",  "market.add",  "<market_name>", true)->connect(command_market_add);
        mtk::admin::register_command("qf",  "market.del",  "<market_name>", true)->connect(command_market_del);
        mtk::admin::register_command("qf",  "market.list",  "")->connect(command_market_list);

        mtk::admin::register_command("qf",  "product.add",  "<product_name>  <market>  <re-pattern>")->connect(command_product_add);
        mtk::admin::register_command("qf",  "product.del",  "<product_name>", true)->connect(command_product_del);
        mtk::admin::register_command("qf",  "product.list",  "")->connect(command_product_list);



        mtk::admin::register_command("qf",  "client.add",     "<client_name>")->connect(command_client_add);
        mtk::admin::register_command("qf",  "client.del",     "<client_name>", true)->connect(command_client_del);
        mtk::admin::register_command("qf",  "client.list",     "prints the list of client")->connect(command_client_list);

        mtk::admin::register_command("qf",  "client.filter.add",     "<client_name>  <product-name> <quantity>")->connect(command_client_filter_add);
        mtk::admin::register_command("qf",  "client.filter.del",     "<client_name>  <product-name> <quantity>", true)->connect(command_client_filter_del);
        mtk::admin::register_command("qf",  "client.filter.modif",   "<client_name>  <product-name> <old_quantity>  <new_quantity>")->connect(command_client_filter_modif);
        
        mtk::admin::register_command("qf",  "client.find",    "<re-client_name>  prints full client info for given pattern")->connect(command_client_find);



        mtk::admin::register_command("qf",  "user.add",     "<user_name> <client_code>")->connect(command_user_add);
        mtk::admin::register_command("qf",  "user.del",     "<user_name> <client_code>", true)->connect(command_user_del);

        mtk::admin::register_command("qf",  "user.filter.add",     "<user_name>  <product-name> <quantity>")->connect(command_user_filter_add);
        mtk::admin::register_command("qf",  "user.filter.del",     "<user_name>  <product-name> <quantity>", true)->connect(command_user_filter_del);
        mtk::admin::register_command("qf",  "user.filter.modif",   "<user_name>  <product-name> <old_quantity>  <new_quantity>")->connect(command_user_filter_modif);
        
        mtk::admin::register_command("qf",  "user.find",    "<re-user_name>  prints full user info for given pattern")->connect(command_user_find);


        mtk::admin::register_command("qf",  "load",        "DANGEROUS delete current filters and load from db", true)->connect(command_load);
        mtk::admin::register_command("qf",  "save",        "save filters to db", true)->connect(command_save);

        mtk::admin::register_command("qf",  "debug.getfilter",        "<user_name> <cli_name> <market> <product_name>")->connect(command_debug_get_filter);

        mtk::admin::register_command("qf",  "check",        "it will look for inconsistent info configured in db", true)->connect(command_check);

    }
    
    


    
    void init(const std::string& _db_file_name)
    {   
        register_global_commands(); 
        db_file_name  =  _db_file_name;   
        load(); 
        
        MTK_TIMER_1SF(timer_check)
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
        response_lines.push_back(MTK_SS("[filters db] ________________________________ " << ref_map_user_info()->size()));
        response_lines.push_back(MTK_SS("#markets: " << ref_list_markets()->size()));
        response_lines.push_back(MTK_SS("#clients: " << ref_map_client_info()->size()));
        response_lines.push_back(MTK_SS("#users: " << ref_map_user_info()->size()));
        response_lines.push_back(MTK_SS("#products: " << ref_map_registered_products()->size()));
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



    void try_add_market(const std::string& market, mtk::list<std::string>&  response_lines)
    {
        for(mtk::list<std::string>::const_iterator it=ref_list_markets()->begin(); it!= ref_list_markets()->end(); ++it)
        {
            if(*it == market)
            {
                response_lines.push_back(MTK_SS("market " << market << " already exists"));
                return;
            }
                
        }
        ref_list_markets()->push_back(market);
        response_lines.push_back(MTK_SS("market " << market << " added"));
    }

    void command_market_add(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        response_lines.push_back(MTK_SS("before adding ... " << ref_list_markets()->size()));
        try_add_market(vparams[0], response_lines);
        response_lines.push_back(MTK_SS("after adding ... " << ref_list_markets()->size()));
    }

    void try_del_market(const std::string& market, mtk::list<std::string>&  response_lines)
    {
        for(mtk::list<std::string>::iterator it=ref_list_markets()->begin(); it!= ref_list_markets()->end(); ++it)
        {
            if(*it == market)
            {
                response_lines.push_back(MTK_SS("deleting... " << *it));
                it = ref_list_markets()->erase(it);
                if(it == ref_list_markets()->end())
                    return;
            }
        }
        return;
    }

    void command_market_del(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        response_lines.push_back(MTK_SS("before deleting ... " << ref_list_markets()->size()));
        try_del_market(vparams[0], response_lines);
        response_lines.push_back(MTK_SS("after adding ... " << ref_list_markets()->size()));
    }
    void  command_market_list(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 0, vparams)  == false)     return;
        
        YAML::Emitter yo;
        yo << *ref_list_markets();
        response_lines.push_back(yo.c_str());
    }




    void  try_add_product(const std::string&  product_name, const std::string&  market,  const  std::string&  re_pattern, mtk::list<std::string>&  response_lines)
    {
        if(ref_map_registered_products()->find(product_name) != ref_map_registered_products()->end())
        {
            response_lines.push_back(MTK_SS("already exists product with name "  << product_name));
            return;
        }
        ref_map_registered_products()->insert(std::make_pair(product_name, msg::sub_product(product_name, market, re_pattern)));
        response_lines.push_back(MTK_SS("Added product " <<  product_name));
        return;
    }

    void command_product_add(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 3, vparams)  == false)     return;

        response_lines.push_back(MTK_SS("before adding ... " <<  ref_map_registered_products()->size()));
        try_add_product(vparams[0], vparams[1], vparams[2], response_lines);
        response_lines.push_back(MTK_SS("after adding ... " <<  ref_map_registered_products()->size()));
    }

    void command_product_del(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        {
            const std::string  product_name = vparams[0];
            response_lines.push_back(MTK_SS("before deleting ... " <<  ref_map_registered_products()->size()));
            if(ref_map_registered_products()->find(product_name) == ref_map_registered_products()->end())
                response_lines.push_back(MTK_SS("name not found  " << product_name));
            else
                ref_map_registered_products()->erase(ref_map_registered_products()->find(product_name));
            response_lines.push_back(MTK_SS("after deleting ... " <<  ref_map_registered_products()->size()));
        }
    }

    void command_product_list(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 0, vparams)  == false)     return;

        YAML::Emitter yo;
        yo << YAML::BeginSeq;
            for(auto it=ref_map_registered_products()->begin(); it != ref_map_registered_products()->end(); ++it)
                yo << it->second;
        yo << YAML::EndSeq;
        response_lines.push_back(yo.c_str());
    }




    void command_client_add(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        {
            std::string  client_name = vparams[0];
            if(check_client_code(client_name) == false)
            {
                response_lines.push_back("Error, client name not valid");
                return;
            }
            if(ref_map_client_info()->find(client_name)  !=  ref_map_client_info()->end())
            {
                response_lines.push_back("Error, client name already exists");
                return;
            }
            response_lines.push_back(MTK_SS("before adding... " << ref_map_client_info()->size()));
            ref_map_client_info()->insert(std::make_pair(client_name, msg::sub_client_info(client_name, mtk::dtNowLocal(), mtk::list<msg::sub_filter_info>())));
            response_lines.push_back(MTK_SS("after adding... " << ref_map_client_info()->size()));
        }
    }
    
    void command_client_del(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        {
            std::string  client_name = vparams[0];
            if(check_client_code(client_name) == false)
            {
                response_lines.push_back("Error, client name not valid");
                return;
            }
            if(ref_map_client_info()->find(client_name)  ==  ref_map_client_info()->end())
            {
                response_lines.push_back("Error, client name doesn't exist");
                return;
            }
            response_lines.push_back(MTK_SS("before deleting... " << ref_map_client_info()->size()));
            ref_map_client_info()->erase(ref_map_client_info()->find(client_name));
            response_lines.push_back(MTK_SS("after deleting... " << ref_map_client_info()->size()));
        }
    }
    
    void command_client_list(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 0, vparams)  == false)     return;
        
        YAML::Emitter yo;
        yo << YAML::BeginSeq;
        for(auto it= ref_map_client_info()->begin(); it != ref_map_client_info()->end(); ++it)
            yo << it->second;
        yo << YAML::EndSeq;
        response_lines.push_back(yo.c_str());
    }
    

    void command_client_filter_add(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 3, vparams)  == false)     return;
        
        {
            std::string  client_name        = vparams[0];
            std::string  gen_product_name   = vparams[1];
            int          quantity           = mtk::s_TRY_stoi(vparams[2], 0)._0;
            
            if(ref_map_client_info()->find(client_name)  ==  ref_map_client_info()->end())
            {
                response_lines.push_back("Error, client name doesn't exist");
                return;
            }
            else
            {
                msg::sub_client_info&  client_info = ref_map_client_info()->find(client_name)->second;
                // check if exists previus filter
                for(auto it=client_info.filter_list.begin(); it!=client_info.filter_list.end(); ++it)
                {
                    if(it->gen_product_name == gen_product_name)
                    {
                        response_lines.push_back(MTK_SS("Error, already exists a filter for this client and product"  <<  *it));
                        return;
                    }
                }
                response_lines.push_back(MTK_SS("Before inserting filter... "  <<  client_info.filter_list.size()));
                client_info.filter_list.push_back(msg::sub_filter_info(gen_product_name, quantity));
                response_lines.push_back(MTK_SS("After inserting filter... "  <<  client_info.filter_list.size()));
            }
        }
    }
    
    void command_client_filter_del(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 3, vparams)  == false)     return;
        
        {
            std::string  client_name        = vparams[0];
            std::string  gen_product_name   = vparams[1];
            int          quantity           = mtk::s_TRY_stoi(vparams[2], 0)._0;
            
            if(ref_map_client_info()->find(client_name)  ==  ref_map_client_info()->end())
            {
                response_lines.push_back("Error, client name doesn't exist");
                return;
            }
            else
            {
                msg::sub_client_info&  client_info = ref_map_client_info()->find(client_name)->second;
                // check if exists previus filter
                int count_located = 0;
                response_lines.push_back(MTK_SS("Before deleting filter... "  <<  client_info.filter_list.size()));
                auto it=client_info.filter_list.begin();
                while(it!=client_info.filter_list.end())
                {
                    if(it->gen_product_name == gen_product_name)
                    {
                        ++count_located;
                        if(it->quantity == quantity)
                            it = client_info.filter_list.erase(it);
                        else
                        {
                            response_lines.push_back("quantity doesn't match");
                            ++it;
                        }
                    }
                    else    
                        ++it;
                }
                if(count_located > 1)
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qf.db", "More than one filter for a product", mtk::alPriorError, mtk::alTypeNoPermisions));
                if(count_located == 0)
                {
                    response_lines.push_back(MTK_SS("Error, doesn't exist filter for this client and product"  <<  client_name << " , " << gen_product_name));
                    return;
                }
                response_lines.push_back(MTK_SS("After deleting filter... "  <<  client_info.filter_list.size()));
            }
        }
    }
    
    void command_client_filter_modif(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 4, vparams)  == false)     return;
        
        {
            std::string  client_name        = vparams[0];
            std::string  gen_product_name   = vparams[1];
            int          old_quantity       = mtk::s_TRY_stoi(vparams[2], 0)._0;
            int          new_quantity       = mtk::s_TRY_stoi(vparams[3], 0)._0;
            
            if(ref_map_client_info()->find(client_name)  ==  ref_map_client_info()->end())
            {
                response_lines.push_back("Error, client name doesn't exist");
                return;
            }
            else
            {
                msg::sub_client_info&  client_info = ref_map_client_info()->find(client_name)->second;
                // check if exists previus filter
                int count_located = 0;
                response_lines.push_back(MTK_SS("Before modifing filter... "  <<  client_info.filter_list.size()));
                auto it=client_info.filter_list.begin();
                while(it!=client_info.filter_list.end())
                {
                    if(it->gen_product_name == gen_product_name)
                    {
                        ++count_located;
                        if(it->quantity == old_quantity)
                            it->quantity = new_quantity;
                        else
                            response_lines.push_back(MTK_SS("old quantity doesn't match with current quantity "));
                    }
                    ++it;
                }
                if(count_located > 1)
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qf.db", "More than one filter for a product", mtk::alPriorError, mtk::alTypeNoPermisions));
                if(count_located == 0)
                {
                    response_lines.push_back(MTK_SS("Error, doesn't exist filter for this client and product"  <<  client_name << " , " << gen_product_name));
                    return;
                }
                response_lines.push_back(MTK_SS("After modifing filter... "  <<  client_info.filter_list.size()));
            }
        }
    }
    

    void command_client_find(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        {
            YAML::Emitter yo;
            yo << YAML::BeginSeq;
            
            mtk::RegExp  re (vparams[0]);

            for(auto  it = ref_map_client_info()->begin(); it != ref_map_client_info()->end(); ++it)
            {
                if(re.Match(it->first))
                {
                    yo << it->second;
                }
            }
            yo << YAML::EndSeq;
            response_lines.push_back(yo.c_str());
        }
    }
    




    void command_user_add(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 2, vparams)  == false)     return;

        {
            std::string  user_name   = vparams[0];
            std::string  client_name = vparams[1];
            if(check_user_name(user_name) == false)
            {
                response_lines.push_back("Error, user name not valid");
                return;
            }
            if(check_client_code(client_name) == false)
            {
                response_lines.push_back("Error, client name not valid");
                return;
            }
            if(ref_map_user_info()->find(user_name)  !=  ref_map_user_info()->end())
            {
                response_lines.push_back("Error, user, client already exists");
                return;
            }
            response_lines.push_back(MTK_SS("before adding... " << ref_map_user_info()->size()));
            ref_map_user_info()->insert(std::make_pair(user_name, msg::sub_user_info(user_name, mtk::dtNowLocal(), client_name, mtk::list<msg::sub_filter_info>())));
            response_lines.push_back(MTK_SS("after adding... " << ref_map_user_info()->size()));
        }
    }
    
    void command_user_del(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 2, vparams)  == false)     return;

        {
            std::string  user_name   = vparams[0];
            std::string  client_name = vparams[1];
            if(check_client_code(client_name) == false)
            {
                response_lines.push_back("Error, client name not valid");
                return;
            }
            if(ref_map_user_info()->find(user_name)  ==  ref_map_user_info()->end())
            {
                response_lines.push_back("Error, client name doesn't exist");
                return;
            }
            if(ref_map_user_info()->find(user_name)->second.client_code  !=  client_name)
            {
                response_lines.push_back("error client code doesn't match");
                return;
            }
            response_lines.push_back(MTK_SS("before deleting... " << ref_map_user_info()->size()));
            ref_map_user_info()->erase(ref_map_user_info()->find(user_name));
            response_lines.push_back(MTK_SS("after deleting... " << ref_map_user_info()->size()));
        }
    }
    
    

    void command_user_filter_add(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 3, vparams)  == false)     return;
        
        {
            std::string  user_name          = vparams[0];
            std::string  gen_product_name   = vparams[1];
            int          quantity           = mtk::s_TRY_stoi(vparams[2], 0)._0;
            
            if(ref_map_user_info()->find(user_name)  ==  ref_map_user_info()->end())
            {
                response_lines.push_back("Error, user name doesn't exist");
                return;
            }
            else
            {
                msg::sub_user_info&  user_info = ref_map_user_info()->find(user_name)->second;
                // check if exists previus filter
                for(auto it=user_info.filter_list.begin(); it!=user_info.filter_list.end(); ++it)
                {
                    if(it->gen_product_name == gen_product_name)
                    {
                        response_lines.push_back(MTK_SS("Error, already exists a filter for this user and product"  <<  *it));
                        return;
                    }
                }
                response_lines.push_back(MTK_SS("Before inserting filter... "  <<  user_info.filter_list.size()));
                user_info.filter_list.push_back(msg::sub_filter_info(gen_product_name, quantity));
                response_lines.push_back(MTK_SS("After inserting filter... "  <<  user_info.filter_list.size()));
            }
        }
    }
    
    void command_user_filter_del(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 3, vparams)  == false)     return;
        
        {
            std::string  user_name          = vparams[0];
            std::string  gen_product_name   = vparams[1];
            int          quantity           = mtk::s_TRY_stoi(vparams[2], 0)._0;
            
            if(ref_map_user_info()->find(user_name)  ==  ref_map_user_info()->end())
            {
                response_lines.push_back("Error, user name doesn't exist");
                return;
            }
            else
            {
                msg::sub_user_info&  user_info = ref_map_user_info()->find(user_name)->second;
                // check if exists previus filter
                int count_located = 0;
                response_lines.push_back(MTK_SS("Before deleting filter... "  <<  user_info.filter_list.size()));
                auto it=user_info.filter_list.begin();
                while(it!=user_info.filter_list.end())
                {
                    if(it->gen_product_name == gen_product_name)
                    {
                        ++count_located;
                        if(it->quantity == quantity)
                            it = user_info.filter_list.erase(it);
                        else
                        {
                            response_lines.push_back("quantity doesn't match");
                            ++it;
                        }
                    }
                    else    
                        ++it;
                }
                if(count_located > 1)
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qf.db", "More than one filter for a product", mtk::alPriorError, mtk::alTypeNoPermisions));
                if(count_located == 0)
                {
                    response_lines.push_back(MTK_SS("Error, doesn't exist filter for this user and product"  <<  user_name << " , " << gen_product_name));
                    return;
                }
                response_lines.push_back(MTK_SS("After deleting filter... "  <<  user_info.filter_list.size()));
            }
        }
    }
    
    void command_user_filter_modif(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 4, vparams)  == false)     return;
        
        {
            std::string  user_name          = vparams[0];
            std::string  gen_product_name   = vparams[1];
            int          old_quantity       = mtk::s_TRY_stoi(vparams[2], 0)._0;
            int          new_quantity       = mtk::s_TRY_stoi(vparams[3], 0)._0;
            
            if(ref_map_user_info()->find(user_name)  ==  ref_map_user_info()->end())
            {
                response_lines.push_back("Error, user name doesn't exist");
                return;
            }
            else
            {
                msg::sub_user_info&  user_info = ref_map_user_info()->find(user_name)->second;
                // check if exists previus filter
                int count_located = 0;
                response_lines.push_back(MTK_SS("Before modifing filter... "  <<  user_info.filter_list.size()));
                auto it=user_info.filter_list.begin();
                while(it!=user_info.filter_list.end())
                {
                    if(it->gen_product_name == gen_product_name)
                    {
                        ++count_located;
                        if(it->quantity == old_quantity)
                            it->quantity = new_quantity;
                        else
                            response_lines.push_back(MTK_SS("old quantity doesn't match with current quantity "));
                    }
                    ++it;
                }
                if(count_located > 1)
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qf.db", "More than one filter for a product", mtk::alPriorError, mtk::alTypeNoPermisions));
                if(count_located == 0)
                {
                    response_lines.push_back(MTK_SS("Error, doesn't exist filter for this user and product"  <<  user_name << " , " << gen_product_name));
                    return;
                }
                response_lines.push_back(MTK_SS("After modifing filter... "  <<  user_info.filter_list.size()));
            }
        }
    }
    

    void command_user_find(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 1, vparams)  == false)     return;

        {
            YAML::Emitter yo;
            yo << YAML::BeginSeq;
            
            mtk::RegExp  re (vparams[0]);

            for(auto  it = ref_map_user_info()->begin(); it != ref_map_user_info()->end(); ++it)
            {
                if(re.Match(it->first))
                {
                    yo << it->second;
                }
            }
            yo << YAML::EndSeq;
            response_lines.push_back(yo.c_str());
        }
    }


    void save(void)
    {
        std::ofstream file;
        file.open (db_file_name.c_str());


        try
        {
            YAML::Emitter out;
            out  <<  YAML::BeginMap;

            out  << YAML::Key << "version"   <<  YAML::Value << 1;

            out  << YAML::Key << "markets"   <<  YAML::Value  <<  *ref_list_markets();

            out  << YAML::Key << "products" <<  YAML::Value  <<  *ref_map_registered_products();

            out  << YAML::Key << "clients" <<  YAML::Value  <<  *ref_map_client_info();

            out  << YAML::Key << "user_info"  <<  YAML::Value  <<  *ref_map_user_info();

            out <<  YAML::EndMap;

            file << out.c_str();
            file.close();
        }
        MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "accmgr_db", "error saving db")
    }
    void load(void)
    {
        ref_list_markets()->clear();
        ref_map_registered_products()->clear();
        ref_map_client_info()->clear();
        ref_map_user_info()->clear();
        
        std::ifstream file(db_file_name.c_str());

        try
        {
            YAML::Parser parser(file);

            YAML::Node doc;
            parser.GetNextDocument(doc);
            std::string config_version;
            
            doc["markets"] >> *ref_list_markets();
            doc["products"] >> *ref_map_registered_products();
            doc["clients"] >> *ref_map_client_info();
            doc["user_info"] >> *ref_map_user_info();
            file.close();
        }
        MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "accmgr_db", "error loading db")
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
    


    mtk::tuple<int, int>    get_user_filters____tpl_cli_user(const std::string&  cli_name, const std::string&  user_name, const std::string& market, const std::string&  product)
    {
        int filter_client = 0;
        int filter_user   = 0;

        {
            auto  itclient  = ref_map_client_info()->find(cli_name);
            if(itclient  ==  ref_map_client_info()->end())
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qf.db", MTK_SS("error, client name not found trying to filter" <<  cli_name), mtk::alPriorError, mtk::alTypeNoPermisions ));
            else
            {
                bool located = false;
                
                std::string  gen_product_name;
                for(auto it_clifilter = itclient->second.filter_list.begin(); it_clifilter != itclient->second.filter_list.end(); ++it_clifilter)
                {
                    auto  it_product_info = ref_map_registered_products()->find(it_clifilter->gen_product_name);
                    if(it_product_info != ref_map_registered_products()->end())
                    {
                        mtk::RegExp re_product (it_product_info->second.re_product_code);
                        if(re_product.Match(product)  &&  it_product_info->second.market == market)
                        {
                            located = true;
                            filter_client = it_clifilter->quantity;
                            break;
                        }
                    }
                }
                if(located == false)
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qf.db", 
                                    MTK_SS("error, requested filter on not located product for client " 
                                            <<  mtk::make_tuple(cli_name, product)), mtk::alPriorError, mtk::alTypeNoPermisions ));
            }
        }
        
        {
            auto  ituser  = ref_map_user_info()->find(user_name);
            if(ituser  ==  ref_map_user_info()->end())
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qf.db", MTK_SS("error, user name not found trying to filter" <<  user_name), mtk::alPriorError, mtk::alTypeNoPermisions ));
            else
            {
                bool located = false;
                
                std::string  gen_product_name;
                for(auto it_usrfilter = ituser->second.filter_list.begin(); it_usrfilter != ituser->second.filter_list.end(); ++it_usrfilter)
                {
                    auto  it_product_info = ref_map_registered_products()->find(it_usrfilter->gen_product_name);
                    if(it_product_info != ref_map_registered_products()->end())
                    {
                        mtk::RegExp re_product (it_product_info->second.re_product_code);
                        if(re_product.Match(product)  &&  it_product_info->second.market == market)
                        {
                            located = true;
                            filter_user = it_usrfilter->quantity;
                            break;
                        }
                    }
                }
                if(located == false)
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qf.db", 
                                    MTK_SS("error, requested filter on not located product for user " 
                                            <<  mtk::make_tuple(user_name, product)), mtk::alPriorError, mtk::alTypeNoPermisions ));
            }
        }
        return mtk::make_tuple(filter_client, filter_user);
    }


    void command_debug_get_filter(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params__converting2upper(params, response_lines, 4, vparams)  == false)     return;
        
        {
            std::string  cli_name  = vparams[0];
            std::string  user_name = vparams[1];
            std::string  market    = vparams[2];
            std::string  product   = vparams[3];
            
            auto filters = get_user_filters____tpl_cli_user(cli_name, user_name, market, product);
            
            response_lines.push_back(MTK_SS(filters));
        }
    }




    std::string  look_mising_in_second_set(const std::set<std::string>& first, const std::set<std::string>& second)
    {
        std::string  result;
        for(auto it=first.begin(); it!=first.end(); ++it)
        {
            if(second.find(*it) == second.end())
                result += *it + " ";
        }
        return result;
    }

    std::string                 check(void)
    {
        std::string result;
        
        mtk::list<std::string>                                        list_markets    =   *ref_list_markets();
        mtk::map<std::string, msg::sub_product >                      map_products    =   *ref_map_registered_products();
        mtk::map<std::string  /*client_name*/, msg::sub_client_info>  map_client_info =   *ref_map_client_info();
        mtk::map<std::string  /*user_name*/, msg::sub_user_info>      map_user_info   =   *ref_map_user_info();
        
        
        std::set<std::string>       markets_set;
        std::set<std::string>       markets_in_products_set;
        std::set<std::string>       product_names_set;
        std::set<std::string>       product_names_in_clients_set;
        std::set<std::string>       product_names_in_users_set;
        std::set<std::string>       clients_set;
        std::set<std::string>       clients_in_users_set;
        
        
        for(auto it=list_markets.begin(); it!=list_markets.end(); ++it)         
            markets_set.insert(*it);
        for(auto it=map_products.begin(); it!=map_products.end(); ++it)         
            markets_in_products_set.insert(it->second.market);
        for(auto it=map_products.begin(); it!=map_products.end(); ++it)
            product_names_set.insert(it->second.gen_product_name);
        for(auto it=map_client_info.begin(); it!=map_client_info.end(); ++it)
            for(auto it2=it->second.filter_list.begin(); it2!=it->second.filter_list.end(); ++it2)
                product_names_in_clients_set.insert(it2->gen_product_name);
        for(auto it=map_user_info.begin(); it!=map_user_info.end(); ++it)
            for(auto it2=it->second.filter_list.begin(); it2!=it->second.filter_list.end(); ++it2)
                product_names_in_users_set.insert(it2->gen_product_name);
        for(auto it=map_client_info.begin(); it!=map_client_info.end(); ++it)
            clients_set.insert(it->second.name);
        for(auto it=map_user_info.begin(); it!=map_user_info.end(); ++it)
            clients_in_users_set.insert(it->second.client_code);
            
        std::string missings;
        
        missings = look_mising_in_second_set(markets_set, markets_in_products_set);
        if(missings != "")          result += MTK_SS("markets not configured in products  "  <<  missings << std::endl);

        missings = look_mising_in_second_set(markets_in_products_set, markets_set);
        if(missings != "")          result += MTK_SS("markets not registered but configured in products  "  <<  missings << std::endl);

        missings = look_mising_in_second_set(product_names_set, product_names_in_clients_set);
        if(missings != "")          result += MTK_SS("products registered not configured in any client  "  <<  missings << std::endl);

        missings = look_mising_in_second_set(product_names_in_clients_set, product_names_set);
        if(missings != "")          result += MTK_SS("products configured on client but not registered  "  <<  missings << std::endl);

        missings = look_mising_in_second_set(product_names_set, product_names_in_users_set);
        if(missings != "")          result += MTK_SS("products registered not configured in any user  "  <<  missings << std::endl);

        missings = look_mising_in_second_set(product_names_in_users_set, product_names_set);
        if(missings != "")          result += MTK_SS("products configured on users but not registered  "  <<  missings << std::endl);
        
        missings = look_mising_in_second_set(clients_in_users_set, clients_set);
        if(missings != "")          result += MTK_SS("client configured on users but not registered  "  <<  missings << std::endl);

        missings = look_mising_in_second_set(clients_set, clients_in_users_set);
        if(missings != "")          result += MTK_SS("client registered not configured in any user  "  <<  missings << std::endl);


        for(auto it=map_client_info.begin(); it!=map_client_info.end(); ++it)
            if(it->second.filter_list.size() == 0)
                result += MTK_SS("client " << it->second.name  << "has no filters configured");
        for(auto it=map_user_info.begin(); it!=map_user_info.end(); ++it)
            if(it->second.filter_list.size() == 0)
                result += MTK_SS("client " << it->second.name  << "has no filters configured");
        
        
        
        return result;
    }

    void command_check(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        std::string  result_check = check();
        
        if(result_check == "")
            response_lines.push_back("db looks ok");
        else
            response_lines.push_back(result_check);
    }

    void timer_check(void)
    {
        if((mtk::dtToday_0Time() + mtk::dtHours(18)) + mtk::dtMinutes(30)  <  mtk::dtNowLocal())
        {
            MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(25))
                std::string  result_check = check();
                if(result_check != "")
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qf.db", result_check, mtk::alPriorError, mtk::alTypeNoPermisions));
            MTK_END_EXEC_MAX_FREC
        }
    }









    

   
};  //  namespace db {
};  //  namespace accmgr { 
