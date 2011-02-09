#include "timer.h"

#include "support/exec_max_frec.h"
#include "misc.h"



namespace mtk {



Timer* Timer::pinstance = 0;

bool stopping = false;






//----------------------------------------------------------------------
void __internal_check_timers(void)
{
    MTK_EXEC_MAX_FREC_NO_FIRST_S(mtk::dtMilliseconds(8))
        Timer::instance()->signal1c();
    MTK_END_EXEC_MAX_FREC

    MTK_EXEC_MAX_FREC_NO_FIRST_S(mtk::dtMilliseconds(90))
        Timer::instance()->signal1d();
    MTK_END_EXEC_MAX_FREC

    MTK_EXEC_MAX_FREC_NO_FIRST_S(mtk::dtMilliseconds(990))
        Timer::instance()->signal1s();
    MTK_END_EXEC_MAX_FREC
}


void start_timer_wait_till_end(void)
{
    while (stopping == false) {
        mtk::sleep( dtMilliseconds(10) );
        try
        {
            __internal_check_timers();
        }
        MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, MTK_HERE, "exception not catched");
    }
}

void stop_timer(void)
{
    stopping = true;
}

//----------------------------------------------------------------------
};      //  end namespace mtk
