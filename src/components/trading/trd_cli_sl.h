#ifndef __trd_cli_sl_h__
#define __trd_cli_sl_h__


//  code generated by fsm_gen
// generated automatically
// coded last modification:        $CODED_LAST_MODIF  desactivated, lots of false notifications
// pythonscript last modification: $SCRIPT_LAST_MODIF

#include "support/mtk_string.h"



#include "support/alarm.h"
#include "support/signalslot.hpp"
#include "support/list.hpp"

#include "components/trading/msg_trd_cli_sl.h"
#include "components/trading/trd_cli_support.h"
#include "components/admin/admin.h"
#include "components/trading/trd_cli_historic.h"
#include "support/call_later.h"

namespace fsmgen_trd_cli_sl {
    class abstract_status;
};





namespace mtk{namespace trd{

class trd_cli_sl_dangerous_signals_not_warped;




class trd_cli_sl   : public mtk::SignalReceptor
{
    mtk::non_copyable nc;

public:
    explicit trd_cli_sl ();
    explicit trd_cli_sl (const mtk::CountPtr<trd_cli_sl_dangerous_signals_not_warped>&  _ptr);
    virtual ~trd_cli_sl (){};



    //  INPUT
    void rq_nw          ( const mtk::trd::msg::RQ_NW_SL&   rq           );
    void rq_md          ( const mtk::trd::msg::RQ_MD_SL&   rq           );
    void rq_cc          ( const mtk::trd::msg::RQ_CC_SL&   rq           );
    void cf_nw          ( const mtk::trd::msg::CF_NW_SL&   cf           );
    void cf_md          ( const mtk::trd::msg::CF_MD_SL&   cf           );
    void cf_cc          ( const mtk::trd::msg::CF_CC_SL&   cf           );
    void rj_nw          ( const mtk::trd::msg::RJ_NW_SL&   rj           );
    void rj_md          ( const mtk::trd::msg::RJ_MD_SL&   rj           );
    void rj_cc          ( const mtk::trd::msg::RJ_CC_SL&   rj           );
    void cf_tr          ( const mtk::trd::msg::CF_TR_SL&   tr           );
    void cf_st          ( const mtk::trd::msg::CF_ST_SL&   st           );
    void time_out       ( const int&          _            );


    //  OUTPUT
    mtk::Signal< const mtk::trd::msg::RQ_NW_SL&   /*rq*/          > sig_rq_nw;
    mtk::Signal< const mtk::trd::msg::RQ_MD_SL&   /*rq*/          > sig_rq_md;
    mtk::Signal< const mtk::trd::msg::RQ_CC_SL&   /*rq*/          > sig_rq_cc;
    mtk::Signal< const mtk::trd::msg::RJ_NW_SL&   /*rj*/          > sig_rj_nw;
    mtk::Signal< const mtk::trd::msg::RJ_MD_SL&   /*rj*/          > sig_rj_md;
    mtk::Signal< const mtk::trd::msg::RJ_CC_SL&   /*rj*/          > sig_rj_cc;
    mtk::Signal< const mtk::trd::msg::CF_NW_SL&   /*cf*/          > sig_cf_nw;
    mtk::Signal< const mtk::trd::msg::CF_MD_SL&   /*cf*/          > sig_cf_md;
    mtk::Signal< const mtk::trd::msg::CF_CC_SL&   /*cf*/          > sig_cf_cc;
    mtk::Signal< const mtk::trd::msg::CF_TR_SL&   /*trg*/         > sig_cf_tr;
    mtk::Signal< const mtk::trd::msg::CF_ST_SL&   /*st*/          > sig_cf_st;
    mtk::Signal<  > sig_changed;


    //  ACCESS
    const mtk::nullable<mtk::trd::msg::CF_XX_SL>           &  last_confirmation () const;
    const mtk::nullable<mtk::trd::msg::RQ_XX_SL>           &  last_request () const;
    const mtk::CountPtr<mtk::trd::hist::order_historic_dangerous_not_signal_warped      >   &  history () const;
    const bool                                             &  in_market_no_pend () const;
    const bool                                             &  is_canceled () const;
    const bool                                             &  is_triggered () const;
    const bool                                             &  is_alive () const;
    const bool                                             &  has_pending_rq () const;
    const std::string                                      &  serrors () const;




    //  STATS AND COVERAGE
    std::string  get_coverage_string(void);
    
    

    void  set   (const mtk::CountPtr<trd_cli_sl_dangerous_signals_not_warped>&  _ptr);


private:
    mtk::CountPtr<trd_cli_sl_dangerous_signals_not_warped>       ptr;

};




//  this class has to be used carefully
//  It has to be used as internal storage in respositories

class trd_cli_sl_dangerous_signals_not_warped   : public mtk::SignalReceptor
{
    mtk::non_copyable nc;


public:
    trd_cli_sl_dangerous_signals_not_warped ();
    virtual ~trd_cli_sl_dangerous_signals_not_warped ();

    //  INPUT
    void rq_nw          ( const mtk::trd::msg::RQ_NW_SL&   rq           );
    void rq_md          ( const mtk::trd::msg::RQ_MD_SL&   rq           );
    void rq_cc          ( const mtk::trd::msg::RQ_CC_SL&   rq           );
    void cf_nw          ( const mtk::trd::msg::CF_NW_SL&   cf           );
    void cf_md          ( const mtk::trd::msg::CF_MD_SL&   cf           );
    void cf_cc          ( const mtk::trd::msg::CF_CC_SL&   cf           );
    void rj_nw          ( const mtk::trd::msg::RJ_NW_SL&   rj           );
    void rj_md          ( const mtk::trd::msg::RJ_MD_SL&   rj           );
    void rj_cc          ( const mtk::trd::msg::RJ_CC_SL&   rj           );
    void cf_tr          ( const mtk::trd::msg::CF_TR_SL&   tr           );
    void cf_st          ( const mtk::trd::msg::CF_ST_SL&   st           );
    void time_out       ( const int&          _            );


    //  OUTPUT
    mtk::Signal< const mtk::trd::msg::RQ_NW_SL&   /*rq*/          > sig_rq_nw;
    mtk::Signal< const mtk::trd::msg::RQ_MD_SL&   /*rq*/          > sig_rq_md;
    mtk::Signal< const mtk::trd::msg::RQ_CC_SL&   /*rq*/          > sig_rq_cc;
    mtk::Signal< const mtk::trd::msg::RJ_NW_SL&   /*rj*/          > sig_rj_nw;
    mtk::Signal< const mtk::trd::msg::RJ_MD_SL&   /*rj*/          > sig_rj_md;
    mtk::Signal< const mtk::trd::msg::RJ_CC_SL&   /*rj*/          > sig_rj_cc;
    mtk::Signal< const mtk::trd::msg::CF_NW_SL&   /*cf*/          > sig_cf_nw;
    mtk::Signal< const mtk::trd::msg::CF_MD_SL&   /*cf*/          > sig_cf_md;
    mtk::Signal< const mtk::trd::msg::CF_CC_SL&   /*cf*/          > sig_cf_cc;
    mtk::Signal< const mtk::trd::msg::CF_TR_SL&   /*trg*/         > sig_cf_tr;
    mtk::Signal< const mtk::trd::msg::CF_ST_SL&   /*st*/          > sig_cf_st;
    mtk::Signal<  > sig_changed;


    //  ACCESS
    const mtk::nullable<mtk::trd::msg::CF_XX_SL>           &  last_confirmation () const;
    const mtk::nullable<mtk::trd::msg::RQ_XX_SL>           &  last_request () const;
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
    mtk::CountPtr<fsmgen_trd_cli_sl::abstract_status>      current_status;
    void on_new_status (mtk::CountPtr<fsmgen_trd_cli_sl::abstract_status>  new_status);

    //  keep temp status
    mtk::list<mtk::CountPtr<fsmgen_trd_cli_sl::abstract_status> >     queue_temp_status;
    void on_keep_temp_status (void);
    void on_remove_temp_status (void);
};






};   //  namespace mtk
};   //  namespace trd


#endif // __trd_cli_sl_h__


