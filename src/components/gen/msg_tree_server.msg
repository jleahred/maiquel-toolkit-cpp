BEGIN_INIT

INCLUDES = ['#include "support/mtk_string.h"', '#include "components/msg_common.h"' ]
NAMESPACES = ['mtk', 'gen', 'msg']

END_INIT







sub_tree_item [< V:0 >]
{
    branch          (b)         :   string      //  separating by dots the full path (including current item name)
    user_name       (un)        :   string
    product_code    (pc)        :   mtk::msg::sub_product_code   [optional]       //  if exists, means it is a product
}




tree_request_items [< V:0, SUBJ:REQ.${request_info.process_location.location.client_code}.TREE_REQUEST >]
{
    request_info    (ri)        :   mtk::msg::sub_request_info
    branch          (br)        :   string      //  separated by dots, the full path branch (not included the current item name)
}



tree_response_items [< V:0 , SUBJ:REP.${response_info.request_info.process_location.location.client_code}.${response_info.request_info.process_location.location.machine}.${response_info.request_info.process_location.process_uuid}.${response_info.request_info.req_id.sess_id}.${response_info.request_info.req_id.req_code} >]
{
    response_info   (ri)    :   mtk::msg::sub_r_response
    item            (it)    :   sub_tree_item
}