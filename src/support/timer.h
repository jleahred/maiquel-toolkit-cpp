#ifndef mtk_TimerH
#define mtk_TimerH




#include <iostream>     //  no es debug, revisar porqué es necesario esto

#include "support/signalslot.hpp"
#include "support/alarm.h"





#if (MTK_PLATFORM == MTK_WIN_PLATFORM)


    #include <windows.h>


#endif






#define MTK_TIMER_1S(__METHOD_NAME1__)\
        mtk::Timer::instance()->signal1s.connect(this, &std::remove_reference<decltype(*this)>::type::__METHOD_NAME1__);


#define MTK_TIMER_1S_STOP(__METHOD_NAME1__)\
        mtk::Timer::instance()->signal1s.disconnect(this, &std::remove_reference<decltype(*this)>::type::__METHOD_NAME1__);




#define MTK_TIMER_1C(__METHOD_NAME1__)\
        mtk::Timer::instance()->signal1c.connect(this, &std::remove_reference<decltype(*this)>::type::__METHOD_NAME1__);

#define MTK_TIMER_1C_STOP(__METHOD_NAME1__)\
        mtk::Timer::instance()->signal1c.disconnect(this, &std::remove_reference<decltype(*this)>::type::__METHOD_NAME1__);



#define MTK_TIMER_1D(__METHOD_NAME1__)\
        mtk::Timer::instance()->signal1d.connect(this, &std::remove_reference<decltype(*this)>::type::__METHOD_NAME1__);

#define MTK_TIMER_1D_STOP(__METHOD_NAME1__)\
        mtk::Timer::instance()->signal1d.disconnect(this, &std::remove_reference<decltype(*this)>::type::__METHOD_NAME1__);





//  para funciones

#define MTK_TIMER_1SF(__METHOD_NAME1__)\
        mtk::Timer::instance()->signal1s.connect(&__METHOD_NAME1__);


#define MTK_TIMER_1SF_STOP(__METHOD_NAME1__)\
        mtk::Timer::instance()->signal1s.disconnect(&__METHOD_NAME1__);




#define MTK_TIMER_1CF(__METHOD_NAME1__)\
        mtk::Timer::instance()->signal1c.connect(&__METHOD_NAME1__);

#define MTK_TIMER_1CF_STOP(__METHOD_NAME1__)\
        mtk::Timer::instance()->signal1c.disconnect(&__METHOD_NAME1__);



#define MTK_TIMER_1DF(__METHOD_NAME1__)\
        mtk::Timer::instance()->signal1d.connect(&__METHOD_NAME1__);

#define MTK_TIMER_1DF_STOP(__METHOD_NAME1__)\
        mtk::Timer::instance()->signal1d.disconnect(&__METHOD_NAME1__);





namespace mtk {





class Timer : public SignalReceptor
{
    mtk::non_copyable nc;


private:

    static Timer* pinstance;



    Timer() {};


public:
    static Timer* instance(void) {
        if (pinstance==0)
        {
            pinstance = new Timer();
        }
        return pinstance;
    };





public:

    mtk::Signal<>   signal1c;
    mtk::Signal<>   signal1d;
    mtk::Signal<>   signal1s;

    mtk::Signal<>   signal_async_inmediate;





    static void __internal_nevercall_me_release_on_exit(void)
    {
        delete pinstance;
        pinstance = 0;
    }
    #define  RELEASE_Timer__internal_nevercall_me_release_on_exit   mtk::Timer::__internal_nevercall_me_release_on_exit();


};



//------------------------------------------------------------------------

void start_timer_wait_till_end(void);

void stop_timer(void);




void __internal_check_timers(void);


};      //  end namespace mtk

#endif
