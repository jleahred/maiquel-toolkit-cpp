
#ifndef  __msg_prices__
#define  __msg_prices__


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
#include "support/mtk_double.h"
#include "components/trading/msg_trd_common_support.h"

namespace mtk { 
namespace prices { 
namespace msg { 




//-------------------------------
//      sub_price_level
//-------------------------------    
class sub_price_level     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_price_level (    const mtk::FixedNumber&  _price,   const mtk::FixedNumber&  _quantity );
    explicit sub_price_level ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_price_level (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_price_level"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_price_level"; }
    
    

    

    
    
    
    

    // fields
    mtk::FixedNumber                          price; 
    mtk::FixedNumber                          quantity; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_price_level__qpid_map
        {
        public:
            explicit  sub_price_level__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_price_level__qpid_map ( const sub_price_level&  c ) : m_static(c) {}
            explicit  sub_price_level__qpid_map (    const mtk::FixedNumber&  _price,   const mtk::FixedNumber&  _quantity );
            ~sub_price_level__qpid_map() {};
            

            sub_price_level                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_price_deph5
//-------------------------------    
class sub_price_deph5     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_price_deph5 (    const sub_price_level&  _level0,   const sub_price_level&  _level1,   const sub_price_level&  _level2,   const sub_price_level&  _level3,   const sub_price_level&  _level4 );
    explicit sub_price_deph5 ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_price_deph5 (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_price_deph5"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_price_deph5"; }
    
    

    

    
    
    
    

    // fields
    sub_price_level                           level0; 
    sub_price_level                           level1; 
    sub_price_level                           level2; 
    sub_price_level                           level3; 
    sub_price_level                           level4; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_price_deph5__qpid_map
        {
        public:
            explicit  sub_price_deph5__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_price_deph5__qpid_map ( const sub_price_deph5&  c ) : m_static(c) {}
            explicit  sub_price_deph5__qpid_map (    const sub_price_level&  _level0,   const sub_price_level&  _level1,   const sub_price_level&  _level2,   const sub_price_level&  _level3,   const sub_price_level&  _level4 );
            ~sub_price_deph5__qpid_map() {};
            

            sub_price_deph5                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_best_prices
//-------------------------------    
class sub_best_prices     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_best_prices (    const sub_price_deph5&  _bids,   const sub_price_deph5&  _asks );
    explicit sub_best_prices ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_best_prices (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_best_prices"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_best_prices"; }
    
    

    

    
    
    
    

    // fields
    sub_price_deph5                           bids; 
    sub_price_deph5                           asks; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_best_prices__qpid_map
        {
        public:
            explicit  sub_best_prices__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_best_prices__qpid_map ( const sub_best_prices&  c ) : m_static(c) {}
            explicit  sub_best_prices__qpid_map (    const sub_price_deph5&  _bids,   const sub_price_deph5&  _asks );
            ~sub_best_prices__qpid_map() {};
            

            sub_best_prices                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_best_prices
//-------------------------------    
class pub_best_prices     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_best_prices (    const mtk::msg::sub_product_code&  _product_code,   const sub_best_prices&  _best_prices,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
    explicit pub_best_prices ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_best_prices (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_best_prices"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_best_prices"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_product_code                product_code; 
    sub_best_prices                           best_prices; 
    mtk::msg::sub_control_fluct               orig_control_fluct; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address (const std::string& product_code_market);
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& product_code_market,const std::string& product_code_product);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_best_prices__qpid_map
        {
        public:
            explicit  pub_best_prices__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_best_prices__qpid_map ( const pub_best_prices&  c ) : m_static(c) {}
            explicit  pub_best_prices__qpid_map (    const mtk::msg::sub_product_code&  _product_code,   const sub_best_prices&  _best_prices,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
            ~pub_best_prices__qpid_map() {};
            

            pub_best_prices                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address (const std::string& product_code_market)  {  return  pub_best_prices::static_get_qpid_address(product_code_market);  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_best_prices::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_best_prices::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_best_prices::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_new_products
//-------------------------------    
class pub_new_products     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_new_products (    const std::string&  _market );
    explicit pub_new_products ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_new_products (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_new_products"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_new_products"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

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



        //  qpid_variant wrapper for dynamic
        class pub_new_products__qpid_map
        {
        public:
            explicit  pub_new_products__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_new_products__qpid_map ( const pub_new_products&  c ) : m_static(c) {}
            explicit  pub_new_products__qpid_map (    const std::string&  _market );
            ~pub_new_products__qpid_map() {};
            

            pub_new_products                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  pub_new_products::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_new_products::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_new_products::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_new_products::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_future_info
//-------------------------------    
class sub_future_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_future_info (    const int16_t&  _num_legs,   const mtk::nullable<mtk::DateTime>&  _maturity,   const mtk::DateTime&  _last_trading_dt,   const std::string&  _underlying );
    explicit sub_future_info ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_future_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_future_info"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_future_info"; }
    
    

    

    
    
    
    

    // fields
    int16_t                                   num_legs; 
    mtk::nullable<mtk::DateTime>              maturity; 
    mtk::DateTime                             last_trading_dt; 
    std::string                               underlying; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_future_info__qpid_map
        {
        public:
            explicit  sub_future_info__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_future_info__qpid_map ( const sub_future_info&  c ) : m_static(c) {}
            explicit  sub_future_info__qpid_map (    const int16_t&  _num_legs,   const mtk::DateTime&  _last_trading_dt,   const std::string&  _underlying );
            ~sub_future_info__qpid_map() {};
            

            sub_future_info                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_option_info
//-------------------------------    
class sub_option_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_option_info (    const mtk::DateTime&  _last_trading_dt,   const std::string&  _underlying );
    explicit sub_option_info ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_option_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_option_info"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_option_info"; }
    
    

    

    
    
    
    

    // fields
    mtk::DateTime                             last_trading_dt; 
    std::string                               underlying; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_option_info__qpid_map
        {
        public:
            explicit  sub_option_info__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_option_info__qpid_map ( const sub_option_info&  c ) : m_static(c) {}
            explicit  sub_option_info__qpid_map (    const mtk::DateTime&  _last_trading_dt,   const std::string&  _underlying );
            ~sub_option_info__qpid_map() {};
            

            sub_option_info                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_additional_info
//-------------------------------    
class sub_additional_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_additional_info (    const std::string&  _group,   const mtk::nullable<std::string>&  _description,   const mtk::nullable<mtk::DateTime>&  _value_date,   const mtk::Double&  _unit_cost,   const mtk::nullable<sub_future_info>&  _future_info,   const mtk::nullable<sub_option_info>&  _option_info,   const std::string&  _yaml_misc );
    explicit sub_additional_info ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_additional_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_additional_info"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_additional_info"; }
    
    

    

    
    
    
    

    // fields
    std::string                               group; 
    mtk::nullable<std::string>                description; 
    mtk::nullable<mtk::DateTime>              value_date; 
    mtk::Double                               unit_cost; 
    mtk::nullable<sub_future_info>            future_info; 
    mtk::nullable<sub_option_info>            option_info; 
    std::string                               yaml_misc; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_additional_info__qpid_map
        {
        public:
            explicit  sub_additional_info__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_additional_info__qpid_map ( const sub_additional_info&  c ) : m_static(c) {}
            explicit  sub_additional_info__qpid_map (    const std::string&  _group,   const mtk::Double&  _unit_cost,   const std::string&  _yaml_misc );
            ~sub_additional_info__qpid_map() {};
            

            sub_additional_info                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_last_mk_execs_ticker
//-------------------------------    
class sub_last_mk_execs_ticker     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_last_mk_execs_ticker (    const mtk::FixedNumber&  _last_price,   const mtk::FixedNumber&  _last_quantity,   const mtk::FixedNumber&  _max_last_price,   const mtk::FixedNumber&  _min_last_price,   const mtk::FixedNumber&  _opened_price );
    explicit sub_last_mk_execs_ticker ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_last_mk_execs_ticker (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_last_mk_execs_ticker"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_last_mk_execs_ticker"; }
    
    

    

    
    
    
    

    // fields
    mtk::FixedNumber                          last_price; 
    mtk::FixedNumber                          last_quantity; 
    mtk::FixedNumber                          max_last_price; 
    mtk::FixedNumber                          min_last_price; 
    mtk::FixedNumber                          opened_price; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_last_mk_execs_ticker__qpid_map
        {
        public:
            explicit  sub_last_mk_execs_ticker__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_last_mk_execs_ticker__qpid_map ( const sub_last_mk_execs_ticker&  c ) : m_static(c) {}
            explicit  sub_last_mk_execs_ticker__qpid_map (    const mtk::FixedNumber&  _last_price,   const mtk::FixedNumber&  _last_quantity,   const mtk::FixedNumber&  _max_last_price,   const mtk::FixedNumber&  _min_last_price,   const mtk::FixedNumber&  _opened_price );
            ~sub_last_mk_execs_ticker__qpid_map() {};
            

            sub_last_mk_execs_ticker                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_last_mk_execs_ticker
//-------------------------------    
class pub_last_mk_execs_ticker     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_last_mk_execs_ticker (    const mtk::msg::sub_product_code&  _product_code,   const sub_last_mk_execs_ticker&  _last_mk_execs_ticker,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
    explicit pub_last_mk_execs_ticker ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_last_mk_execs_ticker (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_last_mk_execs_ticker"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_last_mk_execs_ticker"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_product_code                product_code; 
    sub_last_mk_execs_ticker                  last_mk_execs_ticker; 
    mtk::msg::sub_control_fluct               orig_control_fluct; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address (const std::string& product_code_market);
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& product_code_market,const std::string& product_code_product);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_last_mk_execs_ticker__qpid_map
        {
        public:
            explicit  pub_last_mk_execs_ticker__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_last_mk_execs_ticker__qpid_map ( const pub_last_mk_execs_ticker&  c ) : m_static(c) {}
            explicit  pub_last_mk_execs_ticker__qpid_map (    const mtk::msg::sub_product_code&  _product_code,   const sub_last_mk_execs_ticker&  _last_mk_execs_ticker,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
            ~pub_last_mk_execs_ticker__qpid_map() {};
            

            pub_last_mk_execs_ticker                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address (const std::string& product_code_market)  {  return  pub_last_mk_execs_ticker::static_get_qpid_address(product_code_market);  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_last_mk_execs_ticker::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_last_mk_execs_ticker::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_last_mk_execs_ticker::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_additional_info
//-------------------------------    
class pub_additional_info     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_additional_info (    const mtk::msg::sub_product_code&  _product_code,   const sub_additional_info&  _additional_info,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
    explicit pub_additional_info ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_additional_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_additional_info"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_additional_info"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_product_code                product_code; 
    sub_additional_info                       additional_info; 
    mtk::msg::sub_control_fluct               orig_control_fluct; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address (const std::string& product_code_market);
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& product_code_product);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_additional_info__qpid_map
        {
        public:
            explicit  pub_additional_info__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_additional_info__qpid_map ( const pub_additional_info&  c ) : m_static(c) {}
            explicit  pub_additional_info__qpid_map (    const mtk::msg::sub_product_code&  _product_code,   const sub_additional_info&  _additional_info,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
            ~pub_additional_info__qpid_map() {};
            

            pub_additional_info                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address (const std::string& product_code_market)  {  return  pub_additional_info::static_get_qpid_address(product_code_market);  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_additional_info::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_additional_info::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_additional_info::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_full_product_info
//-------------------------------    
class sub_full_product_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_full_product_info (    const mtk::msg::sub_product_code&  _product_code,   const sub_best_prices&  _best_prices,   const sub_additional_info&  _additional_info,   const mtk::nullable<sub_last_mk_execs_ticker>&  _last_mk_execs_ticker );
    explicit sub_full_product_info ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_full_product_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_full_product_info"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_full_product_info"; }
    
    

    

    
    
    
    

    // fields
    mtk::msg::sub_product_code                product_code; 
    sub_best_prices                           best_prices; 
    sub_additional_info                       additional_info; 
    mtk::nullable<sub_last_mk_execs_ticker>   last_mk_execs_ticker; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_full_product_info__qpid_map
        {
        public:
            explicit  sub_full_product_info__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_full_product_info__qpid_map ( const sub_full_product_info&  c ) : m_static(c) {}
            explicit  sub_full_product_info__qpid_map (    const mtk::msg::sub_product_code&  _product_code,   const sub_best_prices&  _best_prices,   const sub_additional_info&  _additional_info );
            ~sub_full_product_info__qpid_map() {};
            

            sub_full_product_info                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_full_product_info_optionals
//-------------------------------    
class sub_full_product_info_optionals     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_full_product_info_optionals (    const bool&  _initialized,   const mtk::msg::sub_product_code&  _product_code,   const mtk::nullable<sub_best_prices>&  _best_prices,   const mtk::nullable<sub_additional_info>&  _additional_info,   const mtk::nullable<sub_last_mk_execs_ticker>&  _last_mk_execs_ticker );
    explicit sub_full_product_info_optionals ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_full_product_info_optionals (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_full_product_info_optionals"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_full_product_info_optionals"; }
    
    

    

    
    
    
    

    // fields
    bool                                      initialized; 
    mtk::msg::sub_product_code                product_code; 
    mtk::nullable<sub_best_prices>            best_prices; 
    mtk::nullable<sub_additional_info>        additional_info; 
    mtk::nullable<sub_last_mk_execs_ticker>   last_mk_execs_ticker; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_full_product_info_optionals__qpid_map
        {
        public:
            explicit  sub_full_product_info_optionals__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_full_product_info_optionals__qpid_map ( const sub_full_product_info_optionals&  c ) : m_static(c) {}
            explicit  sub_full_product_info_optionals__qpid_map (    const bool&  _initialized,   const mtk::msg::sub_product_code&  _product_code );
            ~sub_full_product_info_optionals__qpid_map() {};
            

            sub_full_product_info_optionals                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      req_product_info
//-------------------------------    
class req_product_info     
{
public:
    //  inner classes

    
    // constructor
    explicit req_product_info (    const mtk::msg::sub_request_info&  _request_info,   const mtk::msg::sub_product_code&  _product_code );
    explicit req_product_info ( const qpid::types::Variant::Map&  mv );
    virtual ~req_product_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_product_info"; }
    static  std::string static_get_message_type_as_string(void)        { return "req_product_info"; }
    
    static  int         static_return_message_RT_priority(void)        { return 1; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 
    mtk::msg::sub_product_code                product_code; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& request_info_process_info_location_broker_code,const std::string& product_code_market);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class req_product_info__qpid_map
        {
        public:
            explicit  req_product_info__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  req_product_info__qpid_map ( const req_product_info&  c ) : m_static(c) {}
            explicit  req_product_info__qpid_map (    const mtk::msg::sub_request_info&  _request_info,   const mtk::msg::sub_product_code&  _product_code );
            ~req_product_info__qpid_map() {};
            

            req_product_info                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  req_product_info::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  req_product_info::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  req_product_info::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  req_product_info::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      res_product_info
//-------------------------------    
class res_product_info     
{
public:
    //  inner classes

    
    //-------------------------------
    //      IC_response
    //-------------------------------    
    class IC_response     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit IC_response (    const sub_full_product_info&  _full_product_info );
        explicit IC_response ( const qpid::types::Variant::Map&  mv );
        virtual ~IC_response (){};
        virtual std::string get_message_type_as_string       (void) const  { return "IC_response"; }
        static  std::string static_get_message_type_as_string(void)        { return "IC_response"; }
        
        
    
        
    
        
        
        
        
    
        // fields
        sub_full_product_info                     full_product_info; 
    
    
    
        //  ADDRESS info
    
    
    
        //  subject info
        
    
        
        
        
        
        void        before_send(void) const;
        
        void check_recomended(void) const;
    };
    
    
    
    
    // constructor
    explicit res_product_info (    const mtk::msg::sub_r_response&  _response_info,   const res_product_info::IC_response&  _response );
    explicit res_product_info ( const qpid::types::Variant::Map&  mv );
    virtual ~res_product_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "res_product_info"; }
    static  std::string static_get_message_type_as_string(void)        { return "res_product_info"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_r_response                  response_info; 
    IC_response                               response; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& response_info_request_info_process_info_location_broker_code,const std::string& response_info_request_info_process_info_location_machine,const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_session_id,const std::string& response_info_request_info_req_id_req_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class res_product_info__qpid_map
        {
        public:
            explicit  res_product_info__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  res_product_info__qpid_map ( const res_product_info&  c ) : m_static(c) {}
            explicit  res_product_info__qpid_map (    const mtk::msg::sub_r_response&  _response_info,   const res_product_info::IC_response&  _response );
            ~res_product_info__qpid_map() {};
            

            res_product_info                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  res_product_info::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  res_product_info::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  res_product_info::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  res_product_info::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      ppc
//-------------------------------    
class ppc     
{
public:
    //  inner classes

    
    // constructor
    explicit ppc (    const std::string&  _market,   const std::string&  _product,   const std::string&  _compacted_data,   const std::string&  _key,   const mtk::DateTime&  _datetime );
    explicit ppc ( const qpid::types::Variant::Map&  mv );
    virtual ~ppc (){};
    virtual std::string get_message_type_as_string       (void) const  { return "ppc"; }
    static  std::string static_get_message_type_as_string(void)        { return "ppc"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               market; 
    std::string                               product; 
    std::string                               compacted_data; 
    std::string                               key; 
    mtk::DateTime                             datetime; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address (const std::string& market);
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& product);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class ppc__qpid_map
        {
        public:
            explicit  ppc__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  ppc__qpid_map ( const ppc&  c ) : m_static(c) {}
            explicit  ppc__qpid_map (    const std::string&  _market,   const std::string&  _product,   const std::string&  _compacted_data,   const std::string&  _key,   const mtk::DateTime&  _datetime );
            ~ppc__qpid_map() {};
            

            ppc                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address (const std::string& market)  {  return  ppc::static_get_qpid_address(market);  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  ppc::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  ppc::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  ppc::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      sub_last_exec_info
//-------------------------------    
class sub_last_exec_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_last_exec_info (    const mtk::FixedNumber&  _price,   const mtk::FixedNumber&  _quantity,   const mtk::DateTime&  _datetime );
    explicit sub_last_exec_info ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_last_exec_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_last_exec_info"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_last_exec_info"; }
    
    

    

    
    
    
    

    // fields
    mtk::FixedNumber                          price; 
    mtk::FixedNumber                          quantity; 
    mtk::DateTime                             datetime; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_last_exec_info__qpid_map
        {
        public:
            explicit  sub_last_exec_info__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_last_exec_info__qpid_map ( const sub_last_exec_info&  c ) : m_static(c) {}
            explicit  sub_last_exec_info__qpid_map (    const mtk::FixedNumber&  _price,   const mtk::FixedNumber&  _quantity,   const mtk::DateTime&  _datetime );
            ~sub_last_exec_info__qpid_map() {};
            

            sub_last_exec_info                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_last_mk__ALL__execs_ticker
//-------------------------------    
class pub_last_mk__ALL__execs_ticker     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_last_mk__ALL__execs_ticker (    const mtk::msg::sub_product_code&  _product_code,   const mtk::list<sub_last_exec_info >&  _last_execs,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
    explicit pub_last_mk__ALL__execs_ticker ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_last_mk__ALL__execs_ticker (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_last_mk__ALL__execs_ticker"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_last_mk__ALL__execs_ticker"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_product_code                product_code; 
    mtk::list<sub_last_exec_info >            last_execs; 
    mtk::msg::sub_control_fluct               orig_control_fluct; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address (const std::string& product_code_market);
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& product_code_market,const std::string& product_code_product);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_last_mk__ALL__execs_ticker__qpid_map
        {
        public:
            explicit  pub_last_mk__ALL__execs_ticker__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_last_mk__ALL__execs_ticker__qpid_map ( const pub_last_mk__ALL__execs_ticker&  c ) : m_static(c) {}
            explicit  pub_last_mk__ALL__execs_ticker__qpid_map (    const mtk::msg::sub_product_code&  _product_code,   const mtk::list<sub_last_exec_info >&  _last_execs,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
            ~pub_last_mk__ALL__execs_ticker__qpid_map() {};
            

            pub_last_mk__ALL__execs_ticker                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address (const std::string& product_code_market)  {  return  pub_last_mk__ALL__execs_ticker::static_get_qpid_address(product_code_market);  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_last_mk__ALL__execs_ticker::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_last_mk__ALL__execs_ticker::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_last_mk__ALL__execs_ticker::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      plaet
//-------------------------------    
class plaet     
{
public:
    //  inner classes

    
    // constructor
    explicit plaet (    const std::string&  _market,   const std::string&  _product,   const std::string&  _compacted_data,   const std::string&  _key,   const mtk::DateTime&  _datetime );
    explicit plaet ( const qpid::types::Variant::Map&  mv );
    virtual ~plaet (){};
    virtual std::string get_message_type_as_string       (void) const  { return "plaet"; }
    static  std::string static_get_message_type_as_string(void)        { return "plaet"; }
    
    static  int         static_return_message_RT_priority(void)        { return 0; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               market; 
    std::string                               product; 
    std::string                               compacted_data; 
    std::string                               key; 
    mtk::DateTime                             datetime; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address (const std::string& market);
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& product);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class plaet__qpid_map
        {
        public:
            explicit  plaet__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  plaet__qpid_map ( const plaet&  c ) : m_static(c) {}
            explicit  plaet__qpid_map (    const std::string&  _market,   const std::string&  _product,   const std::string&  _compacted_data,   const std::string&  _key,   const mtk::DateTime&  _datetime );
            ~plaet__qpid_map() {};
            

            plaet                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address (const std::string& market)  {  return  plaet::static_get_qpid_address(market);  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  plaet::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  plaet::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  plaet::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        
    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_price_level & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_price_level & c);
   void           operator >> (const YAML::Node& n,       sub_price_level & c);

bool operator== (const sub_price_level& a, const sub_price_level& b);
bool operator!= (const sub_price_level& a, const sub_price_level& b);

    std::ostream& operator<< (std::ostream& o, const sub_price_deph5 & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_price_deph5 & c);
   void           operator >> (const YAML::Node& n,       sub_price_deph5 & c);

bool operator== (const sub_price_deph5& a, const sub_price_deph5& b);
bool operator!= (const sub_price_deph5& a, const sub_price_deph5& b);

    std::ostream& operator<< (std::ostream& o, const sub_best_prices & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_best_prices & c);
   void           operator >> (const YAML::Node& n,       sub_best_prices & c);

bool operator== (const sub_best_prices& a, const sub_best_prices& b);
bool operator!= (const sub_best_prices& a, const sub_best_prices& b);

    std::ostream& operator<< (std::ostream& o, const pub_best_prices & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_best_prices & c);
   void           operator >> (const YAML::Node& n,       pub_best_prices & c);

bool operator== (const pub_best_prices& a, const pub_best_prices& b);
bool operator!= (const pub_best_prices& a, const pub_best_prices& b);

    std::ostream& operator<< (std::ostream& o, const pub_new_products & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_new_products & c);
   void           operator >> (const YAML::Node& n,       pub_new_products & c);

bool operator== (const pub_new_products& a, const pub_new_products& b);
bool operator!= (const pub_new_products& a, const pub_new_products& b);

    std::ostream& operator<< (std::ostream& o, const sub_future_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_future_info & c);
   void           operator >> (const YAML::Node& n,       sub_future_info & c);

bool operator== (const sub_future_info& a, const sub_future_info& b);
bool operator!= (const sub_future_info& a, const sub_future_info& b);

    std::ostream& operator<< (std::ostream& o, const sub_option_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_option_info & c);
   void           operator >> (const YAML::Node& n,       sub_option_info & c);

bool operator== (const sub_option_info& a, const sub_option_info& b);
bool operator!= (const sub_option_info& a, const sub_option_info& b);

    std::ostream& operator<< (std::ostream& o, const sub_additional_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_additional_info & c);
   void           operator >> (const YAML::Node& n,       sub_additional_info & c);

bool operator== (const sub_additional_info& a, const sub_additional_info& b);
bool operator!= (const sub_additional_info& a, const sub_additional_info& b);

    std::ostream& operator<< (std::ostream& o, const sub_last_mk_execs_ticker & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_last_mk_execs_ticker & c);
   void           operator >> (const YAML::Node& n,       sub_last_mk_execs_ticker & c);

bool operator== (const sub_last_mk_execs_ticker& a, const sub_last_mk_execs_ticker& b);
bool operator!= (const sub_last_mk_execs_ticker& a, const sub_last_mk_execs_ticker& b);

    std::ostream& operator<< (std::ostream& o, const pub_last_mk_execs_ticker & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_last_mk_execs_ticker & c);
   void           operator >> (const YAML::Node& n,       pub_last_mk_execs_ticker & c);

bool operator== (const pub_last_mk_execs_ticker& a, const pub_last_mk_execs_ticker& b);
bool operator!= (const pub_last_mk_execs_ticker& a, const pub_last_mk_execs_ticker& b);

    std::ostream& operator<< (std::ostream& o, const pub_additional_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_additional_info & c);
   void           operator >> (const YAML::Node& n,       pub_additional_info & c);

bool operator== (const pub_additional_info& a, const pub_additional_info& b);
bool operator!= (const pub_additional_info& a, const pub_additional_info& b);

    std::ostream& operator<< (std::ostream& o, const sub_full_product_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_full_product_info & c);
   void           operator >> (const YAML::Node& n,       sub_full_product_info & c);

bool operator== (const sub_full_product_info& a, const sub_full_product_info& b);
bool operator!= (const sub_full_product_info& a, const sub_full_product_info& b);

    std::ostream& operator<< (std::ostream& o, const sub_full_product_info_optionals & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_full_product_info_optionals & c);
   void           operator >> (const YAML::Node& n,       sub_full_product_info_optionals & c);

bool operator== (const sub_full_product_info_optionals& a, const sub_full_product_info_optionals& b);
bool operator!= (const sub_full_product_info_optionals& a, const sub_full_product_info_optionals& b);

    std::ostream& operator<< (std::ostream& o, const req_product_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const req_product_info & c);
   void           operator >> (const YAML::Node& n,       req_product_info & c);

bool operator== (const req_product_info& a, const req_product_info& b);
bool operator!= (const req_product_info& a, const req_product_info& b);

    std::ostream& operator<< (std::ostream& o, const res_product_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const res_product_info & c);
   void           operator >> (const YAML::Node& n,       res_product_info & c);

bool operator== (const res_product_info::IC_response& a, const res_product_info::IC_response& b);
bool operator!= (const res_product_info::IC_response& a, const res_product_info::IC_response& b);


bool operator== (const res_product_info& a, const res_product_info& b);
bool operator!= (const res_product_info& a, const res_product_info& b);

    std::ostream& operator<< (std::ostream& o, const res_product_info::IC_response & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const res_product_info::IC_response & c);
   void           operator >> (const YAML::Node& n,       res_product_info::IC_response & c);

bool operator== (const res_product_info::IC_response& a, const res_product_info::IC_response& b);
bool operator!= (const res_product_info::IC_response& a, const res_product_info::IC_response& b);

    std::ostream& operator<< (std::ostream& o, const ppc & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const ppc & c);
   void           operator >> (const YAML::Node& n,       ppc & c);

bool operator== (const ppc& a, const ppc& b);
bool operator!= (const ppc& a, const ppc& b);

    std::ostream& operator<< (std::ostream& o, const sub_last_exec_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_last_exec_info & c);
   void           operator >> (const YAML::Node& n,       sub_last_exec_info & c);

bool operator== (const sub_last_exec_info& a, const sub_last_exec_info& b);
bool operator!= (const sub_last_exec_info& a, const sub_last_exec_info& b);

    std::ostream& operator<< (std::ostream& o, const pub_last_mk__ALL__execs_ticker & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_last_mk__ALL__execs_ticker & c);
   void           operator >> (const YAML::Node& n,       pub_last_mk__ALL__execs_ticker & c);

bool operator== (const pub_last_mk__ALL__execs_ticker& a, const pub_last_mk__ALL__execs_ticker& b);
bool operator!= (const pub_last_mk__ALL__execs_ticker& a, const pub_last_mk__ALL__execs_ticker& b);

    std::ostream& operator<< (std::ostream& o, const plaet & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const plaet & c);
   void           operator >> (const YAML::Node& n,       plaet & c);

bool operator== (const plaet& a, const plaet& b);
bool operator!= (const plaet& a, const plaet& b);

void __internal_add2map (qpid::types::Variant::Map& map, const sub_price_level& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_price_level>& a, const std::string& field);
void copy (sub_price_level& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_price_deph5& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_price_deph5>& a, const std::string& field);
void copy (sub_price_deph5& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_best_prices& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_best_prices>& a, const std::string& field);
void copy (sub_best_prices& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_best_prices& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_best_prices>& a, const std::string& field);
void copy (pub_best_prices& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_new_products& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_new_products>& a, const std::string& field);
void copy (pub_new_products& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_future_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_future_info>& a, const std::string& field);
void copy (sub_future_info& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_option_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_option_info>& a, const std::string& field);
void copy (sub_option_info& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_additional_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_additional_info>& a, const std::string& field);
void copy (sub_additional_info& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_last_mk_execs_ticker& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_last_mk_execs_ticker>& a, const std::string& field);
void copy (sub_last_mk_execs_ticker& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_last_mk_execs_ticker& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_last_mk_execs_ticker>& a, const std::string& field);
void copy (pub_last_mk_execs_ticker& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_additional_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_additional_info>& a, const std::string& field);
void copy (pub_additional_info& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_full_product_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_full_product_info>& a, const std::string& field);
void copy (sub_full_product_info& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_full_product_info_optionals& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_full_product_info_optionals>& a, const std::string& field);
void copy (sub_full_product_info_optionals& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const req_product_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_product_info>& a, const std::string& field);
void copy (req_product_info& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const res_product_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_product_info>& a, const std::string& field);
void copy (res_product_info& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const res_product_info::IC_response& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_product_info::IC_response>& a, const std::string& field);
void copy (res_product_info::IC_response& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const ppc& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ppc>& a, const std::string& field);
void copy (ppc& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_last_exec_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_last_exec_info>& a, const std::string& field);
void copy (sub_last_exec_info& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_last_mk__ALL__execs_ticker& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_last_mk__ALL__execs_ticker>& a, const std::string& field);
void copy (pub_last_mk__ALL__execs_ticker& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const plaet& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<plaet>& a, const std::string& field);
void copy (plaet& a, const qpid::types::Variant& map);

    
    
    
//  fordward declarations  dynamic--------------------------------------------------------


inline std::ostream& operator<< (std::ostream& o, const sub_price_level__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_price_level__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_price_level__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_price_level__qpid_map& a, const sub_price_level__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_price_level__qpid_map& a, const sub_price_level__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_price_level__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_price_level__qpid_map>& a, const std::string& field);
void copy (sub_price_level__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_price_deph5__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_price_deph5__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_price_deph5__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_price_deph5__qpid_map& a, const sub_price_deph5__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_price_deph5__qpid_map& a, const sub_price_deph5__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_price_deph5__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_price_deph5__qpid_map>& a, const std::string& field);
void copy (sub_price_deph5__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_best_prices__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_best_prices__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_best_prices__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_best_prices__qpid_map& a, const sub_best_prices__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_best_prices__qpid_map& a, const sub_best_prices__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_best_prices__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_best_prices__qpid_map>& a, const std::string& field);
void copy (sub_best_prices__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_best_prices__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_best_prices__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_best_prices__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_best_prices__qpid_map& a, const pub_best_prices__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_best_prices__qpid_map& a, const pub_best_prices__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_best_prices__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_best_prices__qpid_map>& a, const std::string& field);
void copy (pub_best_prices__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_new_products__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_new_products__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_new_products__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_new_products__qpid_map& a, const pub_new_products__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_new_products__qpid_map& a, const pub_new_products__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_new_products__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_new_products__qpid_map>& a, const std::string& field);
void copy (pub_new_products__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_future_info__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_future_info__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_future_info__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_future_info__qpid_map& a, const sub_future_info__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_future_info__qpid_map& a, const sub_future_info__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_future_info__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_future_info__qpid_map>& a, const std::string& field);
void copy (sub_future_info__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_option_info__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_option_info__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_option_info__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_option_info__qpid_map& a, const sub_option_info__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_option_info__qpid_map& a, const sub_option_info__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_option_info__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_option_info__qpid_map>& a, const std::string& field);
void copy (sub_option_info__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_additional_info__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_additional_info__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_additional_info__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_additional_info__qpid_map& a, const sub_additional_info__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_additional_info__qpid_map& a, const sub_additional_info__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_additional_info__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_additional_info__qpid_map>& a, const std::string& field);
void copy (sub_additional_info__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_last_mk_execs_ticker__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_last_mk_execs_ticker__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_last_mk_execs_ticker__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_last_mk_execs_ticker__qpid_map& a, const sub_last_mk_execs_ticker__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_last_mk_execs_ticker__qpid_map& a, const sub_last_mk_execs_ticker__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_last_mk_execs_ticker__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_last_mk_execs_ticker__qpid_map>& a, const std::string& field);
void copy (sub_last_mk_execs_ticker__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_last_mk_execs_ticker__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_last_mk_execs_ticker__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_last_mk_execs_ticker__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_last_mk_execs_ticker__qpid_map& a, const pub_last_mk_execs_ticker__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_last_mk_execs_ticker__qpid_map& a, const pub_last_mk_execs_ticker__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_last_mk_execs_ticker__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_last_mk_execs_ticker__qpid_map>& a, const std::string& field);
void copy (pub_last_mk_execs_ticker__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_additional_info__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_additional_info__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_additional_info__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_additional_info__qpid_map& a, const pub_additional_info__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_additional_info__qpid_map& a, const pub_additional_info__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_additional_info__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_additional_info__qpid_map>& a, const std::string& field);
void copy (pub_additional_info__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_full_product_info__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_full_product_info__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_full_product_info__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_full_product_info__qpid_map& a, const sub_full_product_info__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_full_product_info__qpid_map& a, const sub_full_product_info__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_full_product_info__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_full_product_info__qpid_map>& a, const std::string& field);
void copy (sub_full_product_info__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_full_product_info_optionals__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_full_product_info_optionals__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_full_product_info_optionals__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_full_product_info_optionals__qpid_map& a, const sub_full_product_info_optionals__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_full_product_info_optionals__qpid_map& a, const sub_full_product_info_optionals__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_full_product_info_optionals__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_full_product_info_optionals__qpid_map>& a, const std::string& field);
void copy (sub_full_product_info_optionals__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const req_product_info__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const req_product_info__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       req_product_info__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const req_product_info__qpid_map& a, const req_product_info__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const req_product_info__qpid_map& a, const req_product_info__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const req_product_info__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_product_info__qpid_map>& a, const std::string& field);
void copy (req_product_info__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const res_product_info__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const res_product_info__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       res_product_info__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const res_product_info__qpid_map& a, const res_product_info__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const res_product_info__qpid_map& a, const res_product_info__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const res_product_info__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_product_info__qpid_map>& a, const std::string& field);
void copy (res_product_info__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const ppc__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const ppc__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       ppc__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const ppc__qpid_map& a, const ppc__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const ppc__qpid_map& a, const ppc__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const ppc__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ppc__qpid_map>& a, const std::string& field);
void copy (ppc__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const sub_last_exec_info__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_last_exec_info__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_last_exec_info__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_last_exec_info__qpid_map& a, const sub_last_exec_info__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_last_exec_info__qpid_map& a, const sub_last_exec_info__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_last_exec_info__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_last_exec_info__qpid_map>& a, const std::string& field);
void copy (sub_last_exec_info__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_last_mk__ALL__execs_ticker__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_last_mk__ALL__execs_ticker__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_last_mk__ALL__execs_ticker__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_last_mk__ALL__execs_ticker__qpid_map& a, const pub_last_mk__ALL__execs_ticker__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_last_mk__ALL__execs_ticker__qpid_map& a, const pub_last_mk__ALL__execs_ticker__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_last_mk__ALL__execs_ticker__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_last_mk__ALL__execs_ticker__qpid_map>& a, const std::string& field);
void copy (pub_last_mk__ALL__execs_ticker__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const plaet__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const plaet__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       plaet__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const plaet__qpid_map& a, const plaet__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const plaet__qpid_map& a, const plaet__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const plaet__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<plaet__qpid_map>& a, const std::string& field);
void copy (plaet__qpid_map& a, const qpid::types::Variant& map);

    sub_price_level  __internal_get_default(sub_price_level *);
    
        inline sub_price_level__qpid_map  __internal_get_default(sub_price_level__qpid_map *) { return  sub_price_level__qpid_map(__internal_get_default((sub_price_level*)0));  }

    sub_price_deph5  __internal_get_default(sub_price_deph5 *);
    
        inline sub_price_deph5__qpid_map  __internal_get_default(sub_price_deph5__qpid_map *) { return  sub_price_deph5__qpid_map(__internal_get_default((sub_price_deph5*)0));  }

    sub_best_prices  __internal_get_default(sub_best_prices *);
    
        inline sub_best_prices__qpid_map  __internal_get_default(sub_best_prices__qpid_map *) { return  sub_best_prices__qpid_map(__internal_get_default((sub_best_prices*)0));  }

    pub_best_prices  __internal_get_default(pub_best_prices *);
    
        inline pub_best_prices__qpid_map  __internal_get_default(pub_best_prices__qpid_map *) { return  pub_best_prices__qpid_map(__internal_get_default((pub_best_prices*)0));  }

    pub_new_products  __internal_get_default(pub_new_products *);
    
        inline pub_new_products__qpid_map  __internal_get_default(pub_new_products__qpid_map *) { return  pub_new_products__qpid_map(__internal_get_default((pub_new_products*)0));  }

    sub_future_info  __internal_get_default(sub_future_info *);
    
        inline sub_future_info__qpid_map  __internal_get_default(sub_future_info__qpid_map *) { return  sub_future_info__qpid_map(__internal_get_default((sub_future_info*)0));  }

    sub_option_info  __internal_get_default(sub_option_info *);
    
        inline sub_option_info__qpid_map  __internal_get_default(sub_option_info__qpid_map *) { return  sub_option_info__qpid_map(__internal_get_default((sub_option_info*)0));  }

    sub_additional_info  __internal_get_default(sub_additional_info *);
    
        inline sub_additional_info__qpid_map  __internal_get_default(sub_additional_info__qpid_map *) { return  sub_additional_info__qpid_map(__internal_get_default((sub_additional_info*)0));  }

    sub_last_mk_execs_ticker  __internal_get_default(sub_last_mk_execs_ticker *);
    
        inline sub_last_mk_execs_ticker__qpid_map  __internal_get_default(sub_last_mk_execs_ticker__qpid_map *) { return  sub_last_mk_execs_ticker__qpid_map(__internal_get_default((sub_last_mk_execs_ticker*)0));  }

    pub_last_mk_execs_ticker  __internal_get_default(pub_last_mk_execs_ticker *);
    
        inline pub_last_mk_execs_ticker__qpid_map  __internal_get_default(pub_last_mk_execs_ticker__qpid_map *) { return  pub_last_mk_execs_ticker__qpid_map(__internal_get_default((pub_last_mk_execs_ticker*)0));  }

    pub_additional_info  __internal_get_default(pub_additional_info *);
    
        inline pub_additional_info__qpid_map  __internal_get_default(pub_additional_info__qpid_map *) { return  pub_additional_info__qpid_map(__internal_get_default((pub_additional_info*)0));  }

    sub_full_product_info  __internal_get_default(sub_full_product_info *);
    
        inline sub_full_product_info__qpid_map  __internal_get_default(sub_full_product_info__qpid_map *) { return  sub_full_product_info__qpid_map(__internal_get_default((sub_full_product_info*)0));  }

    sub_full_product_info_optionals  __internal_get_default(sub_full_product_info_optionals *);
    
        inline sub_full_product_info_optionals__qpid_map  __internal_get_default(sub_full_product_info_optionals__qpid_map *) { return  sub_full_product_info_optionals__qpid_map(__internal_get_default((sub_full_product_info_optionals*)0));  }

    req_product_info  __internal_get_default(req_product_info *);
    
        inline req_product_info__qpid_map  __internal_get_default(req_product_info__qpid_map *) { return  req_product_info__qpid_map(__internal_get_default((req_product_info*)0));  }

    res_product_info  __internal_get_default(res_product_info *);
    
        inline res_product_info__qpid_map  __internal_get_default(res_product_info__qpid_map *) { return  res_product_info__qpid_map(__internal_get_default((res_product_info*)0));  }

    res_product_info::IC_response  __internal_get_default(res_product_info::IC_response *);
    
    ppc  __internal_get_default(ppc *);
    
        inline ppc__qpid_map  __internal_get_default(ppc__qpid_map *) { return  ppc__qpid_map(__internal_get_default((ppc*)0));  }

    sub_last_exec_info  __internal_get_default(sub_last_exec_info *);
    
        inline sub_last_exec_info__qpid_map  __internal_get_default(sub_last_exec_info__qpid_map *) { return  sub_last_exec_info__qpid_map(__internal_get_default((sub_last_exec_info*)0));  }

    pub_last_mk__ALL__execs_ticker  __internal_get_default(pub_last_mk__ALL__execs_ticker *);
    
        inline pub_last_mk__ALL__execs_ticker__qpid_map  __internal_get_default(pub_last_mk__ALL__execs_ticker__qpid_map *) { return  pub_last_mk__ALL__execs_ticker__qpid_map(__internal_get_default((pub_last_mk__ALL__execs_ticker*)0));  }

    plaet  __internal_get_default(plaet *);
    
        inline plaet__qpid_map  __internal_get_default(plaet__qpid_map *) { return  plaet__qpid_map(__internal_get_default((plaet*)0));  }


};   //namespace mtk {
};   //namespace prices {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::pub_best_prices)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::pub_best_prices__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::pub_new_products)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::pub_new_products__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::pub_last_mk_execs_ticker)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::pub_last_mk_execs_ticker__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::pub_additional_info)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::pub_additional_info__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::req_product_info)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::req_product_info__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::res_product_info)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::res_product_info__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::ppc)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::ppc__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::pub_last_mk__ALL__execs_ticker)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::pub_last_mk__ALL__execs_ticker__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::plaet)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::plaet__qpid_map)




#endif
