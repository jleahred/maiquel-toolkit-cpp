BEGIN_INIT

INCLUDES = ['#include "support/mtk_string.h"', '#include "msg_common_support.h"' ]
NAMESPACES = ['mtk', 'msg']

END_INIT





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




sub_request_id   [<V:0>]
{
    sess_id   (sid) :  string
    req_code  (rqc) :  string
}

sub_order_id   [< V:0, I:sub_request_id  >]   {}

sub_request_info [< V:0 >]   
{
    req_id  (rid)  : sub_request_id
    client  (cli)  : string
    //...
}