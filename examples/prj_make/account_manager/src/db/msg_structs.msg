BEGIN_INIT

INCLUDES = ['#include "support/mtk_string.h"', '#include "components/trading/msg_trd_common.h"' , '#include "components/trading/accounts/msg_account_manager.h"' ]
NAMESPACES = ['accmgr', 'msg']

END_INIT



//---------------------------------------------------------------------
//        
//
//---------------------------------------------------------------------




sub_user_info  [< V:0, KEY:name >]
{
    name        (nm)    : string
    created     (cdt)   : date_time
    client_code (cc)    : string
    
    [grant_list](gl)    : mtk::trd::account::msg::sub_grant
}

