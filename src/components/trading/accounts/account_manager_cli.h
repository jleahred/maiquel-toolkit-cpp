#ifndef  __account_manager_cli__
#define  __account_manager_cli__


#include "support/count_ptr.hpp"
#include "support/signalslot.hpp"
#include "components/trading/accounts/msg_account_manager.h"



namespace mtk {
    namespace accmgrcli {


        void init();

        mtk::CountPtr<mtk::Signal<const mtk::trd::account::msg::sub_grant&> >           get_signal_new_grant_received(void);
        mtk::list<mtk::trd::account::msg::sub_grant>                                    get_grant_list               (const std::string& market);
        std::string                                                                     get_grant_less_restrictive   (const std::string& market);
        std::string                                                                     get_grant                    (const std::string& market, const mtk::trd::msg::sub_account_info& ai);


    };  //      namespace accmgrcli {
};      //  namespace mtk {


#endif   //  __account_manager_cli__

