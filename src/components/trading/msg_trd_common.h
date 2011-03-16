
#ifndef  __msg_trd_common__
#define  __msg_trd_common__


// generated automatically
// coded last modification:        Mon Jan 17 22:34:07 2011


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
#include "msg_trd_common_support.h"

namespace mtk { 
namespace trd { 
namespace msg { 




//-------------------------------
//      sub_order_id
//-------------------------------    
class sub_order_id        :  public  mtk::msg::sub_request_id
{
public:
    //  inner classes

    
    // constructor
    explicit sub_order_id (  const mtk::msg::sub_request_id&  parent );
    explicit sub_order_id ( const qpid::messaging::Message& message );
    virtual ~sub_order_id (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_order_id"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_order_id"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields



    //  subject info
    
private:
    std::string check_recomended(void) const;
};





//-------------------------------
//      sub_total_executions
//-------------------------------    
class sub_total_executions     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_total_executions (    const mtk::Double&  _sum_price_by_qty,   const mtk::FixedNumber&  _quantity,   const mtk::FixedNumber&  _remaining_qty );
    explicit sub_total_executions ( const qpid::messaging::Message& message );
    virtual ~sub_total_executions (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_total_executions"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_total_executions"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    mtk::Double                               sum_price_by_qty; 
    mtk::FixedNumber                          quantity; 
    mtk::FixedNumber                          remaining_qty; 



    //  subject info
    
private:
    std::string check_recomended(void) const;
};




    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_order_id & c);

bool operator== (const sub_order_id& a, const sub_order_id& b);
bool operator!= (const sub_order_id& a, const sub_order_id& b);

    std::ostream& operator<< (std::ostream& o, const sub_total_executions & c);

bool operator== (const sub_total_executions& a, const sub_total_executions& b);
bool operator!= (const sub_total_executions& a, const sub_total_executions& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_order_id& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_order_id& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_order_id>& a, const std::string& field);
void copy (sub_order_id& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_total_executions& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_total_executions& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_total_executions>& a, const std::string& field);
void copy (sub_total_executions& a, const qpid::types::Variant& map);

    sub_order_id  __internal_get_default(sub_order_id *);
    
    sub_total_executions  __internal_get_default(sub_total_executions *);
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::sub_order_id)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::sub_total_executions)




#endif
