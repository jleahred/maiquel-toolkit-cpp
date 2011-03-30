#include <QtGui/QApplication>
#include "mainwindow.h"


#include "components/admin/admin.h"



namespace
{

    const char*   APP_NAME          = "ex_send_order";
    const char*   APP_VER           = "2011-03-16";
    const char*   APP_DESCRIPTION   = "This is a testing market.\n";
    const char*   APP_MODIFICATIONS = "testing application, no modifications details";
}



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

    try
    {
        if(argc==1)
            mtk::admin::init("../etc/config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);

        MTK_Qt_ExceptionCatcher a(argc, argv);                  // <3>
        MainWindow w;
        a.signalOnAlarm.connect(&w, &MainWindow::OnAlarm);      // <4>
        w.show();
        return a.exec();
    }
    MTK_CATCH_CALLFUNCION(std::cerr << , MTK_HERE, "initializing application");
}
