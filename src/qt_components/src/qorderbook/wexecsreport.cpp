#include "wexecsreport.h"
#include "ui_wexecsreport.h"


#include <QSpinBox>
#include <Phonon/MediaObject>


#include "qmtk_misc.h"
#include "components/trading/trd_cli_ord_book.h"
#include "components/prices/cli/price_manager.h"
#include "qt_components/src/wusermessage.h"
#include "qt_components/src/qlocaledoublespinbox.h"

#include "ecimd_config.h"




namespace
{
    mtk::Signal<int, const mtk::trd::msg::CF_XX&, const mtk::Double&> &   get_signal_loss_win_modif(void)
    {
        static  mtk::Signal<int, const mtk::trd::msg::CF_XX&, const mtk::Double&>    loss_win;
        return loss_win;
    }

    mtk::Signal<>&   get_signal_end_editing(void)
    {
        static  mtk::Signal<>    result;
        return result;
    }
};




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

QWidget* alarm_delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const
{
    if(index.column() == 7)
    {
        qLocaleDoubleSpinBox*  editor = new qLocaleDoubleSpinBox(parent);
        editor->setButtonSymbols(QAbstractSpinBox::NoButtons);
        editor->setSingleStep(1000);
        editor->setMinimum(-1000000);
        editor->setMaximum(1000000);
        editor->setAlignment(Qt::AlignHCenter);
        editor->setDecimals(0);
        editor->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        QFont font(parent->font());
        font.setBold(false);
        editor->setFont(font);

        return editor;
    }
        //return QItemDelegate::createEditor(parent, option, index);
    else
        return 0;
}


void alarm_delegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    double value = QLocale::system().toDouble(index.model()->data(index, Qt::EditRole).toString());

    qLocaleDoubleSpinBox *spinBox = static_cast<qLocaleDoubleSpinBox*>(editor);
    spinBox->setValue(value);
}


void alarm_delegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    qLocaleDoubleSpinBox *spinBox = static_cast<qLocaleDoubleSpinBox*>(editor);
    if(spinBox->text().size()>0)
    {
        spinBox->interpretText();
        double value = spinBox->value();

        //model->setData(index, value, Qt::EditRole);
        //model->setData(index, QLocale::system().toString(value, 'f', 0), Qt::EditRole);
        model->setData(index, value);
    }
    else
        model->setData(index, QLatin1String(""), Qt::EditRole);

    //  end edition
    get_signal_end_editing().emit();
}





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

    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(slot_itemChanged(QTreeWidgetItem*,int)));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), SLOT(slot_itemDoubleClicked(QTreeWidgetItem*,int)));


    if(ecimd_config::loss_win() == true)
    {
        //      accounts
        if(ecimd_config::loss_win() == true)
            mtk::accmgrcli::get_signal_new_grant_received()->connect(this, &WExecsReport::on_grant_received);
        mtk::list<mtk::trd::account::msg::sub_grant>  grant_list  = mtk::accmgrcli::get_grant_list();
        for(auto it = grant_list.begin(); it!=grant_list.end(); ++it)
            on_grant_received(*it);

        //  edit alarms
        ui->treeWidget->setItemDelegate(new alarm_delegate(this));
    }
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


class QTreeWidgetItem_alarm__account : public  QTreeWidgetItem,   public  mtk::SignalReceptor
{
protected:
    mtk::trd::msg::sub_account_info     account;
    mtk::Double                         alarm;
    mtk::Double                         loss_win;
    mtk::map<int, mtk::Double>          loss_win_detailled;
    bool                                alarm_triggered;
    bool                                editing_alarm;

public:

    QTreeWidgetItem_alarm__account( QTreeWidgetItem * parent, const mtk::trd::msg::sub_account_info&   _account)
        :   QTreeWidgetItem(parent),
            account(_account),
            alarm(mtk::Double::InvalidValue()),
            loss_win(0.),
            alarm_triggered(false),
            editing_alarm(false)
    {
        this->setTextAlignment(6, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setTextAlignment(7, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        this->setBackground(7, QBrush  (qtmisc::mtk_color_header));
        this->setFlags(this->flags() |  Qt::ItemIsEditable);

        MTK_CONNECT_THIS(get_signal_loss_win_modif(), slot_loss_win_modified);
        MTK_CONNECT_THIS(get_signal_end_editing(),    slot_edit_finished);

    }
    virtual ~QTreeWidgetItem_alarm__account(){}



    void  set_editing_alarm(void)
    {
        editing_alarm = true;
    }
    void  slot_edit_finished(void)
    {
        if(editing_alarm)
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "alarm l/w conf", MTK_SS(account << "  " << alarm  << "  current l/w:" << loss_win), mtk::alPriorDebug));
            editing_alarm = false;
            alarm_triggered = false;
            this->setBackground(7, QBrush  (qtmisc::mtk_color_header));
            check_alarm();
        }
    }

    void  set_alarm(const mtk::Double&  _alarm)
    {
        if(alarm == _alarm   &&   alarm_triggered==false)
            return;

        alarm_triggered = false;
        alarm = _alarm;
        this->setBackground(7, QBrush  (qtmisc::mtk_color_header));
        check_alarm();
    }

    void check_alarm(void)
    {
        if(editing_alarm ==false  &&  alarm_triggered==false   &&  alarm.IsValid()  &&  loss_win.IsValid()  &&  alarm != mtk::Double(0.)  &&  alarm>=loss_win)
        {
            this->setBackground(7, QBrush  (qtmisc::mtk_color_problem));
            wUserMessage::show_message(QObject::tr("ALARM\nloss/win  on product %1.  Configured on %2").arg(QLatin1String(MTK_SS(account).c_str()), QLocale::system().toString(alarm.get2(), 'f', 0)));
            static  Phonon::MediaObject* mediaObject = Phonon::createPlayer(Phonon::NoCategory, Phonon::MediaSource(QLatin1String("../data/alarm.wav")));
            mediaObject->stop();
            mediaObject->play();
            alarm_triggered = true;
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "alarm l/w triggered", MTK_SS(account << "  " << alarm  << "  current l/w:" << loss_win), mtk::alPriorDebug));
        }
    }

    void  slot_loss_win_modified(int  uuid_code, const mtk::trd::msg::CF_XX& conf_info, const  mtk::Double&  _loss_win)
    {
        if(conf_info.invariant.account !=  account)
            return;


        auto it = loss_win_detailled.find(uuid_code);
        if(it == loss_win_detailled.end())
            loss_win_detailled.insert(std::make_pair(uuid_code, _loss_win));
        else
            it->second =  _loss_win;

        loss_win = mtk::Double(0.);
        for(auto it=loss_win_detailled.begin(); it!=loss_win_detailled.end(); ++it)
            loss_win = loss_win + it->second;

        if(loss_win.IsValid())
        {
            //if(loss_win == mtk::Double(0.))
            //    this->setText(6, QLatin1String(""));
            //else
            this->setText(6, QLocale::system().toString(loss_win.get2(), 'f', 0));
            check_alarm();
        }
        else
            this->setText(6, QLatin1String("##"));
    }
};






class QTreeWidgetItem_exec : public  QTreeWidgetItem
{
protected:
    mtk::FixedNumber    buy_quantity;
    mtk::FixedNumber    sell_quantity;
    mtk::Double         buy_price_by_quantity;
    mtk::Double         sell_price_by_quantity;

public:
    virtual void add_exec(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
    {
        mtk::FixedNumber*       quantity;
        mtk::Double     *       price_by_quantity;
        int                     index_price;
        int                     index_quantity;

        if(confirm_info.invariant.side == mtk::trd::msg::buy)
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
        *quantity = add_fixed_numbers(*quantity, exec.quantity);
        *price_by_quantity = *price_by_quantity + (exec.price.GetDouble() * exec.quantity.GetDouble());

        this->setText(index_quantity, qtmisc::fn_as_QString(*quantity));
        this->setText(index_price,    QLocale::system().toString((*price_by_quantity / quantity->GetDouble()).get2(), 'f', 4));
    }


    QTreeWidgetItem_exec( QTreeWidgetItem * parent, const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
        :   QTreeWidgetItem(parent),
            buy_quantity(exec.quantity),                            sell_quantity(exec.quantity),
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


        add_exec(confirm_info, exec);
    }
    virtual ~QTreeWidgetItem_exec(){}

};


mtk::Double   calculate_win_loss(                       const mtk::Double&                  unit_cost,
                                                        mtk::nullable<mtk::FixedNumber>     last_price,
                                                        const mtk::Double&                  sum_prec_by_quantity_buy,
                                                        const mtk::Double&                  quantity_buy,
                                                        const mtk::Double&                  sum_prec_by_quantity_sell,
                                                        const mtk::Double&                  quantity_sell
                                               )
{
    if(unit_cost == 0.                              ||  last_price.HasValue() == false   ||
       sum_prec_by_quantity_buy.IsValid() == false  ||  quantity_buy.IsValid() == false  ||
       sum_prec_by_quantity_sell.IsValid() == false ||  quantity_sell.IsValid() == false)
        return  mtk::Double::InvalidValue();

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

    mtk::Double  result = (sell_price - buy_price) *  unit_cost  * max_quantity;
    return  result;
}


class QTreeWidgetItem_exec__Product  : public  QTreeWidgetItem_exec,   public  mtk::SignalReceptor
{
    void local_add_exec(const mtk::trd::msg::CF_XX&  /*confirm_info*/, const mtk::trd::msg::sub_exec_conf& /*exec*/)
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


        //update_win_loss();        called later
    }

public:
    static  int  static_uuid;

    const int                                       uuid;
    const mtk::trd::msg::CF_XX                      cf_xx;
    mtk::CountPtr<mtk::prices::price_manager>       price_manager;
    mtk::Double                                     unit_cost;
    mtk::nullable<mtk::FixedNumber>                 last_price;


    void add_exec(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
    {
        QTreeWidgetItem_exec::add_exec(confirm_info, exec);
        local_add_exec(confirm_info, exec);
        update_win_loss();
    }

    void  update_win_loss (void)
    {
        mtk::Double   win_loss = calculate_win_loss(unit_cost, last_price, buy_price_by_quantity, buy_quantity.GetDouble(), sell_price_by_quantity, sell_quantity.GetDouble());
        if(win_loss.IsValid())
            this->setText(6, QLocale::system().toString(win_loss.get2(), 'f', 0));
        else
            this->setText(6, QLatin1String("##"));
        get_signal_loss_win_modif().emit(uuid, cf_xx, win_loss);
    }


    QTreeWidgetItem_exec__Product( QTreeWidgetItem * parent, const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
        :   QTreeWidgetItem_exec(parent, confirm_info, exec),
            uuid(++QTreeWidgetItem_exec__Product::static_uuid),
            cf_xx(confirm_info),
            price_manager (mtk::make_cptr(new mtk::prices::price_manager(confirm_info.invariant.product_code))),
            unit_cost(mtk::Double::InvalidValue())
    {
        QFont  font = this->font(0);
        font.setBold(true);
        this->setFont(1, font);
        this->setFont(2, font);
        this->setFont(3, font);
        this->setFont(4, font);
        this->setFont(5, font);
        this->setFont(6, font);

        local_add_exec(confirm_info, exec);

        if(ecimd_config::loss_win() == true)
        {
            MTK_CONNECT_THIS(price_manager->signal_additional_info_update, on_message_addtional_info);
            MTK_CONNECT_THIS(price_manager->signal_last_mk_execs_ticker,   on_message_last_mk_execs_ticker);

            if(price_manager->get_additional_info().HasValue())
                on_message_addtional_info(confirm_info.invariant.product_code, price_manager->get_additional_info().Get());
            if(price_manager->get_last_mk_execs_ticker().HasValue())
                on_message_last_mk_execs_ticker(confirm_info.invariant.product_code, price_manager->get_last_mk_execs_ticker().Get());
            update_win_loss();
        }
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
int  QTreeWidgetItem_exec__Product::static_uuid=0;



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

QTreeWidgetItem_alarm__account*  getn_key_item_alarm(QTreeWidgetItem* tree_widget_item, const QString& key, const mtk::trd::msg::sub_account_info&   account)
{
    QTreeWidgetItem_alarm__account *result=0;
    for(int i=0; i<tree_widget_item->childCount(); ++i)
    {
        if(tree_widget_item->child(i)->text(0)  == key)
        {
            result = static_cast<QTreeWidgetItem_alarm__account *>(tree_widget_item->child(i));
            return result;
        }
    }

    result = new QTreeWidgetItem_alarm__account(tree_widget_item, account);
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
            result->add_exec(confirm_info, exec);
            return result;
        }
    }

    result = new QTreeWidgetItem_exec(tree_widget_item, confirm_info, exec);
    result->setText(0, key);
    return result;
}

QTreeWidgetItem_exec__Product*  getn_key_item_exec__Product(QTreeWidgetItem* tree_widget_item, const QString& key, const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
{
    QTreeWidgetItem_exec__Product *result=0;
    for(int i=0; i<tree_widget_item->childCount(); ++i)
    {
        if(tree_widget_item->child(i)->text(0)  == key)
        {
            result = static_cast<QTreeWidgetItem_exec__Product *>(tree_widget_item->child(i));
            result->add_exec(confirm_info, exec);
            return result;
        }
    }

    result = new QTreeWidgetItem_exec__Product(tree_widget_item, confirm_info, exec);
    result->setText(0, key);
    return result;
}
};   //  namespace {


void WExecsReport::on_new_execution(const mtk::trd::msg::CF_XX&  confirm_info, const mtk::trd::msg::sub_exec_conf& exec)
{
    //  NO CALENDAR SPREAD
    if( confirm_info.invariant.product_code.market == "M3"     &&  confirm_info.invariant.product_code.product[0] != 'F')
        return;
    if( confirm_info.invariant.product_code.market == "EU"     &&  confirm_info.invariant.product_code.product.find('-') != std::string::npos)
        return;

    if( mtk::admin::is_production() == false  &&   confirm_info.invariant.product_code.market=="MARKET"  &&  confirm_info.invariant.product_code.product[0] == 'L')
        return;

    auto client_item   = get0_key_item                  (ui->treeWidget, QLatin1String(confirm_info.invariant.account.client_code.c_str()));
    auto account_item  = getn_key_item_alarm            (client_item,    QLatin1String(confirm_info.invariant.account.name.c_str()),             confirm_info.invariant.account);
    auto market_item   = getn_key_item                  (account_item,   QLatin1String(confirm_info.invariant.product_code.market.c_str()));
    //auto product_item  = getn_key_item_exec           (market_item,    QLatin1String(confirm_info.invariant.product_code.product.c_str()),     confirm_info, exec);
    auto product_item  = getn_key_item_exec__Product    (market_item,    QLatin1String(confirm_info.invariant.product_code.product.c_str()),     confirm_info, exec);
                         getn_key_item_exec             (product_item,   qtmisc::fn_as_QString(exec.price),                                      confirm_info, exec);
}


void WExecsReport::on_grant_received(const mtk::trd::account::msg::sub_grant&  grant)
{
    auto client_item   = get0_key_item                  (ui->treeWidget, QLatin1String(grant.key.account.client_code.c_str()));
    /**/                 getn_key_item_alarm            (client_item,    QLatin1String(grant.key.account.name.c_str()),  grant.key.account);
}


void WExecsReport::slot_itemChanged ( QTreeWidgetItem * item, int column )
{
    if(column == 7)
    {
        QTreeWidgetItem_alarm__account* item_alarm_account =  dynamic_cast<QTreeWidgetItem_alarm__account*>(item);
        if(item_alarm_account != 0)
        {
            bool oldState = ui->treeWidget->blockSignals(true);
            item_alarm_account->set_alarm(mtk::Double(item->text(7).remove(QLocale::system().groupSeparator()).toDouble()));

            if(item->text(7) == QLatin1String("0")  ||  item->text(7) == QLatin1String(""))
                item->setText(7, QLatin1String(""));
            else
            {
                double val =  item->text(7).remove(QLocale::system().groupSeparator()).toDouble();
                item_alarm_account->setText(7, QLocale::system().toString(val, 'f', 0));
            }
            ui->treeWidget->blockSignals(oldState);
        }
    }
}


void WExecsReport::slot_itemDoubleClicked ( QTreeWidgetItem * item, int column )
{
    QTreeWidgetItem_alarm__account*  item_alarm_account = dynamic_cast<QTreeWidgetItem_alarm__account*>(item);
    if(item_alarm_account != 0)
    {
        if(column != 7)
            item_alarm_account->setExpanded(!item_alarm_account->isExpanded());
        else if (column == 7)
            item_alarm_account->set_editing_alarm();
    }
}

