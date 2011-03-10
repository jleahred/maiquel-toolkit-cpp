#include "mtk_qpid/mtk_qpid.hpp"
#include "components/prices/msg_prices.h"
#include <iostream>
#include "support/alarm.h"
#include "support/mtk_string.h"
#include "support/timer.h"
#include "components/trading/msg_trd_common.h"

#include "check_request.h"
#include "orders_book.h"

namespace mtk {  
    namespace  msg {
        
	sub_process_location  get_process_location(void)
	{
	    return  mtk::msg::sub_process_location  ("CLIENT", "MACHINE", "PROCESS NAME", "UUID");
	}
	sub_request_info   get_request_info (void)
	{
	    static int i=0;
	    return sub_request_info (sub_request_id("pending", MTK_SS("pending"<<i)), get_process_location());
	}
        
      };   //namespace msg {
};  //namespace mtk {





int main(void)
{
    
    try
    {
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

void mtk::AlarmMsg(const mtk::Alarm& error)
{
    std::cout << error << std::endl;
}
