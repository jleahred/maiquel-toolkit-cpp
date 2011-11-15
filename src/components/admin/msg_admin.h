
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

#include "mtk_qpid/mtk_qpid.hpp"


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
    explicit pub_enter (    const std::string&  _cli_srv,   const mtk::msg::sub_process_info&  _process_info,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check );
    explicit pub_enter ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_enter (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_enter"; };
    static  std::string static_get_message_type_as_string(void)        { return "pub_enter"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               cli_srv; 
    mtk::msg::sub_process_info                process_info; 
    mtk::dtTimeQuantity                       ka_interval_send; 
    mtk::dtTimeQuantity                       ka_interval_check; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& cli_srv);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
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
    virtual std::string get_message_type_as_string       (void) const  { return "pub_keep_alive_srv"; };
    static  std::string static_get_message_type_as_string(void)        { return "pub_keep_alive_srv"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_process_info                process_info; 
    mtk::dtTimeQuantity                       ka_interval_send; 
    mtk::dtTimeQuantity                       ka_interval_check; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject ();
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
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
    virtual std::string get_message_type_as_string       (void) const  { return "pub_keep_alive_cli"; };
    static  std::string static_get_message_type_as_string(void)        { return "pub_keep_alive_cli"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::acs::msg::res_login::IC_session_info  login_confirmation; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject ();
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      pub_exit
//-------------------------------    
class pub_exit     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_exit (    const std::string&  _cli_srv,   const mtk::msg::sub_process_info&  _process_info,   const std::string&  _reason );
    explicit pub_exit ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_exit (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_exit"; };
    static  std::string static_get_message_type_as_string(void)        { return "pub_exit"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               cli_srv; 
    mtk::msg::sub_process_info                process_info; 
    std::string                               reason; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& cli_srv);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      pub_alarm
//-------------------------------    
class pub_alarm     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_alarm (    const std::string&  _cli_srv,   const mtk::msg::sub_process_info&  _process_info,   const std::string&  _code_source,   const std::string&  _subject,   const std::string&  _message,   const mtk::alEnPriority&  _priority,   const mtk::alEnType&  _type,   const mtk::DateTime&  _dateTime_generated,   const int16_t&  _alarm_id );
    explicit pub_alarm ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_alarm (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_alarm"; };
    static  std::string static_get_message_type_as_string(void)        { return "pub_alarm"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               cli_srv; 
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
    static mtk::t_qpid_filter  get_in_subject (const std::string& cli_srv);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      req_command2
//-------------------------------    
class req_command2     
{
public:
    //  inner classes

    
    // constructor
    explicit req_command2 (    const mtk::msg::sub_request_info&  _request_info,   const std::string&  _sender_broker_code,   const mtk::msg::sub_process_info&  _proc_info__destination,   const std::string&  _command_line );
    explicit req_command2 ( const qpid::types::Variant::Map&  mv );
    virtual ~req_command2 (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_command2"; };
    static  std::string static_get_message_type_as_string(void)        { return "req_command2"; };

    
    
    
    

    // fields
    mtk::msg::sub_request_info                request_info; 
    std::string                               sender_broker_code; 
    mtk::msg::sub_process_info                proc_info__destination; 
    std::string                               command_line; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
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
    virtual std::string get_message_type_as_string       (void) const  { return "req_command_srv"; };
    static  std::string static_get_message_type_as_string(void)        { return "req_command_srv"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& sender_broker_code,const std::string& proc_info__destination_location_broker_code,const std::string& proc_info__destination_location_machine,const std::string& proc_info__destination_process_name,const std::string& proc_info__destination_process_uuid);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
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
    virtual std::string get_message_type_as_string       (void) const  { return "req_command_cli"; };
    static  std::string static_get_message_type_as_string(void)        { return "req_command_cli"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& proc_info__destination_location_broker_code,const std::string& proc_info__destination_location_machine,const std::string& proc_info__destination_process_name,const std::string& proc_info__destination_process_uuid);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
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
    virtual std::string get_message_type_as_string       (void) const  { return "sub_command_rd"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_command_rd"; };

    
    
    
    

    // fields
    std::string                               text; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
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
    virtual std::string get_message_type_as_string       (void) const  { return "res_command"; };
    static  std::string static_get_message_type_as_string(void)        { return "res_command"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_r_response                  response_info; 
    sub_command_rd                            response_data; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_req_code);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      pub_central_keep_alive
//-------------------------------    
class pub_central_keep_alive     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_central_keep_alive (    const mtk::msg::sub_process_info&  _process_info,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check );
    explicit pub_central_keep_alive ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_central_keep_alive (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_central_keep_alive"; };
    static  std::string static_get_message_type_as_string(void)        { return "pub_central_keep_alive"; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

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
    
private:
    std::string check_recomended(void) const;
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

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const pub_enter& a);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_enter& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_enter>& a, const std::string& field);
void copy (pub_enter& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const pub_keep_alive_srv& a);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_keep_alive_srv& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_keep_alive_srv>& a, const std::string& field);
void copy (pub_keep_alive_srv& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const pub_keep_alive_cli& a);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_keep_alive_cli& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_keep_alive_cli>& a, const std::string& field);
void copy (pub_keep_alive_cli& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const pub_exit& a);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_exit& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_exit>& a, const std::string& field);
void copy (pub_exit& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const pub_alarm& a);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_alarm& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_alarm>& a, const std::string& field);
void copy (pub_alarm& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const req_command2& a);
void __internal_add2map (qpid::types::Variant::Map& map, const req_command2& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_command2>& a, const std::string& field);
void copy (req_command2& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const req_command_srv& a);
void __internal_add2map (qpid::types::Variant::Map& map, const req_command_srv& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_command_srv>& a, const std::string& field);
void copy (req_command_srv& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const req_command_cli& a);
void __internal_add2map (qpid::types::Variant::Map& map, const req_command_cli& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_command_cli>& a, const std::string& field);
void copy (req_command_cli& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_command_rd& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_command_rd& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_command_rd>& a, const std::string& field);
void copy (sub_command_rd& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const res_command& a);
void __internal_add2map (qpid::types::Variant::Map& map, const res_command& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_command>& a, const std::string& field);
void copy (res_command& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const pub_central_keep_alive& a);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_central_keep_alive& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_central_keep_alive>& a, const std::string& field);
void copy (pub_central_keep_alive& a, const qpid::types::Variant& map);

    pub_enter  __internal_get_default(pub_enter *);
    
    pub_keep_alive_srv  __internal_get_default(pub_keep_alive_srv *);
    
    pub_keep_alive_cli  __internal_get_default(pub_keep_alive_cli *);
    
    pub_exit  __internal_get_default(pub_exit *);
    
    pub_alarm  __internal_get_default(pub_alarm *);
    
    req_command2  __internal_get_default(req_command2 *);
    
    req_command_srv  __internal_get_default(req_command_srv *);
    
    req_command_cli  __internal_get_default(req_command_cli *);
    
    sub_command_rd  __internal_get_default(sub_command_rd *);
    
    res_command  __internal_get_default(res_command *);
    
    pub_central_keep_alive  __internal_get_default(pub_central_keep_alive *);
    

};   //namespace mtk {
};   //namespace admin {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_enter)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_keep_alive_srv)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_keep_alive_cli)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_exit)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_alarm)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::req_command_srv)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::req_command_cli)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::res_command)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::pub_central_keep_alive)




#endif
