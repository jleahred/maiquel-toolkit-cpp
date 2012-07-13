#include <iostream>

#include "support/signalslot.hpp"




mtk::Signal<>       signalNoParams;
mtk::Signal<int>    signalOneParam;






class PrReceptor : public mtk::SignalReceptor{
public:
    PrReceptor()
    {
        //signalNoParams.connect(this, &PrReceptor::OnNoParam);
        //signalOneParam.connect(this, &PrReceptor::OnIntParam);
        MTK_CONNECT_THIS(signalNoParams, OnNoParam );
        MTK_CONNECT_THIS(signalOneParam, OnIntParam);
    }

    void OnNoParam(void) {
        std::cout << std::endl  << "No param";
    }

    void OnIntParam(int param) {
        std::cout << std::endl  << "recibído...  "  << param;
    }


    void OnStringDoubleParam(std::string s, double d) {
        std::cout << std::endl  << "recibído...   string:"  << s << "  double:" << d;
    }

};






int main()
{



    PrReceptor pr;



    signalNoParams();
    signalOneParam(88);
    signalOneParam(987);



    mtk::Signal<std::string, double>    signalPr2Params;
    signalPr2Params.connect(&pr, &PrReceptor::OnStringDoubleParam);

    signalPr2Params("Hola pajarito sin cola", 3.1415926535);
    signalPr2Params("Hasta luego cara huevo", 2.33358);


    std::cout << std::endl;



    return 0;
} 
