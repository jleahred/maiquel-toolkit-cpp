#include "synchr.h"




namespace {

    #if (MTK_PLATFORM == MTK_LINUX_PLATFORM)
        #include <pthread.h>

        typedef   pthread_mutex_t    MUTEX;


        int MUTEX_INIT(MUTEX *mutex)
        {
            return pthread_mutex_init (mutex, NULL);
        }

        int MUTEX_LOCK(MUTEX *mutex)
        {
            return pthread_mutex_lock( mutex );
        }

        int MUTEX_UNLOCK(MUTEX *mutex)
        {
            return pthread_mutex_unlock( mutex );
        }

    #elif (MTK_PLATFORM == MTK_WIN_PLATFORM)
        #include <windows.h>
        #include <process.h>

        #define MUTEX   HANDLE

        int MUTEX_INIT(MUTEX *mutex)
        {
            *mutex = CreateMutex(0, FALSE, 0);;
            return (*mutex==0);
        }

        int MUTEX_LOCK(MUTEX *mutex)
        {
            return (WaitForSingleObject(*mutex, INFINITE)==WAIT_FAILED?1:0);
        }

        int MUTEX_UNLOCK(MUTEX *mutex)
        {
            return (ReleaseMutex(*mutex)==0);
        }
    #endif



};




namespace mtk {










Mutex::Mutex()
{
    MUTEX_INIT(&__internal_mutex);
}

Mutex::~Mutex()
{
}

void Mutex::lock   (void)
{
    MUTEX_LOCK(&__internal_mutex);
}

void Mutex::unlock (void)
{
    MUTEX_UNLOCK(&__internal_mutex);
}



lock::lock(mtk::CountPtr<Mutex>  _mutex)
    : mutex(_mutex)
{
    mutex->lock();
}

lock::~lock(void)
{
    mutex->unlock();
}





mtk::CountPtr<Mutex>   get_mtk_mutex(void)
{
    static   auto  result  =  mtk::make_cptr(new Mutex);
    return  result;
}


//----------------------------------------------------------------------
};      //  end namespace mtk
