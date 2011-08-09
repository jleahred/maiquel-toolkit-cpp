BEGIN_INIT

INCLUDES = [ ]
NAMESPACES = ['qfmgr', 'msg']

END_INIT



//---------------------------------------------------------------------
//        
//
//---------------------------------------------------------------------


sub_product [< V:0, KEY:gen_product_name >]
{
    gen_product_name    (gpn)   :       string
    
    market              (mk)    :       string
    re_product_code     (repc)  :       string
}




sub_filter_info [<V:0>]
{
    gen_product_name    (gpn)   :       string      //  this is not the product on system, is a generic (could match with more than one product) user code
    quantity            (qt)    :       int
}



sub_client_info  [<V:0, KEY:name  >]
{
    name            (nm)    :   string

    created         (cdt)   :   date_time
    [filter_list]   (fl)    :   sub_filter_info
}



sub_user_info  [<V:0, KEY:name >]
{
    name            (nm)    :   string
    
    created         (cdt)   :   date_time
    client_code     (cc)    :   string
    [filter_list]   (fl)    :   sub_filter_info
}

