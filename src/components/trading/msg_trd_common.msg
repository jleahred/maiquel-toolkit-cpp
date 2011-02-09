BEGIN_INIT

NAMESPACES = ['mtk', 'trd', 'msg']
INCLUDES = ['#include "components/msg_common.h"', '#include "support/mtk_double.h"', '#include "msg_trd_common_support.h"']

END_INIT






//---------------------------------------------------------------------
//    COMMON TRADING
//---------------------------------------------------------------------


sub_order_id   [< V:0, I:mtk::msg::sub_request_id  >]   {}



sub_total_executions [<V:0>]
{
    sum_price_by_qty    (spq)   :  double
    quantity            (aqt)   :  fix_num
    remaining_qty       (rq)    :  fix_num
}


