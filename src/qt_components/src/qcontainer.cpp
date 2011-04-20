#include "qcontainer.h"


#include "qt_components/src/qdepth.h"
#include "qt_components/src/qmarginal.h"



qContainer::qContainer(QWidget *parent) :
    QScrollArea(parent), last_inserted_pos(5,5)
{

    //QPalette p(this->palette());
    ////p.setColor(QPalette::Window, QColor(62,96,111));
    //p.setColor(QPalette::Window, QColor(Qt::darkGray).darker(150));
    //this->setPalette(p);
    //this->setBackgroundRole(QPalette::Dark);

    //this->setBackgroundRole(QPalette::Dark);
}


void qContainer::insert_qmarginal(void)
{
    QMarginal* marginals= new QMarginal(this->widget());
    marginals->move(last_inserted_pos);
    last_inserted_pos += QPoint(20, 20);
    marginals->show();
}

void qContainer::insert_qdepth()
{
    QDepth* depth= new QDepth(this->widget());
    depth->move(last_inserted_pos);
    last_inserted_pos += QPoint(20, 20);
    depth->show();
}
