#ifndef MONITOR_H
#define MONITOR_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTextBlock>


#include "components/admin/msg_admin.h"




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




class QPlainTextEditCommand : public QPlainTextEdit
{
    Q_OBJECT
    typedef QPlainTextEditCommand  CLASS_NAME;
public:
    QPlainTextEditCommand(QWidget* parent)  :  QPlainTextEdit(parent) {}

    void keyPressEvent(QKeyEvent *e)
    {
        if(e->key() == Qt::Key_Enter  ||  e->key() == Qt::Key_Return)
        {
            Q_EMIT exec_command(this->textCursor().block().text());
            if(this->textCursor().atBlockEnd())
                QPlainTextEdit::keyPressEvent(e);
        }
        else
            QPlainTextEdit::keyPressEvent(e);
    }

signals:
    void exec_command(const QString& command_to_execute);

};




class Monitor : public QMainWindow,   public  mtk::SignalReceptor
{
    Q_OBJECT
    typedef Monitor  CLASS_NAME;

public:
    explicit Monitor(QWidget *parent = 0);
    ~Monitor();

    void OnAlarm(const mtk::Alarm& alarm) {  Log (alarm);  }


private:
    Ui::Monitor *ui;
    //Highlighter* highlighter_log;

    mtk::dtDateTime   started_application;


    void Log(const QString value);
    void Log(const mtk::Alarm& alarm, int alarm_id=-1) {
        if (alarm_id!= -1)
            Log (MTK_SS(alarm << " [" << alarm_id << "]").c_str());
        else
            Log (MTK_SS(alarm).c_str());
    }

    void LogCliAll  (const QString value);
    void LogCliError(const QString value);
    void LogCli(const mtk::Alarm& alarm, int alarm_id=-1) {
        if (alarm_id!= -1)
        {
            LogCliAll (MTK_SS(alarm << " [" << alarm_id << "]").c_str());
            if(alarm.priority == mtk::alPriorCritic  ||  alarm.priority == mtk::alPriorError)
                LogCliError(MTK_SS(alarm << " [" << alarm_id << "]").c_str());
        }
        else
        {
            LogCliAll (MTK_SS(alarm).c_str());
            if(alarm.priority == mtk::alPriorCritic  ||  alarm.priority == mtk::alPriorError)
                LogCliError(MTK_SS(alarm).c_str());
        }
    }



    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::enter>      > hqpid_client_enter;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::keep_alive> > hqpid_client_ka;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::exit>       > hqpid_client_exit;

    void on_enter_client_received(const mtk::admin::msg::enter& msg);
    void on_exit_client_received (const mtk::admin::msg::exit& msg);
    void on_ka_client_received   (const mtk::admin::msg::keep_alive& msg);

    void check_client_ka(void);



    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::alarm>       > hqpid_client_alarm;
    void on_client_alarm_received(const mtk::admin::msg::alarm& alarm_msg);

    mtk::CountPtr< mtk::qpid_session >  qpid_admin_session;

    void on_command_response (const mtk::list<mtk::admin::msg::command_response>& responses);


    void send_command(const QString& command, const QString& location, const QString& machine, const QString& process);

private slots:
    void send_command(const QString& command);
};

#endif // MONITOR_H
