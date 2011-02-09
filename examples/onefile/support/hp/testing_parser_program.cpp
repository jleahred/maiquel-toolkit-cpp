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






int main(int /*argc*/, char* /*argv*/[])
{
    //mtk::CheckScopeTime cs("Main");
    mtk::HumbleParser  hParser;
    bool result;
    std::string result_string;
    hParser.LoadRulesFromFile("cpp_dep.dhp").assign(result, result_string);
    if (result==false){
	std::cout << std::endl << result_string << std::endl;
	return -1;
    }
    
    std::string string2Parse = GetString2ParseFromFile("../../../../src/support/date_time.h");
    
    //bool result;
    std::string resultTest;
    mtk::AST_Node_Item astRoot("");
    hParser.MultiParse(string2Parse).assign(result, resultTest, astRoot);
    
    
    if (result == false)
    {
	std::cout << "ERROR PARSING..." << resultTest << std::endl;
	return -1;
    }
    else
    {
	std::cout << astRoot.value << std::endl;
    }
    
    std::cout << std::endl << std::endl;
    //cs.Stop();
    //mtk::CheckScopeTime::PrintTimes();
    std::cout << std::endl << std::endl;
    #include "support/release_on_exit.hpp"
    return 0;
    
    
    
    
    
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
