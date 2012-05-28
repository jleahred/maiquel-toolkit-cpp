//---------------------------------------------------------------------------

#include "support/timer.h"
#include "support/exec_max_frec.h"
#include "support/alarm.h"


//---------------------------------------------------------------------------





//---------------------------------------------------------------------------

//  CLASE QUE RECIBE LLAMADAS AUTOMÁTICAS FRECUENTES

//---------------------------------------------------------------------------



class SoloTimer : public mtk::SignalReceptor    //<<-------------------
{
    typedef     SoloTimer  CLASS_NAME;  //<<-------------------

private:

public:

    SoloTimer() {
        MTK_TIMER_1S(OnTimer1s);         //<<-------------------
        MTK_TIMER_1C(OnTimer1c);         //<<-------------------
    };

    void OnTimer1c(void) {
        std::cout << "c";
        std::cout.flush();
    };


    void OnTimer1s(void) {

        MTK_EXEC_MAX_FREC_NO_FIRST(mtk::dtSeconds(6))
            static int contador=0;
            if (++contador > 2)
                mtk::stop_timer();
            static mtk::DateTime prevTQ = mtk::dtNowLocal();

            std::cout   << std::endl
                        << "__NR__:  MTK_TIMER 7 SEGUNDOS_________"
                        << "  " << (mtk::dtNowLocal()-prevTQ)
                        <<  std::endl;
            prevTQ = mtk::dtNowLocal();
        MTK_END_EXEC_MAX_FREC
    };
};




void timerFunc(void)
{
        MTK_EXEC_MAX_FREC_NO_FIRST_S(mtk::dtSeconds(5))
	    MTK_TIMER_1SF_STOP(timerFunc);

            std::cout   << std::endl
                        << "__NR__:  MTK_TIMER 5 SEGUNDOS !!!!!!!!!!!!"
                        <<  std::endl;
        MTK_END_EXEC_MAX_FREC
}




//---------------------------------------------------------------------------

//          M A I N

//---------------------------------------------------------------------------

int main(int /*argc*/, char** /*argv[]*/)
{

    try {

        SoloTimer st;

        MTK_TIMER_1SF(timerFunc);


        mtk::start_timer_wait_till_end();




        #include "support/release_on_exit.hpp"
        return 0;
    } 
    MTK_CATCH_CALLFUNCION(std::cout << , "main", "nothing more to add")

    #include "support/release_on_exit.hpp"
    return -1;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

//  RECEPTOR ALARMAS SALIDA GENERAL

//---------------------------------------------------------------------------

void mtk::AlarmMsg (const Alarm& alarma)
{
        std::cout << "\n\r";
        std::cout << std::endl << "ALARMA SALIDA..." << alarma <<  std::endl ;
        std::cout << alarma << std::endl ;
}



