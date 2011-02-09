#ifndef MW_LOGVIEW_H
#define MW_LOGVIEW_H

#include <QtGui/QMainWindow>



class Highlighter;


namespace Ui
{
    class MW_LogViewClass;
}

class MW_LogView : public QMainWindow
{
    Q_OBJECT

public:
    MW_LogView(QWidget *parent = 0);
    ~MW_LogView();

private:
    Ui::MW_LogViewClass *ui;

    Highlighter* highlighter_log;

};

#endif // MW_LOGVIEW_H
