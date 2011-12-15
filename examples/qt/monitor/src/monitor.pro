#-------------------------------------------------
#
# Project created by QtCreator 2011-03-01T17:45:02
#
#-------------------------------------------------

QT       += core gui  phonon

#QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -std=gnu++0x


TARGET = monitor
TEMPLATE = app


SOURCES += main.cpp\
        monitor.cpp \
    qplaintexteditcommand.cpp \
    qlistprocesses.cpp \
    qtablealarms.cpp \
    msg_structs.cpp  \
    ../../../../src/components/*.cpp \
    ../../../../src/components/acs/*.cpp* \
    ../../../../src/components/admin/msg*.cpp

HEADERS  += monitor.h \
    qplaintexteditcommand.h \
    qlistprocesses.h \
    qtablealarms.h \
    msg_structs.h  \
    ../../../../src/components/*.h* \
    ../../../../src/components/acs/*.h* \
    ../../../../src/components/admin/msg*.h

FORMS    += monitor.ui


INCLUDEPATH = .   ../../../../src/

LIBS =  -L../../../../lib/  -lmtk_qpid -lyaml  -lmtksupport  -lqpidclient -lqpidmessaging  -lqpidtypes  -lphonon

RESOURCES += \
    monitor.qrc
