
#include "support/nullable.hpp"


#include <iostream>
#include "support/mtk_string.h"



int main(int /*argc*/, char **/*argv*/)
{
    mtk::nullable<int> nint1 = mtk::make_nullable(8);
    mtk::nullable<int> nint2;

    if (nint1.HasValue())
        std::cout << "nint1  "  << nint1.Get() << std::endl;
    if (nint2.HasValue())
        std::cout << "nint2  "  << nint2.Get() << std::endl;

    return 0;
}


void mtk::AlarmMsg(const mtk::Alarm& al)
{
    std::cout << "ouch...: "  << al << std::endl;

}
