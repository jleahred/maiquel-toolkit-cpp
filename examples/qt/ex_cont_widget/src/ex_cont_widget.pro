#-------------------------------------------------
#
# Project created by QtCreator 2010-12-20T09:12:13
#
#-------------------------------------------------

QT       += core gui

#QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -std=gnu++0x


TARGET = ex_cont_widget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


INCLUDEPATH = . ../../../../src/ ../../../../src/qt_components/src

LIBS =  -L../../../../lib  -lqt_components -lmtksupport -lyaml
