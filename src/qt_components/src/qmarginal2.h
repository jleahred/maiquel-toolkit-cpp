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
class qmarginal_table_model;
class QCommonTableDelegate_view;

namespace YAML { class Emitter;  class Node;      };




class marginal_in_table2 : public mtk::SignalReceptor
{
    typedef  marginal_in_table2 CLASS_NAME;

public:
    marginal_in_table2(const mtk::msg::sub_product_code& product_code);
    const int id;

    mtk::CountPtr<mtk::prices::price_manager>                       price_manager;

    mtk::msg::sub_product_code                                      product_code;
    mtk::nullable<mtk::prices::msg::sub_best_prices>                best_prices;     //  for blinking  and update
    mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>       last_mk_execs_ticker;
    QString                                                         var;
    QString                                                         percent_var;
    mtk::DateTime                                                   last_updated;





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

    void update_vars(const mtk::prices::msg::sub_last_mk_execs_ticker&   _last_mk_execs_ticker);



    std::vector<mtk::DateTime>  v_blinking;
    mtk::DateTime               last_blinking;
    void add_blinking(int col, const mtk::DateTime&  till);


    static int counter;
};



class qmarginal_table_model  : public  QAbstractTableModel,   public  mtk::SignalReceptor
{
    Q_OBJECT
    typedef  qmarginal_table_model   CLASS_NAME;

public:
    qmarginal_table_model(QObject* parent=0);

    int             rowCount(const QModelIndex &parent) const;
    int             columnCount(const QModelIndex &parent) const;
    QVariant        data(const QModelIndex &index, int role) const;
    QVariant        headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags   flags(const QModelIndex &index) const;
    bool            insertRows(int row, int count, const QModelIndex &parent);
    bool            removeRows(int row, int count, const QModelIndex &parent);


    void            insert      (const mtk::msg::sub_product_code& product_code, int row);
    void            update      (int row, int first_col, int last_col);
    void            remove_row  (int id);


    int             row_count(void)  const  {  return marginals.size();  }

    mtk::CountPtr<marginal_in_table2>   get_marginal(int row)  {  return marginals[row];  }

    mutable mtk::Signal<int&>       signal_request_current_row;

private:
    mtk::DateTime   last_updated_table;

    mtk::vector< mtk::CountPtr<marginal_in_table2> >   marginals;

    void  slot_update_screen(void);

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



class QTableMarginal2 : public QTableView,   public  mtk::SignalReceptor
{
    Q_OBJECT
    typedef  QTableMarginal2 CLASS_NAME;
    friend YAML::Emitter&   operator << (YAML::Emitter&       out, const  QTableMarginal2& m);
    friend void             operator >> (const YAML::Node&   node,        QTableMarginal2& m);


public:
    explicit QTableMarginal2(QWidget *parent = 0);
    ~QTableMarginal2(){}


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
    void slot_sectionMoved ( int logicalIndex, int oldVisualIndex, int newVisualIndex );

private:
    QPoint startPos;
    int    startDragId;
    void start_drag(void);

    void insert_marginal(const mtk::msg::sub_product_code& product_code, int row);

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
    QAction* action_buy_stop_market;
    QAction* action_sell_stop_market;

    QCommonTableDelegate_view* paint_delegate;
    bool showing_menu;
    void disable_actions(void);
    void enable_actions(void);

    void disable_trading_actions(void);
    void enable_trading_actions(void);

    mtk::msg::sub_product_code get_current_product_code(void);

    qmarginal_table_model*      marginal_table_model;

    void  slot_requested_current_row(int& current_row)    {  if(this->hasFocus())   current_row = this->currentIndex().row();  }
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

private:
    QTableMarginal2 *table_marginals;

};





#endif // QMARGINAL2_H

