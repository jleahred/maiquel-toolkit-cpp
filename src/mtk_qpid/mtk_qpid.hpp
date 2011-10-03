/*
        Verificar el control de fluctuaciones

        Meter otra vez el control de versiones


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



#define MTK_QPID_RECEIVER_CONNECT_F(__HANDLER__, __URL__, __ADDRESS__, __FILTER__, __MSG_TYPE__, __FUNCT_RECEPTOR__)  \
    {    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > __internal_handler__ =      \
                                            mtk::get_from_factory<mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >(mtk::make_tuple(std::string(__URL__), std::string(__ADDRESS__), std::string(__FILTER__)));     \
        __internal_handler__->signalMessage->connect(__FUNCT_RECEPTOR__);     \
        (__HANDLER__) = __internal_handler__;     \
    }


#define MTK_QPID_RECEIVER_CONNECT_THIS(__HANDLER__, __URL__, __ADDRESS__, __FILTER__, __MSG_TYPE__, __FUNCT_RECEPTOR__)  \
    {    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > __internal_handler__ =      \
                                            mtk::get_from_factory<mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >(mtk::make_tuple(std::string(__URL__), std::string(__ADDRESS__), std::string(__FILTER__)));     \
        __internal_handler__->signalMessage->connect(this, &CLASS_NAME::__FUNCT_RECEPTOR__);     \
        (__HANDLER__) = __internal_handler__;     \
    }


namespace mtk{




    //      on qpid012 it's necessary to configure as this in order to delete the linked queue when receiver or session
    //      get out of scope
    //      This bug is fixed on qpid013  (pending to test)
    static const char* const  QUEUE__DEFAULT_RECEPTOR_CONFIG  =
                    "{ "
                    "  assert: allways, "
                    //"  create: never, "
                    "  node : "
                    "  { "
                    "    type: topic "
                    "  }, "
                    "  link: "
                    "  { "
                    //"    name: 'testing1" << i << "', "
                    "    durable: false, "
                    "    x-declare: "
                    "    { "
                    "      auto-delete: true, "
                    "      exclusive: True, "
                    "      arguments: "
                    "      { "
                    //"         qpid.last_value_queue_key: 'qpid.subject', "
                    "        'qpid.max_count': 2000, "
                    "        'qpid.max_size': 2000000, "        //  in bytes
                    "        'qpid.policy_type': ring "
                    "      } "
                    "    } "
                    "  } "
                    "} ";


    //  to be defined externally  (when not using admin)
    void check_control_flields_flucts    (const std::string&  key, const mtk::DateTime&  dt);



namespace  OUT_CONFIG {
    void SetIdReloj         (int idReloj);
    int  GetIdReloj         (void);
    //int  GetNumSecuencia    (void);
};


struct qpid_session
{
    qpid::messaging::Connection         connection;
    qpid::messaging::Session            session;
    const std::string                   url;
    const std::string                   address;
    qpid::messaging::Sender             sender;

    qpid::messaging::Receiver      createReceiver(const std::string& filter)  {
            //std::string session_config = MTK_SS(address<< "; {assert:always, create:always, node-properties:{type:topic}, delete:always, filter:[control, "<< filter <<"]}");
            //std::string session_config = MTK_SS(address<< "/" << filter << "; {assert:always, node:{type:topic}}");
            std::string receptor_config = MTK_SS(address << "/" <<  filter << "; " <<   QUEUE__DEFAULT_RECEPTOR_CONFIG);
            qpid::messaging::Receiver receiver = session.createReceiver(receptor_config);
            receiver.setCapacity(100);
            return receiver;
        }

    qpid_session(const std::string& _url, const std::string& _address)
        :  connection   (_url)
         //, session      (connection.newSession())
         , url          (_url)
         , address      (_address)
         ////, sender       (session.createSender(MTK_SS(address<< "; {assert:always, create:always, node-properties:{type:topic}, delete:always}")))
         //, sender       (session.createSender(MTK_SS(address<< "; {assert:always, node-properties:{type:topic} }")))
    {
            connection.open();
            session = connection.createSession();
            sender = session.createSender(MTK_SS(address<< "; {assert:always, node:{type:topic} }"));
            sender.setCapacity(100);
            ++mtk_qpid_stats::num_created_sessions();
    }
    ~qpid_session() {session.close();   --mtk_qpid_stats::num_deleted_sessions();  }
};

//--------------------------------------------------------------------

//      O U T

//--------------------------------------------------------------------


    std::string  get_control_fluct_key(void);       //  defined in mtk_qpid_stats.cpp
    void         set_control_fluct_key(const std::string& control_fluct_key);   //  defined in mtk_qpid_stats.cpp


    template<typename T>
    void send_message (mtk::CountPtr< mtk::qpid_session > qpid_session, const T& message, std::string subject = "")
    {
        static std::string  control_fluct_key="";

        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(40))
            if(control_fluct_key == "")
                control_fluct_key = get_control_fluct_key();
        MTK_END_EXEC_MAX_FREC

        ++mtk_qpid_stats::num_messages_sent();
        if (subject == "")
            subject = message.get_out_subject();
        //qpid::messaging::Sender sender = qpid_session->createSender(subject);
        qpid::messaging::Message msg(message.qpidmsg_codded_as_qpid_message(control_fluct_key));
        msg.setSubject(subject);
        qpid_session->sender.send(msg);
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
        explicit handle_qpid_exchange_receiver(const std::string& url, const std::string& address, const std::string& filter);
        ~handle_qpid_exchange_receiver(void) { ++mtk_qpid_stats::num_deleted_suscriptions_no_parsing(); }

        CountPtr< Signal<const qpid::messaging::Message&> >       signalMessage;




    private:
        qpid::messaging::Receiver           receiver;
        CountPtr<qpid_session>              session;

        void check_queue(void);


};





template<>
inline mtk::CountPtr< mtk::handle_qpid_exchange_receiver> create_instance_for_factory (const mtk::tuple<std::string, std::string, std::string>& key, mtk::CountPtr< mtk::handle_qpid_exchange_receiver> result)
{
    result = mtk::make_cptr(new mtk::handle_qpid_exchange_receiver(key._0, key._1, key._2));
    return result;
}



template<>
inline CountPtr< qpid_session > create_instance_for_factory (const mtk::tuple<std::string/*url*/, std::string/*address*/>& key, CountPtr< qpid_session > result)
{
    result = mtk::make_cptr(new qpid_session(key._0, key._1));
    return result;
}




inline handle_qpid_exchange_receiver::handle_qpid_exchange_receiver(const std::string& url, const std::string& address, const std::string& filter)
    :     signalMessage(mtk::make_cptr(new Signal<const qpid::messaging::Message&>))
        , session(get_from_factory<qpid_session>(mtk::make_tuple(url, address)))
{
    ++mtk_qpid_stats::num_created_suscriptions_no_parsing();
    //std::string session_config = MTK_SS(address<< "; {assert:always, create:always}");
    //std::string session_config = MTK_SS(address<< "; {assert:always, create:always, node-properties:{type:topic}, delete:always, filter:[control, "<< filter <<"]}");
    receiver = session->createReceiver(filter);

    MTK_TIMER_1C(check_queue);

}

inline void handle_qpid_exchange_receiver::check_queue(void)
{
        qpid::messaging::Receiver           local_receiver = receiver;
        CountPtr<qpid_session>              local_session  = session;
        //  this is to protect in case of  handle_qpid_exchange_receiver is out of scope when is processing a message


		qpid::messaging::Message message;
        while(local_receiver.getAvailable())
        {
            local_receiver.fetch(message, qpid::messaging::Duration(0));
            //  pending, not too much fetches each time

            ++mtk_qpid_stats::num_messages_received();
            mtk_qpid_stats::last_received_message() = mtk::dtNowLocal();

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
                                std::string(" address>") + "pending",
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
        explicit handle_qpid_exchange_receiverMT(const std::string& url, const std::string& address, const std::string& filter);
        ~handle_qpid_exchange_receiverMT(void) {  ++mtk_qpid_stats::num_deleted_suscriptions();  }

        CountPtr< Signal<const MESSAGE_TYPE&> >       signalMessage;




    private:
        CountPtr<handle_qpid_exchange_receiver>              hqpid_receiver;
        void on_message(const qpid::messaging::Message& message);
};


template<typename MESSAGE_TYPE>
inline handle_qpid_exchange_receiverMT<MESSAGE_TYPE>::handle_qpid_exchange_receiverMT(const std::string& url, const std::string& address, const std::string& filter)
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
            MESSAGE_TYPE mt(message);
            mt.__internal_warning_control_fields = &cf;
            signalMessage->emit(mt);
            MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(5))
                check_control_flields_flucts(cf.control_fluct_key, cf.sent_date_time);
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
