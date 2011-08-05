#ifndef EMARKET_CHECK_REQUEST_H
#define EMARKET_CHECK_REQUEST_H



#include "components/trading/msg_trd_cli_ls.h"
#include "components/trading/msg_trd_oms_rq.h"
#include "support/signalslot.hpp"
#include "mtk_qpid/mtk_qpid.hpp"


namespace  emarket {  class  sub_product_config;  };



class check_request : public mtk::SignalReceptor {
typedef check_request CLASS_NAME;

public:
    void  init(void);


    //  in  cli(permisions/filter) -> check_request
    void oms_RQ_NW_LS(const mtk::trd::msg::oms_RQ_NW_LS& rq);
    void oms_RQ_MD_LS(const mtk::trd::msg::oms_RQ_MD_LS& rq);
    void oms_RQ_CC_LS(const mtk::trd::msg::oms_RQ_CC_LS& rq);
    
    
    // out -> book_orders
    mtk::Signal<const mtk::trd::msg::oms_RQ_NW_LS&>   sig_oms_rq_nw;
    mtk::Signal<const mtk::trd::msg::oms_RQ_MD_LS&>   sig_oms_rq_md;
    mtk::Signal<const mtk::trd::msg::oms_RQ_CC_LS&>   sig_oms_rq_cc;
    
    mtk::Signal<const emarket::sub_product_config&>   sig_add_product;
    

	check_request();
	~check_request();

private:
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::oms_RQ_NW_LS> > hqpid_rqnwls;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::oms_RQ_MD_LS> > hqpid_rqmdls;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::oms_RQ_CC_LS> > hqpid_rqccls;
};



#endif // EMARKET_CHECK_REQUEST_H
