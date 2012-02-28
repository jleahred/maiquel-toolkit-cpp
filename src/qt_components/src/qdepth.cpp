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
#include <QVBoxLayout>

#include <iostream>


#include "components/trading/trd_cli_ord_book.h"
#include "qt_components/src/qmtk_misc.h"
#include "components/trading/accounts/account_manager_cli.h"
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




class QTableDeph : public QTableWidget, public mtk::SignalReceptor
{
    typedef  QTableDeph   CLASS_NAME;


public:
    QTableDeph(QDepth* _depth)
            :   QTableWidget(_depth),
                depth(_depth),
                last_blinking(mtk::dtNowLocal()-mtk::dtDays(300)),
                prev_painted_prices(mtk::prices::msg::__internal_get_default((mtk::prices::msg::sub_best_prices*)0))
    {
        mtk::DateTime  now = mtk::dtNowLocal();
        for(int i=0; i<3*10; ++i)
            v_blinking.push_back(now - mtk::dtDays(30));

        this->setItemDelegate(new QDepthDelegate(this));
        MTK_TIMER_1D(check_blinking);
    }
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

    void generate_blinking(const mtk::prices::msg::sub_best_prices&  prices);

protected:

private:

    QDepth* depth;

    std::vector<mtk::DateTime>  v_blinking;
    mtk::DateTime               last_blinking;

    void add_blinking(int row, int col, const mtk::DateTime&  till);
    void check_blinking(void);
    mtk::prices::msg::sub_best_prices  prev_painted_prices;     //  for blinking
};




void QTableDeph::add_blinking(int row, int col, const mtk::DateTime&  till)
{
    if(till > last_blinking)
        last_blinking = till;
    v_blinking[row*3 + col] = till;
}

void QTableDeph::check_blinking(void)
{
    //MTK_EXEC_MAX_FREC(mtk::dtMilliseconds(200))
        static  mtk::DateTime    one_year_before = mtk::dtNowLocal() - mtk::dtDays(300);
        mtk::DateTime  one_hour_before = mtk::dtNowLocal() - mtk::dtHours(1);
        mtk::DateTime  now = mtk::dtNowLocal();
        int pending_blinkings = 0;

        if(last_blinking > one_hour_before)
        {
            for(int i=0; i<3*10; ++i)
            {
                if(v_blinking[i] > one_hour_before)
                {
                    if(v_blinking[i] < now)
                    {
                        v_blinking[i] = one_year_before;
                        int row = i/3;
                        int col = i%3;
                        this->item(row, col)->setBackground(QBrush());
                    }
                    else
                        ++pending_blinkings;
                }
            }
            if(pending_blinkings == 0)
                last_blinking = one_year_before;
        }
    //MTK_END_EXEC_MAX_FREC
}


void QTableDeph::generate_blinking(const mtk::prices::msg::sub_best_prices&  prices)
{
    mtk::DateTime  now = mtk::dtNowLocal();
    //  marginals
    #define BLINKING_MARGINALS(__BID_ASK__, __ROW__, __COL__)     \
        {       \
                int  prev_quantity = prev_painted_prices.__BID_ASK__.level0.quantity.GetIntCode();       \
                int  new_quantity  = prices.__BID_ASK__.level0.quantity.GetIntCode();       \
                bool  just_ONE_quantity_is_zero = (prev_quantity*new_quantity == 0   &&  prev_quantity+new_quantity != 0 );  \
                if(prices.__BID_ASK__.level0.price != prev_painted_prices.__BID_ASK__.level0.price  ||   just_ONE_quantity_is_zero)       \
                {       \
                    int row=__ROW__;  int col=__COL__;       \
                    item(row, col)->setBackgroundColor(qtmisc::mtk_color_blinking);       \
                    add_blinking(row, col, now + mtk::dtMilliseconds(200));       \
                    item(row, 1)->setBackgroundColor(qtmisc::mtk_color_blinking);       \
                    add_blinking(row, 1, now + mtk::dtMilliseconds(200));       \
                }       \
                else       \
                {       \
                    if(prices.__BID_ASK__.level0.quantity != prev_painted_prices.__BID_ASK__.level0.quantity)       \
                    {       \
                        int row=__ROW__;  int col=1;       \
                        item(row, col)->setBackgroundColor(qtmisc::mtk_color_blinking);       \
                        add_blinking(row, col, now + mtk::dtMilliseconds(200));       \
                    }       \
                }       \
        }
    BLINKING_MARGINALS(bids, 5, 0)
    BLINKING_MARGINALS(asks, 4, 2)



    #define BLINKING_NO_MARGINALS(__level__, __prev_level__, __next_level__)       \
        if(prices.bids.level##__level__.quantity.GetIntCode() != 0)     \
        {                \
            if(     prices.bids.level##__level__.price != prev_painted_prices.bids.level##__level__.price       \
                    &&  prices.bids.level##__level__.price != prev_painted_prices.bids.level##__prev_level__.price       \
                    &&  prices.bids.level##__level__.price != prev_painted_prices.bids.level##__next_level__.price)       \
            {       \
                int row=5 + __level__;  int col=0;       \
                item(row, col)->setBackgroundColor(qtmisc::mtk_color_blinking);       \
                add_blinking(row, col, now + mtk::dtMilliseconds(200));       \
                item(row, 1)->setBackgroundColor(qtmisc::mtk_color_blinking);       \
                add_blinking(row, 1, now + mtk::dtMilliseconds(200));       \
            }       \
            else if(    prices.bids.level##__level__.price    ==  prev_painted_prices.bids.level##__level__.price  &&      \
                   prices.bids.level##__level__.quantity !=  prev_painted_prices.bids.level##__level__.quantity  )       \
            {       \
                    int row=5 + __level__;        \
                item(row, 1)->setBackgroundColor(qtmisc::mtk_color_blinking);       \
                add_blinking(row, 1, now + mtk::dtMilliseconds(200));       \
            }       \
            else if(    prices.bids.level##__level__.price    ==  prev_painted_prices.bids.level##__prev_level__.price  &&      \
                   prices.bids.level##__level__.quantity !=  prev_painted_prices.bids.level##__prev_level__.quantity  )       \
            {       \
                int row=5 + __level__;         \
                item(row, 1)->setBackgroundColor(qtmisc::mtk_color_blinking);       \
                add_blinking(row, 1, now + mtk::dtMilliseconds(200));       \
            }       \
            else if(__level__!=4  &&    prices.bids.level##__level__.price    ==  prev_painted_prices.bids.level##__next_level__.price  &&      \
                   prices.bids.level##__level__.quantity !=  prev_painted_prices.bids.level##__next_level__.quantity  )       \
            {       \
                int row=5 + __level__;         \
                item(row, 1)->setBackgroundColor(qtmisc::mtk_color_blinking);       \
                add_blinking(row, 1, now + mtk::dtMilliseconds(200));       \
            }       \
        }          \
        if(prices.asks.level##__level__.quantity.GetIntCode() != 0)     \
        {                \
            if(     prices.asks.level##__level__.price != prev_painted_prices.asks.level##__level__.price       \
                    &&  prices.asks.level##__level__.price != prev_painted_prices.asks.level##__prev_level__.price       \
                    &&  prices.asks.level##__level__.price != prev_painted_prices.asks.level##__next_level__.price)       \
            {       \
                int row=4-__level__;  int col=2;       \
                item(row, col)->setBackgroundColor(qtmisc::mtk_color_blinking);       \
                add_blinking(row, col, now + mtk::dtMilliseconds(200));       \
                item(row, 1)->setBackgroundColor(qtmisc::mtk_color_blinking);       \
                add_blinking(row, 1, now + mtk::dtMilliseconds(200));       \
            }           \
            else if(    prices.asks.level##__level__.price    ==  prev_painted_prices.asks.level##__level__.price  &&      \
                   prices.asks.level##__level__.quantity !=  prev_painted_prices.asks.level##__level__.quantity  )       \
            {       \
                    int row=4-  __level__;        \
                item(row, 1)->setBackgroundColor(qtmisc::mtk_color_blinking);       \
                add_blinking(row, 1, now + mtk::dtMilliseconds(200));       \
            }       \
            else if(    prices.asks.level##__level__.price    ==  prev_painted_prices.asks.level##__prev_level__.price  &&      \
                   prices.asks.level##__level__.quantity !=  prev_painted_prices.asks.level##__prev_level__.quantity  )       \
            {       \
                int row=4- __level__;         \
                item(row, 1)->setBackgroundColor(qtmisc::mtk_color_blinking);       \
                add_blinking(row, 1, now + mtk::dtMilliseconds(200));       \
            }       \
            else if(__level__!=4  &&    prices.asks.level##__level__.price    ==  prev_painted_prices.asks.level##__next_level__.price  &&      \
                   prices.asks.level##__level__.quantity !=  prev_painted_prices.asks.level##__next_level__.quantity  )       \
            {       \
                int row=4- __level__;         \
                item(row, 1)->setBackgroundColor(qtmisc::mtk_color_blinking);       \
                add_blinking(row, 1, now + mtk::dtMilliseconds(200));       \
            }       \
    }


    //  not marginals
    BLINKING_NO_MARGINALS(1, 0, 2);
    BLINKING_NO_MARGINALS(2, 1, 3);
    BLINKING_NO_MARGINALS(3, 2, 4);
    BLINKING_NO_MARGINALS(4, 3, 4);

    prev_painted_prices = prices;
}



QDepth::QDepth(QWidget *parent) :
    mtkContainerWidget(parent),
    table_widget(new QTableDeph(this)),
    pending_screen_update(false),
    action_buy(0), action_sell(0), action_hit_the_bid(0), action_lift_the_offer(0),
    action_buy_market(0), action_sell_market(0), action_delete_component(0),
    showing_menu(false),
    keep_paint_focus(false)
{
    this->setGeometry(QRect(5, 5, 290-2, 300-2));
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(5,5,5,5);
    this->setLayout(layout);
    //QPalette p(palette());
    //p.setColor(QPalette::Base, Qt::blue);
    //setPalette(p);

    this->setAcceptDrops(true);

    {
        QString  snullcolor = QLatin1String("rgb(")+ QString::number(qtmisc::mtk_color_null.red()) + QLatin1String(", ") +
                                        QString::number(qtmisc::mtk_color_null.green()) + QLatin1String(", ") +
                                        QString::number(qtmisc::mtk_color_null.blue()) +  QLatin1String(");");
        style_sheet_null = QString::fromUtf8("background-color: ") + snullcolor  + QString::fromUtf8("\n" "color: rgb(0, 220, 0); font-weight: 1000;");
        style_sheet_normal = QString::fromUtf8("background-color: rgb(0, 0, 30);\n" "color: rgb(191,219,255); font-weight: 1000;");
    }

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
        //title->setFrameShape(QFrame::Box);
        //title->setFrameShadow(QFrame::Plain);
        //title->setStyleSheet("color: rgba(30,0,100); background-color: rgba(207,213,235, 200);");
        title->setStyleSheet(QLatin1String("color: rgba(30,0,100); background-color: rgba(191,219,255, 230); font-weight: 1000;"));
        title->setLineWidth(2);
        //QFont font=title->font();
        //font.setBold(true);
        //title->setFont(font);
        title->setMargin(3);
    }

    {
        //QHBoxLayout* layout_last = new QHBoxLayout(this);
        //layout_last->setSpacing(0);
        //layout_last->setContentsMargins(0,0,0,0);
        //layout->addLayout(layout_last);



        frame_last = new QFrame(this);
        layout->addWidget(frame_last);
        frame_last->setFrameShadow(QFrame::Plain);
        frame_last->setAutoFillBackground(true);
        frame_last->setFrameShape(QFrame::Box);
        frame_last->setFrameShadow(QFrame::Plain);
        frame_last->setLineWidth(1);
        frame_last->setStyleSheet(style_sheet_normal);
        QHBoxLayout*  layout_last = new QHBoxLayout(frame_last);
        layout_last->setSpacing(0);
        layout_last->setContentsMargins(0,0,0,0);

        last_price = new QLabel(this);
        layout_last->addWidget(last_price);
        last_price->setAlignment(Qt::AlignCenter);
        last_price->setAutoFillBackground(true);
        //last_price->setFrameShape(QFrame::Box);
        //last_price->setFrameShadow(QFrame::Plain);
        //last_price->setLineWidth(3);
        last_price->setStyleSheet(style_sheet_normal);
        last_price->setMargin(3);

        last_quantity = new QLabel(this);
        layout_last->addWidget(last_quantity);
        last_quantity->setAlignment(Qt::AlignCenter);
        last_quantity->setAutoFillBackground(true);
        //last_quantity->setFrameShape(QFrame::Box);
        //last_quantity->setFrameShadow(QFrame::Plain);
        //last_quantity->setLineWidth(3);
        last_quantity->setStyleSheet(style_sheet_normal);
        last_quantity->setMargin(3);
    }

    {
        layout->addWidget(table_widget);
        //table_widget->setStyleSheet(style_sheet_normal);//QString::fromUtf8("background-color: rgb(0, 0, 30);\n" "color: rgb(0, 220, 0);"));
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
    connect(action_buy, SIGNAL(triggered()), this, SLOT(request_buy()));
    this->addAction(action_buy);

    action_sell = new QAction(tr("sell"), this);
    connect(action_sell, SIGNAL(triggered()), this, SLOT(request_sell()));
    this->addAction(action_sell);

    action_lift_the_offer = new QAction(tr("lift the offer"), this);
    action_lift_the_offer->setShortcut(Qt::Key_Plus);
    connect(action_lift_the_offer, SIGNAL(triggered()), this, SLOT(request_lift_the_offer()));
    this->addAction(action_lift_the_offer);

    action_hit_the_bid = new QAction(tr("hit the bid"), this);
    action_hit_the_bid->setShortcut(Qt::Key_Minus);
    connect(action_hit_the_bid, SIGNAL(triggered()), this, SLOT(request_hit_the_bid()));
    this->addAction(action_hit_the_bid);

    action_buy_market = new QAction(tr("buy"), this);
    connect(action_buy_market, SIGNAL(triggered()), this, SLOT(request_buy_market()));
    this->addAction(action_buy_market);

    action_sell_market = new QAction(tr("sell"), this);
    connect(action_sell_market, SIGNAL(triggered()), this, SLOT(request_sell_market()));
    this->addAction(action_sell_market);

    action_delete_component = new QAction(tr("delete depth"), this);
    action_delete_component->setShortcut(Qt::Key_Delete);
    this->addAction(action_delete_component);


    this->disable_actions();
    remove_focus();


    MTK_TIMER_1D(check_for_pending_screen_update);
}

QDepth::~QDepth()
{
}



void	QDepth::resizeEvent ( QResizeEvent *  event )
{
    mtkContainerWidget::resizeEvent(event);
    table_widget->verticalHeader()->setDefaultSectionSize(table_widget->height()/10-1);
    //table_widget->horizontalHeader()->setDefaultSectionSize(table_widget->width()/3-2);
    table_widget->horizontalHeader()->resizeSection(0, table_widget->width()/3-2);
    table_widget->horizontalHeader()->resizeSection(1, table_widget->width()/3.7-2);
    table_widget->horizontalHeader()->resizeSection(2, table_widget->width()/2.7-2);
}






void delete_cells(QTableWidget* table_widget)
{
    for(int r=0;r<table_widget->rowCount(); ++r)
    {
        for(int c=0;c<table_widget->columnCount();++c)
        {
            table_widget->item(r, c)->setText(QLatin1String(""));
        }
    }
}


void write_in_cell(int row, int price_col, const mtk::prices::msg::sub_price_level& level, QTableDeph* table_widget, const mtk::msg::sub_product_code& product_code)
{
    mtk::dtDateTime  now  = mtk::dtNowLocal();
    if (level.quantity.GetIntCode() != 0)
    {
        QTableWidgetItem*  item_price = table_widget->item(row, price_col);
        QTableWidgetItem*  item_quantity = table_widget->item(row, 1);
        QString  new_price = qtmisc::fn_as_QString(level.price);
        QString  new_quantity = qtmisc::fn_as_QString(level.quantity);

        item_price->setText(new_price);
        item_quantity->setText(new_quantity);
    }
    else if(level.quantity.GetIntCode() == 0  &&   level.price.GetIntCode()!=0)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qdepth", MTK_SS("received quantity 0 with price not 0 on "  << product_code
                                                                << "  " << level), mtk::alPriorCritic, mtk::alTypeNoPermisions));
    }
    else
    {
        table_widget->item(row, price_col)->setText(QLatin1String(""));
        table_widget->item(row, 1)->setText(QLatin1String(""));
    }
}


void QDepth::on_message(const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_best_prices& /*msg*/)
{
    pending_screen_update = true;
}

void QDepth::check_for_pending_screen_update(void)
{
    if(pending_screen_update   &&   price_manager.get2())
    {
        //MTK_EXEC_MAX_FREC(mtk::dtMilliseconds(200))
            update_prices               (price_manager->get_best_prices());
            update_last_mk_execs_ticker (price_manager->get_last_mk_execs_ticker());
            pending_screen_update = false;
        //MTK_END_EXEC_MAX_FREC
    }
}




void QDepth::update_prices(const mtk::prices::msg::sub_best_prices&   best_prices)
{
    this->setUpdatesEnabled(false);
    try
    {
        table_widget->generate_blinking(best_prices);

        write_in_cell(9, 0, best_prices.bids.level4, table_widget, price_manager->get_product_code());
        write_in_cell(8, 0, best_prices.bids.level3, table_widget, price_manager->get_product_code());
        write_in_cell(7, 0, best_prices.bids.level2, table_widget, price_manager->get_product_code());
        write_in_cell(6, 0, best_prices.bids.level1, table_widget, price_manager->get_product_code());
        write_in_cell(5, 0, best_prices.bids.level0, table_widget, price_manager->get_product_code());

        write_in_cell(4, 2, best_prices.asks.level0, table_widget, price_manager->get_product_code());
        write_in_cell(3, 2, best_prices.asks.level1, table_widget, price_manager->get_product_code());
        write_in_cell(2, 2, best_prices.asks.level2, table_widget, price_manager->get_product_code());
        write_in_cell(1, 2, best_prices.asks.level3, table_widget, price_manager->get_product_code());
        write_in_cell(0, 2, best_prices.asks.level4, table_widget, price_manager->get_product_code());

        if(table_widget->styleSheet() == style_sheet_null)
            table_widget->setStyleSheet(style_sheet_normal);
    }
    catch(...)
    {
        this->setUpdatesEnabled(true);
        throw;
    }
    this->setUpdatesEnabled(true);
}

void QDepth::update_prices(const mtk::nullable<mtk::prices::msg::sub_best_prices>&   n_best_prices)
{
    if(n_best_prices.HasValue())
        update_prices(n_best_prices.Get());
    else
        upate_null_prices();
}
void QDepth::upate_null_prices(void)
{
    delete_cells(table_widget);
    table_widget->setStyleSheet(style_sheet_null);
}





void QDepth::update_last_mk_execs_ticker(const mtk::prices::msg::sub_last_mk_execs_ticker&   execs_ticker)
{
    if(execs_ticker.last_quantity.GetIntCode() == 0  &&  execs_ticker.last_price.GetIntCode() == 0)
    {
        last_price->setText(QLatin1String(""));
        last_quantity->setText(QLatin1String(""));
    }
    else
    {
        last_price->setText(qtmisc::fn_as_QString(execs_ticker.last_price));
        last_quantity->setText(qtmisc::fn_as_QString(execs_ticker.last_quantity));
    }
}

void QDepth::update_last_mk_execs_ticker(const mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>&   mk_execs_full_info)
{
    if(mk_execs_full_info.HasValue())
        update_last_mk_execs_ticker(mk_execs_full_info.Get());
    else
    {
        last_price->setText(QLatin1String(""));
        last_quantity->setText(QLatin1String(""));
    }
}




void QDepth::request_side(mtk::trd::msg::enBuySell bs)
{
    //  proposed price
    if(price_manager.isValid() == false  ||  price_manager->get_best_prices().HasValue()==false)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qdepth", "marginal not located", mtk::alPriorError));
    else
    {
        mtk::FixedNumber price(price_manager->get_best_prices().Get().bids.level0.price);
        mtk::FixedNumber quantity(price_manager->get_best_prices().Get().bids.level0.quantity);
        if(bs == mtk::trd::msg::sell)
        {
            price = price_manager->get_best_prices().Get().asks.level0.price;
            quantity= price_manager->get_best_prices().Get().asks.level0.quantity;
        }
        if(quantity.GetIntCode() != 0)    quantity.SetIntCode(-1);        //  means, default quantity
        mtk::trd::msg::sub_position_ls     pos(price, quantity, "" /*cli ref*/);
        mtk::trd::trd_cli_ord_book::rq_nw_ls_manual(price_manager->get_product_code(), bs, pos);
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



void QDepth::request_side_market(mtk::trd::msg::enBuySell bs)
{
    if(price_manager.isValid() == false  ||  price_manager->get_best_prices().HasValue()==false)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qdepth", "marginal not located", mtk::alPriorError));
    else
    {
        mtk::FixedNumber quantity(price_manager->get_best_prices().Get().bids.level0.quantity);
        if(bs == mtk::trd::msg::sell)
        {
            quantity= price_manager->get_best_prices().Get().asks.level0.quantity;
        }
        if(quantity.GetIntCode() != 0)    quantity.SetIntCode(-1);        //  means, default quantity
        mtk::trd::msg::sub_position_mk     pos(quantity, "" /*cli ref*/);
        mtk::trd::trd_cli_ord_book::rq_nw_mk_manual(price_manager->get_product_code(), bs, pos);
    }
}


void QDepth::request_buy_market(void)
{
    keep_paint_focus = true;
    request_side_market(mtk::trd::msg::buy);
    keep_paint_focus = false;
}

void QDepth::request_sell_market(void)
{
    keep_paint_focus = true;
    request_side_market(mtk::trd::msg::sell);
    keep_paint_focus = false;
}




void QDepth::request_aggression(mtk::trd::msg::enBuySell bs)
{
    //  proposed price
    if(price_manager.isValid() == false   ||   price_manager->get_best_prices().HasValue()==false)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "marginal", "marginal not located", mtk::alPriorError));
    else
    {
        mtk::FixedNumber price(price_manager->get_best_prices().Get().bids.level0.price);
        mtk::FixedNumber quantity(price_manager->get_best_prices().Get().bids.level0.quantity);
        if(bs == mtk::trd::msg::buy)
        {
            price = price_manager->get_best_prices().Get().asks.level0.price;
            quantity= price_manager->get_best_prices().Get().asks.level0.quantity;
        }
        if(quantity.GetIntCode() != 0)
        {
            quantity.SetIntCode(-1);        //  means, default quantity
            mtk::trd::msg::sub_position_ls     pos(price, quantity, "" /*cli ref*/);
            mtk::trd::trd_cli_ord_book::rq_nw_ls_manual(price_manager->get_product_code(), bs, pos, true);
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
    subscribe_to(qtmisc::get_product_code(event));
    this->setFocus();
}

void QDepth::subscribe_to (const mtk::msg::sub_product_code& _product_code)
{
    price_manager = mtk::make_cptr(new mtk::prices::price_manager(_product_code));
    MTK_CONNECT_THIS(price_manager->signal_best_prices_update, on_message);

    //  this will make a permanent suscription  for this prices_manager instance
    update_prices               (price_manager->get_best_prices());
    update_last_mk_execs_ticker (price_manager->get_last_mk_execs_ticker());
    title->setText(QLatin1String(MTK_SS(price_manager->get_product_code().market << "."<< price_manager->get_product_code().product).c_str()));
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
            mimeData->setText(qtmisc::dragProductText(price_manager->get_product_code()));
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


    menu.addSeparator();
    menu.addAction(action_lift_the_offer);
    menu.addAction(action_hit_the_bid);

    menu.addSeparator();
    QMenu sub_menu_market_orders(this);
    sub_menu_market_orders.setTitle(tr("Market orders"));
    sub_menu_market_orders.addAction(action_buy_market);
    sub_menu_market_orders.addAction(action_sell_market);
    menu.addMenu(&sub_menu_market_orders);

    menu.addSeparator();
    menu.addAction(action_delete_component);


    //  permisions
    mtk::msg::sub_product_code product_code (price_manager->get_product_code());
    std::string grant = mtk::accmgrcli::get_grant_less_restrictive(product_code.market);
    if(grant=="F")
        enable_trading_actions();
    else
        disable_trading_actions();

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
    frame_last->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 30,0 );\n" "color: rgb(191,219,255); font-weight: 1000;"));
    last_price->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 30,150 );\n" "color: rgb(191,219,255); font-weight: 1000;"));
    last_quantity->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 30,150 );\n" "color: rgb(191,219,255); font-weight: 1000;"));
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
            disable_trading_actions();
        }
    }
}

void QDepth::enable_actions(void)
{
    if(action_buy)
    {
        enable_trading_actions();
    }
}

void QDepth::disable_trading_actions(void)
{
    if(showing_menu==false)
    {
        if(action_buy)
        {
            action_buy->setEnabled(false);
            action_sell->setEnabled(false);
            action_hit_the_bid->setEnabled(false);
            action_lift_the_offer->setEnabled(false);
            action_buy_market->setEnabled(false);
            action_sell_market->setEnabled(false);
            action_delete_component->setEnabled(false);
        }
    }
}

void QDepth::enable_trading_actions(void)
{
    if(action_buy)
    {
        action_buy->setEnabled(true);
        action_sell->setEnabled(true);
        action_hit_the_bid->setEnabled(true);
        action_lift_the_offer->setEnabled(true);
        action_buy_market->setEnabled(true);
        action_sell_market->setEnabled(true);
        action_delete_component->setEnabled(true);
    }
}

void QDepth::paint_focus(void)
{
    //title->setStyleSheet(QLatin1String("background-color: rgba(120,150,210); color: rgba(191,219,255, 230); font-weight: 1000;"));
    title->setStyleSheet(QLatin1String("background-color: rgba(120,150,210); color: rgba(255,255,255, 255); font-weight: 1000;"));

    if(price_manager.isValid()==false)
        table_widget->setStyleSheet(style_sheet_null);
    else
        table_widget->setStyleSheet(style_sheet_normal);

    frame_last->setStyleSheet(style_sheet_normal);
    last_price->setStyleSheet(style_sheet_normal);
    last_quantity->setStyleSheet(style_sheet_normal);

}

void QDepth::remove_focus(void)
{
    if(keep_paint_focus==false)
    {
        title->setStyleSheet(QLatin1String("color: rgba(30,0,100); background-color: rgba(191,219,255, 230); font-weight: 1000;"));
        if(price_manager.isValid()   &&   price_manager->get_best_prices().HasValue()==true)
            table_widget->setStyleSheet(style_sheet_normal);
        else if(price_manager.isValid()==false)
            table_widget->setStyleSheet(style_sheet_null);
        else
            table_widget->setStyleSheet(style_sheet_normal);
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

    if(node.FindValue("product_code"))
    {
        mtk::msg::sub_product_code pc = mtk::msg::__internal_get_default((mtk::msg::sub_product_code*)0);
        node["product_code"] >> pc;
        d.subscribe_to(pc);
    }
}
