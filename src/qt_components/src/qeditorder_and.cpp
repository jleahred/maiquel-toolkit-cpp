#include "qeditorder_and.h"
#include "ui_qeditorder_and.h"


#include "qt_components/src/qmtk_misc.h"
#include "components/admin/admin.h"
#include "components/trading/accounts/account_manager_cli.h"
#include "components/trading/trd_cli_ord_book.h"


#include <QPushButton>




namespace
{
    static QPoint  last_pos;
    QPoint   normalize_pos(void)
    {
        static int counter=0;
        static int increment=20;
        ++counter;
        if(counter%5 == 0)
        {
            last_pos.setX(last_pos.x() - 100);
            last_pos.setY(last_pos.y() - 100);
        }

        QPoint  result = QPoint(QApplication::activeWindow()->childrenRect().x() + last_pos.x(), QApplication::activeWindow()->childrenRect().y() + last_pos.y());
        result.setX(result.x() + increment);
        result.setY(result.y() + increment);
        if(result.x() <= 0)
            result.setX(20);
        if(result.y() <= 0)
            result.setY(20);

        if(result.x() < QApplication::activeWindow()->x())
            result.setX(QApplication::activeWindow()->x() + 10);
        if(result.y() < QApplication::activeWindow()->y())
            result.setY(QApplication::activeWindow()->y() + 10);
        if(result.x() > QApplication::activeWindow()->x() + QApplication::activeWindow()->width())
            result.setX(QApplication::activeWindow()->x() + QApplication::activeWindow()->width()/2);
        if(result.y() > QApplication::activeWindow()->y() + QApplication::activeWindow()->height())
            result.setY(QApplication::activeWindow()->y() + QApplication::activeWindow()->height()/2);
        last_pos = result;
        return result;
    }
};



QEditOrder_and::~QEditOrder_and()
{
    delete ui;
}




void QEditOrder_and::common_init(void)
{
    if(last_pos.x() != 0    ||    last_pos.y()!=0)
        this->move(normalize_pos());


    QFont font(this->font());
    font.setPixelSize(qtmisc::get_base_font_size()+2);
    this->setFont(font);

    ui->market->setText(QLatin1String(pc.market.c_str()));
    ui->product->setText(QLatin1String(pc.product.c_str()));

    ui->quantity->setDecimals(rq_pos.quantity.GetExt().GetDec());

    ui->cliref->setText(QLatin1String(rq_pos.cli_ref.c_str()));


    QString  configure_default_field;

    mtk::Nullable<std::string>  s_default_cli_ref =  mtk::admin::get_config_property("MISC.default_cli_ref");
    if(s_default_cli_ref.HasValue()==false)
    {
        configure_default_field = tr("you can configure default client reference with dblclick on cli_ref label");
    }
    else
    {
        if(s_default_cli_ref.Get() == ""   &&   mtk::rand()%100 <= 7)
            configure_default_field = tr("you can configure default client reference with dblclick on cli_ref label");
        if(ui->cliref->text() == QLatin1String(""))
            ui->cliref->setText(QLatin1String(s_default_cli_ref.Get().c_str()));
    }

    mtk::Nullable<std::string>  n_default_account =  mtk::admin::get_config_property("MISC.default_account");
    if(n_default_account.HasValue() == false)
        configure_default_field =  tr("you can configure default account with dblclick on account label");
    this->fill_accounts();

    mtk::Nullable<std::string>  s_default_qty =  mtk::admin::get_config_property("MISC.default_qty");


    ui->quantity->setDecimals(rq_pos.quantity.GetExt().GetDec());
    ui->quantity->setSingleStep(1./pow(10., rq_pos.quantity.GetExt().GetDec())*rq_pos.quantity.GetExt().GetInc());
    if(rq_pos.quantity.GetIntCode()==0)
        ui->quantity->set_empty();
    if(s_default_qty.HasValue()==false)
        configure_default_field =  tr("you can configure default qty with dblclick on qty label");
    if(rq_pos.quantity.GetIntCode() <= 0)
    {
        QString default_q;
        if(s_default_qty.HasValue())
            default_q = QLatin1String(s_default_qty.Get().c_str());

        if(default_q == QLatin1String("")  ||  default_q == QLatin1String("~"))
            ui->quantity->set_empty();
        else
            ui->quantity->setValue(QString(default_q).toDouble());
    }
    else
        ui->quantity->setValue(rq_pos.quantity.GetDouble().get()._0);


    this->check_if_order_can_be_sent();
    if(configure_default_field!=QLatin1String(""))
        ui->message->setText(configure_default_field);

    register_event_filters();
}




/**
  If quantity is empty, it will get the default quantity
  */
QEditOrder_and::QEditOrder_and( const mtk::msg::sub_product_code&       _pc,
                                mtk::trd::msg::enBuySell                _buy_sell,
                                const mtk::trd::msg::sub_position_ls&   _rq_pos,
                                bool                                    /*agression*/,
                                QWidget *parent) :
        QDialog(parent),
        ui(new Ui::QEditOrder_and),
        pc(_pc),
        buy_sell(_buy_sell),
        rq_pos(_rq_pos),
        price_manager (mtk::make_cptr(new mtk::prices::price_manager(_pc)))
{
    setAttribute(Qt::WA_DeleteOnClose);

    ui->setupUi(this);

    ui->price->setDecimals(rq_pos.price.GetExt().GetDec());
    ui->price->setSingleStep(1./pow(10.,rq_pos.price.GetExt().GetDec())*rq_pos.price.GetExt().GetInc());
    if(rq_pos.price.GetIntCode()==0  &&  (rq_pos.quantity.GetIntCode()==0  || rq_pos.quantity.GetIntCode()==-2))
        ui->price->set_empty();
    else
        ui->price->setValue(rq_pos.price.GetDouble().get()._0);

    ui->lb_oposite_prices->setVisible(false);

    common_init();

    this->setWindowTitle(tr("Edit Limit Order"));
    if (buy_sell == mtk::trd::msg::buy)
    {
        ui->pb_main->setText(tr("buy"));
        ui->pb_secondary->setText(tr("sell"));
    }
    else
    {
        ui->pb_main->setText(tr("sell"));
        ui->pb_secondary->setText(tr("buy"));
    }

    if(ui->price->is_empty() == false)
    {
        ui->quantity->setFocus();
        ui->quantity->selectAll();
    }
    else
    {
        ui->price->setFocus();
    }

    this->adjustSize();

    MTK_CONNECT_THIS(price_manager->signal_best_prices_update, on_best_price_update);

    if(price_manager->get_best_prices().HasValue())
        on_best_price_update(pc, price_manager->get_best_prices().Get());


    const static  QString buy_style = QLatin1String(
            "QPushButton:enabled"
            "{"
            "    background-color: qlineargradient(spread:pad, x1:0, y1:0.0340909, x2:0, y2:1, stop:0 rgb(255, 255, 255), stop:0.41989 rgb(191, 255, 219), stop:0.911602 rgb(191, 255, 191), stop:1 rgb(100, 185, 184));"
            "}"
            "QPushButton:enabled:pressed"
            "{"
            "    background-color: rgb(191, 255, 191);"
            "}"
           );
    const static  QString sell_style = QLatin1String(
            "QPushButton:enabled"
            "{"
            "    background-color: qlineargradient(spread:pad, x1:0, y1:0.0340909, x2:0, y2:1, stop:0 rgb(255, 255, 255), stop:0.41989 rgb(255, 191, 191), stop:0.911602 rgb(255, 191, 191), stop:1 rgb(185, 100, 184));"
            "}"
            "QPushButton:enabled:pressed"
            "{"
            "      background-color: rgb(255, 191, 191);"
            "}"
           );
    if(buy_sell == mtk::trd::msg::buy)
    {
        if(ui->pb_main->styleSheet() !=  buy_style)
            ui->pb_main->setStyleSheet(buy_style);
        if(ui->pb_secondary->styleSheet() !=  sell_style)
            ui->pb_secondary->setStyleSheet(sell_style);
    }
    else
    {
        if(ui->pb_main->styleSheet() !=  sell_style)
            ui->pb_main->setStyleSheet(sell_style);
        if(ui->pb_secondary->styleSheet() !=  buy_style)
            ui->pb_secondary->setStyleSheet(buy_style);
    }

    //if(agression)
    //    ui->best_oposite->setChecked(true);
    ui->best_oposite->setChecked(true);
}


void  QEditOrder_and::on_best_price_update(const mtk::msg::sub_product_code& /*pc*/, const mtk::prices::msg::sub_best_prices& bp)
{
    QString result;

    if(bp.bids.level0.quantity.GetIntCode() > 0)
    {
        result += qtmisc::fn_as_QString(bp.bids.level0.price);
        best_bid = bp.bids.level0.price;
    }
    else
        best_bid = mtk::nullable<mtk::FixedNumber>();
    result += QLatin1String(" / ");
    if(bp.asks.level0.quantity.GetIntCode() > 0)
    {
        result += qtmisc::fn_as_QString(bp.asks.level0.price);
        best_ask = bp.asks.level0.price;
    }
    else
        best_ask = mtk::nullable<mtk::FixedNumber>();


    ui->lb_oposite_prices->setText(result);
    check_if_order_can_be_sent();
}


bool QEditOrder_and::check_if_order_can_be_sent(void)
{
    bool result = true;

    ui->pb_main->setEnabled(true);
    if(ui->best_oposite->isChecked())
        ui->pb_secondary->setEnabled(true);
    else
        ui->pb_secondary->setEnabled(false);
    ui->message->setText(QLatin1String(""));

    int pos = 0;
    QString text;

    text = ui->quantity->text();
    if(ui->quantity->validate(text, pos) != QValidator::Acceptable)
    {
        ui->pb_main->setEnabled(false);
        ui->pb_secondary->setEnabled(false);
        ui->message->setText(tr("invalid quantity"));
        result = false;
    }

    if(int(ui->quantity->value()*100000) == 0)
    {
        ui->pb_main->setEnabled(false);
        ui->pb_secondary->setEnabled(false);
        ui->message->setText(tr("zero quantity"));
        result = false;
    }

    if(ui->best_oposite->isChecked() == false)
    {
        if(buy_sell == mtk::trd::msg::buy)
        {
            if(ui->pb_main->text() != tr("buy"))
                ui->pb_main->setText(tr("buy"));
            if(ui->pb_secondary->text() != tr("sell"))
                ui->pb_secondary->setText(tr("sell"));
        }
        if(buy_sell == mtk::trd::msg::sell)
        {
            if(ui->pb_main->text() != tr("sell"))
                ui->pb_main->setText(tr("sell"));
            if(ui->pb_secondary->text() != tr("buy"))
                ui->pb_secondary->setText(tr("buy"));
        }



        text = ui->price->text();
        if(ui->price->validate(text, pos) != QValidator::Acceptable)
        {
            ui->pb_main->setEnabled(false);
            ui->pb_secondary->setEnabled(false);
            ui->message->setText(tr("invalid price"));
            result = false;
        }
        else
        {
            //  check there are no rounds
            mtk::FixedNumber  price = rq_pos.price;
            price.SetDouble(ui->price->value());
            if(price.GetDouble() !=  mtk::Double(ui->price->value()))
            {
                ui->pb_main->setEnabled(false);
                ui->pb_secondary->setEnabled(false);
                ui->message->setText(tr("invalid price"));
                result = false;
            }
        }
    }
    else
    {
        if(buy_sell == mtk::trd::msg::buy)
        {
            if(best_ask.HasValue() == false)
            {
                ui->pb_main->setEnabled(false);
                ui->pb_main->setText(tr("buy"));
            }
            else
            {
                ui->pb_main->setEnabled(true);
                ui->pb_main->setText(qtmisc::fn_as_QString(best_ask.Get()));
            }

            if(best_bid.HasValue() == false)
            {
                ui->pb_secondary->setEnabled(false);
                ui->pb_secondary->setText(tr("sell"));
            }
            else
            {
                ui->pb_secondary->setEnabled(true);
                ui->pb_secondary->setText(qtmisc::fn_as_QString(best_bid.Get()));
            }
        }

        if(buy_sell == mtk::trd::msg::sell)
        {
            if(best_bid.HasValue() == false)
            {
                ui->pb_main->setEnabled(false);
                ui->pb_main->setText(tr("sell"));
            }
            else
            {
                ui->pb_main->setEnabled(true);
                ui->pb_main->setText(qtmisc::fn_as_QString(best_bid.Get()));
            }

            if(best_ask.HasValue() == false)
            {
                ui->pb_secondary->setEnabled(false);
                ui->pb_secondary->setText(tr("buy"));
            }
            else
            {
                ui->pb_secondary->setEnabled(true);
                ui->pb_secondary->setText(qtmisc::fn_as_QString(best_ask.Get()));
            }
        }


    }

    if(ui->account->currentIndex() == -1)
    {
        ui->pb_main->setEnabled(false);
        ui->pb_secondary->setEnabled(false);
        ui->message->setText(tr("empty account"));
        result = false;
    }

    if(ui->product->text().isEmpty())
    {
        ui->pb_main->setEnabled(false);
        ui->pb_secondary->setEnabled(false);
        ui->message->setText(tr("empty product"));
        result = false;
    }

    if(ui->market->text().isEmpty())
    {
        ui->pb_main->setEnabled(false);
        ui->pb_secondary->setEnabled(false);
        ui->message->setText(tr("empty market"));
        result = false;
    }

    return result;
}






void QEditOrder_and::on_account_currentIndexChanged(QString )
{
    check_if_order_can_be_sent();
    ui->quantity->setFocus();
    ui->quantity->selectAll();
}

void QEditOrder_and::on_price_valueChanged(QString )
{
    check_if_order_can_be_sent();
}

void QEditOrder_and::on_quantity_valueChanged(QString )
{
    check_if_order_can_be_sent();
}

void QEditOrder_and::done(int d)
{
    if(d==0)
        QDialog::done(d);
    else if(check_if_order_can_be_sent())
        QDialog::done(d);
}

void QEditOrder_and::mouseDoubleClickEvent(QMouseEvent *e)
{
    QLabel* lb = dynamic_cast<QLabel*>(this->childAt(e->pos()));
    if(lb == ui->label_quantity  &&  ui->quantity->text().isEmpty()==false)
    {
        std::string default_qty = MTK_SS(ui->quantity->value());
        mtk::admin::set_config_property("MISC.default_qty",default_qty);
        ui->message->setText(tr("configured new default qty with %1").arg(QLatin1String(default_qty.c_str())));
    }
    else if(lb == ui->label_account  &&  ui->account->currentIndex()!=-1)
    {
        QString default_account = ui->account->currentText();
        mtk::admin::set_config_property("MISC.default_account",default_account.toStdString());
        ui->message->setText(tr("configured new default account with %1").arg(default_account));
    }
    else if(lb == ui->label_cli_ref)
    {
        QString default_cli_ref = ui->cliref->text();
        mtk::admin::set_config_property("MISC.default_cli_ref", default_cli_ref.toStdString());
        ui->message->setText(tr("configured new default client reference with %1").arg(default_cli_ref));
    }
}


void QEditOrder_and::fill_accounts(void)
{
    account_list.clear();

    //account_list = mtk::trd::account_manager::get_accounts();
    mtk::list<mtk::trd::account::msg::sub_grant>  grant_list = mtk::accmgrcli::get_grant_list(pc.market);
    for(mtk::list<mtk::trd::account::msg::sub_grant>::iterator  it = grant_list.begin(); it!=grant_list.end(); ++it)
    {
        if(it->type == "F")
            account_list.push_back(it->key.account);
    }

    int default_account_located=0;
    mtk::Nullable<std::string>  n_default_account =  mtk::admin::get_config_property("MISC.default_account");
    std::string default_account;
    if(n_default_account.HasValue())
        default_account = n_default_account.Get();

    int counter=0;
    for(mtk::list<mtk::trd::msg::sub_account_info>::iterator it = account_list.begin(); it!= account_list.end(); ++it)
    {
        ui->account->addItem(QLatin1String(it->name.c_str()));
        if(it->name == default_account)
            default_account_located = counter;
        ++counter;
    }
    ui->account->setCurrentIndex(default_account_located);
}

bool QEditOrder_and::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* key_event = static_cast<QKeyEvent*>(event);

        if(key_event->key() == Qt::Key_Up)
        {
            ui->price->stepUp();
            return true;
        }
        else if(key_event->key() == Qt::Key_Down)
        {
            ui->price->stepDown();
            return true;
        }
        else if((key_event->key() == Qt::Key_Enter ||  key_event->key() == Qt::Key_Return)  /*&&  ui->best_oposite->isChecked() == false*/)
        {
            on_pb_main_clicked();
        }
    }
    return QDialog::eventFilter(object, event);
}

void QEditOrder_and::register_event_filters(void)
{
    ui->price->installEventFilter(this);
    ui->quantity->installEventFilter(this);
    ui->cliref->installEventFilter(this);
    ui->pb_main->installEventFilter(this);
    ui->pb_secondary->installEventFilter(this);
}


void QEditOrder_and::on_pb_main_clicked()
{
    if(ui->best_oposite->isChecked() == false)
    {
        mtk::FixedNumber  price(rq_pos.price);
        price.SetDouble(ui->price->value());
        mtk::FixedNumber  quantity(rq_pos.quantity);
        quantity.SetDouble(ui->quantity->value());
        mtk::trd::msg::sub_position_ls  pos_ls(price, quantity, ui->cliref->text().toStdString());

        mtk::list<mtk::trd::msg::sub_account_info>::iterator it_account=account_list.begin();
        for(int i=0; i<ui->account->currentIndex(); ++i)
            ++it_account;

        mtk::trd::trd_cli_ord_book::rq_nw_ls(pc, buy_sell, pos_ls, mtk::trd::msg::sub_account_info(*it_account));
    }
    else
    {
        mtk::FixedNumber  price(rq_pos.price);      //  temporary

        if(buy_sell == mtk::trd::msg::buy)
        {
            if(best_ask.HasValue() == false)
                throw  mtk::Alarm(MTK_HERE, "user_send_new_order_and", "main button enabled with no valid best_ask", mtk::alPriorError);

            price = best_ask.Get();
        }
        else
        {
            if(best_bid.HasValue() == false)
                throw  mtk::Alarm(MTK_HERE, "user_send_new_order_and", "main button enabled with no valid best_bid", mtk::alPriorError);

            price = best_bid.Get();
        }

        mtk::FixedNumber  quantity(rq_pos.quantity);
        quantity.SetDouble(ui->quantity->value());
        mtk::trd::msg::sub_position_ls  pos_ls(price, quantity, ui->cliref->text().toStdString());

        mtk::list<mtk::trd::msg::sub_account_info>::iterator it_account=account_list.begin();
        for(int i=0; i<ui->account->currentIndex(); ++i)
            ++it_account;

        mtk::trd::trd_cli_ord_book::rq_nw_ls(pc, buy_sell, pos_ls, mtk::trd::msg::sub_account_info(*it_account));
    }

    this->close();
}

void QEditOrder_and::on_best_oposite_toggled(bool checked)
{
    this->setUpdatesEnabled(false);
    try
    {
        ui->lb_oposite_prices->setVisible(checked);
        ui->price->setHidden(checked);
        check_if_order_can_be_sent();
        ui->quantity->setFocus();
        ui->quantity->selectAll();
    }
    catch(...)
    {
        this->setUpdatesEnabled(true);
        throw;
    }
    this->setUpdatesEnabled(true);
}

void QEditOrder_and::on_pb_secondary_clicked()
{
    if(ui->best_oposite->isChecked() == false)
        throw  mtk::Alarm(MTK_HERE, "user_send_new_order_and", "on_pb_secondary_clicked  with no best_oposite", mtk::alPriorError);

    {
        mtk::FixedNumber            price(rq_pos.price);      //  temporary
        mtk::trd::msg::enBuySell    side = buy_sell;          //  temporary

        if(buy_sell == mtk::trd::msg::sell)
        {
            side = mtk::trd::msg::buy;
            if(best_ask.HasValue() == false)
                throw  mtk::Alarm(MTK_HERE, "user_send_new_order_and", "main button enabled with no valid best_ask", mtk::alPriorError);

            price = best_ask.Get();
        }
        else
        {
            side = mtk::trd::msg::sell;
            if(best_bid.HasValue() == false)
                throw  mtk::Alarm(MTK_HERE, "user_send_new_order_and", "main button enabled with no valid best_bid", mtk::alPriorError);

            price = best_bid.Get();
        }

        mtk::FixedNumber  quantity(rq_pos.quantity);
        quantity.SetDouble(ui->quantity->value());
        mtk::trd::msg::sub_position_ls  pos_ls(price, quantity, ui->cliref->text().toStdString());

        mtk::list<mtk::trd::msg::sub_account_info>::iterator it_account=account_list.begin();
        for(int i=0; i<ui->account->currentIndex(); ++i)
            ++it_account;

        mtk::trd::trd_cli_ord_book::rq_nw_ls(pc, side, pos_ls, mtk::trd::msg::sub_account_info(*it_account));
    }

    this->close();
}


void QEditOrder_and::moveEvent ( QMoveEvent * event )
{
    QDialog::moveEvent(event);
    last_pos = event->pos();
}



void  QEditOrder_and::new_order(const mtk::msg::sub_product_code&   pc, mtk::trd::msg::enBuySell  buy_sell, const mtk::trd::msg::sub_position_ls& rq_pos, bool agression, QWidget *parent)
{
    QEditOrder_and*  new_order =   new QEditOrder_and(pc, buy_sell, rq_pos, agression, parent);
    new_order->show();
}
