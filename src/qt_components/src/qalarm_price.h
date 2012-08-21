#ifndef QALARM_PRICE_H
#define QALARM_PRICE_H


#include <QTableWidget>
#include <QItemDelegate>


#include "qt_components/src/mtkcontainerwidget.h"

#include "support/signalslot.hpp"

#include "mtk_qpid/mtk_qpid.h"
#include "components/prices/msg_prices.h"

#include "support/list.hpp"
#include "components/prices/cli/price_manager.h"

#include "components/trading/msg_trd_common_support.h"





class QTableWidget;
class QTableWidgetItem;
class QCommonTableDelegate;
class qLocaleDoubleSpinBox;

namespace YAML { class Emitter;  class Node;      };



class qLocaleDoubleSpinBox_delegate : public QItemDelegate
{
    Q_OBJECT

public:
    qLocaleDoubleSpinBox_delegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    void set_decinc(int _decimals, int _increment) {  decimals = _decimals, increment = _increment;  }

private:
    int decimals;
    int increment;
};




class marginal_in_table_alarm : public  QObject, public mtk::SignalReceptor
{
    Q_OBJECT
public:
    enum            en_status  {  non_initialized,  ready_to_activate,  activated,  ended  };
    en_status       status;



    marginal_in_table_alarm(QTableWidget* _table_widget, const mtk::msg::sub_product_code& product_code, double price, const QString& description, int row=-1);
    const int id;
    int  get_row(void) const {  return tw_product->row(); }

    mtk::CountPtr<mtk::prices::price_manager>       price_manager;


    void  set_status(en_status  _status);



public slots:
    void slot_cell_changed (int row, int column);
    void slot_item_selection_changed (void);


signals:
    void  signal_modif_decimals_increment_for_price_editor(int decimals, int increment);


private:

    QTableWidgetItem*  tw_product;
    QTableWidgetItem*  tw_last_configured;
    QTableWidgetItem*  tw_description;

    QTableWidget* table_widget;



    void on_last_mk_execs_ticker_msg(const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_last_mk_execs_ticker& msg);

    static int  alarm_counter;

    mtk::Double           configured_price;
    bool                  first_maket__bigger__configured_last;

    bool                  alarm_is_checked;

    void normalize_last_price_cofigured(double price);

    void  initialize_paint(void);


    void  set_non_initialized(void);
    void  set_ready_to_activate(void);
    void  set_activated(void);
    void  set_ended (void);

    //void  mark_is_close (bool close=true);
};




class QTableAlarmPrice : public QTableWidget
{
    Q_OBJECT
    friend YAML::Emitter&   operator << (YAML::Emitter&       out, const  QTableAlarmPrice& m);
    friend void             operator >> (const YAML::Node&   node,        QTableAlarmPrice& m);


public:
    explicit QTableAlarmPrice(QWidget *parent = 0);
    ~QTableAlarmPrice(){}


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
    void slot_remove_current_row(void);
    void slot_sectionMoved ( int logicalIndex, int oldVisualIndex, int newVisualIndex );
    void slot_modif_price_editor(int decimals, int increment);


private:
    QPoint startPos;
    int    startDragId;
    void start_drag(void);

    mtk::list< mtk::CountPtr<marginal_in_table_alarm> >   alarms;

    void insert_alarm(const mtk::msg::sub_product_code& product_code, double price, const QString& description, int row);
    void add_alarm(const mtk::msg::sub_product_code& product_code, double price, const QString& description);

    void remove_row(int id);


    void focusInEvent (QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);

    QAction* action_remove_product;

    bool showing_menu;
    void disable_actions(void);
    void enable_actions(void);


    mtk::msg::sub_product_code get_current_product_code(void);

public:
    QCommonTableDelegate* paint_delegate;
private:
    qLocaleDoubleSpinBox_delegate*  price_editor;

};






class QAlarmPrice : public mtkContainerWidget
{
    Q_OBJECT
    friend YAML::Emitter&   operator << (YAML::Emitter&       out, const QAlarmPrice& m);
    friend void             operator >> (const YAML::Node&   node,       QAlarmPrice& m);

public:
    explicit QAlarmPrice(QWidget *parent = 0);
    ~QAlarmPrice();



signals:

public slots:


protected:
    virtual QSize  sizeHint(void) const;


private slots:

private:
    QTableAlarmPrice *table_alarms;

};





#endif // QALARM_PRICE_H

