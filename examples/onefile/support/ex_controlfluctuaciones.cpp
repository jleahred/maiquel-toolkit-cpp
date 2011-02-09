#include <iostream>

#include "support/controlfluctuaciones.h"
#include "support/mtk_string.h"
#include "support/alarm.h"





int main()
{
    try
    {

        mtk::DateTime start(mtk::dtNowLocal());
        mtk::ControlFluctuacionesSingle cf;
        mtk::dtTimeQuantity  fluctPrev (mtk::dtSeconds(0));
        mtk::dtTimeQuantity  fluct5Min (mtk::dtSeconds(0));

        cf.CheckFluctuacion(mtk::dtNowLocal()-start).assign(fluctPrev, fluct5Min);
        std::cout << std::endl;
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;

        cf.CheckFluctuacion(mtk::dtNowLocal()-start).assign(fluctPrev, fluct5Min);
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;

        cf.CheckFluctuacion(mtk::dtNowLocal()-start + mtk::dtSeconds(-3)).assign(fluctPrev, fluct5Min);
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;


        cf.CheckFluctuacion(mtk::dtNowLocal()-start + mtk::dtSeconds(-30)).assign(fluctPrev, fluct5Min);
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;

        cf.CheckFluctuacion(mtk::dtNowLocal()-start + mtk::dtSeconds(30)).assign(fluctPrev, fluct5Min);
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;

        cf.CheckFluctuacion(mtk::dtNowLocal()-start + mtk::dtSeconds(30)).assign(fluctPrev, fluct5Min);
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;

        cf.CheckFluctuacion(mtk::dtNowLocal()-start ).assign(fluctPrev, fluct5Min);
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;

        cf.CheckFluctuacion(mtk::dtNowLocal()-start ).assign(fluctPrev, fluct5Min);
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;



        //  fluctuaciones pequeñas seguidas
        cf.CheckFluctuacion(mtk::dtNowLocal()-start + mtk::dtMilliseconds(100)).assign(fluctPrev, fluct5Min);
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;
        //  fluctuaciones pequeñas seguidas
        cf.CheckFluctuacion(mtk::dtNowLocal()-start + mtk::dtMilliseconds(200)).assign(fluctPrev, fluct5Min);
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;
        //  fluctuaciones pequeñas seguidas
        cf.CheckFluctuacion(mtk::dtNowLocal()-start + mtk::dtMilliseconds(300)).assign(fluctPrev, fluct5Min);
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;
        //  fluctuaciones pequeñas seguidas
        cf.CheckFluctuacion(mtk::dtNowLocal()-start + mtk::dtMilliseconds(400)).assign(fluctPrev, fluct5Min);
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;


        //  fluctuaciones pequeñas seguidas
        cf.CheckFluctuacion(mtk::dtNowLocal()-start + mtk::dtMilliseconds(-100)).assign(fluctPrev, fluct5Min);
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;
        //  fluctuaciones pequeñas seguidas
        cf.CheckFluctuacion(mtk::dtNowLocal()-start + mtk::dtMilliseconds(-200)).assign(fluctPrev, fluct5Min);
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;
        //  fluctuaciones pequeñas seguidas
        cf.CheckFluctuacion(mtk::dtNowLocal()-start + mtk::dtMilliseconds(-300)).assign(fluctPrev, fluct5Min);
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;
        //  fluctuaciones pequeñas seguidas
        cf.CheckFluctuacion(mtk::dtNowLocal()-start + mtk::dtMilliseconds(-400)).assign(fluctPrev, fluct5Min);
        std::cout << "__NR__:  " << "prev: " << fluctPrev << " \t\t\t5min: " << fluct5Min << std::endl ;


    } catch(const mtk::Alarm& al)
    {
        std::cout << std::endl << al << std::endl ;
    }
}



//---------------------------------------------------------------------------

//  RECEPTOR ALARMAS SALIDA GENERAL

//---------------------------------------------------------------------------

void mtk::AlarmMsg (const mtk::Alarm& alarma)
{
        std::cout << std::endl << "ALARMA SALIDA..." << std::endl ;
        std::cout << alarma << std::endl ;
}