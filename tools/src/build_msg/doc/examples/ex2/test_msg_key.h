
#ifndef  __test_msg_key__
#define  __test_msg_key__


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




namespace test { 




//-------------------------------
//      sub_test_key
//-------------------------------    
class sub_test_key     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_test_key (    const std::string&  _name,   const std::string&  _address,   const std::string&  _telephone,   const std::string&  _email );
    explicit sub_test_key ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_test_key (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_test_key"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_test_key"; }
    
    

    

    
    
    
    

    // fields
    std::string                               name; 
    std::string                               address; 
    std::string                               telephone; 
    std::string                               email; 




    //   KEY INFO
        typedef decltype(name) key_type;
        key_type    get_key(void) const  {   return  name;  }
    //   KEY INFO


    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_test_key__qpid_map
        {
        public:
            explicit  sub_test_key__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_test_key__qpid_map ( const sub_test_key&  c ) : m_static(c) {}
            explicit  sub_test_key__qpid_map (    const std::string&  _name,   const std::string&  _address,   const std::string&  _telephone,   const std::string&  _email );
            ~sub_test_key__qpid_map() {};
            

            sub_test_key                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        
    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_test_key & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_test_key & c);
   void           operator >> (const YAML::Node& n,       sub_test_key & c);

bool operator== (const sub_test_key& a, const sub_test_key& b);
bool operator!= (const sub_test_key& a, const sub_test_key& b);

void __internal_add2map (qpid::types::Variant::Map& map, const sub_test_key& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_test_key>& a, const std::string& field);
void copy (sub_test_key& a, const qpid::types::Variant& map);

    
    
    
//  fordward declarations  dynamic--------------------------------------------------------


inline std::ostream& operator<< (std::ostream& o, const sub_test_key__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_test_key__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_test_key__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_test_key__qpid_map& a, const sub_test_key__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_test_key__qpid_map& a, const sub_test_key__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_test_key__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_test_key__qpid_map>& a, const std::string& field);
void copy (sub_test_key__qpid_map& a, const qpid::types::Variant& map);

    sub_test_key  __internal_get_default(sub_test_key *);
    
        inline sub_test_key__qpid_map  __internal_get_default(sub_test_key__qpid_map *) { return  sub_test_key__qpid_map(__internal_get_default((sub_test_key*)0));  }


};   //namespace test {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);






#endif
