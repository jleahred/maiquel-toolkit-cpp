#include "qtablealarms.h"

#include <QHeaderView>
#include <QMouseEvent>
#include <QScrollBar>


#include "yaml/mtkemitter.h"



QTableAlarms::QTableAlarms(QWidget *parent) :
    QTableWidget(parent)
{
    connect(this, SIGNAL(currentCellChanged(int,int,int,int)), this, SLOT(slot_currentCellChanged(int,int,int,int)));
}

void QTableAlarms::init(const mtk::t_qpid_url& url, const std::string& _cli_srv, bool _only_errors)
{
    only_errors = _only_errors;
    cli_srv = QString(_cli_srv.c_str());

    prepare();


    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_alarm1,
                            url,
                            mtk::admin::msg::pub_alarm::get_in_subject("*", _cli_srv),
                            mtk::admin::msg::pub_alarm,
                            on_alarm_received);
}

void QTableAlarms::prepare(void)
{
    setRowCount(0);
    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(true);
    verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    horizontalHeader()->setStretchLastSection(true);

    setColumnCount(7);

    #define QTABLE_ALARMS_INIT_HEADER_ITEM(__COLUMN__, __TEXT__) \
    {   \
        item = new QTableWidgetItem(); \
        item->setForeground(QBrush(QColor(30,0,100)));  \
        item->setText(__TEXT__);   \
        setHorizontalHeaderItem(__COLUMN__, item);   \
    }

    {
        QTableWidgetItem *item=0;
        QFont font(this->font());
        font.setBold(true);
        //font.setPointSize(11);
        int counter=0;
        QTABLE_ALARMS_INIT_HEADER_ITEM(counter++, "time (rec)")
        QTABLE_ALARMS_INIT_HEADER_ITEM(counter++, "from")
        //QTABLE_ALARMS_INIT_HEADER_ITEM(counter++, "priority")
        QTABLE_ALARMS_INIT_HEADER_ITEM(counter++, "id")
        QTABLE_ALARMS_INIT_HEADER_ITEM(counter++, "subject")
        QTABLE_ALARMS_INIT_HEADER_ITEM(counter++, "message")
        QTABLE_ALARMS_INIT_HEADER_ITEM(counter++, "type")
        QTABLE_ALARMS_INIT_HEADER_ITEM(counter++, "gen.time")
    }
    int counter=0;
    horizontalHeader()->resizeSection(counter++, 105);
    horizontalHeader()->resizeSection(counter++, 100);
    //horizontalHeader()->resizeSection(counter++, 100);
    horizontalHeader()->resizeSection(counter++, 30);
    horizontalHeader()->resizeSection(counter++, 100);
    horizontalHeader()->resizeSection(counter++, 900);
    horizontalHeader()->resizeSection(counter++, 100);
    horizontalHeader()->resizeSection(counter++, 100);

    MTK_TIMER_1S(timer_check_number_of_rows);
    MTK_TIMER_1S(timer_check_last_alarms_received);
    MTK_TIMER_1D(timer_unqueue_alarms);
}


void QTableAlarms::on_alarm_received(const mtk::admin::msg::pub_alarm&  alarm_msg)
{
    if(only_errors  &&  !(alarm_msg.priority==mtk::alPriorCritic  ||  alarm_msg.priority==mtk::alPriorError))
        return;
    else
    {
        mtk::DateTime  now = mtk::dtNowLocal();
        last_alarms.push_back(mtk::make_tuple(now, alarm_msg));
        queue_alarm_msg(now, alarm_msg);
    }
}


void QTableAlarms::queue_alarm_msg         (const mtk::DateTime&  received,  const mtk::admin::msg::pub_alarm& alarm_msg)
{
    queued_alarms.push_back(mtk::make_tuple(received, alarm_msg));
}

void QTableAlarms::timer_unqueue_alarms(void)
{
    if(queued_alarms.size()==0)
    {
        signal_status_tip(QString(cli_srv) + QString::number(only_errors) + ":" + QString("  rc") + QString::number(this->rowCount())  + QString("  qa") + QString::number(queued_alarms.size()));
        return;
    }


    MTK_EXEC_MAX_FREC(mtk::dtMilliseconds(200))
        this->setUpdatesEnabled(false);
        for(int i=0; i<3; ++i)
        {
            if(queued_alarms.size() == 0)       break;
            auto tuple_rec_alarmmsg = queued_alarms.front();
            queued_alarms.pop_front();
            write_alarm_msg2(tuple_rec_alarmmsg._0, tuple_rec_alarmmsg._1);
        }
        this->setUpdatesEnabled(true);
        signal_status_tip(QString(cli_srv) + QString::number(only_errors) + ":" + QString("  rc") + QString::number(this->rowCount())  + QString("  qa") + QString::number(queued_alarms.size()));
    MTK_END_EXEC_MAX_FREC
}


class  QTableWidgetItem_full_alarm_msg  : public   QTableWidgetItem
{
public:

    const QString    full_message;

    QTableWidgetItem_full_alarm_msg(const QString&  _full_text_message)
        : QTableWidgetItem(), full_message(_full_text_message)
    {
    }
};


void QTableAlarms::write_alarm_msg2         (const mtk::DateTime&  received, const mtk::admin::msg::pub_alarm& alarm_msg)
{
    QString  full_text_message = QString(YAML::string_from_yaml(alarm_msg).c_str());

    mtk::alEnPriority  priority = filter_alarm_priority(alarm_msg.priority, full_text_message);
    //if(cli_srv == ""  &&  only_errors &&  (priority!=mtk::alPriorCritic  &&  priority!=mtk::alPriorError))
    if(only_errors &&  (priority!=mtk::alPriorCritic  &&  priority!=mtk::alPriorError))
        return;

    signal_alarm(alarm_msg);

    if(cli_srv != ""  &&  pass_filter(full_text_message)  == false)
        return;


    bool go_to_bottom=false;
    if(this->visualItemRect(this->item(this->rowCount()-1, 0)).top() < this->height()-this->horizontalHeader()->height()-this->horizontalScrollBar()->height())
        go_to_bottom = true;

    this->insertRow(this->rowCount());
    int last_row = this->rowCount()-1;

    //this->insertRow(0);
    //int last_row = 0;

    QColor back_color = Qt::white;
    QColor foregroud_color = Qt::black;



    if(priority == mtk::alPriorCritic)
    {
        back_color = Qt::red;
        foregroud_color = Qt::white;
    }
    else if(priority == mtk::alPriorError)
    {
        back_color = Qt::white;
        foregroud_color = Qt::red;
    }

    int column=-1;
    {
        QTableWidgetItem_full_alarm_msg* new_item = new QTableWidgetItem_full_alarm_msg(full_text_message);
        new_item->setText(MTK_SS(received).substr(11).c_str());
        new_item->setBackgroundColor(back_color);
        new_item->setForeground(QBrush(foregroud_color));
        this->setItem(last_row, ++column, new_item);
    }

    if(cli_srv == "CLI")
    {
        QTableWidgetItem* new_item = new QTableWidgetItem();
        new_item->setText(MTK_SS(alarm_msg.process_info.location.broker_code << "."
                                    << alarm_msg.process_info.location.machine << "."
                                    << alarm_msg.process_info.process_name).c_str());
        new_item->setBackgroundColor(back_color);
        new_item->setForeground(QBrush(foregroud_color));
        this->setItem(last_row, ++column, new_item);
    }
    else if (cli_srv == "SRV")
    {
        QTableWidgetItem* new_item = new QTableWidgetItem();
        new_item->setText(MTK_SS(alarm_msg.process_info.location.broker_code << "." << alarm_msg.process_info.process_name).c_str());
        new_item->setBackgroundColor(back_color);
        new_item->setForeground(QBrush(foregroud_color));
        this->setItem(last_row, ++column, new_item);
    }
    else
    {
        QTableWidgetItem* new_item = new QTableWidgetItem();
        new_item->setText(MTK_SS(alarm_msg.process_info.location.broker_code << "."
                                    << alarm_msg.process_info.location.machine << "."
                                    << alarm_msg.process_info.process_name << "."
                                    << alarm_msg.process_info.process_uuid << "."
                                    << alarm_msg.process_info.version  ).c_str());
        new_item->setBackgroundColor(back_color);
        new_item->setForeground(QBrush(foregroud_color));
        this->setItem(last_row, ++column, new_item);
    }

    /*
    {
        QTableWidgetItem* new_item = new QTableWidgetItem();
        new_item->setText(MTK_SS(alarm_msg.priority).c_str());
        new_item->setBackgroundColor(back_color);
        new_item->setForeground(QBrush(foregroud_color));
        this->setItem(last_row, ++column, new_item);
    }
    */

    {
        QTableWidgetItem* new_item = new QTableWidgetItem();
        new_item->setText(MTK_SS(alarm_msg.alarm_id).c_str());
        new_item->setBackgroundColor(back_color);
        new_item->setForeground(QBrush(foregroud_color));
        this->setItem(last_row, ++column, new_item);
    }

    {

        QTableWidgetItem* new_item = new QTableWidgetItem();
        new_item->setText(MTK_SS(alarm_msg.subject).c_str());
        new_item->setBackgroundColor(back_color);
        new_item->setForeground(QBrush(foregroud_color));
        this->setItem(last_row, ++column, new_item);

    }

    {
        QTableWidgetItem* new_item = new QTableWidgetItem();
        if(alarm_msg.message.size() > 80)
            new_item->setText(MTK_SS(alarm_msg.message.substr(0, 80) <<  " ...").c_str());
        else
            new_item->setText(alarm_msg.message.c_str());
        new_item->setBackgroundColor(back_color);
        new_item->setForeground(QBrush(foregroud_color));
        this->setItem(last_row, ++column, new_item);
    }

    {
        QTableWidgetItem* new_item = new QTableWidgetItem();
        new_item->setText(MTK_SS(alarm_msg.type).c_str());
        new_item->setBackgroundColor(back_color);
        new_item->setForeground(QBrush(foregroud_color));
        this->setItem(last_row, ++column, new_item);
    }

    {
        QTableWidgetItem* new_item = new QTableWidgetItem();
        new_item->setText(MTK_SS(alarm_msg.dateTime_generated).substr(11).c_str());
        new_item->setBackgroundColor(back_color);
        new_item->setForeground(QBrush(foregroud_color));
        this->setItem(last_row, ++column, new_item);
    }

    if(go_to_bottom)
        this->verticalScrollBar()->setSliderPosition(verticalScrollBar()->maximum());
}




void QTableAlarms::write_alarm(const mtk::DateTime&  received,  const mtk::Alarm& alarm)
{
    mtk::admin::msg::pub_alarm alarm_msg(mtk::msg::sub_process_info(mtk::msg::sub_location("LOCAL", "LOCAL"), "LOCAL", "LOCAL", "LOCAL", std::string("CLI")),
                                     alarm.codeSource, "monitor", alarm.message, alarm.priority, alarm.type, received, -1);

    queue_alarm_msg(received, alarm_msg);

    std::list<mtk::BaseAlarm>::const_iterator it = alarm.stackAlarms.begin();
    while (it != alarm.stackAlarms.end())
    {
        mtk::admin::msg::pub_alarm alarm_msg(mtk::msg::sub_process_info(mtk::msg::sub_location("LOCAL", "LOCAL"), "LOCAL", "LOCAL", "LOCAL", std::string("CLI")),
                                         "monitor", it->codeSource, it->message, it->priority, it->type, received, -1);
        queue_alarm_msg(received, alarm_msg);
        ++it;
    }
}

void QTableAlarms::init(const mtk::t_qpid_url& url, bool _only_errors)
{
    only_errors = _only_errors;

    prepare();


    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_alarm1,
                            url,
                            mtk::admin::msg::pub_alarm::get_in_subject("*", "CLI"),
                            mtk::admin::msg::pub_alarm,
                            on_alarm_received);
    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_alarm2,
                            url,
                            mtk::admin::msg::pub_alarm::get_in_subject("*", "SRV"),
                            mtk::admin::msg::pub_alarm,
                            on_alarm_received);
}


void QTableAlarms::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->modifiers() &&  Qt::ControlModifier)
    {
        this->setRowCount(0);
        mtk::list< mtk::tuple<mtk::DateTime, mtk::admin::msg::pub_alarm> >::iterator it=last_alarms.begin();
        for(; it!=last_alarms.end(); ++it)
        {
            if((it->_0 + mtk::dtSeconds(8)) > mtk::dtNowLocal())
                queue_alarm_msg(it->_0, it->_1);
        }
    }
}


void QTableAlarms::timer_check_number_of_rows(void)
{
    MTK_EXEC_MAX_FREC(mtk::dtSeconds(30))
        if(this->rowCount() > 500)
        {
            this->setUpdatesEnabled(false);
            while(this->rowCount() > 250)
                this->removeRow(0);
            this->setUpdatesEnabled(true);
        }
    MTK_END_EXEC_MAX_FREC
}

void QTableAlarms::timer_check_last_alarms_received(void)
{
    MTK_EXEC_MAX_FREC(mtk::dtSeconds(45))
        while(last_alarms.size()>0   &&  last_alarms.front()._0 + mtk::dtSeconds(8) < mtk::dtNowLocal())
                last_alarms.pop_front();
    MTK_END_EXEC_MAX_FREC
}


void  QTableAlarms::slot_currentCellChanged(int current_row,int ,int,int)
{
    QTableWidgetItem_full_alarm_msg*  it_msg =  dynamic_cast<QTableWidgetItem_full_alarm_msg*>(this->item(current_row, 0));
    if(it_msg==0)
        signal_show_full_message("nope");
    else
        signal_show_full_message( it_msg->full_message);
}

bool QTableAlarms::pass_filter(const QString& full_text_message)
{
    if (re_filter.Match(full_text_message.toStdString()))
        return true;
    else
        return false;
}
