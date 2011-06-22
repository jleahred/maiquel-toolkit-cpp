#ifndef __trd_cli_ord_book_h__
#define __trd_cli_ord_book_h__


#include "support/alarm.h"
#include "support/signalslot.hpp"
#include "support/map.hpp"
#include "trd_cli_ls.h"
#include "trd_cli_mk.h"
#include "mtk_qpid/mtk_qpid.hpp"




namespace mtk{namespace trd{

    
    
    namespace  trd_cli_ord_book {


        enum  en_order_type  {  ot_limit, ot_market  };
        
        
        void   init(void);      //  mtk::accmgrcli::init()  has to be called before
        
        //  INPUT
        mtk::CountPtr<trd_cli_ls>   rq_nw_ls        (                                   const mtk::msg::sub_product_code&   pc, mtk::trd::msg::enBuySell  buy_sell, const msg::sub_position_ls& rq_pos, const mtk::trd::msg::sub_account_info& account, const std::string& cli_ref);
        mtk::CountPtr<trd_cli_ls>   rq_nw_ls_manual (                                   const mtk::msg::sub_product_code&   pc, mtk::trd::msg::enBuySell  buy_sell, const msg::sub_position_ls& rq_pos,                                                 const std::string& cli_ref, bool agressive=false);
        mtk::CountPtr<trd_cli_ls>   rq_md_ls        ( const msg::sub_order_id& ord_id,                                                                              const msg::sub_position_ls& rq_pos,                                                 const std::string& cli_ref);
        mtk::CountPtr<trd_cli_ls>   rq_md_ls_manual ( const msg::sub_order_id& ord_id);
        mtk::CountPtr<trd_cli_ls>   rq_cc_ls        ( const msg::sub_order_id& ord_id);

        mtk::CountPtr<trd_cli_mk>   rq_nw_mk        (                                   const mtk::msg::sub_product_code&   pc, mtk::trd::msg::enBuySell  buy_sell, const msg::sub_position_mk& rq_pos, const mtk::trd::msg::sub_account_info& account, const std::string& cli_ref);
        mtk::CountPtr<trd_cli_mk>   rq_nw_mk_manual (                                   const mtk::msg::sub_product_code&   pc, mtk::trd::msg::enBuySell  buy_sell, const msg::sub_position_mk& rq_pos,                                                 const std::string& cli_ref, bool agressive=false);
        mtk::CountPtr<trd_cli_mk>   rq_md_mk        ( const msg::sub_order_id& ord_id,                                                                              const msg::sub_position_mk& rq_pos,                                                 const std::string& cli_ref);
        mtk::CountPtr<trd_cli_mk>   rq_md_mk_manual ( const msg::sub_order_id& ord_id);
        mtk::CountPtr<trd_cli_mk>   rq_cc_mk        ( const msg::sub_order_id& ord_id);


        //  OUTPUT
        mtk::Signal< const mtk::msg::sub_product_code&, const mtk::trd::msg::sub_exec_conf& >&   get_sig_execution       (void);
        
        mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_ls>&  >&          get_sig_order_ls_new    (void);
        mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_mk>&  >&          get_sig_order_mk_new    (void);


        //  ACCESS
        mtk::CountPtr<trd_cli_ls>                   get_order_ls            (const msg::sub_order_id& ord_id);
        mtk::CountPtr<trd_cli_mk>                   get_order_mk            (const msg::sub_order_id& ord_id);
        
        mtk::list<mtk::trd::msg::sub_order_id>      get_all_order_ids       (void);
        
        
        en_order_type  get_order_type(const msg::sub_order_id& ord_id);
        
        
        
        //  hooks
        mtk::Signal< mtk::trd::msg::RQ_XX_LS&, bool& /* canceled */, bool /*agress*/    >&   get_signal_request_hook_ls         (void);
        mtk::Signal< mtk::trd::msg::RQ_XX_MK&, bool& /* canceled */, bool /*agress*/    >&   get_signal_request_hook_mk         (void);
        
        
    };  //  namespace  trd_cli_ord_book {


};   //  namespace mtk
};   //  namespace trd


#endif // __trd_cli_ord_book_h__


 
