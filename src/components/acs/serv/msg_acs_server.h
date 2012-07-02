
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

#include "mtk_qpid/mtk_qpid.h"


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
    explicit pub_add_user (    const std::string&  _broker_code,   const mtk::acs::msg::res_login::IC_session_info&  _login_confirmation );
    explicit pub_add_user ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_add_user (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_add_user"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_add_user"; }
    
    static  int         static_return_message_RT_priority(void)        { return 1; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               broker_code; 
    mtk::acs::msg::res_login::IC_session_info  login_confirmation; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& broker_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_add_user__qpid_map
        {
        public:
            explicit  pub_add_user__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_add_user__qpid_map ( const pub_add_user&  c ) : m_static(c) {}
            explicit  pub_add_user__qpid_map (    const std::string&  _broker_code,   const mtk::acs::msg::res_login::IC_session_info&  _login_confirmation );
            ~pub_add_user__qpid_map() {};
            

            pub_add_user                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  pub_add_user::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_add_user::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_add_user::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_add_user::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_del_user
//-------------------------------    
class pub_del_user     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_del_user (    const std::string&  _broker_code,   const mtk::acs::msg::res_login::IC_session_info&  _login_confirmation );
    explicit pub_del_user ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_del_user (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_del_user"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_del_user"; }
    
    static  int         static_return_message_RT_priority(void)        { return 1; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               broker_code; 
    mtk::acs::msg::res_login::IC_session_info  login_confirmation; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& broker_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_del_user__qpid_map
        {
        public:
            explicit  pub_del_user__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_del_user__qpid_map ( const pub_del_user&  c ) : m_static(c) {}
            explicit  pub_del_user__qpid_map (    const std::string&  _broker_code,   const mtk::acs::msg::res_login::IC_session_info&  _login_confirmation );
            ~pub_del_user__qpid_map() {};
            

            pub_del_user                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  pub_del_user::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_del_user::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_del_user::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_del_user::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      req_session_id_conf
//-------------------------------    
class req_session_id_conf     
{
public:
    //  inner classes

    
    // constructor
    explicit req_session_id_conf (    const std::string&  _broker_code,   const std::string&  _session_id,   const mtk::msg::sub_process_info&  _from );
    explicit req_session_id_conf ( const qpid::types::Variant::Map&  mv );
    virtual ~req_session_id_conf (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_session_id_conf"; }
    static  std::string static_get_message_type_as_string(void)        { return "req_session_id_conf"; }
    
    static  int         static_return_message_RT_priority(void)        { return 1; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               broker_code; 
    std::string                               session_id; 
    mtk::msg::sub_process_info                from; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& broker_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class req_session_id_conf__qpid_map
        {
        public:
            explicit  req_session_id_conf__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  req_session_id_conf__qpid_map ( const req_session_id_conf&  c ) : m_static(c) {}
            explicit  req_session_id_conf__qpid_map (    const std::string&  _broker_code,   const std::string&  _session_id,   const mtk::msg::sub_process_info&  _from );
            ~req_session_id_conf__qpid_map() {};
            

            req_session_id_conf                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  req_session_id_conf::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  req_session_id_conf::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  req_session_id_conf::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  req_session_id_conf::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_partial_user_list_acs2serv
//-------------------------------    
class pub_partial_user_list_acs2serv     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_partial_user_list_acs2serv (    const std::string&  _broker_code,   const mtk::list<mtk::acs::msg::res_login::IC_session_info >&  _list_login_confirmation );
    explicit pub_partial_user_list_acs2serv ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_partial_user_list_acs2serv (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_partial_user_list_acs2serv"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_partial_user_list_acs2serv"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               broker_code; 
    mtk::list<mtk::acs::msg::res_login::IC_session_info >  list_login_confirmation; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& broker_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_partial_user_list_acs2serv__qpid_map
        {
        public:
            explicit  pub_partial_user_list_acs2serv__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_partial_user_list_acs2serv__qpid_map ( const pub_partial_user_list_acs2serv&  c ) : m_static(c) {}
            explicit  pub_partial_user_list_acs2serv__qpid_map (    const std::string&  _broker_code,   const mtk::list<mtk::acs::msg::res_login::IC_session_info >&  _list_login_confirmation );
            ~pub_partial_user_list_acs2serv__qpid_map() {};
            

            pub_partial_user_list_acs2serv                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  pub_partial_user_list_acs2serv::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_partial_user_list_acs2serv::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_partial_user_list_acs2serv::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_partial_user_list_acs2serv::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_partial_user_list_serv2acs
//-------------------------------    
class pub_partial_user_list_serv2acs     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_partial_user_list_serv2acs (    const std::string&  _broker_code,   const mtk::list<mtk::acs::msg::res_login::IC_session_info >&  _list_login_confirmation );
    explicit pub_partial_user_list_serv2acs ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_partial_user_list_serv2acs (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_partial_user_list_serv2acs"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_partial_user_list_serv2acs"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               broker_code; 
    mtk::list<mtk::acs::msg::res_login::IC_session_info >  list_login_confirmation; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& broker_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_partial_user_list_serv2acs__qpid_map
        {
        public:
            explicit  pub_partial_user_list_serv2acs__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_partial_user_list_serv2acs__qpid_map ( const pub_partial_user_list_serv2acs&  c ) : m_static(c) {}
            explicit  pub_partial_user_list_serv2acs__qpid_map (    const std::string&  _broker_code,   const mtk::list<mtk::acs::msg::res_login::IC_session_info >&  _list_login_confirmation );
            ~pub_partial_user_list_serv2acs__qpid_map() {};
            

            pub_partial_user_list_serv2acs                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  pub_partial_user_list_serv2acs::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_partial_user_list_serv2acs::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_partial_user_list_serv2acs::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_partial_user_list_serv2acs::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
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
    explicit req_user_list ( const qpid::types::Variant::Map&  mv );
    virtual ~req_user_list (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_user_list"; }
    static  std::string static_get_message_type_as_string(void)        { return "req_user_list"; }
    
    static  int         static_return_message_RT_priority(void)        { return 1; };

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
        class req_user_list__qpid_map
        {
        public:
            explicit  req_user_list__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  req_user_list__qpid_map ( const req_user_list&  c ) : m_static(c) {}
            explicit  req_user_list__qpid_map (    const mtk::msg::sub_request_info&  _request_info );
            ~req_user_list__qpid_map() {};
            

            req_user_list                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  req_user_list::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  req_user_list::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  req_user_list::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  req_user_list::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
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
    explicit res_user_list ( const qpid::types::Variant::Map&  mv );
    virtual ~res_user_list (){};
    virtual std::string get_message_type_as_string       (void) const  { return "res_user_list"; }
    static  std::string static_get_message_type_as_string(void)        { return "res_user_list"; }
    
    static  int         static_return_message_RT_priority(void)        { return 1; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_r_response                  response_info; 
    mtk::list<mtk::acs::msg::res_login::IC_session_info >  list_login_confirmation; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& response_info_process_info_location_broker_code,const std::string& response_info_request_info_process_info_location_broker_code,const std::string& response_info_request_info_process_info_location_machine,const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_session_id,const std::string& response_info_request_info_req_id_req_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class res_user_list__qpid_map
        {
        public:
            explicit  res_user_list__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  res_user_list__qpid_map ( const res_user_list&  c ) : m_static(c) {}
            explicit  res_user_list__qpid_map (    const mtk::msg::sub_r_response&  _response_info,   const mtk::list<mtk::acs::msg::res_login::IC_session_info >&  _list_login_confirmation );
            ~res_user_list__qpid_map() {};
            

            res_user_list                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  res_user_list::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  res_user_list::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  res_user_list::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  res_user_list::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
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

void __internal_add2map (qpid::types::Variant::Map& map, const pub_add_user& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_add_user>& a, const std::string& field);
void copy (pub_add_user& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_del_user& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_del_user>& a, const std::string& field);
void copy (pub_del_user& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const req_session_id_conf& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_session_id_conf>& a, const std::string& field);
void copy (req_session_id_conf& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_partial_user_list_acs2serv& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_partial_user_list_acs2serv>& a, const std::string& field);
void copy (pub_partial_user_list_acs2serv& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_partial_user_list_serv2acs& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_partial_user_list_serv2acs>& a, const std::string& field);
void copy (pub_partial_user_list_serv2acs& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const req_user_list& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_user_list>& a, const std::string& field);
void copy (req_user_list& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const res_user_list& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_user_list>& a, const std::string& field);
void copy (res_user_list& a, const qpid::types::Variant& map);

    
    
    
//  fordward declarations  dynamic--------------------------------------------------------


inline std::ostream& operator<< (std::ostream& o, const pub_add_user__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_add_user__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_add_user__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_add_user__qpid_map& a, const pub_add_user__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_add_user__qpid_map& a, const pub_add_user__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_add_user__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_add_user__qpid_map>& a, const std::string& field);
void copy (pub_add_user__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_del_user__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_del_user__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_del_user__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_del_user__qpid_map& a, const pub_del_user__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_del_user__qpid_map& a, const pub_del_user__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_del_user__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_del_user__qpid_map>& a, const std::string& field);
void copy (pub_del_user__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const req_session_id_conf__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const req_session_id_conf__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       req_session_id_conf__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const req_session_id_conf__qpid_map& a, const req_session_id_conf__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const req_session_id_conf__qpid_map& a, const req_session_id_conf__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const req_session_id_conf__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_session_id_conf__qpid_map>& a, const std::string& field);
void copy (req_session_id_conf__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_partial_user_list_acs2serv__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_partial_user_list_acs2serv__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_partial_user_list_acs2serv__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_partial_user_list_acs2serv__qpid_map& a, const pub_partial_user_list_acs2serv__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_partial_user_list_acs2serv__qpid_map& a, const pub_partial_user_list_acs2serv__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_partial_user_list_acs2serv__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_partial_user_list_acs2serv__qpid_map>& a, const std::string& field);
void copy (pub_partial_user_list_acs2serv__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_partial_user_list_serv2acs__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_partial_user_list_serv2acs__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_partial_user_list_serv2acs__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_partial_user_list_serv2acs__qpid_map& a, const pub_partial_user_list_serv2acs__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_partial_user_list_serv2acs__qpid_map& a, const pub_partial_user_list_serv2acs__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_partial_user_list_serv2acs__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_partial_user_list_serv2acs__qpid_map>& a, const std::string& field);
void copy (pub_partial_user_list_serv2acs__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const req_user_list__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const req_user_list__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       req_user_list__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const req_user_list__qpid_map& a, const req_user_list__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const req_user_list__qpid_map& a, const req_user_list__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const req_user_list__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_user_list__qpid_map>& a, const std::string& field);
void copy (req_user_list__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const res_user_list__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const res_user_list__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       res_user_list__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const res_user_list__qpid_map& a, const res_user_list__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const res_user_list__qpid_map& a, const res_user_list__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const res_user_list__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_user_list__qpid_map>& a, const std::string& field);
void copy (res_user_list__qpid_map& a, const qpid::types::Variant& map);

    pub_add_user  __internal_get_default(pub_add_user *);
    
        inline pub_add_user__qpid_map  __internal_get_default(pub_add_user__qpid_map *) { return  pub_add_user__qpid_map(__internal_get_default((pub_add_user*)0));  }

    pub_del_user  __internal_get_default(pub_del_user *);
    
        inline pub_del_user__qpid_map  __internal_get_default(pub_del_user__qpid_map *) { return  pub_del_user__qpid_map(__internal_get_default((pub_del_user*)0));  }

    req_session_id_conf  __internal_get_default(req_session_id_conf *);
    
        inline req_session_id_conf__qpid_map  __internal_get_default(req_session_id_conf__qpid_map *) { return  req_session_id_conf__qpid_map(__internal_get_default((req_session_id_conf*)0));  }

    pub_partial_user_list_acs2serv  __internal_get_default(pub_partial_user_list_acs2serv *);
    
        inline pub_partial_user_list_acs2serv__qpid_map  __internal_get_default(pub_partial_user_list_acs2serv__qpid_map *) { return  pub_partial_user_list_acs2serv__qpid_map(__internal_get_default((pub_partial_user_list_acs2serv*)0));  }

    pub_partial_user_list_serv2acs  __internal_get_default(pub_partial_user_list_serv2acs *);
    
        inline pub_partial_user_list_serv2acs__qpid_map  __internal_get_default(pub_partial_user_list_serv2acs__qpid_map *) { return  pub_partial_user_list_serv2acs__qpid_map(__internal_get_default((pub_partial_user_list_serv2acs*)0));  }

    req_user_list  __internal_get_default(req_user_list *);
    
        inline req_user_list__qpid_map  __internal_get_default(req_user_list__qpid_map *) { return  req_user_list__qpid_map(__internal_get_default((req_user_list*)0));  }

    res_user_list  __internal_get_default(res_user_list *);
    
        inline res_user_list__qpid_map  __internal_get_default(res_user_list__qpid_map *) { return  res_user_list__qpid_map(__internal_get_default((res_user_list*)0));  }


};   //namespace mtk {
};   //namespace acs_server {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::pub_add_user)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::pub_add_user__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::pub_del_user)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::pub_del_user__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::req_session_id_conf)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::req_session_id_conf__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::pub_partial_user_list_acs2serv)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::pub_partial_user_list_acs2serv__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::pub_partial_user_list_serv2acs)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::pub_partial_user_list_serv2acs__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::req_user_list)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::req_user_list__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::res_user_list)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::acs_server::msg::res_user_list__qpid_map)




#endif
