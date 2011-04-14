#ifndef QORDERBOOK_H
#define QORDERBOOK_H

#include <QWidget>
#include <QTabWidget>


#include "qorder_table.h"




class QOrderBook : public QWidget//, public mtk::SignalReceptor
{
    Q_OBJECT
    //typedef  QOrderBook CLASS_NAME;

public:
    explicit QOrderBook(QWidget *parent = 0);
    ~QOrderBook();

    void update_sizes(void);

signals:

public slots:


private slots:
    void slot_request_new_tab(void);
    void slot_request_close_tab();
    void slot_request_showfilter(void);
    void slot_current_tab_name_changed(const QString& new_name);
    void slot_tab_index_changed(int);

private:
    QTabWidget      *tab_widget;
    QTableWidget    *table_executions;


    QPushButton* new_button;
    QPushButton* filter_button;
    QPushButton* close_button;

};

#endif // QORDERBOOK_H
