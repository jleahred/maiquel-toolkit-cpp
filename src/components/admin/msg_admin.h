
#ifndef  __msg_admin__
#define  __msg_admin__


// generated automatically
// coded last modification:        Tue Mar 15 12:41:59 2011


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

namespace mtk { 
namespace admin { 
namespace msg { 




//-------------------------------
//      enter
//-------------------------------    
class enter     
{
public:
    //  inner classes

    
    // constructor
    explicit enter (    const mtk::msg::sub_process_location&  _process_location,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check );
    explicit enter ( const qpid::messaging::Message& message );
    virtual ~enter (){};
    virtual std::string get_message_type_as_string       (void) const  { return "enter"; };
    static  std::string static_get_message_type_as_string(void)        { return "enter"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    mtk::msg::sub_process_location            process_location; 
    mtk::dtTimeQuantity                       ka_interval_send; 
    mtk::dtTimeQuantity                       ka_interval_check; 



    //  subject info
    static std::string  get_in_subject ();
virtual std::string  get_out_subject (void) const;

private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      keep_alive
//-------------------------------    
class keep_alive     
{
public:
    //  inner classes

    
    // constructor
    explicit keep_alive (    const mtk::msg::sub_process_location&  _process_location,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check );
    explicit keep_alive ( const qpid::messaging::Message& message );
    virtual ~keep_alive (){};
    virtual std::string get_message_type_as_string       (void) const  { return "keep_alive"; };
    static  std::string static_get_message_type_as_string(void)        { return "keep_alive"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    mtk::msg::sub_process_location            process_location; 
    mtk::dtTimeQuantity                       ka_interval_send; 
    mtk::dtTimeQuantity                       ka_interval_check; 



    //  subject info
    static std::string  get_in_subject ();
virtual std::string  get_out_subject (void) const;

private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      exit
//-------------------------------    
class exit     
{
public:
    //  inner classes

    
    // constructor
    explicit exit (    const mtk::msg::sub_process_location&  _process_location,   const std::string&  _reason );
    explicit exit ( const qpid::messaging::Message& message );
    virtual ~exit (){};
    virtual std::string get_message_type_as_string       (void) const  { return "exit"; };
    static  std::string static_get_message_type_as_string(void)        { return "exit"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    mtk::msg::sub_process_location            process_location; 
    std::string                               reason; 



    //  subject info
    static std::string  get_in_subject ();
virtual std::string  get_out_subject (void) const;

private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      alarm
//-------------------------------    
class alarm     
{
public:
    //  inner classes

    
    // constructor
    explicit alarm (    const mtk::msg::sub_process_location&  _process_location,   const std::string&  _code_source,   const std::string&  _message,   const mtk::alEnPriority&  _priority,   const mtk::alEnType&  _type,   const mtk::DateTime&  _dateTime_generated,   const int16_t&  _alarm_id );
    explicit alarm ( const qpid::messaging::Message& message );
    virtual ~alarm (){};
    virtual std::string get_message_type_as_string       (void) const  { return "alarm"; };
    static  std::string static_get_message_type_as_string(void)        { return "alarm"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    mtk::msg::sub_process_location            process_location; 
    std::string                               code_source; 
    std::string                               message; 
    mtk::alEnPriority                         priority; 
    mtk::alEnType                             type; 
    mtk::DateTime                             dateTime_generated; 
    int16_t                                   alarm_id; 



    //  subject info
    static std::string  get_in_subject ();
virtual std::string  get_out_subject (void) const;

private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      command
//-------------------------------    
class command     
{
public:
    //  inner classes

    
    // constructor
    explicit command (    const mtk::msg::sub_request_info&  _request_info,   const mtk::msg::sub_process_location&  _proc_loc__destination,   const std::string&  _command_line );
    explicit command ( const qpid::messaging::Message& message );
    virtual ~command (){};
    virtual std::string get_message_type_as_string       (void) const  { return "command"; };
    static  std::string static_get_message_type_as_string(void)        { return "command"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 
    mtk::msg::sub_process_location            proc_loc__destination; 
    std::string                               command_line; 



    //  subject info
    static std::string  get_in_subject (const std::string& proc_loc__destination_location,const std::string& proc_loc__destination_machine,const std::string& proc_loc__destination_process_name,const std::string& proc_loc__destination_process_uuid);
virtual std::string  get_out_subject (void) const;

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
    explicit sub_command_rd ( const qpid::messaging::Message& message );
    virtual ~sub_command_rd (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_command_rd"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_command_rd"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    std::string                               text; 



    //  subject info
    
private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      command_response
//-------------------------------    
class command_response     
{
public:
    //  inner classes

    
    // constructor
    explicit command_response (    const mtk::msg::sub_r_response&  _response_info,   const sub_command_rd&  _response_data );
    explicit command_response ( const qpid::messaging::Message& message );
    virtual ~command_response (){};
    virtual std::string get_message_type_as_string       (void) const  { return "command_response"; };
    static  std::string static_get_message_type_as_string(void)        { return "command_response"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    mtk::msg::sub_r_response                  response_info; 
    sub_command_rd                            response_data; 



    //  subject info
    static std::string  get_in_subject (const std::string& response_info_request_info_process_location_process_uuid,const std::string& response_info_request_info_req_id_req_code);
virtual std::string  get_out_subject (void) const;

private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      central_keep_alive
//-------------------------------    
class central_keep_alive     
{
public:
    //  inner classes

    
    // constructor
    explicit central_keep_alive (    const mtk::msg::sub_process_location&  _process_location,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check );
    explicit central_keep_alive ( const qpid::messaging::Message& message );
    virtual ~central_keep_alive (){};
    virtual std::string get_message_type_as_string       (void) const  { return "central_keep_alive"; };
    static  std::string static_get_message_type_as_string(void)        { return "central_keep_alive"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    mtk::msg::sub_process_location            process_location; 
    mtk::dtTimeQuantity                       ka_interval_send; 
    mtk::dtTimeQuantity                       ka_interval_check; 



    //  subject info
    static std::string  get_in_subject ();
virtual std::string  get_out_subject (void) const;

private:
    std::string check_recomended(void) const;
};




    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const enter & c);

bool operator== (const enter& a, const enter& b);
bool operator!= (const enter& a, const enter& b);

    std::ostream& operator<< (std::ostream& o, const keep_alive & c);

bool operator== (const keep_alive& a, const keep_alive& b);
bool operator!= (const keep_alive& a, const keep_alive& b);

    std::ostream& operator<< (std::ostream& o, const exit & c);

bool operator== (const exit& a, const exit& b);
bool operator!= (const exit& a, const exit& b);

    std::ostream& operator<< (std::ostream& o, const alarm & c);

bool operator== (const alarm& a, const alarm& b);
bool operator!= (const alarm& a, const alarm& b);

    std::ostream& operator<< (std::ostream& o, const command & c);

bool operator== (const command& a, const command& b);
bool operator!= (const command& a, const command& b);

    std::ostream& operator<< (std::ostream& o, const sub_command_rd & c);

bool operator== (const sub_command_rd& a, const sub_command_rd& b);
bool operator!= (const sub_command_rd& a, const sub_command_rd& b);

    std::ostream& operator<< (std::ostream& o, const command_response & c);

bool operator== (const command_response& a, const command_response& b);
bool operator!= (const command_response& a, const command_response& b);

    std::ostream& operator<< (std::ostream& o, const central_keep_alive & c);

bool operator== (const central_keep_alive& a, const central_keep_alive& b);
bool operator!= (const central_keep_alive& a, const central_keep_alive& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const enter& a);
void __internal_add2map (qpid::types::Variant::Map& map, const enter& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<enter>& a, const std::string& field);
void copy (enter& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const keep_alive& a);
void __internal_add2map (qpid::types::Variant::Map& map, const keep_alive& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<keep_alive>& a, const std::string& field);
void copy (keep_alive& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const exit& a);
void __internal_add2map (qpid::types::Variant::Map& map, const exit& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<exit>& a, const std::string& field);
void copy (exit& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const alarm& a);
void __internal_add2map (qpid::types::Variant::Map& map, const alarm& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<alarm>& a, const std::string& field);
void copy (alarm& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const command& a);
void __internal_add2map (qpid::types::Variant::Map& map, const command& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<command>& a, const std::string& field);
void copy (command& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_command_rd& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_command_rd& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_command_rd>& a, const std::string& field);
void copy (sub_command_rd& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const command_response& a);
void __internal_add2map (qpid::types::Variant::Map& map, const command_response& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<command_response>& a, const std::string& field);
void copy (command_response& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const central_keep_alive& a);
void __internal_add2map (qpid::types::Variant::Map& map, const central_keep_alive& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<central_keep_alive>& a, const std::string& field);
void copy (central_keep_alive& a, const qpid::types::Variant& map);

    enter  __internal_get_default(enter *);
    
    keep_alive  __internal_get_default(keep_alive *);
    
    exit  __internal_get_default(exit *);
    
    alarm  __internal_get_default(alarm *);
    
    command  __internal_get_default(command *);
    
    sub_command_rd  __internal_get_default(sub_command_rd *);
    
    command_response  __internal_get_default(command_response *);
    
    central_keep_alive  __internal_get_default(central_keep_alive *);
    

};   //namespace mtk {
};   //namespace admin {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::enter)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::keep_alive)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::exit)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::alarm)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::command)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::sub_command_rd)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::command_response)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::admin::msg::central_keep_alive)




#endif
