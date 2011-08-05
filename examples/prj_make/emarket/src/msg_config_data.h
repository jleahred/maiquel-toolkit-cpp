
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

#include "mtk_qpid/mtk_qpid.hpp"




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
    explicit sub_product_config ( const qpid::messaging::Message& message );
    virtual ~sub_product_config (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_product_config"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_product_config"; };

    
    
    
    

    // fields
    //   KEY INFO
    std::string                               get_key(void) const  {   return  product_name;  }
    typedef                                   std::string   key_type;
    //   KEY INFO

    std::string                               product_name; 
    std::string                               product_user_name; 
    std::string                               group; 
    std::string                               group_user_name; 
    mtk::fnExt                                price_fnext; 



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_product_config & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_product_config & c);
   void           operator >> (const YAML::Node& n,       sub_product_config & c);

bool operator== (const sub_product_config& a, const sub_product_config& b);
bool operator!= (const sub_product_config& a, const sub_product_config& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_product_config& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_product_config& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_product_config>& a, const std::string& field);
void copy (sub_product_config& a, const qpid::types::Variant& map);

    sub_product_config  __internal_get_default(sub_product_config *);
    

};   //namespace emarket {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);






#endif
