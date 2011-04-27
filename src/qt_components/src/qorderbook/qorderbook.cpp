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



void on_request_with_user_check(mtk::trd::msg::RQ_XX_LS& rq, bool& canceled)
{
    QEditOrder eo(rq);
    if (eo.exec())
    {
        rq = eo.get_request();
    }
    else canceled =true;
}



QOrderBook::QOrderBook(QWidget *parent) :
    QWidget(parent),
    table_executions(new QExecsTable(this))
{
    //table_executions->setMinimumWidth(300);
    table_executions->setMinimumWidth(30);

    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setChildrenCollapsible(false);
    tab_widget = new QTabWidget(this);
    tab_widget->setMovable(true);
    //tab_widget->setTabsClosable(true);
    {
        qorder_table* order_table = new qorder_table(this);
        tab_widget->addTab(order_table, QLatin1String("."));
        connect(order_table, SIGNAL(signal_named_changed(QString)), this, SLOT(slot_current_tab_name_changed(QString)));
        connect(order_table, SIGNAL(signal_filter_changed()), this, SLOT(slot_filter_changed()));
    }
    //connect(tab_widget, SIGNAL(tabCloseRequested(int)), SLOT(slot_request_close_tab()));
    connect(tab_widget, SIGNAL(currentChanged(int)), SLOT(slot_tab_index_changed(int)));

    {
        QWidget* w = new QWidget(this);
        QHBoxLayout *hl= new QHBoxLayout(w);
        hl->setSpacing(0);
        hl->setContentsMargins(0, 0, 0, 0);

        new_button = new QPushButton(QIcon(QLatin1String(":/small_icons/new")), QLatin1String(""), w);
        connect(new_button, SIGNAL(clicked()), this, SLOT(slot_request_new_tab()));
        new_button->setFlat(true);
        hl->addWidget(new_button);

        filter_button = new QPushButton(QIcon(QLatin1String(":/small_icons/filter")), QLatin1String(""), w);
        connect(filter_button, SIGNAL(clicked()), this, SLOT(slot_request_showfilter()));
        filter_button->setFlat(true);
        filter_button->setCheckable(true);
        hl->addWidget(filter_button);

        close_button = new QPushButton(QIcon(QLatin1String(":/small_icons/image_close")), QLatin1String(""), w);
        connect(close_button, SIGNAL(clicked()), this, SLOT(slot_request_close_tab()));
        close_button->setFlat(true);
        close_button->setEnabled(false);
        hl->addWidget(close_button);

        tab_widget->setCornerWidget(w);
    }

    splitter->addWidget(tab_widget);
    splitter->addWidget(table_executions);
    splitter->setStretchFactor(0, 1);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    layout->setMargin(0);
    this->setLayout(layout);

    mtk::trd::trd_cli_ord_book::get_signal_request_hook().connect(on_request_with_user_check);
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
}


void QOrderBook::slot_request_new_tab(void)
{
    {
        qorder_table* order_table = new qorder_table(this);
        tab_widget->addTab(order_table, QLatin1String("."));
        connect(order_table, SIGNAL(signal_named_changed(QString)), this, SLOT(slot_current_tab_name_changed(QString)));
        connect(order_table, SIGNAL(signal_filter_changed()), this, SLOT(slot_filter_changed()));
    }

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
}

void QOrderBook::slot_request_close_tab(void)
{
    if(QMessageBox::warning(this, QLatin1String("CimdTrade"), tr("Do you want to close current tab?"), QMessageBox::Ok, QMessageBox::Cancel)!=QMessageBox::Ok)     return;

    if(tab_widget->count()==1)      return;
    tab_widget->widget(tab_widget->currentIndex())->deleteLater();
    if(tab_widget->count() <= 5)
        new_button->setEnabled(true);
    if(tab_widget->count() == 2)        //  2 because of deletelater  IMPORTANT
        close_button->setEnabled(false);
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

void QOrderBook::slot_tab_index_changed(int)
{
    qorder_table* tw = dynamic_cast<qorder_table*>(tab_widget->widget(tab_widget->currentIndex()));
    if(tw != 0)
    {
        filter_button->setChecked(tw->is_filter_visible());
    }
    else
        filter_button->setChecked(false);
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
