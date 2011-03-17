#ifndef QLISTPROCESSES_H
#define QLISTPROCESSES_H

#include <QListWidget>


#include "support/date_time.h"
#include "mtk_qpid/mtk_qpid.hpp"
#include "components/admin/msg_admin.h"




class QListWidgetItem_ka;


class QListProcesses : public QListWidget  , public mtk::SignalReceptor
{
    typedef  QListProcesses  CLASS_NAME;
    Q_OBJECT
public:
    explicit QListProcesses(QWidget *parent = 0);

    void init(mtk::CountPtr< mtk::qpid_session >  qpid_admin_session);


    mtk::Signal<const mtk::Alarm&>    signal_alarm;

    void  fill_process_info_for_selected_items(mtk::list<mtk::msg::sub_process_info>&  pinfo2fill) const;


signals:

public slots:



private:
    mtk::dtDateTime   started_application;

    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_enter>      > hqpid_client_enter;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_keep_alive> > hqpid_client_ka;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_exit>       > hqpid_client_exit;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_alarm>      > hqpid_client_alarm;

    void on_enter_client_received(const mtk::admin::msg::pub_enter& msg);
    void on_exit_client_received (const mtk::admin::msg::pub_exit& msg);
    void on_ka_client_received   (const mtk::admin::msg::pub_keep_alive& msg);

    void check_client_ka(void);

    QListWidgetItem_ka*  find_item(const mtk::msg::sub_process_location& l);

    void  check_alarm_received(const mtk::msg::sub_process_info& l);
    void  on_client_alarm_received(const mtk::admin::msg::pub_alarm& alarm_msg);

};

#endif // QLISTPROCESSES_H
