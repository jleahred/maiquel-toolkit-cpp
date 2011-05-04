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
    qtablealarms.cpp \
    ../../../../src/components/*.cpp \
    ../../../../src/components/acs/*.cpp* \
    ../../../../src/components/admin/msg*.cpp

HEADERS  += monitor.h \
    qplaintexteditcommand.h \
    qlistprocesses.h \
    qtablealarms.h \
    ../../../../src/components/*.h* \
    ../../../../src/components/acs/*.h* \
    ../../../../src/components/admin/msg*.h

FORMS    += monitor.ui


INCLUDEPATH = .   ../../../../src/

LIBS =  -L../../../../lib/  -lmtk_qpid -lmtksupport -lyaml -lqpidclient -lqpidmessaging -lqpidtypes
