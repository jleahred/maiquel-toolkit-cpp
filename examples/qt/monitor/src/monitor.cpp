#include "monitor.h"
#include "ui_monitor.h"


#include <QMessageBox>
#include <QLabel>

#include <fstream>


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

void mtk::check_control_fields_flucts(const std::string & /*key*/, const mtk::DateTime & /*dt*/)
{

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



Config*        ptr_config_info=0;

Monitor::Monitor(const std::string& _config_file_name,  QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Monitor),
    production(false),
    url(mtk::t_qpid_url("")),
    mediaObject (Phonon::createPlayer(Phonon::NoCategory, Phonon::MediaSource(QLatin1String("alarm.wav")))),
    config_info(_config_file_name)
{
    ui->setupUi(this);

    MTK_CONNECT_THIS(config_info.signal_text_changed, update_config_text);
    config_info.load();
    ptr_config_info = &config_info;


    ui->split_client->setStretchFactor(1,4);
    ui->split_server->setStretchFactor(1,4);

    //ui->splitter_client_command->setStretchFactor(1,8);


    MTK_Qt_timer_and_AlarmMsg* mtk_timer_alarmmsg = new MTK_Qt_timer_and_AlarmMsg(this);
    MTK_CONNECT_THIS(mtk_timer_alarmmsg->signalAlarm, OnAlarm);

    try
    {
        //QString  qurl = "amqp:tcp:127.0.0.1:5683";
        //QString  qurl = "amqp:tcp:192.168.7.1:5683";
        //QString  qurl = "amqp:tcp:192.168.7.21:6684";           //  production
        //QString  qurl = "amqp:tcp:192.168.7.2:5683";             //    simulación
        QString  qurl = config_info.amqp_url.c_str();

        url = mtk::t_qpid_url(qurl.toStdString());

        if(qurl.split(":")[3][0] == '6')
            production = true;

        if(production == false)
            this->setStyleSheet(
                        "QWidget"
                        "{"
                        "        background-color: rgb(255, 220, 168);"
                        "}"

                        "QAbstractScrollArea, QLineEdit"
                        "{"
                        "        background-color: rgb(255, 255, 255);"
                        "}");
    }
    MTK_CATCH_CALLFUNCION(error_connecting, "main", "")


    ui->alarms_all_errors->init     (url, true);
    {
        ui->alarms_client_all->init     (url, "CLI", false);
        ui->alarms_client_error->init   (url, "CLI", true);
        ui->client_command->init(ui->client_command_response, ui->clientlist, url, "CLI");
        ui->clientlist->init(url, "CLI");
        ui->clientlist->signal_alarm.connect(&sig_alarm_msg);
    }
    {
        ui->alarms_server_all->init     (url, "SRV", false);
        ui->alarms_server_error->init   (url, "SRV", true);
        ui->server_command->init(ui->server_command_response, ui->serverlist, url, "SRV");
        ui->serverlist->init(url, "SRV");
        ui->serverlist->signal_alarm.connect(&sig_alarm_msg);
    }



    QLabel * version = new QLabel();
    //version->setFrameShape(QFrame::Panel);
    //version->setFrameShadow(QFrame::Sunken);
    version->setText("0.12");
    statusBar()->addWidget(version);


    status_client_processes = new QLabel();
    status_client_processes->setFrameShape(QFrame::Panel);
    status_client_processes->setFrameShadow(QFrame::Sunken);
    statusBar()->addWidget(status_client_processes);
    connect(ui->clientlist, SIGNAL(signal_status_tip(QString)), status_client_processes, SLOT(setText(QString)));

    status_server_processes = new QLabel();
    status_server_processes->setFrameShape(QFrame::Panel);
    status_server_processes->setFrameShadow(QFrame::Sunken);
    statusBar()->addWidget(status_server_processes);
    connect(ui->serverlist, SIGNAL(signal_status_tip(QString)), status_server_processes, SLOT(setText(QString)));

    status_all_alarm = new QLabel();
    status_all_alarm->setFrameShape(QFrame::Panel);
    status_all_alarm->setFrameShadow(QFrame::Sunken);
    statusBar()->addWidget(status_all_alarm);
    connect(ui->alarms_all_errors, SIGNAL(signal_status_tip(QString)), status_all_alarm,  SLOT(setText(QString)));

    status_cli_error_alarm = new QLabel();
    status_cli_error_alarm->setFrameShape(QFrame::Panel);
    status_cli_error_alarm->setFrameShadow(QFrame::Sunken);
    statusBar()->addWidget(status_cli_error_alarm);
    connect(ui->alarms_client_error, SIGNAL(signal_status_tip(QString)), status_cli_error_alarm,  SLOT(setText(QString)));


    status_cli_all_alarm = new QLabel();
    status_cli_all_alarm->setFrameShape(QFrame::Panel);
    status_cli_all_alarm->setFrameShadow(QFrame::Sunken);
    statusBar()->addWidget(status_cli_all_alarm);
    connect(ui->alarms_client_all, SIGNAL(signal_status_tip(QString)), status_cli_all_alarm,  SLOT(setText(QString)));

    status_srv_error_alarm = new QLabel();
    status_srv_error_alarm->setFrameShape(QFrame::Panel);
    status_srv_error_alarm->setFrameShadow(QFrame::Sunken);
    statusBar()->addWidget(status_srv_error_alarm);
    connect(ui->alarms_server_error, SIGNAL(signal_status_tip(QString)), status_srv_error_alarm,  SLOT(setText(QString)));

    status_srv_all_alarm = new QLabel();
    status_srv_all_alarm->setFrameShape(QFrame::Panel);
    status_srv_all_alarm->setFrameShadow(QFrame::Sunken);
    statusBar()->addWidget(status_srv_all_alarm);
    connect(ui->alarms_server_all, SIGNAL(signal_status_tip(QString)), status_srv_all_alarm,  SLOT(setText(QString)));

    connect(ui->alarms_client_all,   SIGNAL(signal_show_full_message(QString)), ui->cli_alarm_msg_all,          SLOT(setPlainText(QString)));
    connect(ui->alarms_client_error, SIGNAL(signal_show_full_message(QString)), ui->cli_alarm_msg_errors,       SLOT(setPlainText(QString)));
    connect(ui->alarms_server_all,   SIGNAL(signal_show_full_message(QString)), ui->server_alarm_msg_all,       SLOT(setPlainText(QString)));
    connect(ui->alarms_server_error, SIGNAL(signal_show_full_message(QString)), ui->server_alarm_msg_errors,    SLOT(setPlainText(QString)));

    connect(ui->filter_client_all, SIGNAL(textEdited(QString)), ui->alarms_client_all, SLOT(slot_set_filter(QString)));
    connect(ui->filter_server_all, SIGNAL(textEdited(QString)), ui->alarms_server_all, SLOT(slot_set_filter(QString)));

    connect(ui->alarms_all_errors, SIGNAL(signal_alarm(mtk::admin::msg::pub_alarm)), this, SLOT(slot_alarm(mtk::admin::msg::pub_alarm)));






    minimizeAction = new QAction(tr("Hide"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    /*
    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));
    */

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(slot_show_window()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    createTrayIcon();
}

Monitor::~Monitor()
{
    on_mem_save_refresh_clicked();
    delete ui;
}


void Monitor::OnAlarm(const mtk::Alarm& alarm)
{
    ui->alarms_all_errors->write_alarm(mtk::dtNowLocal(), alarm);
    /*
    if(production)
    {
        trayIcon->showMessage("New alarm", "Generated internally from monitor", QSystemTrayIcon::Critical, 300000);
        trayIcon->setIcon(QIcon(":/images/images/bug_red.svg"));
        MTK_EXEC_MAX_FREC(mtk::dtSeconds(10))
                mediaObject->setCurrentSource(Phonon::MediaSource("alarm.wav"));
                mediaObject->play();
        MTK_END_EXEC_MAX_FREC

    }
    else
        trayIcon->setIcon(QIcon(":/images/images/warning4.svg"));
    */
}


void Monitor::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    //trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    if(production)
    {
        trayIcon->setIcon(QIcon(":/images/images/bug_green.svg"));
        setWindowIcon(QIcon(":/images/images/bug_red.svg"));
    }
    else
    {
        trayIcon->setIcon(QIcon(":/images/images/Off_bulb_icon.svg"));
        setWindowIcon(QIcon(":/images/images/Light_bulb_icon.svg"));
    }
    trayIcon->setToolTip("monitor");
    trayIcon->show();
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(slot_show_window()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slot_iconActivated(QSystemTrayIcon::ActivationReason)));
}

void Monitor::slot_show_window(bool lets_hide_if_visible)
{
    if(lets_hide_if_visible)
    {
        if(this->isVisible())
            hide();
        else
        {
            hide();
            showMaximized();
        }
    }
    else
    {
        hide();
        //showNormal();
        showMaximized();
    }

    trayIcon->showMessage("", "", QSystemTrayIcon::NoIcon, 0);
    if(production)
    {
        trayIcon->setIcon(QIcon(":/images/images/bug_green.svg"));
        if(mediaObject->state() == Phonon::PlayingState)
            mediaObject->stop();
    }
    else
        trayIcon->setIcon(QIcon(":/images/images/Off_bulb_icon.svg"));
}

void Monitor::closeEvent(QCloseEvent *event)
{
    /*
    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Monitor"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));
    }*/
    hide();
    event->ignore();
}

void Monitor::slot_iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        slot_show_window(true);
        break;
    case QSystemTrayIcon::MiddleClick:
        if((QApplication::keyboardModifiers() &  Qt::ControlModifier)  != 0)
        {
            mediaObject->setCurrentSource(Phonon::MediaSource("alarm.wav"));
            mediaObject->play();
        }
        break;
    default:
        ;
    }
}

void  Monitor::slot_alarm(const mtk::admin::msg::pub_alarm& alarm_msg)
{
    if(production)
    {
        trayIcon->showMessage("New alarm", MTK_SS(alarm_msg.process_info).c_str(), QSystemTrayIcon::Critical, 300000);
        trayIcon->setIcon(QIcon(":/images/images/bug_red.svg"));
        MTK_EXEC_MAX_FREC(mtk::dtSeconds(10))
                mediaObject->setCurrentSource(Phonon::MediaSource("alarm.wav"));
                mediaObject->play();
        MTK_END_EXEC_MAX_FREC
    }
    else
        trayIcon->setIcon(QIcon(":/images/images/Light_bulb_icon.svg"));
}

void Monitor::on_pb_save_clicked()
{
    config_info.save(ui->config_text->toPlainText().toStdString());
    ui->config_text->document()->setModified(false);
}

void Monitor::update_config_text(const std::string& new_text)
{
    ui->config_text->setPlainText(new_text.c_str());
    ui->client_command->gs_code = config_info.gs_code;
    ui->server_command->gs_code = config_info.gs_code;
}


void  Config::save(const std::string&  text)
{
    std::ofstream config_file;
    config_file.open (file_name.c_str());


    try
    {
        config_file << text.c_str();
        config_file.close();
        load();
    }
    catch(const mtk::Alarm&  error)
    {
        QMessageBox(QMessageBox::Critical, "Error", MTK_SS("Error saving configuration  " << error).c_str()).exec();
    }
    catch(const std::exception& error)
    {
        QMessageBox(QMessageBox::Critical, "Error", MTK_SS("Error saving configuration  " << error.what()).c_str()).exec();
    }
    catch(...)
    {
        QMessageBox(QMessageBox::Critical, "Error", "Error saving configuration").exec();
    }
}

void  Config::load(void)
{

    try
    {
        std::ifstream config_file(file_name.c_str());
        YAML::Parser parser(config_file);

        YAML::Node doc;
        parser.GetNextDocument(doc);
        std::string config_version;
        doc["version"] >> config_version;
        rules__error2warning.clear();
        doc["amqp_url"]  >>  amqp_url;
        doc["gs_code"]  >>  gs_code;
        doc["rules__error2warning"]  >>  rules__error2warning;
        config_file.close();

        /*
        if(doc.FindValue("splitter_main"))
        {
            std::string  splitter_status;
            doc["splitter_main"]  >> splitter_status;
            ui->splitter_main->restoreState(QByteArray::fromHex(splitter_status.c_str()));
        }
        */
        {
            std::ifstream config_file(file_name.c_str());
            std::string text;
            while(!config_file.eof())
            {
                std::string line;
                std::getline(config_file, line);
                text += line +"\n";
            }
            signal_text_changed.emit(text);
            config_file.close();
        }
    }
    catch(const mtk::Alarm&  error)
    {
        QMessageBox(QMessageBox::Critical, "Error", MTK_SS("Error loading configuration  " << error).c_str()).exec();
    }
    catch(const std::exception& error)
    {
        QMessageBox(QMessageBox::Critical, "Error", MTK_SS("Error loading configuration  " << error.what()).c_str()).exec();
    }
    catch(...)
    {
        QMessageBox(QMessageBox::Critical, "Error", "Error loading configuration").exec();
    }
}


void Monitor::on_config_text_modificationChanged(bool )
{
    if(ui->config_text->document()->isModified())
        ui->config_text->setStyleSheet("background-color: rgb(255, 192, 192);");
   else
        ui->config_text->setStyleSheet("");
}

//Config*        ptr_config_info=0;
mtk::alEnPriority  filter_alarm_priority(mtk::alEnPriority  orig_priority, const QString&  full_text_message)
{
    mtk::RegExp  re_filter;

    if(orig_priority  ==  mtk::alPriorCritic   ||  orig_priority == mtk::alPriorError)
    {
        for (auto it = ptr_config_info->rules__error2warning.begin(); it!=ptr_config_info->rules__error2warning.end(); ++it)
        {
            mtk::dtDateTime  now   = mtk::dtNowLocal();
            mtk::dtDateTime  today = mtk::dtToday_0Time();
            if(it->last_notified + mtk::dtSeconds(5)  <  now       &&
               today + it->start_time                 <  now       &&
               today + it->end_time                   >  now         )
            {
                //mon::msg::sub_rule rule; rule.frequency
                re_filter.SetPattern(it->re_rule); re_filter.Compile(true);
                if (re_filter.Match(full_text_message.toStdString()))
                {
                    ++it->n_received;
                    if(it->last_notified + it->frequency > mtk::dtNowLocal())
                    {
                        return mtk::alPriorWarning;
                    }
                    else
                    {
                        it->last_notified = mtk::dtNowLocal();
                        return orig_priority;
                    }
                }
            }
        }
    }
    return orig_priority;
}


void Monitor::on_mem_save_refresh_clicked()
{
    config_info.mem_save_refresh();
}

void        Config::mem_save_refresh(void)
{
    std::ofstream config_file;
    config_file.open (file_name.c_str());


    try
    {
        YAML::Emitter out;
        out  <<  YAML::BeginMap;

        out  << YAML::Key << "version"   <<  YAML::Value << 1;

        out  << YAML::Key << "amqp_url"   <<  YAML::Value   <<  amqp_url;

        out  << YAML::Key << "gs_code"   <<  YAML::Value   <<  gs_code;

        if(rules__error2warning.size() == 0)
            rules__error2warning.push_back(mon::msg::sub_rule("__just__example__", mtk::dtSeconds(5), 0, "description", mtk::dtSeconds(0), mtk::dtDays(1),  mtk::dtNowLocal()));
        out  << YAML::Key << "rules__error2warning"   <<  YAML::Value   <<  rules__error2warning;

        out <<  YAML::EndMap;
        config_file << out.c_str();
        config_file.close();

        load();

    }
    catch(const mtk::Alarm&  error)
    {
        QMessageBox(QMessageBox::Critical, "Error", MTK_SS("Error saving configuration  " << error).c_str()).exec();
    }
    catch(const std::exception& error)
    {
        QMessageBox(QMessageBox::Critical, "Error", MTK_SS("Error saving configuration  " << error.what()).c_str()).exec();
    }
    catch(...)
    {
        QMessageBox(QMessageBox::Critical, "Error", "Error saving configuration").exec();
    }
}


void  Monitor::slot_ruletext_modificated(void)
{
    ui->re_rule_result->setText("_");
}

void Monitor::slot_compute_re_rule(void)
{
    mtk::RegExp  re_filter;
    //re_filter.SetOptions(mtk::RegExp::MULTILINE);

    re_filter.SetPattern(ui->re_rule2test->text().toStdString());  re_filter.Compile(true);
    if (re_filter.Match(ui->re_rule_message2test->toPlainText().toStdString()))
    {
        ui->re_rule_result->setText("matches");
    }
    else
    {
        ui->re_rule_result->setText("DOESN'T MATCH");
    }
}
