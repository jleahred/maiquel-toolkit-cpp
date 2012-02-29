
#ifndef  __msg_ps_prices__
#define  __msg_ps_prices__


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
#include "support/mtk_double.h"
#include "msg_prices.h"

namespace mtk { 
namespace prices { 
namespace msg { 




//-------------------------------
//      ps_req_product_info
//-------------------------------    
class ps_req_product_info        :  public  req_product_info
{
public:
    //  inner classes

    
    // constructor
    explicit ps_req_product_info (  const req_product_info&  parent,   const std::string&  _from );
    explicit ps_req_product_info ( const qpid::types::Variant::Map&  mv );
    virtual ~ps_req_product_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "ps_req_product_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "ps_req_product_info"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               from; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& product_code_market,const std::string& from);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      ps_pub_prod_info_mtk_ready
//-------------------------------    
class ps_pub_prod_info_mtk_ready     
{
public:
    //  inner classes

    
    // constructor
    explicit ps_pub_prod_info_mtk_ready (    const std::string&  _market );
    explicit ps_pub_prod_info_mtk_ready ( const qpid::types::Variant::Map&  mv );
    virtual ~ps_pub_prod_info_mtk_ready (){};
    virtual std::string get_message_type_as_string       (void) const  { return "ps_pub_prod_info_mtk_ready"; };
    static  std::string static_get_message_type_as_string(void)        { return "ps_pub_prod_info_mtk_ready"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               market; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& market);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      ps_req_init_prod_info
//-------------------------------    
class ps_req_init_prod_info     
{
public:
    //  inner classes

    
    // constructor
    explicit ps_req_init_prod_info (    const std::string&  _market,   const mtk::msg::sub_process_info&  _process_info );
    explicit ps_req_init_prod_info ( const qpid::types::Variant::Map&  mv );
    virtual ~ps_req_init_prod_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "ps_req_init_prod_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "ps_req_init_prod_info"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               market; 
    mtk::msg::sub_process_info                process_info; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& market);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      ps_conf_full_product_info_init
//-------------------------------    
class ps_conf_full_product_info_init     
{
public:
    //  inner classes

    
    // constructor
    explicit ps_conf_full_product_info_init (    const std::string&  _market,   const mtk::msg::sub_process_info&  _to_process_info );
    explicit ps_conf_full_product_info_init ( const qpid::types::Variant::Map&  mv );
    virtual ~ps_conf_full_product_info_init (){};
    virtual std::string get_message_type_as_string       (void) const  { return "ps_conf_full_product_info_init"; };
    static  std::string static_get_message_type_as_string(void)        { return "ps_conf_full_product_info_init"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               market; 
    mtk::msg::sub_process_info                to_process_info; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& market,const std::string& to_process_info_process_name,const std::string& to_process_info_process_uuid);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      ps_conf_full_product_info
//-------------------------------    
class ps_conf_full_product_info     
{
public:
    //  inner classes

    
    // constructor
    explicit ps_conf_full_product_info (    const sub_full_product_info&  _full_prod_info,   const mtk::msg::sub_process_info&  _to_process_info,   const int&  _seq_number );
    explicit ps_conf_full_product_info ( const qpid::types::Variant::Map&  mv );
    virtual ~ps_conf_full_product_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "ps_conf_full_product_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "ps_conf_full_product_info"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    sub_full_product_info                     full_prod_info; 
    mtk::msg::sub_process_info                to_process_info; 
    int                                       seq_number; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& full_prod_info_product_code_market,const std::string& to_process_info_process_name,const std::string& to_process_info_process_uuid);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      ps_pub_prod_info_mtk_ready__from_publisher
//-------------------------------    
class ps_pub_prod_info_mtk_ready__from_publisher        :  public  ps_pub_prod_info_mtk_ready
{
public:
    //  inner classes

    
    // constructor
    explicit ps_pub_prod_info_mtk_ready__from_publisher (  const ps_pub_prod_info_mtk_ready&  parent );
    explicit ps_pub_prod_info_mtk_ready__from_publisher ( const qpid::types::Variant::Map&  mv );
    virtual ~ps_pub_prod_info_mtk_ready__from_publisher (){};
    virtual std::string get_message_type_as_string       (void) const  { return "ps_pub_prod_info_mtk_ready__from_publisher"; };
    static  std::string static_get_message_type_as_string(void)        { return "ps_pub_prod_info_mtk_ready__from_publisher"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& market);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      ps_req_init_prod_info__to_publisher
//-------------------------------    
class ps_req_init_prod_info__to_publisher        :  public  ps_req_init_prod_info
{
public:
    //  inner classes

    
    // constructor
    explicit ps_req_init_prod_info__to_publisher (  const ps_req_init_prod_info&  parent );
    explicit ps_req_init_prod_info__to_publisher ( const qpid::types::Variant::Map&  mv );
    virtual ~ps_req_init_prod_info__to_publisher (){};
    virtual std::string get_message_type_as_string       (void) const  { return "ps_req_init_prod_info__to_publisher"; };
    static  std::string static_get_message_type_as_string(void)        { return "ps_req_init_prod_info__to_publisher"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& market);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      ps_conf_full_product_info_init__from_publisher
//-------------------------------    
class ps_conf_full_product_info_init__from_publisher        :  public  ps_conf_full_product_info_init
{
public:
    //  inner classes

    
    // constructor
    explicit ps_conf_full_product_info_init__from_publisher (  const ps_conf_full_product_info_init&  parent );
    explicit ps_conf_full_product_info_init__from_publisher ( const qpid::types::Variant::Map&  mv );
    virtual ~ps_conf_full_product_info_init__from_publisher (){};
    virtual std::string get_message_type_as_string       (void) const  { return "ps_conf_full_product_info_init__from_publisher"; };
    static  std::string static_get_message_type_as_string(void)        { return "ps_conf_full_product_info_init__from_publisher"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& market,const std::string& to_process_info_process_name,const std::string& to_process_info_process_uuid);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      ps_conf_full_product_info__from_publisher
//-------------------------------    
class ps_conf_full_product_info__from_publisher        :  public  ps_conf_full_product_info
{
public:
    //  inner classes

    
    // constructor
    explicit ps_conf_full_product_info__from_publisher (  const ps_conf_full_product_info&  parent );
    explicit ps_conf_full_product_info__from_publisher ( const qpid::types::Variant::Map&  mv );
    virtual ~ps_conf_full_product_info__from_publisher (){};
    virtual std::string get_message_type_as_string       (void) const  { return "ps_conf_full_product_info__from_publisher"; };
    static  std::string static_get_message_type_as_string(void)        { return "ps_conf_full_product_info__from_publisher"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& full_prod_info_product_code_market,const std::string& to_process_info_process_name,const std::string& to_process_info_process_uuid);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const ps_req_product_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const ps_req_product_info & c);
   void           operator >> (const YAML::Node& n,       ps_req_product_info & c);

bool operator== (const ps_req_product_info& a, const ps_req_product_info& b);
bool operator!= (const ps_req_product_info& a, const ps_req_product_info& b);

    std::ostream& operator<< (std::ostream& o, const ps_pub_prod_info_mtk_ready & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const ps_pub_prod_info_mtk_ready & c);
   void           operator >> (const YAML::Node& n,       ps_pub_prod_info_mtk_ready & c);

bool operator== (const ps_pub_prod_info_mtk_ready& a, const ps_pub_prod_info_mtk_ready& b);
bool operator!= (const ps_pub_prod_info_mtk_ready& a, const ps_pub_prod_info_mtk_ready& b);

    std::ostream& operator<< (std::ostream& o, const ps_req_init_prod_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const ps_req_init_prod_info & c);
   void           operator >> (const YAML::Node& n,       ps_req_init_prod_info & c);

bool operator== (const ps_req_init_prod_info& a, const ps_req_init_prod_info& b);
bool operator!= (const ps_req_init_prod_info& a, const ps_req_init_prod_info& b);

    std::ostream& operator<< (std::ostream& o, const ps_conf_full_product_info_init & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const ps_conf_full_product_info_init & c);
   void           operator >> (const YAML::Node& n,       ps_conf_full_product_info_init & c);

bool operator== (const ps_conf_full_product_info_init& a, const ps_conf_full_product_info_init& b);
bool operator!= (const ps_conf_full_product_info_init& a, const ps_conf_full_product_info_init& b);

    std::ostream& operator<< (std::ostream& o, const ps_conf_full_product_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const ps_conf_full_product_info & c);
   void           operator >> (const YAML::Node& n,       ps_conf_full_product_info & c);

bool operator== (const ps_conf_full_product_info& a, const ps_conf_full_product_info& b);
bool operator!= (const ps_conf_full_product_info& a, const ps_conf_full_product_info& b);

    std::ostream& operator<< (std::ostream& o, const ps_pub_prod_info_mtk_ready__from_publisher & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const ps_pub_prod_info_mtk_ready__from_publisher & c);
   void           operator >> (const YAML::Node& n,       ps_pub_prod_info_mtk_ready__from_publisher & c);

bool operator== (const ps_pub_prod_info_mtk_ready__from_publisher& a, const ps_pub_prod_info_mtk_ready__from_publisher& b);
bool operator!= (const ps_pub_prod_info_mtk_ready__from_publisher& a, const ps_pub_prod_info_mtk_ready__from_publisher& b);

    std::ostream& operator<< (std::ostream& o, const ps_req_init_prod_info__to_publisher & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const ps_req_init_prod_info__to_publisher & c);
   void           operator >> (const YAML::Node& n,       ps_req_init_prod_info__to_publisher & c);

bool operator== (const ps_req_init_prod_info__to_publisher& a, const ps_req_init_prod_info__to_publisher& b);
bool operator!= (const ps_req_init_prod_info__to_publisher& a, const ps_req_init_prod_info__to_publisher& b);

    std::ostream& operator<< (std::ostream& o, const ps_conf_full_product_info_init__from_publisher & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const ps_conf_full_product_info_init__from_publisher & c);
   void           operator >> (const YAML::Node& n,       ps_conf_full_product_info_init__from_publisher & c);

bool operator== (const ps_conf_full_product_info_init__from_publisher& a, const ps_conf_full_product_info_init__from_publisher& b);
bool operator!= (const ps_conf_full_product_info_init__from_publisher& a, const ps_conf_full_product_info_init__from_publisher& b);

    std::ostream& operator<< (std::ostream& o, const ps_conf_full_product_info__from_publisher & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const ps_conf_full_product_info__from_publisher & c);
   void           operator >> (const YAML::Node& n,       ps_conf_full_product_info__from_publisher & c);

bool operator== (const ps_conf_full_product_info__from_publisher& a, const ps_conf_full_product_info__from_publisher& b);
bool operator!= (const ps_conf_full_product_info__from_publisher& a, const ps_conf_full_product_info__from_publisher& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const ps_req_product_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const ps_req_product_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_req_product_info>& a, const std::string& field);
void copy (ps_req_product_info& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const ps_pub_prod_info_mtk_ready& a);
void __internal_add2map (qpid::types::Variant::Map& map, const ps_pub_prod_info_mtk_ready& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_pub_prod_info_mtk_ready>& a, const std::string& field);
void copy (ps_pub_prod_info_mtk_ready& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const ps_req_init_prod_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const ps_req_init_prod_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_req_init_prod_info>& a, const std::string& field);
void copy (ps_req_init_prod_info& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const ps_conf_full_product_info_init& a);
void __internal_add2map (qpid::types::Variant::Map& map, const ps_conf_full_product_info_init& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_conf_full_product_info_init>& a, const std::string& field);
void copy (ps_conf_full_product_info_init& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const ps_conf_full_product_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const ps_conf_full_product_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_conf_full_product_info>& a, const std::string& field);
void copy (ps_conf_full_product_info& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const ps_pub_prod_info_mtk_ready__from_publisher& a);
void __internal_add2map (qpid::types::Variant::Map& map, const ps_pub_prod_info_mtk_ready__from_publisher& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_pub_prod_info_mtk_ready__from_publisher>& a, const std::string& field);
void copy (ps_pub_prod_info_mtk_ready__from_publisher& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const ps_req_init_prod_info__to_publisher& a);
void __internal_add2map (qpid::types::Variant::Map& map, const ps_req_init_prod_info__to_publisher& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_req_init_prod_info__to_publisher>& a, const std::string& field);
void copy (ps_req_init_prod_info__to_publisher& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const ps_conf_full_product_info_init__from_publisher& a);
void __internal_add2map (qpid::types::Variant::Map& map, const ps_conf_full_product_info_init__from_publisher& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_conf_full_product_info_init__from_publisher>& a, const std::string& field);
void copy (ps_conf_full_product_info_init__from_publisher& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const ps_conf_full_product_info__from_publisher& a);
void __internal_add2map (qpid::types::Variant::Map& map, const ps_conf_full_product_info__from_publisher& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_conf_full_product_info__from_publisher>& a, const std::string& field);
void copy (ps_conf_full_product_info__from_publisher& a, const qpid::types::Variant& map);

    ps_req_product_info  __internal_get_default(ps_req_product_info *);
    
    ps_pub_prod_info_mtk_ready  __internal_get_default(ps_pub_prod_info_mtk_ready *);
    
    ps_req_init_prod_info  __internal_get_default(ps_req_init_prod_info *);
    
    ps_conf_full_product_info_init  __internal_get_default(ps_conf_full_product_info_init *);
    
    ps_conf_full_product_info  __internal_get_default(ps_conf_full_product_info *);
    
    ps_pub_prod_info_mtk_ready__from_publisher  __internal_get_default(ps_pub_prod_info_mtk_ready__from_publisher *);
    
    ps_req_init_prod_info__to_publisher  __internal_get_default(ps_req_init_prod_info__to_publisher *);
    
    ps_conf_full_product_info_init__from_publisher  __internal_get_default(ps_conf_full_product_info_init__from_publisher *);
    
    ps_conf_full_product_info__from_publisher  __internal_get_default(ps_conf_full_product_info__from_publisher *);
    

};   //namespace mtk {
};   //namespace prices {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::ps_req_product_info)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::ps_pub_prod_info_mtk_ready)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::ps_req_init_prod_info)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::ps_conf_full_product_info_init)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::ps_conf_full_product_info)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::ps_pub_prod_info_mtk_ready__from_publisher)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::ps_req_init_prod_info__to_publisher)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::ps_conf_full_product_info_init__from_publisher)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::ps_conf_full_product_info__from_publisher)




#endif
