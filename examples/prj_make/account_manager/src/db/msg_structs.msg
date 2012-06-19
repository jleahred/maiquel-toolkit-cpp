BEGIN_INIT

INCLUDES = ['#include "support/mtk_string.h"', '#include "components/trading/msg_trd_common.h"' , '#include "components/trading/accounts/msg_account_manager.h"' ]
NAMESPACES = ['accmgr', 'msg']

END_INIT



//---------------------------------------------------------------------
//
//
//---------------------------------------------------------------------




sub_user_info  [< KEY:name >]
{
    name        (nm)    : string
    created     (cdt)   : date_time
    client_code (cc)    : string

    [grant_list](gl)    : mtk::trd::account::msg::sub_grant
}


sub_oms_account_info  [<KEY:account>]
{
    account                 (acc)       :   mtk::trd::msg::sub_account_info

    oms_additional_info     (oai)       :   string
}
