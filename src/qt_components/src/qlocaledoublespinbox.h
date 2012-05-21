#ifndef QLOCALEDOUBLESPINBOX_H
#define QLOCALEDOUBLESPINBOX_H

#include <QDoubleSpinBox>



class qLocaleDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit qLocaleDoubleSpinBox(QWidget *parent = 0);

    QValidator::State validate(QString &input, int &pos) const;

    void  set_empty(void);
    bool  is_empty(void) const  {  return _is_empty;  }

private:
    bool                _is_empty;
    mutable QString     previous_input;
    mutable int         previous_pos;

    void keyPressEvent(QKeyEvent *event);
    QString textFromValue(double val) const;

signals:

public slots:

};

#endif // QLOCALEDOUBLESPINBOX_H
