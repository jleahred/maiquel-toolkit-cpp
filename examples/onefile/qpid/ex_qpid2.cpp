#include <iostream>
#include "mtk_qpid/mtk_qpid.hpp"
#include "support/timer.h"
#include "support/call_later.h"
#include "support/alarm.h"


const std::string g_url = "amqp:tcp:127.0.0.1:5672";
const std::string g_address = "testing";



class ex_qpid_sender_and_receptor : public mtk::SignalReceptor
{
typedef ex_qpid_sender_and_receptor CLASS_NAME;

public:

    ex_qpid_sender_and_receptor()
    {
        MTK_TIMER_1S(send_message)
        hqpidr2 = mtk::get_from_factory<mtk::handle_qpid_exchange_receiver>(mtk::make_tuple(g_url, g_address, std::string("#")));
        MTK_CONNECT_THIS(*(hqpidr2->signalMessage), on_message);
    }

private:
    mtk::CountPtr<mtk::handle_qpid_exchange_receiver> hqpidr2;

    void send_message(void)
    {
        static int counter=0;
        static mtk::CountPtr< mtk::qpid_session > qpid_session = mtk::get_from_factory< mtk::qpid_session >(mtk::make_tuple(g_url, g_address));

        qpid::messaging::Message msg(MTK_SS(++counter));
        msg.setSubject("hola.pajarito");
        qpid_session->sender.send(msg);
    }

    void on_message(const qpid::messaging::Message& message)
    {
        std::cout <<  message.getHeaders() << "  " << message.getContent() << std::endl;
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





void mtk::AlarmMsg(const mtk::Alarm& error)
{
    std::cout << error << std::endl;
}