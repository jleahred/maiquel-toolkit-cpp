#include "sockets/tcp_pstringseparator.h"
#include "sockets/tcp_client.h"
#include "sockets/tcp_server_mono.h"
#include "sockets/tcp_base_socket.h"
#include "support/call_later.h"




class tcp_client_stringseparator 
            :  public   mtk::tcp_pstringseparator<
                            mtk::tcp_client <mtk::tcp_base_socket> >
{
    mtk::non_copyable noncopy;
public:
    tcp_client_stringseparator(const std::string& _name, const std::string& _separator)
            : mtk::tcp_pstringseparator<mtk::tcp_client<mtk::tcp_base_socket> >(_name, _separator) {};

};


class tcp_servermono_stringseparator 
            :  public mtk::tcp_pstringseparator<
                            mtk::tcp_server_mono<mtk::tcp_base_socket> >
{
    mtk::non_copyable noncopy;
public:
tcp_servermono_stringseparator(const std::string& _name, const std::string& _separator)
            : mtk::tcp_pstringseparator<mtk::tcp_server_mono<mtk::tcp_base_socket> >(_name, _separator) {};
};





tcp_client_stringseparator         tcp_client("prueba", "\n\r");
tcp_servermono_stringseparator     tcp_server("prueba", "\n\r");




void server_receive(const std::string& data)
{
    std::cout << "recibe el servidor...  "  << data;
}

void server_connected(void)
{
    std::cout << "server connected" << std::endl;
    tcp_server.write("hola pajaritooooooooooooooooooooooooo");
}

void client_receive(const std::string& data)
{
    std::cout << "RECIBE EL CLIENTE...   "  << data;
}


void client_connected(void)
{
    std::cout << "client connected" << std::endl;
    tcp_client.write("Hola pajarito sin cola");
    tcp_client.write("Hasta luego, cara huevo");
    tcp_client.write("");
    tcp_client.write("Una pasa que me he tragado y no me pasa");
}


void stop(const int&)
{
    mtk::stop_timer();
}



int  main(int /*argc*/, char** /*argv*/)
{

   try
   {


        //  INIT  ------------------------------------------------------

            tcp_server.listen(22303);
            tcp_server.signal_received_string.connect(server_receive);
            tcp_server.signal_connect.connect(server_connected);
            tcp_client.signal_received_string.connect(client_receive);
            tcp_client.signal_connect.connect(client_connected);

            tcp_client.connect("127.0.0.1", 22303);


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
