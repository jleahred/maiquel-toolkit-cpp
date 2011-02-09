#include <QtGui/QApplication>
#include "mw_logview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MW_LogView w;
    w.show();
    return a.exec();
}
