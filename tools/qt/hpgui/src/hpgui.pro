# -------------------------------------------------
# Project created by QtCreator 2009-12-12T22:42:07
# -------------------------------------------------

#QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -std=gnu++0x


TARGET = hpgui
TEMPLATE = app
SOURCES +=     *.cpp \
    /home/maiquel/develop/mtk/src/support/*.cpp \
    /home/maiquel/develop/mtk/src/support/re/*.cpp \
    /home/maiquel/develop/mtk/src/support/re/pcre/*.c \
    /home/maiquel/develop/mtk/src/support/hp/*.cpp

HEADERS += *.h
INCLUDEPATH += /home/maiquel/develop/mtk/src
FORMS += hpgui.ui
RESOURCES += 

LIBS = -L../../../../../mtk/lib  -lyaml