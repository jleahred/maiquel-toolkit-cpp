#ifndef WEXECSHISTREPORT_H
#define WEXECSHISTREPORT_H

#include <QDialog>
#include <QDate>

#include "components/trading/trd_cli_support.h"
#include "components/msg_common.h"
#include "support/signalslot.hpp"
#include "support/list.hpp"



namespace Ui {
    class WExecsHistReport;
}

class WExecsHistReport : public QDialog,  public  mtk::SignalReceptor
{
    Q_OBJECT

public:
    explicit WExecsHistReport(QWidget *parent = 0);
    ~WExecsHistReport();

    void process_execution(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec);


private:
    Ui::WExecsHistReport *ui;
    mtk::list<mtk::trd::msg::CF_EXLK>  list_execs;

    void  reactivate_request_button(const int&);
    void  subscribe_response(const mtk::msg::sub_request_id&  request_id);
    void  on_cf_ex_hist(const mtk::trd::msg::CF_EX_HIST&  ex_hist);

private slots:
    void on_pb_copy_clicked();
    void on_filter_product_currentIndexChanged(QString value);
    void on_dateEdit_dateChanged(QDate date);
    void on_pb_request_clicked();
};



namespace execs_hist_report
{
    void show(void);
};



#endif // WEXECSHISTREPORT_H
