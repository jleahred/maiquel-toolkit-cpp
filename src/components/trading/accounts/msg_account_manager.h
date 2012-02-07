
#ifndef  __msg_account_manager__
#define  __msg_account_manager__


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
#include "components/trading/msg_trd_common.h"
#include "components/acs/msg_acs.h"

namespace mtk { 
namespace trd { 
namespace account { 
namespace msg { 




//-------------------------------
//      sub_grant
//-------------------------------    
class sub_grant     
{
public:
    //  inner classes

    
    //-------------------------------
    //      IC_key
    //-------------------------------    
    class IC_key     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit IC_key (    const std::string&  _market,   const mtk::trd::msg::sub_account_info&  _account );
        explicit IC_key ( const qpid::types::Variant::Map&  mv );
        virtual ~IC_key (){};
        virtual std::string get_message_type_as_string       (void) const  { return "IC_key"; };
        static  std::string static_get_message_type_as_string(void)        { return "IC_key"; };
    
        
    
        
        
        
        
    
        // fields
        std::string                               market; 
        mtk::trd::msg::sub_account_info           account; 
    
    
    
        //  ADDRESS info
    
    
    
        //  subject info
        
    
        
        
        
        
        void        before_send(void) const;
        
    private:
        std::string check_recomended(void) const;
    };
    
    
    
    
    // constructor
    explicit sub_grant (    const IC_key&  _key,   const std::string&  _type );
    explicit sub_grant ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_grant (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_grant"; };
    static  std::string static_get_message_type_as_string(void)        { return "sub_grant"; };

    

    
    
    
    

    // fields
    IC_key                                    key; 
    std::string                               type; 




    //   KEY INFO
        typedef decltype(key) key_type;
        key_type    get_key(void) const  {   return  key;  }
    //   KEY INFO


    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      rq_accounts
//-------------------------------    
class rq_accounts     
{
public:
    //  inner classes

    
    // constructor
    explicit rq_accounts (    const mtk::msg::sub_request_info&  _request_info );
    explicit rq_accounts ( const qpid::types::Variant::Map&  mv );
    virtual ~rq_accounts (){};
    virtual std::string get_message_type_as_string       (void) const  { return "rq_accounts"; };
    static  std::string static_get_message_type_as_string(void)        { return "rq_accounts"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& request_info_process_info_location_broker_code);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      conf_add_accounts
//-------------------------------    
class conf_add_accounts     
{
public:
    //  inner classes

    
    // constructor
    explicit conf_add_accounts (    const mtk::msg::sub_gen_response_location&  _gen_response_location,   const mtk::list<sub_grant >&  _grant_list );
    explicit conf_add_accounts ( const qpid::types::Variant::Map&  mv );
    virtual ~conf_add_accounts (){};
    virtual std::string get_message_type_as_string       (void) const  { return "conf_add_accounts"; };
    static  std::string static_get_message_type_as_string(void)        { return "conf_add_accounts"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_gen_response_location       gen_response_location; 
    mtk::list<sub_grant >                     grant_list; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& gen_response_location_broker_code,const std::string& gen_response_location_session_id);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      pub_accmgr_init
//-------------------------------    
class pub_accmgr_init     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_accmgr_init (    const mtk::msg::sub_process_info&  _process_info,   const std::string&  _request_sufix_subjetc );
    explicit pub_accmgr_init ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_accmgr_init (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_accmgr_init"; };
    static  std::string static_get_message_type_as_string(void)        { return "pub_accmgr_init"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_process_info                process_info; 
    std::string                               request_sufix_subjetc; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject ();
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};




//-------------------------------
//      rq_accounts_oninit
//-------------------------------    
class rq_accounts_oninit     
{
public:
    //  inner classes

    
    // constructor
    explicit rq_accounts_oninit (    const mtk::msg::sub_request_info&  _request_info,   const std::string&  _request_sufix_subjetc );
    explicit rq_accounts_oninit ( const qpid::types::Variant::Map&  mv );
    virtual ~rq_accounts_oninit (){};
    virtual std::string get_message_type_as_string       (void) const  { return "rq_accounts_oninit"; };
    static  std::string static_get_message_type_as_string(void)        { return "rq_accounts_oninit"; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return mtk::nullable<mtk::DateTime>{}; };

    
    
    qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 
    std::string                               request_sufix_subjetc; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& request_info_process_info_location_broker_code,const std::string& request_sufix_subjetc);
virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_grant & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_grant & c);
   void           operator >> (const YAML::Node& n,       sub_grant & c);

bool operator== (const sub_grant::IC_key& a, const sub_grant::IC_key& b);
bool operator!= (const sub_grant::IC_key& a, const sub_grant::IC_key& b);


bool operator== (const sub_grant& a, const sub_grant& b);
bool operator!= (const sub_grant& a, const sub_grant& b);

    std::ostream& operator<< (std::ostream& o, const sub_grant::IC_key & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_grant::IC_key & c);
   void           operator >> (const YAML::Node& n,       sub_grant::IC_key & c);

bool operator== (const sub_grant::IC_key& a, const sub_grant::IC_key& b);
bool operator!= (const sub_grant::IC_key& a, const sub_grant::IC_key& b);


    bool operator< (const sub_grant::IC_key& a, const sub_grant::IC_key& b);

    std::ostream& operator<< (std::ostream& o, const rq_accounts & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const rq_accounts & c);
   void           operator >> (const YAML::Node& n,       rq_accounts & c);

bool operator== (const rq_accounts& a, const rq_accounts& b);
bool operator!= (const rq_accounts& a, const rq_accounts& b);

    std::ostream& operator<< (std::ostream& o, const conf_add_accounts & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const conf_add_accounts & c);
   void           operator >> (const YAML::Node& n,       conf_add_accounts & c);

bool operator== (const conf_add_accounts& a, const conf_add_accounts& b);
bool operator!= (const conf_add_accounts& a, const conf_add_accounts& b);

    std::ostream& operator<< (std::ostream& o, const pub_accmgr_init & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_accmgr_init & c);
   void           operator >> (const YAML::Node& n,       pub_accmgr_init & c);

bool operator== (const pub_accmgr_init& a, const pub_accmgr_init& b);
bool operator!= (const pub_accmgr_init& a, const pub_accmgr_init& b);

    std::ostream& operator<< (std::ostream& o, const rq_accounts_oninit & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const rq_accounts_oninit & c);
   void           operator >> (const YAML::Node& n,       rq_accounts_oninit & c);

bool operator== (const rq_accounts_oninit& a, const rq_accounts_oninit& b);
bool operator!= (const rq_accounts_oninit& a, const rq_accounts_oninit& b);

qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_grant& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_grant& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_grant>& a, const std::string& field);
void copy (sub_grant& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const sub_grant::IC_key& a);
void __internal_add2map (qpid::types::Variant::Map& map, const sub_grant::IC_key& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_grant::IC_key>& a, const std::string& field);
void copy (sub_grant::IC_key& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const rq_accounts& a);
void __internal_add2map (qpid::types::Variant::Map& map, const rq_accounts& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<rq_accounts>& a, const std::string& field);
void copy (rq_accounts& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const conf_add_accounts& a);
void __internal_add2map (qpid::types::Variant::Map& map, const conf_add_accounts& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<conf_add_accounts>& a, const std::string& field);
void copy (conf_add_accounts& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const pub_accmgr_init& a);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_accmgr_init& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_accmgr_init>& a, const std::string& field);
void copy (pub_accmgr_init& a, const qpid::types::Variant& map);
qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const rq_accounts_oninit& a);
void __internal_add2map (qpid::types::Variant::Map& map, const rq_accounts_oninit& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<rq_accounts_oninit>& a, const std::string& field);
void copy (rq_accounts_oninit& a, const qpid::types::Variant& map);

    sub_grant  __internal_get_default(sub_grant *);
    
    sub_grant::IC_key  __internal_get_default(sub_grant::IC_key *);
    
    rq_accounts  __internal_get_default(rq_accounts *);
    
    conf_add_accounts  __internal_get_default(conf_add_accounts *);
    
    pub_accmgr_init  __internal_get_default(pub_accmgr_init *);
    
    rq_accounts_oninit  __internal_get_default(rq_accounts_oninit *);
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace account {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::account::msg::rq_accounts)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::account::msg::conf_add_accounts)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::account::msg::pub_accmgr_init)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::trd::account::msg::rq_accounts_oninit)




#endif
