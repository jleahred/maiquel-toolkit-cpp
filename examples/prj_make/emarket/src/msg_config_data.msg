BEGIN_INIT

INCLUDES = [ ]
NAMESPACES = ['emarket' ]

END_INIT



//---------------------------------------------------------------------
//        
//
//---------------------------------------------------------------------


sub_product_config [< KEY:product_name >]
{
    product_name        (pn)    :       string
    
    product_user_name   (pun)   :       string
    group               (grp)   :       string
    group_user_name     (gun)   :       string
    price_fnext         (pfe)   :       fn_ext
}

