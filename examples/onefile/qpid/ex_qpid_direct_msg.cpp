 
#include <iostream>
#include "mtk_qpid/mtk_qpid.hpp"
#include "support/timer.h"
#include "support/call_later.h"
#include "support/alarm.h"

#include <qpid/messaging/MapContent.h>



const std::string g_url = "amqp:tcp:127.0.0.1:5672";
const std::string g_address = "testing";



void on_message(const qpid::messaging::Message& message)
{
    qpid::messaging::MapView  view(message);
    
    std::cout <<  message.getHeaders() << "  " << view << std::endl;
}




void send_message(void)
{
    static mtk::CountPtr< mtk::qpid_session > qpid_session = mtk::get_from_factory< mtk::qpid_session >(mtk::make_tuple(g_url, g_address));
    
    qpid::messaging::Message message;
    qpid::messaging::MapContent content(message);
    


    //  <1>
    content["id"] = 987654321;
    content["name"] = "Widget";
    content["percent"] = 0.99;
    qpid::messaging::Variant::List colours;
    colours.push_back(qpid::messaging::Variant::Variant("red"));
    colours.push_back(qpid::messaging::Variant::Variant("green"));
    colours.push_back(qpid::messaging::Variant::Variant("white"));
    content["colours"] = colours;

    qpid::messaging::Variant::Map nested;
    nested["n1"] = 1;
    nested["n2"] = 22;
    content["nested"] = nested;
    
    //  list of sub_messages
    qpid::messaging::Variant::List vlist;
    vlist.push_back("hi");
    vlist.push_back("there");
    
    content["list"] = vlist;
    
    

    content.encode();
    
    message.setSubject("hola.pajarito");
    qpid_session->sender.send(message);
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
        hqpidr2 = mtk::get_from_factory<mtk::handle_qpid_exchange_receiver>(mtk::make_tuple(g_url, g_address, std::string("#")));
        hqpidr2->signalMessage->connect(on_message);        
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
