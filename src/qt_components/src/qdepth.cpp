#include "qdepth.h"

#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QAction>
#include <QLabel>
#include <QApplication>
#include <QMenu>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QPen>

#include <iostream>


#include "components/trading/trd_cli_ord_book.h"
#include "qt_components/src/qmtk_misc.h"







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

    struct register_global_commands
    {
        register_global_commands (void)
        {
            mtk::admin::register_command("__GLOBAL__",  "ver",   "")->connect(command_version);
            mtk::admin::register_command("__GLOBAL__",  "modifs",   "")->connect(command_modifications);
        }
    };
    register_global_commands rc;

}       //  anonymous namespace  to register "static" commnads












namespace  {

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


mtk::prices::msg::best_prices    get_emtpy_best_prices   (void)
{
    return mtk::prices::msg::best_prices(
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




class QDepthDelegate : public QStyledItemDelegate
{
public:
    QDepthDelegate(QObject * parent) : QStyledItemDelegate(parent){};
protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
private:
};



void QDepthDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    //  remove focus
    QStyleOptionViewItem ViewOption(option);
    if (ViewOption.state & QStyle::State_HasFocus)
        ViewOption.state = ViewOption.state ^ QStyle::State_HasFocus;
    QStyledItemDelegate::paint(painter, ViewOption, index);
}



}; // namespace  {




class QTableDeph : public QTableWidget
{
public:
    QTableDeph(QDepth* _depth) : QTableWidget(_depth), depth(_depth) {     this->setItemDelegate(new QDepthDelegate(this));  }
    void mousePressEvent(QMouseEvent *event)   {
        raise();
        depth->mousePressEvent(event);
        QTableWidget::mousePressEvent(event);
        QWidget* w = dynamic_cast<QWidget*>(this->parent());
        if(w)
        {
            w->raise();
            w->setFocus(Qt::OtherFocusReason);
            //this->setFocus(Qt::OtherFocusReason);
        }
    }
    void mouseReleaseEvent(QMouseEvent *event) { depth->mouseReleaseEvent(event);  QTableWidget::mouseReleaseEvent(event); }
    void mouseMoveEvent(QMouseEvent *event)    { depth->mouseMoveEvent(event);     QTableWidget::mouseMoveEvent(event);    }


protected:

private:

    QDepth* depth;
};








QDepth::QDepth(QWidget *parent) :
    mtkContainerWidget(parent),
    product_code(get_empty_product_code()),
    table_widget(new QTableDeph(this))
{
    this->setGeometry(QRect(5, 5, 290, 300));
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(5,5,5,5);
    this->setLayout(layout);
    //QPalette p(palette());
    //p.setColor(QPalette::Base, Qt::blue);
    //setPalette(p);

    this->setAcceptDrops(true);

    {
        title = new QLabel(this);
        //QPalette titlePalette = title->palette();
        //titlePalette.setColor(QPalette::Foreground, Qt::white);
        //titlePalette.setColor(QPalette::Foreground, QColor(0,0,0));
        //titlePalette.setColor(QPalette::Text, QColor(0,0,0));
        //title->setPalette(titlePalette);
        layout->addWidget(title);
        title->setAlignment(Qt::AlignCenter);
        title->setAutoFillBackground(true);
        title->setFrameShape(QFrame::Box);
        title->setFrameShadow(QFrame::Plain);
        //title->setStyleSheet("color: rgba(30,0,100); background-color: rgba(207,213,235, 200);");
        title->setStyleSheet("color: rgba(30,0,100); background-color: rgba(191,219,255, 230); font-weight: 1000;");
        //QFont font=title->font();
        //font.setBold(true);
        //title->setFont(font);
        title->setMargin(3);
    }

    {
        layout->addWidget(table_widget);
        table_widget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 30);\n" "color: rgb(0, 220, 0);"));
        table_widget->setRowCount(10);
        table_widget->setColumnCount(3);
        table_widget->verticalHeader()->setVisible(false);
        table_widget->horizontalHeader()->setVisible(false);
        table_widget->setSelectionMode(QAbstractItemView::NoSelection);
        table_widget->verticalHeader()->setDefaultSectionSize(20);
        table_widget->horizontalHeader()->setDefaultSectionSize(20);
        table_widget->setShowGrid(false);
        //QPalette p(table_widget->palette());
        //QPalette p;
        //p.setColor(QPalette::Base, Qt::black);
        //p.setColor(QPalette::Base, QColor(0,0,0,100));
        //p.setColor(QPalette::, Qt::black);
        //table_widget->setPalette(p);
        //  setting up actions
        /*
        table_widget->setContextMenuPolicy(Qt::ActionsContextMenu);
        {
            QAction* action = new QAction("buy", this);
            connect(action, SIGNAL(triggered()), this, SLOT(request_buy()));
            table_widget->addAction(action);
        }
        {
            QAction* action = new QAction("sell", this);
            connect(action, SIGNAL(triggered()), this, SLOT(request_sell()));
            table_widget->addAction(action);
        }
        */
        for (int col=0; col<table_widget->columnCount(); col++)
        {
            for (int row=0; row<table_widget->rowCount(); row++)
            {
                QTableWidgetItem* item = new QTableWidgetItem;
                item->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
                QFont font(item->font());
                font.setBold(true);
                //font.setPointSize(11);
                item->setFont(font);
                //item->setBackgroundColor(Qt::black);
                //item->setForeground(QColor(Qt::green).lighter());
                //item->setForeground(QColor(207,213,235));
                item->setForeground(QColor(191,219,255));
                //if (col==1  ||  (col==0 &&  row>4)  ||  (col==2 &&  row<=4))
                //    item->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsEnabled);
                //else
                //    item->setFlags(Qt::ItemIsDragEnabled);
                item->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsEnabled);
                table_widget->setItem(row, col, item);
            }
        }
    }


    this->inserting_components_ended();

    on_message(get_emtpy_best_prices());

    connect(this, SIGNAL(signal_start_moving()), SLOT(make_transparent()));
    connect(this, SIGNAL(signal_stop_moving()), SLOT(remove_transparecy()));

}

QDepth::~QDepth()
{
}


void	QDepth::resizeEvent ( QResizeEvent *  event )
{
    mtkContainerWidget::resizeEvent(event);
    table_widget->verticalHeader()->setDefaultSectionSize(table_widget->height()/10-1);
    table_widget->horizontalHeader()->setDefaultSectionSize(table_widget->width()/3-2);
}





void write_in_cell(int row, int qty_col, const mtk::prices::msg::sub_price_level& level, QTableWidget* table_widget)
{
    if (level.price.GetIntCode()!=0  &&  level.quantity.GetIntCode() != 0)
    {
        table_widget->item(row, 1)->setText(fn_as_QString(level.price));
        table_widget->item(row, qty_col)->setText(fn_as_QString(level.quantity));
    }
    else
    {
        table_widget->item(row, 1)->setText("");
        table_widget->item(row, qty_col)->setText("");
    }
}


void QDepth::on_message(const mtk::prices::msg::best_prices& msg)
{
    write_in_cell(5, 0, msg.bids.level0, table_widget);
    write_in_cell(6, 0, msg.bids.level1, table_widget);
    write_in_cell(7, 0, msg.bids.level2, table_widget);
    write_in_cell(8, 0, msg.bids.level3, table_widget);
    write_in_cell(9, 0, msg.bids.level4, table_widget);

    write_in_cell(4, 2, msg.asks.level0, table_widget);
    write_in_cell(3, 2, msg.asks.level1, table_widget);
    write_in_cell(2, 2, msg.asks.level2, table_widget);
    write_in_cell(1, 2, msg.asks.level3, table_widget);
    write_in_cell(0, 2, msg.asks.level4, table_widget);

}


void QDepth::request_buy(void)
{
    if (mtk::msg::is_valid(product_code)==false)      return;

    mtk::trd::msg::sub_position_ls     pos(
                                                      mtk::FixedNumber(mtk::fnDouble(100.),  mtk::fnDec(2),  mtk::fnInc(1))
                                                    , mtk::FixedNumber(mtk::fnDouble(10)  ,  mtk::fnDec(0),  mtk::fnInc(1))
                                                    , mtk::trd::msg::buy);

    mtk::trd::trd_cli_ord_book::rq_nw_ls_manual(product_code, pos, "cli_ref");
}

void QDepth::request_sell(void)
{
    if (mtk::msg::is_valid(product_code)==false)      return;

    mtk::trd::msg::sub_position_ls     pos(
                                                      mtk::FixedNumber(mtk::fnDouble(100.),  mtk::fnDec(2),  mtk::fnInc(1))
                                                    , mtk::FixedNumber(mtk::fnDouble(10)  ,  mtk::fnDec(0),  mtk::fnInc(1))
                                                    , mtk::trd::msg::sell);

    mtk::trd::trd_cli_ord_book::rq_nw_ls_manual(product_code, pos, "cli_ref");
}



void QDepth::dragEnterEvent(QDragEnterEvent *event)
{
    event->setDropAction(Qt::CopyAction);
    event->accept();
}

void QDepth::dropEvent(QDropEvent *event)
{
    subscribe_to(get_product_code(event));
}

void QDepth::subscribe_to (const mtk::msg::sub_product_code& _product_code)
{
    product_code = _product_code;
    title->setText(MTK_SS(product_code.sys_code.market << "."<<product_code.sys_code.user_name).c_str());
    MTK_QPID_RECEIVER_CONNECT_THIS(
                            h_best_prices,
                            mtk::admin::get_url("client"),
                            "CLITESTING",
                            mtk::prices::msg::best_prices::get_in_subject(product_code.sys_code.market, product_code.sys_code.product),
                            mtk::prices::msg::best_prices,
                            on_message)

}


void QDepth::mousePressEvent(QMouseEvent *event)
{
    startPos = event->pos();
    mtkContainerWidget::mousePressEvent(event);
}

void QDepth::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    startPos = QPoint(-1,-1);
}

void QDepth::mouseMoveEvent(QMouseEvent *event)
{
    mtkContainerWidget::mouseMoveEvent(event);
    if ((event->buttons() & Qt::LeftButton)  &&  startPos.x()>=0  &&  startPos.y()>=0)
    {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance()+5  &&  mtk::msg::is_valid(product_code))
        {
            QMimeData* mimeData = new QMimeData;
            mimeData->setText(dragProductText(product_code));
            QDrag* drag = new QDrag(this);
            drag->setMimeData(mimeData);

            QPixmap pixmap (title->size());
            title->render(&pixmap);
            drag->setPixmap(pixmap);

            drag->exec(Qt::CopyAction);
        }
    }
}

void QDepth::contextMenuEvent ( QContextMenuEvent * event )
{
    if (mtk::msg::is_valid(product_code)== false)  return;

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


void QDepth::make_transparent(void)
{
    title->setStyleSheet("color: rgba(30,0,100); background-color: rgba(191,219,255, 150); font-weight: 400;");
    table_widget->setStyleSheet(QString::fromUtf8("background-color: rgb(0,0,30, 150);\n" "color: rgb(0, 220, 0);"));
}

void QDepth::remove_transparecy(void)
{
    title->setStyleSheet("color: rgba(30,0,100); background-color: rgba(191,219,255, 230); font-weight: 1000;");
    table_widget->setStyleSheet(QString::fromUtf8("background-color: rgb(0,0,30);\n" "color: rgb(0, 220, 0);"));
}


/*
void QDepth::paintEvent   (QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter qpainter(this);

    QColor color = mtk_yellow;
    if (this->hasFocus())
        color = Qt::blue;
    QPen pen = QPen(color, 1, Qt::SolidLine);
    qpainter.setPen(pen);
    qpainter.drawLine(4, 4, 4, this->height()-5);
    qpainter.drawLine(4, 4, this->width()-5, 4);
    qpainter.drawLine(this->width()-5, 4, this->width()-5, this->height()-5);
    qpainter.drawLine(4, this->height()-5, this->width()-5, this->height()-5);
}
*/
