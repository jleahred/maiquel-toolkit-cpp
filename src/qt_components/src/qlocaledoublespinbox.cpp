#include "qlocaledoublespinbox.h"


#include <iostream>
#include <math.h>

#include <QKeyEvent>


#include "support/mtk_double.h"





qLocaleDoubleSpinBox::qLocaleDoubleSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent), _is_empty(false)
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
    if(this->text() == QLatin1String(""))   _is_empty = true;
    else                                    _is_empty = false;
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
    //if(this->text() == QLatin1String("")  &&  mtk::Double(val) == mtk::Double(0))
    if(_is_empty  &&  mtk::Double(val) == mtk::Double(0))
        return QLatin1String("");
    else if(this->text() != QLatin1String("+")  &&   this->text() != QLatin1String("-"))
        return QDoubleSpinBox::textFromValue(val);
        //return this->locale().toString(val);
    else
        return this->text();
}


void  qLocaleDoubleSpinBox::set_empty(void)
{
    _is_empty = true;
    this->setValue(0.);
    this->clear();
}
