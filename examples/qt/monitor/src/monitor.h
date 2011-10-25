#ifndef MONITOR_H
#define MONITOR_H

#include <QMainWindow>


#include "components/admin/msg_admin.h"




class Highlighter;
namespace Ui {
    class Monitor;
}



//-------------------------------------------------------------------------------
//      P R E P A R I N G     M T K
//-------------------------------------------------------------------------------
#include "support/signalslot.hpp"
#include "support/alarm.h"
#include "mtk_qpid/mtk_qpid.hpp"

class MTK_Qt_timer_and_AlarmMsg : public QObject, public mtk::SignalReceptor    // <1>
    {
        Q_OBJECT

    public:
        MTK_Qt_timer_and_AlarmMsg (QWidget *parent = 0);
        ~MTK_Qt_timer_and_AlarmMsg();

        mtk::Signal<const mtk::Alarm&>     signalAlarm;                         // <2>

    private slots:
        void check_mtk_timer();
    private:
        void process_signalAlarm (const mtk::Alarm& alarm);

    };
//-------------------------------------------------------------------------------
//      P R E P A R I N G     M T K
//-------------------------------------------------------------------------------








class Monitor : public QMainWindow,   public  mtk::SignalReceptor
{
    Q_OBJECT
    typedef Monitor  CLASS_NAME;

public:
    explicit Monitor(QWidget *parent = 0);
    ~Monitor();

    void OnAlarm(const mtk::Alarm& alarm);


private:
    Ui::Monitor *ui;


    mtk::t_qpid_url     url;

    void on_command_response (const mtk::list<mtk::admin::msg::res_command>& responses);


private slots:

};

#endif // MONITOR_H
