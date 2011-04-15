#include "qorder_table.h"


#include <QHeaderView>
#include <QAction>
#include <QHBoxLayout>
#include <QMenu>


#include "qmtk_misc.h"
#include "qt_components/src/qcommontabledelegate.h"
#include "components/trading/trd_cli_support.h"





namespace {
    const int col_session_id    = 0;
    const int col_req_code      = 1;
    const int col_market        = 2;
    const int col_product       = 3;
    const int col_side          = 4;
    const int col_price         = 5;
    const int col_quantity      = 6;
    const int col_exec_price    = 7;
    const int col_exec_quantity = 8;
    const int col_observs       = 9;
    const char* col_captions[] = { "sess_id", "req_code", "market", "product","side","price","qty","exec price", "exec qty", "observs" , 0};
};







QString get_session_id_from_order(mtk::CountPtr<mtk::trd::trd_cli_ls>& order)
{
    if (order->last_confirmation().HasValue())
        return order->last_confirmation().Get().confirmated_info.order_id.sess_id.c_str();
    else if (order->last_request().HasValue())
        return order->last_request().Get().order_id.sess_id.c_str();
    else
        throw mtk::Alarm(MTK_HERE, "qorderbook", "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
}


QString get_req_code_from_order(mtk::CountPtr<mtk::trd::trd_cli_ls>& order)
{
    if (order->last_confirmation().HasValue())
        return order->last_confirmation().Get().confirmated_info.order_id.req_code.c_str();
    else if (order->last_request().HasValue())
        return order->last_request().Get().order_id.req_code.c_str();
    else
        throw mtk::Alarm(MTK_HERE, "qorderbook", "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
}



//----------------------------------------------------------------------------------------------------
//  class order_in_qbook
//----------------------------------------------------------------------------------------------------
class order_in_qbook  : public mtk::SignalReceptor
{
    typedef order_in_qbook  CLASS_NAME;
public:
    order_in_qbook(QTableWidget *table_widget, const mtk::CountPtr<mtk::trd::trd_cli_ls>& order)
        : inner_order(order),
          items (new QTableWidgetItem*[10])
    {
        int row = table_widget->rowCount();
        table_widget->insertRow(row);

        for (int column=0; column<10; ++column)
        {
            items[column] = new QTableWidgetItem;
            items[column]->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            items[column]->setBackgroundColor(Qt::white);
            table_widget->setItem(row, column, items[column]);
            if (column == col_price  ||  column == col_quantity  ||  column == col_exec_quantity
                || column == col_exec_price)
                items[column]->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        }

        MTK_CONNECT_THIS(inner_order->sig_cf_cc, update_on_cf);
        MTK_CONNECT_THIS(inner_order->sig_cf_ex, update_on_cf);
        MTK_CONNECT_THIS(inner_order->sig_cf_md, update_on_cf);
        MTK_CONNECT_THIS(inner_order->sig_cf_nw, update_on_cf);
        MTK_CONNECT_THIS(inner_order->sig_rj_cc, update_on_rj);
        MTK_CONNECT_THIS(inner_order->sig_rj_md, update_on_rj);
        MTK_CONNECT_THIS(inner_order->sig_rj_nw, update_on_rj);
        MTK_CONNECT_THIS(inner_order->sig_rq_cc, update_on_rq);
        MTK_CONNECT_THIS(inner_order->sig_rq_md, update_on_rq);
        MTK_CONNECT_THIS(inner_order->sig_rq_nw, update_on_rq);
        update();
    }
    ~order_in_qbook() {
        delete [] items;
    }

    mtk::CountPtr<mtk::trd::trd_cli_ls> inner_order;
    QTableWidgetItem**                  items;

    void update(void)
    {
        update_item_session_id          ();
        update_item_req_code            ();
        update_item_market              ();
        update_item_product             ();
        update_item_price               ();
        update_item_quantity            ();
        update_item_side                ();
        update_item_exec_quantity       ();
        update_item_exec_price          ();
        update_item_exec_observations   ();
    }

    void update_on_cf(const mtk::trd::msg::CF_NW_LS&)  {    update();   }
    void update_on_cf(const mtk::trd::msg::CF_MD_LS&)  {    update();   }
    void update_on_cf(const mtk::trd::msg::CF_CC_LS&)  {    update();   }
    void update_on_cf(const mtk::trd::msg::CF_EX_LS&)  {    update();   }
    void update_on_rj(const mtk::trd::msg::RJ_NW_LS&)  {    update();   }
    void update_on_rj(const mtk::trd::msg::RJ_MD_LS&)  {    update();   }
    void update_on_rj(const mtk::trd::msg::RJ_CC_LS&)  {    update();   }
    void update_on_rq(const mtk::trd::msg::RQ_NW_LS&)  {    update();   }
    void update_on_rq(const mtk::trd::msg::RQ_MD_LS&)  {    update();   }
    void update_on_rq(const mtk::trd::msg::RQ_CC_LS&)  {    update();   }



    QColor  get_default_color(void)
    {
        if      (inner_order->serrors() != "")
            return mtk_red;
        else if (inner_order->in_market())
            //return mtk_yellow;
            return Qt::white;
        else if (inner_order->is_canceled())
            return Qt::gray;
        else if (inner_order->is_full_executed())
            return Qt::cyan;
        else
            return Qt::white;
    }

    void update_item_session_id(void)
    {
        QTableWidgetItem* item = items[col_session_id];
        item->setText(get_session_id_from_order(inner_order));
        item->setBackgroundColor(get_default_color());
    }


    void update_item_req_code()
    {
        QTableWidgetItem* item = items[col_req_code];
        item->setText(get_req_code_from_order(inner_order));
        if (inner_order->last_confirmation().HasValue()==false)
            item->setBackgroundColor(Qt::white);
        item->setBackgroundColor(get_default_color());
    }

    void update_item_market(void)
    {
        QTableWidgetItem* item = items[col_market];
        if (inner_order->last_confirmation().HasValue())
            item->setText(inner_order->last_confirmation().Get().confirmated_info.product_code.sys_code.market.c_str());
        else if (inner_order->last_request().HasValue())
            item->setText(inner_order->last_request().Get().product_code.sys_code.market.c_str());
        else
            throw mtk::Alarm(MTK_HERE, "qorderbook", "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
        item->setBackgroundColor(get_default_color());
    }

    void update_item_product(void)
    {
        QTableWidgetItem* item = items[col_product];
        if (inner_order->last_confirmation().HasValue())
            item->setText(inner_order->last_confirmation().Get().confirmated_info.product_code.sys_code.product.c_str());
        else if (inner_order->last_request().HasValue())
            item->setText(inner_order->last_request().Get().product_code.sys_code.product.c_str());
        else
            throw mtk::Alarm(MTK_HERE, "qorderbook", "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
        item->setBackgroundColor(get_default_color());
    }


    void update_item_price(void)
    {
        mtk::nullable<mtk::FixedNumber> requested;
        mtk::nullable<mtk::FixedNumber> confirmed;

        QTableWidgetItem* item = items[col_price];
        if (inner_order->last_confirmation().HasValue())
            confirmed = inner_order->last_confirmation().Get().confirmated_info.market_pos.price;
        if (inner_order->last_request().HasValue())
            requested = inner_order->last_request().Get().request_pos.price;


        if (requested.HasValue()==false  &&  confirmed.HasValue()==false)
            throw mtk::Alarm(MTK_HERE, "qorderbook", "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);

        if (confirmed.HasValue()  &&  requested.HasValue()  &&  confirmed.Get() == requested.Get())
        {
            item->setText(fn_as_QString(confirmed.Get()));
            item->setBackgroundColor(get_default_color());
        }
        else
        {
            item->setBackgroundColor(Qt::white);
            QString text_price;
            if (confirmed.HasValue())
                text_price += fn_as_QString(confirmed.Get());
            if (requested.HasValue())
                text_price += QString(" (") + fn_as_QString(requested.Get()) + QString(")");
            item->setText(text_price);
        }
        //item->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        if (inner_order->is_canceled())
            item->setBackgroundColor(Qt::gray);
    }

    void update_item_quantity(void)
    {
        mtk::nullable<mtk::FixedNumber> requested;
        mtk::nullable<mtk::FixedNumber> confirmed;

        QTableWidgetItem* item = items[col_quantity];
        if (inner_order->last_confirmation().HasValue())
            confirmed = inner_order->last_confirmation().Get().confirmated_info.market_pos.quantity;
        if (inner_order->last_request().HasValue())
            requested = inner_order->last_request().Get().request_pos.quantity;

        if (requested.HasValue()==false  &&  confirmed.HasValue()==false)
            throw mtk::Alarm(MTK_HERE, "qorderbook", "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);

        if (confirmed.HasValue()  &&  requested.HasValue()  &&  confirmed.Get() == requested.Get())
        {
            item->setText(fn_as_QString(confirmed.Get()));
            item->setBackgroundColor(get_default_color());
        }
        else
        {
            item->setBackgroundColor(Qt::white);
            QString text_price;
            if (confirmed.HasValue())
                text_price += fn_as_QString(confirmed.Get());
            if (requested.HasValue())
                text_price += QString(" (") + fn_as_QString(requested.Get()) + QString(")");
            item->setText(text_price);
        }
        if (inner_order->is_canceled())
            item->setBackgroundColor(Qt::gray);
    }



    void update_item_side(void)
    {
        QTableWidgetItem* item = items[col_side];
        mtk::trd::msg::enBuySell buy_sell;
        if (inner_order->last_confirmation().HasValue())
            buy_sell =inner_order->last_confirmation().Get().confirmated_info.market_pos.side;
        else if (inner_order->last_request().HasValue())
            buy_sell = inner_order->last_request().Get().request_pos.side;
        else
            throw mtk::Alarm(MTK_HERE, "qorderbook", "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
        if (buy_sell == mtk::trd::msg::buy)
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
        mtk::nullable<mtk::FixedNumber> confirmed;

        QTableWidgetItem* item = items[col_exec_quantity];
        if (inner_order->last_confirmation().HasValue())
        {
            confirmed = inner_order->last_confirmation().Get().confirmated_info.total_execs.quantity;
            item->setText(fn_as_QString(confirmed.Get()));
        }
        if (confirmed.HasValue()  &&  confirmed.Get().GetIntCode() != 0)
        {
            item->setBackgroundColor(Qt::cyan);
        }
        else
        {
            item->setText("");
            item->setBackgroundColor(get_default_color());
        }
    }
    void update_item_exec_price (void)
    {
        mtk::Double confirmed(mtk::Double::InvalidValue());

        QTableWidgetItem* item = items[col_exec_price];
        if (inner_order->last_confirmation().HasValue())
        {
            confirmed = inner_order->last_confirmation().Get().confirmated_info.total_execs.sum_price_by_qty
                            /
                            inner_order->last_confirmation().Get().confirmated_info.total_execs.quantity.GetDouble();
            item->setText(QString::number(confirmed.get()._0, 'f', 5));
        }
        if (confirmed >= mtk::Double(1.))
        {
            item->setBackgroundColor(Qt::cyan);
        }
        else
        {
            item->setText("");
            item->setBackgroundColor(get_default_color());
        }
    }

    void update_item_exec_observations   (void)
    {
        QTableWidgetItem* item = items[col_observs];
        item->setBackgroundColor(get_default_color());
        item->setText(inner_order->serrors().c_str());
    }


};
//----------------------------------------------------------------------------------------------------
//  class order_in_qbook
//----------------------------------------------------------------------------------------------------



qorder_table::qorder_table(QWidget *parent) :
        QWidget(parent),
        table_widget(new QTableWidget(this)),
        orders(new mtk::map<mtk::trd::msg::sub_order_id, mtk::CountPtr<order_in_qbook> >),
        filterf (new filter_form(this))
{
    QHBoxLayout *hl= new QHBoxLayout(this);
    hl->setSpacing(0);
    hl->setContentsMargins(0, 0, 0, 0);
    hl->addWidget(table_widget);

    hl->addWidget(filterf);
    hl->setStretch(0,1);
    filterf->hide();

    connect(filterf, SIGNAL(signal_filter_modified(filter_data)), this, SLOT(slot_apply_filter(filter_data)));



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
    table_widget->setColumnWidth(col_session_id, 20);
    table_widget->setColumnWidth(col_req_code, 20);
    table_widget->setColumnWidth(col_observs, 400);
    table_widget->horizontalHeader()->setStretchLastSection(true);

    table_widget->setItemDelegate(new QCommonTableDelegate(table_widget));
    table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_widget->setSelectionMode(QAbstractItemView::SingleSelection);
    table_widget->setShowGrid(false);

    //  setting up actions
    /*
    setContextMenuPolicy(Qt::ActionsContextMenu);
    {
        QAction* action = new QAction("cancel", this);
        connect(action, SIGNAL(triggered()), this, SLOT(request_cancel()));
        addAction(action);
        action_cancel = action;
    }
    {
        QAction* action = new QAction("modif", this);
        connect(action, SIGNAL(triggered()), this, SLOT(request_modif()));
        addAction(action);
        action_modif = action;
    }
    {
        QAction* action = new QAction(this);
        action->setSeparator(true);
        addAction(action);
    }
    {
        QAction* action = new QAction("empty", this);
        action->setEnabled(false);
        addAction(action);
    }
    */


    MTK_CONNECT_THIS(mtk::trd::trd_cli_ord_book::get_sig_order_ls_new(), on_new_order);
    MTK_TIMER_1C(timer_get_orders2add);

    slot_apply_filter(filter_data());
    //setContentsMargins(0,0,0,0);
}

qorder_table::~qorder_table()
{
    delete orders;
}


void qorder_table::__direct_add_new_order(const mtk::trd::msg::sub_order_id& order_id, mtk::CountPtr<mtk::trd::trd_cli_ls>& order)
{
    orders->insert(std::make_pair(order_id, mtk::make_cptr(new order_in_qbook(table_widget, order))));
}

void qorder_table::on_new_order(const mtk::trd::msg::sub_order_id& order_id, mtk::CountPtr<mtk::trd::trd_cli_ls>& /*order*/)
{
    orders2add_online.push_back(order_id);
    //orders->insert(std::make_pair(order_id, mtk::make_cptr(new order_in_qbook(this, order))));
/*
    static int size = QFontMetrics(this->font()).height()*1.4;
    static bool initialized=false;
    if (!initialized)
        table_widget->verticalHeader()->setDefaultSectionSize(size);
    initialized = true;
*/
}





mtk::trd::msg::sub_order_id   get_order_id_from_row(QTableWidget *table_widget, int row)
{
    std::string session_id;
    std::string request_code;
    QTableWidgetItem* item;

    item = table_widget->item(row, col_session_id);
    if (item)   session_id = item->text().toStdString();
    else throw mtk::Alarm(MTK_HERE, "qorderbook", "missing item", mtk::alPriorCritic, mtk::alTypeNoPermisions);

    item = table_widget->item(row, col_req_code);
    if (item)   request_code = item->text().toStdString();
    else throw mtk::Alarm(MTK_HERE, "qorderbook", "missing item", mtk::alPriorCritic, mtk::alTypeNoPermisions);

    return mtk::trd::msg::sub_order_id(mtk::msg::sub_request_id(session_id, request_code));
}

void qorder_table::request_modif(void)
{
    int row = table_widget->currentRow();
    if (row==-1)        return;
    const mtk::trd::msg::sub_order_id   ord_id(get_order_id_from_row(table_widget, row));
    mtk::trd::trd_cli_ord_book::rq_md_ls_manual(ord_id);
}

void qorder_table::request_cancel(void)
{
    int row = table_widget->currentRow();
    if (row==-1)        return;
    const mtk::trd::msg::sub_order_id   ord_id(get_order_id_from_row(table_widget, row));
    mtk::trd::trd_cli_ord_book::rq_cc_ls(ord_id);
}


bool check_filter_order(const filter_data     fd, const mtk::trd::msg::sub_order_id& order_id)
{
    mtk::CountPtr<mtk::trd::trd_cli_ls> order=mtk::trd::trd_cli_ord_book::get_order_ls(order_id);
    mtk::msg::sub_product_code pc = mtk::trd::get_product_code(*order);
    int matches = 0;
    if(mtk::s_toUpper(pc.sys_code.user_name).find(fd.product.toUpper().toStdString())!=std::string::npos
                ||  mtk::s_toUpper(pc.sys_code.product).find(fd.product.toUpper().toStdString())!=std::string::npos)
        ++matches;
    if(mtk::s_toUpper(pc.sys_code.market).find(fd.market.toUpper().toStdString())!=std::string::npos)
        ++matches;

    if(matches==2)  return true;
    else            return false;
}

void qorder_table::slot_apply_filter(const filter_data& fd)
{
    //if(fd.name == current_filter.name  &&  fd.client_code  ==  current_filter.client_code
    //                        &&  fd.market  ==  current_filter.market  &&  fd.product == current_filter.product)
    //    return;

    Q_EMIT(signal_named_changed(fd.name));
    orders->clear();
    table_widget->setRowCount(0);
    mtk::list<mtk::trd::msg::sub_order_id> all_orders = mtk::trd::trd_cli_ord_book::get_all_order_ids();
    for(mtk::list<mtk::trd::msg::sub_order_id>::const_iterator it= all_orders.begin(); it!=all_orders.end(); ++it)
            orders2add_loading.push_back(*it);

    current_filter = fd;
}

void   qorder_table::timer_get_orders2add(void)
{
    int counter=0;
    while(orders2add_loading.size()>0)
    {
        mtk::trd::msg::sub_order_id order_id = orders2add_loading.front();
        orders2add_loading.pop_front();
        if(check_filter_order(current_filter, order_id))
        {
            mtk::CountPtr<mtk::trd::trd_cli_ls> order=mtk::trd::trd_cli_ord_book::get_order_ls(order_id);
            __direct_add_new_order(order_id, order);
            ++counter;
            if(counter%5==0)
                return;
        }
    }
    while(orders2add_online.size()>0)
    {
        mtk::trd::msg::sub_order_id order_id = orders2add_online.front();
        orders2add_online.pop_front();
        if(check_filter_order(current_filter, order_id))
        {
            mtk::CountPtr<mtk::trd::trd_cli_ls> order=mtk::trd::trd_cli_ord_book::get_order_ls(order_id);
            __direct_add_new_order(order_id, order);
            ++counter;
            if(counter%5==0)
                return;
        }
    }
}

void qorder_table::update_sizes()
{
    table_widget->verticalHeader()->setDefaultSectionSize(QFontMetrics(this->font()).height()*1.4);
}

void qorder_table::show_filter(bool show)
{
    if(show)
    {
        filterf->set_filter_conf(current_filter);
        filterf->show();
    }
    else
        filterf->hide();
}


bool qorder_table::is_filter_visible(void)
{
    return filterf->isVisible();
}

void qorder_table::contextMenuEvent(QContextMenuEvent *e)
{
    bool enabled_cancel=false;
    bool enabled_modif = false;
    int row = table_widget->currentRow();
    if (row==-1)
    {
        enabled_cancel = false;
        enabled_modif = false;
    }
    else
    {
        mtk::trd::msg::sub_order_id   ord_id(get_order_id_from_row(table_widget, row));

        mtk::CountPtr<mtk::trd::trd_cli_ls> order=mtk::trd::trd_cli_ord_book::get_order_ls(ord_id);
        if(order->is_canceled()  ||  order->is_full_executed())
        {
            enabled_cancel = false;
            enabled_modif = false;
        }
        else
        {
            enabled_cancel = true;
            enabled_modif = true;
        }
    }
    QMenu  menu;
    {
        QAction* action = new QAction("cancel", this);
        connect(action, SIGNAL(triggered()), this, SLOT(request_cancel()));
        action->setEnabled(enabled_cancel);
        menu.addAction(action);
    }
    {
        QAction* action = new QAction("modif", this);
        connect(action, SIGNAL(triggered()), this, SLOT(request_modif()));
        action->setEnabled(enabled_modif);
        menu.addAction(action);
    }
    {
        QAction* action = new QAction(this);
        action->setSeparator(true);
        menu.addAction(action);
    }
    {
        QAction* action = new QAction("empty", this);
        action->setEnabled(false);
        menu.addAction(action);
    }
    menu.setStyleSheet(this->styleSheet());
    menu.exec(this->mapToGlobal(e->pos()));
}
