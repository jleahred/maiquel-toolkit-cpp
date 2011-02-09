//---------------------------------------------------------------------------


#include "sockets/tcp_p2bytes_size.h"
#include "sockets/tcp_client.h"
#include "support/call_later.h"

#include "support/misc.h"
#include "support/exec_max_frec.h"



void Stop(const int&)
{
    mtk::stop_timer();
}


//---------------------------------------------------------------------------
//  declaración socket tcp 2bytes size client

class class_tcp_client
            :  public   mtk::tcp_p2bytes_size<
                            mtk::tcp_client <mtk::tcp_base_socket> >
{
    mtk::non_copyable noncopy;
public:
    class_tcp_client(const std::string& _name)
            : mtk::tcp_p2bytes_size<mtk::tcp_client<mtk::tcp_base_socket> >(_name) {};

};



//  ------------------------------------------------------------
//      gestión tcp client

void client_receive(const char* data, int size)
{
    static int contador=0;
    ++contador;

    static int          max_msg_size=0;

    MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(1))
        std::cout << "__NR__:  " << "msg/seg...              " << contador << std::endl;
        if (max_msg_size>0)
            std::cout << "max msg size... (>1000) " << max_msg_size << std::endl;
        contador=0;
        max_msg_size=0;
    MTK_END_EXEC_MAX_FREC

	if (size>1000)
    {
	    std::cout << "  -----------------"  << size << std::endl;
        if (max_msg_size < size)
            max_msg_size = size;
    }


    MTK_EXEC_MAX_FREC_S(mtk::dtMilliseconds(10))
        std::cout << "recibido... "  << (const char*)data << "-----------------------" << std::endl;
    MTK_END_EXEC_MAX_FREC
}


void client_connected(void)
{
    std::cout << "client connected___________________________" << std::endl;
}


class_tcp_client* global_tcp_client;
void timer(void)
{
    static int contador=0;
    std::string message = MTK_SS("ping " << ++contador << std::endl);
    std::cout << "sending...  "  << message;
    global_tcp_client->write(message.c_str(), int(message.size()));
}


//---------------------------------------------------------------------------

//          M A I N

//---------------------------------------------------------------------------

int main(int /*argc*/, char** /*argv[]*/)
{

    try {

        mtk::sleep(mtk::dtSeconds(3));

        //  TCP  CLIENT -------------------------------------------------------
        class_tcp_client     tcp_client("pr_client");
        tcp_client.signal_received.connect(client_receive);
        tcp_client.signal_connect.connect(client_connected);
        tcp_client.connect("127.0.0.1", 22333);
        //---------------------------------------------------------------------

        global_tcp_client = &tcp_client;        //  just for this example, try don't do this things
        MTK_TIMER_1DF(timer);

        MTK_CALL_LATER1S_F(mtk::dtSeconds(9), 0, Stop)      //  programamos parada

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



//  SUPPORT  -------------------------------------------------

