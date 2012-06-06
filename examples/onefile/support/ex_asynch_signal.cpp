#include <iostream>


#include "support/asynch_signal.hpp"


#include "support/call_later.h"






void called (void)
{
    std::cout << "-0-" << std::endl;
}

void called1 (int& value)
{
    std::cout << "-1-" << "  " << value << std::endl;
}


void stop(const int&)
{
    mtk::stop_timer();
}




int main()
{
    try {

        mtk::async_signal_last<>  signal0(mtk::dtSeconds(10));

        signal0.signal.connect(&called);

        signal0.emit();
        signal0.emit();
        signal0.emit();
        signal0.emit();
        signal0.emit();


        mtk::async_signal_last<int&>    signal1(mtk::dtSeconds(10));
        signal1.signal.connect(&called1);
        int counter=0;
        signal1.emit(++counter);
        signal1.emit(++counter);
        signal1.emit(++counter);
        signal1.emit(++counter);
        signal1.emit(++counter);
        signal1.emit(++counter);
        signal1.emit(++counter);
        signal1.emit(++counter);
        signal1.emit(++counter);



        mtk::async_signal_all<int&>    signal1a(mtk::dtSeconds(2));
        signal1a.signal.connect(&called1);
        counter=0;
        signal1a.emit(++counter);
        signal1a.emit(++counter);
        signal1a.emit(++counter);
        signal1a.emit(++counter);
        signal1a.emit(++counter);
        signal1a.emit(++counter);
        signal1a.emit(++counter);
        signal1a.emit(++counter);
        signal1a.emit(++counter);


        MTK_CALL_LATER1S_F(mtk::dtSeconds(30), 0, stop)

        mtk::start_timer_wait_till_end();






        mtk::start_timer_wait_till_end();


        #include "support/release_on_exit.hpp"
        return 0;

    } MTK_CATCH_CALLFUNCION(std::cout << , "main", "nothig additional to say")

    #include "support/release_on_exit.hpp"
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

