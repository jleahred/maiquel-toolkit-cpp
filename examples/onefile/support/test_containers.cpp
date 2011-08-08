#include "support/vector.hpp"
#include "support/list.hpp"
#include "support/map.hpp"


#include "support/alarm.h"
#include <iostream>




int main(void)
{


    try
    {
        {
            //  prueba con vectores

            mtk::vector<int> vint;

            vint.push_back(5);
            vint.push_back(4);
            vint.push_back(3);
            vint.push_back(2);
            vint.push_back(1);

            std::cout << vint.size() << std::endl;
            std::cout << vint[0] << std::endl;
            std::cout << vint[0] << std::endl;
            std::cout << vint.at(2) << std::endl;
            vint.pop_back();
            vint.push_back(3);
            std::cout << vint.front() << std::endl;


            //  esto lanzaría una excepción
            //std::cout << vint[100] << std::endl;



            //  prueba con mapas  -----------------------------------------

            mtk::map<int, std::string>  mis;
            mis[44] = "lkjlkjlkj";
            mis[55] = "555555";
            mis[33] = "333333";
            mis[44] = "444444";

            std::cout << mis[33] << std::endl;
            std::cout << mis[44] << std::endl;

            std::cout << "tamaño " << mis.size() << std::endl;

            mtk::map<int, std::string>::iterator it = mis.begin();
            for(;it != mis.end(); ++it)
            {
                std::cout << (*it).first << "  ,  " << it->second << std::endl;
            }

            for(auto it2 = mis.begin(); it2 != mis.end(); ++it2)
                std::cout << (*it2).first << "  ,  " << it2->second << std::endl;


            mtk::map<int, std::string>::iterator itf = mis.find(33);
            if (itf== mis.end())
                return -1;
            else
                std::cout << "existe 33  con "  << itf->second << std::endl;

            itf = mis.find(88);
            if (itf== mis.end())
                std::cout << "no existe 88" << std::endl;
            else
                return -1;

            mis.clear();
        }


            //  prueba con listas  -----------------------------------------

            std::cout << "Mínima prueba con listas" << std::endl;
            mtk::list<std::string>  li;
            li.push_back("00000000");
            li.push_back("1111111");
            li.push_back("22222222");
            std::cout << "copia iterator lista" << std::endl;
            mtk::list<std::string>::const_iterator itb;
            itb = li.begin();
            for(auto itl = li.begin(); itl != li.end(); ++itl)
                std::cout << *itl << std::endl;




        //    probar seguros  --------------------------
        int counter=0;

        std::cout << std::endl << "Pruebas de fallos.................." << std::endl;
        //  tratamos de obtener un dato de un iterador que no está inicialiado
        try
        {
            std::cout << ++counter << ".-  tratamos de obtener un dato de un iterador que no está inicialiado" << std::endl;
            mtk::map<int, int>  mii;
            mii[0] = 0;
            mtk::map<int, int>::iterator  it;
            std::cout << it->first << std::endl;
        }
        MTK_CATCH_CALLFUNCION (std::cout << "__NR__:  " << , "OK testing errors", "O K   properly catched")

        //  tratamos de avanzar en un iterador no inicializado
        try
        {
            std::cout << ++counter << ".-  tratamos de avanzar en un iterador no inicializado" << std::endl;
            mtk::map<int, int>  mii;
            mii[0] = 0;
            mtk::map<int, int>::iterator  it;
            ++it;
            //std::cout << (++it)->first << std::endl;
        }
        MTK_CATCH_CALLFUNCION (std::cout << "__NR__:  "<< , "OK testing errors", "O K   properly catched")



        //  tratamos de obtener datos de un iterador que apunta a un mapa vacío
        try
        {
            std::cout << ++counter << ".-  tratamos de obtener datos de un iterador que apunta a un mapa vacío" << std::endl;
            mtk::map<int, int>  mii;
            mtk::map<int, int>::iterator  it = mii.begin();
            std::cout << it->first << std::endl;
        }
        MTK_CATCH_CALLFUNCION (std::cout << "__NR__:  "<< , "OK testing errors", "O K   properly catched")


        //  tratamos de obtener un datos de un iterador cuando su contenedor se ha borrado
        try
        {
            std::cout << ++counter << ".-  tratamos de obtener un datos de un iterador cuando su contenedor se ha borrado" << std::endl;
            mtk::map<int, int>::iterator  it;
            {
                mtk::map<int, int>  mii;
                mii[0]=0;
                it = mii.begin();
                std::cout << "esto bien " << it->first << std::endl;
            }
            std::cout << "esto MAL " << it->first << std::endl;
        }
        MTK_CATCH_CALLFUNCION (std::cout << "__NR__:  "<< , "OK testing errors", "O K   properly catched")

        //  tratamos de avanzar iterador su contenedor se ha borrado (eliminado)
        try
        {
            std::cout << ++counter << ".-  tratamos de avanzar iterador su contenedor se ha borrado (eliminado)" << std::endl;
            mtk::map<int, int>::iterator  it;
            {
                mtk::map<int, int>  mii;
                mii[0]=0;
                it = mii.begin();
                std::cout << "esto bien " << it->first << std::endl;
            }
            ++it;
            std::cout << "esto MAL " << std::endl;
        }
        MTK_CATCH_CALLFUNCION (std::cout << "__NR__:  "<< , "OK testing errors", "O K   properly catched")


        //  tratamos de avanzar en un iterador cuando su contenedor se ha vaciado
        try
        {
            std::cout << ++counter << ".-  tratamos de avanzar en un iterador cuando su contenedor se ha vaciado" << std::endl;
            mtk::map<int, int>::iterator  it;
            {
                mtk::map<int, int>  mii;
                mii[0]=0;
                it = mii.begin();
                mii.clear();
                std::cout << "esto bien " << it->first << std::endl;
            }
        }
        MTK_CATCH_CALLFUNCION (std::cout << "__NR__:  "<< , "OK testing errors", "O K   properly catched")

        //  tratamos de obtener datos de un iterador del que se ha borrado su elemento
        try
        {
            std::cout << ++counter << ".-  tratamos de obtener datos de un iterador del que se ha borrado su elemento" << std::endl;
            {
                mtk::map<int, int>  mii;
                mtk::map<int, int>::iterator  it;
                mii[0]=0;
                it = mii.find(0);
                mii.erase(0);
                std::cout << "esto MALLLLL " << it->first << std::endl;
            }
        }
        MTK_CATCH_CALLFUNCION (std::cout << "__NR__:  "<< , "OK testing errors", "O K   properly catched")



        //  tratamos de avanzar en un iterador que apunta al final
        try
        {
            std::cout << ++counter << ".-  tratamos de avanzar en un iterador que apunta al final" << std::endl;
            mtk::map<int, int>  mii;
            mii[0] = 0;
            mtk::map<int, int>::iterator  it = mii.end();
            std::cout << (++it)->first << std::endl;
        }
        MTK_CATCH_CALLFUNCION (std::cout << "__NR__:  "<< , "OK testing errors", "O K   properly catched")


        //  tratamos de avanzar en un iterador que llegó al final
        try
        {
            std::cout << ++counter << ".-  tratamos de avanzar en un iterador que llegó al final" << std::endl;
            mtk::map<int, int>  mii;
            mii[0] = 0;
            mtk::map<int, int>::iterator  it = mii.begin();
            ++it;       std::cout << "este bien______________" << std::endl;
            ++it;       std::cout << "NNNOOOOOOO______________" << std::endl;//  este tiene que fallar
        }
        MTK_CATCH_CALLFUNCION (std::cout << "__NR__:  "<< , "OK testing errors", "O K   properly catched")

        //  comparar iteradores de diferentes contenedores
        //      esta verificación no es imprescindible, estamos protegidos por el desbordamiento de límite end()
        //      pero no está de más y es barata
        try
        {
            std::cout << ++counter << ".-  comparar iteradores de diferentes contenedores" << std::endl;
            mtk::map<int, int>  mii;
            mtk::map<int, int>  mii2;
            mii[0] = 0;
            mii2[1] = 1;
            mtk::map<int, int>::iterator  it = mii.begin();
            while (it != mii2.end()) {
                ++it;
                std::cout << " it->first  " << it->first << std::endl;
            }
        }
        MTK_CATCH_CALLFUNCION (std::cout << "__NR__:  "<< , "OK testing errors", "O K   properly catched")



        std::cout << std::endl << std::endl << "TIENE BUENA PINTA." << std::endl;
        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION (std::cout<< , "main", "nothing more")

    #include "support/release_on_exit.hpp"
    return -1;


}

void mtk::AlarmMsg(const mtk::Alarm& al)
{
    std::cout << "ouch...: "  << al << std::endl;

}