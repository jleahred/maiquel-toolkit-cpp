#ifndef WEXECSHISTREPORT_H
#define WEXECSHISTREPORT_H

#include <QDialog>
#include <QDate>

#include "components/trading/trd_cli_support.h"
#include "components/msg_common.h"
#include "support/signalslot.hpp"


namespace Ui {
    class WExecsHistReport;
}

class WExecsHistReport : public QDialog,  public  mtk::SignalReceptor
{
    Q_OBJECT
    typedef WExecsHistReport  CLASS_NAME;

public:
    explicit WExecsHistReport(QWidget *parent = 0);
    ~WExecsHistReport();

    void on_new_execution(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec);


private:
    Ui::WExecsHistReport *ui;

    void  reactivate_request_button(const int&);
    void  subscribe_response(const mtk::msg::sub_request_id&  request_id);
    void  on_cf_ex_hist(const mtk::trd::msg::CF_EX_HIST&  ex_hist);

private slots:
    void on_dateEdit_dateChanged(QDate date);
    void on_pb_request_clicked();
};



namespace execs_hist_report
{
    void show(void);
};



#endif // WEXECSHISTREPORT_H
