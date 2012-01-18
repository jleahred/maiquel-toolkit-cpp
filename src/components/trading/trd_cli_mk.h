#ifndef __trd_cli_mk_h__
#define __trd_cli_mk_h__


//  code generated by fsm_gen
// generated automatically
// coded last modification:        $CODED_LAST_MODIF  desactivated, lots of false notifications
// pythonscript last modification: $SCRIPT_LAST_MODIF

#include "support/mtk_string.h"



#include "support/alarm.h"
#include "support/signalslot.hpp"
#include "support/list.hpp"

#include "components/trading/msg_trd_cli_mk.h"
#include "components/trading/trd_cli_support.h"
#include "components/admin/admin.h"
#include "components/trading/trd_cli_historic.h"

namespace fsmgen_trd_cli_mk {
    class abstract_status;
};





namespace mtk{namespace trd{

class trd_cli_mk_dangerous_signals_not_warped;




class trd_cli_mk   : public mtk::SignalReceptor
{
    mtk::non_copyable nc;
    typedef  trd_cli_mk  CLASS_NAME;

public:
    explicit trd_cli_mk ();
    explicit trd_cli_mk (const mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped>&  _ptr);
    virtual ~trd_cli_mk (){};



    //  INPUT
    void rq_nw          ( const mtk::trd::msg::RQ_NW_MK&   rq           );
    void rq_md          ( const mtk::trd::msg::RQ_MD_MK&   rq           );
    void rq_cc          ( const mtk::trd::msg::RQ_CC_MK&   rq           );
    void cf_nw          ( const mtk::trd::msg::CF_NW_MK&   cf           );
    void cf_md          ( const mtk::trd::msg::CF_MD_MK&   cf           );
    void cf_cc          ( const mtk::trd::msg::CF_CC_MK&   cf           );
    void rj_nw          ( const mtk::trd::msg::RJ_NW_MK&   rj           );
    void rj_md          ( const mtk::trd::msg::RJ_MD_MK&   rj           );
    void rj_cc          ( const mtk::trd::msg::RJ_CC_MK&   rj           );
    void cf_ex          ( const mtk::trd::msg::CF_EX_MK&   ex           );
    void cf_exLK        ( const mtk::trd::msg::CF_EXLK&   exlk         );
    void cf_st          ( const mtk::trd::msg::CF_ST_MK&   st           );


    //  OUTPUT
    mtk::Signal< const mtk::trd::msg::RQ_NW_MK&   /*rq*/          > sig_rq_nw;
    mtk::Signal< const mtk::trd::msg::RQ_MD_MK&   /*rq*/          > sig_rq_md;
    mtk::Signal< const mtk::trd::msg::RQ_CC_MK&   /*rq*/          > sig_rq_cc;
    mtk::Signal< const mtk::trd::msg::RJ_NW_MK&   /*rj*/          > sig_rj_nw;
    mtk::Signal< const mtk::trd::msg::RJ_MD_MK&   /*rj*/          > sig_rj_md;
    mtk::Signal< const mtk::trd::msg::RJ_CC_MK&   /*rj*/          > sig_rj_cc;
    mtk::Signal< const mtk::trd::msg::CF_NW_MK&   /*cf*/          > sig_cf_nw;
    mtk::Signal< const mtk::trd::msg::CF_MD_MK&   /*cf*/          > sig_cf_md;
    mtk::Signal< const mtk::trd::msg::CF_CC_MK&   /*cf*/          > sig_cf_cc;
    mtk::Signal< const mtk::trd::msg::CF_EX_MK&   /*ex*/          > sig_cf_ex;
    mtk::Signal< const mtk::trd::msg::CF_ST_MK&   /*st*/          > sig_cf_st;
    mtk::Signal<  > sig_changed;


    //  ACCESS
    const mtk::nullable<mtk::trd::msg::CF_XX_MK>           &  last_confirmation () const;
    const mtk::nullable<mtk::trd::msg::RQ_XX_MK>           &  last_request () const;
    const mtk::CountPtr<mtk::trd::hist::order_historic_dangerous_not_signal_warped      >   &  history () const;
    const mtk::CountPtr<mtk::trd::hist::order_EXECS_historic_dangerous_not_signal_warped>   &  executions () const;
    const bool                                             &  in_market () const;
    const bool                                             &  is_canceled () const;
    const bool                                             &  is_full_executed () const;
    const bool                                             &  has_pending_rq () const;
    const std::string                                      &  serrors () const;




    //  STATS AND COVERAGE
    std::string  get_coverage_string(void);
    
    

    void  set   (const mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped>&  _ptr);


private:
    mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped>       ptr;

};




//  this class has to be used carefully
//  It has to be used as internal storage in respositories

class trd_cli_mk_dangerous_signals_not_warped   : public mtk::SignalReceptor
{
    mtk::non_copyable nc;
    typedef  trd_cli_mk_dangerous_signals_not_warped  CLASS_NAME;


public:
    trd_cli_mk_dangerous_signals_not_warped ();
    virtual ~trd_cli_mk_dangerous_signals_not_warped ();

    //  INPUT
    void rq_nw          ( const mtk::trd::msg::RQ_NW_MK&   rq           );
    void rq_md          ( const mtk::trd::msg::RQ_MD_MK&   rq           );
    void rq_cc          ( const mtk::trd::msg::RQ_CC_MK&   rq           );
    void cf_nw          ( const mtk::trd::msg::CF_NW_MK&   cf           );
    void cf_md          ( const mtk::trd::msg::CF_MD_MK&   cf           );
    void cf_cc          ( const mtk::trd::msg::CF_CC_MK&   cf           );
    void rj_nw          ( const mtk::trd::msg::RJ_NW_MK&   rj           );
    void rj_md          ( const mtk::trd::msg::RJ_MD_MK&   rj           );
    void rj_cc          ( const mtk::trd::msg::RJ_CC_MK&   rj           );
    void cf_ex          ( const mtk::trd::msg::CF_EX_MK&   ex           );
    void cf_exLK        ( const mtk::trd::msg::CF_EXLK&   exlk         );
    void cf_st          ( const mtk::trd::msg::CF_ST_MK&   st           );


    //  OUTPUT
    mtk::Signal< const mtk::trd::msg::RQ_NW_MK&   /*rq*/          > sig_rq_nw;
    mtk::Signal< const mtk::trd::msg::RQ_MD_MK&   /*rq*/          > sig_rq_md;
    mtk::Signal< const mtk::trd::msg::RQ_CC_MK&   /*rq*/          > sig_rq_cc;
    mtk::Signal< const mtk::trd::msg::RJ_NW_MK&   /*rj*/          > sig_rj_nw;
    mtk::Signal< const mtk::trd::msg::RJ_MD_MK&   /*rj*/          > sig_rj_md;
    mtk::Signal< const mtk::trd::msg::RJ_CC_MK&   /*rj*/          > sig_rj_cc;
    mtk::Signal< const mtk::trd::msg::CF_NW_MK&   /*cf*/          > sig_cf_nw;
    mtk::Signal< const mtk::trd::msg::CF_MD_MK&   /*cf*/          > sig_cf_md;
    mtk::Signal< const mtk::trd::msg::CF_CC_MK&   /*cf*/          > sig_cf_cc;
    mtk::Signal< const mtk::trd::msg::CF_EX_MK&   /*ex*/          > sig_cf_ex;
    mtk::Signal< const mtk::trd::msg::CF_ST_MK&   /*st*/          > sig_cf_st;
    mtk::Signal<  > sig_changed;


    //  ACCESS
    const mtk::nullable<mtk::trd::msg::CF_XX_MK>           &  last_confirmation () const;
    const mtk::nullable<mtk::trd::msg::RQ_XX_MK>           &  last_request () const;
    const mtk::CountPtr<mtk::trd::hist::order_historic_dangerous_not_signal_warped      >   &  history () const;
    const mtk::CountPtr<mtk::trd::hist::order_EXECS_historic_dangerous_not_signal_warped>   &  executions () const;
    const bool                                             &  in_market () const;
    const bool                                             &  is_canceled () const;
    const bool                                             &  is_full_executed () const;
    const bool                                             &  has_pending_rq () const;
    const std::string                                      &  serrors () const;



    //  STATS AND COVERAGE
    std::string  get_coverage_string(void);


private:
    //  current_status
    mtk::CountPtr<fsmgen_trd_cli_mk::abstract_status>      current_status;
    void on_new_status (mtk::CountPtr<fsmgen_trd_cli_mk::abstract_status>  new_status);

    //  keep temp status
    mtk::list<mtk::CountPtr<fsmgen_trd_cli_mk::abstract_status> >     queue_temp_status;
    void on_keep_temp_status (void);
    void on_remove_temp_status (void);
};






};   //  namespace mtk
};   //  namespace trd


#endif // __trd_cli_mk_h__


