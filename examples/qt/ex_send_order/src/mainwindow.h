#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "components/trading/msg_trd_cli_ls.h"



namespace Ui {
    class MainWindow;
}



//-------------------------------------------------------------------------------
//      P R E P A R I N G     M T K
//-------------------------------------------------------------------------------
#include "support/signalslot.hpp"
#include "support/alarm.h"
#include "mtk_qpid/mtk_qpid.h"

class MTK_Qt_timer_and_AlarmMsg : public QObject, public mtk::SignalReceptor    // <1>
    {
        Q_OBJECT

    public:
        MTK_Qt_timer_and_AlarmMsg (QWidget *parent = 0);
        ~MTK_Qt_timer_and_AlarmMsg();

        mtk::Signal<const mtk::Alarm&>     signalAlarm;                         // <2>

    private slots:
        void check_mtk_timer();
    private:
        void process_signalAlarm (const mtk::Alarm& alarm);

    };
//-------------------------------------------------------------------------------
//      P R E P A R I N G     M T K
//-------------------------------------------------------------------------------




class MainWindow : public QMainWindow,   public  mtk::SignalReceptor
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void OnAlarm(const mtk::Alarm& alarm) {
        Log (MTK_SS(alarm).c_str());
    }

private:
    Ui::MainWindow *ui;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiver> hqpidr_in;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiver> hqpidr_out;

    void Log(const QString value);
    void on_message(const qpid::messaging::Message& message);

    mtk::trd::msg::RQ_XX_LS get_xx_request(void);
    mtk::msg::sub_process_info   get_process_info(void);

    mtk::list<mtk::trd::msg::RQ_NW_LS>  list_new;
    mtk::list<mtk::trd::msg::RQ_CC_LS>  list_cc;
    void timer_new_cancel(void);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pbNewOrderFromOrderBook_clicked();
    void on_pbSendCancelOrder_clicked();
    void on_pbPrepareNewRequest_clicked();
    void on_pbSendModifOrder_clicked();
    void on_pbPrepareNewOrder_clicked();
    void on_pbDelLog_clicked();
    void on_pbListen_clicked();
    void on_pbNewOrder_clicked();
};

#endif // MAINWINDOW_H
