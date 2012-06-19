
#ifndef  __msg_structs__
#define  __msg_structs__


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
#include "components/trading/msg_trd_common.h"
#include "components/trading/accounts/msg_account_manager.h"

namespace accmgr { 
namespace msg { 




//-------------------------------
//      sub_user_info
//-------------------------------    
class sub_user_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_user_info (    const std::string&  _name,   const mtk::DateTime&  _created,   const std::string&  _client_code,   const mtk::list<mtk::trd::account::msg::sub_grant >&  _grant_list );
    explicit sub_user_info ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_user_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_user_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_user_info"; };
    
    

    

    
    
    
    

    // fields
    std::string                               name; 
    mtk::DateTime                             created; 
    std::string                               client_code; 
    mtk::list<mtk::trd::account::msg::sub_grant >  grant_list; 




    //   KEY INFO
        typedef decltype(name) key_type;
        key_type    get_key(void) const  {   return  name;  }
    //   KEY INFO


    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};




//-------------------------------
//      sub_oms_account_info
//-------------------------------    
class sub_oms_account_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_oms_account_info (    const mtk::trd::msg::sub_account_info&  _account,   const std::string&  _oms_additional_info );
    explicit sub_oms_account_info ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_oms_account_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_oms_account_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_oms_account_info"; };
    
    

    

    
    
    
    

    // fields
    mtk::trd::msg::sub_account_info           account; 
    std::string                               oms_additional_info; 




    //   KEY INFO
        typedef decltype(account) key_type;
        key_type    get_key(void) const  {   return  account;  }
    //   KEY INFO


    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_user_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_user_info & c);
   void           operator >> (const YAML::Node& n,       sub_user_info & c);

bool operator== (const sub_user_info& a, const sub_user_info& b);
bool operator!= (const sub_user_info& a, const sub_user_info& b);

    std::ostream& operator<< (std::ostream& o, const sub_oms_account_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_oms_account_info & c);
   void           operator >> (const YAML::Node& n,       sub_oms_account_info & c);

bool operator== (const sub_oms_account_info& a, const sub_oms_account_info& b);
bool operator!= (const sub_oms_account_info& a, const sub_oms_account_info& b);

void __internal_add2map (qpid::types::Variant::Map& map, const sub_user_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_user_info>& a, const std::string& field);
void copy (sub_user_info& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_oms_account_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_oms_account_info>& a, const std::string& field);
void copy (sub_oms_account_info& a, const qpid::types::Variant& map);

    sub_user_info  __internal_get_default(sub_user_info *);
    
    sub_oms_account_info  __internal_get_default(sub_oms_account_info *);
    

};   //namespace accmgr {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);






#endif
