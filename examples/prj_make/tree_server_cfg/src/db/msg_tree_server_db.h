
#ifndef  __msg_tree_server_db__
#define  __msg_tree_server_db__


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




namespace tree_server2 { 
namespace msg { 




//-------------------------------
//      sub_path_grants
//-------------------------------    
class sub_path_grants     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_path_grants (    const std::string&  _re_path,   const mtk::list<std::string >&  _users );
    explicit sub_path_grants ( const qpid::messaging::Message& message );
    virtual ~sub_path_grants (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_path_grants"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_path_grants"; };

    
    
    
    

    // fields
    std::string                               re_path; 
    mtk::list<std::string >                   users; 




    //   KEY INFO
        typedef decltype(re_path) key_type;
        key_type    get_key(void) const  {   return  re_path;  }
    //   KEY INFO


    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_path_grants & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_path_grants & c);
   void           operator >> (const YAML::Node& n,       sub_path_grants & c);

bool operator== (const sub_path_grants& a, const sub_path_grants& b);
bool operator!= (const sub_path_grants& a, const sub_path_grants& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_path_grants& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_path_grants& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_path_grants>& a, const std::string& field);
void copy (sub_path_grants& a, const qpid::types::Variant& map);

    sub_path_grants  __internal_get_default(sub_path_grants *);
    

};   //namespace tree_server2 {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);






#endif
