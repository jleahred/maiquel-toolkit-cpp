#ifndef __trd_cli_ord_book_h_
#define __trd_cli_ord_book_h_

#include <string>


#include "msg_acs_server.h"


namespace mtk{namespace msg { class sub_request_info;  } };



namespace mtk{namespace acs_server {

    
    
    namespace  synchr {


        void  init(void);
        
        //  INPUT


        //  OUTPUT
        mtk::CountPtr<mtk::Signal<> >   get_signal_received_user_list();


        //  ACCESS
        mtk::acs::msg::res_login::IC_session_info               get_session_info_for_session_id  ( const std::string& session_id);      //  it returns emtpy string if not found
        mtk::list<mtk::acs::msg::res_login::IC_session_info>    bad_performance_get_sessions_info( const std::string& user_name); 
        
        
        //  hooks
        
        
    };  //  namespace  synchr {


};   //  namespace acs_server
};   //  namespace trd


#endif // __trd_cli_ord_book_h__


 
 
