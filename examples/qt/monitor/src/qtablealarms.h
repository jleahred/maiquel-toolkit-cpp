#ifndef QTABLEALARMS_H
#define QTABLEALARMS_H

#include <QTableWidget>

#include "components/admin/msg_admin.h"



class QTableAlarms : public QTableWidget, public mtk::SignalReceptor
{
    Q_OBJECT
    typedef QTableAlarms  CLASS_NAME;

public:
    explicit QTableAlarms(QWidget *parent = 0);
    void init(mtk::CountPtr< mtk::qpid_session > _qpid_session, bool _only_errors);
    void init(mtk::CountPtr< mtk::qpid_session > _qpid_session1, mtk::CountPtr< mtk::qpid_session > _qpid_session2, bool _only_errors);
    void write_alarm(const mtk::Alarm& alarm);

signals:

public slots:

private:
    bool                                                                                    only_errors;

    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::alarm>       >     hqpid_alarm1;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::alarm>       >     hqpid_alarm2;

    void on_client_alarm_received(const mtk::admin::msg::alarm& alarm_msg);
    void write_alarm_msg         (const mtk::admin::msg::alarm& alarm_msg);
};

#endif // QTABLEALARMS_H
