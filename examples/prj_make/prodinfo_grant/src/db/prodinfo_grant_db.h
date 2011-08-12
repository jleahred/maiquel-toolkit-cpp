#ifndef  __prod_info_grant_db_33__
#define  __prod_info_grant_db_33__



#include "components/gen/msg_tree_server.h"


namespace mtk { namespace prices { namespace msg { class  req_product_info; }}};


namespace prodinfo_grant { 
    namespace db {

        

        void init(const std::string& filename);
        void load(void);
        void save(void);


        bool has_grants(const mtk::prices::msg::req_product_info&  pi_request);

        
                                                                    
        
    };  //      namespace   db {
};      //  namespace prodinfo_grant { 


#endif   //  __prod_info_grant_db_33__
