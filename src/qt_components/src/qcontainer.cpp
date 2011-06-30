#include "qcontainer.h"


#include <iostream>


#include <QMouseEvent>
#include <QVBoxLayout>
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
    marginals->move(QPoint(counter_insertions*20+7, counter_insertions*20+7) );
    ++counter_insertions;
    counter_insertions %= 6;
    marginals->show();

    return marginals;
}

QDepth* qContainer::insert_qdepth()
{
    QDepth* depth= new QDepth(this->widget());
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
}




using namespace std;

