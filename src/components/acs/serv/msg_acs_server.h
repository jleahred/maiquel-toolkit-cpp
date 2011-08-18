
#ifndef  __msg_acs_server__
#define  __msg_acs_server__


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
#include "components/msg_common_support.h"
#include "components/acs/msg_acs.h"

namespace mtk { 
namespace acs_server { 
namespace msg { 




//-------------------------------
//      pub_add_user
//-------------------------------    
class pub_add_user     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_add_user (    const mtk::acs::msg::res_login::IC_session_info&  _login_confirmation );
    explicit pub_add_user ( const qpid::messaging::Message& message );
    virtual ~pub_add_user (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_add_user"; };
    static  std::string static_get_message_type_as_string(void)        { return "pub_add_user"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::acs::msg::res_login::IC_session_info  login_confirmation; 



    //  subject info
    static std::string  get_in_subject ();
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      pub_del_user
//-------------------------------    
class pub_del_user     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_del_user (    const mtk::acs::msg::res_login::IC_session_info&  _login_confirmation );
    explicit pub_del_user ( const qpid::messaging::Message& message );
    virtual ~pub_del_user (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_del_user"; };
    static  std::string static_get_message_type_as_string(void)        { return "pub_del_user"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::acs::msg::res_login::IC_session_info  login_confirmation; 



    //  subject info
    static std::string  get_in_subject ();
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      req_session_id_conf
//-------------------------------    
class req_session_id_conf     
{
public:
    //  inner classes

    
    // constructor
    explicit req_session_id_conf (    const std::string&  _session_id,   const mtk::msg::sub_process_info&  _from );
    explicit req_session_id_conf ( const qpid::messaging::Message& message );
    virtual ~req_session_id_conf (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_session_id_conf"; };
    static  std::string static_get_message_type_as_string(void)        { return "req_session_id_conf"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               session_id; 
    mtk::msg::sub_process_info                from; 



    //  subject info
    static std::string  get_in_subject ();
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      pub_partial_user_list_acs2serv
//-------------------------------    
class pub_partial_user_list_acs2serv     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_partial_user_list_acs2serv (    const mtk::list<mtk::acs::msg::res_login::IC_session_info >&  _list_login_confirmation );
    explicit pub_partial_user_list_acs2serv ( const qpid::messaging::Message& message );
    virtual ~pub_partial_user_list_acs2serv (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_partial_user_list_acs2serv"; };
    static  std::string static_get_message_type_as_string(void)        { return "pub_partial_user_list_acs2serv"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::list<mtk::acs::msg::res_login::IC_session_info >  list_login_confirmation; 



    //  subject info
    static std::string  get_in_subject ();
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      pub_partial_user_list_serv2acs
//-------------------------------    
class pub_partial_user_list_serv2acs     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_partial_user_list_serv2acs (    const mtk::list<mtk::acs::msg::res_login::IC_session_info >&  _list_login_confirmation );
    explicit pub_partial_user_list_serv2acs ( const qpid::messaging::Message& message );
    virtual ~pub_partial_user_list_serv2acs (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_partial_user_list_serv2acs"; };
    static  std::string static_get_message_type_as_string(void)        { return "pub_partial_user_list_serv2acs"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::list<mtk::acs::msg::res_login::IC_session_info >  list_login_confirmation; 



    //  subject info
    static std::string  get_in_subject ();
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      req_user_list
//-------------------------------    
class req_user_list     
{
public:
    //  inner classes

    
    // constructor
    explicit req_user_list (    const mtk::msg::sub_request_info&  _request_info );
    explicit req_user_list ( const qpid::messaging::Message& message );
    virtual ~req_user_list (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_user_list"; };
    static  std::string static_get_message_type_as_string(void)        { return "req_user_list"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 



    //  subject info
    static std::string  get_in_subject ();
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      res_user_list
//-------------------------------    
class res_user_list     
{
public:
    //  inner classes

    
    // constructor
    explicit res_user_list (    const mtk::msg::sub_r_response&  _response_info,   const mtk::list<mtk::acs::msg::res_login::IC_session_info >&  _list_login_confirmation );
    explicit res_user_list ( const qpid::messaging::Message& message );
    virtual ~res_user_list (){};
    virtual std::string get_message_type_as_string       (void) const  { return "res_user_list"; };
    static  std::string static_get_message_type_as_string(void)        { return "res_user_list"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_r_response                  response_info; 
    mtk::list<mtk::acs::msg::res_login::IC_session_info >  list_login_confirmation; 



    //  subject info
    static std::string  get_in_subject (const std::string& response_info_request_info_process_info_location_client_code,const std::string& response_info_request_info_process_info_location_machine,const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_session_id,const std::string& response_info_request_info_req_id_req_code);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const pub_add_user & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_add_user & c);
   void           operator >> (const YAML::Node& n,       pub_add_user & c);

bool operator== (const pub_add_user& a, const pub_add_user& b);
bool operator!= (const pub_add_user& a, const pub_add_user& b);

    std::ostream& operator<< (std::ostream& o, const pub_del_user & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_del_user & c);
   void           operator >> (const YAML::Node& n,       pub_del_user & c);

bool operator== (const pub_del_user& a, const pub_del_user& b);
bool operator!= (const pub_del_user& a, const pub_del_user& b);

    std::ostream& operator<< (std::ostream& o, const req_session_id_conf & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const req_session_id_conf & c);
   void           operator >> (const YAML::Node& n,       req_session_id_conf & c);

bool operator== (const req_session_id_conf& a, const req_session_id_conf& b);
bool operator!= (const req_session_id_conf& a, const req_session_id_conf& b);

    std::ostream& operator<< (std::ostream& o, const pub_partial_user_list_acs2serv & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_partial_user_list_acs2serv & c);
   void           operator >> (const YAML::Node& n,       pub_partial_user_list_acs2serv & c);

bool operator== (const pub_partial_user_list_acs2serv& a, const pub_partial_user_list_acs2serv& b);
bool operator!= (const pub_partial_user_list_acs2serv& a, const pub_partial_user_list_acs2serv& b);

    std::ostream& operator<< (std::ostream& o, const pub_partial_user_list_serv2acs & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_partial_user_list_serv2acs & c);
   void           operator >> (const YAML::Node& n,       pub_partial_user_list_serv2acs & c);

bool operator== (const pub_partial_user_list_serv2acs& a, const pub_partial_user_list_serv2acs& b);
bool operator!= (const pub_partial_user_list_serv2acs& a, const pub_partial_user_list_serv2acs& b);

    std::ostream& operator<< (std::ostream& o, const req_user_list & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const req_user_list & c);
   void           operator >> (const YAML::Node& n,       req_user_list & c);

bool operator== (const req_user_list& a, const req_user_list& b);
bool operator!= (const req_user_list& a, const req_user_list& b);

    std::ostream& operator<< (std::ostream& o, const res_user_list & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const res_user_list & c);
   void           operator >> (const YAML::Node& n,       res_user_list & c);

bool operator== (const res_user_list& a, const res_user_list& b);
bool operator!= (const res_user_list& a, const res_user_list& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const pub_add_user& a);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_add_user& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_add_user>& a, const std::string& field);
void copy (pub_add_user& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const pub_del_user& a);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_del_user& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_del_user>& a, const std::string& field);
void copy (pub_del_user& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const req_session_id_conf& a);
void __internal_add2map (qpid::types::Variant::Map& map, const req_session_id_conf& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_session_id_conf>& a, const std::string& field);
void copy (req_session_id_conf& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const pub_partial_user_list_acs2serv& a);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_partial_user_list_acs2serv& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_partial_user_list_acs2serv>& a, const std::string& field);
void copy (pub_partial_user_list_acs2serv& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const pub_partial_user_list_serv2acs& a);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_partial_user_list_serv2acs& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_partial_user_list_serv2acs>& a, const std::string& field);
void copy (pub_partial_user_list_serv2acs& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const req_user_list& a);
void __internal_add2map (qpid::types::Variant::Map& map, const req_user_list& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_user_list>& a, const std::string& field);
void copy (req_user_list& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const res_user_list& a);
void __internal_add2map (qpid::types::Variant::Map& map, const res_user_list& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_user_list>& a, const std::string& field);
void copy (res_user_list& a, const qpid::types::Variant& map);

    pub_add_user  __internal_get_default(pub_add_user *);
    
    pub_del_user  __internal_get_default(pub_del_user *);
    
    req_session_id_conf  __internal_get_default(req_session_id_conf *);
    
    pub_partial_user_list_acs2serv  __internal_get_default(pub_partial_user_list_acs2serv *);
    
    pub_partial_user_list_serv2acs  __internal_get_default(pub_partial_user_list_serv2acs *);
    
    req_user_list  __internal_get_default(req_user_list *);
    
    res_user_list  __internal_get_default(res_user_list *);
    

};   //namespace mtk {
};   //namespace acs_server {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::pub_add_user)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::pub_del_user)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::req_session_id_conf)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::pub_partial_user_list_acs2serv)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::pub_partial_user_list_serv2acs)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::req_user_list)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::res_user_list)




#endif
