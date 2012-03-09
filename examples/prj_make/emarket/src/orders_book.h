#ifndef ORDERS_BOOK_H
#define ORDERS_BOOK_H

#include "support/basic_types.hpp"
#include "support/signalslot.hpp"
#include "ord_ls.h"

class internal_orders_book;
namespace  emarket {  class  sub_product_config;  };



class orders_book  :  public mtk::SignalReceptor
{
    mtk::non_copyable  nc;
public:
	orders_book();
	~orders_book();

    //  in  check_request->book_orders
    void oms_RQ_NW_LS(const mtk::trd::msg::oms_RQ_NW_LS& rq);
    void oms_RQ_MD_LS(const mtk::trd::msg::oms_RQ_MD_LS& rq);
    void oms_RQ_CC_LS(const mtk::trd::msg::oms_RQ_CC_LS& rq);

    void oms_RQ_NW_MK(const mtk::trd::msg::oms_RQ_NW_MK& rq);


    void add_product (const emarket::sub_product_config&  product_config);


private:

    internal_orders_book*  ptr;
};

#endif // ORDERS_BOOK_H

