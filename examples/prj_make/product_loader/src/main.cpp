#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"
#include "components/prices/msg_prices.h"



namespace
{
    
    const char*   APP_NAME          = "GEN_PRODUCT_LOADER";
    const char*   APP_VER           = "2011-04-12";
    const char*   APP_DESCRIPTION   = "I will keep prices and other product information on memory and I will serve it to clients or other proceses\n"
                                      "I will receive this information listening as a client";
                                      
    const char*   APP_MODIFICATIONS = "           2011-04-12     first version\n";


}


    //  COMMANDS
    void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_lock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_unlock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_status(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    
    void register_global_commands (void)
    {
        mtk::admin::register_command("__GLOBAL__"  ,   "stats",     "")->connect(command_stats);
        mtk::admin::register_command("product_loader", "stats",     "")->connect(command_stats);
        mtk::admin::register_command("product_loader", "lock",      "I will ignore all request (no response)", true)->connect(command_lock);
        mtk::admin::register_command("product_loader", "unlock",    "I will response again", true)->connect(command_unlock);
        mtk::admin::register_command("__GLOBAL__",     "status",    "Info about my current status")->connect(command_status);
        mtk::admin::register_command("product_loader", "status",    "Info about my current status")->connect(command_status);
    }
    
    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)    


    //  status
    bool lock_request_status=false;

    //  market info
    class market_info
    {
        public:
            market_info(const std::string& _name, const mtk::dtTimeQuantity& tq)
                :  name(_name), check_interval(tq), last_update_received(mtk::dtNowLocal())  {}
                
            std::string             name;
            mtk::dtTimeQuantity     check_interval;
            mtk::DateTime           last_update_received;
    };
    mtk::map<std::string, market_info >    map_market_info;
    


    //      stats
    int  stats_req_rec=0;
    int  stats_req_unknown=0;
    int  stats_prec_update=0;






    //  PRICES MAP
    mtk::CountPtr<mtk::map<mtk::msg::sub_product_code, mtk::prices::msg::pub_best_prices> >   map_products;


    //  requests
    void on_request_load_prices(const mtk::prices::msg::req_prod_info& req)
    {
        if(lock_request_status)
        {
            MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(5))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "product_loader", "Ignoring request, process on lock status", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            return;
        }
        ++stats_req_rec;
        static mtk::CountPtr<mtk::qpid_session>  response_session(mtk::admin::get_qpid_session("client", "CLITESTING"));

        mtk::map<mtk::msg::sub_product_code, mtk::prices::msg::pub_best_prices>::iterator it = map_products->find(req.product_code);
        if(it == map_products->end())
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "product_loader", MTK_SS("unknown product code " << req.product_code), mtk::alPriorError, mtk::alTypeNoPermisions));
            ++stats_req_unknown;
        }
        else
        {
            mtk::list<mtk::prices::msg::res_product_info::IC_response>  response_list;
            mtk::prices::msg::res_product_info::IC_response response(it->second);
            response_list.push_back(response);
            MTK_SEND_MULTI_RESPONSE(        mtk::prices::msg::res_product_info, 
                                            mtk::prices::msg::res_product_info::IC_response, 
                                            response_session,
                                            req.request_info,
                                            response_list)
        }
        
    }
    



void on_price_update (const mtk::prices::msg::pub_best_prices& msg_update_price)
{
    ++stats_prec_update;
    mtk::map<mtk::msg::sub_product_code, mtk::prices::msg::pub_best_prices>::iterator it = map_products->find(msg_update_price.product_code);
    if(it == map_products->end())
        map_products->insert(std::make_pair(msg_update_price.product_code, msg_update_price));
    else
        it->second = msg_update_price;
    mtk::admin::check_control_fluct(msg_update_price.orig_control_fluct);
    
    //  update last received message for this market
    mtk::map<std::string, market_info >::iterator  itlu = map_market_info.find(msg_update_price.product_code.market);
    if(itlu==map_market_info.end())
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "product_loader", MTK_SS("unknown market code " << msg_update_price.product_code), mtk::alPriorError, mtk::alTypeNoPermisions));
    else
        itlu->second.last_update_received  = mtk::dtNowLocal();
}


    //  check inactivity
    void check_inactivity(void)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(20))
            //mtk::map<mtk::msg::sub_product_code>, mtk::DateTime >    map_last_update;
            mtk::map<std::string, market_info >::iterator  it = map_market_info.begin();
            for( ; it!= map_market_info.end(); ++it)
            {
                if(it->second.check_interval > mtk::dtSeconds(1))
                {
                    if(it->second.last_update_received + it->second.check_interval < mtk::dtNowLocal())
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "produc_server", MTK_SS("too many time with no activity " << it->first), mtk::alPriorError, mtk::alTypeOverflow));
                }
            }
            
        MTK_END_EXEC_MAX_FREC
    }






    void init_map_market_info()
    {
        mtk::list<std::string>  nodes = mtk::admin::get_config_nodes("MARKETS");
        for(mtk::list<std::string>::iterator it = nodes.begin(); it!= nodes.end(); ++it)
        {
            mtk::dtTimeQuantity tq = mtk::dtSeconds(20);
            bool ok = false;
            mtk::s_TRY_stotq (mtk::admin::get_config_property(MTK_SS("MARKETS." << *it <<".check_activity")).Get(), mtk::dtSeconds(20)).assign(tq, ok);
            if(ok==false)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "produc_server", MTK_SS("error reading configuration for market " << *it), mtk::alPriorError));
            map_market_info.insert(std::make_pair(*it, market_info(*it, tq)));
        }
    }


//      M A I N


int main(int argc, char ** argv)
{
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        
        
        //  init map_market_info
        init_map_market_info();
        
        //  last update info
        map_products = mtk::make_cptr(new mtk::map<mtk::msg::sub_product_code, mtk::prices::msg::pub_best_prices>);
        
        
        //  suscriptions to changes and request
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::pub_best_prices> >  hqpid_update_best_prices;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_update_best_prices,
                                mtk::admin::get_url("client"),
                                "CLITESTING",
                                mtk::prices::msg::pub_best_prices::get_in_subject("MARKET", "*"),
                                mtk::prices::msg::pub_best_prices,
                                on_price_update)

        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::req_prod_info> >  hqpid_request_product_info;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_request_product_info,
                                mtk::admin::get_url("client"),
                                "CLITESTING",
                                mtk::prices::msg::req_prod_info::get_in_subject("*"),
                                mtk::prices::msg::req_prod_info,
                                on_request_load_prices)


        MTK_TIMER_1SF(check_inactivity)

        mtk::start_timer_wait_till_end();
        

        map_products = mtk::CountPtr<mtk::map<mtk::msg::sub_product_code, mtk::prices::msg::pub_best_prices> > ();
        std::cout << "FIN..... " << std::endl;
        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION (std::cout<< , "main", "nothing more")

    std::cout << "MAL..... " << std::endl;
    #include "support/release_on_exit.hpp"
    return -1;

}



void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(MTK_SS("#products: " << map_products->size()));
    response_lines.push_back(MTK_SS("#rq_rec  : " << stats_req_rec));
    response_lines.push_back(MTK_SS("#prec_upd: " << stats_prec_update));
    response_lines.push_back(MTK_SS("#req_unkn: " << stats_req_unknown));
}

void command_lock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    if(lock_request_status==false)
    {
        lock_request_status = true;
        response_lines.push_back(MTK_SS("Ignoring all request"));
    }
    else
        response_lines.push_back(MTK_SS("ignoring command, it was already locked"));
}

void command_unlock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    if(lock_request_status)
    {
        lock_request_status = false;
        response_lines.push_back(MTK_SS("Accepting requests"));
    }
    else
        response_lines.push_back(MTK_SS("ignoring command, it was already unlocked"));
}

void command_status(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(MTK_SS("lock status: " << int(lock_request_status)));
}
