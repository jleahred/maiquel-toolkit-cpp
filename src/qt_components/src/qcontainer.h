#ifndef QCONTAINER_H
#define QCONTAINER_H

#include <QScrollArea>

class qContainer : public QScrollArea
{
    Q_OBJECT
public:
    explicit qContainer(QWidget *parent = 0);

    void insert_qmarginal(void);
    void insert_qdepth(void);

private:
    QPoint  last_inserted_pos;

signals:

public slots:

};

#endif // QCONTAINER_H
