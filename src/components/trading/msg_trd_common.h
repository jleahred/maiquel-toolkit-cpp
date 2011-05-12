
#ifndef  __msg_trd_common__
#define  __msg_trd_common__


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


#include "components/msg_common.h"
#include "support/mtk_double.h"
#include "msg_trd_common_support.h"

namespace mtk { 
namespace trd { 
namespace msg { 




//-------------------------------
//      sub_order_id
//-------------------------------    
class sub_order_id        :  public  mtk::msg::sub_request_id
{
public:
    //  inner classes

    
    // constructor
    explicit sub_order_id (  const mtk::msg::sub_request_id&  parent );
    explicit sub_order_id ( const qpid::messaging::Message& message );
    virtual ~sub_order_id (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_order_id"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_order_id"; };
    
    

    // fields



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      sub_total_executions
//-------------------------------    
class sub_total_executions     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_total_executions (    const mtk::Double&  _sum_price_by_qty,   const mtk::FixedNumber&  _quantity,   const mtk::FixedNumber&  _remaining_qty );
    explicit sub_total_executions ( const qpid::messaging::Message& message );
    virtual ~sub_total_executions (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_total_executions"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_total_executions"; };
    
    

    // fields
    mtk::Double                               sum_price_by_qty; 
    mtk::FixedNumber                          quantity; 
    mtk::FixedNumber                          remaining_qty; 



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      sub_order_xx_confirmated
//-------------------------------    
class sub_order_xx_confirmated     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_order_xx_confirmated (    const sub_order_id&  _order_id,   const sub_total_executions&  _total_execs,   const std::string&  _cli_ref );
    explicit sub_order_xx_confirmated ( const qpid::messaging::Message& message );
    virtual ~sub_order_xx_confirmated (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_order_xx_confirmated"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_order_xx_confirmated"; };
    
    

    // fields
    sub_order_id                              order_id; 
    sub_total_executions                      total_execs; 
    std::string                               cli_ref; 



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      RQ_XX
//-------------------------------    
class RQ_XX     
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_XX (    const mtk::msg::sub_request_info&  _req_info,   const sub_order_id&  _order_id,   const mtk::msg::sub_product_code&  _product_code,   const std::string&  _cli_ref,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
    explicit RQ_XX ( const qpid::messaging::Message& message );
    virtual ~RQ_XX (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_XX"; };
    static  std::string static_get_message_type_as_string(void)        { return "RQ_XX"; };
    
    

    // fields
    mtk::msg::sub_request_info                req_info; 
    sub_order_id                              order_id; 
    mtk::msg::sub_product_code                product_code; 
    std::string                               cli_ref; 
    mtk::msg::sub_control_fluct               orig_control_fluct; 



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      CF_XX
//-------------------------------    
class CF_XX     
{
public:
    //  inner classes

    
    // constructor
    explicit CF_XX (    const mtk::msg::sub_request_info&  _req_info,   const mtk::msg::sub_product_code&  _product_code,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
    explicit CF_XX ( const qpid::messaging::Message& message );
    virtual ~CF_XX (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_XX"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_XX"; };
    
    

    // fields
    mtk::msg::sub_request_info                req_info; 
    mtk::msg::sub_product_code                product_code; 
    mtk::msg::sub_control_fluct               orig_control_fluct; 



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      RJ_XX
//-------------------------------    
class RJ_XX     
{
public:
    //  inner classes

    
    // constructor
    explicit RJ_XX (    const mtk::msg::sub_request_info&  _req_info,   const mtk::msg::sub_product_code&  _product_code,   const std::string&  _description,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
    explicit RJ_XX ( const qpid::messaging::Message& message );
    virtual ~RJ_XX (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RJ_XX"; };
    static  std::string static_get_message_type_as_string(void)        { return "RJ_XX"; };
    
    

    // fields
    mtk::msg::sub_request_info                req_info; 
    mtk::msg::sub_product_code                product_code; 
    std::string                               description; 
    mtk::msg::sub_control_fluct               orig_control_fluct; 



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_order_id & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_order_id & c);
   void           operator >> (const YAML::Node& n,       sub_order_id & c);

bool operator== (const sub_order_id& a, const sub_order_id& b);
bool operator!= (const sub_order_id& a, const sub_order_id& b);

    std::ostream& operator<< (std::ostream& o, const sub_total_executions & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_total_executions & c);
   void           operator >> (const YAML::Node& n,       sub_total_executions & c);

bool operator== (const sub_total_executions& a, const sub_total_executions& b);
bool operator!= (const sub_total_executions& a, const sub_total_executions& b);

    std::ostream& operator<< (std::ostream& o, const sub_order_xx_confirmated & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_order_xx_confirmated & c);
   void           operator >> (const YAML::Node& n,       sub_order_xx_confirmated & c);

bool operator== (const sub_order_xx_confirmated& a, const sub_order_xx_confirmated& b);
bool operator!= (const sub_order_xx_confirmated& a, const sub_order_xx_confirmated& b);

    std::ostream& operator<< (std::ostream& o, const RQ_XX & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_XX & c);
   void           operator >> (const YAML::Node& n,       RQ_XX & c);

bool operator== (const RQ_XX& a, const RQ_XX& b);
bool operator!= (const RQ_XX& a, const RQ_XX& b);

    std::ostream& operator<< (std::ostream& o, const CF_XX & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_XX & c);
   void           operator >> (const YAML::Node& n,       CF_XX & c);

bool operator== (const CF_XX& a, const CF_XX& b);
bool operator!= (const CF_XX& a, const CF_XX& b);

    std::ostream& operator<< (std::ostream& o, const RJ_XX & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RJ_XX & c);
   void           operator >> (const YAML::Node& n,       RJ_XX & c);

bool operator== (const RJ_XX& a, const RJ_XX& b);
bool operator!= (const RJ_XX& a, const RJ_XX& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_order_id& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_order_id& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_order_id>& a, const std::string& field);
void copy (sub_order_id& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_total_executions& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_total_executions& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_total_executions>& a, const std::string& field);
void copy (sub_total_executions& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_order_xx_confirmated& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_order_xx_confirmated& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_order_xx_confirmated>& a, const std::string& field);
void copy (sub_order_xx_confirmated& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RQ_XX& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_XX& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_XX>& a, const std::string& field);
void copy (RQ_XX& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const CF_XX& a);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_XX& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_XX>& a, const std::string& field);
void copy (CF_XX& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RJ_XX& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_XX& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_XX>& a, const std::string& field);
void copy (RJ_XX& a, const qpid::types::Variant& map);

    sub_order_id  __internal_get_default(sub_order_id *);
    
    sub_total_executions  __internal_get_default(sub_total_executions *);
    
    sub_order_xx_confirmated  __internal_get_default(sub_order_xx_confirmated *);
    
    RQ_XX  __internal_get_default(RQ_XX *);
    
    CF_XX  __internal_get_default(CF_XX *);
    
    RJ_XX  __internal_get_default(RJ_XX *);
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);






#endif
