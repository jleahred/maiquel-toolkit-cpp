#-------------------------------------------------
#
# Project created by QtCreator 2010-12-20T09:12:13
#
#-------------------------------------------------

QT       += core gui

TARGET = ex_min_qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


INCLUDEPATH = . ../../../../src/           # <1>

                                        # <2>
LIBS =  -L../../../../lib  -lmtksupport -lyaml -lmtk_qpid -lqpidclient -lqpidmessaging
