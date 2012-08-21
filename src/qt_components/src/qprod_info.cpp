#include "qprod_info.h"

#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QPlainTextEdit>

#include <iostream>


#include "qt_components/src/qmtk_misc.h"
#include "yaml/yaml.h"
#include "ecimd_config.h"






namespace {
    const char*   VERSION = "2012-05-02";

    const char*   MODIFICATIONS =
                        "           2012-05-02     first version\n";


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












/*
QProd_info::Highlighter::Highlighter(QTextDocument *parent)
     : QSyntaxHighlighter(parent)
 {
     HighlightingRule rule;


     formatRule = QTextCharFormat();
     formatRule.setFontWeight(QFont::Bold);
     //formatRule.setFontItalic(true);
     formatRule.setForeground(Qt::darkBlue);
     //formatRule.setBackground(QColor(240, 240, 255));
     rule.pattern = QRegExp(QLatin1String("^.*:"));
     rule.format = formatRule;
     highlightingRules.append(rule);
}


void QProd_info::Highlighter::highlightBlock(const QString &text)
 {
     foreach (const HighlightingRule &rule, highlightingRules) {
         QRegExp expression(rule.pattern);
         int index = expression.indexIn(text);
         while (index >= 0) {
             int length = expression.matchedLength();
             setFormat(index, length, rule.format);
             index = expression.indexIn(text, index + length);
         }
     }
     setCurrentBlockState(0);
 }
*/








QSize  QProd_info::sizeHint(void) const
{
    return  QSize(290-2, 300-2);
}


QProd_info::QProd_info(QWidget *parent) :
    mtkContainerWidget(parent)
{
    //this->setGeometry(QRect(5, 5, 290-2, 300-2));
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(5,5,5,5);
    this->setLayout(layout);

    this->setAcceptDrops(true);

    {
        title = new QLabel(this);
        layout->addWidget(title);
        title->setBackgroundRole(QPalette::Light);
        title->setAlignment(Qt::AlignCenter);
        title->setAutoFillBackground(true);
        title->setStyleSheet(QLatin1String("color: rgb(30,0,100); background-color: rgb(191,219,255); font-weight: 1000;"));
        title->setLineWidth(2);
        title->setMargin(3);
    }

    {
        info = new QPlainTextEdit(this);
        layout->addWidget(info);
        info->setBackgroundRole(QPalette::Light);
        info->setAutoFillBackground(true);
        info->setStyleSheet(QLatin1String("color: rgba(30,0,100); background-color: rgba(255,255,255);"));
        info->setLineWidth(2);
        info->setReadOnly(true);
        info->setFocusProxy(this);
        info->setFont(QFont(QLatin1String("Courier new")));
    }
    {
        //highlighter = new Highlighter(this->info->document());
    }


    this->inserting_components_ended();

    connect(this, SIGNAL(signal_start_moving()), SLOT(make_transparent()));
    connect(this, SIGNAL(signal_stop_moving()), SLOT(remove_transparecy()));

    remove_focus();
}

QProd_info::~QProd_info()
{
}


void	QProd_info::resizeEvent ( QResizeEvent *  event )
{
    mtkContainerWidget::resizeEvent(event);
}



void QProd_info::dragEnterEvent(QDragEnterEvent *event)
{
    if(qtmisc::has_product_code(event))
    {
        event->setDropAction(Qt::CopyAction);
        event->accept();
        return;
    }
    else
    {
        event->ignore();
        return;
    }
}

void QProd_info::dropEvent(QDropEvent *event)
{
    subscribe_to(qtmisc::get_product_code(event));
    this->setFocus();
}

void QProd_info::subscribe_to (const mtk::msg::sub_product_code& _product_code)
{
    price_manager = mtk::make_cptr(new mtk::prices::price_manager(_product_code));
    title->setText(QLatin1String(MTK_SS(price_manager->get_product_code().market << "."<< price_manager->get_product_code().product).c_str()));
    MTK_CONNECT_THIS(price_manager->signal_additional_info_update, on_message_addtional_info);

    //  this will make a permanent suscription  for this prices_manager instance
    if(price_manager->get_additional_info().HasValue())
        on_message_addtional_info(_product_code, price_manager->get_additional_info().Get());
}


void QProd_info::mousePressEvent(QMouseEvent *event)
{
    startPos = event->pos();
    mtkContainerWidget::mousePressEvent(event);
}

void QProd_info::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    startPos = QPoint(-1,-1);
}

void QProd_info::mouseMoveEvent(QMouseEvent *event)
{
    if(price_manager.isValid() == false)        return;


    mtkContainerWidget::mouseMoveEvent(event);
    if ((event->buttons() & Qt::LeftButton)  &&  startPos.x()>=0  &&  startPos.y()>=0)
    {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance()+5  &&  mtk::msg::is_valid(price_manager->get_product_code()))
        {
            QMimeData* mimeData = new QMimeData;
            mimeData->setText(qtmisc::dragProductText(price_manager->get_product_code()));
            QDrag* drag = new QDrag(this);
            drag->setMimeData(mimeData);

            QPixmap pixmap (title->size());
            title->render(&pixmap);
            drag->setPixmap(pixmap);

            drag->exec(Qt::CopyAction);
        }
    }
}

void QProd_info::make_transparent(void)
{
    title->setStyleSheet(QLatin1String("color: rgba(30,0,100); background-color: rgba(191,219,255, 150); font-weight: 400;"));
    info->setAutoFillBackground(false);
    info->setStyleSheet(QLatin1String("color: rgba(30,0,100); background-color: rgba(255,255,255, 150);"));
}

void QProd_info::remove_transparecy(void)
{
    this->setFocus();
    paint_focus();
}


void QProd_info::paint_focus(void)
{
    title->setStyleSheet(QLatin1String("background-color: rgb(120,120,255); color: rgb(255,255,255); font-weight: 1000;"));
    info->setStyleSheet(QLatin1String("color: rgba(30,0,100); background-color: rgba(255,255,255);"));
}

void QProd_info::remove_focus(void)
{
    title->setStyleSheet(QLatin1String("color: rgb(30,0,100); background-color: rgb(191,219,255); font-weight: 1000;"));
}


void QProd_info::on_message_addtional_info(const mtk::msg::sub_product_code& /*product_code*/, const mtk::prices::msg::sub_additional_info&  aditional_info)
{
    QString  s_future_info;
    if(aditional_info.future_info.HasValue())
    {
        mtk::prices::msg::sub_future_info  future_info = aditional_info.future_info.Get();
        s_future_info =
                   QLatin1String("\n") +
                   QLatin1String("----------------------------\n") +
                               tr("*FUTURE*\n")  +
                               tr("  num legs:      ")  +  QLatin1String(MTK_SS(future_info.num_legs).c_str())  +  QLatin1String("\n") +
                               tr("  maturity:      ")  +  QLatin1String(MTK_SS(future_info.maturity).c_str()) +  QLatin1String("\n") +
                               tr("  last trad dt:  ")  +  QLatin1String(MTK_SS(future_info.last_trading_dt).c_str()) +  QLatin1String("\n") +
                               tr("  underlying:    ")  +  QLatin1String(MTK_SS(future_info.underlying).c_str()) +  QLatin1String("\n") +
                    QLatin1String("---------------------------\n")
                    ;
    }

    QString  s_option_info;
    if(aditional_info.option_info.HasValue())
    {
        mtk::prices::msg::sub_option_info  option_info = aditional_info.option_info.Get();
        s_option_info =
                   QLatin1String("\n") +
                   QLatin1String("----------------------------\n") +
                               tr("*OPTION*\n")  +
                               tr("  last trad dt:  ")  +  QLatin1String(MTK_SS(option_info.last_trading_dt).c_str()) +  QLatin1String("\n") +
                               tr("  underlying:    ")  +  QLatin1String(MTK_SS(option_info.underlying).c_str()) +  QLatin1String("\n") +
                    QLatin1String("---------------------------\n")
                    ;
    }


    info->setPlainText(
                    //tr("MARKET:          ")  +  QLatin1String(product_code.market.c_str()) +  QLatin1String("\n") +
                    //tr("PRODUCT:         ")  +  QLatin1String(product_code.product.c_str()) +  QLatin1String("\n") +
                    tr("group:           ")  +  QLatin1String(aditional_info.group.c_str()) +  QLatin1String("\n") +
                    tr("value date:      ")  +  QLatin1String(MTK_SS(aditional_info.value_date).c_str()) +  QLatin1String("\n") +
                    tr("unit cost:       ")  +  QLatin1String(MTK_SS(aditional_info.unit_cost).c_str()) +  QLatin1String("\n") +

                    s_future_info +
                    s_option_info +

                    tr("\ndescription:     ")  +  QLatin1String(MTK_SS(aditional_info.description).c_str()) +  QLatin1String("\n") +
                    tr("misc:            ")  +  QLatin1String(MTK_SS(aditional_info.yaml_misc).c_str())  +  QLatin1String("\n")
            );
}





YAML::Emitter& operator << (YAML::Emitter& out, const QProd_info& m)
{
    out     << YAML::BeginMap;

    //  writing component
    out << YAML::Key   <<  "component" << YAML::Value << static_cast<const mtkContainerWidget&>(m);
    //  end component

    //  writing product
    if(m.price_manager.isValid())
        out << YAML::Key   <<  "product_code"  << YAML::Value   << m.price_manager->get_product_code();
    //  end product


    out << YAML::EndMap;

    return out;
}

void             operator >> (const YAML::Node&   node,       QProd_info& d)
{
    node["component"] >> static_cast<mtkContainerWidget&>(d);

    if(node.FindValue("product_code"))
    {
        mtk::msg::sub_product_code pc = mtk::msg::__internal_get_default((mtk::msg::sub_product_code*)0);
        node["product_code"] >> pc;
        d.subscribe_to(pc);
    }
}
