#include <iostream>

#include "support/foreach.hpp"
#include "support/configfile.h"
#include "support/alarm.h"
#include "support/list.hpp"
#include "support/nullable.hpp"



int main(void)
{

    try
    {

        mtk::ConfigFile config("config.cfg");
        //config.LoadFromFile("config.cfg");

        //  obtener valores de varios niveles
        std::cout << config.GetValue("ADMIN.pr1").Get() << std::endl;
        std::cout << config.GetValue("ADMIN2.pr2").Get() << std::endl;
        std::cout << config.GetValue("ADMIN.pr2").Get() << std::endl;
        std::cout << config.GetValue("ADMIN.ADMIN11.pr11").Get() << std::endl;
        std::cout << config.GetValue("ADMIN.ADMIN11.ADMIN111.pr111").Get() << std::endl;
        std::cout << config.GetValue("ADMIN.ADMIN11.ADMIN111.pr112").Get() << std::endl;
        std::cout << config.GetValue("ADMIN.pr3").Get() << std::endl;

        //  Modificando una entrada con Modif
        config.Modif("ADMIN.ADMIN11.ADMIN111.pr111", "MODIFICADO...");
        std::cout << config.GetValue("ADMIN.ADMIN11.ADMIN111.pr111").Get() << std::endl;


        //  obtener los nodos de un nodo
        std::cout << "NODES..."  << std::endl;
        mtk::list<std::string>  vnodes0 = config.GetNodes("ADMIN");
        MTK_FOREACH(itnodes, vnodes0)
	      std::cout << *itnodes << std::endl;


        //  obtener los nodos del raíz
        {
            std::cout << "NODES..."  << std::endl;
            mtk::list<std::string>  vnodes1 = config.GetNodes("");
            MTK_FOREACH(itnodes, vnodes1)
                std::cout << *itnodes << std::endl;
        }


        //  obtener las propiedades
        {
            std::cout << "PROPERTIES..."  << std::endl;
            mtk::list<mtk::tuple<std::string, mtk::ConfigFile::enPropertyType> >  vproperties = config.GetProperties("ADMIN");
            MTK_FOREACH(itnodes, vproperties)
                std::cout << itnodes->_0 << std::endl;
        }

        //  obtener las propiedades
        {
            std::cout << "PROPERTIES..."  << std::endl;
            mtk::list<mtk::tuple<std::string, mtk::ConfigFile::enPropertyType> >  vproperties = config.GetProperties("ADMIN.ADMIN11");
            MTK_FOREACH(itnodes, vproperties)
            {
                if (itnodes->_1 == mtk::ConfigFile::ptValue)    std::cout << "type value:  ";
                if (itnodes->_1 == mtk::ConfigFile::ptList)     std::cout << "type list :  ";
                std::cout << itnodes->_0 << std::endl;
            }
        }
        
        
        //  leemos una lista y lo escribimos por la pantalla
        {
            std::cout << "UNA LISTA..."  << std::endl;
            mtk::list<std::string>   listitems = config.GetList("ADMIN2.lista").Get();  //  ya lo sé, no compruebo HasValue
            MTK_FOREACH(items, listitems) 
                std::cout << *items << std::endl;
        }


        //  Dejar una entrada en blanco con Modif "" (esto deja en el fichero el símbolo ~)
        config.Modif("ADMIN.EstaSeBorra", "");

        //  crear una entrada con create
        config.Create("ADMIN.EstaEsNUEVA", "MUUUUYYYY NUEVAAAAAA");

        //  tiene símbolos no permitidos en el identificador   (lanzaría una excepción)
        //config.Modif("ADMIN.aaaa Ñá=()", "NOooooop");


//        //  intentamos escribir en una propiedad cuyos nodos no existen
//        //  lanza una excepción
//        config.Modif("ADMIN.LALA.MAL", "KLL");

//        //  intentamos borrar un valor en una sección
//        //  lanza una excepción
//        config.Delete("ADMIN");
//        config.Delete("ADMIN.ADMIN11");

//        //  intentamos modificar un valor en una sección
//        //  lanza una excepción
//        config.Modif("ADMIN", "aaa");
//        config.Modif("ADMIN.ADMIN11", "aaaaa");
//        config.ModifOrCreate("ADMIN.ADMIN11", "aaaaa");

        std::cout << "saving... " << std::endl;
        //  fin, grabamos
        config.SaveToFile("config_saved.cfg");
        //  lo normal sería grabar con config.Save();

		//	prueba de expansión de una variable
		std::cout << config.GetValue("ADMIN2.pr_con_var").Get() << std::endl;

        std::cout << "FIN..... " << std::endl;

	#include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION (std::cout<< , "main", "nothing more")

    std::cout << "MAL..... " << std::endl;
    #include "support/release_on_exit.hpp"
    return -1;

}


void mtk::AlarmMsg(const mtk::Alarm& al)
{
    std::cout << "ouch...: "  << al << std::endl;

}
