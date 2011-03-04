
#ifndef  __msg_common__
#define  __msg_common__


// generated automatically
// coded last modification:        Thu Mar  3 09:08:08 2011


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
#include "msg_common_support.h"

namespace mtk { 
namespace msg { 




//-------------------------------
//      sub_request_id
//-------------------------------    
class sub_request_id     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_request_id (    const std::string&  _sess_id,   const std::string&  _req_code );
    explicit sub_request_id ( const qpid::messaging::Message& message );
    virtual ~sub_request_id (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_request_id"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_request_id"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    std::string                               sess_id; 
    std::string                               req_code; 



    //  subject info
    
private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      sub_request_info
//-------------------------------    
class sub_request_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_request_info (    const sub_request_id&  _req_id,   const std::string&  _client );
    explicit sub_request_info ( const qpid::messaging::Message& message );
    virtual ~sub_request_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_request_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_request_info"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    sub_request_id                            req_id; 
    std::string                               client; 



    //  subject info
    
private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      sub_single_product_code
//-------------------------------    
class sub_single_product_code     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_single_product_code (    const std::string&  _market,   const std::string&  _product,   const mtk::nullable<std::string>&  _code );
    explicit sub_single_product_code ( const qpid::messaging::Message& message );
    virtual ~sub_single_product_code (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_single_product_code"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_single_product_code"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    std::string                               market; 
    std::string                               product; 
    mtk::nullable<std::string>                code; 



    //  subject info
    
private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      sub_product_code
//-------------------------------    
class sub_product_code     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_product_code (    const sub_single_product_code&  _sys_code,   const mtk::nullable<sub_single_product_code>&  _aditional_code,   const mtk::nullable<std::string>&  _description );
    explicit sub_product_code ( const qpid::messaging::Message& message );
    virtual ~sub_product_code (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_product_code"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_product_code"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    sub_single_product_code                   sys_code; 
    mtk::nullable<sub_single_product_code>    aditional_code; 
    mtk::nullable<std::string>                description; 



    //  subject info
    
private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      sub_request_r
//-------------------------------    
class sub_request_r     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_request_r (    const std::string&  _request_code );
    explicit sub_request_r ( const qpid::messaging::Message& message );
    virtual ~sub_request_r (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_request_r"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_request_r"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    std::string                               request_code; 



    //  subject info
    
private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      sub_r_response
//-------------------------------    
class sub_r_response     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_r_response (    const std::string&  _request_code,   const int16_t&  _sec_number,   const bool&  _is_last_response );
    explicit sub_r_response ( const qpid::messaging::Message& message );
    virtual ~sub_r_response (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_r_response"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_r_response"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    std::string                               request_code; 
    int16_t                                   sec_number; 
    bool                                      is_last_response; 



    //  subject info
    
private:
    std::string check_recomended(void) const;
};




    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_request_id & c);

bool operator== (const sub_request_id& a, const sub_request_id& b);
bool operator!= (const sub_request_id& a, const sub_request_id& b);

    std::ostream& operator<< (std::ostream& o, const sub_request_info & c);

bool operator== (const sub_request_info& a, const sub_request_info& b);
bool operator!= (const sub_request_info& a, const sub_request_info& b);

    std::ostream& operator<< (std::ostream& o, const sub_single_product_code & c);

bool operator== (const sub_single_product_code& a, const sub_single_product_code& b);
bool operator!= (const sub_single_product_code& a, const sub_single_product_code& b);

    std::ostream& operator<< (std::ostream& o, const sub_product_code & c);

bool operator== (const sub_product_code& a, const sub_product_code& b);
bool operator!= (const sub_product_code& a, const sub_product_code& b);

    std::ostream& operator<< (std::ostream& o, const sub_request_r & c);

bool operator== (const sub_request_r& a, const sub_request_r& b);
bool operator!= (const sub_request_r& a, const sub_request_r& b);

    std::ostream& operator<< (std::ostream& o, const sub_r_response & c);

bool operator== (const sub_r_response& a, const sub_r_response& b);
bool operator!= (const sub_r_response& a, const sub_r_response& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_request_id& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_request_id& a);
void copy (sub_request_id& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_request_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_request_info& a);
void copy (sub_request_info& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_single_product_code& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_single_product_code& a);
void copy (sub_single_product_code& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_product_code& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_product_code& a);
void copy (sub_product_code& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_request_r& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_request_r& a);
void copy (sub_request_r& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_r_response& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_r_response& a);
void copy (sub_r_response& a, const qpid::types::Variant& map);

    sub_request_id  __internal_get_default(sub_request_id *);
    
    sub_request_info  __internal_get_default(sub_request_info *);
    
    sub_single_product_code  __internal_get_default(sub_single_product_code *);
    
    sub_product_code  __internal_get_default(sub_product_code *);
    
    sub_request_r  __internal_get_default(sub_request_r *);
    
    sub_r_response  __internal_get_default(sub_r_response *);
    

};   //namespace mtk {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::msg::sub_request_id)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::msg::sub_request_info)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::msg::sub_single_product_code)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::msg::sub_product_code)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::msg::sub_request_r)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::msg::sub_r_response)




#endif
