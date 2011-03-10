BEGIN_INIT

INCLUDES = ['#include "support/mtk_string.h"', '#include "msg_common_support.h"' ]
NAMESPACES = ['mtk', 'msg']

END_INIT





sub_process_location  [<V:0>]
{
    location        (lc)  : string
    machine         (mc)  : string
    process_name    (pn)  : string
    process_uuid    (pi)  : string
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
    process_location    (pl)    :   sub_process_location
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

sub_single_product_code   [<V:0>]
{
    market   (mk)   :  string    
    product  (pr)   :  string    
    code     (cd)   :  string    [optional]    // codificated as...
}


sub_product_code    [<V:0>]
{
    sys_code       (spc)   :  sub_single_product_code
    aditional_code (apc)   :  sub_single_product_code   [optional]
    description    (des)   :  string                    [optional]
}




