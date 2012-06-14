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
    static  mtk::Signal<bool>  result;
    return result;
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
