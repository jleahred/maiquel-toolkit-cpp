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
#include <QMessageBox>
#include <QSignalMapper>

#include <iostream>
#include <iomanip>

#include "components/trading/trd_cli_ord_book.h"
#include "qt_components/src/qmtk_misc.h"
#include "qt_components/src/qcommontabledelegate.h"
#include "components/trading/accounts/account_manager_cli.h"

#include "support/vector.hpp"
#include "yaml/yaml.h"







namespace {
    const char*   VERSION = "2011-03-16";

    const char*   MODIFICATIONS =
                        "           2011-03-16     first version\n"
                        "           2012-02-28     added last and company\n";


    static int  col_count =10;

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


    QColor  color_product = qtmisc::mtk_color_header;
    const QColor  color_qty     = Qt::white;
    //const QColor  color_qty     = QColor(237,240,249);
    //const QColor  color_price   = mtk_color_header;
    const QColor  color_price   =  QColor(240,245,250);//QColor(Qt::lightGray).lighter(125);



};  //namespace  {





void QHeaderView_hidding_cols::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton)
    {
        QMenu menu(this);
        QSignalMapper *signalMapper = new QSignalMapper(this);
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(hide_show_col(int)));

        for(int i=1; i<this->count(); ++i)
        {
            QAction* action_col = new QAction(names.at(i), this);
            action_col->setCheckable(true);
            menu.addAction(action_col);
            signalMapper->setMapping(action_col, i);
            connect(action_col, SIGNAL(triggered()), signalMapper, SLOT(map()));
            if(this->sectionSize(i) == 0)
            {
                if(i==count()-1)
                    this->resizeSection(i, 20);
                else
                    this->resizeSection(i, 100);
                this->hideSection(i);
            }
            if(this->isSectionHidden(i) == false)
                action_col->setChecked(true);
            else
                action_col->setChecked(false);
        }

        menu.exec(e->globalPos());
        e->accept();
    }

    QHeaderView::mousePressEvent(e);
}


void  QHeaderView_hidding_cols::hide_show_col(int logicalIndex)
{
    if(isSectionHidden(logicalIndex) == false)
        this->hideSection(logicalIndex);
    else
        this->showSection(logicalIndex);

    setResizeMode(QHeaderView::Interactive);
    resizeSection(this->logicalIndex(count()-1-hiddenSectionCount()), 10);
    setResizeMode(this->logicalIndex(count()-1-hiddenSectionCount()), QHeaderView::Fixed);
    setStretchLastSection(true);
}




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
    this->setGeometry(QRect(5, 5, 100*4+150+2*5-2, 300-2));
    this->setAcceptDrops(true);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(5,5,5,5);
    this->setLayout(layout);
    layout->addWidget(table_marginals);

    connect(this, SIGNAL(signal_start_moving()), SLOT(make_transparent()));
    connect(this, SIGNAL(signal_stop_moving()), SLOT(remove_transparent()));
    this->inserting_components_ended();

    //this->setFocusProxy(table_marginals);
}

QMarginal::~QMarginal()
{
}



QTableMarginal::QTableMarginal(QWidget *parent)
    : QTableWidget(parent), startPos(-1,-1),
      action_buy(0), action_sell(0), action_hit_the_bid(0), action_lift_the_offer(0), action_remove_product(0),
      action_buy_market(0), action_sell_market(0),
      paint_delegate(new QCommonTableDelegate(this)),
      showing_menu(false)
{
    this->setAcceptDrops(true);

    setItemDelegate(paint_delegate);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setShowGrid(false);

    {
        setRowCount(0);
        verticalHeader()->setVisible(false);
        horizontalHeader()->setVisible(true);
        //table_marginals->setSelectionMode(QAbstractItemView::NoSelection);
        //verticalHeader()->setDefaultSectionSize(QFontMetrics(this->font()).height()*1.6);
        verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
        //horizontalHeader()->setDefaultSectionSize(100);
        //this->horizontalHeader()->setResizeMode(this->columnCount()-1, QHeaderView::Stretch);
        //this->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        //this->horizontalHeader()->setResizeMode(0, QHeaderView::Interactive);
        slot_sectionMoved(0,0,0);


        setColumnCount(col_count);
        #define QMARG_INIT_HEADER_ITEM(__COLUMN__, __TEXT__) \
        {   \
            item = new QTableWidgetItem(); \
            item->setText(__TEXT__);   \
            setHorizontalHeaderItem(__COLUMN__, item);   \
            col_names.append(__TEXT__);                 \
        }

        QList<QString> col_names;
        {
            QTableWidgetItem *item=0;
            QMARG_INIT_HEADER_ITEM(0, tr("Product"))
            QMARG_INIT_HEADER_ITEM(1, tr("Qty bid"))
            QMARG_INIT_HEADER_ITEM(2, tr("BID")    )
            QMARG_INIT_HEADER_ITEM(3, tr("ASK")    )
            QMARG_INIT_HEADER_ITEM(4, tr("Qty ask"))
            QMARG_INIT_HEADER_ITEM(5, tr("Last"))
            QMARG_INIT_HEADER_ITEM(6, tr("L.qty"))
            QMARG_INIT_HEADER_ITEM(7, tr("Ref.pr."))
            QMARG_INIT_HEADER_ITEM(8, tr("var"))
            QMARG_INIT_HEADER_ITEM(9, tr("%var"))
        }
        setHorizontalHeader(new QHeaderView_hidding_cols(col_names, Qt::Horizontal, this));
        horizontalHeader()->resizeSection(0, 150);

        horizontalHeader()->setMovable(true);
    }
    this->setFrameShape(QFrame::NoFrame);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(this->horizontalHeader(), SIGNAL(sectionMoved(int,int,int)), this, SLOT(slot_sectionMoved(int,int,int)));

    action_buy = new QAction(tr("buy"), this);
    connect(action_buy, SIGNAL(triggered()), this, SLOT(request_buy()));
    this->addAction(action_buy);
    if(mtk::admin::is_production() == false)
        action_buy->setShortcut(Qt::Key_F4);


    action_sell = new QAction(tr("sell"), this);
    connect(action_sell, SIGNAL(triggered()), this, SLOT(request_sell()));
    this->addAction(action_sell);
    if(mtk::admin::is_production() == false)
        action_sell->setShortcut(Qt::Key_F5);

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


    action_remove_product = new QAction(tr("remove product"), this);
    action_remove_product->setShortcut(Qt::Key_Delete);
    connect(action_remove_product, SIGNAL(triggered()), this, SLOT(slot_remove_current_row()));
    this->addAction(action_remove_product);
    this->disable_actions();
    this->slot_sectionMoved(0,0,0);

}





marginal_in_table::marginal_in_table(QTableWidget* _table_widget, const mtk::msg::sub_product_code& product_code, int row)
    : id(++counter), table_widget(_table_widget), pending_screen_update(false),
      prev_painted_prices(mtk::prices::msg::__internal_get_default((mtk::prices::msg::sub_best_prices*)0)),
      prev_painted_last(mtk::prices::msg::__internal_get_default((mtk::prices::msg::sub_last_mk_execs_ticker*)0)),
      last_blinking(mtk::dtNowLocal()-mtk::dtDays(300))
{
    tw_product      = new QTableWidgetItemProduct(product_code, this->id);
    tw_BID          = new QTableWidgetItem();
    tw_ASK          = new QTableWidgetItem();
    tw_qty_bid      = new QTableWidgetItem();
    tw_qty_ask      = new QTableWidgetItem();
    tw_last_price   = new QTableWidgetItem();
    tw_last_quantity= new QTableWidgetItem();
    tw_ref_price    = new QTableWidgetItem();
    tw_var          = new QTableWidgetItem();
    tw_var_percent  = new QTableWidgetItem();


    mtk::dtDateTime  now = mtk::dtNowLocal();
    for(int i=0; i<col_count; ++i)
        v_blinking.push_back(now - mtk::dtDays(30));

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
    table_widget->setItem(row, 5, tw_last_price);
    table_widget->setItem(row, 6, tw_last_quantity);
    table_widget->setItem(row, 7, tw_ref_price);
    table_widget->setItem(row, 8, tw_var);
    table_widget->setItem(row, 9, tw_var_percent);


    //QFont font(table_widget->font());
    //font.setBold(true);
    {
        tw_product->setText(QLatin1String(MTK_SS(product_code.market << "." << product_code.product).c_str()));
        QFont font(tw_product->font());
        font.setBold(true);
        tw_product->setFont(font);
        tw_product->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    //font.setPointSize(10);
    {
        QFont font(tw_BID->font());
        font.setBold(true);
        tw_BID->setFont(font);
        tw_BID->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tw_BID->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    {
        QFont font(tw_ASK->font());
        font.setBold(true);
        tw_ASK->setFont(font);
        tw_ASK->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tw_ASK->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    {
        //QFont font(tw_qty_bid->font());
        //font.setBold(true);
        //tw_qty_bid->setFont(font);
        tw_qty_bid->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tw_qty_bid->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    {
        //QFont font(tw_qty_ask->font());
        //font.setBold(true);
        //tw_qty_ask->setFont(font);
        tw_qty_ask->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tw_qty_ask->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }

    {
        tw_last_price->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tw_last_price->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    {
        tw_last_quantity->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tw_last_quantity->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    {
        tw_ref_price->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tw_ref_price->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    {
        tw_var->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tw_var->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    {
        tw_var_percent->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        tw_var_percent->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }

    price_manager = mtk::make_cptr(new mtk::prices::price_manager(product_code));
    MTK_CONNECT_THIS(price_manager->signal_best_prices_update,   on_best_prices);
    MTK_CONNECT_THIS(price_manager->signal_last_mk_execs_ticker, on_last_mk_execs_ticker_msg);

    update_prices               (price_manager->get_best_prices());
    update_last_mk_execs_ticker (price_manager->get_last_mk_execs_ticker());

    MTK_TIMER_1D(check_for_pending_screen_update)

    MTK_TIMER_1D(check_blinking);
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
    tw_last_price->setBackgroundColor(color_transparency(color_qty, transparency));
    tw_last_quantity->setBackgroundColor(color_transparency(color_qty, transparency));
    tw_ref_price->setBackgroundColor(color_transparency(color_qty, transparency));
    tw_var->setBackgroundColor(color_transparency(color_qty, transparency));
    tw_var_percent->setBackgroundColor(color_transparency(color_qty, transparency));

    if((price_manager.isValid()==false)  ||  (price_manager.isValid()  &&  price_manager->get_best_prices().HasValue()==false))
    {
        tw_BID->setBackgroundColor(color_transparency(qtmisc::mtk_color_null, transparency));
        tw_ASK->setBackgroundColor(color_transparency(qtmisc::mtk_color_null, transparency));
        tw_qty_bid->setBackgroundColor(color_transparency(qtmisc::mtk_color_null, transparency));
        tw_qty_ask->setBackgroundColor(color_transparency(qtmisc::mtk_color_null, transparency));
        tw_last_price->setBackgroundColor(color_transparency(qtmisc::mtk_color_null, transparency));
        tw_last_quantity->setBackgroundColor(color_transparency(qtmisc::mtk_color_null, transparency));
        tw_ref_price->setBackgroundColor(color_transparency(qtmisc::mtk_color_null, transparency));
        tw_var->setBackgroundColor(color_transparency(qtmisc::mtk_color_null, transparency));
        tw_var_percent->setBackgroundColor(color_transparency(qtmisc::mtk_color_null, transparency));
    }
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
    tw_last_price->setBackgroundColor(color_qty.darker(105));
    tw_last_quantity->setBackgroundColor(color_qty.darker(105));
    tw_ref_price->setBackgroundColor(color_qty.darker(105));
    tw_var->setBackgroundColor(color_qty.darker(105));
    tw_var_percent->setBackgroundColor(color_qty.darker(105));
}








void marginal_in_table::clean_prices(void)
{
    tw_ASK->setText(QLatin1String(""));
    tw_qty_ask->setText(QLatin1String(""));
    tw_BID->setText(QLatin1String(""));
    tw_qty_bid->setText(QLatin1String(""));

    tw_last_price->setText(QLatin1String(""));
    tw_last_quantity->setText(QLatin1String(""));
    tw_ref_price->setText(QLatin1String(""));
    tw_var->setText(QLatin1String(""));
    tw_var_percent->setText(QLatin1String(""));

    tw_ASK->setBackgroundColor(qtmisc::mtk_color_null);
    tw_qty_ask->setBackgroundColor(qtmisc::mtk_color_null);
    tw_BID->setBackgroundColor(qtmisc::mtk_color_null);
    tw_qty_bid->setBackgroundColor(qtmisc::mtk_color_null);

    tw_last_price->setBackgroundColor(qtmisc::mtk_color_null);
    tw_last_quantity->setBackgroundColor(qtmisc::mtk_color_null);
    tw_ref_price->setBackgroundColor(qtmisc::mtk_color_null);
    tw_var->setBackgroundColor(qtmisc::mtk_color_null);
    tw_var_percent->setBackgroundColor(qtmisc::mtk_color_null);
    prev_painted_prices = mtk::prices::msg::__internal_get_default((mtk::prices::msg::sub_best_prices*)0);
}

void marginal_in_table::update_prices(const mtk::prices::msg::sub_best_prices&   best_prices)
{
    //table_widget->setUpdatesEnabled(false);
    //try
    //{

    if(best_prices.bids.level0.price != prev_painted_prices.bids.level0.price)
    {
        if(best_prices.bids.level0.quantity.GetIntCode() != 0)
            tw_BID->setText(qtmisc::fn_as_QString(best_prices.bids.level0.price));
        else
            tw_BID->setText(QLatin1String(""));
    }
    if(best_prices.bids.level0.quantity != prev_painted_prices.bids.level0.quantity)
    {
        if(best_prices.bids.level0.quantity.GetIntCode() != 0)
            tw_qty_bid->setText(qtmisc::fn_as_QString(best_prices.bids.level0.quantity));
        else
            tw_qty_bid->setText(QLatin1String(""));
    }

    if(best_prices.asks.level0.price != prev_painted_prices.asks.level0.price)
    {
        if(best_prices.asks.level0.quantity.GetIntCode() != 0)
            tw_ASK->setText(qtmisc::fn_as_QString(best_prices.asks.level0.price));
        else
            tw_ASK->setText(QLatin1String(""));
    }

    if(best_prices.asks.level0.quantity != prev_painted_prices.asks.level0.quantity)
    {
        if(best_prices.asks.level0.quantity.GetIntCode() != 0)
            tw_qty_ask->setText(qtmisc::fn_as_QString(best_prices.asks.level0.quantity));
        else
            tw_qty_ask->setText(QLatin1String(""));
    }

    if(tw_BID->backgroundColor() == qtmisc::mtk_color_null)
    {
        tw_ASK->setBackgroundColor(color_price);
        tw_qty_ask->setBackgroundColor(color_qty);
        tw_BID->setBackgroundColor(color_price);
        tw_qty_bid->setBackgroundColor(color_qty);
    }
    generate_blinking(best_prices);     //  it will update  prev_painted_prices
    //}
    //catch(...)
    //{
    //    table_widget->setUpdatesEnabled(true);
    //    throw;
    //}
    //table_widget->setUpdatesEnabled(true);
}

void marginal_in_table::update_prices(const mtk::nullable<mtk::prices::msg::sub_best_prices>&   n_best_prices)
{
    if(n_best_prices.HasValue())
        update_prices(n_best_prices.Get());
    else
        clean_prices();
}



void marginal_in_table::clean_lasts(void)
{
    tw_last_price->setText      (QLatin1String(""));
    tw_last_quantity->setText   (QLatin1String(""));
    tw_ref_price->setText       (QLatin1String(""));
    tw_var->setText             (QLatin1String(""));
    tw_var_percent->setText     (QLatin1String(""));
    if(tw_last_price->backgroundColor() == qtmisc::mtk_color_null)
    {
        tw_last_price->setBackgroundColor(color_qty);
        tw_last_quantity->setBackgroundColor(color_qty);
        tw_ref_price->setBackgroundColor(color_qty);
        tw_var->setBackgroundColor(color_qty);
        tw_var_percent->setBackgroundColor(color_qty);
    }
}

void marginal_in_table::update_last_mk_execs_ticker(const mtk::prices::msg::sub_last_mk_execs_ticker&   last_mk_execs_ticker)
{
    if(last_mk_execs_ticker.last_quantity.GetDouble() == 0  &&  last_mk_execs_ticker.last_price.GetDouble() == 0)
        clean_lasts();
    else
    {
        if(prev_painted_last.last_price != last_mk_execs_ticker.last_price)
            tw_last_price->setText(qtmisc::fn_as_QString(last_mk_execs_ticker.last_price));
        if(prev_painted_last.last_quantity != last_mk_execs_ticker.last_quantity)
            tw_last_quantity->setText(qtmisc::fn_as_QString(last_mk_execs_ticker.last_quantity));
        if(prev_painted_last.opened_price != last_mk_execs_ticker.opened_price)
            tw_ref_price->setText(qtmisc::fn_as_QString(last_mk_execs_ticker.opened_price));

        if(prev_painted_last.last_quantity != last_mk_execs_ticker.last_quantity   ||  prev_painted_last.opened_price != last_mk_execs_ticker.opened_price)
        {
            mtk::Double  var = last_mk_execs_ticker.last_price.GetDouble() - last_mk_execs_ticker.opened_price.GetDouble();
            tw_var->setText( QLocale::system().toString(var.get2(), 'f', 3));
            tw_var_percent->setText(  QLocale::system().toString(var.get2() / last_mk_execs_ticker.opened_price.GetDouble().get2(), 'f', 2) + QLatin1String("%") );
        }

        if(tw_last_price->backgroundColor() == qtmisc::mtk_color_null)
        {
            tw_last_price->setBackgroundColor(color_qty);
            tw_last_quantity->setBackgroundColor(color_qty);
            tw_ref_price->setBackgroundColor(color_qty);
            tw_var->setBackgroundColor(color_qty);
            tw_var_percent->setBackgroundColor(color_qty);
        }
    }
    prev_painted_last = last_mk_execs_ticker;
}



void marginal_in_table::update_last_mk_execs_ticker(const mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>&   n_last_mk_execs_ticker)
{
    if(n_last_mk_execs_ticker.HasValue())
        update_last_mk_execs_ticker(n_last_mk_execs_ticker.Get());
    else
        clean_lasts();
}




void marginal_in_table::on_best_prices(const mtk::msg::sub_product_code& /*pc*/, const mtk::prices::msg::sub_best_prices& /*msg*/)
{
    pending_screen_update = true;
}


void marginal_in_table::on_last_mk_execs_ticker_msg(const mtk::msg::sub_product_code& /*pc*/, const mtk::prices::msg::sub_last_mk_execs_ticker& /*msg*/)
{
    pending_screen_update = true;
}




void marginal_in_table::check_for_pending_screen_update(void)
{
    if(pending_screen_update   &&   price_manager.get2())
    {
        //MTK_EXEC_MAX_FREC(mtk::dtMilliseconds(200))
            update_prices(price_manager->get_best_prices());
            update_last_mk_execs_ticker(price_manager->get_last_mk_execs_ticker());
            pending_screen_update = false;
        //MTK_END_EXEC_MAX_FREC
    }
}







void marginal_in_table::add_blinking(int col, const mtk::DateTime&  till)
{
    if(till > last_blinking)
        last_blinking = till;
    v_blinking[col] = till;
}

void marginal_in_table::check_blinking(void)
{
    //MTK_EXEC_MAX_FREC(mtk::dtMilliseconds(200))
        static  mtk::DateTime    one_year_before = mtk::dtNowLocal() - mtk::dtDays(300);
        mtk::DateTime  one_hour_before = mtk::dtNowLocal() - mtk::dtHours(1);
        int pending_blinkings = 0;
        mtk::dtDateTime  now = mtk::dtNowLocal();

        if(last_blinking > one_hour_before)
        {
            #define  CHECK_BLINKING(__COL__, __TW__)  \
                    if(v_blinking[__COL__] > one_hour_before)     \
                    {     \
                          if(v_blinking[__COL__] < now)        \
                          {     \
                                v_blinking[__COL__] = one_year_before;     \
                                if(__COL__ == 2  ||  __COL__ == 3)     \
                                    __TW__->setBackgroundColor(color_price);     \
                                else     \
                                    __TW__->setBackgroundColor(color_qty);     \
                                __TW__->setForeground(QBrush());    \
                          }       \
                          else     \
                              ++pending_blinkings;\
                    }

            CHECK_BLINKING(1, tw_qty_bid)
            CHECK_BLINKING(2, tw_BID)
            CHECK_BLINKING(3, tw_ASK)
            CHECK_BLINKING(4, tw_qty_ask)

            if(pending_blinkings == 0)
                last_blinking = one_year_before;
        }
    //MTK_END_EXEC_MAX_FREC
}


void marginal_in_table::generate_blinking(const mtk::prices::msg::sub_best_prices&  prices)
{
    mtk::DateTime  now = mtk::dtNowLocal();

    #define BLINKING(__BID_ASK__, __PRICE_QUANTITY__, __ITEM__, __COL__)    \
    {       \
        int  prev_quantity = prev_painted_prices.__BID_ASK__.level0.quantity.GetIntCode();  \
        int  new_quantity  = prices.__BID_ASK__.level0.quantity.GetIntCode();   \
        if(prices.__BID_ASK__.level0.__PRICE_QUANTITY__ != prev_painted_prices.__BID_ASK__.level0.__PRICE_QUANTITY__    \
           ||   ( prev_quantity*new_quantity == 0   &&  prev_quantity+new_quantity != 0))    \
        {    \
            __ITEM__->setBackgroundColor(qtmisc::mtk_color_blinking2);    \
            __ITEM__->setForeground(QBrush(QColor(191,219,255)));    \
            add_blinking(__COL__, now + mtk::dtMilliseconds(200));    \
        }       \
    }


    BLINKING(bids, quantity,  tw_qty_bid, 1)
    BLINKING(bids, price,     tw_BID,     2)
    BLINKING(asks, price,     tw_ASK,     3)
    BLINKING(asks, quantity,  tw_qty_ask, 4)

    prev_painted_prices = prices;
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
    insert_marginal(qtmisc::get_product_code(event), rowAt(event->pos().y()));
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
        mimeData->setText(qtmisc::dragProductText(item->product_code));
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
    menu.addAction(action_remove_product);


    //  permisions
    mtk::msg::sub_product_code product_code (get_current_product_code());
    std::string grant = mtk::accmgrcli::get_grant_less_restrictive(product_code.market);
    if(grant=="F")
        enable_trading_actions();
    else
        disable_trading_actions();


    showing_menu = true;
    menu.exec(event->globalPos());
    showing_menu = false;
    this->setFocus();
    enable_actions();
}

void QTableMarginal::keyPressEvent ( QKeyEvent * event )
{
    //QAbstractItemView::
    if(event->key() == Qt::Key_Up)
    {
        if(this->currentRow() > 0)
            this->setCurrentCell(this->currentRow()-1, 0);
    }
    else if(event->key() == Qt::Key_Down)
    {
        if(this->currentRow() < this->rowCount()-1)
            this->setCurrentCell(this->currentRow()+1, 0);
    }
    event->setAccepted(true);
}


mtk::CountPtr<mtk::prices::price_manager>     locate_price_manager (const mtk::list< mtk::CountPtr<marginal_in_table> >& marginals, int id)
{
    for(mtk::list< mtk::CountPtr<marginal_in_table> >::const_iterator it=marginals.begin(); it!= marginals.end(); ++it)
    {
        if((*it)->id == id)
            return (*it)->price_manager;
    }

    //  not located
    return mtk::CountPtr<mtk::prices::price_manager>();
}



void QTableMarginal::request_side(mtk::trd::msg::enBuySell bs)
{
    QTableWidgetItemProduct* item = dynamic_cast<QTableWidgetItemProduct*>(this->item(currentRow(), 0));
    if (item)
    {
        mtk::msg::sub_product_code product_code = item->product_code;
        if (mtk::msg::is_valid(product_code)==false)      return;


        //  proposed price
        mtk::CountPtr<mtk::prices::price_manager>  price_manager =   locate_price_manager(marginals, item->id);
        if(price_manager.isValid() == false  ||  price_manager->get_best_prices().HasValue() == false)
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "marginal", "marginal not located", mtk::alPriorError));
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
            mtk::trd::trd_cli_ord_book::rq_nw_ls_manual(product_code, bs, pos);
        }

    }
}


void QTableMarginal::request_buy (void)
{
    paint_delegate->keep_focus_paint(true);
    request_side(mtk::trd::msg::buy);
    paint_delegate->keep_focus_paint(false);
}

void QTableMarginal::request_sell(void)
{
    paint_delegate->keep_focus_paint(true);
    request_side(mtk::trd::msg::sell);
    paint_delegate->keep_focus_paint(false);
}




void QTableMarginal::request_aggression(mtk::trd::msg::enBuySell bs)
{
    QTableWidgetItemProduct* item = dynamic_cast<QTableWidgetItemProduct*>(this->item(currentRow(), 0));
    if (item)
    {
        mtk::msg::sub_product_code product_code = item->product_code;
        if (mtk::msg::is_valid(product_code)==false)      return;


        //  proposed price
        mtk::CountPtr<mtk::prices::price_manager>  price_manager =   locate_price_manager(marginals, item->id);
        if(price_manager.isValid() == false  ||  price_manager->get_best_prices().HasValue() == false)
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
                mtk::trd::trd_cli_ord_book::rq_nw_ls_manual(product_code, bs, pos, true);
            }
            else
            {
                //   nothing
            }
        }

    }
}


void QTableMarginal::request_hit_the_bid(void)
{
    paint_delegate->keep_focus_paint(true);
    request_aggression(mtk::trd::msg::sell);
    paint_delegate->keep_focus_paint(false);
}

void QTableMarginal::request_lift_the_offer(void)
{
    paint_delegate->keep_focus_paint(true);
    request_aggression(mtk::trd::msg::buy);
    paint_delegate->keep_focus_paint(false);
}


void QTableMarginal::make_transparent(void)
{
    mtk::list< mtk::CountPtr<marginal_in_table> >::iterator it =  marginals.begin();
    while (it != marginals.end())
    {
        (*it)->set_normal_color(0);
        ++it;
    }
}



void QTableMarginal::request_side_market(mtk::trd::msg::enBuySell bs)
{
    QTableWidgetItemProduct* item = dynamic_cast<QTableWidgetItemProduct*>(this->item(currentRow(), 0));
    if (item)
    {
        mtk::msg::sub_product_code product_code = item->product_code;
        if (mtk::msg::is_valid(product_code)==false)      return;


        //  proposed price
        mtk::CountPtr<mtk::prices::price_manager>  price_manager =   locate_price_manager(marginals, item->id);
        if(price_manager.isValid() == false  ||  price_manager->get_best_prices().HasValue() == false)
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "marginal", "marginal not located", mtk::alPriorError));
        else
        {
            mtk::FixedNumber quantity(price_manager->get_best_prices().Get().bids.level0.quantity);
            if(bs == mtk::trd::msg::sell)
                quantity= price_manager->get_best_prices().Get().asks.level0.quantity;
            if(quantity.GetIntCode() != 0)    quantity.SetIntCode(-1);        //  means, default quantity
            mtk::trd::msg::sub_position_mk     pos(quantity, "" /*cli ref*/);
            mtk::trd::trd_cli_ord_book::rq_nw_mk_manual(product_code, bs, pos);
        }
    }
}


void QTableMarginal::request_buy_market(void)
{
    paint_delegate->keep_focus_paint(true);
    request_side_market(mtk::trd::msg::buy);
    paint_delegate->keep_focus_paint(false);
}

void QTableMarginal::request_sell_market(void)
{
    paint_delegate->keep_focus_paint(true);
    request_side_market(mtk::trd::msg::sell);
    paint_delegate->keep_focus_paint(false);
}





void QTableMarginal::remove_transparency(void)
{
    mtk::list< mtk::CountPtr<marginal_in_table> >::iterator it =  marginals.begin();
    while (it != marginals.end())
    {
        (*it)->set_normal_color();
        ++it;
    }
}

void QTableMarginal::disable_actions(void)
{
    if(showing_menu==false)
    {
        if(action_buy)
        {
            disable_trading_actions();
            action_remove_product->setEnabled(false);
        }
    }
}

void QTableMarginal::enable_actions(void)
{
    if(action_remove_product)
    {
        enable_trading_actions();
        action_remove_product->setEnabled(true);
    }
}

void QTableMarginal::disable_trading_actions(void)
{
    if(showing_menu==false)
    {
        if(action_buy)
        {
            action_buy->setEnabled(false);
            action_sell->setEnabled(false);
            action_hit_the_bid->setEnabled(false);
            action_lift_the_offer->setEnabled(false);
            action_sell_market->setEnabled(false);
            action_buy_market->setEnabled(false);
            action_remove_product->setEnabled(false);
        }
    }
}

void QTableMarginal::enable_trading_actions(void)
{
    if(action_buy)
    {
        action_buy->setEnabled(true);
        action_sell->setEnabled(true);
        action_hit_the_bid->setEnabled(true);
        action_lift_the_offer->setEnabled(true);
        action_sell_market->setEnabled(true);
        action_buy_market->setEnabled(true);
        action_remove_product->setEnabled(true);
    }
}


void QTableMarginal::slot_remove_current_row(void)
{
    QTableWidgetItemProduct* i = dynamic_cast<QTableWidgetItemProduct*>(this->item(this->currentRow(), 0));
    if (i)
    {
        paint_delegate->keep_focus_paint(true);
        try
        {
            if(QMessageBox::warning(this, QLatin1String("CimdTrade"), tr("Do you want to remove the current product from this table?"), QMessageBox::Ok, QMessageBox::Cancel)==QMessageBox::Ok)
                this->remove_row(i->id);
        }
        catch(...)
        {
            paint_delegate->keep_focus_paint(false);
            throw;
        }
        paint_delegate->keep_focus_paint(false);
    }
}


mtk::msg::sub_product_code   QTableMarginal::get_current_product_code(void)
{
    QTableWidgetItemProduct* item = dynamic_cast<QTableWidgetItemProduct*>(this->item(currentRow(), 0));
    if (item)
    {
        mtk::msg::sub_product_code product_code = item->product_code;
        if (mtk::msg::is_valid(product_code)==false)
            return mtk::msg::sub_product_code("", "");
        else
            return product_code;
    }
    return mtk::msg::sub_product_code("", "");
}





YAML::Emitter& operator << (YAML::Emitter& out, const QTableMarginal& m)
{
    out     << YAML::BeginMap;

    //  writing products
    out << YAML::Key   <<  "products"
        << YAML::Value << YAML::BeginSeq;

        for(int i=0; i<m.rowCount(); ++i)
    {
        QTableWidgetItemProduct* iproduct = dynamic_cast<QTableWidgetItemProduct*>(m.item(i, 0));
        if(iproduct!=0)
        {
            out <<  iproduct->product_code;
        }

    }
    out << YAML::EndSeq;
    //  end products

    //  writing sections sizes
    out << YAML::Key   <<  "sect_sizes"
            << YAML::Value << YAML::Flow  << YAML::BeginSeq;
    for(int i=0; i<m.horizontalHeader()->count()-1; ++i)
    {
        out << m.horizontalHeader()->sectionSize(i);
    }
    out << YAML::EndSeq;
    //  writing sections sizes

    out << YAML::EndMap;
    return out;
}

void             operator >> (const YAML::Node&   node,        QTableMarginal& m)
{
    for(unsigned i=0; i< node["products"].size(); ++i)
    {
        mtk::msg::sub_product_code pc = mtk::msg::__internal_get_default((mtk::msg::sub_product_code*)0);
        node["products"][i] >> pc;
        m.add_marginal(pc);
    }
    for(unsigned i=0; i< node["sect_sizes"].size(); ++i)
    {
        int sect_size;
        node["sect_sizes"][i] >> sect_size;
        m.horizontalHeader()->resizeSection(i, sect_size);
    }
    m.slot_sectionMoved(0,0,0);
}



YAML::Emitter& operator << (YAML::Emitter& out, const QMarginal& m)
{
    //if(m.table_marginals->rowCount() == 0)      return out;


    out     << YAML::BeginMap;

    //  writing component
    out << YAML::Key   <<  "component" << YAML::Value << static_cast<const mtkContainerWidget&>(m);
    //  end component

    //  writing QTableMarginal
    if(m.table_marginals)
        out << YAML::Key   <<  "qtablemarginal"  << YAML::Value   << *(m.table_marginals);
    //  end QTableMarginal


    out << YAML::EndMap;

    return out;
}


void             operator >> (const YAML::Node&   node,       QMarginal& m)
{
    node["component"] >> static_cast<mtkContainerWidget&>(m);
    node["qtablemarginal"] >>  (*m.table_marginals);
}



void QTableMarginal::slot_sectionMoved ( int /*logicalIndex*/, int /*oldVisualIndex*/, int /*newVisualIndex*/ )
{
    this->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
    horizontalHeader()->resizeSection(horizontalHeader()->logicalIndex(horizontalHeader()->count()-1), 10);
    this->horizontalHeader()->setResizeMode(horizontalHeader()->logicalIndex(horizontalHeader()->count()-1), QHeaderView::Fixed);
    horizontalHeader()->setStretchLastSection(true);
}



void QTableMarginal::focusOutEvent(QFocusEvent *e)
{
    this->update();
    disable_actions();
    QTableWidget::focusOutEvent(e);
}

void QTableMarginal::focusInEvent (QFocusEvent *e)
{
    this->update();
    enable_actions();
    QTableWidget::focusInEvent(e);
}


