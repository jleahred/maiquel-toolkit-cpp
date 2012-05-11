#include "qexecs_table.h"


#include <QHeaderView>
#include <QAction>
#include <QHBoxLayout>
#include <QMenu>
#include <QApplication>
#include <QClipboard>



#include "qmtk_misc.h"
#include "qt_components/src/qcommontabledelegate.h"
#include "components/trading/trd_cli_support.h"
#include "components/trading/trd_cli_historic.h"

extern  void  show_execs_report_window(void);





namespace {
    const int col_count = 7;

    const int col_market_product    = 0;
    const int col_side              = 1;
    const int col_exec_quantity     = 2;
    const int col_exec_price        = 3;
    const int col_exec_time         = 4;
    const int col_exec_id           = 5;
    const int col_exec_description  = 6;
    /*const char* col_captions[] = {    "product",            defined later for translations
                                        "side",
                                        "qty",
                                        "price",
                                        0          };*/
};









//----------------------------------------------------------------------------------------------------
//  class Exec_in_table
//----------------------------------------------------------------------------------------------------
class Exec_in_table  : public mtk::SignalReceptor
{
    typedef Exec_in_table  CLASS_NAME;
public:

    QTableWidgetItem**                  items;
    mtk::trd::hist::order_exec_item     exec_item;

    Exec_in_table(QTableWidget *table_widget, const mtk::trd::hist::order_exec_item&     _exec_item)
        : items (new QTableWidgetItem*[col_count]),
          exec_item(_exec_item)

    {
        int row = table_widget->rowCount();
        table_widget->insertRow(row);

        for (int column=0; column<col_count; ++column)
        {
            items[column] = new QTableWidgetItem;
            items[column]->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            table_widget->setItem(row, column, items[column]);
            items[column]->setTextAlignment(Qt::AlignCenter|Qt::AlignVCenter);
        }

        update();
    }
    ~Exec_in_table() { delete [] items; }


    void update(void)
    {
        update_item_market_product      ();
        update_item_exec_quantity       ();
        update_item_exec_price          ();
        update_item_side                ();
        update_item_time                ();
        update_item_exec_id             ();
        update_item_description         ();
    }

    void update_on_cf(const mtk::trd::msg::CF_NW_LS&)  {    update();   }



    QColor  get_default_color(void)
    {
        return qtmisc::mtk_color_executed;
    }


    void update_item_market_product(void)
    {
        QTableWidgetItem* item = items[col_market_product];
        item->setText(QLatin1String(MTK_SS(exec_item.confirm_info.invariant.product_code.market << "." << exec_item.confirm_info.invariant.product_code.product).c_str()));
        item->setBackgroundColor(get_default_color());
    }


    void update_item_side(void)
    {
        QTableWidgetItem* item = items[col_side];
        if (exec_item.confirm_info.invariant.side == mtk::trd::msg::buy)
        {
            item->setText(QObject::tr("buy"));
            item->setBackgroundColor(qtmisc::mtk_color_buy_cell);
        }
        else
        {
            item->setText(QObject::tr("sell"));
            item->setBackgroundColor(qtmisc::mtk_color_sell_cell);
        }
        item->setTextAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    }

    void update_item_exec_quantity (void)
    {
        QTableWidgetItem* item = items[col_exec_quantity];
        item->setText(qtmisc::fn_as_QString(exec_item.exec_info.quantity));
        item->setBackgroundColor(get_default_color());
    }
    void update_item_exec_price (void)
    {
        QTableWidgetItem* item = items[col_exec_price];
        item->setText(qtmisc::fn_as_QString(exec_item.exec_info.price));
        item->setBackgroundColor(get_default_color());
    }
    void update_item_time (void)
    {
        QTableWidgetItem* item = items[col_exec_time];
        item->setText(QLatin1String(MTK_SS(exec_item.confirm_info.orig_control_fluct.datetime).substr(11, 8).c_str()));
        item->setBackgroundColor(get_default_color());
    }
    void update_item_exec_id (void)
    {
        QTableWidgetItem* item = items[col_exec_id];
        //item->setText(QLatin1String(exec_item.exec_info.exec_id.c_str()));
        item->setText(QLatin1String(exec_item.exec_info.exec_id.c_str()));
        item->setBackgroundColor(get_default_color());
    }
    void update_item_description (void)
    {
        QTableWidgetItem* item = items[col_exec_description];
        item->setText(QLatin1String(exec_item.confirm_info.description.c_str()));
        item->setBackgroundColor(get_default_color());
    }


};
//----------------------------------------------------------------------------------------------------
//  class Exec_in_table
//----------------------------------------------------------------------------------------------------



QExecsTable::QExecsTable(QWidget *parent) :
        QWidget(parent),
        table_widget(new QTableWidget(this)),
        exec_in_table(new mtk::list<Exec_in_table*>)
{
    QHBoxLayout *hl= new QHBoxLayout(this);
    hl->setSpacing(0);
    hl->setContentsMargins(0, 0, 0, 0);
    hl->addWidget(table_widget);

    QStringList headers_captions;
    {
        static const char* const col_captions[] = {     QT_TR_NOOP("product"),
                                                        QT_TR_NOOP("side"),
                                                        QT_TR_NOOP("qty"),
                                                        QT_TR_NOOP("price"),
                                                        QT_TR_NOOP("time"),
                                                        QT_TR_NOOP("exec.id."),
                                                        QT_TR_NOOP("remarks"),
                                                        0          };


        int counter;
        for (counter=0; col_captions[counter]!=0; ++counter)
            headers_captions.append(tr(col_captions[counter]));
        table_widget->setColumnCount(counter);
    }
    table_widget->setHorizontalHeaderLabels(headers_captions);

    table_widget->verticalHeader()->setVisible(false);
    //table_widget->verticalHeader()->setDefaultSectionSize(QFontMetrics(this->font()).height()*1.4);  moved on_new_order
    //table_widget->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    table_widget->horizontalHeader()->setStretchLastSection(true);


    {
        QCommonTableDelegate* delegate_paint = new QCommonTableDelegate(table_widget);
        delegate_paint->set_horiz_line_each(1);
        table_widget->setItemDelegate(delegate_paint);
    }
    table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_widget->setSelectionMode(QAbstractItemView::SingleSelection);
    table_widget->setShowGrid(false);

    table_widget->setColumnWidth(col_market_product, 100);
    table_widget->setColumnWidth(col_side, 30);
    table_widget->setColumnWidth(col_exec_price, 60);
    table_widget->setColumnWidth(col_exec_quantity, 60);
    table_widget->setColumnWidth(col_exec_time, 60);
    table_widget->setColumnWidth(col_exec_id, 100);
    table_widget->setColumnWidth(col_exec_description, 60);


    MTK_TIMER_1C(timer_get_execs2add);
    //setContentsMargins(0,0,0,0);
}


void QExecsTable::__direct_add_new_execution(const mtk::trd::hist::order_exec_item& exec)
{
    exec_in_table->push_back(new Exec_in_table(table_widget, exec));
}

void QExecsTable::on_new_execution(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
{
    mtk::trd::hist::order_exec_item  oei { confirm_info, exec  };
    execs2add_online.push_back(oei);
}



void   QExecsTable::timer_get_execs2add(void)
{
    int counter=0;
    while(execs2add_loading.size()>0)
    {
        auto exec = execs2add_loading.front();
        execs2add_loading.pop_front();
        __direct_add_new_execution(exec);
        ++counter;
        if(counter%5==0)
            return;
    }
    while(execs2add_online.size()>0)
    {
        auto  exec = execs2add_online.front();
        execs2add_online.pop_front();
        __direct_add_new_execution(exec);
        ++counter;
        if(counter%5==0)
            return;
    }
}

void QExecsTable::update_sizes()
{
    table_widget->verticalHeader()->setDefaultSectionSize(QFontMetrics(this->font()).height()*1.2);
}









//      ALL EXECS TABLE




QExecsTable_ALL_execs::QExecsTable_ALL_execs(QWidget *parent) :
        QExecsTable(parent),
        mediaObject (Phonon::createPlayer(Phonon::NoCategory, Phonon::MediaSource(QLatin1String("../data/execution.wav"))))
{
    MTK_CONNECT_THIS(mtk::trd::trd_cli_ord_book::get_sig_execution_RT(), on_new_execution);
    //setContentsMargins(0,0,0,0);
}



void  QExecsTable_ALL_execs::slot_clean_execs(void)
{
    table_widget->setRowCount(0);
    exec_in_table->clear();    
}

void  QExecsTable_ALL_execs::slot_show_all_execs(void)
{
    slot_clean_execs();
    if(execs2add_loading.size()!=0)
        execs2add_loading.clear();

    mtk::list<mtk::trd::msg::CF_EXLK>  list_all_execs = mtk::trd::trd_cli_ord_book::get_all_execs();
    for(auto it=list_all_execs.begin(); it!=list_all_execs.end(); ++it)
    {
        mtk::trd::hist::order_exec_item  oei { *it, it->executed_pos  };
        execs2add_loading.push_back(oei);
    }
}

void  QExecsTable_ALL_execs::slot_copy_all_execs(void)
{
    mtk::list<mtk::trd::msg::CF_EXLK>  list_all_execs = mtk::trd::trd_cli_ord_book::get_all_execs();

    QString  result;
    result += QLatin1String("MARKET");     result += QLatin1String("\t");
    result += QLatin1String("PRODUCT");    result += QLatin1String("\t");
    result += QLatin1String("SIDE");       result += QLatin1String("\t");
    result += QLatin1String("QUANTITY");   result += QLatin1String("\t");
    result += QLatin1String("PRICE");      result += QLatin1String("\t");
    result += QLatin1String("TIME");       result += QLatin1String("\t");
    result += QLatin1String("EXEC_ID");    result += QLatin1String("\t");
    result += QLatin1String("REMARKS");
    result += QLatin1String("\n");

    for(auto it=list_all_execs.begin(); it!=list_all_execs.end(); ++it)
    {
        mtk::trd::hist::order_exec_item  exec_item { *it, it->executed_pos  };
        result += QLatin1String(exec_item.confirm_info.invariant.product_code.market.c_str());
        result += QLatin1String("\t");

        result += QLatin1String(exec_item.confirm_info.invariant.product_code.product.c_str());
        result += QLatin1String("\t");

        if (exec_item.confirm_info.invariant.side == mtk::trd::msg::buy)
            result += QObject::tr("buy");
        else
            result += QObject::tr("sell");
        result += QLatin1String("\t");

        result += qtmisc::fn_as_QString(exec_item.exec_info.quantity);
        result += QLatin1String("\t");

        result += qtmisc::fn_as_QString(exec_item.exec_info.price);
        result += QLatin1String("\t");

        result += QLatin1String(MTK_SS(exec_item.confirm_info.orig_control_fluct.datetime).substr(11, 8).c_str());
        result += QLatin1String("\t");

        result += QLatin1String(exec_item.exec_info.exec_id.c_str());
        result += QLatin1String("\t");

        result += QLatin1String(QLatin1String(exec_item.confirm_info.description.c_str()));

        result += QLatin1String("\n");
    }

    QApplication::clipboard()->setText(result);
}





void  QExecsTable_ALL_execs::slot_copy_execs_group_by_ordprice(void)
{
    mtk::list<mtk::trd::msg::CF_EXLK>  list_all_execs = mtk::trd::trd_cli_ord_book::get_all_execs();

    QString  result;
    result += QLatin1String("CLI_CODE");   result += QLatin1String("\t");
    result += QLatin1String("ACCOUNT");    result += QLatin1String("\t");
    result += QLatin1String("MARKET");     result += QLatin1String("\t");
    result += QLatin1String("PRODUCT");    result += QLatin1String("\t");
    result += QLatin1String("SIDE");       result += QLatin1String("\t");
    result += QLatin1String("QUANTITY");   result += QLatin1String("\t");
    result += QLatin1String("PRICE");      result += QLatin1String("\t");
    result += QLatin1String("\n");



    typedef  mtk::tuple<
            std::string,                                    //  order by
            mtk::trd::msg::sub_account_info,
            mtk::msg::sub_product_code,
            mtk::trd::msg::enBuySell,
            mtk::FixedNumber                   //  price
            >  t_exec_key;

    mtk::map<t_exec_key, mtk::Double>                       map_execs_grouped;
    mtk::map<mtk::trd::msg::sub_order_id, mtk::DateTime>    map_first_exec_per_order;


    for(auto it=list_all_execs.begin(); it!=list_all_execs.end(); ++it)
    {
        mtk::trd::msg::sub_invariant_order_info  invariant = it->invariant;


        auto it_first_exec = map_first_exec_per_order.find(invariant.order_id);
        if(it_first_exec==map_first_exec_per_order.end())
            it_first_exec = map_first_exec_per_order.insert(std::make_pair(invariant.order_id, it->orig_control_fluct.datetime)).first;


        t_exec_key   key = mtk::make_tuple(     MTK_SS(it_first_exec->second <<  invariant.order_id),
                                                invariant.account,
                                                invariant.product_code,
                                                invariant.side,
                                                it->executed_pos.price);

        auto find_exec_grouped = map_execs_grouped.find(key);
        if(find_exec_grouped == map_execs_grouped.end())
            map_execs_grouped.insert(std::make_pair(key, it->executed_pos.quantity.GetDouble()));
        else
            find_exec_grouped->second =  find_exec_grouped->second + it->executed_pos.quantity.GetDouble();
    }

    for(auto it=map_execs_grouped.begin(); it!=map_execs_grouped.end(); ++it)
    {
        result += QLatin1String(it->first._1.client_code.c_str());
        result += QLatin1String("\t");

        result += QLatin1String(it->first._1.name.c_str());
        result += QLatin1String("\t");

        result += QLatin1String(it->first._2.market.c_str());
        result += QLatin1String("\t");

        result += QLatin1String(it->first._2.product.c_str());
        result += QLatin1String("\t");

        result += qtmisc::side_as_text(it->first._3);
        result += QLatin1String("\t");


        result += QLocale::system().toString(it->second.get2(), 'f', 3);
        result += QLatin1String("\t");


        result += qtmisc::fn_as_QString(it->first._4);

        result += QLatin1String("\n");
    }

    QApplication::clipboard()->setText(result);
}


void QExecsTable_ALL_execs::contextMenuEvent(QContextMenuEvent *e)
{
    QMenu  menu;
    {
        QAction* action = new QAction(tr("clear"), this);
        connect(action, SIGNAL(triggered()), this, SLOT(slot_clean_execs()));
        menu.addAction(action);
    }
    {
        QAction* action = new QAction(tr("show all execs"), this);
        connect(action, SIGNAL(triggered()), this, SLOT(slot_show_all_execs()));
        menu.addAction(action);
    }
    {
        QAction* action = new QAction(tr("show execs report"), &menu);
        connect(action, SIGNAL(triggered()), this, SLOT(slot_show_execs_report()));
        menu.addAction(action);
        action->setEnabled(true);
    }
    menu.addSeparator();
    {
        QAction* action = new QAction(tr("copy all execs"), this);
        connect(action, SIGNAL(triggered()), this, SLOT(slot_copy_all_execs()));
        menu.addAction(action);
    }
    {
        QAction* action = new QAction(tr("copy execs group by ord/price"), this);
        connect(action, SIGNAL(triggered()), this, SLOT(slot_copy_execs_group_by_ordprice()));
        menu.addAction(action);
    }

    menu.exec(this->mapToGlobal(e->pos()));
}

void QExecsTable_ALL_execs::on_new_execution(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
{
    QExecsTable::on_new_execution(confirm_info, exec);
    MTK_EXEC_MAX_FREC(mtk::dtSeconds(1))
        mediaObject->stop();
        mediaObject->play();
    MTK_END_EXEC_MAX_FREC
}



/*
QExecsTable_one_order::QExecsTable_one_order(QWidget *parent) :
        QExecsTable(parent)
{
}

void QExecsTable_one_order::on_new_item(const mtk::trd::hist::order_exec_item&  exec_item)
{
    QExecsTable::on_new_execution(exec_item.confirm_info, exec_item.exec_info);
}


void   QExecsTable_one_order::set_executions(mtk::CountPtr<mtk::trd::hist::order_EXECS_historic>  _execs_history)
{
    mtk::CountPtr<mtk::list<mtk::trd::hist::order_exec_item> >   hist_execs =   _execs_history->get_items_list();

    MTK_CONNECT_THIS(_execs_history->signal_new_item_added, on_new_item);

    table_widget->setRowCount(0);
    execs2add_online.clear();

    for(auto it = hist_execs->rbegin(); it != hist_execs->rend(); ++it)
        on_new_item(*it);

    execs_history = _execs_history;
}
*/

void  QExecsTable_ALL_execs::slot_show_execs_report(void)
{
    show_execs_report_window();
}
