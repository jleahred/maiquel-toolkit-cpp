#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>






namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    typedef     MainWindow  CLASS_NAME;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;



private slots:
};

#endif // MAINWINDOW_H
