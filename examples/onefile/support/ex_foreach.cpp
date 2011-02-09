#include "support/foreach.hpp"
#include <vector>
#include <list>
#include <map>
#include <string>
#include <iostream>

int main(int /*argc*/, char** /*argv*/)
{
    std::vector<int>                vint;
    std::list  <int>                lint;
    std::map   <int, std::string>   mint;


    //  fill elements
    for (int i=0; i<10; i++) {
        vint.push_back(3);
        lint.push_back(4);
    }
    mint[1] = "uno";
    mint[2] = "dos";
    mint[3] = "tres";
    mint[4] = "cuatro";
    mint[5] = "cinco";




    //  secuence all elements
    MTK_FOREACH(a, vint) 
    {
        std::cout << "  .." << *a  << std::endl;
    };

    MTK_FOREACH(b, lint) 
    {
        std::cout << "  .." << *b << std::endl;
    };


    MTK_FOREACH(c, mint) 
    {
        std::cout << "  .." << c->first << "  "  << c->second << std::endl;
    };
    
	return 0;
}
