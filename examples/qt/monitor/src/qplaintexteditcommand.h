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

    void init(QPlainTextEdit* _write_into, QListProcesses* _list_processes, const mtk::t_qpid_url& url, const std::string&  cli_srv);


    void on_command_response (const mtk::list<mtk::admin::msg::res_command>& responses);

private:
    QPlainTextEdit*                         write_into;
    QListProcesses*                         list_processes;

    void send_command(const QString& command);
    void keyPressEvent(QKeyEvent *e);

    std::string     cli_srv;
    mtk::t_qpid_url url;


signals:

};




#endif // QPLAINTEXTEDITCOMMAND_H
