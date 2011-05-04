#-------------------------------------------------
#
# Project created by QtCreator 2010-12-20T09:12:13
#
#-------------------------------------------------

QT       += core gui

TARGET = ex_cont_widget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


INCLUDEPATH = . ../../../../src/ ../../../../src/qt_components/src

LIBS =  -L../../../../lib  -lqt_components -lmtksupport -lyaml
