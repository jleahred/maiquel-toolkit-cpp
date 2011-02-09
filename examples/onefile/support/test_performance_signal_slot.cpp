#include <iostream>

#include "support/alarm.h"
#include "support/signalslot.hpp"
#include "support/date_time.h"



class class_receptor_do_nothing : public mtk::SignalReceptor
{

public:
    void do_nothing(void) {};
};



void receptor_do_nothing (void)
{

}


int contador = 0;
void count (void)
{
    ++contador;
}



const long REPETITIONS = 10000000L;


int main (int /*argc*/, char** /*argv*/)
{
    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "BUCLE suma entero " << std::endl << std::endl;
    {
	mtk::DateTime  start =  mtk::dtNowLocal();
	int acc=0;
	for (int i=0; i<REPETITIONS; ++i)
	    acc +=i;
	mtk::DateTime end = mtk::dtNowLocal();
	std:: cout << acc << std::endl;
	std::cout << "__NR__:  " << "time: " << end-start << std::endl;
	std::cout << "__NR__:  " << "calls/millisecond: " << REPETITIONS / mtk::ARE_YOU_SURE_YOU_WANT_GetMillisecsDay(end-start) << std::endl;
    }



    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "signal -> función (emit)" << std::endl << std::endl;
    {
	mtk::Signal<>   svoid;

	svoid.connect( receptor_do_nothing );

	mtk::DateTime  start =  mtk::dtNowLocal();
	for (int i=0; i<REPETITIONS; ++i)
	    svoid.emit();

	mtk::DateTime end = mtk::dtNowLocal();

	std::cout << "__NR__:  " << "time: " << end-start << std::endl;
	std::cout << "__NR__:  " << "calls/millisecond: " << REPETITIONS / mtk::ARE_YOU_SURE_YOU_WANT_GetMillisecsDay(end-start) << std::endl;
    }

    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "signal -> función (no emit)" << std::endl << std::endl;
    {
	mtk::Signal<>   svoid;

	svoid.connect( receptor_do_nothing );

	mtk::DateTime  start =  mtk::dtNowLocal();
	for (int i=0; i<REPETITIONS; ++i)
	    svoid();

	mtk::DateTime end = mtk::dtNowLocal();

	std::cout << "__NR__:  " << "time: " << end-start << std::endl;
	std::cout << "__NR__:  " << "calls/millisecond: " << REPETITIONS / mtk::ARE_YOU_SURE_YOU_WANT_GetMillisecsDay(end-start) << std::endl;
    }

    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "signal -> método  (emit)" << std::endl << std::endl;
    {
	mtk::Signal<>   svoid;
	class_receptor_do_nothing class_do_nothing;

	svoid.connect(&class_do_nothing, &class_receptor_do_nothing::do_nothing );

	mtk::DateTime  start =  mtk::dtNowLocal();
	for (int i=0; i<REPETITIONS; ++i)
	    svoid.emit();

	mtk::DateTime end = mtk::dtNowLocal();

	std::cout << "__NR__:  " << "time: " << end-start << std::endl;
	std::cout << "__NR__:  " << "calls/millisecond: " << REPETITIONS / mtk::ARE_YOU_SURE_YOU_WANT_GetMillisecsDay(end-start) << std::endl;
    }

    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "llamada directa función " << std::endl << std::endl;
    {
	mtk::DateTime  start =  mtk::dtNowLocal();
	for (int i=0; i<REPETITIONS; ++i)
	    count();

	mtk::DateTime end = mtk::dtNowLocal();

	std::cout << contador << std::endl;
	contador = 0;

	std::cout << "time: " << end-start << std::endl;
	if (mtk::ARE_YOU_SURE_YOU_WANT_GetMillisecsDay(end-start) == 0)
	    std::cout << "too fast..." << std::endl;
	else
	    std::cout << "__NR__:  " << "calls/millisecond: " << REPETITIONS / mtk::ARE_YOU_SURE_YOU_WANT_GetMillisecsDay(end-start) << std::endl;
    }

    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "signal -> función " << std::endl << std::endl;
    {
	mtk::Signal<>   svoid;

	svoid.connect( count );

	mtk::DateTime  start =  mtk::dtNowLocal();
	for (int i=0; i<REPETITIONS; ++i)
	    svoid();

	mtk::DateTime end = mtk::dtNowLocal();

	std::cout << contador << std::endl;
	contador = 0;

	std::cout << "__NR__:  " << "time: " << end-start << std::endl;
	std::cout << "__NR__:  " << "calls/millisecond: " << REPETITIONS / mtk::ARE_YOU_SURE_YOU_WANT_GetMillisecsDay(end-start) << std::endl;
    }

    #include "support/release_on_exit.hpp"
    return 0;
}


void mtk::AlarmMsg(const mtk::Alarm& alarm)
{
    std::cout << alarm << std::endl;
}

