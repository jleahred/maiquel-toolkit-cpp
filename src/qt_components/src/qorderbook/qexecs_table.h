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



class QExecsTable : public QWidget , public mtk::SignalReceptor
{
    Q_OBJECT
    typedef  QExecsTable CLASS_NAME;

public:
    explicit QExecsTable(QWidget *parent = 0);
    ~QExecsTable() {  delete  exec_in_table; };

    void update_sizes();


signals:

private slots:
    void  slot_clean_execs(void);
    void  slot_show_all_execs(void);


private:
    QTableWidget*        table_widget;
    void __direct_add_new_execution(const mtk::msg::sub_product_code& pc, const mtk::trd::msg::sub_position_ls& exec);
    void on_new_execution(const mtk::msg::sub_product_code& pc, const mtk::trd::msg::sub_position_ls& exec);

    mtk::list<Exec_in_table*>*                                                          exec_in_table;
    mtk::list<mtk::tuple<mtk::msg::sub_product_code, mtk::trd::msg::sub_position_ls> >  execs2add_loading;
    mtk::list<mtk::tuple<mtk::msg::sub_product_code, mtk::trd::msg::sub_position_ls> >  execs2add_online;
    mtk::list<mtk::tuple<mtk::msg::sub_product_code, mtk::trd::msg::sub_position_ls> >  execs_all;

    void            timer_get_execs2add(void);

    Phonon::MediaObject *mediaObject;

    void contextMenuEvent(QContextMenuEvent *);
};

#endif // QORDER_TABLE_H
