 
#include <iostream>

#include "support/tuples.hpp"
#include "support/basic_types.hpp"

class nothing
{
public:
    nothing(int){};
};

int main(int /*argc*/, const char** /*argv*/)
{

    //  creating tuple
    mtk::tuple<int, int>  t2int (4,5);
    std::cout << t2int << std::endl;
    
    mtk::tuple<int, int> t2int2 (5, 4);
    if (t2int2 < t2int)
        std::cout << "t2int2 < t2int" << std::endl;
    else
        std::cout << "NOT t2int2 < t2int" << std::endl;


    //  make_tuple
    mtk::tuple<double, int>  tdoubleint;
    tdoubleint = mtk::make_tuple(9.9, 7);
    std::cout << tdoubleint << std::endl;
    
    //  getting tuple elements
    std::cout << "first element tdooubleint tuple is : " << tdoubleint._0 << std::endl;
    std::cout << "second element tdooubleint tuple is : " << tdoubleint._1 << std::endl;
    
    
    
    //  copying tuple elements to variables
    double first_element;
    int    second_element;
    
    tdoubleint.assign(first_element, second_element);
    std::cout << "first element tdooubleint tuple is : " << first_element << std::endl;
    std::cout << "second element tdooubleint tuple is : " << second_element << std::endl;


    mtk::tuple<int, nothing>  tintnothing0 (8, 0);
    mtk::tuple<int, nothing>  tintnothing1 (9, 0);
    //  wrong, it doesn't compile
//    if (tintnothing0 < tintnothing1)
//        ;
//    std::cout << tintnothing0;
    return 0;
}
