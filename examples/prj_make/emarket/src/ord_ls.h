#ifndef __ord_ls_h__
#define __ord_ls_h__


//  code generated by fsm_gen
// generated automatically
// coded last modification:        $CODED_LAST_MODIF  desactivated, lots of false notifications
// pythonscript last modification: $SCRIPT_LAST_MODIF

#include "support/mtk_string.h"



#include "support/alarm.h"
#include "support/signalslot.hpp"
#include "support/list.hpp"

#include "components/trading/msg_trd_cli_ls.h"
#include "components/trading/msg_trd_oms_rq.h"
#include "components/admin/admin.h"

namespace fsmgen_ord_ls {
    class abstract_status;
};







class ord_ls_dangerous_signals_not_warped;




class ord_ls   : public mtk::SignalReceptor
{
    mtk::non_copyable nc;
    typedef  ord_ls  CLASS_NAME;

public:
    explicit ord_ls ();
    explicit ord_ls (const mtk::CountPtr<ord_ls_dangerous_signals_not_warped>&  _ptr);
    virtual ~ord_ls (){};



    //  INPUT
    void cli_rq_nw      ( const mtk::trd::msg::oms_RQ_NW_LS&   rq           );
    void cli_rq_md      ( const mtk::trd::msg::oms_RQ_MD_LS&   rq           );
    void cli_rq_cc      ( const mtk::trd::msg::oms_RQ_CC_LS&   rq           );
    void mkt_cf_ex      ( const mtk::trd::msg::CF_EX_LS&   ex           );


    //  OUTPUT
    mtk::Signal< const mtk::trd::msg::CF_XX_LS&   /*order_st*/    > sig_ob_add_order;
    mtk::Signal< const mtk::trd::msg::CF_XX_LS&   /*order_st*/    > sig_ob_del_order;
    mtk::Signal< const mtk::trd::msg::CF_XX_LS&   /*order_st*/    > sig_ob_modif_order;
    mtk::Signal< const mtk::trd::msg::CF_XX_LS&   /*order_st*/    > sig_ob_check_execs;
    mtk::Signal< const mtk::trd::msg::CF_XX_LS&   /*order_st*/    > sig_ob_update_prices;
    mtk::Signal< const mtk::trd::msg::CF_NW_LS&   /*cf*/          > sig_cli_cf_nw;
    mtk::Signal< const mtk::trd::msg::CF_MD_LS&   /*cf*/          > sig_cli_cf_md;
    mtk::Signal< const mtk::trd::msg::CF_CC_LS&   /*cf*/          > sig_cli_cf_cc;
    mtk::Signal< const mtk::trd::msg::RJ_NW_LS&   /*rj*/          > sig_cli_rj_nw;
    mtk::Signal< const mtk::trd::msg::RJ_MD_LS&   /*rj*/          > sig_cli_rj_md;
    mtk::Signal< const mtk::trd::msg::RJ_CC_LS&   /*rj*/          > sig_cli_rj_cc;
    mtk::Signal< const mtk::trd::msg::CF_EX_LS&   /*ex*/          > sig_cli_cf_ex;


    //  ACCESS
    const mtk::nullable<mtk::trd::msg::CF_XX_LS>       &  last_confirmation () const;
    const mtk::nullable<mtk::trd::msg::RQ_XX_LS>       &  last_request () const;
    const int                                          &  sequence () const;




    //  STATS AND COVERAGE
    std::string  get_coverage_string(void);
    
    

    void  set   (const mtk::CountPtr<ord_ls_dangerous_signals_not_warped>&  _ptr);


private:
    mtk::CountPtr<ord_ls_dangerous_signals_not_warped>       ptr;

};




//  this class has to be used carefully
//  It has to be used as internal storage in respositories

class ord_ls_dangerous_signals_not_warped   : public mtk::SignalReceptor
{
    mtk::non_copyable nc;
    typedef  ord_ls_dangerous_signals_not_warped  CLASS_NAME;


public:
    ord_ls_dangerous_signals_not_warped ();
    virtual ~ord_ls_dangerous_signals_not_warped ();

    //  INPUT
    void cli_rq_nw      ( const mtk::trd::msg::oms_RQ_NW_LS&   rq           );
    void cli_rq_md      ( const mtk::trd::msg::oms_RQ_MD_LS&   rq           );
    void cli_rq_cc      ( const mtk::trd::msg::oms_RQ_CC_LS&   rq           );
    void mkt_cf_ex      ( const mtk::trd::msg::CF_EX_LS&   ex           );


    //  OUTPUT
    mtk::Signal< const mtk::trd::msg::CF_XX_LS&   /*order_st*/    > sig_ob_add_order;
    mtk::Signal< const mtk::trd::msg::CF_XX_LS&   /*order_st*/    > sig_ob_del_order;
    mtk::Signal< const mtk::trd::msg::CF_XX_LS&   /*order_st*/    > sig_ob_modif_order;
    mtk::Signal< const mtk::trd::msg::CF_XX_LS&   /*order_st*/    > sig_ob_check_execs;
    mtk::Signal< const mtk::trd::msg::CF_XX_LS&   /*order_st*/    > sig_ob_update_prices;
    mtk::Signal< const mtk::trd::msg::CF_NW_LS&   /*cf*/          > sig_cli_cf_nw;
    mtk::Signal< const mtk::trd::msg::CF_MD_LS&   /*cf*/          > sig_cli_cf_md;
    mtk::Signal< const mtk::trd::msg::CF_CC_LS&   /*cf*/          > sig_cli_cf_cc;
    mtk::Signal< const mtk::trd::msg::RJ_NW_LS&   /*rj*/          > sig_cli_rj_nw;
    mtk::Signal< const mtk::trd::msg::RJ_MD_LS&   /*rj*/          > sig_cli_rj_md;
    mtk::Signal< const mtk::trd::msg::RJ_CC_LS&   /*rj*/          > sig_cli_rj_cc;
    mtk::Signal< const mtk::trd::msg::CF_EX_LS&   /*ex*/          > sig_cli_cf_ex;


    //  ACCESS
    const mtk::nullable<mtk::trd::msg::CF_XX_LS>       &  last_confirmation () const;
    const mtk::nullable<mtk::trd::msg::RQ_XX_LS>       &  last_request () const;
    const int                                          &  sequence () const;



    //  STATS AND COVERAGE
    std::string  get_coverage_string(void);


private:
    //  current_status
    mtk::CountPtr<fsmgen_ord_ls::abstract_status>      current_status;
    void on_new_status (mtk::CountPtr<fsmgen_ord_ls::abstract_status>  new_status);

    //  keep temp status
    mtk::list<mtk::CountPtr<fsmgen_ord_ls::abstract_status> >     queue_temp_status;
    void on_keep_temp_status (void);
    void on_remove_temp_status (void);
};








#endif // __ord_ls_h__


