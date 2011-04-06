#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QCalendarWidget>
#include <QTableWidget>
#include <QVBoxLayout>



class  contExample : public mtkContainerWidget
{
public:
    explicit contExample(QWidget *parent = 0) : mtkContainerWidget(parent)
    {
        QCalendarWidget* calendar =  new QCalendarWidget(this);        //  <1>
        QVBoxLayout* lay= new QVBoxLayout(this);                       //  <2>
        lay->addWidget(calendar);
        inserting_components_ended();                            //  <3>
    }
    ~contExample(){};

};




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //contExample* ex = new contExample(this);


    QCalendarWidget* calendar =  new QCalendarWidget(ui->mtk_contw);
    QVBoxLayout* lay= new QVBoxLayout(ui->mtk_contw);
    lay->addWidget(calendar);
    ui->mtk_contw->inserting_components_ended();

    QTableWidget* table =  new QTableWidget(ui->mtk_contw2);
    QVBoxLayout* lay2= new QVBoxLayout(ui->mtk_contw2);
    lay2->addWidget(table);
    ui->mtk_contw2->inserting_components_ended();


}

MainWindow::~MainWindow()
{
    delete ui;
}

