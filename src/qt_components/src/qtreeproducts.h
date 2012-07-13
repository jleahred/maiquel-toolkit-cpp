#ifndef QTREEPRODUCTS_H
#define QTREEPRODUCTS_H

#include <QTreeWidget>

#include "support/signalslot.hpp"
#include "mtk_qpid/mtk_qpid.h"
#include "components/gen/msg_tree_server.h"



class qTreeProducts : public QTreeWidget, public mtk::SignalReceptor
{
    Q_OBJECT

public:
    explicit qTreeProducts(QWidget *parent = 0);

    void request_root_items(void);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void on_response_request_tree(const mtk::list<mtk::gen::msg::res_tree_items>& list_items);
    void on_colapse_branch_received(const mtk::gen::msg::pub_tree_colapse_branch&  msg);


    QPoint startPos;
    void start_drag(void);
    void show_tree(void);


    QTreeWidgetItem*  get_item_from_branck(QString current_branck, QStringList& pending_branch, QTreeWidgetItem* current_tree_item);

signals:

public slots:
    void on_itemDoubleClicked ( QTreeWidgetItem * item, int column );

};

#endif // QTREEPRODUCTS_H
