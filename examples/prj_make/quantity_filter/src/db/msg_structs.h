
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




namespace qfmgr { 
namespace msg { 




//-------------------------------
//      sub_product
//-------------------------------    
class sub_product     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_product (    const std::string&  _gen_product_name,   const std::string&  _market,   const std::string&  _re_product_code );
    explicit sub_product ( const qpid::messaging::Message& message );
    virtual ~sub_product (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_product"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_product"; };

    
    
    
    

    // fields
    std::string                               gen_product_name; 
    std::string                               market; 
    std::string                               re_product_code; 



    //   KEY INFO
        typedef decltype(gen_product_name) key_type;
        key_type    get_key(void) const  {   return  gen_product_name;  }
    //   KEY INFO



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      sub_filter_info
//-------------------------------    
class sub_filter_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_filter_info (    const std::string&  _gen_product_name,   const int&  _quantity );
    explicit sub_filter_info ( const qpid::messaging::Message& message );
    virtual ~sub_filter_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_filter_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_filter_info"; };

    
    
    
    

    // fields
    std::string                               gen_product_name; 
    int                                       quantity; 





    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      sub_client_info
//-------------------------------    
class sub_client_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_client_info (    const std::string&  _name,   const mtk::DateTime&  _created,   const mtk::list<sub_filter_info >&  _filter_list );
    explicit sub_client_info ( const qpid::messaging::Message& message );
    virtual ~sub_client_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_client_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_client_info"; };

    
    
    
    

    // fields
    std::string                               name; 
    mtk::DateTime                             created; 
    mtk::list<sub_filter_info >               filter_list; 



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
//      sub_user_info
//-------------------------------    
class sub_user_info     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_user_info (    const std::string&  _name,   const mtk::DateTime&  _created,   const std::string&  _client_code,   const mtk::list<sub_filter_info >&  _filter_list );
    explicit sub_user_info ( const qpid::messaging::Message& message );
    virtual ~sub_user_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_user_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_user_info"; };

    
    
    
    

    // fields
    std::string                               name; 
    mtk::DateTime                             created; 
    std::string                               client_code; 
    mtk::list<sub_filter_info >               filter_list; 



    //   KEY INFO
        typedef decltype(name) key_type;
        key_type    get_key(void) const  {   return  name;  }
    //   KEY INFO



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_product & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_product & c);
   void           operator >> (const YAML::Node& n,       sub_product & c);

bool operator== (const sub_product& a, const sub_product& b);
bool operator!= (const sub_product& a, const sub_product& b);

    std::ostream& operator<< (std::ostream& o, const sub_filter_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_filter_info & c);
   void           operator >> (const YAML::Node& n,       sub_filter_info & c);

bool operator== (const sub_filter_info& a, const sub_filter_info& b);
bool operator!= (const sub_filter_info& a, const sub_filter_info& b);

    std::ostream& operator<< (std::ostream& o, const sub_client_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_client_info & c);
   void           operator >> (const YAML::Node& n,       sub_client_info & c);

bool operator== (const sub_client_info& a, const sub_client_info& b);
bool operator!= (const sub_client_info& a, const sub_client_info& b);

    std::ostream& operator<< (std::ostream& o, const sub_user_info & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_user_info & c);
   void           operator >> (const YAML::Node& n,       sub_user_info & c);

bool operator== (const sub_user_info& a, const sub_user_info& b);
bool operator!= (const sub_user_info& a, const sub_user_info& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_product& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_product& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_product>& a, const std::string& field);
void copy (sub_product& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_filter_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_filter_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_filter_info>& a, const std::string& field);
void copy (sub_filter_info& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_client_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_client_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_client_info>& a, const std::string& field);
void copy (sub_client_info& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_user_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_user_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_user_info>& a, const std::string& field);
void copy (sub_user_info& a, const qpid::types::Variant& map);

    sub_product  __internal_get_default(sub_product *);
    
    sub_filter_info  __internal_get_default(sub_filter_info *);
    
    sub_client_info  __internal_get_default(sub_client_info *);
    
    sub_user_info  __internal_get_default(sub_user_info *);
    

};   //namespace qfmgr {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);






#endif
