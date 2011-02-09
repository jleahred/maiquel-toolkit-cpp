#include "support/count_ptr.hpp"


#include <iostream>
#include "support/mtk_string.h"



int main(int /*argc*/, char **/*argv*/)
{
    {
        mtk::CountPtr<int>cpi1;
    
        //  if we try  std::cout << *cpi1;  an exception will be throw
        
        {
            // mtk::CountPtr<int>  cpi2( new int(8)); is more clear to create the CountPtr as...
            mtk::CountPtr<int>  cpi2 = mtk::make_cptr(new int(8));
            cpi1 = cpi2;
        }
        

        if (*cpi1  == 8)
            std::cout << "CountPtr<int>  with value " << *cpi1 << std::endl;
        else
        {
            std::cout << "error " << std::endl;
            return -1;
        }
    }
	
    
    
    return 0;
}
