#ifndef __tcp_server_mono__
#define __tcp_server_mono__



#include "support/alarm.h"
#include "support/signalslot.hpp"
#include "support/timer.h"
#include "support/signalslot.hpp"

#include "support/mtk_string.h"



#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>




#include "impl_socket_support.h"




namespace mtk {


	

    
template <typename LOW_SOCKET>
class tcp_server_mono : public LOW_SOCKET
{
    typedef     tcp_server_mono  CLASS_NAME;
	mtk::non_copyable non_copy;

public:
	tcp_server_mono(const std::string& name);
	virtual ~tcp_server_mono() {};

    void  listen           (short unsigned int _port);


protected:
    unsigned short int              port;
    struct sockaddr_in              sockaddr;  /* Internet socket address stuct */

private:
    bool    listening;
    void    check_connections(void);
    int     socket2accept_connections;

    void    start_timer(void);

};








//      I M P L E M E N T A T I O N
template <typename LOW_SOCKET>
tcp_server_mono<LOW_SOCKET>::tcp_server_mono(const std::string& _name)
    :  LOW_SOCKET(_name), listening(false), socket2accept_connections(-1)
{
      start_timer();
}



template <typename LOW_SOCKET>
void  tcp_server_mono<LOW_SOCKET>::start_timer(void)
{
    MTK_TIMER_1D(check_connections);
}


template <typename LOW_SOCKET>
void  tcp_server_mono<LOW_SOCKET>::check_connections(void)
{
    if (!listening)  return;
    

    if (LOW_SOCKET::handle_socket <= 0)
	{
        socklen_t socklen = sizeof(sockaddr);
		int result = accept(socket2accept_connections,(struct sockaddr*)&sockaddr,&socklen);
		if (result > 0)
		{
			LOW_SOCKET::handle_socket = result;
            LOW_SOCKET::signal_connect.emit();
            mtk::socket_configure_nonblocking(LOW_SOCKET::handle_socket, LOW_SOCKET::name);
		}
	}


}







template <typename LOW_SOCKET>
void  tcp_server_mono<LOW_SOCKET>::listen           (short unsigned int _port)
{
    port = _port;
    listening = true;

    socket2accept_connections =socket(AF_INET, SOCK_STREAM, 0);

    if(socket2accept_connections == MTK_SOCKET_ERROR)
        throw mtk::Alarm(MTK_HERE, "socket", MTK_SS(LOW_SOCKET::name << "  Could not create a server socket"), mtk::alPriorError);
	memset(&sockaddr, 0, sizeof(sockaddr_in));
    sockaddr.sin_addr.s_addr=INADDR_ANY;
    sockaddr.sin_port= in_port_t(MTK_HTONS(port));
    sockaddr.sin_family=AF_INET;


    // bind to a port 
    if(bind(socket2accept_connections,(struct sockaddr*)&sockaddr,sizeof(sockaddr)) == MTK_SOCKET_ERROR)
        throw mtk::Alarm(MTK_HERE, "socket", MTK_SS(LOW_SOCKET::name << "  Could not bind a socket"), mtk::alPriorError);

	#if (MTK_PLATFORM == MTK_WIN_PLATFORM)

		unsigned long val = 1;
		if (ioctlsocket( socket2accept_connections, FIONBIO, &val ) != 0)
			throw mtk::Alarm(MTK_HERE, "socket", MTK_SS(LOW_SOCKET::name << "  Error configuring non blocking socket"), mtk::alPriorError);

	#elif MTK_PLATFORM == MTK_LINUX_PLATFORM

		if ( fcntl(socket2accept_connections, F_SETFL, O_NONBLOCK) != 0)
			throw mtk::Alarm(MTK_HERE, "socket", MTK_SS(LOW_SOCKET::name << "  Error configuring non blocking socket"), mtk::alPriorError);

	#endif



    // establish listen queue 
    if(::listen(socket2accept_connections, 1/*queue of connections*/) == MTK_SOCKET_ERROR)
        throw mtk::Alarm(MTK_HERE, "socket", MTK_SS(LOW_SOCKET::name << "  Could not start listening"), mtk::alPriorError);

}



};      //  namespace mtk




#endif // __tcp_server_mono__
