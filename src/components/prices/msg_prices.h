
#ifndef  __msg_prices__
#define  __msg_prices__


// generated automatically
// coded last modification:        _CODED_LAST_MODIF


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
#include "support/mtk_double.h"

namespace mtk { 
namespace prices { 
namespace msg { 




//-------------------------------
//      sub_price_level
//-------------------------------    
class sub_price_level     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_price_level (    const mtk::FixedNumber&  _price,   const mtk::FixedNumber&  _quantity );
    explicit sub_price_level ( const qpid::messaging::Message& message );
    virtual ~sub_price_level (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_price_level"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_price_level"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    mtk::FixedNumber                          price; 
    mtk::FixedNumber                          quantity; 



    //  subject info
    
    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      sub_price_deph5
//-------------------------------    
class sub_price_deph5     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_price_deph5 (    const sub_price_level&  _level0,   const sub_price_level&  _level1,   const sub_price_level&  _level2,   const sub_price_level&  _level3,   const sub_price_level&  _level4 );
    explicit sub_price_deph5 ( const qpid::messaging::Message& message );
    virtual ~sub_price_deph5 (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_price_deph5"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_price_deph5"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    sub_price_level                           level0; 
    sub_price_level                           level1; 
    sub_price_level                           level2; 
    sub_price_level                           level3; 
    sub_price_level                           level4; 



    //  subject info
    
    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      pub_best_prices
//-------------------------------    
class pub_best_prices     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_best_prices (    const mtk::msg::sub_product_code&  _product_code,   const sub_price_deph5&  _bids,   const sub_price_deph5&  _asks );
    explicit pub_best_prices ( const qpid::messaging::Message& message );
    virtual ~pub_best_prices (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_best_prices"; };
    static  std::string static_get_message_type_as_string(void)        { return "pub_best_prices"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    mtk::msg::sub_product_code                product_code; 
    sub_price_deph5                           bids; 
    sub_price_deph5                           asks; 



    //  subject info
    static std::string  get_in_subject (const std::string& product_code_sys_code_market,const std::string& product_code_sys_code_product);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
private:
    std::string check_recomended(void) const;
};




    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_price_level & c);

bool operator== (const sub_price_level& a, const sub_price_level& b);
bool operator!= (const sub_price_level& a, const sub_price_level& b);

    std::ostream& operator<< (std::ostream& o, const sub_price_deph5 & c);

bool operator== (const sub_price_deph5& a, const sub_price_deph5& b);
bool operator!= (const sub_price_deph5& a, const sub_price_deph5& b);

    std::ostream& operator<< (std::ostream& o, const pub_best_prices & c);

bool operator== (const pub_best_prices& a, const pub_best_prices& b);
bool operator!= (const pub_best_prices& a, const pub_best_prices& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_price_level& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_price_level& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_price_level>& a, const std::string& field);
void copy (sub_price_level& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_price_deph5& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_price_deph5& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_price_deph5>& a, const std::string& field);
void copy (sub_price_deph5& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const pub_best_prices& a);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_best_prices& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_best_prices>& a, const std::string& field);
void copy (pub_best_prices& a, const qpid::types::Variant& map);

    sub_price_level  __internal_get_default(sub_price_level *);
    
    sub_price_deph5  __internal_get_default(sub_price_deph5 *);
    
    pub_best_prices  __internal_get_default(pub_best_prices *);
    

};   //namespace mtk {
};   //namespace prices {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::sub_price_level)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::sub_price_deph5)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::pub_best_prices)




#endif
