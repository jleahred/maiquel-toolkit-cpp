#ifndef QDEPTH_H
#define QDEPTH_H

#include "qt_components/src/mtkcontainerwidget.h"

#include "support/signalslot.hpp"

#include "mtk_qpid/mtk_qpid.hpp"
#include "components/prices/msg_prices.h"
#include "components/prices/cli/price_manager.h"



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
    void focusInEvent (QFocusEvent *) { raise(); this->update(); }
    void focusOutEvent(QFocusEvent *) { raise(); this->update(); }



private slots:
    void request_buy (void);
    void request_sell(void);

    void make_transparent(void);
    void remove_transparecy(void);

private:
    QTableDeph   *table_widget;
    QLabel       *title;

    mtk::CountPtr<mtk::prices::price_manager>       price_manager;
    void on_message(const mtk::prices::msg::pub_best_prices& msg);

    QPoint startPos;

};

#endif // QDEPTH_H
