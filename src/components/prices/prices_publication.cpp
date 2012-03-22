#include "prices_publication.h"

#include "support/map.hpp"
#include "support/mtk_string.h"

#include "components/admin/admin.h"





namespace {

    const char*   VERSION = "2012-03-22";

    const char*   MODIFICATIONS =
                        "           2012-03-22     first version\n";


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
        mtk::admin::register_command("pp",  "get_min_time_between_changes",   "")->connect(command_get_min_time_between_changes);
        mtk::admin::register_command("pp",  "set_min_time_between_changes",   "", true)->connect(command_set_min_time_between_changes);
    }
    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)


}       //  anonymous namespace  to register "static" commnads


namespace mtk {
namespace prices {
namespace publ {





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
            last_sent(mtk::dtNowLocal() - mtk::dtHours(1)), queued(false)
    {
    }

    mtk::msg::sub_product_code              product_code;
    T_INFO_TO_SEND       info_last_sent;
    T_INFO_TO_SEND       info_to_send;


    mtk::DateTime       last_sent;
    bool                queued;         //  to add to list just once
};



// -------------------  MERGE  -------------------
/**
 *  return true if item has to be queued
 *
 *
 */




bool  merge__and_return_if_has_to_be_queued(mtk::CountPtr<item<mtk::prices::msg::sub_best_prices> >  origin, const  mtk::prices::msg::sub_best_prices&  received)
{
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




// -------------------  prepare_and_send_message  -------------------
void prepare_and_send_message(const mtk::msg::sub_product_code&  product_code,  const mtk::prices::msg::sub_best_prices&  best_prices,  const mtk::prices::msg::sub_best_prices&  previus_sent)
{
    static  std::string  url  =  mtk::admin::get_config_mandatory_property("PRICES_PUBLICATION.url");

    if(best_prices  !=  previus_sent)
    {
        mtk::prices::msg::pub_best_prices_pr  msg_to_send(product_code, best_prices,
                                                mtk::msg::sub_control_fluct(MTK_SS("CN_P" << product_code.market), mtk::dtNowLocal()));
        mtk_send_message(url, msg_to_send);
    }
}

void prepare_and_send_message(const mtk::msg::sub_product_code&  product_code,  const mtk::prices::msg::sub_last_mk_execs_ticker&  last_mk_execs_ticker, const mtk::prices::msg::sub_last_mk_execs_ticker&  /*previus_sent*/)
{
    static  std::string  url  =  mtk::admin::get_config_mandatory_property("PRICES_PUBLICATION.url");
    mtk::prices::msg::pub_last_mk_execs_ticker_pr  msg_to_send(product_code, last_mk_execs_ticker,
                                            mtk::msg::sub_control_fluct(MTK_SS("CN_P" << product_code.market), mtk::dtNowLocal()));
    mtk_send_message(url, msg_to_send);
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













// -------------------  INTERFAZ impl  -------------------



void  send_best_prices      (const mtk::msg::sub_product_code&  product_code,  const mtk::prices::msg::sub_best_prices&  best_prices)
{
    get_contention_queue<mtk::prices::msg::sub_best_prices>()->update(product_code, best_prices);
}


void  send_last_exec_ticker (const mtk::msg::sub_product_code&  product_code,  const mtk::prices::msg::sub_last_mk_execs_ticker&  last_mk_execs_ticker)
{
    get_contention_queue<mtk::prices::msg::sub_last_mk_execs_ticker>()->update(product_code, last_mk_execs_ticker);
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
