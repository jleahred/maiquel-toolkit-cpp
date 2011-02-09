#include "mainwindow.h"
#include "ui_mainwindow.h"




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
    //  incializamos tibco, como siempre
    try
    {
        QTimer *timer = new QTimer(this);                                       // <1>
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
        mtk::__internal_check_timers();                                         // <2>
    }
    MTK_CATCH_CALLFUNCION (signalAlarm  , "MTK_Qt_timer::check_mtk_timer", "")
}

void MTK_Qt_timer_and_AlarmMsg::process_signalAlarm (const mtk::Alarm& alarm)                   // <3>
{
    signalAlarm.emit(alarm);
}




//-------------------------------------------------------------------------------
//      P R E P A R I N G    M T K
//-------------------------------------------------------------------------------








const std::string g_url = "amqp:tcp:127.0.0.1:5672";
const std::string g_address = "news_t";




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MTK_Qt_timer_and_AlarmMsg* mtk_timer_alarmmsg = new MTK_Qt_timer_and_AlarmMsg(this);     // <4>
    MTK_CONNECT_THIS(mtk_timer_alarmmsg->signalAlarm, OnAlarm);                              // <5>
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbSendMessage_clicked()
{
    static int counter=0;

    // this is very inneficient, just to test and example
    mtk::CountPtr< mtk::qpid_session > qpid_session = mtk::get_from_factory< mtk::qpid_session >(mtk::make_tuple(ui->lblUrl->text().toStdString(), ui->leAddress->text().toStdString()));
    qpid::messaging::Message msg(MTK_SS("sending message " << ++counter));
    msg.setSubject(ui->leSendingSubject->text().toStdString());
    qpid_session->sender.send(msg);
}

void MainWindow::Write(const QString value)
{
    ui->ptOutput->setPlainText( ui->ptOutput->toPlainText() + value + "\n");
}



void MainWindow::on_pbConnect_clicked()
{
    handle_qpid_receiver = mtk::get_from_factory<mtk::handle_qpid_exchange_receiver>(mtk::make_tuple(ui->lblUrl->text().toStdString(), ui->leAddress->text().toStdString(), ui->leFilter->text().toStdString()));
    MTK_CONNECT_THIS(*(handle_qpid_receiver->signalMessage), OnReceivedMessage)
}

void MainWindow::OnReceivedMessage(const qpid::messaging::Message& message)
{
    Write(MTK_SS(message.getHeaders() << "  " << message.getContent()).c_str());
}
