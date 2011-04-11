#include "price_manager.h"


#include "support/mtk_string.h"
#include "support/list.hpp"
#include "components/admin/admin.h"




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
    return mtk::msg::sub_product_code(mtk::msg::sub_sys_product_code(mtk::msg::sub_single_product_code("", ""), ""),
                                      mtk::nullable<mtk::msg::sub_adic_product_code>());
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
                            mtk::prices::msg::pub_best_prices::get_in_subject(product_code.sys_code.market, product_code.sys_code.product),
                            mtk::prices::msg::pub_best_prices,
                            on_price_update)
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






}   //namespace prices

}  // namespace  mtk
