
#include <iostream>

#include "support/signalslot.hpp"






class PrReceptor : public mtk::SignalReceptor{

public:

    void OnNoParam(void) {
        std::cout << std::endl  << "No param";
    }

    void OnIntParam(int param) {
        std::cout << std::endl  << "recibío...  "  << param;
    }


    void OnStringDoubleParam(std::string s, double d) {
        std::cout << std::endl  << "recibío...   string:"  << s << "  double:" << d;
    }

};







int main()
{

//      probamos una conexión de signal con otro signal  (2009-06-09) con parámetros
    {
        mtk::Signal<>  signalA;

        mtk::Signal<> signalB;

        PrReceptor pr;
        signalB.connect(&pr, &PrReceptor::OnNoParam);

        signalB();


        //  aunque la conexión se puede hacer así...
        signalA.connect(&signalB, &mtk::Signal<>::operator());


        //  parece más cómodo de esta otra forma
        signalA.connect(&signalB);



        //  emitimos señal
        signalA();

    }


//      probamos una conexión de signal con otro signal  (2009-06-09) con parámetros
    {
        mtk::Signal<int>  signalA;

        mtk::Signal<int> signalB;

        PrReceptor pr;
        signalB.connect(&pr, &PrReceptor::OnIntParam);

        signalB(5);

        signalA.connect(&signalB);

        signalA.emit(3);

    }

    std::cout << std::endl;


    #include "support/release_on_exit.hpp"
    return 0;
}