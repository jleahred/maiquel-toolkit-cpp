#include "trd_cli_ls.h"






//#include "components/trading/msg_trd_cli_ls.h"
#include "support/mtk_string.h"
#include "support/fixed_number.h"
#include "support/nullable.hpp"
#include "support/mtk_double.h"

#include "components/trading/msg_trd_common_support.h"




#define CHECK_REQUEST_AND_WRITE_LAST_REQ \
        int nerrors = 0;         \
        mtk::tuple<int, std::string> tresult;    \
        tresult = mtk::trd::msg::check_request_request<mtk::trd::msg::RQ_XX_LS>   (rq, last_request     ()   ); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        tresult = check_request_last_confirm(rq, last_confirmation()   ); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        (void)nerrors;   \
        ci->set_last_request(mtk::make_nullable( static_cast<const mtk::trd::msg::RQ_XX_LS&>(rq)));  

#define CHECK_REQUEST_MOD_AND_WRITE_LAST_REQ \
        int nerrors = 0;         \
        mtk::tuple<int, std::string> tresult;    \
        tresult = mtk::trd::msg::check_request_request<mtk::trd::msg::RQ_XX_LS>(rq, last_request     ()   ); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        tresult = mtk::trd::msg::check_request_last_confirm<mtk::trd::msg::RQ_XX_LS, mtk::trd::msg::CF_XX_LS>(rq, last_confirmation()   ); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        tresult = mtk::trd::msg::check_request_not_modifying<mtk::trd::msg::RQ_XX_LS, mtk::trd::msg::CF_XX_LS>(rq, last_request(), last_confirmation() ); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        (void)nerrors;   \
        ci->set_last_request(mtk::make_nullable( static_cast<const mtk::trd::msg::RQ_XX_LS&>(rq)));





#define CHECK_CONFIRM_AND_WRITE_LAST_CONF \
        int nerrors = 0;         \
        mtk::tuple<int, std::string> tresult;    \
        tresult = check_confirm_request      (cf, last_request     ()); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        tresult = mtk::trd::msg::check_confirm__last_confirm<mtk::trd::msg::CF_XX_LS>(cf, last_confirmation()); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        (void)nerrors;    \
        ci->set_last_confirmation(mtk::make_nullable(static_cast<mtk::trd::msg::CF_XX_LS>(cf)));   





#define CHECK_REJECT_AND_WRITE_LAST_CONF \
        int nerrors = 0;         \
        mtk::tuple<int, std::string> tresult;    \
        tresult = check_reject_request      (rj, last_request     ()); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        (void)nerrors;  \
        tresult = mtk::trd::msg::check_reject__last_confirm<mtk::trd::msg::CF_XX_LS>(rj, last_confirmation());\
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        (void)nerrors;    \
        ci->set_last_confirmation(mtk::make_nullable(static_cast<mtk::trd::msg::CF_XX_LS>(rj)));   


#define IF_LAST_CONF_ISNULL__WRITE_IT  \
        if(ci->last_confirmation().HasValue() == false)      \
            ci->set_last_confirmation(mtk::make_nullable(static_cast<mtk::trd::msg::CF_XX_LS>(st)));   



#define CHECK_EXEC     //nerrors += check_confirm__last_confirm(ex, last_confirmation());



    

#define CREATE_AND_SEND_REJECT(__SIGNAL_TYPE__, __MSG_TYPE__) \
    mtk::CountPtr<mtk::trd::msg::__MSG_TYPE__> cptr_rj;    \
    if (last_confirmation().HasValue())    \
    {               \
        mtk::trd::msg::CF_XX cfxx(rq.invariant, last_confirmation().Get().market_order_id, rq.request_info.req_id, rq.cli_ref, last_confirmation().Get().total_execs, mtk::admin::get_control_fluct_info());  \
        mtk::trd::msg::CF_XX_LS  rjxx(cfxx, last_confirmation().Get().market_pos);      \
        cptr_rj = mtk::make_cptr(new mtk::trd::msg::__MSG_TYPE__(mtk::trd::msg::RJ_XX_LS(rjxx, MTK_SS(ci->__serrors << " in " << method_name), last_request().Get().request_pos))); \
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
            mtk::trd::msg::CF_XX cfxx(rq.invariant, MTK_SS(market_order_id), rq.request_info.req_id, rq.cli_ref, total_execs, mtk::admin::get_control_fluct_info());  \
            mtk::trd::msg::CF_XX_LS  rjxx(cfxx, last_request().Get().request_pos);      \
            cptr_rj = mtk::make_cptr(new mtk::trd::msg::__MSG_TYPE__(mtk::trd::msg::RJ_XX_LS(rjxx, ci->__serrors, last_request().Get().request_pos))); \
            ci->__SIGNAL_TYPE__(*cptr_rj);  \
        }    \
        else     \
            mtk::AlarmMsg(mtk::Alarm("SEND_REJECT", "trd_cli_ls.cpp", MTK_SS("Missing last_request trying to reject "), mtk::alPriorCritic, mtk::alTypeNoPermisions));    \
    }   \
    mtk::trd::msg::__MSG_TYPE__& csr_rj  = *cptr_rj;





#define  ADD_HIST_RQ(__VAR_NAME__, __nw_md_cc__)\
    {       \
        using namespace mtk::trd::hist;       \
        std::string result_additem = ci->history()->add_item(order_historic_item({false, tt_rq_pending, tt2_##__nw_md_cc__,        \
                        mtk::dtNowLocal(), mtk::dtSeconds(0), __VAR_NAME__.request_info.req_id,        \
                        mtk::make_nullable(__VAR_NAME__.request_pos.price), __VAR_NAME__.request_pos.quantity,        \
                        __VAR_NAME__.cli_ref, "", ""}));       \
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
                        mtk::make_nullable(__VAR_NAME__.market_pos.price), __VAR_NAME__.market_pos.quantity,        \
                        __VAR_NAME__.cli_ref, "", ""}));       \
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
                        mtk::make_nullable(__VAR_NAME__.request_pos.price), __VAR_NAME__.request_pos.quantity,        \
                        __VAR_NAME__.cli_ref, "", __VAR_NAME__.reject_description }));       \
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
                        mtk::make_nullable(ex.executed_pos.price), ex.executed_pos.quantity,        \
                        __VAR_NAME__.cli_ref, "", ""}));       \
        if(result_additem != "")        \
        {       \
            ci->__serrors += result_additem;        \
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "ADD_HIST", result_additem, mtk::alPriorCritic, mtk::alTypeNoPermisions));    \
        }       \
    }


#include "components/trading/trd_cli_ls.impl"           //-----------------------------------------------------------



