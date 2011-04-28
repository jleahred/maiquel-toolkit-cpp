
#ifndef  __msg_prices__
#define  __msg_prices__


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
    
    

    // fields
    mtk::FixedNumber                          price; 
    mtk::FixedNumber                          quantity; 



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
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
    
    

    // fields
    sub_price_level                           level0; 
    sub_price_level                           level1; 
    sub_price_level                           level2; 
    sub_price_level                           level3; 
    sub_price_level                           level4; 



    //  subject info
    
    
    
    
    
    void        before_send(void) const;
    
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
    explicit pub_best_prices (    const mtk::msg::sub_product_code&  _product_code,   const sub_price_deph5&  _bids,   const sub_price_deph5&  _asks,   const mtk::msg::sub_control_fluct&  _orig_control_fluct );
    explicit pub_best_prices ( const qpid::messaging::Message& message );
    virtual ~pub_best_prices (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_best_prices"; };
    static  std::string static_get_message_type_as_string(void)        { return "pub_best_prices"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_product_code                product_code; 
    sub_price_deph5                           bids; 
    sub_price_deph5                           asks; 
    mtk::msg::sub_control_fluct               orig_control_fluct; 



    //  subject info
    static std::string  get_in_subject (const std::string& product_code_sys_code_market,const std::string& product_code_sys_code_product);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      req_prod_info
//-------------------------------    
class req_prod_info     
{
public:
    //  inner classes

    
    // constructor
    explicit req_prod_info (    const mtk::msg::sub_request_info&  _request_info,   const mtk::msg::sub_sys_product_code&  _sys_product_code );
    explicit req_prod_info ( const qpid::messaging::Message& message );
    virtual ~req_prod_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_prod_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "req_prod_info"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 
    mtk::msg::sub_sys_product_code            sys_product_code; 



    //  subject info
    static std::string  get_in_subject (const std::string& request_info_process_location_location_client_code);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      res_product_info
//-------------------------------    
class res_product_info     
{
public:
    //  inner classes

    
    //-------------------------------
    //      IC_response
    //-------------------------------    
    class IC_response     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit IC_response (    const pub_best_prices&  _best_prices );
        explicit IC_response ( const qpid::messaging::Message& message );
        virtual ~IC_response (){};
        virtual std::string get_message_type_as_string       (void) const  { return "IC_response"; };
        static  std::string static_get_message_type_as_string(void)        { return "IC_response"; };
        
        
    
        // fields
        pub_best_prices                           best_prices; 
    
    
    
        //  subject info
        
        
        
        
        
        void        before_send(void) const;
        
    private:
        std::string check_recomended(void) const;
    };
    
    
    
    
    // constructor
    explicit res_product_info (    const mtk::msg::sub_r_response&  _response_info,   const IC_response&  _response );
    explicit res_product_info ( const qpid::messaging::Message& message );
    virtual ~res_product_info (){};
    virtual std::string get_message_type_as_string       (void) const  { return "res_product_info"; };
    static  std::string static_get_message_type_as_string(void)        { return "res_product_info"; };
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_r_response                  response_info; 
    IC_response                               response; 



    //  subject info
    static std::string  get_in_subject (const std::string& response_info_request_info_process_location_location_client_code,const std::string& response_info_request_info_process_location_location_machine,const std::string& response_info_request_info_process_location_process_uuid,const std::string& response_info_request_info_req_id_sess_id,const std::string& response_info_request_info_req_id_req_code);
virtual std::string  get_out_subject (void) const;

    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_price_level & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const sub_price_level & c);

bool operator== (const sub_price_level& a, const sub_price_level& b);
bool operator!= (const sub_price_level& a, const sub_price_level& b);

    std::ostream& operator<< (std::ostream& o, const sub_price_deph5 & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const sub_price_deph5 & c);

bool operator== (const sub_price_deph5& a, const sub_price_deph5& b);
bool operator!= (const sub_price_deph5& a, const sub_price_deph5& b);

    std::ostream& operator<< (std::ostream& o, const pub_best_prices & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const pub_best_prices & c);

bool operator== (const pub_best_prices& a, const pub_best_prices& b);
bool operator!= (const pub_best_prices& a, const pub_best_prices& b);

    std::ostream& operator<< (std::ostream& o, const req_prod_info & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const req_prod_info & c);

bool operator== (const req_prod_info& a, const req_prod_info& b);
bool operator!= (const req_prod_info& a, const req_prod_info& b);

    std::ostream& operator<< (std::ostream& o, const res_product_info & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const res_product_info & c);

bool operator== (const res_product_info::IC_response& a, const res_product_info::IC_response& b);
bool operator!= (const res_product_info::IC_response& a, const res_product_info::IC_response& b);


bool operator== (const res_product_info& a, const res_product_info& b);
bool operator!= (const res_product_info& a, const res_product_info& b);

    std::ostream& operator<< (std::ostream& o, const res_product_info::IC_response & c);
   YAML::Emitter& operator << (YAML::Emitter& o, const res_product_info::IC_response & c);

bool operator== (const res_product_info::IC_response& a, const res_product_info::IC_response& b);
bool operator!= (const res_product_info::IC_response& a, const res_product_info::IC_response& b);

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
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const req_prod_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const req_prod_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_prod_info>& a, const std::string& field);
void copy (req_prod_info& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const res_product_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const res_product_info& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_product_info>& a, const std::string& field);
void copy (res_product_info& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const res_product_info::IC_response& a);
void __internal_add2map (qpid::types::Variant::Map& map, const res_product_info::IC_response& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_product_info::IC_response>& a, const std::string& field);
void copy (res_product_info::IC_response& a, const qpid::types::Variant& map);

    sub_price_level  __internal_get_default(sub_price_level *);
    
    sub_price_deph5  __internal_get_default(sub_price_deph5 *);
    
    pub_best_prices  __internal_get_default(pub_best_prices *);
    
    req_prod_info  __internal_get_default(req_prod_info *);
    
    res_product_info  __internal_get_default(res_product_info *);
    
    res_product_info::IC_response  __internal_get_default(res_product_info::IC_response *);
    

};   //namespace mtk {
};   //namespace prices {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::pub_best_prices)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::req_prod_info)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::prices::msg::res_product_info)




#endif
