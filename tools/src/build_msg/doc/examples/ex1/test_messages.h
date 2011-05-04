
#ifndef  __test_messages__
#define  __test_messages__


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




namespace testing { 




//-------------------------------
//      LimitPosition
//-------------------------------    
class LimitPosition     
{
public:
    //  inner classes

    
    // constructor
    explicit LimitPosition (    const mtk::nullable<std::string>&  _buy_sell,   const mtk::nullable<mtk::FixedNumber>&  _price,   const mtk::FixedNumber&  _quantity );
    explicit LimitPosition ( const qpid::messaging::Message& message );
    virtual ~LimitPosition (){};
    virtual std::string get_message_type_as_string       (void) const  { return "LimitPosition"; };
    static  std::string static_get_message_type_as_string(void)        { return "LimitPosition"; };
    
    

    // fields
    mtk::nullable<std::string>                buy_sell; 
    mtk::nullable<mtk::FixedNumber>           price; 
    mtk::FixedNumber                          quantity; 



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      RQ_NW_LS
//-------------------------------    
class RQ_NW_LS     
{
public:
    //  inner classes

    
    //-------------------------------
    //      IC_control_fields_
    //-------------------------------    
    class IC_control_fields_     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit IC_control_fields_ (    const mtk::DateTime&  _clock_id,   const int32_t&  _secuence );
        explicit IC_control_fields_ ( const qpid::messaging::Message& message );
        virtual ~IC_control_fields_ (){};
        virtual std::string get_message_type_as_string       (void) const  { return "IC_control_fields_"; };
        static  std::string static_get_message_type_as_string(void)        { return "IC_control_fields_"; };
        
        
    
        // fields
        mtk::DateTime                             clock_id; 
        int32_t                                   secuence; 
    
    
    
        //  subject info
        
        
        
        
        
        void        before_send(void) const;
        
    private:
        std::string check_recomended(void) const;
    };
    
    
    
    
    //-------------------------------
    //      IC_product_code
    //-------------------------------    
    class IC_product_code     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit IC_product_code (    const std::string&  _market,   const std::string&  _product_code,   const std::string&  _aditional_code );
        explicit IC_product_code ( const qpid::messaging::Message& message );
        virtual ~IC_product_code (){};
        virtual std::string get_message_type_as_string       (void) const  { return "IC_product_code"; };
        static  std::string static_get_message_type_as_string(void)        { return "IC_product_code"; };
        
        
    
        // fields
        std::string                               market; 
        std::string                               product_code; 
        std::string                               aditional_code; 
    
    
    
        //  subject info
        
        
        
        
        
        void        before_send(void) const;
        
    private:
        std::string check_recomended(void) const;
    };
    
    
    
    
    // constructor
    explicit RQ_NW_LS (    const std::string&  _order_id,   const std::string&  _cli_ref,   const LimitPosition&  _position,   const LimitPosition&  _positionnn,   const IC_control_fields_&  _control_fields_,   const IC_product_code&  _product_code,   const mtk::list<std::string >&  _names,   const mtk::list<LimitPosition >&  _postitions );
    explicit RQ_NW_LS ( const qpid::messaging::Message& message );
    virtual ~RQ_NW_LS (){};
    virtual std::string get_message_type_as_string       (void) const  { return "RQ_NW_LS"; };
    static  std::string static_get_message_type_as_string(void)        { return "RQ_NW_LS"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    std::string                               order_id; 
    std::string                               cli_ref; 
    LimitPosition                             position; 
    LimitPosition                             positionnn; 
    IC_control_fields_                        control_fields_; 
    IC_product_code                           product_code; 
    mtk::list<std::string >                   names; 
    mtk::list<LimitPosition >                 postitions; 



    //  subject info
    static std::string  get_in_subject ();
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      LimitPositionChild
//-------------------------------    
class LimitPositionChild        :  public  LimitPosition
{
public:
    //  inner classes

    
    // constructor
    explicit LimitPositionChild (  const LimitPosition&  parent,   const std::string&  _new_field );
    explicit LimitPositionChild ( const qpid::messaging::Message& message );
    virtual ~LimitPositionChild (){};
    virtual std::string get_message_type_as_string       (void) const  { return "LimitPositionChild"; };
    static  std::string static_get_message_type_as_string(void)        { return "LimitPositionChild"; };
    
    

    // fields
    std::string                               new_field; 



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const LimitPosition & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const LimitPosition & c);
   void           operator >> (const YAML::Node& n,       LimitPosition & c);

bool operator== (const LimitPosition& a, const LimitPosition& b);
bool operator!= (const LimitPosition& a, const LimitPosition& b);

    std::ostream& operator<< (std::ostream& o, const RQ_NW_LS & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_NW_LS & c);
   void           operator >> (const YAML::Node& n,       RQ_NW_LS & c);

bool operator== (const RQ_NW_LS::IC_control_fields_& a, const RQ_NW_LS::IC_control_fields_& b);
bool operator!= (const RQ_NW_LS::IC_control_fields_& a, const RQ_NW_LS::IC_control_fields_& b);


bool operator== (const RQ_NW_LS::IC_product_code& a, const RQ_NW_LS::IC_product_code& b);
bool operator!= (const RQ_NW_LS::IC_product_code& a, const RQ_NW_LS::IC_product_code& b);


bool operator== (const RQ_NW_LS& a, const RQ_NW_LS& b);
bool operator!= (const RQ_NW_LS& a, const RQ_NW_LS& b);

    std::ostream& operator<< (std::ostream& o, const RQ_NW_LS::IC_control_fields_ & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_NW_LS::IC_control_fields_ & c);
   void           operator >> (const YAML::Node& n,       RQ_NW_LS::IC_control_fields_ & c);

bool operator== (const RQ_NW_LS::IC_control_fields_& a, const RQ_NW_LS::IC_control_fields_& b);
bool operator!= (const RQ_NW_LS::IC_control_fields_& a, const RQ_NW_LS::IC_control_fields_& b);

    std::ostream& operator<< (std::ostream& o, const RQ_NW_LS::IC_product_code & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const RQ_NW_LS::IC_product_code & c);
   void           operator >> (const YAML::Node& n,       RQ_NW_LS::IC_product_code & c);

bool operator== (const RQ_NW_LS::IC_product_code& a, const RQ_NW_LS::IC_product_code& b);
bool operator!= (const RQ_NW_LS::IC_product_code& a, const RQ_NW_LS::IC_product_code& b);

    std::ostream& operator<< (std::ostream& o, const LimitPositionChild & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const LimitPositionChild & c);
   void           operator >> (const YAML::Node& n,       LimitPositionChild & c);

bool operator== (const LimitPositionChild& a, const LimitPositionChild& b);
bool operator!= (const LimitPositionChild& a, const LimitPositionChild& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const LimitPosition& a);
void __internal_add2map (qpid::types::Variant::Map& map, const LimitPosition& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<LimitPosition>& a, const std::string& field);
void copy (LimitPosition& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RQ_NW_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_NW_LS& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_NW_LS>& a, const std::string& field);
void copy (RQ_NW_LS& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RQ_NW_LS::IC_control_fields_& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_NW_LS::IC_control_fields_& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_NW_LS::IC_control_fields_>& a, const std::string& field);
void copy (RQ_NW_LS::IC_control_fields_& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const RQ_NW_LS::IC_product_code& a);
void __internal_add2map (qpid::types::Variant::Map& map, const RQ_NW_LS::IC_product_code& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_NW_LS::IC_product_code>& a, const std::string& field);
void copy (RQ_NW_LS::IC_product_code& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const LimitPositionChild& a);
void __internal_add2map (qpid::types::Variant::Map& map, const LimitPositionChild& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<LimitPositionChild>& a, const std::string& field);
void copy (LimitPositionChild& a, const qpid::types::Variant& map);

    LimitPosition  __internal_get_default(LimitPosition *);
    
    RQ_NW_LS  __internal_get_default(RQ_NW_LS *);
    
    RQ_NW_LS::IC_control_fields_  __internal_get_default(RQ_NW_LS::IC_control_fields_ *);
    
    RQ_NW_LS::IC_product_code  __internal_get_default(RQ_NW_LS::IC_product_code *);
    
    LimitPositionChild  __internal_get_default(LimitPositionChild *);
    

};   //namespace testing {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(testing::RQ_NW_LS)




#endif
