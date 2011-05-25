#ifndef __trd_cli_ord_book_h_
#define __trd_cli_ord_book_h_

#include <string>


namespace mtk{namespace msg { class sub_request_info;  } };



namespace mtk{namespace adm {

    
    
    namespace  acs_synchr {


        void  init(void);
        
        //  INPUT


        //  OUTPUT


        //  ACCESS
        std::string  get_user_for_session_id ( const std::string& session_id);
        
        
        //  hooks
        
        
    };  //  namespace  acs_synchr {


};   //  namespace adm
};   //  namespace trd


#endif // __trd_cli_ord_book_h__


 
 
