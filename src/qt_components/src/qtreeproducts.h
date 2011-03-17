#ifndef QTREEPRODUCTS_H
#define QTREEPRODUCTS_H

#include <QTreeWidget>

#include "support/signalslot.hpp"
#include "mtk_qpid/mtk_qpid.hpp"
#include "components/gen/msg_tree_server.h"



class qTreeProducts : public QTreeWidget, public mtk::SignalReceptor
{
    Q_OBJECT
    typedef qTreeProducts CLASS_NAME;

public:
    explicit qTreeProducts(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    mtk::CountPtr< mtk::qpid_session >       qpid_session;

    void on_response_request_tree(const mtk::list<mtk::gen::msg::res_tree_items>& list_items);


    QPoint startPos;
    void start_drag(void);
    void show_tree(void);

    void request_root_items(void);

    QTreeWidgetItem*  get_item_from_branck(QString current_branck, QStringList& pending_branch, QTreeWidgetItem* current_tree_item);

signals:

public slots:
    void on_itemDoubleClicked ( QTreeWidgetItem * item, int column );

};

#endif // QTREEPRODUCTS_H
