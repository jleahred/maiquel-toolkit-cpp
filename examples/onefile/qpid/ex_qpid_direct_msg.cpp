
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






const   mtk::t_qpid_url      g_url      ("amqp:tcp:127.0.0.1:5672");
const   mtk::t_qpid_address  g_address  ("testing");



void on_message(const qpid::messaging::Message& message)
{
    qpid::types::Variant::Map  view;
    qpid::messaging::decode(message, view);

    std::cout <<  message.getSubject() << "  " << view << std::endl;
}




void send_message(void)
{
    qpid::messaging::Message message;
    qpid::types::Variant::Map content;



    //  <1>
    content["id"] = 987654321;
    content["name"] = "Widget";
    content["percent"] = 0.99;
    qpid::types::Variant::List colours;
    colours.push_back(qpid::types::Variant("red"));
    colours.push_back(qpid::types::Variant("green"));
    colours.push_back(qpid::types::Variant("white"));
    content["colours"] = colours;

    qpid::types::Variant::Map nested;
    nested["n1"] = 1;
    nested["n2"] = 22;
    content["nested"] = nested;

    //  list of sub_messages
    qpid::types::Variant::List vlist;
    vlist.push_back("hi");
    vlist.push_back("there");

    content["list"] = vlist;


    qpid::messaging::encode(content, message);

    message.setSubject("hola.pajarito");


    static auto sender = mtk::get_from_factory< mtk::mtkqpid_sender2 > (mtk::make_tuple(g_url, g_address, mtk::QUEUE__DEFAULT_SENDER_CONFIG));
    sender->qpid_sender().send(message);
}

void stop(const int&)
{
    mtk::stop_timer();
}

int main(int /*argc*/, char** /*argv*/)
{
    try
    {

        //-----------------------------------------------------------------------------------------------------
        mtk::CountPtr< mtk::handle_qpid_exchange_receiver> hqpidr2;
        hqpidr2 = mtk::get_from_factory<mtk::handle_qpid_exchange_receiver>(mtk::make_tuple(g_url, g_address, mtk::t_qpid_filter("#"), mtk::QUEUE__DEFAULT_RECEPTOR_CONFIG));
        hqpidr2->__impl->signalMessage.connect(on_message);
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
