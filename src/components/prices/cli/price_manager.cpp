#include "price_manager.h"


#include "support/mtk_string.h"
#include "support/list.hpp"
#include "components/admin/admin.h"
#include "components/request_response.hpp"




namespace
{

    const char*   VERSION       =   "2011-08-04";
    const char*   MODIFICATIONS =   "           2011-04-11     first version\n"
                                    "           2011-08-04     updated to prices publishing protocol and correct managment of factory\n"
                                    ;



    void command_version(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(MTK_SS(__FILE__ << ":  " << VERSION));
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
        mtk::admin::register_command("price_manager",  "ver",   "")->connect(command_version);
        mtk::admin::register_command("price_manager",  "modifs",   "")->connect(command_modifications);
    }

    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)
}




//  support functions

namespace {




};  //namespace  {








namespace mtk
{

namespace prices
{




internal_price_manager__factory::internal_price_manager__factory(const mtk::msg::sub_product_code&  _product_code)
    :     product_code(_product_code)
        , full_prod_info(mtk::prices::msg::__internal_get_default((mtk::prices::msg::sub_full_product_info_optionals*) 0))
{
}

internal_price_manager__factory::~internal_price_manager__factory()
{
}




void internal_price_manager__factory::on_price_update(const mtk::prices::msg::pub_best_prices& msg)
{
    if(product_code !=  msg.product_code)
        throw mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received update on " << msg.product_code << " expected product "  << product_code),
                                                    mtk::alPriorCritic, mtk::alTypeNoPermisions);

    if(full_prod_info.best_prices.HasValue()   &&   full_prod_info.best_prices.Get() == msg.best_prices)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(30))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received update with no changes  " << msg.product_code
                                            << full_prod_info.best_prices << " ==  " << msg.best_prices ), mtk::alPriorError, mtk::alTypeNoPermisions));
        MTK_END_EXEC_MAX_FREC
    }


    full_prod_info.best_prices = msg.best_prices;        //      ->1

    if(h_best_prices.isValid()==false)
    {
        //  if no one is interested, the suscription must be canceled
        MTK_EXEC_MAX_FREC(mtk::dtSeconds(10))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received update with no suscriptions   on  " << msg.product_code)
                                            , mtk::alPriorError, mtk::alTypeLogicError));
        MTK_END_EXEC_MAX_FREC
        return;
    }

    if(signal_best_prices_update.emit(product_code, full_prod_info.best_prices.Get()) ==0)  //  not necessary to check if best_prices has value  ->1
    {
        MTK_EXEC_MAX_FREC(mtk::dtSeconds(10))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received update on " << msg.product_code << " with no signal receptor"),
                        mtk::alPriorError, mtk::alTypeLogicError));
        MTK_END_EXEC_MAX_FREC
    }
    MTK_EXEC_MAX_FREC(mtk::dtSeconds(1));
        mtk::admin::check_control_fluct(msg.orig_control_fluct);
    MTK_END_EXEC_MAX_FREC
}


void internal_price_manager__factory::on_res_product_info(const mtk::list<mtk::prices::msg::res_product_info>& res_pi)
{
    const mtk::prices::msg::sub_best_prices local_best_prices = res_pi.front().response.full_product_info.best_prices;
    if(res_pi.front().response.full_product_info.product_code != product_code)
        throw mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("invalid product code on response r/s  " << res_pi.front().response.full_product_info.product_code
                                    << " expected " << product_code), mtk::alPriorCritic, mtk::alTypeNoPermisions);

    if(full_prod_info.best_prices.HasValue() == false)
        full_prod_info.best_prices = local_best_prices;
        //  if it already has prices, they are more recent



    if(signal_best_prices_update.emit(product_code, full_prod_info.best_prices.Get())==0)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("internal_price_manager__factory  cannot have  signal_best_prices_update with no connections  "
                                << res_pi.front().response.full_product_info.product_code),
                                mtk::alPriorError, mtk::alTypeNoPermisions));
}




mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::pub_best_prices> >
internal_price_manager__factory::get_best_prices_suscrp_handle(void)
{
    if(h_best_prices.isValid())
        return  h_best_prices;



    MTK_QPID_RECEIVER_CONNECT_THIS__WITH_ADDRESS(
                            h_best_prices,
                            mtk::admin::get_url("client"),
                            mtk::prices::msg::pub_best_prices::static_get_qpid_address(product_code.market),
                            mtk::prices::msg::pub_best_prices::get_in_subject(product_code.market, product_code.product),
                            mtk::prices::msg::pub_best_prices,
                            on_price_update);



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

    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::pub_best_prices> > result = h_best_prices;
    h_best_prices.DANGEROUS_ThisInstance_NOT_Delete();
    return result;
}

mtk::nullable<mtk::prices::msg::sub_best_prices>
internal_price_manager__factory::get_best_prices(void) const
{
    if(h_best_prices.isValid())
        return full_prod_info.best_prices;
    else
        return  mtk::nullable<mtk::prices::msg::sub_best_prices>();
}




//--------------------------------------------------------------------------------------------------------


price_manager::price_manager(const mtk::msg::sub_product_code&  product_code)
    : ptr(mtk::get_from_factory<internal_price_manager__factory>(product_code))
{
    ptr->signal_best_prices_update.connect(&signal_best_prices_update);
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



}   //namespace prices


template<>
inline mtk::CountPtr< mtk::prices::internal_price_manager__factory > create_instance_for_factory(const mtk::msg::sub_product_code&  key, mtk::CountPtr<mtk::prices::internal_price_manager__factory> result)
{
    result = mtk::make_cptr(new mtk::prices::internal_price_manager__factory(key));
    return result;
}


}  // namespace  mtk
