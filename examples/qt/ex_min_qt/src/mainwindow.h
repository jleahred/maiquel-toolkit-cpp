#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



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



namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow,   public  mtk::SignalReceptor            // <3>
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void OnAlarm(const mtk::Alarm& alarm) {
        Write (MTK_SS(alarm).c_str());
    }

private:
    Ui::MainWindow *ui;

    void Write(const QString value);


    mtk::CountPtr< mtk::handle_qpid_exchange_receiver>  handle_qpid_receiver;    // <4>
    void OnReceivedMessage (const qpid::messaging::Message& message);


private slots:
    void on_pbConnect_clicked();
    void on_pbSendMessage_clicked();
};

#endif // MAINWINDOW_H
