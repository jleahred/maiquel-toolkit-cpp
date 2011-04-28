#include "qeditorder.h"
#include "ui_qeditorder.h"


#include "qt_components/src/qmtk_misc.h"



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


QEditOrder::QEditOrder(const mtk::trd::msg::RQ_XX_LS& _rq, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::QEditOrder),
        rq(_rq)
{
    ui->setupUi(this);
    QFont font(this->font());
    font.setPixelSize(get_base_font_size());
    this->setFont(font);

    rq = _rq;
    if (rq.request_pos.side == mtk::trd::msg::buy)
    {
        ui->BuySell->setText(tr("BUY"));
        setPalette( mtk_green );
    }
    else
    {
        ui->BuySell->setText(tr("SELL"));
        setPalette( QPalette(mtk_red));
        //setPalette( QPalette( Qt::red ) );
    }
    ui->market->setText(QLatin1String(rq.product_code.sys_code.market.c_str()));
    ui->product->setText(QLatin1String(rq.product_code.sys_code.product.c_str()));
    ui->price->setDecimals(rq.request_pos.price.GetExt().GetDec());
    ui->price->setSingleStep(1./pow(10.,rq.request_pos.price.GetExt().GetDec())*rq.request_pos.price.GetExt().GetInc());
    if(rq.request_pos.quantity.GetIntCode()!=0)
        ui->price->setValue(rq.request_pos.price.GetDouble().get()._0);
    else
        ui->price->clear();
    ui->quantity->setDecimals(rq.request_pos.quantity.GetExt().GetDec());
    ui->quantity->setSingleStep(1./pow(10.,rq.request_pos.quantity.GetExt().GetDec())*rq.request_pos.quantity.GetExt().GetInc());
    if(rq.request_pos.quantity.GetIntCode()!=0)
        ui->quantity->setValue(rq.request_pos.quantity.GetDouble().get()._0);
    else
        ui->quantity->clear();
    ui->cliref->setText(QLatin1String(rq.cli_ref.c_str()));

    this->check_if_order_can_be_sent();
    ui->price->setFocus();
    ui->price->selectAll();
}

void QEditOrder::check_if_order_can_be_sent(void)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    ui->message->setText(QLatin1String(""));

    int pos = 0;
    QString text;

    text = ui->quantity->text();
    if(ui->quantity->validate(text, pos) != QValidator::Acceptable)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->message->setText(tr("invalid quantity"));
    }

    text = ui->price->text();
    if(ui->price->validate(text, pos) != QValidator::Acceptable)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->message->setText(tr("invalid price"));
    }

    if(ui->account->currentIndex() == -1)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->message->setText(tr("empty account"));
    }

    if(ui->product->text().isEmpty())
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->message->setText(tr("empty product"));
    }

    if(ui->market->text().isEmpty())
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->message->setText(tr("empty market"));
    }
}


mtk::trd::msg::RQ_XX_LS   QEditOrder::get_request(void)
{
    rq.product_code.sys_code.market = ui->market->text().toStdString();
    rq.product_code.sys_code.product = ui->product->text().toStdString();
    rq.request_pos.price.SetDouble(ui->price->value());
    rq.request_pos.quantity.SetDouble(ui->quantity->value());
    rq.cli_ref = ui->cliref->text().toStdString();
    return rq;
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

