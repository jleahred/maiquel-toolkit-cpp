
#include <iostream>



#include "support/alarm.h"
#include "support/string_codec.h"






void mtk::AlarmMsg (const mtk::Alarm& error)
{
    std::cout << error.message;
}




int main()
{


    mtk::CodecStringList csl1;
    mtk::CodecStringList csl2;


//    std::list<std::string> list1;
//    list1.push_back("hola paj{}}arito sin cola");
//    list1.push_back("hasta luego, cara huevo");
//    list1.push_back("hola \\\\ queso de bola");
//
//    std::list<std::string> list2;
//    list2.push_back("{Esta, es,, la lista 2");
//    list2.push_back(csl1.Encode(list1));
//    list2.push_back("pues e{s{oooo  ");
//    list2.push_back("ala... a pa}{rl\\\\aaaaa.");

    std::list<std::string> list1;
    list1.push_back("hola pajarito sin cola");
    list1.push_back("hasta luego, cara huevo");
    list1.push_back("hola \\\\ queso de bola");

    std::list<std::string> list2;
    list2.push_back("Esta, es,, la lista 2");
    list2.push_back(csl1.Encode(list1));
    list2.push_back("pues esoooo  ");
    list2.push_back("ala... a parl\\\\aaaaa.");


//    csl1.InitEncode();
//    csl1.AddString("hola pajarito sin cola");
//    csl1.AddString("hasta luego cara huevo");
//    csl1.AddString("hola queso de bola");
//
//    csl2.InitEncode();
//    csl2.AddString("Esta, es,, la lista 2");
//    csl2.AddString(csl1.Encode());
//    csl2.AddString("pues e{s{oooo  ");
//    csl2.AddString("pues e\\s}{oooo  ");

    csl2.Encode(list2);


    std::string coded = csl2.Encode();
    std::cout << coded;





    //  Originales...
    std::cout << std::endl << std::endl << "lista 1... ";
    for(auto its = list1.begin(); its != list1.end(); ++its)
        std::cout << std::endl << *its;
    std::cout << std::endl << std::endl << "lista 2... ";
    for(auto its = list2.begin(); its != list2.end(); ++its)
        std::cout << std::endl << *its;






    std::cout << std::endl << std::endl << std::endl <<  "decoding...";


    mtk::CodecStringList csl3;
    //coded = "lñj" + coded;
    mtk::CountPtr<std::list<std::string> > cptrLSDecoded = csl3.Decode(coded);


    for (std::list<std::string>::iterator it = cptrLSDecoded->begin();
            it != cptrLSDecoded->end();
            ++it)
        std::cout << std::endl << *it;




    mtk::CodecStringProperties csp("", '\\', '\n');

    csp.AddProperty("hol=a", "pajarito sin cola");
    csp.AddProperty("aaa", "adio=ssss");
    csp.AddProperty("b=b==bbb", "2222s2d2d2d22");
    csp.AddProperty("ccccc", "33333ed33e3d3d3dd33");


    std::cout << std::endl <<  csp.Encode();


    std::cout << std::endl;


    #include "support/release_on_exit.hpp"
    return 0;
}



