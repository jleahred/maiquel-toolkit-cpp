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



req_login_key [< V:0, SUBJ:RQ.${request_info.process_location.location.client_code}.ACS.RQK >]
{
    request_info    (ri)        :   mtk::msg::sub_request_info
    
    user_name       (u)         :   string
}

res_login_key [< V:0 , SUBJ:RS.${response_info.request_info.process_location.location.client_code}.${response_info.request_info.process_location.location.machine}.${response_info.request_info.process_location.process_uuid}.${response_info.request_info.req_id.sess_id}.${response_info.request_info.req_id.req_code}.RSK >]
{
    response_info   (ri)    :   mtk::msg::sub_r_response
    key             (k)     :   string
}


req_login [< V:0, SUBJ:RQ.${request_info.process_location.location.client_code}.ACS.RQL >]
{
    request_info    (ri)        :   mtk::msg::sub_request_info
    
    user_name       (u)         :   string
    key             (k)         :   string
    coded_pass      (cp)        :   string
}



res_login   [< V:0 , SUBJ:RS.${response_info.request_info.process_location.location.client_code}.${response_info.request_info.process_location.location.machine}.${response_info.request_info.process_location.process_uuid}.${response_info.request_info.req_id.sess_id}.${response_info.request_info.req_id.req_code}.LRES >]
{
    response_info   (ri)        :   mtk::msg::sub_r_response
    
    login_response_info (lr)  [< V:0 >]
    {
        user_name      (u)      :   string      //  empty if login rejected
        session_id     (si)     :   string
    }
}




conf_logout [< V:0 , SUBJ:CONF.${location.client_code}.${location.machine}.${session_id}.LOGOUT >]
{
    location        (lc)    :   mtk::msg::sub_location
    session_id      (si)    :   string
    
    description     (si)    :   string
}


req_logout [< V:0, SUBJ:RQ.${request_info.process_location.location.client_code}.ACS.RQK >]
{
    request_info    (ri)        :   mtk::msg::sub_request_info
}






//---------------------------------------------


req_change_password [< V:0, SUBJ:RQ.${request_info.process_location.location.client_code}.ACS.RQCP >]
{
    request_info    (ri)        :   mtk::msg::sub_request_info
    
    user_name       (un)        :   string
    key             (k)         :   string
    old_password    (op)        :   string
    [new_password]  (np)        :   int32
}




res_change_password    [< V:0 , SUBJ:RS.${response_info.request_info.process_location.location.client_code}.${response_info.request_info.process_location.location.machine}.${response_info.request_info.process_location.process_uuid}.${response_info.request_info.req_id.sess_id}.${response_info.request_info.req_id.req_code}.LCP >]
{
    response_info   (ri)        :   mtk::msg::sub_r_response
    
    change_password_info (cp)  [< V:0 >]
    {
        accepted    (a)         :    bool
    }
}
