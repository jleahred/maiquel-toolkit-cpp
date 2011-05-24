#ifndef __trd_cli_account_manager__
#define __trd_cli_account_manager__



#include "support/list.hpp"
#include "components/trading/msg_trd_common.h"






namespace mtk{namespace trd{

    
    
    namespace  account_manager {

        //  INPUT


        //  OUTPUT


        //  ACCESS
        mtk::list<mtk::trd::msg::sub_account_info>      get_accounts(void);
        
        
        //  hooks

        
        
    };  //  namespace  trd_cli_account_manager {


};   //  namespace mtk
};   //  namespace trd


#endif // __trd_cli_account_manager__


 
