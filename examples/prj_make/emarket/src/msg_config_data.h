
#ifndef  __msg_config_data__
#define  __msg_config_data__


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




namespace emarket { 




//-------------------------------
//      sub_product_config
//-------------------------------    
class sub_product_config     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_product_config (    const std::string&  _product_name,   const std::string&  _product_user_name,   const std::string&  _group,   const std::string&  _group_user_name,   const mtk::fnExt&  _price_fnext );
    explicit sub_product_config ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_product_config (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_product_config"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_product_config"; }
    
    

    

    
    
    
    

    // fields
    std::string                               product_name; 
    std::string                               product_user_name; 
    std::string                               group; 
    std::string                               group_user_name; 
    mtk::fnExt                                price_fnext; 




    //   KEY INFO
        typedef decltype(product_name) key_type;
        key_type    get_key(void) const  {   return  product_name;  }
    //   KEY INFO


    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_product_config__qpid_map
        {
        public:
            explicit  sub_product_config__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_product_config__qpid_map ( const sub_product_config&  c ) : m_static(c) {}
            explicit  sub_product_config__qpid_map (    const std::string&  _product_name,   const std::string&  _product_user_name,   const std::string&  _group,   const std::string&  _group_user_name,   const mtk::fnExt&  _price_fnext );
            ~sub_product_config__qpid_map() {};
            

            sub_product_config                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        
    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_product_config & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_product_config & c);
   void           operator >> (const YAML::Node& n,       sub_product_config & c);

bool operator== (const sub_product_config& a, const sub_product_config& b);
bool operator!= (const sub_product_config& a, const sub_product_config& b);

void __internal_add2map (qpid::types::Variant::Map& map, const sub_product_config& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_product_config>& a, const std::string& field);
void copy (sub_product_config& a, const qpid::types::Variant& map);

    
    
    
//  fordward declarations  dynamic--------------------------------------------------------


inline std::ostream& operator<< (std::ostream& o, const sub_product_config__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_product_config__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_product_config__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_product_config__qpid_map& a, const sub_product_config__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_product_config__qpid_map& a, const sub_product_config__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_product_config__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_product_config__qpid_map>& a, const std::string& field);
void copy (sub_product_config__qpid_map& a, const qpid::types::Variant& map);

    sub_product_config  __internal_get_default(sub_product_config *);
    
        inline sub_product_config__qpid_map  __internal_get_default(sub_product_config__qpid_map *) { return  sub_product_config__qpid_map(__internal_get_default((sub_product_config*)0));  }


};   //namespace emarket {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);






#endif
