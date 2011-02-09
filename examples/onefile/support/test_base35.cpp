#include <iostream>
#include "support/misc.h"

#include "support/alarm.h"



int main(void)
{
    std::cout << std::endl << "TEST base35 functions..." << std::endl << std::endl;
    for(int i=0; i<1000000; ++i)
    {
        if(mtk::convert_from_base_35(mtk::convert_to_base_35(i)) != i)
        {
            std::cout << std::endl << "ERROR..." << std::endl;
            break;
        }
        if(i%1000 == 0)
            std::cout << "." << std::flush;
    }

    std::cout <<  std::endl;

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

