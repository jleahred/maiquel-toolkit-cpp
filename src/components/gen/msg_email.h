
#ifndef  __msg_email__
#define  __msg_email__


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


#include "support/mtk_string.h"

namespace mtk { 
namespace gen { 
namespace msg { 




//-------------------------------
//      pub_email
//-------------------------------    
class pub_email     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_email (    const std::string&  _eto,   const std::string&  _esubject,   const std::string&  _emessage );
    explicit pub_email ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_email (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_email"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_email"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               eto; 
    std::string                               esubject; 
    std::string                               emessage; 



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
        class pub_email__qpid_map
        {
        public:
            explicit  pub_email__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_email__qpid_map ( const pub_email&  c ) : m_static(c) {}
            explicit  pub_email__qpid_map (    const std::string&  _eto,   const std::string&  _esubject,   const std::string&  _emessage );
            ~pub_email__qpid_map() {};
            

            pub_email                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  pub_email::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_email::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_email::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_email::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        
    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const pub_email & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_email & c);
   void           operator >> (const YAML::Node& n,       pub_email & c);

bool operator== (const pub_email& a, const pub_email& b);
bool operator!= (const pub_email& a, const pub_email& b);

void __internal_add2map (qpid::types::Variant::Map& map, const pub_email& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_email>& a, const std::string& field);
void copy (pub_email& a, const qpid::types::Variant& map);

    
    
    
//  fordward declarations  dynamic--------------------------------------------------------


inline std::ostream& operator<< (std::ostream& o, const pub_email__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_email__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_email__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_email__qpid_map& a, const pub_email__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_email__qpid_map& a, const pub_email__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_email__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_email__qpid_map>& a, const std::string& field);
void copy (pub_email__qpid_map& a, const qpid::types::Variant& map);

    pub_email  __internal_get_default(pub_email *);
    
        inline pub_email__qpid_map  __internal_get_default(pub_email__qpid_map *) { return  pub_email__qpid_map(__internal_get_default((pub_email*)0));  }


};   //namespace mtk {
};   //namespace gen {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::gen::msg::pub_email)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::gen::msg::pub_email__qpid_map)




#endif
