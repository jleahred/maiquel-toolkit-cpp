#ifndef  __treedb__
#define  __treedb__



#include "components/gen/msg_tree_server.h"



namespace tree_server2 { 
    namespace db {

        

        void init(const std::string& data_tree_filename, const std::string& data_grants_filename);
        void load(void);
        void save(void);


        mtk::list<mtk::gen::msg::sub_tree_item>   get_items_for_branch__ifso(const mtk::gen::msg::req_tree_items& tree_request);
        
                                                                    
        
    };  //      namespace   db {
};      //  namespace tree_server2 { 


#endif   //  __treedb__
