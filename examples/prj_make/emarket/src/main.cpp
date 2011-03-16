#include "mtk_qpid/mtk_qpid.hpp"
#include "components/prices/msg_prices.h"
#include <iostream>
#include "support/alarm.h"
#include "support/mtk_string.h"
#include "support/timer.h"
#include "components/trading/msg_trd_common.h"

#include "check_request.h"
#include "orders_book.h"
#include "components/admin/admin.h"



namespace
{
    
    const char*   APP_NAME          = "EMARKET";
    const char*   APP_VER           = "2011-03-16";
    const char*   APP_DESCRIPTION   = "This is a testing market.\n";
}




int main(int argc, char ** argv)
{
    
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION);

        check_request  cr;
        orders_book    ob;
        
        cr.sig_oms_rq_nw.connect(&ob, &orders_book::oms_RQ_NW_LS);
        cr.sig_oms_rq_md.connect(&ob, &orders_book::oms_RQ_MD_LS);
        cr.sig_oms_rq_cc.connect(&ob, &orders_book::oms_RQ_CC_LS);
        
        mtk::start_timer_wait_till_end();
        
        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION(std::cout << , "main", "no more info")
    #include "support/release_on_exit.hpp"
    return -1;
}

