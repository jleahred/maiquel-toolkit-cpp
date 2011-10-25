#include <iostream>
#include "mtk_qpid/mtk_qpid.hpp"
#include "support/timer.h"
#include "support/call_later.h"
#include "support/alarm.h"


const   mtk::t_qpid_url      g_url      ("amqp:tcp:127.0.0.1:5672");
const   mtk::t_qpid_address  g_address  ("testing");



void on_message(const qpid::messaging::Message& message)
{
    std::cout <<  message.getSubject() << "  " << message.getContent() << std::endl;
}




void send_message(void)
{
    static int counter=0;

    qpid::messaging::Message msg(MTK_SS(++counter));
    msg.setSubject("hola.pajarito");

    static auto sender = mtk::get_from_factory< mtk::mtkqpid_sender2 > (mtk::make_tuple(g_url, g_address));
    sender->qpid_sender.send(msg);

}

void stop(const int&)
{
    mtk::stop_timer();
}

int main(int /*argc*/, char** /*argv*/)
{
    std::cout << "to run this example...  qpid-cofigure add exchange topic tesging" << std::endl << std::endl;


    try
    {
        mtk::t_qpid_filter   filter  ("#");


        //  <1>
        //-----------------------------------------------------------------------------------------------------
        mtk::CountPtr< mtk::handle_qpid_exchange_receiver> hqpidr =
                                            mtk::get_from_factory<mtk::handle_qpid_exchange_receiver>(mtk::make_tuple(g_url, g_address, filter));
        hqpidr->signalMessage->connect(on_message);
        //-----------------------------------------------------------------------------------------------------



        MTK_TIMER_1SF(send_message)

        MTK_CALL_LATER1S_F(mtk::dtSeconds(5), 0, stop);


        mtk::start_timer_wait_till_end();

        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION(std::cout << , "main", "no more")

    #include "support/release_on_exit.hpp"
    return -1;
}









void mtk::AlarmMsg(const mtk::Alarm& error)
{
    std::cout << error << std::endl;
}
