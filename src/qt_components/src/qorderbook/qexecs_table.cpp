#include "qexecs_table.h"


#include <QHeaderView>
#include <QAction>
#include <QHBoxLayout>
#include <QMenu>



#include "qmtk_misc.h"
#include "qt_components/src/qcommontabledelegate.h"
#include "components/trading/trd_cli_support.h"
#include "components/trading/trd_cli_historic.h"





namespace {
    const int col_count = 6;

    const int col_market_product    = 0;
    const int col_side              = 1;
    const int col_exec_quantity     = 2;
    const int col_exec_price        = 3;
    const int col_exec_time         = 4;
    const int col_exec_description  = 5;
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
            //items[column]->setBackgroundColor(Qt::white);
            table_widget->setItem(row, column, items[column]);
            //if (column == col_exec_price  ||  column == col_exec_quantity)
            //    items[column]->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
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
        if (exec_item.exec_info.side == mtk::trd::msg::buy)
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
        exec_in_table(new mtk::list<Exec_in_table*>),
        mediaObject (Phonon::createPlayer(Phonon::NoCategory, Phonon::MediaSource(QLatin1String("../data/execution.wav"))))
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
    table_widget->setColumnWidth(col_exec_description, 60);

    //  setting up actions
    /*
    setContextMenuPolicy(Qt::ActionsContextMenu);
    {
        QAction* action = new QAction("cancel", this);
        connect(action, SIGNAL(triggered()), this, SLOT(request_cancel()));
        addAction(action);
    }
    {
        QAction* action = new QAction("modif", this);
        connect(action, SIGNAL(triggered()), this, SLOT(request_modif()));
        addAction(action);
    }
    {
        QAction* action = new QAction(this);
        action->setSeparator(true);
        addAction(action);
    }
    {
        QAction* action = new QAction("filter", this);
        connect(action, SIGNAL(triggered()), this, SLOT(request_cancel()));
        addAction(action);
    }
    */




    MTK_CONNECT_THIS(mtk::trd::trd_cli_ord_book::get_sig_execution(), on_new_execution);
    MTK_TIMER_1C(timer_get_execs2add);
    //setContentsMargins(0,0,0,0);
}


void QExecsTable::__direct_add_new_execution(const mtk::trd::hist::order_exec_item& exec)
{
    exec_in_table->push_back(new Exec_in_table(table_widget, exec));
}

void QExecsTable::on_new_execution(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
{
    mtk::trd::hist::order_exec_item  oei { confirm_info, exec};
    execs2add_online.push_back(oei);
    execs_all.push_back(oei);
    MTK_EXEC_MAX_FREC(mtk::dtSeconds(1))
        mediaObject->play();
    MTK_END_EXEC_MAX_FREC
    /*
    if(mediaObject->remainingTime()==0)
    {
        mediaObject->stop();
        mediaObject->play();
    }
    */
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

void  QExecsTable::slot_clean_execs(void)
{
    table_widget->setRowCount(0);
    exec_in_table->clear();
}

void  QExecsTable::slot_show_all_execs(void)
{
    slot_clean_execs();
    if(execs2add_loading.size()!=0)
        execs2add_loading.clear();

    for(auto it = execs_all.begin();  it != execs_all.end(); ++it)
        execs2add_loading.push_back(*it);
}


void QExecsTable::contextMenuEvent(QContextMenuEvent *e)
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
    menu.exec(this->mapToGlobal(e->pos()));
}
