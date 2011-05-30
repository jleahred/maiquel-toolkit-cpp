
#ifndef  __msg_tree_server__
#define  __msg_tree_server__


// generated automatically
// coded last modification:        _CODED_LAST_MODIF


#include "yaml/yaml.h"
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
    
    

    // fields
    std::string                               branch; 
    std::string                               user_name; 
    mtk::nullable<mtk::msg::sub_product_code>  product_code; 



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      req_tree_items
//-------------------------------    
class req_tree_items     
{
public:
    //  inner classes

    
    // constructor
    explicit req_tree_items (    const mtk::msg::sub_request_info&  _request_info,   const std::string&  _branch );
    explicit req_tree_items ( const qpid::messaging::Message& message );
    virtual ~req_tree_items (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_tree_items"; };
    static  std::string static_get_message_type_as_string(void)        { return "req_tree_items"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 
    std::string                               branch; 



    //  subject info
    static std::string  get_in_subject (const std::string& request_info_process_info_location_client_code);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      res_tree_items
//-------------------------------    
class res_tree_items     
{
public:
    //  inner classes

    
    // constructor
    explicit res_tree_items (    const mtk::msg::sub_r_response&  _response_info,   const sub_tree_item&  _item );
    explicit res_tree_items ( const qpid::messaging::Message& message );
    virtual ~res_tree_items (){};
    virtual std::string get_message_type_as_string       (void) const  { return "res_tree_items"; };
    static  std::string static_get_message_type_as_string(void)        { return "res_tree_items"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_r_response                  response_info; 
    sub_tree_item                             item; 



    //  subject info
    static std::string  get_in_subject (const std::string& response_info_request_info_process_info_location_client_code,const std::string& response_info_request_info_process_info_location_machine,const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_session_id,const std::string& response_info_request_info_req_id_req_code);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_tree_item & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_tree_item & c);
   void           operator >> (const YAML::Node& n,       sub_tree_item & c);

bool operator== (const sub_tree_item& a, const sub_tree_item& b);
bool operator!= (const sub_tree_item& a, const sub_tree_item& b);

    std::ostream& operator<< (std::ostream& o, const req_tree_items & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const req_tree_items & c);
   void           operator >> (const YAML::Node& n,       req_tree_items & c);

bool operator== (const req_tree_items& a, const req_tree_items& b);
bool operator!= (const req_tree_items& a, const req_tree_items& b);

    std::ostream& operator<< (std::ostream& o, const res_tree_items & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const res_tree_items & c);
   void           operator >> (const YAML::Node& n,       res_tree_items & c);

bool operator== (const res_tree_items& a, const res_tree_items& b);
bool operator!= (const res_tree_items& a, const res_tree_items& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_tree_item& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_tree_item& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_tree_item>& a, const std::string& field);
void copy (sub_tree_item& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const req_tree_items& a);
void __internal_add2map (qpid::types::Variant::Map& map, const req_tree_items& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_tree_items>& a, const std::string& field);
void copy (req_tree_items& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const res_tree_items& a);
void __internal_add2map (qpid::types::Variant::Map& map, const res_tree_items& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_tree_items>& a, const std::string& field);
void copy (res_tree_items& a, const qpid::types::Variant& map);

    sub_tree_item  __internal_get_default(sub_tree_item *);
    
    req_tree_items  __internal_get_default(req_tree_items *);
    
    res_tree_items  __internal_get_default(res_tree_items *);
    

};   //namespace mtk {
};   //namespace gen {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::gen::msg::req_tree_items)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::gen::msg::res_tree_items)




#endif
