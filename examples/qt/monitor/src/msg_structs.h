
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

#include "mtk_qpid/mtk_qpid.hpp"




namespace mon { 
namespace msg { 




//-------------------------------
//      sub_rule
//-------------------------------    
class sub_rule     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_rule (    const std::string&  _re_rule,   const mtk::dtTimeQuantity&  _frequency,   const int&  _n_received,   const std::string&  _description,   const mtk::dtTimeQuantity&  _start_time,   const mtk::dtTimeQuantity&  _end_time,   const mtk::DateTime&  _last_notified );
    explicit sub_rule ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_rule (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_rule"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_rule"; };

    
    
    
    

    // fields
    std::string                               re_rule; 
    mtk::dtTimeQuantity                       frequency; 
    int                                       n_received; 
    std::string                               description; 
    mtk::dtTimeQuantity                       start_time; 
    mtk::dtTimeQuantity                       end_time; 
    mtk::DateTime                             last_notified; 




    //   KEY INFO
        typedef decltype(re_rule) key_type;
        key_type    get_key(void) const  {   return  re_rule;  }
    //   KEY INFO


    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_rule & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_rule & c);
   void           operator >> (const YAML::Node& n,       sub_rule & c);

bool operator== (const sub_rule& a, const sub_rule& b);
bool operator!= (const sub_rule& a, const sub_rule& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_rule& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_rule& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_rule>& a, const std::string& field);
void copy (sub_rule& a, const qpid::types::Variant& map);

    sub_rule  __internal_get_default(sub_rule *);
    

};   //namespace mon {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);






#endif
