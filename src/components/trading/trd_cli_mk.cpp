#include "trd_cli_mk.h"






//#include "components/trading/msg_trd_cli_mk.h"
#include "support/mtk_string.h"
#include "support/fixed_number.h"
#include "support/nullable.hpp"
#include "support/mtk_double.h"






#define CHECK_REQUEST \
        int nerrors = 0;         \
        mtk::tuple<int, std::string> tresult;    \
        tresult = mtk::trd::msg::check_request_request<mtk::trd::msg::RQ_XX_MK>   (rq, last_request     ()   ); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        tresult = check_request_last_confirm(rq, last_confirmation()   ); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        (void)nerrors;   \
        ci->set_last_request(mtk::make_nullable( static_cast<const mtk::trd::msg::RQ_XX_MK&>(rq)));  

#define CHECK_REQUEST_MOD \
        int nerrors = 0;         \
        mtk::tuple<int, std::string> tresult;    \
        tresult = mtk::trd::msg::check_request_request<mtk::trd::msg::RQ_XX_MK>(rq, last_request     ()   ); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        tresult = mtk::trd::msg::check_request_last_confirm<mtk::trd::msg::RQ_XX_MK, mtk::trd::msg::CF_XX_MK>(rq, last_confirmation()   ); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        tresult = mtk::trd::msg::check_request_not_modifying<mtk::trd::msg::RQ_XX_MK, mtk::trd::msg::CF_XX_MK>(rq, last_request(), last_confirmation() ); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        (void)nerrors;   \
        ci->set_last_request(mtk::make_nullable( static_cast<const mtk::trd::msg::RQ_XX_MK&>(rq)));





#define CHECK_CONFIRM \
        int nerrors = 0;         \
        mtk::tuple<int, std::string> tresult;    \
        tresult = check_confirm_request      (cf, last_request     ()); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        tresult = mtk::trd::msg::check_confirm__last_confirm<mtk::trd::msg::CF_XX_MK>(cf, last_confirmation()); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        (void)nerrors;    \
        ci->set_last_confirmation(mtk::make_nullable(static_cast<mtk::trd::msg::CF_XX_MK>(cf)));   





#define CHECK_REJECT \
        int nerrors = 0;         \
        mtk::tuple<int, std::string> tresult;    \
        tresult = check_reject_request      (rj, last_request     ()); \
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    \
        (void)nerrors;  \
        tresult = mtk::trd::msg::check_reject__last_confirm<mtk::trd::msg::CF_XX_MK>(rj, last_confirmation());\
        nerrors += tresult._0;    \
        ci->__serrors += tresult._1;    




#define CHECK_EXEC     //nerrors += check_confirm__last_confirm(ex, last_confirmation());



    

#define SEND_REJECT(__SIGNAL_TYPE__, __MSG_TYPE__) \
    if (last_confirmation().HasValue())    \
    {               \
        mtk::trd::msg::CF_XX cfxx(rq.invariant, rq.req_info.req_id, rq.cli_ref, last_confirmation().Get().total_execs, mtk::admin::get_control_fluct_info());  \
        mtk::trd::msg::CF_XX_MK  rjxx(cfxx, last_confirmation().Get().market_pos);      \
        mtk::trd::msg::__MSG_TYPE__  _rj_(rjxx, ci->__serrors);  \
        ci->__SIGNAL_TYPE__(_rj_);  \
    }     \
    else      \
    {      \
        if (last_request().HasValue()==true)      \
        {      \
            mtk::trd::msg::sub_total_executions total_execs(0.,     \
                                                mtk::FixedNumber(mtk::fnDouble(0.),  mtk::fnDec(0),  mtk::fnInc(1)),    \
                                                mtk::FixedNumber(mtk::fnDouble(0.),  mtk::fnDec(0),  mtk::fnInc(1)) );    \
            mtk::trd::msg::CF_XX cfxx(rq.invariant, rq.req_info.req_id, rq.cli_ref, total_execs, mtk::admin::get_control_fluct_info());  \
            mtk::trd::msg::CF_XX_MK  rjxx(cfxx, last_request().Get().request_pos);      \
            mtk::trd::msg::__MSG_TYPE__  _rj_(rjxx, ci->__serrors);  \
            ci->__SIGNAL_TYPE__(_rj_);  \
        }    \
        else     \
            throw mtk::Alarm("SEND_REJECT", "trd_cli_mk.cpp", MTK_SS("Missing last_request trying to reject "), mtk::alPriorCritic, mtk::alTypeNoPermisions);    \
    }




#include "components/trading/trd_cli_mk.impl"           //-----------------------------------------------------------



