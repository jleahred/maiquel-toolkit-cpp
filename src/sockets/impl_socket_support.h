#ifndef __impl_socket_support__
#define __impl_socket_support__


/*  This file is to include on cpp, not on .h
 */


#include "support/platform.hpp"
#include <string>


#if (MTK_PLATFORM == MTK_WIN_PLATFORM)

	//#include <winsock.h>
    #define WIN32_LEAN_AND_MEAN
	#include <winsock2.h>    // lib:  ws2_32
	#include <Ws2tcpip.h>
	
	#define MTK_EWOULDBLOCK  WSAEWOULDBLOCK
	typedef int             socklen_t;
	typedef unsigned short  in_port_t;
	typedef unsigned long   in_addr_t;

#elif MTK_PLATFORM == MTK_LINUX_PLATFORM

	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
    #include <arpa/inet.h>

	#define MTK_EWOULDBLOCK  EWOULDBLOCK

#endif



//#if __BYTE_ORDER == __LITTLE_ENDIAN
    #define MTK_HTONS(A) ((((uint16_t)(A) & 0xff00) >> 8) | \
                (((uint16_t)(A) & 0x00ff) << 8))    
//#endif

namespace {
    const int  MTK_SOCKET_ERROR         = -1;
};


namespace mtk {

    
    int     socket_get_last_error       (int handle_socket);
    void    socket_configure_nonblocking(int handle_socket, const std::string& socket_name);
    int     socket_close                (int handle_socket);
    
    



};      //  namespace mtk


#endif // __impl_socket_support__
