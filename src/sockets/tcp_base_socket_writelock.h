#ifndef __tcp_base_socket_writelock__
#define __tcp_base_socket_writelock__


#include "support/platform.hpp"
#if (MTK_PLATFORM == MTK_LINUX_PLATFORM)       //      sólo linux



#include "support/signalslot.hpp"
#include "support/list.hpp"
#include "support/nullable.hpp"



namespace mtk {
    
    


class tcp_base_socket_writelock : public mtk::SignalReceptor
{
	mtk::non_copyable non_copy;
	

public:
	tcp_base_socket_writelock(const std::string& name);
	virtual ~tcp_base_socket_writelock();

    mtk::Signal<>           				signal_connect;
    mtk::Signal<const std::string&>			signal_disconnect;

	mtk::Signal<mtk::dtTimeQuantity>        signal_slow_write;

protected:

    //      interfaz para las clases hijas
    //      se podría poner por herencia, creando una clase abstracta adicional
    void    close           (const std::string& reason);
    void    __write         (const char*data, size_t bytes);
    int     get_buffer_size (void) const;

	virtual void on_received_bytes(const char*, ssize_t)=0;


    int                     handle_socket;
    const std::string       name;
    char*                   pbuffer;
    //      interfaz para las clases hijas


private:
    void  check_input(void); // llamar frecuentemente
    void  start_timer(void);
	
};



};      //  namespace mtk


#endif // sólo linux


#endif // __tcp_base_socket_writelock__
