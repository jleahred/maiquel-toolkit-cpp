#ifndef QEXEC_TABLE_ACC_H
#define QEXEC_TABLE_ACC_H

#include <QTableWidget>


#include "support/signalslot.hpp"
#include "components/trading/trd_cli_ls.h"
#include "components/trading/trd_cli_ord_book.h"

#include "qorderbook/filter_form.h"
#include <Phonon/MediaObject>


class QTableWidget;
class QTableWidgetItem;
class Exec_in_table_acc;


namespace mtk { namespace trd { namespace hist { class  order_exec_item_acc_by_price; }}};



////////////////////////////////////////////////////////////////////////////////
//      QExecsTable

class QExecsTable_acc : public QWidget , public mtk::SignalReceptor
{
    Q_OBJECT
    typedef  QExecsTable_acc CLASS_NAME;

public:
    explicit QExecsTable_acc(QWidget *parent = 0);
    ~QExecsTable_acc() {  delete  exec_in_table; }

    void   set_executions(mtk::CountPtr<mtk::trd::hist::order_EXECS_historic>  execs_history);
    void   update_sizes();


signals:

private slots:


protected:
    QTableWidget*        table_widget;
    void __direct_add_new_execution(const mtk::tuple<int, mtk::trd::hist::order_exec_item_acc_by_price>& exec);

    mtk::vector<Exec_in_table_acc*>*                                            exec_in_table;
    mtk::list<mtk::tuple<int, mtk::trd::hist::order_exec_item_acc_by_price> >   execs2add_online;

    void            timer_get_execs2add(void);

    mtk::CountPtr<mtk::trd::hist::order_EXECS_historic>   execs_history;
    void on_new_item  (const mtk::trd::hist::order_exec_item_acc_by_price&  exec_item);
    void on_modif_item(int pos, const mtk::trd::hist::order_exec_item_acc_by_price&  exec_item);
};






#endif // QEXEC_TABLE_ACC_H
