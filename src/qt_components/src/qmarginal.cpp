#include "qmarginal.h"

#include <QVBoxLayout>
#include <QHeaderView>
#include <QAction>
#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>

#include <QPen>
#include <QPainter>
#include <QApplication>
#include <QMenu>


#include <iostream>


#include "components/trading/trd_cli_ord_book.h"
#include "qt_components/src/qmtk_misc.h"
#include "qt_components/src/qcommontabledelegate.h"









namespace {
    const char*   VERSION = "2011-03-16";

    const char*   MODIFICATIONS =
                        "           2011-03-16     first version\n";


void command_version(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(MTK_SS(__FILE__ << ":  " << VERSION));
}

void command_modifications  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(__FILE__);
    response_lines.push_back(".......................................");
    response_lines.push_back(MODIFICATIONS);
}


void register_global_commands (void)
{
    mtk::admin::register_command("__GLOBAL__",  "ver",   "")->connect(command_version);
    mtk::admin::register_command("__GLOBAL__",  "modifs",   "")->connect(command_modifications);
}

MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)

}       //  anonymous namespace  to register "static" commnads











int marginal_in_table::counter = 0;


namespace {


    QColor  color_product = QColor(Qt::lightGray).lighter(115);
    const QColor  color_qty     = Qt::white;
    //const QColor  color_qty     = QColor(237,240,249);
    const QColor  color_price   = mtk_yellow;


mtk::FixedNumber get_empty_fixed_number_quantity(void)
{
    return mtk::FixedNumber(mtk::fnDouble(0.), mtk::fnDec(0), mtk::fnInc(1));
}
mtk::FixedNumber get_empty_fixed_number_price(void)
{
    return mtk::FixedNumber(mtk::fnDouble(0.), mtk::fnDec(2), mtk::fnInc(1));
}
mtk::prices::msg::sub_price_level   get_emtpy_level_prices(void)
{
    return mtk::prices::msg::sub_price_level(get_empty_fixed_number_price(), get_empty_fixed_number_quantity());
}

mtk::msg::sub_product_code  get_empty_product_code (void)
{
    return mtk::msg::sub_product_code(mtk::msg::sub_sys_product_code(mtk::msg::sub_single_product_code("", ""), ""),
                                      mtk::nullable<mtk::msg::sub_adic_product_code>());
}

mtk::prices::msg::pub_best_prices    get_emtpy_best_prices   (void)
{
    return mtk::prices::msg::pub_best_prices(
        get_empty_product_code(),
        mtk::prices::msg::sub_price_deph5(  get_emtpy_level_prices(),
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices()),
        mtk::prices::msg::sub_price_deph5(  get_emtpy_level_prices(),
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices(),
                                            get_emtpy_level_prices())
    );
}


};  //namespace  {



class QTableWidgetItemProduct : public QTableWidgetItem
{
public:
    QTableWidgetItemProduct (const mtk::msg::sub_product_code&  _product_code, int _id) : QTableWidgetItem(), product_code(_product_code), id(_id) {}
    mtk::msg::sub_product_code  product_code;
    const int id;
};






QMarginal::QMarginal(QWidget *parent) :
    mtkContainerWidget(parent),
    table_marginals(new QTableMarginal(this))
{
    this->setGeometry(QRect(5, 5, 100*4+150+2*5, 300));
    this->setAcceptDrops(true);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(5,5,5,5);
    this->setLayout(layout);
    layout->addWidget(table_marginals);

    connect(this, SIGNAL(signal_start_moving()), SLOT(make_transparent()));
    connect(this, SIGNAL(signal_stop_moving()), SLOT(remove_transparent()));
    this->inserting_components_ended();
}

QMarginal::~QMarginal()
{
}



QTableMarginal::QTableMarginal(QWidget *parent)
    : QTableWidget(parent), startPos(-1,-1)
{
    this->setStyleSheet("background-color: rgb(191,219,255);");
    color_product = QColor(191,219,255);


    //color_product = this->horizontalHeader()->palette().background().color();
    this->setAcceptDrops(true);

    setItemDelegate(new QCommonTableDelegate(this));
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setShowGrid(false);

    {
        setRowCount(0);
        setColumnCount(5);
        verticalHeader()->setVisible(false);
        horizontalHeader()->setVisible(true);
        //table_marginals->setSelectionMode(QAbstractItemView::NoSelection);
        //verticalHeader()->setDefaultSectionSize(QFontMetrics(this->font()).height()*1.6);
        verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
        horizontalHeader()->setStretchLastSection(true);
        //horizontalHeader()->setDefaultSectionSize(100);
        horizontalHeader()->resizeSection(0, 150);


        setColumnCount(5);

        //item->setForeground(QBrush(Qt::black));
        #define QMARG_INIT_HEADER_ITEM(__COLUMN__, __TEXT__) \
        {   \
            item = new QTableWidgetItem(); \
            item->setForeground(QBrush(QColor(30,0,100)));  \
            item->setText(__TEXT__);   \
            setHorizontalHeaderItem(__COLUMN__, item);   \
        }

        {
            QTableWidgetItem *item=0;
            QFont font(this->font());
            font.setBold(true);
            //font.setPointSize(11);
            QMARG_INIT_HEADER_ITEM(0, "Product")
            QMARG_INIT_HEADER_ITEM(1, "Qty bid")
            QMARG_INIT_HEADER_ITEM(2, "BID")
            QMARG_INIT_HEADER_ITEM(3, "ASK")
            QMARG_INIT_HEADER_ITEM(4, "Qty ask")
        }
        horizontalHeader()->setMovable(true);
    }

}







marginal_in_table::marginal_in_table(QTableWidget* _table_widget, const mtk::msg::sub_product_code& product_code, int row)
    : id(++counter), table_widget(_table_widget)
{
    tw_product  = new QTableWidgetItemProduct(product_code, this->id);
    tw_BID      = new QTableWidgetItem();
    tw_ASK      = new QTableWidgetItem();
    tw_qty_bid  = new QTableWidgetItem();
    tw_qty_ask  = new QTableWidgetItem();

    if (row>=0 && row<table_widget->rowCount())
        table_widget->insertRow(row);
    else
    {
        table_widget->setRowCount(table_widget->rowCount()+1);
        row = table_widget->rowCount()-1;
    }
    table_widget->setItem(row, 0, tw_product);
    table_widget->setItem(row, 1, tw_qty_bid);
    table_widget->setItem(row, 2, tw_BID);
    table_widget->setItem(row, 3, tw_ASK);
    table_widget->setItem(row, 4, tw_qty_ask);


    //QFont font(_table_widget->font());
    //font.setBold(true);
    {
        tw_product->setText(QString(MTK_SS(product_code.sys_code.market << "." << product_code.sys_code.user_name).c_str()));
        //font.setPointSize(11);
        //tw_product->setFont(font);
        tw_product->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    //font.setPointSize(10);
    {
        //tw_BID->setFont(font);
        tw_BID->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tw_BID->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    {
        //tw_ASK->setFont(font);
        tw_ASK->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tw_ASK->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    {
        //tw_qty_bid->setFont(font);
        tw_qty_bid->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tw_qty_bid->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    {
        //tw_qty_ask->setFont(font);
        tw_qty_ask->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tw_qty_ask->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }



    MTK_QPID_RECEIVER_CONNECT_THIS(
                            h_best_prices,
                            mtk::admin::get_url("client"),
                            "CLITESTING",
                            mtk::prices::msg::pub_best_prices::get_in_subject(product_code.sys_code.market, product_code.sys_code.product),
                            mtk::prices::msg::pub_best_prices,
                            on_message)

}


namespace {
    QColor color_transparency(const QColor& color, int transparency)
    {
        return QColor(color.red(), color.green(), color.blue(), transparency);
    }

};

void marginal_in_table::set_normal_color(int transparency)
{
    tw_product->setBackgroundColor(color_transparency(color_product, transparency));
    QBrush foreground (tw_product->foreground());
    //foreground.setColor(Qt::black);
    foreground.setColor(QColor(30,0,100));
    tw_product->setForeground(foreground);
    tw_BID->setBackgroundColor(color_transparency(color_price, transparency));
    tw_ASK->setBackgroundColor(color_transparency(color_price, transparency));
    tw_qty_bid->setBackgroundColor(color_transparency(color_qty, transparency));
    tw_qty_ask->setBackgroundColor(color_transparency(color_qty, transparency));
}

void marginal_in_table::set_dark_color(void)
{
    tw_product->setBackgroundColor(color_product.darker(110));
    QBrush foreground (tw_product->foreground());
    foreground.setColor(Qt::black);
    tw_product->setForeground(foreground);
    tw_BID->setBackgroundColor(color_price.darker(105));
    tw_ASK->setBackgroundColor(color_price.darker(105));
    tw_qty_bid->setBackgroundColor(color_qty.darker(105));
    tw_qty_ask->setBackgroundColor(color_qty.darker(105));
}






namespace {
    mtk::tuple<QString, QString>  get_price_quantity(const mtk::msg::sub_product_code& product_code,  const mtk::prices::msg::sub_price_level& marginal)
    {
        if (marginal.quantity.GetIntCode() == 0)
        {
            if (marginal.price.GetIntCode()==0)
                return mtk::make_tuple(QString(), QString());
            else
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qmarginal", MTK_SS("received quantity 0 with price not 0 on "
                                                          << product_code.sys_code.market << "." << product_code.sys_code.product), mtk::alPriorError, mtk::alTypeNoPermisions));
                return mtk::make_tuple(fn_as_QString(marginal.price), fn_as_QString(marginal.quantity));
            }
        }
        else
            return mtk::make_tuple(fn_as_QString(marginal.price), fn_as_QString(marginal.quantity));
    }
};


void marginal_in_table::on_message(const mtk::prices::msg::pub_best_prices& msg)
{

    mtk::tuple<QString, QString>  tprice_tquantity;

    tprice_tquantity = get_price_quantity(msg.product_code, msg.bids.level0);
    tw_BID->setText(tprice_tquantity._0);
    tw_qty_bid->setText(tprice_tquantity._1);

    tprice_tquantity = get_price_quantity(msg.product_code, msg.asks.level0);
    tw_ASK->setText(tprice_tquantity._0);
    tw_qty_ask->setText(tprice_tquantity._1);

}



void QTableMarginal::insert_marginal(const mtk::msg::sub_product_code& product_code, int row)
{
    marginals.push_back(mtk::make_cptr(new marginal_in_table(this, product_code, row)));
    adjust_pajama();
}

void QTableMarginal::add_marginal(const mtk::msg::sub_product_code& product_code)
{
    marginals.push_back(mtk::make_cptr(new marginal_in_table(this, product_code)));
    adjust_pajama();
}

void QTableMarginal::dragEnterEvent(QDragEnterEvent *event)
{
    QTableWidget::dragEnterEvent(event);
    if(qobject_cast<QTableMarginal*>(event->source())!=0)
        event->setDropAction(Qt::MoveAction);
    else
        event->setDropAction(Qt::CopyAction);
    event->accept();
}

void QTableMarginal::dragMoveEvent(QDragMoveEvent *event)
{
    QTableWidget::dragMoveEvent(event);
    if(qobject_cast<QTableMarginal*>(event->source())!=0)
        event->setDropAction(Qt::MoveAction);
    else
        event->setDropAction(Qt::CopyAction);
    event->accept();
}


void QTableMarginal::dropEvent(QDropEvent *event)
{
    insert_marginal(get_product_code(event), rowAt(event->pos().y()));
    if(qobject_cast<QTableMarginal*>(event->source())!=0)
        event->setDropAction(Qt::MoveAction);
    else
        event->setDropAction(Qt::CopyAction);
    event->accept();

    int current_row = rowAt(event->pos().y());
    if (current_row < 0)
        current_row = this->rowCount()-1;
    this->setCurrentCell(current_row, 0);
    this->setFocus(Qt::OtherFocusReason);
}





void QTableMarginal::mousePressEvent(QMouseEvent *event)
{
    QWidget* w = dynamic_cast<QWidget*>(this->parent());
    if(w)       w->raise();
    if(columnAt(event->pos().x())>=0  &&  rowAt(event->pos().y())>=0)
    {
        startPos = event->pos();
        QTableWidgetItemProduct* i = dynamic_cast<QTableWidgetItemProduct*>(this->item(rowAt(startPos.y()), 0));
        if (i)          startDragId = i->id;
    }
    QTableWidget::mousePressEvent(event);
}

void QTableMarginal::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    startPos = QPoint(-1,-1);
}

void QTableMarginal::mouseMoveEvent(QMouseEvent *event)
{
    QTableWidget::mouseMoveEvent(event);

    if (rowAt(event->pos().y())<0)      return;

    if ((event->buttons() & Qt::LeftButton)  &&  startPos.x()>=0  &&  startPos.y()>=0)
    {
        int distance = (event->pos() - startPos).manhattanLength();
        if (this->currentRow() >=0  &&  distance >= QApplication::startDragDistance()+5)
            start_drag();
    }
}

void QTableMarginal::start_drag(void)
{
    QMimeData* mimeData = new QMimeData;
    QTableWidgetItemProduct* item = dynamic_cast<QTableWidgetItemProduct*>(this->item(rowAt(startPos.y()), columnAt(startPos.x())));
    if (item)
    {
        mimeData->setText(dragProductText(item->product_code));
        QDrag* drag = new QDrag(this);
        drag->setMimeData(mimeData);

        //if (this->currentRow()!=this->rowCount()-1)
        {
            QRect rect(this->visualItemRect(this->item(this->currentRow(), 0)));
            int oldheight = rect.height();
            QPixmap pixmap (rect.size());
            rect.setY(rect.y()+horizontalHeader()->height());
            rect.setHeight(oldheight);
            this->render(&pixmap, QPoint(0, 0), rect);
            drag->setPixmap(pixmap);
        }

        if(drag->exec(Qt::CopyAction | Qt::MoveAction) == Qt::MoveAction)
            remove_row(startDragId);
    }
}

void QTableMarginal::remove_row(int id)
{
    mtk::list< mtk::CountPtr<marginal_in_table> >::iterator it = marginals.begin();
    while (it != marginals.end())
    {
        if ((*it)->id == id)
        {
            marginals.erase(it);
            break;
        }
        ++it;
    }

    for(int i=0; i<rowCount();++i)
    {
        QTableWidgetItemProduct* item = dynamic_cast<QTableWidgetItemProduct*>(this->item(i, 0));
        if(item  && item->id == id)
        {
            removeRow(i);
            break;
        }
    }
    adjust_pajama();
}

void QTableMarginal::adjust_pajama(void)
{
    mtk::list< mtk::CountPtr<marginal_in_table> >::iterator it =  marginals.begin();
    while (it != marginals.end())
    {
        if ( ((*it)->get_row()+1)%3 == 0)
            (*it)->set_normal_color();
            //(*it)->set_dark_color();
        else
            (*it)->set_normal_color();
        ++it;
    }
}



void QTableMarginal::contextMenuEvent ( QContextMenuEvent * event )
{
    if (rowAt(event->pos().y())<0)      return;

    if (currentRow() <0)        return;

    QMenu menu(this);
    QAction* action;
    action = new QAction("buy", this);
    connect(action, SIGNAL(triggered()), this, SLOT(request_buy()));
    menu.addAction(action);

    action = new QAction("sell", this);
    connect(action, SIGNAL(triggered()), this, SLOT(request_sell()));
    menu.addAction(action);
    menu.exec(event->globalPos());
}

void QTableMarginal::request_buy (void)
{
    QTableWidgetItemProduct* item = dynamic_cast<QTableWidgetItemProduct*>(this->item(currentRow(), 0));
    if (item)
    {
        mtk::msg::sub_product_code product_code = item->product_code;
        if (mtk::msg::is_valid(product_code)==false)      return;

        mtk::trd::msg::sub_position_ls     pos(
                                                          mtk::FixedNumber(mtk::fnDouble(100.),  mtk::fnDec(2),  mtk::fnInc(1))
                                                        , mtk::FixedNumber(mtk::fnDouble(10)  ,  mtk::fnDec(0),  mtk::fnInc(1))
                                                        , mtk::trd::msg::buy);

        mtk::trd::trd_cli_ord_book::rq_nw_ls_manual(product_code, pos, "cli_ref");
    }
}

void QTableMarginal::request_sell(void)
{
    QTableWidgetItemProduct* item = dynamic_cast<QTableWidgetItemProduct*>(this->item(currentRow(), 0));
    if (item)
    {
        mtk::msg::sub_product_code product_code = item->product_code;
        if (mtk::msg::is_valid(product_code)==false)      return;

        mtk::trd::msg::sub_position_ls     pos(
                                                          mtk::FixedNumber(mtk::fnDouble(100.),  mtk::fnDec(2),  mtk::fnInc(1))
                                                        , mtk::FixedNumber(mtk::fnDouble(10)  ,  mtk::fnDec(0),  mtk::fnInc(1))
                                                        , mtk::trd::msg::sell);

        mtk::trd::trd_cli_ord_book::rq_nw_ls_manual(product_code, pos, "cli_ref");
    }
}


void QTableMarginal::make_transparent(void)
{
    this->setStyleSheet("background-color: rgb(191,219,255, 150);");
    mtk::list< mtk::CountPtr<marginal_in_table> >::iterator it =  marginals.begin();
    while (it != marginals.end())
    {
        (*it)->set_normal_color(0);
        ++it;
    }
}

void QTableMarginal::remove_transparency(void)
{
    this->setStyleSheet("background-color: rgb(191,219,255);");
    mtk::list< mtk::CountPtr<marginal_in_table> >::iterator it =  marginals.begin();
    while (it != marginals.end())
    {
        (*it)->set_normal_color();
        ++it;
    }
}

