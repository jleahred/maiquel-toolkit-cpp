#include "mtk_qpid_stats.h"


#include <iostream>
#include "support/mtk_string.h"


namespace mtk
{
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



long& num_messages_received(void) { return __num_messages_received; };
long& num_messages_sent(void) { return __num_messages_sent; };
long& num_created_suscriptions(void) { return __num_created_suscriptions; };
long& num_deleted_suscriptions(void) { return __num_deleted_suscriptions; };

long& num_created_suscriptions_no_parsing(void) { return __num_created_suscriptions_no_parsing; };
long& num_deleted_suscriptions_no_parsing(void) { return __num_deleted_suscriptions_no_parsing; };


long& num_created_sessions(void) { return __num_created_sessions; };
long& num_deleted_sessions(void) { return __num_deleted_sessions; };


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
        "mtkqpid_delsess:  " << num_deleted_sessions() 
        
    );
}

//  stats info



}       //namespace mtk
}       //namespace mtk_qpid_stats

