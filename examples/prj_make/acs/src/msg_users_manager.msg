BEGIN_INIT

INCLUDES = [ ]
NAMESPACES = [ 'users_manager' ]

END_INIT



//---------------------------------------------------------------------
//        
//
//---------------------------------------------------------------------


sub_user_info  [<V:0,  KEY:name  >]
{
    name                (nm)            :       string
    client_code         (cc)            :       string
    requested_by        (rb)            :       string
    notes               (nt)            :       string
}



sub_user_acs_info  [<  V:0,  KEY:user_info.name  >]
{
    user_info           (ui)            :       sub_user_info
    passwordcrc32       (pw32)          :       string
    created_on          (dtc)           :       date_time
    last_access         (dt)            :       date_time
    check_pass_ok       (cpok)          :       int
    check_pass_wrong    (cpwr)          :       int
}


