#include <QtGui/QApplication>
#include "monitor.h"
#include <QMessageBox>



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



namespace mtk{
std::string  get_cli_srv(void)
{
    return  "CLI";
}
};



int main(int argc, char *argv[])
{
    QApplication::setStyle("cleanlooks");


    //QApplication a(argc, argv);
    MTK_Qt_ExceptionCatcher a(argc, argv);

    if(argc != 2)
    {
        QMessageBox(QMessageBox::Critical, "Error", "Expected one param with configuration file").exec();
        return -1;
    }
    Monitor w(argv[1]);
    a.signalOnAlarm.connect(&w, &Monitor::OnAlarm);
    //w.show();

    return a.exec();
}
