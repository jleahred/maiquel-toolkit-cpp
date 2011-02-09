#include "udp_socket.h"

#include "socket_support.h"
#include "support/alarm.h"
#include "support/timer.h"
#include "support/exec_max_frec.h"
#include "support/mtk_string.h"



#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>


#include "impl_socket_support.h"


namespace {
    const int  TCP_SOCKET_BUFFER_SIZE   = 65536;
};


namespace mtk {

    

udp_socket::udp_socket(const std::string& _name)
    : 
          handle_socket(-1)
        , name(_name)
        , pbuffer (new char [TCP_SOCKET_BUFFER_SIZE])
		, binded_port(0)
{
	start_timer();
	
    #if (MTK_PLATFORM == MTK_WIN_PLATFORM)
        WORD wVersionRequested;
        WSADATA wsaData;
        //int err;
        wVersionRequested = MAKEWORD(2, 2);

        if (WSAStartup(wVersionRequested, &wsaData) != 0)   //pendiente de revisión gestión errores
		{
            get_socket_error();
			throw mtk::Alarm(MTK_HERE, MTK_SS(name << "  WSAStartup " <<  strerror(errno)), mtk::alPriorError);
		}
		
    #endif
	
	if (handle_socket > 0)
        throw mtk::Alarm(MTK_HERE, MTK_SS(name << "  The socket is already connected"), mtk::alPriorError);
	
    // create socket
    handle_socket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    //handle_socket=socket(PF_INET, SOCK_DGRAM, 0);

    if(handle_socket == MTK_SOCKET_ERROR)
        throw mtk::Alarm(MTK_HERE, MTK_SS(name << "Could not create a socket"), mtk::alPriorError);

    configure_socket();
	
}

udp_socket::~udp_socket()
{
    try
    {
        delete[] pbuffer;
        close("~udp_socket");
    }
    MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "~udp_socket", MTK_SS(name << "  closing socket"));    
}


void  udp_socket::start_timer(void)
{
    MTK_TIMER_1C(check_input)
}


int     udp_socket::get_buffer_size (void) const
{
    return TCP_SOCKET_BUFFER_SIZE;
}



void udp_socket::close(const std::string& reason)
{
	if (handle_socket == -1)
		return;
		

    if(mtk::socket_close(handle_socket) == MTK_SOCKET_ERROR)
    {
        handle_socket = -1;
        get_socket_error();
        throw mtk::Alarm(MTK_HERE, MTK_SS(name << "  Error closing socket " <<  strerror(errno)), mtk::alPriorError);
    }
    else
    {
        handle_socket = -1;
        signal_disconnect.emit(reason);
    }

}





void udp_socket::check_input(void)
{
	if (handle_socket<=0)   
		return;		//	todavía no hay nada que chequear

    while(true)
    {
        struct sockaddr_in from;
        memset(&from, 0, sizeof(sockaddr_in));
        from.sin_family=AF_INET;
        from.sin_addr.s_addr=INADDR_ANY;
        socklen_t fromlen = sizeof(from);
        ssize_t bytes_readed = recvfrom (handle_socket, pbuffer, mtk::udp_socket::get_buffer_size(), 0, (sockaddr*)&from, &fromlen);
        if (bytes_readed>0)
            signal_packet_received(pbuffer, int(bytes_readed), from.sin_addr.s_addr);
        else if (bytes_readed == 0)
        {
            break; //   nothing
        }
        else
        {
            int error = mtk::socket_get_last_error(handle_socket);
            if (error == EAGAIN  ||  error == MTK_EWOULDBLOCK  ||  error==0)
                break;  // esperar al próximo intento
            else
            {
                close(MTK_SS(strerror(error) << handle_socket));
                throw mtk::Alarm(MTK_HERE, MTK_SS(name << "  bytes readed " << bytes_readed << "  " << strerror(error)  << " code: " << error << " socket: " << handle_socket), mtk::alPriorError);
            }
        }
    }

}





bool udp_socket::get_socket_error(void)
{
	#if (MTK_PLATFORM == MTK_WIN_PLATFORM)

		int valopt;
		int lon   = sizeof(int); 
		if (getsockopt(handle_socket, SOL_SOCKET, SO_ERROR, (char*)(&valopt), &lon) < 0)
			return true;
		else return false;

	#elif MTK_PLATFORM == MTK_LINUX_PLATFORM

		int valopt;
		socklen_t lon   = sizeof(int); 
		if (getsockopt(handle_socket, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon) < 0)
			return true;
		else return false;

	#endif
}


void  udp_socket::configure_socket()
{
	#if (MTK_PLATFORM == MTK_WIN_PLATFORM)

		unsigned long val = 1;
		if (ioctlsocket( handle_socket, FIONBIO, &val ) != 0)
		{
			get_socket_error();
			throw mtk::Alarm(MTK_HERE, MTK_SS(name << "  Error configuring non blocking socket " << strerror(errno)), mtk::alPriorError);
		}
	#elif MTK_PLATFORM == MTK_LINUX_PLATFORM

		if ( fcntl(handle_socket, F_SETFL, O_NONBLOCK) != 0)
			throw mtk::Alarm(MTK_HERE, MTK_SS(name << "  Error configuring non blocking socket"), mtk::alPriorError);

	#endif
}


void udp_socket::bind(int port)
{
    struct sockaddr_in server;
	memset(&server, 0, sizeof(sockaddr_in));
    server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port= in_port_t(MTK_HTONS(port));

    if (::bind(handle_socket,(struct sockaddr *)&server, sizeof(server))<0) 
       throw mtk::Alarm(MTK_HERE, MTK_SS(name << "Could not bind socket on port "  << port), mtk::alPriorError);

	binded_port = port;
	signal_connect.emit();
}


void udp_socket::send_to    (const sockaddr* destination, const char*data, size_t bytes)
{
    if (bytes == 0)
        throw mtk::Alarm(MTK_HERE, MTK_SS(name << "  sent_to 0 bytes"), mtk::alPriorError);
    if (bytes > 2000)
        throw mtk::Alarm(MTK_HERE, MTK_SS(name << "  too big packet " << bytes), mtk::alPriorCritic);

    ssize_t number_of_bytes_transferred = ::sendto(handle_socket, data, bytes, 0, destination, sizeof(struct sockaddr_in));
    if (number_of_bytes_transferred == 0)        //  se cortó la conexión en el otro lado
        throw mtk::Alarm(MTK_HERE, MTK_SS(name << "  0 bytes sent from " << bytes), mtk::alPriorCritic);
}


void udp_socket::send_to    (unsigned long address, const char*data, size_t bytes)
{
	if (binded_port == 0)
		throw mtk::Alarm(MTK_HERE, MTK_SS(name << "  send_to without port and not binded port"), mtk::alPriorError);
		
	send_to    (address, binded_port, data, bytes);
}


void udp_socket::send_to    (unsigned long address, unsigned int port, const char*data, size_t bytes)
{
	static unsigned long last_address=0;
    static unsigned int  last_port=0;
    static struct sockaddr_in dest_sockaddr_in;  
	
	if (last_address != address  ||  last_port != port)
	{
		memset(&dest_sockaddr_in, 0, sizeof(sockaddr_in));
		dest_sockaddr_in.sin_addr.s_addr=in_addr_t(address);
		dest_sockaddr_in.sin_family=AF_INET;
        dest_sockaddr_in.sin_port= in_port_t(MTK_HTONS(port));
	}


    send_to((struct sockaddr*)&dest_sockaddr_in, data, bytes);
}


void udp_socket::join_multicast (const std::string& multicast_address, const std::string& source_address)
{
    struct ip_mreq mreq;

    mreq.imr_multiaddr.s_addr = in_addr_t(mtk::socket_resolv_url(multicast_address));
    if (source_address == "")
        mreq.imr_interface.s_addr = INADDR_ANY;
    else
        mreq.imr_interface.s_addr = in_addr_t(mtk::socket_resolv_url(source_address.c_str()));
    if (setsockopt(handle_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq)) == MTK_SOCKET_ERROR)
		throw mtk::Alarm(MTK_HERE, MTK_SS(name << "  joining multicast " << multicast_address), mtk::alPriorCritic);
}



};      //  namespace mtk

