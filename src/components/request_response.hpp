#ifndef __r_response_h__
#define __r_response_h__

#include "support/basic_types.hpp"
#include "components/msg_common.h"
#include "components/admin/msg_admin.h"
#include "components/admin/admin.h"
#include "support/call_later.h"


namespace mtk
{


    
    
#define MTK_SEND_MULTI_RESPONSE(__MSG_RESPONSE__, __SUB_MSG_DATA__, __QPID_SESSION__, __REQUEST_INFO__, __DATA_LIST__)  \
            {           \
                        new mtk::__kamikaze_r_response< __MSG_RESPONSE__, __SUB_MSG_DATA__>           \
                                            (  __DATA_LIST__, __REQUEST_INFO__, __QPID_SESSION__);           \
            }
    
    

#define MTK_RECEIVE_MULTI_RESPONSE_F(__MSG_RESPONSE__, __SUB_MSG_DATA__, __QPID_SESSION__, __SUBJECT__, __METHOD_CALL__)  \
                {   \
                    mtk::__kamikaze_receive_r<__MSG_RESPONSE__>* kamikaze_response =     \
                            new mtk::__kamikaze_receive_r<__MSG_RESPONSE__>     \
                            ( __QPID_SESSION__, __SUBJECT__);     \
                    kamikaze_response->signal_received.connect(__METHOD_CALL__);  \
                }

#define MTK_RECEIVE_MULTI_RESPONSE_THIS(__MSG_RESPONSE__, __SUB_MSG_DATA__, __QPID_SESSION__, __SUBJECT__, __METHOD_CALL__)  \
                {   \
                    mtk::__kamikaze_receive_r<__MSG_RESPONSE__>* kamikaze_response =     \
                            new mtk::__kamikaze_receive_r<__MSG_RESPONSE__>     \
                            ( __QPID_SESSION__, __SUBJECT__);     \
                    kamikaze_response->signal_received.connect(this, &CLASS_NAME::__METHOD_CALL__);  \
                }

    
    
    
    
//--------------------------------------------------------------------------------------------------
//      IMPLEMENTATION
//--------------------------------------------------------------------------------------------------
    
template<typename MSG_T, typename DATA_T>    
class __kamikaze_r_response   :   public  mtk::SignalReceptor  {
    mtk::non_copyable  nc;
    typedef __kamikaze_r_response  CLASS_NAME;
    
public:
	__kamikaze_r_response(     typename mtk::list< DATA_T >&   data,
                    const mtk::msg::sub_request_info& ri, 
                    mtk::CountPtr< mtk::qpid_session >  _qpid_session, 
                    const mtk::dtTimeQuantity tq=mtk::dtMilliseconds(200), 
                    int _msg_per_tick=3)
                    
            :  list(data), req_info(ri), qpid_session(_qpid_session), time_quantity(tq), msg_per_tick(_msg_per_tick), counter(-1)
            { 
                if(list.size() > 2000)
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS("too many responses  " << list.size()), mtk::alPriorError));
                    
                MTK_TIMER_1D(send_async)
                //send_async(); 
            }
    

private:

	~__kamikaze_r_response() {}


    typename mtk::list< DATA_T >             list;
    
    const mtk::msg::sub_request_info    req_info;
    mtk::CountPtr< mtk::qpid_session >  qpid_session;
    const mtk::dtTimeQuantity           time_quantity;
    int                                 msg_per_tick;
    int                                 counter;


    void send_async(void) {
        
        for(int i=0; i< msg_per_tick; ++i)
        {
            if(list.size()==0)      break;
            DATA_T d = list.front();
            list.pop_front();
            mtk::send_message(  qpid_session, 
                                MSG_T(  mtk::msg::sub_r_response(req_info, int16_t(++counter), list.size()==0), d));
            
        }
        
        if(list.size()==0)      delete this;
    }


};





template<typename MSG_T>    
class __kamikaze_receive_r;

template<typename MSG_T>    
void delete_later(__kamikaze_receive_r<MSG_T>* const & ptr_to_delete)
{
    delete ptr_to_delete;
}


template<typename MSG_T>    
class __kamikaze_receive_r   :   public  mtk::SignalReceptor  {
    mtk::non_copyable  nc;
    typedef __kamikaze_receive_r  CLASS_NAME;
    friend void delete_later<MSG_T>(__kamikaze_receive_r<MSG_T>* const & ptr_to_delete);
    
public:
	__kamikaze_receive_r(mtk::CountPtr< mtk::qpid_session >  _qpid_session, const std::string in_subject)
                    : programed_to_delete(false), last_received(mtk::dtNowLocal()+mtk::dtSeconds(30)), espected_secuence(-1)
            { 
                MTK_QPID_RECEIVER_CONNECT_THIS(
                                        hqpid_response,
                                        _qpid_session->url,
                                        _qpid_session->address,
                                        in_subject,
                                        MSG_T,
                                        on_command_response)
                MTK_TIMER_1S(check_timeout)
            }

    typename mtk::Signal< const mtk::list<MSG_T>& >    signal_received;
    

private:

	~__kamikaze_receive_r() {}


    typename mtk::list< MSG_T >                                                 list_received;
    typename mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<MSG_T>      >  hqpid_response;
    bool                                                                        programed_to_delete;
    mtk::dtDateTime                                                             last_received;
    int                                                                         espected_secuence;


    void on_command_response(const MSG_T& response)
    {
        if(programed_to_delete)     return;
        last_received = mtk::dtNowLocal();
        
        
        if(++espected_secuence != response.response_info.sec_number)
        {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, 
                                MTK_SS("invalid secuence espected/received  " << espected_secuence << "/" << response.response_info.sec_number
                                    << " canceled response"), mtk::alPriorError));
                MTK_CALL_LATER1S_F(mtk::dtMilliseconds(10), this, delete_later);
                programed_to_delete = true;
                espected_secuence = -100;
                return;
        }

        list_received.push_back(response);

        if(response.response_info.is_last_response  &&  programed_to_delete==false)
        {
            signal_received.emit(list_received);
            MTK_CALL_LATER1S_F(mtk::dtMilliseconds(10), this, delete_later);
            programed_to_delete = true;
            //delete this;      //  it is also valid and program doesn't crash but there are memory leaks reported by valgrind
            //hqpid_response = mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<MSG_T>      >(); 
                //  this is also posible, but it will produce an alarm, it's a bad idea to destroy the objetc that is been executed by
                //  a signal
        }
    }
    
    void check_timeout(void)
    {
        if(mtk::dtNowLocal() -  last_received  > mtk::dtSeconds(20)    &&  programed_to_delete==false)
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS("time out on request "), mtk::alPriorError, mtk::alTypeOverflow));
            MTK_TIMER_1S_STOP(check_timeout)
            MTK_CALL_LATER1S_F(mtk::dtMilliseconds(10), this, delete_later);
            programed_to_delete = true;
        }
    }

};


}

#endif // __r_response_h__
