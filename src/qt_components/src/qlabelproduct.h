#ifndef QLABELPRODUCT_H
#define QLABELPRODUCT_H

#include <QLabel>
#include "components/prices/cli/price_manager.h"



class QDragEnterEvent;


class QLabelProduct : public QLabel,  public  mtk::SignalReceptor
{
    Q_OBJECT
public:
    explicit QLabelProduct(QWidget *parent = 0);


    //  INPUT

    //  OUTPUT
    mtk::Signal<const mtk::msg::sub_product_code&>                                                      signal_product_configured;
    mtk::Signal<const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_best_prices&>            signal_best_prices_update;
    mtk::Signal<const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_last_mk_execs_ticker&>   signal_last_mk_execs_ticker;
    mtk::Signal<const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_additional_info&>        signal_additional_info_update;


    //  ACCESS
    mtk::CountPtr<mtk::prices::price_manager>       price_manager;


protected:
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual bool event ( QEvent * event );
    virtual void dropEvent(QDropEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void mouseReleaseEvent(QMouseEvent *event);


signals:

public slots:

private:
    QPoint startPos;

    void subscribe_to (const mtk::msg::sub_product_code& _product_code);

    void on_message_additional_info_update(const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_additional_info& /*msg*/);
    void check_info_pending(void);

};

#endif // QLABELPRODUCT_H
