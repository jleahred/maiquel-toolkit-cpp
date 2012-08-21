#ifndef QMTKMISC_H
#define QMTKMISC_H


#include <QString>
#include "support/fixed_number.h"

#include <QDropEvent>
#include <QColor>
#include <QDate>

#include "components/msg_common.h"

#include "components/trading/msg_trd_cli_ls.h"
#include "components/trading/msg_trd_cli_mk.h"
#include "components/trading/trd_cli_ls.h"
#include "components/trading/trd_cli_mk.h"
#include "components/trading/trd_cli_sm.h"
#include "components/trading/trd_cli_sl.h"



namespace qtmisc {


QString     fn_as_QString(const mtk::FixedNumber& fn);
QString     nullable_fn_as_QString(const mtk::nullable<mtk::FixedNumber>& fn);
QString     side_as_text(mtk::trd::msg::enBuySell side);

mtk::dtDateTime   QDate_as_mtk_DateTime(const  QDate&  qdate);


QString                             dragProductText         (const mtk::msg::sub_product_code& product);
mtk::msg::sub_product_code          get_product_code        (QDropEvent *event);
bool                                has_product_code        (QDropEvent *event);
QString                             get_property_value      (QDropEvent *event, const QString&  prop_name);
QString                             dragProductText__ext    (const mtk::msg::sub_product_code& product, const mtk::list<mtk::tuple<QString, QString> >&  ext_info);



void  copy_execs_clipboard(const mtk::list<mtk::trd::msg::CF_EXLK>&  execs);





template<typename  ORDER_TYPE>
mtk::trd::msg::sub_invariant_order_info      get_order_invariant (ORDER_TYPE& order)
{
    if (order.last_confirmation().HasValue())
        return order.last_confirmation().Get().invariant;
    else if (order.last_request().HasValue())
        return order.last_request().Get().invariant;
    else
        throw mtk::Alarm(MTK_HERE, "qmtk_misc", "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
}

template<typename  ORDER_TYPE>
mtk::nullable<mtk::trd::msg::sub_total_executions>      get_order_total_executions (ORDER_TYPE& order)
{
    if (order.last_confirmation().HasValue())
        return mtk::make_nullable(order.last_confirmation().Get().total_execs);
    else
        return  mtk::nullable<mtk::trd::msg::sub_total_executions>();
}

template<typename  ORDER_TYPE>
std::string       get_order_remarks (ORDER_TYPE& order)
{
    std::string result;
    if (order.last_confirmation().HasValue())
    {
        result += order.last_confirmation().Get().market_pos.cli_ref;
        std::string  last_tr_descr = order.history()->get_lasttr_descr();
        if(last_tr_descr != "")
            result +=  "  /   " + last_tr_descr;
    }
    else if (order.last_request().HasValue())
        result += order.last_request().Get().request_pos.cli_ref;
    else
        throw mtk::Alarm(MTK_HERE, "qmtk_misc", "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
    return result + "  "  + order.serrors();
}






//  by order type   access   ****************************************************************************************
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_ls_dangerous_signals_not_warped& order);
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_mk_dangerous_signals_not_warped& order);
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_sm_dangerous_signals_not_warped& order);
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_sl_dangerous_signals_not_warped& order);
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_ls                             & order);
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_mk                             & order);
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_sm                             & order);
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_sl                             & order);


template<typename  ORDER_TYPE>
mtk::FixedNumber   get_order_position_quantity  (const ORDER_TYPE& order)
{
    if(order.has_pending_rq())
        return order.last_request().Get().request_pos.quantity;
    else
        return order.last_confirmation().Get().market_pos.quantity;
}




mtk::trd::msg::sub_position_ls      get_request  (mtk::trd::trd_cli_ls_dangerous_signals_not_warped& order);
mtk::trd::msg::sub_position_mk      get_request  (mtk::trd::trd_cli_mk_dangerous_signals_not_warped& order);
mtk::trd::msg::sub_position_ls      get_request  (mtk::trd::trd_cli_ls                             & order);
mtk::trd::msg::sub_position_mk      get_request  (mtk::trd::trd_cli_mk                             & order);


};      //      namespace qtmisc {

#endif // QMTKMISC_H
