/*
    Meter lectura de fichero para la gramática y el texto a parsear

    Opción de compilación completa
    si no hay errores, que seleccione todos los símbolos en la lista de símbolos a mantener
    que ejecute el parsing de la entrada
    si no hay errores, que pase a la solapa de ast

    humbleParser debería de detectar recursión demasiada profunda (infinita) y abortar


    GRAMÁTICA
    ===============

    pasar a formato c++
    pasar desde formato c++

    ¿autocompletar?

    reformatear la gramática


    MÁS
    =============

    Solapa para la configuración donde tendremos los ficheros de configuración y otras posibles opciones


    Prueba para expresiones regulares

    Búsqueda y resalte en gramática e incluso en texto a parsear

    Resalte de la línea activa


*/


#include <iostream>

#include <QtGui/QApplication>
#include "hpgui.h"
#include "support/alarm.h"


int main(int argc, char *argv[])
{
    //QApplication::setStyle("plastique");
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("hp GUI");
    w.show();
    return a.exec();
}

