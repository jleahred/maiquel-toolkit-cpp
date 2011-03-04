BEGIN_INIT

INCLUDES = ['#include "support/mtk_string.h"', '#include "msg_common_support.h"' ]
NAMESPACES = ['mtk', 'msg']

END_INIT





//---------------------------------------------------------------------
//        REQUEST NO RESPONSE
//
//  as request new order
//---------------------------------------------------------------------

sub_request_id   [<V:0>]
{
    sess_id   (sid) :  string
    req_code  (rqc) :  string
}


sub_request_info [< V:0 >]   
{
    req_id  (rid)  : sub_request_id
    client  (cli)  : string
    //...
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




//---------------------------------------------------------------------
//        REQUEST  < - >   RESPONSE
//---------------------------------------------------------------------

sub_request_r  [<V:0>]
{
    request_code       (rc)    :   string
}


sub_r_response [< V:0 >]   
{
    request_code       (rc)     :   string
    sec_number         (sq)     :   int16       //  it will start with 0
    is_last_response   (lr)     :   bool
}
