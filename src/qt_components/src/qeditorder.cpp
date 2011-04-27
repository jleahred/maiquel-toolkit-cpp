#include "qeditorder.h"
#include "ui_qeditorder.h"


#include "qt_components/src/qmtk_misc.h"

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
    ui->price->setValue(rq.request_pos.price.GetDouble().get()._0);
    ui->price->setDecimals(rq.request_pos.price.GetExt().GetDec());
    ui->price->setSingleStep(1./pow(10.,rq.request_pos.price.GetExt().GetDec())*rq.request_pos.price.GetExt().GetInc());
    ui->quantity->setValue(rq.request_pos.quantity.GetDouble().get()._0);
    ui->quantity->setDecimals(rq.request_pos.quantity.GetExt().GetDec());
    ui->quantity->setSingleStep(1./pow(10.,rq.request_pos.quantity.GetExt().GetDec())*rq.request_pos.quantity.GetExt().GetInc());
    ui->cliref->setText(QLatin1String(rq.cli_ref.c_str()));
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
