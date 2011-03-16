
#ifndef  __msg_tree_server__
#define  __msg_tree_server__


// generated automatically
// coded last modification:        Wed Mar 16 12:44:25 2011


#include "support/nullable.hpp"
#include "support/fixed_number.h"
#include "support/date_time.h"
#include "support/list.hpp"
#include "support/alarm.h"
#include "support/exec_max_frec.h"
#include "mtk_qpid/qpid_msg_support.hpp"
#include "support/mtk_string.h"
#include <qpid/messaging/Message.h>
#include "mtk_qpid/msg_control_fields.h"
#include "mtk_qpid/mtk_qpid.hpp"


#include "support/mtk_string.h"
#include "components/msg_common.h"

namespace mtk { 
namespace gen { 
namespace msg { 




//-------------------------------
//      sub_tree_item
//-------------------------------    
class sub_tree_item     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_tree_item (    const std::string&  _branch,   const std::string&  _user_name,   const mtk::nullable<mtk::msg::sub_product_code>&  _product_code );
    explicit sub_tree_item ( const qpid::messaging::Message& message );
    virtual ~sub_tree_item (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_tree_item"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_tree_item"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    std::string                               branch; 
    std::string                               user_name; 
    mtk::nullable<mtk::msg::sub_product_code>  product_code; 



    //  subject info
    
private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      tree_request_items
//-------------------------------    
class tree_request_items     
{
public:
    //  inner classes

    
    // constructor
    explicit tree_request_items (    const mtk::msg::sub_request_info&  _request_info,   const std::string&  _branch );
    explicit tree_request_items ( const qpid::messaging::Message& message );
    virtual ~tree_request_items (){};
    virtual std::string get_message_type_as_string       (void) const  { return "tree_request_items"; };
    static  std::string static_get_message_type_as_string(void)        { return "tree_request_items"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 
    std::string                               branch; 



    //  subject info
    static std::string  get_in_subject (const std::string& request_info_process_location_location_client_code);
virtual std::string  get_out_subject (void) const;

private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      tree_response_items
//-------------------------------    
class tree_response_items     
{
public:
    //  inner classes

    
    // constructor
    explicit tree_response_items (    const mtk::msg::sub_r_response&  _response_info,   const sub_tree_item&  _item );
    explicit tree_response_items ( const qpid::messaging::Message& message );
    virtual ~tree_response_items (){};
    virtual std::string get_message_type_as_string       (void) const  { return "tree_response_items"; };
    static  std::string static_get_message_type_as_string(void)        { return "tree_response_items"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    mtk::msg::sub_r_response                  response_info; 
    sub_tree_item                             item; 



    //  subject info
    static std::string  get_in_subject (const std::string& response_info_request_info_process_location_location_client_code,const std::string& response_info_request_info_process_location_location_machine,const std::string& response_info_request_info_process_location_process_uuid,const std::string& response_info_request_info_req_id_sess_id,const std::string& response_info_request_info_req_id_req_code);
virtual std::string  get_out_subject (void) const;

private:
    std::string check_recomended(void) const;
};




    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_tree_item & c);

bool operator== (const sub_tree_item& a, const sub_tree_item& b);
bool operator!= (const sub_tree_item& a, const sub_tree_item& b);

    std::ostream& operator<< (std::ostream& o, const tree_request_items & c);

bool operator== (const tree_request_items& a, const tree_request_items& b);
bool operator!= (const tree_request_items& a, const tree_request_items& b);

    std::ostream& operator<< (std::ostream& o, const tree_response_items & c);

bool operator== (const tree_response_items& a, const tree_response_items& b);
bool operator!= (const tree_response_items& a, const tree_response_items& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_tree_item& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_tree_item& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_tree_item>& a, const std::string& field);
void copy (sub_tree_item& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const tree_request_items& a);
void __internal_add2map (qpid::types::Variant::Map& map, const tree_request_items& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<tree_request_items>& a, const std::string& field);
void copy (tree_request_items& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const tree_response_items& a);
void __internal_add2map (qpid::types::Variant::Map& map, const tree_response_items& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<tree_response_items>& a, const std::string& field);
void copy (tree_response_items& a, const qpid::types::Variant& map);

    sub_tree_item  __internal_get_default(sub_tree_item *);
    
    tree_request_items  __internal_get_default(tree_request_items *);
    
    tree_response_items  __internal_get_default(tree_response_items *);
    

};   //namespace mtk {
};   //namespace gen {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::gen::msg::sub_tree_item)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::gen::msg::tree_request_items)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::gen::msg::tree_response_items)




#endif
