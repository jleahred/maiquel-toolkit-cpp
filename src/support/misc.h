#ifndef mtkMiscH
#define mtkMiscH


#include <signal.h>
#include <setjmp.h>
#include <string.h>   //  memcpy

#include "platform.hpp"



namespace mtk {

    ///////////////////////////////
    int rand (void);



    ///////////////////////////////
    std::string GetMachineCode(void);


    class dtTimeQuantity;
    ///////////////////////////////
    void sleep(const dtTimeQuantity& tq);



    ///////////////////////////////
    std::string  convert_to_base_35  (int num);
    int          convert_from_base_35(const std::string& num);






    ///////////////////////////////
    //  div0 control
#if (MTK_PLATFORM == MTK_WIN_PLATFORM)

    #define MTK_HANDLE_DIV0_INIT						\
        {									\
        mtk::InitHandleSignalFPE_intdiv0();				\
        if (setjmp(mtk::envJmpDiv0)!=0)				\
        {								\
            throw std::runtime_error("SIGNAL FPE  probably int div0");	\
        }								\
        else								\
        {

/*
    #define MTK_HANDLE_DIV0_INIT						\
        {									\
        jmp_buf previus_envJmpDiv0_l;					\
        memcpy(previus_envJmpDiv0_l, mtk::envJmpDiv0, sizeof(jmp_buf));	\
        bool    previus_initJumpDiv0_l = mtk::initJumpDiv0;		\
        mtk::initJumpDiv0 = true;					\
        mtk::InitHandleSignalFPE_intdiv0();				\
        if (setjmp(mtk::envJmpDiv0)!=0)					\
        {								\
            memcpy(mtk::envJmpDiv0, previus_envJmpDiv0_l, sizeof(jmp_buf)); \
            mtk::initJumpDiv0 = previus_initJumpDiv0_l;			\
            throw std::runtime_error("SIGNAL FPE  probably int div0");	\
        }								\
        else								\
        {
*/
    #define MTK_HANDLE_DIV0_INIT_A(__A__)						\
        {									\
        jmp_buf previus_envJmpDiv0##__A__;					\
        memcpy(previus_envJmpDiv0##__A__, mtk::envJmpDiv0, sizeof(jmp_buf));	\
        bool    previus_initJumpDiv0##__A__ = mtk::initJumpDiv0;		\
        mtk::initJumpDiv0 = true;					\
        mtk::InitHandleSignalFPE_intdiv0();				\
        if (setjmp(mtk::envJmpDiv0)!=0)					\
        {								\
            memcpy(mtk::envJmpDiv0, previus_envJmpDiv0##__A__, sizeof(jmp_buf)); \
            mtk::initJumpDiv0 = previus_initJumpDiv0##__A__;			\
            throw std::runtime_error("SIGNAL FPE  probably int div0");	\
        }								\
        else								\
        {

    #elif MTK_PLATFORM == MTK_LINUX_PLATFORM
    #define MTK_HANDLE_DIV0_INIT						\
        {									\
        mtk::InitHandleSignalFPE_intdiv0();				\
        if (sigsetjmp(mtk::envJmpDiv0, 1)!=0)				\
        {								\
            throw std::runtime_error("SIGNAL FPE  probably int div0");	\
        }								\
        else								\
        {
/*
	#define MTK_HANDLE_DIV0_INIT						\
        {									\
        jmp_buf previus_envJmpDiv0_l;					\
        memcpy(previus_envJmpDiv0_l, mtk::envJmpDiv0, sizeof(jmp_buf));	\
        bool    previus_initJumpDiv0_l = mtk::initJumpDiv0;		\
        mtk::initJumpDiv0 = true;					\
        mtk::InitHandleSignalFPE_intdiv0();				\
        if (sigsetjmp(mtk::envJmpDiv0, 1)!=0)				\
        {								\
            memcpy(mtk::envJmpDiv0, previus_envJmpDiv0_l, sizeof(jmp_buf)); \
            mtk::initJumpDiv0 = previus_initJumpDiv0_l;			\
            throw std::runtime_error("SIGNAL FPE  probably int div0");	\
        }								\
        else								\
        {
*/

        #define MTK_HANDLE_DIV0_INIT_A(__A__)						\
        {									\
        jmp_buf previus_envJmpDiv0##__A__;					\
        memcpy(previus_envJmpDiv0##__A__, mtk::envJmpDiv0, sizeof(jmp_buf));	\
        bool    previus_initJumpDiv0##__A__ = mtk::initJumpDiv0;		\
        mtk::initJumpDiv0 = true;					\
        mtk::InitHandleSignalFPE_intdiv0();				\
        if (sigsetjmp(mtk::envJmpDiv0, 1)!=0)				\
        {								\
            memcpy(mtk::envJmpDiv0, previus_envJmpDiv0##__A__, sizeof(jmp_buf)); \
            mtk::initJumpDiv0 = previus_initJumpDiv0##__A__;			\
            throw std::runtime_error("SIGNAL FPE  probably int div0");	\
        }								\
        else								\
        {

#else
    #error  "Unknown platfom..."
#endif


#define MTK_HANDLE_DIV0_END						\
    }									\
    }

/*
#define MTK_HANDLE_DIV0_END						\
    }									\
	memcpy(mtk::envJmpDiv0, previus_envJmpDiv0_l, sizeof(jmp_buf));	\
	mtk::initJumpDiv0 = previus_initJumpDiv0_l;			\
    }
*/

#define MTK_HANDLE_DIV0_END_A(__A__)						\
    }									\
	memcpy(mtk::envJmpDiv0, previus_envJmpDiv0##__A__, sizeof(jmp_buf));	\
	mtk::initJumpDiv0 = previus_initJumpDiv0##__A__;			\
    }



    //  Si se utiliza la macro MTK_HANDLE_DIV0 no es necesario llamar a esta función
    //  está llamada implícitamente por dicha macro
    void InitHandleSignalFPE_intdiv0 (void);
    extern jmp_buf envJmpDiv0;
    extern bool    initJumpDiv0;






};      //  end namespace mtk

#endif

