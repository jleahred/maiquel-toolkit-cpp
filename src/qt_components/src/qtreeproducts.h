#ifndef QTREEPRODUCTS_H
#define QTREEPRODUCTS_H

#include <QTreeWidget>

#include "support/signalslot.hpp"

class qTreeProducts : public QTreeWidget, public mtk::SignalReceptor
{
    Q_OBJECT
    typedef qTreeProducts CLASS_NAME;

public:
    explicit qTreeProducts(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPoint startPos;
    void start_drag(void);
    void show_tree(void);


signals:

public slots:

};

#endif // QTREEPRODUCTS_H
