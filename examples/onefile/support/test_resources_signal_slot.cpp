#include <iostream>

#include "support/signalslot.hpp"
#include "support/exec_max_frec.h"
#include "support/date_time.h"
#include "support/mtk_string.h"




void mtk::AlarmMsg (const Alarm& alarma)
{
        std::cout << "\n\r";
        std::cout << std::endl << "ALARMA SALIDA..." << std::endl ;
        std::cout << alarma << std::endl ;
}



class PrReceptor : public mtk::SignalReceptor{

public:

    void OnNoParamNoNoise(void)
    {
        MTK_EXEC_MAX_FREC(mtk::dtSeconds(1))
            std::cout << ".";
        MTK_END_EXEC_MAX_FREC
    }

    void OnNoParam(void) {
        std::cout << std::endl  << "No param";
    }

    void OnIntParam(int param) {
        std::cout << std::endl  << "recibído...  "  << param;
    }
};





class PrReceptorConSignal : public mtk::SignalReceptor{

    std::string write;
//    mtk::emfCheckMaxFrecSECONDS<2>  emf;

public:
    mtk::Signal<>   signal;


    explicit PrReceptorConSignal(std::string _write) : write (_write) {};
    PrReceptorConSignal()  {};

    void OnNoParamNoNoise()
    {
        static int contador = 0;
        ++contador;

        MTK_EXEC_MAX_FREC(mtk::dtSeconds(2))
            std::cout <<  std::endl  << "__NR__:  " << write << contador << std::endl;
        MTK_END_EXEC_MAX_FREC

//        EXEC_MAX_FREC_OBJ(emf)
//            std::cout <<  std::endl << write << contador;
//        END_EXEC_MAX_FREC_OBJ

    }
};




int main()
{

//    mtk::Signal<>       signalNoParams;
//    mtk::Signal<int>    signalOneParam;
//
//
//    PrReceptor pr;
//
//    signalNoParams.connect(&pr, &PrReceptor::OnNoParam );
//    signalOneParam.connect(&pr, &PrReceptor::OnIntParam);
//
//
//    signalNoParams();
//    signalOneParam(88);
//    signalOneParam(987);




    std::cout << std::endl << "Sólo mandamos señales..." << std::endl;
    {
        int contador=0;

        mtk::Signal<>    signalNoParam;


        PrReceptor pr;

        mtk::dtDateTime start = mtk::dtNowLocal();
        signalNoParam.connect(&pr, &PrReceptor::OnNoParamNoNoise);
        while (true) {
            signalNoParam();
            contador++;

            if (contador%1000 == 0) {
                if (mtk::dtNowLocal() - start > mtk::dtSeconds(10)) {
                    std::cout << std::endl << "__NR__:  " << "Iteraciones: " << contador 
                                << " en " << MTK_SS(mtk::dtNowLocal() - start) << std::endl;
                    break;
                }
            }
        }
        ////system("pause");

    }
    ////system("pause");




    std::cout << std::endl << "Conectamos y desconectamos SIN MANDAR SEÑALES (MALO, MALO)..." << std::endl;
    {
        int contador=0;

        mtk::Signal<>    signalNOParam;


        PrReceptor pr;

        mtk::dtDateTime start = mtk::dtNowLocal();
        while (true) {
            ++contador;
            signalNOParam.connect(&pr, &PrReceptor::OnNoParamNoNoise);
            signalNOParam.disconnect(&pr, &PrReceptor::OnNoParamNoNoise);

            if (mtk::dtNowLocal() - start > mtk::dtSeconds(10)) {
                std::cout << std::endl << "__NR__:  " << "Iteraciones: " << contador
                            << " en " << MTK_SS(mtk::dtNowLocal() - start) << std::endl ;
                break;
            }
        }

        //system("pause");
    }
    //system("pause");



    std::cout << std::endl << "Conectamos y desconectamos mandando señal..." << std::endl;
    {
        int contador=0;

        mtk::Signal<>    signalNOParam;


        PrReceptor pr;

        mtk::dtDateTime start = mtk::dtNowLocal();
        while (true) {
            ++contador;
            signalNOParam.connect(&pr, &PrReceptor::OnNoParamNoNoise);
            signalNOParam();
            signalNOParam.disconnect(&pr, &PrReceptor::OnNoParamNoNoise);

            if (mtk::dtNowLocal() - start > mtk::dtSeconds(10)) {
                std::cout << std::endl << "__NR__:  " << "Iteraciones: " << contador
                            << " en " << MTK_SS(mtk::dtNowLocal() - start) << std::endl ;
                break;
            }
        }

        ////system("pause");
    }
    ////system("pause");



    std::cout << std::endl << "Creamos receptor, conexión, sacamos de ámbito receptor..." << std::endl;
    {
        int contador=0;

        mtk::Signal<>    signalNoParam;



        mtk::dtDateTime start = mtk::dtNowLocal();
        while (true) {
            {
                PrReceptor pr;
                signalNoParam.connect(&pr, &PrReceptor::OnNoParamNoNoise);
                signalNoParam();
                contador++;
            }

            if (contador%1000 == 0) {
                if (mtk::dtNowLocal() - start > mtk::dtSeconds(10)) {
                    std::cout << std::endl << "__NR__:  " << "Iteraciones: " << contador
                                << " en " << MTK_SS(mtk::dtNowLocal() - start)<< std::endl ;
                    break;
                }
            }
        }
        ////system("pause");

    }
    ////system("pause");



    std::cout << std::endl << "Creamos signal, conexión, sacamos de ámbito signal..." << std::endl;
    {
        int contador=0;



        PrReceptor pr;

        mtk::dtDateTime start = mtk::dtNowLocal();
        while (true) {
            {
                mtk::Signal<>    signalNoParam;
                signalNoParam.connect(&pr, &PrReceptor::OnNoParamNoNoise);
                signalNoParam();
                contador++;
            }

            if (contador%1000 == 0) {
                if (mtk::dtNowLocal() - start > mtk::dtSeconds(10)) {
                    std::cout << std::endl << "__NR__:  " << "Iteraciones: " << contador
                                << " en " << MTK_SS(mtk::dtNowLocal() - start) << std::endl ;
                    break;
                }
            }
        }
        ////system("pause");

    }
    ////system("pause");





    std::cout << std::endl << "Enviamos señal, sobre signal cruzados..." << std::endl;
    {
        int contador=0;



        PrReceptorConSignal pr1(".");
        PrReceptorConSignal pr2("|");

        mtk::dtDateTime start = mtk::dtNowLocal();
        pr1.signal.connect(&pr2, &PrReceptorConSignal::OnNoParamNoNoise);
        pr2.signal.connect(&pr1, &PrReceptorConSignal::OnNoParamNoNoise);
        while (true) {
            {
                pr1.signal();
                pr2.signal();
                contador++;
            }

            if (contador%1000 == 0) {
                if (mtk::dtNowLocal() - start > mtk::dtSeconds(10)) {
                    std::cout << std::endl << "__NR__:  " << "Iteraciones: " << contador
                                << " en " << MTK_SS(mtk::dtNowLocal() - start) << std::endl ;
                    break;
                }
            }
        }
        ////system("pause");

    }
    ////system("pause");



    std::cout << std::endl << "conectamos, desconectamos, enviamos señal sobre signal cruzados..." << std::endl;
    {
        int contador=0;



        PrReceptorConSignal pr1(".");
        PrReceptorConSignal pr2("|");

        mtk::dtDateTime start = mtk::dtNowLocal();
        while (true) {
            {
                pr1.signal.connect(&pr2, &PrReceptorConSignal::OnNoParamNoNoise);
                pr2.signal.connect(&pr1, &PrReceptorConSignal::OnNoParamNoNoise);
                pr1.signal();
                pr2.signal();
                pr1.signal.disconnect(&pr2, &PrReceptorConSignal::OnNoParamNoNoise);
                pr2.signal.disconnect(&pr1, &PrReceptorConSignal::OnNoParamNoNoise);

                contador++;
            }

            if (contador%1000 == 0) {
                if (mtk::dtNowLocal() - start > mtk::dtSeconds(10)) {
                    std::cout << std::endl << "__NR__:  " << "Iteraciones: " << contador
                                << " en " << MTK_SS(mtk::dtNowLocal() - start) << std::endl ;
                    break;
                }
            }
        }
        //system("pause");

    }
    //system("pause");



    std::cout << std::endl << "creamos un receptorsignal, conectamos, desconectamos, enviamos señal sobre signal cruzados..." << std::endl;
    {
        int contador=0;



        PrReceptorConSignal pr1(".");

        mtk::dtDateTime start = mtk::dtNowLocal();
        while (true) {
            {
                PrReceptorConSignal pr2("|");
                pr1.signal.connect(&pr2, &PrReceptorConSignal::OnNoParamNoNoise);
                pr2.signal.connect(&pr1, &PrReceptorConSignal::OnNoParamNoNoise);
                pr1.signal();
                pr2.signal();
                pr1.signal.disconnect(&pr2, &PrReceptorConSignal::OnNoParamNoNoise);
                pr2.signal.disconnect(&pr1, &PrReceptorConSignal::OnNoParamNoNoise);

                contador++;
            }

            if (contador%1000 == 0) {
                if (mtk::dtNowLocal() - start > mtk::dtSeconds(10)) {
                    std::cout << std::endl << "__NR__:  " << "Iteraciones: " << contador
                                << " en " << MTK_SS(mtk::dtNowLocal() - start)<< std::endl ;
                    break;
                }
            }
        }
        //system("pause");

    }
    //system("pause");




    std::cout << std::endl << "creamos dos receptorsignal, conectamos, desconectamos, enviamos señal sobre signal cruzados..." << std::endl;
    {
        int contador=0;

        mtk::dtDateTime start = mtk::dtNowLocal();
        while (true) {
            {
                PrReceptorConSignal pr1(".");
                PrReceptorConSignal pr2("|");
                pr1.signal.connect(&pr2, &PrReceptorConSignal::OnNoParamNoNoise);
                pr2.signal.connect(&pr1, &PrReceptorConSignal::OnNoParamNoNoise);
                pr1.signal();
                pr2.signal();
                pr1.signal.disconnect(&pr2, &PrReceptorConSignal::OnNoParamNoNoise);
                pr2.signal.disconnect(&pr1, &PrReceptorConSignal::OnNoParamNoNoise);

                contador++;
            }

            if (contador%1000 == 0) {
                if (mtk::dtNowLocal() - start > mtk::dtSeconds(10)) {
                    std::cout << std::endl << "__NR__:  " << "Iteraciones: " << contador
                                << " en " << MTK_SS(mtk::dtNowLocal() - start) << std::endl ;
                    break;
                }
            }
        }
        //system("pause");

    }
    //system("pause");



/**
        Faltarían pruebas de conexiones cruzadas de forma compleja

        Falta prueba de llamada a disconnect_all

        Pruebas de llamadas conexión, desconexión y disconnect_all cruzadas

        Pruebas con varios parámetros

*/


    return 0;
} 
