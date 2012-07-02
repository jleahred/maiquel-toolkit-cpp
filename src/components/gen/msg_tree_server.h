
#ifndef  __msg_tree_server__
#define  __msg_tree_server__


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


#include "support/mtk_string.h"
#include "components/msg_common.h"

namespace mtk { 
namespace gen { 
namespace msg { 




//-------------------------------
//      sub_tree_item
//-------------------------------    
class sub_tree_item     
{
public:
    //  inner classes

    
    // constructor
    explicit sub_tree_item (    const std::string&  _branch,   const std::string&  _description,   const mtk::nullable<mtk::msg::sub_product_code>&  _product_code );
    explicit sub_tree_item ( const qpid::types::Variant::Map&  mv );
    virtual ~sub_tree_item (){};
    virtual std::string get_message_type_as_string       (void) const  { return "sub_tree_item"; }
    static  std::string static_get_message_type_as_string(void)        { return "sub_tree_item"; }
    
    

    

    
    
    
    

    // fields
    std::string                               branch; 
    std::string                               description; 
    mtk::nullable<mtk::msg::sub_product_code>  product_code; 




    //   KEY INFO
        typedef decltype(branch) key_type;
        key_type    get_key(void) const  {   return  branch;  }
    //   KEY INFO


    //  ADDRESS info



    //  subject info
    

    
    
    
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class sub_tree_item__qpid_map
        {
        public:
            explicit  sub_tree_item__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  sub_tree_item__qpid_map ( const sub_tree_item&  c ) : m_static(c) {}
            explicit  sub_tree_item__qpid_map (    const std::string&  _branch,   const std::string&  _description );
            ~sub_tree_item__qpid_map() {};
            

            sub_tree_item                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            


            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      req_tree_items
//-------------------------------    
class req_tree_items     
{
public:
    //  inner classes

    
    // constructor
    explicit req_tree_items (    const mtk::msg::sub_request_info&  _request_info,   const std::string&  _branch );
    explicit req_tree_items ( const qpid::types::Variant::Map&  mv );
    virtual ~req_tree_items (){};
    virtual std::string get_message_type_as_string       (void) const  { return "req_tree_items"; }
    static  std::string static_get_message_type_as_string(void)        { return "req_tree_items"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_request_info                request_info; 
    std::string                               branch; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& request_info_process_info_location_broker_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class req_tree_items__qpid_map
        {
        public:
            explicit  req_tree_items__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  req_tree_items__qpid_map ( const req_tree_items&  c ) : m_static(c) {}
            explicit  req_tree_items__qpid_map (    const mtk::msg::sub_request_info&  _request_info,   const std::string&  _branch );
            ~req_tree_items__qpid_map() {};
            

            req_tree_items                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  req_tree_items::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  req_tree_items::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  req_tree_items::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  req_tree_items::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      res_tree_items
//-------------------------------    
class res_tree_items     
{
public:
    //  inner classes

    
    // constructor
    explicit res_tree_items (    const mtk::msg::sub_r_response&  _response_info,   const sub_tree_item&  _item );
    explicit res_tree_items ( const qpid::types::Variant::Map&  mv );
    virtual ~res_tree_items (){};
    virtual std::string get_message_type_as_string       (void) const  { return "res_tree_items"; }
    static  std::string static_get_message_type_as_string(void)        { return "res_tree_items"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    mtk::msg::sub_r_response                  response_info; 
    sub_tree_item                             item; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& response_info_request_info_process_info_location_broker_code,const std::string& response_info_request_info_process_info_location_machine,const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_session_id,const std::string& response_info_request_info_req_id_req_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class res_tree_items__qpid_map
        {
        public:
            explicit  res_tree_items__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  res_tree_items__qpid_map ( const res_tree_items&  c ) : m_static(c) {}
            explicit  res_tree_items__qpid_map (    const mtk::msg::sub_r_response&  _response_info,   const sub_tree_item&  _item );
            ~res_tree_items__qpid_map() {};
            

            res_tree_items                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  res_tree_items::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  res_tree_items::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  res_tree_items::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  res_tree_items::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        

//-------------------------------
//      pub_tree_colapse_branch
//-------------------------------    
class pub_tree_colapse_branch     
{
public:
    //  inner classes

    
    // constructor
    explicit pub_tree_colapse_branch (    const std::string&  _broker_code,   const std::string&  _branch );
    explicit pub_tree_colapse_branch ( const qpid::types::Variant::Map&  mv );
    virtual ~pub_tree_colapse_branch (){};
    virtual std::string get_message_type_as_string       (void) const  { return "pub_tree_colapse_branch"; }
    static  std::string static_get_message_type_as_string(void)        { return "pub_tree_colapse_branch"; }
    
    static  int         static_return_message_RT_priority(void)        { return 2; };

    static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { static const auto  result = mtk::nullable<mtk::DateTime>{};  return result; };

    
    
    qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;
    

    // fields
    std::string                               broker_code; 
    std::string                               branch; 



    //  ADDRESS info
    static mtk::t_qpid_address  static_get_qpid_address ();
    mtk::t_qpid_address  get_qpid_address (void) const;



    //  subject info
    static mtk::t_qpid_filter  get_in_subject (const std::string& broker_code);
    virtual mtk::t_qpid_filter  get_out_subject (void) const;


    
    
    mtk::msg::sub_control_fields*   __internal_warning_control_fields;
    
    void        before_send(void) const;
    
    void check_recomended(void) const;
};



        //  qpid_variant wrapper for dynamic
        class pub_tree_colapse_branch__qpid_map
        {
        public:
            explicit  pub_tree_colapse_branch__qpid_map ( const qpid::types::Variant::Map&  mv );
            explicit  pub_tree_colapse_branch__qpid_map ( const pub_tree_colapse_branch&  c ) : m_static(c) {}
            explicit  pub_tree_colapse_branch__qpid_map (    const std::string&  _broker_code,   const std::string&  _branch );
            ~pub_tree_colapse_branch__qpid_map() {};
            

            pub_tree_colapse_branch                   m_static;
            qpid::types::Variant::Map           m_qpid_map;

            

            //  DERIVED INFO

            static mtk::t_qpid_address  static_get_qpid_address ()  {  return  pub_tree_colapse_branch::static_get_qpid_address();  }
            mtk::t_qpid_address  get_qpid_address (void) const  {  return  m_static.get_qpid_address();  }

            std::string get_message_type_as_string       (void) const  { return  m_static.get_message_type_as_string(); }
            static  std::string static_get_message_type_as_string(void)        { return  pub_tree_colapse_branch::static_get_message_type_as_string();  }
            mtk::t_qpid_filter  get_out_subject (void) const { return  m_static.get_out_subject();  }
            qpid::types::Variant::Map   qpidmsg_codded_as_qpid_map (void) const;//   {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }
            static  int         static_return_message_RT_priority(void)        { return  pub_tree_colapse_branch::static_return_message_RT_priority(); }
            static  mtk::nullable<mtk::DateTime>    static_get_depreciated_on(void)        { return  pub_tree_colapse_branch::static_get_depreciated_on(); }



            mtk::msg::sub_control_fields*   __internal_warning_control_fields;
        };
        
        
    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_tree_item & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_tree_item & c);
   void           operator >> (const YAML::Node& n,       sub_tree_item & c);

bool operator== (const sub_tree_item& a, const sub_tree_item& b);
bool operator!= (const sub_tree_item& a, const sub_tree_item& b);

    std::ostream& operator<< (std::ostream& o, const req_tree_items & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const req_tree_items & c);
   void           operator >> (const YAML::Node& n,       req_tree_items & c);

bool operator== (const req_tree_items& a, const req_tree_items& b);
bool operator!= (const req_tree_items& a, const req_tree_items& b);

    std::ostream& operator<< (std::ostream& o, const res_tree_items & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const res_tree_items & c);
   void           operator >> (const YAML::Node& n,       res_tree_items & c);

bool operator== (const res_tree_items& a, const res_tree_items& b);
bool operator!= (const res_tree_items& a, const res_tree_items& b);

    std::ostream& operator<< (std::ostream& o, const pub_tree_colapse_branch & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const pub_tree_colapse_branch & c);
   void           operator >> (const YAML::Node& n,       pub_tree_colapse_branch & c);

bool operator== (const pub_tree_colapse_branch& a, const pub_tree_colapse_branch& b);
bool operator!= (const pub_tree_colapse_branch& a, const pub_tree_colapse_branch& b);

void __internal_add2map (qpid::types::Variant::Map& map, const sub_tree_item& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_tree_item>& a, const std::string& field);
void copy (sub_tree_item& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const req_tree_items& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_tree_items>& a, const std::string& field);
void copy (req_tree_items& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const res_tree_items& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_tree_items>& a, const std::string& field);
void copy (res_tree_items& a, const qpid::types::Variant& map);
void __internal_add2map (qpid::types::Variant::Map& map, const pub_tree_colapse_branch& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_tree_colapse_branch>& a, const std::string& field);
void copy (pub_tree_colapse_branch& a, const qpid::types::Variant& map);

    
    
    
//  fordward declarations  dynamic--------------------------------------------------------


inline std::ostream& operator<< (std::ostream& o, const sub_tree_item__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const sub_tree_item__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       sub_tree_item__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const sub_tree_item__qpid_map& a, const sub_tree_item__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const sub_tree_item__qpid_map& a, const sub_tree_item__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const sub_tree_item__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_tree_item__qpid_map>& a, const std::string& field);
void copy (sub_tree_item__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const req_tree_items__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const req_tree_items__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       req_tree_items__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const req_tree_items__qpid_map& a, const req_tree_items__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const req_tree_items__qpid_map& a, const req_tree_items__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const req_tree_items__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_tree_items__qpid_map>& a, const std::string& field);
void copy (req_tree_items__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const res_tree_items__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const res_tree_items__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       res_tree_items__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const res_tree_items__qpid_map& a, const res_tree_items__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const res_tree_items__qpid_map& a, const res_tree_items__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const res_tree_items__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_tree_items__qpid_map>& a, const std::string& field);
void copy (res_tree_items__qpid_map& a, const qpid::types::Variant& map);

inline std::ostream& operator<< (std::ostream& o, const pub_tree_colapse_branch__qpid_map & c) {  return (o << c.m_static << "   QPID_VAR: " << c.m_qpid_map);  };
inline YAML::Emitter& operator << (YAML::Emitter&    o, const pub_tree_colapse_branch__qpid_map & c)          {  return (o << c.m_static);  };
inline void           operator >> (const YAML::Node& n,       pub_tree_colapse_branch__qpid_map & c)          {  n  >>  c;  }

inline bool operator== (const pub_tree_colapse_branch__qpid_map& a, const pub_tree_colapse_branch__qpid_map& b)  {  return  a==b;  }
inline bool operator!= (const pub_tree_colapse_branch__qpid_map& a, const pub_tree_colapse_branch__qpid_map& b)  {  return  a!=b;  }
void __internal_add2map (qpid::types::Variant::Map& map, const pub_tree_colapse_branch__qpid_map& a);
void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_tree_colapse_branch__qpid_map>& a, const std::string& field);
void copy (pub_tree_colapse_branch__qpid_map& a, const qpid::types::Variant& map);

    sub_tree_item  __internal_get_default(sub_tree_item *);
    
        inline sub_tree_item__qpid_map  __internal_get_default(sub_tree_item__qpid_map *) { return  sub_tree_item__qpid_map(__internal_get_default((sub_tree_item*)0));  }

    req_tree_items  __internal_get_default(req_tree_items *);
    
        inline req_tree_items__qpid_map  __internal_get_default(req_tree_items__qpid_map *) { return  req_tree_items__qpid_map(__internal_get_default((req_tree_items*)0));  }

    res_tree_items  __internal_get_default(res_tree_items *);
    
        inline res_tree_items__qpid_map  __internal_get_default(res_tree_items__qpid_map *) { return  res_tree_items__qpid_map(__internal_get_default((res_tree_items*)0));  }

    pub_tree_colapse_branch  __internal_get_default(pub_tree_colapse_branch *);
    
        inline pub_tree_colapse_branch__qpid_map  __internal_get_default(pub_tree_colapse_branch__qpid_map *) { return  pub_tree_colapse_branch__qpid_map(__internal_get_default((pub_tree_colapse_branch*)0));  }


};   //namespace mtk {
};   //namespace gen {
};   //namespace msg {





    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::gen::msg::req_tree_items)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::gen::msg::req_tree_items__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::gen::msg::res_tree_items)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::gen::msg::res_tree_items__qpid_map)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::gen::msg::pub_tree_colapse_branch)
MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(mtk::gen::msg::pub_tree_colapse_branch__qpid_map)




#endif
