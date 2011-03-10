#ifndef QPLAINTEXTEDITCOMMAND_H
#define QPLAINTEXTEDITCOMMAND_H

#include <QPlainTextEdit>

#include "components/admin/msg_admin.h"



class QListProcesses;

class QPlainTextEditCommand : public QPlainTextEdit,  public  mtk::SignalReceptor
{
    Q_OBJECT
    typedef QPlainTextEditCommand  CLASS_NAME;
public:
    explicit QPlainTextEditCommand(QWidget* parent);

    void init(QPlainTextEdit* _write_into, QListProcesses* _list_processes, mtk::CountPtr< mtk::qpid_session > qpid_admin_session);


    void on_command_response (const mtk::list<mtk::admin::msg::command_response>& responses);

private:
    QPlainTextEdit*                     write_into;
    QListProcesses*                     list_processes;
    mtk::CountPtr< mtk::qpid_session >  qpid_admin_session;

    void send_command(const QString& command);
    void keyPressEvent(QKeyEvent *e);


signals:
    //void  signal_fill_locations_to_send(mtk::list<mtk::admin::msg::sub_process_location>& locations2fill);

};




#endif // QPLAINTEXTEDITCOMMAND_H
