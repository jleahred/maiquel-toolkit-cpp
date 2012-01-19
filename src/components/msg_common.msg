BEGIN_INIT

INCLUDES = ['#include "support/mtk_string.h"', '#include "msg_common_support.h"' ]
NAMESPACES = ['mtk', 'msg']

END_INIT



//---------------------------------------------------------------------
//        PROCESS INFO
//
//---------------------------------------------------------------------

sub_location  [< >]
{
    broker_code     (bc)  : string          //  on clients, it will be the client code (used in broker filters)
    machine         (mc)  : string
}


sub_process_info  [< >]
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

sub_control_fluct    [< >]
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

sub_request_id   [< >]
{
    session_id  (sid) :  string
    req_code    (rqc) :  string
}


sub_request_info [< >]
{
    req_id              (rqid)  :   sub_request_id
    process_info        (pi)    :   sub_process_info
}


//---------------------------------------------------------------------
//        MULTI-RESPONSE
//---------------------------------------------------------------------


sub_r_response [< >]
{
    process_info       (pi)     :   sub_process_info        //  process sending the response

    request_info       (rqi)    :   sub_request_info
    seq_number         (sqn)    :   int16       //  it will start with 0
    is_last_response   (lr)     :   bool
}


//---------------------------------------------------------------------
//        NON SPECIFIC RESPONSE LOCATION
//---------------------------------------------------------------------

//  it will be used in generic responses subject
//  letting to send "responses" or confirmations not requested
sub_gen_response_location [< >]
{
    session_id      (sid) :     string
    broker_code     (bc)  :     string      //  on clients, it will be the client code used on filter
}



//---------------------------------------------------------------------
//        COMMON TRADING  AND  PRICES
//---------------------------------------------------------------------


//  product identification

sub_product_code  [< >]
{
    market      (mk)   :  string
    product     (pr)   :  string
}

