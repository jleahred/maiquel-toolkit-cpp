#include "qlocaledoublespinbox.h"


#include <iostream>
#include <math.h>


qLocaleDoubleSpinBox::qLocaleDoubleSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent)
{
}


/*
QString qLocaleDoubleSpinBox::textFromValue(double value) const
{
    return QLocale::system().toString(value, 'f', this->decimals());
}

double qLocaleDoubleSpinBox::valueFromText(const QString& text) const
{
    return QLocale::system().toDouble(this->text());
}
*/

QValidator::State   qLocaleDoubleSpinBox::validate(QString &input, int &pos) const
{
    QString new_input = QLocale::system().toString(valueFromText(input), 'f', this->decimals());
    pos += new_input.size() - input.size();
    if(new_input != "0")
        input = new_input;
    return QDoubleSpinBox::validate(input, pos);
}
