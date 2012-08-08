#ifndef __r_response_h__
#define __r_response_h__

#include "support/basic_types.hpp"
#include "components/msg_common.h"
#include "components/admin/msg_admin.h"
#include "components/admin/admin.h"
#include "support/call_later.h"


namespace mtk
{




#define MTK_SEND_MULTI_RESPONSE(__MSG_RESPONSE__, __SUB_MSG_DATA__, __URL__, __REQUEST_INFO__, __DATA_LIST__)  \
            {           \
                        new mtk::__kamikaze_r_response< __MSG_RESPONSE__, __SUB_MSG_DATA__>           \
                                            (  __DATA_LIST__, __REQUEST_INFO__, __URL__);           \
            }



#define MTK_RECEIVE_MULTI_RESPONSE_F(__MSG_RESPONSE__, __SUB_MSG_DATA__, __QPID_URL__ , __SUBJECT__, __METHOD_CALL__, __REQ_CONTEXT_INFO__)  \
                {   \
                    mtk::__kamikaze_receive_r<__MSG_RESPONSE__>* kamikaze_response =     \
                            new mtk::__kamikaze_receive_r<__MSG_RESPONSE__>     \
                            ( __QPID_URL__, __SUBJECT__, __REQ_CONTEXT_INFO__);     \
                    kamikaze_response->signal_received.connect(__METHOD_CALL__);  \
                }

#define MTK_RECEIVE_MULTI_RESPONSE_THIS(__MSG_RESPONSE__, __SUB_MSG_DATA__, __QPID_URL__, __SUBJECT__, __METHOD_CALL__, __REQ_CONTEXT_INFO__)  \
                {   \
                    mtk::__kamikaze_receive_r<__MSG_RESPONSE__>* kamikaze_response =     \
                            new mtk::__kamikaze_receive_r<__MSG_RESPONSE__>     \
                            ( __QPID_URL__, __SUBJECT__, __REQ_CONTEXT_INFO__);     \
                    kamikaze_response->signal_received.connect(this, &std::remove_reference<decltype(*this)>::type::__METHOD_CALL__);  \
                }



template<typename T>
void  delete_later_kamikaze(T* const &  ptr);



//--------------------------------------------------------------------------------------------------
//      IMPLEMENTATION
//--------------------------------------------------------------------------------------------------

template<typename MSG_T, typename DATA_T>
class __kamikaze_r_response   :   public  mtk::SignalReceptor  {
    mtk::non_copyable  nc;

public:
	__kamikaze_r_response(     typename mtk::list< DATA_T >&   data,
                    const mtk::msg::sub_request_info& ri,
                    const mtk::t_qpid_url&     _url,
                    const mtk::dtTimeQuantity tq=mtk::dtMilliseconds(200),
                    int _msg_per_tick=3)

            :       list(data),
                    req_info(ri),
                    sender(mtk::create_instance_for_factory<mtkqpid_sender2>(mtk::make_tuple(_url, MSG_T::static_get_qpid_address()))),
                    time_quantity(tq),
                    msg_per_tick(_msg_per_tick), counter(-1)
            {
                if(list.size() > 2000)
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "req_response", MTK_SS("too many responses  " << list.size()), mtk::alPriorError));

                MTK_TIMER_1D(send_async)
                //send_async();
            }


	~__kamikaze_r_response() { }


private:

    typename mtk::list< DATA_T >            list;

    const mtk::msg::sub_request_info        req_info;
    mtk::CountPtr< mtk::mtkqpid_sender2 >   sender;
    const mtk::dtTimeQuantity               time_quantity;
    int                                     msg_per_tick;
    int                                     counter;


    void send_async(void) {

        for(int i=0; i< msg_per_tick; ++i)
        {
            if(list.size()==0)      break;
            DATA_T d = list.front();
            list.pop_front();
            mtk::send_message_with_sender(  sender,
                                MSG_T(  mtk::msg::sub_r_response(mtk::admin::get_process_info(), req_info, int16_t(++counter), list.size()==0), d));

        }

        //if(list.size()==0)    delete this;        //  this is valid
        if(list.size()==0)
        {
            MTK_TIMER_1D_STOP(send_async);
            delete_later_kamikaze(this);
        }
    }


};







template<typename MSG_T>
class __kamikaze_receive_r   :   public  mtk::SignalReceptor  {
    mtk::non_copyable  nc;

public:
	__kamikaze_receive_r(       const mtk::t_qpid_url&      _url,
                                mtk::t_qpid_filter          in_subject,
                                const std::string           _req_context_info)
                    : programed_to_delete(false), last_received(mtk::dtNowLocal()+mtk::dtSeconds(30)), expected_secuence(-1),  req_context_info(_req_context_info)
            {
                MTK_QPID_RECEIVER_CONNECT_THIS(
                                        hqpid_response,
                                        _url,
                                        in_subject,
                                        MSG_T,
                                        on_command_response)
                MTK_TIMER_1S(check_timeout)
            }

    typename mtk::Signal< const mtk::list<MSG_T>& >    signal_received;


	~__kamikaze_receive_r() { }

private:



    typename mtk::list< MSG_T >                                                 list_received;
    typename mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<MSG_T>      >  hqpid_response;
    bool                                                                        programed_to_delete;
    mtk::dtDateTime                                                             last_received;
    int                                                                         expected_secuence;
    const std::string                                                           req_context_info;


    void on_command_response(const MSG_T& response)
    {
        if(programed_to_delete)     return;
        last_received = mtk::dtNowLocal();


        if(++expected_secuence != response.response_info.seq_number)
        {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "req_response",
                                MTK_SS("invalid secuence expected/received  " << expected_secuence << "/" << response.response_info.seq_number
                                    << " canceled response"), mtk::alPriorError));
                delete_later_kamikaze(this);
                programed_to_delete = true;
                expected_secuence = -100;
                return;
        }

        list_received.push_back(response);

        if(response.response_info.is_last_response  &&  programed_to_delete==false)
        {
            signal_received.emit(list_received);
            delete_later_kamikaze(this);
            programed_to_delete = true;
            //delete this;      //  it is also valid and program doesn't crash but there are memory leaks reported by valgrind
        }
    }

    void check_timeout(void)
    {
        if(mtk::dtNowLocal() -  last_received  > mtk::dtSeconds(20)    &&  programed_to_delete==false)
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "req_response", MTK_SS("time out on request " << req_context_info), mtk::alPriorError, mtk::alTypeOverflow));
            MTK_TIMER_1S_STOP(check_timeout)
            delete_later_kamikaze(this);
            programed_to_delete = true;
        }
    }

};







template<typename T>
mtk::list<mtk::tuple<mtk::dtDateTime, T* > >&  get_list_to_delete_kamikaze(void)
{
    static  auto  result = new mtk::list<mtk::tuple<mtk::dtDateTime, T* > >{};
    return  *result;
}


template<typename T>
void  check_to_delete_kamikaze (void)
{
    auto& list_to_delete = get_list_to_delete_kamikaze<T>();

    if(list_to_delete.size()  ==  0)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(30))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_to_delete kamikaze", MTK_SS("Called with empty list"), mtk::alPriorError));
        MTK_END_EXEC_MAX_FREC
        return;
    }


    auto it= list_to_delete.begin();
    while(it != list_to_delete.end())
    {
        mtk::tuple<mtk::dtDateTime, T* >&  item = *it;
        if(item._0 + mtk::dtMilliseconds(500)  < mtk::dtNowLocal())
        {
            delete it->_1;
            it->_1 = 0;
            it = list_to_delete.erase(it);
        }
        else
            ++it;
    }
    if(list_to_delete.size() == 0)
        MTK_TIMER_1SF_STOP(check_to_delete_kamikaze<T>);
}


template<typename T>
void  delete_later_kamikaze(T* const &  ptr)
{
    auto& list_to_delete = get_list_to_delete_kamikaze<T>();
    list_to_delete.push_back(mtk::make_tuple(mtk::dtNowLocal(),ptr));

    if(list_to_delete.size() == 1)
        MTK_TIMER_1SF(check_to_delete_kamikaze<T>);
}


}

#endif // __r_response_h__
