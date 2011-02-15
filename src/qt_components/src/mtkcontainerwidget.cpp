#include "mtkcontainerwidget.h"


#include <QMouseEvent>





mtk_uTitle::mtk_uTitle(QWidget *parent) :
    QWidget(parent), moving(false)
{
    //basecolor = this->palette().background().color();
    //basecolor = Qt::darkBlue;
    //this->setAutoFillBackground(true);

    QPalette p(palette());
    p.setColor(QPalette::Background, Qt::blue);
    this->setPalette(p);

    this->setMouseTracking(true);
    updateBackground(false);
    setCursor(QCursor(Qt::SizeAllCursor));
}



void mtk_uTitle::updateBackground(bool show)
{
    this->setAutoFillBackground(show);
}


void mtk_uTitle::mousePressEvent(QMouseEvent* event)
{
    moving = true;
    updateBackground(true);
    event->accept(); // do not propagate
    emit on_mousePressEvent(event);
}

void mtk_uTitle::mouseMoveEvent(QMouseEvent* event)
{
    updateBackground(true);
    if (moving)
    {
        event->accept(); // do not propagate
        emit on_mouseMoveEvent(event);
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
    emit on_mouseReleaseEvent(event);
}




mtk_uResize::mtk_uResize(QWidget *parent) :
    QWidget(parent)
{
    basecolor = this->palette().background().color();
    //this->setAutoFillBackground(true);
    updateBackground(false);
    setCursor(QCursor(Qt::SizeFDiagCursor));
}

void mtk_uResize::updateBackground(bool focus)
{
    QPalette p(palette());
    //if (focus)
    //    p.setColor(QPalette::Background, basecolor.lighter());
    //else
        p.setColor(QPalette::Background, basecolor);
    this->setPalette(p);
}



void mtk_uResize::mouseMoveEvent(QMouseEvent* event)
{
    event->accept(); // do not propagate
    QMouseEvent new_event(event->type(), mapToParent(event->pos()), event->globalPos(), event->button(), event->buttons(), event->modifiers());
    emit on_mouseMoveEvent(&new_event);
}



void mtk_uResize::mousePressEvent(QMouseEvent* event)
{
    event->accept(); // do not propagate
    updateBackground(true);
}

void mtk_uResize::mouseReleaseEvent(QMouseEvent* event)
{
    event->accept(); // do not propagate
    updateBackground(false);
}





mtkContainerWidget::mtkContainerWidget(QWidget *parent) :
    QWidget(parent)
{
    title = new mtk_uTitle(this);
    title->setGeometry(0,0,60,15);
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

}


void mtkContainerWidget::title_mousePressEvent(QMouseEvent* event)
{
    if (isWindow())
        moving_offset = event->globalPos() - pos();
    else
        moving_offset = event->pos();
}

void mtkContainerWidget::title_mouseMoveEvent(QMouseEvent* event)
{
    if (isWindow())
        move(event->globalPos() - moving_offset);
    else
        move(mapToParent(event->pos() - moving_offset));
}

void mtkContainerWidget::title_mouseReleaseEvent(QMouseEvent* /*event*/)
{
    moving_offset = QPoint();
}


void	mtkContainerWidget::resizeEvent ( QResizeEvent * /*event*/ )
{
    resizer->setGeometry(this->width()-20, this->height()-20, 20, 20);
    resizer->raise();
}


void mtkContainerWidget::resize_mouseMoveEvent(QMouseEvent* event)
{
    QPoint temppos = (event->pos());
    QSize  newsize (temppos.x(), temppos.y());
    if (newsize.width() < 100)
        newsize.setWidth(100);
    if (newsize.height() < 100)
        newsize.setHeight(100);
    resize(newsize);
}

void mtkContainerWidget::inserting_components_ended(void)
{
    resizer->raise();
    title->raise();
}

