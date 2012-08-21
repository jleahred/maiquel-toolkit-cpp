#include "qswitch_money.h"

#include <QVBoxLayout>
#include <QApplication>

#include <iostream>


#include "qt_components/src/qmtk_misc.h"
#include "yaml/yaml.h"
#include "ecimd_config.h"

#include "ui_switch_money.h"
#include "swm_calculator.h"





namespace {
    const char*   VERSION = "2012-08-09";

    const char*   MODIFICATIONS =
                        "           2012-08-09     first version\n";


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







QSize  QSwicthMoney::sizeHint(void) const
{
    return  QWidget::sizeHint();
}


QSwicthMoney::QSwicthMoney(QWidget *parent) :
    mtkContainerWidget(parent), ui (0)
{
    //this->setGeometry(QRect(5, 5, 350-2, 300-2));
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(5,5,5,5);
    this->setLayout(layout);

    this->setAcceptDrops(true);

    /////////////////
    ui = new ui_switch_money(this);
    layout->addWidget(ui);

    
    this->inserting_components_ended();

    connect(this, SIGNAL(signal_start_moving()), SLOT(make_transparent()));
    connect(this, SIGNAL(signal_stop_moving()), SLOT(remove_transparecy()));




    //      connect signals
    ui->signal_config_changed.connect(&calculator, &swm_calculator::on_config_changed);

    calculator.signal_price_update.connect(ui, &ui_switch_money::on_price_update);
    calculator.signal_ERROR.connect       (ui, &ui_switch_money::on_error);


    calculator.signal_ERROR.connect       (this, &QSwicthMoney::on_error);


    remove_focus();
}

QSwicthMoney::~QSwicthMoney()
{
}


void	QSwicthMoney::resizeEvent ( QResizeEvent *  event )
{
    mtkContainerWidget::resizeEvent(event);
}



void QSwicthMoney::dragEnterEvent(QDragEnterEvent *event)
{
    mtkContainerWidget::dragEnterEvent(event);
}

void QSwicthMoney::dropEvent(QDropEvent * /*event*/)
{
    this->setFocus();
}


void QSwicthMoney::mousePressEvent(QMouseEvent *event)
{
    startPos = event->pos();
    mtkContainerWidget::mousePressEvent(event);
}

void QSwicthMoney::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    startPos = QPoint(-1,-1);
}

void QSwicthMoney::mouseMoveEvent(QMouseEvent *event)
{
    mtkContainerWidget::mouseMoveEvent(event);
}

void QSwicthMoney::make_transparent(void)
{
    //ui->make_transparent();
}

void QSwicthMoney::remove_transparecy(void)
{
    this->setFocus();
    paint_focus();
}


void QSwicthMoney::paint_focus(void)
{
    //ui->paint_focus();
}

void QSwicthMoney::remove_focus(void)
{
    //ui->remove_focus();
}

void    QSwicthMoney::on_error(const mtk::Alarm&  error)
{
    mtk::AlarmMsg(error);
}








YAML::Emitter& operator << (YAML::Emitter& out, const QSwicthMoney& c)
{
    out     << YAML::BeginMap;

    //  writing component
    out << YAML::Key   <<  "component" << YAML::Value << static_cast<const mtkContainerWidget&>(c);
    //  end component

    /*
    //  writing product
    if(m.price_manager.isValid())
        out << YAML::Key   <<  "product_code"  << YAML::Value   << m.price_manager->get_product_code();
    //  end product
    */


    out << YAML::EndMap;

    return out;
}

void             operator >> (const YAML::Node&   node,       QSwicthMoney& c)
{
    node["component"] >> static_cast<mtkContainerWidget&>(c);

    /*
    if(node.FindValue("product_code"))
    {
        mtk::msg::sub_product_code pc = mtk::msg::__internal_get_default((mtk::msg::sub_product_code*)0);
        node["product_code"] >> pc;
        d.subscribe_to(pc);
    }
    */
}
