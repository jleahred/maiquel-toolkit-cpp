#ifndef QPROD_INFO_H__
#define QPROD_INFO_H__

#include "qt_components/src/mtkcontainerwidget.h"

#include "support/signalslot.hpp"

#include "mtk_qpid/mtk_qpid.h"
#include "components/prices/msg_prices.h"
#include "components/prices/cli/price_manager.h"

#include <QTextCharFormat>
#include <qsyntaxhighlighter.h>


class  QLabel;
class  QPlainTextEdit;

namespace YAML { class Emitter;  class Node;      };






class QProd_info : public mtkContainerWidget, public mtk::SignalReceptor
{
    Q_OBJECT
    friend YAML::Emitter&   operator << (YAML::Emitter&       out, const QProd_info& m);
    friend void             operator >> (const YAML::Node&   node,       QProd_info& d);
    /*
    class Highlighter : public QSyntaxHighlighter
    {
        //Q_OBJECT

     public:
        Highlighter(QTextDocument *parent = 0);

     protected:
         void highlightBlock(const QString &text);

     private:
         struct HighlightingRule
         {
             QRegExp pattern;
             QTextCharFormat format;
         };

         QVector<HighlightingRule> highlightingRules;
         QTextCharFormat formatRule;
    };
    */
public:
    explicit QProd_info(QWidget *parent = 0);
    ~QProd_info();

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

    void focusInEvent (QFocusEvent *e) { paint_focus();  raise(); this->update(); mtkContainerWidget::focusInEvent(e);}
    void focusOutEvent(QFocusEvent *e) { remove_focus(); raise(); this->update(); mtkContainerWidget::focusOutEvent(e);}



private slots:
    void make_transparent(void);
    void remove_transparecy(void);

private:
    QLabel              *title;
    QPlainTextEdit      *info;
    mtk::CountPtr<mtk::prices::price_manager>       price_manager;
    //Highlighter         *highlighter;

    QPoint startPos;

    void paint_focus(void);
    void remove_focus(void);

    void on_message_addtional_info(const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_additional_info&);
};


YAML::Emitter& operator << (YAML::Emitter& out, const QProd_info& m);


#endif // QPROD_INFO_H__
