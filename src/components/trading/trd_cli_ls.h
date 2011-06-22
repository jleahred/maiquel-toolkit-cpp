#ifndef __trd_cli_ls_h__
#define __trd_cli_ls_h__


//  code generated by fsm_gen
// generated automatically
// coded last modification:        $CODED_LAST_MODIF  desactivated, lots of false notifications
// pythonscript last modification: $SCRIPT_LAST_MODIF


#include "support/alarm.h"
#include "support/signalslot.hpp"
#include "support/list.hpp"

#include "components/trading/msg_trd_cli_ls.h"
#include "components/trading/trd_cli_support.h"
#include "components/admin/admin.h"
#include "components/trading/trd_cli_historic.h"

namespace fsmgen_trd_cli_ls {
    class abstract_status;
};





namespace mtk{namespace trd{


class trd_cli_ls   : public mtk::SignalReceptor
{
    mtk::non_copyable nc;
    typedef  trd_cli_ls  CLASS_NAME;


public:
    trd_cli_ls ();
    virtual ~trd_cli_ls ();

    //  INPUT
    void rq_nw          ( const mtk::trd::msg::RQ_NW_LS&   rq           );
    void rq_md          ( const mtk::trd::msg::RQ_MD_LS&   rq           );
    void rq_cc          ( const mtk::trd::msg::RQ_CC_LS&   rq           );
    void cf_nw          ( const mtk::trd::msg::CF_NW_LS&   cf           );
    void cf_md          ( const mtk::trd::msg::CF_MD_LS&   cf           );
    void cf_cc          ( const mtk::trd::msg::CF_CC_LS&   cf           );
    void rj_nw          ( const mtk::trd::msg::RJ_NW_LS&   rj           );
    void rj_md          ( const mtk::trd::msg::RJ_MD_LS&   rj           );
    void rj_cc          ( const mtk::trd::msg::RJ_CC_LS&   rj           );
    void cf_ex          ( const mtk::trd::msg::CF_EX_LS&   ex           );


    //  OUTPUT
    mtk::Signal< const mtk::trd::msg::RQ_NW_LS&   /*rq*/          > sig_rq_nw;
    mtk::Signal< const mtk::trd::msg::RQ_MD_LS&   /*rq*/          > sig_rq_md;
    mtk::Signal< const mtk::trd::msg::RQ_CC_LS&   /*rq*/          > sig_rq_cc;
    mtk::Signal< const mtk::trd::msg::RJ_NW_LS&   /*rj*/          > sig_rj_nw;
    mtk::Signal< const mtk::trd::msg::RJ_MD_LS&   /*rj*/          > sig_rj_md;
    mtk::Signal< const mtk::trd::msg::RJ_CC_LS&   /*rj*/          > sig_rj_cc;
    mtk::Signal< const mtk::trd::msg::CF_NW_LS&   /*cf*/          > sig_cf_nw;
    mtk::Signal< const mtk::trd::msg::CF_MD_LS&   /*cf*/          > sig_cf_md;
    mtk::Signal< const mtk::trd::msg::CF_CC_LS&   /*cf*/          > sig_cf_cc;
    mtk::Signal< const mtk::trd::msg::CF_EX_LS&   /*ex*/          > sig_cf_ex;
    mtk::Signal<  > sig_changed;


    //  ACCESS
    const mtk::nullable<mtk::trd::msg::CF_XX_LS>           &  last_confirmation () const;
    const mtk::nullable<mtk::trd::msg::RQ_XX_LS>           &  last_request () const;
    const mtk::CountPtr<mtk::trd::hist::order_historic>    &  history () const;
    const bool                                             &  in_market () const;
    const bool                                             &  is_canceled () const;
    const bool                                             &  is_full_executed () const;
    const bool                                             &  has_pending_rq () const;
    const std::string                                      &  serrors () const;



private:
    //  current_status
    mtk::CountPtr<fsmgen_trd_cli_ls::abstract_status>      current_status;
    void on_new_status (mtk::CountPtr<fsmgen_trd_cli_ls::abstract_status>  new_status);

    //  keep temp status
    mtk::list<mtk::CountPtr<fsmgen_trd_cli_ls::abstract_status> >     queue_temp_status;
    void on_keep_temp_status (void);
    void on_remove_temp_status (void);
};





};   //  namespace mtk
};   //  namespace trd


#endif // __trd_cli_ls_h__


