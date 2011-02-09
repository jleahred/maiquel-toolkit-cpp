#include "generated/simple_dor.h"

#include "generated/simple_dor.impl"


void on_closed(void)
{
    std::cout << "closed" << std::endl;
}

void on_opened(void)
{
    std::cout << "open" << std::endl;
}






int  main(int /*argc*/, const char** /*argv[]*/)
{

    try
    {
        testing::simple_dor  dor;

        dor.sig_closed.connect(on_closed);
        dor.sig_opened.connect(on_opened);


        dor.open();
        dor.close();
        dor.close();
    }
    MTK_CATCH_CALLFUNCION (std::cout << , "main", "nothing more")

    return 0;
}



void mtk::AlarmMsg(const mtk::Alarm& error)
{
    std::cout << error << std::endl;
}
