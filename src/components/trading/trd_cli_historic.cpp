#include "trd_cli_historic.h"



namespace  mtk {
namespace  trd {
namespace  hist {
    
    



order_historic_dangerous_not_signal_warped::order_historic_dangerous_not_signal_warped(void)
{
    list_historic_item = mtk::make_cptr(new mtk::list<order_historic_item>);
}






mtk::tuple<int, std::string>    check_for_previus_request_and_fill_delay_if_so(order_historic_item& item, mtk::list<order_historic_item>&   list_historic_item)
{
    std::string result_errors;
    int max_items2check=10;
    bool located_previus_confirmed_request=false;
    int i=0;
    for(auto it=list_historic_item.begin(); it!=list_historic_item.end(); ++i, ++it)
    {
        if(it->request_id  ==  item.request_id) 
        {
            if(located_previus_confirmed_request==true)
                result_errors += MTK_SS("out of order confirmation ");
            if(it->type == tt_rq_confirmed)
                result_errors += MTK_SS("confirmation on confirmated transaction ");
            if(it->type == tt_cf)
                    result_errors += MTK_SS("confirmation on confirmation transaction ");
            if(it->type == tt_rj)
                    result_errors += MTK_SS("confirmation on reject transaction ");
                
            item.confirmation_delay = it->date_time - item.date_time;
            
            if(it->type == tt_rq_pending)
                it->type = tt_rq_confirmed;

            if(it->price.HasValue()  &&  item.price.HasValue())
            {
                if(it->price.Get() != item.price.Get())
                    result_errors += MTK_SS("diferent price " << it->price.Get() << "  !=  " << item.price.Get());
            }
            if(it->quantity  != item.quantity)
                    result_errors += MTK_SS("diferent quantity " << it->quantity << "  !=  " << item.quantity);
            if(it->cli_ref  != item.cli_ref)
                    result_errors += MTK_SS("diferent client_code " << it->cli_ref << "  !=  " << item.cli_ref);

            if(result_errors != "")
            {
                item.error = true;
                item.remarks += result_errors;
            }

            return mtk::make_tuple(i, result_errors);
        }
        if (it->type == tt_rq_confirmed)
            located_previus_confirmed_request = true;
            
        if(--max_items2check  == 0)     break;
    }
    return mtk::make_tuple(-1, result_errors);
}


std::string    order_historic_dangerous_not_signal_warped::add_item(const order_historic_item& _item)
{
    auto item = _item;
    
    bool         result_located_request = true;
    std::string  result_errors;
    int located_distance=-1;
    if((item.type == tt_cf  &&  item.type2 != tt2_ex)  ||  item.type == tt_rj)
    {
        check_for_previus_request_and_fill_delay_if_so(item, *list_historic_item).assign(located_distance, result_errors);
        if(located_distance == -1)
            result_located_request = false;
        if(located_distance == 0)
        {
            list_historic_item->pop_front();
        }
    }
    
    list_historic_item->push_front(item);
    if(located_distance == -1)
        signal_new_item_added.emit(item);
    if(located_distance >= 0)
        signal_modified_item.emit(located_distance, item);
    
    if(list_historic_item->size() > 50)
    {
        for (int items2delete = list_historic_item->size() -25; items2delete!=0; --items2delete)
            list_historic_item->pop_front();
    }
    return result_errors;
}


};      //  namespace  hist {
};      //  namespace  trd
};      //  namespace  mtk {
