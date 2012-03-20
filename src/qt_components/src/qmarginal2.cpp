#include "qmarginal2.h"

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
//#include <QTableWidgetItem>

#include <iostream>
#include <iomanip>

#include "components/trading/trd_cli_ord_book.h"
#include "qt_components/src/qmtk_misc.h"
#include "qt_components/src/qcommontabledelegate.h"
#include "components/trading/accounts/account_manager_cli.h"
#include "qt_components/src/qmtk_misc.h"

#include "support/vector.hpp"
#include "yaml/yaml.h"











namespace {
    const char*   VERSION = "2011-03-16";

    const char*   MODIFICATIONS =
                        "           2011-03-16     first version\n"
                        "           2012-02-28     added last and company\n"
                        "           2012-03-15     performance\n"
                        ;


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











int marginal_in_table2::counter = 0;


namespace {


    QColor  color_product = qtmisc::mtk_color_header;
    const QColor  color_qty     = Qt::white;
    //const QColor  color_qty     = QColor(237,240,249);
    //const QColor  color_price   = mtk_color_header;
    const QColor  color_price   =  QColor(240,245,250);//QColor(Qt::lightGray).lighter(125);



    std::vector<QString>  col_names  = {    QObject::tr("Product"),
                                            QObject::tr("Qty bid"),
                                            QObject::tr("BID"),
                                            QObject::tr("ASK"),
                                            QObject::tr("Qty ask"),
                                            QObject::tr("Last"),
                                            QObject::tr("L.qty"),
                                            QObject::tr("Ref.pr."),
                                            QObject::tr("var"),
                                            QObject::tr("%var") };


    QColor  more_blue(const QColor& input_color)
    {
        QColor color = input_color;
        int new_red = color.red()-45 ;  new_red = new_red < 0 ? 0:  new_red;
        int new_green = color.green()-45;  new_green = new_green < 0 ? 0:  new_green;
        color.setRgb(new_red, new_green, color.blue());

        return color;
    }

};  //namespace  {




qmarginal_table_model::qmarginal_table_model(QObject *parent)
    : QAbstractTableModel(parent), last_updated_table(mtk::dtNowLocal() - mtk::dtHours(1))
{
    MTK_TIMER_1D(slot_update_screen)
}

int qmarginal_table_model::rowCount(const QModelIndex &  /*parent*/) const
{
    return  marginals.size();
}


int qmarginal_table_model::columnCount(const QModelIndex &  /*parent*/) const
{
    return col_names.size();
}


QVariant  qmarginal_table_model::data(const QModelIndex &index, int role) const
{
    static  QFont  bold_font = QFont();
    static  bool   just_first = false;
    if(just_first == false)
        bold_font.setBold(true);



    if(index.isValid() == false)
    {
        return QVariant();
    }
    if(role == Qt::TextAlignmentRole)
    {
        if(index.column() == 0)
            return int(Qt::AlignLeft  |  Qt::AlignVCenter);
        else
            return int(Qt::AlignRight  |  Qt::AlignVCenter);
    }
    else if(role == Qt::FontRole)
    {
        if(index.column() == 0  ||  index.column() == 2  ||  index.column() == 3)
            return  bold_font;
    }
    else if (role == Qt::DisplayRole)
    {
        if(unsigned(index.row()) <  marginals.size()  &&  marginals[index.row()].isValid())
        {
            marginal_in_table2&  mt = *marginals[index.row()];
            switch (index.column())
            {
            case 0:
                return QLatin1String(MTK_SS(mt.product_code.market << "." << mt.product_code.product).c_str());
            case 1:
                if(mt.best_prices.HasValue())
                {
                    if(mt.best_prices.Get().bids.level0.quantity.GetIntCode() != 0)
                        return qtmisc::fn_as_QString(mt.best_prices.Get().bids.level0.quantity);
                }
                return QVariant();
            case 2:
                if(mt.best_prices.HasValue())
                {
                    if(mt.best_prices.Get().bids.level0.quantity.GetIntCode() != 0)
                        return qtmisc::fn_as_QString(mt.best_prices.Get().bids.level0.price);
                    else if(mt.best_prices.Get().bids.level0.price.GetIntCode() != 0)
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qmarginal2", MTK_SS("price not cero with quantity cero  " << mt.best_prices.Get()), mtk::alPriorError));
                    else    //  price and quantity == 0
                        return QLatin1String("");
                }
                return QVariant();
            case 3:
                if(mt.best_prices.HasValue())
                {
                    if(mt.best_prices.Get().asks.level0.quantity.GetIntCode() != 0)
                        return qtmisc::fn_as_QString(mt.best_prices.Get().asks.level0.price);
                    else if(mt.best_prices.Get().asks.level0.price.GetIntCode() != 0)
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qmarginal2", MTK_SS("price not cero with quantity cero  " << mt.best_prices.Get()), mtk::alPriorError));
                    else
                        return QLatin1String("");
                }
                return QVariant();
            case 4:
                if(mt.best_prices.HasValue())
                {
                    if(mt.best_prices.Get().asks.level0.quantity.GetIntCode() != 0)
                        return qtmisc::fn_as_QString(mt.best_prices.Get().asks.level0.quantity);
                }
                return QVariant();
            case 5:
                if(mt.last_mk_execs_ticker.HasValue())
                {
                    if(mt.last_mk_execs_ticker.Get().last_quantity.GetIntCode() != 0)
                       return qtmisc::fn_as_QString(mt.last_mk_execs_ticker.Get().last_price);
                }
                return QVariant();
            case 6:
                if(mt.last_mk_execs_ticker.HasValue())
                {
                    if(mt.last_mk_execs_ticker.Get().last_quantity.GetIntCode() != 0)
                        return qtmisc::fn_as_QString(mt.last_mk_execs_ticker.Get().last_quantity);
                }
                return QVariant();
            case 7:
                if(mt.last_mk_execs_ticker.HasValue())
                {
                    if(mt.last_mk_execs_ticker.Get().opened_price.GetIntCode() != 0)
                        return qtmisc::fn_as_QString(mt.last_mk_execs_ticker.Get().opened_price);
                }
                return QVariant();
            case 8:
                return mt.var;
            case 9:
                return mt.percent_var;
            }

        }
        return QVariant();
    }
    else if (role == Qt::BackgroundRole)
    {
        marginal_in_table2&  mt = *marginals[index.row()];

        if(mt.best_prices.HasValue() == false  &&  index.column()>=1 &&  index.column()<=4)
            return QBrush(Qt::black);
        if(mt.last_mk_execs_ticker.HasValue() == false  &&  index.column()>=5 &&  index.column()<=9)
            return QBrush(Qt::black);
        if(mt.v_blinking[index.column()]  >  mtk::dtNowLocal())
        {
            return QBrush(qtmisc::mtk_color_blinking2);
        }
        else
        {
            QColor back_ground_color = Qt::white;
            if(index.column() == 0)
                back_ground_color = qtmisc::mtk_color_header;
            else if(index.column() == 2  ||  index.column() == 3)
                back_ground_color = QColor(240,245,250);
            int current_row = -1;
            signal_request_current_row(current_row);
            if(current_row == index.row())
                return QBrush(more_blue(back_ground_color));
            else
                return QBrush(back_ground_color);
        }
    }
    else if (role == Qt::ForegroundRole)
    {
        if(index.column() == 0)
            return  QBrush (QColor(30,0,100));
        marginal_in_table2&  mt = *marginals[index.row()];
        if(mt.v_blinking[index.column()]  >  mtk::dtNowLocal())
            return QBrush(QColor(191,219,255));
        else
            return QBrush(Qt::black);
    }
    return QVariant();
}



void  qmarginal_table_model::update(int /*row*/, int /*first_col*/, int /*last_col*/)
{
    QModelIndex top     = createIndex(0, 0, 0);
    QModelIndex bottom  = createIndex(this->marginals.size()-1, col_names.size()-1,  0);
    Q_EMIT dataChanged(top, bottom);
}



bool qmarginal_table_model::insertRows(int position, int rows, const QModelIndex &/*index*/)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);
    endInsertRows();
    return true;
}

bool   qmarginal_table_model::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count-1);
    endRemoveRows();
    return true;
}


void qmarginal_table_model::insert(const mtk::msg::sub_product_code &product_code, int row)
{
    if(row < 0)
        row = marginals.size();
    marginals.push_back(mtk::make_cptr(new marginal_in_table2(/*this, */product_code)));

    //  move to the correct position
    for(int i=marginals.size()-1; i>row; --i)
    {
        auto temp = marginals[i];
        marginals[i] = marginals[i-1];
        marginals[i-1] = temp;
    }

    insertRows (row, 1, QModelIndex());
}


void qmarginal_table_model::remove_row(int id)
{
    bool located = false;
    for(unsigned i=0; i<marginals.size()-1; ++i)
    {
        if(marginals[i]->id == id)
            located = true;
        if(located)
            marginals[i] = marginals[i+1];
    }
    marginals.pop_back();

    removeRows (marginals.size()-1 , 1, QModelIndex());
}



QVariant  qmarginal_table_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole  &&  orientation == Qt::Horizontal)
        return col_names[section];
    return QVariant();
}


void  qmarginal_table_model::slot_update_screen(void)
{
    bool  to_update = false;

    for(unsigned i=0; i<marginals.size(); ++i)
    {
        if(marginals[i]->last_updated > last_updated_table)
            to_update = true;
        if(marginals[i]->last_blinking < mtk::dtNowLocal()  &&   marginals[i]->last_blinking > mtk::dtNowLocal() - mtk::dtHours(1))
        {
            marginals[i]->last_blinking = mtk::dtNowLocal() - mtk::dtHours(2);
            to_update = true;
        }
    }

    if(to_update)
    {
        last_updated_table = mtk::dtNowLocal();
        this->update(0,0,0);
    }
}




void QHeaderView_hidding_cols2::mousePressEvent(QMouseEvent *e)
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


void  QHeaderView_hidding_cols2::hide_show_col(int logicalIndex)
{
    if(isSectionHidden(logicalIndex) == false)
    {
        this->hideSection(logicalIndex);
    }
    else
    {
        this->showSection(logicalIndex);
        if(this->visualIndex(logicalIndex) == count()-1-hiddenSectionCount())
            this->resizeSection(this->visualIndex(count()-2), this->sectionSize(count()-2)/2);
    }

    setResizeMode(QHeaderView::Interactive);
    resizeSection(this->logicalIndex(count()-hiddenSectionCount()), 10);
    setResizeMode(this->logicalIndex(count()-hiddenSectionCount()), QHeaderView::Fixed);
    setStretchLastSection(true);
}


Qt::ItemFlags  qmarginal_table_model::flags(const QModelIndex &index) const
{
    Qt::ItemFlags  flags  = QAbstractItemModel::flags(index);
    return  flags;
}







QMarginal2::QMarginal2(QWidget *parent) :
    mtkContainerWidget(parent),
    table_marginals(new QTableMarginal2(this))
{
    this->setGeometry(QRect(5, 5, 100*4+150+2*5-2, 300-2));
    this->setAcceptDrops(true);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(5,5,5,5);
    this->setLayout(layout);
    layout->addWidget(table_marginals);

    this->inserting_components_ended();
}

QMarginal2::~QMarginal2()
{
}



QTableMarginal2::QTableMarginal2(QWidget *parent)
    : QTableView(parent), startPos(-1,-1),
      action_buy(0), action_sell(0), action_hit_the_bid(0), action_lift_the_offer(0), action_remove_product(0),
      action_buy_market(0), action_sell_market(0),
      action_buy_stop_market(0), action_sell_stop_market(0),
      paint_delegate(new QCommonTableDelegate_view(this)),
      showing_menu(false),
      marginal_table_model(new qmarginal_table_model(this))
{
    MTK_CONNECT_THIS(marginal_table_model->signal_request_current_row, slot_requested_current_row)
    this->setAttribute(Qt::WA_OpaquePaintEvent);
    this->setModel(marginal_table_model);
    this->setAcceptDrops(true);

    setItemDelegate(paint_delegate);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setShowGrid(false);

    {
        verticalHeader()->setVisible(false);
        horizontalHeader()->setVisible(true);
        verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
        slot_sectionMoved(0,0,0);

        QStringList  names;
        for(unsigned i=0; i < col_names.size(); ++i)
            names.append(col_names[i]);
        setHorizontalHeader(new QHeaderView_hidding_cols2(names, Qt::Horizontal, this));
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


    action_buy_market = new QAction(tr("market buy"), this);
    connect(action_buy_market, SIGNAL(triggered()), this, SLOT(request_buy_market()));
    this->addAction(action_buy_market);

    action_sell_market = new QAction(tr("market sell"), this);
    connect(action_sell_market, SIGNAL(triggered()), this, SLOT(request_sell_market()));
    this->addAction(action_sell_market);


    action_buy_stop_market = new QAction(tr("stop market buy"), this);
    connect(action_buy_stop_market, SIGNAL(triggered()), this, SLOT(request_buy_stop_market()));
    this->addAction(action_buy_stop_market);

    action_sell_stop_market = new QAction(tr("stop market sell"), this);
    connect(action_sell_stop_market, SIGNAL(triggered()), this, SLOT(request_sell_stop_market()));
    this->addAction(action_sell_stop_market);


    action_remove_product = new QAction(tr("remove product"), this);
    action_remove_product->setShortcut(Qt::Key_Delete);
    connect(action_remove_product, SIGNAL(triggered()), this, SLOT(slot_remove_current_row()));
    this->addAction(action_remove_product);
    this->disable_actions();
    this->slot_sectionMoved(0,0,0);
}



marginal_in_table2::marginal_in_table2(const mtk::msg::sub_product_code& _product_code)
    :   id(++counter),
        product_code(_product_code),
        last_updated(mtk::dtNowLocal() - mtk::dtHours(1)),
        pending_screen_update(true),
        last_blinking(mtk::dtNowLocal()-mtk::dtDays(300))
{
    mtk::dtDateTime  now = mtk::dtNowLocal();
    for(int i=0; i<col_count; ++i)
        v_blinking.push_back(now - mtk::dtDays(30));

    price_manager = mtk::make_cptr(new mtk::prices::price_manager(product_code));
    MTK_CONNECT_THIS(price_manager->signal_best_prices_update,   on_best_prices);
    MTK_CONNECT_THIS(price_manager->signal_last_mk_execs_ticker, on_last_mk_execs_ticker_msg);

    update_prices               (price_manager->get_best_prices());
    update_last_mk_execs_ticker (price_manager->get_last_mk_execs_ticker());

    MTK_TIMER_1D(check_for_pending_screen_update)
}






void marginal_in_table2::clean_prices(void)
{
    best_prices             =       mtk::nullable<mtk::prices::msg::sub_best_prices>();
    //marginal_table_model->update(this->row, 1, 4);
    last_updated = mtk::dtNowLocal();
}

void marginal_in_table2::update_prices(const mtk::prices::msg::sub_best_prices&   _best_prices)
{
    auto  prev_best_prices = this->best_prices;
    this->best_prices   = _best_prices;

    if(prev_best_prices.HasValue())
    {
        const  mtk::prices::msg::sub_best_prices&  ref_sub_best_prices = prev_best_prices.Get();
        mtk::DateTime  now = mtk::dtNowLocal();

        if(ref_sub_best_prices.bids.level0.quantity !=  _best_prices.bids.level0.quantity)
        {
            add_blinking(1, now + mtk::dtMilliseconds(200));
            last_updated = mtk::dtNowLocal();
        }
        if(ref_sub_best_prices.bids.level0.price    !=  _best_prices.bids.level0.price)
        {
            add_blinking(2, now + mtk::dtMilliseconds(200));
            last_updated = mtk::dtNowLocal();
        }
        if(ref_sub_best_prices.asks.level0.price    !=  _best_prices.asks.level0.price)
        {
            add_blinking(3, now + mtk::dtMilliseconds(200));
            last_updated = mtk::dtNowLocal();
        }
        if(ref_sub_best_prices.asks.level0.quantity !=  _best_prices.asks.level0.quantity)
        {
            add_blinking(4, now + mtk::dtMilliseconds(200));
            last_updated = mtk::dtNowLocal();
        }
    }
}

void marginal_in_table2::update_prices(const mtk::nullable<mtk::prices::msg::sub_best_prices>&   n_best_prices)
{
    if(n_best_prices.HasValue())
        update_prices(n_best_prices.Get());
    else
        clean_prices();

}



void marginal_in_table2::clean_lasts(void)
{
    last_mk_execs_ticker    =       mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>();
}



void marginal_in_table2::update_vars(const mtk::prices::msg::sub_last_mk_execs_ticker&   _last_mk_execs_ticker)
{
    mtk::Double  dvar = _last_mk_execs_ticker.last_price.GetDouble() - _last_mk_execs_ticker.opened_price.GetDouble();
    this->var           =   QLocale::system().toString(dvar.get2(), 'f', 3);
    if(dvar != 0.  &&   _last_mk_execs_ticker.opened_price.GetIntCode() != 0)
        this->percent_var   =   QLocale::system().toString(dvar.get2() / _last_mk_execs_ticker.opened_price.GetDouble().get2() * 100., 'f', 2) + QLatin1String("%");
    else
        this->percent_var   =   QLatin1String("");
}

void marginal_in_table2::update_last_mk_execs_ticker(const mtk::prices::msg::sub_last_mk_execs_ticker&   _last_mk_execs_ticker)
{
    auto  prev_last_mk_execs_ticker = this->last_mk_execs_ticker;
    this->last_mk_execs_ticker   = _last_mk_execs_ticker;

    if(prev_last_mk_execs_ticker.HasValue())
    {
        const  mtk::prices::msg::sub_last_mk_execs_ticker&  ref_prev_last_mk_execs_ticker = prev_last_mk_execs_ticker.Get();

        if(ref_prev_last_mk_execs_ticker.last_price    !=  _last_mk_execs_ticker.last_price)
        {
            update_vars(_last_mk_execs_ticker);
            last_updated = mtk::dtNowLocal();
        }


        if(ref_prev_last_mk_execs_ticker.last_quantity !=  _last_mk_execs_ticker.last_quantity)
        {
            last_updated = mtk::dtNowLocal();
        }


        if(ref_prev_last_mk_execs_ticker.opened_price  !=  _last_mk_execs_ticker.opened_price)
        {
            update_vars(_last_mk_execs_ticker);
            last_updated = mtk::dtNowLocal();
        }
    }
    else
    {
        update_vars(_last_mk_execs_ticker);
        last_updated = mtk::dtNowLocal();
    }
}



void marginal_in_table2::update_last_mk_execs_ticker(const mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>&   n_last_mk_execs_ticker)
{
    if(n_last_mk_execs_ticker.HasValue())
        update_last_mk_execs_ticker(n_last_mk_execs_ticker.Get());
    else
        clean_lasts();
}




void marginal_in_table2::on_best_prices(const mtk::msg::sub_product_code& /*pc*/, const mtk::prices::msg::sub_best_prices& /*msg*/)
{
    pending_screen_update = true;
}


void marginal_in_table2::on_last_mk_execs_ticker_msg(const mtk::msg::sub_product_code& /*pc*/, const mtk::prices::msg::sub_last_mk_execs_ticker& /*msg*/)
{
    pending_screen_update = true;
}




void marginal_in_table2::check_for_pending_screen_update(void)
{
    if(pending_screen_update   &&   price_manager.isValid())
    {
        //MTK_EXEC_MAX_FREC(mtk::dtMilliseconds(200))
            update_prices(price_manager->get_best_prices());
            update_last_mk_execs_ticker(price_manager->get_last_mk_execs_ticker());
            pending_screen_update = false;
            //marginal_table_model->update(this->row, 1, 9);
        //MTK_END_EXEC_MAX_FREC
    }
}







void marginal_in_table2::add_blinking(int col, const mtk::DateTime&  till)
{
    if(till > last_blinking)
        last_blinking = till;
    v_blinking[col] = till;
}



void QTableMarginal2::insert_marginal(const mtk::msg::sub_product_code& product_code, int row)
{
    marginal_table_model->insert(product_code, row);
}


void QTableMarginal2::dragEnterEvent(QDragEnterEvent *event)
{
    QTableView::dragEnterEvent(event);
    if(qobject_cast<QTableMarginal2*>(event->source())!=0)
        event->setDropAction(Qt::MoveAction);
    else
        event->setDropAction(Qt::CopyAction);
    event->accept();
}

void QTableMarginal2::dragMoveEvent(QDragMoveEvent *event)
{
    QTableView::dragMoveEvent(event);
    if(qobject_cast<QTableMarginal2*>(event->source())!=0)
        event->setDropAction(Qt::MoveAction);
    else
        event->setDropAction(Qt::CopyAction);
    event->accept();
}


void QTableMarginal2::dropEvent(QDropEvent *event)
{
    insert_marginal(qtmisc::get_product_code(event), rowAt(event->pos().y()));
    if(qobject_cast<QTableMarginal2*>(event->source())!=0)
        event->setDropAction(Qt::MoveAction);
    else
        event->setDropAction(Qt::CopyAction);
    event->accept();

    int current_row = rowAt(event->pos().y());
    if (current_row < 0)
    {
        current_row = this->marginal_table_model->row_count()-1;
    }
    QModelIndex index = this->marginal_table_model->index(current_row, 0);
    this->setCurrentIndex(index);
    this->setFocus(Qt::OtherFocusReason);
}





void QTableMarginal2::mousePressEvent(QMouseEvent *event)
{
    QWidget* w = dynamic_cast<QWidget*>(this->parent());
    if(w)       w->raise();

    int row = rowAt(event->pos().y());
    if(columnAt(event->pos().x())>=0    &&     row>=0)
    {
        startPos = event->pos();
        startDragId = this->marginal_table_model->get_marginal(row)->id;
    }
    QTableView::mousePressEvent(event);
}

void QTableMarginal2::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    startPos = QPoint(-1,-1);
}

void QTableMarginal2::mouseMoveEvent(QMouseEvent *event)
{
    QTableView::mouseMoveEvent(event);

    if (rowAt(event->pos().y())<0)      return;

    if ((event->buttons() & Qt::LeftButton)  &&  startPos.x()>=0  &&  startPos.y()>=0)
    {
        int distance = (event->pos() - startPos).manhattanLength();
        if (this->currentIndex().row()>=0  &&   distance >= QApplication::startDragDistance()+5)
            start_drag();
    }
}

void QTableMarginal2::start_drag(void)
{
    QMimeData* mimeData = new QMimeData;
    mimeData->setText(qtmisc::dragProductText(this->get_current_product_code()));
    QDrag* drag = new QDrag(this);
    drag->setMimeData(mimeData);

    {
        QRect rect(this->visualRect(this->marginal_table_model->index(this->currentIndex().row(), 0)));
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

void QTableMarginal2::remove_row(int id)
{
    marginal_table_model->remove_row(id);
}




void QTableMarginal2::contextMenuEvent ( QContextMenuEvent * event )
{
    if (rowAt(event->pos().y())<0)      return;

    int current_row = this->currentIndex().row();
    if (current_row <0)        return;

    mtk::msg::sub_product_code product_code (get_current_product_code());


    QMenu menu(this);
    menu.addAction(action_buy);
    menu.addAction(action_sell);

    menu.addSeparator();
    menu.addAction(action_lift_the_offer);
    menu.addAction(action_hit_the_bid);


    if(product_code.market == "EU"  ||  product_code.market == "MARKET")
    {
        if(mtk::admin::is_production() == false)
        {
            menu.addSeparator();
            menu.addAction(action_buy_market);
            menu.addAction(action_sell_market);

            menu.addAction(action_buy_stop_market);
            menu.addAction(action_sell_stop_market);
        }
    }

    menu.addSeparator();
    menu.addAction(action_remove_product);

    //  permisions
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


void QTableMarginal2::request_side(mtk::trd::msg::enBuySell bs)
{
    mtk::msg::sub_product_code product_code = this->get_current_product_code();
    if (mtk::msg::is_valid(product_code)==false)      return;

    //  proposed price
    mtk::nullable<mtk::prices::msg::sub_best_prices>   n_best_prices = this->marginal_table_model->get_marginal(this->currentIndex().row())->best_prices;
    if(n_best_prices.HasValue() == false)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "marginal", "on request_side   best prices is null", mtk::alPriorError));
    else
    {
        mtk::FixedNumber price(n_best_prices.Get().bids.level0.price);
        mtk::FixedNumber quantity(n_best_prices.Get().bids.level0.quantity);
        if(bs == mtk::trd::msg::sell)
        {
            price = n_best_prices.Get().asks.level0.price;
            quantity= n_best_prices.Get().asks.level0.quantity;
        }
        if(quantity.GetIntCode() != 0)    quantity.SetIntCode(-1);        //  means, default quantity
        else                              quantity.SetIntCode(-2);        //  means, no price, default quantity
        mtk::trd::msg::sub_position_ls     pos(price, quantity, "" /*cli ref*/);
        mtk::trd::trd_cli_ord_book::rq_nw_ls_manual(product_code, bs, pos);
    }
}


void QTableMarginal2::request_buy (void)
{
    paint_delegate->keep_focus_paint(true);
    request_side(mtk::trd::msg::buy);
    paint_delegate->keep_focus_paint(false);
}

void QTableMarginal2::request_sell(void)
{
    paint_delegate->keep_focus_paint(true);
    request_side(mtk::trd::msg::sell);
    paint_delegate->keep_focus_paint(false);
}




void QTableMarginal2::request_aggression(mtk::trd::msg::enBuySell bs)
{
    mtk::msg::sub_product_code product_code = this->get_current_product_code();
    if (mtk::msg::is_valid(product_code)==false)      return;


    //  proposed price
    mtk::nullable<mtk::prices::msg::sub_best_prices>   n_best_prices = this->marginal_table_model->get_marginal(this->currentIndex().row())->best_prices;
    if(n_best_prices.HasValue() == false)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "marginal", "on request_aggression   best prices is null", mtk::alPriorError));
    else
    {
        mtk::FixedNumber price(n_best_prices.Get().bids.level0.price);
        mtk::FixedNumber quantity(n_best_prices.Get().bids.level0.quantity);
        if(bs == mtk::trd::msg::buy)
        {
            price = n_best_prices.Get().asks.level0.price;
            quantity= n_best_prices.Get().asks.level0.quantity;
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


void QTableMarginal2::request_hit_the_bid(void)
{
    paint_delegate->keep_focus_paint(true);
    request_aggression(mtk::trd::msg::sell);
    paint_delegate->keep_focus_paint(false);
}

void QTableMarginal2::request_lift_the_offer(void)
{
    paint_delegate->keep_focus_paint(true);
    request_aggression(mtk::trd::msg::buy);
    paint_delegate->keep_focus_paint(false);
}





void QTableMarginal2::request_side_market(mtk::trd::msg::enBuySell bs)
{
    mtk::msg::sub_product_code product_code = this->get_current_product_code();
    if (mtk::msg::is_valid(product_code)==false)      return;


    //  proposed price
    mtk::nullable<mtk::prices::msg::sub_best_prices>   n_best_prices = this->marginal_table_model->get_marginal(this->currentIndex().row())->best_prices;
    if(n_best_prices.HasValue() == false)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "marginal", "on request_side_market   best prices is null", mtk::alPriorError));
    else
    {
        mtk::FixedNumber quantity(n_best_prices.Get().bids.level0.quantity);
        if(bs == mtk::trd::msg::sell)
            quantity= n_best_prices.Get().asks.level0.quantity;
        if(quantity.GetIntCode() != 0)    quantity.SetIntCode(-1);        //  means, default quantity
        else                              quantity.SetIntCode(-2);        //  means, no price, no quantity
        mtk::trd::msg::sub_position_mk     pos(quantity, "" /*cli ref*/);
        mtk::trd::trd_cli_ord_book::rq_nw_mk_manual(product_code, bs, pos);
    }
}


void QTableMarginal2::request_buy_market(void)
{
    paint_delegate->keep_focus_paint(true);
    request_side_market(mtk::trd::msg::buy);
    paint_delegate->keep_focus_paint(false);
}

void QTableMarginal2::request_sell_market(void)
{
    paint_delegate->keep_focus_paint(true);
    request_side_market(mtk::trd::msg::sell);
    paint_delegate->keep_focus_paint(false);
}






void QTableMarginal2::disable_actions(void)
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

void QTableMarginal2::enable_actions(void)
{
    if(action_remove_product)
    {
        enable_trading_actions();
        action_remove_product->setEnabled(true);
    }
}

void QTableMarginal2::disable_trading_actions(void)
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

void QTableMarginal2::enable_trading_actions(void)
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


void QTableMarginal2::slot_remove_current_row(void)
{
    if (this->currentIndex().row() >= 0)
    {
        paint_delegate->keep_focus_paint(true);
        try
        {
            if(QMessageBox::warning(this, QLatin1String("CimdTrade"), tr("Do you want to remove the current product from this table?"), QMessageBox::Ok, QMessageBox::Cancel)==QMessageBox::Ok)
                this->remove_row(this->marginal_table_model->get_marginal(this->currentIndex().row())->id);
        }
        catch(...)
        {
            paint_delegate->keep_focus_paint(false);
            throw;
        }
        paint_delegate->keep_focus_paint(false);
    }
}


mtk::msg::sub_product_code   QTableMarginal2::get_current_product_code(void)
{
    if(this->currentIndex().row() >= 0)
        return  this->marginal_table_model->get_marginal(this->currentIndex().row())->product_code;
    else
        return mtk::msg::sub_product_code("", "");
}








YAML::Emitter& operator << (YAML::Emitter& out, const QTableMarginal2& m)
{
    out     << YAML::BeginMap;

    //  writing products
    out << YAML::Key   <<  "products"
        << YAML::Value << YAML::BeginSeq;

        for(int i=0; i<m.marginal_table_model->row_count(); ++i)
        {
            out << m.marginal_table_model->get_marginal(i)->product_code;
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

void             operator >> (const YAML::Node&   node,        QTableMarginal2& m)
{
    for(unsigned i=0; i< node["products"].size(); ++i)
    {
        mtk::msg::sub_product_code pc = mtk::msg::__internal_get_default((mtk::msg::sub_product_code*)0);
        node["products"][i] >> pc;
        m.insert_marginal(pc, -1);
    }
    for(unsigned i=0; i< node["sect_sizes"].size(); ++i)
    {
        int sect_size;
        node["sect_sizes"][i] >> sect_size;
        m.horizontalHeader()->resizeSection(i, sect_size);
    }
    m.slot_sectionMoved(0,0,0);
}



YAML::Emitter& operator << (YAML::Emitter& out, const QMarginal2& m)
{
    out     << YAML::BeginMap;

    //  writing component
    out << YAML::Key   <<  "component" << YAML::Value << static_cast<const mtkContainerWidget&>(m);
    //  end component

    //  writing QTableMarginal2
    if(m.table_marginals)
        out << YAML::Key   <<  "QTableMarginal2"  << YAML::Value   << *(m.table_marginals);
    //  end QTableMarginal2


    out << YAML::EndMap;

    return out;
}


void             operator >> (const YAML::Node&   node,       QMarginal2& m)
{
    node["component"] >> static_cast<mtkContainerWidget&>(m);
    node["QTableMarginal2"] >>  (*m.table_marginals);
}



void QTableMarginal2::slot_sectionMoved ( int /*logicalIndex*/, int /*oldVisualIndex*/, int /*newVisualIndex*/ )
{
    this->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
    horizontalHeader()->resizeSection(horizontalHeader()->logicalIndex(horizontalHeader()->count()-1), 10);
    this->horizontalHeader()->setResizeMode(horizontalHeader()->logicalIndex(horizontalHeader()->count()-1), QHeaderView::Fixed);
    horizontalHeader()->setStretchLastSection(true);
}



void QTableMarginal2::focusOutEvent(QFocusEvent *e)
{
    this->update();
    disable_actions();
    QTableView::focusOutEvent(e);
}

void QTableMarginal2::focusInEvent (QFocusEvent *e)
{
    this->update();
    enable_actions();
    QTableView::focusInEvent(e);
}


