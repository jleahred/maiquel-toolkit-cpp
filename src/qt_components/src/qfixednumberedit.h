#ifndef QFIXEDNUMBEREDIT_H
#define QFIXEDNUMBEREDIT_H

#include <QAbstractSpinBox>
#include "support/fixed_number.h"
#include "support/nullable.hpp"



class QFixedNumberEdit : public QAbstractSpinBox
{
    Q_OBJECT
public:
    explicit QFixedNumberEdit(QWidget *parent = 0);

    mtk::nullable<mtk::FixedNumber>   value() const  {  return  never_call_directly_value;  }


    void    prepareExt (const mtk::fnExt&                          ext);
    void    setValue   (const mtk::nullable<mtk::FixedNumber>&     val);
    void    setValue   (const mtk::FixedNumber&                    val);
    void    invalidate (void);

    bool    is_editable(void)  const;


    int     minimum(void) const  {   return  int_minimum;  }
    void    setMinimum(int  new_minimum)     {   int_minimum =  new_minimum; }
    int     maximum(void) const  {   return  int_maximum;  }
    void    setMaximum(int  new_maximum)     {   int_maximum =  new_maximum; }





protected:
    virtual QValidator::State   validate        (QString &input, int &pos) const;

    virtual StepEnabled         stepEnabled     () const;
    virtual void                stepBy          ( int steps );
    virtual void                keyPressEvent   (QKeyEvent *event);
    virtual void                focusInEvent    (QFocusEvent *event);
    virtual void                focusOutEvent   (QFocusEvent *event);

signals:
    void valueChanged(const mtk::nullable<mtk::FixedNumber>&  value);

public slots:

private:
    mtk::nullable<mtk::FixedNumber>             never_call_directly_value;
    mtk::nullable<mtk::fnExt>                   prepared_ext;
    int                                         int_minimum;
    int                                         int_maximum;

    mutable mtk::nullable<mtk::FixedNumber>     cachedValue;
    mutable QString                             cachedText;
    mutable QValidator::State                   cachedState;



    mtk::nullable<mtk::FixedNumber>  validateAndInterpret(QString &input, int &pos,
                                                   QValidator::State &state) const;
    void  update_value(const mtk::nullable<mtk::FixedNumber>& new_value);

    void normalize_selection(void);

private slots:
    void slot_editing_finished(void);
};

#endif // QFIXEDNUMBEREDIT_H

