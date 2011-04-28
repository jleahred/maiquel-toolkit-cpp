
#ifndef  __msg_trd_cli_ls__
#define  __msg_trd_cli_ls__


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
#include "msg_trd_common.h"

namespace mtk { 
namespace trd { 
namespace msg { 




//-------------------------------
//      sub_position_ls
//-------------------------------    
class sub_position_ls     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_position_ls (    const mtk::FixedNumber&  _price,   const mtk::FixedNumber&  _quantity,   const enBuySell&  _side );
    explicit sub_position_ls ( const qpid::messaging::Message& message );
    virtual ~sub_position_ls (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_position_ls"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_position_ls"; };
    
    

    // fields
    mtk::FixedNumber                          price; 
    mtk::FixedNumber                          quantity; 
    enBuySell                                 side; 



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      sub_order_ls_confirmated
//-------------------------------    
class sub_order_ls_confirmated     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_order_ls_confirmated (    const sub_order_id&  _order_id,   const mtk::msg::sub_product_code&  _product_code,   const sub_position_ls&  _market_pos,   const sub_total_executions&  _total_execs,   const std::string&  _cli_ref );
    explicit sub_order_ls_confirmated ( const qpid::messaging::Message& message );
    virtual ~sub_order_ls_confirmated (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_order_ls_confirmated"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_order_ls_confirmated"; };
    
    

    // fields
    sub_order_id                              order_id; 
    mtk::msg::sub_product_code                product_code; 
    sub_position_ls                           market_pos; 
    sub_total_executions                      total_execs; 
    std::string                               cli_ref; 



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      RQ_XX_LS
//-------------------------------    
class RQ_XX_LS     
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_XX_LS (    const mtk::msg::sub_request_info&  _req_info,   const sub_order_id&  _order_id,   const mtk::msg::sub_product_code&  _product_code,   const sub_position_ls&  _request_pos,   const std::string&  _cli_ref,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
    explicit RQ_XX_LS ( const qpid::messaging::Message& message );
    virtual ~RQ_XX_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_XX_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "RQ_XX_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_request_info                req_info; 
    sub_order_id                              order_id; 
    mtk::msg::sub_product_code                product_code; 
    sub_position_ls                           request_pos; 
    std::string                               cli_ref; 
    mtk::msg::sub_control_fluct               orig_control_fluct; 



    //  subject info
    static std::string  get_in_subject (const std::string& req_info_process_location,const std::string& product_code_sys_code_market,const std::string& product_code_sys_code_product);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      RQ_NW_LS
//-------------------------------    
class RQ_NW_LS        :  public  RQ_XX_LS
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_NW_LS (  const RQ_XX_LS&  parent );
    explicit RQ_NW_LS ( const qpid::messaging::Message& message );
    virtual ~RQ_NW_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_NW_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "RQ_NW_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  subject info
    
    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      RQ_MD_LS
//-------------------------------    
class RQ_MD_LS        :  public  RQ_XX_LS
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_MD_LS (  const RQ_XX_LS&  parent );
    explicit RQ_MD_LS ( const qpid::messaging::Message& message );
    virtual ~RQ_MD_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_MD_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "RQ_MD_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  subject info
    
    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      RQ_CC_LS
//-------------------------------    
class RQ_CC_LS        :  public  RQ_XX_LS
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_CC_LS (  const RQ_XX_LS&  parent );
    explicit RQ_CC_LS ( const qpid::messaging::Message& message );
    virtual ~RQ_CC_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_CC_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "RQ_CC_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  subject info
    
    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      CF_XX_LS
//-------------------------------    
class CF_XX_LS     
{
public:
    //  inner classes

    
    // constructor
    explicit CF_XX_LS (    const mtk::msg::sub_request_info&  _req_info,   const sub_order_ls_confirmated&  _confirmated_info,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
    explicit CF_XX_LS ( const qpid::messaging::Message& message );
    virtual ~CF_XX_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_XX_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_XX_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_request_info                req_info; 
    sub_order_ls_confirmated                  confirmated_info; 
    mtk::msg::sub_control_fluct               orig_control_fluct; 



    //  subject info
    static std::string  get_in_subject (const std::string& req_info_process_location_location_client_code,const std::string& confirmated_info_product_code_sys_code_market,const std::string& confirmated_info_product_code_sys_code_product);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      CF_NW_LS
//-------------------------------    
class CF_NW_LS        :  public  CF_XX_LS
{
public:
    //  inner classes

    
    // constructor
    explicit CF_NW_LS (  const CF_XX_LS&  parent );
    explicit CF_NW_LS ( const qpid::messaging::Message& message );
    virtual ~CF_NW_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_NW_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_NW_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  subject info
    
    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      CF_MD_LS
//-------------------------------    
class CF_MD_LS        :  public  CF_XX_LS
{
public:
    //  inner classes

    
    // constructor
    explicit CF_MD_LS (  const CF_XX_LS&  parent );
    explicit CF_MD_LS ( const qpid::messaging::Message& message );
    virtual ~CF_MD_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_MD_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_MD_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  subject info
    
    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      CF_CC_LS
//-------------------------------    
class CF_CC_LS        :  public  CF_XX_LS
{
public:
    //  inner classes

    
    // constructor
    explicit CF_CC_LS (  const CF_XX_LS&  parent );
    explicit CF_CC_LS ( const qpid::messaging::Message& message );
    virtual ~CF_CC_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_CC_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_CC_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  subject info
    
    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      CF_EX_LS
//-------------------------------    
class CF_EX_LS        :  public  CF_XX_LS
{
public:
    //  inner classes

    
    // constructor
    explicit CF_EX_LS (  const CF_XX_LS&  parent,   const sub_position_ls&  _executed_pos );
    explicit CF_EX_LS ( const qpid::messaging::Message& message );
    virtual ~CF_EX_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_EX_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_EX_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    sub_position_ls                           executed_pos; 



    //  subject info
    
    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      RJ_XX_LS
//-------------------------------    
class RJ_XX_LS     
{
public:
    //  inner classes

    
    // constructor
    explicit RJ_XX_LS (    const mtk::msg::sub_request_info&  _req_info,   const sub_order_ls_confirmated&  _confirmated_info,   const std::string&  _description,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
    explicit RJ_XX_LS ( const qpid::messaging::Message& message );
    virtual ~RJ_XX_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RJ_XX_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "RJ_XX_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_request_info                req_info; 
    sub_order_ls_confirmated                  confirmated_info; 
    std::string                               description; 
    mtk::msg::sub_control_fluct               orig_control_fluct; 



    //  subject info
    static std::string  get_in_subject (const std::string& req_info_process_location_location_client_code,const std::string& confirmated_info_product_code_sys_code_market,const std::string& confirmated_info_product_code_sys_code_product);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      RJ_NW_LS
//-------------------------------    
class RJ_NW_LS        :  public  RJ_XX_LS
{
public:
    //  inner classes

    
    // constructor
    explicit RJ_NW_LS (  const RJ_XX_LS&  parent );
    explicit RJ_NW_LS ( const qpid::messaging::Message& message );
    virtual ~RJ_NW_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RJ_NW_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "RJ_NW_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  subject info
    
    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      RJ_MD_LS
//-------------------------------    
class RJ_MD_LS        :  public  RJ_XX_LS
{
public:
    //  inner classes

    
    // constructor
    explicit RJ_MD_LS (  const RJ_XX_LS&  parent );
    explicit RJ_MD_LS ( const qpid::messaging::Message& message );
    virtual ~RJ_MD_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RJ_MD_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "RJ_MD_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  subject info
    
    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      RJ_CC_LS
//-------------------------------    
class RJ_CC_LS        :  public  RJ_XX_LS
{
public:
    //  inner classes

    
    // constructor
    explicit RJ_CC_LS (  const RJ_XX_LS&  parent );
    explicit RJ_CC_LS ( const qpid::messaging::Message& message );
    virtual ~RJ_CC_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RJ_CC_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "RJ_CC_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  subject info
    
    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_position_ls & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const sub_position_ls & c);

bool operator== (const sub_position_ls& a, const sub_position_ls& b);
bool operator!= (const sub_position_ls& a, const sub_position_ls& b);

    std::ostream& operator<< (std::ostream& o, const sub_order_ls_confirmated & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const sub_order_ls_confirmated & c);

bool operator== (const sub_order_ls_confirmated& a, const sub_order_ls_confirmated& b);
bool operator!= (const sub_order_ls_confirmated& a, const sub_order_ls_confirmated& b);

    std::ostream& operator<< (std::ostream& o, const RQ_XX_LS & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const RQ_XX_LS & c);

bool operator== (const RQ_XX_LS& a, const RQ_XX_LS& b);
bool operator!= (const RQ_XX_LS& a, const RQ_XX_LS& b);

    std::ostream& operator<< (std::ostream& o, const RQ_NW_LS & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const RQ_NW_LS & c);

bool operator== (const RQ_NW_LS& a, const RQ_NW_LS& b);
bool operator!= (const RQ_NW_LS& a, const RQ_NW_LS& b);

    std::ostream& operator<< (std::ostream& o, const RQ_MD_LS & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const RQ_MD_LS & c);

bool operator== (const RQ_MD_LS& a, const RQ_MD_LS& b);
bool operator!= (const RQ_MD_LS& a, const RQ_MD_LS& b);

    std::ostream& operator<< (std::ostream& o, const RQ_CC_LS & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const RQ_CC_LS & c);

bool operator== (const RQ_CC_LS& a, const RQ_CC_LS& b);
bool operator!= (const RQ_CC_LS& a, const RQ_CC_LS& b);

    std::ostream& operator<< (std::ostream& o, const CF_XX_LS & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const CF_XX_LS & c);

bool operator== (const CF_XX_LS& a, const CF_XX_LS& b);
bool operator!= (const CF_XX_LS& a, const CF_XX_LS& b);

    std::ostream& operator<< (std::ostream& o, const CF_NW_LS & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const CF_NW_LS & c);

bool operator== (const CF_NW_LS& a, const CF_NW_LS& b);
bool operator!= (const CF_NW_LS& a, const CF_NW_LS& b);

    std::ostream& operator<< (std::ostream& o, const CF_MD_LS & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const CF_MD_LS & c);

bool operator== (const CF_MD_LS& a, const CF_MD_LS& b);
bool operator!= (const CF_MD_LS& a, const CF_MD_LS& b);

    std::ostream& operator<< (std::ostream& o, const CF_CC_LS & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const CF_CC_LS & c);

bool operator== (const CF_CC_LS& a, const CF_CC_LS& b);
bool operator!= (const CF_CC_LS& a, const CF_CC_LS& b);

    std::ostream& operator<< (std::ostream& o, const CF_EX_LS & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const CF_EX_LS & c);

bool operator== (const CF_EX_LS& a, const CF_EX_LS& b);
bool operator!= (const CF_EX_LS& a, const CF_EX_LS& b);

    std::ostream& operator<< (std::ostream& o, const RJ_XX_LS & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const RJ_XX_LS & c);

bool operator== (const RJ_XX_LS& a, const RJ_XX_LS& b);
bool operator!= (const RJ_XX_LS& a, const RJ_XX_LS& b);

    std::ostream& operator<< (std::ostream& o, const RJ_NW_LS & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const RJ_NW_LS & c);

bool operator== (const RJ_NW_LS& a, const RJ_NW_LS& b);
bool operator!= (const RJ_NW_LS& a, const RJ_NW_LS& b);

    std::ostream& operator<< (std::ostream& o, const RJ_MD_LS & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const RJ_MD_LS & c);

bool operator== (const RJ_MD_LS& a, const RJ_MD_LS& b);
bool operator!= (const RJ_MD_LS& a, const RJ_MD_LS& b);

    std::ostream& operator<< (std::ostream& o, const RJ_CC_LS & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const RJ_CC_LS & c);

bool operator== (const RJ_CC_LS& a, const RJ_CC_LS& b);
bool operator!= (const RJ_CC_LS& a, const RJ_CC_LS& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_position_ls& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_position_ls& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_position_ls>& a, const std::string& field);
void copy (sub_position_ls& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_order_ls_confirmated& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_order_ls_confirmated& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_order_ls_confirmated>& a, const std::string& field);
void copy (sub_order_ls_confirmated& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RQ_XX_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_XX_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_XX_LS>& a, const std::string& field);
void copy (RQ_XX_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RQ_NW_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_NW_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_NW_LS>& a, const std::string& field);
void copy (RQ_NW_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RQ_MD_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_MD_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_MD_LS>& a, const std::string& field);
void copy (RQ_MD_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RQ_CC_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_CC_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_CC_LS>& a, const std::string& field);
void copy (RQ_CC_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const CF_XX_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_XX_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_XX_LS>& a, const std::string& field);
void copy (CF_XX_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const CF_NW_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_NW_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_NW_LS>& a, const std::string& field);
void copy (CF_NW_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const CF_MD_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_MD_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_MD_LS>& a, const std::string& field);
void copy (CF_MD_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const CF_CC_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_CC_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_CC_LS>& a, const std::string& field);
void copy (CF_CC_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const CF_EX_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_EX_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_EX_LS>& a, const std::string& field);
void copy (CF_EX_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RJ_XX_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_XX_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_XX_LS>& a, const std::string& field);
void copy (RJ_XX_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RJ_NW_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_NW_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_NW_LS>& a, const std::string& field);
void copy (RJ_NW_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RJ_MD_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_MD_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_MD_LS>& a, const std::string& field);
void copy (RJ_MD_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RJ_CC_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_CC_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_CC_LS>& a, const std::string& field);
void copy (RJ_CC_LS& a, const qpid::types::Variant& map);

    sub_position_ls  __internal_get_default(sub_position_ls *);
    
    sub_order_ls_confirmated  __internal_get_default(sub_order_ls_confirmated *);
    
    RQ_XX_LS  __internal_get_default(RQ_XX_LS *);
    
    RQ_NW_LS  __internal_get_default(RQ_NW_LS *);
    
    RQ_MD_LS  __internal_get_default(RQ_MD_LS *);
    
    RQ_CC_LS  __internal_get_default(RQ_CC_LS *);
    
    CF_XX_LS  __internal_get_default(CF_XX_LS *);
    
    CF_NW_LS  __internal_get_default(CF_NW_LS *);
    
    CF_MD_LS  __internal_get_default(CF_MD_LS *);
    
    CF_CC_LS  __internal_get_default(CF_CC_LS *);
    
    CF_EX_LS  __internal_get_default(CF_EX_LS *);
    
    RJ_XX_LS  __internal_get_default(RJ_XX_LS *);
    
    RJ_NW_LS  __internal_get_default(RJ_NW_LS *);
    
    RJ_MD_LS  __internal_get_default(RJ_MD_LS *);
    
    RJ_CC_LS  __internal_get_default(RJ_CC_LS *);
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RQ_XX_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RQ_NW_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RQ_MD_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RQ_CC_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_XX_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_NW_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_MD_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_CC_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_EX_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RJ_XX_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RJ_NW_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RJ_MD_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RJ_CC_LS)




#endif
