#ifndef WEXECSHISTREPORT_H
#define WEXECSHISTREPORT_H

#include <QDialog>

#include "components/trading/trd_cli_support.h"
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

private slots:
    void on_pb_request_clicked();
};



namespace execs_hist_report
{
    void show(void);
};



#endif // WEXECSHISTREPORT_H
