#include <iostream>
#include <stdexcept>


#include "support/misc.h"






int main()
{

    //  caso sencillo
    try
    {
        MTK_HANDLE_DIV0_INIT

            std::cout << "uno " << std::endl;
            int    izero = 0;
            std::cout << 7 / izero << std::endl;

        MTK_HANDLE_DIV0_END

    }
    catch(const std::exception& error)
    {
        std::cout << "capturamos en 1 " << error.what() << std::endl;
    }




    //  dos consecutivos

    try
    {
        MTK_HANDLE_DIV0_INIT
        {
            std::cout << "dos " << std::endl;
            int    izero = 0;
            std::cout << 7 / izero << std::endl;
        }
        MTK_HANDLE_DIV0_END
        


        MTK_HANDLE_DIV0_INIT
            std::cout << "tres " << std::endl;
            int    izero = 0;
            std::cout << 8 / izero;
        MTK_HANDLE_DIV0_END


    }
    catch(const std::exception& error)
    {
        std::cout << "capturamos en 2-3 " << error.what() << std::endl;
    }



    //  anidados
    try
    {
        MTK_HANDLE_DIV0_INIT

                try
                {
                    MTK_HANDLE_DIV0_INIT_A(A)
                        std::cout << "cuatro " << std::endl;
                        int    izero = 0;
                        std::cout << 7 / izero << std::endl;
                    MTK_HANDLE_DIV0_END_A(A)
                }
                catch(const std::exception& error)
                {
                    std::cout << "capturamos en 4 " << error.what() << std::endl;
                }
                
            std::cout << "cinco " << std::endl;
            std::cout << "lo intentamos OTRA VEZ" << std::endl;
            int    izero = 0;
            std::cout << 8 / izero;
                
        MTK_HANDLE_DIV0_END

    }
    catch(const std::exception& error)
    {
        std::cout << "capturamos en 5 " << error.what() << std::endl;
    }
    
    std::cout << "Pero no me importa...   End of program..." << std::endl;

    #include "support/release_on_exit.hpp"
    return 0;
}