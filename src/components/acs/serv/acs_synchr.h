#ifndef __trd_cli_ord_book_h_
#define __trd_cli_ord_book_h_

#include <string>


namespace mtk{namespace msg { class sub_request_info;  } };



namespace mtk{namespace acs_server {

    
    
    namespace  synchr {


        void  init(void);
        
        //  INPUT


        //  OUTPUT


        //  ACCESS
        std::string  get_user_for_session_id ( const std::string& session_id);      //  it returns emtpy string if not found
        
        
        //  hooks
        
        
    };  //  namespace  synchr {


};   //  namespace acs_server
};   //  namespace trd


#endif // __trd_cli_ord_book_h__


 
 
