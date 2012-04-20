#include "qexecs_table_acc.h"


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





namespace {
    const int col_count = 5;

    const int col_market_product    = 0;
    const int col_side              = 1;
    const int col_exec_quantity     = 2;
    const int col_exec_price        = 3;
    const int col_exec_description  = 4;
};









//----------------------------------------------------------------------------------------------------
//  class Exec_in_table_acc
//----------------------------------------------------------------------------------------------------
class Exec_in_table_acc  : public mtk::SignalReceptor
{
    typedef Exec_in_table_acc  CLASS_NAME;
public:

    QTableWidgetItem**                              items;
    mtk::trd::hist::order_exec_item_acc_by_price    exec_item;
    void set_exec_item(const mtk::trd::hist::order_exec_item_acc_by_price& _exec_item) { exec_item = _exec_item; update(); }

    Exec_in_table_acc(QTableWidget *table_widget, const mtk::trd::hist::order_exec_item_acc_by_price&     _exec_item)
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
    ~Exec_in_table_acc() { delete [] items; }


    void update(void)
    {
        update_item_market_product      ();
        update_item_exec_quantity       ();
        update_item_exec_price          ();
        update_item_side                ();
        update_item_description         ();
    }


    QColor  get_default_color(void)
    {
        return qtmisc::mtk_color_executed;
    }


    void update_item_market_product(void)
    {
        QTableWidgetItem* item = items[col_market_product];
        item->setText(QLatin1String(MTK_SS(exec_item.invariant.product_code.market << "." << exec_item.invariant.product_code.product).c_str()));
        item->setBackgroundColor(get_default_color());
    }


    void update_item_side(void)
    {
        QTableWidgetItem* item = items[col_side];

        if (exec_item.invariant.side == mtk::trd::msg::buy)
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
        item->setText(qtmisc::fn_as_QString(exec_item.quantity));
        item->setBackgroundColor(get_default_color());
    }
    void update_item_exec_price (void)
    {
        QTableWidgetItem* item = items[col_exec_price];
        item->setText(qtmisc::fn_as_QString(exec_item.price));
        item->setBackgroundColor(get_default_color());
    }
    void update_item_description (void)
    {
        QTableWidgetItem* item = items[col_exec_description];
//        item->setText(QLatin1String(exec_item.description.c_str()));
        item->setBackgroundColor(get_default_color());
    }


};
//----------------------------------------------------------------------------------------------------
//  class Exec_in_table_acc
//----------------------------------------------------------------------------------------------------



QExecsTable_acc::QExecsTable_acc(QWidget *parent) :
        QWidget(parent),
        table_widget(new QTableWidget(this)),
        exec_in_table(new mtk::vector<Exec_in_table_acc*>)
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
                                                        QT_TR_NOOP("remarks"),
                                                        0          };


        int counter;
        for (counter=0; col_captions[counter]!=0; ++counter)
            headers_captions.append(tr(col_captions[counter]));
        table_widget->setColumnCount(counter);
    }
    table_widget->setHorizontalHeaderLabels(headers_captions);

    table_widget->verticalHeader()->setVisible(false);
    table_widget->horizontalHeader()->setStretchLastSection(true);


    {
        QCommonTableDelegate* delegate_paint = new QCommonTableDelegate(table_widget);
        delegate_paint->set_horiz_line_each(1);
        table_widget->setItemDelegate(delegate_paint);
    }
    table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_widget->setSelectionMode(QAbstractItemView::SingleSelection);
    table_widget->setShowGrid(false);

    table_widget->setColumnWidth(col_market_product, 130);
    table_widget->setColumnWidth(col_side, 60);
    table_widget->setColumnWidth(col_exec_price, 120);
    table_widget->setColumnWidth(col_exec_quantity, 120);
    table_widget->setColumnWidth(col_exec_description, 60);


    MTK_TIMER_1C(timer_get_execs2add);
}


void QExecsTable_acc::__direct_add_new_execution(const mtk::tuple<int, mtk::trd::hist::order_exec_item_acc_by_price>& exec)
{
    if(exec._0 == -1  ||  unsigned(exec._0) >= this->exec_in_table->size())
        exec_in_table->push_back(new Exec_in_table_acc(table_widget, exec._1));
    else
        exec_in_table->at(exec._0)->set_exec_item(exec._1);
}




void   QExecsTable_acc::timer_get_execs2add(void)
{
    int counter=0;
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

void QExecsTable_acc::update_sizes()
{
    table_widget->verticalHeader()->setDefaultSectionSize(QFontMetrics(this->font()).height()*1.2);
}





void QExecsTable_acc::on_new_item(const mtk::trd::hist::order_exec_item_acc_by_price&  exec_item)
{
    execs2add_online.push_back(mtk::make_tuple(-1, exec_item));
}

void QExecsTable_acc::on_modif_item(int pos, const mtk::trd::hist::order_exec_item_acc_by_price&  exec_item)
{
    execs2add_online.push_back(mtk::make_tuple(pos, exec_item));
}


void   QExecsTable_acc::set_executions(mtk::CountPtr<mtk::trd::hist::order_EXECS_historic>  _execs_history)
{
    mtk::CountPtr<mtk::list<mtk::trd::hist::order_exec_item_acc_by_price> >   hist_execs =   _execs_history->get_items_list_acc_by_price();

    MTK_CONNECT_THIS(_execs_history->signal_new_item_added_acc_by_price, on_new_item);
    MTK_CONNECT_THIS(_execs_history->signal_modif_item_acc_by_price,     on_modif_item);

    table_widget->setRowCount(0);
    exec_in_table->clear();
    execs2add_online.clear();

    for(auto it = hist_execs->rbegin(); it != hist_execs->rend(); ++it)
        on_new_item(*it);

    execs_history = _execs_history;
}

