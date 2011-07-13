
#ifndef  __msg_trd_oms_rq__
#define  __msg_trd_oms_rq__


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


#include "components/msg_common.h"
#include "msg_trd_common.h"
#include "msg_trd_cli_ls.h"
#include "msg_trd_cli_mk.h"

namespace mtk { 
namespace trd { 
namespace msg { 




//-------------------------------
//      oms_RQ_NW_LS
//-------------------------------    
class oms_RQ_NW_LS        :  public  RQ_NW_LS
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_NW_LS (  const RQ_NW_LS&  parent,   const std::string&  _reject_description );
    explicit oms_RQ_NW_LS ( const qpid::messaging::Message& message );
    virtual ~oms_RQ_NW_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_NW_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_NW_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               reject_description; 



    //  subject info
    static std::string  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_MD_LS
//-------------------------------    
class oms_RQ_MD_LS        :  public  RQ_MD_LS
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_MD_LS (  const RQ_MD_LS&  parent,   const std::string&  _reject_description );
    explicit oms_RQ_MD_LS ( const qpid::messaging::Message& message );
    virtual ~oms_RQ_MD_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_MD_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_MD_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               reject_description; 



    //  subject info
    static std::string  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_CC_LS
//-------------------------------    
class oms_RQ_CC_LS        :  public  RQ_CC_LS
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_CC_LS (  const RQ_CC_LS&  parent,   const std::string&  _reject_description );
    explicit oms_RQ_CC_LS ( const qpid::messaging::Message& message );
    virtual ~oms_RQ_CC_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_CC_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_CC_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               reject_description; 



    //  subject info
    static std::string  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_NW_MK
//-------------------------------    
class oms_RQ_NW_MK        :  public  RQ_NW_MK
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_NW_MK (  const RQ_NW_MK&  parent,   const std::string&  _reject_description );
    explicit oms_RQ_NW_MK ( const qpid::messaging::Message& message );
    virtual ~oms_RQ_NW_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_NW_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_NW_MK"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               reject_description; 



    //  subject info
    static std::string  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_MD_MK
//-------------------------------    
class oms_RQ_MD_MK        :  public  RQ_MD_MK
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_MD_MK (  const RQ_MD_MK&  parent,   const std::string&  _reject_description );
    explicit oms_RQ_MD_MK ( const qpid::messaging::Message& message );
    virtual ~oms_RQ_MD_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_MD_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_MD_MK"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               reject_description; 



    //  subject info
    static std::string  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_CC_MK
//-------------------------------    
class oms_RQ_CC_MK        :  public  RQ_CC_MK
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_CC_MK (  const RQ_CC_MK&  parent,   const std::string&  _reject_description );
    explicit oms_RQ_CC_MK ( const qpid::messaging::Message& message );
    virtual ~oms_RQ_CC_MK (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_CC_MK"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_CC_MK"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               reject_description; 



    //  subject info
    static std::string  get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      oms_RQ_ORDERS_STATUS
//-------------------------------    
class oms_RQ_ORDERS_STATUS        :  public  RQ_ORDERS_STATUS
{
public:
    //  inner classes

    
    // constructor
    explicit oms_RQ_ORDERS_STATUS (  const RQ_ORDERS_STATUS&  parent,   const std::string&  _reject_description );
    explicit oms_RQ_ORDERS_STATUS ( const qpid::messaging::Message& message );
    virtual ~oms_RQ_ORDERS_STATUS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_ORDERS_STATUS"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_ORDERS_STATUS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               reject_description; 



    //  subject info
    static std::string  get_in_subject (const std::string& account_client_code,const std::string& market);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_LS & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_NW_LS & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_NW_LS & c);

bool operator== (const oms_RQ_NW_LS& a, const oms_RQ_NW_LS& b);
bool operator!= (const oms_RQ_NW_LS& a, const oms_RQ_NW_LS& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_LS & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_MD_LS & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_MD_LS & c);

bool operator== (const oms_RQ_MD_LS& a, const oms_RQ_MD_LS& b);
bool operator!= (const oms_RQ_MD_LS& a, const oms_RQ_MD_LS& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_LS & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_CC_LS & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_CC_LS & c);

bool operator== (const oms_RQ_CC_LS& a, const oms_RQ_CC_LS& b);
bool operator!= (const oms_RQ_CC_LS& a, const oms_RQ_CC_LS& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_NW_MK & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_NW_MK & c);

bool operator== (const oms_RQ_NW_MK& a, const oms_RQ_NW_MK& b);
bool operator!= (const oms_RQ_NW_MK& a, const oms_RQ_NW_MK& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_MD_MK & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_MD_MK & c);

bool operator== (const oms_RQ_MD_MK& a, const oms_RQ_MD_MK& b);
bool operator!= (const oms_RQ_MD_MK& a, const oms_RQ_MD_MK& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_MK & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_CC_MK & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_CC_MK & c);

bool operator== (const oms_RQ_CC_MK& a, const oms_RQ_CC_MK& b);
bool operator!= (const oms_RQ_CC_MK& a, const oms_RQ_CC_MK& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_ORDERS_STATUS & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const oms_RQ_ORDERS_STATUS & c);
   void           operator >> (const YAML::Node& n,       oms_RQ_ORDERS_STATUS & c);

bool operator== (const oms_RQ_ORDERS_STATUS& a, const oms_RQ_ORDERS_STATUS& b);
bool operator!= (const oms_RQ_ORDERS_STATUS& a, const oms_RQ_ORDERS_STATUS& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const oms_RQ_NW_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_LS>& a, const std::string& field);
void copy (oms_RQ_NW_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const oms_RQ_MD_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_LS>& a, const std::string& field);
void copy (oms_RQ_MD_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const oms_RQ_CC_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_LS>& a, const std::string& field);
void copy (oms_RQ_CC_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const oms_RQ_NW_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_MK>& a, const std::string& field);
void copy (oms_RQ_NW_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const oms_RQ_MD_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_MK>& a, const std::string& field);
void copy (oms_RQ_MD_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const oms_RQ_CC_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_MK& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_MK>& a, const std::string& field);
void copy (oms_RQ_CC_MK& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const oms_RQ_ORDERS_STATUS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_ORDERS_STATUS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_ORDERS_STATUS>& a, const std::string& field);
void copy (oms_RQ_ORDERS_STATUS& a, const qpid::types::Variant& map);

    oms_RQ_NW_LS  __internal_get_default(oms_RQ_NW_LS *);
    
    oms_RQ_MD_LS  __internal_get_default(oms_RQ_MD_LS *);
    
    oms_RQ_CC_LS  __internal_get_default(oms_RQ_CC_LS *);
    
    oms_RQ_NW_MK  __internal_get_default(oms_RQ_NW_MK *);
    
    oms_RQ_MD_MK  __internal_get_default(oms_RQ_MD_MK *);
    
    oms_RQ_CC_MK  __internal_get_default(oms_RQ_CC_MK *);
    
    oms_RQ_ORDERS_STATUS  __internal_get_default(oms_RQ_ORDERS_STATUS *);
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_NW_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_MD_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_CC_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_NW_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_MD_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_CC_MK)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_ORDERS_STATUS)




#endif
