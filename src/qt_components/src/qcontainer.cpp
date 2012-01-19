#include "qcontainer.h"


#include <iostream>


#include <QMouseEvent>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QScrollBar>
#include <QMessageBox>



#include "qt_components/src/qdepth.h"
#include "qt_components/src/qmarginal.h"


#include "support/string_codec.h"
#include "yaml/yaml.h"






qContainer::qContainer(QWidget *parent) :
    QScrollArea(parent), counter_insertions(0)
{
}


QMarginal*  qContainer::insert_qmarginal(void)
{
    QMarginal* marginals= new QMarginal(this->widget());
    connect(marginals, SIGNAL(signal_stop_moving()), this, SLOT(slot_widget_moved_or_deleted()));
    marginals->move(QPoint(counter_insertions*20+7, counter_insertions*20+7) );
    ++counter_insertions;
    counter_insertions %= 6;
    marginals->show();

    return marginals;
}

QDepth* qContainer::insert_qdepth()
{
    QDepth* depth= new QDepth(this->widget());
    connect(depth, SIGNAL(signal_stop_moving()), this, SLOT(slot_widget_moved_or_deleted()));
    depth->move(QPoint(counter_insertions*20+7, counter_insertions*20+7) );
    ++counter_insertions;
    counter_insertions %= 6;
    depth->show();

    return depth;
}



YAML::Emitter& operator << (YAML::Emitter& out, const qContainer& m)
{
    out << YAML::BeginMap;
    out << YAML::Key  << "tables_marginal"  << YAML::Value
                                            << YAML::BeginSeq;
    for(int i=0; i<m.widget()->children().count(); ++i)
    {
        QMarginal* marginal = dynamic_cast<QMarginal*>(m.widget()->children().at(i));
        if(marginal!=0)
            out << *marginal;
    }
    out << YAML::EndSeq;

    out << YAML::Key  << "tables_depths"  << YAML::Value
                                            << YAML::BeginSeq;

    for(int i=0; i<m.widget()->children().count(); ++i)
    {
        QDepth* depth = dynamic_cast<QDepth*>(m.widget()->children().at(i));
        if(depth!=0)
            out << *depth;
    }
    out << YAML::EndSeq;

    out << YAML::EndMap;
    return out;
}

void     operator>> (const YAML::Node & node   , qContainer& c)
{
    for(unsigned i=0; i<node["tables_marginal"].size(); ++i)
    {
        QMarginal* marginal = c.insert_qmarginal();
        node["tables_marginal"][i] >>  *marginal;
    }
    for(unsigned i=0; i<node["tables_depths"].size(); ++i)
    {
        QDepth* d = c.insert_qdepth();
        node["tables_depths"][i] >>  *d;
    }
    c.slot_widget_moved_or_deleted();
}


void qContainer::slot_widget_moved_or_deleted(void)
{
    int maxwith = 30;
    int maxheigh = 30;
    for(int i=0; i<this->children().at(0)->children().at(0)->children().count(); ++i)
    {
        mtkContainerWidget* mtkwidget = dynamic_cast<mtkContainerWidget*>(this->children().at(0)->children().at(0)->children().at(i));
        if(mtkwidget != 0)
        {
            if(maxheigh < mtkwidget->geometry().top()+mtkwidget->geometry().height())
                maxheigh = mtkwidget->geometry().top()+mtkwidget->geometry().height();
            if(maxwith < mtkwidget->geometry().left()+mtkwidget->geometry().width())
                maxwith = mtkwidget->geometry().left()+mtkwidget->geometry().width();
        }
    }

    bool  will_show_horiz_sb = 0;
    bool  will_show_vert_sb = 0;
    if(maxwith > this->geometry().width())
        will_show_horiz_sb = 1;
    if(maxheigh > this->geometry().height())
        will_show_vert_sb = 1;

    int  hsb_value = this->horizontalScrollBar()->value();
    int  vsb_value = this->verticalScrollBar()->value();


    if(maxwith < this->geometry().width() - will_show_vert_sb * this->verticalScrollBar()->width())
        maxwith  =  this->geometry().width()-4    - will_show_vert_sb * this->verticalScrollBar()->width();
    if(maxheigh < this->geometry().height()- will_show_horiz_sb * this->verticalScrollBar()->width())
        maxheigh  =  this->geometry().height()-4  - will_show_horiz_sb * this->verticalScrollBar()->width();
    static int  prev_maxwith;
    static int  prev_maxheigh;
    if(prev_maxheigh != maxheigh   ||  prev_maxwith  !=  maxheigh)
        this->widget()->setGeometry(0,0,maxwith, maxheigh);

    this->horizontalScrollBar()->setValue(hsb_value);
    this->verticalScrollBar()->setValue(vsb_value);
}


void qContainer::resizeEvent ( QResizeEvent * event)
{
    QScrollArea::resizeEvent ( event );
    slot_widget_moved_or_deleted();
}
