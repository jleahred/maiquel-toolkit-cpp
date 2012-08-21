#include "qticker_execs.h"

#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QPlainTextEdit>
#include <QMessageBox>

#include <iostream>


#include "qt_components/src/qmtk_misc.h"
#include "yaml/yaml.h"
#include "ecimd_config.h"






namespace {
    const char*   VERSION = "2012-07-17";

    const char*   MODIFICATIONS =
                        "           2012-07-17     first version\n";


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




int QTickerExecs::num_subscriptions = 0;



QSize  QTickerExecs::sizeHint(void) const
{
    return QSize(290-2, 300-2);
}

QTickerExecs::QTickerExecs(QWidget *parent) :
        mtkContainerWidget(parent), product_code(mtk::msg::__internal_get_default((mtk::msg::sub_product_code*)0))
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


    this->inserting_components_ended();

    connect(this, SIGNAL(signal_start_moving()), SLOT(make_transparent()));
    connect(this, SIGNAL(signal_stop_moving()), SLOT(remove_transparecy()));

    remove_focus();
}

QTickerExecs::~QTickerExecs()
{
    if(mtk::msg::is_valid(product_code))
        --QTickerExecs::num_subscriptions;
}


void	QTickerExecs::resizeEvent ( QResizeEvent *  event )
{
    mtkContainerWidget::resizeEvent(event);
}



void QTickerExecs::dragEnterEvent(QDragEnterEvent *event)
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

void QTickerExecs::dropEvent(QDropEvent *event)
{
    subscribe_to(qtmisc::get_product_code(event));
    this->setFocus();
}

void QTickerExecs::subscribe_to (const mtk::msg::sub_product_code& _product_code)
{
    if(QTickerExecs::num_subscriptions>=5)
    {
        QMessageBox::warning(this, QLatin1String("eCimd"), tr("Too many subscriptions to execs ticker  "), QMessageBox::Ok);
        info->setPlainText(tr("too many subscriptions, subscription canceled."));
        return;
    }

    this->product_code = _product_code;
    MTK_QPID_RECEIVER_CONNECT_THIS__WITH_ADDRESS(
                            handle_execs_subscription,
                            mtk::admin::get_url("client"),
                            mtk::prices::msg::plaet::static_get_qpid_address(product_code.market),
                            mtk::prices::msg::plaet::get_in_subject(product_code.product),
                            mtk::prices::msg::plaet,
                            on_all_last_execs__update)


    title->setText(QLatin1String(MTK_SS(product_code.market << "."<< product_code.product).c_str()));
    info->setPlainText(QLatin1String(""));
    ++QTickerExecs::num_subscriptions;
}


void QTickerExecs::mousePressEvent(QMouseEvent *event)
{
    startPos = event->pos();
    mtkContainerWidget::mousePressEvent(event);
}

void QTickerExecs::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    startPos = QPoint(-1,-1);
}

void QTickerExecs::mouseMoveEvent(QMouseEvent *event)
{
    if(mtk::msg::is_valid(product_code)  == false)  return;

    mtkContainerWidget::mouseMoveEvent(event);
    if ((event->buttons() & Qt::LeftButton)  &&  startPos.x()>=0  &&  startPos.y()>=0)
    {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance()+5  &&  mtk::msg::is_valid(product_code))
        {
            QMimeData* mimeData = new QMimeData;
            mimeData->setText(qtmisc::dragProductText(product_code));
            QDrag* drag = new QDrag(this);
            drag->setMimeData(mimeData);

            QPixmap pixmap (title->size());
            title->render(&pixmap);
            drag->setPixmap(pixmap);

            drag->exec(Qt::CopyAction);
        }
    }
}

void QTickerExecs::make_transparent(void)
{
    title->setStyleSheet(QLatin1String("color: rgba(30,0,100); background-color: rgba(191,219,255, 150); font-weight: 400;"));
    info->setAutoFillBackground(false);
    info->setStyleSheet(QLatin1String("color: rgba(30,0,100); background-color: rgba(255,255,255, 150);"));
}

void QTickerExecs::remove_transparecy(void)
{
    this->setFocus();
    paint_focus();
}


void QTickerExecs::paint_focus(void)
{
    title->setStyleSheet(QLatin1String("background-color: rgb(120,120,255); color: rgb(255,255,255); font-weight: 1000;"));
    info->setStyleSheet(QLatin1String("color: rgba(30,0,100); background-color: rgba(255,255,255);"));
}

void QTickerExecs::remove_focus(void)
{
    title->setStyleSheet(QLatin1String("color: rgb(30,0,100); background-color: rgb(191,219,255); font-weight: 1000;"));
}


void QTickerExecs::on_all_last_execs__update          (const mtk::prices::msg::plaet&  plaet)
{
    mtk::list<mtk::prices::msg::sub_last_exec_info>  decompacted = mtk::prices::publ::decompact_last_exec_list(plaet.compacted_data);

    mtk::msg::sub_product_code          _product_code    (plaet.market, plaet.product);

    if(_product_code != this->product_code)
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "eCimd.on_all_last_execs__update", MTK_SS("Received invalid product code  " << _product_code << "  expected " << this->product_code), mtk::alPriorError));
        return;
    }

    //std::string  sresult;
    QString  sresult;


    for(auto it=decompacted.begin(); it!=decompacted.end(); ++it)
    {
        mtk::prices::msg::sub_last_exec_info& last_exec_info = *it;

        std::string  __time = MTK_SS(last_exec_info.datetime << "_error dectm");
        sresult = QString::fromLatin1("%1 %2 %3\n")
                   .arg(QString::fromLatin1(__time.substr(11, 8).c_str()))
                   .arg(qtmisc::fn_as_QString(last_exec_info.quantity), 8)
                   .arg(qtmisc::fn_as_QString(last_exec_info.price), 8) + sresult;
    }
    info->setPlainText(sresult + info->toPlainText());
    if(info->toPlainText().size() > 30*27)
        info->setPlainText(info->toPlainText().mid(0, 20*27));
}




YAML::Emitter& operator << (YAML::Emitter& out, const QTickerExecs& m)
{
    out     << YAML::BeginMap;

    //  writing component
    out << YAML::Key   <<  "component" << YAML::Value << static_cast<const mtkContainerWidget&>(m);
    //  end component

    //  writing product
    if(mtk::msg::is_valid(m.get_product_code()))
        out << YAML::Key   <<  "product_code"  << YAML::Value   << m.get_product_code();
    //  end product


    out << YAML::EndMap;

    return out;
}

void             operator >> (const YAML::Node&   node,       QTickerExecs& d)
{
    node["component"] >> static_cast<mtkContainerWidget&>(d);

    if(node.FindValue("product_code"))
    {
        mtk::msg::sub_product_code pc = mtk::msg::__internal_get_default((mtk::msg::sub_product_code*)0);
        node["product_code"] >> pc;
        d.subscribe_to(pc);
    }
}
