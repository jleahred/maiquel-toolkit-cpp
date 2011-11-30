#ifndef QTABLEALARMS_H
#define QTABLEALARMS_H

#include <QTableWidget>
#include "support/re/RegExp.h"

#include "components/admin/msg_admin.h"



class QTableAlarms : public QTableWidget, public mtk::SignalReceptor
{
    Q_OBJECT
    typedef QTableAlarms  CLASS_NAME;

public:
    explicit QTableAlarms(QWidget *parent = 0);
    void init(const mtk::t_qpid_url& url, bool _only_errors);       //  "CLI" and "SRV"
    void init(const mtk::t_qpid_url& url, const std::string&  cli_srv, bool _only_errors);
    void write_alarm(const mtk::DateTime&  received, const mtk::Alarm& alarm);

signals:
    void  signal_status_tip(const QString& status_tip);
    void  signal_show_full_message(const QString& message);
    void  signal_alarm(const mtk::admin::msg::pub_alarm& alarm_msg);

public slots:
    void  slot_currentCellChanged(int current_row,int current_column,int,int);
    void  slot_set_filter(const QString&  filter)  {  re_filter.SetPattern(filter.toStdString()); re_filter.Compile(true);  }

private:
    QString                                                                                     cli_srv;
    bool                                                                                        only_errors;
    mtk::RegExp                                                                                 re_filter;

    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_alarm>       >     hqpid_alarm1;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_alarm>       >     hqpid_alarm2;

    void on_client_alarm_received(const mtk::admin::msg::pub_alarm& alarm_msg);
    void queue_alarm_msg         (const mtk::DateTime&  received,  const mtk::admin::msg::pub_alarm& alarm_msg);
    void write_alarm_msg2        (const mtk::DateTime&  received,  const mtk::admin::msg::pub_alarm& alarm_msg);

    void mouseDoubleClickEvent(QMouseEvent *event);

    void timer_check_number_of_rows(void);

    mtk::list< mtk::tuple<mtk::DateTime, mtk::admin::msg::pub_alarm> >       last_alarms;
    mtk::list< mtk::tuple<mtk::DateTime, mtk::admin::msg::pub_alarm> >       queued_alarms;
    void timer_unqueue_alarms(void);
    void timer_check_last_alarms_received(void);
    void prepare();

    bool pass_filter(const QString& full_text_message);

};

#endif // QTABLEALARMS_H
