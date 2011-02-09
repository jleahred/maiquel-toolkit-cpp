#include "socket_support.h"

#include "support/platform.hpp"
#include "impl_socket_support.h"


#include <string.h>







namespace mtk
{

long unsigned  socket_resolv_url    (const  std::string& url)
{
    unsigned long                result=0;
	static std::string last_url="<none>";
    static struct sockaddr_in dest_sockaddr_in;

	if (last_url != url)
	{
		struct hostent* pdest_info=0;
		memset(&dest_sockaddr_in, 0, sizeof(sockaddr_in));
		pdest_info = gethostbyname(url.c_str());
		memcpy(&result,pdest_info->h_addr,pdest_info->h_length);
	}
    return result;
}



std::string    socket_address2string (long unsigned  address)
{
    in_addr _address;
    _address.s_addr = in_addr_t(address);

    return std::string(inet_ntoa(_address));
}


};      //  namespace mtk

