/********************************************************************************
** Form generated from reading UI file 'hpgui.ui'
**
** Created: Thu Dec 2 09:33:32 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HPGUI_H
#define UI_HPGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetClass
{
public:
    QAction *actionCompile_gramar;
    QAction *actionConvert_to_c_code;
    QAction *actionParse;
    QAction *actionRun_Regular_Expresion;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *twMain;
    QWidget *tab_9;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *cbProjects;
    QPushButton *pbProjectsReload;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *cbONCompileGramatTestGotoOutput;
    QSpacerItem *verticalSpacer;
    QPlainTextEdit *pteLoadInfo;
    QWidget *tab;
    QVBoxLayout *verticalLayout_5;
    QSplitter *splitter;
    QPlainTextEdit *pteGramarSource;
    QTabWidget *twGramarInfo;
    QWidget *tab_8;
    QVBoxLayout *verticalLayout_6;
    QPlainTextEdit *pteCompilerOut;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QListWidget *lwSymbols;
    QPushButton *pbSelectAllRules;
    QPushButton *pbLoadSymbols;
    QSpacerItem *horizontalSpacer;
    QWidget *tab_4;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_7;
    QSplitter *splitter_2;
    QTabWidget *twInput;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_3;
    QPlainTextEdit *pteInput;
    QWidget *tab_6;
    QHBoxLayout *horizontalLayout_7;
    QTreeWidget *twAST_parsed;
    QWidget *tab_7;
    QVBoxLayout *verticalLayout_15;
    QPlainTextEdit *pteParsed;
    QPlainTextEdit *pteParsingOut;
    QWidget *tab_10;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout_10;
    QPlainTextEdit *pteRe;
    QPlainTextEdit *pteReInput;
    QPlainTextEdit *pteReOut;

    void setupUi(QWidget *WidgetClass)
    {
        if (WidgetClass->objectName().isEmpty())
            WidgetClass->setObjectName(QString::fromUtf8("WidgetClass"));
        WidgetClass->resize(749, 601);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WidgetClass->sizePolicy().hasHeightForWidth());
        WidgetClass->setSizePolicy(sizePolicy);
        WidgetClass->setContextMenuPolicy(Qt::DefaultContextMenu);
        actionCompile_gramar = new QAction(WidgetClass);
        actionCompile_gramar->setObjectName(QString::fromUtf8("actionCompile_gramar"));
        actionConvert_to_c_code = new QAction(WidgetClass);
        actionConvert_to_c_code->setObjectName(QString::fromUtf8("actionConvert_to_c_code"));
        actionParse = new QAction(WidgetClass);
        actionParse->setObjectName(QString::fromUtf8("actionParse"));
        actionRun_Regular_Expresion = new QAction(WidgetClass);
        actionRun_Regular_Expresion->setObjectName(QString::fromUtf8("actionRun_Regular_Expresion"));
        verticalLayout_4 = new QVBoxLayout(WidgetClass);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        twMain = new QTabWidget(WidgetClass);
        twMain->setObjectName(QString::fromUtf8("twMain"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(twMain->sizePolicy().hasHeightForWidth());
        twMain->setSizePolicy(sizePolicy1);
        twMain->setTabPosition(QTabWidget::North);
        twMain->setTabShape(QTabWidget::Rounded);
        twMain->setElideMode(Qt::ElideNone);
        tab_9 = new QWidget();
        tab_9->setObjectName(QString::fromUtf8("tab_9"));
        verticalLayout_9 = new QVBoxLayout(tab_9);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(tab_9);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        cbProjects = new QComboBox(tab_9);
        cbProjects->setObjectName(QString::fromUtf8("cbProjects"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cbProjects->sizePolicy().hasHeightForWidth());
        cbProjects->setSizePolicy(sizePolicy2);
        cbProjects->setEditable(true);

        horizontalLayout_2->addWidget(cbProjects);

        pbProjectsReload = new QPushButton(tab_9);
        pbProjectsReload->setObjectName(QString::fromUtf8("pbProjectsReload"));

        horizontalLayout_2->addWidget(pbProjectsReload);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_8->addLayout(horizontalLayout_2);

        cbONCompileGramatTestGotoOutput = new QCheckBox(tab_9);
        cbONCompileGramatTestGotoOutput->setObjectName(QString::fromUtf8("cbONCompileGramatTestGotoOutput"));
        cbONCompileGramatTestGotoOutput->setChecked(false);

        verticalLayout_8->addWidget(cbONCompileGramatTestGotoOutput);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer);

        pteLoadInfo = new QPlainTextEdit(tab_9);
        pteLoadInfo->setObjectName(QString::fromUtf8("pteLoadInfo"));
        sizePolicy2.setHeightForWidth(pteLoadInfo->sizePolicy().hasHeightForWidth());
        pteLoadInfo->setSizePolicy(sizePolicy2);

        verticalLayout_8->addWidget(pteLoadInfo);


        verticalLayout_9->addLayout(verticalLayout_8);

        twMain->addTab(tab_9, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(10);
        sizePolicy3.setHeightForWidth(tab->sizePolicy().hasHeightForWidth());
        tab->setSizePolicy(sizePolicy3);
        verticalLayout_5 = new QVBoxLayout(tab);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        splitter = new QSplitter(tab);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        pteGramarSource = new QPlainTextEdit(splitter);
        pteGramarSource->setObjectName(QString::fromUtf8("pteGramarSource"));
        sizePolicy1.setHeightForWidth(pteGramarSource->sizePolicy().hasHeightForWidth());
        pteGramarSource->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("Courier 10 Pitch"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        pteGramarSource->setFont(font);
        pteGramarSource->setContextMenuPolicy(Qt::ActionsContextMenu);
        pteGramarSource->setStyleSheet(QString::fromUtf8("font: 12pt \"Courier 10 Pitch\";"));
        pteGramarSource->setFrameShape(QFrame::Box);
        pteGramarSource->setLineWidth(1);
        pteGramarSource->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        pteGramarSource->setLineWrapMode(QPlainTextEdit::NoWrap);
        splitter->addWidget(pteGramarSource);
        twGramarInfo = new QTabWidget(splitter);
        twGramarInfo->setObjectName(QString::fromUtf8("twGramarInfo"));
        sizePolicy.setHeightForWidth(twGramarInfo->sizePolicy().hasHeightForWidth());
        twGramarInfo->setSizePolicy(sizePolicy);
        twGramarInfo->setTabShape(QTabWidget::Rounded);
        tab_8 = new QWidget();
        tab_8->setObjectName(QString::fromUtf8("tab_8"));
        verticalLayout_6 = new QVBoxLayout(tab_8);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        pteCompilerOut = new QPlainTextEdit(tab_8);
        pteCompilerOut->setObjectName(QString::fromUtf8("pteCompilerOut"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Courier 10 Pitch"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        pteCompilerOut->setFont(font1);
        pteCompilerOut->setStyleSheet(QString::fromUtf8("font: 10pt \"Courier 10 Pitch\";\n"
"\n"
""));
        pteCompilerOut->setFrameShape(QFrame::Box);
        pteCompilerOut->setLineWidth(1);
        pteCompilerOut->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        pteCompilerOut->setLineWrapMode(QPlainTextEdit::NoWrap);

        verticalLayout_6->addWidget(pteCompilerOut);

        twGramarInfo->addTab(tab_8, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_2 = new QVBoxLayout(tab_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lwSymbols = new QListWidget(tab_3);
        lwSymbols->setObjectName(QString::fromUtf8("lwSymbols"));
        lwSymbols->setFrameShape(QFrame::Box);
        lwSymbols->setAlternatingRowColors(true);
        lwSymbols->setSelectionMode(QAbstractItemView::MultiSelection);
        lwSymbols->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(lwSymbols);

        pbSelectAllRules = new QPushButton(tab_3);
        pbSelectAllRules->setObjectName(QString::fromUtf8("pbSelectAllRules"));

        verticalLayout->addWidget(pbSelectAllRules);

        pbLoadSymbols = new QPushButton(tab_3);
        pbLoadSymbols->setObjectName(QString::fromUtf8("pbLoadSymbols"));
        sizePolicy2.setHeightForWidth(pbLoadSymbols->sizePolicy().hasHeightForWidth());
        pbLoadSymbols->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(pbLoadSymbols);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(368, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout);

        twGramarInfo->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        twGramarInfo->addTab(tab_4, QString());
        splitter->addWidget(twGramarInfo);

        verticalLayout_5->addWidget(splitter);

        twMain->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        sizePolicy.setHeightForWidth(tab_2->sizePolicy().hasHeightForWidth());
        tab_2->setSizePolicy(sizePolicy);
        verticalLayout_7 = new QVBoxLayout(tab_2);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        splitter_2 = new QSplitter(tab_2);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        sizePolicy.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy);
        splitter_2->setOrientation(Qt::Vertical);
        twInput = new QTabWidget(splitter_2);
        twInput->setObjectName(QString::fromUtf8("twInput"));
        sizePolicy1.setHeightForWidth(twInput->sizePolicy().hasHeightForWidth());
        twInput->setSizePolicy(sizePolicy1);
        twInput->setTabPosition(QTabWidget::North);
        twInput->setTabShape(QTabWidget::Rounded);
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        verticalLayout_3 = new QVBoxLayout(tab_5);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pteInput = new QPlainTextEdit(tab_5);
        pteInput->setObjectName(QString::fromUtf8("pteInput"));
        pteInput->setFont(font);
        pteInput->setContextMenuPolicy(Qt::ActionsContextMenu);
        pteInput->setStyleSheet(QString::fromUtf8("font: 12pt \"Courier 10 Pitch\";"));
        pteInput->setFrameShape(QFrame::Box);
        pteInput->setLineWidth(1);
        pteInput->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        pteInput->setLineWrapMode(QPlainTextEdit::NoWrap);

        verticalLayout_3->addWidget(pteInput);

        twInput->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        horizontalLayout_7 = new QHBoxLayout(tab_6);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        twAST_parsed = new QTreeWidget(tab_6);
        twAST_parsed->setObjectName(QString::fromUtf8("twAST_parsed"));
        twAST_parsed->setFrameShape(QFrame::Box);
        twAST_parsed->setAlternatingRowColors(true);
        twAST_parsed->setUniformRowHeights(true);
        twAST_parsed->header()->setDefaultSectionSize(300);
        twAST_parsed->header()->setHighlightSections(true);

        horizontalLayout_7->addWidget(twAST_parsed);

        twInput->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        verticalLayout_15 = new QVBoxLayout(tab_7);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(0, 0, 0, 0);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        pteParsed = new QPlainTextEdit(tab_7);
        pteParsed->setObjectName(QString::fromUtf8("pteParsed"));
        pteParsed->setFont(font);
        pteParsed->setStyleSheet(QString::fromUtf8("font: 12pt \"Courier 10 Pitch\";"));
        pteParsed->setFrameShape(QFrame::Box);
        pteParsed->setLineWidth(1);
        pteParsed->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        pteParsed->setLineWrapMode(QPlainTextEdit::NoWrap);

        verticalLayout_15->addWidget(pteParsed);

        twInput->addTab(tab_7, QString());
        splitter_2->addWidget(twInput);
        pteParsingOut = new QPlainTextEdit(splitter_2);
        pteParsingOut->setObjectName(QString::fromUtf8("pteParsingOut"));
        sizePolicy.setHeightForWidth(pteParsingOut->sizePolicy().hasHeightForWidth());
        pteParsingOut->setSizePolicy(sizePolicy);
        pteParsingOut->setFont(font1);
        pteParsingOut->setStyleSheet(QString::fromUtf8("font: 10pt \"Courier 10 Pitch\";\n"
"\n"
""));
        pteParsingOut->setFrameShape(QFrame::Box);
        pteParsingOut->setLineWidth(1);
        pteParsingOut->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        pteParsingOut->setLineWrapMode(QPlainTextEdit::NoWrap);
        splitter_2->addWidget(pteParsingOut);

        verticalLayout_7->addWidget(splitter_2);

        twMain->addTab(tab_2, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName(QString::fromUtf8("tab_10"));
        verticalLayout_11 = new QVBoxLayout(tab_10);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        pteRe = new QPlainTextEdit(tab_10);
        pteRe->setObjectName(QString::fromUtf8("pteRe"));
        pteRe->setContextMenuPolicy(Qt::ActionsContextMenu);
        pteRe->setStyleSheet(QString::fromUtf8("font: 12pt \"Courier 10 Pitch\";"));
        pteRe->setFrameShape(QFrame::Box);
        pteRe->setTabChangesFocus(true);
        pteRe->setLineWrapMode(QPlainTextEdit::NoWrap);

        verticalLayout_10->addWidget(pteRe);

        pteReInput = new QPlainTextEdit(tab_10);
        pteReInput->setObjectName(QString::fromUtf8("pteReInput"));
        pteReInput->setContextMenuPolicy(Qt::ActionsContextMenu);
        pteReInput->setStyleSheet(QString::fromUtf8("font: 12pt \"Courier 10 Pitch\";"));
        pteReInput->setFrameShape(QFrame::Box);
        pteReInput->setTabChangesFocus(true);

        verticalLayout_10->addWidget(pteReInput);

        pteReOut = new QPlainTextEdit(tab_10);
        pteReOut->setObjectName(QString::fromUtf8("pteReOut"));
        pteReOut->setStyleSheet(QString::fromUtf8(""));
        pteReOut->setFrameShape(QFrame::Box);
        pteReOut->setTabChangesFocus(true);

        verticalLayout_10->addWidget(pteReOut);


        verticalLayout_11->addLayout(verticalLayout_10);

        twMain->addTab(tab_10, QString());

        verticalLayout_4->addWidget(twMain);


        retranslateUi(WidgetClass);

        twMain->setCurrentIndex(0);
        twGramarInfo->setCurrentIndex(0);
        twInput->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WidgetClass);
    } // setupUi

    void retranslateUi(QWidget *WidgetClass)
    {
        WidgetClass->setWindowTitle(QApplication::translate("WidgetClass", "Widget", 0, QApplication::UnicodeUTF8));
        actionCompile_gramar->setText(QApplication::translate("WidgetClass", "compile gramar     ", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCompile_gramar->setToolTip(QApplication::translate("WidgetClass", "compile gramar", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCompile_gramar->setShortcut(QApplication::translate("WidgetClass", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        actionConvert_to_c_code->setText(QApplication::translate("WidgetClass", "Convert to c++ code", 0, QApplication::UnicodeUTF8));
        actionParse->setText(QApplication::translate("WidgetClass", "Parse", 0, QApplication::UnicodeUTF8));
        actionParse->setShortcut(QApplication::translate("WidgetClass", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        actionRun_Regular_Expresion->setText(QApplication::translate("WidgetClass", "Run Regular Expresion", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WidgetClass", "Project...", 0, QApplication::UnicodeUTF8));
        pbProjectsReload->setText(QApplication::translate("WidgetClass", "Update", 0, QApplication::UnicodeUTF8));
        cbONCompileGramatTestGotoOutput->setText(QApplication::translate("WidgetClass", "On compile, goto to gramar output", 0, QApplication::UnicodeUTF8));
        twMain->setTabText(twMain->indexOf(tab_9), QApplication::translate("WidgetClass", "config", 0, QApplication::UnicodeUTF8));
        pteGramarSource->setPlainText(QApplication::translate("WidgetClass", "MAIN\n"
"\n"
"MAIN     ::=  SECTION*  \n"
"\n"
"\n"
"SECTION  ::=  sep NAME sep { sep  INFO_SECTION*  sep }  sep       ##transf2->  $(NAME)\n"
"\n"
"\n"
"INFO_SECTION ::=  PROPERTY    endl\n"
"INFO_SECTION ::=  PROPERTY    endl\n"
"INFO_SECTION ::=  COMMENT     endl\n"
"INFO_SECTION ::=  BLANK_LINE  endl\n"
"INFO_SECTION ::=  SECTION       \n"
"\n"
"\n"
"PROPERTY ::= _ NAME _ : _ VALUE  COMMENT\n"
"\n"
"PROPERTY ::= _ NAME _ : _ VALUE _  \n"
"\n"
"\n"
"VALUE  ::= !endl_or_#*  \n"
"\n"
"\n"
"BLANK_LINE  ::=  _  \n"
"\n"
"\n"
"NAME ::= id  \n"
"id        ::=  ([a-zA-Z0-9\\-_]+)  \n"
"\n"
"\n"
"\n"
"COMMENT   ::=   _ # TILL_ENDL\n"
"\n"
"\n"
"\n"
"TILL_ENDL ::=  !endl*  \n"
"TILL_ENDL ::=  !endl*  \n"
"\n"
"\n"
"\n"
"{   ::= '{'  \n"
"}   ::= '}'  \n"
":   ::= ':'  \n"
"#   ::= '#'  \n"
"_   ::= ([ \\t]*)  \n"
"sep ::= __isspace*__  \n"
"\n"
"\n"
"space           ::= __isspace__  \n"
"!endl_or_#       ::=  !([\\n\\r#])  \n"
"endl            ::=  __endl__  \n"
"!endl            ::=  !([\\n\\r])  \n"
"", 0, QApplication::UnicodeUTF8));
        pteCompilerOut->setPlainText(QApplication::translate("WidgetClass", "compiler output", 0, QApplication::UnicodeUTF8));
        twGramarInfo->setTabText(twGramarInfo->indexOf(tab_8), QApplication::translate("WidgetClass", "Compiler output", 0, QApplication::UnicodeUTF8));
        pbSelectAllRules->setText(QApplication::translate("WidgetClass", "select ALL", 0, QApplication::UnicodeUTF8));
        pbLoadSymbols->setText(QApplication::translate("WidgetClass", "Update", 0, QApplication::UnicodeUTF8));
        twGramarInfo->setTabText(twGramarInfo->indexOf(tab_3), QApplication::translate("WidgetClass", "mantain Nodes (ast)", 0, QApplication::UnicodeUTF8));
        twGramarInfo->setTabText(twGramarInfo->indexOf(tab_4), QApplication::translate("WidgetClass", "Graph", 0, QApplication::UnicodeUTF8));
        twMain->setTabText(twMain->indexOf(tab), QApplication::translate("WidgetClass", "Gramar", 0, QApplication::UnicodeUTF8));
        pteInput->setPlainText(QApplication::translate("WidgetClass", "ADMIN\n"
"{\n"
"    IdReloj:1234\n"
"    ProcessName:TEST_FBINSERT\n"
"    ProcessPriority:High\n"
"\n"
"    # pueden leerse de global (comunes)\n"
"    Production:No\n"
"    Market:~\n"
"    TibcoDaemon:128.2.254.100:7500\n"
"    TibcoNetwork:~\n"
"\n"
"\n"
"    TibcoServices\n"
"    {\n"
"        Client:03\n"
"        Server:02\n"
"        Service:01\n"
"        Other:07\n"
"        Pepe:09\n"
"    }\n"
"}\n"
"\n"
"DBPR\n"
"{\n"
"    SERVER: 128.2.8.44\n"
"    NAME: MABE\n"
"    USER: SYSDBA\n"
"}\n"
"\n"
"DBLOCALPR\n"
"{\n"
"    SERVER: 128.2.7.188\n"
"    NAME: testfbinsert\n"
"    USER: SYSDBA\n"
"}\n"
"\n"
"", 0, QApplication::UnicodeUTF8));
        twInput->setTabText(twInput->indexOf(tab_5), QApplication::translate("WidgetClass", "INPUT", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = twAST_parsed->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("WidgetClass", "VALUE", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("WidgetClass", "NAME", 0, QApplication::UnicodeUTF8));
        twInput->setTabText(twInput->indexOf(tab_6), QApplication::translate("WidgetClass", "AST", 0, QApplication::UnicodeUTF8));
        pteParsed->setPlainText(QString());
        twInput->setTabText(twInput->indexOf(tab_7), QApplication::translate("WidgetClass", "OUTPUT", 0, QApplication::UnicodeUTF8));
        pteParsingOut->setPlainText(QApplication::translate("WidgetClass", "parsing messages", 0, QApplication::UnicodeUTF8));
        twMain->setTabText(twMain->indexOf(tab_2), QApplication::translate("WidgetClass", "Testing", 0, QApplication::UnicodeUTF8));
        pteRe->setPlainText(QApplication::translate("WidgetClass", "Hola ([^ ]+) sin (.*)", 0, QApplication::UnicodeUTF8));
        pteReInput->setPlainText(QApplication::translate("WidgetClass", "Hola pajarito sin cola", 0, QApplication::UnicodeUTF8));
        twMain->setTabText(twMain->indexOf(tab_10), QApplication::translate("WidgetClass", "Regular expresions", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WidgetClass: public Ui_WidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HPGUI_H
