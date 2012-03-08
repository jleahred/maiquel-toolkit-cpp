#ifndef QCONTAINER_H
#define QCONTAINER_H

#include <QScrollArea>


namespace YAML { class Emitter;  class Node;  };
class  QMarginal;
class  QMarginal2;
class  QDepth;
class  QAlarmPrice;



class qContainer : public QScrollArea
{
    Q_OBJECT
public:
    explicit qContainer(QWidget *parent = 0);

    QMarginal*      insert_qmarginal        (void);
    QMarginal2*     insert_qmarginal2       (void);
    QDepth*         insert_qdepth           (void);
    QAlarmPrice*    insert_qalarm_price     (void);


    friend YAML::Emitter& operator << (YAML::Emitter   & out , const qContainer& m);
    friend void           operator>> (const YAML::Node & i   ,       qContainer& m);


protected:
    void    resizeEvent ( QResizeEvent * ); //  virtual inherited

private:
    int   counter_insertions;

signals:

public slots:


private slots:
    void slot_widget_moved_or_deleted(void);

};

#endif // QCONTAINER_H
