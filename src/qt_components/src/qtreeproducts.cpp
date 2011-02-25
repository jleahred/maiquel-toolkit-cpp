#include "qtreeproducts.h"

#include <QMouseEvent>
#include <QApplication>
#include <QTreeWidgetItem>
#include <QPainter>

#include "components/msg_common.h"
#include "qmtk_misc.h"











class QShowTree : public QWidget
{
public:
    QShowTree(QWidget* w): QWidget(w)
    {
        setAutoFillBackground(false);

        //QPalette p(palette());
        //p.setColor(QPalette::Background, QColor(0,0,255,160));
        //setPalette(p);

        //this->setStyleSheet("background-color: rgba(0,0,255,160, 0);");
        raise();
        setMouseTracking(true);
        this->setStyleSheet("background-color: rgba(0, 0, 255, 0); color:rgba(255,255,255)");
    }

    void paintEvent(QPaintEvent /**event*/)
    {
        //QWidget::paintEvent(event);
        if (autoFillBackground())
        {
            QPainter painter(this);
            painter.save();
            //painter.fillRect(this->rect(), QColor(0,0,255,160));
            painter.translate(this->width()-3, this->height()-10);
            painter.rotate(270);
            painter.setPen(Qt::white);
            painter.setBrush(QBrush(QColor(Qt::white)));
            painter.drawText(0, 0, "tree prods");
            painter.restore();
        }
    }

    void mousePressEvent(QMouseEvent *event) {
        QWidget::mousePressEvent(event);
        if(event->button() == Qt::LeftButton)
            signal_click.emit();
    }

    void mouseMoveEvent(QMouseEvent *event) { QWidget::mouseMoveEvent(event); this->setAutoFillBackground(true); this->setStyleSheet("background-color: rgba(0,0,255,160, 160); color:rgba(255,255,255,255)");}

    void leaveEvent(QEvent *)  { setAutoFillBackground(false);  this->setStyleSheet("background-color: rgba(0, 0, 255, 0); color:rgba(255,255,255,255)");  }

    mtk::Signal<>  signal_click;
};





qTreeProducts::qTreeProducts(QWidget *parent) :
    QTreeWidget(parent)
{
    //QShowTree* open_tree (new QShowTree(dynamic_cast<QWidget*>(this->parent()->parent()->parent())));
    QShowTree* open_tree (new QShowTree(this));
    open_tree->setParent(dynamic_cast<QWidget*>(this->parent()->parent()->parent()));
    open_tree->setGeometry(1, 1, 17, 100);
    MTK_CONNECT_THIS(open_tree->signal_click, show_tree)
    setVisible(false);
}


void qTreeProducts::show_tree(void)
{
    if (this->isVisible())
        this->setVisible(false);
   else
       this->setVisible(true);
}

void qTreeProducts::mousePressEvent(QMouseEvent *event)
{
    QTreeWidget::mousePressEvent(event);
    if (event->button() == Qt::LeftButton)
        startPos = event->pos();
}

void qTreeProducts::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance())
            start_drag();
    }
    QTreeWidget::mouseMoveEvent(event);
}


void qTreeProducts::start_drag(void)
{
    QTreeWidgetItem* item = currentItem();
    if (item)
    {
        QMimeData* mimeData = new QMimeData;
        mtk::msg::sub_single_product_code spc(mtk::msg::sub_single_product_code("MARKET", item->text(0).toStdString(), mtk::nullable<std::string>()));
        mimeData->setText(dragProductText(mtk::msg::sub_product_code(spc, mtk::nullable<mtk::msg::sub_single_product_code>(), mtk::make_nullable(std::string("aaaaa")))));
        //mimeData->setText("PRODUCT>MARKET::" + item->text(0));
        QDrag* drag = new QDrag(this);
        drag->setMimeData(mimeData);

        QRect rect(this->visualItemRect(this->currentItem()));
        QPixmap pixmap (rect.size());
        this->render(&pixmap, QPoint(), rect);
        drag->setPixmap(pixmap);

        drag->start(Qt::CopyAction);
    }
}
