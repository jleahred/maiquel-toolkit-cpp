#include "support/exec_max_frec.h"
#include <iostream>
#include "support/misc.h"




int main()
{

    //  simple MTK_EXEC_MAX_FREC_S
    for (int i=0; i<=100; ++i)
    {
        mtk::sleep(mtk::dtMilliseconds(20));
        MTK_EXEC_MAX_FREC_S(mtk::dtMilliseconds(500))
            std::cout << "__NR__:  " << i << std::endl;
        MTK_END_EXEC_MAX_FREC
    }


    //  nested MTK_EXEC_MAX_FREC_S
    for (int i=0; i<=500; ++i)
    {
        mtk::sleep(mtk::dtMilliseconds(20));
        MTK_EXEC_MAX_FREC_S_A(mtk::dtMilliseconds(500), first)
            MTK_EXEC_MAX_FREC_S_A(mtk::dtMilliseconds(1000), second)
                std::cout << "__NR__:  " << i << std::endl;
            MTK_END_EXEC_MAX_FREC
        MTK_END_EXEC_MAX_FREC
    }


    //  one control time for two blocs
    mtk::emfCheckMaxFrecSECONDS<1>  emf;    //  control time
    for (int i=0; i<=500; ++i)
    {
        mtk::sleep(mtk::dtMilliseconds(20));
        if (mtk::rand()%2 == 0)
        {
            MTK_EXEC_MAX_FREC_OBJ(emf)
                    std::cout << "__NR__:  " << "first block... " << i << std::endl;
            MTK_END_EXEC_MAX_FREC_OBJ
        }
        else
        {
            MTK_EXEC_MAX_FREC_OBJ(emf)
                    std::cout << "__NR__:  " << "second block block... " << i << std::endl;
            MTK_END_EXEC_MAX_FREC_OBJ
        }
    }
    
    

    #include "support/release_on_exit.hpp"
    return 0;
}