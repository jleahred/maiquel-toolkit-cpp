#include "qeditorder.h"
#include "ui_qeditorder.h"


#include "qt_components/src/qmtk_misc.h"
#include "components/admin/admin.h"



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
    font.setPixelSize(get_base_font_size()+2);
    this->setFont(font);

    if (rq.request_pos.side == mtk::trd::msg::buy)
    {
        ui->BuySell->setText(tr("BUY"));
        setPalette( mtk_color_buy );
    }
    else
    {
        ui->BuySell->setText(tr("SELL"));
        setPalette( QPalette(mtk_color_sell));
    }
    ui->market->setText(QLatin1String(rq.product_code.market.c_str()));
    ui->product->setText(QLatin1String(rq.product_code.product.c_str()));
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
        ui->quantity->clear();
    ui->cliref->setText(QLatin1String(rq.cli_ref.c_str()));

    this->check_if_order_can_be_sent();

    mtk::Nullable<std::string>  s_default_qty =  mtk::admin::get_config_property("MISC.default_qty");
    if(s_default_qty.HasValue()==false)
    {
        ui->message->setText(tr("you can configure default qty with dblclick on qty label"));
    }
    else
    {
        if(rq.request_pos.quantity.GetIntCode() == 0)
        {
            QLatin1String default_q (s_default_qty.Get().c_str());
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
}

QEditOrder::QEditOrder(const mtk::trd::msg::RQ_XX_MK& rq, bool /*agressive*/, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::QEditOrder),
        rq_mk(rq)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Edit Limit Order"));

    QFont font(this->font());
    font.setPixelSize(get_base_font_size()+2);
    this->setFont(font);

    if (rq.request_pos.side == mtk::trd::msg::buy)
    {
        ui->BuySell->setText(tr("BUY"));
        setPalette( mtk_color_buy );
    }
    else
    {
        ui->BuySell->setText(tr("SELL"));
        setPalette( QPalette(mtk_color_sell));
    }
    ui->market->setText(QLatin1String(rq.product_code.market.c_str()));
    ui->product->setText(QLatin1String(rq.product_code.product.c_str()));
    ui->price->setVisible(false);
    ui->price->setEnabled(false);
    ui->quantity->setDecimals(rq.request_pos.quantity.GetExt().GetDec());
    ui->quantity->setSingleStep(1./pow(10.,rq.request_pos.quantity.GetExt().GetDec())*rq.request_pos.quantity.GetExt().GetInc());
    if(rq.request_pos.quantity.GetIntCode()!=0)
        ui->quantity->setValue(rq.request_pos.quantity.GetDouble().get()._0);
    else
        ui->quantity->clear();
    ui->cliref->setText(QLatin1String(rq.cli_ref.c_str()));

    this->check_if_order_can_be_sent();

    mtk::Nullable<std::string>  s_default_qty =  mtk::admin::get_config_property("MISC.default_qty");
    if(s_default_qty.HasValue()==false)
    {
        ui->message->setText(tr("you can configure default qty with dblclick on qty label"));
    }
    else
    {
        if(rq.request_pos.quantity.GetIntCode() == 0)
        {
            QLatin1String default_q (s_default_qty.Get().c_str());
            ui->quantity->setValue(QString(default_q).toDouble());
        }
        else
            ui->quantity->setValue(rq.request_pos.quantity.GetDouble().get()._0);
    }

    ui->quantity->setFocus();
    ui->quantity->selectAll();
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
    result.product_code.market = ui->market->text().toStdString();
    result.product_code.product = ui->product->text().toStdString();
    result.request_pos.price.SetDouble(ui->price->value());
    result.request_pos.quantity.SetDouble(ui->quantity->value());
    result.cli_ref = ui->cliref->text().toStdString();
    return result;
}

mtk::trd::msg::RQ_XX_MK   QEditOrder::get_request_mk(void)
{
    mtk::trd::msg::RQ_XX_MK  result = rq_mk.Get();
    result.product_code.market = ui->market->text().toStdString();
    result.product_code.product = ui->product->text().toStdString();
    result.request_pos.quantity.SetDouble(ui->quantity->value());
    result.cli_ref = ui->cliref->text().toStdString();
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
}
