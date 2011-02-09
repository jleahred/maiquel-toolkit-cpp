 
#include <iostream>

#include "support/signalslot.hpp"




void receptorFunction(void)
{
    std::cout << "Resibío sin parámetrosss...  "  <<  std::endl;
}


void receptorFunction1(int val)
{
    std::cout << "Resibío1...  "  <<  val  << std::endl;
}

void receptorFunction2(int val, int val2)
{
    std::cout << "Resibío2...  "  <<  val +val2  << std::endl;
}

void receptorFunction3(int val, int val2, int val3)
{
    std::cout << "Resibío3...  "  <<  val+val2+val3  << std::endl;
}

void receptorFunction4(int val, int val2, int val3, int val4)
{
    std::cout << "Resibío4...  "  <<  val+val2+val3+val4  << std::endl;
}







int main()
{

    //  prueba conexión y desconexión sin parámetros
    {
        mtk::Signal<>  signalA;


        signalA.connect(&receptorFunction);

        //  emitimos señal
        signalA();

        signalA.disconnect(&receptorFunction);
        signalA();


        //  repetimos
        std::cout << "repetimos... "  <<  std::endl;
        signalA.connect(&receptorFunction);
        signalA();
        signalA.disconnect_all();
        signalA();

    }


    //  prueba conexión y desconexión 1 parámetro
    {
        mtk::Signal<int>  signalA;


        signalA.connect(&receptorFunction1);

        //  emitimos señal
        signalA(1);

        signalA.disconnect(&receptorFunction1);
        signalA(1);


        //  repetimos
        std::cout << "repetimos... "  <<  std::endl;
        signalA.connect(&receptorFunction1);
        signalA(1);
        signalA.disconnect_all();
        signalA(1);

    }


    //  prueba conexión y desconexión 2 parámetro
    {
        mtk::Signal<int, int>  signalA;


        signalA.connect(&receptorFunction2);

        //  emitimos señal
        signalA(1, 2);

        signalA.disconnect(&receptorFunction2);
        signalA(1, 2);


        //  repetimos
        std::cout << "repetimos... "  <<  std::endl;
        signalA.connect(&receptorFunction2);
        signalA(1, 2);
        signalA.disconnect_all();
        signalA(1, 2);

    }

    //  prueba conexión y desconexión 3 parámetro
    {
        mtk::Signal<int, int, int>  signalA;


        signalA.connect(&receptorFunction3);

        //  emitimos señal
        signalA(1, 2, 3);

        signalA.disconnect(&receptorFunction3);
        signalA(1, 2, 3);


        //  repetimos
        std::cout << "repetimos... "  <<  std::endl;
        signalA.connect(&receptorFunction3);
        signalA(1, 2, 3);
        signalA.disconnect_all();
        signalA(1, 2, 3);

    }


    //  prueba conexión y desconexión 4 parámetro
    {
        mtk::Signal<int, int, int, int>  signalA;


        signalA.connect(&receptorFunction4);

        //  emitimos señal
        signalA(1, 2, 3, 4);

        signalA.disconnect(&receptorFunction4);
        signalA(1, 2, 3, 4);


        //  repetimos
        std::cout << "repetimos... "  <<  std::endl;
        signalA.connect(&receptorFunction4);
        signalA(1, 2, 3, 4);
        signalA.disconnect_all();
        signalA(1, 2, 3, 4);

    }


    #include "support/release_on_exit.hpp"
    return 0;
}