//---------------------------------------------------------------------------

#include "sockets/tcp_p2bytes_size.h"
#include "sockets/tcp_server_mono.h"
#include "support/call_later.h"








void Stop(const int&)
{
    mtk::stop_timer();
}

//---------------------------------------------------------------------------
//  declaración socket tcp 2bytessize server mono

class class_tcp_server
            :  public mtk::tcp_p2bytes_size<
                            mtk::tcp_server_mono<mtk::tcp_base_socket> >
{
    mtk::non_copyable noncopy;
    
public:

    class_tcp_server(const std::string& _name)
            :   mtk::tcp_p2bytes_size<mtk::tcp_server_mono<mtk::tcp_base_socket> >(_name), 
                connected(false) 
    {
        MTK_CONNECT_THIS(signal_connect,    OnConnectClient)
        MTK_CONNECT_THIS(signal_disconnect, OnDisconnectClient)
    }
            
    void OnConnectClient    (void);
    void OnDisconnectClient (const std::string& reason);
    
private:
    bool connected;
};


//---------------------------------------------------------------------------

//  RECEPCIÓN DE MENSAJES TIBCO

//---------------------------------------------------------------------------

void OnErrorMsg(const mtk::Alarm& alarma)
{
    std::cout << std::endl << std::endl << alarma << std::endl;
}



//---------------------------------------------------------------------------
//  GESTIÓN TCP SERVER
//---------------------------------------------------------------------------

class_tcp_server* server=0;
void server_receive(const char* data, int /*size*/)
{
    std::cout << "received... "  << std::string(data);
    
    std::string message(MTK_SS("sending...    "  << std::string(data) << " PONG... " << std::endl));
    server->write(message.c_str(), int(message.size()));
}

void class_tcp_server::OnConnectClient(void)
{
    std::cout << "client connected__________________________" << std::endl;
    connected = true;
}


void class_tcp_server::OnDisconnectClient(const std::string& reason)
{
    std::cout << "client   D I S C O N N E C T E D  __   "  <<  reason  << std::endl;
    connected = false;
}





//---------------------------------------------------------------------------

//          M A I N

//---------------------------------------------------------------------------

int main(int /*argc*/, char** /*argv[]*/)
{

    try {


        //  TCP  SERVER -------------------------------------------------------
        class_tcp_server     tcp_server("pr_server");        
        tcp_server.listen(22333);
        tcp_server.signal_received.connect(server_receive);
        //---------------------------------------------------------------------


        server = &tcp_server;   // just for this example, try don't do this things
            
        MTK_CALL_LATER1S_F(mtk::dtSeconds(15), 0, Stop)      //  programamos parada

        //  S T A R T 
		mtk::start_timer_wait_till_end();
        //---------------------------------------------------------------------

        

        //  F I N  !!! 
        #include "support/release_on_exit.hpp"
        return 0;
        //---------------------------------------------------------------------


    }
    MTK_CATCH_CALLFUNCION(std::cout <<, "main", "nothing aditional to say")

    return -1;
}
//---------------------------------------------------------------------------






//---------------------------------------------------------------------------

//  RECEPTOR ALARMAS SALIDA GENERAL

//---------------------------------------------------------------------------

void mtk::AlarmMsg (const Alarm& alarma)
{
        std::cout << std::endl;
        std::cout << std::endl << "ALARMA SALIDA..." << std::endl ;
        std::cout << alarma << std::endl ;
}



