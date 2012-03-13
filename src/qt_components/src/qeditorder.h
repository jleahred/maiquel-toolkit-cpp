#ifndef QEDITORDER_H
#define QEDITORDER_H

#include <QDialog>

#include "components/trading/msg_trd_cli_ls.h"
#include "components/trading/msg_trd_cli_mk.h"
#include "components/trading/msg_trd_cli_sm.h"



/*
    If account is not empty, it will not be possible to change it
    It is used on modifications
    On new orders, it will receive a empty account
    and this dialog will fill acount fields choosing the default one (as in quantity)
 */


namespace Ui {
    class QEditOrder;
}

class QEditOrder : public QDialog
{
    Q_OBJECT

public:

    template<typename  RQ_TYPE>
    void common_init(const RQ_TYPE& rq);

    //explicit QEditOrder(QWidget *parent = 0);
    explicit QEditOrder(const mtk::trd::msg::RQ_XX_LS& _rq, bool agressive, QWidget *parent = 0);
    explicit QEditOrder(const mtk::trd::msg::RQ_XX_MK& _rq, bool agressive, QWidget *parent = 0);
    explicit QEditOrder(const mtk::trd::msg::RQ_XX_SM& _rq, bool agressive, QWidget *parent = 0);

    ~QEditOrder();

    //void set_request(const mtk::trd::msg::RQ_XX_LS& rq);
    mtk::trd::msg::RQ_XX_LS   get_request_ls(void);
    mtk::trd::msg::RQ_XX_MK   get_request_mk(void);
    mtk::trd::msg::RQ_XX_SM   get_request_sm(void);

protected:
    virtual bool eventFilter(QObject *, QEvent *);

private:
    Ui::QEditOrder *ui;

    mtk::nullable<mtk::trd::msg::RQ_XX_LS>      rq_ls;
    mtk::nullable<mtk::trd::msg::RQ_XX_MK>      rq_mk;
    mtk::nullable<mtk::trd::msg::RQ_XX_SM>      rq_sm;
    mtk::list<mtk::trd::msg::sub_account_info>  account_list;


    bool check_if_order_can_be_sent(void);
    void done(int);
    void mouseDoubleClickEvent(QMouseEvent *);

    void fill_accounts(const mtk::trd::msg::RQ_XX& rq);
    void register_event_filters(void);


private slots:
    void on_account_currentIndexChanged(QString );
    void on_price_valueChanged(QString );
    void on_quantity_valueChanged(QString );
};

#endif // QEDITORDER_H
