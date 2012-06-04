#ifndef __trd_cli_sm_h__
#define __trd_cli_sm_h__


//  code generated by fsm_gen
// generated automatically
// coded last modification:        $CODED_LAST_MODIF  desactivated, lots of false notifications
// pythonscript last modification: $SCRIPT_LAST_MODIF

#include "support/mtk_string.h"



#include "support/alarm.h"
#include "support/signalslot.hpp"
#include "support/list.hpp"

#include "components/trading/msg_trd_cli_sm.h"
#include "components/trading/trd_cli_support.h"
#include "components/admin/admin.h"
#include "components/trading/trd_cli_historic.h"
#include "support/call_later.h"

namespace fsmgen_trd_cli_sm {
    class abstract_status;
};





namespace mtk{namespace trd{

class trd_cli_sm_dangerous_signals_not_warped;




class trd_cli_sm   : public mtk::SignalReceptor
{
    mtk::non_copyable nc;
    typedef  trd_cli_sm  CLASS_NAME;

public:
    explicit trd_cli_sm ();
    explicit trd_cli_sm (const mtk::CountPtr<trd_cli_sm_dangerous_signals_not_warped>&  _ptr);
    virtual ~trd_cli_sm (){};



    //  INPUT
    void rq_nw          ( const mtk::trd::msg::RQ_NW_SM&   rq           );
    void rq_md          ( const mtk::trd::msg::RQ_MD_SM&   rq           );
    void rq_cc          ( const mtk::trd::msg::RQ_CC_SM&   rq           );
    void cf_nw          ( const mtk::trd::msg::CF_NW_SM&   cf           );
    void cf_md          ( const mtk::trd::msg::CF_MD_SM&   cf           );
    void cf_cc          ( const mtk::trd::msg::CF_CC_SM&   cf           );
    void rj_nw          ( const mtk::trd::msg::RJ_NW_SM&   rj           );
    void rj_md          ( const mtk::trd::msg::RJ_MD_SM&   rj           );
    void rj_cc          ( const mtk::trd::msg::RJ_CC_SM&   rj           );
    void cf_tr          ( const mtk::trd::msg::CF_TR_SM&   tr           );
    void cf_st          ( const mtk::trd::msg::CF_ST_SM&   st           );
    void time_out       ( const int&          _            );


    //  OUTPUT
    mtk::Signal< const mtk::trd::msg::RQ_NW_SM&   /*rq*/          > sig_rq_nw;
    mtk::Signal< const mtk::trd::msg::RQ_MD_SM&   /*rq*/          > sig_rq_md;
    mtk::Signal< const mtk::trd::msg::RQ_CC_SM&   /*rq*/          > sig_rq_cc;
    mtk::Signal< const mtk::trd::msg::RJ_NW_SM&   /*rj*/          > sig_rj_nw;
    mtk::Signal< const mtk::trd::msg::RJ_MD_SM&   /*rj*/          > sig_rj_md;
    mtk::Signal< const mtk::trd::msg::RJ_CC_SM&   /*rj*/          > sig_rj_cc;
    mtk::Signal< const mtk::trd::msg::CF_NW_SM&   /*cf*/          > sig_cf_nw;
    mtk::Signal< const mtk::trd::msg::CF_MD_SM&   /*cf*/          > sig_cf_md;
    mtk::Signal< const mtk::trd::msg::CF_CC_SM&   /*cf*/          > sig_cf_cc;
    mtk::Signal< const mtk::trd::msg::CF_TR_SM&   /*trg*/         > sig_cf_tr;
    mtk::Signal< const mtk::trd::msg::CF_ST_SM&   /*st*/          > sig_cf_st;
    mtk::Signal<  > sig_changed;


    //  ACCESS
    const mtk::nullable<mtk::trd::msg::CF_XX_SM>           &  last_confirmation () const;
    const mtk::nullable<mtk::trd::msg::RQ_XX_SM>           &  last_request () const;
    const mtk::CountPtr<mtk::trd::hist::order_historic_dangerous_not_signal_warped      >   &  history () const;
    const bool                                             &  in_market_no_pend () const;
    const bool                                             &  is_canceled () const;
    const bool                                             &  is_triggered () const;
    const bool                                             &  is_alive () const;
    const bool                                             &  has_pending_rq () const;
    const std::string                                      &  serrors () const;




    //  STATS AND COVERAGE
    std::string  get_coverage_string(void);
    
    

    void  set   (const mtk::CountPtr<trd_cli_sm_dangerous_signals_not_warped>&  _ptr);


private:
    mtk::CountPtr<trd_cli_sm_dangerous_signals_not_warped>       ptr;

};




//  this class has to be used carefully
//  It has to be used as internal storage in respositories

class trd_cli_sm_dangerous_signals_not_warped   : public mtk::SignalReceptor
{
    mtk::non_copyable nc;
    typedef  trd_cli_sm_dangerous_signals_not_warped  CLASS_NAME;


public:
    trd_cli_sm_dangerous_signals_not_warped ();
    virtual ~trd_cli_sm_dangerous_signals_not_warped ();

    //  INPUT
    void rq_nw          ( const mtk::trd::msg::RQ_NW_SM&   rq           );
    void rq_md          ( const mtk::trd::msg::RQ_MD_SM&   rq           );
    void rq_cc          ( const mtk::trd::msg::RQ_CC_SM&   rq           );
    void cf_nw          ( const mtk::trd::msg::CF_NW_SM&   cf           );
    void cf_md          ( const mtk::trd::msg::CF_MD_SM&   cf           );
    void cf_cc          ( const mtk::trd::msg::CF_CC_SM&   cf           );
    void rj_nw          ( const mtk::trd::msg::RJ_NW_SM&   rj           );
    void rj_md          ( const mtk::trd::msg::RJ_MD_SM&   rj           );
    void rj_cc          ( const mtk::trd::msg::RJ_CC_SM&   rj           );
    void cf_tr          ( const mtk::trd::msg::CF_TR_SM&   tr           );
    void cf_st          ( const mtk::trd::msg::CF_ST_SM&   st           );
    void time_out       ( const int&          _            );


    //  OUTPUT
    mtk::Signal< const mtk::trd::msg::RQ_NW_SM&   /*rq*/          > sig_rq_nw;
    mtk::Signal< const mtk::trd::msg::RQ_MD_SM&   /*rq*/          > sig_rq_md;
    mtk::Signal< const mtk::trd::msg::RQ_CC_SM&   /*rq*/          > sig_rq_cc;
    mtk::Signal< const mtk::trd::msg::RJ_NW_SM&   /*rj*/          > sig_rj_nw;
    mtk::Signal< const mtk::trd::msg::RJ_MD_SM&   /*rj*/          > sig_rj_md;
    mtk::Signal< const mtk::trd::msg::RJ_CC_SM&   /*rj*/          > sig_rj_cc;
    mtk::Signal< const mtk::trd::msg::CF_NW_SM&   /*cf*/          > sig_cf_nw;
    mtk::Signal< const mtk::trd::msg::CF_MD_SM&   /*cf*/          > sig_cf_md;
    mtk::Signal< const mtk::trd::msg::CF_CC_SM&   /*cf*/          > sig_cf_cc;
    mtk::Signal< const mtk::trd::msg::CF_TR_SM&   /*trg*/         > sig_cf_tr;
    mtk::Signal< const mtk::trd::msg::CF_ST_SM&   /*st*/          > sig_cf_st;
    mtk::Signal<  > sig_changed;


    //  ACCESS
    const mtk::nullable<mtk::trd::msg::CF_XX_SM>           &  last_confirmation () const;
    const mtk::nullable<mtk::trd::msg::RQ_XX_SM>           &  last_request () const;
    const mtk::CountPtr<mtk::trd::hist::order_historic_dangerous_not_signal_warped      >   &  history () const;
    const bool                                             &  in_market_no_pend () const;
    const bool                                             &  is_canceled () const;
    const bool                                             &  is_triggered () const;
    const bool                                             &  is_alive () const;
    const bool                                             &  has_pending_rq () const;
    const std::string                                      &  serrors () const;



    //  STATS AND COVERAGE
    std::string  get_coverage_string(void);


private:
    //  current_status
    mtk::CountPtr<fsmgen_trd_cli_sm::abstract_status>      current_status;
    void on_new_status (mtk::CountPtr<fsmgen_trd_cli_sm::abstract_status>  new_status);

    //  keep temp status
    mtk::list<mtk::CountPtr<fsmgen_trd_cli_sm::abstract_status> >     queue_temp_status;
    void on_keep_temp_status (void);
    void on_remove_temp_status (void);
};






};   //  namespace mtk
};   //  namespace trd


#endif // __trd_cli_sm_h__


