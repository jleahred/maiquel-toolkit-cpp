
#ifndef  __db_qfmgr__
#define  __db_qfmgr__


#include <string>
#include "support/list.hpp"
#include "support/tuples.hpp"
#include "components/trading/msg_trd_oms_rq.h"



namespace qfmgr { 
    namespace db {

        

        void init(const std::string& db_file_name);
        void load();
        void save();


        
        mtk::list<std::string>&   get_market_list(void);
        
        mtk::tuple<int, int>    get_user_filters____tpl_cli_user(   const std::string&  cli_name, 
                                                                    const std::string&  user_name, 
                                                                    const std::string& market, 
                                                                    const std::string&  product);
        
        
        
    };  //      namespace db {
};      //  namespace qfmgr { 


#endif   //  __db_qfmgr__
