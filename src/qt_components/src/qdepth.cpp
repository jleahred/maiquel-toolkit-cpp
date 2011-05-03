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
#include "yaml/yaml.h"







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












namespace  {




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
    table_widget(new QTableDeph(this)),
    action_buy(0), action_sell(0), action_hit_the_bid(0), action_lift_the_offer(0),
    showing_menu(false),
    keep_paint_focus(false)
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
        title->setBackgroundRole(QPalette::Light);
        title->setAlignment(Qt::AlignCenter);
        title->setAutoFillBackground(true);
        title->setFrameShape(QFrame::Box);
        title->setFrameShadow(QFrame::Plain);
        //title->setStyleSheet("color: rgba(30,0,100); background-color: rgba(207,213,235, 200);");
        title->setStyleSheet(QLatin1String("color: rgba(30,0,100); background-color: rgba(191,219,255, 230); font-weight: 1000;"));
        title->setLineWidth(2);
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

    connect(this, SIGNAL(signal_start_moving()), SLOT(make_transparent()));
    connect(this, SIGNAL(signal_stop_moving()), SLOT(remove_transparecy()));



    action_buy = new QAction(tr("buy"), this);
    action_buy->setShortcut(Qt::Key_Plus);
    connect(action_buy, SIGNAL(triggered()), this, SLOT(request_buy()));
    this->addAction(action_buy);

    action_sell = new QAction(tr("sell"), this);
    action_sell->setShortcut(Qt::Key_Minus);
    connect(action_sell, SIGNAL(triggered()), this, SLOT(request_sell()));
    this->addAction(action_sell);

    action_lift_the_offer = new QAction(tr("lift the offer"), this);
    action_lift_the_offer->setShortcut(Qt::Key_F8);
    connect(action_lift_the_offer, SIGNAL(triggered()), this, SLOT(request_lift_the_offer()));
    this->addAction(action_lift_the_offer);

    action_hit_the_bid = new QAction(tr("hit the bid"), this);
    action_hit_the_bid->setShortcut(Qt::Key_F12);
    connect(action_hit_the_bid, SIGNAL(triggered()), this, SLOT(request_hit_the_bid()));
    this->addAction(action_hit_the_bid);
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





void write_in_cell(int row, int price_col, const mtk::prices::msg::sub_price_level& level, QTableWidget* table_widget)
{
    if (level.price.GetIntCode()!=0  &&  level.quantity.GetIntCode() != 0)
    {
        table_widget->item(row, price_col)->setText(fn_as_QString(level.price));
        table_widget->item(row, 1)->setText(fn_as_QString(level.quantity));
    }
    else
    {
        table_widget->item(row, price_col)->setText(QLatin1String(""));
        table_widget->item(row, 1)->setText(QLatin1String(""));
    }
}


void QDepth::on_message(const mtk::prices::msg::pub_best_prices& msg)
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


void QDepth::request_side(mtk::trd::msg::enBuySell bs)
{
    //  proposed price
    if(price_manager.isValid() == false)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qdepth", "marginal not located", mtk::alPriorError));
    else
    {
        mtk::FixedNumber price(price_manager->get_best_prices().bids.level0.price);
        mtk::FixedNumber quantity(price_manager->get_best_prices().bids.level0.quantity);
        if(bs == mtk::trd::msg::sell)
        {
            price = price_manager->get_best_prices().asks.level0.price;
            quantity= price_manager->get_best_prices().asks.level0.quantity;
        }
        if(quantity.GetIntCode() != 0)
        {
            quantity.SetIntCode(1);
            mtk::trd::msg::sub_position_ls     pos(
                                                              price
                                                            , quantity
                                                            , bs);
            mtk::trd::trd_cli_ord_book::rq_nw_ls_manual(price_manager->get_product_code(), pos, "cli_ref");
        }
        else
        {
            mtk::trd::msg::sub_position_ls     pos(
                                                              mtk::FixedNumber(mtk::fnDouble(0.),  mtk::fnDec(2),  mtk::fnInc(1))
                                                            , mtk::FixedNumber(mtk::fnDouble(0.)  ,  mtk::fnDec(0),  mtk::fnInc(1))
                                                            , bs);
            mtk::trd::trd_cli_ord_book::rq_nw_ls_manual(price_manager->get_product_code(), pos, "cli_ref");
        }
    }

}


void QDepth::request_buy(void)
{
    keep_paint_focus = true;
    request_side(mtk::trd::msg::buy);
    keep_paint_focus = false;
}

void QDepth::request_sell(void)
{
    keep_paint_focus = true;
    request_side(mtk::trd::msg::sell);
    keep_paint_focus = false;
}



void QDepth::request_aggression(mtk::trd::msg::enBuySell bs)
{
    //  proposed price
    if(price_manager.isValid() == false)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "marginal", "marginal not located", mtk::alPriorError));
    else
    {
        mtk::FixedNumber price(price_manager->get_best_prices().bids.level0.price);
        mtk::FixedNumber quantity(price_manager->get_best_prices().bids.level0.quantity);
        if(bs == mtk::trd::msg::buy)
        {
            price = price_manager->get_best_prices().asks.level0.price;
            quantity= price_manager->get_best_prices().asks.level0.quantity;
        }
        if(quantity.GetIntCode() != 0)
        {
            quantity.SetIntCode(1);
            mtk::trd::msg::sub_position_ls     pos(
                                                              price
                                                            , quantity
                                                            , bs);
            mtk::trd::trd_cli_ord_book::rq_nw_ls_manual(price_manager->get_product_code(), pos, "cli_ref", true);
        }
        else
        {
               //   nothing
        }
    }
}



void QDepth::request_hit_the_bid(void)
{
    keep_paint_focus = true;
    request_aggression(mtk::trd::msg::sell);
    keep_paint_focus = false;
}

void QDepth::request_lift_the_offer(void)
{
    keep_paint_focus = true;
    request_aggression(mtk::trd::msg::buy);
    keep_paint_focus = false;
}



void QDepth::dragEnterEvent(QDragEnterEvent *event)
{
    event->setDropAction(Qt::CopyAction);
    event->accept();
}

void QDepth::dropEvent(QDropEvent *event)
{
    subscribe_to(get_product_code(event));
    this->setFocus();
}

void QDepth::subscribe_to (const mtk::msg::sub_product_code& _product_code)
{
    if(price_manager.isValid())
        price_manager->signal_best_prices_update.disconnect(this, &QDepth::on_message);
    price_manager = mtk::get_from_factory<mtk::prices::price_manager>(_product_code);
    MTK_CONNECT_THIS(price_manager->signal_best_prices_update, on_message);

    on_message(price_manager->get_best_prices());
    title->setText(QLatin1String(MTK_SS(price_manager->get_product_code().sys_code.market << "."<< price_manager->get_product_code().sys_code.user_name).c_str()));
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
    if(price_manager.isValid() == false)        return;


    mtkContainerWidget::mouseMoveEvent(event);
    if ((event->buttons() & Qt::LeftButton)  &&  startPos.x()>=0  &&  startPos.y()>=0)
    {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance()+5  &&  mtk::msg::is_valid(price_manager->get_product_code()))
        {
            QMimeData* mimeData = new QMimeData;
            mimeData->setText(dragProductText(price_manager->get_product_code()));
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
    if (price_manager.isValid() == false)      return;

    QMenu menu(this);
    menu.addAction(action_buy);
    menu.addAction(action_sell);


    {
        QAction* action = new QAction(&menu);
        action->setSeparator(true);
        menu.addAction(action);
    }

    menu.addAction(action_lift_the_offer);
    menu.addAction(action_hit_the_bid);
    showing_menu = true;
    keep_paint_focus = true;
    menu.exec(event->globalPos());
    keep_paint_focus = false;
    showing_menu = false;
    this->setFocus();
    enable_actions();
}


void QDepth::make_transparent(void)
{
    title->setStyleSheet(QLatin1String("color: rgba(30,0,100); background-color: rgba(191,219,255, 150); font-weight: 400;"));
    table_widget->setStyleSheet(QString::fromUtf8("background-color: rgb(0,0,30, 150);\n" "color: rgb(0, 220, 0);"));
}

void QDepth::remove_transparecy(void)
{
    this->setFocus();
    paint_focus();
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

void QDepth::disable_actions(void)
{
    if(showing_menu==false)
    {
        if(action_buy)
        {
            action_buy->setEnabled(false);
            action_sell->setEnabled(false);
            action_hit_the_bid->setEnabled(false);
            action_lift_the_offer->setEnabled(false);
        }
    }
}

void QDepth::enable_actions(void)
{
    if(action_buy)
    {
        action_buy->setEnabled(true);
        action_sell->setEnabled(true);
        action_hit_the_bid->setEnabled(true);
        action_lift_the_offer->setEnabled(true);
    }
}

void QDepth::paint_focus(void)
{
    //title->setStyleSheet(QLatin1String("background-color: rgba(120,150,210); color: rgba(191,219,255, 230); font-weight: 1000;"));
    title->setStyleSheet(QLatin1String("background-color: rgba(120,150,210); color: rgba(255,255,255); font-weight: 1000;"));
    table_widget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 70);\n" "color: rgb(0, 220, 0);"));
}

void QDepth::remove_focus(void)
{
    if(keep_paint_focus==false)
    {
        title->setStyleSheet(QLatin1String("color: rgba(30,0,100); background-color: rgba(191,219,255, 230); font-weight: 1000;"));
        table_widget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 30);\n" "color: rgb(0, 220, 0);"));
    }
}


YAML::Emitter& operator << (YAML::Emitter& out, const QDepth& m)
{
    out     << YAML::BeginMap;

    //  writing component
    out << YAML::Key   <<  "component" << YAML::Value << static_cast<const mtkContainerWidget&>(m);
    //  end component

    //  writing product
    if(m.price_manager.isValid())
        out << YAML::Key   <<  "product_code"  << YAML::Value   << m.price_manager->get_product_code();
    //  end product


    out << YAML::EndMap;

    return out;
}

void             operator >> (const YAML::Node&   node,       QDepth& d)
{
    node["component"] >> static_cast<mtkContainerWidget&>(d);

    mtk::msg::sub_product_code pc = mtk::msg::__internal_get_default((mtk::msg::sub_product_code*)0);
    node["product_code"] >> pc;
    d.subscribe_to(pc);
}
