#-------------------------------------------------
#
# Project created by QtCreator 2011-01-02T23:10:36
#
#-------------------------------------------------

QT       += core gui

TARGET = ../../../lib/qt_components
TEMPLATE = lib
CONFIG += staticlib

SOURCES += *.cpp

HEADERS += *.h

FORMS    += *.ui


INCLUDEPATH = . ../../../src/

LIBS =  -L../../../../lib  -lmtk_comp_trd -lmtk_comp_support -lmtksupport  -lqpidclient
