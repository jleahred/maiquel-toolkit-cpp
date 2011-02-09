#ifndef __tcp_base_socket__
#define __tcp_base_socket__

#include "support/signalslot.hpp"
#include "support/list.hpp"
#include "support/nullable.hpp"



namespace mtk {
    
    


class tcp_base_socket : public mtk::SignalReceptor
{
    typedef     tcp_base_socket  CLASS_NAME;
	mtk::non_copyable non_copy;
	

public:
	tcp_base_socket(const std::string& _name);
	virtual ~tcp_base_socket();

    mtk::Signal<>           				signal_connect;
    mtk::Signal<const std::string&>			signal_disconnect;

	mtk::Signal<mtk::dtTimeQuantity>        signal_fastproducer_slowreceptor;	//	fast writer, slow reader or slow network

protected:

    //      interfaz para las clases hijas
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
	
	//	control of fastproducer slow receptor
	std::string  					fast_producer_queue;
	mtk::nullable<mtk::DateTime>    since_fast_producer_queue;
	void 							check_fast_producer_queue(void);	//	revisa y reenvía
    void                            insert_fast_producer(const char*data, size_t bytes);

};



};      //  namespace mtk


#endif // __tcp_base_socket__
