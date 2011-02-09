#include <iostream>
#include "support/alarm.h"
#include "mtk_qpid/mtk_qpid.h"
#include "support/timer.h"
#include "support/call_later.h"
#include "support/alarm.h"
#include "support/factory.hpp"
#include <qpid/messaging/Message.h>


void mtk::AlarmMsg(const mtk::Alarm& error)
{
    std::cout << error << std::endl;
}

namespace  mtk {
std::string  get_cli_srv(void)
{
    return "SRV";
}

void check_control_fields_flucts(const std::string &, const mtk::DateTime&)
{
}
};      //  namespace  mtk {








#include "test_messages.h"    // <1>


// trick to maintain a single file. Only valid for onefile examples
#include "test_messages.impl"




const   mtk::t_qpid_url      g_url      ("amqp:tcp:127.0.0.1:5672");
const   mtk::t_qpid_address  g_address  ("testing");




void on_message(const testing::RQ_NW_LS& message)
{
    std::cout << "RECEIVED----------------------------" << std::endl;
    std::cout <<  message << std::endl;
    std::cout << std::endl << std::endl << std::endl;
}


void on_message(const qpid::messaging::Message& message)
{
    qpid::types::Variant::Map mv;
    qpid::messaging::decode(message, mv);
    std::cout << mv  << std::endl;


    std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it = mv.find("pos");
    if (it == mv.end())
        std::cout << "NOT FOUND" << std::endl;
    else
    {
        std::cout << it->second << "-------------------" <<std::endl;
    }
}



void send_messages(void)
{
    {
        testing::LimitPosition lp(     mtk::make_nullable(std::string("b")),
                                    mtk::make_nullable(mtk::FixedNumber(mtk::fnDouble(1.88), mtk::fnDec(2), mtk::fnInc(1))),
                                    mtk::FixedNumber(mtk::fnDouble(2.66), mtk::fnDec(2), mtk::fnInc(1)));

        mtk::list<std::string> names;
        names.push_back("john");
        names.push_back("peter");

        mtk::list<testing::LimitPosition>  positions;
        positions.push_back(lp);


        testing::RQ_NW_LS rq(   "order_id",
                                "cli_ref",
                                lp,
                                lp,
                                testing::RQ_NW_LS::IC_control_fields_(mtk::DateTime(mtk::dtYear(2011), mtk::dtMonth(1), mtk::dtDay(20)), 123),
                                testing::RQ_NW_LS::IC_product_code("market", "product", "aditional code"),
                                names,
                                positions);


        static auto sender = mtk::get_from_factory< mtk::mtkqpid_sender2 > (mtk::make_tuple(g_url, g_address, mtk::QUEUE__DEFAULT_SENDER_CONFIG));
        mtk::send_message_with_sender(sender, rq);      //  using implicit address and routing key  defined on message, and it will add control fields
        //  mtk_send_message("url_for", rq);     if you are using mtk::admin, it's better this way
    }

}

void stop(const int&)
{
    mtk::stop_timer();
}

int main(int /*argc*/, char** /*argv*/)
{
    try
    {

        //  <2>
        //-----------------------------------------------------------------------------------------------------
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<testing::RQ_NW_LS> > hqpidr2;
        MTK_QPID_RECEIVER_CONNECT_F__DEPRECIATED(
                                hqpidr2,
                                g_url,
                                testing::RQ_NW_LS::get_in_subject(),        //  using implicit subject defined on message
                                testing::RQ_NW_LS,
                                on_message,
                                (mtk::dtDateTime{mtk::dtYear(2011), mtk::dtMonth(2), mtk::dtDay(5)}))
        //-----------------------------------------------------------------------------------------------------



        //  <3>
        //-----------------------------------------------------------------------------------------------------
        mtk::CountPtr< mtk::handle_qpid_exchange_receiver> hqpidr3;
        hqpidr3 = mtk::get_from_factory<mtk::handle_qpid_exchange_receiver>(mtk::make_tuple(g_url, g_address, mtk::t_qpid_filter("#"), mtk::QUEUE__DEFAULT_RECEPTOR_CONFIG));
        hqpidr3->__impl->signalMessage.connect(on_message);
        //-----------------------------------------------------------------------------------------------------


        send_messages();

        MTK_CALL_LATER1S_F(mtk::dtSeconds(5), 0, stop);


        mtk::start_timer_wait_till_end();

        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION(std::cout << , "main", "no more")

    #include "support/release_on_exit.hpp"
    return -1;
}

