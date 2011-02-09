//---------------------------------------------------------------------------

#include <iostream>
#include "support/debug/checkscopetime.h"
#include "support/alarm.h"

//---------------------------------------------------------------------------

double sumr (double val)
{
    mtk::CheckScopeTime cs("sumr");
    if (val>1)
        return sumr(val-1) + val;
    else
        return val;
}



double suml (double val)
{
    int till = int(val);
    double result = 1.;
    for (int i=1; i<=till; i++)
    {
        mtk::CheckScopeTime cs("suml");
        result += i;
    }
    return result;
}


double suml2 (double val)
{
    mtk::CheckScopeTime cs("suml2");
    double result = 1.;
    for (int i=1; i<=val; i++)
    {
        result += i;
    }
    return result;
}

double suml3 (double val)
{
    mtk::CheckScopeTime cs("suml3");
    int till = int(val);
    double result = 1.;
    for (int i=1; i<=till; i++)
        result += i;
    return result;
}


double suml4 (double val)
{
    int till = int(val);
    mtk::CheckScopeTime cs("suml4");
    int result = 1;
    for (int i=1; i<=till; i++)
        result += i;

    return double(result);
}



int main(int /*argc*/, char** /*argv[]*/)
{
    std::cout << "sum recursivo... "  << sumr (10000) << std::endl;
    std::cout << "sum lineal   ... "  << suml (1000000) << std::endl;
    std::cout << "sum lineal2  ... "  << suml2(100000000) << std::endl;
    std::cout << "sum lineal3  ... "  << suml3(100000000) << std::endl;
    std::cout << "sum lineal4  ... "  << suml4(100000000) << std::endl;
    
    std::cout << std::endl << std::endl;
    
    mtk::CheckScopeTime::PrintTimes();

    std::cout << std::endl << std::endl;
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

//  RECEPTOR ALARMAS SALIDA GENERAL

//---------------------------------------------------------------------------

void mtk::AlarmMsg (const Alarm& alarma)
{
        std::cout << "ouch... " << alarma << std::endl ;
} 
