#include "wexechistreport.h"
#include "ui_wexechistreport.h"

#include <QCalendarWidget>

#include "qmtk_misc.h"


//testing
#include "components/trading/trd_cli_ord_book.h"




QDialog*   get_main_window();



namespace execs_hist_report
{
    void show(void)
    {
        static WExecsHistReport*  execs_hist_report = new WExecsHistReport(get_main_window());

        execs_hist_report->show();
    }
};






/*      testing
mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>
        __testing_generate_exec_conf(const std::string& _market, const std::string& _product_code, const std::string _account, mtk::trd::msg::enBuySell _buy_sell, double price, int quantity)
{
    static int counter = 0;
    mtk::trd::msg::sub_order_id                 order_id    (mtk::msg::sub_request_id("201205041131007400", MTK_SS(counter)));
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

WExecsHistReport::WExecsHistReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WExecsHistReport)
{
    ui->setupUi(this);
    ui->treeWidget->header()->resizeSection(0, 20);
    ui->dateEdit->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    if(QDate::currentDate().dayOfWeek() == Qt::Monday)
        ui->dateEdit->setDate(QDate::currentDate().addDays(-3));
    else
        ui->dateEdit->setDate(QDate::currentDate().addDays(-1));

    /*      testing
    {
        mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>  exec =
                __testing_generate_exec_conf("MARKET", "FGBLZZ", "JOSE", mtk::trd::msg::buy, 102.3, 7);
        on_new_execution(exec._0, exec._1);
    }
    {
        mtk::tuple<mtk::trd::msg::CF_XX, mtk::trd::msg::sub_exec_conf>  exec =
                __testing_generate_exec_conf("MARKET", "FGBLZZ", "JOSE", mtk::trd::msg::buy, 102.3, 1);
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
    //on_new_execution(*it, it->executed_pos);
    ui->treeWidget->header()->setSectionHidden(0, true);
}

WExecsHistReport::~WExecsHistReport()
{
    delete ui;
}



namespace  {

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

public:
    const mtk::trd::msg::CF_XX      cf_xx;

    mtk::Double                     sum__price_by_quantity;
    mtk::Double                     quantity;


    virtual void add_exec(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
    {
        if(cf_xx.invariant  ==  confirm_info.invariant)
        {
            quantity +=  exec.quantity.GetDouble();
            sum__price_by_quantity +=  exec.price.GetDouble() * exec.quantity.GetDouble();
            this->setText(5, QLocale::system().toString(quantity.get2(), 'f', 0));
            this->setText(6, QLocale::system().toString((sum__price_by_quantity / quantity).get2(), 'f', 4));
        }
    }


    QTreeWidgetItem_exec( QTreeWidget * parent, const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
        :   QTreeWidgetItem(parent),
            cf_xx(confirm_info),
            sum__price_by_quantity(0.),
            quantity(0.)
    {
        this->setText(1, QLatin1String(cf_xx.invariant.account.client_code.c_str()));
        this->setText(2, QLatin1String(cf_xx.invariant.account.name.c_str()));
        this->setText(3, QLatin1String(MTK_SS(cf_xx.invariant.product_code.market << "." << cf_xx.invariant.product_code.product).c_str()));
        this->setText(4, qtmisc::side_as_text(cf_xx.invariant.side));

        this->setTextAlignment(1, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setTextAlignment(2, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setTextAlignment(3, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setTextAlignment(4, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setTextAlignment(5, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setTextAlignment(6, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);

        add_exec(confirm_info, exec);
    }

    /*
    QTreeWidgetItem_exec( QTreeWidgetItem * parent, const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
        :   QTreeWidgetItem(parent),
            invariant(confirm_info.invariant),
            price_by_quantity(0.)
    {
        price = exec.price;
        add_exec(confirm_info, exec);
    }
*/
    virtual ~QTreeWidgetItem_exec(){}

};


class QTreeWidgetItem_exec_by_price : public  QTreeWidgetItem
{

public:
    const mtk::trd::msg::sub_invariant_order_info   invariant;

    const mtk::FixedNumber                price;
    mtk::FixedNumber                quantity;


    virtual void add_exec(const mtk::trd::msg::CF_XX&  /*confirm_info*/, const mtk::trd::msg::sub_exec_conf& exec)
    {
        quantity = add_fixed_numbers(quantity, exec.quantity);
        this->setText(5, qtmisc::fn_as_QString(quantity));
    }


    QTreeWidgetItem_exec_by_price( QTreeWidgetItem * parent, const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec, const mtk::trd::msg::CF_XX&  parent_confirm_info)
        :   QTreeWidgetItem(parent),
            invariant(confirm_info.invariant),
            price(exec.price),
            quantity(exec.quantity)
    {
        quantity.SetIntCode(0);
        if(parent_confirm_info.invariant.account.client_code != invariant.account.client_code)
            this->setText(1, QLatin1String(invariant.account.client_code.c_str()));
        if(parent_confirm_info.invariant.account.name != invariant.account.name)
            this->setText(2, QLatin1String(invariant.account.name.c_str()));
        if(parent_confirm_info.invariant.product_code != invariant.product_code)
            this->setText(3, QLatin1String(MTK_SS(invariant.product_code.market << "." << invariant.product_code.product).c_str()));

        this->setText(4, qtmisc::side_as_text(invariant.side));
        this->setText(6, qtmisc::fn_as_QString(price));

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

        add_exec(confirm_info, exec);
    }

    /*
    QTreeWidgetItem_exec( QTreeWidgetItem * parent, const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
        :   QTreeWidgetItem(parent),
            invariant(confirm_info.invariant),
            price_by_quantity(0.)
    {
        price = exec.price;
        add_exec(confirm_info, exec);
    }
*/
    virtual ~QTreeWidgetItem_exec_by_price(){}

};


QTreeWidgetItem_exec*  get0_key_item_exec(QTreeWidget* tree_widget, const QString& key, const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
{
    QTreeWidgetItem_exec *result=0;
    for(int i=0; i<tree_widget->topLevelItemCount(); ++i)
    {
        if(tree_widget->topLevelItem(i)->text(0)  == key)
        {
            result = static_cast<QTreeWidgetItem_exec *>(tree_widget->topLevelItem(i));
            result->add_exec(confirm_info, exec);
            return result;
        }
    }

    result = new QTreeWidgetItem_exec(tree_widget, confirm_info, exec);
    result->setText(0, key);
    return result;
}

QTreeWidgetItem_exec_by_price*  get1_key_item_exec_by_price(QTreeWidgetItem* tree_widget_item, const QString& key, const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec,
                                                                    const mtk::trd::msg::CF_XX&  parent_confirm_info)
{
    QTreeWidgetItem_exec_by_price *result=0;
    for(int i=0; i<tree_widget_item->childCount(); ++i)
    {
        if(tree_widget_item->child(i)->text(0)  == key)
        {
            result = static_cast<QTreeWidgetItem_exec_by_price *>(tree_widget_item->child(i));
            result->add_exec(confirm_info, exec);
            return result;
        }
    }

    result = new QTreeWidgetItem_exec_by_price(tree_widget_item, confirm_info, exec, parent_confirm_info);
    result->setText(0, key);
    return result;
}


/*
QString  get_order_id(const  mtk::trd::msg::sub_order_id&  order_id)
{
    return QLatin1String(MTK_SS(order_id.session_id << ":" << order_id.req_code).c_str());
}
*/

QString  get_main_text_key(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf&  /*exec*/)
{
    return QLatin1String(MTK_SS(confirm_info.invariant.order_id).c_str());
}

QString  get_second_text_key(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf&  exec)
{
    return QLatin1String(MTK_SS(confirm_info.invariant  <<  exec.price).c_str());
}

};  //  namespace {



void WExecsHistReport::process_execution(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
{
    //auto client_item   = get0_key_item                  (ui->treeWidget, QLatin1String(confirm_info.invariant.account.client_code.c_str()));
    //auto account_item  = getn_key_item                  (client_item,    QLatin1String(confirm_info.invariant.account.name.c_str()));
    //auto market_item   = getn_key_item                  (account_item,   QLatin1String(confirm_info.invariant.product_code.market.c_str()));
    //auto product_item  = getn_key_item_exec__Product    (market_item,    QLatin1String(confirm_info.invariant.product_code.product.c_str()),     confirm_info, exec, confirm_info.invariant.product_code);
    //auto order_item    = getn_key_item_exec             (product_item,   get_order_id(confirm_info.invariant.order_id),                          confirm_info, exec);
    //auto order_item    =

    std::string  filter_product_name = ui->filter_product->currentText().toStdString();
    std::string  product_name = confirm_info.invariant.product_code.product;
    {
        bool located=false;
        for(int i=0; i<ui->filter_product->count(); ++i)
        {
            if(ui->filter_product->itemText(i).toStdString() ==  product_name)
            {
                located = true;
                break;
            }
        }
        if(!located)
            ui->filter_product->addItem(QLatin1String(product_name.c_str()));
    }
    if(confirm_info.invariant.product_code.product.find(filter_product_name.c_str()) <1000  ||  filter_product_name == tr("all").toStdString())
    {
        QTreeWidgetItem_exec*  order_item    =  get0_key_item_exec               (ui->treeWidget,   get_main_text_key  (confirm_info, exec),                     confirm_info, exec);
                                                get1_key_item_exec_by_price      (order_item,       get_second_text_key(confirm_info, exec),                     confirm_info, exec, order_item->cf_xx);
    }

                         //getn_key_item_exec               (order_item,       qtmisc::fn_as_QString(exec.price),                                 confirm_info, exec);
    //new QTreeWidgetItem_exec(ui->treeWidget, confirm_info, exec);
}



void  WExecsHistReport::reactivate_request_button(const int&)
{
    ui->pb_request->setEnabled(true);
    ui->dateEdit->setEnabled(true);
}





void WExecsHistReport::on_pb_request_clicked()
{
    ui->treeWidget->clear();
    list_execs.clear();
    ui->filter_product->clear();
    ui->filter_product->addItem(tr("all"));
    ui->message->clear();

    //  testing
    /*
    mtk::list<mtk::trd::msg::CF_EXLK>  list_all_execs = mtk::trd::trd_cli_ord_book::get_all_execs();
    for(auto it=list_all_execs.begin(); it!=list_all_execs.end(); ++it)
        on_new_execution(*it, it->executed_pos);
        */
    //  testing


    ui->pb_request->setEnabled(false);
    ui->dateEdit->setEnabled(false);
    MTK_CALL_LATER1S_THIS(mtk::dtSeconds(10), 0, reactivate_request_button);

    mtk::msg::sub_request_info              request_info        (mtk::admin::get_request_info());
    mtk::trd::msg::RQ_EXECS_HISTORIC        rq_execs_historic   (request_info, qtmisc::QDate_as_mtk_DateTime(ui->dateEdit->date()));
    mtk_send_message("client", rq_execs_historic);

    subscribe_response(request_info.req_id);

    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "request_execs_hist", MTK_SS("date " << qtmisc::QDate_as_mtk_DateTime(ui->dateEdit->date())), mtk::alPriorDebug));
}


void  WExecsHistReport::subscribe_response(const mtk::msg::sub_request_id&  request_id)
{
    static mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_EX_HIST> >    handle;
    MTK_QPID_RECEIVER_CONNECT_THIS(
                            handle,
                            mtk::admin::get_url("client"),
                            mtk::trd::msg::CF_EX_HIST::get_in_subject(mtk::admin::get_process_info().location.broker_code, mtk::admin::get_session_id(), request_id.req_code),
                            mtk::trd::msg::CF_EX_HIST,
                            on_cf_ex_hist)
}


void  WExecsHistReport::on_cf_ex_hist(const mtk::trd::msg::CF_EX_HIST&  ex_hist)
{
    list_execs.push_back(mtk::trd::msg::CF_EXLK(ex_hist));
    process_execution(ex_hist, ex_hist.executed_pos);
    if(ex_hist.truncated_response)
        ui->message->setText(tr("Too many execs. Truncated response."));
}

void WExecsHistReport::on_dateEdit_dateChanged(QDate date)
{
    ui->treeWidget->clear();

    mtk::DateTime   selected_date = qtmisc::QDate_as_mtk_DateTime(date);
    if(selected_date < (mtk::dtNowLocal()-mtk::dtDays(60)) )
        ui->message->setText(tr("invalid date. Date too far"));
    else if(selected_date > mtk::dtNowLocal())
        ui->message->setText(tr("invalid date. Future date"));
    else if(selected_date == mtk::dtToday_0Time())
        ui->message->setText(tr("invalid date."));
    else
        ui->message->setText(QLatin1String(""));

    if(ui->message->text() == QLatin1String("")  ||  ui->message->text() == QLatin1String("_"))
        ui->pb_request->setEnabled(true);
    else
        ui->pb_request->setEnabled(false);
}


void WExecsHistReport::on_filter_product_currentIndexChanged(QString /*value*/)
{
    ui->treeWidget->clear();
    for(auto it= list_execs.begin(); it!=list_execs.end(); ++it)
    {
        mtk::trd::msg::CF_EXLK& item= *it;      //  I know it's dangerous
        process_execution(item, item.executed_pos);
    }
}

void WExecsHistReport::on_pb_copy_clicked()
{
    qtmisc::copy_execs_clipboard(list_execs);
}
