#include "monitor.h"
#include "ui_monitor.h"


#include "../../../../tools/qt/logview/src/highlighter.h"
#include "support/mtk_string.h"
#include "components/admin/msg_admin.h"
#include "components/request_response.hpp"



namespace {

    const mtk::dtTimeQuantity starting_time = mtk::dtSeconds(40);

};


//-------------------------------------------------------------------------------
//      P R E P A R I N G    M T K
//-------------------------------------------------------------------------------
#include <QTimer>
#include "support/timer.h"


mtk::Signal<const mtk::Alarm&>  sig_alarm_msg;
void mtk::AlarmMsg (const Alarm& alarm)
{
        sig_alarm_msg.emit(alarm);
}


MTK_Qt_timer_and_AlarmMsg::MTK_Qt_timer_and_AlarmMsg (QWidget *parent) : QObject(parent)
{
    //  incializamos qpid, como siempre
    try
    {
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(check_mtk_timer()));
        timer->start(10);

        sig_alarm_msg.connect(this, &MTK_Qt_timer_and_AlarmMsg::process_signalAlarm);
        return;
    }
    MTK_CATCH_CALLFUNCION(std::cerr << , "MTK_Qt_Prepare", "Initializing library")
    exit(-1);
};

MTK_Qt_timer_and_AlarmMsg::~MTK_Qt_timer_and_AlarmMsg()
{
}
void MTK_Qt_timer_and_AlarmMsg::check_mtk_timer()
{
    try
    {
        mtk::__internal_check_timers();
    }
    MTK_CATCH_CALLFUNCION (signalAlarm  , "MTK_Qt_timer::check_mtk_timer", "")
}

void MTK_Qt_timer_and_AlarmMsg::process_signalAlarm (const mtk::Alarm& alarm)
{
    signalAlarm.emit(alarm);
}




//-------------------------------------------------------------------------------
//      P R E P A R I N G    M T K
//-------------------------------------------------------------------------------





class QListWidgetItem_ka  : public QListWidgetItem
{
public:
    QListWidgetItem_ka(QString text, QListWidget* parent, mtk::dtDateTime   _next_ka, const std::string& _location, const std::string& _machine)
        :     QListWidgetItem(text, parent)
            , next_ka(mtk::make_nullable(_next_ka))
            , location(_location)
            , machine(_machine)
    {}

    mtk::nullable<mtk::dtDateTime>   next_ka;
    std::string   location;
    std::string   machine;

private:
};




Monitor::Monitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Monitor),
    started_application(mtk::dtNowLocal())
{
    ui->setupUi(this);



    ui->split_client->setStretchFactor(1,4);
    //ui->splitter_client_command->setStretchFactor(1,8);

    // code highlight
    /*highlighter_log = */new Highlighter(ui->log->document());
                          new Highlighter(ui->logAllCli->document());
                          new Highlighter(ui->logErrorCli->document());


    connect(ui->client_command, SIGNAL(exec_command(QString)), SLOT(send_command(QString)));


    MTK_Qt_timer_and_AlarmMsg* mtk_timer_alarmmsg = new MTK_Qt_timer_and_AlarmMsg(this);
    MTK_CONNECT_THIS(mtk_timer_alarmmsg->signalAlarm, OnAlarm);


    qpid_admin_session = mtk::get_from_factory< mtk::qpid_session >(mtk::make_tuple(std::string("amqp:tcp:127.0.0.1:5672"), std::string("ADMCLI")));

    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_client_enter,
                            "amqp:tcp:127.0.0.1:5672",
                            "ADMCLI",
                            mtk::admin::msg::enter::get_in_subject(),
                            mtk::admin::msg::enter,
                            on_enter_client_received)

    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_client_exit,
                            "amqp:tcp:127.0.0.1:5672",
                            "ADMCLI",
                            mtk::admin::msg::exit::get_in_subject(),
                            mtk::admin::msg::exit,
                            on_exit_client_received)

    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_client_ka,
                            "amqp:tcp:127.0.0.1:5672",
                            "ADMCLI",
                            mtk::admin::msg::keep_alive::get_in_subject(),
                            mtk::admin::msg::keep_alive,
                            on_ka_client_received)

    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_client_alarm,
                            "amqp:tcp:127.0.0.1:5672",
                            "ADMCLI",
                            mtk::admin::msg::alarm::get_in_subject(),
                            mtk::admin::msg::alarm,
                            on_client_alarm_received)

    MTK_TIMER_1S(check_client_ka)

}

Monitor::~Monitor()
{
    delete ui;
}


void Monitor::Log(const QString value)
{
    if (ui->log->isVisible() == false)
        ui->log->setVisible(true);
    ui->log->appendPlainText(value);
}

void Monitor::LogCliAll  (const QString value)
{
    ui->logAllCli->appendPlainText(value);
}

void Monitor::LogCliError(const QString value)
{
    ui->logErrorCli->appendPlainText(value);
}




void Monitor::on_enter_client_received(const mtk::admin::msg::enter& msg)
{
    //Log(MTK_SS(msg).c_str());
    QString composed_name = MTK_SS(msg.header.location << "." << msg.header.machine).c_str();
    QList<QListWidgetItem *> item_list = ui->clientlist->findItems(composed_name, Qt::MatchExactly);
    if (item_list.size() != 0)
    {
        QListWidgetItem_ka* itka = dynamic_cast<QListWidgetItem_ka*>(item_list.front());
        if(itka)
        {
            if(itka->next_ka.HasValue())
                Log(mtk::Alarm(MTK_HERE, "received enter on a client already registered", mtk::alPriorError, mtk::alTypeNoPermisions));
            else
                itka->next_ka = mtk::dtNowLocal() + msg.ka_interval_check;
        }
    }
    else
    {
        QListWidgetItem_ka* new_item = new QListWidgetItem_ka(composed_name, ui->clientlist, mtk::dtNowLocal() + msg.ka_interval_check, msg.header.location, msg.header.machine);
        new_item->setCheckState(Qt::Unchecked);
        ui->clientlist->addItem(new_item);
    }
}


void Monitor::on_exit_client_received (const mtk::admin::msg::exit& msg)
{
    //Log(MTK_SS(msg).c_str());
    QString composed_name = MTK_SS(msg.header.location << "." << msg.header.machine).c_str();

    QList<QListWidgetItem *> item_list = ui->clientlist->findItems(composed_name, Qt::MatchExactly);
    if (item_list.size() == 0)
        Log(mtk::Alarm(MTK_HERE, "received exit on a non registered client", mtk::alPriorError, mtk::alTypeNoPermisions));
    else
    {
        QListWidgetItem *it;
        foreach(it, item_list)
        {
            delete it;
        }
    }
}


void Monitor::on_ka_client_received   (const mtk::admin::msg::keep_alive& msg)
{
    //Log(MTK_SS(msg).c_str());
    QString composed_name = MTK_SS(msg.header.location << "." << msg.header.machine).c_str();

    QList<QListWidgetItem *> item_list = ui->clientlist->findItems(composed_name, Qt::MatchExactly);
    if (item_list.size() == 0)
    {
        if ((mtk::dtNowLocal() - started_application) > starting_time)
            Log(mtk::Alarm(MTK_HERE, "received keep alive  on a non registered client", mtk::alPriorError, mtk::alTypeNoPermisions));
        QString composed_name = MTK_SS(msg.header.location << "." << msg.header.machine).c_str();
        QListWidgetItem_ka* new_item = new QListWidgetItem_ka(composed_name, ui->clientlist, mtk::dtNowLocal() + msg.ka_interval_check, msg.header.location, msg.header.machine);
        new_item->setCheckState(Qt::Unchecked);
        ui->clientlist->addItem(new_item);
    }
    else
    {
        QListWidgetItem *it;
        foreach(it, item_list)
        {
            QListWidgetItem_ka* itka = dynamic_cast<QListWidgetItem_ka*>(it);
            if(itka)
                itka->next_ka = mtk::dtNowLocal() + msg.ka_interval_check;
        }
    }
}


void Monitor::check_client_ka(void)
{
    for(int i=0;i<ui->clientlist->count();i++){
        QListWidgetItem_ka* itka = dynamic_cast<QListWidgetItem_ka*>(ui->clientlist->item(i));
        if(itka)
        {
            if(itka->next_ka.HasValue())
            {
                if(itka->next_ka.Get() < mtk::dtNowLocal())
                {
                        Log(mtk::Alarm(MTK_HERE, MTK_SS(itka->text().toStdString() << "  lost keep alive"), mtk::alPriorError, mtk::alTypeNoPermisions));
                        itka->setBackgroundColor(Qt::red);
                        itka->next_ka = mtk::nullable<mtk::DateTime>();
                }
                else
                {
                    itka->setBackgroundColor(Qt::white);
                }
            }
        }
    }
}


mtk::Alarm  get_alarm_from_msg(const mtk::admin::msg::alarm& alarm_msg)
{
    return mtk::Alarm(alarm_msg.code_source, alarm_msg.message, alarm_msg.priority, alarm_msg.type);
}


void Monitor::on_client_alarm_received(const mtk::admin::msg::alarm& alarm_msg)
{
    QString composed_name = MTK_SS(alarm_msg.header.location << "." << alarm_msg.header.machine).c_str();
    QList<QListWidgetItem *> item_list = ui->clientlist->findItems(composed_name, Qt::MatchExactly);
    if (item_list.size() == 0)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(5))
            if ((mtk::dtNowLocal() - started_application) > starting_time)
                Log(mtk::Alarm(MTK_HERE, MTK_SS(composed_name.toStdString() << "  receiving alarms with no keep alive"), mtk::alPriorError, mtk::alTypeNoPermisions));
        MTK_END_EXEC_MAX_FREC
    }


    mtk::Alarm rec_alarm(get_alarm_from_msg(alarm_msg));
    if(rec_alarm.priority == mtk::alPriorCritic  ||  rec_alarm.priority == mtk::alPriorError)
        Log(rec_alarm, rec_alarm.alarmID);
    LogCli(rec_alarm, rec_alarm.alarmID);
}



/*
 chivarse si se recibe una alarma de un proceso no monitorizado

 */
/*
void Monitor::on_pushButton_clicked()
{

    for(int i=0; i<ui->clientlist->count(); ++i)
    {
        QListWidgetItem_ka* itka = dynamic_cast<QListWidgetItem_ka*>(ui->clientlist->item(i));
        if(itka)
        {
            if(itka->checkState() == Qt::Checked)
            {
                mtk::admin::msg::command cmd_msg(
                        mtk::msg::sub_request_r(MTK_SS("Monitor::" << mtk::rand())),
                        mtk::admin::msg::sub_admin_header(itka->location, itka->machine, mtk::dtNowLocal()),
                        ui->client_command->toPlainText().toStdString());
                mtk::send_message(qpid_admin_session, cmd_msg);
            }
        }
    }
}
*/

void Monitor::send_command(const QString &command)
{
    if(command=="__")
    {
        ui->client_command_response->appendPlainText("");
        ui->client_command_response->appendPlainText("Local command help...................");
        ui->client_command_response->appendPlainText("__clear to delete the results window");
        ui->client_command_response->appendPlainText("");
        return;
    }
    if(command=="__clear")
    {
        ui->client_command_response->clear();
        return;
    }

    for(int i=0;i<ui->clientlist->count();i++)
    {
        QListWidgetItem_ka* itka = dynamic_cast<QListWidgetItem_ka*>(ui->clientlist->item(i));
        if(itka)
        {
            if(itka->checkState() == Qt::Checked)
            {
                send_command(command, itka->location.c_str(), itka->machine.c_str(), "");
            }
        }
    }
}

void Monitor::send_command(const QString& command, const QString& location, const QString& machine, const QString& /*process*/)
{
    mtk::msg::sub_request_r request_code(MTK_SS(mtk::rand()));


    //  subscription to multiresponse
    MTK_RECEIVE_MULTI_RESPONSE_THIS(   mtk::admin::msg::command_response,
                                    mtk::admin::msg::sub_command_rd,
                                    qpid_admin_session,
                                    mtk::admin::msg::command_response::get_in_subject(request_code.request_code),
                                    on_command_response)

    //  sending hello command
    mtk::admin::msg::command command_request_msg(   request_code,
                                                    mtk::admin::msg::sub_admin_header(  location.toStdString(),
                                                                                        machine.toStdString(),
                                                                                        mtk::dtNowLocal()),
                                                                                        command.toStdString());
    mtk::send_message(qpid_admin_session, command_request_msg);
    ui->client_command_response->appendPlainText(
            MTK_SS(std::endl << std::endl << std::endl << "SENDING COMMAND  " << command.toStdString() << "  TO " << location.toStdString() << "  "  << machine.toStdString()
                   << std::endl << "----------------------------------------------------").c_str());
}


void Monitor::on_command_response (const mtk::list<mtk::admin::msg::command_response>& responses)
{
    mtk::list<mtk::admin::msg::command_response>::const_iterator it = responses.begin();
    while(it != responses.end())
    {
        const mtk::admin::msg::command_response& response = *it;
        ui->client_command_response->appendPlainText(response.response_data.text.c_str());
        std::cout << *it << std::endl;
        ++it;
    }
}

