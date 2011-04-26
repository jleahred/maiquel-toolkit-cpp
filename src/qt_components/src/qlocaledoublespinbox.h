#ifndef QLOCALEDOUBLESPINBOX_H
#define QLOCALEDOUBLESPINBOX_H

#include <QDoubleSpinBox>



class qLocaleDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit qLocaleDoubleSpinBox(QWidget *parent = 0);

private:
    //QString  textFromValue(double val) const;
    //double   valueFromText(const QString &text) const;
    QValidator::State validate(QString &input, int &pos) const;

signals:

public slots:

};

#endif // QLOCALEDOUBLESPINBOX_H
