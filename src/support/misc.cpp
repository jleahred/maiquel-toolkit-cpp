#include <stdexcept>
#include <stdlib.h>
#include <time.h>
#include <iostream>   


#include "misc.h"
#include "date_time.h"




#if (MTK_PLATFORM == MTK_WIN_PLATFORM)
   #include <float.h>   
#endif



namespace mtk {

    int rand (void)
    {
        static bool initialized = false;

        if (!initialized)
        {
            //srand ( (unsigned int) time(NULL) );      only one second precision
            srand ( (unsigned int) ARE_YOU_SURE_YOU_WANT_GetMillisecsDay(mtk::dtMachineGetTotalMillisecs()) );
            initialized = true;
        }
        return ::rand();
    }






    jmp_buf envJmpDiv0;
    bool    initJumpDiv0= false;

    void bypass_sigfpe(int /*sig_no*/)
    {
	//throw std::runtime_error("FPE error  probably  div0 handler");
//	if (initJumpDiv0)
//	{
	    if( signal(SIGFPE, bypass_sigfpe) == SIG_ERR )
		std::cerr << "div0 handler not initialized";
#if (MTK_PLATFORM == MTK_WIN_PLATFORM)
	    _fpreset();
	    longjmp(envJmpDiv0, 1);
#elif MTK_PLATFORM == MTK_LINUX_PLATFORM
	    siglongjmp(envJmpDiv0, 1);
#endif
//	}
//	else
//	    std::cerr << "div0 handler,  probably div0 without  MTK_HANDLE_DIV0";
    }

    void InitHandleSignalFPE_intdiv0 (void)
    {
	static bool initialized = false;

	if (initialized)   return;
	initialized = true;

	if( signal(SIGFPE, bypass_sigfpe) == SIG_ERR )
	    throw std::runtime_error("div0 handler not initialized");
    }



};      //  end namespace mtk





#if (MTK_PLATFORM == MTK_WIN_PLATFORM)
    #include <windows.h>

#elif MTK_PLATFORM == MTK_LINUX_PLATFORM
    #include <unistd.h>

#else

#endif


namespace mtk
{

#if (MTK_PLATFORM == MTK_WIN_PLATFORM)


    std::string GetMachineCode(void)
    {
        char computerName[255];
        unsigned long size=250;
        GetComputerName(
                computerName,
                &size
           );

        return std::string(computerName);
    }
    void sleep(const dtTimeQuantity& tq)
    {
        ::Sleep(ARE_YOU_SURE_YOU_WANT_GetMillisecsDay(tq));
    }

#elif MTK_PLATFORM == MTK_LINUX_PLATFORM

    std::string GetMachineCode(void)
    {
        //  en linux poner esto
        char hostName[1024];
        hostName[0] = 0x0;
        gethostname(hostName, 1023);
        return std::string(hostName);
    }

    void sleep(const dtTimeQuantity& tq)
    {
        //  en windows con directiva de compilación linux se puede cambiar lo siguiente
        //_sleep(ARE_YOU_SURE_YOU_WANT_GetMillisecsDay(tq));

        struct timespec ts;
        unsigned millisecs = ARE_YOU_SURE_YOU_WANT_GetMillisecsDay(tq);
        ts.tv_sec  = millisecs /1000;
        ts.tv_nsec = (millisecs - ts.tv_sec*1000)*1000000L;
        nanosleep (&ts, NULL);
    }

#else

    #error   Unknown platform

#endif






};  //  namespace mtk
