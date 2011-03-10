#include "qplaintexteditcommand.h"

#include <QPlainTextEdit>
#include <QTextBlock>
#include "qlistprocesses.h"

#include "components/request_response.hpp"





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
    if(command=="__")
    {
        std::string result = MTK_SS(std::endl <<"Local command help..................." << std::endl <<
                                    "__clear to delete the results window"  << std::endl);
        if(write_into)
            write_into->appendPlainText(result.c_str());
        else
            throw mtk::Alarm(MTK_HERE, "write_into not initialized.", mtk::alPriorError);
        return;
    }
    if(command=="__clear")
    {
        std::string result = "__clear__";
        if(write_into)
            write_into->clear();
        else
            throw mtk::Alarm(MTK_HERE, "write_into not initialized.", mtk::alPriorError);
        return;
    }




    mtk::list<mtk::admin::msg::sub_process_location>  admin_locations_to_send;
    //Q_EMIT signal_fill_locations_to_send(admin_locations_to_send);
    if(list_processes)
        list_processes->fill_locations_for_selected_items(admin_locations_to_send);
    else
        throw mtk::Alarm(MTK_HERE, "list_processes  not initialized.", mtk::alPriorError);


    mtk::list<mtk::admin::msg::sub_process_location>::iterator it = admin_locations_to_send.begin();
    while(it!=admin_locations_to_send.end())
    {
        mtk::msg::sub_request_r request_code(MTK_SS(mtk::rand()));
        //  subscription to multiresponse
        MTK_RECEIVE_MULTI_RESPONSE_THIS(mtk::admin::msg::command_response,
                                        mtk::admin::msg::sub_command_rd,
                                        qpid_admin_session,
                                        mtk::admin::msg::command_response::get_in_subject(request_code.request_code),
                                        on_command_response)

        mtk::admin::msg::command command_request_msg(request_code, *it,  command.toStdString());
        mtk::send_message(qpid_admin_session, command_request_msg);
        if(write_into)
            write_into->appendPlainText(MTK_SS(std::endl << std::endl << std::endl << "SENDING COMMAND  "
                                               << command.toStdString() << "  -->  " << it->location << "  "
                                               << it->machine  << "  "
                                               << it->process_name << "  "
                                               << it->process_uuid
                                               << std::endl << "--------------------------------------------------------------").c_str());
        else
            throw mtk::Alarm(MTK_HERE, "write_into not initialized.", mtk::alPriorError);
        ++it;
    }
}


void QPlainTextEditCommand::on_command_response (const mtk::list<mtk::admin::msg::command_response>& responses)
{
    std::string result;
    mtk::list<mtk::admin::msg::command_response>::const_iterator it = responses.begin();
    while(it != responses.end())
    {
        const mtk::admin::msg::command_response& response = *it;
        result += response.response_data.text;
        ++it;
    }
    if(write_into)
        write_into->appendPlainText(result.c_str());
    else
        throw mtk::Alarm(MTK_HERE, "write_into not initialized.", mtk::alPriorError);
}


void QPlainTextEditCommand::init(QPlainTextEdit *_write_into, QListProcesses* _list_processes, mtk::CountPtr< mtk::qpid_session > _qpid_admin_session)
{
    write_into      = _write_into;
    list_processes  = _list_processes;
    qpid_admin_session = _qpid_admin_session;
}
