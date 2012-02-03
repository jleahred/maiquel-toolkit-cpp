#include "mtk_qpid_stats.h"


#include <iostream>
#include "support/mtk_string.h"


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





mtk::DateTime  __last_received_message=mtk::dtNowLocal();

mtk::DateTime&  last_received_message(void) { return __last_received_message; };



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



}       //namespace mtk
}       //namespace mtk_qpid_stats

