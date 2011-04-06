#include "impl_socket_support.h"

#include "support/platform.hpp"
#include "support/alarm.h"
#include "support/mtk_string.h"


#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>



namespace mtk {



int socket_get_last_error(int handle_socket)
{
    int valopt=0;
    socklen_t lon   = sizeof(int); 
	#if (MTK_PLATFORM == MTK_WIN_PLATFORM)
        getsockopt(handle_socket, SOL_SOCKET, SO_ERROR, (char FAR*)(&valopt), &lon);
	#elif MTK_PLATFORM == MTK_LINUX_PLATFORM
        getsockopt(handle_socket, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon);
	#endif
    return valopt;
}


void  socket_configure_nonblocking(int handle_socket, const std::string& socket_name)
{
	#if (MTK_PLATFORM == MTK_WIN_PLATFORM)

		unsigned long val = 1;
		if (ioctlsocket( handle_socket, FIONBIO, &val ) != 0)
		{
            int error = mtk::socket_get_last_error(handle_socket);
			throw mtk::Alarm(MTK_HERE, "sockect", MTK_SS(socket_name << "  Error configuring non blocking socket " << strerror(error)), mtk::alPriorError);
		}
	#elif MTK_PLATFORM == MTK_LINUX_PLATFORM

		if ( fcntl(handle_socket, F_SETFL, O_NONBLOCK) != 0)
        {
            int error = mtk::socket_get_last_error(handle_socket);
	    throw mtk::Alarm(MTK_HERE, "sockect",  MTK_SS(socket_name << "  Error configuring non blocking socket" <<  strerror(error)), mtk::alPriorError);
        }

	#endif
}


int     socket_close                (int handle_socket)
{
	#if (MTK_PLATFORM == MTK_WIN_PLATFORM)

		return ::closesocket(handle_socket);

	#elif MTK_PLATFORM == MTK_LINUX_PLATFORM

		return ::close(handle_socket) == MTK_SOCKET_ERROR;
            
    #endif
    
}



};      //  namespace mtk

