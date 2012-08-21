#include "qlabelproduct.h"

#include <QDragEnterEvent>

#include "ecimd_styles.h"
#include "qmtk_misc.h"
#include "QDragLeaveEvent"
#include <QApplication>



QLabelProduct::QLabelProduct(QWidget *parent) :
    QLabel(parent)
{
    this->setAcceptDrops(true);
    check_info_pending();
}


void QLabelProduct::dragEnterEvent(QDragEnterEvent *event)
{
    QLabel::dragEnterEvent(event);

    if(qtmisc::has_product_code(event))
    {
        event->setDropAction(Qt::CopyAction);
        event->accept();
        this->setStyleSheet(ecimd_styles::style_get_label_product_drag_over_ok());
    }
    else
        event->ignore();
}


bool QLabelProduct::event ( QEvent * event )
{
    if(dynamic_cast<QDragLeaveEvent*>(event))
    {
        check_info_pending();
    }
    return QLabel::event(event);
}


void QLabelProduct::dropEvent(QDropEvent *event)
{
    mtk::msg::sub_product_code  product_code = qtmisc::get_product_code(event);
    this->setFocus();
    this->setText(QLatin1String(MTK_SS(product_code.market << "." << product_code.product).c_str()));
    this->adjustSize();
    check_info_pending();
    subscribe_to(product_code);
}


void QLabelProduct::subscribe_to (const mtk::msg::sub_product_code& _product_code)
{
    price_manager = mtk::make_cptr(new mtk::prices::price_manager(_product_code));


    MTK_CONNECT_THIS(price_manager->signal_additional_info_update,      on_message_additional_info_update);
    price_manager->signal_additional_info_update.connect(&signal_additional_info_update);

    price_manager->signal_best_prices_update.connect(&signal_best_prices_update);
    price_manager->signal_last_mk_execs_ticker.connect(&signal_last_mk_execs_ticker);

    check_info_pending();

    signal_product_configured.emit(_product_code);


    if(price_manager->get_additional_info().HasValue())
        signal_additional_info_update.emit(_product_code, price_manager->get_additional_info().Get());

    if(price_manager->get_best_prices().HasValue())
        signal_best_prices_update.emit(_product_code, price_manager->get_best_prices().Get());

    if(price_manager->get_last_mk_execs_ticker().HasValue())
        signal_last_mk_execs_ticker.emit(_product_code, price_manager->get_last_mk_execs_ticker().Get());
}


void QLabelProduct::on_message_additional_info_update(const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_additional_info& /*msg*/)
{
    check_info_pending();
}


void QLabelProduct::check_info_pending(void)
{
    if(price_manager.isValid()  &&  price_manager->get_additional_info().HasValue())
    {
        this->setStyleSheet(ecimd_styles::style_get_label_product_ok());
        this->setToolTip(tr(""));
    }
    else
    {
        this->setStyleSheet(ecimd_styles::style_get_label_product_missing_info());
        this->setToolTip(tr("missing product info"));
    }
}


void QLabelProduct::mouseMoveEvent(QMouseEvent *event)
{
    if(price_manager.isValid() == false)        return;


    QLabel::mouseMoveEvent(event);
    if ((event->buttons() & Qt::LeftButton)  &&  startPos.x()>=0  &&  startPos.y()>=0)
    {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance()+5  &&  mtk::msg::is_valid(price_manager->get_product_code()))
        {
            QMimeData* mimeData = new QMimeData;
            mimeData->setText(qtmisc::dragProductText(price_manager->get_product_code()));
            QDrag* drag = new QDrag(this);
            drag->setMimeData(mimeData);

            QPixmap pixmap (this->size());
            this->render(&pixmap);
            drag->setPixmap(pixmap);

            drag->exec(Qt::CopyAction);
        }
    }

}

void QLabelProduct::mousePressEvent(QMouseEvent *event)
{
    startPos = event->pos();
    QLabel::mousePressEvent(event);
}

void QLabelProduct::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    startPos = QPoint(-1,-1);
}
