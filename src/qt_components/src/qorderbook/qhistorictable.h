#ifndef QHISTORIC_TABLE_H
#define QHISTORIC_TABLE_H

#include <QTableWidget>


#include "support/signalslot.hpp"
#include "components/trading/trd_cli_historic.h"


class QTableWidget;
class QTableWidgetItem;
class Exec_in_table;



class QHistoricTable : public   QTableWidget , public mtk::SignalReceptor
{
    Q_OBJECT
    typedef  QHistoricTable   CLASS_NAME;

public:
    explicit QHistoricTable(QWidget *parent = 0);
    ~QHistoricTable() {}

    void update_sizes();

    void set_historic(mtk::CountPtr<mtk::trd::hist::order_historic2>  order_historic);


signals:

private slots:
    void  slot_doubleClicked_header(int);

private:
    mtk::CountPtr<mtk::trd::hist::order_historic2>   order_historic;
    void        new_item_added(const mtk::trd::hist::order_historic_item&);
    void        modified_item(int pos, const  mtk::trd::hist::order_historic_item&  item);

    void        add_item(const  mtk::trd::hist::order_historic_item&  item);
    void        update_item  (int row, const  mtk::trd::hist::order_historic_item&  item);
};

#endif // QHISTORIC_TABLE_H
