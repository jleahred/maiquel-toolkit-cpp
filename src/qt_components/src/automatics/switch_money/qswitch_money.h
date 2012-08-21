#ifndef QSWITCH_MONEY_COMPONENT__
#define QSWITCH_MONEY_COMPONENT__

#include "qt_components/src/mtkcontainerwidget.h"

#include "support/signalslot.hpp"

#include "mtk_qpid/mtk_qpid.h"
#include "components/prices/msg_prices.h"
#include "components/prices/cli/price_manager.h"
#include "swm_calculator.h"

#include <QTextCharFormat>
#include <qsyntaxhighlighter.h>


class  QLabel;
class  QPlainTextEdit;
class  swm_config;


namespace YAML { class Emitter;  class Node;      };


class  ui_switch_money;



class QSwicthMoney : public mtkContainerWidget, public mtk::SignalReceptor
{
    Q_OBJECT
    friend YAML::Emitter&   operator << (YAML::Emitter&       out, const QSwicthMoney& m);
    friend void             operator >> (const YAML::Node&   node,       QSwicthMoney& d);

public:
    explicit QSwicthMoney(QWidget *parent = 0);
    ~QSwicthMoney();



    //**********************************************************************
    //----------------------------------------------------------------------
    //......................................................................






    //......................................................................
    //----------------------------------------------------------------------
    //**********************************************************************


















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

    //void focusInEvent (QFocusEvent *e) { raise(); this->update(); mtkContainerWidget::focusInEvent(e);  paint_focus();}
    //void focusOutEvent(QFocusEvent *e) { raise(); this->update(); mtkContainerWidget::focusOutEvent(e); remove_focus();}
    virtual QSize  sizeHint(void) const;



private slots:
    void make_transparent(void);
    void remove_transparecy(void);

private:
    QPoint startPos;

    void paint_focus(void);
    void remove_focus(void);

    void on_message_addtional_info(const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_additional_info&);



    ui_switch_money*  ui;
    swm_calculator    calculator;


    void    on_error(const mtk::Alarm&  error);
};


YAML::Emitter& operator << (YAML::Emitter& out, const QSwicthMoney& m);


#endif // QSWITCH_MONEY_COMPONENT__
