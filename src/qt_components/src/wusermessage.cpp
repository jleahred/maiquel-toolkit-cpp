#include "wusermessage.h"
#include "ui_wusermessage.h"


#include "support/date_time.h"
#include "support/mtk_string.h"




wUserMessage::wUserMessage(QWidget *_parent) :
    QDialog(_parent),
    ui(new Ui::wUserMessage),
    parent(_parent)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.75);

    createTrayIcon();
}

wUserMessage::~wUserMessage()
{
    trayIcon->hide();
    delete trayIcon;
    delete ui;
    wUserMessage::user_message_window = 0;
}



QPoint  wUserMessage::last_pos = QPoint(0,0);
wUserMessage*  wUserMessage::user_message_window =0;

void wUserMessage::show_message(const QString& message)
{
    if(last_pos.x() != 0    ||    last_pos.y()!=0)
        user_message_window->move(last_pos);

    user_message_window->ui->message->appendPlainText(QLatin1String(""));
    user_message_window->ui->message->appendHtml(QLatin1String(MTK_SS("<P STYLE=\"margin-bottom: 0in\"><FONT COLOR=\"#000000\"><B>" << mtk::dtNowLocal() << "</B></FONT></P>").c_str()));
    user_message_window->ui->message->appendHtml(message);
    //user_message_window->adjustSize();
    user_message_window->show();

    QTextDocument doc;
    doc.setHtml( message );
    user_message_window->trayIcon->showMessage(QLatin1String("eCimd"), doc.toPlainText(), QSystemTrayIcon::Warning, 300000);

    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "wusermessage", message.toStdString(), mtk::alPriorWarning));
}

void wUserMessage::on_pushButton_clicked()
{
    ui->message->clear();
    this->hide();
    trayIcon->showMessage(QLatin1String(""), QLatin1String(""), QSystemTrayIcon::NoIcon, 0);
}

void wUserMessage::init(QWidget* parent)
{
    if(user_message_window != 0)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "wUserMessage::init", "double init??", mtk::alPriorError));
    }
    else
        user_message_window = new wUserMessage(parent);
}





void wUserMessage::closeEvent(QCloseEvent *  /*event*/)
{
    last_pos = this->pos();
}


void wUserMessage::createTrayIcon(void)
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(QString::fromUtf8(":/small_icons/ecimd_ico")));

    trayIcon->setToolTip(QLatin1String("eCimd"));
    trayIcon->show();
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(slot_show_window()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slot_iconActivated(QSystemTrayIcon::ActivationReason)));
}

void wUserMessage::slot_iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        slot_show_window(false);
        break;
    case QSystemTrayIcon::MiddleClick:
    default:
        ;
    }
}

void wUserMessage::slot_show_window(bool /*lets_hide_if_visible*/)
{
    parent->hide();
    parent->showMinimized();
    parent->showMaximized();
    parent->raise();
    qApp->setActiveWindow(parent);
    if(ui->message->toPlainText().size() != 0)
        showNormal();
}
