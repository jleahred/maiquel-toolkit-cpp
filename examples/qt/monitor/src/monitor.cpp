#include "monitor.h"
#include "ui_monitor.h"


#include <QMessageBox>

#include "../../../../tools/qt/logview/src/highlighter.h"
#include "support/mtk_string.h"
#include "components/admin/msg_admin.h"




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





void error_connecting (const mtk::Alarm& error)
{
    std::cerr << error;
    QMessageBox msgBox;
    msgBox.setText(MTK_SS("Problem connecting to server.  \n\n" << error).c_str());
    msgBox.exec();
    QApplication::closeAllWindows();
    exit(-1);
}




Monitor::Monitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Monitor)
{
    ui->setupUi(this);



    ui->split_client->setStretchFactor(1,4);
    ui->split_server->setStretchFactor(1,4);

    //ui->splitter_client_command->setStretchFactor(1,8);


    MTK_Qt_timer_and_AlarmMsg* mtk_timer_alarmmsg = new MTK_Qt_timer_and_AlarmMsg(this);
    MTK_CONNECT_THIS(mtk_timer_alarmmsg->signalAlarm, OnAlarm);

    try
    {
        qpid_admin_session_srv = mtk::get_from_factory< mtk::qpid_session >(mtk::make_tuple(std::string("amqp:tcp:127.0.0.1:5672"), std::string("SRVTESTING")));
        qpid_admin_session_cli = mtk::get_from_factory< mtk::qpid_session >(mtk::make_tuple(std::string("amqp:tcp:127.0.0.1:5672"), std::string("CLITESTING")));
    }
    MTK_CATCH_CALLFUNCION(error_connecting, "main", "")


    ui->alarms_all_errors->init     (qpid_admin_session_cli, qpid_admin_session_srv, true);
    {
        ui->alarms_client_all->init     (qpid_admin_session_cli, false);
        ui->alarms_client_error->init   (qpid_admin_session_cli, true);
        ui->client_command->init(ui->client_command_response, ui->clientlist, qpid_admin_session_cli);
        ui->clientlist->init(qpid_admin_session_cli);
        ui->clientlist->signal_alarm.connect(&sig_alarm_msg);
    }
    {
        ui->alarms_server_all->init     (qpid_admin_session_srv, false);
        ui->alarms_server_error->init   (qpid_admin_session_srv, true);
        ui->server_command->init(ui->server_command_response, ui->serverlist, qpid_admin_session_srv);
        ui->serverlist->init(qpid_admin_session_srv);
        ui->serverlist->signal_alarm.connect(&sig_alarm_msg);
    }
}

Monitor::~Monitor()
{
    delete ui;
}


void Monitor::OnAlarm(const mtk::Alarm& alarm)
{
    ui->alarms_all_errors->write_alarm(alarm);
}
