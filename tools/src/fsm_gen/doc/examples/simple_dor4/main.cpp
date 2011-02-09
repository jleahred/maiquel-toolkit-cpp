#include "support/mtk_string.h"
#include "support/misc.h"
#include "support/crc32.h"



std::string generate_key (const std::string& /*user*/)
{
	return MTK_SS(mtk::rand());
}


#include "generated/simple_dor.h"
#include "generated/simple_dor.impl"


void on_closed(void)
{
    std::cout << "closed  --------------------------------------------------------" << std::endl;
}

void on_opened(void)
{
    std::cout << "opened  --------------------------------------------------------" << std::endl;
}


std::string generated_key;
void on_generated_key(const std::string& key)
{
	std::cout  << "generated key " << key << std::endl;
	generated_key = key;
}


void on_logic_error(const mtk::Alarm& al)
{
	std::cout << al << std::endl;
	std::cout << "================================================================================" << std::endl;
}







int  main(int /*argc*/, const char* /*argv*/[])
{
    try
    {
        testing::simple_dor dor;

        dor.sig_closed.connect(on_closed);
        dor.sig_opened.connect(on_opened);
        dor.sig_generated_key.connect(on_generated_key);
        dor.sig_alarm.connect(on_logic_error);


        dor.rq_key("fulanito");
        dor.rq_open("fulanito", MTK_SS(mtk::crc32(MTK_SS("fulanito1111"<< generated_key, A))));
        dor.rq_open("fulanito", "1111");
        dor.rq_key("fulanito");
        dor.rq_key("fulanito");
        dor.rq_key("fulanito");
        dor.rq_close("fulanito", "key");
    }
    MTK_CATCH_CALLFUNCION (std::cout << , "main", "nothing more")

    return 0;
}



void mtk::AlarmMsg(const mtk::Alarm& error)
{
    std::cout << error << std::endl;
}
