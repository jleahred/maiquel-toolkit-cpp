#ifndef __mtk_qpid_stats_h__
#define __mtk_qpid_stats_h__


#include <string>
#include "support/date_time.h"


namespace mtk
{

namespace mtk_qpid_stats {



//  stats info
long& num_messages_received                  (void);
long& num_messages_sent                      (void);

long& num_messages_received_today            (void);
long& num_messages_sent_today                (void);


long& num_created_suscriptions               (void);
long& num_deleted_suscriptions               (void);

long& num_created_suscriptions_no_parsing    (void);
long& num_deleted_suscriptions_no_parsing    (void);


long& num_created_sessions                   (void);
long& num_deleted_sessions                   (void);

long& num_created_senders                    (void);
long& num_deleted_senders                    (void);

long& num_created_receivers                  (void);
long& num_deleted_receivers                  (void);

long& num_restored_sessions(void);



std::string get_mtk_qpid_stats_string        (void);

mtk::DateTime&  last_received_message     (void);



//  Bandwith used
enum  en_msg_type  {  mt_bests, mt_last, mt_full  };
void    message_received(size_t size_in_bytes, en_msg_type  mt);
void    message_received_for_message_size(size_t size_in_bytes, const std::string& message_type);


}

//  stats info



}


#endif // __mtk_qpid_stats_h__
