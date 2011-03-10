#-------------------------------------------------
#
# Project created by QtCreator 2011-03-01T17:45:02
#
#-------------------------------------------------

QT       += core gui

TARGET = monitor
TEMPLATE = app


SOURCES += main.cpp\
        monitor.cpp \
    qplaintexteditcommand.cpp \
    qlistprocesses.cpp \
    qtablealarms.cpp

HEADERS  += monitor.h \
    qplaintexteditcommand.h \
    qlistprocesses.h \
    qtablealarms.h

FORMS    += monitor.ui


INCLUDEPATH = .   ../../../../src/

LIBS =  -L../../../../lib/  -lmtk_components -lmtk_qpid -lmtksupport  -lqpidclient -lqpidmessaging -lqpidtypes
