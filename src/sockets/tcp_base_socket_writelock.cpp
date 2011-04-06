
#include "tcp_base_socket_writelock.h"

#if (MTK_PLATFORM == MTK_LINUX_PLATFORM)       //      sólo linux


#include "support/alarm.h"
#include "support/timer.h"
#include "support/mtk_string.h"




#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>


#include "impl_socket_support.h"


namespace {    
    const int  TCP_SOCKET_BUFFER_SIZE  =  65536;
};


namespace mtk {


tcp_base_socket_writelock::tcp_base_socket_writelock(const std::string& _name)
    : 
          handle_socket(-1)
        , name(_name)
        , pbuffer (new char [TCP_SOCKET_BUFFER_SIZE])
{
      start_timer();
}

tcp_base_socket_writelock::~tcp_base_socket_writelock()
{
    try
    {
        delete[] pbuffer;
        close("~tcp_base_socket_writelock");
    }
    MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, MTK_HERE, MTK_SS(name << "closing socket"));    
}


void  tcp_base_socket_writelock::start_timer(void)
{
    MTK_TIMER_1S(check_input)
}


int     tcp_base_socket_writelock::get_buffer_size (void) const
{
    return TCP_SOCKET_BUFFER_SIZE;
}



void tcp_base_socket_writelock::close(const std::string& reason)
{
	if (handle_socket == -1)
		return;
		
    if (mtk::socket_close(handle_socket) == MTK_SOCKET_ERROR)
    {
        int error = mtk::socket_get_last_error(handle_socket);
        handle_socket = -1;
        throw mtk::Alarm(MTK_HERE, "socket", MTK_SS(name << "  Error closing socket " <<  strerror(error) << " " << error), mtk::alPriorError);
    }
    else
    {
        handle_socket = -1;
        signal_disconnect.emit(reason);
    }
}


void tcp_base_socket_writelock::__write(const char* data, size_t bytes)
{
	if (handle_socket<=0)   
		throw mtk::Alarm(MTK_HERE, "socket", MTK_SS(name << "  __write on not initialized/conected socket"), mtk::alPriorError);
	

    mtk::DateTime  start = mtk::dtNowLocal();
    ssize_t result = ::write(handle_socket, data, bytes);
    mtk::dtTimeQuantity total_time = mtk::dtNowLocal() - start;
    
    if (total_time > mtk::dtMilliseconds(500))
        signal_slow_write(total_time);
    
    
	if (result == 0)
	{
		close("detected ordered disconection on write");
		throw mtk::Alarm(MTK_HERE, "socket", MTK_SS(name << "  __write disconnected socket"), mtk::alPriorError);
	}
	else if (result < 0)      //  sólo puede ser -1 error  o   0 si se ha cortado la conexión en el otro extremo
    {
        close(MTK_SS(strerror(errno) << handle_socket));
        throw mtk::Alarm(MTK_HERE, "socket", MTK_SS(name << "  "  << strerror(errno) << handle_socket), mtk::alPriorError);
    }
	else
	{
		if (size_t(result) != bytes)
        {
            close ("partial write");
			throw mtk::Alarm(MTK_HERE, "socket", MTK_SS(name << "  Error sending bytes, partial send???"), mtk::alPriorError);
        }
	}
}




void tcp_base_socket_writelock::check_input(void)
{

	if (handle_socket<=0)   
		return;		//	todavía no hay nada que chequear

#if (MTK_PLATFORM == MTK_WIN_PLATFORM)
#error pending  socket windows   recv  MSG_DONTWAIT
#endif
    ssize_t bytes_readed=recv(  handle_socket, 
                            pbuffer, 
                            mtk::tcp_base_socket_writelock::get_buffer_size(),
                            MSG_DONTWAIT
                            );
    if (bytes_readed>0)
    {
		on_received_bytes(pbuffer, bytes_readed);
    }
	else if (bytes_readed < 0)
	{
		if (errno == EAGAIN  ||  errno == MTK_EWOULDBLOCK)
			;  // esperar al próximo intento
		else
		{
            int error = mtk::socket_get_last_error(handle_socket);
            close(MTK_SS(strerror(error) << handle_socket));
            throw mtk::Alarm(MTK_HERE, "socket", MTK_SS(name <<  "reading error " << strerror(error) << handle_socket), mtk::alPriorError);
        }
	}
}





};      //  namespace mtk

#endif
