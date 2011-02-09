#include <iostream>
#include "mtk_qpid/mtk_qpid.h"
#include "support/timer.h"
#include "support/call_later.h"
#include "support/alarm.h"


namespace  mtk {
std::string  get_cli_srv(void)
{
    return "SRV";
}
};      //  namespace  mtk {

void mtk::AlarmMsg(const mtk::Alarm& error)
{
    std::cout << error << std::endl;
}





const mtk::t_qpid_url       g_url ("amqp:tcp:127.0.0.1:5672");
const mtk::t_qpid_address   g_address ("testing");



class ex_qpid_sender_and_receptor : public mtk::SignalReceptor
{
public:

    ex_qpid_sender_and_receptor()
    {
        MTK_TIMER_1S(send_message)
        hqpidr2 = mtk::get_from_factory<mtk::handle_qpid_exchange_receiver>(mtk::make_tuple(g_url, g_address, mtk::t_qpid_filter("#"), mtk::QUEUE__DEFAULT_RECEPTOR_CONFIG));
        MTK_CONNECT_THIS(hqpidr2->__impl->signalMessage, on_message);
    }

private:
    mtk::CountPtr<mtk::handle_qpid_exchange_receiver> hqpidr2;

    void send_message(void)
    {
        static int counter=0;

        qpid::messaging::Message msg(MTK_SS(++counter));
        msg.setSubject("hola.pajarito");

        static auto sender = mtk::get_from_factory< mtk::mtkqpid_sender2 > (mtk::make_tuple(g_url, g_address, mtk::QUEUE__DEFAULT_SENDER_CONFIG));
        sender->qpid_sender().send(msg);
    }

    void on_message(const qpid::messaging::Message& message)
    {
        std::cout <<  message.getSubject() << "  " << message.getContent() << std::endl;
    }

};





void stop(const int&)
{
    mtk::stop_timer();
}


int main(int /*argc*/, char** /*argv*/)
{
    try
    {

        ex_qpid_sender_and_receptor testing;


        MTK_CALL_LATER1S_F(mtk::dtSeconds(5), 0, stop);


        mtk::start_timer_wait_till_end();

        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION(std::cout << , "main", "no more")

    #include "support/release_on_exit.hpp"
    return -1;
}
