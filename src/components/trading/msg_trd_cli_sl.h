
#ifndef  __msg_trd_cli_sl__
#define  __msg_trd_cli_sl__


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
#include "components/acs/msg_acs.h"

namespace mtk { 
namespace trd { 
namespace msg { 




//-------------------------------
//      sub_position_sl
//-------------------------------    
class sub_position_sl     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_position_sl (    const mtk::FixedNumber&  _stop_price,   const mtk::FixedNumber&  _price,   const mtk::FixedNumber&  _quantity,   const std::string&  _cli_ref );
    explicit sub_position_sl ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_position_sl (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_position_sl"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_position_sl"; }
    
    

    

    
    
    
    

    // fields
    mtk::FixedNumber                          stop_price; 
    mtk::FixedNumber                          price; 
    mtk::FixedNumber                          quantity; 
    std::string                               cli_ref; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_position_sl__qpid_map
        {
        public:
            explicit  sub_position_sl__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_position_sl__qpid_map ( const sub_position_sl&  c ) : m_static(c) {}
            explicit  sub_position_sl__qpid_map (    const mtk::FixedNumber&  _stop_price,   const mtk::FixedNumber&  _price,   const mtk::FixedNumber&  _quantity,   const std::string&  _cli_ref );
            ~sub_position_sl__qpid_map() {};
            

            sub_position_sl                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      RQ_XX_SL
//-------------------------------    
class RQ_XX_SL        :  public  RQ_XX
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_XX_SL (  const RQ_XX&  parent,   const sub_position_sl&  _request_pos );
    explicit RQ_XX_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~RQ_XX_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_XX_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "RQ_XX_SL"; }
    
    

    

    
    
    
    

    // fields
    sub_position_sl                           request_pos; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class RQ_XX_SL__qpid_map
        {
        public:
            explicit  RQ_XX_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  RQ_XX_SL__qpid_map ( const RQ_XX_SL&  c ) : m_static(c) {}
            explicit  RQ_XX_SL__qpid_map (  const RQ_XX&  parent,   const sub_position_sl&  _request_pos );
            ~RQ_XX_SL__qpid_map() {};
            

            RQ_XX_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      RQ_NW_SL
//-------------------------------    
class RQ_NW_SL        :  public  RQ_XX_SL
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_NW_SL (  const RQ_XX_SL&  parent );
    explicit RQ_NW_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~RQ_NW_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_NW_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "RQ_NW_SL"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

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



        //  qpid_variant wrapper for dynamic
        class RQ_NW_SL__qpid_map
        {
        public:
            explicit  RQ_NW_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  RQ_NW_SL__qpid_map ( const RQ_NW_SL&  c ) : m_static(c) {}
            explicit  RQ_NW_SL__qpid_map (  const RQ_XX_SL&  parent );
            ~RQ_NW_SL__qpid_map() {};
            

            RQ_NW_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  RQ_NW_SL::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  RQ_NW_SL::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  RQ_NW_SL::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  RQ_NW_SL::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      RQ_MD_SL
//-------------------------------    
class RQ_MD_SL        :  public  RQ_XX_SL
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_MD_SL (  const RQ_XX_SL&  parent );
    explicit RQ_MD_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~RQ_MD_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_MD_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "RQ_MD_SL"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

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



        //  qpid_variant wrapper for dynamic
        class RQ_MD_SL__qpid_map
        {
        public:
            explicit  RQ_MD_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  RQ_MD_SL__qpid_map ( const RQ_MD_SL&  c ) : m_static(c) {}
            explicit  RQ_MD_SL__qpid_map (  const RQ_XX_SL&  parent );
            ~RQ_MD_SL__qpid_map() {};
            

            RQ_MD_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  RQ_MD_SL::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  RQ_MD_SL::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  RQ_MD_SL::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  RQ_MD_SL::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      RQ_CC_SL
//-------------------------------    
class RQ_CC_SL        :  public  RQ_XX_SL
{
public:
    //  inner classes

    
    // constructor
    explicit RQ_CC_SL (  const RQ_XX_SL&  parent );
    explicit RQ_CC_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~RQ_CC_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_CC_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "RQ_CC_SL"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

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



        //  qpid_variant wrapper for dynamic
        class RQ_CC_SL__qpid_map
        {
        public:
            explicit  RQ_CC_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  RQ_CC_SL__qpid_map ( const RQ_CC_SL&  c ) : m_static(c) {}
            explicit  RQ_CC_SL__qpid_map (  const RQ_XX_SL&  parent );
            ~RQ_CC_SL__qpid_map() {};
            

            RQ_CC_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  RQ_CC_SL::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  RQ_CC_SL::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  RQ_CC_SL::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  RQ_CC_SL::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      CF_XX_SL
//-------------------------------    
class CF_XX_SL        :  public  CF_XX
{
public:
    //  inner classes

    
    // constructor
    explicit CF_XX_SL (  const CF_XX&  parent,   const sub_position_sl&  _market_pos );
    explicit CF_XX_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_XX_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_XX_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "CF_XX_SL"; }
    
    

    

    
    
    
    

    // fields
    sub_position_sl                           market_pos; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class CF_XX_SL__qpid_map
        {
        public:
            explicit  CF_XX_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  CF_XX_SL__qpid_map ( const CF_XX_SL&  c ) : m_static(c) {}
            explicit  CF_XX_SL__qpid_map (  const CF_XX&  parent,   const sub_position_sl&  _market_pos );
            ~CF_XX_SL__qpid_map() {};
            

            CF_XX_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      CF_NW_SL
//-------------------------------    
class CF_NW_SL        :  public  CF_XX_SL
{
public:
    //  inner classes

    
    // constructor
    explicit CF_NW_SL (  const CF_XX_SL&  parent );
    explicit CF_NW_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_NW_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_NW_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "CF_NW_SL"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

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



        //  qpid_variant wrapper for dynamic
        class CF_NW_SL__qpid_map
        {
        public:
            explicit  CF_NW_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  CF_NW_SL__qpid_map ( const CF_NW_SL&  c ) : m_static(c) {}
            explicit  CF_NW_SL__qpid_map (  const CF_XX_SL&  parent );
            ~CF_NW_SL__qpid_map() {};
            

            CF_NW_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  CF_NW_SL::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  CF_NW_SL::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  CF_NW_SL::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  CF_NW_SL::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      CF_MD_SL
//-------------------------------    
class CF_MD_SL        :  public  CF_XX_SL
{
public:
    //  inner classes

    
    // constructor
    explicit CF_MD_SL (  const CF_XX_SL&  parent );
    explicit CF_MD_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_MD_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_MD_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "CF_MD_SL"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

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



        //  qpid_variant wrapper for dynamic
        class CF_MD_SL__qpid_map
        {
        public:
            explicit  CF_MD_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  CF_MD_SL__qpid_map ( const CF_MD_SL&  c ) : m_static(c) {}
            explicit  CF_MD_SL__qpid_map (  const CF_XX_SL&  parent );
            ~CF_MD_SL__qpid_map() {};
            

            CF_MD_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  CF_MD_SL::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  CF_MD_SL::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  CF_MD_SL::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  CF_MD_SL::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      CF_CC_SL
//-------------------------------    
class CF_CC_SL        :  public  CF_XX_SL
{
public:
    //  inner classes

    
    // constructor
    explicit CF_CC_SL (  const CF_XX_SL&  parent );
    explicit CF_CC_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_CC_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_CC_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "CF_CC_SL"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

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



        //  qpid_variant wrapper for dynamic
        class CF_CC_SL__qpid_map
        {
        public:
            explicit  CF_CC_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  CF_CC_SL__qpid_map ( const CF_CC_SL&  c ) : m_static(c) {}
            explicit  CF_CC_SL__qpid_map (  const CF_XX_SL&  parent );
            ~CF_CC_SL__qpid_map() {};
            

            CF_CC_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  CF_CC_SL::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  CF_CC_SL::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  CF_CC_SL::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  CF_CC_SL::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      CF_TR_SL
//-------------------------------    
class CF_TR_SL        :  public  CF_XX_SL
{
public:
    //  inner classes

    
    // constructor
    explicit CF_TR_SL (  const CF_XX_SL&  parent );
    explicit CF_TR_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_TR_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_TR_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "CF_TR_SL"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

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



        //  qpid_variant wrapper for dynamic
        class CF_TR_SL__qpid_map
        {
        public:
            explicit  CF_TR_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  CF_TR_SL__qpid_map ( const CF_TR_SL&  c ) : m_static(c) {}
            explicit  CF_TR_SL__qpid_map (  const CF_XX_SL&  parent );
            ~CF_TR_SL__qpid_map() {};
            

            CF_TR_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  CF_TR_SL::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  CF_TR_SL::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  CF_TR_SL::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  CF_TR_SL::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      RJ_XX_SL
//-------------------------------    
class RJ_XX_SL        :  public  CF_XX_SL
{
public:
    //  inner classes

    
    // constructor
    explicit RJ_XX_SL (  const CF_XX_SL&  parent,   const sub_position_sl&  _request_pos );
    explicit RJ_XX_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~RJ_XX_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RJ_XX_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "RJ_XX_SL"; }
    
    

    

    
    
    
    

    // fields
    sub_position_sl                           request_pos; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class RJ_XX_SL__qpid_map
        {
        public:
            explicit  RJ_XX_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  RJ_XX_SL__qpid_map ( const RJ_XX_SL&  c ) : m_static(c) {}
            explicit  RJ_XX_SL__qpid_map (  const CF_XX_SL&  parent,   const sub_position_sl&  _request_pos );
            ~RJ_XX_SL__qpid_map() {};
            

            RJ_XX_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      RJ_NW_SL
//-------------------------------    
class RJ_NW_SL        :  public  RJ_XX_SL
{
public:
    //  inner classes

    
    // constructor
    explicit RJ_NW_SL (  const RJ_XX_SL&  parent );
    explicit RJ_NW_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~RJ_NW_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RJ_NW_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "RJ_NW_SL"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

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



        //  qpid_variant wrapper for dynamic
        class RJ_NW_SL__qpid_map
        {
        public:
            explicit  RJ_NW_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  RJ_NW_SL__qpid_map ( const RJ_NW_SL&  c ) : m_static(c) {}
            explicit  RJ_NW_SL__qpid_map (  const RJ_XX_SL&  parent );
            ~RJ_NW_SL__qpid_map() {};
            

            RJ_NW_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  RJ_NW_SL::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  RJ_NW_SL::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  RJ_NW_SL::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  RJ_NW_SL::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      RJ_MD_SL
//-------------------------------    
class RJ_MD_SL        :  public  RJ_XX_SL
{
public:
    //  inner classes

    
    // constructor
    explicit RJ_MD_SL (  const RJ_XX_SL&  parent );
    explicit RJ_MD_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~RJ_MD_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RJ_MD_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "RJ_MD_SL"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

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



        //  qpid_variant wrapper for dynamic
        class RJ_MD_SL__qpid_map
        {
        public:
            explicit  RJ_MD_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  RJ_MD_SL__qpid_map ( const RJ_MD_SL&  c ) : m_static(c) {}
            explicit  RJ_MD_SL__qpid_map (  const RJ_XX_SL&  parent );
            ~RJ_MD_SL__qpid_map() {};
            

            RJ_MD_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  RJ_MD_SL::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  RJ_MD_SL::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  RJ_MD_SL::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  RJ_MD_SL::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      RJ_CC_SL
//-------------------------------    
class RJ_CC_SL        :  public  RJ_XX_SL
{
public:
    //  inner classes

    
    // constructor
    explicit RJ_CC_SL (  const RJ_XX_SL&  parent );
    explicit RJ_CC_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~RJ_CC_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RJ_CC_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "RJ_CC_SL"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

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



        //  qpid_variant wrapper for dynamic
        class RJ_CC_SL__qpid_map
        {
        public:
            explicit  RJ_CC_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  RJ_CC_SL__qpid_map ( const RJ_CC_SL&  c ) : m_static(c) {}
            explicit  RJ_CC_SL__qpid_map (  const RJ_XX_SL&  parent );
            ~RJ_CC_SL__qpid_map() {};
            

            RJ_CC_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  RJ_CC_SL::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  RJ_CC_SL::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  RJ_CC_SL::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  RJ_CC_SL::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      CF_ST_SL
//-------------------------------    
class CF_ST_SL        :  public  CF_XX_SL
{
public:
    //  inner classes

    
    // constructor
    explicit CF_ST_SL (  const CF_XX_SL&  parent,   const mtk::msg::sub_gen_response_location&  _gen_response_location );
    explicit CF_ST_SL ( const qpid::types::Variant::Map&  mv );
    virtual ~CF_ST_SL (){};
    virtual std::string get_message_type_as_string       (void) const  { return "CF_ST_SL"; }
    static  std::string static_get_message_type_as_string(void)        { return "CF_ST_SL"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

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



        //  qpid_variant wrapper for dynamic
        class CF_ST_SL__qpid_map
        {
        public:
            explicit  CF_ST_SL__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  CF_ST_SL__qpid_map ( const CF_ST_SL&  c ) : m_static(c) {}
            explicit  CF_ST_SL__qpid_map (  const CF_XX_SL&  parent,   const mtk::msg::sub_gen_response_location&  _gen_response_location );
            ~CF_ST_SL__qpid_map() {};
            

            CF_ST_SL                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  CF_ST_SL::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  CF_ST_SL::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  CF_ST_SL::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  CF_ST_SL::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        
    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_position_sl & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_position_sl & c);
   void           operator >> (const YAML::Node& n,       sub_position_sl & c);

bool operator== (const sub_position_sl& a, const sub_position_sl& b);
bool operator!= (const sub_position_sl& a, const sub_position_sl& b);

    std::ostream& operator<< (std::ostream& o, const RQ_XX_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_XX_SL & c);
   void           operator >> (const YAML::Node& n,       RQ_XX_SL & c);

bool operator== (const RQ_XX_SL& a, const RQ_XX_SL& b);
bool operator!= (const RQ_XX_SL& a, const RQ_XX_SL& b);

    std::ostream& operator<< (std::ostream& o, const RQ_NW_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_NW_SL & c);
   void           operator >> (const YAML::Node& n,       RQ_NW_SL & c);

bool operator== (const RQ_NW_SL& a, const RQ_NW_SL& b);
bool operator!= (const RQ_NW_SL& a, const RQ_NW_SL& b);

    std::ostream& operator<< (std::ostream& o, const RQ_MD_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_MD_SL & c);
   void           operator >> (const YAML::Node& n,       RQ_MD_SL & c);

bool operator== (const RQ_MD_SL& a, const RQ_MD_SL& b);
bool operator!= (const RQ_MD_SL& a, const RQ_MD_SL& b);

    std::ostream& operator<< (std::ostream& o, const RQ_CC_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_CC_SL & c);
   void           operator >> (const YAML::Node& n,       RQ_CC_SL & c);

bool operator== (const RQ_CC_SL& a, const RQ_CC_SL& b);
bool operator!= (const RQ_CC_SL& a, const RQ_CC_SL& b);

    std::ostream& operator<< (std::ostream& o, const CF_XX_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_XX_SL & c);
   void           operator >> (const YAML::Node& n,       CF_XX_SL & c);

bool operator== (const CF_XX_SL& a, const CF_XX_SL& b);
bool operator!= (const CF_XX_SL& a, const CF_XX_SL& b);

    std::ostream& operator<< (std::ostream& o, const CF_NW_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_NW_SL & c);
   void           operator >> (const YAML::Node& n,       CF_NW_SL & c);

bool operator== (const CF_NW_SL& a, const CF_NW_SL& b);
bool operator!= (const CF_NW_SL& a, const CF_NW_SL& b);

    std::ostream& operator<< (std::ostream& o, const CF_MD_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_MD_SL & c);
   void           operator >> (const YAML::Node& n,       CF_MD_SL & c);

bool operator== (const CF_MD_SL& a, const CF_MD_SL& b);
bool operator!= (const CF_MD_SL& a, const CF_MD_SL& b);

    std::ostream& operator<< (std::ostream& o, const CF_CC_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_CC_SL & c);
   void           operator >> (const YAML::Node& n,       CF_CC_SL & c);

bool operator== (const CF_CC_SL& a, const CF_CC_SL& b);
bool operator!= (const CF_CC_SL& a, const CF_CC_SL& b);

    std::ostream& operator<< (std::ostream& o, const CF_TR_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_TR_SL & c);
   void           operator >> (const YAML::Node& n,       CF_TR_SL & c);

bool operator== (const CF_TR_SL& a, const CF_TR_SL& b);
bool operator!= (const CF_TR_SL& a, const CF_TR_SL& b);

    std::ostream& operator<< (std::ostream& o, const RJ_XX_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RJ_XX_SL & c);
   void           operator >> (const YAML::Node& n,       RJ_XX_SL & c);

bool operator== (const RJ_XX_SL& a, const RJ_XX_SL& b);
bool operator!= (const RJ_XX_SL& a, const RJ_XX_SL& b);

    std::ostream& operator<< (std::ostream& o, const RJ_NW_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RJ_NW_SL & c);
   void           operator >> (const YAML::Node& n,       RJ_NW_SL & c);

bool operator== (const RJ_NW_SL& a, const RJ_NW_SL& b);
bool operator!= (const RJ_NW_SL& a, const RJ_NW_SL& b);

    std::ostream& operator<< (std::ostream& o, const RJ_MD_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RJ_MD_SL & c);
   void           operator >> (const YAML::Node& n,       RJ_MD_SL & c);

bool operator== (const RJ_MD_SL& a, const RJ_MD_SL& b);
bool operator!= (const RJ_MD_SL& a, const RJ_MD_SL& b);

    std::ostream& operator<< (std::ostream& o, const RJ_CC_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RJ_CC_SL & c);
   void           operator >> (const YAML::Node& n,       RJ_CC_SL & c);

bool operator== (const RJ_CC_SL& a, const RJ_CC_SL& b);
bool operator!= (const RJ_CC_SL& a, const RJ_CC_SL& b);

    std::ostream& operator<< (std::ostream& o, const CF_ST_SL & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const CF_ST_SL & c);
   void           operator >> (const YAML::Node& n,       CF_ST_SL & c);

bool operator== (const CF_ST_SL& a, const CF_ST_SL& b);
bool operator!= (const CF_ST_SL& a, const CF_ST_SL& b);

void __internal_add2map (qpid::types::Variant::Map& map, const sub_position_sl& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_position_sl>& a, const std::string& field);
void copy (sub_position_sl& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_XX_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_XX_SL>& a, const std::string& field);
void copy (RQ_XX_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_NW_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_NW_SL>& a, const std::string& field);
void copy (RQ_NW_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_MD_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_MD_SL>& a, const std::string& field);
void copy (RQ_MD_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_CC_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_CC_SL>& a, const std::string& field);
void copy (RQ_CC_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_XX_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_XX_SL>& a, const std::string& field);
void copy (CF_XX_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_NW_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_NW_SL>& a, const std::string& field);
void copy (CF_NW_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_MD_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_MD_SL>& a, const std::string& field);
void copy (CF_MD_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_CC_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_CC_SL>& a, const std::string& field);
void copy (CF_CC_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_TR_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_TR_SL>& a, const std::string& field);
void copy (CF_TR_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_XX_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_XX_SL>& a, const std::string& field);
void copy (RJ_XX_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_NW_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_NW_SL>& a, const std::string& field);
void copy (RJ_NW_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_MD_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_MD_SL>& a, const std::string& field);
void copy (RJ_MD_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_CC_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_CC_SL>& a, const std::string& field);
void copy (RJ_CC_SL& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const CF_ST_SL& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_ST_SL>& a, const std::string& field);
void copy (CF_ST_SL& a, const qpid::types::Variant& map);

    
    
    
//  fordward declarations  dynamic--------------------------------------------------------


inline std::ostream& operator<< (std::ostream& o, const sub_position_sl__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_position_sl__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_position_sl__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_position_sl__qpid_map& a, const sub_position_sl__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_position_sl__qpid_map& a, const sub_position_sl__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_position_sl__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_position_sl__qpid_map>& a, const std::string& field);
void copy (sub_position_sl__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const RQ_XX_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_XX_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       RQ_XX_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const RQ_XX_SL__qpid_map& a, const RQ_XX_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const RQ_XX_SL__qpid_map& a, const RQ_XX_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_XX_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_XX_SL__qpid_map>& a, const std::string& field);
void copy (RQ_XX_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const RQ_NW_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_NW_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       RQ_NW_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const RQ_NW_SL__qpid_map& a, const RQ_NW_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const RQ_NW_SL__qpid_map& a, const RQ_NW_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_NW_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_NW_SL__qpid_map>& a, const std::string& field);
void copy (RQ_NW_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const RQ_MD_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_MD_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       RQ_MD_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const RQ_MD_SL__qpid_map& a, const RQ_MD_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const RQ_MD_SL__qpid_map& a, const RQ_MD_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_MD_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_MD_SL__qpid_map>& a, const std::string& field);
void copy (RQ_MD_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const RQ_CC_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_CC_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       RQ_CC_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const RQ_CC_SL__qpid_map& a, const RQ_CC_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const RQ_CC_SL__qpid_map& a, const RQ_CC_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_CC_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_CC_SL__qpid_map>& a, const std::string& field);
void copy (RQ_CC_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const CF_XX_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const CF_XX_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       CF_XX_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const CF_XX_SL__qpid_map& a, const CF_XX_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const CF_XX_SL__qpid_map& a, const CF_XX_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const CF_XX_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_XX_SL__qpid_map>& a, const std::string& field);
void copy (CF_XX_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const CF_NW_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const CF_NW_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       CF_NW_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const CF_NW_SL__qpid_map& a, const CF_NW_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const CF_NW_SL__qpid_map& a, const CF_NW_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const CF_NW_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_NW_SL__qpid_map>& a, const std::string& field);
void copy (CF_NW_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const CF_MD_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const CF_MD_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       CF_MD_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const CF_MD_SL__qpid_map& a, const CF_MD_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const CF_MD_SL__qpid_map& a, const CF_MD_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const CF_MD_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_MD_SL__qpid_map>& a, const std::string& field);
void copy (CF_MD_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const CF_CC_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const CF_CC_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       CF_CC_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const CF_CC_SL__qpid_map& a, const CF_CC_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const CF_CC_SL__qpid_map& a, const CF_CC_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const CF_CC_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_CC_SL__qpid_map>& a, const std::string& field);
void copy (CF_CC_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const CF_TR_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const CF_TR_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       CF_TR_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const CF_TR_SL__qpid_map& a, const CF_TR_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const CF_TR_SL__qpid_map& a, const CF_TR_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const CF_TR_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_TR_SL__qpid_map>& a, const std::string& field);
void copy (CF_TR_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const RJ_XX_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const RJ_XX_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       RJ_XX_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const RJ_XX_SL__qpid_map& a, const RJ_XX_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const RJ_XX_SL__qpid_map& a, const RJ_XX_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_XX_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_XX_SL__qpid_map>& a, const std::string& field);
void copy (RJ_XX_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const RJ_NW_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const RJ_NW_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       RJ_NW_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const RJ_NW_SL__qpid_map& a, const RJ_NW_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const RJ_NW_SL__qpid_map& a, const RJ_NW_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_NW_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_NW_SL__qpid_map>& a, const std::string& field);
void copy (RJ_NW_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const RJ_MD_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const RJ_MD_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       RJ_MD_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const RJ_MD_SL__qpid_map& a, const RJ_MD_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const RJ_MD_SL__qpid_map& a, const RJ_MD_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_MD_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_MD_SL__qpid_map>& a, const std::string& field);
void copy (RJ_MD_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const RJ_CC_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const RJ_CC_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       RJ_CC_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const RJ_CC_SL__qpid_map& a, const RJ_CC_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const RJ_CC_SL__qpid_map& a, const RJ_CC_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const RJ_CC_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_CC_SL__qpid_map>& a, const std::string& field);
void copy (RJ_CC_SL__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const CF_ST_SL__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const CF_ST_SL__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       CF_ST_SL__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const CF_ST_SL__qpid_map& a, const CF_ST_SL__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const CF_ST_SL__qpid_map& a, const CF_ST_SL__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const CF_ST_SL__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_ST_SL__qpid_map>& a, const std::string& field);
void copy (CF_ST_SL__qpid_map& a, const qpid::types::Variant& map);

    sub_position_sl  __internal_get_default(sub_position_sl *);
    
        inline sub_position_sl__qpid_map  __internal_get_default(sub_position_sl__qpid_map *) { return  sub_position_sl__qpid_map(__internal_get_default((sub_position_sl*)0));  }

    RQ_XX_SL  __internal_get_default(RQ_XX_SL *);
    
        inline RQ_XX_SL__qpid_map  __internal_get_default(RQ_XX_SL__qpid_map *) { return  RQ_XX_SL__qpid_map(__internal_get_default((RQ_XX_SL*)0));  }

    RQ_NW_SL  __internal_get_default(RQ_NW_SL *);
    
        inline RQ_NW_SL__qpid_map  __internal_get_default(RQ_NW_SL__qpid_map *) { return  RQ_NW_SL__qpid_map(__internal_get_default((RQ_NW_SL*)0));  }

    RQ_MD_SL  __internal_get_default(RQ_MD_SL *);
    
        inline RQ_MD_SL__qpid_map  __internal_get_default(RQ_MD_SL__qpid_map *) { return  RQ_MD_SL__qpid_map(__internal_get_default((RQ_MD_SL*)0));  }

    RQ_CC_SL  __internal_get_default(RQ_CC_SL *);
    
        inline RQ_CC_SL__qpid_map  __internal_get_default(RQ_CC_SL__qpid_map *) { return  RQ_CC_SL__qpid_map(__internal_get_default((RQ_CC_SL*)0));  }

    CF_XX_SL  __internal_get_default(CF_XX_SL *);
    
        inline CF_XX_SL__qpid_map  __internal_get_default(CF_XX_SL__qpid_map *) { return  CF_XX_SL__qpid_map(__internal_get_default((CF_XX_SL*)0));  }

    CF_NW_SL  __internal_get_default(CF_NW_SL *);
    
        inline CF_NW_SL__qpid_map  __internal_get_default(CF_NW_SL__qpid_map *) { return  CF_NW_SL__qpid_map(__internal_get_default((CF_NW_SL*)0));  }

    CF_MD_SL  __internal_get_default(CF_MD_SL *);
    
        inline CF_MD_SL__qpid_map  __internal_get_default(CF_MD_SL__qpid_map *) { return  CF_MD_SL__qpid_map(__internal_get_default((CF_MD_SL*)0));  }

    CF_CC_SL  __internal_get_default(CF_CC_SL *);
    
        inline CF_CC_SL__qpid_map  __internal_get_default(CF_CC_SL__qpid_map *) { return  CF_CC_SL__qpid_map(__internal_get_default((CF_CC_SL*)0));  }

    CF_TR_SL  __internal_get_default(CF_TR_SL *);
    
        inline CF_TR_SL__qpid_map  __internal_get_default(CF_TR_SL__qpid_map *) { return  CF_TR_SL__qpid_map(__internal_get_default((CF_TR_SL*)0));  }

    RJ_XX_SL  __internal_get_default(RJ_XX_SL *);
    
        inline RJ_XX_SL__qpid_map  __internal_get_default(RJ_XX_SL__qpid_map *) { return  RJ_XX_SL__qpid_map(__internal_get_default((RJ_XX_SL*)0));  }

    RJ_NW_SL  __internal_get_default(RJ_NW_SL *);
    
        inline RJ_NW_SL__qpid_map  __internal_get_default(RJ_NW_SL__qpid_map *) { return  RJ_NW_SL__qpid_map(__internal_get_default((RJ_NW_SL*)0));  }

    RJ_MD_SL  __internal_get_default(RJ_MD_SL *);
    
        inline RJ_MD_SL__qpid_map  __internal_get_default(RJ_MD_SL__qpid_map *) { return  RJ_MD_SL__qpid_map(__internal_get_default((RJ_MD_SL*)0));  }

    RJ_CC_SL  __internal_get_default(RJ_CC_SL *);
    
        inline RJ_CC_SL__qpid_map  __internal_get_default(RJ_CC_SL__qpid_map *) { return  RJ_CC_SL__qpid_map(__internal_get_default((RJ_CC_SL*)0));  }

    CF_ST_SL  __internal_get_default(CF_ST_SL *);
    
        inline CF_ST_SL__qpid_map  __internal_get_default(CF_ST_SL__qpid_map *) { return  CF_ST_SL__qpid_map(__internal_get_default((CF_ST_SL*)0));  }


};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RQ_NW_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RQ_NW_SL__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RQ_MD_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RQ_MD_SL__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RQ_CC_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RQ_CC_SL__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_NW_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_NW_SL__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_MD_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_MD_SL__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_CC_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_CC_SL__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_TR_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_TR_SL__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RJ_NW_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RJ_NW_SL__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RJ_MD_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RJ_MD_SL__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RJ_CC_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::RJ_CC_SL__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_ST_SL)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::CF_ST_SL__qpid_map)




#endif
