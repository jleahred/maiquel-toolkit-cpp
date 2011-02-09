#ifndef __tcp_pstringseparator___
#define __tcp_pstringseparator___

#include "sockets/tcp_base_socket.h"


namespace mtk
{


template<typename PARENT>
class tcp_pstringseparator : public PARENT
{
	mtk::non_copyable non_copy;

public:
	tcp_pstringseparator(const std::string& _name, const std::string& _separator) : PARENT(_name), separator(_separator) {}
	virtual ~tcp_pstringseparator() {};


    void write (const std::string& manda);

    mtk::Signal<const std::string&>  signal_received_string;

    std::string get_separator(void) const { return separator; }

private:
    std::string     separator;
    std::string     buffer_received;

    void on_received_bytes(const char* data, ssize_t size);		//	sobreescribimos

};








//      I M P L E M E N T A T I O N



template<typename PARENT>
void tcp_pstringseparator<PARENT>::on_received_bytes(const char* data, ssize_t size)
{
    for (int i=0; i<size; ++i)
    {
        buffer_received.push_back(data[i]);
        if (buffer_received.size() >= separator.size())
        {
            bool found = true;
            for (unsigned j=0; j < separator.size(); ++j)
            {
                if (buffer_received[buffer_received.size() - separator.size() + j] != separator[j])
                {
                    found = false;
                    break;
                }
            }
            if (found)
            {
                signal_received_string.emit(buffer_received);
                buffer_received.clear();
            }
        }
    }
}



template<typename PARENT>
void tcp_pstringseparator<PARENT>::write (const std::string& manda)
{
    if (manda.length()>0)
        PARENT::__write(manda.c_str(), int(manda.length()));
    PARENT::__write(separator.c_str(), int(separator.size()));
}




};  //         namespace mtk


#endif // __tcp_pstringseparator__
