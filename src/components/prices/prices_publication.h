#ifndef  __mtk_prices_publication__
#define  __mtk_prices_publication__


#include "msg_prices.h"
#include "components/msg_common.h"





namespace mtk {
namespace prices {

namespace publ {


    void  send_best_prices      (const mtk::msg::sub_product_code&  product_code,  const mtk::prices::msg::sub_best_prices&  best_prices);
    void  send_last_exec_ticker (const mtk::msg::sub_product_code&  product_code,  const mtk::prices::msg::sub_last_mk_execs_ticker&  last_mk_execs_ticker);


    mtk::tuple<mtk::nullable<mtk::prices::msg::sub_best_prices>, mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker> >
    decompact_prices(const std::string& compacted_prices);


};  //  namespace publ {
};  //  namespace prices {
};  //  namespace mtk {


#endif   //__mtk_prices_publication__
