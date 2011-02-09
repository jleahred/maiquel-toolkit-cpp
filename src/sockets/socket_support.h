#ifndef __socket_support__
#define __socket_support__


#include <string>




namespace mtk {



    long unsigned  socket_resolv_url     (const  std::string& url);
    //  to convert without resolving an ip address from format "xxx.xxx.xxx.xxx"
    //  use...  inet_addr(string_address.c_str());

    std::string    socket_address2string (long unsigned  address);



};      //  namespace mtk


#endif // __socket_support__
