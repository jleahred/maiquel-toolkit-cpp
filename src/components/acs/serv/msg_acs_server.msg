BEGIN_INIT

INCLUDES = ['#include "support/mtk_string.h"', '#include "components/msg_common_support.h"', '#include "components/acs/msg_acs.h"' ]
NAMESPACES = ['mtk', 'acs_server', 'msg']

END_INIT



//---------------------------------------------------------------------
//
//
//---------------------------------------------------------------------


pub_add_user  [<  QE:ALL_GS, SUBJ:SYS.SRV.ACS_SYNC.AU  >]
{
    login_confirmation  (lgc)    :   mtk::acs::msg::res_login::IC_session_info
}


pub_del_user [<  QE:ALL_GS, SUBJ:SYS.SRV.ACS_SYNC.DU  >]
{
    login_confirmation  (lgc)    :   mtk::acs::msg::res_login::IC_session_info
}



//  partial user list sent  to synchornize   servers  <-->  acs


req_session_id_conf  [<  QE:ALL_GS, SUBJ:GS.ACS.ASK_SESSID  >]
{
    session_id          (sid)   :       string

    from                (from)  :       mtk::msg::sub_process_info
}

pub_partial_user_list_acs2serv  [<  QE:ALL_GS, SUBJ:SYS.SRV.ACS_SYNC.PUL  >]
{
    [list_login_confirmation] (slc)  :   mtk::acs::msg::res_login::IC_session_info
}
pub_partial_user_list_serv2acs  [<  QE:ALL_GS, SUBJ:SYS.ACS.ACS_SYNC.PUL  >]
{
    [list_login_confirmation] (slc)  :   mtk::acs::msg::res_login::IC_session_info
}





//---------------------------------------------------------------------
//      REQUEST LIST
//---------------------------------------------------------------------

req_user_list [<  QE:ALL_GS, SUBJ:GS.ACS.RQ_USER_LIST  >]
{
    request_info    (rqi)    :   mtk::msg::sub_request_info
}

res_user_list  [< QE:ALL_GS, SUBJ:SYS.SRV.ACS.${response_info.request_info.process_info.location.client_code}.${response_info.request_info.process_info.location.machine}.${response_info.request_info.process_info.process_uuid}.${response_info.request_info.req_id.session_id}.${response_info.request_info.req_id.req_code}.RSUL >]
{
    response_info                (rsi)   :   mtk::msg::sub_r_response
    [list_login_confirmation]    (slc)   :   mtk::acs::msg::res_login::IC_session_info
}
