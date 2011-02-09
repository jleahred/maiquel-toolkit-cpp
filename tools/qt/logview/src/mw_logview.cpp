#include "mw_logview.h"
#include "ui_mw_logview.h"


#include "highlighter.h"



MW_LogView::MW_LogView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MW_LogViewClass)
{
    ui->setupUi(this);

    // code highlight
    highlighter_log = new Highlighter(ui->pteLogText->document());
}

MW_LogView::~MW_LogView()
{
    delete ui;
}
