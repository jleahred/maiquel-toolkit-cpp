#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"
#include "components/prices/msg_prices.h"
#include "components/prices/msg_ps_prices.h"
#include "components/prices/prices_support.h"



namespace
{

    const char*   APP_NAME          = "GEN_PRODUCT_LOADER";
    const char*   APP_VER           = "2011-04-12";
    const char*   APP_DESCRIPTION   = "I will keep prices and other product information on memory and I will serve it to clients or other proceses\n"
                                      "I will receive this information listening as a client";

    const char*   APP_MODIFICATIONS =   "           2011-04-12     first version\n"
                                        "           2011-08-01     filling product publishing protocol (update)\n"
                                        "           2012-01-13     delete on init from publisher and modifs on check activity\n"
                                        ;

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
            market_info(const std::string& _name, const mtk::dtTimeQuantity& tq, const mtk::dtDateTime&  _starts, const mtk::dtDateTime&  _ends)
                :  name(_name), check_interval(tq), last_update_received(mtk::dtNowLocal()) , starts(_starts), ends(_ends) {}

            std::string             name;
            mtk::dtTimeQuantity     check_interval;
            mtk::DateTime           last_update_received;
            mtk::DateTime           starts;
            mtk::DateTime           ends;
    };
    mtk::map<std::string, market_info >    map_market_info;



    //      stats
    int  stats_req_rec=0;
    int  stats_req_unknown=0;
    int  stats_prec_update=0;
    int  stats_prod_init=0;






    //  PRICES MAP
    mtk::CountPtr<mtk::map<mtk::msg::sub_product_code, mtk::prices::msg::sub_full_product_info_optionals> >   map_products;



void on_request_load_prices(const mtk::prices::msg::ps_req_product_info& req);
void on_price_update (const mtk::prices::msg::pub_best_prices& msg_update_price);
void check_inactivity(void);
void init_map_market_info(void);


void send_req_init_prod_info_to_markets__to_publisher(void);
void suscribe_publisher_updates(void);
void suscribe_cli_request_product(void);
void suscribe_publisher_ready__from_publisher(void);
void suscribe_publisher_conf_full_prod_info_init__from_publisher(void);
void suscribe_publisher_conf_full_prod_info__from_publisher(void);



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
        map_products = mtk::make_cptr(new mtk::map<mtk::msg::sub_product_code, mtk::prices::msg::sub_full_product_info_optionals>);

        suscribe_publisher_updates();
        suscribe_cli_request_product();
        suscribe_publisher_ready__from_publisher();
        suscribe_publisher_conf_full_prod_info_init__from_publisher();
        suscribe_publisher_conf_full_prod_info__from_publisher();
        send_req_init_prod_info_to_markets__to_publisher();


        MTK_TIMER_1CF(check_inactivity)

        mtk::start_timer_wait_till_end();


        map_products = mtk::CountPtr<mtk::map<mtk::msg::sub_product_code, mtk::prices::msg::sub_full_product_info_optionals> > ();
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
    response_lines.push_back(MTK_SS("#products : " << map_products->size()));
    response_lines.push_back(MTK_SS("#rq_rec   : " << stats_req_rec));
    response_lines.push_back(MTK_SS("#prec_upd : " << stats_prec_update));
    response_lines.push_back(MTK_SS("#req_unkn : " << stats_req_unknown));
    response_lines.push_back(MTK_SS("#prod_init: " << stats_prod_init));
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


void send_req_init_prod_info_to_markets__to_publisher(void)
{
    for(auto it=map_market_info.begin(); it!=map_market_info.end(); ++it)
    {
        mtk::prices::msg::ps_req_init_prod_info__to_publisher
                ps_req_init_prod_info__to_publisher(mtk::prices::msg::ps_req_init_prod_info(it->first, mtk::admin::get_process_info()));
        mtk_send_message("server", ps_req_init_prod_info__to_publisher);
    }
}

void suscribe_publisher_updates(void)
{
    typedef  mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::pub_best_prices> >      type_cptrhandle;
    static mtk::list< type_cptrhandle >  hqpid_update_best_prices_list_by_market;
    for(auto it=map_market_info.begin(); it!=map_market_info.end(); ++it)
    {
        hqpid_update_best_prices_list_by_market.push_back(type_cptrhandle());
        MTK_QPID_RECEIVER_CONNECT_F__WITH_ADDRESS(
                                hqpid_update_best_prices_list_by_market.back(),
                                mtk::admin::get_url("client"),
                                mtk::prices::msg::pub_best_prices::static_get_qpid_address(it->first),
                                mtk::prices::msg::pub_best_prices::get_in_subject(it->first, "*"),
                                mtk::prices::msg::pub_best_prices,
                                on_price_update)
    }
}
void suscribe_cli_request_product(void)
{
    typedef  mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ps_req_product_info> >    type_cptrhandle;
    static mtk::list< type_cptrhandle >  hqpid_ps_request_product_infolist_by_market;
    for(auto it=map_market_info.begin(); it!=map_market_info.end(); ++it)
    {
        hqpid_ps_request_product_infolist_by_market.push_back(type_cptrhandle());
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_ps_request_product_infolist_by_market.back(),
                                mtk::admin::get_url("server"),
                                mtk::prices::msg::ps_req_product_info::get_in_subject(it->first, "pigrant"),
                                mtk::prices::msg::ps_req_product_info,
                                on_request_load_prices)
    }
}

void on_ps_pub_prod_info_mtk_ready__from_publisher(const mtk::prices::msg::ps_pub_prod_info_mtk_ready__from_publisher&    ps_pub_prod_info_mtk_ready__from_publisher)
{
    map_products->clear();
    mtk::prices::msg::ps_req_init_prod_info__to_publisher    ps_req_init_prod_info__to_publisher(
            mtk::prices::msg::ps_req_init_prod_info(ps_pub_prod_info_mtk_ready__from_publisher.market, mtk::admin::get_process_info()));
    mtk_send_message("server", ps_req_init_prod_info__to_publisher);
}
void suscribe_publisher_ready__from_publisher(void)
{
    typedef  mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ps_pub_prod_info_mtk_ready__from_publisher> >      type_cptrhandle;
    static mtk::list< type_cptrhandle >  hqpid_ps_pub_prod_info_mtk_ready_by_market;
    for(auto it=map_market_info.begin(); it!=map_market_info.end(); ++it)
    {
        hqpid_ps_pub_prod_info_mtk_ready_by_market.push_back(type_cptrhandle());

        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_ps_pub_prod_info_mtk_ready_by_market.back(),
                                mtk::admin::get_url("server"),
                                mtk::prices::msg::ps_pub_prod_info_mtk_ready__from_publisher::get_in_subject(it->first),
                                mtk::prices::msg::ps_pub_prod_info_mtk_ready__from_publisher,
                                on_ps_pub_prod_info_mtk_ready__from_publisher)
    }
}


void on_ps_conf_full_product_info_init__from_publisher(const mtk::prices::msg::ps_conf_full_product_info_init__from_publisher&  pi_init)
{
    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "prod_loader", MTK_SS("Received conf_full_product_info_init " << pi_init), mtk::alPriorDebug, mtk::alTypeUnknown));
}
void suscribe_publisher_conf_full_prod_info_init__from_publisher(void)
{
    typedef  mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ps_conf_full_product_info_init__from_publisher> >      type_cptrhandle;
    static mtk::list< type_cptrhandle >  hqpid_ps_conf_full_product_info_init_by_market;
    for(auto it=map_market_info.begin(); it!=map_market_info.end(); ++it)
    {
        mtk::msg::sub_process_info  process_info = mtk::admin::get_process_info();
        hqpid_ps_conf_full_product_info_init_by_market.push_back(type_cptrhandle());
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_ps_conf_full_product_info_init_by_market.back(),
                                mtk::admin::get_url("server"),
                                mtk::prices::msg::ps_conf_full_product_info_init__from_publisher::get_in_subject(it->first, process_info.process_name, process_info.process_uuid),
                                mtk::prices::msg::ps_conf_full_product_info_init__from_publisher,
                                on_ps_conf_full_product_info_init__from_publisher)
    }
}





void on_ps_conf_full_product_info__from_publisher(const mtk::prices::msg::ps_conf_full_product_info__from_publisher&  pi)
{
    static int sequence=0;
    ++sequence;
    if(pi.seq_number != sequence)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "prod_loader", MTK_SS("out of sequence  expected " << sequence << "  received " << pi.seq_number),
                                                                                        mtk::alPriorDebug, mtk::alTypeUnknown));

    ++stats_prod_init;
    mtk::msg::sub_product_code  pc =  pi.full_prod_info.product_code;
    mtk::map<mtk::msg::sub_product_code, mtk::prices::msg::sub_full_product_info_optionals>::iterator it = map_products->find(pc);
    if(it == map_products->end())
        map_products->insert(std::make_pair(pc, mtk::prices::get_full_product_info_optional_from__full_product_info(pi.full_prod_info)));
    else
        mtk::prices::merge_full_product_info_optionals__with_full_product_info(it->second, pi.full_prod_info);
}
void suscribe_publisher_conf_full_prod_info__from_publisher(void)
{
    typedef  mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ps_conf_full_product_info__from_publisher> >      type_cptrhandle;
    static mtk::list< type_cptrhandle >  hqpid_ps_conf_full_product_info_by_market;
    for(auto it=map_market_info.begin(); it!=map_market_info.end(); ++it)
    {
        hqpid_ps_conf_full_product_info_by_market.push_back(type_cptrhandle());
        mtk::msg::sub_process_info  process_info = mtk::admin::get_process_info();
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_ps_conf_full_product_info_by_market.back(),
                                mtk::admin::get_url("server"),
                                mtk::prices::msg::ps_conf_full_product_info__from_publisher::get_in_subject(it->first, process_info.process_name, process_info.process_uuid),
                                mtk::prices::msg::ps_conf_full_product_info__from_publisher,
                                on_ps_conf_full_product_info__from_publisher)
    }
}



//  requests
void on_request_load_prices(const mtk::prices::msg::ps_req_product_info& req)
{
    if(lock_request_status)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(5))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "product_loader", "Ignoring request, process on lock status", mtk::alPriorError));
        MTK_END_EXEC_MAX_FREC
        return;
    }
    ++stats_req_rec;

    mtk::map<mtk::msg::sub_product_code, mtk::prices::msg::sub_full_product_info_optionals>::iterator it = map_products->find(req.product_code);
    if(it == map_products->end())
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "product_loader", MTK_SS("unknown product code " << req.product_code), mtk::alPriorError, mtk::alTypeNoPermisions));
        ++stats_req_unknown;
    }
    else
    {
        if(it->second.initialized  == false)
        {
            static int counter_request_with_partial_info=0;
            MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(2))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "product_loader", MTK_SS("request with partial info  counter:" << counter_request_with_partial_info), mtk::alPriorError, mtk::alTypeNoPermisions));
            MTK_END_EXEC_MAX_FREC
        }
        mtk::list<mtk::prices::msg::res_product_info::IC_response>  response_list;
        mtk::prices::msg::sub_full_product_info   sub_full_product_info =  mtk::prices::get_full_product_info_from_optional(it->second);
        mtk::prices::msg::res_product_info::IC_response response(sub_full_product_info);
        response_list.push_back(response);
        MTK_SEND_MULTI_RESPONSE(        mtk::prices::msg::res_product_info,
                                        mtk::prices::msg::res_product_info::IC_response,
                                        mtk::admin::get_url("client"),
                                        req.request_info,
                                        response_list)
    }

}





void on_price_update (const mtk::prices::msg::pub_best_prices& msg_update_price)
{
    ++stats_prec_update;
    mtk::map<mtk::msg::sub_product_code, mtk::prices::msg::sub_full_product_info_optionals>::iterator it = map_products->find(msg_update_price.product_code);
    if(it == map_products->end())
        map_products->insert(std::make_pair(msg_update_price.product_code, mtk::prices::get_empty_full_product_info_optional(msg_update_price.product_code)));
    else
        it->second.best_prices = msg_update_price.best_prices;
    mtk::admin::check_control_fluct(msg_update_price.orig_control_fluct);

    //  update last received message for this market
    mtk::map<std::string, market_info >::iterator  itlu = map_market_info.find(msg_update_price.product_code.market);
    if(itlu==map_market_info.end())
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "product_loader", MTK_SS("unknown market code " << msg_update_price.product_code), mtk::alPriorError, mtk::alTypeNoPermisions));
    else
    {
        mtk::dtDateTime  now = mtk::dtNowLocal();
        itlu->second.last_update_received  = now;
        if(itlu->second.last_update_received - now > itlu->second.check_interval)
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "produc_server", MTK_SS("recovered activity  " << it->first  << "  checking interval " << itlu->second.check_interval), mtk::alPriorError, mtk::alTypeOverflow));
        }
    }
}


//  check inactivity
void check_inactivity(void)
{
    MTK_EXEC_MAX_FREC_S(mtk::dtMilliseconds(500))
        //mtk::map<mtk::msg::sub_product_code>, mtk::DateTime >    map_last_update;
        mtk::map<std::string, market_info >::iterator  it = map_market_info.begin();
        for( ; it!= map_market_info.end(); ++it)
        {
            if(it->second.check_interval > mtk::dtSeconds(1))
            {
                if(it->second.ends  -  it->second.starts   < mtk::dtHours(2))
                {
                    MTK_EXEC_MAX_FREC_S_A(mtk::dtMinutes(30), A)
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "produc_server", MTK_SS("too low time to check " << it->first  << it->second.ends  -  it->second.starts), mtk::alPriorError, mtk::alTypeOverflow));
                    MTK_END_EXEC_MAX_FREC
                }

                mtk::dtDateTime  now = mtk::dtNowLocal();
                if(it->second.starts < now  &&   it->second.ends > now)
                {
                    if(it->second.last_update_received + it->second.check_interval < mtk::dtNowLocal())
                    {
                        MTK_EXEC_MAX_FREC_S_A(mtk::dtSeconds(30), A)
                            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "produc_server", MTK_SS("too many time with no activity " << it->first  << "  checking interval " << it->second.check_interval), mtk::alPriorError, mtk::alTypeOverflow));
                        MTK_END_EXEC_MAX_FREC
                    }
                }
            }
            else
            {
                if(it->second.check_interval > mtk::dtMilliseconds(10))
                {
                    MTK_EXEC_MAX_FREC_S_A(mtk::dtMinutes(15), A)
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "produc_server", MTK_SS("check activity time configuration too low " << it->second.check_interval), mtk::alPriorError, mtk::alTypeOverflow));
                    MTK_END_EXEC_MAX_FREC
                }
            }
        }
    MTK_END_EXEC_MAX_FREC
}






void init_map_market_info()
{
    mtk::list<std::string>  nodes = mtk::admin::get_config_nodes("MARKETS");
    for(mtk::list<std::string>::iterator it = nodes.begin(); it!= nodes.end(); ++it)
    {
        mtk::dtTimeQuantity interval = mtk::dtSeconds(20);
        bool ok = false;
        mtk::dtTimeQuantity starts = mtk::dtSeconds(0);
        mtk::dtTimeQuantity ends = mtk::dtSeconds(0);

        ok = false;
        mtk::s_TRY_stotq (mtk::admin::get_config_mandatory_property(MTK_SS("MARKETS." << *it <<".check_activity")), interval).assign(interval, ok);
        if(ok==false)
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "produc_server", MTK_SS("error reading configuration for market " << *it  <<  "  prop. check_activity"), mtk::alPriorError));

        ok = false;
        mtk::s_TRY_stotq (mtk::admin::get_config_mandatory_property(MTK_SS("MARKETS." << *it <<".start_time")), starts).assign(starts, ok);
        if(ok==false)
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "produc_server", MTK_SS("error reading configuration for market " << *it  <<  " prop. start_time"), mtk::alPriorError));

        ok = false;
        mtk::s_TRY_stotq (mtk::admin::get_config_mandatory_property(MTK_SS("MARKETS." << *it <<".end_time")), ends).assign(ends, ok);
        if(ok==false)
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "produc_server", MTK_SS("error reading configuration for market " << *it  <<  " prop.  end_time"), mtk::alPriorError));

        mtk::dtDateTime  starts_today = mtk::dtToday_0Time() + starts;
        mtk::dtDateTime  ends_today = mtk::dtToday_0Time() + ends;

        if(ends_today - starts_today  < mtk::dtHours(2))
            std::cout << "too low time to check " << ends_today - starts_today;

        if(interval  < mtk::dtSeconds(1)  &&   interval  > mtk::dtMilliseconds(10))
            std::cout << "interval too low  " << interval;

        map_market_info.insert(std::make_pair(*it, market_info(*it, interval, starts_today, ends_today)));
    }
}
