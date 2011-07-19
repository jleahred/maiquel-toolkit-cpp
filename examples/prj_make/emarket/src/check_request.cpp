#include "check_request.h"


#include "components/admin/admin.h"



check_request::check_request()
{
    static  std::string   oms_from = mtk::admin::get_config_property("OMS_CHAIN.from").Get();
    
    std::cout << "connecting oms_RQ_NW_LS... ";
    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_rqnwls,
                            mtk::admin::get_url("server"),
                            "SRVTESTING",
                            mtk::trd::msg::oms_RQ_NW_LS::get_in_subject("MARKET", "*", oms_from),
                            mtk::trd::msg::oms_RQ_NW_LS,
                            oms_RQ_NW_LS)
    std::cout << " ok" << std::endl;
    
    std::cout << "connecting oms_RQ_MD_LS... ";
    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_rqmdls,
                            mtk::admin::get_url("server"),
                            "SRVTESTING",
                            mtk::trd::msg::oms_RQ_MD_LS::get_in_subject("MARKET", "*", oms_from),
                            mtk::trd::msg::oms_RQ_MD_LS,
                            oms_RQ_MD_LS)
    std::cout << " ok" << std::endl;

    std::cout << "connecting oms_RQ_CC_LS... ";
    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_rqccls,
                            mtk::admin::get_url("server"),
                            "SRVTESTING",
                            mtk::trd::msg::oms_RQ_CC_LS::get_in_subject("MARKET", "*", oms_from),
                            mtk::trd::msg::oms_RQ_CC_LS,
                            oms_RQ_CC_LS)
    std::cout << " ok" << std::endl;

}

check_request::~check_request()
{
}



//std::string verif_is_valid_request(const mtk::trd::msg::oms_RQ_NW_LS& rq)
template<typename  RQ_TYPE>
std::string verif_is_valid_request(const RQ_TYPE& rq)
{
    return rq.reject_description;
}

void check_request::oms_RQ_CC_LS(const mtk::trd::msg::oms_RQ_CC_LS& rq)
{
    std::cout << mtk::dtNowLocal() << "  received... " << __FUNCTION__ << std::endl;
    std::string reject_reason = verif_is_valid_request(rq);
    sig_oms_rq_cc.emit(mtk::trd::msg::oms_RQ_CC_LS(rq, reject_reason, ""));
}

void check_request::oms_RQ_MD_LS(const mtk::trd::msg::oms_RQ_MD_LS& rq)
{
    std::cout << mtk::dtNowLocal() << "  received... " << __FUNCTION__ << std::endl;
    std::string reject_reason = verif_is_valid_request(rq);
    sig_oms_rq_md.emit(mtk::trd::msg::oms_RQ_MD_LS(rq, reject_reason, ""));
}

void check_request::oms_RQ_NW_LS(const mtk::trd::msg::oms_RQ_NW_LS& rq)
{
    std::cout << mtk::dtNowLocal() << "  received... " << __FUNCTION__ << std::endl;
    std::string reject_reason = verif_is_valid_request(rq);
    sig_oms_rq_nw.emit(mtk::trd::msg::oms_RQ_NW_LS(rq, reject_reason, ""));
}
