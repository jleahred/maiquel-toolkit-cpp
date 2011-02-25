#ifndef QCOMMONTABLEDELEGATE_H
#define QCOMMONTABLEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPen>




class QTableWidget;


class QCommonTableDelegate : public QStyledItemDelegate
{
public:
    QCommonTableDelegate(QTableWidget* tableView);
protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
private:
    QPen _gridPen;
    QTableWidget* tableView;
};



#endif // QCOMMONTABLEDELEGATE_H
