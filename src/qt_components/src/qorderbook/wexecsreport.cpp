#include "wexecsreport.h"
#include "ui_wexecsreport.h"

#include "qmtk_misc.h"
#include "components/trading/trd_cli_ord_book.h"


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

    /*      testing
    {
        mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>  exec =
                __testing_generate_exec_conf("EU", "FGBLZZ", "JOSE", mtk::trd::msg::buy, 102.3, 7);
        on_new_execution(exec._0, exec._1);
    }
    {
        mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>  exec =
                __testing_generate_exec_conf("EU", "FGBLZA", "JOSE", mtk::trd::msg::buy, 102.0, 1);
        on_new_execution(exec._0, exec._1);
    }
    {
        mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>  exec =
                __testing_generate_exec_conf("EU", "FGBLZZ", "JOSE", mtk::trd::msg::buy, 102.0, 1);
        on_new_execution(exec._0, exec._1);
    }
    {
        mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>  exec =
                __testing_generate_exec_conf("EU", "FGBLZZ", "JOSE", mtk::trd::msg::sell, 102.0, 1);
        on_new_execution(exec._0, exec._1);
    }
    {
        mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>  exec =
                __testing_generate_exec_conf("M3", "FGBLZZ", "JOSE", mtk::trd::msg::sell, 102.0, 1);
        on_new_execution(exec._0, exec._1);
    }
    {
        mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>  exec =
                __testing_generate_exec_conf("M3", "FGBLZZ", "JOSE2", mtk::trd::msg::sell, 102.0, 1);
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
private:
    mtk::FixedNumber    buy_quantity;
    mtk::FixedNumber    sell_quantity;
    mtk::Double         buy_price_by_quantity;
    mtk::Double         sell_price_by_quantity;

public:
    void add_exec(mtk::trd::msg::enBuySell buy_sell, const mtk::FixedNumber& _price, const mtk::FixedNumber& _quantity)
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

        mtk::FixedNumber  diff_quantity = subs_fixed_numbers(buy_quantity, sell_quantity);
        this->setText(5,    QLocale::system().toString(diff_quantity.GetDouble().get2(), 'f', 0));

        QBrush  bbuy(qtmisc::mtk_color_buy_cell);
        bbuy.setStyle(Qt::SolidPattern);
        QBrush  bsell(qtmisc::mtk_color_sell_cell);
        bsell.setStyle(Qt::SolidPattern);
        QBrush  bnone(Qt::white);
        bnone.setStyle(Qt::SolidPattern);
        if(diff_quantity.GetIntCode() == 0)
            this->setBackground(5, QBrush());
        else if(diff_quantity.GetIntCode() < 0)
            this->setBackground(5, bsell);
        else
            this->setBackground(5, bbuy);
    }


    QTreeWidgetItem_exec( QTreeWidgetItem * parent, mtk::trd::msg::enBuySell buy_sell, const mtk::FixedNumber& _price, const mtk::FixedNumber& _quantity, bool bold)
        :   QTreeWidgetItem(parent),
            buy_quantity(_quantity),                            sell_quantity(_quantity),
            buy_price_by_quantity(0.), sell_price_by_quantity(0.)
    {
        buy_quantity.SetIntCode(0);
        sell_quantity.SetIntCode(0);

        QBrush  bbuy(qtmisc::mtk_color_buy_cell);
        bbuy.setStyle(Qt::SolidPattern);
        QBrush  bsell(qtmisc::mtk_color_sell_cell);
        bsell.setStyle(Qt::SolidPattern);
        this->setBackground(1, bbuy);
        this->setBackground(2, bbuy);
        this->setBackground(3, bsell);
        this->setBackground(4, bsell);

        this->setTextAlignment(1, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setTextAlignment(2, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setTextAlignment(3, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setTextAlignment(4, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setTextAlignment(5, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);

        QFont  font = this->font(0);
        font.setBold(bold);
        this->setFont(1, font);
        this->setFont(2, font);
        this->setFont(3, font);
        this->setFont(4, font);
        this->setFont(5, font);

        add_exec(buy_sell, _price, _quantity);
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

QTreeWidgetItem_exec*  getn_key_item_exec(QTreeWidgetItem* tree_widget_item, const QString& key, const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec, bool bold)
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

    result = new QTreeWidgetItem_exec(tree_widget_item, confirm_info.invariant.side, exec.price, exec.quantity, bold);
    result->setText(0, key);
    return result;
}

void WExecsReport::on_new_execution(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
{
    auto client_item   = get0_key_item         (ui->treeWidget, QLatin1String(confirm_info.invariant.account.client_code.c_str()));
    auto account_item  = getn_key_item         (client_item,    QLatin1String(confirm_info.invariant.account.name.c_str()));
    auto market_item   = getn_key_item         (account_item,   QLatin1String(confirm_info.invariant.product_code.market.c_str()));
    auto product_item  = getn_key_item_exec    (market_item,    QLatin1String(confirm_info.invariant.product_code.product.c_str()),     confirm_info, exec, true);
                         getn_key_item_exec    (product_item,   qtmisc::fn_as_QString(exec.price),                                      confirm_info, exec, false);
}


