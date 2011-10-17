BEGIN_INIT

INCLUDES = ['#include "support/mtk_string.h"', '#include "components/msg_common.h"' ]
NAMESPACES = ['mtk', 'gen', 'msg']

END_INIT







sub_tree_item [< KEY:branch >]
{
    branch          (br)        :   string      //  starting and separated by  .  the full path (including current item name)
    description     (desc)      :   string
    product_code    (pc)        :   mtk::msg::sub_product_code   [optional]       //  if exists, means it is a product
}




req_tree_items [< QE:ALL_GS, SUBJ:GS.${request_info.process_info.location.client_code}.TREE.REQ >]
{
    request_info    (rqi)       :   mtk::msg::sub_request_info
    branch          (br)        :   string      //  separated by dots, the full path branch (not included the current item name)
}



res_tree_items [< QE:ALL_GS, SUBJ:CLI.${response_info.request_info.process_info.location.client_code}.${response_info.request_info.process_info.location.machine}.${response_info.request_info.process_info.process_uuid}.${response_info.request_info.req_id.session_id}.${response_info.request_info.req_id.req_code}.RSTI >]
{
    response_info   (rsi)   :   mtk::msg::sub_r_response
    item            (it)    :   sub_tree_item
}
