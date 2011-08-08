#-------------------------------------------------
#
# Project created by QtCreator 2010-12-20T09:12:13
#
#-------------------------------------------------

QT       += core gui

#QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -std=gnu++0x


TARGET = ex_min_qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


INCLUDEPATH = . ../../../../src/           # <1>

                                        # <2>
LIBS =  -L../../../../lib  -lmtksupport -lyaml -lmtk_qpid -lqpidclient -lqpidmessaging
