
#ifndef  __msg_trd_oms_rq__
#define  __msg_trd_oms_rq__


// generated automatically
// coded last modification:        Mon Jan 17 22:33:43 2011
// pythonscript last modification: Thu Feb 10 18:34:23 2011


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
    explicit oms_RQ_NW_LS (  const RQ_NW_LS&  parent,   const std::string&  _reject_descr );
    explicit oms_RQ_NW_LS ( const qpid::messaging::Message& message );
    virtual ~oms_RQ_NW_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_NW_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_NW_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    std::string                               reject_descr; 



    //  subject info
    
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
    explicit oms_RQ_MD_LS (  const RQ_MD_LS&  parent,   const std::string&  _reject_descr );
    explicit oms_RQ_MD_LS ( const qpid::messaging::Message& message );
    virtual ~oms_RQ_MD_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_MD_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_MD_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    std::string                               reject_descr; 



    //  subject info
    
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
    explicit oms_RQ_CC_LS (  const RQ_CC_LS&  parent,   const std::string&  _reject_descr );
    explicit oms_RQ_CC_LS ( const qpid::messaging::Message& message );
    virtual ~oms_RQ_CC_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "oms_RQ_CC_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "oms_RQ_CC_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (void) const;
    

    // fields
    std::string                               reject_descr; 



    //  subject info
    
private:
    std::string check_recomended(void) const;
};




    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_LS & c);

bool operator== (const oms_RQ_NW_LS& a, const oms_RQ_NW_LS& b);
bool operator!= (const oms_RQ_NW_LS& a, const oms_RQ_NW_LS& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_LS & c);

bool operator== (const oms_RQ_MD_LS& a, const oms_RQ_MD_LS& b);
bool operator!= (const oms_RQ_MD_LS& a, const oms_RQ_MD_LS& b);

    std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_LS & c);

bool operator== (const oms_RQ_CC_LS& a, const oms_RQ_CC_LS& b);
bool operator!= (const oms_RQ_CC_LS& a, const oms_RQ_CC_LS& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const oms_RQ_NW_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_LS& a);
void copy (oms_RQ_NW_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const oms_RQ_MD_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_LS& a);
void copy (oms_RQ_MD_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const oms_RQ_CC_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_LS& a);
void copy (oms_RQ_CC_LS& a, const qpid::types::Variant& map);

    oms_RQ_NW_LS  __internal_get_default(oms_RQ_NW_LS *);
    
    oms_RQ_MD_LS  __internal_get_default(oms_RQ_MD_LS *);
    
    oms_RQ_CC_LS  __internal_get_default(oms_RQ_CC_LS *);
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_NW_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_MD_LS)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::msg::oms_RQ_CC_LS)




#endif
