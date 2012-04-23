#ifndef WEXECSREPORT_H
#define WEXECSREPORT_H

#include <QDialog>

#include "components/trading/trd_cli_support.h"
#include "support/signalslot.hpp"


namespace Ui {
    class WExecsReport;
}

class WExecsReport : public QDialog,  public  mtk::SignalReceptor
{
    Q_OBJECT
    typedef WExecsReport  CLASS_NAME;

public:
    explicit WExecsReport(QWidget *parent = 0);
    ~WExecsReport();

    void on_new_execution(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec);


private:
    Ui::WExecsReport *ui;
};

#endif // WEXECSREPORT_H
