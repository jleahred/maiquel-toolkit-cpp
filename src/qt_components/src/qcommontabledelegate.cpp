#include "qcommontabledelegate.h"

#include <QTableWidget>
#include <QPainter>

/*
QCommonTableDelegate::QCommonTableDelegate(QObject *parent) :
    QStyledDelegate(parent)
{
}
*/


// custom item delegate to draw grid lines around cells

QCommonTableDelegate::QCommonTableDelegate(QTableWidget* _tableView)
    : QStyledItemDelegate(_tableView),
      tableView(_tableView),
      focus_paint(false),
      horiz_line_each_xrows(3)
{
    // create grid pen
    int gridHint = tableView->style()->styleHint(QStyle::SH_Table_GridLineColor, new QStyleOptionViewItemV4());
    QColor gridColor = static_cast<QRgb>(gridHint);
    _gridPen = //QPen(gridColor, 0, tableView->gridStyle());
                QPen(Qt::blue, 2);
}


void QCommonTableDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (tableView->currentRow()==index.row())
    {
        if (tableView->hasFocus()  ||  focus_paint)
        {
            QStyleOptionViewItem ViewOption(option);
            //  remove focus
            if (ViewOption.state & QStyle::State_HasFocus)
                ViewOption.state = ViewOption.state ^ QStyle::State_HasFocus;

            QColor color = tableView->item(index.row(), index.column())->background().color();
            int new_red = color.red()-45 ;  new_red = new_red < 0 ? 0:  new_red;
            int new_green = color.green()-45;  new_green = new_green < 0 ? 0:  new_green;
            color.setRgb(new_red, new_green, color.blue());

            ViewOption.palette.setColor(QPalette::Highlight, color);
            ViewOption.palette.setColor(QPalette::HighlightedText, tableView->item(index.row(), index.column())->foreground().color());
            QStyledItemDelegate::paint(painter, ViewOption, index);

            /*
            ///////////////////////////////////////////////
            if ((index.row()+1)%3!=0  &&  (index.row()+2)%3!=0)
            {
                QPen grid_pPen = QPen(tableView->item(index.row(), index.column())->background().color().darker(104), 1, tableView->gridStyle()); painter->setPen(grid_pPen);
                painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight()); //draw only horizontal line
            }
            ///////////////////////////////////////////////
            */
            //painter->save();
            painter->setPen(_gridPen);

            // uroundborder
            QPoint urb;
            if (index.column()==0)
                urb = QPoint(2,0);
            if (index.column() == tableView->columnCount()-1)
                urb = QPoint(-1,0);

            painter->drawLine(option.rect.topLeft()+QPoint(0,1)+urb, option.rect.topRight()+QPoint(0,1)+urb); //draw only horizontal line
            painter->drawLine(option.rect.bottomLeft()+QPoint(0,0)+urb, option.rect.bottomRight()+QPoint(0,0)+urb); //draw only horizontal line

            if (index.column()==0)
                painter->drawLine(option.rect.topLeft()+QPoint(1,2), option.rect.bottomLeft()+QPoint(1,-2)); //draw only horizontal line
            if (index.column()==tableView->columnCount()-1)
                painter->drawLine(option.rect.topRight()+QPoint(0,2), option.rect.bottomRight()+QPoint(0,-2)); //draw only horizontal line

            //painter->restore();
        }
        else
        {
            QStyleOptionViewItem ViewOption(option);
            QColor color = tableView->item(index.row(), index.column())->background().color();

            ViewOption.palette.setColor(QPalette::Highlight, color);
            ViewOption.palette.setColor(QPalette::HighlightedText, tableView->item(index.row(), index.column())->foreground().color());
            QStyledItemDelegate::paint(painter, ViewOption, index);

            ///////////////////////////////////////////////
            if ((index.row()+1)%horiz_line_each_xrows==0)
            {
                QColor bluer(tableView->item(index.row(), index.column())->background().color());
                bluer = QColor(bluer.red()-40, bluer.green()-40, bluer.blue());
                QPen grid_pPen = QPen(bluer, 1, tableView->gridStyle()); painter->setPen(grid_pPen);
                painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight()); //draw only horizontal line
                //QPen grid_pPen = QPen(tableView->item(index.row(), index.column())->background().color().darker(125), 1, tableView->gridStyle()); painter->setPen(grid_pPen);
                //painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight()); //draw only horizontal line
            }
            if(index.column()==0)
            {
                QColor bluer(tableView->item(index.row(), index.column())->background().color());
                bluer = QColor(bluer.red()-40, bluer.green()-40, bluer.blue());
                QPen grid_pPen = QPen(bluer, 1, tableView->gridStyle()); painter->setPen(grid_pPen);
                painter->drawLine(option.rect.topRight(), option.rect.bottomRight()); //draw only horizontal line
            }
            ///////////////////////////////////////////////
        }
    }
    else
    {
        QStyleOptionViewItem ViewOption(option);


        QStyledItemDelegate::paint(painter, ViewOption, index);

        ///////////////////////////////////////////////
        if ((index.row()+1)%horiz_line_each_xrows==0)
        {
            QColor bluer(tableView->item(index.row(), index.column())->background().color());
            bluer = QColor(bluer.red()-40, bluer.green()-40, bluer.blue());
            QPen grid_pPen = QPen(bluer, 1, tableView->gridStyle()); painter->setPen(grid_pPen);
            painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight()); //draw only horizontal line
            //QPen grid_pPen = QPen(tableView->item(index.row(), index.column())->background().color().darker(125), 1, tableView->gridStyle()); painter->setPen(grid_pPen);
            //painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight()); //draw only horizontal line
        }
        if(index.column()==0)
        {
            QColor bluer(tableView->item(index.row(), index.column())->background().color());
            bluer = QColor(bluer.red()-40, bluer.green()-40, bluer.blue());
            QPen grid_pPen = QPen(bluer, 1, tableView->gridStyle()); painter->setPen(grid_pPen);
            painter->drawLine(option.rect.topRight(), option.rect.bottomRight()); //draw only horizontal line
        }
        ///////////////////////////////////////////////

        //QStyledItemDelegate::paint(painter, option, index);
    }
}


void  QCommonTableDelegate::keep_focus_paint(bool keep)
{

    focus_paint = keep;
}
