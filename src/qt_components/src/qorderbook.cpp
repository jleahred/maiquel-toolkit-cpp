#include "qorderbook.h"

#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QAction>

#include "qeditorder.h"
#include "qmtk_misc.h"


//  pending admin
namespace mtk {
    namespace  msg {


        sub_request_info   get_request_info (void)
        {
            static int contador;
            return sub_request_info(    sub_request_id("sess_id", MTK_SS(contador)),
                                        "CLIENT");
        }


      };   //namespace msg {
};  //namespace mtk {



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


void on_request_with_user_check(mtk::trd::msg::RQ_XX_LS& rq, bool& canceled)
{
    QEditOrder eo(rq);
    if (eo.exec())
    {
        rq = eo.get_request();
    }
    else canceled =true;
}



QString get_session_id_from_order(mtk::CountPtr<mtk::trd::trd_cli_ls>& order)
{
    if (order->last_confirmation().HasValue())
        return order->last_confirmation().Get().confirmated_info.order_id.sess_id.c_str();
    else if (order->last_request().HasValue())
        return order->last_request().Get().order_id.sess_id.c_str();
    else
        throw mtk::Alarm(MTK_HERE, "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
}


QString get_req_code_from_order(mtk::CountPtr<mtk::trd::trd_cli_ls>& order)
{
    if (order->last_confirmation().HasValue())
        return order->last_confirmation().Get().confirmated_info.order_id.req_code.c_str();
    else if (order->last_request().HasValue())
        return order->last_request().Get().order_id.req_code.c_str();
    else
        throw mtk::Alarm(MTK_HERE, "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
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
            items[column]->setFlags(Qt::ItemIsEnabled);
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
    }
    ~order_in_qbook() { delete [] items; }

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
            return Qt::red;
        else if (inner_order->in_market())
            return Qt::yellow;
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
            throw mtk::Alarm(MTK_HERE, "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
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
            throw mtk::Alarm(MTK_HERE, "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
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
            throw mtk::Alarm(MTK_HERE, "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);

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
            throw mtk::Alarm(MTK_HERE, "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);

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
            throw mtk::Alarm(MTK_HERE, "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
        if (buy_sell == mtk::trd::msg::buy)
        {
            item->setText("buy");
            item->setBackgroundColor(Qt::green);
        }
        else
        {
            item->setText("sell");
            item->setBackgroundColor(QColor(Qt::red).lighter());
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



QOrderBook::QOrderBook(QWidget *parent) :
    QWidget(parent),
    table_widget(new QTableWidget(this)),
    orders(new mtk::map<mtk::trd::msg::sub_order_id, mtk::CountPtr<order_in_qbook> >)
{
    QStringList headers_captions;
    {
        int counter;
        for (counter=0; col_captions[counter]!=0; ++counter)
            headers_captions.append(col_captions[counter]);
        table_widget->setColumnCount(counter);
    }
    table_widget->setHorizontalHeaderLabels(headers_captions);
    table_widget->verticalHeader()->setDefaultSectionSize(20);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(table_widget);
    this->setLayout(layout);
    table_widget->verticalHeader()->setVisible(false);
    table_widget->setSelectionMode(QAbstractItemView::SingleSelection);
    table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_widget->setColumnWidth(col_session_id, 20);
    table_widget->setColumnWidth(col_req_code, 20);
    table_widget->setColumnWidth(col_observs, 400);

    //  setting up actions
    table_widget->setContextMenuPolicy(Qt::ActionsContextMenu);
    {
        QAction* action = new QAction("cancel", this);
        connect(action, SIGNAL(triggered()), this, SLOT(request_cancel()));
        table_widget->addAction(action);
    }
    {
        QAction* action = new QAction("modif", this);
        connect(action, SIGNAL(triggered()), this, SLOT(request_modif()));
        table_widget->addAction(action);
    }
    {
        QAction* action = new QAction(this);
        action->setSeparator(true);
        table_widget->addAction(action);
    }
    {
        QAction* action = new QAction("filter", this);
        connect(action, SIGNAL(triggered()), this, SLOT(request_cancel()));
        table_widget->addAction(action);
    }



    MTK_CONNECT_THIS(mtk::trd::trd_cli_ord_book::get_sig_order_ls_new(), on_new_order);
    mtk::trd::trd_cli_ord_book::get_signal_request_hook().connect(on_request_with_user_check);
    //setContentsMargins(0,0,0,0);
}

QOrderBook::~QOrderBook()
{
}




void QOrderBook::on_new_order(const mtk::trd::msg::sub_order_id& order_id, mtk::CountPtr<mtk::trd::trd_cli_ls>& order)
{
    orders->insert(std::make_pair(order_id, mtk::make_cptr(new order_in_qbook(table_widget, order))));
}





mtk::trd::msg::sub_order_id   get_order_id_from_row(QTableWidget *table_widget, int row)
{
    std::string session_id;
    std::string request_code;
    QTableWidgetItem* item;

    item = table_widget->item(row, col_session_id);
    if (item)   session_id = item->text().toStdString();
    else throw mtk::Alarm(MTK_HERE, "missing item", mtk::alPriorCritic, mtk::alTypeNoPermisions);

    item = table_widget->item(row, col_req_code);
    if (item)   request_code = item->text().toStdString();
    else throw mtk::Alarm(MTK_HERE, "missing item", mtk::alPriorCritic, mtk::alTypeNoPermisions);

    return mtk::trd::msg::sub_order_id(mtk::msg::sub_request_id(session_id, request_code));
}

void QOrderBook::request_modif(void)
{
    int row = table_widget->currentRow();
    if (row==-1)        return;
    const mtk::trd::msg::sub_order_id   ord_id(get_order_id_from_row(table_widget, row));
    mtk::trd::trd_cli_ord_book::rq_md_ls_manual(ord_id);
}

void QOrderBook::request_cancel(void)
{
    int row = table_widget->currentRow();
    if (row==-1)        return;
    const mtk::trd::msg::sub_order_id   ord_id(get_order_id_from_row(table_widget, row));
    mtk::trd::trd_cli_ord_book::rq_cc_ls(ord_id);
}
