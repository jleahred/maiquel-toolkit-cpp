
#ifndef  __msg_trd_oms_rq__
#define  __msg_trd_oms_rq__


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
#include "msg_trd_common.h"
#include "msg_trd_cli_ls.h"
#include "msg_trd_cli_mk.h"
#include "msg_trd_cli_sm.h"
#include "msg_trd_cli_sl.h"

namespace mtk { 
namespace trd { 
namespace msg { 




//-------------------------------
//      oms_RQ_NW_LS
//-------------------------------    
class oms_RQ_NW_LS        :  public  RQ_NW_LS
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_NW_LS (  const RQ_NW_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from );
    explicit oms_RQ_NW_LS ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_NW_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_NW_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_NW_LS"; };
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_MD_LS
//-------------------------------    
class oms_RQ_MD_LS        :  public  RQ_MD_LS
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_MD_LS (  const RQ_MD_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from );
    explicit oms_RQ_MD_LS ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_MD_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_MD_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_MD_LS"; };
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_CC_LS
//-------------------------------    
class oms_RQ_CC_LS        :  public  RQ_CC_LS
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_CC_LS (  const RQ_CC_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from );
    explicit oms_RQ_CC_LS ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_CC_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_CC_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_CC_LS"; };
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_NW_MK
//-------------------------------    
class oms_RQ_NW_MK        :  public  RQ_NW_MK
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_NW_MK (  const RQ_NW_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from );
    explicit oms_RQ_NW_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_NW_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_NW_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_NW_MK"; };
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_MD_MK
//-------------------------------    
class oms_RQ_MD_MK        :  public  RQ_MD_MK
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_MD_MK (  const RQ_MD_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from );
    explicit oms_RQ_MD_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_MD_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_MD_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_MD_MK"; };
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_CC_MK
//-------------------------------    
class oms_RQ_CC_MK        :  public  RQ_CC_MK
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_CC_MK (  const RQ_CC_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from );
    explicit oms_RQ_CC_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_CC_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_CC_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_CC_MK"; };
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_NW_SM
//-------------------------------    
class oms_RQ_NW_SM        :  public  RQ_NW_SM
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_NW_SM (  const RQ_NW_SM&  parent,   const std::string&  _reject_description,   const std::string&  _from );
    explicit oms_RQ_NW_SM ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_NW_SM (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_NW_SM"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_NW_SM"; };
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_MD_SM
//-------------------------------    
class oms_RQ_MD_SM        :  public  RQ_MD_SM
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_MD_SM (  const RQ_MD_SM&  parent,   const std::string&  _reject_description,   const std::string&  _from );
    explicit oms_RQ_MD_SM ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_MD_SM (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_MD_SM"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_MD_SM"; };
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_CC_SM
//-------------------------------    
class oms_RQ_CC_SM        :  public  RQ_CC_SM
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_CC_SM (  const RQ_CC_SM&  parent,   const std::string&  _reject_description,   const std::string&  _from );
    explicit oms_RQ_CC_SM ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_CC_SM (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_CC_SM"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_CC_SM"; };
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_NW_SL
//-------------------------------    
class oms_RQ_NW_SL        :  public  RQ_NW_SL
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_NW_SL (  const RQ_NW_SL&  parent,   const std::string&  _reject_description,   const std::string&  _from );
    explicit oms_RQ_NW_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_NW_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_NW_SL"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_NW_SL"; };
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_MD_SL
//-------------------------------    
class oms_RQ_MD_SL        :  public  RQ_MD_SL
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_MD_SL (  const RQ_MD_SL&  parent,   const std::string&  _reject_description,   const std::string&  _from );
    explicit oms_RQ_MD_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_MD_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_MD_SL"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_MD_SL"; };
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_CC_SL
//-------------------------------    
class oms_RQ_CC_SL        :  public  RQ_CC_SL
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_CC_SL (  const RQ_CC_SL&  parent,   const std::string&  _reject_description,   const std::string&  _from );
    explicit oms_RQ_CC_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_CC_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_CC_SL"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_CC_SL"; };
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_ORDERS_STATUS
//-------------------------------    
class oms_RQ_ORDERS_STATUS        :  public  RQ_ORDERS_STATUS
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_ORDERS_STATUS (  const RQ_ORDERS_STATUS&  parent,   const std::string&  _reject_description,   const std::string&  _from );
    explicit oms_RQ_ORDERS_STATUS ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_ORDERS_STATUS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_ORDERS_STATUS"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_ORDERS_STATUS"; };
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& market,const std::string& from);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_LS & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_NW_LS & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_NW_LS & c);

bool operator== (const oms_RQ_NW_LS& a, const oms_RQ_NW_LS& b);
bool operator!= (const oms_RQ_NW_LS& a, const oms_RQ_NW_LS& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_LS & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_MD_LS & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_MD_LS & c);

bool operator== (const oms_RQ_MD_LS& a, const oms_RQ_MD_LS& b);
bool operator!= (const oms_RQ_MD_LS& a, const oms_RQ_MD_LS& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_LS & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_CC_LS & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_CC_LS & c);

bool operator== (const oms_RQ_CC_LS& a, const oms_RQ_CC_LS& b);
bool operator!= (const oms_RQ_CC_LS& a, const oms_RQ_CC_LS& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_NW_MK & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_NW_MK & c);

bool operator== (const oms_RQ_NW_MK& a, const oms_RQ_NW_MK& b);
bool operator!= (const oms_RQ_NW_MK& a, const oms_RQ_NW_MK& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_MD_MK & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_MD_MK & c);

bool operator== (const oms_RQ_MD_MK& a, const oms_RQ_MD_MK& b);
bool operator!= (const oms_RQ_MD_MK& a, const oms_RQ_MD_MK& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_CC_MK & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_CC_MK & c);

bool operator== (const oms_RQ_CC_MK& a, const oms_RQ_CC_MK& b);
bool operator!= (const oms_RQ_CC_MK& a, const oms_RQ_CC_MK& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_SM & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_NW_SM & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_NW_SM & c);

bool operator== (const oms_RQ_NW_SM& a, const oms_RQ_NW_SM& b);
bool operator!= (const oms_RQ_NW_SM& a, const oms_RQ_NW_SM& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_SM & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_MD_SM & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_MD_SM & c);

bool operator== (const oms_RQ_MD_SM& a, const oms_RQ_MD_SM& b);
bool operator!= (const oms_RQ_MD_SM& a, const oms_RQ_MD_SM& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_SM & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_CC_SM & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_CC_SM & c);

bool operator== (const oms_RQ_CC_SM& a, const oms_RQ_CC_SM& b);
bool operator!= (const oms_RQ_CC_SM& a, const oms_RQ_CC_SM& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_NW_SL & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_NW_SL & c);

bool operator== (const oms_RQ_NW_SL& a, const oms_RQ_NW_SL& b);
bool operator!= (const oms_RQ_NW_SL& a, const oms_RQ_NW_SL& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_MD_SL & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_MD_SL & c);

bool operator== (const oms_RQ_MD_SL& a, const oms_RQ_MD_SL& b);
bool operator!= (const oms_RQ_MD_SL& a, const oms_RQ_MD_SL& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_CC_SL & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_CC_SL & c);

bool operator== (const oms_RQ_CC_SL& a, const oms_RQ_CC_SL& b);
bool operator!= (const oms_RQ_CC_SL& a, const oms_RQ_CC_SL& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_ORDERS_STATUS & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_ORDERS_STATUS & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_ORDERS_STATUS & c);

bool operator== (const oms_RQ_ORDERS_STATUS& a, const oms_RQ_ORDERS_STATUS& b);
bool operator!= (const oms_RQ_ORDERS_STATUS& a, const oms_RQ_ORDERS_STATUS& b);

void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_LS>& a, const std::string& field);
void copy (oms_RQ_NW_LS& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_LS>& a, const std::string& field);
void copy (oms_RQ_MD_LS& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_LS>& a, const std::string& field);
void copy (oms_RQ_CC_LS& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_MK>& a, const std::string& field);
void copy (oms_RQ_NW_MK& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_MK>& a, const std::string& field);
void copy (oms_RQ_MD_MK& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_MK>& a, const std::string& field);
void copy (oms_RQ_CC_MK& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_SM& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_SM>& a, const std::string& field);
void copy (oms_RQ_NW_SM& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_SM& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_SM>& a, const std::string& field);
void copy (oms_RQ_MD_SM& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_SM& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_SM>& a, const std::string& field);
void copy (oms_RQ_CC_SM& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_SL>& a, const std::string& field);
void copy (oms_RQ_NW_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_SL>& a, const std::string& field);
void copy (oms_RQ_MD_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_SL>& a, const std::string& field);
void copy (oms_RQ_CC_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_ORDERS_STATUS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_ORDERS_STATUS>& a, const std::string& field);
void copy (oms_RQ_ORDERS_STATUS& a, const qpid::types::Variant& map);

    oms_RQ_NW_LS  __internal_get_default(oms_RQ_NW_LS *);
    
    oms_RQ_MD_LS  __internal_get_default(oms_RQ_MD_LS *);
    
    oms_RQ_CC_LS  __internal_get_default(oms_RQ_CC_LS *);
    
    oms_RQ_NW_MK  __internal_get_default(oms_RQ_NW_MK *);
    
    oms_RQ_MD_MK  __internal_get_default(oms_RQ_MD_MK *);
    
    oms_RQ_CC_MK  __internal_get_default(oms_RQ_CC_MK *);
    
    oms_RQ_NW_SM  __internal_get_default(oms_RQ_NW_SM *);
    
    oms_RQ_MD_SM  __internal_get_default(oms_RQ_MD_SM *);
    
    oms_RQ_CC_SM  __internal_get_default(oms_RQ_CC_SM *);
    
    oms_RQ_NW_SL  __internal_get_default(oms_RQ_NW_SL *);
    
    oms_RQ_MD_SL  __internal_get_default(oms_RQ_MD_SL *);
    
    oms_RQ_CC_SL  __internal_get_default(oms_RQ_CC_SL *);
    
    oms_RQ_ORDERS_STATUS  __internal_get_default(oms_RQ_ORDERS_STATUS *);
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_NW_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_MD_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_CC_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_NW_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_MD_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_CC_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_NW_SM)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_MD_SM)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_CC_SM)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_NW_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_MD_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_CC_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_ORDERS_STATUS)




#endif
