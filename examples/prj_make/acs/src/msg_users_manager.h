
#ifndef  __msg_users_manager__
#define  __msg_users_manager__


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




namespace users_manager { 




//-------------------------------
//      sub_user_info
//-------------------------------    
class sub_user_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_user_info (    const std::string&  _name,   const std::string&  _client_code,   const std::string&  _requested_by,   const std::string&  _notes );
    explicit sub_user_info ( const qpid::messaging::Message& message );
    virtual ~sub_user_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_user_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_user_info"; };

    
    
    
    

    // fields
    std::string                               name; 
    std::string                               client_code; 
    std::string                               requested_by; 
    std::string                               notes; 



    //   KEY INFO
        typedef decltype(name) key_type;
        key_type    get_key(void) const  {   return  name;  }
    //   KEY INFO



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      sub_user_acs_info
//-------------------------------    
class sub_user_acs_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_user_acs_info (    const sub_user_info&  _user_info,   const std::string&  _passwordcrc32,   const mtk::DateTime&  _created_on,   const mtk::DateTime&  _last_access,   const int&  _check_pass_ok,   const int&  _check_pass_wrong );
    explicit sub_user_acs_info ( const qpid::messaging::Message& message );
    virtual ~sub_user_acs_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_user_acs_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_user_acs_info"; };

    
    
    
    

    // fields
    sub_user_info                             user_info; 
    std::string                               passwordcrc32; 
    mtk::DateTime                             created_on; 
    mtk::DateTime                             last_access; 
    int                                       check_pass_ok; 
    int                                       check_pass_wrong; 



    //   KEY INFO
        typedef decltype(user_info.name) key_type;
        key_type    get_key(void) const  {   return  user_info.name;  }
    //   KEY INFO



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_user_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_user_info & c);
   void           operator >> (const YAML::Node& n,       sub_user_info & c);

bool operator== (const sub_user_info& a, const sub_user_info& b);
bool operator!= (const sub_user_info& a, const sub_user_info& b);

    std::ostream& operator<< (std::ostream& o, const sub_user_acs_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_user_acs_info & c);
   void           operator >> (const YAML::Node& n,       sub_user_acs_info & c);

bool operator== (const sub_user_acs_info& a, const sub_user_acs_info& b);
bool operator!= (const sub_user_acs_info& a, const sub_user_acs_info& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_user_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_user_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_user_info>& a, const std::string& field);
void copy (sub_user_info& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_user_acs_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_user_acs_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_user_acs_info>& a, const std::string& field);
void copy (sub_user_acs_info& a, const qpid::types::Variant& map);

    sub_user_info  __internal_get_default(sub_user_info *);
    
    sub_user_acs_info  __internal_get_default(sub_user_acs_info *);
    

};   //namespace users_manager {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);






#endif
