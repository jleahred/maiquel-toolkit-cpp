#ifndef QCOMMONTABLEDELEGATE_H
#define QCOMMONTABLEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPen>




class QTableWidget;


class QCommonTableDelegate : public QStyledItemDelegate
{
public:
    QCommonTableDelegate(QTableWidget* tableView, bool _just_cell=false);
    void  keep_focus_paint(bool keep);
    void  set_horiz_line_each(int rows) { horiz_line_each_xrows=rows; }

    int   get_left_visual_index  (void) const;
    int   get_right_visual_index (void) const;

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
protected:
private:
    QPen _gridPen;
    QTableWidget* tableView;

    bool focus_paint;
    int  horiz_line_each_xrows;
    bool just_cell;
};





#endif // QCOMMONTABLEDELEGATE_H
