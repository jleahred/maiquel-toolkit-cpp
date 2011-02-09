#include "timer.h"

#include "support/exec_max_frec.h"
#include "misc.h"
#include "synchr.h"



namespace mtk {



Timer* Timer::pinstance = 0;

bool stopping = false;



void  call_signal_async_inmediate(void)
{
    try
    {
        Timer::instance()->signal_async_inmediate.emit();
    } catch (const mtk::Alarm& __alarm__) {
        mtk::Alarm  mtkError(
                    MTK_HERE,
                    "call_signal_async_inmediate",
                    std::string("not trapped alarm"),
                    mtk::alPriorCritic
            );
        mtkError.Add(__alarm__);
        mtk::AlarmMsg(mtkError);
    } catch (const std::exception& e) {
        mtk::AlarmMsg(mtk::Alarm(
                    MTK_HERE,
                    "call_signal_async_inmediate",
                    std::string("not trapped alarm  std::exception  ") + std::string(e.what()),
                    mtk::alPriorCritic));
    } catch (...) {
        mtk::AlarmMsg (mtk::Alarm(
                    MTK_HERE,
                    "call_signal_async_inmediate",
                    std::string("not trapped alarm  unknown  ...  "),
                    mtk::alPriorCritic));
    }

    Timer::instance()->signal_async_inmediate.disconnect_all();
}


//----------------------------------------------------------------------
void __internal_check_timers(void)
{
    MTK_EXEC_MAX_FREC_NO_FIRST_S(mtk::dtMilliseconds(8))
        Timer::instance()->signal1c();
        call_signal_async_inmediate();
    MTK_END_EXEC_MAX_FREC

    MTK_EXEC_MAX_FREC_NO_FIRST_S(mtk::dtMilliseconds(90))
        Timer::instance()->signal1d();
        call_signal_async_inmediate();
    MTK_END_EXEC_MAX_FREC

    MTK_EXEC_MAX_FREC_NO_FIRST_S(mtk::dtMilliseconds(990))
        Timer::instance()->signal1s();
        call_signal_async_inmediate();
    MTK_END_EXEC_MAX_FREC
}


void start_timer_wait_till_end(void)
{
    static  Mutex*  mtk_mutex = mtk::get_mtk_mutex();
    mtk_mutex->lock();
    while (stopping == false) {
        mtk_mutex->unlock();
            mtk::sleep( dtMilliseconds(10) );
        mtk_mutex->lock();
        try
        {
            __internal_check_timers();
        } catch (const mtk::Alarm& __alarm__) {
            mtk::Alarm  mtkError(
                        MTK_HERE,
                        "start_timer_wait_till_end",
                        std::string("not trapped alarm"),
                        mtk::alPriorCritic
                );
            mtkError.Add(__alarm__);
            mtk::AlarmMsg(mtkError);
        } catch (const std::exception& e) {
            mtk::AlarmMsg(mtk::Alarm(
                        MTK_HERE,
                        "start_timer_wait_till_end",
                        std::string("not trapped alarm  std::exception  ") + std::string(e.what()),
                        mtk::alPriorCritic));
        } catch (...) {
            mtk::AlarmMsg (mtk::Alarm(
                        MTK_HERE,
                        "start_timer_wait_till_end",
                        std::string("not trapped alarm  unknown  ...  "),
                        mtk::alPriorCritic));
        }
    }
}

void stop_timer(void)
{
    stopping = true;
}

//----------------------------------------------------------------------
};      //  end namespace mtk
