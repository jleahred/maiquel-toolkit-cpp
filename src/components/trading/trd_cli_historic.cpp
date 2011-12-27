#include "trd_cli_historic.h"

#include "support/exec_max_frec.h"


namespace  mtk {
namespace  trd {
namespace  hist {





order_historic_dangerous_not_signal_warped::order_historic_dangerous_not_signal_warped(void)
{
    list_historic_item = mtk::make_cptr(new mtk::list<order_historic_item>);
}



std::string  check_item_cf_or_rj__is_ok__and_update_prev_item_status_and_delay(order_historic_item&   prev_item,   order_historic_item&   new_item, bool is_previus = false)
{
    if(new_item.type  != tt_cf   &&  new_item.type  != tt_rj)
    {
        std::string error = "not cf or rj on new_item ";
        new_item.error = true;
        new_item.remarks += "  "  + error;
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "historic", error, mtk::alPriorCritic, mtk::alTypeLogicError));
        return error;
    }
    else
    {
        std::string  result_errors;
        if(prev_item.type == tt_rq_not_pending)
            result_errors += MTK_SS("confirmation on non pending transaction. ");
        if(prev_item.type == tt_rq_confirmated)
            result_errors += MTK_SS("confirmation on confirmated transaction. ");
        if(prev_item.type == tt_cf)
            result_errors += MTK_SS("confirmation on confirmation transaction. ");
        if(prev_item.type == tt_rj)
                result_errors += MTK_SS("confirmation on reject transaction. ");

        new_item.confirmation_delay = prev_item.date_time - new_item.date_time;
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(30))
            if(new_item.confirmation_delay > mtk::dtMilliseconds(800))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "historic_msf30s", "delay on response bigger than 800ms", mtk::alPriorError, mtk::alTypeRealTime));
        MTK_END_EXEC_MAX_FREC

        if(prev_item.type == tt_rq_pending)
        {
            if(is_previus==true)
            {
                if(new_item.type == tt_cf)
                    prev_item.type = tt_rq_confirmated;
                else if (new_item.type == tt_rj)        //  rejects will be added as new item
                    prev_item.type = tt_rq_not_pending;
                else
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "historic", "expected ttcf or ttrj", mtk::alPriorCritic, mtk::alTypeLogicError));
            }
            else
            {
                if(new_item.type == tt_cf)
                    prev_item.type = tt_rq_not_pending;
                else if (new_item.type == tt_rj)        //  rejects will be added as new item
                    prev_item.type = tt_rq_not_pending;
                else
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "historic", "expected ttcf or ttrj", mtk::alPriorCritic, mtk::alTypeLogicError));
            }
        }

        if(prev_item.price.HasValue()  &&  new_item.price.HasValue())
        {
            if(prev_item.price.Get() != new_item.price.Get()  &&  new_item.type2 != tt2_cc)
                result_errors += MTK_SS("diferent price " << prev_item.price.Get() << "  !=  " << new_item.price.Get());
        }
        if(prev_item.quantity  != new_item.quantity  &&  new_item.type2 != tt2_cc)
                result_errors += MTK_SS("diferent quantity " << prev_item.quantity << "  !=  " << new_item.quantity);
        if(prev_item.cli_ref  != new_item.cli_ref  &&  new_item.type2 != tt2_cc)
                result_errors += MTK_SS("diferent client_code " << prev_item.cli_ref << "  !=  " << new_item.cli_ref);

        if(result_errors=="")
        {
            return "";
        }
        else
        {
            new_item.error = true;
            new_item.remarks += "  "  +  result_errors;
            return result_errors;
        }
    }
}



std::string  add_item_check_for_previus_request__fill_delay_if_so_and_signal_new_or_modif_item(  order_historic_item                    item,
                                                                                        mtk::list<order_historic_item>&                 list_historic_item,
                                                                                        mtk::Signal<const order_historic_item&>&        signal_new_item_added,
                                                                                        mtk::Signal<int, const order_historic_item&>&   signal_modified_item)
{
    std::string  result_error;
    if((item.type  == tt_cf   ||  item.type  == tt_rj)  &&   list_historic_item.size()!=0)
    {

        //  generally if it is a confirmation, it will confirm the previus transaction
        //      we will modify previus transaction and we will send a modif signal
        //  if not, we have to add a new item and look for previus request. It could not exist if request has been done for a diferente process
        //      if we locate the previus request, we will modify it configuring it as not pending and we will send a modification signal
        //      previus pending modifications request will be modified to  not pending modification request


        //  confirmation of previus item
        if(list_historic_item.front().request_id  ==  item.request_id    &&  item.type  != tt_rj)
        {
            order_historic_item&        last_inserted_item = list_historic_item.front();
            result_error = check_item_cf_or_rj__is_ok__and_update_prev_item_status_and_delay(last_inserted_item, item, true);
            last_inserted_item.confirmation_delay = item.confirmation_delay;
            if(result_error == "")
                signal_modified_item.emit(0, last_inserted_item);
            else
            {
                list_historic_item.push_front(item);
                signal_new_item_added.emit(item);
            }
        }
        else
        {
            int item_pos = 0;
            bool   just_change_rqpending_by_rqconfirmed = false;    //  items older than current confirmed are already confirmed
                                                                    //  this also lets order confirmation checking
            for(auto it=list_historic_item.begin(); it!=list_historic_item.end(); ++it)
            {
                if(just_change_rqpending_by_rqconfirmed)
                {
                    if(it->type == tt_rq_pending)
                    {
                        it->type = tt_rq_not_pending;
                        signal_modified_item.emit(item_pos, *it);
                    }
                    else
                        break;
                }
                else
                {
                    if(it->request_id  ==  item.request_id)
                    {
                        result_error = check_item_cf_or_rj__is_ok__and_update_prev_item_status_and_delay(*it, item);
                        signal_modified_item.emit(item_pos, *it);
                        just_change_rqpending_by_rqconfirmed = true;
                    }
                    //  pending change status to previus request pendings
                }

                if(++item_pos > 10)        break;
            }
            list_historic_item.push_front(item);
            signal_new_item_added.emit(item);
        }
    }
    else    //  there is not confirmation or reject item
    {
        list_historic_item.push_front(item);
        signal_new_item_added.emit(item);
    }
    return result_error;
}



std::string  order_historic_dangerous_not_signal_warped::add_item(const order_historic_item& item)
{
    return  add_item_check_for_previus_request__fill_delay_if_so_and_signal_new_or_modif_item(item,
                                                                                            *list_historic_item,
                                                                                            signal_new_item_added,
                                                                                            signal_modified_item);
}


std::string   order_historic_dangerous_not_signal_warped::get_lasttr_rjdescr (void)  const
{
    if(list_historic_item->size()>0  &&  list_historic_item->front().type  ==  tt_rj)
        return list_historic_item->front().remarks;
    else
        return "";
}



};      //  namespace  hist {
};      //  namespace  trd
};      //  namespace  mtk {
