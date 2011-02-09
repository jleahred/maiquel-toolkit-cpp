#include "support/alarm.h"
#include <iostream>



void mtk::AlarmMsg(const mtk::Alarm& error)
{
    std::cout << "__NR__:  " << error << std::endl;
}



int main()
{

    //  simple throw catch    --------------------------------------------------
    try
    {
        throw mtk::Alarm(MTK_HERE, "exalarm", "throwing", mtk::alPriorError);
    }
    catch(const mtk::Alarm& alarm)
    {
        std::cout << "__NR__:  " << "catched alarm  " << alarm << std::endl;
    }


    //  throw  and  rethrow --------------------------------------------------
    std::cout << std::endl;
    try
    {
        try
        {
            throw mtk::Alarm(MTK_HERE, "exalarm", "throwing", mtk::alPriorError);
        }
        MTK_CATCH_RETHROW(MTK_HERE, "MTK_CATCH_RETHROW")
    }
    catch(const mtk::Alarm& alarm)
    {
        std::cout << "__NR__:  " << "catched alarm  " << alarm << std::endl;
    }


    //  throw  and  call function  -----------------------------------------
    std::cout << std::endl;
    try
    {
        try
        {
            throw mtk::Alarm(MTK_HERE, "exalarm", "throwing", mtk::alPriorError);
        }
        MTK_CATCH_CALLFUNCION(std::cout << "__NR__:  "<<, MTK_HERE, "testing call function")
    }
    catch(const mtk::Alarm& alarm)
    {
        std::cout << "__NR__:  " << "catched alarm  " << alarm << std::endl;
    }


    //  notifying with no flow interuption   ------------------------------
    std::cout << std::endl;
    mtk::AlarmMsg( mtk::Alarm(MTK_HERE, "exalarm",  "no interuption notification", mtk::alPriorWarning, mtk::alTypeUnknown) );


    //  stacking alarms   --------------------------------------------------
    std::cout << std::endl;
    mtk::Alarm a7 = mtk::Alarm(MTK_HERE, "exalarm",  "stacking", mtk::alPriorWarning, mtk::alTypeUnknown);
    a7.Add( mtk::Alarm(MTK_HERE, "exalarm",  "stacked", mtk::alPriorWarning, mtk::alTypeUnknown) );
    mtk::AlarmMsg(a7);


    #include "support/release_on_exit.hpp"
    return 0;
}



