#include <iostream>

#include "support/alarm.h"
#include "hell/asocmem0.h"



void assign_value(const std::string& value, std::string& write_in)
{
    //  oportunidad para comprobar los tipos...
    write_in = value;
}



int main()
{


    hell::asoc_mem0 memory;
    memory.signal_error.connect(&mtk::AlarmMsg);
    memory.signal_assign_to.connect(&assign_value);

    //  declaramos e inicializamos una variable
    memory.declare_var("hola", "pajarito sin cola");
    //  reescribimos una variable
    memory.write_var("hola", "cara de bola");
    //  ver resultado
    std::cout << memory.read_var("hola");
    //  inciamos un ámbito nuevo
    memory.begin_scope();
    //  acceso  variable no existente
    std::cout << memory.read_var("holaa") << std::endl;
    //  declaración e incialización de variable
    memory.declare_var("hasta_luego", "cara de huevo");
    //  visualización de variable
    std::cout << memory.read_var("hasta_luego") << std::endl;
    //  cerramos ámbito
    memory.end_scope();
    //  verificamos que ya no tenemos acceso a la variable que salió de ámbito
    std::cout << memory.read_var("hasta_luego") << std::endl;




    memory.declare_var("2222", "prueba22222");
    //  inciamos un ámbito nuevo
    memory.begin_scope();
        //  reescribimos una variable
        memory.write_var("2222", "222222222222222222");
        //  ver resultado
        std::cout << memory.read_var("2222") << "!!!!!!!!!" << std::endl;
        //  cerramos ámbito
    memory.end_scope();
    //  verificamos que el valor se mantiene
    std::cout << memory.read_var("2222") << std::endl;


    //  inciamos un ámbito nuevo
    std::cout << "before create scope " << std::endl;
    memory.begin_scope();
        memory.declare_var("333", "prueba22222");
        //  reescribimos una variable
        memory.write_var("333", "33333333333333333333");
        //  ver resultado
        std::cout << memory.read_var("333") << "!!!!!!!!!" << std::endl;
        //  cerramos ámbito
    std::cout << "before end scope " << std::endl;
    memory.end_scope();
    std::cout << "after end scope " << std::endl;
    //  verificamos que el valor se mantiene
    std::cout << memory.read_var("333") << std::endl;


    //  inciamos un ámbito nuevo
    memory.declare_var("44", "0");
    std::cout << "before create scope 44" << std::endl;
    memory.begin_scope();
        //  reescribimos una variable
        //memory.write_var("44", "44");
        //  ver resultado
        std::cout << memory.read_var("44") << "!!!!!!!!!" << std::endl;
        std::cout << "before end scope " << std::endl;
	memory.begin_scope();
            //  reescribimos una variable
            memory.write_var("44", "4444");
	    //  ver resultado
	    //std::cout << memory.read_var("44") << "!!!!!!!!!" << std::endl;
	    //  cerramos ámbito
	    std::cout << "before end scope " << std::endl;
        //  cerramos ámbito
	memory.end_scope();
    //  cerramos ámbito
    memory.end_scope();
    std::cout << "after end scope " << std::endl;
    //  verificamos que el valor se mantiene
    std::cout << memory.read_var("44") << std::endl;


    #include "support/release_on_exit.hpp"
    return 0;
}



//---------------------------------------------------------------------------

//  RECEPTOR ALARMAS SALIDA GENERAL

//---------------------------------------------------------------------------

void mtk::AlarmMsg (const mtk::Alarm& alarma)
{
        std::cout << "\n\r";
        std::cout << std::endl << "ALARMA SALIDA..." << std::endl ;
        std::cout << alarma << std::endl ;
}
