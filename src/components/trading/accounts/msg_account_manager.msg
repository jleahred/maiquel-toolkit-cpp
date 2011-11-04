BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'account', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "components/trading/msg_trd_common.h"' , '#include "components/acs/msg_acs.h"' ]

END_INIT





sub_grant  [<KEY:key>]
{
    key  [< LessOP:1 >]
    {
        market      (mk)        :   string
        account     (acc)       :   mtk::trd::msg::sub_account_info

    }
    type        (ty)    : string        //  F   C  V   (Full  Cancel  View    <deleted>)
}





//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------




rq_accounts  [<  QE:CLI_MK, SUBJ:MK.${request_info.process_info.location.broker_code}.ALL.ACCOUNT.RQGRANTS  >]
{
    request_info    (rqi)       :   mtk::msg::sub_request_info
}


conf_add_accounts [<  QE:CLI_MK, SUBJ:CLI.${gen_response_location.broker_code}.${gen_response_location.session_id}.CONF_ADD_ACOUNTS  >]
    //  this "generic" subject let us send accounts with no request from user
    //  it's possible receive account several times
{
    gen_response_location   (grl)   :   mtk::msg::sub_gen_response_location

    [grant_list]            (gl)    :   sub_grant       //  grant type is empty to revoque permision
}



//--------------------------------------------------------------------------------------
//      recovery messages
//  when account server manager starts, it will send   pub_accmgr_init
//  clients has the oportunity to send an specific request to load or reload the account
//  list managed by this server
//  instead of requesting to all servers, as rq_accounts, rq_accounts_oninit is a specific
//  request to one specific server
//--------------------------------------------------------------------------------------

pub_accmgr_init [<  QE:CLI_MK, SUBJ:CLI.ALL.ACCMGRINIT   >]
{
    process_info                (pi)        :       mtk::msg::sub_process_info
    request_sufix_subjetc       (rss)       :       string
}


rq_accounts_oninit  [<  QE:CLI_MK, SUBJ:MK.${request_info.process_info.location.broker_code}.ALL.${request_sufix_subjetc}.ACCOUNTS.RQINIT   >]  // mising market on subject
{
    request_info                (rqi)       :   mtk::msg::sub_request_info
    request_sufix_subjetc       (rss)       :   string
}
