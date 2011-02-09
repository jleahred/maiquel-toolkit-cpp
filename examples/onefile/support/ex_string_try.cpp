#include <iostream>



#include "support/alarm.h"

#include "support/mtk_string.h"



void mtk::AlarmMsg (const mtk::Alarm& error)
{
    std::cout << error.message;
}




int main()
{
    bool   succes;
    double result_double;
    mtk::s_TRY_stod("9.098", 0.).assign(result_double, succes);
    std::cout << std::endl << result_double << "  " << succes << std::endl;


    std::cout << std::endl << mtk::s_TRY_stod("9.098", 0.)._0;
    std::cout << std::endl << mtk::s_TRY_stod("33_NOO_98", 3.14151926535)._0;
    std::cout << std::endl << mtk::s_TRY_stod("33_NOO_98", 3.14151926535)._1;


    std::cout << std::endl << mtk::s_TRY_stoi("9", 0)._0;
    std::cout << std::endl << mtk::s_TRY_stoi("33_NOO_98", 0)._0;
    std::cout << std::endl << mtk::s_TRY_stoi("33_NOO_98", 0)._1;
    std::cout << std::endl << mtk::s_TRY_stoi("33", 0)._1;


    std::cout << std::endl;
    return 0;
} 
