BEGIN_INIT

NAMESPACES = ['mtk', 'acs', 'msg']
INCLUDES   = ['#include "components/msg_common.h"']

END_INIT



/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////





//-------------------------------------------------------------------
//
//  On next request, we will not have the sessionid
//  This field will be filled with   "provisional"
//  client code location, has to be filled with a value readed from file
//  This value has to match with configured value on system
//
//-------------------------------------------------------------------



req_login_key [< QE:ALL_GS, RT:1, SUBJ:GS.${request_info.process_info.location.broker_code}.ACS.RQK >]
{
    request_info    (rqi)        :   mtk::msg::sub_request_info

    user_name       (un)         :   string
}

res_login_key [< QE:ALL_GS, RT:0, SUBJ:CLI.${response_info.request_info.process_info.location.broker_code}.${response_info.request_info.process_info.location.machine}.${response_info.request_info.process_info.process_uuid}.${response_info.request_info.req_id.session_id}.${response_info.request_info.req_id.req_code}.RSK >]
{
    response_info   (rsi)   :   mtk::msg::sub_r_response
    key             (k)     :   string
}


req_login [< QE:ALL_GS, RT:1, SUBJ:GS.${request_info.process_info.location.broker_code}.ACS.RQL >]
{
    request_info    (rqi)       :   mtk::msg::sub_request_info

    user_name       (un)        :   string
    key             (k)         :   string
    coded_pass      (cpw)       :   string
}



res_login   [< QE:ALL_GS, RT:0, SUBJ:CLI.${response_info.request_info.process_info.location.broker_code}.${response_info.request_info.process_info.location.machine}.${response_info.request_info.process_info.process_uuid}.${response_info.request_info.req_id.session_id}.${response_info.request_info.req_id.req_code}.RESLOGIN >]
{
    response_info   (rsi)       :   mtk::msg::sub_r_response

    session_info (lr)  [<  >]
    {
        user_name      (un)     :   string      //  empty if login rejected
        client_code    (cc)     :   string
        session_id     (sid)    :   string
    }
}




conf_logout [< QE:ALL_GS, RT:0, SUBJ:CLI.${location.broker_code}.${location.machine}.${session_id}.CONFLOGOUT >]
{
    location        (lc)    :   mtk::msg::sub_location
    session_id      (sid)   :   string

    description     (desc)  :   string
}


req_logout [< QE:ALL_GS, RT:0, SUBJ:GS.${request_info.process_info.location.broker_code}.ACS.RQLO >]
{
    request_info    (rqi)       :   mtk::msg::sub_request_info
}






//---------------------------------------------


req_change_password [< QE:ALL_GS, RT:1, SUBJ:GS.${request_info.process_info.location.broker_code}.ACS.RQCP >]
{
    request_info    (rqi)       :   mtk::msg::sub_request_info

    user_name       (un)        :   string
    key             (k)         :   string
    old_password    (opw)       :   string
    [new_password]  (npw)       :   int32
}




res_change_password    [< QE:ALL_GS, RT:1, SUBJ:CLI.${response_info.request_info.process_info.location.broker_code}.${response_info.request_info.process_info.location.machine}.${response_info.request_info.process_info.process_uuid}.${response_info.request_info.req_id.session_id}.${response_info.request_info.req_id.req_code}.RESLCP >]
{
    response_info   (rsi)       :   mtk::msg::sub_r_response

    change_password_info (cpi)  [<  >]
    {
        accepted    (a)         :    bool
    }
}
