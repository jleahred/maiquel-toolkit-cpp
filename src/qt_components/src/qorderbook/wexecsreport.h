#ifndef WEXECSREPORT_H
#define WEXECSREPORT_H

#include <QDialog>
#include <QItemDelegate>

#include "components/trading/trd_cli_support.h"
#include "components/trading/accounts/account_manager_cli.h"

#include "support/signalslot.hpp"




namespace Ui {
    class WExecsReport;
}



class QTreeWidgetItem;




class alarm_delegate  : public QItemDelegate,  public  mtk::SignalReceptor
{
    Q_OBJECT

public:
    alarm_delegate(QObject *parent):QItemDelegate(parent){};
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
};



class WExecsReport : public QDialog,  public  mtk::SignalReceptor
{
    Q_OBJECT
    typedef WExecsReport  CLASS_NAME;

public:
    explicit WExecsReport(QWidget *parent = 0);
    ~WExecsReport();

    void on_new_execution(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec);


private:
    Ui::WExecsReport *ui;

    void on_grant_received(const mtk::trd::account::msg::sub_grant&  grant);

private slots:
    void slot_itemChanged ( QTreeWidgetItem * item, int column );
    void slot_itemDoubleClicked ( QTreeWidgetItem * item, int column );
};

#endif // WEXECSREPORT_H
