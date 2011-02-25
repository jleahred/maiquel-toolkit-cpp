#ifndef QORDERBOOK_H
#define QORDERBOOK_H

#include <QWidget>

#include "support/signalslot.hpp"
#include "components/trading/trd_cli_ls.h"
#include "components/trading/trd_cli_ord_book.h"




class QTableWidget;
class QTableWidgetItem;
class order_in_qbook;

class QOrderBook : public QWidget, public mtk::SignalReceptor
{
    Q_OBJECT
    typedef  QOrderBook CLASS_NAME;

public:
    explicit QOrderBook(QWidget *parent = 0);
    ~QOrderBook();

    void update_sizes(void);

signals:

public slots:


private slots:
    void request_cancel(void);
    void request_modif (void);

private:
    QTableWidget *table_widget;

    void on_new_order(const mtk::trd::msg::sub_order_id& order_id, mtk::CountPtr<mtk::trd::trd_cli_ls>& order);

    mtk::map<mtk::trd::msg::sub_order_id, mtk::CountPtr<order_in_qbook> >* orders;

};

#endif // QORDERBOOK_H
