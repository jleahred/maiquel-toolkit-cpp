#include <QtGui/QApplication>
#include "mainwindow.h"


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
            MTK_CATCH_CALLFUNCION (ProcessException  , "main", "")      //  <1>

            return false;
        }
        void ProcessException (const mtk::Alarm& alarm)
        {
            signalOnAlarm.emit(alarm);                                              // <2>
        }
        mtk::Signal<const mtk::Alarm&>     signalOnAlarm;
    };
//-------------------------------------------------------------------------------
//      P R E P A R I N G     M T K
//-------------------------------------------------------------------------------



int main(int argc, char *argv[])
{
    MTK_Qt_ExceptionCatcher a(argc, argv);                  // <3>
    MainWindow w;
    a.signalOnAlarm.connect(&w, &MainWindow::OnAlarm);      // <4>
    w.show();

    return a.exec();
}
