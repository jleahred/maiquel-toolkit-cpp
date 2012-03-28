#include "prices_publication.h"

#include "support/map.hpp"
#include "support/mtk_string.h"

#include "components/admin/admin.h"
#include "support/integer_compactor.h"





namespace {

    const char*   VERSION = "2012-03-28";

    const char*   MODIFICATIONS =
                        "           2012-03-22     first version\n"
                        "           2012-03-28     price compactation\n"
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
    void command_get_min_time_between_changes  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines);
    void command_set_min_time_between_changes  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines);



    void register_global_commands (void)
    {
        mtk::admin::register_command("__GLOBAL__",    "ver",   "")->connect(command_version);
        mtk::admin::register_command("__GLOBAL__",    "modifs","")->connect(command_modifications);
        mtk::admin::register_command("pp",  "get_min_time",   "get min time between changes")->connect(command_get_min_time_between_changes);
        mtk::admin::register_command("pp",  "set_min_time",   "set min time between changes", true)->connect(command_set_min_time_between_changes);
    }
    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)

}       //  anonymous namespace  to register "static" commnads


namespace mtk {
namespace prices {
namespace publ {


    std::string  compacted_prices(const mtk::prices::msg::sub_best_prices& best_prices, const mtk::prices::msg::sub_last_mk_execs_ticker&  last_mk_execs_ticker);
    std::string  compacted_prices(const mtk::prices::msg::sub_best_prices& best_prices);
    std::string  compacted_prices(const mtk::prices::msg::sub_last_mk_execs_ticker&  last_mk_execs_ticker);

    mtk::tuple<mtk::nullable<mtk::prices::msg::sub_best_prices>, mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker> >
    decompact_prices(const std::string& compacted_prices);




    void prepare_and_send_message(const mtk::msg::sub_product_code&  product_code,  const mtk::prices::msg::sub_best_prices&  best_prices,  const mtk::prices::msg::sub_best_prices&  previus_sent);
    void prepare_and_send_message(const mtk::msg::sub_product_code&  product_code,  const mtk::prices::msg::sub_last_mk_execs_ticker&  last_mk_execs_ticker, const mtk::prices::msg::sub_last_mk_execs_ticker&  /*previus_sent*/);







// -------------------  CONFIG  -------------------
mtk::CountPtr<mtk::dtTimeQuantity>   min_time_between_changes;
void  gen_min_time_between_changes(void)
{
    std::string  smin_time_between_changes  =  mtk::admin::get_config_mandatory_property("PRICES_PUBLICATION.min_time_between_changes");
    mtk::tuple<mtk::dtTimeQuantity, bool>  convert = mtk::s_TRY_stotq(smin_time_between_changes, mtk::dtSeconds(0));
    if(convert._1 == true)
        min_time_between_changes = mtk::make_cptr(new mtk::dtTimeQuantity{convert._0});
}

// -------------------  ITEM  -------------------
template<typename T_INFO_TO_SEND>       //      i.e.  mtk::prices::msg::sub_best_prices
class   item
{
public:
    item(const mtk::msg::sub_product_code&  _product_code,   const T_INFO_TO_SEND&   _info_to_send)
        :
            product_code{_product_code},
            info_last_sent{mtk::prices::msg::__internal_get_default((T_INFO_TO_SEND*)0)},
            info_to_send{_info_to_send},
            last_sent(mtk::dtNowLocal() - mtk::dtHours(1)), queued(false), cancel_send(false)
    {
    }

    mtk::msg::sub_product_code              product_code;
    T_INFO_TO_SEND       info_last_sent;
    T_INFO_TO_SEND       info_to_send;


    mtk::DateTime       last_sent;
    bool                queued;         //  to add to list just once
    bool                cancel_send;
};



// -------------------  MERGE  -------------------
/**
 *  return true if item has to be queued
 *
 *
 */




bool  merge__and_return_if_has_to_be_queued(mtk::CountPtr<item<mtk::prices::msg::sub_best_prices> >  origin, const  mtk::prices::msg::sub_best_prices&  received)
{
    origin->cancel_send = false;
    if(origin->info_last_sent != received)
    {
        origin->info_to_send = received;
        if(origin->queued == false)
        {
            origin->queued = true;
            return true;
        }
    }
    return false;
}

bool  merge__and_return_if_has_to_be_queued(mtk::CountPtr<item<mtk::prices::msg::sub_last_mk_execs_ticker> >  origin, const  mtk::prices::msg::sub_last_mk_execs_ticker&  received)
{
    origin->cancel_send = false;
    origin->info_to_send.last_price       = received.last_price;
    origin->info_to_send.last_quantity    = received.last_quantity;
    origin->info_to_send.opened_price     = received.opened_price;

    if (origin->info_to_send.min_last_price   > received.min_last_price)
        origin->info_to_send.min_last_price   = received.min_last_price;
    if (origin->info_to_send.max_last_price   < received.max_last_price)
        origin->info_to_send.max_last_price   = received.max_last_price;


    if(origin->queued == false)
    {
        origin->queued = true;
        return true;
    }

    return false;
}








// -------------------  contention_queue  -------------------
template<typename T_INFO_TO_SEND>       //      i.e.  mtk::prices::msg::sub_best_prices
class   contention_queue   :    public  mtk::SignalReceptor
{
    typedef  contention_queue  CLASS_NAME;

public:
    contention_queue(void)
    {
        gen_min_time_between_changes();
        MTK_TIMER_1C(timer_check_unqueue);
    };

    void update(const mtk::msg::sub_product_code& product_code, const T_INFO_TO_SEND&  data)
    {
        auto located_item = map.find(product_code);
        if(located_item == map.end())
        {
            auto new_item = mtk::make_cptr(new item<T_INFO_TO_SEND>{product_code, data});
            map[product_code] = new_item;
            list.push_back(new_item);
        }
        else
        {
            if(merge__and_return_if_has_to_be_queued(located_item->second, data))
                list.push_back(located_item->second);
        }
    }

    mtk::CountPtr<item<T_INFO_TO_SEND> >  get_item(const mtk::msg::sub_product_code& product_code)
    {
        auto it = map.find(product_code);
        if(it!= map.end())
            return it->second;
        else
            return  mtk::CountPtr<item<T_INFO_TO_SEND> >();
    }

private:
    mtk::map<mtk::msg::sub_product_code, mtk::CountPtr<item<T_INFO_TO_SEND> > >  map;
    mtk::list<mtk::CountPtr<item<T_INFO_TO_SEND> > >                             list;

    void  timer_check_unqueue(void)
    {
        typename mtk::list<mtk::CountPtr<item<T_INFO_TO_SEND> > >::iterator it = list.begin();
        while(it != list.end())
        {
            mtk::CountPtr<item<T_INFO_TO_SEND> >   item_to_send =  *it;

            if(*min_time_between_changes  >  mtk::dtMinutes(20))
            {
                MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(30))
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "prices_publication", MTK_SS("min_time_between_changes  too high "  <<  *min_time_between_changes <<  "   possible error on config file"), mtk::alPriorCritic));
                MTK_END_EXEC_MAX_FREC
            }
            if(item_to_send->last_sent + *min_time_between_changes < mtk::dtNowLocal())
            {
                it = list.erase(it);
                item_to_send->queued = false;
                item_to_send->last_sent = mtk::dtNowLocal();
                prepare_and_send_message(item_to_send->product_code, item_to_send->info_to_send, item_to_send->info_last_sent);
                item_to_send->info_last_sent = item_to_send->info_to_send;
            }

            if(it== list.end())
                return;


            ++it;
        }
    }

};



template<typename T_INFO_TO_SEND>       //      i.e.  mtk::prices::msg::sub_best_prices
mtk::CountPtr<contention_queue<T_INFO_TO_SEND> >   get_contention_queue  (void)
{
    static  mtk::CountPtr<contention_queue<T_INFO_TO_SEND> >   _contention_queue =  mtk::make_cptr(new contention_queue<T_INFO_TO_SEND>);
    return _contention_queue;
}







// -------------------  prepare_and_send_message  -------------------
void prepare_and_send_message(const mtk::msg::sub_product_code&  product_code,  const mtk::prices::msg::sub_best_prices&  best_prices,  const mtk::prices::msg::sub_best_prices&  previus_sent)
{
    static  std::string  url  =  mtk::admin::get_config_mandatory_property("PRICES_PUBLICATION.url");

    if(best_prices  !=  previus_sent)
    {
        std::string  compacted_data;

        mtk::CountPtr<item<mtk::prices::msg::sub_last_mk_execs_ticker> >
        item = get_contention_queue<mtk::prices::msg::sub_last_mk_execs_ticker>()->get_item(product_code);
        if(item.isValid()  &&  item->info_last_sent != item->info_to_send  &&  item->cancel_send==false)
        {
            compacted_data = compacted_prices(best_prices, item->info_to_send);
            item->info_last_sent = item->info_to_send;
            item->cancel_send = true;
        }
        else
            compacted_data = compacted_prices(best_prices);

        mtk::prices::msg::ppc  msg_to_send(product_code.market, product_code.product,  compacted_data, MTK_SS("CN_P" << product_code.market), mtk::dtNowLocal());
        mtk_send_message(url, msg_to_send);
    }
}

void prepare_and_send_message(const mtk::msg::sub_product_code&  product_code,  const mtk::prices::msg::sub_last_mk_execs_ticker&  last_mk_execs_ticker, const mtk::prices::msg::sub_last_mk_execs_ticker&  /*previus_sent*/)
{
    static  std::string  url  =  mtk::admin::get_config_mandatory_property("PRICES_PUBLICATION.url");

    std::string  compacted_data = compacted_prices(last_mk_execs_ticker);

        mtk::CountPtr<item<mtk::prices::msg::sub_best_prices> >
        item = get_contention_queue<mtk::prices::msg::sub_best_prices>()->get_item(product_code);
        if(item.isValid()  &&  item->info_last_sent != item->info_to_send  &&  item->cancel_send==false)
        {
            compacted_data = compacted_prices(item->info_to_send, last_mk_execs_ticker);
            item->info_last_sent = item->info_to_send;
            item->cancel_send = true;
        }
        else
            compacted_data = compacted_prices(last_mk_execs_ticker);



    mtk::prices::msg::ppc  msg_to_send(product_code.market, product_code.product,  compacted_data, MTK_SS("CN_P" << product_code.market), mtk::dtNowLocal());
    mtk_send_message(url, msg_to_send);
}








// -------------------  INTERFAZ impl  -------------------



void  send_best_prices      (const mtk::msg::sub_product_code&  product_code,  const mtk::prices::msg::sub_best_prices&  best_prices)
{
    get_contention_queue<mtk::prices::msg::sub_best_prices>()->update(product_code, best_prices);

    //  provisional, keeped for compatibility
    /*
    static  std::string  url  =  mtk::admin::get_config_mandatory_property("PRICES_PUBLICATION.url");
    mtk::prices::msg::pub_best_prices_pr  msg_to_send(product_code, best_prices,
                                            mtk::msg::sub_control_fluct(MTK_SS("CN_P" << product_code.market), mtk::dtNowLocal()));
    mtk_send_message(url, msg_to_send);
    */
}


void  send_last_exec_ticker (const mtk::msg::sub_product_code&  product_code,  const mtk::prices::msg::sub_last_mk_execs_ticker&  last_mk_execs_ticker)
{
    get_contention_queue<mtk::prices::msg::sub_last_mk_execs_ticker>()->update(product_code, last_mk_execs_ticker);

    //  provisional, keeped for compatibility
    /*
    static  std::string  url  =  mtk::admin::get_config_mandatory_property("PRICES_PUBLICATION.url");
    static  std::string  url  =  mtk::admin::get_config_mandatory_property("PRICES_PUBLICATION.url");
    mtk::prices::msg::pub_last_mk_execs_ticker_pr  msg_to_send(product_code, last_mk_execs_ticker,
                                            mtk::msg::sub_control_fluct(MTK_SS("CN_P" << product_code.market), mtk::dtNowLocal()));
    mtk_send_message(url, msg_to_send);
     */
}





// -------------------  PRICES MSG COMPACTION   -------------------



void  __compacted_best_prices(mtk::integer_compactor&  ic, const mtk::prices::msg::sub_best_prices& best_prices)
{
    ic.push(best_prices.bids.level0.price.GetIntCode());
    ic.push(best_prices.bids.level0.quantity.GetIntCode());
    ic.push(best_prices.bids.level1.price.GetIntCode()      - best_prices.bids.level0.price.GetIntCode());
    ic.push(best_prices.bids.level1.quantity.GetIntCode()   - best_prices.bids.level0.quantity.GetIntCode());
    ic.push(best_prices.bids.level2.price.GetIntCode()      - best_prices.bids.level1.price.GetIntCode());
    ic.push(best_prices.bids.level2.quantity.GetIntCode()   - best_prices.bids.level1.quantity.GetIntCode());
    ic.push(best_prices.bids.level3.price.GetIntCode()      - best_prices.bids.level2.price.GetIntCode());
    ic.push(best_prices.bids.level3.quantity.GetIntCode()   - best_prices.bids.level2.quantity.GetIntCode());
    ic.push(best_prices.bids.level4.price.GetIntCode()      - best_prices.bids.level3.price.GetIntCode());
    ic.push(best_prices.bids.level4.quantity.GetIntCode()   - best_prices.bids.level3.quantity.GetIntCode());

    ic.push(best_prices.asks.level0.price.GetIntCode());
    ic.push(best_prices.asks.level0.quantity.GetIntCode());
    ic.push(best_prices.asks.level1.price.GetIntCode()      - best_prices.asks.level0.price.GetIntCode());
    ic.push(best_prices.asks.level1.quantity.GetIntCode()   - best_prices.asks.level0.quantity.GetIntCode());
    ic.push(best_prices.asks.level2.price.GetIntCode()      - best_prices.asks.level1.price.GetIntCode());
    ic.push(best_prices.asks.level2.quantity.GetIntCode()   - best_prices.asks.level1.quantity.GetIntCode());
    ic.push(best_prices.asks.level3.price.GetIntCode()      - best_prices.asks.level2.price.GetIntCode());
    ic.push(best_prices.asks.level3.quantity.GetIntCode()   - best_prices.asks.level2.quantity.GetIntCode());
    ic.push(best_prices.asks.level4.price.GetIntCode()      - best_prices.asks.level3.price.GetIntCode());
    ic.push(best_prices.asks.level4.quantity.GetIntCode()   - best_prices.asks.level3.quantity.GetIntCode());
}


void  __compacted_last(mtk::integer_compactor&  ic, const mtk::prices::msg::sub_last_mk_execs_ticker&  last_mk_execs_ticker)
{
    ic.push(last_mk_execs_ticker.last_price.GetIntCode());
    ic.push(last_mk_execs_ticker.last_quantity.GetIntCode());
    ic.push(last_mk_execs_ticker.max_last_price.GetIntCode() - last_mk_execs_ticker.last_price.GetIntCode());
    ic.push(last_mk_execs_ticker.min_last_price.GetIntCode() - last_mk_execs_ticker.last_price.GetIntCode());

    ic.push(last_mk_execs_ticker.opened_price.GetExt().GetDec());
    ic.push(last_mk_execs_ticker.opened_price.GetExt().GetInc());
    ic.push(last_mk_execs_ticker.opened_price.GetIntCode());
}



std::string  compacted_prices(const mtk::prices::msg::sub_best_prices& best_prices)
{
    mtk::integer_compactor  ic;

    ic.push(1);                                                         //  means it has best

    ic.push(best_prices.bids.level0.price.GetExt().GetDec());
    ic.push(best_prices.bids.level0.price.GetExt().GetInc());

    ic.push(best_prices.bids.level0.quantity.GetExt().GetDec());
    ic.push(best_prices.bids.level0.quantity.GetExt().GetInc());


    //  best  -----------------------------
    __compacted_best_prices(ic, best_prices);

    return ic.get_buffer();
}


std::string  compacted_prices(const mtk::prices::msg::sub_last_mk_execs_ticker&  last_mk_execs_ticker)
{
    mtk::integer_compactor  ic;

    ic.push(2);                                                         //  means it has best and last

    ic.push(last_mk_execs_ticker.last_price.GetExt().GetDec());
    ic.push(last_mk_execs_ticker.last_price.GetExt().GetInc());

    ic.push(last_mk_execs_ticker.last_quantity.GetExt().GetDec());
    ic.push(last_mk_execs_ticker.last_quantity.GetExt().GetInc());




    //  last  -----------------------------
    __compacted_last(ic, last_mk_execs_ticker);

    return ic.get_buffer();
}


std::string  compacted_prices(const mtk::prices::msg::sub_best_prices& best_prices, const mtk::prices::msg::sub_last_mk_execs_ticker&  last_mk_execs_ticker)
{
    mtk::integer_compactor  ic;

    ic.push(3);                                                         //  means it has best and last

    ic.push(best_prices.bids.level0.price.GetExt().GetDec());
    ic.push(best_prices.bids.level0.price.GetExt().GetInc());

    ic.push(best_prices.bids.level0.quantity.GetExt().GetDec());
    ic.push(best_prices.bids.level0.quantity.GetExt().GetInc());


    //  best  -----------------------------
    __compacted_best_prices(ic, best_prices);


    //  last  -----------------------------
    __compacted_last(ic, last_mk_execs_ticker);

    return ic.get_buffer();
}



mtk::fnExt   pop_extended(mtk::integer_DEcompactor&  iDEc)
{
    int  dec  =  iDEc.pop_int8_t();
    int  inc  =  iDEc.pop_int8_t();

    return mtk::fnExt(mtk::fnDec(dec), mtk::fnInc(inc));
}



mtk::prices::msg::sub_price_level  pop_sub_price_level(mtk::integer_DEcompactor&  iDEc, const mtk::fnExt& extended_price, const mtk::fnExt& extended_quantity, int prev_price, int prev_quantity)
{
    mtk::FixedNumber  price     (mtk::fnIntCode(iDEc.pop_int32_t() + prev_price),    extended_price);
    mtk::FixedNumber  quantity  (mtk::fnIntCode(iDEc.pop_int32_t() + prev_quantity), extended_quantity);

    return mtk::prices::msg::sub_price_level(price, quantity);
}

mtk::prices::msg::sub_price_deph5  pop_sub_price_deph5(mtk::integer_DEcompactor&  iDEc, const mtk::fnExt& extended_price, const mtk::fnExt& extended_quantity)
{
    auto level0 = pop_sub_price_level(iDEc, extended_price, extended_quantity, 0, 0);
    auto level1 = pop_sub_price_level(iDEc, extended_price, extended_quantity, level0.price.GetIntCode(), level0.quantity.GetIntCode());
    auto level2 = pop_sub_price_level(iDEc, extended_price, extended_quantity, level1.price.GetIntCode(), level1.quantity.GetIntCode());
    auto level3 = pop_sub_price_level(iDEc, extended_price, extended_quantity, level2.price.GetIntCode(), level2.quantity.GetIntCode());
    auto level4 = pop_sub_price_level(iDEc, extended_price, extended_quantity, level3.price.GetIntCode(), level3.quantity.GetIntCode());

    return mtk::prices::msg::sub_price_deph5(  level0, level1, level2, level3, level4 );
}

mtk::prices::msg::sub_last_mk_execs_ticker  pop_last_mk_execs_ticker(mtk::integer_DEcompactor&  iDEc, const mtk::fnExt& extended_price, const mtk::fnExt& extended_quantity)
{
    int last_price_integer_code = iDEc.pop_int32_t();
    mtk::FixedNumber    last_price      (mtk::fnIntCode(last_price_integer_code),   extended_price);
    mtk::FixedNumber    last_quantity   (mtk::fnIntCode(iDEc.pop_int32_t()),   extended_quantity);

    mtk::FixedNumber    max_last_price  (mtk::fnIntCode(iDEc.pop_int32_t() + last_price_integer_code),   extended_price);
    mtk::FixedNumber    min_last_price  (mtk::fnIntCode(iDEc.pop_int32_t() + last_price_integer_code),   extended_price);

    mtk::fnExt          extended_price_openend   =  pop_extended(iDEc);
    mtk::FixedNumber    opened_price    (mtk::fnIntCode(iDEc.pop_int32_t()),   extended_price_openend);

    return  mtk::prices::msg::sub_last_mk_execs_ticker(last_price, last_quantity, max_last_price, min_last_price, opened_price);
}

mtk::tuple<mtk::nullable<mtk::prices::msg::sub_best_prices>, mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker> >
decompact_prices(const std::string& compacted_prices)
{
    mtk::nullable<mtk::prices::msg::sub_best_prices>            best_prices;
    mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>   last_mk_execs_ticker;

    mtk::integer_DEcompactor  iDEc;

    iDEc.set_buffer(compacted_prices);
    int8_t  coded = iDEc.pop_int8_t();
    mtk::fnExt  extended_price      =  pop_extended(iDEc);
    mtk::fnExt  extended_quantity   =  pop_extended(iDEc);

    if(coded&0x01)
    {
        auto bids = pop_sub_price_deph5(iDEc, extended_price, extended_quantity);
        auto asks = pop_sub_price_deph5(iDEc, extended_price, extended_quantity);
        best_prices = mtk::prices::msg::sub_best_prices(bids, asks);
    }
    if(coded&0x02)
    {
        last_mk_execs_ticker = pop_last_mk_execs_ticker(iDEc, extended_price, extended_quantity);
    }
    return mtk::make_tuple(best_prices, last_mk_execs_ticker);
}



};  //  namespace publ {
};  //  namespace prices {
};  //  namespace mtk {





// -------------------  commands  impl  -------------------

namespace {

    void command_get_min_time_between_changes  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines)
    {
        if(mtk::prices::publ::min_time_between_changes.isValid()==false)
            response_lines.push_back("min_time_between_changes not initialized");
        else
            response_lines.push_back(MTK_SS("min_time_between_changes: " << *mtk::prices::publ::min_time_between_changes));

    }
    void command_set_min_time_between_changes  (const std::string& /*command*/, const std::string& param,  mtk::list<std::string>&  response_lines)
    {
        if(mtk::prices::publ::min_time_between_changes.isValid()==false)
            response_lines.push_back("min_time_between_changes not initialized");
        else
        {
            std::string  check  =  param;
            mtk::tuple<mtk::dtTimeQuantity, bool>  convert = mtk::s_TRY_stotq(check, mtk::dtSeconds(0));
            if(convert._1 == false)
            {
                response_lines.push_back(MTK_SS("invalid format "  << param));
                return;
            }

            mtk::admin::set_config_property("PRICES_PUBLICATION.min_time_between_changes", param);
            mtk::prices::publ::gen_min_time_between_changes();
            response_lines.push_back("reconfigured");
            response_lines.push_back(MTK_SS("min_time_between_changes: " << *mtk::prices::publ::min_time_between_changes));
        }
    }
}       //  anonymous namespace  to register "static" commnads

