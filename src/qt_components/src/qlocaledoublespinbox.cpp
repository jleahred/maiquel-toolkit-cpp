#include "qlocaledoublespinbox.h"


#include <iostream>
#include <math.h>


qLocaleDoubleSpinBox::qLocaleDoubleSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent)
{
}


void qLocaleDoubleSpinBox::keyPressEvent(QKeyEvent *event)
{
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

