#ifndef MONITOR_H
#define MONITOR_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <Phonon/MediaObject>


#include "components/admin/msg_admin.h"





class QLabel;




class Highlighter;
namespace Ui {
    class Monitor;
}



//-------------------------------------------------------------------------------
//      P R E P A R I N G     M T K
//-------------------------------------------------------------------------------
#include "support/signalslot.hpp"
#include "support/alarm.h"
#include "mtk_qpid/mtk_qpid.hpp"

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








class Monitor : public QMainWindow,   public  mtk::SignalReceptor
{
    Q_OBJECT
    typedef Monitor  CLASS_NAME;

public:
    explicit Monitor(QWidget *parent = 0);
    ~Monitor();

    void OnAlarm(const mtk::Alarm& alarm);


private slots:
    void  slot_show_window(bool lets_hide_if_visible=false);
    void  slot_iconActivated(QSystemTrayIcon::ActivationReason reason);
    void  slot_alarm(const mtk::admin::msg::pub_alarm& alarm_msg);


protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::Monitor *ui;
    bool                production;


    mtk::t_qpid_url     url;

    void on_command_response (const mtk::list<mtk::admin::msg::res_command>& responses);

    QLabel*  status_client_processes;
    QLabel*  status_server_processes;
    QLabel*  status_all_alarm;
    QLabel*  status_cli_error_alarm;
    QLabel*  status_cli_all_alarm;
    QLabel*  status_srv_error_alarm;
    QLabel*  status_srv_all_alarm;



    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    void createTrayIcon();
    QAction *minimizeAction;
    //QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    Phonon::MediaObject *mediaObject;
};

#endif // MONITOR_H
