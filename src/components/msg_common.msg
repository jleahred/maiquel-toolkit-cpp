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
    location        (l)     :   sub_location
    process_name    (pn)    :   string
    process_uuid    (pi)    :   string
    version         (pv)    :   string
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
    sess_id   (sid) :  string
    req_code  (rqc) :  string
}


sub_request_info [< V:0 >]   
{
    req_id              (rid)   :   sub_request_id
    process_info        (pi)    :   sub_process_info
}


//---------------------------------------------------------------------
//        MULTI-RESPONSE
//---------------------------------------------------------------------


sub_r_response [< V:0 >]   
{
    request_info       (ri)     :   sub_request_info
    sec_number         (sq)     :   int16       //  it will start with 0
    is_last_response   (lr)     :   bool
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

