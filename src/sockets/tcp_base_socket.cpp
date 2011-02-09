#include "tcp_base_socket.h"

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



tcp_base_socket::tcp_base_socket(const std::string& _name)
    : 
          handle_socket(-1)
        , name(_name)
        , pbuffer (new char [TCP_SOCKET_BUFFER_SIZE])
{
	start_timer();
	
    #if (MTK_PLATFORM == MTK_WIN_PLATFORM)
        //WORD wVersionRequested;
        //WSADATA wsaData;
        //int err;
        //wVersionRequested = MAKEWORD(2, 2);
        //err = WSAStartup(wVersionRequested, &wsaData);   pendiente de revisión gestión errores
    #endif
}

tcp_base_socket::~tcp_base_socket()
{
    try
    {
        delete[] pbuffer;
        close("~tcp_base_socket");
    }
    MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, MTK_HERE, MTK_SS(name << "  closing socket"));    
}


void  tcp_base_socket::start_timer(void)
{
    MTK_TIMER_1C(check_input)
    MTK_TIMER_1C(check_fast_producer_queue)
}


int     tcp_base_socket::get_buffer_size (void) const
{
    return TCP_SOCKET_BUFFER_SIZE;
}



void tcp_base_socket::close(const std::string& reason)
{
	if (handle_socket == -1)
		return;
		
    if (mtk::socket_close(handle_socket) == MTK_SOCKET_ERROR)
    {
        int error = mtk::socket_get_last_error(handle_socket);
        handle_socket = -1;
        throw mtk::Alarm(MTK_HERE, MTK_SS(name << "  Error closing socket " <<  strerror(error) << " " << error), mtk::alPriorError);
    }
    else
    {
        handle_socket = -1;
        signal_disconnect.emit(reason);
    }
}


void tcp_base_socket::__write(const char* data, size_t bytes)
{
    if (handle_socket<=0)   
        throw mtk::Alarm(MTK_HERE, MTK_SS(name << "  __write on not initialized/conected socket"), mtk::alPriorError);
    

    if (fast_producer_queue.size()>0)
    {
        //	guardamos todo
        insert_fast_producer(data, bytes);
        check_fast_producer_queue();
        return;
    }
    
    if (bytes > size_t(get_buffer_size()))
    {
        //	guardamos todo
        insert_fast_producer(data, bytes);
        check_fast_producer_queue();
        return;
    }


    ssize_t number_of_bytes_transferred = ::send(handle_socket, data, bytes, 0);
    if (number_of_bytes_transferred == MTK_SOCKET_ERROR)
    {
        int error = socket_get_last_error(handle_socket);
        if (error == EAGAIN  ||  error == MTK_EWOULDBLOCK)
            insert_fast_producer(data, bytes);
        else
        {
            close(MTK_SS(strerror(error) << handle_socket));
            throw mtk::Alarm(MTK_HERE, MTK_SS(name << " __write error " << strerror(error) << handle_socket), mtk::alPriorError);
        }
    }
    else
    {
        if(number_of_bytes_transferred<int(bytes))
        {
            int error = socket_get_last_error(handle_socket);
            if (error == EAGAIN)
            {
                //	guardamos lo que no se pudo enviar
                insert_fast_producer(data+number_of_bytes_transferred, bytes-number_of_bytes_transferred);
            }
            else
            {
                throw mtk::Alarm(MTK_HERE, MTK_SS(name << "  Error sending bytes, partial send with not EAGAIN error  sent " << number_of_bytes_transferred << " of " << bytes << "   with error " << strerror(error) << " code: " << error << "   EAGAIN code is" << EAGAIN), mtk::alPriorError);
            }
        }

    }
    
}




void tcp_base_socket::check_input(void)
{
	if (handle_socket<=0)   
		return;		//	todavía no hay nada que chequear
        
    while(true)
    {
        ssize_t bytes_readed=recv(handle_socket, pbuffer, mtk::tcp_base_socket::get_buffer_size(), 0);
        if (bytes_readed>0)
            on_received_bytes(pbuffer, int(bytes_readed));
        else if (bytes_readed == 0)     //  conexión cerrada
        {
            close(MTK_SS(" connection down " << name << " " << handle_socket));
            throw mtk::Alarm(MTK_HERE, MTK_SS(name << " Connection down  bytes readed " << bytes_readed << "  " <<  "  socket: " << handle_socket), mtk::alPriorError);
        }
        else    //  sólo puede ser == -1   IDIDMTK_ET_ERROR
        {
            int error = mtk::socket_get_last_error(handle_socket); 
            if (error == EAGAIN  ||  error == 0/*error == MTK_EWOULDBLOCK*/)
                break;  // esperar al próximo intento
            else
            {
                close(MTK_SS(strerror(error) << handle_socket));
                throw mtk::Alarm(MTK_HERE, MTK_SS(name << "  bytes readed " << bytes_readed << "  " << strerror(error) << " " << error << "  socket: " << handle_socket), mtk::alPriorError);
            }
        }
    }

}


void tcp_base_socket::check_fast_producer_queue(void)
{
    if (fast_producer_queue.size()==0)
            return;
	if (since_fast_producer_queue.HasValue()==false)
		return;
		
	MTK_EXEC_MAX_FREC(mtk::dtSeconds(6))
	
		if(mtk::dtNowLocal() - since_fast_producer_queue.Get()  > mtk::dtMilliseconds(700))
		{
			mtk::AlarmMsg(mtk::Alarm(MTK_HERE, 
								MTK_SS(name << "  fast producer since " << mtk::dtNowLocal() - since_fast_producer_queue.Get()), 
								mtk::alPriorError));
		}
		
	MTK_END_EXEC_MAX_FREC
	
    
    if (int(fast_producer_queue.size()) < get_buffer_size())
    {
        std::string temp_fast_producer_queue = fast_producer_queue;
        fast_producer_queue.clear();
        since_fast_producer_queue = mtk::nullable<mtk::DateTime>();
        __write(temp_fast_producer_queue.c_str(), temp_fast_producer_queue.size());
    }
    else
    {
        std::string temp_fast_producer_queue = fast_producer_queue;
        fast_producer_queue.clear();
        since_fast_producer_queue = mtk::nullable<mtk::DateTime>();
        while (temp_fast_producer_queue.size()!=0)
        {
            std::string to_write = temp_fast_producer_queue.substr(0, get_buffer_size());
            temp_fast_producer_queue.erase(0, get_buffer_size());
            __write(to_write.c_str(), to_write.size());
            if (fast_producer_queue.size()!=0)
                break;
        }
        fast_producer_queue += temp_fast_producer_queue;
        since_fast_producer_queue = mtk::make_nullable(mtk::dtNowLocal());
    }
}

void tcp_base_socket::insert_fast_producer(const char*data, size_t bytes)
{
    if (since_fast_producer_queue.HasValue()==false)
        since_fast_producer_queue = mtk::make_nullable(mtk::dtNowLocal());
    for (size_t i=0; i<bytes; ++i)
        fast_producer_queue.push_back(data[i]);
        
	MTK_EXEC_MAX_FREC(mtk::dtSeconds(10))
		if(fast_producer_queue.size() > 15000)
			mtk::AlarmMsg(mtk::Alarm(MTK_HERE, 
								MTK_SS(name << "  too big fast producer queue  size " << fast_producer_queue.size()), 
								mtk::alPriorError));
	MTK_END_EXEC_MAX_FREC
        
}




};      //  namespace mtk

