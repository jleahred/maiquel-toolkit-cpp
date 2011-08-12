BEGIN_INIT

INCLUDES = [ '#include "components/msg_common.h"' ]
NAMESPACES = ['prodinfo_grant', 'db', 'msg']

END_INIT



//---------------------------------------------------------------------
//        
//
//---------------------------------------------------------------------



sub_pattern_users_grants [< V:0, KEY:user_pattern >]
{
    user_pattern                (reu)    :   string
    [re_product_code_list]      (pcl)    :   mtk::msg::sub_product_code         //  list of regular product code regular expresions
    last_applied_rule           (lar)    :   date_time
}


sub_client__pattern_users [< V:0, KEY:client_code >]
{
    client_code                 (cc)     :   string
    [users_pattern]             (up)     :   sub_pattern_users_grants
}


