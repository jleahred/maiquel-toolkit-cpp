#ifndef UI_SWITCH_MONEY_H
#define UI_SWITCH_MONEY_H

#include <QFrame>
#include <QWidget>

#include "swm_config.h"
#include "swm_calculator.h"


#include "components/prices/msg_prices.h"



namespace Ui {
    class ui_switch_money;
}

class ui_switch_money : public QFrame,  public  mtk::SignalReceptor
{
    Q_OBJECT

public:
    explicit ui_switch_money(QWidget *parent = 0);
    ~ui_switch_money();


    //**********************************************************************
    //----------------------------------------------------------------------
    //......................................................................



    //  INPUT
    void        on_price_update(const swm_calculator::s_price_update&);
    void        on_error(const mtk::Alarm&);




    //  OUTPUT
    mtk::Signal<const swm_config&>      signal_config_changed;



    //......................................................................
    //----------------------------------------------------------------------
    //**********************************************************************





protected:

private:
    Ui::ui_switch_money *ui;

    //  inputs
    void on_ORIGIN_message_best_prices  (const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_best_prices& msg);
    void on_DESTIN_message_best_prices  (const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_best_prices& msg);

    void on_ORIGIN_product_configured   (const mtk::msg::sub_product_code&);
    void on_DESTIN_product_configured   (const mtk::msg::sub_product_code&);


    //  look


    //  config
    void start_config(void);
    void end_config(void);
    void set_empty_input_price_quantity(void);
    void initialize_origin(void);
    void initialize_destiny(void);

    void add_log(const QString&  text);


private slots:
    void on_config_button_clicked();
    void on_config_button_toggled(bool checked);

    //void applicationFocusChanged ( QWidget * old, QWidget * now );

    void  config_changed(void);
    void  set_status(const QString&  status);

};

#endif // UI_SWITCH_MONEY_H
