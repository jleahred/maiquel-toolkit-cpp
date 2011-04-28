#include "qcontainer.h"


#include <iostream>
#include <fstream>


#include <QMouseEvent>
#include <QVBoxLayout>

#include "qt_components/src/qdepth.h"
#include "qt_components/src/qmarginal.h"


#include "support/string_codec.h"
#include "yaml/yaml.h"






qContainer::qContainer(QWidget *parent) :
    QScrollArea(parent), last_inserted_pos(7, 7)
{
    this->viewport()->setBackgroundRole(QPalette::Dark);
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


void qContainer::save_config(void)
{
    std::ofstream config_file;
    config_file.open ("cimdtrade.cfg");


   YAML::Emitter out;
   out
    <<  YAML::BeginMap
                <<  YAML::Key << "version"   <<  YAML::Value << 1
                << YAML::Key  << "marginals"  << YAML::Value
                                                        << YAML::BeginSeq
                                                            << 111
                                                            << 222
                                                        << YAML::EndSeq

    <<  YAML::EndMap;



    config_file << out.c_str();
    config_file.close();
}

void qContainer::load_config(void)
{

}


using namespace std;

