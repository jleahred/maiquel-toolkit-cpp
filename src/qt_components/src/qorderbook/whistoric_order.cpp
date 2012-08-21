#include "whistoric_order.h"
#include "ui_whistoric_order.h"

#include "components/trading/msg_trd_common.h"
#include "qmtk_misc.h"
#include <QPalette>

#include "ecimd_styles.h"


whistoric_order::whistoric_order(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::whistoric_order)
{
    ui->setupUi(this);
}

whistoric_order::~whistoric_order()
{
    delete ui;
}


void   whistoric_order::set_order(const mtk::trd::msg::sub_order_id& order_id)
{
    if(order_ls.isValid()      &&   (order_id  ==  qtmisc::get_order_invariant(*order_ls).order_id))
        return;

    if(order_mk.isValid()      &&   (order_id  ==  qtmisc::get_order_invariant(*order_mk).order_id))
        return;

    if(order_sm.isValid()      &&   (order_id  ==  qtmisc::get_order_invariant(*order_sm).order_id))
        return;

    if(order_sl.isValid()      &&   (order_id  ==  qtmisc::get_order_invariant(*order_sl).order_id))
        return;

    mtk::trd::trd_cli_ord_book::en_order_type     ot  =  mtk::trd::trd_cli_ord_book::get_order_type(order_id);
    if(ot ==  mtk::trd::trd_cli_ord_book::ot_limit)
    {
        order_ls = mtk::trd::trd_cli_ord_book::get_order_ls(order_id);
        order_mk = mtk::CountPtr<mtk::trd::trd_cli_mk>();
        order_sm = mtk::CountPtr<mtk::trd::trd_cli_sm>();
        order_sl = mtk::CountPtr<mtk::trd::trd_cli_sl>();
        ui->historic->set_historic(mtk::trd::hist::order_historic2_sig_wp_cptr(order_ls->history()));
        MTK_CONNECT_THIS(order_ls->sig_changed, update_on_change);
        ui->executions->set_executions(mtk::trd::hist::order_EXECS_sig_wp_cptr(order_ls->executions()));
    }
    else if(ot ==  mtk::trd::trd_cli_ord_book::ot_market)
    {
        order_ls = mtk::CountPtr<mtk::trd::trd_cli_ls>();
        order_mk = mtk::trd::trd_cli_ord_book::get_order_mk(order_id);
        order_sm = mtk::CountPtr<mtk::trd::trd_cli_sm>();
        order_sl = mtk::CountPtr<mtk::trd::trd_cli_sl>();
        ui->historic->set_historic(mtk::trd::hist::order_historic2_sig_wp_cptr(order_mk->history()));
        MTK_CONNECT_THIS(order_mk->sig_changed, update_on_change);
        ui->executions->set_executions(mtk::trd::hist::order_EXECS_sig_wp_cptr(order_mk->executions()));
    }
    else if(ot ==  mtk::trd::trd_cli_ord_book::ot_stop_market)
    {
        order_ls = mtk::CountPtr<mtk::trd::trd_cli_ls>();
        order_mk = mtk::CountPtr<mtk::trd::trd_cli_mk>();
        order_sm = mtk::trd::trd_cli_ord_book::get_order_sm(order_id);
        order_sl = mtk::CountPtr<mtk::trd::trd_cli_sl>();
        ui->historic->set_historic(mtk::trd::hist::order_historic2_sig_wp_cptr(order_sm->history()));
        MTK_CONNECT_THIS(order_sm->sig_changed, update_on_change);
        ui->executions->set_executions(mtk::trd::hist::order_EXECS_sig_wp_cptr(mtk::make_cptr(new mtk::trd::hist::order_EXECS_historic_dangerous_not_signal_warped)));
    }
    else if(ot ==  mtk::trd::trd_cli_ord_book::ot_stop_limit)
    {
        order_ls = mtk::CountPtr<mtk::trd::trd_cli_ls>();
        order_mk = mtk::CountPtr<mtk::trd::trd_cli_mk>();
        order_sm = mtk::CountPtr<mtk::trd::trd_cli_sm>();
        order_sl = mtk::trd::trd_cli_ord_book::get_order_sl(order_id);
        ui->historic->set_historic(mtk::trd::hist::order_historic2_sig_wp_cptr(order_sl->history()));
        MTK_CONNECT_THIS(order_sl->sig_changed, update_on_change);
        ui->executions->set_executions(mtk::trd::hist::order_EXECS_sig_wp_cptr(mtk::make_cptr(new mtk::trd::hist::order_EXECS_historic_dangerous_not_signal_warped)));
    }

    update_on_change();
}

template<typename  ORDER_TYPE>
bool  is_full_executed(const  ORDER_TYPE&  order);

template<>
bool  is_full_executed<mtk::trd::trd_cli_sm > (const  mtk::trd::trd_cli_sm&  )
{
    return  false;
}

template<>
bool  is_full_executed<mtk::trd::trd_cli_sl > (const  mtk::trd::trd_cli_sl&  )
{
    return  false;
}


template<typename  ORDER_TYPE>
bool  is_full_executed(const  ORDER_TYPE&  order)
{
    return order.is_full_executed();
}



template<typename  ORDER_TYPE>
void fill_from(whistoric_order* _this, ORDER_TYPE& order)
{
    QString  sorder_id      = QLatin1String(qtmisc::get_order_invariant(order).order_id.session_id.c_str()) + QLatin1String(":") + QLatin1String(qtmisc::get_order_invariant(order).order_id.req_code.c_str());
    QString  product_name   = QLatin1String(qtmisc::get_order_invariant(order).product_code.product.c_str());
    QString  side           = qtmisc::side_as_text(qtmisc::get_order_invariant(order).side);
    QString  price          = qtmisc::nullable_fn_as_QString(qtmisc::get_order_position_price(order));
    QString  quantity       = qtmisc::fn_as_QString(qtmisc::get_order_position_quantity(order));

    if(is_full_executed(order)  ||  order.is_canceled())
    {
        price = QLatin1String("");  quantity = QLatin1String("");
    }


    QString  remarks        = QLatin1String(qtmisc::get_order_remarks(order).c_str());


    mtk::nullable<mtk::trd::msg::sub_total_executions>   total_executions = qtmisc::get_order_total_executions(order);
    QString  exec_price;
    QString  exec_quantity;
    QString  rem_quantity;
    if(total_executions.HasValue())
    {
        if(total_executions.Get().acc_quantity.GetIntCode() > 0)
        {

            exec_price     =  QLocale::system().toString(total_executions.Get().sum_price_by_qty.get()._0 / total_executions.Get().acc_quantity.GetDouble().get()._0, 'f', 3);
            exec_quantity  =  QLocale::system().toString(total_executions.Get().acc_quantity.GetDouble().get()._0, 'f', 0);
            rem_quantity   =  QLocale::system().toString(total_executions.Get().remaining_qty.GetDouble().get()._0, 'f', 0);
        }
    }



    _this->ui->order_id->setText(sorder_id);
    _this->ui->product_name->setText(product_name);
    _this->ui->side->setText(side);
    _this->ui->price->setText(price);
    _this->ui->quantity->setText(quantity);
    _this->ui->exec_price->setText(exec_price);
    _this->ui->exec_quantity->setText(exec_quantity);
    _this->ui->rem_quantity->setText(rem_quantity);
    _this->ui->remarks->setText(remarks);

    QColor  side_color;
    if(qtmisc::get_order_invariant(order).side == mtk::trd::msg::buy)
        side_color = ecimd_styles::color_buy;
    else if(qtmisc::get_order_invariant(order).side == mtk::trd::msg::sell)
        side_color = ecimd_styles::color_sell;

    _this->ui->side->setStyleSheet(QLatin1String("background-color: rgb(") +    QString::number(side_color.red()) + QLatin1String(", ") +
                                                                                QString::number(side_color.green()) + QLatin1String(", ") +
                                                                                QString::number(side_color.blue()) +
                                                                                QLatin1String(") "));

}

void whistoric_order::update_on_change(void)
{
    if(order_ls.isValid())
        fill_from(this, *order_ls);

    else if(order_mk.isValid())
        fill_from(this, *order_mk);

    else if(order_sm.isValid())
        fill_from(this, *order_sm);
    else if(order_sl.isValid())
        fill_from(this, *order_sl);

}

void whistoric_order::on_radioButton_toggled(bool checked)
{
    if(checked)
        ui->stackedWidget->setCurrentIndex(0);
    else
        ui->stackedWidget->setCurrentIndex(1);
}

void whistoric_order::showEvent ( QShowEvent * event )
{
    QDialog::showEvent(event);
    ui->show_execs->setChecked(true);
}
