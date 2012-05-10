#include "components/prices/prices_publication.h"
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
    const char*   APP_VER           = "2012-05-10 f";
    const char*   APP_DESCRIPTION   = "I will keep prices and other product information on memory and I will serve it to clients or other proceses\n"
                                      "I will receive this information listening as a client";

    const char*   APP_MODIFICATIONS =   "           2011-04-12     first version\n"
                                        "           2011-08-01     filling product publishing protocol (update)\n"
                                        "           2012-01-13     delete on init from publisher and modifs on check activity\n"
                                        "           2012-01-19     reduce exponentially no activity message\n"
                                        "           2012-01-30     recover activity only when frecuency > 0\n"
                                        "           2012-04-02     price compactation and cli_serv moved from msg_admin\n"
                                        "           2012-05-10     deleting prices at 4h\n"
                                        ;

}





    //  COMMANDS
    void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_lock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_unlock(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_status(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_set_frecuency(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_set_frecuency_provisional(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_get_activity_config(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);


    void register_global_commands (void)
    {
        mtk::admin::register_command("__GLOBAL__",  "stats",                 "")->connect(command_stats);
        mtk::admin::register_command("pl",          "stats",                 "")->connect(command_stats);
        mtk::admin::register_command("pl",          "lock",                  "I will ignore all request (no response)", true)->connect(command_lock);
        mtk::admin::register_command("pl",          "unlock",                "I will response again", true)->connect(command_unlock);
        mtk::admin::register_command("__GLOBAL__",  "status",                "Info about my current status")->connect(command_status);
        mtk::admin::register_command("pl",          "status",                "Info about my current status")->connect(command_status);
        mtk::admin::register_command("pl",          "set_frec_activity",     "<market>  <new_frec>  Configure the frecuency to check activity", true)->connect(command_set_frecuency);
        mtk::admin::register_command("pl",          "set_frec_activity_prov","<market>  <new_frec> <for_time> Configure the frecuency to check activity for a period of time")->connect(command_set_frecuency_provisional);
        mtk::admin::register_command("pl",          "get_activity_config",   "show all activity configurations")->connect(command_get_activity_config);
    }

    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)


    //  status
    bool lock_request_status=false;

    //  market info
    class market_info
    {
        public:
            market_info(const std::string& _name, const mtk::dtTimeQuantity& tq, const mtk::dtDateTime&  _starts, const mtk::dtDateTime&  _ends)
                :         name(_name)
                        , official_check_interval(tq)
                        , provisonal_check_interval(tq)
                        , provisional_valid_till(mtk::dtNowLocal())
                        , delay_notif(mtk::dtSeconds(0))
                        , last_update_received(mtk::dtNowLocal())
                        , starts(_starts), ends(_ends) {}

            std::string             name;
            mtk::dtTimeQuantity     official_check_interval;
            mtk::dtTimeQuantity     provisonal_check_interval;
            mtk::dtDateTime         provisional_valid_till;
            mtk::dtTimeQuantity     delay_notif;
            mtk::DateTime           last_update_received;
            mtk::DateTime           starts;
            mtk::DateTime           ends;

            mtk::dtTimeQuantity     get_check_interval(void)  const
            {
                mtk::dtDateTime  now  = mtk::dtNowLocal();
                if(now<provisional_valid_till)
                    return provisonal_check_interval;
                else
                    return official_check_interval;
            }
    };
    mtk::map<std::string, market_info >    map_market_info;



    //      stats
    int  stats_req_rec=0;
    int  stats_req_unknown=0;
    int  stats_prec_update=0;
    int  stats_mk_last_execs_update=0;
    int  stats_prod_init=0;






    //  PRICES MAP
    mtk::CountPtr<mtk::map<mtk::msg::sub_product_code, mtk::prices::msg::sub_full_product_info_optionals> >   map_products;



void on_request_load_prices      (const mtk::prices::msg::ps_req_product_info& req);
void on_price_update__or_last    (const mtk::prices::msg::ppc& msg_update_price__or_last_ex_ticker);
void check_inactivity            (void);
void check_end_of_day            (void);
void init_map_market_info        (void);


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
        MTK_TIMER_1CF(check_end_of_day)

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
    response_lines.push_back(MTK_SS("#last_ex  : " << stats_mk_last_execs_update));
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



bool  check_and_split_params(const std::string& params, mtk::list<std::string>&  response_lines, int number_of_params, mtk::vector<std::string>& vparams)
{
    mtk::vector<std::string> temp_vparams = mtk::s_split(mtk::s_trim(params, ' '), " ");
    //  remove empty params
    vparams.clear();
    for(unsigned i=0; i<temp_vparams.size(); ++i)
    {
        std::string param = mtk::s_trim(temp_vparams[i], ' ');
        if(param != "")
            vparams.push_back(param);
    }
    if(vparams.size() != unsigned(number_of_params))
    {
        response_lines.push_back(MTK_SS("invalid number of params. There is needed "  <<  number_of_params  <<  "  params:   "  << params));
        return  false;
    }
    return true;
}

void command_set_frecuency(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    mtk::vector<std::string>  vparams;
    if(check_and_split_params(params, response_lines, 2, vparams)  == false)     return;

    std::string  market  =   vparams[0];
    auto  new_frecuency  =   mtk::s_TRY_stotq(vparams[1], mtk::dtSeconds(0));

    if(new_frecuency._1  ==  false)
    {
        response_lines.push_back(MTK_SS("invalid frecuency string  " <<  vparams[0]));
        return;
    }

    mtk::map<std::string, market_info >::iterator  itlu = map_market_info.find(market);
    if(itlu == map_market_info.end())
    {
        response_lines.push_back(MTK_SS("market code not found  " <<  market));
        return;
    }

    itlu->second.official_check_interval    = new_frecuency._0;
    itlu->second.provisional_valid_till     = mtk::dtNowLocal();
    itlu->second.provisonal_check_interval  = new_frecuency._0;

    mtk::admin::set_config_property(MTK_SS("MARKETS" << "." <<  market << ".check_activity"), MTK_SS(new_frecuency._0));

    command_get_activity_config("", "", response_lines);
}

void command_set_frecuency_provisional(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    mtk::vector<std::string>  vparams;
    if(check_and_split_params(params, response_lines, 3, vparams)  == false)     return;

    std::string  market  =   vparams[0];
    auto  new_frecuency  =   mtk::s_TRY_stotq(vparams[1], mtk::dtSeconds(0));
    auto  for_time       =   mtk::s_TRY_stotq(vparams[2], mtk::dtSeconds(0));

    if(new_frecuency._1  ==  false)
    {
        response_lines.push_back(MTK_SS("invalid frecuency string  " <<  vparams[1]));
        return;
    }
    if(for_time._1  ==  false)
    {
        response_lines.push_back(MTK_SS("invalid second param  (for time)    " <<  vparams[2]));
        return;
    }

    mtk::map<std::string, market_info >::iterator  itlu = map_market_info.find(market);
    if(itlu == map_market_info.end())
    {
        response_lines.push_back(MTK_SS("market code not found  " <<  market));
        return;
    }

    itlu->second.provisional_valid_till     = mtk::dtNowLocal() + for_time._0;
    itlu->second.provisonal_check_interval  = new_frecuency._0;

    command_get_activity_config("", "", response_lines);
}



void command_get_activity_config(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    if (mtk::s_trim(params, ' ')  != "")
    {
        response_lines.push_back(MTK_SS("non exptected params  "));
        return;
    }

    for(auto it=map_market_info.begin(); it!=map_market_info.end(); ++it)
    {
        response_lines.push_back(MTK_SS(it->first  <<  "    --------------------------------"));
        response_lines.push_back(MTK_SS("CHECKING INTERVAL....   "  <<  it->second.get_check_interval()));
        #define WRITE_RESPONSE(__NAME__)  \
            response_lines.push_back(MTK_SS(#__NAME__ ":  "  << it->second.__NAME__));
        WRITE_RESPONSE(official_check_interval);
        WRITE_RESPONSE(provisonal_check_interval);
        WRITE_RESPONSE(provisional_valid_till);
        response_lines.push_back(MTK_SS("provisional valid for:  "  <<  it->second.provisional_valid_till - mtk::dtNowLocal()));
        WRITE_RESPONSE(delay_notif);
        WRITE_RESPONSE(last_update_received);
        WRITE_RESPONSE(starts);
        WRITE_RESPONSE(ends);
    }
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
    typedef  mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ppc> >               type_cptrhandle;
    static mtk::list< type_cptrhandle >  hqpid_update_best_prices_list_by_market;


    for(auto it=map_market_info.begin(); it!=map_market_info.end(); ++it)
    {
        hqpid_update_best_prices_list_by_market.push_back(type_cptrhandle{});
        MTK_QPID_RECEIVER_CONNECT_F__WITH_ADDRESS(
                                hqpid_update_best_prices_list_by_market.back(),
                                mtk::admin::get_url("client"),
                                mtk::prices::msg::ppc::static_get_qpid_address(it->first),
                                mtk::prices::msg::ppc::get_in_subject("*"),
                                mtk::prices::msg::ppc,
                                on_price_update__or_last)
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




void on_price_update (const  mtk::msg::sub_product_code& product_code,  const mtk::prices::msg::sub_best_prices&   best_prices)
{
    ++stats_prec_update;
    mtk::map<mtk::msg::sub_product_code, mtk::prices::msg::sub_full_product_info_optionals>::iterator it = map_products->find(product_code);
    if(it == map_products->end())
        map_products->insert(std::make_pair(product_code, mtk::prices::get_empty_full_product_info_optional(product_code)));
    else
        it->second.best_prices = best_prices;


    //  update last received message for this market
    mtk::map<std::string, market_info >::iterator  itlu = map_market_info.find(product_code.market);
    if(itlu==map_market_info.end())
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "product_loader", MTK_SS("unknown market code " << product_code), mtk::alPriorError, mtk::alTypeNoPermisions));
    else
    {
        mtk::dtDateTime  now = mtk::dtNowLocal();
        if(now - itlu->second.last_update_received  > itlu->second.get_check_interval()  &&  itlu->second.get_check_interval() > mtk::dtSeconds(1))
        {
            if(itlu->second.starts < now  &&   itlu->second.ends > now)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "produc_server", MTK_SS("recovered activity  " << itlu->second.name  <<  " after  " <<  now - itlu->second.last_update_received
                                                            << "  checking interval " << itlu->second.get_check_interval()), mtk::alPriorError, mtk::alTypeOverflow));
            itlu->second.delay_notif = mtk::dtSeconds(0);
        }
        itlu->second.last_update_received  = now;
    }
}




void on_mk_last_ex_ticher_update (const  mtk::msg::sub_product_code& product_code,  const mtk::prices::msg::sub_last_mk_execs_ticker&   last_mk_execs_ticker)
{
    ++stats_mk_last_execs_update;
    auto it = map_products->find(product_code);
    if(it == map_products->end())
        map_products->insert(std::make_pair(product_code, mtk::prices::get_empty_full_product_info_optional(product_code)));
    else
        it->second.last_mk_execs_ticker = last_mk_execs_ticker;

    //  update last received message for this market
    mtk::map<std::string, market_info >::iterator  itlu = map_market_info.find(product_code.market);
    if(itlu==map_market_info.end())
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "product_loader", MTK_SS("unknown market code " << product_code), mtk::alPriorError, mtk::alTypeNoPermisions));
    else
    {
        mtk::dtDateTime  now = mtk::dtNowLocal();
        if(now - itlu->second.last_update_received  > itlu->second.get_check_interval()  &&  itlu->second.get_check_interval() > mtk::dtSeconds(1))
        {
            if(itlu->second.starts < now  &&   itlu->second.ends > now)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "produc_server", MTK_SS("recovered activity  " << itlu->second.name  <<  " after  " <<  now - itlu->second.last_update_received
                                                            << "  checking interval " << itlu->second.get_check_interval()), mtk::alPriorError, mtk::alTypeOverflow));
            itlu->second.delay_notif = mtk::dtSeconds(0);
        }
        itlu->second.last_update_received  = now;
    }
}

void  on_price_update__or_last (const mtk::prices::msg::ppc& ppc)
{
    auto received = mtk::prices::publ::decompact_prices(ppc.compacted_data);

    mtk::admin::check_control_fluct  (mtk::msg::sub_control_fluct{ppc.key, ppc.datetime});
    mtk::msg::sub_product_code   product_code{ppc.market, ppc.product};
    if(received._0.HasValue())
        on_price_update(product_code, received._0.Get());

    if(received._1.HasValue())
        on_mk_last_ex_ticher_update(product_code, received._1.Get());
}



//  check inactivity
void check_inactivity(void)
{
    MTK_EXEC_MAX_FREC_S(mtk::dtMilliseconds(500))
        //mtk::map<mtk::msg::sub_product_code>, mtk::DateTime >    map_last_update;
        mtk::map<std::string, market_info >::iterator  it = map_market_info.begin();
        for( ; it!= map_market_info.end(); ++it)
        {
            MTK_EXEC_MAX_FREC_S_A(mtk::dtMinutes(1), A)
                if(it->second.ends <  mtk::dtToday_0Time())
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_inactivity", "possible change of day, calling  init_map_market_info", mtk::alPriorWarning));
                    init_map_market_info();
                    return;
                }
            MTK_END_EXEC_MAX_FREC

            if(it->second.get_check_interval() > mtk::dtSeconds(1))
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
                    if(it->second.last_update_received + it->second.get_check_interval() + it->second.delay_notif < mtk::dtNowLocal())
                    {
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "produc_server", MTK_SS("too much time with no activity " << it->first
                                                                                << "  checking interval " << it->second.get_check_interval()
                                                                                << "  +delay notifying " << it->second.delay_notif
                                                                                ), mtk::alPriorError, mtk::alTypeOverflow));
                        if(it->second.delay_notif > mtk::dtSeconds(0))
                        {
                            if(it->second.delay_notif < mtk::dtHours(2))
                                it->second.delay_notif += it->second.delay_notif;
                            else
                                it->second.delay_notif += mtk::dtHours(2);
                        }
                        else
                            it->second.delay_notif = mtk::dtMinutes(1);
                    }
                }
            }
            else
            {
                if(it->second.get_check_interval() > mtk::dtMilliseconds(10))
                {
                    MTK_EXEC_MAX_FREC_S_A(mtk::dtMinutes(15), A)
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "produc_server", MTK_SS("check activity time configuration too low " << it->second.get_check_interval()), mtk::alPriorError, mtk::alTypeOverflow));
                    MTK_END_EXEC_MAX_FREC
                }
            }
        }
    MTK_END_EXEC_MAX_FREC
}






void init_map_market_info()
{
    map_market_info.clear();
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


void  check_end_of_day(void)
{
    //  At this moment, it is not configurable the time to do it
    //  in the future (if would be necessary), we could add the time on configuration file, or even use a market message
    MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(1))
        static  mtk::DateTime  time_delete_end_of_day  = mtk::dtToday_0Time() + mtk::dtHours(4);
        mtk::dtDateTime  now = mtk::dtNowLocal();
        if(now > time_delete_end_of_day)
        {
            auto  next_time_delete_end_of_day  =  time_delete_end_of_day + mtk::dtDays(1);

            if(map_products.isValid())
            {
                int size = map_products->size();
                map_products->clear();

                AlarmMsg(mtk::Alarm(MTK_HERE, "product_loader", MTK_SS("deleted product info...   next deletion:"  <<  next_time_delete_end_of_day <<
                                    "  #products_deleted:"  << size), mtk::alPriorWarning, mtk::alTypeUnknown));
                time_delete_end_of_day  = next_time_delete_end_of_day;
                send_req_init_prod_info_to_markets__to_publisher();
            }
        }
    MTK_END_EXEC_MAX_FREC
}
