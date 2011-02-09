#ifndef __tcp_client__
#define __tcp_client__


#include "support/alarm.h"
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
class tcp_client : public LOW_SOCKET
{
	mtk::non_copyable non_copy;
    static const int  MTK_SOCKET_ERROR         = -1;

public:
	tcp_client(const std::string& _name) : LOW_SOCKET(_name) {};
	virtual ~tcp_client(){};


    void  connect    (const std::string& _dest_name, short unsigned int port);


private:
    long                dest_address;
    std::string         dest_name;
    short unsigned int  dest_port;


};







//      I M P L E M E N T A T I O N

template <typename LOW_SOCKET>
void tcp_client<LOW_SOCKET>::connect(const std::string& _dest_name, short unsigned int _dest_port)
{
	if (LOW_SOCKET::handle_socket > 0)
        throw mtk::Alarm(MTK_HERE, "socket", MTK_SS(LOW_SOCKET::name << "  The socket is already connected"), mtk::alPriorError);

    struct hostent* pdest_info=0;   /* holds info about a machine */
    struct sockaddr_in dest_sockaddr_in;  /* Internet socket address stuct */
	memset(&dest_sockaddr_in, 0, sizeof(sockaddr_in));

    dest_name = _dest_name;
    dest_port = _dest_port;


    // create socket
    LOW_SOCKET::handle_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if(LOW_SOCKET::handle_socket == MTK_SOCKET_ERROR)
        throw mtk::Alarm(MTK_HERE, "socket", MTK_SS(LOW_SOCKET::name << "Could not create a socket"), mtk::alPriorError);


    // get IP address from name
    pdest_info = gethostbyname(dest_name.c_str());

    // copy address into long
    memcpy(&dest_address,pdest_info->h_addr,pdest_info->h_length);

    // fill address struct
    dest_sockaddr_in.sin_addr.s_addr=in_addr_t(dest_address);
    dest_sockaddr_in.sin_port= in_port_t(MTK_HTONS(dest_port));
    dest_sockaddr_in.sin_family=AF_INET;


    // connect to host
    if(::connect(LOW_SOCKET::handle_socket,(struct sockaddr*)&dest_sockaddr_in,sizeof(dest_sockaddr_in))
                    == MTK_SOCKET_ERROR)
        throw mtk::Alarm(MTK_HERE, "socket", MTK_SS(LOW_SOCKET::name << "  Could not connect a socket"), mtk::alPriorError);

    mtk::socket_configure_nonblocking(LOW_SOCKET::handle_socket, LOW_SOCKET::name);
    LOW_SOCKET::signal_connect.emit();
}



};      //  namespace mtk





#endif // __tcp_client__
