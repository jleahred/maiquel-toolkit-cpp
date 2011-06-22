#ifndef QORDER_TABLE_H
#define QORDER_TABLE_H

#include <QTableWidget>

#include "support/signalslot.hpp"
#include "components/trading/trd_cli_ls.h"
#include "components/trading/trd_cli_mk.h"
#include "components/trading/trd_cli_ord_book.h"
#include "qorderbook/filter_form.h"


class QTableWidget;
class QTableWidgetItem;
class order_in_qbook;
class filter_form;
class QCommonTableDelegate;
namespace YAML { class Emitter;  class Node;  };



class qorder_table : public QWidget , public mtk::SignalReceptor
{
    Q_OBJECT
    typedef  qorder_table CLASS_NAME;
    friend YAML::Emitter& operator<< (YAML::Emitter    & out , const qorder_table& m);
    friend void           operator>> (const YAML::Node & i   ,       qorder_table& m);

public:
    explicit qorder_table(QWidget *parent = 0);
    ~qorder_table();

    void update_sizes();
    void show_filter(bool);
    bool is_filter_visible(void);
    mtk::nullable<mtk::trd::msg::sub_order_id>       get_current_order_id(void);


signals:
    void signal_named_changed(const QString& name);
    void signal_filter_changed(void);
    void signal_double_click(QModelIndex);
    void signal_cell_changed(int, int, int, int);
    void signal_request_show_historic(void);
    void signal_request_hide_historic(void);

private slots:
    void request_cancel(void);
    void request_modif (void);
    void slot_apply_filter(const filter_data& fd);
    void slot_live_orders(void);
    void slot_live_and_exec_orders(void);
    void slot_all_orders(void);
    void slot_on_double_clicked(QModelIndex);
    void slot_current_cell_changed(int, int, int, int);


private:
    QTableWidget*        table_widget;
    void __direct_add_new_order(const mtk::trd::msg::sub_order_id& order_id, mtk::CountPtr<order_in_qbook>& order);
    void on_new_order(const mtk::trd::msg::sub_order_id& order_id, mtk::CountPtr<mtk::trd::trd_cli_ls>& order);
    void on_new_order(const mtk::trd::msg::sub_order_id& order_id, mtk::CountPtr<mtk::trd::trd_cli_mk>& order);

    mtk::map<mtk::trd::msg::sub_order_id, mtk::CountPtr<order_in_qbook> >* orders;
    mtk::list<mtk::trd::msg::sub_order_id>     orders2add_loading;
    mtk::list<mtk::trd::msg::sub_order_id>     orders2add_online;
    mtk::trd::msg::sub_order_id   current_order_id;
    void  try_realocate_order(const mtk::trd::msg::sub_order_id&);

    filter_data     current_filter;
    filter_form*    filterf;
    void            timer_get_orders2add(void);

    //QAction*  action_cancel;
    //QAction*  action_modif;
    void contextMenuEvent(QContextMenuEvent *);

    void keyPressEvent(QKeyEvent *);
    bool eventFilter(QObject *, QEvent *);

    QCommonTableDelegate* delegate_paint;
};

#endif // QORDER_TABLE_H
