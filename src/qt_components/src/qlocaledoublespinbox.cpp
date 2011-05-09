#include "qlocaledoublespinbox.h"


#include <iostream>
#include <math.h>


#include <QKeyEvent>




qLocaleDoubleSpinBox::qLocaleDoubleSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent)
{
}


void qLocaleDoubleSpinBox::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter  ||   event->key() == Qt::Key_Return)
    {
        if(this->text() == QLatin1String("+")  ||  this->text()== QLatin1String("-"))
            return;
    }
    QDoubleSpinBox::keyPressEvent(event);
    Q_EMIT(this->valueChanged(this->text()));
}

QValidator::State   qLocaleDoubleSpinBox::validate(QString &input, int &pos) const
{
    if(input.isEmpty())
        return QValidator::Intermediate;

    if(decimals()==0)
    {
        QString new_input = QLocale::system().toString(valueFromText(input), 'f', this->decimals());
        pos += new_input.size() - input.size();
        if(new_input != QLatin1String("0"))
            input = new_input;
    }

    return QDoubleSpinBox::validate(input, pos);
}

QString qLocaleDoubleSpinBox::textFromValue(double val) const
{
    if(this->text().isEmpty()  &&  abs(val) < 0.00000001)
        return QString();
    else
        return QDoubleSpinBox::textFromValue(val);
}
