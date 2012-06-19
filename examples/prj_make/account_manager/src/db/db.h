
#ifndef  __db_accmgr__
#define  __db_accmgr__


#include <string>
#include "support/list.hpp"
#include "support/tuples.hpp"
#include "msg_structs.h"



namespace accmgr {
    namespace db {


        void init(const std::string& db_file_name);
        void load();
        void save();
        void purge();


        //  It will return a string
        //  emtpy if there is no grant
        //  <deleted>  if the account has been deleted and the list has not been purged
        //  First char will be the efective grant
        //  In case of having more than one grant
        //      It will apply the more restrictive one
        //      It will return a string with all the computed grants
        std::string                                         get_grant_type (    const mtk::msg::sub_request_id          rid,
                                                                                const std::string&                      market,
                                                                                const mtk::trd::msg::sub_account_info&  account_info);

        std::string                                         get_account_oms_additional_info(const mtk::trd::msg::sub_account_info&  account_info);

        mtk::list<mtk::trd::account::msg::sub_grant>        get_user_grants(const std::string& user_name, const std::string& client_code);

        mtk::list<std::string>                              get_market_list(void);

    };  //      namespace db {
};      //  namespace accmgr {


#endif   //  __db_accmgr__
