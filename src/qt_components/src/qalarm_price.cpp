#include "qalarm_price.h"

#include <QVBoxLayout>
#include <QHeaderView>
#include <QAction>
#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMessageBox>

#include <QPen>
#include <QPainter>
#include <QApplication>
#include <QMenu>
#include <QMessageBox>


#include <iostream>
#include <iomanip>

#include "components/trading/trd_cli_ord_book.h"
#include "qt_components/src/qmtk_misc.h"
#include "qt_components/src/qcommontabledelegate.h"
#include "qt_components/src/qlocaledoublespinbox.h"
#include "components/trading/accounts/account_manager_cli.h"

#include "support/vector.hpp"
#include "yaml/yaml.h"

#include "wusermessage.h"






namespace {
    const char*   VERSION = "2012-03-01";

    const char*   MODIFICATIONS =
                        "           2012-03-01     first version\n";


    static int  col_count =3;

    void command_version(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(MTK_SS(__FILE__ << ":  " << VERSION));
    }

    void command_modifications  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(__FILE__);
        response_lines.push_back(".......................................");
        response_lines.push_back(MODIFICATIONS);
    }


    void register_global_commands (void)
    {
        mtk::admin::register_command("__GLOBAL__",  "ver",   "")->connect(command_version);
        mtk::admin::register_command("__GLOBAL__",  "modifs",   "")->connect(command_modifications);
    }

    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)

}       //  anonymous namespace  to register "static" commnads











int marginal_in_table_alarm::alarm_counter = 0;


namespace {


    QColor  color_product = qtmisc::mtk_color_header;
    const QColor  color_cell   =  Qt::white;//QColor(240,245,250);


    class QTableWidgetItemProduct : public QTableWidgetItem
    {
    public:
        QTableWidgetItemProduct (const mtk::msg::sub_product_code&  _product_code, int _id) : QTableWidgetItem(), product_code(_product_code), id(_id) {}
        mtk::msg::sub_product_code  product_code;
        const int id;
    };



};  //namespace  {




qLocaleDoubleSpinBox_delegate::qLocaleDoubleSpinBox_delegate(QObject *parent)
        : QItemDelegate(parent), decimals(3), increment(1)
{
}



QWidget *qLocaleDoubleSpinBox_delegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    qLocaleDoubleSpinBox *editor = new qLocaleDoubleSpinBox(parent);
    editor->setMinimum(-100000);
    editor->setMaximum(100000);
    editor->setDecimals(decimals);
    editor->setSingleStep(increment / pow(10, decimals));

    return editor;
}

void qLocaleDoubleSpinBox_delegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    double value = QLocale::system().toDouble(index.model()->data(index, Qt::EditRole).toString());

    qLocaleDoubleSpinBox *spinBox = static_cast<qLocaleDoubleSpinBox*>(editor);
    spinBox->setValue(value);
}


void qLocaleDoubleSpinBox_delegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    qLocaleDoubleSpinBox *spinBox = static_cast<qLocaleDoubleSpinBox*>(editor);
    if(spinBox->text().size()>0)
    {
        spinBox->interpretText();
        double value = spinBox->value();

        //model->setData(index, value, Qt::EditRole);
        model->setData(index, QLocale::system().toString(value, 'f', decimals), Qt::EditRole);
    }
    else
        model->setData(index, QLatin1String(""), Qt::EditRole);
}


void qLocaleDoubleSpinBox_delegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}



void qLocaleDoubleSpinBox_delegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QTableAlarmPrice* parent = static_cast<QTableAlarmPrice*>(this->parent());
    parent->paint_delegate->paint(painter, option, index);
}














QAlarmPrice::QAlarmPrice(QWidget *parent) :
    mtkContainerWidget(parent),
    table_alarms(new QTableAlarmPrice(this))
{
    this->setGeometry(QRect(5, 5, 100*4+150+2*5-2, 150-2));
    this->setAcceptDrops(true);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(5,5,5,5);
    this->setLayout(layout);
    layout->addWidget(table_alarms);

    this->inserting_components_ended();
}

QAlarmPrice::~QAlarmPrice()
{
}



QTableAlarmPrice::QTableAlarmPrice(QWidget *parent)
    : QTableWidget(parent), startPos(-1,-1),
      action_remove_product(0),
      showing_menu(false),
      paint_delegate(new QCommonTableDelegate(this, true)),
      price_editor(new qLocaleDoubleSpinBox_delegate(this))
{
    this->setAcceptDrops(true);
    this->setItemDelegateForColumn(1, price_editor);

    setItemDelegate(paint_delegate);
    //setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setShowGrid(false);

    {
        setRowCount(0);
        verticalHeader()->setVisible(false);
        horizontalHeader()->setVisible(true);
        verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
        horizontalHeader()->resizeSection(0, 150);
        slot_sectionMoved(0,0,0);


        setColumnCount(col_count);
        #define QMARG_INIT_HEADER_ITEM(__COLUMN__, __TEXT__) \
        {   \
            item = new QTableWidgetItem(); \
            item->setText(__TEXT__);   \
            setHorizontalHeaderItem(__COLUMN__, item);   \
        }

        {
            QTableWidgetItem *item=0;
            QMARG_INIT_HEADER_ITEM(0, tr("Alarms"))
            QMARG_INIT_HEADER_ITEM(1, tr("Price")    )
            QMARG_INIT_HEADER_ITEM(2, tr("Message")    )
        }
        horizontalHeader()->setMovable(true);
    }
    this->setFrameShape(QFrame::NoFrame);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(this->horizontalHeader(), SIGNAL(sectionMoved(int,int,int)), this, SLOT(slot_sectionMoved(int,int,int)));

    action_remove_product = new QAction(tr("remove alarm"), this);
    //action_remove_product->setShortcut(Qt::Key_Delete);
    connect(action_remove_product, SIGNAL(triggered()), this, SLOT(slot_remove_current_row()));

    this->addAction(action_remove_product);
    this->disable_actions();
}




void marginal_in_table_alarm::normalize_last_price_cofigured(double price)
{
    if(price_manager.isValid())
    {
        mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>  n_last_mk_execs_ticker = price_manager->get_last_mk_execs_ticker();
        if(n_last_mk_execs_ticker.HasValue() == true)
        {
            mtk::prices::msg::sub_last_mk_execs_ticker  last_mk_execs_ticker = n_last_mk_execs_ticker.Get();

            tw_last_configured->setText(QLocale::system().toString(price, 'f', last_mk_execs_ticker.last_price.GetExt().GetDec()));
        }
        else tw_last_configured->setText(QLocale::system().toString(price, 'f', 3));
    }
    else
        tw_last_configured->setText(QLocale::system().toString(price, 'f', 3));
}


marginal_in_table_alarm::marginal_in_table_alarm(QTableWidget* _table_widget, const mtk::msg::sub_product_code& product_code, double price, const QString& description, int row)
    : status(non_initialized), id(++alarm_counter), table_widget(_table_widget),  configured_price(mtk::Double::InvalidValue()), first_maket__configured_last_sign(0), alarm_is_checked(false)
{
    tw_product          = new QTableWidgetItemProduct(product_code, this->id);
    tw_last_configured  = new QTableWidgetItem();
    tw_description      = new QTableWidgetItem();

    if (row>=0 && row<table_widget->rowCount())
        table_widget->insertRow(row);
    else
    {
        table_widget->setRowCount(table_widget->rowCount()+1);
        row = table_widget->rowCount()-1;
    }
    table_widget->setItem(row, 0, tw_product);
    table_widget->setItem(row, 1, tw_last_configured);
    table_widget->setItem(row, 2, tw_description);


    tw_product->setText(QLatin1String(MTK_SS(product_code.market << "." << product_code.product).c_str()));

    tw_last_configured->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    tw_last_configured->setText(QLocale::system().toString(price, 'f', 3));


    tw_description->setText(description);
    tw_description->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    price_manager = mtk::make_cptr(new mtk::prices::price_manager(product_code));
    MTK_CONNECT_THIS(price_manager->signal_last_mk_execs_ticker, on_last_mk_execs_ticker_msg);

    connect(table_widget, SIGNAL(cellChanged(int,int)), this, SLOT(slot_cell_changed(int,int)));
    connect(table_widget, SIGNAL(itemSelectionChanged()), this, SLOT(slot_item_selection_changed()));
    QTableAlarmPrice*  tap = static_cast<QTableAlarmPrice*>(table_widget);
    connect(this, SIGNAL(signal_modif_decimals_increment_for_price_editor(int,int)), tap, SLOT(slot_modif_price_editor(int,int)));

    this->set_status(non_initialized);
    if(price_manager->get_last_mk_execs_ticker().HasValue())
        this->on_last_mk_execs_ticker_msg(product_code, price_manager->get_last_mk_execs_ticker().Get());
}




void  marginal_in_table_alarm::set_non_initialized(void)
{
    initialize_paint();

    tw_product->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
    tw_product->setCheckState(Qt::Unchecked);
    tw_product->setBackgroundColor(qtmisc::mtk_color_header);
    QBrush foreground (tw_product->foreground());
    foreground.setColor(Qt::darkGray);
    tw_product->setForeground(foreground);
    configured_price = mtk::Double::InvalidValue();
    first_maket__configured_last_sign = 0;

    tw_description->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
    tw_product->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
    tw_product->setCheckState(Qt::Unchecked);
    tw_last_configured->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
    alarm_is_checked = false;
    status = non_initialized;
}

void  marginal_in_table_alarm::set_ready_to_activate(void)
{
    if(price_manager.isValid() == false  ||  price_manager->get_last_mk_execs_ticker().HasValue()  == false)
        this->set_non_initialized();


    normalize_last_price_cofigured(QLocale::system().toDouble(tw_last_configured->text()));

    if(status == activated)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS("auto::alarm::" << id << "::deactivated"), MTK_SS("product:"  <<  tw_product->text().toStdString() << "  sign:" << first_maket__configured_last_sign  <<  "  price:"  <<  configured_price
                                                                            << "  market_price:" << price_manager->get_last_mk_execs_ticker().Get().last_price), mtk::alPriorWarning));
    }

    initialize_paint();
    mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>  last_mk_execs_ticker  =  price_manager->get_last_mk_execs_ticker();
    if(last_mk_execs_ticker.HasValue() == false)
        this->set_non_initialized();
    else
    {
        configured_price = mtk::Double::InvalidValue();
        first_maket__configured_last_sign = 0;
        alarm_is_checked = false;
    }


    tw_product->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable  | Qt::ItemIsEnabled);
    tw_product->setCheckState(Qt::Unchecked);
    tw_description->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
    tw_last_configured->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);


    status = ready_to_activate;
}

void  marginal_in_table_alarm::set_activated(void)
{
    initialize_paint();

    if(tw_description->text() == QLatin1String(""))
    {
        tw_product->setCheckState(Qt::Unchecked);
        QMessageBox::warning(this->table_widget, QLatin1String("CimdTrade"), tr("You have to write a message to activate an alarm"), QMessageBox::Ok);
        return;
    }

    mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>  n_last_mk_execs_ticker = price_manager->get_last_mk_execs_ticker();
    if(n_last_mk_execs_ticker.HasValue() == false)
    {
        tw_product->setCheckState(Qt::Unchecked);
        QMessageBox::warning(this->table_widget, QLatin1String("CimdTrade"), tr("Missing last price."), QMessageBox::Ok);
        return;
    }

    mtk::Double  dconfigured_last = QLocale::system().toDouble(tw_last_configured->text());
    mtk::Double abs_var =fabs(((n_last_mk_execs_ticker.Get().last_price.GetDouble()).get2() - dconfigured_last.get2()) / dconfigured_last.get2());
    if(abs_var > mtk::Double(0.2))
    {
        tw_product->setCheckState(Qt::Unchecked);
        QMessageBox::warning(this->table_widget, QLatin1String("CimdTrade"), tr("Configured price too far  ") +
                                            QLatin1String(MTK_SS(n_last_mk_execs_ticker.Get().last_price.GetDouble() << " " << QLocale::system().toDouble(tw_last_configured->text())).c_str()), QMessageBox::Ok);
        return;
    }

    if(n_last_mk_execs_ticker.Get().last_price.GetDouble() ==  QLocale::system().toDouble(tw_last_configured->text()))
    {
        tw_product->setCheckState(Qt::Unchecked);
        QMessageBox::warning(this->table_widget, QLatin1String("CimdTrade"), tr("Cannot activate the alarm. Market price and alarm price are equal"), QMessageBox::Ok);
        return;
    }


    configured_price = QLocale::system().toDouble(tw_last_configured->text());
    if(price_manager.isValid() == false  ||  price_manager->get_last_mk_execs_ticker().HasValue()==false)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "activating", "missing price manager or not received price", mtk::alPriorError));
        this->set_non_initialized();
    }


    if(price_manager->get_last_mk_execs_ticker().Get().last_price.GetDouble() - configured_price  <= mtk::Double(0.))
        first_maket__configured_last_sign = -1;
    else
        first_maket__configured_last_sign = 1;

    alarm_is_checked= true;

    tw_product->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsSelectable  | Qt::ItemIsEnabled);
    tw_product->setCheckState(Qt::Checked);
    tw_description->setFlags(0);
    tw_last_configured->setFlags(0);
    status = activated;

    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS("auto::alarm::" << id << "::activated"), MTK_SS("product:"  <<  tw_product->text().toStdString()  << "  sign:" << first_maket__configured_last_sign  <<  "  price:"  <<  configured_price
                                                                        << "  market_price:" << price_manager->get_last_mk_execs_ticker().Get().last_price), mtk::alPriorWarning));

}

void  marginal_in_table_alarm::set_ended (void)
{
    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS("auto::alarm::" << id << "::triggered"), MTK_SS("product:"  <<  tw_product->text().toStdString() << "  sign:" << first_maket__configured_last_sign  <<  "  price:"  <<  configured_price
                                                                        << "  market_price:" << price_manager->get_last_mk_execs_ticker().Get().last_price), mtk::alPriorWarning));
    tw_last_configured->setBackgroundColor(Qt::red);
    tw_description->setBackgroundColor(Qt::red);
    QBrush foreground (tw_last_configured->foreground());
    foreground.setColor(Qt::white);
    tw_last_configured->setForeground(foreground);
    tw_description->setForeground(foreground);
    configured_price = mtk::Double::InvalidValue();
    first_maket__configured_last_sign = 0;
    alarm_is_checked = true;
    wUserMessage::show_message(tw_description->text());

    status = ended;
}


void  marginal_in_table_alarm::set_status(en_status  new_status)
{
    switch(status)
    {
    case  non_initialized:      //  current status
            switch(new_status)
            {
                case  non_initialized:
                    //mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "alarm_set_status", "non_initialized -> non_initialized", mtk::alPriorError));
                    set_non_initialized();
                    break;
                case  ready_to_activate:
                    set_ready_to_activate();
                    break;
                case  activated:
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "alarm_set_status", "non_initialized -> activated", mtk::alPriorError));
                    set_non_initialized();
                    break;
                case  ended:
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "alarm_set_status", "non_initialized -> ended", mtk::alPriorError));
                    set_non_initialized();
                    break;
            }
            break;
        case  ready_to_activate:    //  current status
            switch(new_status)
            {
                case  non_initialized:
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "alarm_set_status", "ready_to_activate -> non_initialized", mtk::alPriorError));
                    set_non_initialized();
                    break;
                case  ready_to_activate:
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "alarm_set_status", "ready_to_activate -> ready_to_activate", mtk::alPriorError));
                    break;
                case  activated:
                    set_activated();
                    break;
                case  ended:
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "alarm_set_status", "non_initialized -> ended", mtk::alPriorError));
                    set_non_initialized();
                    break;
            }
            break;
        case  activated:    //  current status
            switch(new_status)
            {
                case  non_initialized:
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "alarm_set_status", "activated -> non_initialized", mtk::alPriorError));
                    set_non_initialized();
                    break;
                case  ready_to_activate:
                    set_ready_to_activate();
                    break;
                case  activated:
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "alarm_set_status", "activated -> activated", mtk::alPriorError));
                    break;
                case  ended:
                    set_ended();
                    break;
            }
            break;
        case  ended:    //  current status
            switch(new_status)
            {
                case  non_initialized:
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "alarm_set_status", "ended -> non_initialized", mtk::alPriorError));
                    set_non_initialized();
                    break;
                case  ready_to_activate:
                    set_ready_to_activate();
                    break;
                case  activated:
                    set_activated();
                    break;
                case  ended:
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "alarm_set_status", "ended -> ended", mtk::alPriorError));
                    break;
            }
            break;
    }
}



void     marginal_in_table_alarm::initialize_paint(void)
{
    {
        QFont font(tw_product->font());
        font.setBold(true);
        tw_product->setFont(font);
        tw_product->setBackgroundColor(qtmisc::mtk_color_header);
        QBrush foreground (tw_product->foreground());
        foreground.setColor(QColor(30,0,100));
        tw_product->setForeground(foreground);
    }

    {
        tw_last_configured->setBackgroundColor(Qt::white);
        QFont font(tw_last_configured->font());
        font.setBold(true);
        tw_last_configured->setFont(font);
        tw_last_configured->setBackgroundColor(color_cell);
        QBrush foreground (tw_last_configured->foreground());
        foreground.setColor(Qt::black);
        tw_last_configured->setForeground(foreground);
    }
    {
        tw_description->setBackgroundColor(Qt::white);
        QFont font(tw_description->font());
        //font.setBold(true);
        tw_description->setFont(font);
        tw_description->setBackgroundColor(color_cell);
        QBrush foreground (tw_last_configured->foreground());
        foreground.setColor(Qt::black);
        tw_description->setForeground(foreground);
    }
}






/*
void  marginal_in_table_alarm::mark_is_close (bool is_close)
{
    QColor color(Qt::red);
    if(is_close)
      color = color.lighter();
    tw_last_configured->setBackgroundColor(color);
    tw_description->setBackgroundColor(color);
}
*/






void marginal_in_table_alarm::on_last_mk_execs_ticker_msg(const mtk::msg::sub_product_code& /*pc*/, const mtk::prices::msg::sub_last_mk_execs_ticker& last_mk_execs_ticker)
{
    switch(status)
    {
        case  non_initialized:
            set_status(ready_to_activate);
            break;
        case  ready_to_activate:
            break;
        case  activated:
            if     (last_mk_execs_ticker.max_last_price.GetDouble() - configured_price  <= mtk::Double(0.)  &&  first_maket__configured_last_sign>0)
                this->set_status(ended);
            else if(last_mk_execs_ticker.min_last_price.GetDouble() - configured_price  >= mtk::Double(0.)  &&  first_maket__configured_last_sign<0)
                this->set_status(ended);
            /*
            else
            {
                if     ((last_mk_execs_ticker.max_last_price - mtk::fnTicks(2)).GetDouble() - configured_price  <= 0  &&  first_maket__configured_last_sign>0)
                            this->mark_is_close();
                else if((last_mk_execs_ticker.min_last_price + mtk::fnTicks(2)).GetDouble() - configured_price  >= 0  &&  first_maket__configured_last_sign<0)
                           this->mark_is_close();
                else this->mark_is_close(false);
            }
            */
            break;
        case  ended:
            break;
    }
}








void QTableAlarmPrice::insert_alarm(const mtk::msg::sub_product_code& product_code, double price, const QString& description, int row)
{
    alarms.push_back(mtk::make_cptr(new marginal_in_table_alarm(this, product_code, price, description, row)));
}

void QTableAlarmPrice::add_alarm(const mtk::msg::sub_product_code& product_code, double price, const QString&  description)
{
    alarms.push_back(mtk::make_cptr(new marginal_in_table_alarm(this, product_code, price, description)));
}

void QTableAlarmPrice::dragEnterEvent(QDragEnterEvent *event)
{
    QTableWidget::dragEnterEvent(event);
    if(qobject_cast<QTableAlarmPrice*>(event->source())!=0)
        event->setDropAction(Qt::MoveAction);
    else
        event->setDropAction(Qt::CopyAction);
    event->accept();
}

void QTableAlarmPrice::dragMoveEvent(QDragMoveEvent *event)
{
    QTableWidget::dragMoveEvent(event);
    if(qobject_cast<QTableAlarmPrice*>(event->source())!=0)
        event->setDropAction(Qt::MoveAction);
    else
        event->setDropAction(Qt::CopyAction);
    event->accept();
}


void QTableAlarmPrice::dropEvent(QDropEvent *event)
{
    //  TODO
    QString sprice = qtmisc::get_property_value(event, QLatin1String("alarm_price"));
    QString description = qtmisc::get_property_value(event, QLatin1String("alarm_description"));
    insert_alarm(qtmisc::get_product_code(event), QLocale::system().toDouble(sprice), description, rowAt(event->pos().y()));
    if(qobject_cast<QTableAlarmPrice*>(event->source())!=0)
        event->setDropAction(Qt::MoveAction);
    else
        event->setDropAction(Qt::CopyAction);
    event->accept();

    int current_row = rowAt(event->pos().y());
    if (current_row < 0)
        current_row = this->rowCount()-1;
    this->setCurrentCell(current_row, 0);
    this->setFocus(Qt::OtherFocusReason);
}





void QTableAlarmPrice::mousePressEvent(QMouseEvent *event)
{
    QWidget* w = dynamic_cast<QWidget*>(this->parent());
    if(w)       w->raise();
    if(columnAt(event->pos().x())>=0  &&  rowAt(event->pos().y())>=0)
    {
        startPos = event->pos();
        QTableWidgetItemProduct* i = dynamic_cast<QTableWidgetItemProduct*>(this->item(rowAt(startPos.y()), 0));
        if (i)          startDragId = i->id;
    }
    QTableWidget::mousePressEvent(event);
}

void QTableAlarmPrice::mouseReleaseEvent(QMouseEvent * event)
{
    startPos = QPoint(-1,-1);
    QTableWidget::mouseReleaseEvent(event);
}

void QTableAlarmPrice::mouseMoveEvent(QMouseEvent *event)
{
    QTableWidget::mouseMoveEvent(event);

    if (rowAt(event->pos().y())<0)      return;

    if ((event->buttons() & Qt::LeftButton)  &&  startPos.x()>=0  &&  startPos.y()>=0)
    {
        int distance = (event->pos() - startPos).manhattanLength();
        if (this->currentRow() >=0  &&  distance >= QApplication::startDragDistance()+5)
            start_drag();
    }
}

void QTableAlarmPrice::start_drag(void)
{
    QMimeData* mimeData = new QMimeData;
    int row = rowAt(startPos.y());
    int column =columnAt(startPos.x());
    QTableWidgetItemProduct* item = dynamic_cast<QTableWidgetItemProduct*>(this->item(row, column));
    if(this->item(row, 0)->checkState() == Qt::Checked)
    {
        QMessageBox::warning(this, QLatin1String("CimdTrade"), tr("You cannot move an activated alarm."), QMessageBox::Ok);
        return;
    }

    if (item)
    {
        mtk::list<mtk::tuple<QString, QString> >  ext_info;
        ext_info.push_back(mtk::make_tuple(QString(QLatin1String("alarm_price")),  this->item(row, 1)->text()));
        ext_info.push_back(mtk::make_tuple(QString(QLatin1String("alarm_description")),  this->item(row, 2)->text()));
        mimeData->setText(qtmisc::dragProductText__ext(item->product_code, ext_info));
        QDrag* drag = new QDrag(this);
        drag->setMimeData(mimeData);

        //if (this->currentRow()!=this->rowCount()-1)
        {
            QRect rect(this->visualItemRect(this->item(this->currentRow(), 0)));
            int oldheight = rect.height();
            QPixmap pixmap (rect.size());
            rect.setY(rect.y()+horizontalHeader()->height());
            rect.setHeight(oldheight);
            this->render(&pixmap, QPoint(0, 0), rect);
            drag->setPixmap(pixmap);
        }

        if(drag->exec(Qt::CopyAction | Qt::MoveAction) == Qt::MoveAction)
            remove_row(startDragId);
    }
}

void QTableAlarmPrice::remove_row(int id)
{
    mtk::list< mtk::CountPtr<marginal_in_table_alarm> >::iterator it = alarms.begin();
    while (it != alarms.end())
    {
        if ((*it)->id == id)
        {
            alarms.erase(it);
            break;
        }
        ++it;
    }

    for(int i=0; i<rowCount();++i)
    {
        QTableWidgetItemProduct* item = dynamic_cast<QTableWidgetItemProduct*>(this->item(i, 0));
        if(item  && item->id == id)
        {
            removeRow(i);
            break;
        }
    }
}


void QTableAlarmPrice::contextMenuEvent ( QContextMenuEvent * event )
{
    if (rowAt(event->pos().y())<0)      return;

    if (currentRow() <0)        return;

    QMenu menu(this);
    menu.addAction(action_remove_product);

    showing_menu = true;
    menu.exec(event->globalPos());
    showing_menu = false;
    this->setFocus();
    enable_actions();
}


void QTableAlarmPrice::keyPressEvent ( QKeyEvent * event )
{
    if(event->key() == Qt::Key_Enter  ||  event->key() == Qt::Key_Return)
        this->editItem(this->currentItem());
    else if(event->key() == Qt::Key_Delete  &&  this->currentColumn() != 0)
    {
        this->editItem(this->currentItem());
    }
    if(event->key() == Qt::Key_Delete  &&  this->currentColumn() == 0)
        this->slot_remove_current_row();
    else
        QTableWidget::keyPressEvent(event);
}



void QTableAlarmPrice::disable_actions(void)
{
    if(showing_menu==false)
        action_remove_product->setEnabled(false);
}

void QTableAlarmPrice::enable_actions(void)
{
    action_remove_product->setEnabled(true);
}


void QTableAlarmPrice::slot_remove_current_row(void)
{
    QTableWidgetItemProduct* i = dynamic_cast<QTableWidgetItemProduct*>(this->item(this->currentRow(), 0));
    if (i)
    {
        paint_delegate->keep_focus_paint(true);
        try
        {
            if(QMessageBox::warning(this, QLatin1String("CimdTrade"), tr("Do you want to remove the current alarm from this table?"), QMessageBox::Ok, QMessageBox::Cancel)==QMessageBox::Ok)
                this->remove_row(i->id);
        }
        catch(...)
        {
            paint_delegate->keep_focus_paint(false);
            throw;
        }
        paint_delegate->keep_focus_paint(false);
    }
}


mtk::msg::sub_product_code   QTableAlarmPrice::get_current_product_code(void)
{
    QTableWidgetItemProduct* item = dynamic_cast<QTableWidgetItemProduct*>(this->item(currentRow(), 0));
    if (item)
    {
        mtk::msg::sub_product_code product_code = item->product_code;
        if (mtk::msg::is_valid(product_code)==false)
            return mtk::msg::sub_product_code("", "");
        else
            return product_code;
    }
    return mtk::msg::sub_product_code("", "");
}





YAML::Emitter& operator << (YAML::Emitter& out, const QTableAlarmPrice& m)
{
    out     << YAML::BeginMap;

    //  writing alarms
    out << YAML::Key   <<  "alarms"  << YAML::Value
    << YAML::BeginSeq;

        for(int i=0; i<m.rowCount(); ++i)
        {
            QTableWidgetItemProduct* iproduct = dynamic_cast<QTableWidgetItemProduct*>(m.item(i, 0));
            if(iproduct!=0)
            {
                out << YAML::BeginMap;
                        out << YAML::Key   <<  "product_name"  << YAML::Value << iproduct->product_code;
                        out << YAML::Key   <<  "price"  << YAML::Value << int(QLocale::system().toDouble(m.item(i,1)->text()) *1000);
                        out << YAML::Key   <<  "description"  << YAML::Value << m.item(i,2)->text().toStdString();
                out << YAML::EndMap;
            }
        }
    out << YAML::EndSeq;
    //  end products

    //  writing sections sizes
    out << YAML::Key   <<  "sect_sizes"
            << YAML::Value << YAML::Flow  << YAML::BeginSeq;
    for(int i=0; i<m.horizontalHeader()->count()-1; ++i)
    {
        out << m.horizontalHeader()->sectionSize(i);
    }
    out << YAML::EndSeq;
    //  writing sections sizes

    out << YAML::EndMap;
    return out;
}

void             operator >> (const YAML::Node&   node,        QTableAlarmPrice& m)
{
    for(unsigned i=0; i< node["alarms"].size(); ++i)
    {
        mtk::msg::sub_product_code pc = mtk::msg::__internal_get_default((mtk::msg::sub_product_code*)0);
        std::string  price;
        std::string  description;
        node["alarms"][i]["product_name"] >> pc;
        node["alarms"][i]["price"] >> price;
        node["alarms"][i]["description"] >> description;
        if(description == "~")
            description = "";
        m.add_alarm(pc, mtk::s_TRY_stod(price, 0)._0 / 1000., QLatin1String(description.c_str()));
    }
    for(unsigned i=0; i< node["sect_sizes"].size(); ++i)
    {
        int sect_size;
        node["sect_sizes"][i] >> sect_size;
        m.horizontalHeader()->resizeSection(i, sect_size);
    }
    m.slot_sectionMoved(0,0,0);
}



YAML::Emitter& operator << (YAML::Emitter& out, const QAlarmPrice& m)
{
    //if(m.table_alarms->rowCount() == 0)      return out;


    out     << YAML::BeginMap;

    //  writing component
    out << YAML::Key   <<  "component" << YAML::Value << static_cast<const mtkContainerWidget&>(m);
    //  end component

    //  writing QTableAlarmPrice
    if(m.table_alarms)
        out << YAML::Key   <<  "QTableAlarmPrice"  << YAML::Value   << *(m.table_alarms);
    //  end QTableAlarmPrice


    out << YAML::EndMap;

    return out;
}


void             operator >> (const YAML::Node&   node,       QAlarmPrice& m)
{
    node["component"] >> static_cast<mtkContainerWidget&>(m);
    node["QTableAlarmPrice"] >>  (*m.table_alarms);
}



void QTableAlarmPrice::slot_sectionMoved ( int /*logicalIndex*/, int /*oldVisualIndex*/, int /*newVisualIndex*/ )
{
    this->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
    horizontalHeader()->resizeSection(horizontalHeader()->logicalIndex(horizontalHeader()->count()-1), 10);
    this->horizontalHeader()->setResizeMode(horizontalHeader()->logicalIndex(horizontalHeader()->count()-1), QHeaderView::Fixed);
    horizontalHeader()->setStretchLastSection(true);
}



void QTableAlarmPrice::focusOutEvent(QFocusEvent *e)
{
    this->update();
    disable_actions();
    QTableWidget::focusOutEvent(e);
}

void QTableAlarmPrice::focusInEvent (QFocusEvent *e)
{
    this->update();
    enable_actions();
    QTableWidget::focusInEvent(e);
}


void marginal_in_table_alarm::slot_cell_changed (int row, int column)
{
    if(column == 0)
    {
        if(tw_product->row() == row)
        {
            if(tw_product->checkState()  ==  Qt::Checked   &&      alarm_is_checked==false)
            {
                    this->set_status(activated);
            }
            else  if(tw_product->checkState()  !=  Qt::Checked   &&      alarm_is_checked==true)
            {
                    this->set_status(ready_to_activate);
            }
        }
    }
    if(column==1  &&  tw_last_configured->row() == row)
    {
        normalize_last_price_cofigured(QLocale::system().toDouble(tw_last_configured->text()));
    }
}

void marginal_in_table_alarm::slot_item_selection_changed (void)
{

    int column = table_widget->currentColumn();
    int row = table_widget->currentRow();
    if(column==1  &&  tw_product->row() == row)
    {
        mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>  n_last_mk_execs_ticker = price_manager->get_last_mk_execs_ticker();
        if(n_last_mk_execs_ticker.HasValue() == true)
        {
            mtk::prices::msg::sub_last_mk_execs_ticker  last_mk_execs_ticker = n_last_mk_execs_ticker.Get();
            signal_modif_decimals_increment_for_price_editor(last_mk_execs_ticker.last_price.GetExt().GetDec(), last_mk_execs_ticker.last_price.GetExt().GetInc());
        }
        else
            signal_modif_decimals_increment_for_price_editor(3, 1);
    }
}


void QTableAlarmPrice::slot_modif_price_editor(int decimals, int increment)
{
    price_editor->set_decinc(decimals, increment);
}
