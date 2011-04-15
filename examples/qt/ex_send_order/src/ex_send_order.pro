#-------------------------------------------------
#
# Project created by QtCreator 2010-12-21T08:05:29
#
#-------------------------------------------------

QT       += core gui

TARGET = ex_send_order
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
    #../../../../src/qt_components/src/*.cpp \  #  for debug
    #../../../../src/mtk_qpid/*.cpp \  #  for debug
    #../../../../src/components/*.cpp \  #  for debug
    #../../../../src/components/trading/*.cpp \  #  for debug

HEADERS  += mainwindow.h \
    #../../../../src/qt_components/src/*.h  \  # for debug
    #../../../../src/mtk_qpid/*.h \  #  for debug
    #../../../../src/components/*.h   \  # for debug
    #../../../../src/components/trading/*.h   # for debug

FORMS    += mainwindow.ui \
    #../../../../src/qt_components/src/qeditorder.ui   # for debug


INCLUDEPATH = . ../../../../src/ \
    ../../../../src/qt_components/src

LIBS =  -L../../../../lib  -lqt_components -lmtk_components -lmtk_qpid -lmtksupport  -lqpidclient -lqpidmessaging -lphonon
#LIBS =  -L../../../../lib  -lmtksupport  -lqpidclient  # for debug
