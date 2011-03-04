#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "support/date_time.h"

#include "qorderbook.h"

//-------------------------------------------------------------------------------
//      P R E P A R I N G    M T K
//-------------------------------------------------------------------------------
#include <QTimer>
#include "support/timer.h"

/*
mtk::Signal<const mtk::Alarm&>  sig_alarm_msg;
void mtk::AlarmMsg (const Alarm& alarm)
{
        sig_alarm_msg.emit(alarm);
}
*/

MTK_Qt_timer_and_AlarmMsg::MTK_Qt_timer_and_AlarmMsg (QWidget *parent) : QObject(parent)
{
    //  incializamos mtk, como siempre
    try
    {
        QTimer *timer = new QTimer(this);                                       // <1>
        connect(timer, SIGNAL(timeout()), this, SLOT(check_mtk_timer()));
        timer->start(10);

        //sig_alarm_msg.connect(this, &MTK_Qt_timer_and_AlarmMsg::process_signalAlarm);
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



/*
namespace mtk{  namespace msg  {
sub_request_id   get_request_id (void)
{
    static int i=0;
    static std::string session = MTK_SS("pending" << mtk::dtNowLocal());
    return sub_request_id(session, MTK_SS("pending"<<++i));
}

};};  //namespace mkt{  namespace msg  {
*/


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MTK_Qt_timer_and_AlarmMsg* mtk_timer_alarmmsg = new MTK_Qt_timer_and_AlarmMsg(this);     // <4>
    MTK_CONNECT_THIS(mtk_timer_alarmmsg->signalAlarm, OnAlarm);                              // <5>

    ui->leReqInfo_SessionID->setText(MTK_SS(mtk::dtNowLocal()).c_str());
    ui->leOderID_SessionID->setText(ui->leReqInfo_SessionID->text());
    ui->leReqInfo_RequestCode->setText("1");
    ui->leOrderID_RequestCode->setText("1");


    //  start listening
    on_pbListen_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::Log(const QString value)
{
    ui->pteLog->appendPlainText(value);
}

void MainWindow::on_pbListen_clicked()
{
    hqpidr_in = mtk::get_from_factory<mtk::handle_qpid_exchange_receiver>(mtk::make_tuple(ui->leUrl->text().toStdString(), ui->leInAddress->text().toStdString(), std::string("#")));
    MTK_CONNECT_THIS(*(hqpidr_in->signalMessage), on_message)
}

void MainWindow::on_message(const qpid::messaging::Message& message)
{
    qpid::types::Variant::Map mv;
    qpid::messaging::decode(message, mv);
    Log(QString(MTK_SS(message.getSubject() << " " << message.getSubject()  << " " << mv).c_str()));
}

void MainWindow::on_pbDelLog_clicked()
{
    ui->pteLog->clear();
}

void MainWindow::on_pbPrepareNewOrder_clicked()
{
    ui->leOrderID_RequestCode->setText(QString::number(ui->leOrderID_RequestCode->text().toInt()+1));
    ui->leReqInfo_RequestCode->setText(QString::number(ui->leReqInfo_RequestCode->text().toInt()+1));
}

void MainWindow::on_pbPrepareNewRequest_clicked()
{
    ui->leReqInfo_RequestCode->setText(QString::number(ui->leReqInfo_RequestCode->text().toInt()+1));
}



mtk::trd::msg::RQ_XX_LS MainWindow::get_xx_request(void)
{
    mtk::trd::msg::sub_order_id         ord_id(mtk::msg::sub_request_id(ui->leOderID_SessionID->text().toStdString(), ui->leOrderID_RequestCode->text().toStdString()));
    mtk::msg::sub_product_code          pc (    mtk::msg::sub_single_product_code  (    ui->leMarket->text().toStdString(),
                                                                                        ui->leProduct->text().toStdString(),
                                                                                        mtk::nullable<std::string>()),
                                                    mtk::nullable<mtk::msg::sub_single_product_code>(), mtk::nullable<std::string>() );

    mtk::trd::msg::enBuySell side;
    if (ui->buy->isChecked())
        side = mtk::trd::msg::buy;
    else
        side = mtk::trd::msg::sell;


    return mtk::trd::msg::RQ_XX_LS(
                                              mtk::msg::sub_request_info( mtk::msg::sub_request_id(ui->leReqInfo_SessionID->text().toStdString(),
                                                                                                   ui->leReqInfo_RequestCode->text().toStdString()),
                                                                          ui->leReqInfo_CliCode->text().toStdString())
                                            , ord_id
                                            , pc
                                            , mtk::trd::msg::sub_position_ls(
                                                      mtk::FixedNumber(mtk::fnDouble(ui->lePrice->text().toDouble()),  mtk::fnDec(2),  mtk::fnInc(1))
                                                    , mtk::FixedNumber(mtk::fnDouble(ui->leQuantity->text().toDouble())     ,  mtk::fnDec(0),  mtk::fnInc(1))
                                                    , side)
                                            , ui->leCliRef->text().toStdString());
}

void MainWindow::on_pbNewOrder_clicked()
{
    //  not efficient, just to test
    mtk::CountPtr< mtk::qpid_session > qpid_session = mtk::get_from_factory< mtk::qpid_session >(mtk::make_tuple(ui->leUrl->text().toStdString(), ui->leOutAddress->text().toStdString()));

    mtk::trd::msg::RQ_NW_LS rq(get_xx_request());
    mtk::send_message(qpid_session, rq, "");
}

void MainWindow::on_pbSendModifOrder_clicked()
{
    //  not efficient, just to test
    mtk::CountPtr< mtk::qpid_session > qpid_session = mtk::get_from_factory< mtk::qpid_session >(mtk::make_tuple(ui->leUrl->text().toStdString(), ui->leOutAddress->text().toStdString()));

    mtk::trd::msg::RQ_MD_LS rq(get_xx_request());
    mtk::send_message(qpid_session, rq, "");
}


void MainWindow::on_pbSendCancelOrder_clicked()
{
    //  not efficient, just to test
    mtk::CountPtr< mtk::qpid_session > qpid_session = mtk::get_from_factory< mtk::qpid_session >(mtk::make_tuple(ui->leUrl->text().toStdString(), ui->leOutAddress->text().toStdString()));

    mtk::trd::msg::RQ_CC_LS rq(get_xx_request());
    mtk::send_message(qpid_session, rq, "");
}

void MainWindow::on_pbNewOrderFromOrderBook_clicked()
{
    mtk::trd::msg::RQ_NW_LS rq(get_xx_request());
    mtk::trd::trd_cli_ord_book::rq_nw_ls_manual(rq.product_code, rq.request_pos, rq.cli_ref);
}
void MainWindow::on_pushButton_clicked()
{
    for (int i=0; i<100; ++i)
    {
        on_pbPrepareNewOrder_clicked();
        on_pbNewOrder_clicked();
    }
}
