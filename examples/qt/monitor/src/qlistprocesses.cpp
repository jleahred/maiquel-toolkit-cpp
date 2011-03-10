#include "qlistprocesses.h"



namespace {

    const mtk::dtTimeQuantity starting_time = mtk::dtSeconds(40);


    QString get_composed_name(const mtk::admin::msg::sub_process_location& l)
    {
        return MTK_SS(l.location << "." << l.machine << "." << l.process_name).c_str();
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
                            hqpid_client_enter,
                            qpid_admin_session->url,
                            qpid_admin_session->address,
                            mtk::admin::msg::enter::get_in_subject(),
                            mtk::admin::msg::enter,
                            on_enter_client_received)

    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_client_exit,
                            qpid_admin_session->url,
                            qpid_admin_session->address,
                            mtk::admin::msg::exit::get_in_subject(),
                            mtk::admin::msg::exit,
                            on_exit_client_received)

    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_client_ka,
                            qpid_admin_session->url,
                            qpid_admin_session->address,
                            mtk::admin::msg::keep_alive::get_in_subject(),
                            mtk::admin::msg::keep_alive,
                            on_ka_client_received)


    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_client_alarm,
                            qpid_admin_session->url,
                            qpid_admin_session->address,
                            mtk::admin::msg::alarm::get_in_subject(),
                            mtk::admin::msg::alarm,
                            on_client_alarm_received)



    MTK_TIMER_1S(check_client_ka)
}



class QListWidgetItem_ka  : public QListWidgetItem
{
public:
    QListWidgetItem_ka(QString text, QListWidget* parent, mtk::dtDateTime   _next_ka, const mtk::admin::msg::sub_process_location& l)
        :     QListWidgetItem(text, parent)
            , next_ka(mtk::make_nullable(_next_ka))
            , process_location(l)
    {}

    mtk::nullable<mtk::dtDateTime>                  next_ka;
    const mtk::admin::msg::sub_process_location     process_location;

private:
};



void QListProcesses::on_enter_client_received(const mtk::admin::msg::enter& msg)
{
    QListWidgetItem_ka* item = find_item(msg.process_location);
    if(item!=0)
    {
        if(item->next_ka.HasValue())
            signal_alarm.emit(mtk::Alarm(MTK_HERE, "received enter on a client already registered", mtk::alPriorError, mtk::alTypeNoPermisions));
        else
            signal_alarm.emit(mtk::Alarm(MTK_HERE, "RE-ENTER process with keep alive lost", mtk::alPriorError, mtk::alTypeNoPermisions));
        item->next_ka = mtk::dtNowLocal() + msg.ka_interval_check;
        item->setBackgroundColor(Qt::white);
    }
    else
    {
        QListWidgetItem_ka* new_item = new QListWidgetItem_ka(get_composed_name(msg.process_location), this, mtk::dtNowLocal() + msg.ka_interval_check, msg.process_location);
        new_item->setCheckState(Qt::Unchecked);
        addItem(new_item);
    }
}


void QListProcesses::on_exit_client_received (const mtk::admin::msg::exit& msg)
{
    QListWidgetItem_ka* item = find_item(msg.process_location);
    if(item==0)
        signal_alarm.emit(mtk::Alarm(MTK_HERE, "received exit on a non registered client", mtk::alPriorError, mtk::alTypeNoPermisions));
    else
        delete item;
}


void QListProcesses::on_ka_client_received   (const mtk::admin::msg::keep_alive& msg)
{
    QListWidgetItem_ka* item = find_item(msg.process_location);
    if(item==0)
    {
        if ((mtk::dtNowLocal() - started_application) > starting_time)
            signal_alarm.emit(mtk::Alarm(MTK_HERE, "received keep alive  on a non registered client", mtk::alPriorError, mtk::alTypeNoPermisions));
        QListWidgetItem_ka* new_item = new QListWidgetItem_ka(get_composed_name(msg.process_location), this, mtk::dtNowLocal() + msg.ka_interval_check, msg.process_location);
        new_item->setCheckState(Qt::Unchecked);
        addItem(new_item);
    }
    else
    {
        if (item->next_ka.HasValue() == false)
        {
            signal_alarm.emit(mtk::Alarm(MTK_HERE, "recovered keep alive", mtk::alPriorError, mtk::alTypeNoPermisions));
            item->setBackgroundColor(Qt::white);
        }
        item->next_ka = mtk::dtNowLocal() + msg.ka_interval_check;
    }
}


void QListProcesses::check_client_ka(void)
{
    for(int i=0;i<this->count();i++){
        QListWidgetItem_ka* itka = dynamic_cast<QListWidgetItem_ka*>(this->item(i));
        if(itka)
        {
            if(itka->next_ka.HasValue())
            {
                if(itka->next_ka.Get() < mtk::dtNowLocal())
                {
                        signal_alarm.emit(mtk::Alarm(MTK_HERE, MTK_SS(get_composed_name(itka->process_location).toStdString()
                                                                      << "." << itka->process_location.process_uuid
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


QListWidgetItem_ka*  QListProcesses::find_item(const mtk::admin::msg::sub_process_location& l)
{
    for(int i=0;i<this->count();i++)
    {
        QListWidgetItem_ka* itka = dynamic_cast<QListWidgetItem_ka*>(this->item(i));
        if(itka  &&  itka->process_location == l)
            return itka;
    }
    return 0;
}

void  QListProcesses::check_alarm_received(const mtk::admin::msg::sub_process_location& l)
{
    MTK_EXEC_MAX_FREC(mtk::dtSeconds(5))
        QListWidgetItem_ka* item = this->find_item(l);
        if(item==0  &&  (mtk::dtNowLocal() - started_application) > starting_time)
            signal_alarm.emit(mtk::Alarm(MTK_HERE, MTK_SS("Receiving alarms with no keep alive  " << l), mtk::alPriorError, mtk::alTypeNoPermisions));
    MTK_END_EXEC_MAX_FREC
}


void  QListProcesses::fill_locations_for_selected_items(mtk::list<mtk::admin::msg::sub_process_location> &locations2fill) const
{
    for(int i=0;i<this->count();i++)
    {
        QListWidgetItem_ka* itka = dynamic_cast<QListWidgetItem_ka*>(this->item(i));
        if(itka)
        {
            if(itka->checkState() == Qt::Checked)
            {
                locations2fill.push_back(itka->process_location);
            }
        }
    }
}

void QListProcesses::on_client_alarm_received(const mtk::admin::msg::alarm& alarm_msg)
{
    check_alarm_received(alarm_msg.process_location);
}
