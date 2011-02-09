#ifndef __tcp_p2bytes_size___
#define __tcp_p2bytes_size___

#include "sockets/tcp_base_socket.h"
#include "support/mtk_string.h"


namespace mtk
{

    
template<typename PARENT>
class tcp_p2bytes_size : public PARENT
{
	mtk::non_copyable non_copy;

public:
	tcp_p2bytes_size(const std::string& _name, bool _big_endian=true) 
                : PARENT(_name)
                , big_endian (_big_endian)
                , posInSizeMessage(-1)
                , posInMessage(-1) 
                , sizeCurrentMessage(-1) 
                {}
	virtual ~tcp_p2bytes_size() {};


    void write (const char* data, int n_bytes);
    
    mtk::Signal<const char*/*data*/, int/*size*/>  signal_received;
    

private:
    static const int BUFFER_SIZE = 65536;
    char buffer_message[BUFFER_SIZE];

    void on_received_bytes(const char* data, ssize_t);		//	sobreescribimos


    const bool  big_endian;
    int         posInSizeMessage;
    int         posInMessage;
    int         sizeCurrentMessage;
};








//      I M P L E M E N T A T I O N



template<typename PARENT>
void tcp_p2bytes_size<PARENT>::on_received_bytes(const char* data, ssize_t size)
{
    //  Qué fácil y seguro sería esto en erlang
    for (int i=0; i<size; ++i)
    {
        if(posInSizeMessage==-1)
        {
            //  next byte is first size byte
            if (big_endian)
                sizeCurrentMessage = 256* (unsigned char)(data[i]);
            else
                sizeCurrentMessage = (unsigned char)(data[i]);
            posInSizeMessage += 1;
        }
        else if(posInSizeMessage==0)
        {
            //  next byte is second size byte
            if (big_endian)
                sizeCurrentMessage += (unsigned char)(data[i]);
            else
                sizeCurrentMessage += 256* (unsigned char)(data[i]);
            posInSizeMessage += 1;
            posInMessage = 0;
        }
        else
        {
            if (posInMessage < BUFFER_SIZE)
                buffer_message[posInMessage] = data[i];
            ++posInMessage;
        }
        
        
        if (posInMessage >= BUFFER_SIZE)
        {
            int tempPosInMessage = posInMessage;
            posInMessage=-1;
            sizeCurrentMessage=-1;
            posInSizeMessage = -1;
            throw mtk::Alarm(MTK_HERE, MTK_SS("message received too long >" << tempPosInMessage << " . Ignoring it"), 
                                                        mtk::alPriorCritic, mtk::alTypeOverflow);
        }

        if (posInMessage == sizeCurrentMessage  &&  posInMessage>0  &&  sizeCurrentMessage >0)
        {
            //  tenemos mensaje completo, mandar
            int tempPosInMessage = posInMessage;
            posInMessage=-1;
            sizeCurrentMessage=-1;
            posInSizeMessage = -1;

            signal_received.emit(buffer_message, tempPosInMessage);
        }
    }
}



template<typename PARENT>
void tcp_p2bytes_size<PARENT>::write (const char* data, int n_bytes)
{
    short ssize = 0;
    if (big_endian)
        ssize = short((n_bytes % 256) *256 + n_bytes /256);    //  como la arquitectura es little endian, hay que darle la vuelta
    else
        ssize = short(n_bytes);
    PARENT::__write((const char*)(&ssize), 2);
    PARENT::__write(data, n_bytes);
}




};  //         namespace mtk


#endif // __tcp_p2bytes_size__
