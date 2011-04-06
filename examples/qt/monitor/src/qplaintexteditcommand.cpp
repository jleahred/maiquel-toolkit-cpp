#include "qplaintexteditcommand.h"

#include <QPlainTextEdit>
#include <QTextBlock>
#include "qlistprocesses.h"

#include "components/request_response.hpp"
#include "support/crc32.h"





QPlainTextEditCommand::QPlainTextEditCommand(QWidget *parent) :
    QPlainTextEdit(parent), write_into(0)
{
}




void QPlainTextEditCommand::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter  ||  event->key() == Qt::Key_Return)
    {
        send_command(this->textCursor().block().text());
        if(this->textCursor().atBlockEnd())
            QPlainTextEdit::keyPressEvent(event);
    }
    else
    {
        //  emacs movement keys...
        if ((event->key() == Qt::Key_P)  &&  (event->modifiers()  &  Qt::ControlModifier) )
        {
            QTextCursor cursor = this->textCursor();
            cursor.movePosition(QTextCursor::PreviousBlock);
            this->setTextCursor(cursor);
            return;
        }
        if ((event->key() == Qt::Key_N)  &&  (event->modifiers()  &  Qt::ControlModifier) )
        {
            QTextCursor cursor = this->textCursor();
            cursor.movePosition(QTextCursor::NextBlock);
            this->setTextCursor(cursor);
            return;
        }
        if ((event->key() == Qt::Key_P)  &&  (event->modifiers()  &  Qt::AltModifier) )
        {
            QTextCursor cursor = this->textCursor();
            for (int i=0; i<20; ++i)
                cursor.movePosition(QTextCursor::PreviousBlock);
            this->setTextCursor(cursor);
            return;
        }
        if ((event->key() == Qt::Key_N)  &&  (event->modifiers()  &  Qt::AltModifier) )
        {
            QTextCursor cursor = this->textCursor();
            for (int i=0; i<20; ++i)
                cursor.movePosition(QTextCursor::NextBlock);
            this->setTextCursor(cursor);
            return;
        }

        if ((event->key() == Qt::Key_A)  &&  (event->modifiers()  &  Qt::ControlModifier) )
        {
            QTextCursor cursor = this->textCursor();
            cursor.movePosition(QTextCursor::StartOfBlock);
            this->setTextCursor(cursor);
            return;
        }
        if ((event->key() == Qt::Key_E)  &&  (event->modifiers()  &  Qt::ControlModifier) )
        {
            QTextCursor cursor = this->textCursor();
            cursor.movePosition(QTextCursor::EndOfBlock);
            this->setTextCursor(cursor);
            return;
        }
        if ((event->key() == Qt::Key_F)  &&  (event->modifiers()  &  Qt::ControlModifier) )
        {
            QTextCursor cursor = this->textCursor();
            cursor.movePosition(QTextCursor::NextCharacter);
            this->setTextCursor(cursor);
            return;
        }
        if ((event->key() == Qt::Key_B)  &&  (event->modifiers()  &  Qt::ControlModifier) )
        {
            QTextCursor cursor = this->textCursor();
            cursor.movePosition(QTextCursor::PreviousCharacter);
            this->setTextCursor(cursor);
            return;
        }
        if ((event->key() == Qt::Key_F)  &&  (event->modifiers()  &  Qt::AltModifier) )
        {
            QTextCursor cursor = this->textCursor();
            cursor.movePosition(QTextCursor::NextWord);
            this->setTextCursor(cursor);
            return;
        }
        if ((event->key() == Qt::Key_B)  &&  (event->modifiers()  &  Qt::AltModifier) )
        {
            QTextCursor cursor = this->textCursor();
            cursor.movePosition(QTextCursor::PreviousWord);
            this->setTextCursor(cursor);
            return;
        }

        if ((event->key() == Qt::Key_D)  &&  (event->modifiers()  &  Qt::ControlModifier) )
        {
            QTextCursor cursor = this->textCursor();
            cursor.deleteChar();
            return;
        }
        if ((event->key() == Qt::Key_K)  &&  (event->modifiers()  &  Qt::ControlModifier) )
        {
            this->textCursor().deleteChar();
            QTextCursor cursor = this->textCursor();
            while (this->textCursor().atBlockEnd() == false)
            {
                this->textCursor().deleteChar();
            }
            return;
        }


        QPlainTextEdit::keyPressEvent(event);
    }
}


void QPlainTextEditCommand::send_command(const QString& command)
{
    if(command.trimmed() == "")
        return;
    if(command=="__")
    {
        std::string result = MTK_SS(std::endl <<"Local command help..................." << std::endl <<
                                    "__clear to delete the results window"  << std::endl);
        if(write_into)
            write_into->appendPlainText(result.c_str());
        else
            throw mtk::Alarm(MTK_HERE, "monitor", "write_into not initialized.", mtk::alPriorError);
        return;
    }
    if(command=="__clear")
    {
        std::string result = "__clear__";
        if(write_into)
            write_into->clear();
        else
            throw mtk::Alarm(MTK_HERE, "monitor", "write_into not initialized.", mtk::alPriorError);
        return;
    }




    mtk::list<mtk::msg::sub_process_info>  admin_process_info_to_send;
    //Q_EMIT signal_fill_locations_to_send(admin_locations_to_send);
    if(list_processes)
        list_processes->fill_process_info_for_selected_items(admin_process_info_to_send);
    else
        throw mtk::Alarm(MTK_HERE, "monitor", "list_processes  not initialized.", mtk::alPriorError);


    mtk::list<mtk::msg::sub_process_info>::iterator it = admin_process_info_to_send.begin();
    while(it!=admin_process_info_to_send.end())
    {
        mtk::msg::sub_request_info   request_info(mtk::msg::sub_request_id("monitor", mtk::crc32_as_string(MTK_SS(mtk::rand()))), it->process_location);
        //  subscription to multiresponse
        MTK_RECEIVE_MULTI_RESPONSE_THIS(mtk::admin::msg::res_command,
                                        mtk::admin::msg::sub_command_rd,
                                        qpid_admin_session,
                                        mtk::admin::msg::res_command::get_in_subject(it->process_location.process_uuid, request_info.req_id.req_code),
                                        on_command_response)

        mtk::admin::msg::req_command   command_request_msg(request_info, it->process_location,  command.toStdString());
        mtk::send_message(qpid_admin_session, command_request_msg);
        if(write_into)
            write_into->appendPlainText(MTK_SS(std::endl << std::endl << std::endl << "SENDING COMMAND  "
                                               << command.toStdString() << "  -->  " << it->process_location.location.client_code << "  "
                                               << it->process_location.location.machine  << "  "
                                               << it->process_location.process_name << "  "
                                               << it->process_location.process_uuid
                                               << std::endl << "_______________________________________________________________________________________________").c_str());
        else
            throw mtk::Alarm(MTK_HERE, "monitor","write_into not initialized.", mtk::alPriorError);
        ++it;
    }
}


void QPlainTextEditCommand::on_command_response (const mtk::list<mtk::admin::msg::res_command>& responses)
{
    std::string result;
    mtk::list<mtk::admin::msg::res_command>::const_iterator it = responses.begin();
    while(it != responses.end())
    {
        const mtk::admin::msg::res_command& response = *it;
        result += response.response_data.text;
        ++it;
    }
    if(write_into)
        write_into->appendPlainText(result.c_str());
    else
        throw mtk::Alarm(MTK_HERE, "monitor","write_into not initialized.", mtk::alPriorError);
}


void QPlainTextEditCommand::init(QPlainTextEdit *_write_into, QListProcesses* _list_processes, mtk::CountPtr< mtk::qpid_session > _qpid_admin_session)
{
    write_into      = _write_into;
    list_processes  = _list_processes;
    qpid_admin_session = _qpid_admin_session;
}
