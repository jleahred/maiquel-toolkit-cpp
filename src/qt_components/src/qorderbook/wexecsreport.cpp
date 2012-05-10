#include "wexecsreport.h"
#include "ui_wexecsreport.h"

#include "qmtk_misc.h"
#include "components/trading/trd_cli_ord_book.h"
#include "components/prices/cli/price_manager.h"

#include "ecimd_config.h"



/*      testing
mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>
        __testing_generate_exec_conf(const std::string& _market, const std::string& _product_code, const std::string _account, mtk::trd::msg::enBuySell _buy_sell, double price, int quantity)
{
    mtk::trd::msg::sub_order_id                 order_id    (mtk::msg::sub_request_id("", ""));
    mtk::msg::sub_product_code                  product_code(_market, _product_code);
    mtk::trd::msg::enBuySell                    buy_sell    (_buy_sell);
    mtk::trd::msg::sub_account_info             account_info(_account, "client_code");
    mtk::trd::msg::sub_invariant_order_info     invariant   (order_id, product_code, buy_sell, account_info, "DAY", false);
    mtk::msg::sub_request_id                    request_id  ("session_id", "request_code");
    mtk::trd::msg::sub_total_executions         total_executions = mtk::trd::msg::__internal_get_default((mtk::trd::msg::sub_total_executions*)0);
    mtk::trd::msg::CF_XX                        cfxx        (invariant, "market_order_id", request_id, total_executions, "description", mtk::admin::get_control_fluct_info());

    mtk::trd::msg::sub_exec_conf                exec_conf   ("exec_id", mtk::FixedNumber(mtk::fnDouble(price), mtk::fnDec(2), mtk::fnInc(1)), mtk::FixedNumber(mtk::fnIntCode(quantity), mtk::fnDec(0), mtk::fnInc(1)));

    return  mtk::make_tuple(cfxx, exec_conf);
}
*/

WExecsReport::WExecsReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WExecsReport)
{
    ui->setupUi(this);
    ui->treeWidget->header()->resizeSection(0, 200);

    if(ecimd_config::loss_win() == false)
    {
        ui->treeWidget->header()->setSectionHidden(6, true);
        ui->treeWidget->header()->setSectionHidden(7, true);
    }

    /*      testing
    {
        mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>  exec =
                __testing_generate_exec_conf("MARKET", "FGBLZZ", "JOSE", mtk::trd::msg::buy, 102.3, 7);
        on_new_execution(exec._0, exec._1);
    }
    {
        mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>  exec =
                __testing_generate_exec_conf("MARKET", "FGBLZA", "JOSE", mtk::trd::msg::buy, 102.0, 1);
        on_new_execution(exec._0, exec._1);
    }
    {
        mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>  exec =
                __testing_generate_exec_conf("MARKET", "FGBLZZ", "JOSE", mtk::trd::msg::buy, 102.0, 1);
        on_new_execution(exec._0, exec._1);
    }
    {
        mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>  exec =
                __testing_generate_exec_conf("MARKET", "FGBLZZ", "JOSE", mtk::trd::msg::sell, 102.0, 1);
        on_new_execution(exec._0, exec._1);
    }
    {
        mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>  exec =
                __testing_generate_exec_conf("MARKET", "FGBLZZ", "JOSE", mtk::trd::msg::sell, 102.0, 1);
        on_new_execution(exec._0, exec._1);
    }
    {
        mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>  exec =
                __testing_generate_exec_conf("MARKET", "FGBLZZ", "JOSE2", mtk::trd::msg::sell, 102.0, 1);
        on_new_execution(exec._0, exec._1);
    }
    */
    mtk::list<mtk::trd::msg::CF_EXLK>  list_all_execs = mtk::trd::trd_cli_ord_book::get_all_execs();
    for(auto it=list_all_execs.begin(); it!=list_all_execs.end(); ++it)
    {
        on_new_execution(*it, it->executed_pos);
    }

    MTK_CONNECT_THIS(mtk::trd::trd_cli_ord_book::get_sig_execution_RT(),        on_new_execution);
    MTK_CONNECT_THIS(mtk::trd::trd_cli_ord_book::get_sig_execution_NON_RT(),    on_new_execution);
}

WExecsReport::~WExecsReport()
{
    delete ui;
}


namespace {
mtk::FixedNumber  add_fixed_numbers(const mtk::FixedNumber& val1, const mtk::FixedNumber& val2)
{
    mtk::FixedNumber  result = val2;
    result.SetDouble(val2.GetDouble() + val1.GetDouble());
    return result;
}

mtk::FixedNumber  subs_fixed_numbers(const mtk::FixedNumber& val1, const mtk::FixedNumber& val2)
{
    mtk::FixedNumber  result = val2;
    result.SetDouble(val1.GetDouble() - val2.GetDouble());
    return result;
}


class QTreeWidgetItem_exec : public  QTreeWidgetItem
{
protected:
    mtk::FixedNumber    buy_quantity;
    mtk::FixedNumber    sell_quantity;
    mtk::Double         buy_price_by_quantity;
    mtk::Double         sell_price_by_quantity;

public:
    virtual void add_exec(mtk::trd::msg::enBuySell buy_sell, const mtk::FixedNumber& _price, const mtk::FixedNumber& _quantity)
    {
        mtk::FixedNumber*       quantity;
        mtk::Double     *       price_by_quantity;
        int                     index_price;
        int                     index_quantity;

        if(buy_sell == mtk::trd::msg::buy)
        {
            quantity            = &buy_quantity;
            price_by_quantity   = &buy_price_by_quantity;
            index_price         = 2;
            index_quantity      = 1;
        }
        else
        {
            quantity            = &sell_quantity;
            price_by_quantity   = &sell_price_by_quantity;
            index_price         = 3;
            index_quantity      = 4;
        }
        *quantity = add_fixed_numbers(*quantity, _quantity);
        *price_by_quantity = *price_by_quantity + (_price.GetDouble() * _quantity.GetDouble());

        this->setText(index_quantity, qtmisc::fn_as_QString(*quantity));
        this->setText(index_price,    QLocale::system().toString((*price_by_quantity / quantity->GetDouble()).get2(), 'f', 4));
    }


    QTreeWidgetItem_exec( QTreeWidgetItem * parent, mtk::trd::msg::enBuySell buy_sell, const mtk::FixedNumber& _price, const mtk::FixedNumber& _quantity)
        :   QTreeWidgetItem(parent),
            buy_quantity(_quantity),                            sell_quantity(_quantity),
            buy_price_by_quantity(0.), sell_price_by_quantity(0.)
    {
        buy_quantity.SetIntCode(0);
        sell_quantity.SetIntCode(0);

        this->setTextAlignment(1, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setTextAlignment(2, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setTextAlignment(3, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setTextAlignment(4, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setTextAlignment(5, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setTextAlignment(6, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);

        QFont  font = this->font(0);
        font.setBold(false);
        this->setFont(1, font);
        this->setFont(2, font);
        this->setFont(3, font);
        this->setFont(4, font);
        this->setFont(5, font);
        this->setFont(6, font);

        QBrush  bbuy(qtmisc::mtk_color_buy_cell);
        bbuy.setStyle(Qt::SolidPattern);
        QBrush  bsell(qtmisc::mtk_color_sell_cell);
        bsell.setStyle(Qt::SolidPattern);
        this->setBackground(1, bbuy);
        this->setBackground(2, bbuy);
        this->setBackground(3, bsell);
        this->setBackground(4, bsell);


        add_exec(buy_sell, _price, _quantity);
    }
    virtual ~QTreeWidgetItem_exec(){}

};


mtk::nullable<mtk::Double>   calculate_win_loss(        const mtk::nullable<mtk::Double>&   unit_cost,
                                                        mtk::nullable<mtk::FixedNumber>     last_price,
                                                        const mtk::Double&                  sum_prec_by_quantity_buy,
                                                        const mtk::Double&                  quantity_buy,
                                                        const mtk::Double&                  sum_prec_by_quantity_sell,
                                                        const mtk::Double&                  quantity_sell
                                               )
{
    if(unit_cost.HasValue() == false                ||  last_price.HasValue() == false   ||
       sum_prec_by_quantity_buy.IsValid() == false  ||  quantity_buy.IsValid() == false  ||
       sum_prec_by_quantity_sell.IsValid() == false ||  quantity_sell.IsValid() == false)
            return  mtk::nullable<mtk::Double>();

    mtk::Double  buy_price    {mtk::Double::InvalidValue()};
    mtk::Double  sell_price   {mtk::Double::InvalidValue()};
    mtk::Double  max_quantity {mtk::Double::InvalidValue()};

    if(quantity_buy > quantity_sell)
    {
        max_quantity = quantity_buy;
        buy_price = sum_prec_by_quantity_buy   / max_quantity;

        sell_price = (sum_prec_by_quantity_sell + (quantity_buy-quantity_sell)*last_price.Get().GetDouble())  / max_quantity;
    }
    else if (quantity_buy < quantity_sell)
    {
        max_quantity = quantity_sell;
        sell_price = sum_prec_by_quantity_sell  / max_quantity;

        buy_price = (sum_prec_by_quantity_buy + (quantity_sell-quantity_buy)*last_price.Get().GetDouble())  / max_quantity;
    }
    else
    {
        max_quantity = quantity_buy;
        buy_price = sum_prec_by_quantity_buy    / max_quantity;
        sell_price = sum_prec_by_quantity_sell  / max_quantity;
    }

    mtk::Double  result = (sell_price - buy_price) *  unit_cost.Get()  * max_quantity;
    return  mtk::make_nullable(  result  );
}


class QTreeWidgetItem_exec__Product  : public  QTreeWidgetItem_exec,   public  mtk::SignalReceptor
{
    typedef  QTreeWidgetItem_exec__Product     CLASS_NAME;

    void local_add_exec(mtk::trd::msg::enBuySell /*buy_sell*/, const mtk::FixedNumber& /*_price*/, const mtk::FixedNumber& /*_quantity*/)
    {
        mtk::FixedNumber  diff_quantity = subs_fixed_numbers(buy_quantity, sell_quantity);

        this->setText(5,    QLocale::system().toString(diff_quantity.GetDouble().get2(), 'f', 0));

        QBrush  bbuy(qtmisc::mtk_color_buy_cell);
        bbuy.setStyle(Qt::SolidPattern);
        QBrush  bsell(qtmisc::mtk_color_sell_cell);
        bsell.setStyle(Qt::SolidPattern);
        if(diff_quantity.GetIntCode() == 0)
            this->setBackground(5, QBrush());
        else if(diff_quantity.GetIntCode() < 0)
            this->setBackground(5, bsell);
        else
            this->setBackground(5, bbuy);


        update_win_loss();
    }

public:
    mtk::CountPtr<mtk::prices::price_manager>       price_manager;
    mtk::nullable<mtk::Double>                      unit_cost;
    mtk::nullable<mtk::FixedNumber>                 last_price;


    void add_exec(mtk::trd::msg::enBuySell buy_sell, const mtk::FixedNumber& _price, const mtk::FixedNumber& _quantity)
    {
        QTreeWidgetItem_exec::add_exec(buy_sell, _price, _quantity);
        local_add_exec(buy_sell, _price, _quantity);
    }

    void  update_win_loss (void)
    {
        mtk::nullable<mtk::Double> win_loss = calculate_win_loss(unit_cost, last_price, buy_price_by_quantity, buy_quantity.GetDouble(), sell_price_by_quantity, sell_quantity.GetDouble());
        if(win_loss.HasValue())
            this->setText(6, QLocale::system().toString(win_loss.Get().get2(), 'f', 2));
        else
            this->setText(6, QLatin1String("##"));
    }


    QTreeWidgetItem_exec__Product( QTreeWidgetItem * parent, mtk::trd::msg::enBuySell buy_sell, const mtk::FixedNumber& _price, const mtk::FixedNumber& _quantity, const mtk::msg::sub_product_code& _product_code)
        :   QTreeWidgetItem_exec(parent, buy_sell, _price, _quantity),
            price_manager (mtk::make_cptr(new mtk::prices::price_manager(_product_code)))
    {
        QFont  font = this->font(0);
        font.setBold(true);
        this->setFont(1, font);
        this->setFont(2, font);
        this->setFont(3, font);
        this->setFont(4, font);
        this->setFont(5, font);
        this->setFont(6, font);

        if(ecimd_config::loss_win() == true)
        {
            MTK_CONNECT_THIS(price_manager->signal_additional_info_update, on_message_addtional_info);
            MTK_CONNECT_THIS(price_manager->signal_last_mk_execs_ticker,   on_message_last_mk_execs_ticker);

            if(price_manager->get_additional_info().HasValue())
                on_message_addtional_info(_product_code, price_manager->get_additional_info().Get());
            if(price_manager->get_last_mk_execs_ticker().HasValue())
                on_message_last_mk_execs_ticker(_product_code, price_manager->get_last_mk_execs_ticker().Get());
        }

        local_add_exec(buy_sell, _price, _quantity);
        update_win_loss();
    }

    void on_message_addtional_info(const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_additional_info& additional_info)
    {
        unit_cost = additional_info.unit_cost;
        update_win_loss();
    }

    void on_message_last_mk_execs_ticker(const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_last_mk_execs_ticker&  mk_execs_ticker)
    {
        last_price = mk_execs_ticker.last_price;
        update_win_loss();
    }

};



QTreeWidgetItem*  get0_client_item(QTreeWidget* tree_widget, const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& /*exec*/)
{
    QTreeWidgetItem *result=0;
    QString key = QLatin1String(confirm_info.invariant.account.client_code.c_str());
    for(int i=0; i<tree_widget->topLevelItemCount(); ++i)
    {
        if(tree_widget->topLevelItem(i)->text(0)  == key)
            return tree_widget->topLevelItem(i);
    }

    result = new QTreeWidgetItem(tree_widget);
    result->setText(0, key);
    return result;
}


QTreeWidgetItem*  get0_key_item(QTreeWidget* tree_widget, const QString& key)
{
    QTreeWidgetItem *result=0;
    for(int i=0; i<tree_widget->topLevelItemCount(); ++i)
    {
        if(tree_widget->topLevelItem(i)->text(0)  == key)
            return tree_widget->topLevelItem(i);
    }

    result = new QTreeWidgetItem(tree_widget);
    result->setText(0, key);
    return result;
}

QTreeWidgetItem*  getn_key_item(QTreeWidgetItem* tree_widget_item, const QString& key)
{
    QTreeWidgetItem *result=0;
    for(int i=0; i<tree_widget_item->childCount(); ++i)
    {
        if(tree_widget_item->child(i)->text(0)  == key)
            return tree_widget_item->child(i);
    }

    result = new QTreeWidgetItem(tree_widget_item);
    result->setText(0, key);
    return result;
}

QTreeWidgetItem_exec*  getn_key_item_exec(QTreeWidgetItem* tree_widget_item, const QString& key, const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
{
    QTreeWidgetItem_exec *result=0;
    for(int i=0; i<tree_widget_item->childCount(); ++i)
    {
        if(tree_widget_item->child(i)->text(0)  == key)
        {
            result = static_cast<QTreeWidgetItem_exec *>(tree_widget_item->child(i));
            result->add_exec(confirm_info.invariant.side, exec.price, exec.quantity);
            return result;
        }
    }

    result = new QTreeWidgetItem_exec(tree_widget_item, confirm_info.invariant.side, exec.price, exec.quantity);
    result->setText(0, key);
    return result;
}

QTreeWidgetItem_exec__Product*  getn_key_item_exec__Product(QTreeWidgetItem* tree_widget_item, const QString& key, const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec,
                                                   const  mtk::msg::sub_product_code&   product_code)
{
    QTreeWidgetItem_exec__Product *result=0;
    for(int i=0; i<tree_widget_item->childCount(); ++i)
    {
        if(tree_widget_item->child(i)->text(0)  == key)
        {
            result = static_cast<QTreeWidgetItem_exec__Product *>(tree_widget_item->child(i));
            result->add_exec(confirm_info.invariant.side, exec.price, exec.quantity);
            return result;
        }
    }

    result = new QTreeWidgetItem_exec__Product(tree_widget_item, confirm_info.invariant.side, exec.price, exec.quantity, product_code);
    result->setText(0, key);
    return result;
}
};   //  namespace {


void WExecsReport::on_new_execution(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
{
    if( (confirm_info.invariant.product_code.market == "EU"  ||  confirm_info.invariant.product_code.market == "M3"  ||  confirm_info.invariant.product_code.market == "LF")
       &&  confirm_info.invariant.product_code.product[0] != 'F')       //  it isn't a calendar spread
        return;

    auto client_item   = get0_key_item                  (ui->treeWidget, QLatin1String(confirm_info.invariant.account.client_code.c_str()));
    auto account_item  = getn_key_item                  (client_item,    QLatin1String(confirm_info.invariant.account.name.c_str()));
    auto market_item   = getn_key_item                  (account_item,   QLatin1String(confirm_info.invariant.product_code.market.c_str()));
    //auto product_item  = getn_key_item_exec           (market_item,    QLatin1String(confirm_info.invariant.product_code.product.c_str()),     confirm_info, exec);
    auto product_item  = getn_key_item_exec__Product    (market_item,    QLatin1String(confirm_info.invariant.product_code.product.c_str()),     confirm_info, exec, confirm_info.invariant.product_code);
                         getn_key_item_exec             (product_item,   qtmisc::fn_as_QString(exec.price),                                      confirm_info, exec);
}


