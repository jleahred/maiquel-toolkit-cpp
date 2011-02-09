#include <stdexcept>
#include <stdlib.h>
#include <time.h>
#include <iostream>


#include "misc.h"
#include "date_time.h"
#include "support/mtk_string.h"




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
            srand ( (unsigned int) (mtk::dtNowLocal().__WARNING_NOT_CALL_IT_internal_use_GetTimeQuantitySerialNumber().WarningDontDoThisGetInternal()*24.*60.*60.*1000.) );
            initialized = true;
        }
        return ::rand();
    }



    std::string  convert_to_base_skip_O(int num, int base)
    {
        std::string result;

        while(num>0)
        {
            int temp = num%base;
            if(temp >= 10)
            {
                char  c = char(temp-10+'A');
                if (c>='O')
                    ++c;
                result = MTK_SS(c) + result;
            }
            else
                result = MTK_SS(temp) + result;
            num /= base;
        }

        return result;
    }


    int  convert_from_base_skip_O(const std::string&  num, int base)
    {
        int result=0;

        int base_i = 1;
        for(int i=int(num.size())-1; i>=0; --i)
        {
            char c = num[i];
            int val =0;
            if (c > 'O')
                --c;
            if(c>='0'  &&  c<='9')
                val = c-'0';
            else
                val = c-'A'+10;

            result += base_i * val;
            base_i *= base;
        }

        return result;
    }


    std::string  convert_to_base_35(int num)
    {
        return convert_to_base_skip_O(num, 35);
    }

    int   convert_from_base_35(const std::string& num)
    {
        return convert_from_base_skip_O(num, 35);
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
