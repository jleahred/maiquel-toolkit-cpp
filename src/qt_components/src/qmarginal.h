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
class QCommonTableDelegate;

namespace YAML { class Emitter;  class Node;      };




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


    bool        pending_screen_update;
    void        check_for_pending_screen_update(void);



    void clean_prices(void);
    void update_prices(const mtk::msg::sub_product_code& pc, const mtk::nullable<mtk::prices::msg::sub_best_prices>&   n_best_prices);
    void update_prices(const mtk::msg::sub_product_code& pc, const mtk::prices::msg::sub_best_prices&   best_prices);
    void on_message(const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_best_prices& msg);

    static int counter;
};




class QTableMarginal : public QTableWidget
{
    Q_OBJECT
    typedef  QTableMarginal CLASS_NAME;
    friend YAML::Emitter&   operator << (YAML::Emitter&       out, const  QTableMarginal& m);
    friend void             operator >> (const YAML::Node&   node,        QTableMarginal& m);


public:
    explicit QTableMarginal(QWidget *parent = 0);
    ~QTableMarginal(){}
    void make_transparent(void);
    void remove_transparency(void);


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

private slots:
    void request_buy (void);
    void request_sell(void);
    void request_hit_the_bid(void);
    void request_lift_the_offer(void);

    void request_side(mtk::trd::msg::enBuySell bs);
    void request_aggression(mtk::trd::msg::enBuySell bs);


    void request_buy_market(void);
    void request_sell_market(void);
    void request_side_market(mtk::trd::msg::enBuySell bs);

    void slot_remove_current_row(void);

private:
    QPoint startPos;
    int    startDragId;
    void start_drag(void);

    mtk::list< mtk::CountPtr<marginal_in_table> >   marginals;

    void insert_marginal(const mtk::msg::sub_product_code& product_code, int row);
    void add_marginal(const mtk::msg::sub_product_code& product_code);

    void remove_row(int id);
    void adjust_pajama(void);




    void focusInEvent (QFocusEvent *e) { this->update(); enable_actions();  QTableWidget::focusInEvent(e);}
    void focusOutEvent(QFocusEvent *e) { this->update(); disable_actions(); QTableWidget::focusOutEvent(e); }
    QAction* action_buy;
    QAction* action_sell;
    QAction* action_hit_the_bid;
    QAction* action_lift_the_offer;
    QAction* action_remove_product;
    QAction* action_buy_market;
    QAction* action_sell_market;

    QCommonTableDelegate* paint_delegate;
    bool showing_menu;
    void disable_actions(void);
    void enable_actions(void);

    void disable_trading_actions(void);
    void enable_trading_actions(void);

    mtk::msg::sub_product_code get_current_product_code(void);
};






class QMarginal : public mtkContainerWidget
{
    Q_OBJECT
    typedef  QMarginal CLASS_NAME;
    friend YAML::Emitter&   operator << (YAML::Emitter&       out, const QMarginal& m);
    friend void             operator >> (const YAML::Node&   node,       QMarginal& m);

public:
    explicit QMarginal(QWidget *parent = 0);
    ~QMarginal();



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

