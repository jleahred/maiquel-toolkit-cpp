#include "mtk_qpid.h"


#include "components/admin/admin.h"



namespace {


    struct  delayed_message_to_send_info
    {
        mtk::CountPtr< mtk::mtkqpid_sender2 >   sender;
        qpid::types::Variant::Map               content;
        std::string                             subject;
        std::string                             message_type;
        std::string                             control_fluct_key;
        mtk::nullable<mtk::DateTime>            depreciated_on;
    };


    void check_NORMAL_queue(void);
    void check_SLOW_queue  (void);


    mtk::CountPtr<mtk::list<delayed_message_to_send_info> >   get_list_msg_to_send_NORMAL(void)
    {
        static auto  result = mtk::make_cptr(new mtk::list<delayed_message_to_send_info>);
        static bool  first_call=true;
        if(first_call)
        {
            MTK_TIMER_1CF(check_NORMAL_queue);
            first_call = false;
        }
        return result;
    }

    mtk::CountPtr<mtk::list<delayed_message_to_send_info> >   get_list_msg_to_send_SLOW(void)
    {
        static auto  result = mtk::make_cptr(new mtk::list<delayed_message_to_send_info>);
        static bool  first_call=true;
        if(first_call)
        {
            MTK_TIMER_1DF(check_SLOW_queue);
            first_call = false;
        }
        return result;
    }



    void    send_qpid_message_NOW      (        delayed_message_to_send_info&  msg_info  );
    void    send_qpid_message_NORMAL   (  const delayed_message_to_send_info&  msg_info  );
    void    send_qpid_message_SLOW     (  const delayed_message_to_send_info&  msg_info  );


};




namespace mtk{


mtk::Signal<bool>&    get_signal_connection_status(void)
{
    static  auto  result = mtk::make_cptr(new mtk::Signal<bool>{});
    return *result;
}


mtk::Signal<>&        __internal_get_signal_clossing_app(void)
{
    static  auto  result = mtk::make_cptr(new mtk::Signal<>{});
    return *result;
}


void __internal_mtk_qpid_nevercall_me_release_on_exit(void)
{
    __internal_get_signal_clossing_app().emit();
}



qpid::messaging::Session&           mtkqpid_session::qpid_session(void)
{
    if(is_clossing_app)
    {
        std::cerr  << "requested qpid_session on   clossing_app" << std::endl;
        return  _qpid_session;
    }

    if(connection.isOpen()==false)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(30))
            get_signal_connection_status().emit(false);
        MTK_END_EXEC_MAX_FREC
        static mtk::DateTime  last_try_reconnect = mtk::dtNowLocal() - mtk::dtSeconds(10);
        if(last_try_reconnect + mtk::dtSeconds(2) < mtk::dtNowLocal())
        {
            std::cerr << "error, trying to reconnect" << std::endl;
            last_try_reconnect = mtk::dtNowLocal();
            //connection.open();
            connection   = qpid::messaging::Connection(url.WarningDontDoThisGetInternal());
            #if  MTK_PLATFORM  ==  MTK_LINUX_PLATFORM
                connection.setOption("tcp-nodelay", true);
            #endif
            connection.open();
            if(connection.isOpen())
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "mtk_qpid", "reconnected!!!", mtk::alPriorCritic));
                get_signal_connection_status().emit(true);
            }
        }
        else
            throw mtk::Alarm(MTK_HERE, "QPID", "connection down", mtk::alPriorCritic);
    }

    if(_qpid_session.hasError())
    {
        _qpid_session  = connection.createSession();
        ++mtk_qpid_stats::num_restored_sessions();
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(10))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "restoring session", "invalid session", mtk::alPriorCritic));
        MTK_END_EXEC_MAX_FREC
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

void  mtkqpid_session::clossing_app(void)
{
    connection.close();
}





qpid::messaging::Sender&            mtkqpid_sender2::qpid_sender(void)
{
    if(_qpid_sender.getSession().hasError())
    {
        if(session->qpid_session().hasError()==false)
        {
            MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(10))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "mtkqpid_sender2", "reseting sender", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            create_sender();
        }
        else
            throw mtk::Alarm(MTK_HERE, "mtkqpid_sender2", "invalid sender and session. not possible to recover", mtk::alPriorCritic);
    }
    return _qpid_sender;
}



qpid::messaging::Receiver&          mtkqpid_receiver::qpid_receiver(void)
{
    if(_qpid_receiver.getSession().hasError())
    {
        if(session->qpid_session().hasError()==false)
        {
            MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(10))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "mtkqpid_receiver", "reseting sender", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            create_receiver();
        }
        else
            throw mtk::Alarm(MTK_HERE, "mtkqpid_receiver", "invalid sender and session. not possible to recover", mtk::alPriorCritic);
    }
    return _qpid_receiver;
}



__internal_impl_handle_qpid_exchange_receiver::__internal_impl_handle_qpid_exchange_receiver(const t_qpid_url& url, const t_qpid_address& address, const t_qpid_filter& filter)
    :     signalMessage{}
        , receiver(get_from_factory<mtkqpid_receiver>(mtk::make_tuple(url, address, filter)))
{
    ++mtk_qpid_stats::num_created_suscriptions_no_parsing();

    MTK_TIMER_1C(check_queue);
}


__internal_impl_handle_qpid_exchange_receiver::~__internal_impl_handle_qpid_exchange_receiver(void)
{
    try{
        ++mtk_qpid_stats::num_deleted_suscriptions_no_parsing();
    } catch(...){
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "exception on destructor", "catched exception on destructor", mtk::alPriorError));
    }
}


void __internal_impl_handle_qpid_exchange_receiver::check_queue(void)
{
        qpid::messaging::Receiver           local_receiver;
        try
        {
             local_receiver = receiver->qpid_receiver();
        }
        catch(...)
        {
            MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(10))
                throw;
            MTK_END_EXEC_MAX_FREC
            return;
        }
//        catch(mtk::Alarm alarm)
//        {
//            MTK_TIMER_1C_STOP(check_queue);
//            mtk::AlarmMsg(alarm.Add(mtk::Alarm(MTK_HERE, "check_queue", MTK_SS("disconecting receiver  on address  " << receiver->address), mtk::alPriorCritic)));
//        }
//        catch(const std::exception& e)
//        {
//            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_queue", MTK_SS("disconecting receiver  on address  " << receiver->address << "  "  << e.what()), mtk::alPriorCritic));
//        }
//        catch(...)
//        {
//            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_queue", MTK_SS("disconecting receiver  (...) on address  " << receiver->address), mtk::alPriorCritic));
//        }



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
                try
                {
                    MTK_HANDLE_DIV0_INIT
                    {
                        mtk::mtk_qpid_stats::message_received(message.getContentSize(), mtk::mtk_qpid_stats::mt_full);
                        signalMessage.emit(message);
                    }
                    MTK_HANDLE_DIV0_END
                } catch (const Alarm& alError) {
                    Alarm  qpid_error(
                                MTK_HERE, "handle_qpid_exchange_receiver",
                                std::string("exception processing message"),
                                alPriorCritic
                        );
                    //qpid::types::Variant::Map mv;
                    //qpid::messaging::decode(message, mv);
                    //qpid_error.Add(mtk::Alarm(MTK_HERE, "handle_qpid_exchange_receiver", MTK_SS("msg>  " << mv), mtk::alPriorCritic));
                    qpid_error.Add(mtk::Alarm(MTK_HERE, "handle_qpid_exchange_receiver", MTK_SS("msg>  " << message.getContent()), mtk::alPriorCritic));
                    qpid_error.Add(alError);
                    mtk::AlarmMsg(qpid_error);
                }
                catch (std::exception& e) {
                    Alarm  qpid_error(MTK_HERE, "handle_qpid_exchange_receiver",
                                MTK_SS (" SUBJ>" << message.getSubject() << "  " << e.what()),
                                alPriorCritic);
                    //qpid::types::Variant::Map mv;
                    //qpid::messaging::decode(message, mv);
                    //qpid_error.Add(mtk::Alarm(MTK_HERE, "handle_qpid_exchange_receiver", MTK_SS("msg>  " << mv), mtk::alPriorCritic));
                    qpid_error.Add(mtk::Alarm(MTK_HERE, "handle_qpid_exchange_receiver", MTK_SS("msg>  " << message.getContent()), mtk::alPriorCritic));
                    mtk::AlarmMsg(qpid_error);
                } catch (...) {
                    Alarm  qpid_error(MTK_HERE, "handle_qpid_exchange_receiver",
                                MTK_SS (" SUBJ>" << message.getSubject() << "  ... unkown exception"),
                                alPriorCritic);
                    //qpid::types::Variant::Map mv;
                    //qpid::messaging::decode(message, mv);
                    //qpid_error.Add(mtk::Alarm(MTK_HERE, "handle_qpid_exchange_receiver", MTK_SS("msg>  " << mv), mtk::alPriorCritic));
                    qpid_error.Add(mtk::Alarm(MTK_HERE, "handle_qpid_exchange_receiver", MTK_SS("msg>  " << message.getContent()), mtk::alPriorCritic));
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











void    __internal_send_qpid_message___dont_use_it_directly(     mtk::CountPtr< mtk::mtkqpid_sender2 >      sender,
                                                                          qpid::types::Variant::Map&        content,
                                                                    const std::string&                      subject,
                                                                    const std::string&                      message_type,
                                                                    const std::string&                      control_fluct_key,
                                                                    int                                     real_time_level,
                                                                    mtk::nullable<mtk::DateTime>            depreciated_on
                                                                    )
{
    delayed_message_to_send_info  msg_info {sender, content, subject, message_type, control_fluct_key, depreciated_on};

    if      (real_time_level == 0)
        send_qpid_message_NOW(msg_info);
    else if (real_time_level == 1)
        send_qpid_message_NORMAL(msg_info);
    else if (real_time_level == 2)
        send_qpid_message_SLOW(msg_info);
    else
    {
            MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(20))           \
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "mtk_qpid", MTK_SS("incorrect real_time level " << message_type << "  " << real_time_level
                                << "  message not sent"), mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC           \
    }
}








};  // end namespace mtk


namespace {

void    send_qpid_message_NOW(  delayed_message_to_send_info&  msg_info  )
{
    static std::string  control_fluct_key="";
    MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(40))
        if(control_fluct_key == "")
            control_fluct_key = mtk::get_control_fluct_key();
    MTK_END_EXEC_MAX_FREC

    ++mtk::mtk_qpid_stats::num_messages_sent();
    if(mtk::mtk_qpid_stats::last_received_message() >  (mtk::dtToday_0Time() + mtk::dtHours(23) + mtk::dtMinutes(50)))
        mtk::mtk_qpid_stats::num_messages_sent_today() = 0;
    ++mtk::mtk_qpid_stats::num_messages_sent_today();


    mtk::msg::sub_control_fields    control_fields{msg_info.message_type, msg_info.control_fluct_key, mtk::dtNowLocal(),  msg_info.depreciated_on};
    qpid::types::Variant::Map       map_control_fields;
    mtk::msg::__internal_add2map(map_control_fields, control_fields);
    msg_info.content["_cf_"] = map_control_fields;
    qpid::messaging::Message msg;
    qpid::messaging::encode(msg_info.content, msg);
    msg.setSubject(MTK_SS(msg_info.subject));

    try {
        msg_info.sender->qpid_sender().send(msg);
    } catch(...)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(10))
            throw;
        MTK_END_EXEC_MAX_FREC
        return;
    }

}


void    send_qpid_message_NORMAL(  const delayed_message_to_send_info&  msg_info  )
{
    get_list_msg_to_send_NORMAL()->push_back(msg_info);
}



void    send_qpid_message_SLOW(  const delayed_message_to_send_info&  msg_info  )
{
    get_list_msg_to_send_SLOW()->push_back(msg_info);
}



void check_NORMAL_queue(void)
{
    static  int  messages_per_check_interval = -1;
    static  mtk::dtTimeQuantity      check_interval = mtk::dtHours(1);
    if(messages_per_check_interval < 0)
    {
        if(mtk::get_cli_srv() == "SRV")
        {
            messages_per_check_interval = 50;       //  500 msg/s
            check_interval = mtk::dtMilliseconds(10);
        }
        else
        {
            messages_per_check_interval = 1;        //  10 msg/s
            check_interval = mtk::dtMilliseconds(100);
        }
    }

    MTK_EXEC_MAX_FREC_S(check_interval)
    {
        int messages_sent = 0;
        while(get_list_msg_to_send_NORMAL()->size() != 0)
        {
            auto  msg_info = get_list_msg_to_send_NORMAL()->front();
            get_list_msg_to_send_NORMAL()->pop_front();
            send_qpid_message_NOW(msg_info);
            if(++messages_sent > messages_per_check_interval)
                break;
        }
    }
    MTK_END_EXEC_MAX_FREC
}

void check_SLOW_queue  (void)
{
    static  int  messages_per_check_interval = -1;
    static  mtk::dtTimeQuantity      check_interval = mtk::dtHours(1);
    static  int  messages_per_check_interval_client = -1;       //  to client and from client
    static  mtk::dtTimeQuantity      check_interval_client = mtk::dtHours(1);

    if(messages_per_check_interval < 0)
    {
        messages_per_check_interval = 10;       //  100 msg/s
        check_interval = mtk::dtMilliseconds(100);

        messages_per_check_interval_client = 2;        //  4 msg/s  from client
        check_interval_client = mtk::dtMilliseconds(500);

        //  sending from server to client, it will be used...  messages_per_check_interval_client  and  check_interval_client
    }

    if(mtk::get_cli_srv() == "CLI")
    {
        MTK_EXEC_MAX_FREC_S(check_interval_client)
        {
            int messages_sent = 0;
            while(get_list_msg_to_send_SLOW()->size() != 0)
            {
                auto  msg_info = get_list_msg_to_send_SLOW()->front();
                get_list_msg_to_send_SLOW()->pop_front();
                send_qpid_message_NOW(msg_info);
                if(++messages_sent > messages_per_check_interval_client)
                    break;
            }
        }
        MTK_END_EXEC_MAX_FREC
    }
    else
    {
        MTK_EXEC_MAX_FREC_S(check_interval)
        mtk::map<std::string, int/*msg sent*/>   map_cli_msg_sent;

        {
            auto it = get_list_msg_to_send_SLOW()->begin();
            while(it != get_list_msg_to_send_SLOW()->end())
            {
                auto  msg_info = *it;
                std::string  cli = msg_info.subject.substr(4, 1+msg_info.subject.find('.', msg_info.subject.find("CLI.")));

                if(map_cli_msg_sent.find(cli) == map_cli_msg_sent.end())
                    map_cli_msg_sent[cli]= 0;

                int max_messages = -1;
                if(cli != "")
                    max_messages = messages_per_check_interval_client;
                else
                    max_messages = messages_per_check_interval;

                if(map_cli_msg_sent[cli] > 10)
                {
                    MTK_EXEC_MAX_FREC_S_A(mtk::dtSeconds(30), A)
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "mtk_qpid", MTK_SS("too many messages queued for client " << cli <<  "   queued:" << map_cli_msg_sent[cli] <<  "   easy..."), mtk::alPriorError));
                    MTK_END_EXEC_MAX_FREC
                }

                if(map_cli_msg_sent[cli] < max_messages)
                {
                    it = get_list_msg_to_send_SLOW()->erase(it);
                    send_qpid_message_NOW(msg_info);
                    ++map_cli_msg_sent[cli];
                }
                else
                    ++it;
            }
        }
        MTK_END_EXEC_MAX_FREC

    }
}

};
