#include <iostream>

#include "components/trading/msg_trd_cli_ls.h"
#include "components/trading/msg_trd_cli_mk.h"
#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"
#include "support/nullable.hpp"
#include "support/re/RegExp.h"
#include "components/trading/msg_trd_oms_rq.h"



namespace
{

    const char*   APP_NAME          = "ORDERS_LOADER";
    const char*   APP_VER           = "2011-07-08";
    const char*   APP_DESCRIPTION   = "I send current order status to clients\n"
                                      "I'm a stupid process\n"
                                      "I'm not checking order sequence, or values on orders\n"
                                      "I receive, I keep, I response. Not checkings at all\n";

    const char*   APP_MODIFICATIONS = "           2011-07-08     first version\n";



    void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_find_order(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);


    void register_global_commands (void)
    {
        mtk::admin::register_command("__GLOBAL__",  "stats",     "")->connect(command_stats);
        mtk::admin::register_command("orderserver",  "stats",     "")->connect(command_stats);
        mtk::admin::register_command("orderserver",  "find_order",     "<market> <regexp_product_code> <regexp_sessionid> <regexp_requestid>"
                                                                        "  it returns maximun 10 matches")->connect(command_find_order);
    }


    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)

}




namespace
{





template<typename  CF_TYPE>     //  ex:    mtk::trd::msg::CF_XX_LS
mtk::CountPtr<mtk::map<mtk::trd::msg::sub_order_id, CF_TYPE> >    get_map_order(void)
{
    static mtk::CountPtr<mtk::map<mtk::trd::msg::sub_order_id, CF_TYPE> >  map_ordersls;

    if(map_ordersls.isValid() == false)
        map_ordersls = mtk::make_cptr(new mtk::map<mtk::trd::msg::sub_order_id, CF_TYPE>);
    return map_ordersls;
}

template<typename  CF_TYPE>     //  ex:    mtk::trd::msg::CF_XX_LS
void update_or_insert(const CF_TYPE&  orders_status)
{
    mtk::CountPtr<mtk::map<mtk::trd::msg::sub_order_id, CF_TYPE> >    map_orders_ls = get_map_order<CF_TYPE>();
    //auto  map_orders_ls = get_map_order<CF_TYPE>();

    auto it = map_orders_ls->find(orders_status.invariant.order_id);
    if(it == map_orders_ls->end())
        map_orders_ls->insert(std::make_pair(orders_status.invariant.order_id, orders_status));
    else
        it->second = orders_status;
}


template<typename  CF_TYPE>     //  ex:    mtk::trd::msg::CF_XX_LS
void delete_order(const CF_TYPE&  orders_status)
{
    mtk::CountPtr<mtk::map<mtk::trd::msg::sub_order_id, CF_TYPE> >    map_orders_ls = get_map_order<CF_TYPE>();
    //auto  map_orders_ls = get_map_order<CF_TYPE>();

    auto it = map_orders_ls->find(orders_status.invariant.order_id);
    if(it != map_orders_ls->end())
        map_orders_ls->erase(it);
}



//      LIMIT ORDERS

template<typename T>        //  ie:  mtk::trd::msg::CF_NW_LS
void on_cf_xx_ls(const T&  cf)
{
    update_or_insert(mtk::trd::msg::CF_XX_LS(cf));
}

template<typename T>        //  ie:  mtk::trd::msg::CF_NW_LS
void on_cf_ex_ls(const T&  ex)
{
    update_or_insert(mtk::trd::msg::CF_XX_LS(ex));
}

void on_cf_cc_ls(const mtk::trd::msg::CF_CC_LS&  cfcc)
{
    if(cfcc.total_execs.acc_quantity.GetIntCode() == 0)
        delete_order(mtk::trd::msg::CF_XX_LS(cfcc));
    else
    {
        mtk::trd::msg::CF_XX_LS status  (cfcc);
        status.total_execs.remaining_qty.SetIntCode(0);
        update_or_insert(status);
    }
}





//      MARKET ORDERS

template<typename T>        //  ie:  mtk::trd::msg::CF_NW_MK
void on_cf_xx_mk(const T&  cf)
{
    update_or_insert(mtk::trd::msg::CF_XX_MK(cf));
}

template<typename T>        //  ie:  mtk::trd::msg::CF_NW_LS
void on_cf_ex_mk(const T&  ex)
{
    update_or_insert(mtk::trd::msg::CF_XX_MK(ex));
}


void on_cf_cc_mk(const mtk::trd::msg::CF_CC_MK&  cfcc)
{
    if(cfcc.total_execs.acc_quantity.GetIntCode() == 0)
        delete_order(mtk::trd::msg::CF_XX_MK(cfcc));
    else
    {
        mtk::trd::msg::CF_XX_MK status(cfcc);
        status.total_execs.remaining_qty.SetIntCode(0);
        update_or_insert(status);
    }
}







//---------------------------
void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(MTK_SS("orders in memory._____________________"));
    response_lines.push_back(MTK_SS("ls:  " << get_map_order<mtk::trd::msg::CF_XX_LS>()->size()));
    response_lines.push_back(MTK_SS("mk:  " << get_map_order<mtk::trd::msg::CF_XX_MK>()->size()));
}



template<typename CF_TYPE>
void find_orders(const std::string&  market, const std::string&  re_product_code, const std::string&  re_session_id, const std::string&  re_req_code,
                                mtk::list<std::string>&  response_lines)
{
    mtk::CountPtr<mtk::map<mtk::trd::msg::sub_order_id, CF_TYPE> >    map_orders = get_map_order<CF_TYPE>();

    mtk::RegExp re_sid(re_session_id);
    mtk::RegExp re_rid(re_req_code);
    mtk::RegExp re_pc(re_product_code);


    int located_lines=0;
    for(auto it = map_orders->begin(); it != map_orders->end(); ++it)
    {
        int matches = 0;
        mtk::trd::msg::sub_order_id oi = it->first;

        if(re_sid.Match(oi.session_id))
            ++matches;
        if(re_rid.Match(oi.req_code))
            ++matches;
        if(re_pc.Match(re_product_code))
            ++matches;
        if(market == it->second.invariant.product_code.market)
            ++matches;

        if(matches == 4)
        {
            response_lines.push_back(MTK_SS(it->second));
            ++located_lines;
        }
        if(located_lines>7)
        {
            response_lines.push_back("...");
            break;
        }
    }
}

void command_find_order(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    mtk::vector<std::string>   vparams = mtk::s_split(params, " ");
    if(vparams.size() != 4)
    {
        response_lines.push_back(MTK_SS("expected 4 parameters received " << vparams.size()));
        return;
    }


    response_lines.push_back(MTK_SS("\n\nLIMITED"));
    find_orders<mtk::trd::msg::CF_XX_LS>(vparams[0], vparams[1], vparams[2], vparams[3], response_lines);
    response_lines.push_back(MTK_SS("\n\nMARKET"));
    find_orders<mtk::trd::msg::CF_XX_MK>(vparams[0], vparams[1], vparams[2], vparams[3], response_lines);
}



template<typename  CF_TYPE,  typename  STATUS_TYPE>     //  ex:  mtk::trd::msg::CF_XX_LS     STATUS_TYPE:  mtk::trd::msg::CF_ST_LS
void send_orders_from_request(const mtk::trd::msg::oms_RQ_ORDERS_STATUS&  rq)
{
    static auto client_qpid_sender = mtk::admin::get_qpid_sender  ("client", mtk::t_qpid_address("CLITESTING"));

    if(rq.reject_description != "")
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "orders_loader", MTK_SS("received request status rejected (ignoring)... " << rq.reject_description << "  full message " << rq),
                                                mtk::alPriorError, mtk::alTypeNoPermisions));
        return;
    }

    {       //      limit orders
        mtk::CountPtr<mtk::map<mtk::trd::msg::sub_order_id, CF_TYPE> >    map_orders = get_map_order<CF_TYPE>();
        for(auto it = map_orders->begin(); it != map_orders->end(); ++it)
        {
            if(rq.market  == it->second.invariant.product_code.market &&  rq.account == it->second.invariant.account)
            {
                mtk::msg::sub_gen_response_location gen_response_location (rq.request_info.req_id.session_id, rq.request_info.process_info.location.client_code);
                STATUS_TYPE   msg(it->second, gen_response_location);
                msg.orig_control_fluct = mtk::msg::sub_control_fluct("__none__", mtk::dtNowLocal());
                mtk::send_message(client_qpid_sender, msg);
            }
        }
    }
}

void on_rq_order_status(const mtk::trd::msg::oms_RQ_ORDERS_STATUS&  rq)
{
    send_orders_from_request<mtk::trd::msg::CF_XX_LS, mtk::trd::msg::CF_ST_LS>(rq);
    send_orders_from_request<mtk::trd::msg::CF_XX_MK, mtk::trd::msg::CF_ST_MK>(rq);
}


};      //  anonymous namespace











//  ex msg_type   CF_NW_LS   __RECEIVER__  on_cf_xx_ls
#define  MAKE_TRADING_SUSCRIPTION(__MARKET__, __MSG_TYPE__, __RECEIVER__)    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::__MSG_TYPE__>            > hqpid_##__MSG_TYPE__;    \
        MTK_QPID_RECEIVER_CONNECT_F(     \
                                hqpid_##__MSG_TYPE__,     \
                                mtk::admin::get_url("client"),     \
                                mtk::trd::msg::__MSG_TYPE__::get_in_subject("*", __MARKET__, "*", "*"),     \
                                mtk::trd::msg::__MSG_TYPE__,     \
                                __RECEIVER__)    \
        list_hqpid_##__MSG_TYPE__.push_back(hqpid_##__MSG_TYPE__);




int main(int argc, char ** argv)
{
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);


        mtk::Nullable<mtk::list<std::string> >  list_markets = mtk::admin::get_config_list("MISC.markets");

        if(list_markets.HasValue() == false)
            throw mtk::Alarm(MTK_HERE, "main", "no markets defined on config file", mtk::alPriorCritic, mtk::alTypeLogicError);


        //  too keep in scope handles created in for
        mtk::vector<mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_NW_LS>             > >   list_hqpid_CF_NW_LS;
        mtk::vector<mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_MD_LS>             > >   list_hqpid_CF_MD_LS;
        mtk::vector<mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_CC_LS>             > >   list_hqpid_CF_CC_LS;
        mtk::vector<mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_EX_LS>             > >   list_hqpid_CF_EX_LS;
        mtk::vector<mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_NW_MK>             > >   list_hqpid_CF_NW_MK;
        mtk::vector<mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_MD_MK>             > >   list_hqpid_CF_MD_MK;
        mtk::vector<mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_CC_MK>             > >   list_hqpid_CF_CC_MK;
        mtk::vector<mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_EX_MK>             > >   list_hqpid_CF_EX_MK;
        mtk::vector<mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::oms_RQ_ORDERS_STATUS> > >   list_hqpid_oms_RQ_ORDERS_STATUS;
        for(auto it_market=list_markets.Get().begin(); it_market!=list_markets.Get().end(); ++it_market)
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "order_loader", MTK_SS("adding market " << *it_market), mtk::alPriorDebug, mtk::alTypeLogicError));
            std::cout << MTK_SS("adding market " << *it_market) << std::endl;
            //      LS
            MAKE_TRADING_SUSCRIPTION(*it_market, CF_NW_LS, on_cf_xx_ls);
            MAKE_TRADING_SUSCRIPTION(*it_market, CF_MD_LS, on_cf_xx_ls);
            MAKE_TRADING_SUSCRIPTION(*it_market, CF_CC_LS, on_cf_cc_ls);

            MAKE_TRADING_SUSCRIPTION(*it_market, CF_EX_LS, on_cf_ex_ls);




            //      MK
            MAKE_TRADING_SUSCRIPTION(*it_market, CF_NW_MK, on_cf_xx_mk);
            MAKE_TRADING_SUSCRIPTION(*it_market, CF_MD_MK, on_cf_xx_mk);
            MAKE_TRADING_SUSCRIPTION(*it_market, CF_CC_MK, on_cf_cc_mk);

            MAKE_TRADING_SUSCRIPTION(*it_market, CF_EX_MK, on_cf_ex_mk);


            //      STATUS
            static  std::string  oms_from = mtk::admin::get_config_property("OMS_CHAIN.from").Get();
            mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::oms_RQ_ORDERS_STATUS>            > hqpid_oms_RQ_ORDERS_STATUS;
            MTK_QPID_RECEIVER_CONNECT_F(
                                    hqpid_oms_RQ_ORDERS_STATUS,
                                    mtk::admin::get_url("server"),
                                    mtk::trd::msg::oms_RQ_ORDERS_STATUS::get_in_subject(*it_market, oms_from),
                                    mtk::trd::msg::oms_RQ_ORDERS_STATUS,
                                    on_rq_order_status)
            list_hqpid_oms_RQ_ORDERS_STATUS.push_back(hqpid_oms_RQ_ORDERS_STATUS);
        }



        mtk::start_timer_wait_till_end();


        std::cout << "FIN..... " << std::endl;
        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION (std::cout<< , "main", "nothing more")

    std::cout << "MAL..... " << std::endl;
    #include "support/release_on_exit.hpp"
    return -1;

}
