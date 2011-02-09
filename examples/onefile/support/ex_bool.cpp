 
#include <iostream>

#include "support/mtk_bool.hpp"



int main (void)
{
    std::cout << "testing mtk::Bool<bool>"  << std::endl;
  
    mtk::Bool<true> t;
    mtk::Bool<false> f;

    if (t == true)
        std::cout << "correcto";
    else
        return -1;
    std::cout << std::endl;        
    
    if (f == true)
        return -1;
    else
        std::cout << "correcto";
    std::cout << std::endl;        

    if (f == false)
        std::cout << "correcto";
    else
        return -1;
    std::cout << std::endl;        

    
    mtk::Bool<false>  b;
    std::cout << int(b) << std::endl;
    b = true;
    std::cout << int(b) << std::endl;
    
    return 0;
}