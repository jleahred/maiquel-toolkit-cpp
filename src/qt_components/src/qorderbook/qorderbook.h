#ifndef QORDERBOOK_H
#define QORDERBOOK_H

#include <QWidget>
#include <QTabWidget>




class  QExecsTable;
class  QPushButton;
class  qorder_table;
namespace YAML { class Emitter;  class Node;  };


class QOrderBook : public QWidget//, public mtk::SignalReceptor
{
    Q_OBJECT
    //typedef  QOrderBook CLASS_NAME;
    friend YAML::Emitter& operator<< (YAML::Emitter    & out , const QOrderBook& m);
    friend void           operator>> (const YAML::Node & i   ,       QOrderBook& m);

public:
    explicit QOrderBook(QWidget *parent = 0);
    ~QOrderBook();

    void update_sizes(void);

signals:

public slots:


private slots:
    void slot_request_new_tab(void);
    void slot_request_close_tab(void);
    void slot_request_showfilter(void);
    void slot_current_tab_name_changed(const QString& new_name);
    void slot_filter_changed();
    void slot_tab_index_changed(int);

private:
    QTabWidget      *tab_widget;
    QExecsTable     *table_executions;


    QPushButton* new_button;
    QPushButton* filter_button;
    QPushButton* close_button;    


    qorder_table*   create_new_tab(void);
    void            delete_current_tab(bool ask=true);
};

#endif // QORDERBOOK_H
