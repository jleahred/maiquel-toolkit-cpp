#include "checkscopetime.h"

#include <iostream>


#include "support/foreach.hpp"
#include "support/mtk_string.h"
#include "support/date_time.h"


#include "support/platform.hpp"




#ifndef MTK_PLATFORM
    #error  "mtk::   NO ESTÁ CARGADO EL FICHERO DE CONFIGURACIÓN  support/platform.hpp"
#endif

#if (MTK_PLATFORM == MTK_WIN_PLATFORM)


    #include <windows.h>
    #include <basetyps.h>       //  __int64		//	quitar en bcb

#elif MTK_PLATFORM == MTK_LINUX_PLATFORM

    #include <sys/time.h>

#else

    #error Unknown plattform

#endif





namespace mtk{


std::map<std::string, mtk::tuple<__int64, int, bool> > CheckScopeTime::mNameTime;



CheckScopeTime::CheckScopeTime(const char* _name)
    :   name    (_name),
        running (false)
{
    Start();
    IncrementCounter(name);
};

CheckScopeTime::~CheckScopeTime()
{
    Stop();
};




void CheckScopeTime::Stop(void)
{
    if (running)
    {
        #if (MTK_PLATFORM == MTK_WIN_PLATFORM)
            LARGE_INTEGER frequency;
            QueryPerformanceCounter(&frequency);
            __int64 elapsedTime = frequency.QuadPart - start;
        #elif MTK_PLATFORM == MTK_LINUX_PLATFORM
            timeval now;
            gettimeofday(&now, 0);
            __int64 elapsedTime =  (now.tv_sec *1000 + now.tv_usec/1000) - start;
        #else

            #error Unknown plattform

        #endif
        AddTime(name, elapsedTime);
        RegisterStop(name);
    }
    running = false;
};


void CheckScopeTime::Start(void)
{
    if (RegisterStart(name))
    {
        if (!running)
        {
            #if (MTK_PLATFORM == MTK_WIN_PLATFORM)
                LARGE_INTEGER frequency;
                QueryPerformanceCounter(&frequency);
                start = frequency.QuadPart;
            #elif MTK_PLATFORM == MTK_LINUX_PLATFORM
                timeval now;
                gettimeofday(&now, 0);
                start = now.tv_sec * 1000 + now.tv_usec/1000;
            #else

                #error Unknown plattform

            #endif
        }
        running = true;
    }
};





void CheckScopeTime::AddTime(const char* name, __int64 tq)
{
    std::map<std::string, mtk::tuple<__int64, int, bool> >::iterator it = (mNameTime.find(name));
    if (it != mNameTime.end())
    {
        it->second._0 += tq;
    }
    else
        std::cout << std::endl << "checking time error"  << name;
}

bool CheckScopeTime::RegisterStart(const char* name)
{
    std::map<std::string, mtk::tuple<__int64, int, bool> >::iterator it = (mNameTime.find(name));
    if (it != mNameTime.end())
    {
        if (it->second._2==false)
        {
            it->second._2 = true;
            return true;
        }
        else
            return false;
    }
    else
    {
        mNameTime.insert(std::pair<std::string, mtk::tuple<__int64, int, bool> >(name, mtk::make_tuple((__int64)(0), 0, true)));
        return true;
    }
}

void CheckScopeTime::RegisterStop(const char* name)
{
    std::map<std::string, mtk::tuple<__int64, int, bool> >::iterator it = (mNameTime.find(name));
    if (it != mNameTime.end())
        it->second._2 = false;
}

void CheckScopeTime::IncrementCounter(const char* name)
{
    std::map<std::string, mtk::tuple<__int64, int, bool> >::iterator it = (mNameTime.find(name));
    if (it != mNameTime.end())
        it->second._1 += 1;
}

//bool CheckScopeTime::IsRunning(const char* name)
//{
//    std::map<std::string, mtk::tuple<__int64, int, bool> >::iterator it = (mNameTime.find(name));
//    if (it != mNameTime.end())
//        return it->second._2;
//
//    return false;
//}


void CheckScopeTime::PrintTimes(void)
{

    #if (MTK_PLATFORM == MTK_WIN_PLATFORM)
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(
            &frequency
        );

        std::cout   << std::endl << "times...  " << std::endl;
        MTK_FOREACH_CONST_ITERATOR(it, mNameTime)
        {
            std::cout   << std::endl << "   "
                        << s_AlignLeft( it->first, 30, '_')
                        << s_AlignRight( MTK_SS( dtMilliseconds(int(it->second._0*1000 / frequency.QuadPart)).WarningDontDoThisGetInternal()), 8, '_')
                        <<  "   n: "
                        << it->second._1;
        }
    #elif MTK_PLATFORM == MTK_LINUX_PLATFORM
        std::cout   << std::endl << "times...  " << std::endl;
        MTK_FOREACH_CONST_ITERATOR(it, mNameTime)
        {
            std::cout   << std::endl << "   "
                        << s_AlignLeft( it->first, 30, '_')
                        << s_AlignRight( MTK_SS( dtMilliseconds(int(it->second._0)).WarningDontDoThisGetInternal()), 8, '_')
                        <<  "   n: "
                        << it->second._1;
        }
    #else

        #error Unknown plattform

    #endif
}


};//    end namespace mtk
