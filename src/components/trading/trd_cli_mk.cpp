#include "trd_cli_mk.h"






//#include "components/trading/msg_trd_cli_mk.h"
#include "support/mtk_string.h"
#include "support/fixed_number.h"
#include "support/nullable.hpp"
#include "support/mtk_double.h"

#include "components/trading/msg_trd_common_support.h"




#define CHECK_REQUEST_AND_WRITE_LAST_REQ \
    {   \
        mtk::tuple<int, std::string> tresult;    \
        tresult = mtk::trd::msg::check_request_request<mtk::trd::msg::RQ_XX_MK>   (rq, last_request     ()   ); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        mtk::tuple<int, std::string, bool> tresult2;    \
        tresult2 = check_request_last_confirm(rq, last_confirmation()   ); \
        nerrors += tresult2._0;    \
        ci->__serrors += tresult2._1;    \
        qty_lower_exec = tresult2._2;    \
        (void)nerrors;   \
        (void)qty_lower_exec;   \
        ci->set_last_request(mtk::make_nullable( static_cast<const mtk::trd::msg::RQ_XX_MK&>(rq))); \
    }

#define CHECK_REQUEST_MOD_AND_WRITE_LAST_REQ \
    {   \
        mtk::tuple<int, std::string> tresult;    \
        tresult = mtk::trd::msg::check_request_request<mtk::trd::msg::RQ_XX_MK>(rq, last_request     ()   ); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        mtk::tuple<int, std::string, bool> tresult2;    \
        tresult2 = mtk::trd::msg::check_request_last_confirm<mtk::trd::msg::RQ_XX_MK, mtk::trd::msg::CF_XX_MK>(rq, last_confirmation()   ); \
        nerrors += tresult2._0;    \
        ci->__serrors += tresult2._1;    \
        qty_lower_exec = tresult2._2;    \
        tresult = mtk::trd::msg::check_request_not_modifying<mtk::trd::msg::RQ_XX_MK, mtk::trd::msg::CF_XX_MK>(rq, last_request(), last_confirmation() ); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        (void)nerrors;   \
        ci->set_last_request(mtk::make_nullable( static_cast<const mtk::trd::msg::RQ_XX_MK&>(rq))); \
    }





#define CHECK_CONFIRM_AND_WRITE_LAST_CONF \
    {   \
        mtk::tuple<int, std::string> tresult;    \
        tresult = check_confirm      (cf); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        tresult = check_confirm_request      (cf, last_request     ()); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        tresult = mtk::trd::msg::check_confirm__last_confirm<mtk::trd::msg::CF_XX_MK>(cf, last_confirmation()); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        (void)nerrors;    \
        ci->set_last_confirmation(mtk::make_nullable(static_cast<mtk::trd::msg::CF_XX_MK>(cf)));    \
    }





#define CHECK_REJECT_AND_WRITE_LAST_CONF \
    {   \
        mtk::tuple<int, std::string> tresult;    \
        tresult = check_confirm      (rj); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        tresult = check_reject_request      (rj, last_request     ()); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        (void)nerrors;  \
        tresult = mtk::trd::msg::check_reject__last_confirm<mtk::trd::msg::CF_XX_MK>(rj, last_confirmation());\
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        (void)nerrors;    \
        ci->set_last_confirmation(mtk::make_nullable(static_cast<mtk::trd::msg::CF_XX_MK>(rj)));    \
    }


#define IF_LAST_CONF_ISNULL__WRITE_IT  \
        if(ci->last_confirmation().HasValue() == false)      \
            ci->set_last_confirmation(mtk::make_nullable(static_cast<mtk::trd::msg::CF_XX_MK>(st)));



#define CHECK_EXEC     \
        {   \
            mtk::tuple<int, std::string> tresult;    \
            std::string s_errors;   \
            int   n_errors;   \
            tresult = check_exec__last_confirm      (ex, last_confirmation());   \
            tresult.assign(n_errors, s_errors);   \
            ci->__serrors += tresult._1;    \
            if (nerrors >0)   \
            {   \
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_exec__last_confirm", s_errors, mtk::alPriorCritic, mtk::alTypeNoPermisions));   \
                ci->__serrors += s_errors;   \
            }   \
        }    \






#define CREATE_AND_SEND_REJECT(__SIGNAL_TYPE__, __MSG_TYPE__, __DESCRIPTION__) \
    mtk::CountPtr<mtk::trd::msg::__MSG_TYPE__> cptr_rj;    \
    if (last_confirmation().HasValue())    \
    {               \
        mtk::trd::msg::CF_XX cfxx(rq.invariant, last_confirmation().Get().market_order_id, rq.request_info.req_id, last_confirmation().Get().total_execs, __DESCRIPTION__, mtk::admin::get_control_fluct_info());  \
        mtk::trd::msg::CF_XX_MK  rjxx(cfxx, last_confirmation().Get().market_pos);      \
        cptr_rj = mtk::make_cptr(new mtk::trd::msg::__MSG_TYPE__(mtk::trd::msg::RJ_XX_MK(rjxx, last_request().Get().request_pos))); \
        ci->__SIGNAL_TYPE__(*cptr_rj);  \
    }     \
    else      \
    {      \
        static int market_order_id =0;   \
        ++market_order_id;   \
        if (last_request().HasValue()==true)      \
        {      \
            mtk::trd::msg::sub_total_executions total_execs(0.,     \
                                                mtk::FixedNumber(mtk::fnDouble(0.),  mtk::fnDec(0),  mtk::fnInc(1)),    \
                                                mtk::FixedNumber(mtk::fnDouble(0.),  mtk::fnDec(0),  mtk::fnInc(1)) );    \
            mtk::trd::msg::CF_XX cfxx(rq.invariant, MTK_SS(market_order_id), rq.request_info.req_id, total_execs, ci->__serrors + __DESCRIPTION__, mtk::admin::get_control_fluct_info());  \
            mtk::trd::msg::CF_XX_MK  rjxx(cfxx, last_request().Get().request_pos);      \
            cptr_rj = mtk::make_cptr(new mtk::trd::msg::__MSG_TYPE__(mtk::trd::msg::RJ_XX_MK(rjxx, last_request().Get().request_pos))); \
            ci->__SIGNAL_TYPE__(*cptr_rj);  \
        }    \
        else     \
            mtk::AlarmMsg(mtk::Alarm("SEND_REJECT", "trd_cli_mk.cpp", MTK_SS("Missing last_request trying to reject "), mtk::alPriorCritic, mtk::alTypeNoPermisions));    \
    }   \
    mtk::trd::msg::__MSG_TYPE__& csr_rj  = *cptr_rj;





#define  ADD_HIST_RQ(__VAR_NAME__, __nw_md_cc__)\
    {       \
        using namespace mtk::trd::hist;       \
        std::string result_additem = ci->history()->add_item(order_historic_item({false, tt_rq_pending, tt2_##__nw_md_cc__,        \
                        mtk::dtNowLocal(), mtk::dtSeconds(0), __VAR_NAME__.request_info.req_id,        \
                        mtk::nullable<mtk::FixedNumber>(), __VAR_NAME__.request_pos.quantity,        \
                        __VAR_NAME__.request_pos.cli_ref, "", ""}));       \
        if(result_additem != "")        \
        {       \
            ci->__serrors += result_additem;        \
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "ADD_HIST", result_additem, mtk::alPriorCritic, mtk::alTypeNoPermisions));    \
        }       \
    }



#define  ADD_HIST_CF(__VAR_NAME__, __nw_md_cc__)  \
    {       \
        using namespace mtk::trd::hist;       \
        std::string result_additem = ci->history()->add_item(order_historic_item({false, tt_cf, tt2_##__nw_md_cc__,        \
                        mtk::dtNowLocal(), mtk::dtSeconds(0), __VAR_NAME__.req_id,        \
                        mtk::nullable<mtk::FixedNumber>(), __VAR_NAME__.market_pos.quantity,        \
                        __VAR_NAME__.market_pos.cli_ref, __VAR_NAME__.market_order_id, __VAR_NAME__.description}));       \
        if(result_additem != "")        \
        {       \
            ci->__serrors += result_additem;        \
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "ADD_HIST", result_additem, mtk::alPriorCritic, mtk::alTypeNoPermisions));    \
        }       \
    }

#define  ADD_HIST_RJ(__VAR_NAME__, __nw_md_cc__)  \
    {       \
        using namespace mtk::trd::hist;       \
        std::string result_additem = ci->history()->add_item(order_historic_item({false, tt_rj, tt2_##__nw_md_cc__,        \
                        mtk::dtNowLocal(), mtk::dtSeconds(0), __VAR_NAME__.req_id,        \
                        mtk::nullable<mtk::FixedNumber>(), __VAR_NAME__.request_pos.quantity,        \
                        __VAR_NAME__.request_pos.cli_ref, __VAR_NAME__.market_order_id, __VAR_NAME__.description }));       \
        if(result_additem != "")        \
        {       \
            ci->__serrors += result_additem;        \
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "ADD_HIST", result_additem, mtk::alPriorCritic, mtk::alTypeNoPermisions));    \
        }       \
    }


#define  ADD_HIST_CFEX(__VAR_NAME__)  \
    {       \
        using namespace mtk::trd::hist;       \
        std::string result_additem = ci->history()->add_item(order_historic_item({false, tt_cf, tt2_ex,        \
                        mtk::dtNowLocal(), mtk::dtSeconds(0), __VAR_NAME__.req_id,        \
                        mtk::nullable<mtk::FixedNumber>(), __VAR_NAME__.executed_pos.quantity,        \
                        __VAR_NAME__.market_pos.cli_ref, __VAR_NAME__.executed_pos.exec_id, __VAR_NAME__.description}));       \
        if(result_additem != "")        \
        {       \
            ci->__serrors += result_additem;        \
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "ADD_HIST", result_additem, mtk::alPriorCritic, mtk::alTypeNoPermisions));    \
        }       \
    }




#include "components/trading/trd_cli_mk.impl"           //-----------------------------------------------------------



