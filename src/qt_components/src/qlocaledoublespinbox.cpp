#include "qlocaledoublespinbox.h"


#include <iostream>
#include <math.h>

#include <QKeyEvent>


#include "support/mtk_double.h"





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

    return QDoubleSpinBox::validate(input, pos);
}

QString qLocaleDoubleSpinBox::textFromValue(double val) const
{
    if(this->text() == QLatin1String("")  &&  mtk::Double(val) == mtk::Double(0))
        return this->text();
    else if(this->text() != QLatin1String("+")  &&   this->text() != QLatin1String("-"))
        return QDoubleSpinBox::textFromValue(val);
    else
        return this->text();
}
