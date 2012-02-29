
#ifndef  __msg_trd_cli_mk__
#define  __msg_trd_cli_mk__


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
#include "components/acs/msg_acs.h"

namespace mtk { 
namespace trd { 
namespace msg { 




//-------------------------------
//      sub_position_mk
//-------------------------------    
class sub_position_mk     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_position_mk (    const mtk::FixedNumber&  _quantity,   const std::string&  _cli_ref );
    explicit sub_position_mk ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_position_mk (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_position_mk"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_position_mk"; };

    

    
    
    
    

    // fields
    mtk::FixedNumber                          quantity; 
    std::string                               cli_ref; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      RQ_XX_MK
//-------------------------------    
class RQ_XX_MK        :  public  RQ_XX
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_XX_MK (  const RQ_XX&  parent,   const sub_position_mk&  _request_pos );
    explicit RQ_XX_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~RQ_XX_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_XX_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "RQ_XX_MK"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    
    

    // fields
    sub_position_mk                           request_pos; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      RQ_NW_MK
//-------------------------------    
class RQ_NW_MK        :  public  RQ_XX_MK
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_NW_MK (  const RQ_XX_MK&  parent );
    explicit RQ_NW_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~RQ_NW_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_NW_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "RQ_NW_MK"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name,const std::string& invariant_product_code_product);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      RQ_MD_MK
//-------------------------------    
class RQ_MD_MK        :  public  RQ_XX_MK
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_MD_MK (  const RQ_XX_MK&  parent );
    explicit RQ_MD_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~RQ_MD_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_MD_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "RQ_MD_MK"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name,const std::string& invariant_product_code_product);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      RQ_CC_MK
//-------------------------------    
class RQ_CC_MK        :  public  RQ_XX_MK
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_CC_MK (  const RQ_XX_MK&  parent );
    explicit RQ_CC_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~RQ_CC_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_CC_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "RQ_CC_MK"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name,const std::string& invariant_product_code_product);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      CF_XX_MK
//-------------------------------    
class CF_XX_MK        :  public  CF_XX
{
public:
    //  inner classes

    
    // constructor
    explicit CF_XX_MK (  const CF_XX&  parent,   const sub_position_mk&  _market_pos );
    explicit CF_XX_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_XX_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_XX_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_XX_MK"; };

    

    
    
    
    

    // fields
    sub_position_mk                           market_pos; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      CF_NW_MK
//-------------------------------    
class CF_NW_MK        :  public  CF_XX_MK
{
public:
    //  inner classes

    
    // constructor
    explicit CF_NW_MK (  const CF_XX_MK&  parent );
    explicit CF_NW_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_NW_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_NW_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_NW_MK"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



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
//      CF_MD_MK
//-------------------------------    
class CF_MD_MK        :  public  CF_XX_MK
{
public:
    //  inner classes

    
    // constructor
    explicit CF_MD_MK (  const CF_XX_MK&  parent );
    explicit CF_MD_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_MD_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_MD_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_MD_MK"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



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
//      CF_CC_MK
//-------------------------------    
class CF_CC_MK        :  public  CF_XX_MK
{
public:
    //  inner classes

    
    // constructor
    explicit CF_CC_MK (  const CF_XX_MK&  parent );
    explicit CF_CC_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_CC_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_CC_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_CC_MK"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



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
//      CF_EX_MK
//-------------------------------    
class CF_EX_MK        :  public  CF_XX_MK
{
public:
    //  inner classes

    
    // constructor
    explicit CF_EX_MK (  const CF_XX_MK&  parent,   const sub_exec_conf&  _executed_pos );
    explicit CF_EX_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_EX_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_EX_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_EX_MK"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

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
//      RJ_XX_MK
//-------------------------------    
class RJ_XX_MK        :  public  CF_XX_MK
{
public:
    //  inner classes

    
    // constructor
    explicit RJ_XX_MK (  const CF_XX_MK&  parent,   const sub_position_mk&  _request_pos );
    explicit RJ_XX_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~RJ_XX_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RJ_XX_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "RJ_XX_MK"; };

    

    
    
    
    

    // fields
    sub_position_mk                           request_pos; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      RJ_NW_MK
//-------------------------------    
class RJ_NW_MK        :  public  RJ_XX_MK
{
public:
    //  inner classes

    
    // constructor
    explicit RJ_NW_MK (  const RJ_XX_MK&  parent );
    explicit RJ_NW_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~RJ_NW_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RJ_NW_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "RJ_NW_MK"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



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
//      RJ_MD_MK
//-------------------------------    
class RJ_MD_MK        :  public  RJ_XX_MK
{
public:
    //  inner classes

    
    // constructor
    explicit RJ_MD_MK (  const RJ_XX_MK&  parent );
    explicit RJ_MD_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~RJ_MD_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RJ_MD_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "RJ_MD_MK"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



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
//      RJ_CC_MK
//-------------------------------    
class RJ_CC_MK        :  public  RJ_XX_MK
{
public:
    //  inner classes

    
    // constructor
    explicit RJ_CC_MK (  const RJ_XX_MK&  parent );
    explicit RJ_CC_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~RJ_CC_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RJ_CC_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "RJ_CC_MK"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



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
//      CF_ST_MK
//-------------------------------    
class CF_ST_MK        :  public  CF_XX_MK
{
public:
    //  inner classes

    
    // constructor
    explicit CF_ST_MK (  const CF_XX_MK&  parent,   const mtk::msg::sub_gen_response_location&  _gen_response_location );
    explicit CF_ST_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_ST_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_ST_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "CF_ST_MK"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

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



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_position_mk & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_position_mk & c);
   void           operator >> (const YAML::Node& n,       sub_position_mk & c);

bool operator== (const sub_position_mk& a, const sub_position_mk& b);
bool operator!= (const sub_position_mk& a, const sub_position_mk& b);

    std::ostream& operator<< (std::ostream& o, const RQ_XX_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_XX_MK & c);
   void           operator >> (const YAML::Node& n,       RQ_XX_MK & c);

bool operator== (const RQ_XX_MK& a, const RQ_XX_MK& b);
bool operator!= (const RQ_XX_MK& a, const RQ_XX_MK& b);

    std::ostream& operator<< (std::ostream& o, const RQ_NW_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_NW_MK & c);
   void           operator >> (const YAML::Node& n,       RQ_NW_MK & c);

bool operator== (const RQ_NW_MK& a, const RQ_NW_MK& b);
bool operator!= (const RQ_NW_MK& a, const RQ_NW_MK& b);

    std::ostream& operator<< (std::ostream& o, const RQ_MD_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_MD_MK & c);
   void           operator >> (const YAML::Node& n,       RQ_MD_MK & c);

bool operator== (const RQ_MD_MK& a, const RQ_MD_MK& b);
bool operator!= (const RQ_MD_MK& a, const RQ_MD_MK& b);

    std::ostream& operator<< (std::ostream& o, const RQ_CC_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_CC_MK & c);
   void           operator >> (const YAML::Node& n,       RQ_CC_MK & c);

bool operator== (const RQ_CC_MK& a, const RQ_CC_MK& b);
bool operator!= (const RQ_CC_MK& a, const RQ_CC_MK& b);

    std::ostream& operator<< (std::ostream& o, const CF_XX_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_XX_MK & c);
   void           operator >> (const YAML::Node& n,       CF_XX_MK & c);

bool operator== (const CF_XX_MK& a, const CF_XX_MK& b);
bool operator!= (const CF_XX_MK& a, const CF_XX_MK& b);

    std::ostream& operator<< (std::ostream& o, const CF_NW_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_NW_MK & c);
   void           operator >> (const YAML::Node& n,       CF_NW_MK & c);

bool operator== (const CF_NW_MK& a, const CF_NW_MK& b);
bool operator!= (const CF_NW_MK& a, const CF_NW_MK& b);

    std::ostream& operator<< (std::ostream& o, const CF_MD_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_MD_MK & c);
   void           operator >> (const YAML::Node& n,       CF_MD_MK & c);

bool operator== (const CF_MD_MK& a, const CF_MD_MK& b);
bool operator!= (const CF_MD_MK& a, const CF_MD_MK& b);

    std::ostream& operator<< (std::ostream& o, const CF_CC_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_CC_MK & c);
   void           operator >> (const YAML::Node& n,       CF_CC_MK & c);

bool operator== (const CF_CC_MK& a, const CF_CC_MK& b);
bool operator!= (const CF_CC_MK& a, const CF_CC_MK& b);

    std::ostream& operator<< (std::ostream& o, const CF_EX_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_EX_MK & c);
   void           operator >> (const YAML::Node& n,       CF_EX_MK & c);

bool operator== (const CF_EX_MK& a, const CF_EX_MK& b);
bool operator!= (const CF_EX_MK& a, const CF_EX_MK& b);

    std::ostream& operator<< (std::ostream& o, const RJ_XX_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RJ_XX_MK & c);
   void           operator >> (const YAML::Node& n,       RJ_XX_MK & c);

bool operator== (const RJ_XX_MK& a, const RJ_XX_MK& b);
bool operator!= (const RJ_XX_MK& a, const RJ_XX_MK& b);

    std::ostream& operator<< (std::ostream& o, const RJ_NW_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RJ_NW_MK & c);
   void           operator >> (const YAML::Node& n,       RJ_NW_MK & c);

bool operator== (const RJ_NW_MK& a, const RJ_NW_MK& b);
bool operator!= (const RJ_NW_MK& a, const RJ_NW_MK& b);

    std::ostream& operator<< (std::ostream& o, const RJ_MD_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RJ_MD_MK & c);
   void           operator >> (const YAML::Node& n,       RJ_MD_MK & c);

bool operator== (const RJ_MD_MK& a, const RJ_MD_MK& b);
bool operator!= (const RJ_MD_MK& a, const RJ_MD_MK& b);

    std::ostream& operator<< (std::ostream& o, const RJ_CC_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RJ_CC_MK & c);
   void           operator >> (const YAML::Node& n,       RJ_CC_MK & c);

bool operator== (const RJ_CC_MK& a, const RJ_CC_MK& b);
bool operator!= (const RJ_CC_MK& a, const RJ_CC_MK& b);

    std::ostream& operator<< (std::ostream& o, const CF_ST_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_ST_MK & c);
   void           operator >> (const YAML::Node& n,       CF_ST_MK & c);

bool operator== (const CF_ST_MK& a, const CF_ST_MK& b);
bool operator!= (const CF_ST_MK& a, const CF_ST_MK& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_position_mk& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_position_mk& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_position_mk>& a, const std::string& field);
void copy (sub_position_mk& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RQ_XX_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_XX_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_XX_MK>& a, const std::string& field);
void copy (RQ_XX_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RQ_NW_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_NW_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_NW_MK>& a, const std::string& field);
void copy (RQ_NW_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RQ_MD_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_MD_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_MD_MK>& a, const std::string& field);
void copy (RQ_MD_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RQ_CC_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_CC_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_CC_MK>& a, const std::string& field);
void copy (RQ_CC_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const CF_XX_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_XX_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_XX_MK>& a, const std::string& field);
void copy (CF_XX_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const CF_NW_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_NW_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_NW_MK>& a, const std::string& field);
void copy (CF_NW_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const CF_MD_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_MD_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_MD_MK>& a, const std::string& field);
void copy (CF_MD_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const CF_CC_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_CC_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_CC_MK>& a, const std::string& field);
void copy (CF_CC_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const CF_EX_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_EX_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_EX_MK>& a, const std::string& field);
void copy (CF_EX_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RJ_XX_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_XX_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_XX_MK>& a, const std::string& field);
void copy (RJ_XX_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RJ_NW_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_NW_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_NW_MK>& a, const std::string& field);
void copy (RJ_NW_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RJ_MD_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_MD_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_MD_MK>& a, const std::string& field);
void copy (RJ_MD_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RJ_CC_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_CC_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_CC_MK>& a, const std::string& field);
void copy (RJ_CC_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const CF_ST_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_ST_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_ST_MK>& a, const std::string& field);
void copy (CF_ST_MK& a, const qpid::types::Variant& map);

    sub_position_mk  __internal_get_default(sub_position_mk *);
    
    RQ_XX_MK  __internal_get_default(RQ_XX_MK *);
    
    RQ_NW_MK  __internal_get_default(RQ_NW_MK *);
    
    RQ_MD_MK  __internal_get_default(RQ_MD_MK *);
    
    RQ_CC_MK  __internal_get_default(RQ_CC_MK *);
    
    CF_XX_MK  __internal_get_default(CF_XX_MK *);
    
    CF_NW_MK  __internal_get_default(CF_NW_MK *);
    
    CF_MD_MK  __internal_get_default(CF_MD_MK *);
    
    CF_CC_MK  __internal_get_default(CF_CC_MK *);
    
    CF_EX_MK  __internal_get_default(CF_EX_MK *);
    
    RJ_XX_MK  __internal_get_default(RJ_XX_MK *);
    
    RJ_NW_MK  __internal_get_default(RJ_NW_MK *);
    
    RJ_MD_MK  __internal_get_default(RJ_MD_MK *);
    
    RJ_CC_MK  __internal_get_default(RJ_CC_MK *);
    
    CF_ST_MK  __internal_get_default(CF_ST_MK *);
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RQ_NW_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RQ_MD_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RQ_CC_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_NW_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_MD_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_CC_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_EX_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RJ_NW_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RJ_MD_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RJ_CC_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_ST_MK)




#endif
