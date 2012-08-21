#include "ui_switch_money.h"
#include "ui_ui_switch_money.h"

#include "ecimd_styles.h"
#include "qmtk_misc.h"

#include <QApplication>


ui_switch_money::ui_switch_money(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ui_switch_money)
{
    ui->setupUi(this);

    this->setAcceptDrops(true);

    //connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(applicationFocusChanged(QWidget*,QWidget*)));

    MTK_CONNECT_THIS(ui->orig_prod->signal_best_prices_update, on_ORIGIN_message_best_prices);
    MTK_CONNECT_THIS(ui->dest_prod->signal_best_prices_update, on_DESTIN_message_best_prices);

    MTK_CONNECT_THIS(ui->orig_prod->signal_product_configured, on_ORIGIN_product_configured);
    MTK_CONNECT_THIS(ui->dest_prod->signal_product_configured, on_DESTIN_product_configured);


    // config changed
    connect(ui->input_orig_prc_bid, SIGNAL(editingFinished()), this, SLOT(config_changed()));
    connect(ui->input_orig_prc_ask, SIGNAL(editingFinished()), this, SLOT(config_changed()));
    connect(ui->input_orig_qty_bid, SIGNAL(editingFinished()), this, SLOT(config_changed()));
    connect(ui->input_orig_qty_ask, SIGNAL(editingFinished()), this, SLOT(config_changed()));

    connect(ui->input_dest_prc_bid, SIGNAL(editingFinished()), this, SLOT(config_changed()));
    connect(ui->input_dest_prc_ask, SIGNAL(editingFinished()), this, SLOT(config_changed()));
    connect(ui->input_dest_qty_bid, SIGNAL(editingFinished()), this, SLOT(config_changed()));
    connect(ui->input_dest_qty_ask, SIGNAL(editingFinished()), this, SLOT(config_changed()));

    connect(ui->input_total_qty, SIGNAL(editingFinished()), this, SLOT(config_changed()));
    connect(ui->input_min_ord_qty, SIGNAL(editingFinished()), this, SLOT(config_changed()));
    connect(ui->input_max_ord_qty, SIGNAL(editingFinished()), this, SLOT(config_changed()));

    connect(ui->bs_button, SIGNAL(toggled(bool)), this, SLOT(config_changed()));
    connect(ui->sb_button, SIGNAL(toggled(bool)), this, SLOT(config_changed()));

    end_config();

    initialize_origin();
    initialize_destiny();

    config_changed();
}

ui_switch_money::~ui_switch_money()
{
    delete ui;
}

void ui_switch_money::initialize_origin(void)
{
    ui->input_orig_prc_bid->invalidate();
    ui->input_orig_prc_ask->invalidate();
    ui->input_orig_qty_bid->invalidate();
    ui->input_orig_qty_ask->invalidate();
    ui->input_orig_prc_bid->setEnabled(false);
    ui->input_orig_prc_ask->setEnabled(false);
    ui->input_orig_qty_bid->setEnabled(false);
    ui->input_orig_qty_ask->setEnabled(false);

    if(ui->orig_prod->price_manager.isValid())
        ui->l_prod_orig->setText(QLatin1String(ui->orig_prod->price_manager->get_product_code().product.c_str()));
    else
        ui->l_prod_orig->setText(QLatin1String(""));
}

void ui_switch_money::initialize_destiny(void)
{
    ui->input_dest_qty_bid->setEnabled(false);
    ui->input_dest_qty_ask->setEnabled(false);
    ui->input_dest_prc_bid->setEnabled(false);
    ui->input_dest_prc_ask->setEnabled(false);
    ui->input_dest_qty_bid->invalidate();
    ui->input_dest_qty_ask->invalidate();
    ui->input_dest_prc_bid->invalidate();
    ui->input_dest_prc_ask->invalidate();

    if(ui->dest_prod->price_manager.isValid())
        ui->l_prod_dest->setText(QLatin1String(ui->dest_prod->price_manager->get_product_code().product.c_str()));
    else
        ui->l_prod_dest->setText(QLatin1String(""));
}





namespace {

void fill_market_prices(QLabel* label_price, QLabel* label_quantity, const mtk::prices::msg::sub_price_level& level)
{
    if(level.quantity.GetIntCode() != 0)
    {
        label_price->setText(qtmisc::fn_as_QString(level.price));
        label_quantity->setText(qtmisc::fn_as_QString(level.quantity));
    }
    else
    {
        label_price->setText(QLatin1String(""));
        label_quantity->setText(QLatin1String(""));
    }
    if(level.quantity.GetIntCode() != 0)
    {
        label_price->setText(qtmisc::fn_as_QString(level.price));
        label_quantity->setText(qtmisc::fn_as_QString(level.quantity));
    }
    else
    {
        label_price->setText(QLatin1String(""));
        label_quantity->setText(QLatin1String(""));
    }
}


void check_initialization_price_qty_config(QFixedNumberEdit* sb_price,   QFixedNumberEdit* sb_qty, const mtk::prices::msg::sub_price_level& level)
{
    if(sb_price->isEnabled() == false)
    {
        sb_price->prepareExt(level.price.GetExt());
        sb_price->setEnabled(true);

        sb_qty->prepareExt(level.quantity.GetExt());
        sb_qty->setEnabled(true);
        if(level.quantity.GetIntCode() != 0)
            sb_price->setValue(level.price);
    }
}

};//  namespace {




void ui_switch_money::on_ORIGIN_message_best_prices  (const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_best_prices& msg)
{
    fill_market_prices(ui->orig_price_bid, ui->orig_qty_bid, msg.bids.level0);
    fill_market_prices(ui->orig_price_ask, ui->orig_qty_ask, msg.asks.level0);


    check_initialization_price_qty_config(ui->input_orig_prc_bid, ui->input_orig_qty_bid, msg.bids.level0);
    check_initialization_price_qty_config(ui->input_orig_prc_ask, ui->input_orig_qty_ask, msg.asks.level0);
}

void ui_switch_money::on_DESTIN_message_best_prices  (const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_best_prices& msg)
{
    fill_market_prices(ui->dest_price_bid, ui->dest_qty_bid, msg.bids.level0);
    fill_market_prices(ui->dest_price_ask, ui->dest_qty_ask, msg.asks.level0);

    check_initialization_price_qty_config(ui->input_dest_prc_bid, ui->input_dest_qty_bid, msg.bids.level0);
    check_initialization_price_qty_config(ui->input_dest_prc_ask, ui->input_dest_qty_ask, msg.asks.level0);
}


void ui_switch_money::start_config(void)
{
    ui->orig_qty_bid->setVisible(false);
    ui->orig_qty_ask->setVisible(false);
    ui->dest_qty_bid->setVisible(false);
    ui->dest_qty_ask->setVisible(false);

    //    3,2,2,0,2,0,2
    ui->grid_products->setColumnStretch(0, 3);
    ui->grid_products->setColumnStretch(1, 0);
    ui->grid_products->setColumnStretch(2, 2);
    ui->grid_products->setColumnStretch(3, 4);  //  edit config
    ui->grid_products->setColumnStretch(4, 2);
    ui->grid_products->setColumnStretch(5, 3);  //  edit config
    ui->grid_products->setColumnStretch(6, 0);

    ui->bs_button->setVisible(true);
    ui->sb_button->setVisible(true);
    if(ui->sb_button->isChecked())
    {
        ui->input_orig_prc_bid->setVisible(true);
        ui->input_orig_prc_ask->setVisible(false);
        ui->input_dest_prc_bid->setVisible(true);
        ui->input_dest_prc_ask->setVisible(false);

        ui->input_orig_qty_bid->setVisible(true);
        ui->input_orig_qty_ask->setVisible(false);
        ui->input_dest_qty_bid->setVisible(true);
        ui->input_dest_qty_ask->setVisible(false);

        ui->input_orig_prc_bid->setFocus(Qt::TabFocusReason);
    }
    else
    {
        ui->bs_button->setChecked(true);

        ui->input_orig_prc_bid->setVisible(false);
        ui->input_orig_prc_ask->setVisible(true);
        ui->input_dest_prc_bid->setVisible(false);
        ui->input_dest_prc_ask->setVisible(true);

        ui->input_orig_qty_bid->setVisible(false);
        ui->input_orig_qty_ask->setVisible(true);
        ui->input_dest_qty_bid->setVisible(false);
        ui->input_dest_qty_ask->setVisible(true);

        ui->input_orig_prc_bid->setFocus(Qt::TabFocusReason);
    }
    ui->stacked_widget->setCurrentIndex(1);
    config_changed();
}

void ui_switch_money::end_config(void)
{
    ui->input_orig_prc_bid->setVisible(false);
    ui->input_orig_prc_ask->setVisible(false);

    ui->input_dest_prc_bid->setVisible(false);
    ui->input_dest_prc_ask->setVisible(false);

    ui->input_orig_qty_bid->setVisible(false);
    ui->input_orig_qty_ask->setVisible(false);

    ui->input_dest_qty_bid->setVisible(false);
    ui->input_dest_qty_ask->setVisible(false);

    ui->sb_button->setVisible(false);
    ui->bs_button->setVisible(false);


    //    3,2,2,0,2,0,2
    ui->grid_products->setColumnStretch(0, 3);
    ui->grid_products->setColumnStretch(1, 2);
    ui->grid_products->setColumnStretch(2, 2);
    ui->grid_products->setColumnStretch(3, 0);
    ui->grid_products->setColumnStretch(4, 2);
    ui->grid_products->setColumnStretch(5, 0);
    ui->grid_products->setColumnStretch(6, 2);

    ui->orig_qty_bid->setVisible(true);
    ui->orig_qty_ask->setVisible(true);
    ui->dest_qty_bid->setVisible(true);
    ui->dest_qty_ask->setVisible(true);
    ui->calc_bid->setVisible(true);
    ui->calc_ask->setVisible(true);

    ui->l_effective_dif->setText(QLatin1String(""));
    ui->l_prc_dest_avg->setText(QLatin1String(""));
    ui->l_prc_orig_avg->setText(QLatin1String(""));
    ui->l_qty_dest_avg->setText(QLatin1String(""));
    ui->l_qty_dif->setText(QLatin1String(""));
    ui->l_qty_orig_avg->setText(QLatin1String(""));

    ui->stacked_widget->setCurrentIndex(0);
    config_changed();
}


void ui_switch_money::on_config_button_toggled(bool checked)
{
    if(checked)
        start_config();
    else
        end_config();
}


void ui_switch_money::on_config_button_clicked()
{

}

/*
void ui_switch_money::applicationFocusChanged ( QWidget * / *old* /, QWidget * / *now* / )
{
    if(ui->config_button->now)
    {
        if((now == this  ||  now==this->parent())  ||  (now->parent()  &&  now->parent() == this)  ||   (now->parent()  &&  now->parent() == this->parent()))
            update_status(normal);
        else
            update_status(normal);
    }
    else
        update_status(normal);
}*/

void ui_switch_money::on_ORIGIN_product_configured   (const mtk::msg::sub_product_code&)
{
    initialize_origin();
    config_changed ();
}

void ui_switch_money::on_DESTIN_product_configured   (const mtk::msg::sub_product_code&)
{
    initialize_destiny();
    config_changed ();
}


void  ui_switch_money::config_changed(void)
{
    swm_config::en_side   side =  ui->sb_button->isChecked() ?  swm_config::sell_buy : swm_config::buy_sell;
    mtk::nullable<mtk::FixedNumber>               origin_price =  ui->sb_button->isChecked() ?  ui->input_orig_prc_bid->value()    :  ui->input_orig_prc_ask->value();
    mtk::nullable<mtk::FixedNumber>               origin_qty   =  ui->sb_button->isChecked() ?  ui->input_orig_qty_bid->value()    :  ui->input_orig_qty_ask->value();
    mtk::nullable<mtk::FixedNumber>               dest_price   =  ui->sb_button->isChecked() ?  ui->input_dest_prc_bid->value()    :  ui->input_dest_prc_ask->value();
    mtk::nullable<mtk::FixedNumber>               dest_qty     =  ui->sb_button->isChecked() ?  ui->input_dest_qty_bid->value()    :  ui->input_dest_qty_ask->value();

    /*
    if(side == swm_config::sell_buy)
    {
        ui->calc_bid->setStyleSheet(QLatin1String("color: green;"));
        ui->calc_ask->setStyleSheet(QLatin1String("color: green;"));
    }
    else
    {
        ui->calc_bid->setStyleSheet(QLatin1String("color: red;"));
        ui->calc_ask->setStyleSheet(QLatin1String("color: red;"));
    }*/



    swm_config  config {
        side,

        {
            ui->orig_prod->price_manager,
            origin_price,
            origin_qty
        },

        {
            ui->dest_prod->price_manager,
            dest_price,
            dest_qty
        },

        ui->input_total_qty->value(),
        ui->input_min_ord_qty->value(),
        ui->input_max_ord_qty->value()
    };


    signal_config_changed.emit(config);
}


void    ui_switch_money::set_status(const QString&  status)
{
    ui->status->setText(status);
}


void   ui_switch_money::on_price_update(const swm_calculator::s_price_update&  price_update)
{
    set_status(price_update.message);
    if(price_update.price.HasValue())
    {
        QLabel*  label_calculated=0;
        QLabel*  label_NOT_calculated=0;

        if(price_update.side == mtk::trd::msg::buy)
        {
            label_calculated      = ui->calc_bid;
            label_NOT_calculated  = ui->calc_ask;
        }
        else
        {
            label_calculated      = ui->calc_ask;
            label_NOT_calculated  = ui->calc_bid;
        }

        label_calculated->setText(qtmisc::fn_as_QString(price_update.price.Get()));
        label_NOT_calculated->setText(QLatin1String(""));;
    }
    else
    {
        ui->calc_ask->setText(QLatin1String(""));
        ui->calc_bid->setText(QLatin1String(""));
    }
}


void  ui_switch_money::on_error(const mtk::Alarm&  alarm)
{
    set_status(tr("ERROR "));
    add_log(QLatin1String(alarm.message.c_str()));
}


void ui_switch_money::add_log(const QString&  text)
{
    std::string  now = MTK_SS(MTK_SS(mtk::dtNowLocal()).substr(11,8));
    ui->log->appendPlainText(QLatin1String(MTK_SS(now << " " << text.toStdString()).c_str()));
}
