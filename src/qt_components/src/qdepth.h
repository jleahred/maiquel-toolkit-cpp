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
class depth_in_table;







class QDepth : public mtkContainerWidget, public mtk::SignalReceptor
{
    Q_OBJECT
    typedef  QDepth CLASS_NAME;
    friend class QTableDeph;

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
    void focusInEvent (QFocusEvent *e) { raise(); this->update(); enable_actions();   mtkContainerWidget::focusInEvent(e);}
    void focusOutEvent(QFocusEvent *e) { raise(); this->update(); disable_actions();  mtkContainerWidget::focusOutEvent(e);}



private slots:
    void request_buy (void);
    void request_sell(void);

    void request_hit_the_bid(void);
    void request_lift_the_offer(void);

    void request_side(mtk::trd::msg::enBuySell bs);
    void request_aggression(mtk::trd::msg::enBuySell bs);


    void make_transparent(void);
    void remove_transparecy(void);

private:
    QTableDeph   *table_widget;
    QLabel       *title;

    mtk::CountPtr<mtk::prices::price_manager>       price_manager;
    void on_message(const mtk::prices::msg::pub_best_prices& msg);

    QPoint startPos;

    QAction* action_buy;
    QAction* action_sell;
    QAction* action_hit_the_bid;
    QAction* action_lift_the_offer;

    bool showing_menu;
    void disable_actions(void);
    void enable_actions(void);
};

#endif // QDEPTH_H
