
#include <iostream>


#include "support/async_delayed_call.hpp"            //  <1>


#include "support/call_later.h"


#define NO_COMPILAR false




class Pr  : public mtk::SignalReceptor          //  <2>
{
public:

    void AsyncDelayedCall_Overflow(std::string description) //  <3>
    {
        std::cout << description << std::endl;
    }

    #if NO_COMPILAR             //  <4>
    void MandaNumero(int p)
    #endif
    MTK_ASYNC_DELAYED_CALL_DI(MandaNumero, int, 1, mtk::dtMilliseconds(100), 200)    //  <5>

        std::cout << p << std::endl ;

    MTK_ASYNC_DELAYED_CALL_END_I            //  <6>


};

void stop(const int&)
{
    mtk::stop_timer();
}


int main()
{
    Pr pr1;


    for(int i=0; i<205; ++i)   //  <7>
    {
        std::cout << "Que lo mandoooo..."  << i << std::endl;
        pr1.MandaNumero(i);
    }

    MTK_CALL_LATER1S_F(mtk::dtSeconds(25), 0, stop);

    mtk::start_timer_wait_till_end();

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
