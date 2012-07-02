
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
    explicit oms_RQ_NW_LS (  const RQ_NW_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
    explicit oms_RQ_NW_LS ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_NW_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_NW_LS"; }
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_NW_LS"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 
    std::string                               oms_additional_info; 



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



        //  qpid_variant wrapper for dynamic
        class oms_RQ_NW_LS__qpid_map
        {
        public:
            explicit  oms_RQ_NW_LS__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  oms_RQ_NW_LS__qpid_map ( const oms_RQ_NW_LS&  c ) : m_static(c) {}
            explicit  oms_RQ_NW_LS__qpid_map (  const RQ_NW_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
            ~oms_RQ_NW_LS__qpid_map() {};
            

            oms_RQ_NW_LS                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  oms_RQ_NW_LS::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  oms_RQ_NW_LS::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  oms_RQ_NW_LS::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  oms_RQ_NW_LS::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      oms_RQ_MD_LS
//-------------------------------    
class oms_RQ_MD_LS        :  public  RQ_MD_LS
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_MD_LS (  const RQ_MD_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
    explicit oms_RQ_MD_LS ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_MD_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_MD_LS"; }
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_MD_LS"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 
    std::string                               oms_additional_info; 



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



        //  qpid_variant wrapper for dynamic
        class oms_RQ_MD_LS__qpid_map
        {
        public:
            explicit  oms_RQ_MD_LS__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  oms_RQ_MD_LS__qpid_map ( const oms_RQ_MD_LS&  c ) : m_static(c) {}
            explicit  oms_RQ_MD_LS__qpid_map (  const RQ_MD_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
            ~oms_RQ_MD_LS__qpid_map() {};
            

            oms_RQ_MD_LS                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  oms_RQ_MD_LS::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  oms_RQ_MD_LS::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  oms_RQ_MD_LS::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  oms_RQ_MD_LS::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      oms_RQ_CC_LS
//-------------------------------    
class oms_RQ_CC_LS        :  public  RQ_CC_LS
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_CC_LS (  const RQ_CC_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
    explicit oms_RQ_CC_LS ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_CC_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_CC_LS"; }
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_CC_LS"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 
    std::string                               oms_additional_info; 



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



        //  qpid_variant wrapper for dynamic
        class oms_RQ_CC_LS__qpid_map
        {
        public:
            explicit  oms_RQ_CC_LS__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  oms_RQ_CC_LS__qpid_map ( const oms_RQ_CC_LS&  c ) : m_static(c) {}
            explicit  oms_RQ_CC_LS__qpid_map (  const RQ_CC_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
            ~oms_RQ_CC_LS__qpid_map() {};
            

            oms_RQ_CC_LS                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  oms_RQ_CC_LS::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  oms_RQ_CC_LS::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  oms_RQ_CC_LS::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  oms_RQ_CC_LS::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      oms_RQ_NW_MK
//-------------------------------    
class oms_RQ_NW_MK        :  public  RQ_NW_MK
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_NW_MK (  const RQ_NW_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
    explicit oms_RQ_NW_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_NW_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_NW_MK"; }
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_NW_MK"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 
    std::string                               oms_additional_info; 



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



        //  qpid_variant wrapper for dynamic
        class oms_RQ_NW_MK__qpid_map
        {
        public:
            explicit  oms_RQ_NW_MK__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  oms_RQ_NW_MK__qpid_map ( const oms_RQ_NW_MK&  c ) : m_static(c) {}
            explicit  oms_RQ_NW_MK__qpid_map (  const RQ_NW_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
            ~oms_RQ_NW_MK__qpid_map() {};
            

            oms_RQ_NW_MK                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  oms_RQ_NW_MK::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  oms_RQ_NW_MK::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  oms_RQ_NW_MK::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  oms_RQ_NW_MK::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      oms_RQ_MD_MK
//-------------------------------    
class oms_RQ_MD_MK        :  public  RQ_MD_MK
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_MD_MK (  const RQ_MD_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
    explicit oms_RQ_MD_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_MD_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_MD_MK"; }
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_MD_MK"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 
    std::string                               oms_additional_info; 



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



        //  qpid_variant wrapper for dynamic
        class oms_RQ_MD_MK__qpid_map
        {
        public:
            explicit  oms_RQ_MD_MK__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  oms_RQ_MD_MK__qpid_map ( const oms_RQ_MD_MK&  c ) : m_static(c) {}
            explicit  oms_RQ_MD_MK__qpid_map (  const RQ_MD_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
            ~oms_RQ_MD_MK__qpid_map() {};
            

            oms_RQ_MD_MK                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  oms_RQ_MD_MK::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  oms_RQ_MD_MK::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  oms_RQ_MD_MK::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  oms_RQ_MD_MK::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      oms_RQ_CC_MK
//-------------------------------    
class oms_RQ_CC_MK        :  public  RQ_CC_MK
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_CC_MK (  const RQ_CC_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
    explicit oms_RQ_CC_MK ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_CC_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_CC_MK"; }
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_CC_MK"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 
    std::string                               oms_additional_info; 



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



        //  qpid_variant wrapper for dynamic
        class oms_RQ_CC_MK__qpid_map
        {
        public:
            explicit  oms_RQ_CC_MK__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  oms_RQ_CC_MK__qpid_map ( const oms_RQ_CC_MK&  c ) : m_static(c) {}
            explicit  oms_RQ_CC_MK__qpid_map (  const RQ_CC_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
            ~oms_RQ_CC_MK__qpid_map() {};
            

            oms_RQ_CC_MK                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  oms_RQ_CC_MK::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  oms_RQ_CC_MK::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  oms_RQ_CC_MK::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  oms_RQ_CC_MK::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      oms_RQ_NW_SM
//-------------------------------    
class oms_RQ_NW_SM        :  public  RQ_NW_SM
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_NW_SM (  const RQ_NW_SM&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
    explicit oms_RQ_NW_SM ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_NW_SM (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_NW_SM"; }
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_NW_SM"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 
    std::string                               oms_additional_info; 



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



        //  qpid_variant wrapper for dynamic
        class oms_RQ_NW_SM__qpid_map
        {
        public:
            explicit  oms_RQ_NW_SM__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  oms_RQ_NW_SM__qpid_map ( const oms_RQ_NW_SM&  c ) : m_static(c) {}
            explicit  oms_RQ_NW_SM__qpid_map (  const RQ_NW_SM&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
            ~oms_RQ_NW_SM__qpid_map() {};
            

            oms_RQ_NW_SM                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  oms_RQ_NW_SM::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  oms_RQ_NW_SM::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  oms_RQ_NW_SM::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  oms_RQ_NW_SM::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      oms_RQ_MD_SM
//-------------------------------    
class oms_RQ_MD_SM        :  public  RQ_MD_SM
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_MD_SM (  const RQ_MD_SM&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
    explicit oms_RQ_MD_SM ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_MD_SM (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_MD_SM"; }
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_MD_SM"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 
    std::string                               oms_additional_info; 



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



        //  qpid_variant wrapper for dynamic
        class oms_RQ_MD_SM__qpid_map
        {
        public:
            explicit  oms_RQ_MD_SM__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  oms_RQ_MD_SM__qpid_map ( const oms_RQ_MD_SM&  c ) : m_static(c) {}
            explicit  oms_RQ_MD_SM__qpid_map (  const RQ_MD_SM&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
            ~oms_RQ_MD_SM__qpid_map() {};
            

            oms_RQ_MD_SM                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  oms_RQ_MD_SM::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  oms_RQ_MD_SM::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  oms_RQ_MD_SM::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  oms_RQ_MD_SM::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      oms_RQ_CC_SM
//-------------------------------    
class oms_RQ_CC_SM        :  public  RQ_CC_SM
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_CC_SM (  const RQ_CC_SM&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
    explicit oms_RQ_CC_SM ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_CC_SM (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_CC_SM"; }
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_CC_SM"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 
    std::string                               oms_additional_info; 



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



        //  qpid_variant wrapper for dynamic
        class oms_RQ_CC_SM__qpid_map
        {
        public:
            explicit  oms_RQ_CC_SM__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  oms_RQ_CC_SM__qpid_map ( const oms_RQ_CC_SM&  c ) : m_static(c) {}
            explicit  oms_RQ_CC_SM__qpid_map (  const RQ_CC_SM&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
            ~oms_RQ_CC_SM__qpid_map() {};
            

            oms_RQ_CC_SM                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  oms_RQ_CC_SM::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  oms_RQ_CC_SM::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  oms_RQ_CC_SM::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  oms_RQ_CC_SM::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      oms_RQ_NW_SL
//-------------------------------    
class oms_RQ_NW_SL        :  public  RQ_NW_SL
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_NW_SL (  const RQ_NW_SL&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
    explicit oms_RQ_NW_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_NW_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_NW_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_NW_SL"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 
    std::string                               oms_additional_info; 



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



        //  qpid_variant wrapper for dynamic
        class oms_RQ_NW_SL__qpid_map
        {
        public:
            explicit  oms_RQ_NW_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  oms_RQ_NW_SL__qpid_map ( const oms_RQ_NW_SL&  c ) : m_static(c) {}
            explicit  oms_RQ_NW_SL__qpid_map (  const RQ_NW_SL&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
            ~oms_RQ_NW_SL__qpid_map() {};
            

            oms_RQ_NW_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  oms_RQ_NW_SL::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  oms_RQ_NW_SL::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  oms_RQ_NW_SL::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  oms_RQ_NW_SL::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      oms_RQ_MD_SL
//-------------------------------    
class oms_RQ_MD_SL        :  public  RQ_MD_SL
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_MD_SL (  const RQ_MD_SL&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
    explicit oms_RQ_MD_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_MD_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_MD_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_MD_SL"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 
    std::string                               oms_additional_info; 



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



        //  qpid_variant wrapper for dynamic
        class oms_RQ_MD_SL__qpid_map
        {
        public:
            explicit  oms_RQ_MD_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  oms_RQ_MD_SL__qpid_map ( const oms_RQ_MD_SL&  c ) : m_static(c) {}
            explicit  oms_RQ_MD_SL__qpid_map (  const RQ_MD_SL&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
            ~oms_RQ_MD_SL__qpid_map() {};
            

            oms_RQ_MD_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  oms_RQ_MD_SL::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  oms_RQ_MD_SL::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  oms_RQ_MD_SL::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  oms_RQ_MD_SL::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      oms_RQ_CC_SL
//-------------------------------    
class oms_RQ_CC_SL        :  public  RQ_CC_SL
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_CC_SL (  const RQ_CC_SL&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
    explicit oms_RQ_CC_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_CC_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_CC_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_CC_SL"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               reject_description; 
    std::string                               from; 
    std::string                               oms_additional_info; 



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



        //  qpid_variant wrapper for dynamic
        class oms_RQ_CC_SL__qpid_map
        {
        public:
            explicit  oms_RQ_CC_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  oms_RQ_CC_SL__qpid_map ( const oms_RQ_CC_SL&  c ) : m_static(c) {}
            explicit  oms_RQ_CC_SL__qpid_map (  const RQ_CC_SL&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info );
            ~oms_RQ_CC_SL__qpid_map() {};
            

            oms_RQ_CC_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  oms_RQ_CC_SL::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  oms_RQ_CC_SL::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  oms_RQ_CC_SL::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  oms_RQ_CC_SL::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
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
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_ORDERS_STATUS"; }
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_ORDERS_STATUS"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
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



        //  qpid_variant wrapper for dynamic
        class oms_RQ_ORDERS_STATUS__qpid_map
        {
        public:
            explicit  oms_RQ_ORDERS_STATUS__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  oms_RQ_ORDERS_STATUS__qpid_map ( const oms_RQ_ORDERS_STATUS&  c ) : m_static(c) {}
            explicit  oms_RQ_ORDERS_STATUS__qpid_map (  const RQ_ORDERS_STATUS&  parent,   const std::string&  _reject_description,   const std::string&  _from );
            ~oms_RQ_ORDERS_STATUS__qpid_map() {};
            

            oms_RQ_ORDERS_STATUS                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  oms_RQ_ORDERS_STATUS::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  oms_RQ_ORDERS_STATUS::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  oms_RQ_ORDERS_STATUS::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  oms_RQ_ORDERS_STATUS::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      oms_RQ_EXECS_HISTORIC
//-------------------------------    
class oms_RQ_EXECS_HISTORIC        :  public  RQ_EXECS_HISTORIC
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_EXECS_HISTORIC (  const RQ_EXECS_HISTORIC&  parent,   const std::string&  _market,   const mtk::DateTime&  _date,   const mtk::list<mtk::trd::msg::sub_account_info >&  _list_accounts );
    explicit oms_RQ_EXECS_HISTORIC ( const qpid::types::Variant::Map&  mv );
    virtual ~oms_RQ_EXECS_HISTORIC (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_EXECS_HISTORIC"; }
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_EXECS_HISTORIC"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               market; 
    mtk::DateTime                             date; 
    mtk::list<mtk::trd::msg::sub_account_info >  list_accounts; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject ();
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class oms_RQ_EXECS_HISTORIC__qpid_map
        {
        public:
            explicit  oms_RQ_EXECS_HISTORIC__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  oms_RQ_EXECS_HISTORIC__qpid_map ( const oms_RQ_EXECS_HISTORIC&  c ) : m_static(c) {}
            explicit  oms_RQ_EXECS_HISTORIC__qpid_map (  const RQ_EXECS_HISTORIC&  parent,   const std::string&  _market,   const mtk::DateTime&  _date,   const mtk::list<mtk::trd::msg::sub_account_info >&  _list_accounts );
            ~oms_RQ_EXECS_HISTORIC__qpid_map() {};
            

            oms_RQ_EXECS_HISTORIC                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  oms_RQ_EXECS_HISTORIC::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  oms_RQ_EXECS_HISTORIC::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  oms_RQ_EXECS_HISTORIC::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  oms_RQ_EXECS_HISTORIC::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
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

    std::ostream& operator<< (std::ostream& o, const oms_RQ_EXECS_HISTORIC & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_EXECS_HISTORIC & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_EXECS_HISTORIC & c);

bool operator== (const oms_RQ_EXECS_HISTORIC& a, const oms_RQ_EXECS_HISTORIC& b);
bool operator!= (const oms_RQ_EXECS_HISTORIC& a, const oms_RQ_EXECS_HISTORIC& b);

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
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_EXECS_HISTORIC& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_EXECS_HISTORIC>& a, const std::string& field);
void copy (oms_RQ_EXECS_HISTORIC& a, const qpid::types::Variant& map);

    
    
    
//  fordward declarations  dynamic--------------------------------------------------------


inline std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_LS__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_NW_LS__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       oms_RQ_NW_LS__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const oms_RQ_NW_LS__qpid_map& a, const oms_RQ_NW_LS__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const oms_RQ_NW_LS__qpid_map& a, const oms_RQ_NW_LS__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_LS__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_LS__qpid_map>& a, const std::string& field);
void copy (oms_RQ_NW_LS__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_LS__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_MD_LS__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       oms_RQ_MD_LS__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const oms_RQ_MD_LS__qpid_map& a, const oms_RQ_MD_LS__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const oms_RQ_MD_LS__qpid_map& a, const oms_RQ_MD_LS__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_LS__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_LS__qpid_map>& a, const std::string& field);
void copy (oms_RQ_MD_LS__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_LS__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_CC_LS__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       oms_RQ_CC_LS__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const oms_RQ_CC_LS__qpid_map& a, const oms_RQ_CC_LS__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const oms_RQ_CC_LS__qpid_map& a, const oms_RQ_CC_LS__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_LS__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_LS__qpid_map>& a, const std::string& field);
void copy (oms_RQ_CC_LS__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_MK__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_NW_MK__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       oms_RQ_NW_MK__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const oms_RQ_NW_MK__qpid_map& a, const oms_RQ_NW_MK__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const oms_RQ_NW_MK__qpid_map& a, const oms_RQ_NW_MK__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_MK__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_MK__qpid_map>& a, const std::string& field);
void copy (oms_RQ_NW_MK__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_MK__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_MD_MK__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       oms_RQ_MD_MK__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const oms_RQ_MD_MK__qpid_map& a, const oms_RQ_MD_MK__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const oms_RQ_MD_MK__qpid_map& a, const oms_RQ_MD_MK__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_MK__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_MK__qpid_map>& a, const std::string& field);
void copy (oms_RQ_MD_MK__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_MK__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_CC_MK__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       oms_RQ_CC_MK__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const oms_RQ_CC_MK__qpid_map& a, const oms_RQ_CC_MK__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const oms_RQ_CC_MK__qpid_map& a, const oms_RQ_CC_MK__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_MK__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_MK__qpid_map>& a, const std::string& field);
void copy (oms_RQ_CC_MK__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_SM__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_NW_SM__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       oms_RQ_NW_SM__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const oms_RQ_NW_SM__qpid_map& a, const oms_RQ_NW_SM__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const oms_RQ_NW_SM__qpid_map& a, const oms_RQ_NW_SM__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_SM__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_SM__qpid_map>& a, const std::string& field);
void copy (oms_RQ_NW_SM__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_SM__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_MD_SM__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       oms_RQ_MD_SM__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const oms_RQ_MD_SM__qpid_map& a, const oms_RQ_MD_SM__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const oms_RQ_MD_SM__qpid_map& a, const oms_RQ_MD_SM__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_SM__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_SM__qpid_map>& a, const std::string& field);
void copy (oms_RQ_MD_SM__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_SM__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_CC_SM__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       oms_RQ_CC_SM__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const oms_RQ_CC_SM__qpid_map& a, const oms_RQ_CC_SM__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const oms_RQ_CC_SM__qpid_map& a, const oms_RQ_CC_SM__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_SM__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_SM__qpid_map>& a, const std::string& field);
void copy (oms_RQ_CC_SM__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_NW_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       oms_RQ_NW_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const oms_RQ_NW_SL__qpid_map& a, const oms_RQ_NW_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const oms_RQ_NW_SL__qpid_map& a, const oms_RQ_NW_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_SL__qpid_map>& a, const std::string& field);
void copy (oms_RQ_NW_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_MD_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       oms_RQ_MD_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const oms_RQ_MD_SL__qpid_map& a, const oms_RQ_MD_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const oms_RQ_MD_SL__qpid_map& a, const oms_RQ_MD_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_SL__qpid_map>& a, const std::string& field);
void copy (oms_RQ_MD_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_CC_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       oms_RQ_CC_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const oms_RQ_CC_SL__qpid_map& a, const oms_RQ_CC_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const oms_RQ_CC_SL__qpid_map& a, const oms_RQ_CC_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_SL__qpid_map>& a, const std::string& field);
void copy (oms_RQ_CC_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const oms_RQ_ORDERS_STATUS__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_ORDERS_STATUS__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       oms_RQ_ORDERS_STATUS__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const oms_RQ_ORDERS_STATUS__qpid_map& a, const oms_RQ_ORDERS_STATUS__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const oms_RQ_ORDERS_STATUS__qpid_map& a, const oms_RQ_ORDERS_STATUS__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_ORDERS_STATUS__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_ORDERS_STATUS__qpid_map>& a, const std::string& field);
void copy (oms_RQ_ORDERS_STATUS__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const oms_RQ_EXECS_HISTORIC__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_EXECS_HISTORIC__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       oms_RQ_EXECS_HISTORIC__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const oms_RQ_EXECS_HISTORIC__qpid_map& a, const oms_RQ_EXECS_HISTORIC__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const oms_RQ_EXECS_HISTORIC__qpid_map& a, const oms_RQ_EXECS_HISTORIC__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_EXECS_HISTORIC__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_EXECS_HISTORIC__qpid_map>& a, const std::string& field);
void copy (oms_RQ_EXECS_HISTORIC__qpid_map& a, const qpid::types::Variant& map);

    oms_RQ_NW_LS  __internal_get_default(oms_RQ_NW_LS *);
    
        inline oms_RQ_NW_LS__qpid_map  __internal_get_default(oms_RQ_NW_LS__qpid_map *) { return  oms_RQ_NW_LS__qpid_map(__internal_get_default((oms_RQ_NW_LS*)0));  }

    oms_RQ_MD_LS  __internal_get_default(oms_RQ_MD_LS *);
    
        inline oms_RQ_MD_LS__qpid_map  __internal_get_default(oms_RQ_MD_LS__qpid_map *) { return  oms_RQ_MD_LS__qpid_map(__internal_get_default((oms_RQ_MD_LS*)0));  }

    oms_RQ_CC_LS  __internal_get_default(oms_RQ_CC_LS *);
    
        inline oms_RQ_CC_LS__qpid_map  __internal_get_default(oms_RQ_CC_LS__qpid_map *) { return  oms_RQ_CC_LS__qpid_map(__internal_get_default((oms_RQ_CC_LS*)0));  }

    oms_RQ_NW_MK  __internal_get_default(oms_RQ_NW_MK *);
    
        inline oms_RQ_NW_MK__qpid_map  __internal_get_default(oms_RQ_NW_MK__qpid_map *) { return  oms_RQ_NW_MK__qpid_map(__internal_get_default((oms_RQ_NW_MK*)0));  }

    oms_RQ_MD_MK  __internal_get_default(oms_RQ_MD_MK *);
    
        inline oms_RQ_MD_MK__qpid_map  __internal_get_default(oms_RQ_MD_MK__qpid_map *) { return  oms_RQ_MD_MK__qpid_map(__internal_get_default((oms_RQ_MD_MK*)0));  }

    oms_RQ_CC_MK  __internal_get_default(oms_RQ_CC_MK *);
    
        inline oms_RQ_CC_MK__qpid_map  __internal_get_default(oms_RQ_CC_MK__qpid_map *) { return  oms_RQ_CC_MK__qpid_map(__internal_get_default((oms_RQ_CC_MK*)0));  }

    oms_RQ_NW_SM  __internal_get_default(oms_RQ_NW_SM *);
    
        inline oms_RQ_NW_SM__qpid_map  __internal_get_default(oms_RQ_NW_SM__qpid_map *) { return  oms_RQ_NW_SM__qpid_map(__internal_get_default((oms_RQ_NW_SM*)0));  }

    oms_RQ_MD_SM  __internal_get_default(oms_RQ_MD_SM *);
    
        inline oms_RQ_MD_SM__qpid_map  __internal_get_default(oms_RQ_MD_SM__qpid_map *) { return  oms_RQ_MD_SM__qpid_map(__internal_get_default((oms_RQ_MD_SM*)0));  }

    oms_RQ_CC_SM  __internal_get_default(oms_RQ_CC_SM *);
    
        inline oms_RQ_CC_SM__qpid_map  __internal_get_default(oms_RQ_CC_SM__qpid_map *) { return  oms_RQ_CC_SM__qpid_map(__internal_get_default((oms_RQ_CC_SM*)0));  }

    oms_RQ_NW_SL  __internal_get_default(oms_RQ_NW_SL *);
    
        inline oms_RQ_NW_SL__qpid_map  __internal_get_default(oms_RQ_NW_SL__qpid_map *) { return  oms_RQ_NW_SL__qpid_map(__internal_get_default((oms_RQ_NW_SL*)0));  }

    oms_RQ_MD_SL  __internal_get_default(oms_RQ_MD_SL *);
    
        inline oms_RQ_MD_SL__qpid_map  __internal_get_default(oms_RQ_MD_SL__qpid_map *) { return  oms_RQ_MD_SL__qpid_map(__internal_get_default((oms_RQ_MD_SL*)0));  }

    oms_RQ_CC_SL  __internal_get_default(oms_RQ_CC_SL *);
    
        inline oms_RQ_CC_SL__qpid_map  __internal_get_default(oms_RQ_CC_SL__qpid_map *) { return  oms_RQ_CC_SL__qpid_map(__internal_get_default((oms_RQ_CC_SL*)0));  }

    oms_RQ_ORDERS_STATUS  __internal_get_default(oms_RQ_ORDERS_STATUS *);
    
        inline oms_RQ_ORDERS_STATUS__qpid_map  __internal_get_default(oms_RQ_ORDERS_STATUS__qpid_map *) { return  oms_RQ_ORDERS_STATUS__qpid_map(__internal_get_default((oms_RQ_ORDERS_STATUS*)0));  }

    oms_RQ_EXECS_HISTORIC  __internal_get_default(oms_RQ_EXECS_HISTORIC *);
    
        inline oms_RQ_EXECS_HISTORIC__qpid_map  __internal_get_default(oms_RQ_EXECS_HISTORIC__qpid_map *) { return  oms_RQ_EXECS_HISTORIC__qpid_map(__internal_get_default((oms_RQ_EXECS_HISTORIC*)0));  }


};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_NW_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_NW_LS__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_MD_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_MD_LS__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_CC_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_CC_LS__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_NW_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_NW_MK__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_MD_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_MD_MK__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_CC_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_CC_MK__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_NW_SM)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_NW_SM__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_MD_SM)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_MD_SM__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_CC_SM)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_CC_SM__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_NW_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_NW_SL__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_MD_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_MD_SL__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_CC_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_CC_SL__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_ORDERS_STATUS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_ORDERS_STATUS__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_EXECS_HISTORIC)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_EXECS_HISTORIC__qpid_map)




#endif
