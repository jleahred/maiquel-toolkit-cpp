#include "qlistprocesses.h"

#include <QMouseEvent>


namespace {

    const mtk::dtTimeQuantity starting_time = mtk::dtSeconds(40);


    QString get_composed_name(const mtk::msg::sub_process_info& l)
    {
        return MTK_SS(l.location.client_code << "." << l.location.machine << "." << l.process_name).c_str();
    }

};




QListProcesses::QListProcesses(QWidget *parent) :
    QListWidget(parent),
    started_application(mtk::dtNowLocal())
{

}

void QListProcesses::init(mtk::CountPtr<mtk::qpid_session> qpid_admin_session)
{

    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_enter,
                            qpid_admin_session->url,
                            qpid_admin_session->address,
                            mtk::admin::msg::pub_enter::get_in_subject(),
                            mtk::admin::msg::pub_enter,
                            on_enter_received)

    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_exit,
                            qpid_admin_session->url,
                            qpid_admin_session->address,
                            mtk::admin::msg::pub_exit::get_in_subject(),
                            mtk::admin::msg::pub_exit,
                            on_exit_received)

    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_client_ka,
                            qpid_admin_session->url,
                            qpid_admin_session->address,
                            mtk::admin::msg::pub_keep_alive_clients::get_in_subject(),
                            mtk::admin::msg::pub_keep_alive_clients,
                            on_ka_client_received)

    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_server_ka,
                            qpid_admin_session->url,
                            qpid_admin_session->address,
                            mtk::admin::msg::pub_keep_alive_srv::get_in_subject(),
                            mtk::admin::msg::pub_keep_alive_srv,
                            on_ka_server_received)


    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_alarm,
                            qpid_admin_session->url,
                            qpid_admin_session->address,
                            mtk::admin::msg::pub_alarm::get_in_subject(),
                            mtk::admin::msg::pub_alarm,
                            on_alarm_received)



    MTK_TIMER_1S(check_ka)
}



class QListWidgetItem_ka  : public QListWidgetItem
{
public:
    QListWidgetItem_ka(QString text, QListWidget* parent, mtk::dtDateTime   _next_ka, const mtk::msg::sub_process_info& l)
        :     QListWidgetItem(text, parent)
            , next_ka(mtk::make_nullable(_next_ka))
            , process_info(l)
    {}

    mtk::nullable<mtk::dtDateTime>                  next_ka;
    const mtk::msg::sub_process_info                process_info;

private:
};



void QListProcesses::on_enter_received(const mtk::admin::msg::pub_enter& msg)
{
    QListWidgetItem_ka* item = find_item(msg.process_info);
    if(item!=0)
    {
        if(item->next_ka.HasValue())
            signal_alarm.emit(mtk::Alarm(MTK_HERE, "monitor","received enter on a client already registered", mtk::alPriorError, mtk::alTypeNoPermisions));
        else
            signal_alarm.emit(mtk::Alarm(MTK_HERE, "monitor","RE-ENTER process with keep alive lost", mtk::alPriorError, mtk::alTypeNoPermisions));
        item->next_ka = mtk::dtNowLocal() + msg.ka_interval_check;
        item->setBackgroundColor(Qt::white);
    }
    else
    {
        QListWidgetItem_ka* new_item = new QListWidgetItem_ka(get_composed_name(msg.process_info), this, mtk::dtNowLocal() + msg.ka_interval_check, msg.process_info);
        new_item->setCheckState(Qt::Unchecked);
        addItem(new_item);
    }
}


void QListProcesses::on_exit_received (const mtk::admin::msg::pub_exit& msg)
{
    QListWidgetItem_ka* item = find_item(msg.process_info);
    if(item==0)
        signal_alarm.emit(mtk::Alarm(MTK_HERE, "monitor","received exit on a non registered client", mtk::alPriorError, mtk::alTypeNoPermisions));
    else
        delete item;
}


void QListProcesses::on_ka_client_received   (const mtk::admin::msg::pub_keep_alive_clients& msg)
{
    QListWidgetItem_ka* item = find_item(msg.process_info);
    if(item==0)
    {
        if ((mtk::dtNowLocal() - started_application) > starting_time)
            signal_alarm.emit(mtk::Alarm(MTK_HERE, "monitor","received keep alive  on a non registered client", mtk::alPriorError, mtk::alTypeNoPermisions));
        QListWidgetItem_ka* new_item = new QListWidgetItem_ka(get_composed_name(msg.process_info), this, mtk::dtNowLocal() + msg.ka_interval_check, msg.process_info);
        new_item->setCheckState(Qt::Unchecked);
        addItem(new_item);
    }
    else
    {
        if (item->next_ka.HasValue() == false)
        {
            signal_alarm.emit(mtk::Alarm(MTK_HERE, "monitor","recovered keep alive", mtk::alPriorError, mtk::alTypeNoPermisions));
            item->setBackgroundColor(Qt::white);
        }
        item->next_ka = mtk::dtNowLocal() + msg.ka_interval_check;
    }
}

void QListProcesses::on_ka_server_received   (const mtk::admin::msg::pub_keep_alive_srv& msg)
{
    QListWidgetItem_ka* item = find_item(msg.process_info);
    if(item==0)
    {
        if ((mtk::dtNowLocal() - started_application) > starting_time)
            signal_alarm.emit(mtk::Alarm(MTK_HERE, "monitor","received keep alive  on a non registered client", mtk::alPriorError, mtk::alTypeNoPermisions));
        QListWidgetItem_ka* new_item = new QListWidgetItem_ka(get_composed_name(msg.process_info), this, mtk::dtNowLocal() + msg.ka_interval_check, msg.process_info);
        new_item->setCheckState(Qt::Unchecked);
        addItem(new_item);
    }
    else
    {
        if (item->next_ka.HasValue() == false)
        {
            signal_alarm.emit(mtk::Alarm(MTK_HERE, "monitor","recovered keep alive", mtk::alPriorError, mtk::alTypeNoPermisions));
            item->setBackgroundColor(Qt::white);
        }
        item->next_ka = mtk::dtNowLocal() + msg.ka_interval_check;
    }
}

void QListProcesses::check_ka(void)
{
    for(int i=0;i<this->count();i++){
        QListWidgetItem_ka* itka = dynamic_cast<QListWidgetItem_ka*>(this->item(i));
        if(itka)
        {
            if(itka->next_ka.HasValue())
            {
                if(itka->next_ka.Get() < mtk::dtNowLocal())
                {
                        signal_alarm.emit(mtk::Alarm(MTK_HERE, "monitor",MTK_SS(get_composed_name(itka->process_info).toStdString()
                                                                      << "." << itka->process_info.process_uuid
                                                                      << "  lost keep alive"), mtk::alPriorError, mtk::alTypeNoPermisions));
                        itka->setBackgroundColor(Qt::red);
                        itka->next_ka = mtk::nullable<mtk::DateTime>();
                }
                else
                {
                    itka->setBackgroundColor(Qt::white);
                }
            }
        }
    }
}


QListWidgetItem_ka*  QListProcesses::find_item(const mtk::msg::sub_process_info& l)
{
    for(int i=0;i<this->count();i++)
    {
        QListWidgetItem_ka* itka = dynamic_cast<QListWidgetItem_ka*>(this->item(i));
        if(itka  &&  itka->process_info == l)
            return itka;
    }
    return 0;
}

void  QListProcesses::check_alarm_received(const mtk::msg::sub_process_info& pi)
{
    MTK_EXEC_MAX_FREC(mtk::dtSeconds(5))
        QListWidgetItem_ka* item = this->find_item(pi);
        if(item==0  &&  (mtk::dtNowLocal() - started_application) > starting_time)
            signal_alarm.emit(mtk::Alarm(MTK_HERE, "monitor",MTK_SS("Receiving alarms with no keep alive  " << pi), mtk::alPriorError, mtk::alTypeNoPermisions));
    MTK_END_EXEC_MAX_FREC
}


void  QListProcesses::fill_process_info_for_selected_items(mtk::list<mtk::msg::sub_process_info> &pinfo2fill) const
{
    for(int i=0;i<this->count();i++)
    {
        QListWidgetItem_ka* itka = dynamic_cast<QListWidgetItem_ka*>(this->item(i));
        if(itka)
        {
            if(itka->checkState() == Qt::Checked)
            {
                pinfo2fill.push_back(itka->process_info);
            }
        }
    }
}

void QListProcesses::on_alarm_received(const mtk::admin::msg::pub_alarm& alarm_msg)
{
    check_alarm_received(alarm_msg.process_info);
}

void QListProcesses::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->modifiers() &&  Qt::ControlModifier)
    {
        for(int i=0;i<this->count();i++)
        {
            QListWidgetItem_ka* itka = dynamic_cast<QListWidgetItem_ka*>(this->item(i));
            if(itka)
            {
                if(itka->next_ka.HasValue() ==false)
                    delete itka;
            }
        }
    }
}
