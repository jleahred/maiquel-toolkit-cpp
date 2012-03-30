
#ifndef  __msg_prodinfo_grant_db__
#define  __msg_prodinfo_grant_db__


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

namespace prodinfo_grant { 
namespace db { 
namespace msg { 




//-------------------------------
//      sub_pattern_users_grants
//-------------------------------    
class sub_pattern_users_grants     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_pattern_users_grants (    const std::string&  _user_pattern,   const mtk::list<mtk::msg::sub_product_code >&  _re_product_code_list,   const mtk::DateTime&  _last_applied_rule );
    explicit sub_pattern_users_grants ( const qpid::messaging::Message& message );
    virtual ~sub_pattern_users_grants (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_pattern_users_grants"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_pattern_users_grants"; };

    
    
    
    

    // fields
    std::string                               user_pattern; 
    mtk::list<mtk::msg::sub_product_code >    re_product_code_list; 
    mtk::DateTime                             last_applied_rule; 




    //   KEY INFO
        typedef decltype(user_pattern) key_type;
        key_type    get_key(void) const  {   return  user_pattern;  }
    //   KEY INFO


    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      sub_client__pattern_users
//-------------------------------    
class sub_client__pattern_users     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_client__pattern_users (    const std::string&  _client_code,   const mtk::list<sub_pattern_users_grants >&  _users_pattern );
    explicit sub_client__pattern_users ( const qpid::messaging::Message& message );
    virtual ~sub_client__pattern_users (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_client__pattern_users"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_client__pattern_users"; };

    
    
    
    

    // fields
    std::string                               client_code; 
    mtk::list<sub_pattern_users_grants >      users_pattern; 




    //   KEY INFO
        typedef decltype(client_code) key_type;
        key_type    get_key(void) const  {   return  client_code;  }
    //   KEY INFO


    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_pattern_users_grants & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_pattern_users_grants & c);
   void           operator >> (const YAML::Node& n,       sub_pattern_users_grants & c);

bool operator== (const sub_pattern_users_grants& a, const sub_pattern_users_grants& b);
bool operator!= (const sub_pattern_users_grants& a, const sub_pattern_users_grants& b);

    std::ostream& operator<< (std::ostream& o, const sub_client__pattern_users & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_client__pattern_users & c);
   void           operator >> (const YAML::Node& n,       sub_client__pattern_users & c);

bool operator== (const sub_client__pattern_users& a, const sub_client__pattern_users& b);
bool operator!= (const sub_client__pattern_users& a, const sub_client__pattern_users& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_pattern_users_grants& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_pattern_users_grants& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_pattern_users_grants>& a, const std::string& field);
void copy (sub_pattern_users_grants& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_client__pattern_users& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_client__pattern_users& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_client__pattern_users>& a, const std::string& field);
void copy (sub_client__pattern_users& a, const qpid::types::Variant& map);

    sub_pattern_users_grants  __internal_get_default(sub_pattern_users_grants *);
    
    sub_client__pattern_users  __internal_get_default(sub_client__pattern_users *);
    

};   //namespace prodinfo_grant {
};   //namespace db {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);






#endif
