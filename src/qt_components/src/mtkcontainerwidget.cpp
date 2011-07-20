#include "mtkcontainerwidget.h"


#include <QMouseEvent>
#include <QPainter>
#include <QMessageBox>


#include "qt_components/src/qmtk_misc.h"

#include "yaml/yaml.h"




mtk_uTitle::mtk_uTitle(QWidget *parent) :
    QWidget(parent), moving(false)
{
    /*
    QPalette p(palette());
    p.setColor(QPalette::Background, Qt::blue);
    this->setPalette(p);
    */
    this->setMouseTracking(true);
    updateBackground(false);
    this->setStyleSheet(QLatin1String("background-color: rgba(0, 0, 255, 200);"));

    image_close.load(QLatin1String(":/small_icons/image_close"));
}



void mtk_uTitle::updateBackground(bool show)
{
    this->setAutoFillBackground(show);
}


void mtk_uTitle::mousePressEvent(QMouseEvent* event)
{
    if (event->pos().x()  <  image_close.width())
    {
    //if (event->pos().x()  >  this->width()-image_close.width())
        //dynamic_cast<mtkContainerWidget*>(this->parent())->close();
        if(QMessageBox::warning(this->parentWidget(), QLatin1String("CimdTrade"), tr("Do you want to remove the component?"), QMessageBox::Ok, QMessageBox::Cancel)==QMessageBox::Ok)
            dynamic_cast<mtkContainerWidget*>(this->parent())->deleteLater();
        else
            return;
    }
    moving = true;
    updateBackground(true);
    event->accept(); // do not propagate
    Q_EMIT on_mousePressEvent(event);
}

void mtk_uTitle::mouseMoveEvent(QMouseEvent* event)
{
    updateBackground(true);
    if (moving)
    {
        event->accept(); // do not propagate
        Q_EMIT on_mouseMoveEvent(event);
    }
}

void mtk_uTitle::leaveEvent ( QEvent * event )
{
    event->accept();
    updateBackground(false);
}

void mtk_uTitle::mouseReleaseEvent(QMouseEvent* event)
{
    moving = false;
    event->accept(); // do not propagate
    Q_EMIT on_mouseReleaseEvent(event);
}

void mtk_uTitle::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    if(this->autoFillBackground())
    {
        QPainter qpainter(this);
        //qpainter.drawImage(this->width()-image_close.width(), 0, image_close);
        qpainter.drawImage(0, 0, image_close);
    }
}




mtk_uResize::mtk_uResize(QWidget *parent) :
    QWidget(parent)
{
    basecolor = this->palette().background().color();
    setCursor(QCursor(Qt::SizeFDiagCursor));
}



void mtk_uResize::mouseMoveEvent(QMouseEvent* event)
{
    event->accept(); // do not propagate
    QMouseEvent new_event(event->type(), mapToParent(event->pos()), event->globalPos(), event->button(), event->buttons(), event->modifiers());
    Q_EMIT on_mouseMoveEvent(&new_event);
}


/*
void mtk_uResize::mousePressEvent(QMouseEvent* event)
{
    event->accept(); // do not propagate
}

void mtk_uResize::mouseReleaseEvent(QMouseEvent* event)
{
    event->accept(); // do not propagate
}
*/




mtkContainerWidget::mtkContainerWidget(QWidget *parent) :
    QWidget(parent)
{
    title = new mtk_uTitle(this);
    title->setGeometry(0,0,80,15);
    connect(title, SIGNAL(on_mouseMoveEvent(QMouseEvent*)), this, SLOT(title_mouseMoveEvent(QMouseEvent*)));
    connect(title, SIGNAL(on_mousePressEvent(QMouseEvent*)), this, SLOT(title_mousePressEvent(QMouseEvent*)));
    connect(title, SIGNAL(on_mouseReleaseEvent(QMouseEvent*)), this, SLOT(title_mouseReleaseEvent(QMouseEvent*)));


    resizer = new mtk_uResize(this);
    connect(resizer, SIGNAL(on_mouseMoveEvent(QMouseEvent*)), this, SLOT(resize_mouseMoveEvent(QMouseEvent*)));

    this->setFocusPolicy(Qt::StrongFocus);

    /*QPalette p(palette());
    p.setColor(QPalette::Background, Qt::red);
    this->setAutoFillBackground(true);
    this->setPalette(p);*/
    this->setAutoFillBackground(false);
}


void mtkContainerWidget::title_mousePressEvent(QMouseEvent* event)
{
    Q_EMIT signal_start_moving();

    if (isWindow())
        moving_offset = event->globalPos() - pos();
    else
        moving_offset = event->pos();
}

void mtkContainerWidget::title_mouseMoveEvent(QMouseEvent* event)
{
    if (isWindow())
    {
        QPoint new_pos (event->globalPos() - moving_offset);
        if (new_pos.y() <= -6)
            new_pos.setY(-6);

        move(new_pos);
    }
    else
    {
        QPoint new_pos (mapToParent(event->pos() - moving_offset));
        if (new_pos.y() <= -6)
            new_pos.setY(-6);
        if (new_pos.x() <= -6)
            new_pos.setX(-6);
        if (new_pos.x() >= 2000-30)
            new_pos.setX(2000-30);
        if (new_pos.y() >= 1080-30)
            new_pos.setY(1080-30);
        move(new_pos/10*10 + QPoint(6,6));
        Q_EMIT signal_moving(this->geometry());
    }
}

void mtkContainerWidget::title_mouseReleaseEvent(QMouseEvent* /*event*/)
{
    moving_offset = QPoint();
    Q_EMIT signal_stop_moving();
}


void	mtkContainerWidget::resizeEvent ( QResizeEvent * /*event*/ )
{
    resizer->setGeometry(this->width()-20, this->height()-20, 20, 20);
    resizer->raise();
    Q_EMIT signal_moving(this->geometry());
}


void mtkContainerWidget::resize_mouseMoveEvent(QMouseEvent* event)
{
    QPoint temppos = (event->pos());
    QSize  newsize (temppos.x(), temppos.y());
    if (newsize.width() < 100)
        newsize.setWidth(100);
    if (newsize.height() < 100)
        newsize.setHeight(100);
    newsize = newsize/10*10;
    newsize.setWidth(newsize.width()-1);
    resize(newsize);
}

void mtkContainerWidget::inserting_components_ended(void)
{
    resizer->raise();
    title->raise();
}

void mtkContainerWidget::paintEvent   (QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter qpainter(this);

    QColor color = qtmisc::mtk_color_header;
    if (this->hasFocus())
        color = Qt::blue;
    QPen pen = QPen(color, 1, Qt::SolidLine);
    qpainter.setPen(pen);
    qpainter.drawLine(4, 4, 4, this->height()-5);
    qpainter.drawLine(4, 4, this->width()-5, 4);
    qpainter.drawLine(this->width()-5, 4, this->width()-5, this->height()-5);
    qpainter.drawLine(4, this->height()-5, this->width()-5, this->height()-5);
}


YAML::Emitter& operator << (YAML::Emitter& out, const mtkContainerWidget& m)
{
    out     << YAML::BeginMap;

    //  writing geometry
    out << YAML::Key   <<  "geometry";
    out << YAML::Value << YAML::Flow << YAML::BeginSeq;
    out << m.geometry().top() << m.geometry().left() << m.geometry().width() << m.geometry().height();
    out << YAML::EndSeq;
    //  end geometry

    out << YAML::EndMap;

    return out;
}

void             operator >> (const YAML::Node& node,    mtkContainerWidget& m)
{
    int top, left, width, height;

    node["geometry"][0] >> top;
    node["geometry"][1] >> left;
    node["geometry"][2] >> width;
    node["geometry"][3] >> height;

    m.setGeometry(left, top, width, height);
}
