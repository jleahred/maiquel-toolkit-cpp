#ifndef QEditOrder_AND_H
#define QEditOrder_AND_H

#include <QDialog>

#include "components/trading/msg_trd_cli_ls.h"
#include "components/prices/cli/price_manager.h"




namespace Ui {
    class QEditOrder_and;
}

class QEditOrder_and : public QDialog, public  mtk::SignalReceptor
{
    Q_OBJECT
    typedef  QEditOrder_and  CLASS_NAME;

public:
    static  void  new_order(    const mtk::msg::sub_product_code&       pc,
                                mtk::trd::msg::enBuySell                buy_sell,
                                const mtk::trd::msg::sub_position_ls&   rq_pos,
                                bool                                    agression,
                                QWidget *parent);


    ~QEditOrder_and();


protected:
    virtual bool eventFilter(QObject *, QEvent *);
    virtual void moveEvent ( QMoveEvent * event );

private:
    Ui::QEditOrder_and *ui;

    const mtk::msg::sub_product_code        pc;
    const mtk::trd::msg::enBuySell          buy_sell;
    const mtk::trd::msg::sub_position_ls    rq_pos;
    mtk::nullable<mtk::FixedNumber>         best_bid;
    mtk::nullable<mtk::FixedNumber>         best_ask;


    mtk::list<mtk::trd::msg::sub_account_info>  account_list;

    mtk::CountPtr<mtk::prices::price_manager>       price_manager;



    void common_init(void);

    explicit QEditOrder_and(    const mtk::msg::sub_product_code&       pc,
                                mtk::trd::msg::enBuySell                buy_sell,
                                const mtk::trd::msg::sub_position_ls&   rq_pos,
                                bool                                    agression,
                                QWidget *parent);


    bool check_if_order_can_be_sent(void);
    void done(int);
    void mouseDoubleClickEvent(QMouseEvent *);

    void fill_accounts(void);
    void register_event_filters(void);
    void  on_best_price_update(const mtk::msg::sub_product_code& pc, const mtk::prices::msg::sub_best_prices& bp);


private slots:
    void on_pb_secondary_clicked();
    void on_best_oposite_toggled(bool checked);
    void on_pb_main_clicked();
    void on_account_currentIndexChanged(QString );
    void on_price_valueChanged(QString );
    void on_quantity_valueChanged(QString );
};





#endif // QEditOrder_AND_H
