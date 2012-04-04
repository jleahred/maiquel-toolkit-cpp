#include <iostream>

#include "components/trading/trd_cli_support.h"
#include "components/trading/msg_trd_cli_ls.h"
#include "components/trading/msg_trd_cli_mk.h"
#include "components/trading/msg_trd_cli_sm.h"
#include "components/trading/msg_trd_cli_sl.h"
#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"
#include "support/nullable.hpp"
#include "support/re/RegExp.h"
#include "components/trading/msg_trd_oms_rq.h"



namespace
{

    const char*   APP_NAME          = "EXECS_LOADER";
    const char*   APP_VER           = "2012-04-03 e";
    const char*   APP_DESCRIPTION   = "I send execs to clients\n"
                                      "I'm not checking order sequence, or values on orders\n"
                                      "I receive, I keep, I response. Not checkings at all\n"
                                      ;

    const char*   APP_MODIFICATIONS =   "           2012-04-03 e  first version\n"
                                        ;



    void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);


    void register_global_commands (void)
    {
        mtk::admin::register_command("__GLOBAL__",  "stats",     "")->connect(command_stats);
        mtk::admin::register_command("orderserver",  "stats",     "")->connect(command_stats);
    }


    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)

}




namespace
{




//typedef mtk::tuple<mtk::trd::msg::sub_order_id, std::string/*mk order_id*/, mtk::msg::sub_request_id>    t_exec_key;
mtk::CountPtr<mtk::map<mtk::trd::t_exec_key, mtk::trd::msg::CF_EXLK> >    get_map_execs(void)
{
    static mtk::CountPtr<mtk::map<mtk::trd::t_exec_key, mtk::trd::msg::CF_EXLK> >  result = mtk::make_cptr(new mtk::map<mtk::trd::t_exec_key, mtk::trd::msg::CF_EXLK>{});
    return result;
}

template<typename CF_TYPE>
void update_or_insert(const CF_TYPE&  cf_ex_xx)
{
    mtk::CountPtr<mtk::map<mtk::trd::t_exec_key, mtk::trd::msg::CF_EXLK> >    map_execs = get_map_execs();

    mtk::trd::t_exec_key        exec_key    {mtk::trd::get_exec_key(cf_ex_xx)};
    mtk::trd::msg::CF_EXLK      cf_exlk     {cf_ex_xx, cf_ex_xx.executed_pos };


    auto it = map_execs->find(exec_key);
    if(it == map_execs->end())
        map_execs->insert(std::make_pair(exec_key, cf_exlk));
    else
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "execs_loader", MTK_SS("overwritting execution " << it->second << "  " <<  cf_exlk), mtk::alPriorError, mtk::alTypeLogicError));
        it->second = cf_exlk;
    }
}




void on_cf_ex_ls(const mtk::trd::msg::CF_EX_LS&  ex)
{
    update_or_insert(ex);
}

void on_cf_ex_mk(const mtk::trd::msg::CF_EX_MK&  ex)
{
    update_or_insert(ex);
}







//---------------------------
void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(MTK_SS("execs in memory._____________________"));
    response_lines.push_back(MTK_SS("ls:  " << get_map_execs()->size()));
}



void send_execs_from_request(const mtk::trd::msg::oms_RQ_ORDERS_STATUS&  rq)
{
    if(rq.reject_description != "")
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "execs_loader", MTK_SS("received request status rejected (ignoring)... " << rq.reject_description << "  full message " << rq),
                                                mtk::alPriorError, mtk::alTypeNoPermisions));
        return;
    }

    {
        mtk::CountPtr<mtk::map<mtk::trd::t_exec_key, mtk::trd::msg::CF_EXLK> >    map_execs = get_map_execs();
        for(auto it = map_execs->begin(); it != map_execs->end(); ++it)
        {
            if(rq.market  == it->second.invariant.product_code.market &&  rq.account == it->second.invariant.account)
            {
                mtk::msg::sub_gen_response_location gen_response_location (rq.request_info.req_id.session_id, rq.request_info.process_info.location.broker_code);
                mtk::trd::msg::CF_ST_EX   msg(it->second, gen_response_location);
                msg.orig_control_fluct = mtk::msg::sub_control_fluct("__none__", mtk::dtNowLocal());
                mtk_send_message("client", msg);
            }
        }
    }
}

void on_rq_order_status(const mtk::trd::msg::oms_RQ_ORDERS_STATUS&  rq)
{
    std::cout << "received request " << rq << std::endl;
    send_execs_from_request(rq);
}


};      //  anonymous namespace





int   delete_end_of_day_execs(void)
{
    int  result = 0;

    mtk::CountPtr<mtk::map<mtk::trd::t_exec_key, mtk::trd::msg::CF_EXLK> >        map_execs = get_map_execs();
    auto it = map_execs->begin();
    while  (it != map_execs->end())
    {
        if(it->second.invariant.time_in_force ==  "DAY")
        {
            it = map_execs->erase(it);
            ++result;
        }
        else
        {
            MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(30))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "execs_loader", MTK_SS("Order with time_in_foce not DAY??? " << it->second.invariant),
                                                        mtk::alPriorError, mtk::alTypeNoPermisions));
            MTK_END_EXEC_MAX_FREC
            ++it;
        }
    }

    return  result;
}


void  timer_check_delete_end_of_day(void)
{
    //  At this moment, it is not configurable the time to do it
    //  in the future (if would be necessary), we could add the time on configuration file, or even use a market message
    MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(1))
        static  mtk::DateTime  time_delete_end_of_day_execs  = mtk::dtToday_0Time() + mtk::dtHours(2);
        mtk::dtDateTime  now = mtk::dtNowLocal();
        if(now > time_delete_end_of_day_execs)
        {
            auto  next_time_delete_end_of_day_order  =  time_delete_end_of_day_execs + mtk::dtDays(1);
            int deleted_execs = delete_end_of_day_execs();

            AlarmMsg(mtk::Alarm(MTK_HERE, "order execs_loader", MTK_SS("deleted end of day execs...   next:"  <<  next_time_delete_end_of_day_order <<
                    "  num execs deleted:"  << deleted_execs), mtk::alPriorWarning, mtk::alTypeUnknown));
            time_delete_end_of_day_execs  = next_time_delete_end_of_day_order;
        }
    MTK_END_EXEC_MAX_FREC
}










//  ex msg_type   CF_NW_LS   __RECEIVER__  on_cf_xx_ls
#define  MAKE_TRADING_SUSCRIPTION(__MARKET__, __MSG_TYPE__, __RECEIVER__)    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::__MSG_TYPE__>            > hqpid_##__MSG_TYPE__;    \
        MTK_QPID_RECEIVER_CONNECT_F(     \
                                hqpid_##__MSG_TYPE__,     \
                                mtk::admin::get_url("client"),     \
                                mtk::trd::msg::__MSG_TYPE__::get_in_subject("*", __MARKET__, "*"),     \
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
        mtk::vector<mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_EX_LS>             > >   list_hqpid_CF_EX_LS;
        mtk::vector<mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_EX_MK>             > >   list_hqpid_CF_EX_MK;


        mtk::vector<mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::oms_RQ_ORDERS_STATUS> > >   list_hqpid_oms_RQ_ORDERS_STATUS;
        for(auto it_market=list_markets.Get().begin(); it_market!=list_markets.Get().end(); ++it_market)
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "execs_loader", MTK_SS("adding market " << *it_market), mtk::alPriorDebug, mtk::alTypeLogicError));
            std::cout << MTK_SS("adding market " << *it_market) << std::endl;

            MAKE_TRADING_SUSCRIPTION(*it_market, CF_EX_LS, on_cf_ex_ls);
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


        MTK_TIMER_1SF(timer_check_delete_end_of_day)

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
