#include "mtk_qpid_stats.h"


#include <iostream>
#include <iomanip>

#include "support/mtk_string.h"
#include "support/exec_max_frec.h"


namespace mtk
{
    std::string  control_fluct_key;
    std::string  get_control_fluct_key(void)
    {
        return control_fluct_key;
    }

    void         set_control_fluct_key(const std::string& _control_fluct_key)
    {
        control_fluct_key = _control_fluct_key;
    }


namespace mtk_qpid_stats {



//  stats info
long __num_messages_received=0;
long __num_messages_sent=0;

long __num_messages_received_today=0;
long __num_messages_sent_today=0;

long __num_created_suscriptions=0;
long __num_deleted_suscriptions=0;

long __num_created_suscriptions_no_parsing=0;
long __num_deleted_suscriptions_no_parsing=0;


long __num_created_sessions=0;
long __num_deleted_sessions=0;

long __num_created_senders=0;
long __num_deleted_senders=0;

long __num_created_receivers=0;
long __num_deleted_receivers=0;

long  __num_restored_sessions=0;


long& num_messages_received(void)
{
    static  long*  value = new long(0);
    return *value;
};
long& num_messages_sent(void)
{
    static  long*  value = new long(0);
    return *value;
};

long& num_messages_received_today(void)
{
    static  long*  value = new long(0);
    return *value;
};
long& num_messages_sent_today(void)
{
    static  long*  value = new long(0);
    return *value;
};


long& num_created_suscriptions(void)
{
    static  long*  value = new long(0);
    return *value;
};
long& num_deleted_suscriptions(void)
{
    static  long*  value = new long(0);
    return *value;
};

long& num_created_suscriptions_no_parsing(void)
{
    static  long*  value = new long(0);
    return *value;
};
long& num_deleted_suscriptions_no_parsing(void)
{
    static  long*  value = new long(0);
    return *value;
};


long& num_created_sessions(void)
{
    static  long*  value = new long(0);
    return *value;
};
long& num_deleted_sessions(void)
{
    static  long*  value = new long(0);
    return *value;
};



long& num_created_senders(void)
{
    static  long*  value = new long(0);
    return *value;
};

long& num_deleted_senders(void)
{
    static  long*  value = new long(0);
    return *value;
};


long& num_created_receivers(void)
{
    static  long*  value = new long(0);
    return *value;
};

long& num_deleted_receivers(void)
{
    static  long*  value = new long(0);
    return *value;
};



long& num_restored_sessions(void)
{
    static  long*  value = new long(0);
    return *value;
};





mtk::DateTime&  last_received_message(void)
{
    static mtk::DateTime*  result = new mtk::DateTime{mtk::dtNowLocal()};

    return *result;
};



std::string get_mtk_qpid_stats_string(void) {
    return MTK_SS(
        "mtkqpid_msgrecv:  " << num_messages_received() << std::endl <<
        "mtkqpid_msgsent:  " << num_messages_sent() << std::endl <<

        "mtkqpid_msgrecv_today:  " << num_messages_received_today() << std::endl <<
        "mtkqpid_msgsent_today:  " << num_messages_sent_today() << std::endl <<

        "mtkqpid_newsuscr: " << num_created_suscriptions() << std::endl <<
        "mtkqpid_delsuscr: " << -1*num_deleted_suscriptions() << std::endl <<

        "mtkqpid_newsusnp: " << num_created_suscriptions_no_parsing() << std::endl <<
        "mtkqpid_delsusnp: " << -1*num_deleted_suscriptions_no_parsing() << std::endl <<

        "mtkqpid_newsess:  " << num_created_sessions() << std::endl <<
        "mtkqpid_delsess:  " << -1*num_deleted_sessions() << std::endl <<

        "mtkqpid_newsenders:  " << num_created_senders() << std::endl <<
        "mtkqpid_delsenders:  " << -1*num_deleted_senders() << std::endl <<

        "mtkqpid_newrecev:  " << num_created_receivers() << std::endl <<
        "mtkqpid_delrecev:  " << -1*num_deleted_receivers()  << std::endl <<

        "mtkqpid_rest_sess: " << num_restored_sessions()
    );;
}

//  stats info


void    message_received(size_t size_in_bytes, en_msg_type  mt)
{
    static mtk::dtDateTime lasts_sent_stats = mtk::dtNowLocal();
    static mtk::dtDateTime last_sec_verif = mtk::dtNowLocal();


    static size_t accumulated_bytes_inlast_sec = 0;
    static size_t max_bs  = 0;
    static int    num_messages  = 0;
    static int    max_num_messages  = 0;

    static size_t accumulated_bytes_prices_inlast_sec = 0;
    static size_t max_bs_prices  = 0;
    static int    num_messages_prices  = 0;
    static int    max_num_messages_prices  = 0;

//    static size_t accumulated_bytes_lasts_inlast_sec = 0;
//    static size_t max_bs_last  = 0;
//    static int    num_messages_lasts  = 0;
//    static int    max_num_messages_lasts  = 0;

    mtk::DateTime  now = mtk::dtNowLocal();
    if(last_sec_verif < now - mtk::dtSeconds(1))
    {
        if(accumulated_bytes_inlast_sec > max_bs)
            max_bs = accumulated_bytes_inlast_sec;
        accumulated_bytes_inlast_sec = 0;
        if(num_messages >  max_num_messages)
            max_num_messages = num_messages;
        num_messages = 0;

        if(accumulated_bytes_prices_inlast_sec > max_bs_prices)
            max_bs_prices = accumulated_bytes_prices_inlast_sec;
        accumulated_bytes_prices_inlast_sec = 0;

        if(num_messages_prices >  max_num_messages_prices)
            max_num_messages_prices = num_messages_prices;
        num_messages_prices = 0;

//        if(accumulated_bytes_lasts_inlast_sec > max_bs_last)
//            max_bs_last = accumulated_bytes_lasts_inlast_sec;
//        accumulated_bytes_lasts_inlast_sec = 0;
//
//        if(num_messages_lasts >  max_num_messages_lasts)
//            max_num_messages_lasts = num_messages_lasts;
//        num_messages_lasts = 0;

        last_sec_verif = now;
    }


    if(mt == mt_prices)
    {
        accumulated_bytes_prices_inlast_sec += size_in_bytes;
        ++num_messages_prices;
    }
//    else if(mt == mt_last)
//    {
//        accumulated_bytes_lasts_inlast_sec += size_in_bytes;
//        ++num_messages_lasts;
//    }
    else    //  best and last are called twice, here we remove one of them
    {
        accumulated_bytes_inlast_sec += size_in_bytes;
        ++num_messages;
    }


    if(lasts_sent_stats < now - mtk::dtMinutes(1))
    {
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "stats mtk_qpid",
                    MTK_SS( "maxs/minut  " <<
                        "all: "     << std::fixed <<  std::setprecision(1) << double(max_bs)       /1024. << "Kb/s "  << max_num_messages        << "#msg/s   "  <<
                        "prices: "  << std::fixed <<  std::setprecision(1) << double(max_bs_prices)/1024. << "Kb/s "  << max_num_messages_prices << "#msg/s   "
                        //"lasts: "  << std::fixed <<  std::setprecision(1) << double(max_bs_last) /1024. << "Kb/s "  << max_num_messages_lasts << "#msg/s   "
                    )
                    , mtk::alPriorStats));
        lasts_sent_stats = now;
        accumulated_bytes_inlast_sec = 0;
        num_messages =0;
        accumulated_bytes_prices_inlast_sec = 0;
        num_messages_prices =0;
//        accumulated_bytes_lasts_inlast_sec = 0;
//        num_messages_lasts  = 0;
        max_bs  = 0;
        max_bs_prices  = 0;
//        max_bs_last  = 0;
        max_num_messages = 0;
        max_num_messages_prices = 0;
//        max_num_messages_lasts = 0;
    }
}

void    message_received_for_message_size(size_t size_in_bytes, const std::string& message_type)
{
    static std::string   biggest_message_type;
    static size_t        biggest_message_size;

    if(biggest_message_size < size_in_bytes)
    {
        biggest_message_type = message_type;
        biggest_message_size = size_in_bytes;
    }

    MTK_EXEC_MAX_FREC_NO_FIRST_S(mtk::dtMinutes(5))
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "stats mtk_qpid",
                    MTK_SS( "biggest: "<< biggest_message_type << "  " <<  biggest_message_size << "bytes")
                    , mtk::alPriorStats));

        biggest_message_type = "";
        biggest_message_size = 0;
    MTK_END_EXEC_MAX_FREC
}



}       //namespace mtk
}       //namespace mtk_qpid_stats

