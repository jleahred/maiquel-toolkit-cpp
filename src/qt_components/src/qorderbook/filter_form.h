#ifndef FILTER_FORM_H
#define FILTER_FORM_H

#include <QDialog>
#include <QAbstractButton>


namespace Ui {
    class filter_form;
}




struct  filter_data
{
    filter_data() : liveFilter(lfAll) {};
    QString   name;
    QString   client_code;
    QString   market;
    QString   product;
    QString   account;

    enum enLiveFilter { lfAll, lfLive, lfLiveExecuted };
    enLiveFilter  liveFilter;

};



class filter_form : public QWidget
{
    Q_OBJECT

public:
    explicit filter_form(QWidget *parent = 0);
    ~filter_form();

    void set_filter_conf(const filter_data& fd);

private:
    Ui::filter_form *ui;

    filter_data  fd;

    void showEvent(QShowEvent *);
    void keyPressEvent(QKeyEvent *);

    void set_status_filter_not_modified(void);

signals:
    void signal_filter_modified(const filter_data& fd);


private slots:
    void filter_modified(void);
    void slot_button_pressed(QAbstractButton*);
};

#endif // FILTER_FORM_H
