#include "support/hp/humbleparser.h"
#include "support/alarm.h"
#include "support/mtk_string.h"

#include <iostream>  // I/O
#include <fstream>   // file I/O
#include <iomanip>   // format manipulation



//#include "support/debug/checkscopetime.h"



std::string GetString2ParseFromFile(const std::string& fileName)
{
    char buffer[4096];
    std::ifstream fText2Transform(fileName.c_str(), std::ios::in);
    std::ostringstream ostext4parse;
    bool first = true;
    while (fText2Transform.getline(buffer, 4096))
    {
        if (!first)
            ostext4parse   << std::endl;
        first = false;
        ostext4parse << std::string(buffer);
    }
    fText2Transform.close();

    return std::string(ostext4parse.str());
}






int main(int argc, char* argv[])
{
//    mtk::CheckScopeTime cs("Main");
//    mtk::HumbleParser  hParser;
//    bool result;
//    std::string result_string;
//        hParser.LoadRulesFromFile("/home/maiquel/tmp/cpp_dep.dhp").assign(result, result_string);
//    if (result==false){
//      std::cout << std::endl << result_string << std::endl;
//      return -1;
//    }

//        std::string string2Parse = GetString2ParseFromFile("/home/maiquel/tmp/mtk/src/support/alarm.h");

//        //bool result;
//        std::string resultTest;
//        mtk::AST_Node_Item astRoot("");
//        hParser.MultiParse(string2Parse).assign(result, resultTest, astRoot);


//        if (result == false)
//        {
//            std::cout << "ERROR PARSING..." << resultTest << std::endl;
//            return -1;
//        }
//        else
//        {
//            std::cout << astRoot.value << std::endl;
//        }

//    std::cout << std::endl << std::endl;
//    cs.Stop();
//    mtk::CheckScopeTime::PrintTimes();
//    std::cout << std::endl << std::endl;
// return 0;











    std::string fileRules;

    if (argc == 1)
    {
        // sin parámetros, es para prueba automática
        fileRules = "test_rules.txt";
    }
    else if (argc == 0)
    {
        std::cout << "Ussage prog_trans_from_file <rules-file> [input-file-list]" << std::endl;
    }
    else if (argc>1)
        fileRules = argv[1];


    //mtk::CheckScopeTime cs("Main");


    mtk::HumbleParser  hParser;
    bool result1;
    std::string result_string;
    hParser.LoadRulesFromFile(fileRules).assign(result1, result_string);

    if (result1==false){
      std::cout << std::endl << result_string << std::endl;
      return -1;
    }


    if (argc > 2)
    {
        for (int contador=2; contador < argc; ++contador)
        {
            std::string string2Parse = GetString2ParseFromFile(std::string(argv[contador]));

            bool result2;
            std::string resultTest;
            mtk::AST_Node_Item astRoot("");
            hParser.MultiParse(string2Parse).assign(result2, resultTest, astRoot);


            if (result2 == false)
            {
                std::cout << "ERROR PARSING..." << resultTest << std::endl;
                return -1;
            }
            else
            {
                std::cout << astRoot.value << std::endl;
            }

        }
    }
    else if (argc==1)
    {
        std::string string2Parse = GetString2ParseFromFile("test_input.txt");

        bool result2;
        std::string resultTest;
        mtk::AST_Node_Item astRoot("");
        hParser.MultiParse(string2Parse).assign(result2, resultTest, astRoot);


        if (result2 == false)
        {
            std::cout << "ERROR PARSING..." << resultTest << std::endl;
            return -1;
        }
        else
        {
            std::cout << astRoot.value << std::endl;
        }
    }
    else if (argc==2)
    {
        //  el input es la entrada estándar
        std::string string2Parse;
        while (std::cin.eof() == false)
        {
	    char next_char = char(std::cin.get());
	    //if (next_char == '\n'  ||  next_char == '\r')
	    //      break;

	    string2Parse += next_char;
        }
	string2Parse = string2Parse.substr(0, string2Parse.size()-2);


        bool result2;
        std::string resultTest;
        mtk::AST_Node_Item astRoot("");
        hParser.MultiParse(string2Parse).assign(result2, resultTest, astRoot);


        if (result2 == false)
        {
            std::cout << "ERROR PARSING..." << resultTest << std::endl;
            return -1;
        }
        else
        {
            std::cout << astRoot.value << std::endl;
        }
    }



    #include "support/release_on_exit.hpp"
    return  0;

    //cs.Stop();

    //std::cout << std::endl << result <<  "  "  <<   resultTest;

    //std::cout << std::endl << std::endl ;

    //std::cout << std::endl << astRoot.value;

    //std::cout << std::endl << "reemplazando... ";     //  ahora el reemplazo es implícito
    //std::cout << std::endl << AST_GetStringNodes(&astRoot);


    //std::cout << std::endl << std::endl;
    //mtk::CheckScopeTime::PrintTimes();
    //std::cout << std::endl << std::endl;



}




//---------------------------------------------------------------------------

//  RECEPTOR ALARMAS SALIDA GENERAL

//---------------------------------------------------------------------------

void mtk::AlarmMsg (const Alarm& alarma)
{
    std::cout << "\n\r";
    std::cout << std::endl << "ALARMA SALIDA..." << std::endl ;
    std::cout << alarma << std::endl ;
}
