#include "qeditorder.h"
#include "ui_qeditorder.h"


#include "qt_components/src/qmtk_misc.h"
#include "components/admin/admin.h"
#include "components/trading/accounts/account_manager_cli.h"


#include <QPushButton>




/*
QEditOrder::QEditOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QEditOrder)
{
    ui->setupUi(this);
}
*/

QEditOrder::~QEditOrder()
{
    delete ui;
}


/**
  If quantity is empty, it will get the default quantity
  */
QEditOrder::QEditOrder(const mtk::trd::msg::RQ_XX_LS& rq, bool agressive, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::QEditOrder),
        rq_ls(rq)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Edit Limit Order"));

    QFont font(this->font());
    font.setPixelSize(qtmisc::get_base_font_size()+2);
    this->setFont(font);

    if (rq.invariant.side == mtk::trd::msg::buy)
        ui->side->setText(tr("buy"));
    else
        ui->side->setText(tr("sell"));

    ui->market->setText(QLatin1String(rq.invariant.product_code.market.c_str()));
    ui->product->setText(QLatin1String(rq.invariant.product_code.product.c_str()));
    ui->price->setDecimals(rq.request_pos.price.GetExt().GetDec());
    ui->price->setSingleStep(1./pow(10.,rq.request_pos.price.GetExt().GetDec())*rq.request_pos.price.GetExt().GetInc());
    if(rq.request_pos.quantity.GetIntCode()==0  &&  rq.request_pos.price.GetIntCode()==0)
        ui->price->clear();
    else
        ui->price->setValue(rq.request_pos.price.GetDouble().get()._0);
    ui->quantity->setDecimals(rq.request_pos.quantity.GetExt().GetDec());
    ui->quantity->setSingleStep(1./pow(10.,rq.request_pos.quantity.GetExt().GetDec())*rq.request_pos.quantity.GetExt().GetInc());
    if(rq.request_pos.quantity.GetIntCode()!=0)
        ui->quantity->setValue(rq.request_pos.quantity.GetDouble().get()._0);
    else
        ui->quantity->setValue(1.);//ui->quantity->clear();
    ui->cliref->setText(QLatin1String(rq.cli_ref.c_str()));


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
    this->fill_accounts(rq);

    mtk::Nullable<std::string>  s_default_qty =  mtk::admin::get_config_property("MISC.default_qty");
    if(s_default_qty.HasValue()==false)
    {
        configure_default_field =  tr("you can configure default qty with dblclick on qty label");
    }
    else
    {
        if(rq.request_pos.quantity.GetIntCode() == 0)
        {
            QLatin1String default_q (s_default_qty.Get().c_str());
            if(default_q == ""  ||  default_q == "~")
                ui->quantity->setValue(1.);
            else
                ui->quantity->setValue(QString(default_q).toDouble());
        }
        else
            ui->quantity->setValue(rq.request_pos.quantity.GetDouble().get()._0);
    }

    if(agressive==false)
    {
        ui->price->setFocus();
        ui->price->selectAll();
    }
    else
    {
        ui->quantity->setFocus();
        ui->quantity->selectAll();
    }

    this->check_if_order_can_be_sent();
    if(configure_default_field!=QLatin1String(""))
        ui->message->setText(configure_default_field);

    this->adjustSize();
}

QEditOrder::QEditOrder(const mtk::trd::msg::RQ_XX_MK& rq, bool /*agressive*/, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::QEditOrder),
        rq_mk(rq)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Edit Limit Order"));

    QFont font(this->font());
    font.setPixelSize(qtmisc::get_base_font_size()+2);
    this->setFont(font);

    if (rq.invariant.side == mtk::trd::msg::buy)
    {
        ui->side->setText(tr("buy"));
    }
    else
    {
        ui->side->setText(tr("sell"));
    }
    ui->market->setText(QLatin1String(rq.invariant.product_code.market.c_str()));
    ui->product->setText(QLatin1String(rq.invariant.product_code.product.c_str()));
    ui->price->setVisible(false);
    ui->price->setEnabled(false);
    ui->quantity->setDecimals(rq.request_pos.quantity.GetExt().GetDec());
    ui->quantity->setSingleStep(1./pow(10.,rq.request_pos.quantity.GetExt().GetDec())*rq.request_pos.quantity.GetExt().GetInc());
    if(rq.request_pos.quantity.GetIntCode()!=0)
        ui->quantity->setValue(rq.request_pos.quantity.GetDouble().get()._0);
    else
        ui->quantity->setValue(1.);//ui->quantity->clear();
    ui->cliref->setText(QLatin1String(rq.cli_ref.c_str()));


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
    this->fill_accounts(rq);

    mtk::Nullable<std::string>  s_default_qty =  mtk::admin::get_config_property("MISC.default_qty");
    if(s_default_qty.HasValue()==false)
    {
        configure_default_field =  tr("you can configure default qty with dblclick on qty label");
    }
    else
    {
        if(rq.request_pos.quantity.GetIntCode() == 0)
        {
            QLatin1String default_q (s_default_qty.Get().c_str());
            if(default_q == ""  ||  default_q == "~")
                ui->quantity->setValue(1.);
            else
                ui->quantity->setValue(QString(default_q).toDouble());
        }
        else
            ui->quantity->setValue(rq.request_pos.quantity.GetDouble().get()._0);
    }

    this->check_if_order_can_be_sent();
    if(configure_default_field!=QLatin1String(""))
        ui->message->setText(configure_default_field);
}


bool QEditOrder::check_if_order_can_be_sent(void)
{
    bool result = true;

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    ui->message->setText(QLatin1String(""));

    int pos = 0;
    QString text;

    text = ui->quantity->text();
    if(ui->quantity->validate(text, pos) != QValidator::Acceptable)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->message->setText(tr("invalid quantity"));
        result = false;
    }

    if(int(ui->quantity->value()*100000) == 0)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->message->setText(tr("zero quantity"));
        result = false;
    }


    if(rq_ls.HasValue())
    {
        text = ui->price->text();
        if(ui->price->validate(text, pos) != QValidator::Acceptable)
        {
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
            ui->message->setText(tr("invalid price"));
            result = false;
        }
    }

    if(ui->account->currentIndex() == -1)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->message->setText(tr("empty account"));
        result = false;
    }

    if(ui->product->text().isEmpty())
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->message->setText(tr("empty product"));
        result = false;
    }

    if(ui->market->text().isEmpty())
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->message->setText(tr("empty market"));
        result = false;
    }

    return result;
}


mtk::trd::msg::RQ_XX_LS   QEditOrder::get_request_ls(void)
{
    mtk::trd::msg::RQ_XX_LS  result = rq_ls.Get();
    result.invariant.product_code.market = ui->market->text().toStdString();
    result.invariant.product_code.product = ui->product->text().toStdString();
    result.request_pos.price.SetDouble(ui->price->value());
    result.request_pos.quantity.SetDouble(ui->quantity->value());
    result.cli_ref = ui->cliref->text().toStdString();

    mtk::list<mtk::trd::msg::sub_account_info>::iterator it_account=account_list.begin();
    for(int i=0; i<ui->account->currentIndex(); ++i)
        ++it_account;
    result.invariant.account = mtk::trd::msg::sub_account_info(*it_account);

    return result;
}

mtk::trd::msg::RQ_XX_MK   QEditOrder::get_request_mk(void)
{
    mtk::trd::msg::RQ_XX_MK  result = rq_mk.Get();
    result.invariant.product_code.market = ui->market->text().toStdString();
    result.invariant.product_code.product = ui->product->text().toStdString();
    result.request_pos.quantity.SetDouble(ui->quantity->value());
    result.cli_ref = ui->cliref->text().toStdString();

    mtk::list<mtk::trd::msg::sub_account_info>::iterator it_account=account_list.begin();
    for(int i=0; i<ui->account->currentIndex(); ++i)
        ++it_account;
    result.invariant.account = mtk::trd::msg::sub_account_info(*it_account);

    return result;
}


void QEditOrder::on_account_currentIndexChanged(QString )
{
    check_if_order_can_be_sent();
}

void QEditOrder::on_price_valueChanged(QString )
{
    check_if_order_can_be_sent();
}

void QEditOrder::on_quantity_valueChanged(QString )
{
    check_if_order_can_be_sent();
}

void QEditOrder::done(int d)
{
    if(d==0)
        QDialog::done(d);
    else if(check_if_order_can_be_sent())
        QDialog::done(d);
}

void QEditOrder::mouseDoubleClickEvent(QMouseEvent *e)
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


void QEditOrder::fill_accounts(const mtk::trd::msg::RQ_XX& rq)
{
    account_list.clear();
    if(rq.invariant.account.client_code == "")      //  it's  a new order
    {

        //account_list = mtk::trd::account_manager::get_accounts();
        mtk::list<mtk::trd::account::msg::sub_grant>  grant_list = mtk::accmgrcli::get_grant_list();
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
    else
    {
        account_list.push_back(rq.invariant.account);
        ui->account->addItem(QLatin1String(rq.invariant.account.name.c_str()));
        ui->account->setCurrentIndex(0);
    }
}
