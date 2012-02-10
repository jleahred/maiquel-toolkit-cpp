#ifndef WHISTORIC_ORDER_H
#define WHISTORIC_ORDER_H

#include <QDialog>

#include "components/trading/trd_cli_ord_book.h"
#include "components/trading/trd_cli_ls.h"
#include "components/trading/trd_cli_mk.h"




namespace Ui {
    class whistoric_order;
}

namespace mtk { namespace trd {  namespace msg  {  class sub_order_id;  } } };


class whistoric_order : public QDialog,  public  mtk::SignalReceptor
{
    Q_OBJECT
    typedef  whistoric_order  CLASS_NAME;
    template<typename  ORDER_TYPE>  friend void fill_from(whistoric_order*, ORDER_TYPE&);

public:
    explicit whistoric_order(QWidget *parent = 0);
    ~whistoric_order();

    void set_order  (const mtk::trd::msg::sub_order_id& order_id);

protected:
    void   showEvent ( QShowEvent * event );        //  overwritten

private:
    Ui::whistoric_order *ui;


    mtk::CountPtr<mtk::trd::trd_cli_ls>   order_ls;
    mtk::CountPtr<mtk::trd::trd_cli_mk>   order_mk;

    void update_on_change(void);


private slots:
    void on_radioButton_toggled(bool checked);
};

#endif // WHISTORIC_ORDER_H
