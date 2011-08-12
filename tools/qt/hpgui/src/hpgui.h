#ifndef HPGUI_H
#define HPGUI_H

#include <QtGui/QWidget>
#include <QModelIndex>

#include "support/hp/humbleparser.h"

#include "highlighter.h"



class QTreeWidgetItem;


namespace Ui
{
    class WidgetClass;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::WidgetClass *ui;

private slots:
    void on_actionRun_Regular_Expresion_triggered();
    void on_cbProjects_currentIndexChanged(int index);
    void on_pbProjectsReload_clicked();
    void on_pteGramarSource_selectionChanged();
    void on_pbSelectAllRules_clicked();
    void on_pbLoadSymbols_clicked();
    void on_actionParse_triggered();
    void on_actionCompile_gramar_triggered();

private:
    mtk::HumbleParser  hParser;
    mtk::AST_Node_Item astRoot;

    Highlighter* highlighter;

    void FillAST_listTree(const mtk::AST_Node_Item& node, QTreeWidgetItem* item);
};

#endif // HPGUI_H
