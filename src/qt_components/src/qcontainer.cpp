#include "qcontainer.h"


#include <iostream>


#include <QMouseEvent>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QScrollBar>
#include <QMessageBox>



#include "qt_components/src/qdepth.h"
#include "qt_components/src/qmarginal2.h"
#include "qt_components/src/qalarm_price.h"
#include "qt_components/src/qprod_info.h"
#include "qt_components/src/qticker_execs.h"
#include "qt_components/src/automatics/switch_money/qswitch_money.h"



#include "support/string_codec.h"
#include "components/admin/admin.h"
#include "yaml/yaml.h"






qContainer::qContainer(QWidget *parent) :
    QScrollArea(parent), counter_insertions(0)
{
    this->setFocusPolicy(Qt::NoFocus);
}



void     qContainer::insert_component        (QWidget* compo)
{
    connect(compo, SIGNAL(signal_stop_moving()), this, SLOT(slot_widget_moved_or_deleted()));
    compo->move(QPoint(counter_insertions*20+7, counter_insertions*20+7) );
    ++counter_insertions;
    counter_insertions %= 6;
    compo->show();
    compo->setFocus();
    compo->adjustSize();
}



QMarginal2*  qContainer::insert_qmarginal2(void)
{
    auto compo= new QMarginal2(this->widget());
    insert_component(compo);
    return compo;
    /*
    auto compo= new QMarginal2(this->widget());
    connect(compo, SIGNAL(signal_stop_moving()), this, SLOT(slot_widget_moved_or_deleted()));
    compo->move(QPoint(counter_insertions*20+7, counter_insertions*20+7) );
    ++counter_insertions;
    counter_insertions %= 6;
    compo->show();
    compo->setFocus();
    compo->adjustSize();
    return compo;
    */
}



QDepth* qContainer::insert_qdepth()
{
    QDepth* compo= new QDepth(this->widget());
    insert_component(compo);
    return compo;
    /*
    connect(compo, SIGNAL(signal_stop_moving()), this, SLOT(slot_widget_moved_or_deleted()));
    compo->move(QPoint(counter_insertions*20+7, counter_insertions*20+7) );
    ++counter_insertions;
    counter_insertions %= 6;
    compo->show();
    compo->setFocus();
    compo->adjustSize();
    return compo;
    */
}


QAlarmPrice*    qContainer::insert_qalarm_price     (void)
{
    QAlarmPrice* compo= new QAlarmPrice(this->widget());
    insert_component(compo);
    return compo;
    /*
    connect(compo, SIGNAL(signal_stop_moving()), this, SLOT(slot_widget_moved_or_deleted()));
    compo->move(QPoint(counter_insertions*20+7, counter_insertions*20+7) );
    ++counter_insertions;
    counter_insertions %= 6;
    compo->show();
    compo->setFocus();
    compo->adjustSize();
    return compo;
    */
}

QProd_info*    qContainer::insert_qproduct_info     (void)
{
    QProd_info* compo= new QProd_info(this->widget());
    insert_component(compo);
    return compo;
    /*
    connect(compo, SIGNAL(signal_stop_moving()), this, SLOT(slot_widget_moved_or_deleted()));
    compo->move(QPoint(counter_insertions*20+7, counter_insertions*20+7) );
    ++counter_insertions;
    counter_insertions %= 6;
    compo->show();
    compo->setFocus();
    compo->adjustSize();
    return compo;
    */
}


QTickerExecs*   qContainer::insert_qticker_execs    (void)
{
    QTickerExecs* compo= new QTickerExecs(this->widget());
    insert_component(compo);
    return compo;
    /*
    connect(compo, SIGNAL(signal_stop_moving()), this, SLOT(slot_widget_moved_or_deleted()));
    compo->move(QPoint(counter_insertions*20+7, counter_insertions*20+7) );
    ++counter_insertions;
    counter_insertions %= 6;
    compo->show();
    compo->setFocus();
    compo->adjustSize();
    return compo;
    */
}

QSwicthMoney*   qContainer::insert_qswitch_money    (void)
{
    QSwicthMoney* compo= new QSwicthMoney(this->widget());
    insert_component(compo);
    return compo;
    /*
    connect(compo, SIGNAL(signal_stop_moving()), this, SLOT(slot_widget_moved_or_deleted()));
    compo->move(QPoint(counter_insertions*20+7, counter_insertions*20+7) );
    ++counter_insertions;
    counter_insertions %= 6;
    compo->show();
    compo->setFocus();
    compo->adjustSize();
    return compo;
    */
}




YAML::Emitter& operator << (YAML::Emitter& out, const qContainer& m)
{
    out << YAML::BeginMap;




        out << YAML::Key  << "tables_marginal2"  << YAML::Value
                                                << YAML::BeginSeq;
        for(int i=0; i<m.widget()->children().count(); ++i)
        {
            QMarginal2* compo = dynamic_cast<QMarginal2*>(m.widget()->children().at(i));
            if(compo!=0)
                out << *compo;
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



        out << YAML::Key  << "alarm_tables"  << YAML::Value
                                                << YAML::BeginSeq;

        for(int i=0; i<m.widget()->children().count(); ++i)
        {
            QAlarmPrice* compo = dynamic_cast<QAlarmPrice*>(m.widget()->children().at(i));
            if(compo!=0)
                out << *compo;
        }
        out << YAML::EndSeq;





        out << YAML::Key  << "produtct_info"  << YAML::Value
                                                << YAML::BeginSeq;

        for(int i=0; i<m.widget()->children().count(); ++i)
        {
            QProd_info* compo = dynamic_cast<QProd_info*>(m.widget()->children().at(i));
            if(compo!=0)
                out << *compo;
        }
        out << YAML::EndSeq;



        out << YAML::Key  << "ticker_execs"  << YAML::Value  << YAML::BeginSeq;
        for(int i=0; i<m.widget()->children().count(); ++i)
        {
            QTickerExecs* compo = dynamic_cast<QTickerExecs*>(m.widget()->children().at(i));
            if(compo!=0)
                out << *compo;
        }
        out << YAML::EndSeq;


        out << YAML::Key  << "switch_money"  << YAML::Value  << YAML::BeginSeq;
        for(int i=0; i<m.widget()->children().count(); ++i)
        {
            QSwicthMoney* compo = dynamic_cast<QSwicthMoney*>(m.widget()->children().at(i));
            if(compo!=0)
                out << *compo;
        }
        out << YAML::EndSeq;



    out << YAML::EndMap;
    return out;
}

void     operator>> (const YAML::Node & node   , qContainer& c)
{
    if(node.FindValue("tables_marginal"))
    {
        for(unsigned i=0; i<node["tables_marginal"].size(); ++i)
        {
            QMarginal2* compo = c.insert_qmarginal2();
            node["tables_marginal"][i] >>  *compo;
        }
    }


    if(node.FindValue("tables_marginal2"))
    {
        for(unsigned i=0; i<node["tables_marginal2"].size(); ++i)
        {
            QMarginal2* compo = c.insert_qmarginal2();
            node["tables_marginal2"][i] >>  *compo;
        }
    }


    if(node.FindValue("tables_depths"))
    {
        for(unsigned i=0; i<node["tables_depths"].size(); ++i)
        {
            QDepth* d = c.insert_qdepth();
            node["tables_depths"][i] >>  *d;
        }
    }

    if(node.FindValue("alarm_tables"))
    {
        for(unsigned i=0; i<node["alarm_tables"].size(); ++i)
        {
            QAlarmPrice* d = c.insert_qalarm_price();
            node["alarm_tables"][i] >>  *d;
        }
    }

    if(node.FindValue("produtct_info"))
    {
        for(unsigned i=0; i<node["produtct_info"].size(); ++i)
        {
            QProd_info* d = c.insert_qproduct_info();
            node["produtct_info"][i] >>  *d;
        }
    }


    if(node.FindValue("ticker_execs"))
    {
        for(unsigned i=0; i<node["ticker_execs"].size(); ++i)
        {
            QTickerExecs* d = c.insert_qticker_execs();
            node["ticker_execs"][i] >>  *d;
        }
    }

    if(node.FindValue("switch_money"))
    {
        for(unsigned i=0; i<node["switch_money"].size(); ++i)
        {
            QSwicthMoney* d = c.insert_qswitch_money();
            node["switch_money"][i] >>  *d;
        }
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


