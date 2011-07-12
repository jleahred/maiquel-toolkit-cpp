#ifndef QCOMMONTABLEDELEGATE_H
#define QCOMMONTABLEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPen>




class QTableWidget;


class QCommonTableDelegate : public QStyledItemDelegate
{
public:
    QCommonTableDelegate(QTableWidget* tableView);
    void  keep_focus_paint(bool keep);
    void  set_horiz_line_each(int rows) { horiz_line_each_xrows=rows; }

    int   get_left_visual_index  (void) const;
    int   get_right_visual_index (void) const;

protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
private:
    QPen _gridPen;
    QTableWidget* tableView;

    bool focus_paint;
    int  horiz_line_each_xrows;
};



#endif // QCOMMONTABLEDELEGATE_H
