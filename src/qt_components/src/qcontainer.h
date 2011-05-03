#ifndef QCONTAINER_H
#define QCONTAINER_H

#include <QScrollArea>


namespace YAML { class Emitter;  class Node;  };
class  QMarginal;
class  QDepth;



class qContainer : public QScrollArea
{
    Q_OBJECT
public:
    explicit qContainer(QWidget *parent = 0);

    QMarginal*  insert_qmarginal(void);
    QDepth*     insert_qdepth   (void);


    friend YAML::Emitter& operator << (YAML::Emitter   & out , const qContainer& m);
    friend void           operator>> (const YAML::Node & i   ,       qContainer& m);

private:
    QPoint  last_inserted_pos;

signals:

public slots:

};

#endif // QCONTAINER_H
