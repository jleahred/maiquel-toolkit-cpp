#ifndef MONITOR_H
#define MONITOR_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <Phonon/MediaObject>


#include "components/admin/msg_admin.h"
#include "msg_structs.h"





class QLabel;




class Highlighter_rules;
class Highlighter_alarm;
namespace Ui {
    class Monitor;
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




struct   Config
{
    Config(const std::string&   _file_name)  :      file_name(_file_name) {}
    std::string                         file_name;


    //  properties
    mtk::list<mon::msg::sub_rule>       rules__error2warning;
    std::string                         amqp_url;
    std::string                         gs_code;


    void            save(const std::string&  text);
    void            load(void);
    void            mem_save_refresh(void);

    mtk::Signal<const std::string&>     signal_text_changed;

};





class Monitor : public QMainWindow,   public  mtk::SignalReceptor
{
    Q_OBJECT

public:
    explicit Monitor(const std::string&  _config_file_name, QWidget *parent = 0);
    ~Monitor();

    void OnAlarm(const mtk::Alarm& alarm);


private slots:
    void on_set_counters_to_zero_clicked();
    void on_prepare_edit_clicked();
    void on_mem_save_refresh_clicked();
    void on_config_text_modificationChanged(bool );
    void on_pb_save_clicked();
    void  slot_show_window(bool lets_hide_if_visible=false);
    void  slot_iconActivated(QSystemTrayIcon::ActivationReason reason);
    void  slot_alarm(const mtk::admin::msg::pub_alarm& alarm_msg);
    void  slot_ruletext_modificated(void);
    void  slot_compute_re_rule(void);

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

    Config        config_info;
    void update_config_text(const std::string& new_text);

    Highlighter_rules* highlighter_rules;
    Highlighter_alarm* highlighter_alarm0;
    Highlighter_alarm* highlighter_alarm1;
    Highlighter_alarm* highlighter_alarm2;
    Highlighter_alarm* highlighter_alarm3;

};

#endif // MONITOR_H
