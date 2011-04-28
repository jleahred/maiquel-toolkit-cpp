#include "qcontainer.h"


#include <iostream>
#include <fstream>


#include <QMouseEvent>
#include <QVBoxLayout>
#include <QMessageBox>


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


    try
    {
        YAML::Emitter out;
        out
        <<  YAML::BeginMap
                    <<  YAML::Key << "version"   <<  YAML::Value << 1;


                    out << YAML::Key  << "marginals"  << YAML::Value
                                                            << YAML::BeginSeq;
            int located_marginals=0;
            for(int i=0; i<this->widget()->children().count(); ++i)
            {
                QMarginal* marginal = dynamic_cast<QMarginal*>(this->widget()->children().at(i));
                if(marginal!=0)
                {
                    out << *marginal;
                    ++located_marginals;
                }
            }
            if(located_marginals==0)        out << YAML::Null;
                                                    out    << YAML::EndSeq;

                    out << YAML::Key  << "depths"  << YAML::Value
                                                            << YAML::Flow
                                                            << YAML::BeginSeq
                                                            << YAML::EndSeq
        <<  YAML::EndMap;

        config_file << out.c_str();
        config_file.close();
    }
    catch(...)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "save_config", "error saving config", mtk::alPriorError));
        QMessageBox(QMessageBox::Critical, tr("Error"), tr("Error saving configuration")).exec();
    }
}

void qContainer::load_config(void)
{

}


using namespace std;

