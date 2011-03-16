#include "qtreeproducts.h"

#include <QMouseEvent>
#include <QApplication>
#include <QTreeWidgetItem>
#include <QPainter>

#include "components/msg_common.h"
#include "qmtk_misc.h"


#include "components/admin/admin.h"
#include "components/request_response.hpp"








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

    struct register_global_commands
    {
        register_global_commands (void)
        {
            mtk::admin::register_command("__GLOBAL__",  "ver",   "")->connect(command_version);
            mtk::admin::register_command("__GLOBAL__",  "modifs",   "")->connect(command_modifications);
        }
    };
    register_global_commands rc;

}       //  anonymous namespace  to register "static" commnads













class mtkQtreeItem : public  QTreeWidgetItem
{
public:
    mtkQtreeItem(QTreeWidget* w, const mtk::gen::msg::sub_tree_item& _item)
        : QTreeWidgetItem(w), item(_item)  {}
    mtkQtreeItem(QTreeWidgetItem* w, const mtk::gen::msg::sub_tree_item& _item)
        : QTreeWidgetItem(w), item(_item)  {}

    const mtk::gen::msg::sub_tree_item   item;
};



class QShowTree : public QWidget
{
public:
    QShowTree(QWidget* w): QWidget(w)
    {
        setAutoFillBackground(false);

        //QPalette p(palette());
        //p.setColor(QPalette::Background, QColor(0,0,255,160));
        //setPalette(p);

        //this->setStyleSheet("background-color: rgba(0,0,255,160, 0);");
        raise();
        setMouseTracking(true);
        this->setStyleSheet("background-color: rgba(0, 0, 255, 0); color:rgba(255,255,255)");
    }

    void paintEvent(QPaintEvent /**event*/)
    {
        //QWidget::paintEvent(event);
        if (autoFillBackground())
        {
            QPainter painter(this);
            painter.save();
            //painter.fillRect(this->rect(), QColor(0,0,255,160));
            painter.translate(this->width()-3, this->height()-10);
            painter.rotate(270);
            painter.setPen(Qt::white);
            painter.setBrush(QBrush(QColor(Qt::white)));
            painter.drawText(0, 0, "tree prods");
            painter.restore();
        }
    }

    void mousePressEvent(QMouseEvent *event) {
        QWidget::mousePressEvent(event);
        if(event->button() == Qt::LeftButton)
            signal_click.emit();
    }

    void mouseMoveEvent(QMouseEvent *event) { QWidget::mouseMoveEvent(event); this->setAutoFillBackground(true); this->setStyleSheet("background-color: rgba(0,0,255,160, 160); color:rgba(255,255,255,255)");}

    void leaveEvent(QEvent *)  { setAutoFillBackground(false);  this->setStyleSheet("background-color: rgba(0, 0, 255, 0); color:rgba(255,255,255,255)");  }

    mtk::Signal<>  signal_click;
};





qTreeProducts::qTreeProducts(QWidget *parent) :
    QTreeWidget(parent), startPos (-1,-1)
{
    //QShowTree* open_tree (new QShowTree(dynamic_cast<QWidget*>(this->parent()->parent()->parent())));
    QShowTree* open_tree (new QShowTree(this));
    open_tree->setParent(dynamic_cast<QWidget*>(this->parent()->parent()->parent()));
    open_tree->setGeometry(1, 1, 17, 100);
    MTK_CONNECT_THIS(open_tree->signal_click, show_tree)
    setVisible(false);

    qpid_session = mtk::admin::get_qpid_session("client", "CLITESTING");

    MTK_TIMER_1S(request_root_items);

    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), SLOT(on_itemDoubleClicked(QTreeWidgetItem*,int)));
}




void qTreeProducts::show_tree(void)
{
    if (this->isVisible())
        this->setVisible(false);
    else
       this->setVisible(true);
}

void qTreeProducts::mousePressEvent(QMouseEvent *event)
{
    startPos = event->pos();
    QTreeWidget::mousePressEvent(event);
}

void qTreeProducts::mouseReleaseEvent(QMouseEvent *  event)
{
    startPos = QPoint(-1,-1);
    QTreeWidget::mouseReleaseEvent(event);
}


void qTreeProducts::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton)  &&  startPos.x()>=0  &&  startPos.y()>=0)
    {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance() + 100)
            start_drag();
    }
    else
        QTreeWidget::mouseMoveEvent(event);
}


void qTreeProducts::start_drag(void)
{
    mtkQtreeItem* item = dynamic_cast<mtkQtreeItem*>(currentItem());
    if (item  &&  item->item.product_code.HasValue())
    {
        QMimeData* mimeData = new QMimeData;
        mimeData->setText(dragProductText(item->item.product_code.Get()));
        QDrag* drag = new QDrag(this);
        drag->setMimeData(mimeData);

        QRect rect(this->visualItemRect(this->currentItem()));
        QPixmap pixmap (rect.size());
        this->render(&pixmap, QPoint(), rect);
        drag->setPixmap(pixmap);

        drag->start(Qt::CopyAction);
    }
}

void qTreeProducts::request_root_items(void)
{
    MTK_EXEC_MAX_FREC(mtk::dtSeconds(10))
    {
        if(this->topLevelItemCount() == 0)
        {
            mtk::msg::sub_request_info   request_info = mtk::admin::get_request_info();
            mtk::gen::msg::tree_request_items  tree_request_message(request_info, "ROOT");
            mtk::send_message(qpid_session, tree_request_message);

            //  subscription to multiresponse
            MTK_RECEIVE_MULTI_RESPONSE_THIS(mtk::gen::msg::tree_response_items,
                                            mtk::gen::msg::sub_tree_item,
                                            qpid_session,
                                            mtk::gen::msg::tree_response_items::get_in_subject( request_info.process_location.location,
                                                                                                request_info.process_location.machine,
                                                                                                request_info.process_location.process_uuid,
                                                                                                request_info.req_id.sess_id,
                                                                                                request_info.req_id.req_code),
                                            on_response_request_tree)
        }
        else
            MTK_TIMER_1S_STOP(request_root_items)
    }
    MTK_END_EXEC_MAX_FREC
}


QTreeWidgetItem*  qTreeProducts::get_item_from_branck(QString current_branch, QStringList& pending_branch, QTreeWidgetItem* current_tree_item)
{
    if(pending_branch.size()==0)
        return current_tree_item;

    if(current_branch == "ROOT")
    {
        QString next_branch_name =  MTK_SS(current_branch.toStdString() << "." << pending_branch.front().toStdString()).c_str();
        pending_branch.pop_front();
        return get_item_from_branck(next_branch_name, pending_branch, this->invisibleRootItem());
    }


    for(int i=0; i<current_tree_item->childCount(); ++i)
    {
        mtkQtreeItem* next_item = dynamic_cast<mtkQtreeItem*>(current_tree_item->child(i));
        if(next_item == 0)
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "invalid item type", mtk::alPriorError, mtk::alTypeNoPermisions));
        if(current_branch == next_item->item.branch.c_str())
        {
            QString next_branch_name =  MTK_SS(current_branch.toStdString() << "." << pending_branch.front().toStdString()).c_str();
            pending_branch.pop_front();
            return get_item_from_branck(next_branch_name, pending_branch, next_item);
        }
    }
    throw mtk::Alarm(MTK_HERE, MTK_SS(current_branch.toStdString() <<  "  item not found"), mtk::alPriorError, mtk::alTypeNoPermisions);
}

void qTreeProducts::on_response_request_tree(const mtk::list<mtk::gen::msg::tree_response_items>& list_items)
{
    mtk::list<mtk::gen::msg::tree_response_items>::const_iterator it = list_items.begin();
    QTreeWidgetItem* insert_into_item=0;
    while(it != list_items.end())
    {
        mtk::gen::msg::sub_tree_item   item = it->item;
        mtkQtreeItem* new_item;

        QStringList full_path_branch = QString(item.branch.c_str()).split(".");
        QString next_branch_name =  full_path_branch.front();
        full_path_branch.pop_front();
        QTreeWidgetItem* start_item = dynamic_cast<QTreeWidgetItem*>(this->invisibleRootItem());
        if(start_item==0)
            throw mtk::Alarm(MTK_HERE, "invalid start item", mtk::alPriorError, mtk::alTypeNoPermisions);
        insert_into_item = get_item_from_branck(next_branch_name, full_path_branch, start_item);
        if(insert_into_item==0)
            throw mtk::Alarm(MTK_HERE, MTK_SS(item.branch << "  item not found"), mtk::alPriorError, mtk::alTypeNoPermisions);
        else
        {
            if(insert_into_item == start_item)
                new_item = new mtkQtreeItem(this, item);
            else
                new_item = new mtkQtreeItem(insert_into_item, item);
        }
        new_item->setText(0, item.user_name.c_str());
        if(item.product_code.HasValue())
            new_item->setForeground(0, QBrush(Qt::blue));
        ++it;
    }
    if(insert_into_item)
        insert_into_item->setExpanded(true);
}



void qTreeProducts::on_itemDoubleClicked ( QTreeWidgetItem * item, int /*column*/ )
{
    mtkQtreeItem* mtk_item = dynamic_cast<mtkQtreeItem*>(item);
    if(mtk_item==0)
        throw mtk::Alarm(MTK_HERE, "invalid item type", mtk::alPriorError, mtk::alTypeNoPermisions);

    if(mtk_item->childCount()==0)
    {
        mtk::msg::sub_request_info   request_info = mtk::admin::get_request_info();
        mtk::gen::msg::tree_request_items  tree_request_message(request_info, MTK_SS(mtk_item->item.branch));
        mtk::send_message(qpid_session, tree_request_message);

        //  subscription to multiresponse
        MTK_RECEIVE_MULTI_RESPONSE_THIS(mtk::gen::msg::tree_response_items,
                                        mtk::gen::msg::sub_tree_item,
                                        qpid_session,
                                        mtk::gen::msg::tree_response_items::get_in_subject( request_info.process_location.location,
                                                                                            request_info.process_location.machine,
                                                                                            request_info.process_location.process_uuid,
                                                                                            request_info.req_id.sess_id,
                                                                                            request_info.req_id.req_code),
                                        on_response_request_tree)
    }
}
