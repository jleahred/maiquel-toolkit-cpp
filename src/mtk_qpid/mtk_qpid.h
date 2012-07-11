/*
        Verificar el control de fluctuaciones

        se lee dos veces control fields

*/




//---------------------------------------------------------------------------

#ifndef __mtk_qpid__
#define __mtk_qpid__


#include <qpid/messaging/Connection.h>
#include <qpid/messaging/Message.h>
#include <qpid/messaging/Receiver.h>
#include <qpid/messaging/Sender.h>
#include <qpid/messaging/Session.h>
#include <qpid/messaging/Message.h>
#include "qpid/client/ConnectionSettings.h"


#include "support/basic_types.hpp"
#include "support/count_ptr.hpp"
#include "support/signalslot.hpp"
#include "support/alarm.h"
#include "support/exec_max_frec.h"
#include "support/mtk_string.h"
#include "support/misc.h"
#include "support/timer.h"
#include "support/factory.hpp"
#include "msg_control_fields.h"
#include "support/exec_max_frec.h"


#include "mtk_qpid_stats.h"



#define  __MTK_CHECK_NON_DEPRECIATED_THIS(__MSG_TYPE__)     \
        if(__internal_handler__->depreciated_on.HasValue() ==  true)    \
        {           \
            MTK_EXEC_MAX_FREC(mtk::dtMinutes(15))           \
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "depreciated", MTK_SS("previus depreciated register on " << #__MSG_TYPE__), mtk::alPriorError));           \
            MTK_END_EXEC_MAX_FREC           \
        }           \


#define  __MTK_CHECK_DEPRECIATED_THIS(__MSG_TYPE__, __DEPRECIATED_DATE__)     \
        if(__DEPRECIATED_DATE__ <  mtk::dtNowLocal())                  \
        {           \
            MTK_EXEC_MAX_FREC(mtk::dtMinutes(15))           \
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "depreciated"           \
                        , MTK_SS("depreciated register receptor " << #__MSG_TYPE__ << "  "  <<  __DEPRECIATED_DATE__)         \
                        , mtk::alPriorError));           \
            MTK_END_EXEC_MAX_FREC           \
        }           \
        if(__internal_handler__->depreciated_on.HasValue()   &&    __internal_handler__->depreciated_on.Get()!= (__DEPRECIATED_DATE__))                     \
        {           \
            MTK_EXEC_MAX_FREC(mtk::dtMinutes(15))           \
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "depreciated"           \
                        , MTK_SS("previus non depreciated register on " << #__MSG_TYPE__ << "  with diferent depreciated date  "  <<           \
                          __internal_handler__->depreciated_on.Get()  <<  " != "  <<  __DEPRECIATED_DATE__)           \
                        , mtk::alPriorError));           \
            MTK_END_EXEC_MAX_FREC           \
        }           \
        else           \
            __internal_handler__->depreciated_on = mtk::make_nullable((__DEPRECIATED_DATE__));           \


#define  __MTK_CHECK_NON_DEPRECIATED_F(__MSG_TYPE__)     \
        if(__internal_handler__->depreciated_on.HasValue() ==  true)    \
        {           \
            MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(15))           \
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "depreciated", MTK_SS("previus depreciated register on " << #__MSG_TYPE__), mtk::alPriorError));           \
            MTK_END_EXEC_MAX_FREC           \
        }           \


#define  __MTK_CHECK_DEPRECIATED_F(__MSG_TYPE__, __DEPRECIATED_DATE__)     \
        if(__DEPRECIATED_DATE__ <  mtk::dtNowLocal())                  \
        {           \
            MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(15))           \
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "depreciated"           \
                        , MTK_SS("depreciated register receptor " << #__MSG_TYPE__ << "  "  <<  __DEPRECIATED_DATE__)         \
                        , mtk::alPriorError));           \
            MTK_END_EXEC_MAX_FREC           \
        }           \
        if(__internal_handler__->depreciated_on.HasValue()   &&    __internal_handler__->depreciated_on.Get()!= (__DEPRECIATED_DATE__))                     \
        {           \
            MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(15))           \
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "depreciated"           \
                        , MTK_SS("previus non depreciated register on " << #__MSG_TYPE__ << "  with diferent depreciated date  "  <<           \
                          __internal_handler__->depreciated_on.Get()  <<  "  "  <<  __DEPRECIATED_DATE__)           \
                        , mtk::alPriorError));           \
            MTK_END_EXEC_MAX_FREC           \
        }           \
        else           \
            __internal_handler__->depreciated_on = mtk::make_nullable((__DEPRECIATED_DATE__));           \




//------------------------------------------------------------------------------------------------------------------------------------------


#define MTK_QPID_RECEIVER_CONNECT_F(__HANDLER__, __URL__, __FILTER__, __MSG_TYPE__, __FUNCT_RECEPTOR__)  \
    {    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > __internal_handler__ =      \
                                            mtk::get_from_factory<mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >(mtk::make_tuple(     __URL__, \
                                                                                                                                            mtk::t_qpid_address(__MSG_TYPE__::static_get_qpid_address()), \
                                                                                                                                            __FILTER__));     \
        __MTK_CHECK_NON_DEPRECIATED_F(__MSG_TYPE__)     \
        __internal_handler__->signalMessage->connect(__FUNCT_RECEPTOR__);     \
        (__HANDLER__) = __internal_handler__;     \
    }


#define MTK_QPID_RECEIVER_CONNECT_F__DEPRECIATED(__HANDLER__, __URL__, __FILTER__, __MSG_TYPE__, __FUNCT_RECEPTOR__, __DEPRECIATED_DATE__)  \
    {    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > __internal_handler__ =      \
                                            mtk::get_from_factory<mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >(mtk::make_tuple(     __URL__, \
                                                                                                                                            mtk::t_qpid_address(__MSG_TYPE__::static_get_qpid_address()), \
                                                                                                                                            __FILTER__));     \
        __MTK_CHECK_DEPRECIATED_F(__MSG_TYPE__,  __DEPRECIATED_DATE__)     \
        __internal_handler__->signalMessage->connect(__FUNCT_RECEPTOR__);     \
        (__HANDLER__) = __internal_handler__;     \
    }


//------------------------------------------------------------------------------------------------------------------------------------------



#define MTK_QPID_RECEIVER_CONNECT_THIS(__HANDLER__, __URL__, __FILTER__, __MSG_TYPE__, __FUNCT_RECEPTOR__)  \
    {    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > __internal_handler__ =      \
                                            mtk::get_from_factory<mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >(mtk::make_tuple(     __URL__, \
                                                                                                                                            mtk::t_qpid_address(__MSG_TYPE__::static_get_qpid_address()), \
                                                                                                                                            __FILTER__));     \
        __MTK_CHECK_NON_DEPRECIATED_THIS(__MSG_TYPE__)     \
        __internal_handler__->signalMessage->connect(this, &CLASS_NAME::__FUNCT_RECEPTOR__);     \
        (__HANDLER__) = __internal_handler__;     \
    }

#define MTK_QPID_RECEIVER_CONNECT_THIS__DEPRECIATED(__HANDLER__, __URL__, __FILTER__, __MSG_TYPE__, __FUNCT_RECEPTOR__)  \
    {    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > __internal_handler__ =      \
                                            mtk::get_from_factory<mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >(mtk::make_tuple(     __URL__, \
                                                                                                                                            mtk::t_qpid_address(__MSG_TYPE__::static_get_qpid_address()), \
                                                                                                                                            __FILTER__));     \
        __MTK_CHECK_DEPRECIATED_THIS(__MSG_TYPE__,  __DEPRECIATED_DATE__)     \
        __internal_handler__->signalMessage->connect(this, &CLASS_NAME::__FUNCT_RECEPTOR__);     \
        (__HANDLER__) = __internal_handler__;     \
    }


//------------------------------------------------------------------------------------------------------------------------------------------


#define MTK_QPID_RECEIVER_CONNECT_F__WITH_ADDRESS(__HANDLER__, __URL__, __ADDRESS__, __FILTER__, __MSG_TYPE__, __FUNCT_RECEPTOR__)  \
    {    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > __internal_handler__ =      \
                                            mtk::get_from_factory<mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >(mtk::make_tuple(__URL__, __ADDRESS__, __FILTER__));     \
        __internal_handler__->signalMessage->connect(__FUNCT_RECEPTOR__);     \
        __MTK_CHECK_NON_DEPRECIATED_F(__MSG_TYPE__)     \
        (__HANDLER__) = __internal_handler__;     \
    }


#define MTK_QPID_RECEIVER_CONNECT_F__WITH_ADDRESS__DEPRECIATED(__HANDLER__, __URL__, __ADDRESS__, __FILTER__, __MSG_TYPE__, __FUNCT_RECEPTOR__)  \
    {    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > __internal_handler__ =      \
                                            mtk::get_from_factory<mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >(mtk::make_tuple(__URL__, __ADDRESS__, __FILTER__));     \
        __MTK_CHECK_DEPRECIATED_F(__MSG_TYPE__,  __DEPRECIATED_DATE__)     \
        __internal_handler__->signalMessage->connect(__FUNCT_RECEPTOR__);     \
        (__HANDLER__) = __internal_handler__;     \
    }


//------------------------------------------------------------------------------------------------------------------------------------------


#define MTK_QPID_RECEIVER_CONNECT_THIS__WITH_ADDRESS(__HANDLER__, __URL__, __ADDRESS__, __FILTER__, __MSG_TYPE__, __FUNCT_RECEPTOR__)  \
    {    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > __internal_handler__ =      \
                                            mtk::get_from_factory<mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >(mtk::make_tuple(__URL__, __ADDRESS__, __FILTER__));     \
        __MTK_CHECK_NON_DEPRECIATED_THIS(__MSG_TYPE__)     \
        __internal_handler__->signalMessage->connect(this, &CLASS_NAME::__FUNCT_RECEPTOR__);     \
        (__HANDLER__) = __internal_handler__;     \
    }

#define MTK_QPID_RECEIVER_CONNECT_THIS__WITH_ADDRESS__DEPRECIATED(__HANDLER__, __URL__, __ADDRESS__, __FILTER__, __MSG_TYPE__, __FUNCT_RECEPTOR__)  \
    {    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > __internal_handler__ =      \
                                            mtk::get_from_factory<mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >(mtk::make_tuple(__URL__, __ADDRESS__, __FILTER__));     \
        __MTK_CHECK_DEPRECIATED_THIS(__MSG_TYPE__,  __DEPRECIATED_DATE__)     \
        __internal_handler__->signalMessage->connect(this, &CLASS_NAME::__FUNCT_RECEPTOR__);     \
        (__HANDLER__) = __internal_handler__;     \
    }


//------------------------------------------------------------------------------------------------------------------------------------------





namespace mtk{


    //  to be defined externally  (when not using admin)
    void check_control_fields_flucts    (const std::string&  key, const mtk::DateTime&  dt);


mtk::Signal<bool>&    get_signal_connection_status(void);



mtk::Signal<>&        __internal_get_signal_clossing_app(void);
void __internal_mtk_qpid_nevercall_me_release_on_exit(void);
#define RELEASE_____internal_mtk_qpid_nevercall_me_release_on_exit  mtk::__internal_mtk_qpid_nevercall_me_release_on_exit();


struct mtkqpid_session   :  public  mtk::SignalReceptor
{
    typedef  mtkqpid_session  CLASS_NAME;

private:
    qpid::messaging::Connection         connection;

public:
    const t_qpid_url                    url;
    qpid::messaging::Session&           qpid_session(void);

    mtkqpid_session(const t_qpid_url& _url)
        :    connection   (_url.WarningDontDoThisGetInternal())
           , url          (_url)
           , is_clossing_app(false)
    {
            //connection.setOption("reconnect", true);
            #if  MTK_PLATFORM  ==  MTK_LINUX_PLATFORM
                connection.setOption("tcp-nodelay", true);
            #endif
            connection.open();
            _qpid_session = connection.createSession();
            ++mtk_qpid_stats::num_created_sessions();
            MTK_CONNECT_THIS(__internal_get_signal_clossing_app(), clossing_app);
    }
    ~mtkqpid_session()
    {
        std::cout << "~mtkqpid_session" << std::endl;
        try{
            _qpid_session.close();
            connection.close();
            ++mtk_qpid_stats::num_deleted_sessions();
        } catch(...){
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "exception on destructor", "catched exception on destructor", mtk::alPriorError));
        }
    }

private:
    qpid::messaging::Session            _qpid_session;

    bool  is_clossing_app;
    void  clossing_app(void);
};



struct mtkqpid_sender2
{
    mtk::CountPtr<mtkqpid_session>      session;
    const t_qpid_address                address;
    mtk::t_qpid_exch_sender_conf        qe_config;
    qpid::messaging::Sender&            qpid_sender(void);

    mtkqpid_sender2(const t_qpid_url& _url, const t_qpid_address& _address, mtk::t_qpid_exch_sender_conf  _qe_config=mtk::t_qpid_exch_sender_conf(""))
        :  session (mtk::get_from_factory<mtkqpid_session>(_url))
         , address      (_address)
         , qe_config(_qe_config)
    {
        create_sender();
    }
    ~mtkqpid_sender2()
    {
        try{
            _qpid_sender.close();
            ++mtk_qpid_stats::num_deleted_senders();
        } catch(...){
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "exception on destructor", "catched exception on destructor", mtk::alPriorError));
        }
    }

private:
    qpid::messaging::Sender             _qpid_sender;

    void create_sender(void)
    {
        if(qe_config.WarningDontDoThisGetInternal() == "")
            _qpid_sender = session->qpid_session().createSender(MTK_SS(address<< ";" << QUEUE__DEFAULT_SENDER_CONFIG));
        else
            _qpid_sender = session->qpid_session().createSender(MTK_SS(address<< ";" <<  qe_config));
        _qpid_sender.setCapacity(100);
        ++mtk_qpid_stats::num_created_senders();
    }

};



struct mtkqpid_receiver
{
    mtk::CountPtr<mtkqpid_session>      session;
    const t_qpid_address                address;
    const t_qpid_filter                 filter;
    mtk::t_qpid_exch_recept_conf        qe_config;

    qpid::messaging::Receiver&          qpid_receiver(void);


    mtkqpid_receiver(const t_qpid_url& _url, const t_qpid_address&  _address, const t_qpid_filter& _filter, mtk::t_qpid_exch_recept_conf  _qe_config=mtk::t_qpid_exch_recept_conf(""))
        :  session (mtk::get_from_factory<mtkqpid_session>(_url))
         , address      (_address)
         , filter       (_filter)
         , qe_config    (_qe_config)
    {
        create_receiver();
    }
    ~mtkqpid_receiver()
    {
        try{
            _qpid_receiver.close();      //  http://apache-qpid-users.2158936.n2.nabble.com/receptor-out-of-scope-with-no-calling-receptor-close-td6858408.html
                                                    //  this not is a fully solution  http://192.168.7.10/wiki/index.php?n=Main.QPIDProblems
            ++mtk_qpid_stats::num_deleted_receivers();
        } catch(...){
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "exception on destructor", "catched exception on destructor", mtk::alPriorError));
        }
    }

private:
    qpid::messaging::Receiver           _qpid_receiver;

    void create_receiver(void)
    {
        std::string receptor_config;
        if(qe_config.WarningDontDoThisGetInternal() == "")
            receptor_config = MTK_SS(address << "/" <<  filter << "; " <<   QUEUE__DEFAULT_RECEPTOR_CONFIG);
        else
            receptor_config = MTK_SS(address << "/" <<  filter << "; " <<   qe_config);

        _qpid_receiver = session->qpid_session().createReceiver(receptor_config);
        _qpid_receiver.setCapacity(100);
        ++mtk_qpid_stats::num_created_receivers();
    }

};



//--------------------------------------------------------------------

//      O U T

//--------------------------------------------------------------------


    std::string  get_control_fluct_key(void);       //  defined in mtk_qpid_stats.cpp
    void         set_control_fluct_key(const std::string& control_fluct_key);   //  defined in mtk_qpid_stats.cpp


    void    __internal_send_qpid_message___dont_use_it_directly(     mtk::CountPtr< mtk::mtkqpid_sender2 >      sender,
                                                                              qpid::types::Variant::Map&        content,
                                                                        const std::string&                      subject,
                                                                        const std::string&                      message_type,
                                                                        const std::string&                      control_fluct_key,
                                                                        int                                     real_time_level,
                                                                        mtk::nullable<mtk::DateTime>            depreciated_on
                                                                        );

    template<typename T>
    void send_message_with_sender (mtk::CountPtr< mtk::mtkqpid_sender2 >  sender, const T& message, mtk::t_qpid_filter subject =  mtk::t_qpid_filter(""))
    {
        static std::string  control_fluct_key="";
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(40))
            if(control_fluct_key == "")
                control_fluct_key = mtk::get_control_fluct_key();
        MTK_END_EXEC_MAX_FREC

        if(message.get_qpid_address() !=  sender->address)
            throw mtk::Alarm(MTK_HERE, "send_message_with_sender", MTK_SS("sender address and message address doesn't match. Message not sent"), mtk::alPriorCritic);

        if (subject.WarningDontDoThisGetInternal() == "")
            subject = message.get_out_subject();
        //qpid::messaging::Message msg(message.qpidmsg_codded_as_qpid_message(control_fluct_key));
        //msg.setSubject(MTK_SS(subject));

        int real_time_level =  T::static_return_message_RT_priority();

        if(T::static_get_depreciated_on().HasValue()  &&  T::static_get_depreciated_on().Get() < mtk::dtNowLocal())
        {
            MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(5))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "depreciated", MTK_SS("sending depreciated message " << T::static_get_message_type_as_string() << "  " << T::static_get_depreciated_on()), mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
        }


        qpid::types::Variant::Map   content = message.qpidmsg_codded_as_qpid_map();
        __internal_send_qpid_message___dont_use_it_directly(sender, content, MTK_SS(subject), T::static_get_message_type_as_string(), control_fluct_key, real_time_level, T::static_get_depreciated_on());
    }

    #define mtk_send_message(__URL_FOR__, __MESSAGE__)  \
    {               \
        static auto qpid_sender = mtk::get_from_factory< mtk::mtkqpid_sender2 >(mtk::make_tuple(mtk::admin::get_url(__URL_FOR__), __MESSAGE__.get_qpid_address()));    \
        send_message_with_sender(qpid_sender, __MESSAGE__);                                                                                                                     \
    }




//--------------------------------------------------------------------

//      I N

//--------------------------------------------------------------------



//---------------------------------------------------------------------
//      Messages reception with no parsing
//---------------------------------------------------------------------


class handle_qpid_exchange_receiver   :  public mtk::SignalReceptor {
    mtk::non_copyable nc;
    typedef handle_qpid_exchange_receiver CLASS_NAME;

    public:
        explicit handle_qpid_exchange_receiver(const t_qpid_url& url, const t_qpid_address& address, const t_qpid_filter& filter);
        ~handle_qpid_exchange_receiver(void);

        CountPtr< Signal<const qpid::messaging::Message&> >       signalMessage;


    private:
        CountPtr<mtkqpid_receiver>             receiver;

        void check_queue(void);


};






template<>
inline mtk::CountPtr< mtk::mtkqpid_session> create_instance_for_factory (const t_qpid_url& key_url, mtk::CountPtr<mtk::mtkqpid_session> result)
{
    result = mtk::make_cptr(new mtk::mtkqpid_session(key_url));
    return result;
}

template<>
inline mtk::CountPtr< mtk::mtkqpid_receiver> create_instance_for_factory (const mtk::tuple<t_qpid_url, t_qpid_address, t_qpid_filter>& key, mtk::CountPtr<mtk::mtkqpid_receiver> result)
{
    result = mtk::make_cptr(new mtk::mtkqpid_receiver(key._0, key._1, key._2));
    return result;
}


template<>
inline mtk::CountPtr< mtk::mtkqpid_sender2> create_instance_for_factory (const mtk::tuple<t_qpid_url, t_qpid_address>& key, mtk::CountPtr<mtk::mtkqpid_sender2> result)
{
    result = mtk::make_cptr(new mtk::mtkqpid_sender2(key._0, key._1));
    return result;
}



template<>
inline mtk::CountPtr< mtk::handle_qpid_exchange_receiver> create_instance_for_factory (const mtk::tuple<t_qpid_url, t_qpid_address, t_qpid_filter>& key, mtk::CountPtr< mtk::handle_qpid_exchange_receiver> result)
{
    result = mtk::make_cptr(new mtk::handle_qpid_exchange_receiver(key._0, key._1, key._2));
    return result;
}







template<typename MESSAGE_TYPE>
class handle_qpid_exchange_receiverMT   :  public mtk::SignalReceptor {
    mtk::non_copyable nc;
    typedef handle_qpid_exchange_receiverMT CLASS_NAME;

    public:
        explicit handle_qpid_exchange_receiverMT(const t_qpid_url& url, const t_qpid_address& address, const t_qpid_filter& filter);
        ~handle_qpid_exchange_receiverMT(void)
        {
            try{
                ++mtk_qpid_stats::num_deleted_suscriptions();
                signalBeforeDestroy.emit();
            } catch(...){
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "exception on destructor", "catched exception on destructor", mtk::alPriorError));
            }
        }

        mtk::nullable<mtk::DateTime>                  depreciated_on;
        CountPtr< Signal<const MESSAGE_TYPE&> >       signalMessage;
        mtk::Signal<>                                 signalBeforeDestroy;




    private:
        CountPtr<handle_qpid_exchange_receiver>              hqpid_receiver;
        void on_message(const qpid::messaging::Message& message);
};


template<typename MESSAGE_TYPE>
inline handle_qpid_exchange_receiverMT<MESSAGE_TYPE>::handle_qpid_exchange_receiverMT(const t_qpid_url& url, const t_qpid_address& address, const t_qpid_filter& filter)
    :     signalMessage(mtk::make_cptr(new Signal<const MESSAGE_TYPE&>()))
        , hqpid_receiver( get_from_factory<mtk::handle_qpid_exchange_receiver>(mtk::make_tuple(url, address, filter)) )
{
    ++mtk_qpid_stats::num_created_suscriptions();
    MTK_CONNECT_THIS(*(hqpid_receiver->signalMessage), on_message)
}


template<typename MESSAGE_TYPE>
inline void handle_qpid_exchange_receiverMT<MESSAGE_TYPE>::on_message(const qpid::messaging::Message& message)
{
    //  get control fields
    //  if message type matches, convert and send signal


    //  to let a save handle deleting when receiving and processing a message from it selft
    CountPtr< Signal<const MESSAGE_TYPE&> >       local_copy_signalMessage (signalMessage);;
    CountPtr<handle_qpid_exchange_receiver>       local_copy_hqpid_receiver(hqpid_receiver);


    if (message.getContentType() != "amqp/map")
        throw mtk::Alarm(MTK_HERE, "handle_qpid_exchange_receiverMT<>",
                                    MTK_SS("invalid message structure, spected map  "  << message.getContent()),
                                    mtk::alPriorCritic, mtk::alTypeNoPermisions);

    qpid::types::Variant::Map mv;
    qpid::messaging::decode(message, mv);
    std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

    if (mv.find("_cf_") == mv.end())
        throw mtk::Alarm(MTK_HERE, "handle_qpid_exchange_receiverMT<>", "missing control fields", mtk::alPriorCritic, mtk::alTypeNoPermisions);
    else
    {
        msg::sub_control_fields cf(__internal_get_default((msg::sub_control_fields*)0));
        msg::copy(cf, mv["_cf_"].asMap());
        if (cf.message_type == MESSAGE_TYPE::static_get_message_type_as_string())
        {
            MESSAGE_TYPE mt(mv);
            mt.__internal_warning_control_fields = &cf;

            if(cf.message_type  ==  "ppc")
                mtk::mtk_qpid_stats::message_received(message.getContentSize(), mtk::mtk_qpid_stats::mt_prices);
            mtk::mtk_qpid_stats::message_received_for_message_size(message.getContentSize(), cf.message_type);

            MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(10))
                if(cf.depreciated_on.HasValue()   &&   this->depreciated_on.HasValue()    &&   cf.depreciated_on.Get() != this->depreciated_on.Get())
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "depreciated",
                            MTK_SS("diferent depreciated date " << MESSAGE_TYPE::static_get_message_type_as_string()
                                    << "  "  <<   cf.depreciated_on.Get() << "  !=  "  <<  this->depreciated_on.Get()
                            ), mtk::alPriorError));
                else if(cf.depreciated_on.HasValue()   &&   this->depreciated_on.HasValue()==false)
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "depreciated",
                            MTK_SS("received depreciated  on non registered as depreciated message " << MESSAGE_TYPE::static_get_message_type_as_string()
                                    << "  "  <<   cf.depreciated_on.Get()
                            ), mtk::alPriorError));
                else if(cf.depreciated_on.HasValue()==false   &&   this->depreciated_on.HasValue())
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "depreciated",
                            MTK_SS("received NON  depreciated  on message  registered as depreciated message " << MESSAGE_TYPE::static_get_message_type_as_string()
                                    << "  "  <<   this->depreciated_on.Get()
                            ), mtk::alPriorError));
                else if(cf.depreciated_on.HasValue()   &&   cf.depreciated_on.Get() < mtk::dtNowLocal())
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "depreciated",
                            MTK_SS("received depreciated  message   " << MESSAGE_TYPE::static_get_message_type_as_string()
                                    << "  "  <<   cf.depreciated_on.Get()
                            ), mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC

            signalMessage->emit(mt);
            MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(5))
                check_control_fields_flucts(cf.control_fluct_key, cf.sent_date_time);
            MTK_END_EXEC_MAX_FREC
        }
//        nullable<msg::sub_control_fields> cf;
//        msg::copy(cf, mv["_cf_"].asMap());
//        if (cf.HasValue() == false)
//            throw mtk::Alarm(MTK_HERE, "missing control fileds", mtk::alPriorCritic, mtk::alTypeNoPermisions);
//        else
//        {
//            if (cf.Get().message_type == MESSAGE_TYPE::static_get_message_type_as_string())
//                signalMessage->emit(MESSAGE_TYPE(message));
//        }
    }


}





extern    std::string  get_cli_srv(void);




};  //  namespace mtk

#endif
