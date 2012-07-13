#ifndef __udp_socket__
#define __udp_socket__

#include "support/signalslot.hpp"
#include "support/list.hpp"
#include "support/nullable.hpp"

class sockaddr;
class sockaddr_in;





namespace mtk {

    



class udp_socket : public mtk::SignalReceptor
{
	mtk::non_copyable non_copy;
	

public:
	udp_socket(const std::string& _name);
	virtual ~udp_socket();

    
    mtk::Signal<const char*, ssize_t, long unsigned/*ip address source*/>    signal_packet_received;
    
    mtk::Signal<>           							signal_connect;         //  binded
    mtk::Signal<const std::string&>						signal_disconnect;
    
    
    void bind           (int port);
    void join_multicast (const std::string& multicast_address, const std::string& source_address);
    
    void close          (const std::string& reason);
    
    

    void send_to        (unsigned long destination , const char*data,                    size_t bytes);
    void send_to        (unsigned long destination , unsigned int port, const char*data, size_t bytes);



protected:

private:

    int                     handle_socket;
    const std::string       name;
    char*                   pbuffer;
	unsigned int 			binded_port;

    void send_to        (const sockaddr* destination    , const char*data,                    size_t bytes);

    void  check_input(void); // llamar frecuentemente
    void  start_timer(void);
	

    bool  get_socket_error(void);
    int   get_buffer_size (void) const;
	void  configure_socket(void);

};



};      //  namespace mtk


#endif // __udp_socket__
