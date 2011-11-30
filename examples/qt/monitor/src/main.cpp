#include <QtGui/QApplication>
#include "monitor.h"




//-------------------------------------------------------------------------------
//      P R E P A R I N G     M T K
//-------------------------------------------------------------------------------
    #include "support/alarm.h"
    #include "support/signalslot.hpp"

    class MTK_Qt_ExceptionCatcher : public QApplication
    {
    public:
        MTK_Qt_ExceptionCatcher(int& _argc, char *_argv[]) :  QApplication(_argc, _argv) {};

        bool notify ( QObject * receiver, QEvent * event )
        {
            try
            {
                return QApplication::notify(receiver, event);
            }
            MTK_CATCH_CALLFUNCION (ProcessException  , "main", "")

            return false;
        }
        void ProcessException (const mtk::Alarm& alarm)
        {
            signalOnAlarm.emit(alarm);
        }
        mtk::Signal<const mtk::Alarm&>     signalOnAlarm;
    };
//-------------------------------------------------------------------------------
//      P R E P A R I N G     M T K
//-------------------------------------------------------------------------------







int main(int argc, char *argv[])
{
    QApplication::setStyle("cleanlooks");


    //QApplication a(argc, argv);
    MTK_Qt_ExceptionCatcher a(argc, argv);

    Monitor w;
    a.signalOnAlarm.connect(&w, &Monitor::OnAlarm);
    //w.show();

    return a.exec();
}
