BEGIN_INIT

INCLUDES = ['#include "support/mtk_string.h"', '#include "msg_common_support.h"' ]
NAMESPACES = ['mtk', 'msg']

END_INIT



//---------------------------------------------------------------------
//        PROCESS INFO
//
//---------------------------------------------------------------------

sub_location  [<V:0>]
{
    client_code     (cc)  : string
    machine         (mc)  : string
}


sub_process_info  [<V:0>]
{
    location        (lc)    :   sub_location
    process_name    (pn)    :   string
    process_uuid    (pui)   :   string
    version         (ver)   :   string
}





//---------------------------------------------------------------------
//        CONTROL FLUCT
//
//      Next submessage has to be used only on real time messages
//---------------------------------------------------------------------

sub_control_fluct    [<V:0>]
{
    key         (k)    :   string
    datetime    (dt)   :   date_time
    
    #send [{  const_cast<sub_control_fluct*>(this)->datetime = mtk::dtNowLocal();    }]
}





//---------------------------------------------------------------------
//        REQUEST 
//
//  could be with no response as request new order
//---------------------------------------------------------------------

sub_request_id   [<V:0>]
{
    session_id  (sid) :  string
    req_code    (rqc) :  string
}


sub_request_info [< V:0 >]   
{
    req_id              (rqid)  :   sub_request_id
    process_info        (pi)    :   sub_process_info
}


//---------------------------------------------------------------------
//        MULTI-RESPONSE
//---------------------------------------------------------------------


sub_r_response [< V:0 >]   
{
    request_info       (rqi)    :   sub_request_info
    seq_number         (sqn)    :   int16       //  it will start with 0
    is_last_response   (lr)     :   bool
}


//---------------------------------------------------------------------
//        NON SPECIFIC RESPONSE LOCATION
//---------------------------------------------------------------------

//  it will be used in generic responses subject
//  letting to send "responses" or confirmations not requested
//  ex:  CF_ST_LS  [< V:0,  I:CF_XX_LS,  SUBJ:CONF.${gen_response_location.client_code}.STATUS_CF.${gen_response_location.session_id}  >]
sub_gen_response_location [< V:0 >]   
{
    session_id      (sid) :     string
    client_code     (cc)  :     string
}



//---------------------------------------------------------------------
//        COMMON TRADING  AND  PRICES
//---------------------------------------------------------------------


//  product identification

sub_product_code  [<V:0>]
{
    market      (mk)   :  string    
    product     (pr)   :  string    
}

