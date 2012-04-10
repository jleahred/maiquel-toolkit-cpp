#include "qcommontabledelegate.h"

#include <QTableWidget>
#include <QTableView>
#include <QPainter>
#include <QHeaderView>

#include "qt_components/src/qmtk_misc.h"

/*
QCommonTableDelegate::QCommonTableDelegate(QObject *parent) :
    QStyledDelegate(parent)
{
}
*/


// custom item delegate to draw grid lines around cells

QCommonTableDelegate::QCommonTableDelegate(QTableWidget* _tableView, bool _just_cell)
    : QStyledItemDelegate(_tableView),
      tableView(_tableView),
      focus_paint(false),
      horiz_line_each_xrows(3),
      just_cell(_just_cell)
{
    // create grid pen
    _gridPen = //QPen(gridColor, 0, tableView->gridStyle());
                QPen(Qt::blue, 2);
}


QColor  more_blue(const QColor& input_color)
{
    QColor color = input_color;
    int new_red = color.red()-45 ;  new_red = new_red < 0 ? 0:  new_red;
    int new_green = color.green()-45;  new_green = new_green < 0 ? 0:  new_green;
    color.setRgb(new_red, new_green, color.blue());

    return color;
}

void QCommonTableDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (tableView->currentRow()==index.row()   ||   (just_cell  &&  tableView->currentRow()==index.row()  &&  tableView->currentColumn()==index.column()) )
    {
        if (tableView->hasFocus()  ||  focus_paint)
        {
            QStyleOptionViewItem ViewOption(option);
            //  remove focus
            if (ViewOption.state & QStyle::State_HasFocus)
                ViewOption.state = ViewOption.state ^ QStyle::State_HasFocus;

            QColor color = more_blue(tableView->item(index.row(), index.column())->background().color());

            ViewOption.palette.setColor(QPalette::Highlight, color);
            ViewOption.palette.setColor(QPalette::HighlightedText, tableView->item(index.row(), index.column())->foreground().color());
            QStyledItemDelegate::paint(painter, ViewOption, index);

            ///////////////////////////////////////////////
            if ((index.row()+1)%horiz_line_each_xrows==0)
            {
                QColor bluer(tableView->item(index.row(), index.column())->background().color());
                int new_red = bluer.red()-40 ;  new_red = new_red < 0 ? 0:  new_red;
                int new_green = bluer.green()-40;  new_green = new_green < 0 ? 0:  new_green;
                bluer = QColor(new_red, new_green, bluer.blue());
                QPen grid_pPen = QPen(bluer, 1, tableView->gridStyle()); painter->setPen(grid_pPen);
                painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight()); //draw only horizontal line
                //QPen grid_pPen = QPen(tableView->item(index.row(), index.column())->background().color().darker(125), 1, tableView->gridStyle()); painter->setPen(grid_pPen);
                //painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight()); //draw only horizontal line
            }
            ///////////////////////////////////////////////
            //painter->save();
            painter->setPen(_gridPen);

            // uroundborder
            if(just_cell == false)
            {
                QPoint urb;
                if (index.column()==0)
                    urb = QPoint(2,0);
                if (index.column() == tableView->columnCount()-1)
                    urb = QPoint(-1,0);

                painter->drawLine(option.rect.topLeft()+QPoint(0,1)+urb, option.rect.topRight()+QPoint(0,1)+urb); //draw only horizontal line
                painter->drawLine(option.rect.bottomLeft()+QPoint(0,0)+urb, option.rect.bottomRight()+QPoint(0,0)+urb); //draw only horizontal line

                if (index.column()==get_left_visual_index())
                    painter->drawLine(option.rect.topLeft()+QPoint(1,2), option.rect.bottomLeft()+QPoint(1,-2)); //draw only horizontal line
                if (index.column()==get_right_visual_index())
                    painter->drawLine(option.rect.topRight()+QPoint(0,2), option.rect.bottomRight()+QPoint(0,-2)); //draw only horizontal line
            }
            else
            {
                if(index.column() == tableView->currentColumn()  &&  index.row() == tableView->currentRow()  &&  (tableView->currentItem()->flags() & Qt::ItemIsSelectable))
                {
                    QPoint urb_left = QPoint(2,0);
                    QPoint urb_right = QPoint(-1,0);

                    painter->drawLine(option.rect.topLeft()+QPoint(0,1)+urb_left, option.rect.topRight()+QPoint(0,1)+urb_right); //draw only horizontal line
                    painter->drawLine(option.rect.bottomLeft()+QPoint(0,0)+urb_left, option.rect.bottomRight()+QPoint(0,0)+urb_right); //draw only horizontal line

                    painter->drawLine(option.rect.topLeft()+QPoint(1,2), option.rect.bottomLeft()+QPoint(1,-2)); //draw only horizontal line
                    painter->drawLine(option.rect.topRight()+QPoint(0,2), option.rect.bottomRight()+QPoint(0,-2)); //draw only horizontal line
                }
            }
            if(index.column()==0)
            {
                QColor bluer(more_blue(tableView->item(index.row(), index.column())->background().color()));
                QPen grid_pPen = QPen(bluer, 1, tableView->gridStyle()); painter->setPen(grid_pPen);
                painter->drawLine(option.rect.topRight(), option.rect.bottomRight()); //draw only horizontal line
            }
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
                int new_red = bluer.red()-40 ;  new_red = new_red < 0 ? 0:  new_red;
                int new_green = bluer.green()-40;  new_green = new_green < 0 ? 0:  new_green;
                bluer = QColor(new_red, new_green, bluer.blue());
                QPen grid_pPen = QPen(bluer, 1, tableView->gridStyle()); painter->setPen(grid_pPen);
                painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight()); //draw only horizontal line
                //QPen grid_pPen = QPen(tableView->item(index.row(), index.column())->background().color().darker(125), 1, tableView->gridStyle()); painter->setPen(grid_pPen);
                //painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight()); //draw only horizontal line
            }
            ///////////////////////////////////////////////
            if(index.column()==0)
            {
                QColor bluer(more_blue(tableView->item(index.row(), index.column())->background().color()));
                QPen grid_pPen = QPen(bluer, 1, tableView->gridStyle()); painter->setPen(grid_pPen);
                painter->drawLine(option.rect.topRight(), option.rect.bottomRight()); //draw only horizontal line
            }
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
            int new_red = bluer.red()-40 ;  new_red = new_red < 0 ? 0:  new_red;
            int new_green = bluer.green()-40;  new_green = new_green < 0 ? 0:  new_green;
            bluer = QColor(new_red, new_green, bluer.blue());
            QPen grid_pPen = QPen(bluer, 1, tableView->gridStyle()); painter->setPen(grid_pPen);
            painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight()); //draw only horizontal line
            //QPen grid_pPen = QPen(tableView->item(index.row(), index.column())->background().color().darker(125), 1, tableView->gridStyle()); painter->setPen(grid_pPen);
            //painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight()); //draw only horizontal line
        }
        if(index.column()==0)
        {
            QColor bluer(more_blue(tableView->item(index.row(), index.column())->background().color()));
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


int   QCommonTableDelegate::get_left_visual_index  (void) const
{
    return  tableView->horizontalHeader()->logicalIndex(0);
}
int   QCommonTableDelegate::get_right_visual_index (void) const
{
    return  tableView->horizontalHeader()->logicalIndex(tableView->columnCount()-1);
}





QCommonTableDelegate_view::QCommonTableDelegate_view(QTableView* _tableView, bool _just_cell)
    : QStyledItemDelegate(_tableView),
      tableView(_tableView),
      focus_paint(false),
      horiz_line_each_xrows(3),
      just_cell(_just_cell)
{
    // create grid pen
    _gridPen = //QPen(gridColor, 0, tableView->gridStyle());
                QPen(Qt::blue, 2);
}



void QCommonTableDelegate_view::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    static const  QColor  color_price   =  QColor(240,245,250);


    QColor cell_color = Qt::white;
    if(index.column() == 0)
            cell_color = qtmisc::mtk_color_header;
    else if (index.column() == 2  ||  index.column() == 3)
            cell_color = color_price;


    if (tableView->currentIndex().row()==index.row()   ||   (just_cell  &&  tableView->currentIndex().row()==index.row()  &&  tableView->currentIndex().column()==index.column()) )
    {
        if (tableView->hasFocus()  ||  focus_paint)
        {
            QStyleOptionViewItem ViewOption(option);
            ViewOption.state = QStyle::State_None;
            QStyledItemDelegate::paint(painter, ViewOption, index);

            ///////////////////////////////////////////////
            if ((index.row()+1)%horiz_line_each_xrows==0)
            {
                QColor bluer = more_blue(cell_color);
                int new_red = bluer.red()-40 ;  new_red = new_red < 0 ? 0:  new_red;
                int new_green = bluer.green()-40;  new_green = new_green < 0 ? 0:  new_green;
                bluer = QColor(new_red, new_green, bluer.blue());
                QPen grid_pPen = QPen(bluer, 1, tableView->gridStyle()); painter->setPen(grid_pPen);
                painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight()); //draw only horizontal line
            }
            ///////////////////////////////////////////////
            painter->setPen(_gridPen);

            // uroundborder
            if(just_cell == false)
            {
                QPoint urb;
                if (index.column()==0)
                    urb = QPoint(2,0);
                if (index.column() == tableView->horizontalHeader()->count()-1)
                    urb = QPoint(-1,0);

                painter->drawLine(option.rect.topLeft()+QPoint(0,1)+urb, option.rect.topRight()+QPoint(0,1)+urb); //draw only horizontal line
                painter->drawLine(option.rect.bottomLeft()+QPoint(0,0)+urb, option.rect.bottomRight()+QPoint(0,0)+urb); //draw only horizontal line

                if (index.column()==get_left_visual_index())
                    painter->drawLine(option.rect.topLeft()+QPoint(1,2), option.rect.bottomLeft()+QPoint(1,-2)); //draw only horizontal line
                if (index.column()==get_right_visual_index())
                    painter->drawLine(option.rect.topRight()+QPoint(0,2), option.rect.bottomRight()+QPoint(0,-2)); //draw only horizontal line
            }
            else
            {
                if(index.column() == tableView->currentIndex().row()  &&  index.row() == tableView->currentIndex().row())
                {
                    QPoint urb_left = QPoint(2,0);
                    QPoint urb_right = QPoint(-1,0);

                    painter->drawLine(option.rect.topLeft()+QPoint(0,1)+urb_left, option.rect.topRight()+QPoint(0,1)+urb_right); //draw only horizontal line
                    painter->drawLine(option.rect.bottomLeft()+QPoint(0,0)+urb_left, option.rect.bottomRight()+QPoint(0,0)+urb_right); //draw only horizontal line

                    painter->drawLine(option.rect.topLeft()+QPoint(1,2), option.rect.bottomLeft()+QPoint(1,-2)); //draw only horizontal line
                    painter->drawLine(option.rect.topRight()+QPoint(0,2), option.rect.bottomRight()+QPoint(0,-2)); //draw only horizontal line
                }
            }
            if(index.column()==0)
            {
                QColor bluer = more_blue(cell_color);
                QPen grid_pPen = QPen(bluer, 1, tableView->gridStyle()); painter->setPen(grid_pPen);
                painter->drawLine(option.rect.topRight(), option.rect.bottomRight()); //draw only horizontal line
            }
        }
        else
        {
            QStyleOptionViewItem ViewOption(option);
            ViewOption.state = QStyle::State_None;
            QStyledItemDelegate::paint(painter, ViewOption, index);

            ///////////////////////////////////////////////
            if ((index.row()+1)%horiz_line_each_xrows==0)
            {
                QColor bluer = cell_color;
                int new_red = bluer.red()-40 ;  new_red = new_red < 0 ? 0:  new_red;
                int new_green = bluer.green()-40;  new_green = new_green < 0 ? 0:  new_green;
                bluer = QColor(new_red, new_green, bluer.blue());
                QPen grid_pPen = QPen(bluer, 1, tableView->gridStyle()); painter->setPen(grid_pPen);
                painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight()); //draw only horizontal line
            }
            ///////////////////////////////////////////////
            if(index.column()==0)
            {
                QColor bluer = more_blue(cell_color);
                QPen grid_pPen = QPen(bluer, 1, tableView->gridStyle()); painter->setPen(grid_pPen);
                painter->drawLine(option.rect.topRight(), option.rect.bottomRight()); //draw only horizontal line
            }
        }
    }
    else
    {
        QStyleOptionViewItem ViewOption(option);
        ViewOption.state = QStyle::State_None;
        QStyledItemDelegate::paint(painter, ViewOption, index);

        ///////////////////////////////////////////////
        if ((index.row()+1)%horiz_line_each_xrows==0)
        {
            QColor bluer = cell_color;
            int new_red = bluer.red()-40 ;  new_red = new_red < 0 ? 0:  new_red;
            int new_green = bluer.green()-40;  new_green = new_green < 0 ? 0:  new_green;
            bluer = QColor(new_red, new_green, bluer.blue());
            QPen grid_pPen = QPen(bluer, 1, tableView->gridStyle()); painter->setPen(grid_pPen);
            painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight()); //draw only horizontal line
        }
        if(index.column()==0)
        {
            QColor bluer = more_blue(cell_color);
            QPen grid_pPen = QPen(bluer, 1, tableView->gridStyle()); painter->setPen(grid_pPen);
            painter->drawLine(option.rect.topRight(), option.rect.bottomRight()); //draw only horizontal line
        }
        ///////////////////////////////////////////////

    }
}


void  QCommonTableDelegate_view::keep_focus_paint(bool keep)
{

    focus_paint = keep;
}


int   QCommonTableDelegate_view::get_left_visual_index  (void) const
{
    return  tableView->horizontalHeader()->logicalIndex(0);
}
int   QCommonTableDelegate_view::get_right_visual_index (void) const
{
    return  tableView->horizontalHeader()->logicalIndex(tableView->horizontalHeader()->count()-1);
}


