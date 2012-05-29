
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

#include "mtk_qpid/mtk_qpid.h"


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
    explicit sub_order_id ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_order_id (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_order_id"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_order_id"; };
    
    

    

    
    
    
    

    // fields



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      sub_exec_conf
//-------------------------------    
class sub_exec_conf     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_exec_conf (    const std::string&  _exec_id,   const mtk::FixedNumber&  _price,   const mtk::FixedNumber&  _quantity );
    explicit sub_exec_conf ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_exec_conf (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_exec_conf"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_exec_conf"; };
    
    

    

    
    
    
    

    // fields
    std::string                               exec_id; 
    mtk::FixedNumber                          price; 
    mtk::FixedNumber                          quantity; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      sub_total_executions
//-------------------------------    
class sub_total_executions     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_total_executions (    const mtk::Double&  _sum_price_by_qty,   const mtk::FixedNumber&  _acc_quantity,   const mtk::FixedNumber&  _remaining_qty );
    explicit sub_total_executions ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_total_executions (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_total_executions"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_total_executions"; };
    
    

    

    
    
    
    

    // fields
    mtk::Double                               sum_price_by_qty; 
    mtk::FixedNumber                          acc_quantity; 
    mtk::FixedNumber                          remaining_qty; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      sub_account_info
//-------------------------------    
class sub_account_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_account_info (    const std::string&  _name,   const std::string&  _client_code );
    explicit sub_account_info ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_account_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_account_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_account_info"; };
    
    

    

    
    
    
    

    // fields
    std::string                               name; 
    std::string                               client_code; 




    //   KEY INFO
        typedef decltype(name) key_type;
        key_type    get_key(void) const  {   return  name;  }
    //   KEY INFO


    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      sub_invariant_order_info
//-------------------------------    
class sub_invariant_order_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_invariant_order_info (    const sub_order_id&  _order_id,   const mtk::msg::sub_product_code&  _product_code,   const enBuySell&  _side,   const sub_account_info&  _account,   const std::string&  _time_in_force,   const bool&  _automatic );
    explicit sub_invariant_order_info ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_invariant_order_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_invariant_order_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_invariant_order_info"; };
    
    

    

    
    
    
    

    // fields
    sub_order_id                              order_id; 
    mtk::msg::sub_product_code                product_code; 
    enBuySell                                 side; 
    sub_account_info                          account; 
    std::string                               time_in_force; 
    bool                                      automatic; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      RQ_XX
//-------------------------------    
class RQ_XX     
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_XX (    const sub_invariant_order_info&  _invariant,   const mtk::msg::sub_request_info&  _request_info,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
    explicit RQ_XX ( const qpid::types::Variant::Map&  mv );
    virtual ~RQ_XX (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_XX"; };
    static  std::string static_get_message_type_as_string(void)        { return "RQ_XX"; };
    
    

    

    
    
    
    

    // fields
    sub_invariant_order_info                  invariant; 
    mtk::msg::sub_request_info                request_info; 
    mtk::msg::sub_control_fluct               orig_control_fluct; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      CF_XX
//-------------------------------    
class CF_XX     
{
public:
    //  inner classes

    
    // constructor
    explicit CF_XX (    const sub_invariant_order_info&  _invariant,   const std::string&  _market_order_id,   const mtk::msg::sub_request_id&  _req_id,   const sub_total_executions&  _total_execs,   const std::string&  _description,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
    explicit CF_XX ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_XX (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_XX"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_XX"; };
    
    

    

    
    
    
    

    // fields
    sub_invariant_order_info                  invariant; 
    std::string                               market_order_id; 
    mtk::msg::sub_request_id                  req_id; 
    sub_total_executions                      total_execs; 
    std::string                               description; 
    mtk::msg::sub_control_fluct               orig_control_fluct; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      RQ_ORDERS_STATUS
//-------------------------------    
class RQ_ORDERS_STATUS     
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_ORDERS_STATUS (    const mtk::msg::sub_request_info&  _request_info,   const std::string&  _market,   const sub_account_info&  _account );
    explicit RQ_ORDERS_STATUS ( const qpid::types::Variant::Map&  mv );
    virtual ~RQ_ORDERS_STATUS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_ORDERS_STATUS"; };
    static  std::string static_get_message_type_as_string(void)        { return "RQ_ORDERS_STATUS"; };
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 
    std::string                               market; 
    sub_account_info                          account; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& account_client_code,const std::string& market);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      CF_EXLK
//-------------------------------    
class CF_EXLK        :  public  CF_XX
{
public:
    //  inner classes

    
    // constructor
    explicit CF_EXLK (  const CF_XX&  parent,   const sub_exec_conf&  _executed_pos );
    explicit CF_EXLK ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_EXLK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_EXLK"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_EXLK"; };
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    sub_exec_conf                             executed_pos; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      CF_ST_EX
//-------------------------------    
class CF_ST_EX        :  public  CF_EXLK
{
public:
    //  inner classes

    
    // constructor
    explicit CF_ST_EX (  const CF_EXLK&  parent,   const mtk::msg::sub_gen_response_location&  _gen_response_location );
    explicit CF_ST_EX ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_ST_EX (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_ST_EX"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_ST_EX"; };
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_gen_response_location       gen_response_location; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& gen_response_location_broker_code,const std::string& gen_response_location_session_id);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      RQ_EXECS_HISTORIC
//-------------------------------    
class RQ_EXECS_HISTORIC     
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_EXECS_HISTORIC (    const mtk::msg::sub_request_info&  _request_info,   const mtk::DateTime&  _date );
    explicit RQ_EXECS_HISTORIC ( const qpid::types::Variant::Map&  mv );
    virtual ~RQ_EXECS_HISTORIC (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_EXECS_HISTORIC"; };
    static  std::string static_get_message_type_as_string(void)        { return "RQ_EXECS_HISTORIC"; };
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 
    mtk::DateTime                             date; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& request_info_process_info_location_broker_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      CF_EX_HIST
//-------------------------------    
class CF_EX_HIST        :  public  CF_EXLK
{
public:
    //  inner classes

    
    // constructor
    explicit CF_EX_HIST (  const CF_EXLK&  parent,   const mtk::msg::sub_gen_response_location2&  _gen_response_location2 );
    explicit CF_EX_HIST ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_EX_HIST (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_EX_HIST"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_EX_HIST"; };
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_gen_response_location2      gen_response_location2; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& gen_response_location2_broker_code,const std::string& gen_response_location2_req_id_session_id,const std::string& gen_response_location2_req_id_req_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
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


    bool operator< (const sub_account_info& a, const sub_account_info& b);

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

    std::ostream& operator<< (std::ostream& o, const RQ_ORDERS_STATUS & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_ORDERS_STATUS & c);
   void           operator >> (const YAML::Node& n,       RQ_ORDERS_STATUS & c);

bool operator== (const RQ_ORDERS_STATUS& a, const RQ_ORDERS_STATUS& b);
bool operator!= (const RQ_ORDERS_STATUS& a, const RQ_ORDERS_STATUS& b);

    std::ostream& operator<< (std::ostream& o, const CF_EXLK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_EXLK & c);
   void           operator >> (const YAML::Node& n,       CF_EXLK & c);

bool operator== (const CF_EXLK& a, const CF_EXLK& b);
bool operator!= (const CF_EXLK& a, const CF_EXLK& b);

    std::ostream& operator<< (std::ostream& o, const CF_ST_EX & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_ST_EX & c);
   void           operator >> (const YAML::Node& n,       CF_ST_EX & c);

bool operator== (const CF_ST_EX& a, const CF_ST_EX& b);
bool operator!= (const CF_ST_EX& a, const CF_ST_EX& b);

    std::ostream& operator<< (std::ostream& o, const RQ_EXECS_HISTORIC & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_EXECS_HISTORIC & c);
   void           operator >> (const YAML::Node& n,       RQ_EXECS_HISTORIC & c);

bool operator== (const RQ_EXECS_HISTORIC& a, const RQ_EXECS_HISTORIC& b);
bool operator!= (const RQ_EXECS_HISTORIC& a, const RQ_EXECS_HISTORIC& b);

    std::ostream& operator<< (std::ostream& o, const CF_EX_HIST & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_EX_HIST & c);
   void           operator >> (const YAML::Node& n,       CF_EX_HIST & c);

bool operator== (const CF_EX_HIST& a, const CF_EX_HIST& b);
bool operator!= (const CF_EX_HIST& a, const CF_EX_HIST& b);

void __internal_add2map (qpid::types::Variant::Map& map, const sub_order_id& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_order_id>& a, const std::string& field);
void copy (sub_order_id& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_exec_conf& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_exec_conf>& a, const std::string& field);
void copy (sub_exec_conf& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_total_executions& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_total_executions>& a, const std::string& field);
void copy (sub_total_executions& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_account_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_account_info>& a, const std::string& field);
void copy (sub_account_info& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_invariant_order_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_invariant_order_info>& a, const std::string& field);
void copy (sub_invariant_order_info& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_XX& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_XX>& a, const std::string& field);
void copy (RQ_XX& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_XX& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_XX>& a, const std::string& field);
void copy (CF_XX& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_ORDERS_STATUS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_ORDERS_STATUS>& a, const std::string& field);
void copy (RQ_ORDERS_STATUS& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_EXLK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_EXLK>& a, const std::string& field);
void copy (CF_EXLK& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_ST_EX& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_ST_EX>& a, const std::string& field);
void copy (CF_ST_EX& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_EXECS_HISTORIC& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_EXECS_HISTORIC>& a, const std::string& field);
void copy (RQ_EXECS_HISTORIC& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_EX_HIST& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_EX_HIST>& a, const std::string& field);
void copy (CF_EX_HIST& a, const qpid::types::Variant& map);

    sub_order_id  __internal_get_default(sub_order_id *);
    
    sub_exec_conf  __internal_get_default(sub_exec_conf *);
    
    sub_total_executions  __internal_get_default(sub_total_executions *);
    
    sub_account_info  __internal_get_default(sub_account_info *);
    
    sub_invariant_order_info  __internal_get_default(sub_invariant_order_info *);
    
    RQ_XX  __internal_get_default(RQ_XX *);
    
    CF_XX  __internal_get_default(CF_XX *);
    
    RQ_ORDERS_STATUS  __internal_get_default(RQ_ORDERS_STATUS *);
    
    CF_EXLK  __internal_get_default(CF_EXLK *);
    
    CF_ST_EX  __internal_get_default(CF_ST_EX *);
    
    RQ_EXECS_HISTORIC  __internal_get_default(RQ_EXECS_HISTORIC *);
    
    CF_EX_HIST  __internal_get_default(CF_EX_HIST *);
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RQ_ORDERS_STATUS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_EXLK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_ST_EX)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RQ_EXECS_HISTORIC)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_EX_HIST)




#endif
