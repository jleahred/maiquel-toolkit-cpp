
#include "support/date_time.h"
#include <iostream>

#include "support/basic_types.hpp"



__int64  dtMachineGetTotalMillisecs (int ticksSimulated)
{
//    return  dtTotalMillisecs(GetTickCount());

    static __int64          vueltas64           = 0;
    static const __int64    _2pow32             = 4294967296LL;
    static unsigned         previusTickCount32  = 0;
    unsigned                currentTickCount32  = ticksSimulated;

    if (currentTickCount32 < previusTickCount32)    //  casi seguro que hemos dado la vuelta al int32
    {
        vueltas64 += _2pow32;
    }

    previusTickCount32 = currentTickCount32;
    return  (__int64)(currentTickCount32) + (__int64)(vueltas64);
}


int main()
{
    unsigned  base;
    long long increment;
    long long result;
    bool      diff;


    std::cout << std::endl << std::endl << "elemental, llamada sin desbordamiento";
    base=   5000;
    increment = 0;
    result = dtMachineGetTotalMillisecs(int(base+increment));
    if (result-base  ==  increment)
        diff = true;

    std::cout   <<  std::endl
                << "base:   " << base       <<  std::endl
                << "incr:   " << increment  <<  std::endl
                << "b+i 32  " << base+unsigned(increment) <<  std::endl
                << "result: " << result     <<  std::endl
                << "diff:   " << diff;

    std::cout << std::endl << std::endl << "elemental, nueva llamada sin desbordamiento";
    //base=   0;
    increment = 5000;
    result = dtMachineGetTotalMillisecs(int(base+increment));
    if (result-base  ==  increment)
        diff = true;

    std::cout   <<  std::endl
                << "base:   " << base       <<  std::endl
                << "incr:   " << increment  <<  std::endl
                << "b+i 32  " << base+unsigned(increment) <<  std::endl
                << "result: " << result     <<  std::endl
                << "diff:   " << diff;


    std::cout << std::endl << std::endl << "sin desbordamiento pero muy cerca  (sólo a 5 milisegundos)";
    base=   4294967296LL-5;
    increment = 0;
    result = dtMachineGetTotalMillisecs(int(base+increment));
    if (result-base  ==  increment)
        diff = true;

    std::cout   <<  std::endl
                << "base:   " << base       <<  std::endl
                << "incr:   " << increment  <<  std::endl
                << "b+i 32  " << base+unsigned(increment) <<  std::endl
                << "result: " << result     <<  std::endl
                << "diff:   " << diff;


    std::cout << std::endl << std::endl << "primer desbordamiento por poquito (15-5 millisecs)";
    //base=15;
    increment = 15;
    result = dtMachineGetTotalMillisecs(int(base+increment));
    if (result-base  ==  increment)
        diff = true;

    std::cout   <<  std::endl  <<  std::endl
                << "base:   " << base       <<  std::endl
                << "incr:   " << increment  <<  std::endl
                << "b+i 32  " << base+unsigned(increment) <<  std::endl
                << "result: " << result     <<  std::endl
                << "diff:   " << diff;

    std::cout << std::endl << std::endl << "sin desbordamiento adicional";
    //base=15;
    increment = 20000;
    result = dtMachineGetTotalMillisecs(int(base+increment));
    if (result-base  ==  increment)
        diff = true;

    std::cout   <<  std::endl  <<  std::endl
                << "base:   " << base       <<  std::endl
                << "incr:   " << increment  <<  std::endl
                << "b+i 32  " << base+unsigned(increment) <<  std::endl
                << "result: " << result     <<  std::endl
                << "diff:   " << diff;


    std::cout << std::endl << std::endl << "cerca segundo desbordamiento (a 1000ms)";
    base=   4294967296LL-1000;
    increment = 0;
    result = dtMachineGetTotalMillisecs(int(base+increment));
    if (result-base  ==  increment)
        diff = true;

    std::cout   <<  std::endl
                << "base:   " << base       <<  std::endl
                << "incr:   " << increment  <<  std::endl
                << "b+i 32  " << base+unsigned(increment) <<  std::endl
                << "result: " << result     <<  std::endl
                << "diff:   " << diff;

    std::cout << std::endl << std::endl << "segundo desbordamiento (por 500ms)";
    //base=   4294967296LL-1000;
    increment = 1500;
    result = dtMachineGetTotalMillisecs(int(base+increment));
    if (result-base  ==  increment)
        diff = true;

    std::cout   <<  std::endl
                << "base:   " << base       <<  std::endl
                << "incr:   " << increment  <<  std::endl
                << "b+i 32  " << base+unsigned(increment) <<  std::endl
                << "result: " << result     <<  std::endl
                << "diff:   " << diff;

}
