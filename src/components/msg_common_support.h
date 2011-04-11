#ifndef  __msg_common_support__
#define  __msg_common_support__




namespace mtk {
    namespace msg {
      
        class sub_request_id;
        class sub_product_code;
        class sub_single_product_code;
        //    implemented on msg_common_support.cpp
        bool is_valid  (const sub_request_id& req_info);
        bool is_valid  (const sub_product_code& pc);
        bool operator< (const sub_single_product_code& p1, const sub_single_product_code& p2);        
        bool operator< (const sub_product_code& p1, const sub_product_code& p2);        


    };   //namespace msg {
};  //namespace mtk {


#endif