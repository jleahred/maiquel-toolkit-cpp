#ifndef mtk_synchr__h__
#define mtk_synchr__h__


#include "support/platform.hpp"
#include "support/count_ptr.hpp"

#if (MTK_PLATFORM == MTK_LINUX_PLATFORM)

    #include <pthread.h>

    typedef   pthread_mutex_t    MUTEX;

#elif (MTK_PLATFORM == MTK_WIN_PLATFORM)

    #include <windows.h>
    #include <process.h>

    typedef   HANDLE    MUTEX;

#endif



//--------------------------------------------------------------

#define  MTK_SYNCHR   mtk::lock  __mtk_lock__ {mtk::get_mtk_mutex()};  (void)__mtk_lock__;

//--------------------------------------------------------------




namespace mtk {




class  Mutex
{
public:
    Mutex (void);
    ~Mutex(void);

    void lock   (void);
    void unlock (void);

private:
    MUTEX   __internal_mutex;
};



class  lock
{
public:
    lock(Mutex*  mutex);
    ~lock(void);


private:
    Mutex*   mutex;
};



//-----------------------------------------------------------------------------------------------------------------

    Mutex*   get_mtk_mutex(void);

//-----------------------------------------------------------------------------------------------------------------



};      //  end namespace mtk

#endif      //  mtk_synchr__h__
