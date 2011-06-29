#include "qhistorictable.h"


#include <QHeaderView>
#include <QAction>
#include <QHBoxLayout>
#include <QMenu>



#include "qmtk_misc.h"
#include "qt_components/src/qcommontabledelegate.h"
#include "components/trading/trd_cli_support.h"






namespace {
    const int col_transaction_type      = 0;
    const int col_date_time             = 1;
    const int col_quantity              = 2;
    const int col_price                 = 3;
    const int col_cli_ref               = 4;
    const int col_aditional_code        = 5;
    const int col_request_id            = 6;
    const int col_remarks               = 7;

    const int count_items               = 8;



    /*const char* col_captions[] = {                    defined later for translations  */
};









//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------

QHistoricTable::QHistoricTable(QWidget *parent) :
        QTableWidget(parent)
{
    QStringList headers_captions;
    {
        static const char* const col_captions[] = {     QT_TR_NOOP("t.type"),
                                                        QT_TR_NOOP("time"),
                                                        QT_TR_NOOP("quantity"),
                                                        QT_TR_NOOP("price"),
                                                        QT_TR_NOOP("cli_ref"),
                                                        QT_TR_NOOP("adit.code."),
                                                        QT_TR_NOOP("req.id."),
                                                        QT_TR_NOOP("remarks"),
                                                        0          };


        int counter;
        for (counter=0; col_captions[counter]!=0; ++counter)
            headers_captions.append(tr(col_captions[counter]));
        setColumnCount(counter);
    }
    setHorizontalHeaderLabels(headers_captions);

    verticalHeader()->setVisible(false);
    horizontalHeader()->setStretchLastSection(true);


    {
        QCommonTableDelegate* delegate_paint = new QCommonTableDelegate(this);
        delegate_paint->set_horiz_line_each(1);
        setItemDelegate(delegate_paint);
    }
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setShowGrid(false);

    /*
    setColumnWidth(col_market_product, 100);
    setColumnWidth(col_side, 30);
    setColumnWidth(col_exec_price, 60);
    setColumnWidth(col_exec_quantity, 60);
    */
}



void QHistoricTable::update_sizes()
{
    verticalHeader()->setDefaultSectionSize(QFontMetrics(this->font()).height()*1.2);
}




void        QHistoricTable::update_item(int row, const  mtk::trd::hist::order_historic_item&  item)
{
    QColor color = Qt::white;
    QString trans_text;

    if (item.type == mtk::trd::hist::tt_rq_pending)
    {
        trans_text = tr("rq pend");
        color = qtmisc::mtk_color_pending;
    }
    else if (item.type == mtk::trd::hist::tt_rq_confirmed)
        trans_text = tr("rq conf");
    else if (item.type == mtk::trd::hist::tt_cf)
        trans_text = tr("conf");
    else if (item.type == mtk::trd::hist::tt_rj)
    {
        trans_text = tr("rej");
        color = qtmisc::mtk_color_problem;
    }

    if (item.type2 == mtk::trd::hist::tt2_nw)
        trans_text += tr(" new");
    else if (item.type2 == mtk::trd::hist::tt2_md)
        trans_text += tr(" mod");
    else if (item.type2 == mtk::trd::hist::tt2_cc  &&  item.type != mtk::trd::hist::tt_rq_pending)
    {
        trans_text += tr(" canc");
        color = Qt::gray;
    }
    else if (item.type2 == mtk::trd::hist::tt2_ex)
    {
        trans_text += tr(" exec");
        color = qtmisc::mtk_color_executed;
    }


    this->item(row, col_transaction_type)->setText(trans_text);

    this->item(row, col_date_time)->setText(QLatin1String(MTK_SS(item.date_time).c_str()));
    if(item.price.HasValue())
        this->item(row, col_price)->setText(qtmisc::fn_as_QString(item.price.Get()));
    else
        this->item(row, col_price)->setText(QLatin1String("") );
    this->item(row, col_quantity)->setText(qtmisc::fn_as_QString(item.quantity));
    this->item(row, col_cli_ref)->setText(QLatin1String(MTK_SS(item.cli_ref).c_str()));
    this->item(row, col_aditional_code)->setText(QLatin1String(MTK_SS(item.aditional_code).c_str()));
    this->item(row, col_request_id)->setText(QLatin1String(MTK_SS(item.request_id).c_str()));

    this->item(row, col_remarks)->setText(QLatin1String(MTK_SS(item.confirmation_delay << "  " << item.remarks).c_str()));

    for (int column=0; column<count_items; ++column)
        this->item(row, column)->setBackgroundColor(color);
    this->setCurrentCell(row, 0);
}


void        QHistoricTable::add_item(const  mtk::trd::hist::order_historic_item&  item)
{
    int new_row = this->rowCount();
    this->insertRow(new_row);
    for (int column=0; column<count_items; ++column)
    {
        QTableWidgetItem* new_item = new QTableWidgetItem;
        new_item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        new_item->setBackgroundColor(Qt::white);
        setItem(new_row, column, new_item);
        if (column == col_price  ||  column == col_quantity)
            new_item->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
        else if(column == col_aditional_code  ||  column == col_request_id)
            new_item->setTextAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    }
    update_item(new_row, item);
}

void QHistoricTable::set_historic(mtk::CountPtr<mtk::trd::hist::order_historic2>  _order_historic)
{
    mtk::CountPtr<mtk::list<mtk::trd::hist::order_historic_item> >   hist_items =   _order_historic->get_items_list();


    MTK_CONNECT_THIS(_order_historic->signal_new_item_added, new_item_added);
    MTK_CONNECT_THIS(_order_historic->signal_modified_item, modified_item);


    this->setRowCount(0);

    for(mtk::list<mtk::trd::hist::order_historic_item>::reverse_iterator it = hist_items->rbegin(); it != hist_items->rend(); ++it)
        add_item(*it);

    order_historic = _order_historic;
}

void  QHistoricTable::new_item_added(const mtk::trd::hist::order_historic_item& item)
{
    add_item(item);
}

void        QHistoricTable::modified_item(int pos, const  mtk::trd::hist::order_historic_item&  item)
{
    if(pos >=  this->rowCount())
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "qhistorictable", MTK_SS("error locating item on pos " << pos << " this->rowCount()==" << this->rowCount()),
                                 mtk::alPriorError, mtk::alTypeLogicError));

    update_item(this->rowCount() - pos - 1, item);
}
