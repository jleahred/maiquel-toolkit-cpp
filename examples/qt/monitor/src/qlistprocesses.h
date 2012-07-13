#ifndef QLISTPROCESSES_H
#define QLISTPROCESSES_H

#include <QListWidget>


#include "support/date_time.h"
#include "mtk_qpid/mtk_qpid.h"
#include "components/admin/msg_admin.h"




class QListWidgetItem_ka;


class QListProcesses : public QListWidget  , public mtk::SignalReceptor
{
    Q_OBJECT
public:
    explicit QListProcesses(QWidget *parent = 0);

    void init(const mtk::t_qpid_url& url,  const std::string&  cli_srv);


    mtk::Signal<const mtk::Alarm&>    signal_alarm;

    void  fill_process_info_for_selected_items(mtk::list<mtk::msg::sub_process_info>&  pinfo2fill) const;


signals:
    void  signal_status_tip(const QString& status_tip);

public slots:

private slots:


private:
    mtk::dtDateTime   started_application;
    QString           cli_srv;

    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_enter>      >          hqpid_enter;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_keep_alive_srv> >      hqpid_server_ka;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_keep_alive_cli> >      hqpid_client_ka;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_exit>       >          hqpid_exit;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_alarm>      >          hqpid_alarm;

    void on_enter_received      (const mtk::admin::msg::pub_enter& msg);
    void on_exit_received       (const mtk::admin::msg::pub_exit& msg);
    void on_ka_client_received  (const mtk::admin::msg::pub_keep_alive_cli& msg);
    void on_ka_server_received  (const mtk::admin::msg::pub_keep_alive_srv& msg);

    void check_ka(void);

    QListWidgetItem_ka*  find_item(const mtk::msg::sub_process_info& l);

    void  check_alarm_received(const mtk::msg::sub_process_info& l);
    void  on_alarm_received(const mtk::admin::msg::pub_alarm& alarm_msg);

    void mouseDoubleClickEvent(QMouseEvent *event);

    void set_status_tool_tip(void);

};

#endif // QLISTPROCESSES_H
