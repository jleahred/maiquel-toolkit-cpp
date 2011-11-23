#ifndef QMTKMISC_H
#define QMTKMISC_H


#include <QString>
#include "support/fixed_number.h"

#include <QDropEvent>
#include <QColor>

#include "components/msg_common.h"

#include "components/trading/msg_trd_cli_ls.h"
#include "components/trading/msg_trd_cli_mk.h"
#include "components/trading/trd_cli_ls.h"
#include "components/trading/trd_cli_mk.h"



namespace qtmisc {


QString     fn_as_QString(const mtk::FixedNumber& fn);
QString     nullable_fn_as_QString(const mtk::nullable<mtk::FixedNumber>& fn);
QString     side_as_text(mtk::trd::msg::enBuySell side);


QString                             dragProductText (const mtk::msg::sub_product_code& product);
mtk::msg::sub_product_code          get_product_code(QDropEvent *event);


//const QColor mtk_yellow(QColor(Qt::yellow).lighter(150));
//const QColor mtk_yellow(QColor(227,233,255));
const QColor mtk_color_header       (QColor(191,219,255));
const QColor mtk_color_problem      (QColor(Qt::red));
const QColor mtk_color_sell         (QColor(Qt::red).lighter(160));
const QColor mtk_color_buy          (QColor(Qt::green).lighter(160));
const QColor mtk_color_sell_cell    (QColor(255,215,225));
const QColor mtk_color_buy_cell     (QColor(215,255,225));
const QColor mtk_color_executed     (QColor(Qt::cyan).lighter(120));
//const QColor mtk_color_executed     (QColor(255, 175, 75));
const QColor mtk_color_pending      (QColor(Qt::yellow).lighter(150));
const QColor mtk_color_null         (QColor(40, 0, 60));
const QColor mtk_color_rejected     (QColor(100, 0, 50));
const QColor mtk_color_blinking     (QColor(100, 0, 50));



int  get_base_font_size(void);
void set_base_font_size(int new_size);






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
        result += order.last_confirmation().Get().market_pos.cli_ref;
    else if (order.last_request().HasValue())
        result += order.last_request().Get().request_pos.cli_ref;
    else
        throw mtk::Alarm(MTK_HERE, "qmtk_misc", "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
    return result + order.serrors();
}






//  by order type   access   ****************************************************************************************
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_ls_dangerous_signals_not_warped& order);
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_mk_dangerous_signals_not_warped& order);
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_ls                             & order);
mtk::nullable<mtk::FixedNumber>     get_order_position_price  (mtk::trd::trd_cli_mk                             & order);

mtk::FixedNumber   get_order_position_quantity  (mtk::trd::trd_cli_ls_dangerous_signals_not_warped& order);
mtk::FixedNumber   get_order_position_quantity  (mtk::trd::trd_cli_mk_dangerous_signals_not_warped& order);
mtk::FixedNumber   get_order_position_quantity  (mtk::trd::trd_cli_ls                             & order);
mtk::FixedNumber   get_order_position_quantity  (mtk::trd::trd_cli_mk                             & order);

mtk::trd::msg::sub_position_ls      get_request  (mtk::trd::trd_cli_ls_dangerous_signals_not_warped& order);
mtk::trd::msg::sub_position_mk      get_request  (mtk::trd::trd_cli_mk_dangerous_signals_not_warped& order);
mtk::trd::msg::sub_position_ls      get_request  (mtk::trd::trd_cli_ls                             & order);
mtk::trd::msg::sub_position_mk      get_request  (mtk::trd::trd_cli_mk                             & order);


};      //      namespace qtmisc {

#endif // QMTKMISC_H
