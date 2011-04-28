#ifndef QLOCALEDOUBLESPINBOX_H
#define QLOCALEDOUBLESPINBOX_H

#include <QDoubleSpinBox>



class qLocaleDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit qLocaleDoubleSpinBox(QWidget *parent = 0);

    QValidator::State validate(QString &input, int &pos) const;

private:
    void keyPressEvent(QKeyEvent *event);
    QString textFromValue(double val) const;

signals:

public slots:

};

#endif // QLOCALEDOUBLESPINBOX_H
