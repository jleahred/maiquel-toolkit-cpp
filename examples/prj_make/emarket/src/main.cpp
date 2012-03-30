#include "mtk_qpid/mtk_qpid.h"
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

    const char*   APP_MODIFICATIONS =   "           2011-03-16     first version\n"
                                        "           2011-08-01     product loader comunication\n"
                                        ;

}




int main(int argc, char ** argv)
{

    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);

        check_request  cr;
        orders_book    ob;

        cr.sig_oms_rq_nw_ls.connect  (&ob, &orders_book::oms_RQ_NW_LS);
        cr.sig_oms_rq_md_ls.connect  (&ob, &orders_book::oms_RQ_MD_LS);
        cr.sig_oms_rq_cc_ls.connect  (&ob, &orders_book::oms_RQ_CC_LS);

        cr.sig_oms_rq_nw_mk.connect  (&ob, &orders_book::oms_RQ_NW_MK);

        cr.sig_oms_rq_nw_sm.connect  (&ob, &orders_book::oms_RQ_NW_SM);
        cr.sig_oms_rq_md_sm.connect  (&ob, &orders_book::oms_RQ_MD_SM);
        cr.sig_oms_rq_cc_sm.connect  (&ob, &orders_book::oms_RQ_CC_SM);


        cr.sig_add_product.connect(&ob, &orders_book::add_product);
        cr.init();

        mtk::start_timer_wait_till_end();

        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION(std::cout << , "main", "no more info")
    #include "support/release_on_exit.hpp"
    return -1;
}

