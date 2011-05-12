#include "qtablealarms.h"

#include <QHeaderView>
#include <QMouseEvent>
#include <QScrollBar>



QTableAlarms::QTableAlarms(QWidget *parent) :
    QTableWidget(parent)
{
}

void QTableAlarms::init(mtk::CountPtr< mtk::qpid_session > qpid_session, bool _only_errors)
{
    only_errors = _only_errors;

    setRowCount(0);
    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(true);
    //table_marginals->setSelectionMode(QAbstractItemView::NoSelection);
    //verticalHeader()->setDefaultSectionSize(QFontMetrics(this->font()).height()*1.6);
    verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    horizontalHeader()->setStretchLastSection(true);
    //horizontalHeader()->setDefaultSectionSize(100);

    setColumnCount(8);

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
        QTABLE_ALARMS_INIT_HEADER_ITEM(counter++, "priority")
        QTABLE_ALARMS_INIT_HEADER_ITEM(counter++, "id")
        QTABLE_ALARMS_INIT_HEADER_ITEM(counter++, "subject")
        QTABLE_ALARMS_INIT_HEADER_ITEM(counter++, "message")
        QTABLE_ALARMS_INIT_HEADER_ITEM(counter++, "type")
        QTABLE_ALARMS_INIT_HEADER_ITEM(counter++, "gen.time")
    }
    int counter=0;
    horizontalHeader()->resizeSection(counter++, 105);
    horizontalHeader()->resizeSection(counter++, 100);
    horizontalHeader()->resizeSection(counter++, 100);
    horizontalHeader()->resizeSection(counter++, 30);
    horizontalHeader()->resizeSection(counter++, 100);
    horizontalHeader()->resizeSection(counter++, 1200);
    horizontalHeader()->resizeSection(counter++, 100);
    horizontalHeader()->resizeSection(counter++, 100);
    //horizontalHeader()->setMovable(true);



    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_alarm1,
                            qpid_session->url,
                            qpid_session->address,
                            mtk::admin::msg::pub_alarm::get_in_subject(),
                            mtk::admin::msg::pub_alarm,
                            on_client_alarm_received);



    MTK_TIMER_1S(timer_check_number_of_rows);
    MTK_TIMER_1S(timer_check_last_alarms_received);
}

void QTableAlarms::on_client_alarm_received(const mtk::admin::msg::pub_alarm& alarm_msg)
{
    if(only_errors  &&  !(alarm_msg.priority==mtk::alPriorCritic  ||  alarm_msg.priority==mtk::alPriorError))
        return;
    else
    {
        last_alarms.push_back(mtk::make_tuple(mtk::dtNowLocal(), alarm_msg));
        write_alarm_msg(alarm_msg);
    }
}
void QTableAlarms::write_alarm_msg         (const mtk::admin::msg::pub_alarm& alarm_msg)
{
    bool go_to_bottom=false;
    if(this->visualItemRect(this->item(this->rowCount()-1, 0)).top() < this->height()-this->horizontalHeader()->height()-this->horizontalScrollBar()->height())
        go_to_bottom = true;

    this->insertRow(this->rowCount());
    int last_row = this->rowCount()-1;

    //this->insertRow(0);
    //int last_row = 0;

    QColor back_color = Qt::white;
    QColor foregroud_color = Qt::black;


    if(alarm_msg.priority == mtk::alPriorCritic)
    {
        back_color = Qt::red;
        foregroud_color = Qt::white;
    }
    else if(alarm_msg.priority == mtk::alPriorError)
    {
        back_color = Qt::white;
        foregroud_color = Qt::red;
    }

    int column=-1;
    {
        QTableWidgetItem* new_item = new QTableWidgetItem();
        new_item->setText(MTK_SS(mtk::dtNowLocal()).substr(11).c_str());
        new_item->setBackgroundColor(back_color);
        new_item->setForeground(QBrush(foregroud_color));
        this->setItem(last_row, ++column, new_item);
    }

    {
        QTableWidgetItem* new_item = new QTableWidgetItem();
        new_item->setText(MTK_SS(alarm_msg.process_info.location.client_code << "."
                                    << alarm_msg.process_info.location.machine << "."
                                    << alarm_msg.process_info.process_name << "."
                                    << alarm_msg.process_info.process_uuid << "."
                                    << alarm_msg.process_info.version  ).c_str());
        new_item->setBackgroundColor(back_color);
        new_item->setForeground(QBrush(foregroud_color));
        this->setItem(last_row, ++column, new_item);
    }

    {
        QTableWidgetItem* new_item = new QTableWidgetItem();
        new_item->setText(MTK_SS(alarm_msg.priority).c_str());
        new_item->setBackgroundColor(back_color);
        new_item->setForeground(QBrush(foregroud_color));
        this->setItem(last_row, ++column, new_item);
    }

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
        new_item->setText(MTK_SS(alarm_msg.message).c_str());
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




void QTableAlarms::write_alarm(const mtk::Alarm& alarm)
{
    mtk::admin::msg::pub_alarm alarm_msg(mtk::msg::sub_process_info(mtk::msg::sub_location("LOCAL", "LOCAL"), "LOCAL", "LOCAL", "LOCAL"),
                                     alarm.codeSource, "monitor", alarm.message, alarm.priority, alarm.type, mtk::dtNowLocal(), -1);

    write_alarm_msg(alarm_msg);

    std::list<mtk::BaseAlarm>::const_iterator it = alarm.stackAlarms.begin();
    while (it != alarm.stackAlarms.end())
    {
        mtk::admin::msg::pub_alarm alarm_msg(mtk::msg::sub_process_info(mtk::msg::sub_location("LOCAL", "LOCAL"), "LOCAL", "LOCAL", "LOCAL"),
                                         "monitor", it->codeSource, it->message, it->priority, it->type, mtk::dtNowLocal(), -1);
        write_alarm_msg(alarm_msg);
        ++it;
    }
}

void QTableAlarms::init(mtk::CountPtr< mtk::qpid_session > qpid_session1, mtk::CountPtr< mtk::qpid_session > qpid_session2, bool only_errors)
{
    init(qpid_session1, only_errors);
    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_alarm2,
                            qpid_session2->url,
                            qpid_session2->address,
                            mtk::admin::msg::pub_alarm::get_in_subject(),
                            mtk::admin::msg::pub_alarm,
                            on_client_alarm_received)

}


void QTableAlarms::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->modifiers() &&  Qt::ControlModifier)
    {
        this->setRowCount(0);
        mtk::list< mtk::tuple<mtk::DateTime, mtk::admin::msg::pub_alarm> >::iterator it=last_alarms.begin();
        for(; it!=last_alarms.end(); ++it)
        {
            std::cout << it->_1 << std::endl;
            write_alarm_msg(it->_1);
        }
    }
}


void QTableAlarms::timer_check_number_of_rows(void)
{
    MTK_EXEC_MAX_FREC(mtk::dtSeconds(45))
        if(this->rowCount() > 1000)
            this->setRowCount(500);
    MTK_END_EXEC_MAX_FREC
}

void QTableAlarms::timer_check_last_alarms_received(void)
{
    MTK_EXEC_MAX_FREC(mtk::dtSeconds(45))
        while(last_alarms.size()>0   &&  last_alarms.front()._0 + mtk::dtSeconds(15) < mtk::dtNowLocal())
                last_alarms.pop_front();
    MTK_END_EXEC_MAX_FREC
}
