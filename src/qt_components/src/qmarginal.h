#ifndef QMARGINAL_H
#define QMARGINAL_H


#include <QTableWidget>


#include "qt_components/src/mtkcontainerwidget.h"

#include "support/signalslot.hpp"

#include "mtk_qpid/mtk_qpid.hpp"
#include "components/prices/msg_prices.h"

#include "support/list.hpp"
#include "components/prices/cli/price_manager.h"

#include "components/trading/msg_trd_common_support.h"



class QTableWidget;
class QTableWidgetItem;



class marginal_in_table : public mtk::SignalReceptor
{
    typedef  marginal_in_table CLASS_NAME;

public:
    marginal_in_table(QTableWidget* _table_widget, const mtk::msg::sub_product_code& product_code, int row=-1);
    const int id;
    void set_normal_color(int transparency=255);
    void set_dark_color(void);
    int  get_row(void) const {  return tw_product->row(); }

    mtk::CountPtr<mtk::prices::price_manager>       price_manager;

private:

    QTableWidgetItem*  tw_product;
    QTableWidgetItem*  tw_BID;
    QTableWidgetItem*  tw_ASK;
    QTableWidgetItem*  tw_qty_bid;
    QTableWidgetItem*  tw_qty_ask;

    QTableWidget* table_widget;

    void on_message(const mtk::prices::msg::pub_best_prices& msg);

    static int counter;
};




class QTableMarginal : public QTableWidget
{
    Q_OBJECT
    typedef  QTableMarginal CLASS_NAME;

public:
    explicit QTableMarginal(QWidget *parent = 0);
    ~QTableMarginal(){}
    void make_transparent(void);
    void remove_transparency(void);
    std::string  get_config(void);


protected:
    //drag
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    //drop
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *);
    void contextMenuEvent ( QContextMenuEvent * event );
    //void resizeEvent(QResizeEvent *event);

private slots:
    void request_buy (void);
    void request_sell(void);
    void request_hit_the_bid(void);
    void request_lift_the_offer(void);

    void request_side(mtk::trd::msg::enBuySell bs);
    void request_aggression(mtk::trd::msg::enBuySell bs);

    void slot_column_resized(int, int, int);

private:
    QPoint startPos;
    int    startDragId;
    void start_drag(void);

    mtk::list< mtk::CountPtr<marginal_in_table> >   marginals;

    void insert_marginal(const mtk::msg::sub_product_code& product_code, int row);
    void add_marginal(const mtk::msg::sub_product_code& product_code);

    void remove_row(int id);
    void adjust_pajama(void);



    QAction* action_buy;
    QAction* action_sell;
    QAction* action_hit_the_bid;
    QAction* action_lift_the_offer;
};






class QMarginal : public mtkContainerWidget
{
    Q_OBJECT
    typedef  QMarginal CLASS_NAME;

public:
    explicit QMarginal(QWidget *parent = 0);
    ~QMarginal();

    std::string  get_config(void);

signals:

public slots:


protected:


private slots:
    void make_transparent(void) { table_marginals->make_transparent();  }
    void remove_transparent(void) { table_marginals->remove_transparency();  }

private:
    QTableMarginal *table_marginals;

};

#endif // QMARGINAL_H

