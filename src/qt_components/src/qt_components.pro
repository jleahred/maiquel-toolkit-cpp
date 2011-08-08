#-------------------------------------------------
#
# Project created by QtCreator 2011-01-02T23:10:36
#
#-------------------------------------------------

QT       += core gui
QT       += phonon

#QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -std=gnu++0x


TARGET = ../../../lib/qt_components
TEMPLATE = lib
CONFIG += staticlib

SOURCES += *.cpp \
        ../src/qorderbook/*.cpp

HEADERS += *.h \
        ../src/qorderbook/*.h

FORMS    += *.ui ../src/qorderbook/*.ui


INCLUDEPATH = . ../../../src/

LIBS =  -L../../../../lib  -lmtk_comp_trd -lmtk_comp_support -lmtksupport  -lqpidclient
