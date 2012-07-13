#ifndef QEXEC_TABLE_H
#define QEXEC_TABLE_H

#include <QTableWidget>


#include "support/signalslot.hpp"
#include "components/trading/trd_cli_ls.h"
#include "components/trading/trd_cli_ord_book.h"

#include "qorderbook/filter_form.h"
#include <Phonon/MediaObject>


class QTableWidget;
class QTableWidgetItem;
class Exec_in_table;


namespace mtk { namespace trd { namespace hist { class  order_exec_item; }}};



////////////////////////////////////////////////////////////////////////////////
//      QExecsTable

class QExecsTable : public QWidget , public mtk::SignalReceptor
{
    Q_OBJECT

public:
    explicit QExecsTable(QWidget *parent = 0);
    ~QExecsTable() {  delete  exec_in_table; }

    void update_sizes();


signals:

private slots:


protected:
    QTableWidget*        table_widget;
    void __direct_add_new_execution(const mtk::trd::hist::order_exec_item& exec);
    void on_new_execution(const mtk::trd::msg::CF_XX&  order_info, const mtk::trd::msg::sub_exec_conf& exec);

    mtk::list<Exec_in_table*>*                             exec_in_table;
    mtk::list<mtk::trd::hist::order_exec_item>             execs2add_loading;
    mtk::list<mtk::trd::hist::order_exec_item>             execs2add_online;

    void            timer_get_execs2add(void);
};




////////////////////////////////////////////////////////////////////////////////
//      QExecsTable_ALL_execs

class QExecsTable_ALL_execs : public QExecsTable //, public mtk::SignalReceptor     father has it
{
    Q_OBJECT

public:
    explicit QExecsTable_ALL_execs(QWidget *parent = 0);


signals:

private slots:
    void  slot_clean_execs(void);
    void  slot_show_all_execs(void);
    void  slot_copy_all_execs(void);
    void  slot_copy_execs_group_by_ordprice(void);
    void  slot_show_execs_report(void);


private:

    void on_new_execution(const mtk::trd::msg::CF_XX&  order_info, const mtk::trd::msg::sub_exec_conf& exec);

    Phonon::MediaObject *mediaObject;

    void contextMenuEvent(QContextMenuEvent *);
};




////////////////////////////////////////////////////////////////////////////////
//      QExecsTable_one_order
/*
class QExecsTable_one_order : public QExecsTable //, public mtk::SignalReceptor     father has it
{
    Q_OBJECT

public:
    explicit QExecsTable_one_order(QWidget *parent = 0);

    void   set_executions(mtk::CountPtr<mtk::trd::hist::order_EXECS_historic>  execs_history);


signals:

private slots:

private:

    mtk::CountPtr<mtk::trd::hist::order_EXECS_historic>   execs_history;
    void on_new_item(const mtk::trd::hist::order_exec_item&  exec_item);

};
*/





#endif // QEXEC_TABLE_H
