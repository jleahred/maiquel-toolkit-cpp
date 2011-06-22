#include "qexecs_table.h"


#include <QHeaderView>
#include <QAction>
#include <QHBoxLayout>
#include <QMenu>



#include "qmtk_misc.h"
#include "qt_components/src/qcommontabledelegate.h"
#include "components/trading/trd_cli_support.h"





namespace {
    const int col_market_product= 0;
    const int col_side          = 1;
    const int col_exec_price    = 2;
    const int col_exec_quantity = 3;
    /*const char* col_captions[] = {    "product",            defined later for translations
                                        "side",
                                        "price",
                                        "qty",
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
    mtk::msg::sub_product_code          product_code;
    mtk::trd::msg::sub_exec_conf        exec;

    Exec_in_table(QTableWidget *table_widget, const mtk::msg::sub_product_code& _product_code, const mtk::trd::msg::sub_exec_conf& _exec)
        : items (new QTableWidgetItem*[4]),
            product_code(_product_code),  exec (_exec)

    {
        int row = table_widget->rowCount();
        table_widget->insertRow(row);

        for (int column=0; column<4; ++column)
        {
            items[column] = new QTableWidgetItem;
            items[column]->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            items[column]->setBackgroundColor(Qt::white);
            table_widget->setItem(row, column, items[column]);
            if (column == col_exec_price  ||  column == col_exec_quantity)
                items[column]->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
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
    }

    void update_on_cf(const mtk::trd::msg::CF_NW_LS&)  {    update();   }



    QColor  get_default_color(void)
    {
        return qtmisc::mtk_color_executed;
    }


    void update_item_market_product(void)
    {
        QTableWidgetItem* item = items[col_market_product];
        item->setText(QLatin1String(MTK_SS(product_code.market << "." <<product_code.product).c_str()));
        item->setBackgroundColor(get_default_color());
    }


    void update_item_side(void)
    {
        QTableWidgetItem* item = items[col_side];
        if (exec.side == mtk::trd::msg::buy)
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
        item->setText(qtmisc::fn_as_QString(exec.quantity));
        item->setBackgroundColor(get_default_color());
    }
    void update_item_exec_price (void)
    {
        QTableWidgetItem* item = items[col_exec_price];
        item->setText(qtmisc::fn_as_QString(exec.price));
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

    //table_widget->horizontalHeader()->setStyleSheet(QLatin1String("background-color: rgb(191,219,255);"));

    QStringList headers_captions;
    {
        static const char* const col_captions[] = {     QT_TR_NOOP("product"),
                                                        QT_TR_NOOP("side"),
                                                        QT_TR_NOOP("price"),
                                                        QT_TR_NOOP("qty"),
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


void QExecsTable::__direct_add_new_execution(const mtk::msg::sub_product_code& pc, const mtk::trd::msg::sub_exec_conf& exec)
{
    exec_in_table->push_back(new Exec_in_table(table_widget, pc, exec));
}

void QExecsTable::on_new_execution(const mtk::msg::sub_product_code& pc, const mtk::trd::msg::sub_exec_conf& exec)
{
    execs2add_online.push_back(mtk::make_tuple(pc, exec));
    execs_all.push_back(mtk::make_tuple(pc, exec));
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
        mtk::tuple<mtk::msg::sub_product_code, mtk::trd::msg::sub_exec_conf> exec = execs2add_loading.front();
        execs2add_loading.pop_front();
        __direct_add_new_execution(exec._0, exec._1);
        ++counter;
        if(counter%5==0)
            return;
    }
    while(execs2add_online.size()>0)
    {
        mtk::tuple<mtk::msg::sub_product_code, mtk::trd::msg::sub_exec_conf> exec = execs2add_online.front();
        execs2add_online.pop_front();
        __direct_add_new_execution(exec._0, exec._1);
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

    for(mtk::list<mtk::tuple<mtk::msg::sub_product_code, mtk::trd::msg::sub_exec_conf> >::iterator it = execs_all.begin();  it != execs_all.end(); ++it)
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
    //menu.setStyleSheet(this->styleSheet());
    menu.exec(this->mapToGlobal(e->pos()));
}
