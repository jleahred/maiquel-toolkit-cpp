#ifndef QDEPTH_H
#define QDEPTH_H

#include "qt_components/src/mtkcontainerwidget.h"

#include "support/signalslot.hpp"

#include "mtk_qpid/mtk_qpid.hpp"
#include "components/prices/msg_prices.h"
#include "components/prices/cli/price_manager.h"
#include "components/trading/msg_trd_common_support.h"



class QTableDeph;
class QLabel;
namespace YAML { class Emitter;  class Node;      };







class QDepth : public mtkContainerWidget, public mtk::SignalReceptor
{
    Q_OBJECT
    typedef  QDepth CLASS_NAME;
    friend class QTableDeph;
    friend YAML::Emitter&   operator << (YAML::Emitter&       out, const QDepth& m);
    friend void             operator >> (const YAML::Node&   node,       QDepth& d);

public:
    explicit QDepth(QWidget *parent = 0);
    ~QDepth();

    void subscribe_to (const mtk::msg::sub_product_code&  _product_code);


signals:

public slots:


protected:
    void resizeEvent ( QResizeEvent * event );

    //  drop
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);

    //  drag
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void contextMenuEvent ( QContextMenuEvent * event );
    //void paintEvent(QPaintEvent *);
    void focusInEvent (QFocusEvent *e) { paint_focus();  raise(); this->update(); enable_actions();   mtkContainerWidget::focusInEvent(e);}
    void focusOutEvent(QFocusEvent *e) { remove_focus(); raise(); this->update(); disable_actions();  mtkContainerWidget::focusOutEvent(e);}



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


    void make_transparent(void);
    void remove_transparecy(void);

private:
    QTableDeph   *table_widget;
    QLabel       *title;

    QString       style_sheet_normal;
    QString       style_sheet_null;
    QString       style_sheet_focus;

    bool          pending_screen_update;
    mtk::CountPtr<mtk::prices::price_manager>       price_manager;
    void on_message(const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_best_prices& msg);
    void check_for_pending_screen_update(void);


    void update_prices(const mtk::prices::msg::sub_best_prices&   best_prices);
    void update_prices(const mtk::nullable<mtk::prices::msg::sub_best_prices>&   n_best_prices);
    void upate_null_prices(void);

    QPoint startPos;

    QAction* action_buy;
    QAction* action_sell;
    QAction* action_hit_the_bid;
    QAction* action_lift_the_offer;
    QAction* action_buy_market;
    QAction* action_sell_market;

    bool showing_menu;
    void disable_actions(void);
    void enable_actions(void);
    void disable_trading_actions(void);
    void enable_trading_actions(void);

    bool keep_paint_focus;
    void paint_focus(void);
    void remove_focus(void);
};


YAML::Emitter& operator << (YAML::Emitter& out, const QDepth& m);


#endif // QDEPTH_H
