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


#include "mtk_qpid_stats.h"



#define MTK_QPID_RECEIVER_CONNECT_F(__HANDLER__, __URL__, __FILTER__, __MSG_TYPE__, __FUNCT_RECEPTOR__)  \
    {    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > __internal_handler__ =      \
                                            mtk::get_from_factory<mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >(mtk::make_tuple(     __URL__, \
                                                                                                                                            mtk::t_qpid_address(__MSG_TYPE__::static_get_qpid_address()), \
                                                                                                                                            __FILTER__));     \
        __internal_handler__->signalMessage->connect(__FUNCT_RECEPTOR__);     \
        (__HANDLER__) = __internal_handler__;     \
    }


#define MTK_QPID_RECEIVER_CONNECT_THIS(__HANDLER__, __URL__, __FILTER__, __MSG_TYPE__, __FUNCT_RECEPTOR__)  \
    {    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > __internal_handler__ =      \
                                            mtk::get_from_factory<mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >(mtk::make_tuple(     __URL__, \
                                                                                                                                            mtk::t_qpid_address(__MSG_TYPE__::static_get_qpid_address()), \
                                                                                                                                            __FILTER__));     \
        __internal_handler__->signalMessage->connect(this, &CLASS_NAME::__FUNCT_RECEPTOR__);     \
        (__HANDLER__) = __internal_handler__;     \
    }


#define MTK_QPID_RECEIVER_CONNECT_F__WITH_ADDRESS(__HANDLER__, __URL__, __ADDRESS__, __FILTER__, __MSG_TYPE__, __FUNCT_RECEPTOR__)  \
    {    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > __internal_handler__ =      \
                                            mtk::get_from_factory<mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >(mtk::make_tuple(__URL__, __ADDRESS__, __FILTER__));     \
        __internal_handler__->signalMessage->connect(__FUNCT_RECEPTOR__);     \
        (__HANDLER__) = __internal_handler__;     \
    }


#define MTK_QPID_RECEIVER_CONNECT_THIS__WITH_ADDRESS(__HANDLER__, __URL__, __ADDRESS__, __FILTER__, __MSG_TYPE__, __FUNCT_RECEPTOR__)  \
    {    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > __internal_handler__ =      \
                                            mtk::get_from_factory<mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >(mtk::make_tuple(__URL__, __ADDRESS__, __FILTER__));     \
        __internal_handler__->signalMessage->connect(this, &CLASS_NAME::__FUNCT_RECEPTOR__);     \
        (__HANDLER__) = __internal_handler__;     \
    }







namespace mtk{


    //  to be defined externally  (when not using admin)
    void check_control_fields_flucts    (const std::string&  key, const mtk::DateTime&  dt);





struct mtkqpid_session
{
    qpid::messaging::Connection         connection;
    const t_qpid_url                    url;
    qpid::messaging::Session&           qpid_session(void)
    {
        if(_qpid_session.hasError())
        {
            _qpid_session  = connection.createSession();
            ++mtk_qpid_stats::num_restored_sessions();
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "restoring session", "invalid session", mtk::alPriorCritic));
            try
            {
                _qpid_session.checkError();
            } catch (const qpid::types::Exception & error)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "restoring session", error.what(), mtk::alPriorCritic));
            }
        }
        return  _qpid_session;
    }

    mtkqpid_session(const t_qpid_url& _url)
        :  connection   (_url.WarningDontDoThisGetInternal())
         , url          (_url)
    {
            connection.open();
            _qpid_session = connection.createSession();
            ++mtk_qpid_stats::num_created_sessions();
    }
    ~mtkqpid_session()
    {
        try{
            _qpid_session.close();
            ++mtk_qpid_stats::num_deleted_sessions();
        } catch(...){
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "exception on destructor", "catched exception on destructor", mtk::alPriorError));
        }
    }

private:
    qpid::messaging::Session            _qpid_session;
};



struct mtkqpid_sender2
{
    mtk::CountPtr<mtkqpid_session>      session;
    const t_qpid_address                address;
    mtk::t_qpid_exch_sender_conf        qe_config;
    qpid::messaging::Sender&            qpid_sender(void)
    {
        if(_qpid_sender.getSession().hasError())
        {
            if(session->qpid_session().hasError()==false)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "mtkqpid_sender2", "reseting sender", mtk::alPriorError));
                create_sender();
            }
            else
                throw mtk::Alarm(MTK_HERE, "mtkqpid_sender2", "invalid sender and session. not possible to recover", mtk::alPriorCritic);
        }
        return _qpid_sender;
    }


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

    qpid::messaging::Receiver&          qpid_receiver()
    {
        if(_qpid_receiver.getSession().hasError())
        {
            if(session->qpid_session().hasError()==false)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "mtkqpid_receiver", "reseting sender", mtk::alPriorError));
                create_receiver();
            }
            else
                throw mtk::Alarm(MTK_HERE, "mtkqpid_receiver", "invalid sender and session. not possible to recover", mtk::alPriorCritic);
        }
        return _qpid_receiver;
    }


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


    template<typename T>
    void send_message_with_sender (mtk::CountPtr< mtk::mtkqpid_sender2 >  sender, const T& message, mtk::t_qpid_filter subject =  mtk::t_qpid_filter(""))
    {
        static std::string  control_fluct_key="";

        if(message.get_qpid_address() !=  sender->address)
            throw mtk::Alarm(MTK_HERE, "send_message_with_sender", MTK_SS("sender address and message address doesn't match. Message not sent"), mtk::alPriorCritic);


        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(40))
            if(control_fluct_key == "")
                control_fluct_key = get_control_fluct_key();
        MTK_END_EXEC_MAX_FREC

        ++mtk_qpid_stats::num_messages_sent();
        if(mtk_qpid_stats::last_received_message() >  (mtk::dtToday_0Time() + mtk::dtHours(23) + mtk::dtMinutes(50)))
            mtk_qpid_stats::num_messages_sent_today() = 0;
        ++mtk_qpid_stats::num_messages_sent_today();

        if (subject.WarningDontDoThisGetInternal() == "")
            subject = message.get_out_subject();
        //qpid::messaging::Sender sender = qpid_session->createSender(subject);
        qpid::messaging::Message msg(message.qpidmsg_codded_as_qpid_message(control_fluct_key));
        msg.setSubject(MTK_SS(subject));
        sender->qpid_sender().send(msg);
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
        ~handle_qpid_exchange_receiver(void)
        {
            try{
                ++mtk_qpid_stats::num_deleted_suscriptions_no_parsing();
            } catch(...){
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "exception on destructor", "catched exception on destructor", mtk::alPriorError));
            }
        }

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







inline handle_qpid_exchange_receiver::handle_qpid_exchange_receiver(const t_qpid_url& url, const t_qpid_address& address, const t_qpid_filter& filter)
    :     signalMessage(mtk::make_cptr(new Signal<const qpid::messaging::Message&>))
        , receiver(get_from_factory<mtkqpid_receiver>(mtk::make_tuple(url, address, filter)))
{
    ++mtk_qpid_stats::num_created_suscriptions_no_parsing();

    MTK_TIMER_1C(check_queue);
}

inline void handle_qpid_exchange_receiver::check_queue(void)
{
        qpid::messaging::Receiver           local_receiver;
        try
        {
             local_receiver = receiver->qpid_receiver();
        }
        catch(mtk::Alarm alarm)
        {
            MTK_TIMER_1C_STOP(check_queue);
            mtk::AlarmMsg(alarm.Add(mtk::Alarm(MTK_HERE, "check_queue", MTK_SS("disconecting receiver  on address  " << receiver->address), mtk::alPriorCritic)));
        }
        catch(const std::exception& e)
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_queue", MTK_SS("disconecting receiver  on address  " << receiver->address << "  "  << e.what()), mtk::alPriorCritic));
        }
        catch(...)
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_queue", MTK_SS("disconecting receiver  (...) on address  " << receiver->address), mtk::alPriorCritic));
        }

        //  this is to protect in case of  handle_qpid_exchange_receiver is out of scope when is processing a message


		qpid::messaging::Message message;
        while(local_receiver.getAvailable())
        {
            local_receiver.fetch(message, qpid::messaging::Duration(0));
            //  pending, not too much fetches each time

            ++mtk_qpid_stats::num_messages_received();
            mtk_qpid_stats::last_received_message() = mtk::dtNowLocal();

            if(mtk_qpid_stats::last_received_message() >  (mtk::dtToday_0Time() + mtk::dtHours(23) + mtk::dtMinutes(50)))
                mtk_qpid_stats::num_messages_received_today() = 0;
            ++mtk_qpid_stats::num_messages_received_today();

            try
            {
                //  copiamos el estado que nos podría hacer falta por si acaso...
//                std::string localcopy_subject = subject;
                //  estas copias además tienen el objetivo de asegurar que no salgan de ámbito
                //  si se destruyese el objeto mientras se ejecuta el método
                CountPtr< Signal<const qpid::messaging::Message&> >      localcopy_signalMessage(signalMessage);
                //CountPtr< Signal<const Alarm& > >  localcopy_signalError(signalError);

                try
                {
                    MTK_HANDLE_DIV0_INIT
                    {

                        //  OJO, después de emit no debe accederse a este objeto
                        //  por si nos lo borran en el proceso del propio emit
                        //  con stop o reescribiéndolo con otro valor
                        localcopy_signalMessage->emit(message);

                    }
                    MTK_HANDLE_DIV0_END
                } catch (const Alarm& alError) {
                    Alarm  qpid_error(
                                MTK_HERE, "handle_qpid_exchange_receiver",
                                std::string("exception processing message"),
                                alPriorCritic
                        );
                    qpid::types::Variant::Map mv;
                    qpid::messaging::decode(message, mv);
                    qpid_error.Add(mtk::Alarm(MTK_HERE, "handle_qpid_exchange_receiver", MTK_SS("msg>  " << mv), mtk::alPriorCritic));
                    qpid_error.Add(alError);
                    mtk::AlarmMsg(qpid_error);
                }
                catch (std::exception& e) {
                    Alarm  qpid_error(MTK_HERE, "handle_qpid_exchange_receiver",
                                MTK_SS (" SUBJ>" << message.getSubject() << "  " << e.what()),
                                alPriorCritic);
                    qpid::types::Variant::Map mv;
                    qpid::messaging::decode(message, mv);
                    qpid_error.Add(mtk::Alarm(MTK_HERE, "handle_qpid_exchange_receiver", MTK_SS("msg>  " << mv), mtk::alPriorCritic));
                    mtk::AlarmMsg(qpid_error);
                } catch (...) {
                    Alarm  qpid_error(MTK_HERE, "handle_qpid_exchange_receiver",
                                MTK_SS (" SUBJ>" << message.getSubject() << "  ... unkown exception"),
                                alPriorCritic);
                    qpid::types::Variant::Map mv;
                    qpid::messaging::decode(message, mv);
                    qpid_error.Add(mtk::Alarm(MTK_HERE, "handle_qpid_exchange_receiver", MTK_SS("msg>  " << mv), mtk::alPriorCritic));
                    mtk::AlarmMsg(qpid_error);
                }

            } catch (const Alarm& alError) {
                std::cerr << "handle_qpid_exchange_receiver " << std::endl << alError << std::endl;
                std::cerr << "Ostrás!!!!   qué hago, qué hago!!!!... si alguien ve este mensaje que avise al desarrollador "
                             " socorro!!!!" << std::endl  << "esto no debería pasarme a mi" << std::endl;
            }
            catch (std::exception& e) {
                std::cerr << "handle_qpid_exchange_receiver " << std::endl << e.what() << std::endl;
                std::cerr << "Ostrás!!!!   qué hago, qué hago!!!!... si alguien ve este mensaje que avise al desarrollador "
                             " socorro!!!!" << std::endl  << "esto no debería pasarme a mi" << std::endl;
            } catch (...) {
                std::cerr << "handle_qpid_exchange_receiver " << std::endl << "  ... unkown exception" << std::endl;
                std::cerr << "Ostrás!!!!   qué hago, qué hago!!!!... si alguien ve este mensaje que avise al desarrollador "
                             " socorro!!!!" << std::endl  << "esto no debería pasarme a mi" << std::endl;
            }

        }
        //  local_session->session.acknowledge();     //  configure it asynchronous?        working with publish subscription is not necesary
                                                      //  if it would be necessary, it has to be called just after message reception
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
            } catch(...){
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "exception on destructor", "catched exception on destructor", mtk::alPriorError));
            }
        }

        CountPtr< Signal<const MESSAGE_TYPE&> >       signalMessage;




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
        throw mtk::Alarm(MTK_HERE, "handle_qpid_exchange_receiverMT<>", "missing control fileds", mtk::alPriorCritic, mtk::alTypeNoPermisions);
    else
    {
        msg::sub_control_fields cf(__internal_get_default((msg::sub_control_fields*)0));
        msg::copy(cf, mv["_cf_"].asMap());
        if (cf.message_type == MESSAGE_TYPE::static_get_message_type_as_string())
        {
            MESSAGE_TYPE mt(mv);
            mt.__internal_warning_control_fields = &cf;
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









};  //  namespace mtk

#endif
