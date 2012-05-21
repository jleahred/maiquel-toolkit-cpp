#ifndef WUSERMESSAGE_H
#define WUSERMESSAGE_H

#include <QDialog>
#include <QSystemTrayIcon>

namespace Ui {
    class wUserMessage;
}

class wUserMessage : public QDialog
{
    Q_OBJECT

public:
    ~wUserMessage();


    static  void init(QWidget* parent);
    static  void show_message       (const QString& message);
    static  void show_message_hard  (const QString& message);


protected:
    void closeEvent(QCloseEvent *event);

private:
    explicit wUserMessage(QWidget *parent = 0);
    Ui::wUserMessage *ui;

    QSystemTrayIcon *trayIcon;
    void   createTrayIcon(void);
    QWidget *parent;

    static wUserMessage* user_message_window;

    static  QPoint  last_pos;

private slots:
    void on_pushButton_clicked();
    void  slot_iconActivated(QSystemTrayIcon::ActivationReason reason);
    void  slot_show_window(bool lets_hide_if_visible=false);
};

#endif // WUSERMESSAGE_H
