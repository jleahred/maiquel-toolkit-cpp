 
#include "support/crc32.h"


#include <iostream>
#include "support/mtk_string.h"



int main(int /*argc*/, char **/*argv*/)
{
    for (int i=0; i<100; ++i)
        std::cout <<  mtk::crc32_as_string( MTK_SS("hello bird with no tail" << i) ) << std::endl;
    
    
    std::cout << std::endl << mtk::crc32("hola pajarito sin cola");
    std::cout << std::endl << mtk::crc32_as_string("hola pajarito sin cola");
    std::cout << std::endl << mtk::crc32_as_string("abcdefg");
    std::cout << std::endl << mtk::crc32_as_string("");

    
    return 0;
}
