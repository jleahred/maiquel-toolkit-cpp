#include "qorderbook.h"

#include <QTableWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <QHeaderView>
#include <QPushButton>
#include <QMessageBox>

#include "components/admin/admin.h"
#include "qeditorder.h"
#include "qorder_table.h"
#include "qexecs_table.h"
#include "whistoric_order.h"




namespace {
    const char*   VERSION = "2011-03-16";

    const char*   MODIFICATIONS =
                        "           2011-03-16     first version\n";


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



void on_request_with_user_check_ls(mtk::trd::msg::RQ_XX_LS& rq, bool& canceled, bool agressive)
{
    QEditOrder eo(rq, agressive);
    if (eo.exec())
    {
        rq = eo.get_request_ls();
    }
    else canceled =true;
}

void on_request_with_user_check_mk(mtk::trd::msg::RQ_XX_MK& rq, bool& canceled, bool agressive)
{
    QEditOrder eo(rq, agressive);
    if (eo.exec())
    {
        rq = eo.get_request_mk();
    }
    else canceled =true;
}



QOrderBook::QOrderBook(QWidget *parent) :
    QWidget(parent),
    table_executions(new QExecsTable(this)),
    historic_order_window(new whistoric_order(this))
{
    historic_order_window->setAttribute(Qt::WA_ShowWithoutActivating);
    //historic_order_window->setWindowFlags(Qt::WindowStaysOnTopHint);
    //table_executions->setMinimumWidth(300);
    table_executions->setMinimumWidth(30);

    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setChildrenCollapsible(false);
    tab_widget = new QTabWidget(this);
    tab_widget->setMovable(true);
    tab_widget->setTabPosition(QTabWidget::South);

    //tab_widget->setTabsClosable(true);
    connect(tab_widget, SIGNAL(currentChanged(int)), SLOT(slot_tab_index_changed(int)));

    {
        QWidget* w = new QWidget(this);
        QHBoxLayout *hl= new QHBoxLayout(w);
        hl->setSpacing(0);
        hl->setContentsMargins(0, 0, 0, 0);

        close_button = new QPushButton(QIcon(QLatin1String(":/small_icons/image_close")), QLatin1String(""), w);
        connect(close_button, SIGNAL(clicked()), this, SLOT(slot_request_close_tab()));
        close_button->setFlat(true);
        close_button->setEnabled(false);
        close_button->setToolTip(tr("Close selected tab"));
        hl->addWidget(close_button);
        new_button = new QPushButton(QIcon(QLatin1String(":/small_icons/new")), QLatin1String(""), w);
        connect(new_button, SIGNAL(clicked()), this, SLOT(slot_request_new_tab()));
        new_button->setFlat(true);
        hl->addWidget(new_button);
        new_button->setToolTip(tr("Create a new tab"));

        tab_widget->setCornerWidget(w, Qt::TopLeftCorner);
    }

    {
        QWidget* w = new QWidget(this);
        QHBoxLayout *hl= new QHBoxLayout(w);
        hl->setSpacing(0);
        hl->setContentsMargins(0, 0, 0, 0);

        filter_button = new QPushButton(QIcon(QLatin1String(":/small_icons/filter")), QLatin1String(""), w);
        connect(filter_button, SIGNAL(clicked()), this, SLOT(slot_request_showfilter()));
        filter_button->setFlat(true);
        filter_button->setCheckable(true);
        filter_button->setToolTip(tr("Show/Hide the filter aplied on this tab"));
        hl->addWidget(filter_button);

        tab_widget->setCornerWidget(w);
    }
    create_new_tab();

    splitter->addWidget(tab_widget);
    splitter->addWidget(table_executions);
    splitter->setStretchFactor(0, 1);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    layout->setMargin(0);
    this->setLayout(layout);

    mtk::trd::trd_cli_ord_book::get_signal_request_hook_ls().connect(on_request_with_user_check_ls);
    mtk::trd::trd_cli_ord_book::get_signal_request_hook_mk().connect(on_request_with_user_check_mk);
}

QOrderBook::~QOrderBook()
{
}



void QOrderBook::update_sizes(void)
{
    for(int i=0; i<tab_widget->count(); ++i)
    {
        qorder_table* tw = dynamic_cast<qorder_table*>(tab_widget->widget(i));
        if(tw != 0)
            tw->update_sizes();
    }
    table_executions->update_sizes();
}


void QOrderBook::slot_request_new_tab(void)
{
    create_new_tab();
}


void QOrderBook::delete_current_tab(bool ask)
{
    if(ask)
        if(QMessageBox::warning(this, QLatin1String("CimdTrade"), tr("Do you want to close current tab?"), QMessageBox::Ok, QMessageBox::Cancel)!=QMessageBox::Ok)
            return;

    if(tab_widget->count()==1)      return;
    //tab_widget->widget(tab_widget->currentIndex())->deleteLater();
    delete tab_widget->widget(tab_widget->currentIndex());
    if(tab_widget->count() <= 5)
        new_button->setEnabled(true);
    if(tab_widget->count() == 1)
        close_button->setEnabled(false);

}

void QOrderBook::slot_request_close_tab(void)
{
    delete_current_tab();
}

void QOrderBook::slot_request_showfilter(void)
{
    qorder_table* tw = dynamic_cast<qorder_table*>(tab_widget->widget(tab_widget->currentIndex()));
    if(tw != 0)
        tw->show_filter(filter_button->isChecked());
}

void QOrderBook::slot_current_tab_name_changed(const QString& new_name)
{
    tab_widget->setTabText(tab_widget->currentIndex(), new_name);
}

void QOrderBook::slot_tab_index_changed(int /*index*/)
{
    qorder_table* tw = dynamic_cast<qorder_table*>(tab_widget->widget(tab_widget->currentIndex()));
    if(tw != 0)
    {
        filter_button->setChecked(tw->is_filter_visible());
    }
    else
        filter_button->setChecked(false);
    update_historic();
}

void QOrderBook::slot_filter_changed()
{
    qorder_table* tw = dynamic_cast<qorder_table*>(tab_widget->widget(tab_widget->currentIndex()));
    if(tw != 0)
    {
        filter_button->setChecked(false);
        tw->show_filter(filter_button->isChecked());
    }
}




qorder_table* QOrderBook::create_new_tab(void)
{
    qorder_table* order_table = new qorder_table(this);


    //  set section positions
    {
        qorder_table* ot = dynamic_cast<qorder_table*>(tab_widget->widget(tab_widget->currentIndex()));
        if(ot != 0)
        {
            order_table->set_header_positions(*ot);
        }
    }

    //  set header sections sizes
    {
        qorder_table* ot = dynamic_cast<qorder_table*>(tab_widget->widget(tab_widget->currentIndex()));
        if(ot != 0)
        {
            order_table->resize_header_sections(*ot);
        }
    }

    order_table->setFont(this->font());
    tab_widget->addTab(order_table, QLatin1String("."));
    connect(order_table, SIGNAL(signal_named_changed(QString)), this, SLOT(slot_current_tab_name_changed(QString)));
    connect(order_table, SIGNAL(signal_filter_changed()), this, SLOT(slot_filter_changed()));

    qorder_table* tw = dynamic_cast<qorder_table*>(tab_widget->widget(tab_widget->count()-1));
    if(tw != 0)
        tw->update_sizes();
    tab_widget->setCurrentIndex(tab_widget->count()-1);
    if(tab_widget->count() > 5)
        new_button->setEnabled(false);
    if(tab_widget->count() > 1)
        close_button->setEnabled(true);
    filter_button->setChecked(true);
    if(tw != 0)
        tw->show_filter(filter_button->isChecked());

    connect(order_table, SIGNAL(signal_double_click(QModelIndex)), this, SLOT(slot_order_table_double_clicked(QModelIndex)));
    connect(order_table, SIGNAL(signal_cell_changed(int, int, int, int)), this, SLOT(slot_order_table_cell_changed(int,int,int,int)));
    connect(order_table, SIGNAL(signal_request_show_historic()), SLOT(slot_show_historic()));
    connect(order_table, SIGNAL(signal_request_hide_historic()), SLOT(slot_hide_historic()));
    connect(order_table, SIGNAL(signal_sectionResized(int,int,int)), this, SLOT(slot_sectionResized(int,int,int)));
    connect(order_table, SIGNAL(signal_columnMoved(qorder_table*, int,int,int)), this, SLOT(slot_columnMoved(qorder_table*, int,int,int)));

    return order_table;
}


YAML::Emitter& operator << (YAML::Emitter& out, const QOrderBook& qob)
{
    out << YAML::BeginMap;
    out << YAML::Key  << "tabs"  << YAML::Value
                                            << YAML::BeginSeq;

    for(int i=0; i<qob.tab_widget->count(); ++i)
    {
        qorder_table* ot = dynamic_cast<qorder_table*>(qob.tab_widget->widget(i));
        if(ot != 0)
            out << *ot;
    }

    out << YAML::EndSeq;


    out << YAML::EndMap;
    return out;
}

void     operator>> (const YAML::Node & node   , QOrderBook& qob)
{
    bool delete_first = false;
    if(node["tabs"].size() > 0)
        delete_first = true;
    for(unsigned i=0; i<node["tabs"].size()  &&  i<6; ++i)
    {
        qorder_table*  order_table  =   qob.create_new_tab();
        node["tabs"][i] >> *order_table;
    }

    qob.tab_widget->setCurrentIndex(0);
    if(delete_first)
        qob.delete_current_tab(false);
}


void QOrderBook::slot_show_historic(void)
{
    qorder_table* tw = dynamic_cast<qorder_table*>(tab_widget->widget(tab_widget->currentIndex()));
    if(tw != 0)
    {
        mtk::nullable<mtk::trd::msg::sub_order_id>   order_id = tw->get_current_order_id();
        if(order_id.HasValue())
        {
            historic_order_window->setVisible(true);
            update_historic();
        }
    }
}

void QOrderBook::slot_hide_historic(void)
{
    historic_order_window->setVisible(false);
}

void QOrderBook::update_historic(void)
{
    if(historic_order_window->isVisible())
    {
        qorder_table* tw = dynamic_cast<qorder_table*>(tab_widget->widget(tab_widget->currentIndex()));
        if(tw != 0)
        {
            mtk::nullable<mtk::trd::msg::sub_order_id>   order_id = tw->get_current_order_id();
            if(order_id.HasValue())
            {
                historic_order_window->set_order(order_id.Get());
            }
        }
    }
}


void QOrderBook::slot_order_table_cell_changed(int, int, int, int)
{
    update_historic();
}

void QOrderBook::slot_order_table_double_clicked(QModelIndex)
{
    slot_show_historic();
}


void QOrderBook::slot_sectionResized(int index, int old_size, int new_size)
{
    for(int i=0; i<tab_widget->count(); ++i)
    {
        qorder_table* ot = dynamic_cast<qorder_table*>(tab_widget->widget(i));
        if(ot != 0)
        {
            ot->resize_header_section(index, old_size, new_size);
        }
    }
}

void QOrderBook::slot_columnMoved(qorder_table* origin, int logicalIndex, int oldVisualIndex, int newVisualIndex)
{
    for(int i=0; i<tab_widget->count(); ++i)
    {
        qorder_table* ot = dynamic_cast<qorder_table*>(tab_widget->widget(i));
        if(ot != 0)
        {
            ot->move_column(origin, logicalIndex, oldVisualIndex, newVisualIndex);
        }
    }
}
