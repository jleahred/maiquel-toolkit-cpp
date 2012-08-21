#include "qfixednumberedit.h"
#include "support/mtk_string.h"
#include "support/alarm.h"
#include <QLineEdit>
#include <QRegExp>
#include <QKeyEvent>



namespace {
    QString fn_as_QString(const mtk::FixedNumber& fn)
    {
        if(fn.GetExt().GetInc() == 0)       return QLatin1String(0);
        else    return QLocale::system().toString(fn.GetDouble().get()._0, 'f', fn.GetExt().GetDec());

    }
}





QFixedNumberEdit::QFixedNumberEdit(QWidget *parent) :
    QAbstractSpinBox(parent), int_minimum(0), int_maximum(0)
{
    connect(this, SIGNAL(editingFinished()), this, SLOT(slot_editing_finished()));
}



void QFixedNumberEdit::setValue(const mtk::nullable<mtk::FixedNumber>& val)
{
    never_call_directly_value = val;
    lineEdit()->clear();
    if(val.HasValue() == true)
    {
        setValue(val.Get());
        Q_EMIT(editingFinished());
    }
}

void QFixedNumberEdit::setValue(const mtk::FixedNumber& val)
{
    never_call_directly_value = val;
    prepared_ext = val.GetExt();

    lineEdit()->setText(fn_as_QString(value().Get()));
    Q_EMIT(valueChanged(never_call_directly_value));
    Q_EMIT(editingFinished());
}

void QFixedNumberEdit::invalidate(void)
{
    setValue(mtk::nullable<mtk::FixedNumber>{});
}



QAbstractSpinBox::StepEnabled QFixedNumberEdit::stepEnabled () const
{
    if(value().HasValue()== false)
        return QAbstractSpinBox::StepNone;
    else
        return QAbstractSpinBox::StepDownEnabled |  QAbstractSpinBox::StepUpEnabled;
}



void QFixedNumberEdit::stepBy ( int steps )
{
    if(value().HasValue())
    {
        auto new_value = value().Get();
        if(steps>0)
            ++new_value;
        else
            --new_value;

        if(minimum() ==  maximum()   ||  new_value.GetIntCode() >= minimum())
        {
            setValue(new_value);
            if(hasFocus())
                lineEdit()->selectAll();
        }
    }
}

void QFixedNumberEdit::prepareExt (const mtk::fnExt&                          ext)
{
    prepared_ext = ext;
    invalidate();
}


QValidator::State   QFixedNumberEdit::validate(QString &input, int &pos) const
{
    QValidator::State state;
    validateAndInterpret(input, pos, state);

    return state;
}



QString remove_thousands_separator(QString input, int &pos)
{
    QString result;
    int result_pos = pos;
    for(int i=0; i<input.size(); ++i)
    {
        if(input.at(i) == QLocale::system().groupSeparator())
        {
            if(i<pos)  --result_pos;
        }
        else
            result.append(input.at(i));
    }
    pos = result_pos;
    return result;
}

QString introduce_thousand_separator(QString input, int &pos)
{
    QString result;

    bool located_decimal_point = false;
    if(input.indexOf(QLocale::system().decimalPoint()) == -1)
        located_decimal_point = true;

    int count_left_decimal_point=0;
    for(int i=input.size()-1; i>=0; --i)
    {
        if(input.at(i) == QLocale::system().decimalPoint())
            located_decimal_point = true;
        else
        {
            if(located_decimal_point)
            {
                if(count_left_decimal_point%3==0  &&  count_left_decimal_point!=0  &&  input.at(i) != QLatin1Char('-'))
                {
                    result = QString(QLocale::system().groupSeparator()) + result;
                    if(pos > i+1)
                        ++pos;
                }
                ++count_left_decimal_point;
            }
        }
        result = QString(input.at(i)) + result;
    }
    return result;
}

mtk::nullable<mtk::FixedNumber>  QFixedNumberEdit::validateAndInterpret(QString &input, int &pos,
                                               QValidator::State &state) const
{
    if(is_editable() == false)
    {
        state = QValidator::Invalid;
        return mtk::nullable<mtk::FixedNumber>{};
    }

    if (cachedText == input && !input.isEmpty())
    {
        state = cachedState;
        return cachedValue;
    }
    cachedValue = mtk::nullable<mtk::FixedNumber>{};


    static QRegExp  regexp(QLatin1String(
                           "^"
                           "\\-?"
                           "("
                             "0"
                             "|"
                             "(0[\\.\\,][0-9]*)"
                             "|"
                             "([1-9][0-9]*([\\.\\,][0-9]*)?)"
                            ")$"));


    input = QLatin1String(mtk::s_trim(input.toStdString(), "\t ").c_str());

    input = remove_thousands_separator(input, pos);
    if(input.isEmpty()==false)
    {

        if(input.at(0)==QLocale::system().decimalPoint())
        {
            input = QLatin1String("0") + input;
            ++pos;
        }
        else if(input.at(0)==QLatin1Char('0')  &&  input.size()>1  &&  input.at(1)!=QLocale::system().decimalPoint())
        {
            input = input.mid(1);
            --pos;
        }
        else if(input.indexOf(QLatin1String("-")+QString(QLocale::system().decimalPoint())) == 0)
        {
            input = QLatin1String("-0") + QString(QLocale::system().decimalPoint())  + input.mid(2);
            pos = 2;
        }
        else if(input.indexOf(QRegExp(QLatin1String("\\-0[0-9][\\.\\,]"))) == 0)
        {
            input = QLatin1String("-") + input.mid(2);
            pos = 2;
        }
    }


    //  check decimal positions
    bool decimals_ok=true;
    {
        int decimal_position = input.indexOf(QLocale::system().decimalPoint());
        if(decimal_position>=0   &&  (input.size() - decimal_position-1) >  prepared_ext.Get().GetDec())
        {
            decimals_ok = false;
            state = QValidator::Invalid;
        }
    }

    if(input == QLatin1String("-")  ||  input == QLatin1String(""))
        state = QValidator::Intermediate;
    else if(regexp.exactMatch(input) == false)
        state = QValidator::Invalid;
    else if(decimals_ok)
    {
        bool ok= false;
        try
        {
            mtk::FixedNumber check_value(mtk::fnDouble(0.), prepared_ext.Get());
            double double_value=0.;

            double_value = QLocale::system().toDouble(input, &ok);
            check_value.SetDouble(double_value, mtk::fnRoundNotAllowed);


            if(minimum() ==  maximum()   ||  check_value.GetIntCode() >= minimum())
            {
                state = QValidator::Acceptable;
                cachedValue = check_value;
            }
        }catch(...)
        {
            state = QValidator::Invalid;
        }
    }

    input = introduce_thousand_separator(input, pos);


    cachedText = input;
    cachedState = state;


    return cachedValue;
}


void QFixedNumberEdit::keyPressEvent(QKeyEvent *event)
{
    int cursor_pos = lineEdit()->cursorPosition();
    QChar previus_char = QLatin1Char('0');
    QChar next_char = QLatin1Char('0');
    QChar decimal_point = QLocale::system().decimalPoint();
    int decimal_point_position = lineEdit()->text().indexOf(decimal_point);
    if(decimal_point_position<0)    decimal_point_position = 1000;

    if(cursor_pos < lineEdit()->text().size()-1)
        next_char = lineEdit()->text().at(cursor_pos);
    if(cursor_pos > 0)
        previus_char = lineEdit()->text().at(cursor_pos-1);

    if(next_char == decimal_point)
    {
        if(event->key() == QLocale::system().decimalPoint())
        {
            lineEdit()->setCursorPosition(cursor_pos+1);
            return;
        }
        if(event->key() == Qt::Key_Delete)
            lineEdit()->setCursorPosition(cursor_pos+1);
        if(lineEdit()->text().indexOf(QLatin1String("-0") + QString(QLocale::system().decimalPoint()))==0  &&  cursor_pos==2)
            lineEdit()->setCursorPosition(cursor_pos-1);
    }

    if(previus_char == decimal_point)
    {
        if(event->key() == Qt::Key_Backspace)
            lineEdit()->setCursorPosition(cursor_pos-1);
    }

    if(next_char == QLocale::system().groupSeparator()  &&  event->key() == Qt::Key_Delete)
        lineEdit()->setCursorPosition(cursor_pos+1);
    if(previus_char == QLocale::system().groupSeparator()  &&  event->key() == Qt::Key_Backspace)
        lineEdit()->setCursorPosition(cursor_pos-1);


    QAbstractSpinBox::keyPressEvent(event);

    QValidator::State state;
    QString           input = lineEdit()->text();
    int               pos   = lineEdit()->cursorPosition();

    if(input.size()>0  &&  (input.at(input.size()-1)==QLocale::system().decimalPoint())  &&  pos<input.size())     //  remove if last char is '.'
        lineEdit()->setText(input.mid(0, input.size()-1));

    update_value(validateAndInterpret(input, pos, state));
}

bool QFixedNumberEdit::is_editable(void)  const
{
    return  prepared_ext.HasValue();
}


void QFixedNumberEdit::slot_editing_finished(void)
{
    if(value().HasValue())
        lineEdit()->setText(fn_as_QString(value().Get()));
    else
        lineEdit()->clear();
    if(hasFocus())
        lineEdit()->selectAll();
}

void  QFixedNumberEdit::update_value(const mtk::nullable<mtk::FixedNumber>& new_value)
{
    never_call_directly_value = new_value;
    Q_EMIT(valueChanged(never_call_directly_value));
}


void     QFixedNumberEdit::focusInEvent    (QFocusEvent *event)
{
    QAbstractSpinBox::focusInEvent(event);
    lineEdit()->selectAll();
}


void     QFixedNumberEdit::focusOutEvent   (QFocusEvent *event)
{
    QAbstractSpinBox::focusOutEvent(event);
    lineEdit()->deselect();
}
