#ifndef __trd_cli_ord_book_h__
#define __trd_cli_ord_book_h__


#include "support/alarm.h"
#include "support/signalslot.hpp"
#include "support/map.hpp"
#include "trd_cli_ls.h"
#include "mtk_qpid/mtk_qpid.hpp"




namespace mtk{namespace trd{

    
    
    namespace  trd_cli_ord_book {
        
        
        //  INPUT
        mtk::CountPtr<trd_cli_ls>   rq_nw_ls        (                                   const mtk::msg::sub_product_code&   pc, const msg::sub_position_ls& rq_pos, const std::string& cli_ref);
        mtk::CountPtr<trd_cli_ls>   rq_nw_ls_manual (                                   const mtk::msg::sub_product_code&   pc, const msg::sub_position_ls& rq_pos, const std::string& cli_ref);
        mtk::CountPtr<trd_cli_ls>   rq_md_ls        ( const msg::sub_order_id& ord_id,                                          const msg::sub_position_ls& rq_pos, const std::string& cli_ref);
        mtk::CountPtr<trd_cli_ls>   rq_md_ls_manual ( const msg::sub_order_id& ord_id);
        mtk::CountPtr<trd_cli_ls>   rq_cc_ls        ( const msg::sub_order_id& ord_id);


        //  OUTPUT
        mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_ls>&  >& get_sig_order_ls_new    (void);


        //  ACCESS
        mtk::CountPtr<trd_cli_ls>                   get_order_ls            (const msg::sub_order_id& ord_id);
        
        //  hooks
        mtk::Signal< mtk::trd::msg::RQ_XX_LS&, bool& /* canceled */    >&   get_signal_request_hook         (void);
        
        
    };  //  namespace  trd_cli_ord_book {


};   //  namespace mtk
};   //  namespace trd


#endif // __trd_cli_ord_book_h__


 
