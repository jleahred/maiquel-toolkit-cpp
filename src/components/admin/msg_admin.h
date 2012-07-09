
#ifndef  __msg_admin__
#define  __msg_admin__


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


#include "../msg_common.h"
#include "../msg_common_support.h"
#include "msg_admin_support.h"
#include "../acs/msg_acs.h"

namespace mtk { 
namespace admin { 
namespace msg { 




//-------------------------------
//      pub_enter
//-------------------------------    
class pub_enter     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_enter (    const mtk::msg::sub_process_info&  _process_info,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check );
    explicit pub_enter ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_enter (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_enter"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_enter"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_process_info                process_info; 
    mtk::dtTimeQuantity                       ka_interval_send; 
    mtk::dtTimeQuantity                       ka_interval_check; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& process_info_location_broker_code,const std::string& process_info_cli_srv);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_enter__qpid_map
        {
        public:
            explicit  pub_enter__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_enter__qpid_map ( const pub_enter&  c ) : m_static(c) {}
            explicit  pub_enter__qpid_map (    const mtk::msg::sub_process_info&  _process_info,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check );
            ~pub_enter__qpid_map() {};
            

            pub_enter                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  pub_enter::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_enter::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_enter::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_enter::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_keep_alive_srv
//-------------------------------    
class pub_keep_alive_srv     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_keep_alive_srv (    const mtk::msg::sub_process_info&  _process_info,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check );
    explicit pub_keep_alive_srv ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_keep_alive_srv (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_keep_alive_srv"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_keep_alive_srv"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_process_info                process_info; 
    mtk::dtTimeQuantity                       ka_interval_send; 
    mtk::dtTimeQuantity                       ka_interval_check; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& process_info_location_broker_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_keep_alive_srv__qpid_map
        {
        public:
            explicit  pub_keep_alive_srv__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_keep_alive_srv__qpid_map ( const pub_keep_alive_srv&  c ) : m_static(c) {}
            explicit  pub_keep_alive_srv__qpid_map (    const mtk::msg::sub_process_info&  _process_info,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check );
            ~pub_keep_alive_srv__qpid_map() {};
            

            pub_keep_alive_srv                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  pub_keep_alive_srv::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_keep_alive_srv::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_keep_alive_srv::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_keep_alive_srv::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_keep_alive_cli
//-------------------------------    
class pub_keep_alive_cli        :  public  pub_keep_alive_srv
{
public:
    //  inner classes

    
    // constructor
    explicit pub_keep_alive_cli (  const pub_keep_alive_srv&  parent,   const mtk::acs::msg::res_login::IC_session_info&  _login_confirmation );
    explicit pub_keep_alive_cli ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_keep_alive_cli (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_keep_alive_cli"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_keep_alive_cli"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::acs::msg::res_login::IC_session_info  login_confirmation; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& process_info_location_broker_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_keep_alive_cli__qpid_map
        {
        public:
            explicit  pub_keep_alive_cli__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_keep_alive_cli__qpid_map ( const pub_keep_alive_cli&  c ) : m_static(c) {}
            explicit  pub_keep_alive_cli__qpid_map (  const pub_keep_alive_srv&  parent,   const mtk::acs::msg::res_login::IC_session_info&  _login_confirmation );
            ~pub_keep_alive_cli__qpid_map() {};
            

            pub_keep_alive_cli                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  pub_keep_alive_cli::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_keep_alive_cli::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_keep_alive_cli::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_keep_alive_cli::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_exit
//-------------------------------    
class pub_exit     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_exit (    const mtk::msg::sub_process_info&  _process_info,   const std::string&  _reason );
    explicit pub_exit ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_exit (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_exit"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_exit"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_process_info                process_info; 
    std::string                               reason; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& process_info_location_broker_code,const std::string& process_info_cli_srv);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_exit__qpid_map
        {
        public:
            explicit  pub_exit__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_exit__qpid_map ( const pub_exit&  c ) : m_static(c) {}
            explicit  pub_exit__qpid_map (    const mtk::msg::sub_process_info&  _process_info,   const std::string&  _reason );
            ~pub_exit__qpid_map() {};
            

            pub_exit                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  pub_exit::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_exit::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_exit::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_exit::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_alarm
//-------------------------------    
class pub_alarm     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_alarm (    const mtk::msg::sub_process_info&  _process_info,   const std::string&  _code_source,   const std::string&  _subject,   const std::string&  _message,   const mtk::alEnPriority&  _priority,   const mtk::alEnType&  _type,   const mtk::DateTime&  _dateTime_generated,   const int16_t&  _alarm_id );
    explicit pub_alarm ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_alarm (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_alarm"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_alarm"; }
    
    static  int         static_return_message_RT_priority(void)        { return 1; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_process_info                process_info; 
    std::string                               code_source; 
    std::string                               subject; 
    std::string                               message; 
    mtk::alEnPriority                         priority; 
    mtk::alEnType                             type; 
    mtk::DateTime                             dateTime_generated; 
    int16_t                                   alarm_id; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& process_info_location_broker_code,const std::string& process_info_cli_srv);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_alarm__qpid_map
        {
        public:
            explicit  pub_alarm__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_alarm__qpid_map ( const pub_alarm&  c ) : m_static(c) {}
            explicit  pub_alarm__qpid_map (    const mtk::msg::sub_process_info&  _process_info,   const std::string&  _code_source,   const std::string&  _subject,   const std::string&  _message,   const mtk::alEnPriority&  _priority,   const mtk::alEnType&  _type,   const mtk::DateTime&  _dateTime_generated,   const int16_t&  _alarm_id );
            ~pub_alarm__qpid_map() {};
            

            pub_alarm                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  pub_alarm::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_alarm::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_alarm::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_alarm::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      req_command2
//-------------------------------    
class req_command2     
{
public:
    //  inner classes

    
    // constructor
    explicit req_command2 (    const mtk::msg::sub_request_info&  _request_info,   const std::string&  _broker_code,   const mtk::msg::sub_process_info&  _proc_info__destination,   const std::string&  _command_line );
    explicit req_command2 ( const qpid::types::Variant::Map&  mv );
    virtual ~req_command2 (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_command2"; }
    static  std::string static_get_message_type_as_string(void)        { return "req_command2"; }
    
    

    

    
    
    
    

    // fields
    mtk::msg::sub_request_info                request_info; 
    std::string                               broker_code; 
    mtk::msg::sub_process_info                proc_info__destination; 
    std::string                               command_line; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class req_command2__qpid_map
        {
        public:
            explicit  req_command2__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  req_command2__qpid_map ( const req_command2&  c ) : m_static(c) {}
            explicit  req_command2__qpid_map (    const mtk::msg::sub_request_info&  _request_info,   const std::string&  _broker_code,   const mtk::msg::sub_process_info&  _proc_info__destination,   const std::string&  _command_line );
            ~req_command2__qpid_map() {};
            

            req_command2                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      req_command_srv
//-------------------------------    
class req_command_srv        :  public  req_command2
{
public:
    //  inner classes

    
    // constructor
    explicit req_command_srv (  const req_command2&  parent );
    explicit req_command_srv ( const qpid::types::Variant::Map&  mv );
    virtual ~req_command_srv (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_command_srv"; }
    static  std::string static_get_message_type_as_string(void)        { return "req_command_srv"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& broker_code,const std::string& proc_info__destination_location_broker_code,const std::string& proc_info__destination_location_machine,const std::string& proc_info__destination_process_name,const std::string& proc_info__destination_process_uuid);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class req_command_srv__qpid_map
        {
        public:
            explicit  req_command_srv__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  req_command_srv__qpid_map ( const req_command_srv&  c ) : m_static(c) {}
            explicit  req_command_srv__qpid_map (  const req_command2&  parent );
            ~req_command_srv__qpid_map() {};
            

            req_command_srv                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  req_command_srv::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  req_command_srv::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  req_command_srv::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  req_command_srv::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      req_command_cli
//-------------------------------    
class req_command_cli        :  public  req_command2
{
public:
    //  inner classes

    
    // constructor
    explicit req_command_cli (  const req_command2&  parent );
    explicit req_command_cli ( const qpid::types::Variant::Map&  mv );
    virtual ~req_command_cli (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_command_cli"; }
    static  std::string static_get_message_type_as_string(void)        { return "req_command_cli"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& proc_info__destination_location_broker_code,const std::string& proc_info__destination_location_machine,const std::string& proc_info__destination_process_name,const std::string& proc_info__destination_process_uuid);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class req_command_cli__qpid_map
        {
        public:
            explicit  req_command_cli__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  req_command_cli__qpid_map ( const req_command_cli&  c ) : m_static(c) {}
            explicit  req_command_cli__qpid_map (  const req_command2&  parent );
            ~req_command_cli__qpid_map() {};
            

            req_command_cli                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  req_command_cli::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  req_command_cli::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  req_command_cli::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  req_command_cli::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_command_rd
//-------------------------------    
class sub_command_rd     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_command_rd (    const std::string&  _text );
    explicit sub_command_rd ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_command_rd (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_command_rd"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_command_rd"; }
    
    

    

    
    
    
    

    // fields
    std::string                               text; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_command_rd__qpid_map
        {
        public:
            explicit  sub_command_rd__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_command_rd__qpid_map ( const sub_command_rd&  c ) : m_static(c) {}
            explicit  sub_command_rd__qpid_map (    const std::string&  _text );
            ~sub_command_rd__qpid_map() {};
            

            sub_command_rd                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      res_command
//-------------------------------    
class res_command     
{
public:
    //  inner classes

    
    // constructor
    explicit res_command (    const mtk::msg::sub_r_response&  _response_info,   const sub_command_rd&  _response_data );
    explicit res_command ( const qpid::types::Variant::Map&  mv );
    virtual ~res_command (){};
    virtual std::string get_message_type_as_string       (void) const  { return "res_command"; }
    static  std::string static_get_message_type_as_string(void)        { return "res_command"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_r_response                  response_info; 
    sub_command_rd                            response_data; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& response_info_request_info_process_info_location_broker_code,const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_req_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class res_command__qpid_map
        {
        public:
            explicit  res_command__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  res_command__qpid_map ( const res_command&  c ) : m_static(c) {}
            explicit  res_command__qpid_map (    const mtk::msg::sub_r_response&  _response_info,   const sub_command_rd&  _response_data );
            ~res_command__qpid_map() {};
            

            res_command                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  res_command::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  res_command::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  res_command::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  res_command::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_central_keep_alive
//-------------------------------    
class pub_central_keep_alive     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_central_keep_alive (    const mtk::msg::sub_process_info&  _process_info,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check,   const bool&  _is_production );
    explicit pub_central_keep_alive ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_central_keep_alive (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_central_keep_alive"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_central_keep_alive"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_process_info                process_info; 
    mtk::dtTimeQuantity                       ka_interval_send; 
    mtk::dtTimeQuantity                       ka_interval_check; 
    bool                                      is_production; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& process_info_location_broker_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_central_keep_alive__qpid_map
        {
        public:
            explicit  pub_central_keep_alive__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_central_keep_alive__qpid_map ( const pub_central_keep_alive&  c ) : m_static(c) {}
            explicit  pub_central_keep_alive__qpid_map (    const mtk::msg::sub_process_info&  _process_info,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check,   const bool&  _is_production );
            ~pub_central_keep_alive__qpid_map() {};
            

            pub_central_keep_alive                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  pub_central_keep_alive::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_central_keep_alive::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_central_keep_alive::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_central_keep_alive::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        
    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const pub_enter & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_enter & c);
   void           operator >> (const YAML::Node& n,       pub_enter & c);

bool operator== (const pub_enter& a, const pub_enter& b);
bool operator!= (const pub_enter& a, const pub_enter& b);

    std::ostream& operator<< (std::ostream& o, const pub_keep_alive_srv & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_keep_alive_srv & c);
   void           operator >> (const YAML::Node& n,       pub_keep_alive_srv & c);

bool operator== (const pub_keep_alive_srv& a, const pub_keep_alive_srv& b);
bool operator!= (const pub_keep_alive_srv& a, const pub_keep_alive_srv& b);

    std::ostream& operator<< (std::ostream& o, const pub_keep_alive_cli & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_keep_alive_cli & c);
   void           operator >> (const YAML::Node& n,       pub_keep_alive_cli & c);

bool operator== (const pub_keep_alive_cli& a, const pub_keep_alive_cli& b);
bool operator!= (const pub_keep_alive_cli& a, const pub_keep_alive_cli& b);

    std::ostream& operator<< (std::ostream& o, const pub_exit & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_exit & c);
   void           operator >> (const YAML::Node& n,       pub_exit & c);

bool operator== (const pub_exit& a, const pub_exit& b);
bool operator!= (const pub_exit& a, const pub_exit& b);

    std::ostream& operator<< (std::ostream& o, const pub_alarm & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_alarm & c);
   void           operator >> (const YAML::Node& n,       pub_alarm & c);

bool operator== (const pub_alarm& a, const pub_alarm& b);
bool operator!= (const pub_alarm& a, const pub_alarm& b);

    std::ostream& operator<< (std::ostream& o, const req_command2 & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const req_command2 & c);
   void           operator >> (const YAML::Node& n,       req_command2 & c);

bool operator== (const req_command2& a, const req_command2& b);
bool operator!= (const req_command2& a, const req_command2& b);

    std::ostream& operator<< (std::ostream& o, const req_command_srv & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const req_command_srv & c);
   void           operator >> (const YAML::Node& n,       req_command_srv & c);

bool operator== (const req_command_srv& a, const req_command_srv& b);
bool operator!= (const req_command_srv& a, const req_command_srv& b);

    std::ostream& operator<< (std::ostream& o, const req_command_cli & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const req_command_cli & c);
   void           operator >> (const YAML::Node& n,       req_command_cli & c);

bool operator== (const req_command_cli& a, const req_command_cli& b);
bool operator!= (const req_command_cli& a, const req_command_cli& b);

    std::ostream& operator<< (std::ostream& o, const sub_command_rd & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_command_rd & c);
   void           operator >> (const YAML::Node& n,       sub_command_rd & c);

bool operator== (const sub_command_rd& a, const sub_command_rd& b);
bool operator!= (const sub_command_rd& a, const sub_command_rd& b);

    std::ostream& operator<< (std::ostream& o, const res_command & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const res_command & c);
   void           operator >> (const YAML::Node& n,       res_command & c);

bool operator== (const res_command& a, const res_command& b);
bool operator!= (const res_command& a, const res_command& b);

    std::ostream& operator<< (std::ostream& o, const pub_central_keep_alive & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_central_keep_alive & c);
   void           operator >> (const YAML::Node& n,       pub_central_keep_alive & c);

bool operator== (const pub_central_keep_alive& a, const pub_central_keep_alive& b);
bool operator!= (const pub_central_keep_alive& a, const pub_central_keep_alive& b);

void __internal_add2map (qpid::types::Variant::Map& map, const pub_enter& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_enter>& a, const std::string& field);
void copy (pub_enter& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_keep_alive_srv& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_keep_alive_srv>& a, const std::string& field);
void copy (pub_keep_alive_srv& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_keep_alive_cli& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_keep_alive_cli>& a, const std::string& field);
void copy (pub_keep_alive_cli& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_exit& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_exit>& a, const std::string& field);
void copy (pub_exit& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_alarm& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_alarm>& a, const std::string& field);
void copy (pub_alarm& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const req_command2& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_command2>& a, const std::string& field);
void copy (req_command2& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const req_command_srv& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_command_srv>& a, const std::string& field);
void copy (req_command_srv& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const req_command_cli& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_command_cli>& a, const std::string& field);
void copy (req_command_cli& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_command_rd& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_command_rd>& a, const std::string& field);
void copy (sub_command_rd& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const res_command& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_command>& a, const std::string& field);
void copy (res_command& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_central_keep_alive& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_central_keep_alive>& a, const std::string& field);
void copy (pub_central_keep_alive& a, const qpid::types::Variant& map);

    
    
    
//  fordward declarations  dynamic--------------------------------------------------------


inline std::ostream& operator<< (std::ostream& o, const pub_enter__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_enter__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_enter__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_enter__qpid_map& a, const pub_enter__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_enter__qpid_map& a, const pub_enter__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_enter__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_enter__qpid_map>& a, const std::string& field);
void copy (pub_enter__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_keep_alive_srv__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_keep_alive_srv__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_keep_alive_srv__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_keep_alive_srv__qpid_map& a, const pub_keep_alive_srv__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_keep_alive_srv__qpid_map& a, const pub_keep_alive_srv__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_keep_alive_srv__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_keep_alive_srv__qpid_map>& a, const std::string& field);
void copy (pub_keep_alive_srv__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_keep_alive_cli__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_keep_alive_cli__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_keep_alive_cli__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_keep_alive_cli__qpid_map& a, const pub_keep_alive_cli__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_keep_alive_cli__qpid_map& a, const pub_keep_alive_cli__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_keep_alive_cli__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_keep_alive_cli__qpid_map>& a, const std::string& field);
void copy (pub_keep_alive_cli__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_exit__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_exit__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_exit__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_exit__qpid_map& a, const pub_exit__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_exit__qpid_map& a, const pub_exit__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_exit__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_exit__qpid_map>& a, const std::string& field);
void copy (pub_exit__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_alarm__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_alarm__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_alarm__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_alarm__qpid_map& a, const pub_alarm__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_alarm__qpid_map& a, const pub_alarm__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_alarm__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_alarm__qpid_map>& a, const std::string& field);
void copy (pub_alarm__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const req_command2__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const req_command2__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       req_command2__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const req_command2__qpid_map& a, const req_command2__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const req_command2__qpid_map& a, const req_command2__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const req_command2__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_command2__qpid_map>& a, const std::string& field);
void copy (req_command2__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const req_command_srv__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const req_command_srv__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       req_command_srv__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const req_command_srv__qpid_map& a, const req_command_srv__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const req_command_srv__qpid_map& a, const req_command_srv__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const req_command_srv__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_command_srv__qpid_map>& a, const std::string& field);
void copy (req_command_srv__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const req_command_cli__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const req_command_cli__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       req_command_cli__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const req_command_cli__qpid_map& a, const req_command_cli__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const req_command_cli__qpid_map& a, const req_command_cli__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const req_command_cli__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_command_cli__qpid_map>& a, const std::string& field);
void copy (req_command_cli__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_command_rd__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_command_rd__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_command_rd__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_command_rd__qpid_map& a, const sub_command_rd__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_command_rd__qpid_map& a, const sub_command_rd__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_command_rd__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_command_rd__qpid_map>& a, const std::string& field);
void copy (sub_command_rd__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const res_command__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const res_command__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       res_command__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const res_command__qpid_map& a, const res_command__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const res_command__qpid_map& a, const res_command__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const res_command__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_command__qpid_map>& a, const std::string& field);
void copy (res_command__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_central_keep_alive__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_central_keep_alive__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_central_keep_alive__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_central_keep_alive__qpid_map& a, const pub_central_keep_alive__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_central_keep_alive__qpid_map& a, const pub_central_keep_alive__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_central_keep_alive__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_central_keep_alive__qpid_map>& a, const std::string& field);
void copy (pub_central_keep_alive__qpid_map& a, const qpid::types::Variant& map);

    pub_enter  __internal_get_default(pub_enter *);
    
        inline pub_enter__qpid_map  __internal_get_default(pub_enter__qpid_map *) { return  pub_enter__qpid_map(__internal_get_default((pub_enter*)0));  }

    pub_keep_alive_srv  __internal_get_default(pub_keep_alive_srv *);
    
        inline pub_keep_alive_srv__qpid_map  __internal_get_default(pub_keep_alive_srv__qpid_map *) { return  pub_keep_alive_srv__qpid_map(__internal_get_default((pub_keep_alive_srv*)0));  }

    pub_keep_alive_cli  __internal_get_default(pub_keep_alive_cli *);
    
        inline pub_keep_alive_cli__qpid_map  __internal_get_default(pub_keep_alive_cli__qpid_map *) { return  pub_keep_alive_cli__qpid_map(__internal_get_default((pub_keep_alive_cli*)0));  }

    pub_exit  __internal_get_default(pub_exit *);
    
        inline pub_exit__qpid_map  __internal_get_default(pub_exit__qpid_map *) { return  pub_exit__qpid_map(__internal_get_default((pub_exit*)0));  }

    pub_alarm  __internal_get_default(pub_alarm *);
    
        inline pub_alarm__qpid_map  __internal_get_default(pub_alarm__qpid_map *) { return  pub_alarm__qpid_map(__internal_get_default((pub_alarm*)0));  }

    req_command2  __internal_get_default(req_command2 *);
    
        inline req_command2__qpid_map  __internal_get_default(req_command2__qpid_map *) { return  req_command2__qpid_map(__internal_get_default((req_command2*)0));  }

    req_command_srv  __internal_get_default(req_command_srv *);
    
        inline req_command_srv__qpid_map  __internal_get_default(req_command_srv__qpid_map *) { return  req_command_srv__qpid_map(__internal_get_default((req_command_srv*)0));  }

    req_command_cli  __internal_get_default(req_command_cli *);
    
        inline req_command_cli__qpid_map  __internal_get_default(req_command_cli__qpid_map *) { return  req_command_cli__qpid_map(__internal_get_default((req_command_cli*)0));  }

    sub_command_rd  __internal_get_default(sub_command_rd *);
    
        inline sub_command_rd__qpid_map  __internal_get_default(sub_command_rd__qpid_map *) { return  sub_command_rd__qpid_map(__internal_get_default((sub_command_rd*)0));  }

    res_command  __internal_get_default(res_command *);
    
        inline res_command__qpid_map  __internal_get_default(res_command__qpid_map *) { return  res_command__qpid_map(__internal_get_default((res_command*)0));  }

    pub_central_keep_alive  __internal_get_default(pub_central_keep_alive *);
    
        inline pub_central_keep_alive__qpid_map  __internal_get_default(pub_central_keep_alive__qpid_map *) { return  pub_central_keep_alive__qpid_map(__internal_get_default((pub_central_keep_alive*)0));  }


};   //namespace mtk {
};   //namespace admin {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_enter)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_enter__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_keep_alive_srv)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_keep_alive_srv__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_keep_alive_cli)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_keep_alive_cli__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_exit)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_exit__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_alarm)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_alarm__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::req_command_srv)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::req_command_srv__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::req_command_cli)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::req_command_cli__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::res_command)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::res_command__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_central_keep_alive)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_central_keep_alive__qpid_map)




#endif
