#include "price_manager.h"


#include "support/mtk_string.h"
#include "support/list.hpp"
#include "components/admin/admin.h"
#include "components/request_response.hpp"




namespace
{

    const char*   VERSION       = "2011-04-11";
    const char*   MODIFICATIONS = "           2011-04-11     first version\n";
    
    
    
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



mtk::FixedNumber get_empty_fixed_number_quantity(void)
{
    return mtk::FixedNumber(mtk::fnDouble(0.), mtk::fnDec(0), mtk::fnInc(1));
}
mtk::FixedNumber get_empty_fixed_number_price(void)
{
    return mtk::FixedNumber(mtk::fnDouble(0.), mtk::fnDec(2), mtk::fnInc(1));
}
mtk::prices::msg::sub_price_level   get_emtpy_level_prices(void)
{
    return mtk::prices::msg::sub_price_level(get_empty_fixed_number_price(), get_empty_fixed_number_quantity());
}

mtk::msg::sub_product_code  get_empty_product_code (void)
{
    return mtk::msg::sub_product_code("", "");
}

mtk::prices::msg::pub_best_prices    get_emtpy_best_prices   (void)
{
    return mtk::prices::msg::pub_best_prices(
        get_empty_product_code(),
        mtk::prices::msg::sub_price_deph5(  get_emtpy_level_prices(),
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices()),
        mtk::prices::msg::sub_price_deph5(  get_emtpy_level_prices(),
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices()),
        mtk::admin::get_control_fluct_info()
    );
}


};  //namespace  {








namespace mtk
{

namespace prices
{

price_manager::price_manager(const mtk::msg::sub_product_code&  _product_code)
    :     product_code(_product_code)
        , best_prices(get_emtpy_best_prices())
{
    MTK_QPID_RECEIVER_CONNECT_THIS(
                            h_best_prices,
                            mtk::admin::get_url("client"),
                            "CLITESTING",
                            mtk::prices::msg::pub_best_prices::get_in_subject(product_code.market, product_code.product),
                            mtk::prices::msg::pub_best_prices,
                            on_price_update);

    req_session = mtk::admin::get_qpid_session("client", "CLITESTING");


    mtk::msg::sub_request_info  request_info = mtk::admin::get_request_info();
    MTK_RECEIVE_MULTI_RESPONSE_THIS(mtk::prices::msg::res_product_info,
                                    mtk::prices::msg::res_product_info::IC_response,
                                    req_session,
                                    mtk::prices::msg::res_product_info::get_in_subject( request_info.process_info.location.client_code,
                                                                                        request_info.process_info.location.machine,
                                                                                        request_info.process_info.process_uuid,
                                                                                        request_info.req_id.session_id,
                                                                                        request_info.req_id.req_code),
                                    on_res_product_info,
                                    "price_manager_req_load_product_info")


    mtk::prices::msg::req_prod_info req_load_product_info(request_info, product_code);
    mtk::send_message(req_session, req_load_product_info);
}

price_manager::~price_manager()
{
}




void price_manager::on_price_update(const mtk::prices::msg::pub_best_prices& msg)
{
    best_prices = msg;
    if(signal_best_prices_update.emit(best_prices) ==0)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received update on " << msg.product_code << " with no suscription"), mtk::alPriorError, mtk::alTypeNoPermisions));
    MTK_EXEC_MAX_FREC(mtk::dtSeconds(1));
        mtk::admin::check_control_fluct(msg.orig_control_fluct);
    MTK_END_EXEC_MAX_FREC
}


void price_manager::on_res_product_info(const mtk::list<mtk::prices::msg::res_product_info>& res_pi)
{
    const mtk::prices::msg::pub_best_prices local_best_prices = res_pi.front().response.best_prices;
    if(local_best_prices.product_code != product_code)
        throw mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("invalid product code on response r/s  " << local_best_prices.product_code << " " << product_code), mtk::alPriorError, mtk::alTypeNoPermisions);
    best_prices = local_best_prices;
    if(signal_best_prices_update.emit(best_prices) ==0)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "price_manager", MTK_SS("received load " << local_best_prices.product_code << " with no suscription"), mtk::alPriorError, mtk::alTypeNoPermisions));
}




}   //namespace prices

}  // namespace  mtk
