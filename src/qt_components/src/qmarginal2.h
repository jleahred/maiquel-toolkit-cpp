#ifndef QMARGINAL2_H
#define QMARGINAL2_H


#include <QTableView>
#include <QHeaderView>

#include "qt_components/src/mtkcontainerwidget.h"

#include "support/signalslot.hpp"

#include "mtk_qpid/mtk_qpid.hpp"
#include "components/prices/msg_prices.h"

#include "support/list.hpp"
#include "components/prices/cli/price_manager.h"

#include "components/trading/msg_trd_common_support.h"






class QTableWidget;
//class QTableWidgetItem;
//class QCommonTableDelegate;

namespace YAML { class Emitter;  class Node;      };




class marginal_in_table2 : public mtk::SignalReceptor
{
    typedef  marginal_in_table2 CLASS_NAME;

public:
    marginal_in_table2(QTableView* _table_widget, const mtk::msg::sub_product_code& product_code, int row=-1);
    const int id;
    void set_normal_color(int transparency=255);
    void set_dark_color(void);
    //int  get_row(void) const {  return tw_product->row(); }

    mtk::CountPtr<mtk::prices::price_manager>       price_manager;

private:

    /*
    QTableWidgetItem*  tw_product;
    QTableWidgetItem*  tw_BID;
    QTableWidgetItem*  tw_ASK;
    QTableWidgetItem*  tw_qty_bid;
    QTableWidgetItem*  tw_qty_ask;

    QTableWidgetItem*  tw_last_price;
    QTableWidgetItem*  tw_last_quantity;
    QTableWidgetItem*  tw_ref_price;
    QTableWidgetItem*  tw_var;
    QTableWidgetItem*  tw_var_percent;
    */
    QTableView* table_view;


    bool        pending_screen_update;
    void        check_for_pending_screen_update(void);



    void clean_prices(void);
    void update_prices(const mtk::nullable<mtk::prices::msg::sub_best_prices>&   n_best_prices);
    void update_prices(const mtk::prices::msg::sub_best_prices&   best_prices);
    void on_best_prices(const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_best_prices& msg);

    void clean_lasts(void);
    void update_last_mk_execs_ticker(const mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>&);
    void update_last_mk_execs_ticker(const mtk::prices::msg::sub_last_mk_execs_ticker&);
    void on_last_mk_execs_ticker_msg(const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_last_mk_execs_ticker& msg);


    mtk::prices::msg::sub_best_prices           prev_painted_prices;     //  for blinking  and update
    mtk::prices::msg::sub_last_mk_execs_ticker  prev_painted_last;

    std::vector<mtk::DateTime>  v_blinking;
    mtk::DateTime               last_blinking;
    void generate_blinking(const mtk::prices::msg::sub_best_prices&  prices);
    void check_blinking(void);
    void add_blinking(int col, const mtk::DateTime&  till);


    static int counter;
};



class  QHeaderView_hidding_cols2   :   public  QHeaderView
{
    Q_OBJECT


public:
    QHeaderView_hidding_cols2 ( const QList<QString>& _names,  Qt::Orientation orientation, QWidget * parent = 0 )
        :  QHeaderView (orientation, parent), names(_names)
    {
    }

    void mousePressEvent(QMouseEvent *e);


public slots:
    void  hide_show_col(int logicalIndex);

private:
    const QList<QString>  names;
};



class QTableMarginal2 : public QTableView
{
    Q_OBJECT
    typedef  QTableMarginal2 CLASS_NAME;
    friend YAML::Emitter&   operator << (YAML::Emitter&       out, const  QTableMarginal2& m);
    friend void             operator >> (const YAML::Node&   node,        QTableMarginal2& m);


public:
    explicit QTableMarginal2(QWidget *parent = 0);
    ~QTableMarginal2(){}
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
    void keyPressEvent ( QKeyEvent * event );

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
    void slot_sectionMoved ( int logicalIndex, int oldVisualIndex, int newVisualIndex );

private:
    QPoint startPos;
    int    startDragId;
    void start_drag(void);

    mtk::list< mtk::CountPtr<marginal_in_table2> >   marginals;

    void insert_marginal(const mtk::msg::sub_product_code& product_code, int row);
    void add_marginal(const mtk::msg::sub_product_code& product_code);

    void remove_row(int id);


    void focusInEvent (QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);
    QAction* action_buy;
    QAction* action_sell;
    QAction* action_hit_the_bid;
    QAction* action_lift_the_offer;
    QAction* action_remove_product;
    QAction* action_buy_market;
    QAction* action_sell_market;

    //QCommonTableDelegate* paint_delegate;
    bool showing_menu;
    void disable_actions(void);
    void enable_actions(void);

    void disable_trading_actions(void);
    void enable_trading_actions(void);

    mtk::msg::sub_product_code get_current_product_code(void);

};






class QMarginal2 : public mtkContainerWidget
{
    Q_OBJECT
    typedef  QMarginal2 CLASS_NAME;
    friend YAML::Emitter&   operator << (YAML::Emitter&       out, const QMarginal2& m);
    friend void             operator >> (const YAML::Node&   node,       QMarginal2& m);

public:
    explicit QMarginal2(QWidget *parent = 0);
    ~QMarginal2();



signals:

public slots:


protected:


private slots:
    void make_transparent(void) { table_marginals->make_transparent();  }
    void remove_transparent(void) { table_marginals->remove_transparency();  }

private:
    QTableMarginal2 *table_marginals;

};





#endif // QMARGINAL2_H

