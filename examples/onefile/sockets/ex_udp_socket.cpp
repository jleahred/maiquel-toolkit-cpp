#include "sockets/udp_socket.h"
#include "sockets/socket_support.h"
#include "sockets/tcp_client.h"

#include "support/call_later.h"
#include "support/timer.h"
#include "support/date_time.h"





mtk::udp_socket udp("prueba");


void on_packet_received(const char* packet, ssize_t, long unsigned ip_address_source)
{
    std::cout << "   from: " << mtk::socket_address2string(ip_address_source) << packet <<  std::endl;
}



void on_timer(void)
{
    static unsigned  loop_back = unsigned(mtk::socket_resolv_url("127.0.0.1"));
    static int counter=0;
    std::string tosend = MTK_SS(++counter << std::endl);
    udp.send_to( loop_back, tosend.c_str(), tosend.size());
}

void stop(const int&)
{
    mtk::stop_timer();
}



int  main(int argc, const char* argv[])
{

   try
   {

        std::cout << "Prueba de socket udp" << std::endl << std::endl;

        //  debug
        if (argc==1)
        {
            argc = 2;
            argv[1]= "etc/hola.cfg";   // truco sólo para ejemplos
        }

        //  INIT  ------------------------------------------------------

            udp.bind(30356);
            udp.signal_packet_received.connect(on_packet_received);


            MTK_CALL_LATER1S_F(mtk::dtSeconds(5), 0, stop);

            MTK_TIMER_1DF (on_timer);
            mtk::start_timer_wait_till_end();

        //---------------------------------------------------------------------





            #include "support/release_on_exit.hpp"
            return 0;

    }
    MTK_CATCH_CALLFUNCION (std::cout << , "main", "nothing more")

    #include "support/release_on_exit.hpp"
    return -1;
}



void mtk::AlarmMsg(const mtk::Alarm& error)
{
    std::cout << error << std::endl;
}

