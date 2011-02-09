#include "check_request.h"



const char* URL = "amqp:tcp:127.0.0.1:5672";
const char* IN_ADDRESS = "CLITRD";


check_request::check_request()
{
    std::cout << "connecting RQ_NW_LS... ";
    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_rqnwls,
                            URL,
                            IN_ADDRESS,
                            mtk::trd::msg::RQ_NW_LS::get_in_subject("*", "MARKET", "*"),
                            mtk::trd::msg::RQ_NW_LS,
                            RQ_NW_LS)
    std::cout << " ok" << std::endl;
    
    std::cout << "connecting RQ_MD_LS... ";
    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_rqmdls,
                            URL,
                            IN_ADDRESS,
                            mtk::trd::msg::RQ_MD_LS::get_in_subject("*", "MARKET", "*"),
                            mtk::trd::msg::RQ_MD_LS,
                            RQ_MD_LS)
    std::cout << " ok" << std::endl;

    std::cout << "connecting RQ_CC_LS... ";
    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_rqccls,
                            URL,
                            IN_ADDRESS,
                            mtk::trd::msg::RQ_CC_LS::get_in_subject("*", "MARKET", "*"),
                            mtk::trd::msg::RQ_CC_LS,
                            RQ_CC_LS)
    std::cout << " ok" << std::endl;

}

check_request::~check_request()
{
}

std::string verif_is_valid_request(const mtk::trd::msg::RQ_XX_LS& /*rq*/)
{
    return "";
}

void check_request::RQ_CC_LS(const mtk::trd::msg::RQ_CC_LS& rq)
{
    std::cout << mtk::dtNowLocal() << "  received... " << __FUNCTION__ << std::endl;
    std::string reject_reason = verif_is_valid_request(rq);
    sig_oms_rq_cc.emit(mtk::trd::msg::oms_RQ_CC_LS(rq, reject_reason));
}

void check_request::RQ_MD_LS(const mtk::trd::msg::RQ_MD_LS& rq)
{
    std::cout << mtk::dtNowLocal() << "  received... " << __FUNCTION__ << std::endl;
    std::string reject_reason = verif_is_valid_request(rq);
    sig_oms_rq_md.emit(mtk::trd::msg::oms_RQ_MD_LS(rq, reject_reason));
}

void check_request::RQ_NW_LS(const mtk::trd::msg::RQ_NW_LS& rq)
{
    std::cout << mtk::dtNowLocal() << "  received... " << __FUNCTION__ << std::endl;
    std::string reject_reason = verif_is_valid_request(rq);
    sig_oms_rq_nw.emit(mtk::trd::msg::oms_RQ_NW_LS(rq, reject_reason));
}
