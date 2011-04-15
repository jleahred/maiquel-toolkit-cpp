#ifndef QORDER_TABLE_H
#define QORDER_TABLE_H

#include <QTableWidget>

#include "support/signalslot.hpp"
#include "components/trading/trd_cli_ls.h"
#include "components/trading/trd_cli_ord_book.h"
#include "qorderbook/filter_form.h"


class QTableWidget;
class QTableWidgetItem;
class order_in_qbook;
class filter_form;


class qorder_table : public QWidget , public mtk::SignalReceptor
{
    Q_OBJECT
    typedef  qorder_table CLASS_NAME;

public:
    explicit qorder_table(QWidget *parent = 0);
    ~qorder_table();

    void update_sizes();
    void show_filter(bool);
    bool is_filter_visible(void);


signals:
    void signal_named_changed(const QString& name);

private slots:
    void request_cancel(void);
    void request_modif (void);
    void slot_apply_filter(const filter_data& fd);

private:
    QTableWidget*        table_widget;
    void __direct_add_new_order(const mtk::trd::msg::sub_order_id& order_id, mtk::CountPtr<mtk::trd::trd_cli_ls>& order);
    void on_new_order(const mtk::trd::msg::sub_order_id& order_id, mtk::CountPtr<mtk::trd::trd_cli_ls>& order);

    mtk::map<mtk::trd::msg::sub_order_id, mtk::CountPtr<order_in_qbook> >* orders;
    mtk::list<mtk::trd::msg::sub_order_id>     orders2add_loading;
    mtk::list<mtk::trd::msg::sub_order_id>     orders2add_online;

    filter_data     current_filter;
    filter_form*    filterf;
    void            timer_get_orders2add(void);

    //QAction*  action_cancel;
    //QAction*  action_modif;
    void contextMenuEvent(QContextMenuEvent *);
};

#endif // QORDER_TABLE_H