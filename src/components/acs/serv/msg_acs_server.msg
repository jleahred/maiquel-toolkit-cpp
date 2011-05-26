BEGIN_INIT

INCLUDES = ['#include "support/mtk_string.h"', '#include "components/msg_common_support.h"', '#include "components/acs/msg_acs.h"' ]
NAMESPACES = ['mtk', 'acs_server', 'msg']

END_INIT



//---------------------------------------------------------------------
//        
//
//---------------------------------------------------------------------


pub_add_user  [<  V:0, SUBJ:SYS.PUB.ACS_SYNC  >]
{
    login_confirmation  (lc)    :   mtk::acs::msg::res_login::IC_session_info
}


pub_del_user [<  V:0, SUBJ:SYS.PUB.ACS_SYNC  >]
{
    login_confirmation  (lc)    :   mtk::acs::msg::res_login::IC_session_info
}



//  partial user list sent  to synchornize   servers  <-->  acs


req_session_id_conf  [<  V:0, SUBJ:SYS.RQ.ACS_ASK_SESSID  >]
{
    session_id      (sid)   :       string
}

pub_partial_user_list_acs2serv  [<  V:0, SUBJ:SYS.PUB.ACS2SERV_SYNC  >]
{
    [list_login_confirmation] (slc)  :   mtk::acs::msg::res_login::IC_session_info
}
pub_partial_user_list_serv2acs  [<  V:0, SUBJ:SYS.PUB.SERV2ACS_SYNC  >]
{
    [list_login_confirmation] (slc)  :   mtk::acs::msg::res_login::IC_session_info
}





//---------------------------------------------------------------------
//      REQUEST LIST
//---------------------------------------------------------------------

req_user_list [<  V:0, SUBJ:SYS.REQ.ACS.USER_LIST  >]
{
    request_info    (ri)    :   mtk::msg::sub_request_info
}

res_user_list  [< V:0 , SUBJ:SYS.RS.${response_info.request_info.process_info.location.client_code}.${response_info.request_info.process_info.location.machine}.${response_info.request_info.process_info.process_uuid}.${response_info.request_info.req_id.sess_id}.${response_info.request_info.req_id.req_code} >]
{
    response_info                (ri)    :   mtk::msg::sub_r_response
    [list_login_confirmation]    (slc)   :   mtk::acs::msg::res_login::IC_session_info
}