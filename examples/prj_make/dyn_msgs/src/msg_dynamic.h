
#ifndef  __msg_dynamic__
#define  __msg_dynamic__


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




namespace testing { 
namespace dynamic { 




//-------------------------------
//      sub_levels
//-------------------------------    
class sub_levels     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_levels (    const mtk::nullable<int32_t>&  _price0,   const mtk::nullable<int32_t>&  _quantity0,   const mtk::nullable<int32_t>&  _price1,   const mtk::nullable<int32_t>&  _quantity1,   const mtk::nullable<int32_t>&  _price2,   const mtk::nullable<int32_t>&  _quantity2,   const mtk::nullable<int32_t>&  _price3,   const mtk::nullable<int32_t>&  _quantity3,   const mtk::nullable<int32_t>&  _price4,   const mtk::nullable<int32_t>&  _quantity4,   const mtk::nullable<int32_t>&  _price5,   const mtk::nullable<int32_t>&  _quantity5 );
    explicit sub_levels ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_levels (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_levels"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_levels"; }
    
    

    

    
    
    
    

    // fields
    mtk::nullable<int32_t>                    price0; 
    mtk::nullable<int32_t>                    quantity0; 
    mtk::nullable<int32_t>                    price1; 
    mtk::nullable<int32_t>                    quantity1; 
    mtk::nullable<int32_t>                    price2; 
    mtk::nullable<int32_t>                    quantity2; 
    mtk::nullable<int32_t>                    price3; 
    mtk::nullable<int32_t>                    quantity3; 
    mtk::nullable<int32_t>                    price4; 
    mtk::nullable<int32_t>                    quantity4; 
    mtk::nullable<int32_t>                    price5; 
    mtk::nullable<int32_t>                    quantity5; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_levels__qpid_map
        {
        public:
            explicit  sub_levels__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_levels__qpid_map ( const sub_levels&  c ) : m_static(c) {}
            explicit  sub_levels__qpid_map (  );
            ~sub_levels__qpid_map() {};
            

            sub_levels                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_dynamic
//-------------------------------    
class pub_dynamic     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_dynamic (    const std::string&  _product_name,   const bool&  _processed,   const mtk::nullable<mtk::DateTime>&  _value_date,   const mtk::nullable<int16_t>&  _num_legs,   const mtk::nullable<std::string>&  _testing,   const mtk::nullable<sub_levels>&  _bids,   const mtk::nullable<sub_levels__qpid_map>&  _asks );
    explicit pub_dynamic ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_dynamic (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_dynamic"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_dynamic"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               product_name; 
    bool                                      processed; 
    mtk::nullable<mtk::DateTime>              value_date; 
    mtk::nullable<int16_t>                    num_legs; 
    mtk::nullable<std::string>                testing; 
    mtk::nullable<sub_levels>                 bids; 
    mtk::nullable<sub_levels__qpid_map>       asks; 



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
        class pub_dynamic__qpid_map
        {
        public:
            explicit  pub_dynamic__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_dynamic__qpid_map ( const pub_dynamic&  c ) : m_static(c) {}
            explicit  pub_dynamic__qpid_map (    const std::string&  _product_name,   const bool&  _processed );
            ~pub_dynamic__qpid_map() {};
            

            pub_dynamic                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  pub_dynamic::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_dynamic::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_dynamic::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_dynamic::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        
    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_levels & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_levels & c);
   void           operator >> (const YAML::Node& n,       sub_levels & c);

bool operator== (const sub_levels& a, const sub_levels& b);
bool operator!= (const sub_levels& a, const sub_levels& b);

    std::ostream& operator<< (std::ostream& o, const pub_dynamic & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_dynamic & c);
   void           operator >> (const YAML::Node& n,       pub_dynamic & c);

bool operator== (const pub_dynamic& a, const pub_dynamic& b);
bool operator!= (const pub_dynamic& a, const pub_dynamic& b);

void __internal_add2map (qpid::types::Variant::Map& map, const sub_levels& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_levels>& a, const std::string& field);
void copy (sub_levels& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_dynamic& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_dynamic>& a, const std::string& field);
void copy (pub_dynamic& a, const qpid::types::Variant& map);

    
    
    
//  fordward declarations  dynamic--------------------------------------------------------


inline std::ostream& operator<< (std::ostream& o, const sub_levels__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_levels__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_levels__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_levels__qpid_map& a, const sub_levels__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_levels__qpid_map& a, const sub_levels__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_levels__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_levels__qpid_map>& a, const std::string& field);
void copy (sub_levels__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_dynamic__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_dynamic__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_dynamic__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_dynamic__qpid_map& a, const pub_dynamic__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_dynamic__qpid_map& a, const pub_dynamic__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_dynamic__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_dynamic__qpid_map>& a, const std::string& field);
void copy (pub_dynamic__qpid_map& a, const qpid::types::Variant& map);

    sub_levels  __internal_get_default(sub_levels *);
    
        inline sub_levels__qpid_map  __internal_get_default(sub_levels__qpid_map *) { return  sub_levels__qpid_map(__internal_get_default((sub_levels*)0));  }

    pub_dynamic  __internal_get_default(pub_dynamic *);
    
        inline pub_dynamic__qpid_map  __internal_get_default(pub_dynamic__qpid_map *) { return  pub_dynamic__qpid_map(__internal_get_default((pub_dynamic*)0));  }


};   //namespace testing {
};   //namespace dynamic {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(testing::dynamic::pub_dynamic)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(testing::dynamic::pub_dynamic__qpid_map)




#endif
