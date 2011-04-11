#include <iostream>
#include "support/alarm.h"
#include "mtk_qpid/mtk_qpid.hpp"
#include "support/timer.h"
#include "support/call_later.h"
#include "support/alarm.h"
#include "support/factory.hpp"
#include <qpid/messaging/Message.h>


#include "test_messages.h"    // <1>


// trick to maintain a single file. Only valid for onefile examples
#include "test_messages.impl"


const std::string g_url = "amqp:tcp:127.0.0.1:5672";
const std::string g_address = "testing";




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
    static mtk::CountPtr< mtk::qpid_session > qpid_session = mtk::get_from_factory< mtk::qpid_session >(mtk::make_tuple(g_url, g_address));
    
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
        

        mtk::send_message(qpid_session, rq);        //  using implicit subject defined on message, and it will add control fields
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
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpidr2, 
                                g_url,
                                g_address,
                                testing::RQ_NW_LS::get_in_subject(),        //  using implicit subject defined on message
                                testing::RQ_NW_LS, 
                                on_message)
        //-----------------------------------------------------------------------------------------------------



        //  <3>
        //-----------------------------------------------------------------------------------------------------
        mtk::CountPtr< mtk::handle_qpid_exchange_receiver> hqpidr3;
        hqpidr3 = mtk::get_from_factory<mtk::handle_qpid_exchange_receiver>(mtk::make_tuple(g_url, g_address, std::string("#")));
        hqpidr3->signalMessage->connect(on_message);        
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
 





void mtk::AlarmMsg(const mtk::Alarm& error)
{
    std::cout << error << std::endl;
} 

void mtk::check_control_flields_flucts(const std::string &, const mtk::DateTime&)
{
}
