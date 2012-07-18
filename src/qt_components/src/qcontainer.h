#ifndef QCONTAINER_H
#define QCONTAINER_H

#include <QScrollArea>


namespace YAML { class Emitter;  class Node;  };
class  QMarginal2;
class  QDepth;
class  QAlarmPrice;
class  QProd_info;
class  QTickerExecs;



class qContainer : public QScrollArea
{
    Q_OBJECT
public:
    explicit qContainer(QWidget *parent = 0);

    QMarginal2*     insert_qmarginal2       (void);
    QDepth*         insert_qdepth           (void);
    QAlarmPrice*    insert_qalarm_price     (void);
    QProd_info*     insert_qproduct_info    (void);
    QTickerExecs*   insert_qticker_execs    (void);


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
