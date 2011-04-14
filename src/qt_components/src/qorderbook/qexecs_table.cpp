#include "qexecs_table.h"


#include <QHeaderView>
#include <QAction>
#include <QHBoxLayout>



#include "qmtk_misc.h"
#include "qt_components/src/qcommontabledelegate.h"
#include "components/trading/trd_cli_support.h"





namespace {
    const int col_market_product= 0;
    const int col_side          = 1;
    const int col_exec_price    = 2;
    const int col_exec_quantity = 3;
    const char* col_captions[] = { "product", "side", "price", "qty", 0};
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
    mtk::trd::msg::sub_position_ls      exec;

    Exec_in_table(QTableWidget *table_widget, const mtk::msg::sub_product_code& _product_code, const mtk::trd::msg::sub_position_ls& _exec)
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
        return Qt::cyan;
    }


    void update_item_market_product(void)
    {
        QTableWidgetItem* item = items[col_market_product];
        item->setText(MTK_SS(product_code.sys_code.market << "." <<product_code.sys_code.user_name).c_str());
        item->setBackgroundColor(get_default_color());
    }


    void update_item_side(void)
    {
        QTableWidgetItem* item = items[col_side];
        if (exec.side == mtk::trd::msg::buy)
        {
            item->setText("buy");
            item->setBackgroundColor(mtk_green);
        }
        else
        {
            item->setText("sell");
            item->setBackgroundColor(mtk_red);
        }
        item->setTextAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    }

    void update_item_exec_quantity (void)
    {
        QTableWidgetItem* item = items[col_exec_quantity];
        item->setText(fn_as_QString(exec.quantity));
        item->setBackgroundColor(get_default_color());
    }
    void update_item_exec_price (void)
    {
        QTableWidgetItem* item = items[col_exec_price];
        item->setText(fn_as_QString(exec.price));
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
        mediaObject (Phonon::createPlayer(Phonon::NoCategory, Phonon::MediaSource("../data/execution.wav")))
{
    QHBoxLayout *hl= new QHBoxLayout(this);
    hl->setSpacing(0);
    hl->setContentsMargins(0, 0, 0, 0);
    hl->addWidget(table_widget);

    QStringList headers_captions;
    {
        int counter;
        for (counter=0; col_captions[counter]!=0; ++counter)
            headers_captions.append(col_captions[counter]);
        table_widget->setColumnCount(counter);
    }
    table_widget->setHorizontalHeaderLabels(headers_captions);

    table_widget->verticalHeader()->setVisible(false);
    //table_widget->verticalHeader()->setDefaultSectionSize(QFontMetrics(this->font()).height()*1.4);  moved on_new_order
    //table_widget->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    table_widget->horizontalHeader()->setStretchLastSection(true);

    table_widget->setItemDelegate(new QCommonTableDelegate(table_widget));
    table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_widget->setSelectionMode(QAbstractItemView::SingleSelection);
    table_widget->setShowGrid(false);

    table_widget->setColumnWidth(col_market_product, 120);
    table_widget->setColumnWidth(col_side, 40);
    table_widget->setColumnWidth(col_exec_price, 80);
    //table_widget->setColumnWidth(col_exec_quantity, 50);

    connect(table_widget, SIGNAL(cellDoubleClicked(int,int)), SLOT(slot_clean_execs()));
    table_widget->setToolTip("Double click to clean executions");

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


void QExecsTable::__direct_add_new_execution(const mtk::msg::sub_product_code& pc, const mtk::trd::msg::sub_position_ls& exec)
{
    exec_in_table->push_back(new Exec_in_table(table_widget, pc, exec));
}

void QExecsTable::on_new_execution(const mtk::msg::sub_product_code& pc, const mtk::trd::msg::sub_position_ls& exec)
{
    execs2add_online.push_back(mtk::make_tuple(pc, exec));
    mediaObject->play();
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
        mtk::tuple<mtk::msg::sub_product_code, mtk::trd::msg::sub_position_ls> exec = execs2add_loading.front();
        execs2add_loading.pop_front();
        __direct_add_new_execution(exec._0, exec._1);
        ++counter;
        if(counter%5==0)
            return;
    }
    while(execs2add_online.size()>0)
    {
        mtk::tuple<mtk::msg::sub_product_code, mtk::trd::msg::sub_position_ls> exec = execs2add_online.front();
        execs2add_online.pop_front();
        __direct_add_new_execution(exec._0, exec._1);
        ++counter;
        if(counter%5==0)
            return;
    }
}

void QExecsTable::update_sizes()
{
    table_widget->verticalHeader()->setDefaultSectionSize(QFontMetrics(this->font()).height()*1.4);
}

void  QExecsTable::slot_clean_execs(void)
{
    table_widget->setRowCount(0);
}
