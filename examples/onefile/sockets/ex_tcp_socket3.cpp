#include "sockets/tcp_p2bytes_size.h"
#include "sockets/tcp_client.h"
#include "sockets/tcp_server_mono.h"
#include "sockets/tcp_base_socket.h"
#include "support/call_later.h"




class tcp_client_p2bytes
            :  public   mtk::tcp_p2bytes_size<
                            mtk::tcp_client <mtk::tcp_base_socket> >
{
    mtk::non_copyable noncopy;
public:
    tcp_client_p2bytes(const std::string& _name)
            : mtk::tcp_p2bytes_size<mtk::tcp_client<mtk::tcp_base_socket> >(_name) {};

};


class tcp_servermono_p2bytes
            :  public mtk::tcp_p2bytes_size<
                            mtk::tcp_server_mono<mtk::tcp_base_socket> >
{
    mtk::non_copyable noncopy;
public:
    tcp_servermono_p2bytes(const std::string& _name)
            : mtk::tcp_p2bytes_size<mtk::tcp_server_mono<mtk::tcp_base_socket> >(_name) {};
};





tcp_client_p2bytes         tcp_client("pr_client");
tcp_servermono_p2bytes     tcp_server("pr_server");




void server_receive(const char* data, int /*size*/)
{
    std::cout << "recibe el servidor...  "  << data << std::endl;
}

void server_connected(void)
{
    std::cout << "server connected" << std::endl;
    std::string msg = "hola.";
    tcp_server.write(msg.c_str(), int(msg.length()+1));      //  SEUO  +1 para incluir el 0 del final
}

void client_receive(const char* data, int /*size*/)
{
    std::cout << "RECIBE EL CLIENTE...   "  << data  << std::endl;
}


void client_connected(void)
{
    std::cout << "client connected" << std::endl;
    std::string msg = "holaaaaaaa";
    tcp_client.write(msg.c_str(), int(msg.length()+1));
    msg = "adiooooos";
    tcp_client.write(msg.c_str(), int(msg.length()+1));
    msg = "otro mensaje";
    tcp_client.write(msg.c_str(), int(msg.length()+1));

}


void stop(const int&)
{
    mtk::stop_timer();
}



int  main(int /*argc*/, char** /*argv[]*/)
{

   try
   {


        //  INIT   ------------------------------------------------------

            tcp_server.listen(22301);
            tcp_server.signal_received.connect(server_receive);
            tcp_server.signal_connect.connect(server_connected);
            tcp_client.signal_received.connect(client_receive);
            tcp_client.signal_connect.connect(client_connected);

            tcp_client.connect("127.0.0.1", 22301);


            MTK_CALL_LATER1S_F(mtk::dtSeconds(5), 0, stop);

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
