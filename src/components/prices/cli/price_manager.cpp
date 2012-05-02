#include "price_manager.h"


#include "support/mtk_string.h"
#include "support/list.hpp"
#include "components/admin/admin.h"
#include "components/request_response.hpp"
#include "components/prices/prices_publication.h"



//  support functions

namespace {

    struct  stats
    {
        int     num_best_prices;
        int     num_last_exec_ticker;
        int     num_additional_info;
        stats()  :  num_best_prices(0), num_last_exec_ticker(0), num_additional_info(0) {};
    };

    stats&  get_stats(void)
    {
        static  stats*  _stats = new stats{};
        return *_stats;
    }


};  //namespace  {



namespace
{

    const char*   VERSION       =   "2012-03-20";
    const char*   MODIFICATIONS =   "           2011-04-11     first version\n"
                                    "           2011-08-04     updated to prices publishing protocol and correct managment of factory\n"
                                    "           2012-02-23     market exec ticker support\n"
                                    "           2012-03-20     subscriptions limit\n"
                                    "           2012-04-02     addtional info\n"
                                    ;



    void command_version(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(MTK_SS(__FILE__ << ":  " << VERSION));
    }

    void command_stats  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back("PRICES SUBSCRIPTIONS");
        response_lines.push_back(".......................................");
        response_lines.push_back(MTK_SS("#best_prices       : " << get_stats().num_best_prices));
        response_lines.push_back(MTK_SS("#last_ex_mk_ticker : " << get_stats().num_last_exec_ticker));
        response_lines.push_back(MTK_SS("#num_additional_inf: " << get_stats().num_additional_info));
    }

    void command_modifications  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(__FILE__);
        response_lines.push_back(".......................................");
        response_lines.push_back(MODIFICATIONS);
    }


    void register_global_commands (void)
    {
        mtk::admin::register_command("__GLOBAL__",  "ver",          "")->connect(command_version);
        mtk::admin::register_command("__GLOBAL__",  "modifs",       "")->connect(command_modifications);
        mtk::admin::register_command("__GLOBAL__",  "stats",        "")->connect(command_stats);
        mtk::admin::register_command("price_manager",  "ver",       "")->connect(command_version);
        mtk::admin::register_command("price_manager",  "modifs",    "")->connect(command_modifications);
    }

    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)
}












namespace mtk
{

namespace prices
{



mtk::CountPtr<mtk::Signal<> >   get_signal_too_many_subscriptions_best_prices       (void)
{
    static  mtk::CountPtr<mtk::Signal<> >  _signal = mtk::make_cptr(new mtk::Signal<>);
    return _signal;
}

mtk::CountPtr<mtk::Signal<>  >  get_signal_too_many_subscriptions_last_ex_mk_ticker (void)
{
    static  mtk::CountPtr<mtk::Signal<> >  _signal = mtk::make_cptr(new mtk::Signal<>);
    return _signal;
}




internal_price_manager__factory::internal_price_manager__factory(const mtk::msg::sub_product_code&  _product_code)
    :     product_code(_product_code)
        , full_prod_info(   mtk::prices::msg::__internal_get_default((mtk::prices::msg::sub_full_product_info_optionals*) 0))
        , full_prod_info_last_request(mtk::dtNowLocal() - mtk::dtDays(300))
{
}

internal_price_manager__factory::~internal_price_manager__factory()
{
}




void internal_price_manager__factory::on_price_update(const mtk::prices::msg::ppc& msg)
{
    if(product_code.market !=  msg.market  ||  product_code.product != msg.product)
        throw mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received update on " << msg.market << "." << msg.product << " expected product "  << product_code),
                                                    mtk::alPriorCritic, mtk::alTypeNoPermisions);

    auto received = mtk::prices::publ::decompact_prices(msg.compacted_data);
    if(received._0.HasValue() == false)
        return;

    mtk::prices::msg::sub_best_prices  best_prices = received._0.Get();


    if(full_prod_info.best_prices.HasValue()   &&   full_prod_info.best_prices.Get() == best_prices)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(30))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received update with no changes  " << product_code
                                            << full_prod_info.best_prices << " ==  " << best_prices ), mtk::alPriorError, mtk::alTypeNoPermisions));
        MTK_END_EXEC_MAX_FREC
    }


    full_prod_info.best_prices = best_prices;        //      ->1

    if(h_best_prices.isValid()==false)
    {
        //  if no one is interested, the suscription must be canceled
        MTK_EXEC_MAX_FREC(mtk::dtSeconds(10))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received update with no suscriptions   on  " << product_code)
                                            , mtk::alPriorError, mtk::alTypeLogicError));
        MTK_END_EXEC_MAX_FREC
        return;
    }

    if(signal_best_prices_update.emit(product_code, full_prod_info.best_prices.Get()) ==0)  //  not necessary to check if best_prices has value  ->1
    {
        MTK_EXEC_MAX_FREC(mtk::dtSeconds(10))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received update on " << product_code << " with no signal receptor"),
                        mtk::alPriorError, mtk::alTypeLogicError));
        MTK_END_EXEC_MAX_FREC
    }
    MTK_EXEC_MAX_FREC(mtk::dtSeconds(1));

        mtk::admin::check_control_fluct(mtk::msg::sub_control_fluct(msg.key, msg.datetime));
    MTK_END_EXEC_MAX_FREC
}


void internal_price_manager__factory::on_addtional_info_update(const mtk::prices::msg::pub_additional_info& msg)
{
    if(product_code !=  msg.product_code)
        throw mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received pub_additional_info on " << msg.product_code  << " expected product "  << product_code),
                                                    mtk::alPriorCritic, mtk::alTypeNoPermisions);


    full_prod_info.additional_info = msg.additional_info;       //  1

    if(h_additional_info.isValid()==false)
    {
        //  if no one is interested, the suscription must be canceled
        MTK_EXEC_MAX_FREC(mtk::dtSeconds(10))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received pub_additional_info with no suscriptions   on  " << product_code)
                                            , mtk::alPriorError, mtk::alTypeLogicError));
        MTK_END_EXEC_MAX_FREC
        return;
    }

    if(signal_additional_info_update.emit(product_code, full_prod_info.additional_info.Get())==0)  //  not necessary to check if has value  ->1
    {
        MTK_EXEC_MAX_FREC(mtk::dtSeconds(10))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received pub_additional_info on " << product_code << " with no signal receptor"),
                        mtk::alPriorError, mtk::alTypeLogicError));
        MTK_END_EXEC_MAX_FREC
    }
    MTK_EXEC_MAX_FREC(mtk::dtSeconds(1));
        mtk::admin::check_control_fluct(msg.orig_control_fluct);
    MTK_END_EXEC_MAX_FREC
}


void internal_price_manager__factory::on_last_mk_execs_ticker_update(const mtk::prices::msg::ppc& msg)
{
    if(product_code.market !=  msg.market   ||  product_code.product != msg.product)
        throw mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received mk_execs_ticker on " << msg.market << "." << msg.product << " expected product "  << product_code),
                                                    mtk::alPriorCritic, mtk::alTypeNoPermisions);

    auto received = mtk::prices::publ::decompact_prices(msg.compacted_data);
    if(received._1.HasValue() == false)
        return;

    mtk::prices::msg::sub_last_mk_execs_ticker  last_mk_execs_ticker = received._1.Get();


    if(last_mk_execs_ticker.max_last_price.GetDouble()  < last_mk_execs_ticker.last_price.GetDouble())
        throw mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received max price (" << last_mk_execs_ticker.max_last_price << ")  lower than  last price  ("  <<  last_mk_execs_ticker.last_price << ")"),
                                                    mtk::alPriorCritic, mtk::alTypeNoPermisions);
    if(last_mk_execs_ticker.min_last_price.GetDouble() > last_mk_execs_ticker.last_price.GetDouble())
        throw mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received min price (" << last_mk_execs_ticker.min_last_price << ")  bigger than  last price  ("  <<  last_mk_execs_ticker.last_price << ")"),
                                                    mtk::alPriorCritic, mtk::alTypeNoPermisions);

    full_prod_info.last_mk_execs_ticker = last_mk_execs_ticker;        //      ->1

    if(h_last_mk_execs_ticker.isValid()==false)
    {
        //  if no one is interested, the suscription must be canceled
        MTK_EXEC_MAX_FREC(mtk::dtSeconds(10))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received mk_execs_ticker with no suscriptions   on  " << product_code)
                                            , mtk::alPriorError, mtk::alTypeLogicError));
        MTK_END_EXEC_MAX_FREC
        return;
    }

    if(signal_last_mk_execs_ticker.emit(product_code, full_prod_info.last_mk_execs_ticker.Get())==0)  //  not necessary to check if best_prices has value  ->1
    {
        MTK_EXEC_MAX_FREC(mtk::dtSeconds(10))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received mk_execs_ticker on " << product_code << " with no signal receptor"),
                        mtk::alPriorError, mtk::alTypeLogicError));
        MTK_END_EXEC_MAX_FREC
    }
    MTK_EXEC_MAX_FREC(mtk::dtSeconds(1));
        mtk::admin::check_control_fluct(mtk::msg::sub_control_fluct(msg.key, msg.datetime));
    MTK_END_EXEC_MAX_FREC
}



void internal_price_manager__factory::on_res_product_info(const mtk::list<mtk::prices::msg::res_product_info>& res_pi)
{
    const auto  response = res_pi.front().response;
    if(res_pi.front().response.full_product_info.product_code != product_code)
        throw mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("invalid product code on response r/s  " << res_pi.front().response.full_product_info.product_code
                                    << " expected " << product_code), mtk::alPriorCritic, mtk::alTypeNoPermisions);

    //  if it already has prices, they are more recent
    if(full_prod_info.best_prices.HasValue() == false)
        full_prod_info.best_prices = response.full_product_info.best_prices;

    if(full_prod_info.last_mk_execs_ticker.HasValue() == false)
        full_prod_info.last_mk_execs_ticker = response.full_product_info.last_mk_execs_ticker;

    if(full_prod_info.additional_info.HasValue() == false)
        full_prod_info.additional_info = response.full_product_info.additional_info;
    //  if it already has prices, they are more recent



    if(h_best_prices.isValid()  &&  signal_best_prices_update.emit(product_code, full_prod_info.best_prices.Get())==0)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("internal_price_manager__factory  cannot have  signal_best_prices_update with no connections  "
                                << res_pi.front().response.full_product_info.product_code),
                                mtk::alPriorError, mtk::alTypeNoPermisions));

    if(h_last_mk_execs_ticker.isValid()  &&   full_prod_info.last_mk_execs_ticker.HasValue()  &&
                    signal_last_mk_execs_ticker.emit(product_code, full_prod_info.last_mk_execs_ticker.Get())==0)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("internal_price_manager__factory  cannot have  signal_mk_ex_ticker with no connections  "
                                << res_pi.front().response.full_product_info.product_code),
                                mtk::alPriorError, mtk::alTypeNoPermisions));


    if(h_additional_info.isValid()  &&   full_prod_info.additional_info.HasValue()  &&
                    signal_additional_info_update.emit(product_code, full_prod_info.additional_info.Get())==0)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("internal_price_manager__factory  cannot have  signal_additional_info_update with no connections  "
                                << res_pi.front().response.full_product_info.product_code),
                                mtk::alPriorError, mtk::alTypeNoPermisions));
}



void    internal_price_manager__factory::request_full_prod_info(void)
{
    if(full_prod_info_last_request + mtk::dtSeconds(2) <  mtk::dtNowLocal())    //  if less than 2 seconds from last request, we won't request again
    {
        mtk::msg::sub_request_info  request_info = mtk::admin::get_request_info();
        MTK_RECEIVE_MULTI_RESPONSE_THIS(mtk::prices::msg::res_product_info,
                                        mtk::prices::msg::res_product_info::IC_response,
                                        mtk::admin::get_url("client"),
                                        mtk::prices::msg::res_product_info::get_in_subject( request_info.process_info.location.broker_code,
                                                                                            request_info.process_info.location.machine,
                                                                                            request_info.process_info.process_uuid,
                                                                                            request_info.req_id.session_id,
                                                                                            request_info.req_id.req_code),
                                        on_res_product_info,
                                        "price_manager_req_load_product_info")


        mtk::prices::msg::req_product_info   req_load_product_info(request_info, product_code);
        mtk_send_message("client", req_load_product_info);

        full_prod_info_last_request = mtk::dtNowLocal();
    }
}

void decrease_subscriptions_best_prices(void)
{
    get_stats().num_best_prices -= 1;
}

mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ppc> >
internal_price_manager__factory::get_best_prices_suscrp_handle(void)
{
    if(h_best_prices.isValid())
        return  h_best_prices;


    if(get_stats().num_best_prices > 23)        //  therefore  24 subscriptions
    {
        get_signal_too_many_subscriptions_best_prices()->emit();
        return  h_best_prices;
    }

    MTK_QPID_RECEIVER_CONNECT_THIS__WITH_ADDRESS(
                            h_best_prices,
                            mtk::admin::get_url("client"),
                            mtk::prices::msg::ppc::static_get_qpid_address(product_code.market),
                            mtk::prices::msg::ppc::get_in_subject(product_code.product),
                            mtk::prices::msg::ppc,
                            on_price_update);

    get_stats().num_best_prices += 1;
    h_best_prices->signalBeforeDestroy.connect(decrease_subscriptions_best_prices);

    request_full_prod_info();

    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ppc> > result = h_best_prices;
    h_best_prices.DANGEROUS_ThisInstance_NOT_Delete();
    return result;
}


void decrease_subscriptions_last_ex_ticker(void)
{
    get_stats().num_last_exec_ticker -= 1;
}


mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ppc> >
internal_price_manager__factory::get_mk_last_ex_ticker_suscrp_handle(void)
{
    if(h_last_mk_execs_ticker.isValid())
        return  h_last_mk_execs_ticker;


    if(get_stats().num_last_exec_ticker > 23)        //  therefore lets 24 subscriptions
    {
        get_signal_too_many_subscriptions_last_ex_mk_ticker()->emit();
        return  h_last_mk_execs_ticker;
    }

    MTK_QPID_RECEIVER_CONNECT_THIS__WITH_ADDRESS(
                            h_last_mk_execs_ticker,
                            mtk::admin::get_url("client"),
                            mtk::prices::msg::ppc::static_get_qpid_address(product_code.market),
                            mtk::prices::msg::ppc::get_in_subject(product_code.product),
                            mtk::prices::msg::ppc,
                            on_last_mk_execs_ticker_update);

    get_stats().num_last_exec_ticker += 1;
    h_last_mk_execs_ticker->signalBeforeDestroy.connect(decrease_subscriptions_last_ex_ticker);

    request_full_prod_info();


    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ppc> > result = h_last_mk_execs_ticker;
    h_last_mk_execs_ticker.DANGEROUS_ThisInstance_NOT_Delete();
    return result;
}






void decrease_subscriptions_additional_info(void)
{
    get_stats().num_additional_info -= 1;
}


mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::pub_additional_info> >
internal_price_manager__factory::get_addtional_info_suscrp_handle(void)
{
    if(h_additional_info.isValid())
        return  h_additional_info;


    MTK_QPID_RECEIVER_CONNECT_THIS__WITH_ADDRESS(
                            h_additional_info,
                            mtk::admin::get_url("client"),
                            mtk::prices::msg::pub_additional_info::static_get_qpid_address(product_code.market),
                            mtk::prices::msg::pub_additional_info::get_in_subject(product_code.product),
                            mtk::prices::msg::pub_additional_info,
                            on_addtional_info_update);

    get_stats().num_additional_info += 1;
    h_additional_info->signalBeforeDestroy.connect(decrease_subscriptions_additional_info);

    request_full_prod_info();


    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::pub_additional_info> > result = h_additional_info;
    h_additional_info.DANGEROUS_ThisInstance_NOT_Delete();
    return result;
}




mtk::nullable<mtk::prices::msg::sub_best_prices>
internal_price_manager__factory::get_best_prices(void)
{
    if(h_best_prices.isValid()  == false)
        full_prod_info.best_prices = mtk::nullable<mtk::prices::msg::sub_best_prices>();
    return full_prod_info.best_prices;
}



mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>    internal_price_manager__factory::get_last_mk_execs_ticker(void)
{
    if(h_last_mk_execs_ticker.isValid() == false)
        full_prod_info.last_mk_execs_ticker = mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>();
    return full_prod_info.last_mk_execs_ticker;
}


mtk::nullable<mtk::prices::msg::sub_additional_info>    internal_price_manager__factory::get_additional_info(void)
{
    if(h_additional_info.isValid() == false)
        full_prod_info.additional_info = mtk::nullable<mtk::prices::msg::sub_additional_info>();
    return full_prod_info.additional_info;
}




//--------------------------------------------------------------------------------------------------------


price_manager::price_manager(const mtk::msg::sub_product_code&  product_code)
    : ptr(mtk::get_from_factory<internal_price_manager__factory>(product_code))
{
    ptr->signal_best_prices_update.connect(&signal_best_prices_update);
    ptr->signal_last_mk_execs_ticker.connect(&signal_last_mk_execs_ticker);
    ptr->signal_additional_info_update.connect(&signal_additional_info_update);
}


mtk::msg::sub_product_code        price_manager::get_product_code(void) const
{
    return ptr->get_product_code();
}


mtk::nullable<mtk::prices::msg::sub_best_prices>     price_manager::get_best_prices(void)
{
    handle_best_prices_suscrp  =  ptr->get_best_prices_suscrp_handle();

    return  ptr->get_best_prices();
}

mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>     price_manager::get_last_mk_execs_ticker(void)
{
    handle_last_mk_execs_ticker  =  ptr->get_mk_last_ex_ticker_suscrp_handle();

    return  ptr->get_last_mk_execs_ticker();
}

mtk::nullable<mtk::prices::msg::sub_additional_info>     price_manager::get_additional_info(void)
{
    handle_addtional_info  =  ptr->get_addtional_info_suscrp_handle();

    return  ptr->get_additional_info();
}


}   //namespace prices


template<>
inline mtk::CountPtr< mtk::prices::internal_price_manager__factory > create_instance_for_factory(const mtk::msg::sub_product_code&  key, mtk::CountPtr<mtk::prices::internal_price_manager__factory> result)
{
    result = mtk::make_cptr(new mtk::prices::internal_price_manager__factory(key));
    return result;
}


}  // namespace  mtk
