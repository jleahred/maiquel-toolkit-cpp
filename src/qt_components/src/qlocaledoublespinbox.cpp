#include "qlocaledoublespinbox.h"


#include <iostream>
#include <math.h>

#include <QKeyEvent>
#include <QLineEdit>

#include "support/mtk_double.h"





qLocaleDoubleSpinBox::qLocaleDoubleSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent), _is_empty(false), previous_pos(0)
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
    {
        previous_input = input;
        previous_pos = 0;
        return QValidator::Intermediate;
    }

    //return QDoubleSpinBox::validate(input, pos);


    bool negative=false;
    int  after_sign = 0;
    if(input == QLatin1String("-"))
    {
        input = QLatin1String("-0");
        pos = 2;
    }
    if(input[0] == QLatin1Char('-'))
    {
        negative = true;
        after_sign = 1;
    }

    if(input[after_sign] == QLocale::system().groupSeparator())
        input[after_sign] =  QLatin1Char(' ');
    if(input.size()==1  &&  this->decimals()>0  &&  input.count(QLocale::system().decimalPoint())==0)
        input += QString(QLocale::system().decimalPoint());

    bool select_zero_left = true;
    if(mtk::Double(0.) != mtk::Double(input.toDouble()))
        select_zero_left = false;
    if(input.count(QString(QLocale::system().decimalPoint()) + QString(QLocale::system().decimalPoint())) >0)
    {
        input.replace(QString(QLocale::system().decimalPoint()) + QString(QLocale::system().decimalPoint()), QString(QLocale::system().decimalPoint()));
        select_zero_left = false;
    }
    if(input[after_sign] == QLocale::system().decimalPoint())
    {
        select_zero_left = false;
        ++pos;
    }

    int  g_separators = input.count(QLocale::system().groupSeparator());
    int  d_separators = input.count(QLocale::system().decimalPoint());
    int  pow10 = 1;
    if(d_separators == 0  &&  this->decimals()>1)
    {
        pow10 = ::pow(10, this->decimals());
        --pos;
    }

    double truncate_adjustment = 1./(2.01 * ::pow(10, this->decimals()));
    if(input[0] == QLatin1Char('-'))
        truncate_adjustment *= -1;
    if(input.toDouble() == mtk::Double(0.))
        truncate_adjustment = 0;

    bool  ok=false;
    input = QLocale::system().toString(QLocale::system().toDouble(input.remove(QLocale::system().groupSeparator()), &ok)/pow10 - truncate_adjustment, 'f', this->decimals());
    if(negative  &&  input[0] != QLatin1Char('-'))
       input = QLatin1String("-") + input;
    if(ok==false)
    {
        input = previous_input;
        --pos;
        return QDoubleSpinBox::validate(input, pos);
    }

    pos += input.count(QLocale::system().groupSeparator()) - g_separators;
    pos += input.count(QLocale::system().decimalPoint())   - d_separators;

    if(negative == false  &&  select_zero_left  &&  input[0] == QLatin1Char('0')  &&  pos == 1)
        this->lineEdit()->setSelection(0, 1);
    else if(negative == true  &&  select_zero_left  &&  input[1] == QLatin1Char('0')  &&  pos == 2)
        this->lineEdit()->setSelection(1, 1);

    previous_input = input;
    if(pos!=0)
        previous_pos = pos;
    auto result =  QDoubleSpinBox::validate(input, pos);
    return result;
}

QString qLocaleDoubleSpinBox::textFromValue(double val) const
{
    //if(this->text() == QLatin1String("")  &&  mtk::Double(val) == mtk::Double(0))
    if(_is_empty  &&  mtk::Double(val) == mtk::Double(0))
        return QLatin1String("");
    else if(this->text() != QLatin1String("+")  &&   this->text() != QLatin1String("-"))
        return QDoubleSpinBox::textFromValue(val);
        //return QLocale::system().toString(val);
    else
        return this->text();
}


void  qLocaleDoubleSpinBox::set_empty(void)
{
    _is_empty = true;
    this->setValue(0.);
    this->clear();
}
