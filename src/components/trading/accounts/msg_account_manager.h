
#ifndef  __msg_account_manager__
#define  __msg_account_manager__


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
#include "components/trading/msg_trd_common.h"
#include "components/acs/msg_acs.h"

namespace mtk { 
namespace trd { 
namespace account { 
namespace msg { 




//-------------------------------
//      sub_grant
//-------------------------------    
class sub_grant     
{
public:
    //  inner classes

    
    //-------------------------------
    //      IC_key
    //-------------------------------    
    class IC_key     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit IC_key (    const std::string&  _market,   const mtk::trd::msg::sub_account_info&  _account );
        explicit IC_key ( const qpid::types::Variant::Map&  mv );
        virtual ~IC_key (){};
        virtual std::string get_message_type_as_string       (void) const  { return "IC_key"; }
        static  std::string static_get_message_type_as_string(void)        { return "IC_key"; }
        
        
    
        
    
        
        
        
        
    
        // fields
        std::string                               market; 
        mtk::trd::msg::sub_account_info           account; 
    
    
    
        //  ADDRESS info
    
    
    
        //  subject info
        
    
        
        
        
        
        void        before_send(void) const;
        
        void check_recomended(void) const;
    };
    
    
    
    
    // constructor
    explicit sub_grant (    const sub_grant::IC_key&  _key,   const std::string&  _type );
    explicit sub_grant ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_grant (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_grant"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_grant"; }
    
    

    

    
    
    
    

    // fields
    IC_key                                    key; 
    std::string                               type; 




    //   KEY INFO
        typedef decltype(key) key_type;
        key_type    get_key(void) const  {   return  key;  }
    //   KEY INFO


    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_grant__qpid_map
        {
        public:
            explicit  sub_grant__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_grant__qpid_map ( const sub_grant&  c ) : m_static(c) {}
            explicit  sub_grant__qpid_map (    const sub_grant::IC_key&  _key,   const std::string&  _type );
            ~sub_grant__qpid_map() {};
            

            sub_grant                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      rq_accounts
//-------------------------------    
class rq_accounts     
{
public:
    //  inner classes

    
    // constructor
    explicit rq_accounts (    const mtk::msg::sub_request_info&  _request_info );
    explicit rq_accounts ( const qpid::types::Variant::Map&  mv );
    virtual ~rq_accounts (){};
    virtual std::string get_message_type_as_string       (void) const  { return "rq_accounts"; }
    static  std::string static_get_message_type_as_string(void)        { return "rq_accounts"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 



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



        //  qpid_variant wrapper for dynamic
        class rq_accounts__qpid_map
        {
        public:
            explicit  rq_accounts__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  rq_accounts__qpid_map ( const rq_accounts&  c ) : m_static(c) {}
            explicit  rq_accounts__qpid_map (    const mtk::msg::sub_request_info&  _request_info );
            ~rq_accounts__qpid_map() {};
            

            rq_accounts                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  rq_accounts::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  rq_accounts::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  rq_accounts::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  rq_accounts::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      conf_add_accounts
//-------------------------------    
class conf_add_accounts     
{
public:
    //  inner classes

    
    // constructor
    explicit conf_add_accounts (    const mtk::msg::sub_gen_response_location&  _gen_response_location,   const mtk::list<sub_grant >&  _grant_list );
    explicit conf_add_accounts ( const qpid::types::Variant::Map&  mv );
    virtual ~conf_add_accounts (){};
    virtual std::string get_message_type_as_string       (void) const  { return "conf_add_accounts"; }
    static  std::string static_get_message_type_as_string(void)        { return "conf_add_accounts"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_gen_response_location       gen_response_location; 
    mtk::list<sub_grant >                     grant_list; 



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



        //  qpid_variant wrapper for dynamic
        class conf_add_accounts__qpid_map
        {
        public:
            explicit  conf_add_accounts__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  conf_add_accounts__qpid_map ( const conf_add_accounts&  c ) : m_static(c) {}
            explicit  conf_add_accounts__qpid_map (    const mtk::msg::sub_gen_response_location&  _gen_response_location,   const mtk::list<sub_grant >&  _grant_list );
            ~conf_add_accounts__qpid_map() {};
            

            conf_add_accounts                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  conf_add_accounts::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  conf_add_accounts::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  conf_add_accounts::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  conf_add_accounts::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_accmgr_init
//-------------------------------    
class pub_accmgr_init     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_accmgr_init (    const mtk::msg::sub_process_info&  _process_info,   const std::string&  _request_sufix_subjetc );
    explicit pub_accmgr_init ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_accmgr_init (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_accmgr_init"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_accmgr_init"; }
    
    static  int         static_return_message_RT_priority(void)        { return 1; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_process_info                process_info; 
    std::string                               request_sufix_subjetc; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject ();
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_accmgr_init__qpid_map
        {
        public:
            explicit  pub_accmgr_init__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_accmgr_init__qpid_map ( const pub_accmgr_init&  c ) : m_static(c) {}
            explicit  pub_accmgr_init__qpid_map (    const mtk::msg::sub_process_info&  _process_info,   const std::string&  _request_sufix_subjetc );
            ~pub_accmgr_init__qpid_map() {};
            

            pub_accmgr_init                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  pub_accmgr_init::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_accmgr_init::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_accmgr_init::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_accmgr_init::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      rq_accounts_oninit
//-------------------------------    
class rq_accounts_oninit     
{
public:
    //  inner classes

    
    // constructor
    explicit rq_accounts_oninit (    const mtk::msg::sub_request_info&  _request_info,   const std::string&  _request_sufix_subjetc );
    explicit rq_accounts_oninit ( const qpid::types::Variant::Map&  mv );
    virtual ~rq_accounts_oninit (){};
    virtual std::string get_message_type_as_string       (void) const  { return "rq_accounts_oninit"; }
    static  std::string static_get_message_type_as_string(void)        { return "rq_accounts_oninit"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 
    std::string                               request_sufix_subjetc; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& request_info_process_info_location_broker_code,const std::string& request_sufix_subjetc);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class rq_accounts_oninit__qpid_map
        {
        public:
            explicit  rq_accounts_oninit__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  rq_accounts_oninit__qpid_map ( const rq_accounts_oninit&  c ) : m_static(c) {}
            explicit  rq_accounts_oninit__qpid_map (    const mtk::msg::sub_request_info&  _request_info,   const std::string&  _request_sufix_subjetc );
            ~rq_accounts_oninit__qpid_map() {};
            

            rq_accounts_oninit                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  rq_accounts_oninit::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  rq_accounts_oninit::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  rq_accounts_oninit::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  rq_accounts_oninit::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        
    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_grant & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_grant & c);
   void           operator >> (const YAML::Node& n,       sub_grant & c);

bool operator== (const sub_grant::IC_key& a, const sub_grant::IC_key& b);
bool operator!= (const sub_grant::IC_key& a, const sub_grant::IC_key& b);


bool operator== (const sub_grant& a, const sub_grant& b);
bool operator!= (const sub_grant& a, const sub_grant& b);

    std::ostream& operator<< (std::ostream& o, const sub_grant::IC_key & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_grant::IC_key & c);
   void           operator >> (const YAML::Node& n,       sub_grant::IC_key & c);

bool operator== (const sub_grant::IC_key& a, const sub_grant::IC_key& b);
bool operator!= (const sub_grant::IC_key& a, const sub_grant::IC_key& b);


    bool operator< (const sub_grant::IC_key& a, const sub_grant::IC_key& b);

    std::ostream& operator<< (std::ostream& o, const rq_accounts & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const rq_accounts & c);
   void           operator >> (const YAML::Node& n,       rq_accounts & c);

bool operator== (const rq_accounts& a, const rq_accounts& b);
bool operator!= (const rq_accounts& a, const rq_accounts& b);

    std::ostream& operator<< (std::ostream& o, const conf_add_accounts & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const conf_add_accounts & c);
   void           operator >> (const YAML::Node& n,       conf_add_accounts & c);

bool operator== (const conf_add_accounts& a, const conf_add_accounts& b);
bool operator!= (const conf_add_accounts& a, const conf_add_accounts& b);

    std::ostream& operator<< (std::ostream& o, const pub_accmgr_init & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_accmgr_init & c);
   void           operator >> (const YAML::Node& n,       pub_accmgr_init & c);

bool operator== (const pub_accmgr_init& a, const pub_accmgr_init& b);
bool operator!= (const pub_accmgr_init& a, const pub_accmgr_init& b);

    std::ostream& operator<< (std::ostream& o, const rq_accounts_oninit & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const rq_accounts_oninit & c);
   void           operator >> (const YAML::Node& n,       rq_accounts_oninit & c);

bool operator== (const rq_accounts_oninit& a, const rq_accounts_oninit& b);
bool operator!= (const rq_accounts_oninit& a, const rq_accounts_oninit& b);

void __internal_add2map (qpid::types::Variant::Map& map, const sub_grant& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_grant>& a, const std::string& field);
void copy (sub_grant& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_grant::IC_key& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_grant::IC_key>& a, const std::string& field);
void copy (sub_grant::IC_key& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const rq_accounts& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<rq_accounts>& a, const std::string& field);
void copy (rq_accounts& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const conf_add_accounts& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<conf_add_accounts>& a, const std::string& field);
void copy (conf_add_accounts& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_accmgr_init& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_accmgr_init>& a, const std::string& field);
void copy (pub_accmgr_init& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const rq_accounts_oninit& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<rq_accounts_oninit>& a, const std::string& field);
void copy (rq_accounts_oninit& a, const qpid::types::Variant& map);

    
    
    
//  fordward declarations  dynamic--------------------------------------------------------


inline std::ostream& operator<< (std::ostream& o, const sub_grant__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_grant__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_grant__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_grant__qpid_map& a, const sub_grant__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_grant__qpid_map& a, const sub_grant__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_grant__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_grant__qpid_map>& a, const std::string& field);
void copy (sub_grant__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const rq_accounts__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const rq_accounts__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       rq_accounts__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const rq_accounts__qpid_map& a, const rq_accounts__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const rq_accounts__qpid_map& a, const rq_accounts__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const rq_accounts__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<rq_accounts__qpid_map>& a, const std::string& field);
void copy (rq_accounts__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const conf_add_accounts__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const conf_add_accounts__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       conf_add_accounts__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const conf_add_accounts__qpid_map& a, const conf_add_accounts__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const conf_add_accounts__qpid_map& a, const conf_add_accounts__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const conf_add_accounts__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<conf_add_accounts__qpid_map>& a, const std::string& field);
void copy (conf_add_accounts__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_accmgr_init__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_accmgr_init__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_accmgr_init__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_accmgr_init__qpid_map& a, const pub_accmgr_init__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_accmgr_init__qpid_map& a, const pub_accmgr_init__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_accmgr_init__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_accmgr_init__qpid_map>& a, const std::string& field);
void copy (pub_accmgr_init__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const rq_accounts_oninit__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const rq_accounts_oninit__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       rq_accounts_oninit__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const rq_accounts_oninit__qpid_map& a, const rq_accounts_oninit__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const rq_accounts_oninit__qpid_map& a, const rq_accounts_oninit__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const rq_accounts_oninit__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<rq_accounts_oninit__qpid_map>& a, const std::string& field);
void copy (rq_accounts_oninit__qpid_map& a, const qpid::types::Variant& map);

    sub_grant  __internal_get_default(sub_grant *);
    
        inline sub_grant__qpid_map  __internal_get_default(sub_grant__qpid_map *) { return  sub_grant__qpid_map(__internal_get_default((sub_grant*)0));  }

    sub_grant::IC_key  __internal_get_default(sub_grant::IC_key *);
    
    rq_accounts  __internal_get_default(rq_accounts *);
    
        inline rq_accounts__qpid_map  __internal_get_default(rq_accounts__qpid_map *) { return  rq_accounts__qpid_map(__internal_get_default((rq_accounts*)0));  }

    conf_add_accounts  __internal_get_default(conf_add_accounts *);
    
        inline conf_add_accounts__qpid_map  __internal_get_default(conf_add_accounts__qpid_map *) { return  conf_add_accounts__qpid_map(__internal_get_default((conf_add_accounts*)0));  }

    pub_accmgr_init  __internal_get_default(pub_accmgr_init *);
    
        inline pub_accmgr_init__qpid_map  __internal_get_default(pub_accmgr_init__qpid_map *) { return  pub_accmgr_init__qpid_map(__internal_get_default((pub_accmgr_init*)0));  }

    rq_accounts_oninit  __internal_get_default(rq_accounts_oninit *);
    
        inline rq_accounts_oninit__qpid_map  __internal_get_default(rq_accounts_oninit__qpid_map *) { return  rq_accounts_oninit__qpid_map(__internal_get_default((rq_accounts_oninit*)0));  }


};   //namespace mtk {
};   //namespace trd {
};   //namespace account {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::account::msg::rq_accounts)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::account::msg::rq_accounts__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::account::msg::conf_add_accounts)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::account::msg::conf_add_accounts__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::account::msg::pub_accmgr_init)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::account::msg::pub_accmgr_init__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::account::msg::rq_accounts_oninit)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::account::msg::rq_accounts_oninit__qpid_map)




#endif
