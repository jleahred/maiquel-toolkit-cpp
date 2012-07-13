 
//---------------------------------------------------------------------------

#include "support/call_later.h"



//---------------------------------------------------------------------------







class TestCallLater : public mtk::SignalReceptor    //<<-------------------
{
private:

public:

    TestCallLater() {
    //-------------------------------------
    //  tres formas de llamar a call_later 
    //-------------------------------------

        //mtk::CallLaterFactory1S(mtk::dtSeconds(5), 11).connect(this, &TestCallLater::CallAfter5s);
        //mtk::CallLaterFactory1S(mtk::dtSeconds(6), 3.1415926535).connect(this, &TestCallLater::CallAfter6stwice);
        //mtk::CallLaterFactory1S(mtk::dtSeconds(6), 3.1415926535).connect(this, &TestCallLater::CallAfter6stwice);

        //MTK_CONNECT_THIS(mtk::CallLaterFactory1S(mtk::dtSeconds(5), 11),            CallAfter5s);
        //MTK_CONNECT_THIS(mtk::CallLaterFactory1S(mtk::dtSeconds(6), 3.1415926535),  CallAfter6stwice);
        //MTK_CONNECT_THIS(mtk::CallLaterFactory1S(mtk::dtSeconds(6), 1.42),  CallAfter6stwice);

        MTK_CALL_LATER1S_THIS(mtk::dtSeconds(5), 11 , CallAfter5s)
        MTK_CALL_LATER1S_THIS(mtk::dtSeconds(6), 3.1415926535 , CallAfter6stwice)
        MTK_CALL_LATER1S_THIS(mtk::dtSeconds(6), 1.42 , CallAfter6stwice)
    //-------------------------------------
    //  tres formas de llamar a call_later 
    //-------------------------------------

    };

    void CallAfter5s(const int& data) {
        std::cout << "__NR__:  " << mtk::dtNowLocal() <<  "  CallAfter5s " << data  << std::endl;
    };


    void CallAfter6stwice(const double& data) {
        std::cout << "__NR__:  " << mtk::dtNowLocal() << "  CallAfter6stwice " << data  << std::endl;
    };
};




void callLaterInt(const int& data)
{
    std::cout   << std::endl
                << "__NR__:  "
                << mtk::dtNowLocal()
                << "  Me han llamaOOOOO  más tardEEEEEE..." << "data... " << data
                <<  std::endl;
}


void callLaterString(const std::string& data)
{
    std::cout << "__NR__:  " << mtk::dtNowLocal() << "  CALL LATER  " << data << std::endl;
}



void Stop(const int& /*data*/)
{
    std::cout << "__NR__:  " << mtk::dtNowLocal() << "  paramoooooooossss...." << std::endl;
    mtk::stop_timer();
}


//---------------------------------------------------------------------------

//          M A I N

//---------------------------------------------------------------------------

int main(int /*argc*/, char** /*argv[]*/)
{

    try {
        std::cout << "__NR__:  " << "starting... " << mtk::dtNowLocal() << std::endl;


        TestCallLater tcl;

    //-------------------------------------
    //  dos formas de llamar a call_later 
    //-------------------------------------

        //mtk::CallLaterFactory1S(mtk::dtSeconds(2), 11).connect(callLaterInt);
        //mtk::CallLaterFactory1S(mtk::dtSeconds(3), std::string(" parámetro")).connect(callLaterString);
        //mtk::CallLaterFactory1S(mtk::dtSeconds(10), 0).connect(Stop);
        
        MTK_CALL_LATER1S_F(mtk::dtSeconds(2), 11, callLaterInt)
        MTK_CALL_LATER1S_F(mtk::dtSeconds(3), std::string(" parámetro"), callLaterString)
        MTK_CALL_LATER1S_F(mtk::dtSeconds(10), 0, Stop)

    //-------------------------------------
    //  dos formas de llamar a call_later 
    //-------------------------------------


		mtk::start_timer_wait_till_end();


        #include "support/release_on_exit.hpp"
        return 0;

    } MTK_CATCH_CALLFUNCION(std::cout << , "main", "nothig additional to say")

    #include "support/release_on_exit.hpp"
    return -1;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

//  RECEPTOR ALARMAS SALIDA GENERAL

//---------------------------------------------------------------------------

void mtk::AlarmMsg (const Alarm& alarma)
{
        std::cout << "\n\r";
        std::cout << std::endl << "ALARMA SALIDA..." << std::endl ;
        std::cout << alarma << std::endl ;
}
