#include "ord_ls.h"






#include "support/mtk_string.h"
#include "support/fixed_number.h"
#include "support/nullable.hpp"
#include "support/mtk_double.h"



int get_sequence(void)
{
    static int sequence=0;
    return ++sequence;
}

#define __INTERNAL_CHECK_EQUAL(P1, P2) \
    if (P1 !=  P2)   \
    {   \
        serrors += MTK_SS(#P1 #P2 << "  "  <<  P1 << "!=" <<  P2 << std::endl); \
        ++nerrors; \
    }



int check_request_request(const mtk::trd::msg::RQ_XX_LS& rq, const mtk::nullable<mtk::trd::msg::RQ_XX_LS>& last_request, std::string& serrors)
{
    int nerrors=0;
    
    if (is_valid(rq.order_id)==false)
    {
        ++nerrors;
        serrors += "  invalid order_id on request!!!  ";
    }
    if (is_valid(rq.product_code)==false)
    {
        ++nerrors;
        serrors += "  invalid product_code on request!!!  ";
    }

    if (rq.request_pos.quantity.GetIntCode() == 0)
    {
        ++nerrors;
        serrors += "  invalid quantiy!!!  ";
    }

    if (last_request.HasValue() == true)
    {
        __INTERNAL_CHECK_EQUAL(last_request.Get().order_id         , rq.order_id        )
        __INTERNAL_CHECK_EQUAL(last_request.Get().product_code     , rq.product_code    )
        __INTERNAL_CHECK_EQUAL(last_request.Get().request_pos.side , rq.request_pos.side)
    }
    
    if (nerrors >0)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_confirm_request", MTK_SS(serrors << "  " << rq << " / " << last_request), mtk::alPriorCritic, mtk::alTypeNoPermisions));
        ++nerrors;
    }
    return nerrors;
}



int check_request_last_confirm(const mtk::trd::msg::RQ_XX_LS& rq, const mtk::nullable<mtk::trd::msg::CF_XX_LS>& last_conf, std::string& serrors)
{
    if (last_conf.HasValue() == false)     return 0;
    
    int nerrors=0;

    if (is_valid(rq.order_id)==false)
    {
        ++nerrors;
        serrors += "  invalid order_id on request!!!  ";
    }
    if (is_valid(rq.product_code)==false)
    {
        ++nerrors;
        serrors += "  invalid product_code on request!!!  ";
    }

    __INTERNAL_CHECK_EQUAL(rq.order_id          , last_conf.Get().confirmated_info.order_id        )
    __INTERNAL_CHECK_EQUAL(rq.request_pos.side  , last_conf.Get().confirmated_info.market_pos.side )
    
    if (last_conf.HasValue()  &&  mtk::Double(last_conf.Get().confirmated_info.total_execs.quantity.GetDouble()) >= (mtk::Double(rq.request_pos.quantity.GetDouble())))
    {
        serrors += "  requested quantity lower or equal than executed quantity!!!  ";
        ++nerrors;
    }
    

    if (nerrors >0)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_confirm_request", MTK_SS(serrors << "  " << rq << " / " << last_conf), mtk::alPriorCritic, mtk::alTypeNoPermisions));
        ++nerrors;
    }
    return nerrors;
}

int check_request_not_modifying(const mtk::trd::msg::RQ_XX_LS& rq, const mtk::nullable<mtk::trd::msg::RQ_XX_LS>& last_request, const mtk::nullable<mtk::trd::msg::CF_XX_LS>& last_conf, std::string& serrors)
{
    if (last_conf.HasValue() == false)     return 0;
    
    int nerrors=0;

    if (last_request.HasValue()== false  ||  last_request.Get().req_info ==  last_conf.Get().req_info)         //  there are no pending request
        if (rq.request_pos == last_conf.Get().confirmated_info.market_pos)
        {
            //++nerrors;
            //serrors += "  modification not modifying!!!  ";
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_request_not_modifying", MTK_SS("received modification not modifying  rq:" << rq << "  last_conf:" << last_conf.Get()), mtk::alPriorWarning));
        }


    if (nerrors >0)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_request_not_modifying", MTK_SS(serrors << "  " << rq << " / " << last_conf), mtk::alPriorCritic, mtk::alTypeNoPermisions));
        ++nerrors;
    }
    return nerrors;
}

        //nerrors += check_request_not_modifying(rq, last_request(), last_confirmation()  , serrors); 
#define CHECK_REQUEST \
        int nerrors = 0;         \
        std::string serrors;     \
        nerrors += check_request_request     (rq, last_request     ()   ,  serrors); \
        nerrors += check_request_last_confirm(rq, last_confirmation()   ,  serrors); \
        (void)nerrors;   \
        (void)serrors;\
        if (rq.reject_descr != "")  \
        {  \
            ++nerrors;  \
            serrors = rq.reject_descr;  \
        }  \
        ci->set_last_request(mtk::make_nullable( static_cast<const mtk::trd::msg::RQ_XX_LS&>(rq)));




int check_confirm_request(const mtk::trd::msg::CF_XX_LS& cf, const mtk::nullable<mtk::trd::msg::RQ_XX_LS>& last_request, std::string& serrors)
{
    int nerrors=0;

    if (last_request.HasValue()== true)
    {
        __INTERNAL_CHECK_EQUAL(last_request.Get().order_id         , cf.confirmated_info.order_id       )
        __INTERNAL_CHECK_EQUAL(last_request.Get().product_code     , cf.confirmated_info.product_code   )
        __INTERNAL_CHECK_EQUAL(last_request.Get().request_pos.side , cf.confirmated_info.market_pos.side)
    }
    
    if (mtk::Double(cf.confirmated_info.total_execs.quantity.GetDouble()) > (mtk::Double(last_request.Get().request_pos.quantity.GetDouble())))
    {
        serrors += "  over execution!!!  ";
        ++nerrors;
    }
    if (nerrors >0)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_confirm_request", MTK_SS(serrors << "  " << cf << " / " << last_request), mtk::alPriorCritic, mtk::alTypeNoPermisions));
        ++nerrors;
    }
    return nerrors;
}



int check_confirm__last_confirm(const mtk::trd::msg::CF_XX_LS& cf, const mtk::nullable<mtk::trd::msg::CF_XX_LS>& last_conf, std::string& serrors)
{
    if (last_conf.HasValue() == false)     return 0;
    
    int nerrors=0;
    
    __INTERNAL_CHECK_EQUAL(cf.confirmated_info.order_id                 ,   last_conf.Get().confirmated_info.order_id                   )
    __INTERNAL_CHECK_EQUAL(cf.confirmated_info.market_pos.side          ,   last_conf.Get().confirmated_info.market_pos.side            )
    //__INTERNAL_CHECK_EQUAL(cf.confirmated_info.total_execs.remaining_qty,   last_conf.Get().confirmated_info.total_execs.remaining_qty  )
    //__INTERNAL_CHECK_EQUAL(cf.confirmated_info.total_execs.quantity     ,   last_conf.Get().confirmated_info.total_execs.quantity       )

    if (mtk::Double(cf.confirmated_info.total_execs.quantity.GetDouble()) > (mtk::Double(last_conf.Get().confirmated_info.market_pos.quantity.GetDouble())))
    {
        ++nerrors;
        serrors += "  over execution!!!  ";
    }
    if (nerrors >0)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_confirm__last_confirm", MTK_SS(serrors << "  " << cf << " / " << last_conf), mtk::alPriorCritic, mtk::alTypeNoPermisions));
        ++nerrors;
    }
    return nerrors;
}

#define CHECK_CONFIRM \
        int nerrors = 0;         \
        std::string serrors;     \
        nerrors += check_confirm_request      (cf, last_request     (),  serrors); \
        nerrors += check_confirm__last_confirm(cf, last_confirmation(),  serrors); \
        (void)nerrors;    
        //ci->set_last_confirmation(mtk::make_nullable(static_cast<mtk::trd::msg::CF_XX_LS>(cf)));     










int check_reject_request(const mtk::trd::msg::RJ_XX_LS& rj, const mtk::nullable<mtk::trd::msg::RQ_XX_LS>& last_request, std::string& serrors)
{
    int nerrors=0;
    
    if (last_request.HasValue())
    {
        __INTERNAL_CHECK_EQUAL(last_request.Get().order_id        , rj.confirmated_info.order_id        )
        __INTERNAL_CHECK_EQUAL(last_request.Get().product_code    , rj.confirmated_info.product_code    )
    }
    
    if (nerrors >0)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_reject_request", MTK_SS(serrors << "  " << rj << " / " << last_request), mtk::alPriorCritic, mtk::alTypeNoPermisions));
        ++nerrors;
    }
    return nerrors;
}



int check_reject__last_confirm(const mtk::trd::msg::RJ_XX_LS& rj, const mtk::nullable<mtk::trd::msg::CF_XX_LS>& last_conf, std::string& serrors)
{
    if (last_conf.HasValue() == false)     return 0;
    
    
    int nerrors=0;
    
    __INTERNAL_CHECK_EQUAL(rj.confirmated_info.order_id                   , last_conf.Get().confirmated_info.order_id                 )
    __INTERNAL_CHECK_EQUAL(rj.confirmated_info.market_pos.side            , last_conf.Get().confirmated_info.market_pos.side          )
    __INTERNAL_CHECK_EQUAL(rj.confirmated_info.total_execs.quantity       , last_conf.Get().confirmated_info.total_execs.quantity     )
    __INTERNAL_CHECK_EQUAL(rj.confirmated_info.total_execs.remaining_qty  , last_conf.Get().confirmated_info.total_execs.remaining_qty)

    if (nerrors >0)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_reject__last_confirm", MTK_SS(serrors << "  " << rj << " / " << last_conf), mtk::alPriorCritic, mtk::alTypeNoPermisions));
        ++nerrors;
    }
    return nerrors;
}

#define CHECK_REJECT \
        int nerrors = 0;         \
        (void)nerrors;  \
        std::string serrors;     \
        nerrors += check_reject_request      (rj, last_request     (),  serrors); \
        nerrors += check_reject__last_confirm(rj, last_confirmation(),  serrors);




int   check_exec__last_confirm(const mtk::trd::msg::CF_EX_LS& ex, const mtk::nullable<mtk::trd::msg::CF_XX_LS>& last_conf, std::string& serrors)
{
    if (last_conf.HasValue() == false)    
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_exec__last_confirm", MTK_SS("execution received on non confirmated order  " << ex << " / " << last_conf), mtk::alPriorCritic, mtk::alTypeNoPermisions));
        return 1;
    }
    
    int nerrors=0;
    
    __INTERNAL_CHECK_EQUAL(ex.executed_pos.side     ,   last_conf.Get().confirmated_info.market_pos.side    )
    if (mtk::Double(ex.confirmated_info.total_execs.quantity.GetDouble()) !=  
                mtk::Double(ex.executed_pos.quantity.GetDouble()) + mtk::Double(last_conf.Get().confirmated_info.total_execs.quantity.GetDouble()))
    {
        ++nerrors;
        serrors += MTK_SS("  total execution received doesn't match with  execution received and last confirmated execution  "<< ex.confirmated_info.total_execs.quantity << "  !=  "  << ex.executed_pos.quantity  << " + " << last_conf.Get().confirmated_info.total_execs.quantity << std::endl);
        
    }

    if (nerrors >0)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_exec__last_confirm", MTK_SS(serrors << "  " << ex << " / " << last_conf), mtk::alPriorCritic, mtk::alTypeNoPermisions));
        ++nerrors;
    }
    return nerrors;
}
#define CHECK_EXEC      \
        nerrors += check_confirm__last_confirm(ex, last_confirmation(),  serrors);  \
        nerrors += check_exec__last_confirm(ex, last_confirmation(),  serrors);




#define SEND_REJECT(__SIGNAL_TYPE__, __MSG_TYPE__) \
    if (last_confirmation().HasValue())    \
        ci->__SIGNAL_TYPE__(mtk::trd::msg::__MSG_TYPE__(mtk::trd::msg::RJ_XX_LS(rq.req_info, last_confirmation().Get().confirmated_info, serrors, mtk::admin::get_control_fluct_info())));     \
    else      \
    {      \
        if (last_request().HasValue()==true)      \
        {      \
            mtk::trd::msg::RQ_XX_LS  _last_request = last_request().Get();  \
            mtk::trd::msg::sub_order_ls_confirmated to_confirm(    _last_request.order_id,     \
                                                _last_request.product_code,     \
                                                _last_request.request_pos,     \
                                                mtk::trd::msg::sub_total_executions(0.,     \
                                                                                    mtk::FixedNumber(mtk::fnDouble(0.),  mtk::fnDec(0),  mtk::fnInc(1)),    \
                                                                                    mtk::FixedNumber(mtk::fnDouble(0.),  mtk::fnDec(0),  mtk::fnInc(1)) ),    \
                                                _last_request.cli_ref);    \
            ci->__SIGNAL_TYPE__(mtk::trd::msg::__MSG_TYPE__(mtk::trd::msg::RJ_XX_LS(rq.req_info, to_confirm, MTK_SS("Error: Received " << serrors << "  " #__MSG_TYPE__ " on status " << GetStatusName()), mtk::admin::get_control_fluct_info())));    \
        }    \
        else     \
            throw mtk::Alarm(MTK_HERE, "SEND_REJECT", MTK_SS("Missing last_request trying to reject "), mtk::alPriorCritic, mtk::alTypeNoPermisions);    \
    }




#include "ord_ls.impl"



