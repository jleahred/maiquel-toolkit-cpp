#include "filter_form.h"
#include "ui_filter_form.h"


#include <QPushButton>
#include <QKeyEvent>


#include <iostream>



filter_form::filter_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::filter_form)
{
    ui->setupUi(this);
    set_status_filter_not_modified();
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setFlat(true);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setFlat(true);
}

filter_form::~filter_form()
{
    delete ui;
}


void filter_form::showEvent(QShowEvent *)
{
    if(ui->buttonBox->button(QDialogButtonBox::Cancel)->text() != "")
    {
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("");
        ui->buttonBox->button(QDialogButtonBox::Cancel)->setFlat(true);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setText("");
        ui->buttonBox->button(QDialogButtonBox::Ok)->setFlat(true);
    }
    ui->name->setFocus();
    ui->name->selectAll();
}


void filter_form::filter_modified(void)
{
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);


    QLineEdit*  le = dynamic_cast<QLineEdit*>(this->focusWidget());
    if(le!=0)
        le->setStyleSheet("background-color: rgb(255, 255, 192);");
}



void filter_form::slot_button_pressed(QAbstractButton* button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Cancel) == button)
    {
        set_filter_conf(fd);
        set_status_filter_not_modified();
        ui->name->setFocus();
        ui->name->selectAll();
    }
    else if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        set_status_filter_not_modified();
        ui->name->setFocus();
        ui->name->selectAll();
        fd.name = ui->name->text();
        fd.account = ui->account->text();
        fd.market = ui->market->text();
        fd.product = ui->product->text();
        Q_EMIT(signal_filter_modified(fd));
    }
}


void filter_form::set_filter_conf(const filter_data& _fd)
{
    fd = _fd;
    ui->name->setText(fd.name);
    ui->account->setText(fd.account);
    ui->market->setText(fd.market);
    ui->product->setText(fd.product);
    ui->client_code->setText(fd.client_code);
}

void filter_form::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
    {
        QWidget::keyPressEvent(e);
        slot_button_pressed(ui->buttonBox->button(QDialogButtonBox::Cancel));
    }
    else if(e->key() == Qt::Key_Enter  ||  e->key() == Qt::Key_Return)
    {
        if(ui->buttonBox->hasFocus()==false)
            this->focusWidget()->nextInFocusChain()->setFocus();
        else
            QWidget::keyPressEvent(e);
    }
    else
        QWidget::keyPressEvent(e);
}

void filter_form::set_status_filter_not_modified(void)
{
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->name->setStyleSheet("");
    ui->account->setStyleSheet("");
    ui->client_code->setStyleSheet("");
    ui->market->setStyleSheet("");
    ui->product->setStyleSheet("");
}
