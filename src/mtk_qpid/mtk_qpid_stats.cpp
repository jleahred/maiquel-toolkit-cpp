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



long& num_messages_received(void) { return __num_messages_received; };
long& num_messages_sent(void) { return __num_messages_sent; };
long& num_created_suscriptions(void) { return __num_created_suscriptions; };
long& num_deleted_suscriptions(void) { return __num_deleted_suscriptions; };

long& num_created_suscriptions_no_parsing(void) { return __num_created_suscriptions_no_parsing; };
long& num_deleted_suscriptions_no_parsing(void) { return __num_deleted_suscriptions_no_parsing; };


long& num_created_sessions(void) { return __num_created_sessions; };
long& num_deleted_sessions(void) { return __num_deleted_sessions; };



long& num_created_senders(void) { return __num_created_senders; };
long& num_deleted_senders(void) { return __num_deleted_senders; };


long& num_created_receivers(void) { return __num_created_receivers; };
long& num_deleted_receivers(void) { return __num_deleted_receivers; };


mtk::DateTime  __last_received_message=mtk::dtNowLocal();

mtk::DateTime&  last_received_message(void) { return __last_received_message; };



std::string get_mtk_qpid_stats_string(void) {
    return MTK_SS(
        "mtkqpid_msgrecv:  " << num_messages_received() << std::endl <<
        "mtkqpid_msgsent:  " << num_messages_sent() << std::endl <<

        "mtkqpid_newsuscr: " << num_created_suscriptions() << std::endl <<
        "mtkqpid_delsuscr: " << num_deleted_suscriptions() << std::endl <<

        "mtkqpid_newsusnp: " << num_created_suscriptions_no_parsing() << std::endl <<
        "mtkqpid_delsusnp: " << num_deleted_suscriptions_no_parsing() << std::endl <<

        "mtkqpid_newsess:  " << num_created_sessions() << std::endl <<
        "mtkqpid_delsess:  " << num_deleted_sessions() << std::endl <<

        "mtkqpid_newsenders:  " << num_created_senders() << std::endl <<
        "mtkqpid_delsenders:  " << num_deleted_senders() << std::endl <<

        "mtkqpid_newrecev:  " << num_created_receivers() << std::endl <<
        "mtkqpid_delrecev:  " << num_deleted_receivers()
    );
}

//  stats info



}       //namespace mtk
}       //namespace mtk_qpid_stats

