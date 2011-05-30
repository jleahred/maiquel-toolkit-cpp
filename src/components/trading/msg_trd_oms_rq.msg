BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "msg_trd_common.h"', '#include "msg_trd_cli_ls.h"']

END_INIT








oms_RQ_NW_LS  [< V:0, I:RQ_NW_LS >]  
{
    reject_description   (rjd)  :  string  //  empty means ok
}

oms_RQ_MD_LS  [< V:0, I:RQ_MD_LS >]  
{
    reject_description   (rjd)  :  string  //  empty means ok
}

oms_RQ_CC_LS  [< V:0, I:RQ_CC_LS >]  
{
    reject_description   (rjd)  :  string  //  empty means ok
}


