#include "qorder_table.h"


#include <QHeaderView>
#include <QAction>
#include <QHBoxLayout>
#include <QMenu>
#include <QMessageBox>

#include "qmtk_misc.h"
#include "qt_components/src/qcommontabledelegate.h"
#include "components/trading/trd_cli_support.h"
#include "components/trading/msg_trd_cli_ls.h"
#include "components/trading/msg_trd_cli_mk.h"
#include "components/trading/accounts/account_manager_cli.h"





namespace {
    const int col_session_id    = 0;
    const int col_req_code      = 1;
    const int col_cli_code      = 2;
    const int col_account       = 3;
    const int col_order_type    = 4;
    const int col_market        = 5;
    const int col_product       = 6;
    const int col_side          = 7;
    const int col_quantity      = 8;
    const int col_price         = 9;
    const int col_exec_quantity = 10;
    const int col_rem_quantity  = 11;
    const int col_exec_price    = 12;
    const int col_remarks       = 13;

    const int count_items       = 14;
    /*
    const char* const col_captions[] = {    "sess_id",            defined later for translations
                                        QObject::tr("req_code"),
                                        QObject::tr("market"),
                                        QObject::tr("product"),
                                        QObject::tr("side"),
                                        QObject::tr("price"),
                                        QObject::tr("qty"),
                                        QObject::tr("exec price"),
                                        QObject::tr("exec qty"),
                                        QObject::tr("remarks"),
                                        QObject::tr("")                 };
    */



    mtk::list<mtk::trd::msg::sub_order_id>     __do_not_use_it_directly_orders_in_sequence;      //     orders in received sequence

    void realocate_orders_in_sequence(const mtk::trd::msg::sub_order_id& order_id)
    {
        static mtk::trd::msg::sub_order_id  last_ord_id = order_id;
        static bool first_execution=true;
        if(!first_execution)
        {
            if(last_ord_id == order_id)     return;
        }
        else
            first_execution = false;
        last_ord_id = order_id;


        //  realocate   orders_in_sequence
        {
            //  look and delete from orders_in_sequence      dangerous optimization
            bool located=false;
            for(mtk::list<mtk::trd::msg::sub_order_id>::iterator it = __do_not_use_it_directly_orders_in_sequence.begin(); it!= __do_not_use_it_directly_orders_in_sequence.end(); ++it)
            {
                if(*it == order_id)
                {
                    it = __do_not_use_it_directly_orders_in_sequence.erase(it);
                    if(located==true)
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qordertable", MTK_SS("duplicated order in sequence " << order_id), mtk::alPriorError, mtk::alTypeNoPermisions));
                    located=true;
                }
            }
            if(located==false)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qordertable", MTK_SS("missing order in sequence " << order_id), mtk::alPriorError, mtk::alTypeNoPermisions));
            __do_not_use_it_directly_orders_in_sequence.push_back(order_id);
        }
    }
    void add_new_order_orders_in_sequence(const mtk::trd::msg::sub_order_id& order_id)
    {
        static mtk::trd::msg::sub_order_id  last_ord_id = order_id;
        static bool first_execution=true;
        if(!first_execution)
        {
            if(last_ord_id == order_id)     return;
        }
        else
            first_execution = false;
        last_ord_id = order_id;

        //  realocate   orders_in_sequence
        {
            //  look and delete from orders_in_sequence      dangerous optimization
            bool located=false;
            for(mtk::list<mtk::trd::msg::sub_order_id>::iterator it = __do_not_use_it_directly_orders_in_sequence.begin(); it!= __do_not_use_it_directly_orders_in_sequence.end(); ++it)
            {
                if(*it == order_id)
                {
                    it = __do_not_use_it_directly_orders_in_sequence.erase(it);
                    if(located==true)
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qordertable", MTK_SS("duplicated order in sequence " << order_id), mtk::alPriorError, mtk::alTypeNoPermisions));
                    located=true;
                }
            }
            if(located==true)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qordertable", MTK_SS("adding new order in sequence, exist a previus one" << order_id), mtk::alPriorError, mtk::alTypeNoPermisions));
            __do_not_use_it_directly_orders_in_sequence.push_back(order_id);
        }
    }

    mtk::msg::sub_product_code    get_product_code(const mtk::trd::msg::sub_order_id& ord_id)
    {
        mtk::trd::trd_cli_ord_book::en_order_type  order_type = mtk::trd::trd_cli_ord_book::get_order_type(ord_id);
        if(order_type ==  mtk::trd::trd_cli_ord_book::ot_limit)
            return mtk::trd::get_product_code(*mtk::trd::trd_cli_ord_book::get_order_ls(ord_id));
        else if(order_type ==  mtk::trd::trd_cli_ord_book::ot_market)
            return mtk::trd::get_product_code(*mtk::trd::trd_cli_ord_book::get_order_mk(ord_id));
        else
            throw mtk::Alarm(MTK_HERE, "qordertable", MTK_SS("missing order type for orderid " << ord_id), mtk::alPriorCritic, mtk::alTypeNoPermisions);
    }

    mtk::trd::msg::sub_account_info    get_account(const mtk::trd::msg::sub_order_id& ord_id)
    {
        mtk::trd::trd_cli_ord_book::en_order_type  order_type = mtk::trd::trd_cli_ord_book::get_order_type(ord_id);
        if(order_type ==  mtk::trd::trd_cli_ord_book::ot_limit)
            return mtk::trd::get_account(*mtk::trd::trd_cli_ord_book::get_order_ls(ord_id));
        else if(order_type ==  mtk::trd::trd_cli_ord_book::ot_market)
            return mtk::trd::get_account(*mtk::trd::trd_cli_ord_book::get_order_mk(ord_id));
        else
            throw mtk::Alarm(MTK_HERE, "qordertable", MTK_SS("missing order type for orderid " << ord_id), mtk::alPriorCritic, mtk::alTypeNoPermisions);
    }

    mtk::FixedNumber   get_total_exec_quantity (const mtk::trd::msg::sub_order_id& ord_id)
    {
        mtk::trd::trd_cli_ord_book::en_order_type  order_type = mtk::trd::trd_cli_ord_book::get_order_type(ord_id);
        if(order_type ==  mtk::trd::trd_cli_ord_book::ot_limit)
        {

            mtk::CountPtr<mtk::trd::trd_cli_ls> order=mtk::trd::trd_cli_ord_book::get_order_ls(ord_id);
            if(order->last_confirmation().HasValue())
            {
                return order->last_confirmation().Get().total_execs.acc_quantity;
            }
            else
                return mtk::FixedNumber(mtk::fnIntCode(0), mtk::fnDec(0), mtk::fnInc(0));

        }
        else if(order_type ==  mtk::trd::trd_cli_ord_book::ot_market)
        {

            mtk::CountPtr<mtk::trd::trd_cli_mk> order=mtk::trd::trd_cli_ord_book::get_order_mk(ord_id);
            if(order->last_confirmation().HasValue())
            {
                return order->last_confirmation().Get().total_execs.acc_quantity;
            }
            else
                return mtk::FixedNumber(mtk::fnIntCode(0), mtk::fnDec(0), mtk::fnInc(0));

        }
        else
            throw mtk::Alarm(MTK_HERE, "qordertable", MTK_SS("missing order type for orderid " << ord_id), mtk::alPriorError, mtk::alTypeNoPermisions);
    }
    bool  is_canceled(const mtk::trd::msg::sub_order_id& ord_id)
    {
        mtk::trd::trd_cli_ord_book::en_order_type  order_type = mtk::trd::trd_cli_ord_book::get_order_type(ord_id);
        if(order_type ==  mtk::trd::trd_cli_ord_book::ot_limit)
            return  mtk::trd::trd_cli_ord_book::get_order_ls(ord_id)->is_canceled();
        else if(order_type ==  mtk::trd::trd_cli_ord_book::ot_market)
            return  mtk::trd::trd_cli_ord_book::get_order_mk(ord_id)->is_canceled();
        else
            throw mtk::Alarm(MTK_HERE, "qordertable", MTK_SS("missing order type for orderid " << ord_id), mtk::alPriorCritic, mtk::alTypeNoPermisions);
    }

    bool  is_full_executed(const mtk::trd::msg::sub_order_id& ord_id)
    {
        mtk::trd::trd_cli_ord_book::en_order_type  order_type = mtk::trd::trd_cli_ord_book::get_order_type(ord_id);
        if(order_type ==  mtk::trd::trd_cli_ord_book::ot_limit)
            return  mtk::trd::trd_cli_ord_book::get_order_ls(ord_id)->is_full_executed();
        else if(order_type ==  mtk::trd::trd_cli_ord_book::ot_market)
            return  mtk::trd::trd_cli_ord_book::get_order_mk(ord_id)->is_full_executed();
        else
            throw mtk::Alarm(MTK_HERE, "qordertable", MTK_SS("missing order type for orderid " << ord_id), mtk::alPriorError, mtk::alTypeNoPermisions);
    }


};










//----------------------------------------------------------------------------------------------------
//  class order_in_qbook
//----------------------------------------------------------------------------------------------------
class order_in_qbook
{
public:
    QTableWidgetItem**                                  items;
    mtk::Signal<const mtk::trd::msg::sub_order_id&>     signal_executed_order;

    order_in_qbook(QTableWidget *table_widget)
        :   items (new QTableWidgetItem*[count_items])
    {
        int row = table_widget->rowCount();
        table_widget->insertRow(row);

        for (int column=0; column<count_items; ++column)
        {
            items[column] = new QTableWidgetItem;
            items[column]->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            items[column]->setBackgroundColor(Qt::white);
            table_widget->setItem(row, column, items[column]);
            if (column == col_price  ||  column == col_quantity  ||  column == col_exec_quantity
                || column == col_exec_price  ||  column == col_rem_quantity)
                items[column]->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            else if(column == col_order_type)
                items[column]->setTextAlignment(Qt::AlignCenter|Qt::AlignVCenter);
        }

        table_widget->scrollToBottom();
        //update();     calling virtual functions on constructor????    crazy
    }
    virtual ~order_in_qbook() {
        delete [] items;
    }

    int get_row(void) const  {    return  items[0]->row();  }

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
        update_item_cli_code            ();
        update_item_account             ();
        update_item_rem_quantity        ();
        update_item_order_type          ();
    }

    virtual void   update_item_session_id          ()=0;
    virtual void   update_item_req_code            ()=0;
    virtual void   update_item_market              ()=0;
    virtual void   update_item_product             ()=0;
    virtual void   update_item_price               ()=0;
    virtual void   update_item_quantity            ()=0;
    virtual void   update_item_side                ()=0;
    virtual void   update_item_exec_quantity       ()=0;
    virtual void   update_item_exec_price          ()=0;
    virtual void   update_item_exec_observations   ()=0;
    virtual void   update_item_cli_code            ()=0;
    virtual void   update_item_account             ()=0;
    virtual void   update_item_rem_quantity        ()=0;
    virtual void   update_item_order_type          ()=0;

};


template<typename  ORDER_TYPE>
class order_in_qbook_xx  :    public  order_in_qbook
{
    typedef order_in_qbook_xx  CLASS_NAME;
public:
    mtk::CountPtr<ORDER_TYPE>                 inner_order;

    order_in_qbook_xx(QTableWidget *table_widget, const mtk::CountPtr<ORDER_TYPE>& order)
        : order_in_qbook(table_widget), inner_order(order)
    {
    }
    ~order_in_qbook_xx() {
    }


    QColor  get_default_color(void)
    {
        if      (inner_order->serrors() != "")
            return qtmisc::mtk_color_problem;
        else if (get_lasttr_rjdescr(*inner_order) != "")
            return qtmisc::mtk_color_problem;
        else if (inner_order->in_market())
            return Qt::white;
        else if (inner_order->is_canceled())
        {
            return Qt::gray;
        }
        else if (inner_order->is_full_executed())
            return qtmisc::mtk_color_executed;
        //else if(inner_order->last_confirmation().HasValue()==false)
        else if(inner_order->has_pending_rq())
            return qtmisc::mtk_color_pending;
        else
            return Qt::white;
    }

    void update_item_session_id(void)
    {
        QTableWidgetItem* item = items[col_session_id];
        item->setText(QLatin1String(qtmisc::get_order_invariant(*inner_order).order_id.session_id.c_str()));
        item->setBackgroundColor(get_default_color());
    }

    void update_item_req_code()
    {
        QTableWidgetItem* item = items[col_req_code];
        item->setText(QLatin1String(qtmisc::get_order_invariant(*inner_order).order_id.req_code.c_str()));
        item->setBackgroundColor(get_default_color());
    }

    void update_item_market(void)
    {
        QTableWidgetItem* item = items[col_market];
        if (inner_order->last_confirmation().HasValue())
            item->setText(QLatin1String(inner_order->last_confirmation().Get().invariant.product_code.market.c_str()));
        else if (inner_order->last_request().HasValue())
            item->setText(QLatin1String(inner_order->last_request().Get().invariant.product_code.market.c_str()));
        else
            throw mtk::Alarm(MTK_HERE, "qorderbook", "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
        item->setBackgroundColor(get_default_color());
    }

    void update_item_product(void)
    {
        QTableWidgetItem* item = items[col_product];
        if (inner_order->last_confirmation().HasValue())
            item->setText(QLatin1String(inner_order->last_confirmation().Get().invariant.product_code.product.c_str()));
        else if (inner_order->last_request().HasValue())
            item->setText(QLatin1String(inner_order->last_request().Get().invariant.product_code.product.c_str()));
        else
            throw mtk::Alarm(MTK_HERE, "qorderbook", "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
        item->setBackgroundColor(get_default_color());
    }


    void update_item_price(void)
    {
        QTableWidgetItem* item = items[col_price];
        item->setText(qtmisc::nullable_fn_as_QString(qtmisc::get_order_position_price(*inner_order)));
        item->setBackgroundColor(get_default_color());
    }

    void update_item_quantity(void)
    {
        QTableWidgetItem* item = items[col_quantity];
        item->setText(qtmisc::fn_as_QString(qtmisc::get_order_position_quantity(*inner_order)));
        item->setBackgroundColor(get_default_color());
    }

    void update_item_side(void)
    {
        QTableWidgetItem* item = items[col_side];
        mtk::trd::msg::enBuySell side = qtmisc::get_order_invariant(*inner_order).side;
        item->setText(qtmisc::side_as_text(side));
        if (side == mtk::trd::msg::buy)
            item->setBackgroundColor(qtmisc::mtk_color_buy_cell);
        else if (side == mtk::trd::msg::sell)
            item->setBackgroundColor(qtmisc::mtk_color_sell_cell);
       else
           item->setBackgroundColor(qtmisc::mtk_color_problem);
        item->setTextAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    }

    void update_item_exec_quantity (void)
    {
        mtk::nullable<mtk::FixedNumber> confirmed;

        QTableWidgetItem* item = items[col_exec_quantity];
        if (inner_order->last_confirmation().HasValue())
        {
            confirmed = inner_order->last_confirmation().Get().total_execs.acc_quantity;
            item->setText(qtmisc::fn_as_QString(confirmed.Get()));
        }
        if (confirmed.HasValue()  &&  confirmed.Get().GetIntCode() != 0)
        {
            item->setBackgroundColor(qtmisc::mtk_color_executed);
        }
        else
        {
            item->setText(QLatin1String(""));
            item->setBackgroundColor(get_default_color());
        }
    }
    void update_item_exec_price (void)
    {
        mtk::Double confirmed(mtk::Double::InvalidValue());

        QTableWidgetItem* item = items[col_exec_price];
        if (inner_order->last_confirmation().HasValue())
        {
            confirmed = inner_order->last_confirmation().Get().total_execs.sum_price_by_qty
                            /
                            inner_order->last_confirmation().Get().total_execs.acc_quantity.GetDouble();
            item->setText(QString::number(confirmed.get()._0, 'f', 5));
        }
        if (confirmed.IsValid())
        {
            item->setBackgroundColor(qtmisc::mtk_color_executed);
        }
        else
        {
            item->setText(QLatin1String(""));
            item->setBackgroundColor(get_default_color());
        }
    }

    void update_item_exec_observations   (void)
    {
        QTableWidgetItem* item = items[col_remarks];
        item->setBackgroundColor(get_default_color());
        QString ref_cli;
        QString remarks;
        if(inner_order->has_pending_rq())
            ref_cli = QLatin1String(inner_order->last_request().Get().cli_ref.c_str());
        else
            ref_cli = QLatin1String(inner_order->last_confirmation().Get().cli_ref.c_str());
        if(ref_cli.size() != 0)
            remarks = ref_cli;
        remarks += QLatin1String(inner_order->serrors().c_str());
        item->setText(remarks);
    }
    void update_item_cli_code            ()
    {
        QTableWidgetItem* item = items[col_cli_code];
        item->setBackgroundColor(get_default_color());
        if (inner_order->last_confirmation().HasValue())
            item->setText(QLatin1String(inner_order->last_confirmation().Get().invariant.account.client_code.c_str()));
        else if (inner_order->last_request().HasValue())
            item->setText(QLatin1String(inner_order->last_request().Get().invariant.account.client_code.c_str()));
        else
            throw mtk::Alarm(MTK_HERE, "qorderbook", "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);

    }
    void update_item_account             ()
    {
        QTableWidgetItem* item = items[col_account];
        item->setBackgroundColor(get_default_color());
        if (inner_order->last_confirmation().HasValue())
            item->setText(QLatin1String(inner_order->last_confirmation().Get().invariant.account.name.c_str()));
        else if (inner_order->last_request().HasValue())
            item->setText(QLatin1String(inner_order->last_request().Get().invariant.account.name.c_str()));
        else
            throw mtk::Alarm(MTK_HERE, "qorderbook", "ERROR last request and last confirmation null", mtk::alPriorCritic, mtk::alTypeNoPermisions);
    }
    void update_item_rem_quantity        ()
    {
        QTableWidgetItem* item = items[col_rem_quantity];
        if (inner_order->last_confirmation().HasValue())
            item->setText(qtmisc::fn_as_QString(inner_order->last_confirmation().Get().total_execs.remaining_qty));
        else
            item->setText(QLatin1String(""));

        item->setBackgroundColor(get_default_color());
    }
    void update_item_order_type        ()
    {
        QTableWidgetItem* item = items[col_order_type];
        item->setBackgroundColor(get_default_color());
        if(dynamic_cast<mtk::trd::trd_cli_ls*>(inner_order.get2()) != 0)
            item->setText(QObject::tr("limit"));
        else if(dynamic_cast<mtk::trd::trd_cli_mk*>(inner_order.get2()) != 0)
            item->setText(QObject::tr("market"));
        else
        {
            item->setText(QLatin1String("???"));
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qorderbook", "unknown order type", mtk::alPriorCritic, mtk::alTypeNoPermisions));
        }
    }

};



template<typename  ORDER_TYPE>
class order_in_qbook_XX;


//      mtk::trd::trd_cli_ls
template<>
class order_in_qbook_XX<mtk::trd::trd_cli_ls>  :
                                            public  order_in_qbook_xx<mtk::trd::trd_cli_ls>,
                                            public mtk::SignalReceptor
{
    typedef order_in_qbook_XX  CLASS_NAME;
public:
    order_in_qbook_XX(QTableWidget *table_widget, const mtk::CountPtr<mtk::trd::trd_cli_ls>& order)
        : order_in_qbook_xx<mtk::trd::trd_cli_ls>(table_widget, order)
    {
        MTK_CONNECT_THIS(order_in_qbook_xx<mtk::trd::trd_cli_ls>::inner_order->sig_changed, update_on_change);
        MTK_CONNECT_THIS(order_in_qbook_xx<mtk::trd::trd_cli_ls>::inner_order->sig_cf_ex,   update_on_cf);
        order_in_qbook::update();
    }
    ~order_in_qbook_XX() {
    }


    void update_on_change(void)  {    order_in_qbook::update();   }

    //  on execution on order it will signal it
    void update_on_cf(const mtk::trd::msg::CF_EX_LS& cfex)
    {
        order_in_qbook::update();       //      called previusly from  update_on_change
        order_in_qbook::signal_executed_order.emit(cfex.invariant.order_id);        //  to move down on table
    }
};




//      mtk::trd::trd_cli_mk
template<>
class order_in_qbook_XX<mtk::trd::trd_cli_mk>  :
                                    public  order_in_qbook_xx<mtk::trd::trd_cli_mk>,
                                    public mtk::SignalReceptor
{
    typedef order_in_qbook_XX  CLASS_NAME;
public:
    order_in_qbook_XX(QTableWidget *table_widget, const mtk::CountPtr<mtk::trd::trd_cli_mk>& order)
        : order_in_qbook_xx<mtk::trd::trd_cli_mk>(table_widget, order)
    {
        MTK_CONNECT_THIS(order_in_qbook_xx<mtk::trd::trd_cli_mk>::inner_order->sig_changed, update_on_change);
        MTK_CONNECT_THIS(order_in_qbook_xx<mtk::trd::trd_cli_mk>::inner_order->sig_cf_ex,   update_on_cf);
        order_in_qbook::update();
    }
    ~order_in_qbook_XX() {
    }


    void update_on_change(void)  {    order_in_qbook::update();   }

    //  on execution on order it will signal it
    void update_on_cf(const mtk::trd::msg::CF_EX_MK& cfex)
    {
        order_in_qbook::update();       //      called previusly from  update_on_change
        order_in_qbook::signal_executed_order.emit(cfex.invariant.order_id);        //  to move down on table
    }
};



//----------------------------------------------------------------------------------------------------
//  class order_in_qbook
//----------------------------------------------------------------------------------------------------



qorder_table::qorder_table(QWidget *parent) :
        QWidget(parent),
        table_widget(new QTableWidget(this)),
        orders(new mtk::map<mtk::trd::msg::sub_order_id, mtk::CountPtr<order_in_qbook> >),
        current_order_id( mtk::msg::sub_request_id("", "")),
        filterf (new filter_form(this)),
        delegate_paint(new QCommonTableDelegate(table_widget))
{
    table_widget->installEventFilter(this);

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
        static  const char* const col_captions[] = {     "sess_id",
                                                         QT_TR_NOOP("req_code"),
                                                         QT_TR_NOOP("cli_code"),
                                                         QT_TR_NOOP("account"),
                                                         QT_TR_NOOP("o.type"),
                                                         QT_TR_NOOP("market"),
                                                         QT_TR_NOOP("product"),
                                                         QT_TR_NOOP("side"),
                                                         QT_TR_NOOP("qty"),
                                                         QT_TR_NOOP("price"),
                                                         QT_TR_NOOP("exec qty"),
                                                         QT_TR_NOOP("rem qty"),
                                                         QT_TR_NOOP("exec price"),
                                                         QT_TR_NOOP("remarks"),
                                                         0                 };


        int counter;
        for (counter=0; col_captions[counter]!=0; ++counter)
            headers_captions.append(tr(col_captions[counter]));
        table_widget->setColumnCount(counter);
    }
    table_widget->setHorizontalHeaderLabels(headers_captions);

    table_widget->verticalHeader()->setVisible(false);
    //table_widget->verticalHeader()->setDefaultSectionSize(QFontMetrics(this->font()).height()*1.4);  moved on_new_order
    //table_widget->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    table_widget->setColumnWidth(col_session_id, 20);
    table_widget->setColumnWidth(col_req_code, 20);
    table_widget->setColumnWidth(col_remarks, 400);
    table_widget->horizontalHeader()->setStretchLastSection(true);

    delegate_paint->set_horiz_line_each(1);
    table_widget->setItemDelegate(delegate_paint);
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
    MTK_CONNECT_THIS(mtk::trd::trd_cli_ord_book::get_sig_order_mk_new(), on_new_order);
    MTK_TIMER_1C(timer_get_orders2add);

    //slot_apply_filter(filter_data());
    //setContentsMargins(0,0,0,0);
    connect(table_widget, SIGNAL(doubleClicked(QModelIndex)), SLOT(slot_on_double_clicked(QModelIndex)));
    connect(table_widget, SIGNAL(currentCellChanged(int,int,int,int)), this, SLOT(slot_current_cell_changed(int,int,int,int)));
    connect(this->table_widget->horizontalHeader(), SIGNAL(sectionResized(int,int,int)), this, SIGNAL(signal_sectionResized(int,int,int)));
}

qorder_table::~qorder_table()
{
    delete orders;
}


void qorder_table::__direct_add_new_order(const mtk::trd::msg::sub_order_id& order_id, mtk::CountPtr<order_in_qbook>& order)
{
    //  if the order was previusly registered, delete the row and the order info
    mtk::map<mtk::trd::msg::sub_order_id, mtk::CountPtr<order_in_qbook> >::iterator  it = orders->find(order_id);
    if(it != orders->end())
    {
        //  delete the row
        this->table_widget->removeRow(it->second->get_row());
        //  remove from map
        orders->erase(order_id);
    }


    //  register the order
    MTK_CONNECT_THIS(order->signal_executed_order, try_realocate_order);
    orders->insert(std::make_pair(order_id, order));

    if(current_order_id == order_id)
        this->table_widget->setCurrentCell(this->table_widget->rowCount()-1, 0);
}

void qorder_table::on_new_order(const mtk::trd::msg::sub_order_id& order_id, mtk::CountPtr<mtk::trd::trd_cli_ls_dangerous_signals_not_warped>& /*order*/)
{
    orders2add_online.push_back(order_id);
    add_new_order_orders_in_sequence(order_id);

}

void qorder_table::on_new_order(const mtk::trd::msg::sub_order_id& order_id, mtk::CountPtr<mtk::trd::trd_cli_mk_dangerous_signals_not_warped>& /*order*/)
{
    orders2add_online.push_back(order_id);
    add_new_order_orders_in_sequence(order_id);

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


void  qorder_table::try_realocate_order(const mtk::trd::msg::sub_order_id& order_id)
{
    if(this->table_widget->currentRow() != -1)
        current_order_id = get_order_id_from_row(this->table_widget, this->table_widget->currentRow());


    //  if order is on bottom, do nothing
    mtk::map<mtk::trd::msg::sub_order_id, mtk::CountPtr<order_in_qbook> >::iterator  it = orders->find(order_id);
    if(it == orders->end())
        throw mtk::Alarm(MTK_HERE, "qorder_table_exec", "received execution on inexistent order", mtk::alPriorCritic, mtk::alTypeNoPermisions);

    int row = it->second->get_row();
    if(row == this->table_widget->rowCount()-1)
        return;

    //  the row and the previus order will be deleted on inserting on __direct_add_new_order


    realocate_orders_in_sequence(order_id);


    //  program the order to add on this table
    orders2add_online.push_back(order_id);

}







void qorder_table::request_modif(void)
{
    delegate_paint->keep_focus_paint(true);
    try
    {
        int row = table_widget->currentRow();
        if (row==-1)        return;
        const mtk::trd::msg::sub_order_id   ord_id(get_order_id_from_row(table_widget, row));
        if(mtk::trd::trd_cli_ord_book::get_order_type(ord_id) ==  mtk::trd::trd_cli_ord_book::ot_limit)
            mtk::trd::trd_cli_ord_book::rq_md_ls_manual(ord_id);
        else if(mtk::trd::trd_cli_ord_book::get_order_type(ord_id) ==  mtk::trd::trd_cli_ord_book::ot_market)
            mtk::trd::trd_cli_ord_book::rq_md_mk_manual(ord_id);
        else throw mtk::Alarm(MTK_HERE, "qorderbook", MTK_SS("unknown order type " << ord_id << "  type:"  << mtk::trd::trd_cli_ord_book::get_order_type(ord_id)), mtk::alPriorCritic, mtk::alTypeNoPermisions);

    }
    catch(...)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qordertable", "controling focus paint on error managing request", mtk::alPriorError));
        delegate_paint->keep_focus_paint(false);
        throw;
    }
    delegate_paint->keep_focus_paint(false);
}

void qorder_table::request_cancel(void)
{
    delegate_paint->keep_focus_paint(true);
    try
    {
        int row = table_widget->currentRow();
        if (row==-1)        return;

        //  ask for cancelation
        if(QMessageBox::warning(this, QLatin1String("CimdTrade"), tr("Do you want to cancel the order?"), QMessageBox::Ok, QMessageBox::Cancel)==QMessageBox::Ok)
        {
            const mtk::trd::msg::sub_order_id   ord_id(get_order_id_from_row(table_widget, row));
            if(mtk::trd::trd_cli_ord_book::get_order_type(ord_id) ==  mtk::trd::trd_cli_ord_book::ot_limit)
                mtk::trd::trd_cli_ord_book::rq_cc_ls(ord_id);
            else if(mtk::trd::trd_cli_ord_book::get_order_type(ord_id) ==  mtk::trd::trd_cli_ord_book::ot_market)
                mtk::trd::trd_cli_ord_book::rq_cc_mk(ord_id);
            else throw mtk::Alarm(MTK_HERE, "qorderbook", MTK_SS("unknown order type " << ord_id << "  type:"  << mtk::trd::trd_cli_ord_book::get_order_type(ord_id)), mtk::alPriorCritic, mtk::alTypeNoPermisions);

        }
    }
    catch(...)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qordertable", "controling focus paint on error managing request", mtk::alPriorError));
        delegate_paint->keep_focus_paint(false);
        throw;
    }
    delegate_paint->keep_focus_paint(false);
}


bool multicheck_string (const std::string& value, const std::string& multifilter)
{
    if(multifilter == "")       return true;

    static std::string prev_multifilter;
    static mtk::vector<std::string>  vector_multifilter;
    if(prev_multifilter == ""  ||  prev_multifilter != multifilter)
        vector_multifilter = mtk::s_split(mtk::s_toUpper(mtk::s_trim(multifilter, ' ')), " ");
    prev_multifilter = multifilter;

    for(unsigned i=0; i<vector_multifilter.size(); ++i)
    {
        if(vector_multifilter[i] != "")
            if(mtk::s_toUpper(value).find(vector_multifilter[i])!=std::string::npos)
                return true;
    }
    return false;
}

bool check_filter_order(const filter_data     fd, const mtk::trd::msg::sub_order_id& order_id, bool check_no_tab_filter_config)
{
    //  check_no_tab_filter_config means just alives, alives executed, all
    //  on new orders received on line, this filter has to be ignored
    //  this subfilter has to be applied only on user request
    //  at this moment, orders2add_loading is filled with current orders when user make a request
    //  and orders2add_online is filled with new orders or execution on an order
    //  timer_get_orders2add  is calling this function


    mtk::msg::sub_product_code pc = get_product_code(order_id);
    int matches = 0;
    //if(mtk::s_toUpper(pc.product).find(fd.product.toUpper().toStdString())!=std::string::npos)
    if(multicheck_string(mtk::s_toUpper(pc.product), fd.product.toUpper().toStdString()))
        ++matches;
    //if(mtk::s_toUpper(pc.market).find(fd.market.toUpper().toStdString())!=std::string::npos)
    if(multicheck_string(mtk::s_toUpper(pc.market), fd.market.toUpper().toStdString()))
        ++matches;

    mtk::trd::msg::sub_account_info account = get_account(order_id);
    //if(mtk::s_toUpper(account.client_code).find(fd.client_code.toUpper().toStdString())!=std::string::npos)
    if(multicheck_string(mtk::s_toUpper(account.client_code), fd.client_code.toUpper().toStdString()))
        ++matches;
    //if(mtk::s_toUpper(account.name).find(fd.account.toUpper().toStdString())!=std::string::npos)
    if(multicheck_string(mtk::s_toUpper(account.name), fd.account.toUpper().toStdString()))
        ++matches;

    if(check_no_tab_filter_config)
    {
        if(fd.liveFilter == filter_data::lfAll)
            ++matches;
        else if(fd.liveFilter == filter_data::lfLive  &&   (is_canceled(order_id)== false  &&  is_full_executed(order_id)==false))
            ++matches;
        else if(fd.liveFilter == filter_data::lfLiveExecuted  &&
                        ( (is_canceled(order_id)== false  &&  is_full_executed(order_id)==false)       //  alive
                          ||
                          (get_total_exec_quantity(order_id).GetIntCode() > 0)
                          ))
            ++matches;

        if(matches==5)  return true;
        else            return false;
    }
    else
    {
        if(matches==4)  return true;
        else            return false;
    }
}

void qorder_table::slot_apply_filter(const filter_data& fd)
{
    //if(fd.name == current_filter.name  &&  fd.client_code  ==  current_filter.client_code
    //                        &&  fd.market  ==  current_filter.market  &&  fd.product == current_filter.product)
    //    return;

    orders2add_loading.clear();

    Q_EMIT(signal_named_changed(fd.name));
    table_widget->setRowCount(0);
    orders->clear();

    mtk::list<mtk::trd::msg::sub_order_id>& all_orders = __do_not_use_it_directly_orders_in_sequence;

    for(mtk::list<mtk::trd::msg::sub_order_id>::const_iterator it= all_orders.begin(); it!=all_orders.end(); ++it)
            orders2add_loading.push_back(*it);
    current_filter = fd;
    Q_EMIT(signal_filter_changed());
}

void   qorder_table::timer_get_orders2add(void)
{
    int counter=0;
    while(orders2add_loading.size()>0)
    {
        mtk::trd::msg::sub_order_id order_id = orders2add_loading.front();
        orders2add_loading.pop_front();
        if(check_filter_order(current_filter, order_id, true))
        {
            mtk::CountPtr<order_in_qbook>  new_order;
            mtk::trd::trd_cli_ord_book::en_order_type  order_type = mtk::trd::trd_cli_ord_book::get_order_type(order_id);
            if(order_type ==  mtk::trd::trd_cli_ord_book::ot_limit)
            {
                mtk::CountPtr<mtk::trd::trd_cli_ls> order=mtk::trd::trd_cli_ord_book::get_order_ls(order_id);
                new_order = mtk::CountPtr<order_in_qbook>(new order_in_qbook_XX<mtk::trd::trd_cli_ls>(table_widget, order));
            }
            else if(order_type ==  mtk::trd::trd_cli_ord_book::ot_market)
            {
                mtk::CountPtr<mtk::trd::trd_cli_mk> order=mtk::trd::trd_cli_ord_book::get_order_mk(order_id);
                new_order = mtk::CountPtr<order_in_qbook>(new order_in_qbook_XX<mtk::trd::trd_cli_mk>(table_widget, order));
            }
            __direct_add_new_order(order_id, new_order);
            ++counter;
            if(counter%5==0)
                return;
        }
    }
    while(orders2add_online.size()>0)
    {
        mtk::trd::msg::sub_order_id order_id = orders2add_online.front();
        orders2add_online.pop_front();
        if(check_filter_order(current_filter, order_id, false))
        {
            mtk::CountPtr<order_in_qbook>  new_order;
            mtk::trd::trd_cli_ord_book::en_order_type  order_type = mtk::trd::trd_cli_ord_book::get_order_type(order_id);
            if(order_type ==  mtk::trd::trd_cli_ord_book::ot_limit)
            {
                mtk::CountPtr<mtk::trd::trd_cli_ls> order=mtk::trd::trd_cli_ord_book::get_order_ls(order_id);
                new_order = mtk::CountPtr<order_in_qbook>(new order_in_qbook_XX<mtk::trd::trd_cli_ls>(table_widget, order));
            }
            else if(order_type ==  mtk::trd::trd_cli_ord_book::ot_market)
            {
                mtk::CountPtr<mtk::trd::trd_cli_mk> order=mtk::trd::trd_cli_ord_book::get_order_mk(order_id);
                new_order = mtk::CountPtr<order_in_qbook>(new order_in_qbook_XX<mtk::trd::trd_cli_mk>(table_widget, order));
            }
            __direct_add_new_order(order_id, new_order);
            ++counter;
            if(counter%5==0)
                return;
        }
    }
}

void qorder_table::update_sizes()
{
    table_widget->verticalHeader()->setDefaultSectionSize(QFontMetrics(this->font()).height()*1.2);
}

void qorder_table::show_filter(bool show)
{
    if(show)
    {
        filterf->set_filter_conf(current_filter);
        filterf->show();
    }
    else
    {
        filterf->hide();
    }
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

        if(is_canceled(ord_id)  ||  is_full_executed(ord_id))
        {
            enabled_cancel = false;
            enabled_modif = false;
        }
        else
        {
            std::string grant = mtk::accmgrcli::get_grant(get_product_code(ord_id).market, get_account(ord_id));
            if(grant == "F")
            {
                enabled_cancel = true;
                enabled_modif = true;
            }
            else if(grant == "C")
            {
                enabled_cancel = true;
                enabled_modif = false;
            }
            else
            {
                enabled_cancel = false;
                enabled_modif = false;
            }
        }
    }
    QMenu  menu;
    {
        QAction* action = new QAction(tr("cancel"), &menu);
        connect(action, SIGNAL(triggered()), this, SLOT(request_cancel()));
        action->setEnabled(enabled_cancel);
        action->setShortcut(Qt::Key_Delete);
        menu.addAction(action);
    }
    {
        QAction* action = new QAction(tr("modif"), &menu);
        connect(action, SIGNAL(triggered()), this, SLOT(request_modif()));
        action->setEnabled(enabled_modif);
        action->setShortcut(Qt::Key_Enter  |  Qt::Key_Return);
        menu.addAction(action);
    }
    {
        QAction* action = new QAction(&menu);
        action->setSeparator(true);
        menu.addAction(action);
    }
    {
        QAction* action = new QAction(tr("live orders"), &menu);
        connect(action, SIGNAL(triggered()), this, SLOT(slot_live_orders()));
        action->setEnabled(true);
        action->setCheckable(true);
        if(current_filter.liveFilter == filter_data::lfLive)
            action->setChecked(true);
        else
            action->setChecked(false);
        menu.addAction(action);
    }
    {
        QAction* action = new QAction(tr("live and exec orders"), &menu);
        connect(action, SIGNAL(triggered()), this, SLOT(slot_live_and_exec_orders()));
        action->setEnabled(true);
        action->setCheckable(true);
        if(current_filter.liveFilter == filter_data::lfLiveExecuted)
            action->setChecked(true);
        else
            action->setChecked(false);
        menu.addAction(action);
    }
    {
        QAction* action = new QAction(tr("all orders"), &menu);
        connect(action, SIGNAL(triggered()), this, SLOT(slot_all_orders()));
        action->setEnabled(true);
        action->setCheckable(true);
        if(current_filter.liveFilter == filter_data::lfAll)
            action->setChecked(true);
        else
            action->setChecked(false);
        menu.addAction(action);
    }
    menu.addSeparator();
    {
        QAction* action = new QAction(tr("show historic"), &menu);
        connect(action, SIGNAL(triggered()), this, SIGNAL(signal_request_show_historic()));
        action->setShortcut(Qt::Key_Space);
        menu.addAction(action);
        if(get_current_order_id().HasValue())
            action->setEnabled(true);
        else
            action->setEnabled(false);
    }
    menu.exec(this->mapToGlobal(e->pos()));
}


void qorder_table::slot_live_orders(void)
{
    current_filter.liveFilter = filter_data::lfLive;
    slot_apply_filter(current_filter);
}

void qorder_table::slot_live_and_exec_orders(void)
{
    current_filter.liveFilter = filter_data::lfLiveExecuted;
    slot_apply_filter(current_filter);
}

void qorder_table::slot_all_orders(void)
{
    current_filter.liveFilter = filter_data::lfAll;
    slot_apply_filter(current_filter);
}


bool qorder_table::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type()  ==  QEvent::KeyPress)
    {
        QKeyEvent *key_event = static_cast<QKeyEvent*>(event);
        if(key_event->key() == Qt::Key_Space)
            signal_request_show_historic();
    }
    return QObject::eventFilter(obj, event);
}


void qorder_table::keyPressEvent(QKeyEvent *e)
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


        if(is_canceled(ord_id)  ||  is_full_executed(ord_id))
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

    if(enabled_modif  &&  (e->key() == Qt::Key_Enter  ||  e->key() == Qt::Key_Return))
        request_modif();
    else if(enabled_cancel  &&  e->key() == Qt::Key_Delete)
        request_cancel();
    else if(e->key() == Qt::Key_Escape)
        signal_request_hide_historic();
}


YAML::Emitter& operator << (YAML::Emitter& out, const qorder_table& qot)
{
    out << YAML::BeginMap;
    out << YAML::Key  << "order_table"  << YAML::Value;



        out << YAML::BeginMap;
            out << YAML::Key  << "filter"  << YAML::Value;
                out << YAML::BeginMap;
                    out << YAML::Key  << "account" << YAML::Value << qot.current_filter.account.toStdString();
                    out << YAML::Key  << "client_code" << YAML::Value << qot.current_filter.client_code.toStdString();
                    out << YAML::Key  << "market" << YAML::Value << qot.current_filter.market.toStdString();
                    out << YAML::Key  << "name" << YAML::Value << qot.current_filter.name.toStdString();
        out << YAML::EndMap;

        out << YAML::Key  << "column_sizes"  << YAML::Value;
            out << YAML::Flow << YAML::BeginSeq;
                for(int i=0; i < qot.table_widget->horizontalHeader()->count(); ++i)
                {
                    out << qot.table_widget->horizontalHeader()->sectionSize(i);
                }
            out << YAML::EndSeq;

        out << YAML::EndMap;


    out << YAML::EndMap;        //  qorder table
    return out;
}

void     operator>> (const YAML::Node & node   , qorder_table& qot)
{
    {   //  column sizes
        for(int i =0; unsigned(i)< node["order_table"]["column_sizes"].size()   &&   i+1 < qot.table_widget->horizontalHeader()->count(); ++i)
        {
            int size=1;
            node["order_table"]["column_sizes"][i] >> size;
            qot.table_widget->horizontalHeader()->resizeSection(i, size);
        }
    }

    {       //  filter
        std::string  account;
        std::string  client_code;
        std::string  market;
        std::string  name;


        node["order_table"]["filter"]["account"] >> account;
        node["order_table"]["filter"]["client_code"] >> client_code;
        node["order_table"]["filter"]["market"] >> market;
        node["order_table"]["filter"]["name"] >> name;


        if(account=="~")        account = "";
        if(client_code=="~")    client_code = "";
        if(market=="~")         market = "";
        if(name=="~")           name = "";


        qot.current_filter.account =  QLatin1String(account.c_str());
        qot.current_filter.client_code =  QLatin1String(client_code.c_str());
        qot.current_filter.market =  QLatin1String(market.c_str());
        qot.current_filter.name =  QLatin1String(name.c_str());

        Q_EMIT(qot.signal_named_changed(QLatin1String(name.c_str())));
        Q_EMIT(qot.signal_filter_changed());
    }
}

void qorder_table::slot_on_double_clicked(QModelIndex mode)
{
    Q_EMIT(signal_double_click(mode));
}

void qorder_table::slot_current_cell_changed(int a, int b, int c, int d)
{
    Q_EMIT(signal_cell_changed(a,b,c,d));
}

mtk::nullable<mtk::trd::msg::sub_order_id>   qorder_table::get_current_order_id(void)
{
    if(table_widget->currentRow() != -1)
        return mtk::make_nullable(get_order_id_from_row(table_widget, table_widget->currentRow()));
    else
        return  mtk::nullable<mtk::trd::msg::sub_order_id>();
}

void qorder_table::resize_header_section(int index, int /*old_size*/, int new_size)
{
    if(index != table_widget->horizontalHeader()->count()-1  &&    table_widget->horizontalHeader()->sectionSize(index) !=  new_size)
        table_widget->horizontalHeader()->resizeSection(index, new_size);
}

void qorder_table::resize_header_sections(const qorder_table& ot)
{
    for(int i=0; i<this->table_widget->horizontalHeader()->count(); ++i)
    {
        table_widget->horizontalHeader()->resizeSection(i, ot.table_widget->horizontalHeader()->sectionSize(i));
    }
}
