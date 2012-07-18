#ifndef QTickerExecs_H__
#define QTickerExecs_H__

#include "qt_components/src/mtkcontainerwidget.h"

#include "support/signalslot.hpp"

#include "mtk_qpid/mtk_qpid.h"
#include "components/prices/prices_publication.h"


#include <QTextCharFormat>
#include <qsyntaxhighlighter.h>


class  QLabel;
class  QPlainTextEdit;

namespace YAML { class Emitter;  class Node;      };






class QTickerExecs : public mtkContainerWidget, public mtk::SignalReceptor
{
    Q_OBJECT
    friend YAML::Emitter&   operator << (YAML::Emitter&       out, const QTickerExecs& m);
    friend void             operator >> (const YAML::Node&   node,       QTickerExecs& d);

    static    int  num_subscriptions;
public:
    explicit QTickerExecs(QWidget *parent = 0);
    ~QTickerExecs();

    void subscribe_to (const mtk::msg::sub_product_code&  _product_code);

    mtk::msg::sub_product_code  get_product_code(void)  const  {  return product_code;  }


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

    void focusInEvent (QFocusEvent *e) { paint_focus();  raise(); this->update(); mtkContainerWidget::focusInEvent(e);}
    void focusOutEvent(QFocusEvent *e) { remove_focus(); raise(); this->update(); mtkContainerWidget::focusOutEvent(e);}



private slots:
    void make_transparent(void);
    void remove_transparecy(void);

private:
    mtk::msg::sub_product_code   product_code;
    QLabel                       *title;
    QPlainTextEdit               *info;

    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::plaet> >      handle_execs_subscription;
    QPoint startPos;

    void paint_focus(void);
    void remove_focus(void);

    void on_all_last_execs__update          (const mtk::prices::msg::plaet&  plaet);
};


YAML::Emitter& operator << (YAML::Emitter& out, const QTickerExecs& m);


#endif // QTickerExecs_H__
