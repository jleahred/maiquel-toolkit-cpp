
#ifndef  __msg_acs__
#define  __msg_acs__


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

namespace mtk { 
namespace acs { 
namespace msg { 




//-------------------------------
//      req_login_key
//-------------------------------    
class req_login_key     
{
public:
    //  inner classes

    
    // constructor
    explicit req_login_key (    const mtk::msg::sub_request_info&  _request_info,   const std::string&  _user_name );
    explicit req_login_key ( const qpid::messaging::Message& message );
    virtual ~req_login_key (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_login_key"; };
    static  std::string static_get_message_type_as_string(void)        { return "req_login_key"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 
    std::string                               user_name; 



    //  subject info
    static std::string  get_in_subject (const std::string& request_info_process_info_location_client_code);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      res_login_key
//-------------------------------    
class res_login_key     
{
public:
    //  inner classes

    
    // constructor
    explicit res_login_key (    const mtk::msg::sub_r_response&  _response_info,   const std::string&  _key );
    explicit res_login_key ( const qpid::messaging::Message& message );
    virtual ~res_login_key (){};
    virtual std::string get_message_type_as_string       (void) const  { return "res_login_key"; };
    static  std::string static_get_message_type_as_string(void)        { return "res_login_key"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_r_response                  response_info; 
    std::string                               key; 



    //  subject info
    static std::string  get_in_subject (const std::string& response_info_request_info_process_info_location_client_code,const std::string& response_info_request_info_process_info_location_machine,const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_session_id,const std::string& response_info_request_info_req_id_req_code);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      req_login
//-------------------------------    
class req_login     
{
public:
    //  inner classes

    
    // constructor
    explicit req_login (    const mtk::msg::sub_request_info&  _request_info,   const std::string&  _user_name,   const std::string&  _key,   const std::string&  _coded_pass );
    explicit req_login ( const qpid::messaging::Message& message );
    virtual ~req_login (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_login"; };
    static  std::string static_get_message_type_as_string(void)        { return "req_login"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 
    std::string                               user_name; 
    std::string                               key; 
    std::string                               coded_pass; 



    //  subject info
    static std::string  get_in_subject (const std::string& request_info_process_info_location_client_code);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      res_login
//-------------------------------    
class res_login     
{
public:
    //  inner classes

    
    //-------------------------------
    //      IC_session_info
    //-------------------------------    
    class IC_session_info     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit IC_session_info (    const std::string&  _user_name,   const std::string&  _client_code,   const std::string&  _session_id );
        explicit IC_session_info ( const qpid::messaging::Message& message );
        virtual ~IC_session_info (){};
        virtual std::string get_message_type_as_string       (void) const  { return "IC_session_info"; };
        static  std::string static_get_message_type_as_string(void)        { return "IC_session_info"; };
        
        
    
        // fields
        std::string                               user_name; 
        std::string                               client_code; 
        std::string                               session_id; 
    
    
    
        //  subject info
        
        
        
        
        
        void        before_send(void) const;
        
    private:
        std::string check_recomended(void) const;
    };
    
    
    
    
    // constructor
    explicit res_login (    const mtk::msg::sub_r_response&  _response_info,   const IC_session_info&  _session_info );
    explicit res_login ( const qpid::messaging::Message& message );
    virtual ~res_login (){};
    virtual std::string get_message_type_as_string       (void) const  { return "res_login"; };
    static  std::string static_get_message_type_as_string(void)        { return "res_login"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_r_response                  response_info; 
    IC_session_info                           session_info; 



    //  subject info
    static std::string  get_in_subject (const std::string& response_info_request_info_process_info_location_client_code,const std::string& response_info_request_info_process_info_location_machine,const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_session_id,const std::string& response_info_request_info_req_id_req_code);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      conf_logout
//-------------------------------    
class conf_logout     
{
public:
    //  inner classes

    
    // constructor
    explicit conf_logout (    const mtk::msg::sub_location&  _location,   const std::string&  _session_id,   const std::string&  _description );
    explicit conf_logout ( const qpid::messaging::Message& message );
    virtual ~conf_logout (){};
    virtual std::string get_message_type_as_string       (void) const  { return "conf_logout"; };
    static  std::string static_get_message_type_as_string(void)        { return "conf_logout"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_location                    location; 
    std::string                               session_id; 
    std::string                               description; 



    //  subject info
    static std::string  get_in_subject (const std::string& location_client_code,const std::string& location_machine,const std::string& session_id);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      req_logout
//-------------------------------    
class req_logout     
{
public:
    //  inner classes

    
    // constructor
    explicit req_logout (    const mtk::msg::sub_request_info&  _request_info );
    explicit req_logout ( const qpid::messaging::Message& message );
    virtual ~req_logout (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_logout"; };
    static  std::string static_get_message_type_as_string(void)        { return "req_logout"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 



    //  subject info
    static std::string  get_in_subject (const std::string& request_info_process_info_location_client_code);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      req_change_password
//-------------------------------    
class req_change_password     
{
public:
    //  inner classes

    
    // constructor
    explicit req_change_password (    const mtk::msg::sub_request_info&  _request_info,   const std::string&  _user_name,   const std::string&  _key,   const std::string&  _old_password,   const mtk::list<int32_t >&  _new_password );
    explicit req_change_password ( const qpid::messaging::Message& message );
    virtual ~req_change_password (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_change_password"; };
    static  std::string static_get_message_type_as_string(void)        { return "req_change_password"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 
    std::string                               user_name; 
    std::string                               key; 
    std::string                               old_password; 
    mtk::list<int32_t >                       new_password; 



    //  subject info
    static std::string  get_in_subject (const std::string& request_info_process_info_location_client_code);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      res_change_password
//-------------------------------    
class res_change_password     
{
public:
    //  inner classes

    
    //-------------------------------
    //      IC_change_password_info
    //-------------------------------    
    class IC_change_password_info     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit IC_change_password_info (    const bool&  _accepted );
        explicit IC_change_password_info ( const qpid::messaging::Message& message );
        virtual ~IC_change_password_info (){};
        virtual std::string get_message_type_as_string       (void) const  { return "IC_change_password_info"; };
        static  std::string static_get_message_type_as_string(void)        { return "IC_change_password_info"; };
        
        
    
        // fields
        bool                                      accepted; 
    
    
    
        //  subject info
        
        
        
        
        
        void        before_send(void) const;
        
    private:
        std::string check_recomended(void) const;
    };
    
    
    
    
    // constructor
    explicit res_change_password (    const mtk::msg::sub_r_response&  _response_info,   const IC_change_password_info&  _change_password_info );
    explicit res_change_password ( const qpid::messaging::Message& message );
    virtual ~res_change_password (){};
    virtual std::string get_message_type_as_string       (void) const  { return "res_change_password"; };
    static  std::string static_get_message_type_as_string(void)        { return "res_change_password"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_r_response                  response_info; 
    IC_change_password_info                   change_password_info; 



    //  subject info
    static std::string  get_in_subject (const std::string& response_info_request_info_process_info_location_client_code,const std::string& response_info_request_info_process_info_location_machine,const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_session_id,const std::string& response_info_request_info_req_id_req_code);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const req_login_key & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const req_login_key & c);
   void           operator >> (const YAML::Node& n,       req_login_key & c);

bool operator== (const req_login_key& a, const req_login_key& b);
bool operator!= (const req_login_key& a, const req_login_key& b);

    std::ostream& operator<< (std::ostream& o, const res_login_key & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const res_login_key & c);
   void           operator >> (const YAML::Node& n,       res_login_key & c);

bool operator== (const res_login_key& a, const res_login_key& b);
bool operator!= (const res_login_key& a, const res_login_key& b);

    std::ostream& operator<< (std::ostream& o, const req_login & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const req_login & c);
   void           operator >> (const YAML::Node& n,       req_login & c);

bool operator== (const req_login& a, const req_login& b);
bool operator!= (const req_login& a, const req_login& b);

    std::ostream& operator<< (std::ostream& o, const res_login & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const res_login & c);
   void           operator >> (const YAML::Node& n,       res_login & c);

bool operator== (const res_login::IC_session_info& a, const res_login::IC_session_info& b);
bool operator!= (const res_login::IC_session_info& a, const res_login::IC_session_info& b);


bool operator== (const res_login& a, const res_login& b);
bool operator!= (const res_login& a, const res_login& b);

    std::ostream& operator<< (std::ostream& o, const res_login::IC_session_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const res_login::IC_session_info & c);
   void           operator >> (const YAML::Node& n,       res_login::IC_session_info & c);

bool operator== (const res_login::IC_session_info& a, const res_login::IC_session_info& b);
bool operator!= (const res_login::IC_session_info& a, const res_login::IC_session_info& b);

    std::ostream& operator<< (std::ostream& o, const conf_logout & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const conf_logout & c);
   void           operator >> (const YAML::Node& n,       conf_logout & c);

bool operator== (const conf_logout& a, const conf_logout& b);
bool operator!= (const conf_logout& a, const conf_logout& b);

    std::ostream& operator<< (std::ostream& o, const req_logout & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const req_logout & c);
   void           operator >> (const YAML::Node& n,       req_logout & c);

bool operator== (const req_logout& a, const req_logout& b);
bool operator!= (const req_logout& a, const req_logout& b);

    std::ostream& operator<< (std::ostream& o, const req_change_password & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const req_change_password & c);
   void           operator >> (const YAML::Node& n,       req_change_password & c);

bool operator== (const req_change_password& a, const req_change_password& b);
bool operator!= (const req_change_password& a, const req_change_password& b);

    std::ostream& operator<< (std::ostream& o, const res_change_password & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const res_change_password & c);
   void           operator >> (const YAML::Node& n,       res_change_password & c);

bool operator== (const res_change_password::IC_change_password_info& a, const res_change_password::IC_change_password_info& b);
bool operator!= (const res_change_password::IC_change_password_info& a, const res_change_password::IC_change_password_info& b);


bool operator== (const res_change_password& a, const res_change_password& b);
bool operator!= (const res_change_password& a, const res_change_password& b);

    std::ostream& operator<< (std::ostream& o, const res_change_password::IC_change_password_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const res_change_password::IC_change_password_info & c);
   void           operator >> (const YAML::Node& n,       res_change_password::IC_change_password_info & c);

bool operator== (const res_change_password::IC_change_password_info& a, const res_change_password::IC_change_password_info& b);
bool operator!= (const res_change_password::IC_change_password_info& a, const res_change_password::IC_change_password_info& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const req_login_key& a);
void __internal_add2map (qpid::types::Variant::Map& map, const req_login_key& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_login_key>& a, const std::string& field);
void copy (req_login_key& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const res_login_key& a);
void __internal_add2map (qpid::types::Variant::Map& map, const res_login_key& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_login_key>& a, const std::string& field);
void copy (res_login_key& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const req_login& a);
void __internal_add2map (qpid::types::Variant::Map& map, const req_login& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_login>& a, const std::string& field);
void copy (req_login& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const res_login& a);
void __internal_add2map (qpid::types::Variant::Map& map, const res_login& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_login>& a, const std::string& field);
void copy (res_login& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const res_login::IC_session_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const res_login::IC_session_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_login::IC_session_info>& a, const std::string& field);
void copy (res_login::IC_session_info& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const conf_logout& a);
void __internal_add2map (qpid::types::Variant::Map& map, const conf_logout& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<conf_logout>& a, const std::string& field);
void copy (conf_logout& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const req_logout& a);
void __internal_add2map (qpid::types::Variant::Map& map, const req_logout& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_logout>& a, const std::string& field);
void copy (req_logout& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const req_change_password& a);
void __internal_add2map (qpid::types::Variant::Map& map, const req_change_password& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_change_password>& a, const std::string& field);
void copy (req_change_password& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const res_change_password& a);
void __internal_add2map (qpid::types::Variant::Map& map, const res_change_password& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_change_password>& a, const std::string& field);
void copy (res_change_password& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const res_change_password::IC_change_password_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const res_change_password::IC_change_password_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_change_password::IC_change_password_info>& a, const std::string& field);
void copy (res_change_password::IC_change_password_info& a, const qpid::types::Variant& map);

    req_login_key  __internal_get_default(req_login_key *);
    
    res_login_key  __internal_get_default(res_login_key *);
    
    req_login  __internal_get_default(req_login *);
    
    res_login  __internal_get_default(res_login *);
    
    res_login::IC_session_info  __internal_get_default(res_login::IC_session_info *);
    
    conf_logout  __internal_get_default(conf_logout *);
    
    req_logout  __internal_get_default(req_logout *);
    
    req_change_password  __internal_get_default(req_change_password *);
    
    res_change_password  __internal_get_default(res_change_password *);
    
    res_change_password::IC_change_password_info  __internal_get_default(res_change_password::IC_change_password_info *);
    

};   //namespace mtk {
};   //namespace acs {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs::msg::req_login_key)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs::msg::res_login_key)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs::msg::req_login)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs::msg::res_login)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs::msg::conf_logout)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs::msg::req_logout)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs::msg::req_change_password)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs::msg::res_change_password)




#endif
