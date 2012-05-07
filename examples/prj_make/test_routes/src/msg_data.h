
#ifndef  __msg_data__
#define  __msg_data__


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




namespace tr { 




//-------------------------------
//      sub_route
//-------------------------------    
class sub_route     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_route (    const std::string&  _origin,   const std::string&  _dest,   const std::string&  _qe_name,   const std::string&  _subject );
    explicit sub_route ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_route (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_route"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_route"; };
    
    

    

    
    
    
    

    // fields
    std::string                               origin; 
    std::string                               dest; 
    std::string                               qe_name; 
    std::string                               subject; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      sub_ip_names
//-------------------------------    
class sub_ip_names     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_ip_names (    const std::string&  _name,   const std::string&  _ip );
    explicit sub_ip_names ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_ip_names (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_ip_names"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_ip_names"; };
    
    

    

    
    
    
    

    // fields
    std::string                               name; 
    std::string                               ip; 




    //   KEY INFO
        typedef decltype(name) key_type;
        key_type    get_key(void) const  {   return  name;  }
    //   KEY INFO


    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_route & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_route & c);
   void           operator >> (const YAML::Node& n,       sub_route & c);

bool operator== (const sub_route& a, const sub_route& b);
bool operator!= (const sub_route& a, const sub_route& b);

    std::ostream& operator<< (std::ostream& o, const sub_ip_names & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_ip_names & c);
   void           operator >> (const YAML::Node& n,       sub_ip_names & c);

bool operator== (const sub_ip_names& a, const sub_ip_names& b);
bool operator!= (const sub_ip_names& a, const sub_ip_names& b);

void __internal_add2map (qpid::types::Variant::Map& map, const sub_route& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_route>& a, const std::string& field);
void copy (sub_route& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_ip_names& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_ip_names>& a, const std::string& field);
void copy (sub_ip_names& a, const qpid::types::Variant& map);

    sub_route  __internal_get_default(sub_route *);
    
    sub_ip_names  __internal_get_default(sub_ip_names *);
    

};   //namespace tr {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);






#endif
