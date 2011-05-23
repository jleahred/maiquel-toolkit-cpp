
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
//      sub_exec_conf
//-------------------------------    
class sub_exec_conf     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_exec_conf (    const std::string&  _exec_id,   const mtk::FixedNumber&  _price,   const mtk::FixedNumber&  _quantity,   const enBuySell&  _side );
    explicit sub_exec_conf ( const qpid::messaging::Message& message );
    virtual ~sub_exec_conf (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_exec_conf"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_exec_conf"; };
    
    

    // fields
    std::string                               exec_id; 
    mtk::FixedNumber                          price; 
    mtk::FixedNumber                          quantity; 
    enBuySell                                 side; 



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
//      sub_account_info
//-------------------------------    
class sub_account_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_account_info (    const std::string&  _client_code,   const std::string&  _name );
    explicit sub_account_info ( const qpid::messaging::Message& message );
    virtual ~sub_account_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_account_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_account_info"; };
    
    

    // fields
    std::string                               client_code; 
    std::string                               name; 



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      sub_invariant_order_info
//-------------------------------    
class sub_invariant_order_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_invariant_order_info (    const sub_order_id&  _order_id,   const mtk::msg::sub_product_code&  _product_code,   const enBuySell&  _side,   const sub_account_info&  _account );
    explicit sub_invariant_order_info ( const qpid::messaging::Message& message );
    virtual ~sub_invariant_order_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_invariant_order_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_invariant_order_info"; };
    
    

    // fields
    sub_order_id                              order_id; 
    mtk::msg::sub_product_code                product_code; 
    enBuySell                                 side; 
    sub_account_info                          account; 



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
    explicit RQ_XX (    const sub_invariant_order_info&  _invariant,   const mtk::msg::sub_request_info&  _req_info,   const std::string&  _cli_ref,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
    explicit RQ_XX ( const qpid::messaging::Message& message );
    virtual ~RQ_XX (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_XX"; };
    static  std::string static_get_message_type_as_string(void)        { return "RQ_XX"; };
    
    

    // fields
    sub_invariant_order_info                  invariant; 
    mtk::msg::sub_request_info                req_info; 
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
    explicit CF_XX (    const sub_invariant_order_info&  _invariant,   const mtk::msg::sub_request_id&  _req_id,   const std::string&  _cli_ref,   const sub_total_executions&  _total_execs,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
    explicit CF_XX ( const qpid::messaging::Message& message );
    virtual ~CF_XX (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_XX"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_XX"; };
    
    

    // fields
    sub_invariant_order_info                  invariant; 
    mtk::msg::sub_request_id                  req_id; 
    std::string                               cli_ref; 
    sub_total_executions                      total_execs; 
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

    std::ostream& operator<< (std::ostream& o, const sub_exec_conf & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_exec_conf & c);
   void           operator >> (const YAML::Node& n,       sub_exec_conf & c);

bool operator== (const sub_exec_conf& a, const sub_exec_conf& b);
bool operator!= (const sub_exec_conf& a, const sub_exec_conf& b);

    std::ostream& operator<< (std::ostream& o, const sub_total_executions & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_total_executions & c);
   void           operator >> (const YAML::Node& n,       sub_total_executions & c);

bool operator== (const sub_total_executions& a, const sub_total_executions& b);
bool operator!= (const sub_total_executions& a, const sub_total_executions& b);

    std::ostream& operator<< (std::ostream& o, const sub_account_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_account_info & c);
   void           operator >> (const YAML::Node& n,       sub_account_info & c);

bool operator== (const sub_account_info& a, const sub_account_info& b);
bool operator!= (const sub_account_info& a, const sub_account_info& b);

    std::ostream& operator<< (std::ostream& o, const sub_invariant_order_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_invariant_order_info & c);
   void           operator >> (const YAML::Node& n,       sub_invariant_order_info & c);

bool operator== (const sub_invariant_order_info& a, const sub_invariant_order_info& b);
bool operator!= (const sub_invariant_order_info& a, const sub_invariant_order_info& b);

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

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_order_id& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_order_id& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_order_id>& a, const std::string& field);
void copy (sub_order_id& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_exec_conf& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_exec_conf& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_exec_conf>& a, const std::string& field);
void copy (sub_exec_conf& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_total_executions& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_total_executions& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_total_executions>& a, const std::string& field);
void copy (sub_total_executions& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_account_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_account_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_account_info>& a, const std::string& field);
void copy (sub_account_info& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_invariant_order_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_invariant_order_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_invariant_order_info>& a, const std::string& field);
void copy (sub_invariant_order_info& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RQ_XX& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_XX& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_XX>& a, const std::string& field);
void copy (RQ_XX& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const CF_XX& a);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_XX& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_XX>& a, const std::string& field);
void copy (CF_XX& a, const qpid::types::Variant& map);

    sub_order_id  __internal_get_default(sub_order_id *);
    
    sub_exec_conf  __internal_get_default(sub_exec_conf *);
    
    sub_total_executions  __internal_get_default(sub_total_executions *);
    
    sub_account_info  __internal_get_default(sub_account_info *);
    
    sub_invariant_order_info  __internal_get_default(sub_invariant_order_info *);
    
    RQ_XX  __internal_get_default(RQ_XX *);
    
    CF_XX  __internal_get_default(CF_XX *);
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);






#endif
