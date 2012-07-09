
#ifndef  __msg_common__
#define  __msg_common__


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


#include "support/mtk_string.h"
#include "msg_common_support.h"

namespace mtk { 
namespace msg { 




//-------------------------------
//      sub_location
//-------------------------------    
class sub_location     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_location (    const std::string&  _broker_code,   const std::string&  _machine );
    explicit sub_location ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_location (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_location"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_location"; }
    
    

    

    
    
    
    

    // fields
    std::string                               broker_code; 
    std::string                               machine; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_location__qpid_map
        {
        public:
            explicit  sub_location__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_location__qpid_map ( const sub_location&  c ) : m_static(c) {}
            explicit  sub_location__qpid_map (    const std::string&  _broker_code,   const std::string&  _machine );
            ~sub_location__qpid_map() {};
            

            sub_location                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_process_info
//-------------------------------    
class sub_process_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_process_info (    const sub_location&  _location,   const std::string&  _process_name,   const std::string&  _process_uuid,   const std::string&  _version,   const std::string&  _cli_srv );
    explicit sub_process_info ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_process_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_process_info"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_process_info"; }
    
    

    

    
    
    
    

    // fields
    sub_location                              location; 
    std::string                               process_name; 
    std::string                               process_uuid; 
    std::string                               version; 
    std::string                               cli_srv; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_process_info__qpid_map
        {
        public:
            explicit  sub_process_info__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_process_info__qpid_map ( const sub_process_info&  c ) : m_static(c) {}
            explicit  sub_process_info__qpid_map (    const sub_location&  _location,   const std::string&  _process_name,   const std::string&  _process_uuid,   const std::string&  _version,   const std::string&  _cli_srv );
            ~sub_process_info__qpid_map() {};
            

            sub_process_info                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_control_fluct
//-------------------------------    
class sub_control_fluct     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_control_fluct (    const std::string&  _key,   const mtk::DateTime&  _datetime );
    explicit sub_control_fluct ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_control_fluct (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_control_fluct"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_control_fluct"; }
    
    

    

    
    
    
    

    // fields
    std::string                               key; 
    mtk::DateTime                             datetime; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_control_fluct__qpid_map
        {
        public:
            explicit  sub_control_fluct__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_control_fluct__qpid_map ( const sub_control_fluct&  c ) : m_static(c) {}
            explicit  sub_control_fluct__qpid_map (    const std::string&  _key,   const mtk::DateTime&  _datetime );
            ~sub_control_fluct__qpid_map() {};
            

            sub_control_fluct                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_request_id
//-------------------------------    
class sub_request_id     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_request_id (    const std::string&  _session_id,   const std::string&  _req_code );
    explicit sub_request_id ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_request_id (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_request_id"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_request_id"; }
    
    

    

    
    
    
    

    // fields
    std::string                               session_id; 
    std::string                               req_code; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_request_id__qpid_map
        {
        public:
            explicit  sub_request_id__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_request_id__qpid_map ( const sub_request_id&  c ) : m_static(c) {}
            explicit  sub_request_id__qpid_map (    const std::string&  _session_id,   const std::string&  _req_code );
            ~sub_request_id__qpid_map() {};
            

            sub_request_id                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_request_info
//-------------------------------    
class sub_request_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_request_info (    const sub_request_id&  _req_id,   const sub_process_info&  _process_info );
    explicit sub_request_info ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_request_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_request_info"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_request_info"; }
    
    

    

    
    
    
    

    // fields
    sub_request_id                            req_id; 
    sub_process_info                          process_info; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_request_info__qpid_map
        {
        public:
            explicit  sub_request_info__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_request_info__qpid_map ( const sub_request_info&  c ) : m_static(c) {}
            explicit  sub_request_info__qpid_map (    const sub_request_id&  _req_id,   const sub_process_info&  _process_info );
            ~sub_request_info__qpid_map() {};
            

            sub_request_info                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_r_response
//-------------------------------    
class sub_r_response     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_r_response (    const sub_process_info&  _process_info,   const sub_request_info&  _request_info,   const int16_t&  _seq_number,   const bool&  _is_last_response );
    explicit sub_r_response ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_r_response (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_r_response"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_r_response"; }
    
    

    

    
    
    
    

    // fields
    sub_process_info                          process_info; 
    sub_request_info                          request_info; 
    int16_t                                   seq_number; 
    bool                                      is_last_response; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_r_response__qpid_map
        {
        public:
            explicit  sub_r_response__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_r_response__qpid_map ( const sub_r_response&  c ) : m_static(c) {}
            explicit  sub_r_response__qpid_map (    const sub_process_info&  _process_info,   const sub_request_info&  _request_info,   const int16_t&  _seq_number,   const bool&  _is_last_response );
            ~sub_r_response__qpid_map() {};
            

            sub_r_response                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_gen_response_location
//-------------------------------    
class sub_gen_response_location     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_gen_response_location (    const std::string&  _session_id,   const std::string&  _broker_code );
    explicit sub_gen_response_location ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_gen_response_location (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_gen_response_location"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_gen_response_location"; }
    
    

    

    
    
    
    

    // fields
    std::string                               session_id; 
    std::string                               broker_code; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_gen_response_location__qpid_map
        {
        public:
            explicit  sub_gen_response_location__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_gen_response_location__qpid_map ( const sub_gen_response_location&  c ) : m_static(c) {}
            explicit  sub_gen_response_location__qpid_map (    const std::string&  _session_id,   const std::string&  _broker_code );
            ~sub_gen_response_location__qpid_map() {};
            

            sub_gen_response_location                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_gen_response_location2
//-------------------------------    
class sub_gen_response_location2     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_gen_response_location2 (    const sub_request_id&  _req_id,   const std::string&  _broker_code );
    explicit sub_gen_response_location2 ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_gen_response_location2 (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_gen_response_location2"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_gen_response_location2"; }
    
    

    

    
    
    
    

    // fields
    sub_request_id                            req_id; 
    std::string                               broker_code; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_gen_response_location2__qpid_map
        {
        public:
            explicit  sub_gen_response_location2__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_gen_response_location2__qpid_map ( const sub_gen_response_location2&  c ) : m_static(c) {}
            explicit  sub_gen_response_location2__qpid_map (    const sub_request_id&  _req_id,   const std::string&  _broker_code );
            ~sub_gen_response_location2__qpid_map() {};
            

            sub_gen_response_location2                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_product_code
//-------------------------------    
class sub_product_code     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_product_code (    const std::string&  _market,   const std::string&  _product );
    explicit sub_product_code ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_product_code (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_product_code"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_product_code"; }
    
    

    

    
    
    
    

    // fields
    std::string                               market; 
    std::string                               product; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_product_code__qpid_map
        {
        public:
            explicit  sub_product_code__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_product_code__qpid_map ( const sub_product_code&  c ) : m_static(c) {}
            explicit  sub_product_code__qpid_map (    const std::string&  _market,   const std::string&  _product );
            ~sub_product_code__qpid_map() {};
            

            sub_product_code                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        
    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_location & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_location & c);
   void           operator >> (const YAML::Node& n,       sub_location & c);

bool operator== (const sub_location& a, const sub_location& b);
bool operator!= (const sub_location& a, const sub_location& b);

    std::ostream& operator<< (std::ostream& o, const sub_process_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_process_info & c);
   void           operator >> (const YAML::Node& n,       sub_process_info & c);

bool operator== (const sub_process_info& a, const sub_process_info& b);
bool operator!= (const sub_process_info& a, const sub_process_info& b);

    std::ostream& operator<< (std::ostream& o, const sub_control_fluct & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_control_fluct & c);
   void           operator >> (const YAML::Node& n,       sub_control_fluct & c);

bool operator== (const sub_control_fluct& a, const sub_control_fluct& b);
bool operator!= (const sub_control_fluct& a, const sub_control_fluct& b);

    std::ostream& operator<< (std::ostream& o, const sub_request_id & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_request_id & c);
   void           operator >> (const YAML::Node& n,       sub_request_id & c);

bool operator== (const sub_request_id& a, const sub_request_id& b);
bool operator!= (const sub_request_id& a, const sub_request_id& b);


    bool operator< (const sub_request_id& a, const sub_request_id& b);

    std::ostream& operator<< (std::ostream& o, const sub_request_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_request_info & c);
   void           operator >> (const YAML::Node& n,       sub_request_info & c);

bool operator== (const sub_request_info& a, const sub_request_info& b);
bool operator!= (const sub_request_info& a, const sub_request_info& b);

    std::ostream& operator<< (std::ostream& o, const sub_r_response & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_r_response & c);
   void           operator >> (const YAML::Node& n,       sub_r_response & c);

bool operator== (const sub_r_response& a, const sub_r_response& b);
bool operator!= (const sub_r_response& a, const sub_r_response& b);

    std::ostream& operator<< (std::ostream& o, const sub_gen_response_location & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_gen_response_location & c);
   void           operator >> (const YAML::Node& n,       sub_gen_response_location & c);

bool operator== (const sub_gen_response_location& a, const sub_gen_response_location& b);
bool operator!= (const sub_gen_response_location& a, const sub_gen_response_location& b);

    std::ostream& operator<< (std::ostream& o, const sub_gen_response_location2 & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_gen_response_location2 & c);
   void           operator >> (const YAML::Node& n,       sub_gen_response_location2 & c);

bool operator== (const sub_gen_response_location2& a, const sub_gen_response_location2& b);
bool operator!= (const sub_gen_response_location2& a, const sub_gen_response_location2& b);

    std::ostream& operator<< (std::ostream& o, const sub_product_code & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_product_code & c);
   void           operator >> (const YAML::Node& n,       sub_product_code & c);

bool operator== (const sub_product_code& a, const sub_product_code& b);
bool operator!= (const sub_product_code& a, const sub_product_code& b);

void __internal_add2map (qpid::types::Variant::Map& map, const sub_location& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_location>& a, const std::string& field);
void copy (sub_location& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_process_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_process_info>& a, const std::string& field);
void copy (sub_process_info& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_control_fluct& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_control_fluct>& a, const std::string& field);
void copy (sub_control_fluct& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_request_id& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_request_id>& a, const std::string& field);
void copy (sub_request_id& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_request_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_request_info>& a, const std::string& field);
void copy (sub_request_info& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_r_response& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_r_response>& a, const std::string& field);
void copy (sub_r_response& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_gen_response_location& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_gen_response_location>& a, const std::string& field);
void copy (sub_gen_response_location& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_gen_response_location2& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_gen_response_location2>& a, const std::string& field);
void copy (sub_gen_response_location2& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_product_code& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_product_code>& a, const std::string& field);
void copy (sub_product_code& a, const qpid::types::Variant& map);

    
    
    
//  fordward declarations  dynamic--------------------------------------------------------


inline std::ostream& operator<< (std::ostream& o, const sub_location__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_location__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_location__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_location__qpid_map& a, const sub_location__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_location__qpid_map& a, const sub_location__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_location__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_location__qpid_map>& a, const std::string& field);
void copy (sub_location__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_process_info__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_process_info__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_process_info__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_process_info__qpid_map& a, const sub_process_info__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_process_info__qpid_map& a, const sub_process_info__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_process_info__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_process_info__qpid_map>& a, const std::string& field);
void copy (sub_process_info__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_control_fluct__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_control_fluct__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_control_fluct__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_control_fluct__qpid_map& a, const sub_control_fluct__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_control_fluct__qpid_map& a, const sub_control_fluct__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_control_fluct__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_control_fluct__qpid_map>& a, const std::string& field);
void copy (sub_control_fluct__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_request_id__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_request_id__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_request_id__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_request_id__qpid_map& a, const sub_request_id__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_request_id__qpid_map& a, const sub_request_id__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_request_id__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_request_id__qpid_map>& a, const std::string& field);
void copy (sub_request_id__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_request_info__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_request_info__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_request_info__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_request_info__qpid_map& a, const sub_request_info__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_request_info__qpid_map& a, const sub_request_info__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_request_info__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_request_info__qpid_map>& a, const std::string& field);
void copy (sub_request_info__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_r_response__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_r_response__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_r_response__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_r_response__qpid_map& a, const sub_r_response__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_r_response__qpid_map& a, const sub_r_response__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_r_response__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_r_response__qpid_map>& a, const std::string& field);
void copy (sub_r_response__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_gen_response_location__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_gen_response_location__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_gen_response_location__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_gen_response_location__qpid_map& a, const sub_gen_response_location__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_gen_response_location__qpid_map& a, const sub_gen_response_location__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_gen_response_location__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_gen_response_location__qpid_map>& a, const std::string& field);
void copy (sub_gen_response_location__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_gen_response_location2__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_gen_response_location2__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_gen_response_location2__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_gen_response_location2__qpid_map& a, const sub_gen_response_location2__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_gen_response_location2__qpid_map& a, const sub_gen_response_location2__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_gen_response_location2__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_gen_response_location2__qpid_map>& a, const std::string& field);
void copy (sub_gen_response_location2__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_product_code__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_product_code__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_product_code__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_product_code__qpid_map& a, const sub_product_code__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_product_code__qpid_map& a, const sub_product_code__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_product_code__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_product_code__qpid_map>& a, const std::string& field);
void copy (sub_product_code__qpid_map& a, const qpid::types::Variant& map);

    sub_location  __internal_get_default(sub_location *);
    
        inline sub_location__qpid_map  __internal_get_default(sub_location__qpid_map *) { return  sub_location__qpid_map(__internal_get_default((sub_location*)0));  }

    sub_process_info  __internal_get_default(sub_process_info *);
    
        inline sub_process_info__qpid_map  __internal_get_default(sub_process_info__qpid_map *) { return  sub_process_info__qpid_map(__internal_get_default((sub_process_info*)0));  }

    sub_control_fluct  __internal_get_default(sub_control_fluct *);
    
        inline sub_control_fluct__qpid_map  __internal_get_default(sub_control_fluct__qpid_map *) { return  sub_control_fluct__qpid_map(__internal_get_default((sub_control_fluct*)0));  }

    sub_request_id  __internal_get_default(sub_request_id *);
    
        inline sub_request_id__qpid_map  __internal_get_default(sub_request_id__qpid_map *) { return  sub_request_id__qpid_map(__internal_get_default((sub_request_id*)0));  }

    sub_request_info  __internal_get_default(sub_request_info *);
    
        inline sub_request_info__qpid_map  __internal_get_default(sub_request_info__qpid_map *) { return  sub_request_info__qpid_map(__internal_get_default((sub_request_info*)0));  }

    sub_r_response  __internal_get_default(sub_r_response *);
    
        inline sub_r_response__qpid_map  __internal_get_default(sub_r_response__qpid_map *) { return  sub_r_response__qpid_map(__internal_get_default((sub_r_response*)0));  }

    sub_gen_response_location  __internal_get_default(sub_gen_response_location *);
    
        inline sub_gen_response_location__qpid_map  __internal_get_default(sub_gen_response_location__qpid_map *) { return  sub_gen_response_location__qpid_map(__internal_get_default((sub_gen_response_location*)0));  }

    sub_gen_response_location2  __internal_get_default(sub_gen_response_location2 *);
    
        inline sub_gen_response_location2__qpid_map  __internal_get_default(sub_gen_response_location2__qpid_map *) { return  sub_gen_response_location2__qpid_map(__internal_get_default((sub_gen_response_location2*)0));  }

    sub_product_code  __internal_get_default(sub_product_code *);
    
        inline sub_product_code__qpid_map  __internal_get_default(sub_product_code__qpid_map *) { return  sub_product_code__qpid_map(__internal_get_default((sub_product_code*)0));  }


};   //namespace mtk {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);






#endif
