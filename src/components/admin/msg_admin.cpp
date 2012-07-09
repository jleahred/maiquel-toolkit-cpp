
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_admin.h"

namespace mtk { 
namespace admin { 
namespace msg { 







    inline std::string  __internal_get_default(std::string*)
    {
        return std::string();
    }

    inline mtk::Double __internal_get_default(mtk::Double*)
    {
        return mtk::Double(0.0);
    }
    inline mtk::FixedNumber __internal_get_default(mtk::FixedNumber*)
    {
        return mtk::FixedNumber(mtk::fnDouble(0), mtk::fnDec(0), mtk::fnInc(1));
    }
    inline mtk::fnExt  __internal_get_default(mtk::fnExt*)
    {
        return mtk::fnExt(mtk::fnDec(0), mtk::fnInc(1));
    }
    
    inline mtk::DateTime __internal_get_default(mtk::DateTime*)
    {
        return mtk::DateTime(mtk::dtYear(2000), mtk::dtMonth(1), mtk::dtDay(1));
    }
    inline mtk::dtTimeQuantity __internal_get_default(mtk::dtTimeQuantity*)
    {
        return mtk::dtTimeQuantity(mtk::dtHours(0), mtk::dtMinutes(0), mtk::dtSeconds(0), mtk::dtMilliseconds(0));
    }
    inline bool __internal_get_default(bool*)
    {
        return false;
    }
    inline int8_t __internal_get_default(int8_t*)
    {
        return 0;
    }
    inline int16_t  __internal_get_default(int16_t*)
    {
        return 0;
    }
    inline int32_t  __internal_get_default(int32_t*)
    {
        return 0;
    }

    template<typename T>
    mtk::list<T>  __internal_get_default(mtk::list<T>*)
    {
        return mtk::list<T>();
    }



    
template<typename T>
std::ostream& operator<< (std::ostream& o, const mtk::list<T>& list)
{
    typename mtk::list<T>::const_iterator it = list.begin();
    o << "[";
    while (it!= list.end())
    {
        o << *it << ", ";
        ++it;
    }
    o << "]";
    return o;
}



template<typename T>
bool operator== (const mtk::list<T>& l1, const mtk::list<T>& l2)
{
    if (l1.size() != l2.size())     return false;
    
    typename mtk::list<T>::const_iterator it1 = l1.begin();
    typename mtk::list<T>::const_iterator it2 = l2.begin();
    while (it1!= l1.end())
    {
        if (*it1 != *it2)       return false;
        ++it1;
        ++it2;
    }
    return true;
}



inline void  copy(mtk::FixedNumber& result, const qpid::types::Variant& v)
{
    result = ({   std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> ifn = /*it->second*/v.asMap();
                    mtk::FixedNumber(mtk::fnIntCode(ifn["n"].asInt32()), mtk::fnDec(ifn["d"].asInt8()), mtk::fnInc(ifn["i"].asInt8()));
            });
}

inline void  copy(mtk::fnExt& result, const qpid::types::Variant& v)
{
    result = ({   std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> ifn = /*it->second*/v.asMap();
                    mtk::fnExt(mtk::fnDec(ifn["d"].asInt8()), mtk::fnInc(ifn["i"].asInt8()));
            });
}

inline void   copy(std::string& result, const qpid::types::Variant& v)
{
    result = v.asString();
}



inline void   copy(char& result, const qpid::types::Variant& v)
{
    result = v.asInt8();
}


inline void copy(mtk::DateTime& result, const qpid::types::Variant& v)
{
    result =  WARNING_do_not_use_it__I_coul_kill_you_for_it__get_DateTime_from_time_quantity(mtk::dtTimeQuantity(mtk::dtTimeQuantitySerialNumber(v.asDouble())));
}

inline void copy(mtk::dtTimeQuantity& result, const qpid::types::Variant& v)
{
    result =  mtk::dtTimeQuantity(mtk::dtTimeQuantitySerialNumber(v.asDouble()));
}

inline void copy(int8_t& result, const qpid::types::Variant& v)
{
    result =  v.asInt8();
}

inline void copy(int16_t& result, const qpid::types::Variant& v)
{
    result =  v.asInt16();
}

inline void copy(int32_t& result, const qpid::types::Variant& v)
{
    result =  v.asInt32();
}

inline void copy(bool& result, const qpid::types::Variant& v)
{
    result =  v.asBool();
}

inline void copy(mtk::Double& result, const qpid::types::Variant& v)
{
    result =  v.asDouble();
}


template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v)
{
    T temp(__internal_get_default((T*)0));
    copy(temp, v);
    result = temp;
}


template<typename T>
void  copy (mtk::list<T>& result, const qpid::types::Variant& v)
{
    const qpid::types::Variant::List& l = v.asList();
    std::list<qpid::types::Variant>::const_iterator it = l.begin();
    while (it!= l.end())
    {
        T temp(__internal_get_default((T*)0));
        copy(temp, *it);
        result.push_back(temp);
        ++it;
    }
}



    inline void __internal_add2map (qpid::types::Variant::Map& map, const std::string& a, const std::string& key)
    {
        map[key] = a;
    }

    inline void __internal_add2map (qpid::types::Variant::Map& map, const mtk::FixedNumber& a, const std::string& key)
    {
        map[key] = QPID_DESCOMPOSE_FIXED_NUMBER(a);
    }
    inline void __internal_add2map (qpid::types::Variant::Map& map, const mtk::fnExt& a, const std::string& key)
    {
        map[key] = QPID_DESCOMPOSE_FN_EXT(a);
    }

    inline void __internal_add2map (qpid::types::Variant::Map& map, const mtk::Double& a, const std::string& key)
    {
        map[key] = a.get()._0;
    }


    #define REGISTER_LIST_BASIC_TYPE(__TYPE__)         inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<__TYPE__>& l, const std::string& key)            {                qpid::types::Variant::List list;                                mtk::list<__TYPE__>::const_iterator it = l.begin();                while (it != l.end())                {                    list.push_back(*it);                    ++it;                }                                map[key] = list;            }    

    REGISTER_LIST_BASIC_TYPE(std::string)
    
    

    //-----------------------------------------------------
    
    inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<mtk::DateTime>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        mtk::list<mtk::DateTime>::const_iterator it = l.begin();
        while (it != l.end())
        {
            list.push_back(double(it->__WARNING_NOT_CALL_IT_internal_use_GetTimeQuantitySerialNumber().WarningDontDoThisGetInternal()));
            ++it;
        }
        
        map[key] = list;
    }
    
    inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<mtk::dtTimeQuantity>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        mtk::list<mtk::dtTimeQuantity>::const_iterator it = l.begin();
        while (it != l.end())
        {
            list.push_back(double(it->GetQuantitySerialNumber().WarningDontDoThisGetInternal()));
            ++it;
        }
        
        map[key] = list;
    }
    
    
    inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<int32_t>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        mtk::list<int32_t>::const_iterator it = l.begin();
        while (it != l.end())
        {
            list.push_back(*it);
            ++it;
        }
        
        map[key] = list;
    }

    inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<int16_t>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        mtk::list<int16_t>::const_iterator it = l.begin();
        while (it != l.end())
        {
            list.push_back(*it);
            ++it;
        }
        
        map[key] = list;
    }

    inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<int8_t>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        mtk::list<int8_t>::const_iterator it = l.begin();
        while (it != l.end())
        {
            list.push_back(*it);
            ++it;
        }
        
        map[key] = list;
    }
    
    inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<int64_t>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        mtk::list<int64_t>::const_iterator it = l.begin();
        while (it != l.end())
        {
            list.push_back(*it);
            ++it;
        }
        
        map[key] = list;
    }

    inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<bool>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        mtk::list<bool>::const_iterator it = l.begin();
        while (it != l.end())
        {
            list.push_back(*it);
            ++it;
        }
        
        map[key] = list;
    }
    
    //  for composed types
    template<typename T>
    void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<T>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        typename mtk::list<T>::const_iterator it = l.begin();
        while (it != l.end())
        {
            qpid::types::Variant::Map m;
            __internal_add2map(m, *it);
            list.push_back(m);
            ++it;
        }
        
        map[key] = list;
    }



    inline void __internal_add2map (qpid::types::Variant::Map& map, const mtk::DateTime& a, const std::string& key)
    {
        map[key] = double(a.__WARNING_NOT_CALL_IT_internal_use_GetTimeQuantitySerialNumber().WarningDontDoThisGetInternal());
    }
    inline void __internal_add2map (qpid::types::Variant::Map& map, const mtk::dtTimeQuantity& a, const std::string& key)
    {
        map[key] = double(a.GetQuantitySerialNumber().WarningDontDoThisGetInternal());
    }

    inline void __internal_add2map (qpid::types::Variant::Map& map, const int32_t& a, const std::string& key)
    {
        map[key] = int32_t(a);
    }

    inline void __internal_add2map (qpid::types::Variant::Map& map, const int16_t& a, const std::string& key)
    {
        map[key] = int16_t(a);
    }

    inline void __internal_add2map (qpid::types::Variant::Map& map, const int8_t& a, const std::string& key)
    {
        map[key] = int8_t(a);
    }
    inline void __internal_add2map (qpid::types::Variant::Map& map, const int64_t& a, const std::string& key)
    {
        map[key] = int64_t(a);
    }
    inline void __internal_add2map (qpid::types::Variant::Map& map, const bool& a, const std::string& key)
    {
        map[key] = bool(a);
    }


    template<typename T>
    void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::nullable<T>& n, const std::string& key)
    {
        if (n.HasValue())
            __internal_add2map(map, n.Get(), key);
    }

    //  for composed types
    template<typename T>
    void  __internal_add2map(qpid::types::Variant::Map& map, const T& t, const std::string& key)
    {
        qpid::types::Variant::Map m;
        __internal_add2map(m, t);
        map[key] = m;
    }




//========================================================================
//------------------------------------------------------------------------
//  I M P L E M E N T A T I O N
//  internal fordward declarations


pub_enter::pub_enter (   const mtk::msg::sub_process_info&  _process_info,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check)
    :     process_info(_process_info),   ka_interval_send(_ka_interval_send),   ka_interval_check(_ka_interval_check) 
       , __internal_warning_control_fields(0)
    {  
    }



void  pub_enter::check_recomended(void) const
{

}

void pub_enter::before_send(void) const
{

}




pub_keep_alive_srv::pub_keep_alive_srv (   const mtk::msg::sub_process_info&  _process_info,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check)
    :     process_info(_process_info),   ka_interval_send(_ka_interval_send),   ka_interval_check(_ka_interval_check) 
       , __internal_warning_control_fields(0)
    {  
    }



void  pub_keep_alive_srv::check_recomended(void) const
{

}

void pub_keep_alive_srv::before_send(void) const
{

}




pub_keep_alive_cli::pub_keep_alive_cli ( const pub_keep_alive_srv&  parent,   const mtk::acs::msg::res_login::IC_session_info&  _login_confirmation)
    :  pub_keep_alive_srv(parent),   login_confirmation(_login_confirmation) 
       , __internal_warning_control_fields(0)
    {  
    }



void  pub_keep_alive_cli::check_recomended(void) const
{

}

void pub_keep_alive_cli::before_send(void) const
{

}




pub_exit::pub_exit (   const mtk::msg::sub_process_info&  _process_info,   const std::string&  _reason)
    :     process_info(_process_info),   reason(_reason) 
       , __internal_warning_control_fields(0)
    {  
    }



void  pub_exit::check_recomended(void) const
{

}

void pub_exit::before_send(void) const
{

}




pub_alarm::pub_alarm (   const mtk::msg::sub_process_info&  _process_info,   const std::string&  _code_source,   const std::string&  _subject,   const std::string&  _message,   const mtk::alEnPriority&  _priority,   const mtk::alEnType&  _type,   const mtk::DateTime&  _dateTime_generated,   const int16_t&  _alarm_id)
    :     process_info(_process_info),   code_source(_code_source),   subject(_subject),   message(_message),   priority(_priority),   type(_type),   dateTime_generated(_dateTime_generated),   alarm_id(_alarm_id) 
       , __internal_warning_control_fields(0)
    {  
    }



void  pub_alarm::check_recomended(void) const
{

}

void pub_alarm::before_send(void) const
{

}




req_command2::req_command2 (   const mtk::msg::sub_request_info&  _request_info,   const std::string&  _broker_code,   const mtk::msg::sub_process_info&  _proc_info__destination,   const std::string&  _command_line)
    :     request_info(_request_info),   broker_code(_broker_code),   proc_info__destination(_proc_info__destination),   command_line(_command_line) 
       
    {  
    }



void  req_command2::check_recomended(void) const
{

}

void req_command2::before_send(void) const
{

}




req_command_srv::req_command_srv ( const req_command2&  parent)
    :  req_command2(parent) 
       , __internal_warning_control_fields(0)
    {  
    }



void  req_command_srv::check_recomended(void) const
{

}

void req_command_srv::before_send(void) const
{

}




req_command_cli::req_command_cli ( const req_command2&  parent)
    :  req_command2(parent) 
       , __internal_warning_control_fields(0)
    {  
    }



void  req_command_cli::check_recomended(void) const
{

}

void req_command_cli::before_send(void) const
{

}




sub_command_rd::sub_command_rd (   const std::string&  _text)
    :     text(_text) 
       
    {  
    }



void  sub_command_rd::check_recomended(void) const
{

}

void sub_command_rd::before_send(void) const
{

}




res_command::res_command (   const mtk::msg::sub_r_response&  _response_info,   const sub_command_rd&  _response_data)
    :     response_info(_response_info),   response_data(_response_data) 
       , __internal_warning_control_fields(0)
    {  
    }



void  res_command::check_recomended(void) const
{

}

void res_command::before_send(void) const
{

}




pub_central_keep_alive::pub_central_keep_alive (   const mtk::msg::sub_process_info&  _process_info,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check,   const bool&  _is_production)
    :     process_info(_process_info),   ka_interval_send(_ka_interval_send),   ka_interval_check(_ka_interval_check),   is_production(_is_production) 
       , __internal_warning_control_fields(0)
    {  
    }



void  pub_central_keep_alive::check_recomended(void) const
{

}

void pub_central_keep_alive::before_send(void) const
{

}



    //    generate_class_qpid_variant_in_impl
    
pub_enter__qpid_map::pub_enter__qpid_map (   const mtk::msg::sub_process_info&  _process_info,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check)
      :  m_static( 
   _process_info,
   _ka_interval_send,
   _ka_interval_check) 
    {  
    }



    qpid::types::Variant::Map   pub_enter__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
pub_keep_alive_srv__qpid_map::pub_keep_alive_srv__qpid_map (   const mtk::msg::sub_process_info&  _process_info,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check)
      :  m_static( 
   _process_info,
   _ka_interval_send,
   _ka_interval_check) 
    {  
    }



    qpid::types::Variant::Map   pub_keep_alive_srv__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
pub_keep_alive_cli__qpid_map::pub_keep_alive_cli__qpid_map ( const pub_keep_alive_srv&  parent,   const mtk::acs::msg::res_login::IC_session_info&  _login_confirmation)
      :  m_static( 
parent,
   _login_confirmation) 
    {  
    }



    qpid::types::Variant::Map   pub_keep_alive_cli__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
pub_exit__qpid_map::pub_exit__qpid_map (   const mtk::msg::sub_process_info&  _process_info,   const std::string&  _reason)
      :  m_static( 
   _process_info,
   _reason) 
    {  
    }



    qpid::types::Variant::Map   pub_exit__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
pub_alarm__qpid_map::pub_alarm__qpid_map (   const mtk::msg::sub_process_info&  _process_info,   const std::string&  _code_source,   const std::string&  _subject,   const std::string&  _message,   const mtk::alEnPriority&  _priority,   const mtk::alEnType&  _type,   const mtk::DateTime&  _dateTime_generated,   const int16_t&  _alarm_id)
      :  m_static( 
   _process_info,
   _code_source,
   _subject,
   _message,
   _priority,
   _type,
   _dateTime_generated,
   _alarm_id) 
    {  
    }



    qpid::types::Variant::Map   pub_alarm__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
req_command2__qpid_map::req_command2__qpid_map (   const mtk::msg::sub_request_info&  _request_info,   const std::string&  _broker_code,   const mtk::msg::sub_process_info&  _proc_info__destination,   const std::string&  _command_line)
      :  m_static( 
   _request_info,
   _broker_code,
   _proc_info__destination,
   _command_line) 
    {  
    }



    //    generate_class_qpid_variant_in_impl
    
req_command_srv__qpid_map::req_command_srv__qpid_map ( const req_command2&  parent)
      :  m_static( 
parent) 
    {  
    }



    qpid::types::Variant::Map   req_command_srv__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
req_command_cli__qpid_map::req_command_cli__qpid_map ( const req_command2&  parent)
      :  m_static( 
parent) 
    {  
    }



    qpid::types::Variant::Map   req_command_cli__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
sub_command_rd__qpid_map::sub_command_rd__qpid_map (   const std::string&  _text)
      :  m_static( 
   _text) 
    {  
    }



    //    generate_class_qpid_variant_in_impl
    
res_command__qpid_map::res_command__qpid_map (   const mtk::msg::sub_r_response&  _response_info,   const sub_command_rd&  _response_data)
      :  m_static( 
   _response_info,
   _response_data) 
    {  
    }



    qpid::types::Variant::Map   res_command__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
pub_central_keep_alive__qpid_map::pub_central_keep_alive__qpid_map (   const mtk::msg::sub_process_info&  _process_info,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check,   const bool&  _is_production)
      :  m_static( 
   _process_info,
   _ka_interval_send,
   _ka_interval_check,
   _is_production) 
    {  
    }



    qpid::types::Variant::Map   pub_central_keep_alive__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

std::ostream& operator<< (std::ostream& o, const pub_enter & c)
{
    o << "{ "

        << "process_info:"<< c.process_info<<"  "        << "ka_interval_send:"<<   c.ka_interval_send << "  "        << "ka_interval_check:"<<   c.ka_interval_check << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const pub_enter & c)
{
    o << YAML::BeginMap

        << YAML::Key << "process_info"  << YAML::Value << c.process_info        << YAML::Key << "ka_interval_send"  << YAML::Value <<   c.ka_interval_send        << YAML::Key << "ka_interval_check"  << YAML::Value <<   c.ka_interval_check
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, pub_enter & c)
{


        node["process_info"]  >> c.process_info;
        node["ka_interval_send"]  >> c.ka_interval_send;
        node["ka_interval_check"]  >> c.ka_interval_check;


};


std::ostream& operator<< (std::ostream& o, const pub_keep_alive_srv & c)
{
    o << "{ "

        << "process_info:"<< c.process_info<<"  "        << "ka_interval_send:"<<   c.ka_interval_send << "  "        << "ka_interval_check:"<<   c.ka_interval_check << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const pub_keep_alive_srv & c)
{
    o << YAML::BeginMap

        << YAML::Key << "process_info"  << YAML::Value << c.process_info        << YAML::Key << "ka_interval_send"  << YAML::Value <<   c.ka_interval_send        << YAML::Key << "ka_interval_check"  << YAML::Value <<   c.ka_interval_check
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, pub_keep_alive_srv & c)
{


        node["process_info"]  >> c.process_info;
        node["ka_interval_send"]  >> c.ka_interval_send;
        node["ka_interval_check"]  >> c.ka_interval_check;


};


std::ostream& operator<< (std::ostream& o, const pub_keep_alive_cli & c)
{
    o << "{ "
    << "("  <<  static_cast<const pub_keep_alive_srv&>(c)  << ")" 
        << "login_confirmation:"<< c.login_confirmation<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const pub_keep_alive_cli & c)
{
    o << YAML::BeginMap
    << YAML::Key << "pub_keep_alive_srv" <<  YAML::Value << static_cast<const pub_keep_alive_srv&>(c)  
        << YAML::Key << "login_confirmation"  << YAML::Value << c.login_confirmation
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, pub_keep_alive_cli & c)
{

    node["pub_keep_alive_srv"]   >>   static_cast<pub_keep_alive_srv&>(c)  ;

        node["login_confirmation"]  >> c.login_confirmation;


};


std::ostream& operator<< (std::ostream& o, const pub_exit & c)
{
    o << "{ "

        << "process_info:"<< c.process_info<<"  "        << "reason:"<<   c.reason << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const pub_exit & c)
{
    o << YAML::BeginMap

        << YAML::Key << "process_info"  << YAML::Value << c.process_info        << YAML::Key << "reason"  << YAML::Value <<   c.reason
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, pub_exit & c)
{


        node["process_info"]  >> c.process_info;
        node["reason"]  >> c.reason;


};


std::ostream& operator<< (std::ostream& o, const pub_alarm & c)
{
    o << "{ "

        << "process_info:"<< c.process_info<<"  "        << "code_source:"<<   c.code_source << "  "        << "subject:"<<   c.subject << "  "        << "message:"<<   c.message << "  "        << "priority:"<< c.priority<<"  "        << "type:"<< c.type<<"  "        << "dateTime_generated:"<<   c.dateTime_generated << "  "        << "alarm_id:"<<   c.alarm_id << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const pub_alarm & c)
{
    o << YAML::BeginMap

        << YAML::Key << "process_info"  << YAML::Value << c.process_info        << YAML::Key << "code_source"  << YAML::Value <<   c.code_source        << YAML::Key << "subject"  << YAML::Value <<   c.subject        << YAML::Key << "message"  << YAML::Value <<   c.message        << YAML::Key << "priority"  << YAML::Value << c.priority        << YAML::Key << "type"  << YAML::Value << c.type        << YAML::Key << "dateTime_generated"  << YAML::Value <<   c.dateTime_generated        << YAML::Key << "alarm_id"  << YAML::Value <<   c.alarm_id
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, pub_alarm & c)
{


        node["process_info"]  >> c.process_info;
        node["code_source"]  >> c.code_source;
        node["subject"]  >> c.subject;
        node["message"]  >> c.message;
        node["priority"]  >> c.priority;
        node["type"]  >> c.type;
        node["dateTime_generated"]  >> c.dateTime_generated;
        node["alarm_id"]  >> c.alarm_id;


};


std::ostream& operator<< (std::ostream& o, const req_command2 & c)
{
    o << "{ "

        << "request_info:"<< c.request_info<<"  "        << "broker_code:"<<   c.broker_code << "  "        << "proc_info__destination:"<< c.proc_info__destination<<"  "        << "command_line:"<<   c.command_line << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const req_command2 & c)
{
    o << YAML::BeginMap

        << YAML::Key << "request_info"  << YAML::Value << c.request_info        << YAML::Key << "broker_code"  << YAML::Value <<   c.broker_code        << YAML::Key << "proc_info__destination"  << YAML::Value << c.proc_info__destination        << YAML::Key << "command_line"  << YAML::Value <<   c.command_line
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, req_command2 & c)
{


        node["request_info"]  >> c.request_info;
        node["broker_code"]  >> c.broker_code;
        node["proc_info__destination"]  >> c.proc_info__destination;
        node["command_line"]  >> c.command_line;


};


std::ostream& operator<< (std::ostream& o, const req_command_srv & c)
{
    o << "{ "
    << "("  <<  static_cast<const req_command2&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const req_command_srv & c)
{
    o << YAML::BeginMap
    << YAML::Key << "req_command2" <<  YAML::Value << static_cast<const req_command2&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, req_command_srv & c)
{

    node["req_command2"]   >>   static_cast<req_command2&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const req_command_cli & c)
{
    o << "{ "
    << "("  <<  static_cast<const req_command2&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const req_command_cli & c)
{
    o << YAML::BeginMap
    << YAML::Key << "req_command2" <<  YAML::Value << static_cast<const req_command2&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, req_command_cli & c)
{

    node["req_command2"]   >>   static_cast<req_command2&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const sub_command_rd & c)
{
    o << "{ "

        << "text:"<<   c.text << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_command_rd & c)
{
    o << YAML::BeginMap

        << YAML::Key << "text"  << YAML::Value <<   c.text
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_command_rd & c)
{


        node["text"]  >> c.text;


};


std::ostream& operator<< (std::ostream& o, const res_command & c)
{
    o << "{ "

        << "response_info:"<< c.response_info<<"  "        << "response_data:"<< c.response_data<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const res_command & c)
{
    o << YAML::BeginMap

        << YAML::Key << "response_info"  << YAML::Value << c.response_info        << YAML::Key << "response_data"  << YAML::Value << c.response_data
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, res_command & c)
{


        node["response_info"]  >> c.response_info;
        node["response_data"]  >> c.response_data;


};


std::ostream& operator<< (std::ostream& o, const pub_central_keep_alive & c)
{
    o << "{ "

        << "process_info:"<< c.process_info<<"  "        << "ka_interval_send:"<<   c.ka_interval_send << "  "        << "ka_interval_check:"<<   c.ka_interval_check << "  "        << "is_production:"<< c.is_production<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const pub_central_keep_alive & c)
{
    o << YAML::BeginMap

        << YAML::Key << "process_info"  << YAML::Value << c.process_info        << YAML::Key << "ka_interval_send"  << YAML::Value <<   c.ka_interval_send        << YAML::Key << "ka_interval_check"  << YAML::Value <<   c.ka_interval_check        << YAML::Key << "is_production"  << YAML::Value << c.is_production
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, pub_central_keep_alive & c)
{


        node["process_info"]  >> c.process_info;
        node["ka_interval_send"]  >> c.ka_interval_send;
        node["ka_interval_check"]  >> c.ka_interval_check;
        node["is_production"]  >> c.is_production;


};


bool operator== (const pub_enter& a, const pub_enter& b)
{
    return (          a.process_info ==  b.process_info  &&          a.ka_interval_send ==  b.ka_interval_send  &&          a.ka_interval_check ==  b.ka_interval_check  &&   true  );
};

bool operator!= (const pub_enter& a, const pub_enter& b)
{
    return !(a==b);
};



bool operator== (const pub_keep_alive_srv& a, const pub_keep_alive_srv& b)
{
    return (          a.process_info ==  b.process_info  &&          a.ka_interval_send ==  b.ka_interval_send  &&          a.ka_interval_check ==  b.ka_interval_check  &&   true  );
};

bool operator!= (const pub_keep_alive_srv& a, const pub_keep_alive_srv& b)
{
    return !(a==b);
};



bool operator== (const pub_keep_alive_cli& a, const pub_keep_alive_cli& b)
{
    return ( (static_cast<const pub_keep_alive_srv&>(a)   ==  static_cast<const pub_keep_alive_srv&>(b))  &&           a.login_confirmation ==  b.login_confirmation  &&   true  );
};

bool operator!= (const pub_keep_alive_cli& a, const pub_keep_alive_cli& b)
{
    return !(a==b);
};



bool operator== (const pub_exit& a, const pub_exit& b)
{
    return (          a.process_info ==  b.process_info  &&          a.reason ==  b.reason  &&   true  );
};

bool operator!= (const pub_exit& a, const pub_exit& b)
{
    return !(a==b);
};



bool operator== (const pub_alarm& a, const pub_alarm& b)
{
    return (          a.process_info ==  b.process_info  &&          a.code_source ==  b.code_source  &&          a.subject ==  b.subject  &&          a.message ==  b.message  &&          a.priority ==  b.priority  &&          a.type ==  b.type  &&          a.dateTime_generated ==  b.dateTime_generated  &&          a.alarm_id ==  b.alarm_id  &&   true  );
};

bool operator!= (const pub_alarm& a, const pub_alarm& b)
{
    return !(a==b);
};



bool operator== (const req_command2& a, const req_command2& b)
{
    return (          a.request_info ==  b.request_info  &&          a.broker_code ==  b.broker_code  &&          a.proc_info__destination ==  b.proc_info__destination  &&          a.command_line ==  b.command_line  &&   true  );
};

bool operator!= (const req_command2& a, const req_command2& b)
{
    return !(a==b);
};



bool operator== (const req_command_srv& a, const req_command_srv& b)
{
    return ( (static_cast<const req_command2&>(a)   ==  static_cast<const req_command2&>(b))  &&    true  );
};

bool operator!= (const req_command_srv& a, const req_command_srv& b)
{
    return !(a==b);
};



bool operator== (const req_command_cli& a, const req_command_cli& b)
{
    return ( (static_cast<const req_command2&>(a)   ==  static_cast<const req_command2&>(b))  &&    true  );
};

bool operator!= (const req_command_cli& a, const req_command_cli& b)
{
    return !(a==b);
};



bool operator== (const sub_command_rd& a, const sub_command_rd& b)
{
    return (          a.text ==  b.text  &&   true  );
};

bool operator!= (const sub_command_rd& a, const sub_command_rd& b)
{
    return !(a==b);
};



bool operator== (const res_command& a, const res_command& b)
{
    return (          a.response_info ==  b.response_info  &&          a.response_data ==  b.response_data  &&   true  );
};

bool operator!= (const res_command& a, const res_command& b)
{
    return !(a==b);
};



bool operator== (const pub_central_keep_alive& a, const pub_central_keep_alive& b)
{
    return (          a.process_info ==  b.process_info  &&          a.ka_interval_send ==  b.ka_interval_send  &&          a.ka_interval_check ==  b.ka_interval_check  &&          a.is_production ==  b.is_production  &&   true  );
};

bool operator!= (const pub_central_keep_alive& a, const pub_central_keep_alive& b)
{
    return !(a==b);
};




void  copy (pub_enter& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field process_info on message pub_enter::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_info, it->second);
                        //__internal_qpid_fill(c.process_info, it->second.asMap());
//   field_type

                    it = mv.find("kas");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field ka_interval_send on message pub_enter::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.ka_interval_send, it->second);
                        //c.ka_interval_send = it->second;
//   field_type

                    it = mv.find("kac");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field ka_interval_check on message pub_enter::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.ka_interval_check, it->second);
                        //c.ka_interval_check = it->second;

        c.check_recomended ();
    }


void  copy (pub_enter__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const pub_enter& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.process_info, std::string("pi"));
//  field_type
        __internal_add2map(map, a.ka_interval_send, std::string("kas"));
//  field_type
        __internal_add2map(map, a.ka_interval_check, std::string("kac"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const pub_enter__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_enter>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_enter__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (pub_keep_alive_srv& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field process_info on message pub_keep_alive_srv::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_info, it->second);
                        //__internal_qpid_fill(c.process_info, it->second.asMap());
//   field_type

                    it = mv.find("kas");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field ka_interval_send on message pub_keep_alive_srv::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.ka_interval_send, it->second);
                        //c.ka_interval_send = it->second;
//   field_type

                    it = mv.find("kac");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field ka_interval_check on message pub_keep_alive_srv::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.ka_interval_check, it->second);
                        //c.ka_interval_check = it->second;

        c.check_recomended ();
    }


void  copy (pub_keep_alive_srv__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const pub_keep_alive_srv& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.process_info, std::string("pi"));
//  field_type
        __internal_add2map(map, a.ka_interval_send, std::string("kas"));
//  field_type
        __internal_add2map(map, a.ka_interval_check, std::string("kac"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const pub_keep_alive_srv__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_keep_alive_srv>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_keep_alive_srv__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (pub_keep_alive_cli& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<pub_keep_alive_srv&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("lgc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field login_confirmation on message pub_keep_alive_cli::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.login_confirmation, it->second);
                        //__internal_qpid_fill(c.login_confirmation, it->second.asMap());

        c.check_recomended ();
    }


void  copy (pub_keep_alive_cli__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const pub_keep_alive_cli& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const pub_keep_alive_srv&>(a));

//  sub_msg_type
        __internal_add2map(map, a.login_confirmation, std::string("lgc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const pub_keep_alive_cli__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_keep_alive_cli>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_keep_alive_cli__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (pub_exit& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field process_info on message pub_exit::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_info, it->second);
                        //__internal_qpid_fill(c.process_info, it->second.asMap());
//   field_type

                    it = mv.find("r");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reason on message pub_exit::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reason, it->second);
                        //c.reason = it->second;

        c.check_recomended ();
    }


void  copy (pub_exit__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const pub_exit& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.process_info, std::string("pi"));
//  field_type
        __internal_add2map(map, a.reason, std::string("r"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const pub_exit__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_exit>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_exit__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (pub_alarm& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field process_info on message pub_alarm::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_info, it->second);
                        //__internal_qpid_fill(c.process_info, it->second.asMap());
//   field_type

                    it = mv.find("cs");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field code_source on message pub_alarm::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.code_source, it->second);
                        //c.code_source = it->second;
//   field_type

                    it = mv.find("sbj");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field subject on message pub_alarm::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.subject, it->second);
                        //c.subject = it->second;
//   field_type

                    it = mv.find("msg");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field message on message pub_alarm::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.message, it->second);
                        //c.message = it->second;
//   sub_msg_type

                    it = mv.find("p");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field priority on message pub_alarm::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.priority, it->second);
                        //__internal_qpid_fill(c.priority, it->second.asMap());
//   sub_msg_type

                    it = mv.find("ty");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field type on message pub_alarm::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.type, it->second);
                        //__internal_qpid_fill(c.type, it->second.asMap());
//   field_type

                    it = mv.find("dtg");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field dateTime_generated on message pub_alarm::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.dateTime_generated, it->second);
                        //c.dateTime_generated = it->second;
//   field_type

                    it = mv.find("ai");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field alarm_id on message pub_alarm::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.alarm_id, it->second);
                        //c.alarm_id = it->second;

        c.check_recomended ();
    }


void  copy (pub_alarm__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const pub_alarm& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.process_info, std::string("pi"));
//  field_type
        __internal_add2map(map, a.code_source, std::string("cs"));
//  field_type
        __internal_add2map(map, a.subject, std::string("sbj"));
//  field_type
        __internal_add2map(map, a.message, std::string("msg"));
//  sub_msg_type
        __internal_add2map(map, a.priority, std::string("p"));
//  sub_msg_type
        __internal_add2map(map, a.type, std::string("ty"));
//  field_type
        __internal_add2map(map, a.dateTime_generated, std::string("dtg"));
//  field_type
        __internal_add2map(map, a.alarm_id, std::string("ai"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const pub_alarm__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_alarm>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_alarm__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (req_command2& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rqi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_info on message req_command2::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_info, it->second);
                        //__internal_qpid_fill(c.request_info, it->second.asMap());
//   field_type

                    it = mv.find("bc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field broker_code on message req_command2::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.broker_code, it->second);
                        //c.broker_code = it->second;
//   sub_msg_type

                    it = mv.find("pd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field proc_info__destination on message req_command2::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.proc_info__destination, it->second);
                        //__internal_qpid_fill(c.proc_info__destination, it->second.asMap());
//   field_type

                    it = mv.find("cl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field command_line on message req_command2::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.command_line, it->second);
                        //c.command_line = it->second;

        c.check_recomended ();
    }


void  copy (req_command2__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const req_command2& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.request_info, std::string("rqi"));
//  field_type
        __internal_add2map(map, a.broker_code, std::string("bc"));
//  sub_msg_type
        __internal_add2map(map, a.proc_info__destination, std::string("pd"));
//  field_type
        __internal_add2map(map, a.command_line, std::string("cl"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const req_command2__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_command2>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_command2__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (req_command_srv& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<req_command2&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

        c.check_recomended ();
    }


void  copy (req_command_srv__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const req_command_srv& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const req_command2&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const req_command_srv__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_command_srv>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_command_srv__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (req_command_cli& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<req_command2&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

        c.check_recomended ();
    }


void  copy (req_command_cli__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const req_command_cli& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const req_command2&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const req_command_cli__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_command_cli>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_command_cli__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (sub_command_rd& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("txt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field text on message sub_command_rd::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.text, it->second);
                        //c.text = it->second;

        c.check_recomended ();
    }


void  copy (sub_command_rd__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const sub_command_rd& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.text, std::string("txt"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const sub_command_rd__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_command_rd>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_command_rd__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (res_command& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rsi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field response_info on message res_command::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.response_info, it->second);
                        //__internal_qpid_fill(c.response_info, it->second.asMap());
//   sub_msg_type

                    it = mv.find("rsd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field response_data on message res_command::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.response_data, it->second);
                        //__internal_qpid_fill(c.response_data, it->second.asMap());

        c.check_recomended ();
    }


void  copy (res_command__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const res_command& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.response_info, std::string("rsi"));
//  sub_msg_type
        __internal_add2map(map, a.response_data, std::string("rsd"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const res_command__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_command>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_command__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (pub_central_keep_alive& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field process_info on message pub_central_keep_alive::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_info, it->second);
                        //__internal_qpid_fill(c.process_info, it->second.asMap());
//   field_type

                    it = mv.find("kas");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field ka_interval_send on message pub_central_keep_alive::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.ka_interval_send, it->second);
                        //c.ka_interval_send = it->second;
//   field_type

                    it = mv.find("kac");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field ka_interval_check on message pub_central_keep_alive::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.ka_interval_check, it->second);
                        //c.ka_interval_check = it->second;
//   sub_msg_type

                    it = mv.find("prd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field is_production on message pub_central_keep_alive::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.is_production, it->second);
                        //__internal_qpid_fill(c.is_production, it->second.asMap());

        c.check_recomended ();
    }


void  copy (pub_central_keep_alive__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const pub_central_keep_alive& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.process_info, std::string("pi"));
//  field_type
        __internal_add2map(map, a.ka_interval_send, std::string("kas"));
//  field_type
        __internal_add2map(map, a.ka_interval_check, std::string("kac"));
//  sub_msg_type
        __internal_add2map(map, a.is_production, std::string("prd"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const pub_central_keep_alive__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_central_keep_alive>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_central_keep_alive__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)

qpid::types::Variant::Map   pub_enter::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;


//  sub_msg_type
//        content["pi"] =  qpidmsg_coded_as_qpid_Map(this->process_info);
        __internal_add2map(content, this->process_info, std::string("pi"));
//  field_type
//        content["kas"] = this->ka_interval_send;
        __internal_add2map(content, this->ka_interval_send, std::string("kas"));
//  field_type
//        content["kac"] = this->ka_interval_check;
        __internal_add2map(content, this->ka_interval_check, std::string("kac"));



    
    return content;
};




qpid::types::Variant::Map   pub_keep_alive_srv::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;


//  sub_msg_type
//        content["pi"] =  qpidmsg_coded_as_qpid_Map(this->process_info);
        __internal_add2map(content, this->process_info, std::string("pi"));
//  field_type
//        content["kas"] = this->ka_interval_send;
        __internal_add2map(content, this->ka_interval_send, std::string("kas"));
//  field_type
//        content["kac"] = this->ka_interval_check;
        __internal_add2map(content, this->ka_interval_check, std::string("kac"));



    
    return content;
};




qpid::types::Variant::Map   pub_keep_alive_cli::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const pub_keep_alive_srv&>(*this));

//  sub_msg_type
//        content["lgc"] =  qpidmsg_coded_as_qpid_Map(this->login_confirmation);
        __internal_add2map(content, this->login_confirmation, std::string("lgc"));



    
    return content;
};




qpid::types::Variant::Map   pub_exit::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;


//  sub_msg_type
//        content["pi"] =  qpidmsg_coded_as_qpid_Map(this->process_info);
        __internal_add2map(content, this->process_info, std::string("pi"));
//  field_type
//        content["r"] = this->reason;
        __internal_add2map(content, this->reason, std::string("r"));



    
    return content;
};




qpid::types::Variant::Map   pub_alarm::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;


//  sub_msg_type
//        content["pi"] =  qpidmsg_coded_as_qpid_Map(this->process_info);
        __internal_add2map(content, this->process_info, std::string("pi"));
//  field_type
//        content["cs"] = this->code_source;
        __internal_add2map(content, this->code_source, std::string("cs"));
//  field_type
//        content["sbj"] = this->subject;
        __internal_add2map(content, this->subject, std::string("sbj"));
//  field_type
//        content["msg"] = this->message;
        __internal_add2map(content, this->message, std::string("msg"));
//  sub_msg_type
//        content["p"] =  qpidmsg_coded_as_qpid_Map(this->priority);
        __internal_add2map(content, this->priority, std::string("p"));
//  sub_msg_type
//        content["ty"] =  qpidmsg_coded_as_qpid_Map(this->type);
        __internal_add2map(content, this->type, std::string("ty"));
//  field_type
//        content["dtg"] = this->dateTime_generated;
        __internal_add2map(content, this->dateTime_generated, std::string("dtg"));
//  field_type
//        content["ai"] = this->alarm_id;
        __internal_add2map(content, this->alarm_id, std::string("ai"));



    
    return content;
};




qpid::types::Variant::Map   req_command_srv::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const req_command2&>(*this));




    
    return content;
};




qpid::types::Variant::Map   req_command_cli::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const req_command2&>(*this));




    
    return content;
};




qpid::types::Variant::Map   res_command::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;


//  sub_msg_type
//        content["rsi"] =  qpidmsg_coded_as_qpid_Map(this->response_info);
        __internal_add2map(content, this->response_info, std::string("rsi"));
//  sub_msg_type
//        content["rsd"] =  qpidmsg_coded_as_qpid_Map(this->response_data);
        __internal_add2map(content, this->response_data, std::string("rsd"));



    
    return content;
};




qpid::types::Variant::Map   pub_central_keep_alive::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;


//  sub_msg_type
//        content["pi"] =  qpidmsg_coded_as_qpid_Map(this->process_info);
        __internal_add2map(content, this->process_info, std::string("pi"));
//  field_type
//        content["kas"] = this->ka_interval_send;
        __internal_add2map(content, this->ka_interval_send, std::string("kas"));
//  field_type
//        content["kac"] = this->ka_interval_check;
        __internal_add2map(content, this->ka_interval_check, std::string("kac"));
//  sub_msg_type
//        content["prd"] =  qpidmsg_coded_as_qpid_Map(this->is_production);
        __internal_add2map(content, this->is_production, std::string("prd"));



    
    return content;
};




    pub_enter  __internal_get_default(pub_enter*)
    {
        return pub_enter(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_info*)0),
//   field_type
   __internal_get_default ((mtk::dtTimeQuantity*)0),
//   field_type
   __internal_get_default ((mtk::dtTimeQuantity*)0)
            );
    }
    
    pub_keep_alive_srv  __internal_get_default(pub_keep_alive_srv*)
    {
        return pub_keep_alive_srv(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_info*)0),
//   field_type
   __internal_get_default ((mtk::dtTimeQuantity*)0),
//   field_type
   __internal_get_default ((mtk::dtTimeQuantity*)0)
            );
    }
    
    pub_keep_alive_cli  __internal_get_default(pub_keep_alive_cli*)
    {
        return pub_keep_alive_cli(
__internal_get_default((pub_keep_alive_srv*)0), //   sub_msg_type
   __internal_get_default((mtk::acs::msg::res_login::IC_session_info*)0)
            );
    }
    
    pub_exit  __internal_get_default(pub_exit*)
    {
        return pub_exit(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_info*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    pub_alarm  __internal_get_default(pub_alarm*)
    {
        return pub_alarm(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_info*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((mtk::alEnPriority*)0),
//   sub_msg_type
   __internal_get_default((mtk::alEnType*)0),
//   field_type
   __internal_get_default ((mtk::DateTime*)0),
//   field_type
   __internal_get_default ((int16_t*)0)
            );
    }
    
    req_command2  __internal_get_default(req_command2*)
    {
        return req_command2(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_request_info*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_info*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    req_command_srv  __internal_get_default(req_command_srv*)
    {
        return req_command_srv(
__internal_get_default((req_command2*)0)
            );
    }
    
    req_command_cli  __internal_get_default(req_command_cli*)
    {
        return req_command_cli(
__internal_get_default((req_command2*)0)
            );
    }
    
    sub_command_rd  __internal_get_default(sub_command_rd*)
    {
        return sub_command_rd(
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    res_command  __internal_get_default(res_command*)
    {
        return res_command(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_r_response*)0),
//   sub_msg_type
   __internal_get_default((sub_command_rd*)0)
            );
    }
    
    pub_central_keep_alive  __internal_get_default(pub_central_keep_alive*)
    {
        return pub_central_keep_alive(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_info*)0),
//   field_type
   __internal_get_default ((mtk::dtTimeQuantity*)0),
//   field_type
   __internal_get_default ((mtk::dtTimeQuantity*)0),
//   sub_msg_type
   __internal_get_default((bool*)0)
            );
    }
    
pub_enter::pub_enter (const qpid::types::Variant::Map&  mv)
     : //   sub_msg_type
   process_info(__internal_get_default((mtk::msg::sub_process_info*)0)),
//   field_type
   ka_interval_send(__internal_get_default((mtk::dtTimeQuantity*)0)),
//   field_type
   ka_interval_check(__internal_get_default((mtk::dtTimeQuantity*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


pub_enter__qpid_map::pub_enter__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

pub_keep_alive_srv::pub_keep_alive_srv (const qpid::types::Variant::Map&  mv)
     : //   sub_msg_type
   process_info(__internal_get_default((mtk::msg::sub_process_info*)0)),
//   field_type
   ka_interval_send(__internal_get_default((mtk::dtTimeQuantity*)0)),
//   field_type
   ka_interval_check(__internal_get_default((mtk::dtTimeQuantity*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


pub_keep_alive_srv__qpid_map::pub_keep_alive_srv__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

pub_keep_alive_cli::pub_keep_alive_cli (const qpid::types::Variant::Map&  mv)
     : pub_keep_alive_srv(mv), //   sub_msg_type
   login_confirmation(__internal_get_default((mtk::acs::msg::res_login::IC_session_info*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


pub_keep_alive_cli__qpid_map::pub_keep_alive_cli__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

pub_exit::pub_exit (const qpid::types::Variant::Map&  mv)
     : //   sub_msg_type
   process_info(__internal_get_default((mtk::msg::sub_process_info*)0)),
//   field_type
   reason(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


pub_exit__qpid_map::pub_exit__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

pub_alarm::pub_alarm (const qpid::types::Variant::Map&  mv)
     : //   sub_msg_type
   process_info(__internal_get_default((mtk::msg::sub_process_info*)0)),
//   field_type
   code_source(__internal_get_default((std::string*)0)),
//   field_type
   subject(__internal_get_default((std::string*)0)),
//   field_type
   message(__internal_get_default((std::string*)0)),
//   sub_msg_type
   priority(__internal_get_default((mtk::alEnPriority*)0)),
//   sub_msg_type
   type(__internal_get_default((mtk::alEnType*)0)),
//   field_type
   dateTime_generated(__internal_get_default((mtk::DateTime*)0)),
//   field_type
   alarm_id(__internal_get_default((int16_t*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


pub_alarm__qpid_map::pub_alarm__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

req_command2::req_command2 (const qpid::types::Variant::Map&  mv)
     : //   sub_msg_type
   request_info(__internal_get_default((mtk::msg::sub_request_info*)0)),
//   field_type
   broker_code(__internal_get_default((std::string*)0)),
//   sub_msg_type
   proc_info__destination(__internal_get_default((mtk::msg::sub_process_info*)0)),
//   field_type
   command_line(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


req_command2__qpid_map::req_command2__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

req_command_srv::req_command_srv (const qpid::types::Variant::Map&  mv)
     : req_command2(mv) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


req_command_srv__qpid_map::req_command_srv__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

req_command_cli::req_command_cli (const qpid::types::Variant::Map&  mv)
     : req_command2(mv) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


req_command_cli__qpid_map::req_command_cli__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

sub_command_rd::sub_command_rd (const qpid::types::Variant::Map&  mv)
     : //   field_type
   text(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


sub_command_rd__qpid_map::sub_command_rd__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

res_command::res_command (const qpid::types::Variant::Map&  mv)
     : //   sub_msg_type
   response_info(__internal_get_default((mtk::msg::sub_r_response*)0)),
//   sub_msg_type
   response_data(__internal_get_default((sub_command_rd*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


res_command__qpid_map::res_command__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

pub_central_keep_alive::pub_central_keep_alive (const qpid::types::Variant::Map&  mv)
     : //   sub_msg_type
   process_info(__internal_get_default((mtk::msg::sub_process_info*)0)),
//   field_type
   ka_interval_send(__internal_get_default((mtk::dtTimeQuantity*)0)),
//   field_type
   ka_interval_check(__internal_get_default((mtk::dtTimeQuantity*)0)),
//   sub_msg_type
   is_production(__internal_get_default((bool*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


pub_central_keep_alive__qpid_map::pub_central_keep_alive__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    
mtk::t_qpid_filter  pub_enter::get_in_subject (const std::string& process_info_location_broker_code,const std::string& process_info_cli_srv)
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << process_info_location_broker_code << ".MON." << process_info_cli_srv << ".ENTER"));
    }
    mtk::t_qpid_filter  pub_enter::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << this->process_info.location.broker_code << ".MON." << this->process_info.cli_srv << ".ENTER"));
    }
    /*static*/  mtk::t_qpid_address  pub_enter::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  pub_enter::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  pub_keep_alive_srv::get_in_subject (const std::string& process_info_location_broker_code)
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << process_info_location_broker_code << ".MON.SRV.KA"));
    }
    mtk::t_qpid_filter  pub_keep_alive_srv::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << this->process_info.location.broker_code << ".MON.SRV.KA"));
    }
    /*static*/  mtk::t_qpid_address  pub_keep_alive_srv::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  pub_keep_alive_srv::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  pub_keep_alive_cli::get_in_subject (const std::string& process_info_location_broker_code)
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << process_info_location_broker_code << ".MON.CLI.KA"));
    }
    mtk::t_qpid_filter  pub_keep_alive_cli::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << this->process_info.location.broker_code << ".MON.CLI.KA"));
    }
    /*static*/  mtk::t_qpid_address  pub_keep_alive_cli::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  pub_keep_alive_cli::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  pub_exit::get_in_subject (const std::string& process_info_location_broker_code,const std::string& process_info_cli_srv)
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << process_info_location_broker_code << ".MON." << process_info_cli_srv << ".EXIT"));
    }
    mtk::t_qpid_filter  pub_exit::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << this->process_info.location.broker_code << ".MON." << this->process_info.cli_srv << ".EXIT"));
    }
    /*static*/  mtk::t_qpid_address  pub_exit::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  pub_exit::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  pub_alarm::get_in_subject (const std::string& process_info_location_broker_code,const std::string& process_info_cli_srv)
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << process_info_location_broker_code << ".MON." << process_info_cli_srv << ".ALARM"));
    }
    mtk::t_qpid_filter  pub_alarm::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << this->process_info.location.broker_code << ".MON." << this->process_info.cli_srv << ".ALARM"));
    }
    /*static*/  mtk::t_qpid_address  pub_alarm::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  pub_alarm::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  req_command_srv::get_in_subject (const std::string& broker_code,const std::string& proc_info__destination_location_broker_code,const std::string& proc_info__destination_location_machine,const std::string& proc_info__destination_process_name,const std::string& proc_info__destination_process_uuid)
    {
        return mtk::t_qpid_filter(MTK_SS("SYS." << broker_code << ".MON." << proc_info__destination_location_broker_code << "." << proc_info__destination_location_machine << "." << proc_info__destination_process_name << "." << proc_info__destination_process_uuid << ".COMMAND"));
    }
    mtk::t_qpid_filter  req_command_srv::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("SYS." << this->broker_code << ".MON." << this->proc_info__destination.location.broker_code << "." << this->proc_info__destination.location.machine << "." << this->proc_info__destination.process_name << "." << this->proc_info__destination.process_uuid << ".COMMAND"));
    }
    /*static*/  mtk::t_qpid_address  req_command_srv::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  req_command_srv::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  req_command_cli::get_in_subject (const std::string& proc_info__destination_location_broker_code,const std::string& proc_info__destination_location_machine,const std::string& proc_info__destination_process_name,const std::string& proc_info__destination_process_uuid)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << proc_info__destination_location_broker_code << "." << proc_info__destination_location_machine << "." << proc_info__destination_process_name << "." << proc_info__destination_process_uuid << ".COMMAND"));
    }
    mtk::t_qpid_filter  req_command_cli::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->proc_info__destination.location.broker_code << "." << this->proc_info__destination.location.machine << "." << this->proc_info__destination.process_name << "." << this->proc_info__destination.process_uuid << ".COMMAND"));
    }
    /*static*/  mtk::t_qpid_address  req_command_cli::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  req_command_cli::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  res_command::get_in_subject (const std::string& response_info_request_info_process_info_location_broker_code,const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_req_code)
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << response_info_request_info_process_info_location_broker_code << ".MON." << response_info_request_info_process_info_process_uuid << "." << response_info_request_info_req_id_req_code << ".RSCOMM"));
    }
    mtk::t_qpid_filter  res_command::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << this->response_info.request_info.process_info.location.broker_code << ".MON." << this->response_info.request_info.process_info.process_uuid << "." << this->response_info.request_info.req_id.req_code << ".RSCOMM"));
    }
    /*static*/  mtk::t_qpid_address  res_command::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  res_command::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  pub_central_keep_alive::get_in_subject (const std::string& process_info_location_broker_code)
    {
        return mtk::t_qpid_filter(MTK_SS("ALL." << process_info_location_broker_code << ".MON.LHKA"));
    }
    mtk::t_qpid_filter  pub_central_keep_alive::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("ALL." << this->process_info.location.broker_code << ".MON.LHKA"));
    }
    /*static*/  mtk::t_qpid_address  pub_central_keep_alive::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  pub_central_keep_alive::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    

};   //namespace mtk {
};   //namespace admin {
};   //namespace msg {


