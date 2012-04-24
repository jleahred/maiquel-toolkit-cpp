#include "orders_book.h"
#include "support/mtk_string.h"
#include "mtk_qpid/mtk_qpid.h"
#include "support/list.hpp"
#include "support/map.hpp"

#include "components/prices/msg_prices.h"
#include "components/prices/msg_ps_prices.h"
#include "components/admin/admin.h"
#include "components/prices/prices_publication.h"


#include "msg_config_data.h"







namespace {
    const char*   VERSION = "2011-06-10";

    const char*   MODIFICATIONS =
                        "           2010-06-10     Added command print orders queue\n"
                        "           2010-12-01     first version\n";


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
    mtk::admin::register_command("__GLOBAL__",    "ver",   "")->connect(command_version);
    mtk::admin::register_command("__GLOBAL__",    "modifs","")->connect(command_modifications);


    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)
}

};       //  anonymous namespace  to register "static" commnads





namespace {
mtk::CountPtr<mtk::map<std::string, emarket::sub_product_config> >
get_map_product_config(void)
{
    static auto  map_product_config = mtk::make_cptr(new mtk::map<std::string, emarket::sub_product_config>);
    return map_product_config;
}

mtk::tuple<mtk::fnExt, mtk::fnExt>
get_ext_price_quantity_for_product(const std::string&  product_name)
{
    auto it = get_map_product_config()->find(product_name);
    if(it == get_map_product_config()->end())
        throw mtk::Alarm(MTK_HERE, "orders_book", MTK_SS("product not registered " << product_name) , mtk::alPriorCritic, mtk::alTypeLogicError);
    return mtk::make_tuple(mtk::fnExt(it->second.price_fnext),
                    mtk::fnExt(mtk::fnDec(0), mtk::fnInc(1)));
}
}


//----------------------------------------------------------------------------------------
//      o r d e r s _ i n _ p r o d u c t _ q u e u e
//----------------------------------------------------------------------------------------

class orders_in_product_queue
{
public:
    mtk::list<mtk::CountPtr<ord_ls> >  bid_queue;
    mtk::list<mtk::CountPtr<ord_ls> >  ask_queue;
    const int                          adjust_product_comparation;

public:

    void add_order  (mtk::CountPtr<ord_ls> order);
    void del_order  (mtk::CountPtr<ord_ls> order);
    void modif_order(mtk::CountPtr<ord_ls> order);
    void check_execs(const mtk::msg::sub_product_code& product_code);     //  here will be generated the output  cf_ex if so
    void update_prices(const mtk::msg::sub_product_code& product_code);

    orders_in_product_queue()
        : bid_queue(), ask_queue(), adjust_product_comparation(1) {}

private:
    mtk::tuple<mtk::list<mtk::CountPtr<ord_ls> >*/*queue*/, int/*adjust_comparation*/> get_queue_adjust_comparation(mtk::CountPtr<ord_ls> order);

};






//----------------------------------------------------------------------------------------
//      i n t e r n a l _ o r d e r s _ b o o k
//----------------------------------------------------------------------------------------
class internal_orders_book : public mtk::SignalReceptor
{
typedef internal_orders_book  CLASS_NAME;

    mtk::map<mtk::trd::msg::sub_order_id, mtk::CountPtr<ord_ls> >    orders_by_id;
    mtk::map<mtk::msg::sub_product_code, orders_in_product_queue >   queue_by_product;

    mtk::CountPtr<ord_ls> cached_last_request;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ps_req_init_prod_info__to_publisher> > hqpid_ps_req_init_prod_info;

public:
    internal_orders_book();



    //  in  check_request->book_orders
    void oms_RQ_NW_LS (const mtk::trd::msg::oms_RQ_NW_LS& rq);
    void oms_RQ_MD_LS (const mtk::trd::msg::oms_RQ_MD_LS& rq);
    void oms_RQ_CC_LS (const mtk::trd::msg::oms_RQ_CC_LS& rq);

    void oms_RQ_NW_MK (const mtk::trd::msg::oms_RQ_NW_MK& rq);

    void oms_RQ_NW_SM (const mtk::trd::msg::oms_RQ_NW_SM& rq);
    void oms_RQ_MD_SM (const mtk::trd::msg::oms_RQ_MD_SM& rq);
    void oms_RQ_CC_SM (const mtk::trd::msg::oms_RQ_CC_SM& rq);

    void oms_RQ_NW_SL (const mtk::trd::msg::oms_RQ_NW_SL& rq);
    void oms_RQ_MD_SL (const mtk::trd::msg::oms_RQ_MD_SL& rq);
    void oms_RQ_CC_SL (const mtk::trd::msg::oms_RQ_CC_SL& rq);


    void add_order    (const mtk::trd::msg::CF_XX_LS& order_info);
    void del_order    (const mtk::trd::msg::CF_XX_LS& order_info);
    void modif_order  (const mtk::trd::msg::CF_XX_LS& order_info);
    void check_execs  (const mtk::trd::msg::CF_XX_LS& order_info);     //  here will be generated the output  cf_ex if so
    void update_prices(const mtk::trd::msg::CF_XX_LS& order_info);

    void add_product  (const emarket::sub_product_config&  product_config);


    void command_print_queue(const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines);

    void  on_ps_req_init_prod_info(const mtk::prices::msg::ps_req_init_prod_info__to_publisher&  ps_req_init_prod_info);
    void  publish_all_product_full_info(const mtk::msg::sub_process_info&);
};


internal_orders_book::internal_orders_book()
{
    MTK_CONNECT_THIS(*mtk::admin::register_command("ob",            "print_queue",   ""), command_print_queue)


    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_ps_req_init_prod_info,
                            mtk::admin::get_url("server"),
                            mtk::prices::msg::ps_req_init_prod_info__to_publisher::get_in_subject("MARKET"),
                            mtk::prices::msg::ps_req_init_prod_info__to_publisher,
                            on_ps_req_init_prod_info)

}

void internal_orders_book::command_print_queue(const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines)
{
    for(auto it_queue_by_product = queue_by_product.begin(); it_queue_by_product != queue_by_product.end(); ++it_queue_by_product)
    {
        //        mtk::list<mtk::CountPtr<ord_ls> >  bid_queue;
        //        mtk::list<mtk::CountPtr<ord_ls> >  ask_queue;
        response_lines.push_back(MTK_SS(it_queue_by_product->first << "   ->  BIDS"));
        for(auto it_orders = it_queue_by_product->second.bid_queue.begin(); it_orders != it_queue_by_product->second.bid_queue.end(); ++it_orders)
        {
            std::string big_response = MTK_SS((*it_orders)->last_confirmation());
            mtk::vector<std::string> v_big_response = mtk::s_split(big_response, "{");
            for(unsigned i = 0; i< v_big_response.size(); ++i)
                response_lines.push_back(MTK_SS("       { "  <<  v_big_response[i]));
        }
        response_lines.push_back(MTK_SS(it_queue_by_product->first << "   ->  ASKS"));
        for(auto it_orders = it_queue_by_product->second.ask_queue.begin(); it_orders != it_queue_by_product->second.ask_queue.end(); ++it_orders)
        {
            std::string big_response = MTK_SS((*it_orders)->last_confirmation());
            mtk::vector<std::string> v_big_response = mtk::s_split(big_response, "{");
            for(unsigned i = 0; i< v_big_response.size(); ++i)
                response_lines.push_back(MTK_SS("       { "  <<  v_big_response[i]));
        }
    }
}


void  internal_orders_book::on_ps_req_init_prod_info(const mtk::prices::msg::ps_req_init_prod_info__to_publisher&  ps_req_init_prod_info)
{
    if(ps_req_init_prod_info.market == "MARKET")
        publish_all_product_full_info(ps_req_init_prod_info.process_info);
    else
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "orders_book", MTK_SS("received request on invalid market code" << ps_req_init_prod_info), mtk::alPriorError, mtk::alTypeNoPermisions));
}








//------------------------------------------------------------------------------------------
//  o r d e r s _ b o o k
//
//  implementation
//------------------------------------------------------------------------------------------

orders_book::orders_book()
    : ptr(new internal_orders_book())
{
}

orders_book::~orders_book()
{
    delete ptr;
}





//  in  check_request->book_orders
void orders_book::oms_RQ_NW_LS(const mtk::trd::msg::oms_RQ_NW_LS& rq)
{
    ptr->oms_RQ_NW_LS(rq);
}
void orders_book::oms_RQ_MD_LS(const mtk::trd::msg::oms_RQ_MD_LS& rq)
{
    ptr->oms_RQ_MD_LS(rq);
}
void orders_book::oms_RQ_CC_LS(const mtk::trd::msg::oms_RQ_CC_LS& rq)
{
    ptr->oms_RQ_CC_LS(rq);
}



void orders_book::oms_RQ_NW_MK(const mtk::trd::msg::oms_RQ_NW_MK& rq)
{
    ptr->oms_RQ_NW_MK(rq);
}




void orders_book::oms_RQ_NW_SM(const mtk::trd::msg::oms_RQ_NW_SM& rq)
{
    ptr->oms_RQ_NW_SM(rq);
}
void orders_book::oms_RQ_MD_SM(const mtk::trd::msg::oms_RQ_MD_SM& rq)
{
    ptr->oms_RQ_MD_SM(rq);
}
void orders_book::oms_RQ_CC_SM(const mtk::trd::msg::oms_RQ_CC_SM& rq)
{
    ptr->oms_RQ_CC_SM(rq);
}


void orders_book::oms_RQ_NW_SL(const mtk::trd::msg::oms_RQ_NW_SL& rq)
{
    ptr->oms_RQ_NW_SL(rq);
}
void orders_book::oms_RQ_MD_SL(const mtk::trd::msg::oms_RQ_MD_SL& rq)
{
    ptr->oms_RQ_MD_SL(rq);
}
void orders_book::oms_RQ_CC_SL(const mtk::trd::msg::oms_RQ_CC_SL& rq)
{
    ptr->oms_RQ_CC_SL(rq);
}






void orders_book::add_product (const emarket::sub_product_config&  product_config)
{
    get_map_product_config()->insert(std::make_pair(product_config.product_name, product_config));
    ptr->add_product(product_config);
}






//------------------------------------------------------------------------------------------
//
//  i n t e r n a l _ o r d e r s _ b o o k
//
//  implementation
//------------------------------------------------------------------------------------------

#define SET_OR_INIT_CACHED_LAST_REQUEST\
    cached_last_request = orders_by_id[rq.invariant.order_id];    \
    if (cached_last_request.isValid()==false)     \
    {      \
        cached_last_request = make_cptr(new ord_ls());       \
        orders_by_id[rq.invariant.order_id] = cached_last_request;      \
        cached_last_request->sig_cli_cf_nw.connect(&send_to_client);    \
        cached_last_request->sig_cli_cf_md.connect(&send_to_client);    \
        cached_last_request->sig_cli_cf_cc.connect(&send_to_client);    \
        cached_last_request->sig_cli_rj_nw.connect(&send_to_client);    \
        cached_last_request->sig_cli_rj_md.connect(&send_to_client);    \
        cached_last_request->sig_cli_rj_cc.connect(&send_to_client);    \
        cached_last_request->sig_cli_cf_ex.connect(&send_to_client);    \
        cached_last_request->sig_cli_cf_exlk.connect(&send_to_client);    \
        MTK_CONNECT_THIS(cached_last_request->sig_ob_add_order  , add_order);    \
        MTK_CONNECT_THIS(cached_last_request->sig_ob_modif_order, modif_order);    \
        MTK_CONNECT_THIS(cached_last_request->sig_ob_del_order  , del_order);    \
        MTK_CONNECT_THIS(cached_last_request->sig_ob_check_execs, check_execs);    \
        MTK_CONNECT_THIS(cached_last_request->sig_ob_update_prices, update_prices);    \
    }




//  connect order signal to confirmations
template<typename T>
void send_to_client (const T& toclient)
{
    mtk_send_message("client", toclient);
    std::cout << mtk::dtNowLocal() <<"  response sent to client " << toclient.get_message_type_as_string() <<  std::endl;
}



//  in  check_request->book_orders
void internal_orders_book::oms_RQ_NW_LS(const mtk::trd::msg::oms_RQ_NW_LS& rq)
{
    SET_OR_INIT_CACHED_LAST_REQUEST
    cached_last_request->cli_rq_nw(rq);
}
void internal_orders_book::oms_RQ_MD_LS(const mtk::trd::msg::oms_RQ_MD_LS& rq)
{
    SET_OR_INIT_CACHED_LAST_REQUEST
    cached_last_request->cli_rq_md(rq);
}
void internal_orders_book::oms_RQ_CC_LS(const mtk::trd::msg::oms_RQ_CC_LS& rq)
{
    SET_OR_INIT_CACHED_LAST_REQUEST
    cached_last_request->cli_rq_cc(rq);
}




template<typename  ORDER_TYPE>      //  ie.  mtk::trd::msg::oms_RQ_NW_MK
mtk::trd::msg::sub_total_executions     get_empty_total_executions(const ORDER_TYPE& rq)
{
        mtk::Double                             sum_price_quantity {0.};
        mtk::FixedNumber                        acc_quantity(rq.request_pos.quantity);
        acc_quantity.SetIntCode(0);
        mtk::FixedNumber                        remaining_quantity(rq.request_pos.quantity);

        return mtk::trd::msg::sub_total_executions     (sum_price_quantity, acc_quantity, remaining_quantity);
}



void internal_orders_book::oms_RQ_NW_MK(const mtk::trd::msg::oms_RQ_NW_MK& rq)
{
    static int counter=0;
    ++counter;

    {
        mtk::trd::msg::CF_XX        cf_xx       (rq.invariant, MTK_SS("MK_" << counter), rq.request_info.req_id, get_empty_total_executions(rq), "", mtk::msg::sub_control_fluct("EMARKET.TRD", mtk::dtNowLocal()));
        mtk::trd::msg::CF_XX_MK     cf_xx_mk    (cf_xx, rq.request_pos);
        mtk::trd::msg::CF_NW_MK     cf_nw_mk    (cf_xx_mk);

        mtk_send_message("client", cf_nw_mk);
    }

    {
        mtk::Double                             sum_price_quantity {mtk::Double(100) * rq.request_pos.quantity.GetDouble()};
        mtk::FixedNumber                        acc_quantity{rq.request_pos.quantity};
        mtk::FixedNumber                        remaining_quantity(rq.request_pos.quantity);
        remaining_quantity.SetIntCode(0);
        mtk::trd::msg::sub_total_executions     total_executions(sum_price_quantity, acc_quantity, remaining_quantity);

        mtk::msg::sub_request_id        rq_id       ("MK_EX",  MTK_SS(counter));
        mtk::trd::msg::CF_XX            cf_xx       (rq.invariant, MTK_SS("MK_" << counter), rq_id, total_executions, "", mtk::msg::sub_control_fluct("EMARKET.TRD", mtk::dtNowLocal()));
        mtk::trd::msg::CF_XX_MK         cf_xx_mk    (cf_xx, rq.request_pos);
        mtk::trd::msg::CF_NW_MK         cf_nw_mk    (cf_xx_mk);
        mtk::trd::msg::sub_exec_conf    exec_conf   (MTK_SS("MK_exid" << counter), mtk::FixedNumber(mtk::fnDouble(100.), mtk::fnDec(2), mtk::fnInc(1)), rq.request_pos.quantity);
        mtk::trd::msg::CF_EX_MK         cf_ex_mk    (cf_xx_mk, exec_conf);

        mtk_send_message("client", cf_ex_mk);
    }
}





void internal_orders_book::oms_RQ_NW_SM(const mtk::trd::msg::oms_RQ_NW_SM& rq)
{
    static int counter=0;
    ++counter;

    mtk::trd::msg::CF_XX        cf_xx       (rq.invariant, MTK_SS("MK_" << counter), rq.request_info.req_id, get_empty_total_executions(rq), "", mtk::msg::sub_control_fluct("EMARKET.TRD", mtk::dtNowLocal()));
    mtk::trd::msg::CF_XX_SM     cf_xx_sm    (cf_xx, rq.request_pos);
    mtk::trd::msg::CF_NW_SM     cf_nw_sm    (cf_xx_sm);

    mtk_send_message("client", cf_nw_sm);

    if(rq.request_pos.cli_ref == "t")
    {
        mtk::trd::msg::CF_TR_SM     cf_tr_sm    (cf_xx_sm);
        cf_tr_sm.req_id.req_code = MTK_SS(++counter);
        cf_tr_sm.req_id.session_id = "MK:TR";
        mtk_send_message("client", cf_tr_sm);


        static int ex_counter=0;
        mtk::trd::msg::sub_exec_conf    exec_conf(MTK_SS("ex:" << ex_counter), rq.request_pos.stop_price, rq.request_pos.quantity);
        mtk::trd::msg::sub_position_mk  sub_position_mk(rq.request_pos.quantity, rq.request_pos.cli_ref);
        mtk::trd::msg::CF_XX_MK         cf_xx_mk (cf_xx, sub_position_mk);
        cf_xx_mk.req_id.session_id = "MK:EX";
        cf_xx_mk.total_execs.acc_quantity = rq.request_pos.quantity;
        cf_xx_mk.total_execs.remaining_qty.SetIntCode(0);
        cf_xx_mk.total_execs.sum_price_by_qty = exec_conf.price.GetDouble() * exec_conf.quantity.GetDouble();
        mtk::trd::msg::CF_EX_MK         cf_ex_mk (cf_xx_mk, exec_conf);
        mtk_send_message("client", cf_ex_mk);
    }
}
void internal_orders_book::oms_RQ_MD_SM(const mtk::trd::msg::oms_RQ_MD_SM& rq)
{
    static int counter=0;
    ++counter;

    mtk::trd::msg::CF_XX        cf_xx       (rq.invariant, MTK_SS("MK_" << counter), rq.request_info.req_id, get_empty_total_executions(rq), "", mtk::msg::sub_control_fluct("EMARKET.TRD", mtk::dtNowLocal()));
    mtk::trd::msg::CF_XX_SM     cf_xx_sm    (cf_xx, rq.request_pos);
    mtk::trd::msg::CF_MD_SM     cf_md_sm    (cf_xx_sm);

    mtk_send_message("client", cf_md_sm);

    if(rq.request_pos.cli_ref == "t")
    {
        mtk::trd::msg::CF_TR_SM     cf_tr_sm    (cf_xx_sm);
        cf_tr_sm.req_id.req_code = MTK_SS(++counter);
        cf_tr_sm.req_id.session_id = "MK:TR";
        mtk_send_message("client", cf_tr_sm);



        static int ex_counter=0;
        mtk::trd::msg::sub_exec_conf    exec_conf(MTK_SS("exm:" << ex_counter), rq.request_pos.stop_price, rq.request_pos.quantity);
        mtk::trd::msg::sub_position_mk  sub_position_mk(rq.request_pos.quantity, rq.request_pos.cli_ref);
        mtk::trd::msg::CF_XX_MK         cf_xx_mk (cf_xx, sub_position_mk);
        cf_xx_mk.req_id.session_id = "MK:EX";
        cf_xx_mk.total_execs.acc_quantity = rq.request_pos.quantity;
        cf_xx_mk.total_execs.remaining_qty.SetIntCode(0);
        cf_xx_mk.total_execs.sum_price_by_qty = exec_conf.price.GetDouble() * exec_conf.quantity.GetDouble();
        mtk::trd::msg::CF_EX_MK         cf_ex_mk (cf_xx_mk, exec_conf);
        mtk_send_message("client", cf_ex_mk);
    }

}
void internal_orders_book::oms_RQ_CC_SM(const mtk::trd::msg::oms_RQ_CC_SM& rq)
{
    static int counter=0;
    ++counter;

    mtk::trd::msg::CF_XX        cf_xx       (rq.invariant, MTK_SS("MK_" << counter), rq.request_info.req_id, get_empty_total_executions(rq), "", mtk::msg::sub_control_fluct("EMARKET.TRD", mtk::dtNowLocal()));
    mtk::trd::msg::CF_XX_SM     cf_xx_sm    (cf_xx, rq.request_pos);
    mtk::trd::msg::CF_CC_SM     cf_cc_sm    (cf_xx_sm);

    mtk_send_message("client", cf_cc_sm);
}





void internal_orders_book::oms_RQ_NW_SL(const mtk::trd::msg::oms_RQ_NW_SL& rq)
{
    static int counter=0;
    ++counter;

    mtk::trd::msg::CF_XX        cf_xx       (rq.invariant, MTK_SS("MK_" << counter), rq.request_info.req_id, get_empty_total_executions(rq), "", mtk::msg::sub_control_fluct("EMARKET.TRD", mtk::dtNowLocal()));
    mtk::trd::msg::CF_XX_SL     cf_xx_sl    (cf_xx, rq.request_pos);
    mtk::trd::msg::CF_NW_SL     cf_nw_sl    (cf_xx_sl);

    mtk_send_message("client", cf_nw_sl);

    if(rq.request_pos.cli_ref == "t")
    {
        mtk::trd::msg::CF_TR_SL     cf_tr_sl    (cf_xx_sl);
        cf_tr_sl.req_id.req_code = MTK_SS(++counter);
        cf_tr_sl.req_id.session_id = "MK:TR";
        mtk_send_message("client", cf_tr_sl);
    }
}
void internal_orders_book::oms_RQ_MD_SL(const mtk::trd::msg::oms_RQ_MD_SL& rq)
{
    static int counter=0;
    ++counter;

    mtk::trd::msg::CF_XX        cf_xx       (rq.invariant, MTK_SS("MK_" << counter), rq.request_info.req_id, get_empty_total_executions(rq), "", mtk::msg::sub_control_fluct("EMARKET.TRD", mtk::dtNowLocal()));
    mtk::trd::msg::CF_XX_SL     cf_xx_sl    (cf_xx, rq.request_pos);
    mtk::trd::msg::CF_MD_SL     cf_md_sl    (cf_xx_sl);

    mtk_send_message("client", cf_md_sl);

    if(rq.request_pos.cli_ref == "t")
    {
        mtk::trd::msg::CF_TR_SL     cf_tr_sl    (cf_xx_sl);
        cf_tr_sl.req_id.req_code = MTK_SS(++counter);
        cf_tr_sl.req_id.session_id = "MK:TR";
        mtk_send_message("client", cf_tr_sl);
    }

}
void internal_orders_book::oms_RQ_CC_SL(const mtk::trd::msg::oms_RQ_CC_SL& rq)
{
    static int counter=0;
    ++counter;

    mtk::trd::msg::CF_XX        cf_xx       (rq.invariant, MTK_SS("MK_" << counter), rq.request_info.req_id, get_empty_total_executions(rq), "", mtk::msg::sub_control_fluct("EMARKET.TRD", mtk::dtNowLocal()));
    mtk::trd::msg::CF_XX_SL     cf_xx_sl    (cf_xx, rq.request_pos);
    mtk::trd::msg::CF_CC_SL     cf_cc_sl    (cf_xx_sl);

    mtk_send_message("client", cf_cc_sl);
}








#define CHECK_CACHTED_ORDER(ACTION)  \
    if (cached_last_request.isValid()==false)  \
        throw mtk::Alarm(MTK_HERE, "orders_book::" ACTION "_order", MTK_SS("empty cached_last_request" << order_info), mtk::alPriorCritic, mtk::alTypeNoPermisions);  \
    if (cached_last_request->last_request().HasValue() == false)  \
        throw mtk::Alarm(MTK_HERE, "orders_book::" ACTION "_order", MTK_SS("empty cached_last_request request" << order_info), mtk::alPriorCritic, mtk::alTypeNoPermisions);  \
    if (cached_last_request->last_confirmation().HasValue() == false)  \
        throw mtk::Alarm(MTK_HERE, "orders_book::" ACTION "_order", MTK_SS("empty cached_last_request confirmation " << order_info), mtk::alPriorCritic, mtk::alTypeNoPermisions);  \
    else if (cached_last_request->last_request().Get().invariant.order_id != order_info.invariant.order_id)  \
        throw mtk::Alarm(MTK_HERE, "orders_book::" ACTION "_order", MTK_SS("cached_last_request doesn't math with order to " ACTION   \
                        << cached_last_request->last_request().Get() << "  " << order_info), mtk::alPriorCritic, mtk::alTypeNoPermisions);

void internal_orders_book::add_order  (const mtk::trd::msg::CF_XX_LS& order_info)
{
    CHECK_CACHTED_ORDER("add")
    //this->queue_by_product[cached_last_request->last_confirmation().Get().invariant.product_code].add_order(cached_last_request);
    //  if order doesn't exists, it will not be created
    mtk::msg::sub_product_code  pc(cached_last_request->last_confirmation().Get().invariant.product_code);
    if(this->queue_by_product.find(pc) ==  this->queue_by_product.end())
        mtk::Alarm(MTK_HERE, "emarket:obook", MTK_SS("Received invalid product code on add_order " << pc), mtk::alPriorError, mtk::alTypeLogicError);
    else
        this->queue_by_product[pc].add_order(cached_last_request);
}

void internal_orders_book::del_order  (const mtk::trd::msg::CF_XX_LS& order_info)
{
    CHECK_CACHTED_ORDER("del")
    this->queue_by_product[cached_last_request->last_confirmation().Get().invariant.product_code].del_order(cached_last_request);
}

void internal_orders_book::modif_order  (const mtk::trd::msg::CF_XX_LS& order_info)
{
    CHECK_CACHTED_ORDER("modif")
    //this->queue_by_product[cached_last_request->last_confirmation().Get().invariant.product_code].modif_order(cached_last_request);
    //  if order doesn't exists, it will not be created
    mtk::msg::sub_product_code  pc(cached_last_request->last_confirmation().Get().invariant.product_code);
    if(this->queue_by_product.find(pc) ==  this->queue_by_product.end())
        mtk::Alarm(MTK_HERE, "emarket:obook", MTK_SS("Received invalid product code on modif_order " << pc), mtk::alPriorError, mtk::alTypeLogicError);
    else
        this->queue_by_product[pc].modif_order(cached_last_request);
}

void internal_orders_book::check_execs  (const mtk::trd::msg::CF_XX_LS& order_info)
{
    CHECK_CACHTED_ORDER("check_execs")
    this->queue_by_product[cached_last_request->last_confirmation().Get().invariant.product_code].check_execs(cached_last_request->last_confirmation().Get().invariant.product_code);
}

void internal_orders_book::update_prices(const mtk::trd::msg::CF_XX_LS& /*order_info*/)
{
    this->queue_by_product[cached_last_request->last_confirmation().Get().invariant.product_code].update_prices(cached_last_request->last_confirmation().Get().invariant.product_code);
}


void internal_orders_book::add_product  (const emarket::sub_product_config&  product_config)
{
    this->queue_by_product.insert(std::make_pair(mtk::msg::sub_product_code("MARKET", product_config.product_name), orders_in_product_queue()));
}


//----------------------------------------------------------------------------------------
//      o r d e r s _ i n _ p r o d u c t _ q u e u e
//
//  implementation
//----------------------------------------------------------------------------------------



mtk::tuple<mtk::list<mtk::CountPtr<ord_ls> >*/*queue*/, int/*adjust_comparation*/> orders_in_product_queue::get_queue_adjust_comparation(mtk::CountPtr<ord_ls> order)
{
    if      (order->last_confirmation().Get().invariant.side == mtk::trd::msg::buy)
    {
        return mtk::make_tuple(&bid_queue, 1);
    }
    else if (order->last_confirmation().Get().invariant.side == mtk::trd::msg::sell)
    {
        return mtk::make_tuple(&ask_queue,-1);
    }
    else
        throw mtk::Alarm(MTK_HERE, "orders_in_product_queue::", MTK_SS("invalid order side " << order->last_request()), mtk::alPriorCritic, mtk::alTypeNoPermisions);
}

void orders_in_product_queue::add_order(mtk::CountPtr<ord_ls> order)
{
    mtk::list<mtk::CountPtr<ord_ls> >* queue=0;
    int adjust_comparation = 1;
    get_queue_adjust_comparation(order).assign(queue, adjust_comparation);

    adjust_comparation *= this->adjust_product_comparation;

    // iterate queue looking for position
    mtk::list<mtk::CountPtr<ord_ls> >::iterator it = queue->begin();
    while (it != queue->end())
    {
        if ( mtk::Double((*it)->last_confirmation().Get().market_pos.price.GetDouble()*adjust_comparation)
             <
             mtk::Double(order->last_confirmation().Get().market_pos.price.GetDouble()*adjust_comparation))
        //  atention: if they are equal, the order to add, will be back
        //  GetDouble returns a mtk::Double (comparations safe)
        //  Here, we let diferent extended on prices
        {
            queue->insert(it, order);
            break;
        }
        ++it;
    }
    if (it == queue->end())
        queue->insert(it, order);
}

void orders_in_product_queue::del_order(mtk::CountPtr<ord_ls> order)
{
    mtk::list<mtk::CountPtr<ord_ls> >* queue=0;
    int adjust_comparation = 1;
    get_queue_adjust_comparation(order).assign(queue, adjust_comparation);

    // iterate queue looking for position
    mtk::list<mtk::CountPtr<ord_ls> >::iterator it = queue->begin();
    while (it != queue->end())
    {
        if ((*it)->last_confirmation().Get().invariant.order_id  ==  order->last_confirmation().Get().invariant.order_id)
        {
            queue->erase(it);
            break;
        }
        ++it;
    }
}

void orders_in_product_queue::modif_order(mtk::CountPtr<ord_ls> order)
{
    del_order(order);
    add_order(order);
}


mtk::tuple<mtk::FixedNumber, int> get_price (const mtk::CountPtr<ord_ls>& order)
{
    return mtk::make_tuple(order->last_confirmation().Get().market_pos.price, order->sequence());
}
mtk::FixedNumber get_pending_quantity (const mtk::CountPtr<ord_ls>& order)
{
    return order->last_confirmation().Get().total_execs.remaining_qty;
}
mtk::FixedNumber min(const mtk::FixedNumber& a, const mtk::FixedNumber& b)
{
    if (a<b)    return a;
    else        return b;
}

mtk::FixedNumber get_exec_price(const mtk::tuple<mtk::FixedNumber, int>& b, const mtk::tuple<mtk::FixedNumber, int>& s)
{
    if (b._1<s._1)   return b._0;
    else             return s._0;
}

void orders_in_product_queue::check_execs(const mtk::msg::sub_product_code& product_code)
{
    static int ex_counter=0;
    if (bid_queue.size() > 0  &&  ask_queue.size() > 0)
    {
        mtk::CountPtr<ord_ls> best_buy = bid_queue.front();
        mtk::CountPtr<ord_ls> best_sell = ask_queue.front();

        mtk::tuple<mtk::FixedNumber, int> best_buy_price = get_price(best_buy);
        mtk::tuple<mtk::FixedNumber, int> best_sell_price = get_price(best_sell);

        while (best_buy_price._0 >= best_sell_price._0)
        {
            //  this is incorrect, we don't manage aggression, but is just for testing
            mtk::FixedNumber exec_price = get_exec_price(best_buy_price, best_sell_price);
            mtk::FixedNumber exec_quantity = min(get_pending_quantity(best_buy), get_pending_quantity(best_sell));

            //  send mk execs ticker
            mtk::prices::msg::sub_last_mk_execs_ticker  sub_last_mk_execs_ticker(exec_price, exec_quantity, exec_price, exec_price, exec_price);
            //mtk::prices::msg::pub_last_mk_execs_ticker  mk_execs_ticker(product_code, sub_last_mk_execs_ticker, mtk::msg::sub_control_fluct("EMARKET.PRC", mtk::dtNowLocal()));
            //mtk_send_message("server", mk_execs_ticker);
            mtk::prices::publ::send_last_exec_ticker (product_code, sub_last_mk_execs_ticker);

            if (exec_quantity.GetDouble() == mtk::Double(0.))
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "emarket", "exec_quantity.GetDouble() == mtk::Double(0.)", mtk::alPriorCritic, mtk::alTypeLogicError));
                break;
            }



            //  confirmation buy
            {
                mtk::trd::msg::CF_XX_LS cf = best_buy->last_confirmation().Get();
                cf.total_execs.acc_quantity.SetDouble(cf.total_execs.acc_quantity.GetDouble() + exec_quantity.GetDouble());
                cf.total_execs.sum_price_by_qty += exec_quantity.GetDouble() * exec_price.GetDouble();
                cf.total_execs.remaining_qty.SetDouble(
                            cf.market_pos.quantity.GetDouble()
                            -
                            cf.total_execs.acc_quantity.GetDouble());
                cf.req_id.session_id += "em";
                cf.req_id.req_code +=  "em";
                cf.orig_control_fluct = mtk::msg::sub_control_fluct("EMARKET.TRD", mtk::dtNowLocal());
                best_buy->mkt_cf_ex(mtk::trd::msg::CF_EX_LS( cf, mtk::trd::msg::sub_exec_conf(MTK_SS("mk::ex" << ++ex_counter), exec_price, exec_quantity)));

                if (cf.total_execs.acc_quantity  >=  cf.market_pos.quantity)
                    bid_queue.pop_front();
            }
            //  confirmation sell
            {
                mtk::trd::msg::CF_XX_LS cf = best_sell->last_confirmation().Get();
                cf.total_execs.acc_quantity.SetDouble(cf.total_execs.acc_quantity.GetDouble() + exec_quantity.GetDouble());
                cf.total_execs.sum_price_by_qty += exec_quantity.GetDouble() * exec_price.GetDouble();
                cf.total_execs.remaining_qty.SetDouble(
                            cf.market_pos.quantity.GetDouble()
                            -
                            cf.total_execs.acc_quantity.GetDouble());
                cf.req_id.session_id += "em";
                cf.req_id.req_code +=  "em";
                cf.orig_control_fluct = mtk::msg::sub_control_fluct("EMARKET.TRD", mtk::dtNowLocal());
                best_sell->mkt_cf_ex(mtk::trd::msg::CF_EX_LS( cf, mtk::trd::msg::sub_exec_conf(MTK_SS("mk::ex" << ++ex_counter), exec_price, exec_quantity)));
                if (cf.total_execs.acc_quantity  >=  cf.market_pos.quantity)
                    ask_queue.pop_front();
            }
            if (bid_queue.size() == 0  ||  ask_queue.size() == 0)
                break;
            best_buy = bid_queue.front();
            best_sell = ask_queue.front();

            best_buy_price = get_price(best_buy);
            best_sell_price = get_price(best_sell);
        }
    }
    //  generate prices
}




mtk::FixedNumber get_empty_fixed_number(const mtk::fnExt&  ext)
{
    return mtk::FixedNumber(mtk::fnDouble(0.), ext);
}
mtk::prices::msg::sub_price_level   get_emtpy_level_prices(const mtk::tuple<mtk::fnExt, mtk::fnExt>&  ext_pr_qty)
{
    return mtk::prices::msg::sub_price_level(get_empty_fixed_number(ext_pr_qty._0), get_empty_fixed_number(ext_pr_qty._1));
}
mtk::prices::msg::sub_best_prices    get_empty_sub_best_prices   (const mtk::tuple<mtk::fnExt, mtk::fnExt>&  ext_pr_qty)
{
    return mtk::prices::msg::sub_best_prices(
        mtk::prices::msg::sub_price_deph5(  get_emtpy_level_prices(ext_pr_qty),
                                            get_emtpy_level_prices(ext_pr_qty),
                                            get_emtpy_level_prices(ext_pr_qty),
                                            get_emtpy_level_prices(ext_pr_qty),
                                            get_emtpy_level_prices(ext_pr_qty)),
        mtk::prices::msg::sub_price_deph5(  get_emtpy_level_prices(ext_pr_qty),
                                            get_emtpy_level_prices(ext_pr_qty),
                                            get_emtpy_level_prices(ext_pr_qty),
                                            get_emtpy_level_prices(ext_pr_qty),
                                            get_emtpy_level_prices(ext_pr_qty)));
}

/*
mtk::prices::msg::sub_full_product_info    get_emtpy_sub_full_product_info   (const mtk::tuple<mtk::fnExt, mtk::fnExt>&  ext_pr_qty)
{
    return mtk::prices::msg::sub_full_product_info(
                    mtk::msg::sub_product_code("", ""),
                    get_empty_sub_best_prices(ext_pr_qty));
                    //mtk::msg::sub_control_fluct("EMARKET.PRC", mtk::dtNowLocal());
}
*/




void fill_side (const mtk::list<mtk::CountPtr<ord_ls> >& xxx_queue, mtk::prices::msg::sub_price_deph5& deph2fill)
{
        mtk::list<mtk::CountPtr<ord_ls> >::const_iterator it = xxx_queue.begin();
        mtk::list<mtk::prices::msg::sub_price_level>  levels;
        while (it != xxx_queue.end())
        {
            mtk::trd::msg::CF_XX_LS cf = (*it)->last_confirmation().Get();
            if (levels.size() == 0  ||  cf.market_pos.price != levels.front().price)
                levels.push_front(mtk::prices::msg::sub_price_level(cf.market_pos.price, cf.total_execs.remaining_qty));
            else if (cf.market_pos.price == levels.front().price)
                levels.front().quantity.SetDouble( levels.front().quantity.GetDouble() + cf.total_execs.remaining_qty.GetDouble() );
            else
                throw mtk::Alarm(MTK_HERE, "ordersbook", "imposible!?!", mtk::alPriorCritic, mtk::alTypeNoPermisions);


            ++it;
        }

        if (levels.size()>0)    { deph2fill.level0 = levels.back();  levels.pop_back(); }
        if (levels.size()>0)    { deph2fill.level1 = levels.back();  levels.pop_back(); }
        if (levels.size()>0)    { deph2fill.level2 = levels.back();  levels.pop_back(); }
        if (levels.size()>0)    { deph2fill.level3 = levels.back();  levels.pop_back(); }
        if (levels.size()>0)    { deph2fill.level4 = levels.back();  levels.pop_back(); }
}
void orders_in_product_queue::update_prices(const mtk::msg::sub_product_code& product_code)
{
    mtk::prices::msg::pub_best_prices pub_best_prices(  product_code,
                                                        get_empty_sub_best_prices(get_ext_price_quantity_for_product(product_code.product)),
                                                        mtk::msg::sub_control_fluct("EMARKET.PRC", mtk::dtNowLocal()));


    fill_side(bid_queue, pub_best_prices.best_prices.bids);
    fill_side(ask_queue, pub_best_prices.best_prices.asks);

    //send_prices(pub_best_prices);
    mtk::prices::publ::send_best_prices(product_code, pub_best_prices.best_prices);
}





void  internal_orders_book::publish_all_product_full_info(const  mtk::msg::sub_process_info&  pi)
{
    mtk::prices::msg::ps_conf_full_product_info_init__from_publisher
                ps_conf_full_product_info_init(mtk::prices::msg::ps_conf_full_product_info_init("MARKET", mtk::admin::get_process_info()));
    mtk_send_message("server", ps_conf_full_product_info_init);

    mtk::prices::msg::sub_additional_info       additional_info ("GROUP", mtk::nullable<mtk::DateTime>(), mtk::nullable<mtk::DateTime>(), 0, mtk::nullable<mtk::DateTime>(), "");
    mtk::prices::msg::sub_last_mk_execs_ticker  mk_execs_full_info(
                                                                get_empty_fixed_number(mtk::fnExt(mtk::fnDec(0), mtk::fnInc(1))),
                                                                get_empty_fixed_number(mtk::fnExt(mtk::fnDec(0), mtk::fnInc(1))),
                                                                get_empty_fixed_number(mtk::fnExt(mtk::fnDec(0), mtk::fnInc(1))),
                                                                get_empty_fixed_number(mtk::fnExt(mtk::fnDec(0), mtk::fnInc(1))),
                                                                get_empty_fixed_number(mtk::fnExt(mtk::fnDec(0), mtk::fnInc(1)))
                                                                );

    int counter = 0;
    for(auto it_queue_by_product = queue_by_product.begin(); it_queue_by_product != queue_by_product.end(); ++it_queue_by_product)
    {
        //        mtk::list<mtk::CountPtr<ord_ls> >  bid_queue;
        //        mtk::list<mtk::CountPtr<ord_ls> >  ask_queue;
        mtk::prices::msg::sub_full_product_info   sub_full_product_info(  it_queue_by_product->first,
                                                            get_empty_sub_best_prices(get_ext_price_quantity_for_product(it_queue_by_product->first.product)),
                                                            additional_info,
                                                            mtk::make_nullable(mk_execs_full_info));
        fill_side(it_queue_by_product->second.bid_queue, sub_full_product_info.best_prices.bids);
        fill_side(it_queue_by_product->second.ask_queue, sub_full_product_info.best_prices.asks);

        mtk::prices::msg::ps_conf_full_product_info__from_publisher
                    ps_conf_full_product_info(mtk::prices::msg::ps_conf_full_product_info(sub_full_product_info, pi, counter++));

        mtk_send_message("server", ps_conf_full_product_info);
    }

    mtk::prices::msg::pub_new_products  pub_new_products ("MARKET");
    mtk_send_message("server", pub_new_products);
}


