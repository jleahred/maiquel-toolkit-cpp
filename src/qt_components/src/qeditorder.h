#ifndef QEDITORDER_H
#define QEDITORDER_H

#include <QDialog>

#include "components/trading/msg_trd_cli_ls.h"

namespace Ui {
    class QEditOrder;
}

class QEditOrder : public QDialog
{
    Q_OBJECT

public:
    //explicit QEditOrder(QWidget *parent = 0);
    explicit QEditOrder(const mtk::trd::msg::RQ_XX_LS& _rq, QWidget *parent = 0);

    ~QEditOrder();

    //void set_request(const mtk::trd::msg::RQ_XX_LS& rq);
    mtk::trd::msg::RQ_XX_LS get_request(void);

private:
    Ui::QEditOrder *ui;

    mtk::trd::msg::RQ_XX_LS  rq;
};

#endif // QEDITORDER_H
