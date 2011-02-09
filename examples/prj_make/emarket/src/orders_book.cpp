#include "orders_book.h"
#include "support/mtk_string.h"
#include "mtk_qpid/mtk_qpid.hpp"
#include "support/list.hpp"
#include "support/map.hpp"

#include "components/prices/msg_prices.h"


//----------------------------------------------------------------------------------------
//      o r d e r s _ i n _ p r o d u c t _ q u e u e
//----------------------------------------------------------------------------------------

class orders_in_product_queue
{
private:
    mtk::list<mtk::CountPtr<ord_ls> >  bid_queue;
    mtk::list<mtk::CountPtr<ord_ls> >  ask_queue;
    const int                          adjust_product_comparation;
    
public:

    void add_order  (mtk::CountPtr<ord_ls> order);
    void del_order  (mtk::CountPtr<ord_ls> order);
    void modif_order(mtk::CountPtr<ord_ls> order);
    void check_execs(void                       );     //  here will be generated the output  cf_ex if so
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
    
    mtk::map<mtk::trd::msg::sub_order_id, mtk::CountPtr<ord_ls> >           orders_by_id;
    mtk::map<mtk::msg::sub_single_product_code, orders_in_product_queue >   queue_by_product;
    
    mtk::CountPtr<ord_ls> cached_last_request;
    
public:    

    //  in  check_request->book_orders
    void oms_RQ_NW_LS (const mtk::trd::msg::oms_RQ_NW_LS& rq);
    void oms_RQ_MD_LS (const mtk::trd::msg::oms_RQ_MD_LS& rq);
    void oms_RQ_CC_LS (const mtk::trd::msg::oms_RQ_CC_LS& rq);

    void add_order    (const mtk::trd::msg::CF_XX_LS& order_info);
    void del_order    (const mtk::trd::msg::CF_XX_LS& order_info);
    void modif_order  (const mtk::trd::msg::CF_XX_LS& order_info);
    void check_execs  (const mtk::trd::msg::CF_XX_LS& order_info);     //  here will be generated the output  cf_ex if so
    void update_prices(const mtk::trd::msg::CF_XX_LS& order_info);

};







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





//------------------------------------------------------------------------------------------
//
//  i n t e r n a l _ o r d e r s _ b o o k
//
//  implementation
//------------------------------------------------------------------------------------------

#define SET_OR_INIT_CACHED_LAST_REQUEST\
    cached_last_request = orders_by_id[rq.order_id];    \
    if (cached_last_request.isValid()==false)     \
    {      \
        cached_last_request = make_cptr(new ord_ls());       \
        orders_by_id[rq.order_id] = cached_last_request;      \
        cached_last_request->sig_cli_cf_nw.connect(&send_to_client);    \
        cached_last_request->sig_cli_cf_md.connect(&send_to_client);    \
        cached_last_request->sig_cli_cf_cc.connect(&send_to_client);    \
        cached_last_request->sig_cli_rj_nw.connect(&send_to_client);    \
        cached_last_request->sig_cli_rj_md.connect(&send_to_client);    \
        cached_last_request->sig_cli_rj_cc.connect(&send_to_client);    \
        cached_last_request->sig_cli_cf_ex.connect(&send_to_client);    \
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
    static const std::string URL = "amqp:tcp:127.0.0.1:5672";
    static const std::string OUT_ADDRESS = "CLITRD";
    static mtk::CountPtr< mtk::qpid_session > qpid_session = mtk::get_from_factory< mtk::qpid_session >(mtk::make_tuple(URL, OUT_ADDRESS));
    
    send_message(qpid_session, toclient, "");
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



#define CHECK_CACHTED_ORDER(ACTION)  \
    if (cached_last_request.isValid()==false)  \
        throw mtk::Alarm("orders_book::" ACTION "_order", MTK_SS("empty cached_last_request" << order_info), mtk::alPriorCritic, mtk::alTypeNoPermisions);  \
    if (cached_last_request->last_request().HasValue() == false)  \
        throw mtk::Alarm("orders_book::" ACTION "_order", MTK_SS("empty cached_last_request request" << order_info), mtk::alPriorCritic, mtk::alTypeNoPermisions);  \
    if (cached_last_request->last_confirmation().HasValue() == false)  \
        throw mtk::Alarm("orders_book::" ACTION "_order", MTK_SS("empty cached_last_request confirmation " << order_info), mtk::alPriorCritic, mtk::alTypeNoPermisions);  \
    else if (cached_last_request->last_request().Get().order_id != order_info.confirmated_info.order_id)  \
        throw mtk::Alarm("orders_book::" ACTION "_order", MTK_SS("cached_last_request doesn't math with order to " ACTION   \
                        << cached_last_request->last_request().Get() << "  " << order_info), mtk::alPriorCritic, mtk::alTypeNoPermisions);

void internal_orders_book::add_order  (const mtk::trd::msg::CF_XX_LS& order_info)
{
    CHECK_CACHTED_ORDER("add")
    this->queue_by_product[cached_last_request->last_confirmation().Get().confirmated_info.product_code.sys_code].add_order(cached_last_request);
}

void internal_orders_book::del_order  (const mtk::trd::msg::CF_XX_LS& order_info)
{
    CHECK_CACHTED_ORDER("del")
    this->queue_by_product[cached_last_request->last_confirmation().Get().confirmated_info.product_code.sys_code].del_order(cached_last_request);
}

void internal_orders_book::modif_order  (const mtk::trd::msg::CF_XX_LS& order_info)
{
    CHECK_CACHTED_ORDER("modif")
    this->queue_by_product[cached_last_request->last_confirmation().Get().confirmated_info.product_code.sys_code].modif_order(cached_last_request);
}

void internal_orders_book::check_execs  (const mtk::trd::msg::CF_XX_LS& order_info)
{
    CHECK_CACHTED_ORDER("check_execs")
    this->queue_by_product[cached_last_request->last_confirmation().Get().confirmated_info.product_code.sys_code].check_execs();
}

void internal_orders_book::update_prices(const mtk::trd::msg::CF_XX_LS& /*order_info*/)
{
    this->queue_by_product[cached_last_request->last_confirmation().Get().confirmated_info.product_code.sys_code].update_prices(cached_last_request->last_confirmation().Get().confirmated_info.product_code);
}


//----------------------------------------------------------------------------------------
//      o r d e r s _ i n _ p r o d u c t _ q u e u e
//
//  implementation
//----------------------------------------------------------------------------------------



mtk::tuple<mtk::list<mtk::CountPtr<ord_ls> >*/*queue*/, int/*adjust_comparation*/> orders_in_product_queue::get_queue_adjust_comparation(mtk::CountPtr<ord_ls> order)
{
    if      (order->last_confirmation().Get().confirmated_info.market_pos.side == mtk::trd::msg::buy)
    {
        return mtk::make_tuple(&bid_queue, 1);
    }
    else if (order->last_confirmation().Get().confirmated_info.market_pos.side == mtk::trd::msg::sell)
    {
        return mtk::make_tuple(&ask_queue,-1);
    }
    else
        throw mtk::Alarm("orders_in_product_queue::", MTK_SS("invalid order side " << order->last_request()), mtk::alPriorCritic, mtk::alTypeNoPermisions);
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
        if ( mtk::Double((*it)->last_confirmation().Get().confirmated_info.market_pos.price.GetDouble()*adjust_comparation)  
             <  
             mtk::Double(order->last_confirmation().Get().confirmated_info.market_pos.price.GetDouble()*adjust_comparation))
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
        if ((*it)->last_confirmation().Get().confirmated_info.market_pos.price  ==  order->last_confirmation().Get().confirmated_info.market_pos.price)
        //  GetDouble returns a mtk::Double (comparations safe)
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
    return mtk::make_tuple(order->last_confirmation().Get().confirmated_info.market_pos.price, order->sequence());
}
mtk::FixedNumber get_pending_quantity (const mtk::CountPtr<ord_ls>& order)
{
    return order->last_confirmation().Get().confirmated_info.total_execs.remaining_qty;
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

void orders_in_product_queue::check_execs(void)
{
    //  pending...
    //  check executions
    if (bid_queue.size() > 0  &&  ask_queue.size() > 0)
    {
        mtk::CountPtr<ord_ls> best_buy = bid_queue.front();
        mtk::CountPtr<ord_ls> best_sell = ask_queue.front();
       
        mtk::tuple<mtk::FixedNumber, int> best_buy_price = get_price(best_buy);
        mtk::tuple<mtk::FixedNumber, int> best_sell_price = get_price(best_sell);
        
        while (best_buy_price._0 >= best_sell_price._0)
        {
            mtk::FixedNumber exec_price = get_exec_price(best_buy_price, best_sell_price);
            mtk::FixedNumber exec_quantity = min(get_pending_quantity(best_buy), get_pending_quantity(best_sell));
            
            if (exec_quantity.GetDouble() == mtk::Double(0.))   break;
            //  confirmation buy
            {
                mtk::trd::msg::CF_XX_LS cf = best_buy->last_confirmation().Get();
                cf.confirmated_info.total_execs.quantity.SetDouble(cf.confirmated_info.total_execs.quantity.GetDouble() + exec_quantity.GetDouble());
                cf.confirmated_info.total_execs.sum_price_by_qty += exec_quantity.GetDouble() * exec_price.GetDouble();
                cf.confirmated_info.total_execs.remaining_qty.SetDouble(
                            cf.confirmated_info.market_pos.quantity.GetDouble()
                            -
                            cf.confirmated_info.total_execs.quantity.GetDouble());
                best_buy->mkt_cf_ex(mtk::trd::msg::CF_EX_LS( cf, mtk::trd::msg::sub_position_ls(exec_price, exec_quantity, mtk::trd::msg::buy)));
                    
                if (cf.confirmated_info.total_execs.quantity  >=  cf.confirmated_info.market_pos.quantity)
                    bid_queue.pop_front();
            }
            //  confirmation sell
            {
                mtk::trd::msg::CF_XX_LS cf = best_sell->last_confirmation().Get();
                cf.confirmated_info.total_execs.quantity.SetDouble(cf.confirmated_info.total_execs.quantity.GetDouble() + exec_quantity.GetDouble());
                cf.confirmated_info.total_execs.sum_price_by_qty += exec_quantity.GetDouble() * exec_price.GetDouble();
                cf.confirmated_info.total_execs.remaining_qty.SetDouble(
                            cf.confirmated_info.market_pos.quantity.GetDouble()
                            -
                            cf.confirmated_info.total_execs.quantity.GetDouble());
                best_sell->mkt_cf_ex(mtk::trd::msg::CF_EX_LS( cf, mtk::trd::msg::sub_position_ls(exec_price, exec_quantity, mtk::trd::msg::sell)));
                if (cf.confirmated_info.total_execs.quantity  >=  cf.confirmated_info.market_pos.quantity)
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




mtk::FixedNumber get_empty_fixed_number(void)
{
    return mtk::FixedNumber(mtk::fnDouble(0.), mtk::fnDec(0), mtk::fnInc(1));
}
mtk::prices::msg::sub_price_level   get_emtpy_level_prices(void)
{
    return mtk::prices::msg::sub_price_level(get_empty_fixed_number(), get_empty_fixed_number());
}
mtk::prices::msg::best_prices    get_emtpy_best_prices   (void)
{
    return mtk::prices::msg::best_prices(
        mtk::msg::sub_product_code(     mtk::msg::sub_single_product_code("", "", mtk::nullable<std::string>()), 
                                        mtk::nullable<mtk::msg::sub_single_product_code>(),
                                        mtk::nullable<std::string>()),
        mtk::prices::msg::sub_price_deph5(  get_emtpy_level_prices(),  
                                            get_emtpy_level_prices(), 
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices()),
        mtk::prices::msg::sub_price_deph5(  get_emtpy_level_prices(),  
                                            get_emtpy_level_prices(), 
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices())
    );
}



template<typename T>
void send_prices (const T& mtk_msg)
{
    static const std::string URL = "amqp:tcp:127.0.0.1:5672";
    static const std::string OUT_ADDRESS = "PUBPRC";
    static mtk::CountPtr< mtk::qpid_session > qpid_session = mtk::get_from_factory< mtk::qpid_session >(mtk::make_tuple(URL, OUT_ADDRESS));
    
    send_message(qpid_session, mtk_msg, "");
    std::cout << mtk::dtNowLocal() <<"  updated prices " << mtk_msg.get_message_type_as_string() <<  std::endl;
}



void fill_side (const mtk::list<mtk::CountPtr<ord_ls> >& xxx_queue, mtk::prices::msg::sub_price_deph5& deph2fill)
{
        mtk::list<mtk::CountPtr<ord_ls> >::const_iterator it = xxx_queue.begin();
        mtk::list<mtk::prices::msg::sub_price_level>  levels;
        while (it != xxx_queue.end())
        {
            mtk::trd::msg::CF_XX_LS cf = (*it)->last_confirmation().Get();
            if (levels.size() == 0  ||  cf.confirmated_info.market_pos.price != levels.front().price)
                levels.push_front(mtk::prices::msg::sub_price_level(cf.confirmated_info.market_pos.price, cf.confirmated_info.total_execs.remaining_qty));
            else if (cf.confirmated_info.market_pos.price == levels.front().price)
                levels.front().quantity.SetDouble( levels.front().quantity.GetDouble() + cf.confirmated_info.total_execs.remaining_qty.GetDouble() );
            else
                throw mtk::Alarm(MTK_HERE, "imposible!?!", mtk::alPriorCritic, mtk::alTypeNoPermisions);
                
                
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
    mtk::prices::msg::best_prices best =  get_emtpy_best_prices();
    
    best.product_code = product_code;
    
    
    //  fill bid
    fill_side(bid_queue, best.bids);
    fill_side(ask_queue, best.asks);
    
    
    send_prices(best);
}


