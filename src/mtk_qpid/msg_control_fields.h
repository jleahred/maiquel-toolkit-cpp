
#ifndef  __msg_control_fields__
#define  __msg_control_fields__


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






namespace mtk { 
namespace msg { 




//-------------------------------
//      sub_control_fields
//-------------------------------    
class sub_control_fields     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_control_fields (    const std::string&  _message_type,   const std::string&  _control_fluct_key,   const mtk::DateTime&  _sent_date_time );
    explicit sub_control_fields ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_control_fields (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_control_fields"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_control_fields"; };

    
    
    
    

    // fields
    std::string                               message_type; 
    std::string                               control_fluct_key; 
    mtk::DateTime                             sent_date_time; 



    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_control_fields & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_control_fields & c);
   void           operator >> (const YAML::Node& n,       sub_control_fields & c);

bool operator== (const sub_control_fields& a, const sub_control_fields& b);
bool operator!= (const sub_control_fields& a, const sub_control_fields& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_control_fields& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_control_fields& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_control_fields>& a, const std::string& field);
void copy (sub_control_fields& a, const qpid::types::Variant& map);

    sub_control_fields  __internal_get_default(sub_control_fields *);
    

};   //namespace mtk {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);






#endif
