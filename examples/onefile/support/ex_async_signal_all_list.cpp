#include <iostream>


#include "support/asynch_signal.hpp"


#include "support/call_later.h"







void called (const std::string&, const mtk::list<int>& list)
{
    std::cout << "list size " << list.size() << "    -------------------------" << std::endl;
    for(auto it=list.begin(); it!=list.end(); ++it)
        std::cout << *it << std::endl;
}


void stop(const int&)
{
    mtk::stop_timer();
}




int main()
{
    try {

        mtk::async_signal_all_list<std::string, int>  signal1("first", mtk::dtSeconds(10));

        signal1.signal.connect(&called);

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
        signal1.emit(++counter);


        MTK_CALL_LATER1S_F(mtk::dtSeconds(15), 0, stop)



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

