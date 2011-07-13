BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'account', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "components/trading/msg_trd_common.h"' , '#include "components/acs/msg_acs.h"' ]

END_INIT





sub_grant  [<V:0>]
{
    key  [< V:0,  LessOP:1 >]
    {
        market      (mk)        :   string
        account     (acc)       :   mtk::trd::msg::sub_account_info
        
    }
    type        (ty)    : string        //  F   C  V   (Full  Cancel  View    <deleted>)
}





//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------




rq_accounts  [<  V:0, SUBJ:RQ.${request_info.process_info.location.client_code}.ACCOUNT.GRANTS  >]
{
    request_info    (rqi)       :   mtk::msg::sub_request_info
}


add_accounts [<  V:0, SUBJ:CONF.${session_info.client_code}.ACCOUNTS.${session_info.session_id}   >]
{
    session_info    (si)    :   mtk::acs::msg::res_login::IC_session_info

    [grant_list]    (grl)   :   sub_grant       //  grant type is empty to revoque permision
}



//--------------------------------------------------------------------------------------
//      recovery messages
//  when account server manager starts, it will send   pub_accmgr_init
//  clients has the oportunity to send an specific request to load or reload the account
//  list managed by this server
//  instead of requesting to all servers, as rq_accounts, rq_accounts_oninit is a specific
//  request to one specific server
//--------------------------------------------------------------------------------------

pub_accmgr_init [<  V:0, SUBJ:ADM.ALL.ACCMGRINIT   >]
{
    process_info                (pi)        :       mtk::msg::sub_process_info
    request_sufix_subjetc       (rss)       :       string
}


rq_accounts_oninit  [<  V:0, SUBJ:ADM.ALL.ACCMGRINIT.${request_sufix_subjetc}   >]
{
    request_info                (rqi)       :   mtk::msg::sub_request_info
    request_sufix_subjetc       (rss)       :   string
}