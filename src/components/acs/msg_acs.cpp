
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_acs.h"

namespace mtk { 
namespace acs { 
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


req_login_key::req_login_key (   const mtk::msg::sub_request_info&  _request_info,   const std::string&  _user_name)
    :     request_info(_request_info),   user_name(_user_name) 
       , __internal_warning_control_fields(0)
    {  
    }



void  req_login_key::check_recomended(void) const
{

}

void req_login_key::before_send(void) const
{

}




res_login_key::res_login_key (   const mtk::msg::sub_r_response&  _response_info,   const std::string&  _key)
    :     response_info(_response_info),   key(_key) 
       , __internal_warning_control_fields(0)
    {  
    }



void  res_login_key::check_recomended(void) const
{

}

void res_login_key::before_send(void) const
{

}




req_login::req_login (   const mtk::msg::sub_request_info&  _request_info,   const std::string&  _user_name,   const std::string&  _key,   const std::string&  _coded_pass)
    :     request_info(_request_info),   user_name(_user_name),   key(_key),   coded_pass(_coded_pass) 
       , __internal_warning_control_fields(0)
    {  
    }



void  req_login::check_recomended(void) const
{

}

void req_login::before_send(void) const
{

}




res_login::res_login (   const mtk::msg::sub_r_response&  _response_info,   const IC_session_info&  _session_info)
    :     response_info(_response_info),   session_info(_session_info) 
       , __internal_warning_control_fields(0)
    {  
    }



void  res_login::check_recomended(void) const
{

}

void res_login::before_send(void) const
{

}




res_login::IC_session_info::IC_session_info (   const std::string&  _user_name,   const std::string&  _client_code,   const std::string&  _session_id)
    :     user_name(_user_name),   client_code(_client_code),   session_id(_session_id) 
       
    {  
    }



void  res_login::IC_session_info::check_recomended(void) const
{

}

void res_login::IC_session_info::before_send(void) const
{

}




conf_logout::conf_logout (   const mtk::msg::sub_location&  _location,   const std::string&  _session_id,   const std::string&  _description)
    :     location(_location),   session_id(_session_id),   description(_description) 
       , __internal_warning_control_fields(0)
    {  
    }



void  conf_logout::check_recomended(void) const
{

}

void conf_logout::before_send(void) const
{

}




req_logout::req_logout (   const mtk::msg::sub_request_info&  _request_info)
    :     request_info(_request_info) 
       , __internal_warning_control_fields(0)
    {  
    }



void  req_logout::check_recomended(void) const
{

}

void req_logout::before_send(void) const
{

}




req_change_password::req_change_password (   const mtk::msg::sub_request_info&  _request_info,   const std::string&  _user_name,   const std::string&  _key,   const std::string&  _old_password,   const mtk::list<int32_t >&  _new_password)
    :     request_info(_request_info),   user_name(_user_name),   key(_key),   old_password(_old_password),   new_password(_new_password) 
       , __internal_warning_control_fields(0)
    {  
    }



void  req_change_password::check_recomended(void) const
{

}

void req_change_password::before_send(void) const
{

}




res_change_password::res_change_password (   const mtk::msg::sub_r_response&  _response_info,   const IC_change_password_info&  _change_password_info)
    :     response_info(_response_info),   change_password_info(_change_password_info) 
       , __internal_warning_control_fields(0)
    {  
    }



void  res_change_password::check_recomended(void) const
{

}

void res_change_password::before_send(void) const
{

}




res_change_password::IC_change_password_info::IC_change_password_info (   const bool&  _accepted)
    :     accepted(_accepted) 
       
    {  
    }



void  res_change_password::IC_change_password_info::check_recomended(void) const
{

}

void res_change_password::IC_change_password_info::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const req_login_key & c)
{
    o << "{ "

        << "request_info:"<< c.request_info<<"  "        << "user_name:"<<   c.user_name << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const req_login_key & c)
{
    o << YAML::BeginMap

        << YAML::Key << "request_info"  << YAML::Value << c.request_info        << YAML::Key << "user_name"  << YAML::Value <<   c.user_name
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, req_login_key & c)
{


        node["request_info"]  >> c.request_info;
        node["user_name"]  >> c.user_name;


};


std::ostream& operator<< (std::ostream& o, const res_login_key & c)
{
    o << "{ "

        << "response_info:"<< c.response_info<<"  "        << "key:"<<   c.key << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const res_login_key & c)
{
    o << YAML::BeginMap

        << YAML::Key << "response_info"  << YAML::Value << c.response_info        << YAML::Key << "key"  << YAML::Value <<   c.key
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, res_login_key & c)
{


        node["response_info"]  >> c.response_info;
        node["key"]  >> c.key;


};


std::ostream& operator<< (std::ostream& o, const req_login & c)
{
    o << "{ "

        << "request_info:"<< c.request_info<<"  "        << "user_name:"<<   c.user_name << "  "        << "key:"<<   c.key << "  "        << "coded_pass:"<<   c.coded_pass << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const req_login & c)
{
    o << YAML::BeginMap

        << YAML::Key << "request_info"  << YAML::Value << c.request_info        << YAML::Key << "user_name"  << YAML::Value <<   c.user_name        << YAML::Key << "key"  << YAML::Value <<   c.key        << YAML::Key << "coded_pass"  << YAML::Value <<   c.coded_pass
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, req_login & c)
{


        node["request_info"]  >> c.request_info;
        node["user_name"]  >> c.user_name;
        node["key"]  >> c.key;
        node["coded_pass"]  >> c.coded_pass;


};


std::ostream& operator<< (std::ostream& o, const res_login::IC_session_info & c)
{
    o << "{ "

        << "user_name:"<<   c.user_name << "  "        << "client_code:"<<   c.client_code << "  "        << "session_id:"<<   c.session_id << "  "
        << " }";
    return o;
};


std::ostream& operator<< (std::ostream& o, const res_login & c)
{
    o << "{ "

        << "response_info:"<< c.response_info<<"  "        << "session_info:"<< c.session_info<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const res_login::IC_session_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "user_name"  << YAML::Value <<   c.user_name        << YAML::Key << "client_code"  << YAML::Value <<   c.client_code        << YAML::Key << "session_id"  << YAML::Value <<   c.session_id
        << YAML::EndMap;
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const res_login & c)
{
    o << YAML::BeginMap

        << YAML::Key << "response_info"  << YAML::Value << c.response_info        << YAML::Key << "session_info"   << YAML::Value << c.session_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, res_login::IC_session_info & c)
{


        node["user_name"]  >> c.user_name;
        node["client_code"]  >> c.client_code;
        node["session_id"]  >> c.session_id;


};



void  operator >> (const YAML::Node& node, res_login & c)
{


        node["response_info"]  >> c.response_info;
            node["session_info"] >>  c.session_info;


};


std::ostream& operator<< (std::ostream& o, const conf_logout & c)
{
    o << "{ "

        << "location:"<< c.location<<"  "        << "session_id:"<<   c.session_id << "  "        << "description:"<<   c.description << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const conf_logout & c)
{
    o << YAML::BeginMap

        << YAML::Key << "location"  << YAML::Value << c.location        << YAML::Key << "session_id"  << YAML::Value <<   c.session_id        << YAML::Key << "description"  << YAML::Value <<   c.description
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, conf_logout & c)
{


        node["location"]  >> c.location;
        node["session_id"]  >> c.session_id;
        node["description"]  >> c.description;


};


std::ostream& operator<< (std::ostream& o, const req_logout & c)
{
    o << "{ "

        << "request_info:"<< c.request_info<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const req_logout & c)
{
    o << YAML::BeginMap

        << YAML::Key << "request_info"  << YAML::Value << c.request_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, req_logout & c)
{


        node["request_info"]  >> c.request_info;


};


std::ostream& operator<< (std::ostream& o, const req_change_password & c)
{
    o << "{ "

        << "request_info:"<< c.request_info<<"  "        << "user_name:"<<   c.user_name << "  "        << "key:"<<   c.key << "  "        << "old_password:"<<   c.old_password << "  "        << "new_password:"<<   c.new_password << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const req_change_password & c)
{
    o << YAML::BeginMap

        << YAML::Key << "request_info"  << YAML::Value << c.request_info        << YAML::Key << "user_name"  << YAML::Value <<   c.user_name        << YAML::Key << "key"  << YAML::Value <<   c.key        << YAML::Key << "old_password"  << YAML::Value <<   c.old_password        << YAML::Key << "new_password"  << YAML::Value <<   c.new_password
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, req_change_password & c)
{


        node["request_info"]  >> c.request_info;
        node["user_name"]  >> c.user_name;
        node["key"]  >> c.key;
        node["old_password"]  >> c.old_password;
        node["new_password"]  >> c.new_password;


};


std::ostream& operator<< (std::ostream& o, const res_change_password::IC_change_password_info & c)
{
    o << "{ "

        << "accepted:"<< c.accepted<<"  "
        << " }";
    return o;
};


std::ostream& operator<< (std::ostream& o, const res_change_password & c)
{
    o << "{ "

        << "response_info:"<< c.response_info<<"  "        << "change_password_info:"<< c.change_password_info<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const res_change_password::IC_change_password_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "accepted"  << YAML::Value << c.accepted
        << YAML::EndMap;
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const res_change_password & c)
{
    o << YAML::BeginMap

        << YAML::Key << "response_info"  << YAML::Value << c.response_info        << YAML::Key << "change_password_info"   << YAML::Value << c.change_password_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, res_change_password::IC_change_password_info & c)
{


        node["accepted"]  >> c.accepted;


};



void  operator >> (const YAML::Node& node, res_change_password & c)
{


        node["response_info"]  >> c.response_info;
            node["change_password_info"] >>  c.change_password_info;


};


bool operator== (const req_login_key& a, const req_login_key& b)
{
    return (          a.request_info ==  b.request_info  &&          a.user_name ==  b.user_name  &&   true  );
};

bool operator!= (const req_login_key& a, const req_login_key& b)
{
    return !(a==b);
};



bool operator== (const res_login_key& a, const res_login_key& b)
{
    return (          a.response_info ==  b.response_info  &&          a.key ==  b.key  &&   true  );
};

bool operator!= (const res_login_key& a, const res_login_key& b)
{
    return !(a==b);
};



bool operator== (const req_login& a, const req_login& b)
{
    return (          a.request_info ==  b.request_info  &&          a.user_name ==  b.user_name  &&          a.key ==  b.key  &&          a.coded_pass ==  b.coded_pass  &&   true  );
};

bool operator!= (const req_login& a, const req_login& b)
{
    return !(a==b);
};



bool operator== (const res_login::IC_session_info& a, const res_login::IC_session_info& b)
{
    return (          a.user_name ==  b.user_name  &&          a.client_code ==  b.client_code  &&          a.session_id ==  b.session_id  &&   true  );
};

bool operator!= (const res_login::IC_session_info& a, const res_login::IC_session_info& b)
{
    return !(a==b);
};



bool operator== (const res_login& a, const res_login& b)
{
    return (          a.response_info ==  b.response_info  &&          a.session_info  ==  b.session_info  &&   true  );
};

bool operator!= (const res_login& a, const res_login& b)
{
    return !(a==b);
};



bool operator== (const conf_logout& a, const conf_logout& b)
{
    return (          a.location ==  b.location  &&          a.session_id ==  b.session_id  &&          a.description ==  b.description  &&   true  );
};

bool operator!= (const conf_logout& a, const conf_logout& b)
{
    return !(a==b);
};



bool operator== (const req_logout& a, const req_logout& b)
{
    return (          a.request_info ==  b.request_info  &&   true  );
};

bool operator!= (const req_logout& a, const req_logout& b)
{
    return !(a==b);
};



bool operator== (const req_change_password& a, const req_change_password& b)
{
    return (          a.request_info ==  b.request_info  &&          a.user_name ==  b.user_name  &&          a.key ==  b.key  &&          a.old_password ==  b.old_password  &&          a.new_password ==  b.new_password  &&   true  );
};

bool operator!= (const req_change_password& a, const req_change_password& b)
{
    return !(a==b);
};



bool operator== (const res_change_password::IC_change_password_info& a, const res_change_password::IC_change_password_info& b)
{
    return (          a.accepted ==  b.accepted  &&   true  );
};

bool operator!= (const res_change_password::IC_change_password_info& a, const res_change_password::IC_change_password_info& b)
{
    return !(a==b);
};



bool operator== (const res_change_password& a, const res_change_password& b)
{
    return (          a.response_info ==  b.response_info  &&          a.change_password_info  ==  b.change_password_info  &&   true  );
};

bool operator!= (const res_change_password& a, const res_change_password& b)
{
    return !(a==b);
};




void  copy (req_login_key& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rqi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_info on message req_login_key::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_info, it->second);
                        //__internal_qpid_fill(c.request_info, it->second.asMap());
//   field_type

                    it = mv.find("un");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field user_name on message req_login_key::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.user_name, it->second);
                        //c.user_name = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const req_login_key& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.request_info, std::string("rqi"));
//  field_type
        __internal_add2map(map, a.user_name, std::string("un"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_login_key>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (res_login_key& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rsi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field response_info on message res_login_key::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.response_info, it->second);
                        //__internal_qpid_fill(c.response_info, it->second.asMap());
//   field_type

                    it = mv.find("k");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field key on message res_login_key::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.key, it->second);
                        //c.key = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const res_login_key& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.response_info, std::string("rsi"));
//  field_type
        __internal_add2map(map, a.key, std::string("k"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_login_key>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (req_login& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rqi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_info on message req_login::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_info, it->second);
                        //__internal_qpid_fill(c.request_info, it->second.asMap());
//   field_type

                    it = mv.find("un");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field user_name on message req_login::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.user_name, it->second);
                        //c.user_name = it->second;
//   field_type

                    it = mv.find("k");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field key on message req_login::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.key, it->second);
                        //c.key = it->second;
//   field_type

                    it = mv.find("cpw");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field coded_pass on message req_login::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.coded_pass, it->second);
                        //c.coded_pass = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const req_login& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.request_info, std::string("rqi"));
//  field_type
        __internal_add2map(map, a.user_name, std::string("un"));
//  field_type
        __internal_add2map(map, a.key, std::string("k"));
//  field_type
        __internal_add2map(map, a.coded_pass, std::string("cpw"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_login>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (res_login& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rsi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field response_info on message res_login::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.response_info, it->second);
                        //__internal_qpid_fill(c.response_info, it->second.asMap());
//   IN_SUB_MSG

                    it = mv.find("lr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field session_info on message res_login::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.session_info, it->second);
                        //__internal_qpid_fill(c.session_info, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const res_login& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.response_info, std::string("rsi"));
//  IN_SUB_MSG
//        map["lr"] =  qpidmsg_coded_as_qpid_Map(a.session_info);
        __internal_add2map(map, a.session_info);


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_login>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (res_login::IC_session_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("un");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field user_name on message res_login::IC_session_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.user_name, it->second);
                        //c.user_name = it->second;
//   field_type

                    it = mv.find("cc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field client_code on message res_login::IC_session_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.client_code, it->second);
                        //c.client_code = it->second;
//   field_type

                    it = mv.find("sid");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field session_id on message res_login::IC_session_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.session_id, it->second);
                        //c.session_id = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const res_login::IC_session_info& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.user_name, std::string("un"));
//  field_type
        __internal_add2map(map, a.client_code, std::string("cc"));
//  field_type
        __internal_add2map(map, a.session_id, std::string("sid"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_login::IC_session_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (conf_logout& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("lc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field location on message conf_logout::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.location, it->second);
                        //__internal_qpid_fill(c.location, it->second.asMap());
//   field_type

                    it = mv.find("sid");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field session_id on message conf_logout::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.session_id, it->second);
                        //c.session_id = it->second;
//   field_type

                    it = mv.find("desc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field description on message conf_logout::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.description, it->second);
                        //c.description = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const conf_logout& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.location, std::string("lc"));
//  field_type
        __internal_add2map(map, a.session_id, std::string("sid"));
//  field_type
        __internal_add2map(map, a.description, std::string("desc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<conf_logout>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (req_logout& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rqi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_info on message req_logout::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_info, it->second);
                        //__internal_qpid_fill(c.request_info, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const req_logout& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.request_info, std::string("rqi"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_logout>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (req_change_password& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rqi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_info on message req_change_password::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_info, it->second);
                        //__internal_qpid_fill(c.request_info, it->second.asMap());
//   field_type

                    it = mv.find("un");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field user_name on message req_change_password::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.user_name, it->second);
                        //c.user_name = it->second;
//   field_type

                    it = mv.find("k");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field key on message req_change_password::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.key, it->second);
                        //c.key = it->second;
//   field_type

                    it = mv.find("opw");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field old_password on message req_change_password::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.old_password, it->second);
                        //c.old_password = it->second;
//   field_type

                    it = mv.find("npw");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field new_password on message req_change_password::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.new_password, it->second);
                        //c.new_password = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const req_change_password& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.request_info, std::string("rqi"));
//  field_type
        __internal_add2map(map, a.user_name, std::string("un"));
//  field_type
        __internal_add2map(map, a.key, std::string("k"));
//  field_type
        __internal_add2map(map, a.old_password, std::string("opw"));
//  field_type
        __internal_add2map(map, a.new_password, std::string("npw"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_change_password>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (res_change_password& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rsi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field response_info on message res_change_password::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.response_info, it->second);
                        //__internal_qpid_fill(c.response_info, it->second.asMap());
//   IN_SUB_MSG

                    it = mv.find("cpi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field change_password_info on message res_change_password::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.change_password_info, it->second);
                        //__internal_qpid_fill(c.change_password_info, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const res_change_password& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.response_info, std::string("rsi"));
//  IN_SUB_MSG
//        map["cpi"] =  qpidmsg_coded_as_qpid_Map(a.change_password_info);
        __internal_add2map(map, a.change_password_info);


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_change_password>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (res_change_password::IC_change_password_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("a");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field accepted on message res_change_password::IC_change_password_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.accepted, it->second);
                        //__internal_qpid_fill(c.accepted, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const res_change_password::IC_change_password_info& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.accepted, std::string("a"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_change_password::IC_change_password_info>& a, const std::string& field)
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

qpid::messaging::Message req_login_key::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["rqi"] =  qpidmsg_coded_as_qpid_Map(this->request_info);
        __internal_add2map(content, this->request_info, std::string("rqi"));
//  field_type
//        content["un"] = this->user_name;
        __internal_add2map(content, this->user_name, std::string("un"));


    mtk::msg::sub_control_fields control_fields{static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal(),  static_get_depreciated_on()};
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message res_login_key::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["rsi"] =  qpidmsg_coded_as_qpid_Map(this->response_info);
        __internal_add2map(content, this->response_info, std::string("rsi"));
//  field_type
//        content["k"] = this->key;
        __internal_add2map(content, this->key, std::string("k"));


    mtk::msg::sub_control_fields control_fields{static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal(),  static_get_depreciated_on()};
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message req_login::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["rqi"] =  qpidmsg_coded_as_qpid_Map(this->request_info);
        __internal_add2map(content, this->request_info, std::string("rqi"));
//  field_type
//        content["un"] = this->user_name;
        __internal_add2map(content, this->user_name, std::string("un"));
//  field_type
//        content["k"] = this->key;
        __internal_add2map(content, this->key, std::string("k"));
//  field_type
//        content["cpw"] = this->coded_pass;
        __internal_add2map(content, this->coded_pass, std::string("cpw"));


    mtk::msg::sub_control_fields control_fields{static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal(),  static_get_depreciated_on()};
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message res_login::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["rsi"] =  qpidmsg_coded_as_qpid_Map(this->response_info);
        __internal_add2map(content, this->response_info, std::string("rsi"));
//  IN_SUB_MSG
//        content["lr"] =  qpidmsg_coded_as_qpid_Map(this->session_info);
        __internal_add2map(content, this->session_info, std::string("lr"));


    mtk::msg::sub_control_fields control_fields{static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal(),  static_get_depreciated_on()};
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message conf_logout::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["lc"] =  qpidmsg_coded_as_qpid_Map(this->location);
        __internal_add2map(content, this->location, std::string("lc"));
//  field_type
//        content["sid"] = this->session_id;
        __internal_add2map(content, this->session_id, std::string("sid"));
//  field_type
//        content["desc"] = this->description;
        __internal_add2map(content, this->description, std::string("desc"));


    mtk::msg::sub_control_fields control_fields{static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal(),  static_get_depreciated_on()};
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message req_logout::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["rqi"] =  qpidmsg_coded_as_qpid_Map(this->request_info);
        __internal_add2map(content, this->request_info, std::string("rqi"));


    mtk::msg::sub_control_fields control_fields{static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal(),  static_get_depreciated_on()};
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message req_change_password::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["rqi"] =  qpidmsg_coded_as_qpid_Map(this->request_info);
        __internal_add2map(content, this->request_info, std::string("rqi"));
//  field_type
//        content["un"] = this->user_name;
        __internal_add2map(content, this->user_name, std::string("un"));
//  field_type
//        content["k"] = this->key;
        __internal_add2map(content, this->key, std::string("k"));
//  field_type
//        content["opw"] = this->old_password;
        __internal_add2map(content, this->old_password, std::string("opw"));
//  field_type
//        content["npw"] = this->new_password;
        __internal_add2map(content, this->new_password, std::string("npw"));


    mtk::msg::sub_control_fields control_fields{static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal(),  static_get_depreciated_on()};
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message res_change_password::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["rsi"] =  qpidmsg_coded_as_qpid_Map(this->response_info);
        __internal_add2map(content, this->response_info, std::string("rsi"));
//  IN_SUB_MSG
//        content["cpi"] =  qpidmsg_coded_as_qpid_Map(this->change_password_info);
        __internal_add2map(content, this->change_password_info, std::string("cpi"));


    mtk::msg::sub_control_fields control_fields{static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal(),  static_get_depreciated_on()};
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




    req_login_key  __internal_get_default(req_login_key*)
    {
        return req_login_key(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_request_info*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    res_login_key  __internal_get_default(res_login_key*)
    {
        return res_login_key(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_r_response*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    req_login  __internal_get_default(req_login*)
    {
        return req_login(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_request_info*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    res_login  __internal_get_default(res_login*)
    {
        return res_login(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_r_response*)0),
//   IN_SUB_MSG
   __internal_get_default((res_login::IC_session_info*)0)
            );
    }
    
    res_login::IC_session_info  __internal_get_default(res_login::IC_session_info*)
    {
        return res_login::IC_session_info(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    conf_logout  __internal_get_default(conf_logout*)
    {
        return conf_logout(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_location*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    req_logout  __internal_get_default(req_logout*)
    {
        return req_logout(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_request_info*)0)
            );
    }
    
    req_change_password  __internal_get_default(req_change_password*)
    {
        return req_change_password(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_request_info*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((mtk::list<int32_t >*)0)
            );
    }
    
    res_change_password  __internal_get_default(res_change_password*)
    {
        return res_change_password(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_r_response*)0),
//   IN_SUB_MSG
   __internal_get_default((res_change_password::IC_change_password_info*)0)
            );
    }
    
    res_change_password::IC_change_password_info  __internal_get_default(res_change_password::IC_change_password_info*)
    {
        return res_change_password::IC_change_password_info(
//   sub_msg_type
   __internal_get_default((bool*)0)
            );
    }
    
req_login_key::req_login_key (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   request_info(__internal_get_default((mtk::msg::sub_request_info*)0)),
//   field_type
   user_name(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

res_login_key::res_login_key (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   response_info(__internal_get_default((mtk::msg::sub_r_response*)0)),
//   field_type
   key(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

req_login::req_login (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   request_info(__internal_get_default((mtk::msg::sub_request_info*)0)),
//   field_type
   user_name(__internal_get_default((std::string*)0)),
//   field_type
   key(__internal_get_default((std::string*)0)),
//   field_type
   coded_pass(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

res_login::res_login (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   response_info(__internal_get_default((mtk::msg::sub_r_response*)0)),
//   IN_SUB_MSG
   session_info(__internal_get_default((res_login::IC_session_info*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

res_login::IC_session_info::IC_session_info (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   user_name(__internal_get_default((std::string*)0)),
//   field_type
   client_code(__internal_get_default((std::string*)0)),
//   field_type
   session_id(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

conf_logout::conf_logout (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   location(__internal_get_default((mtk::msg::sub_location*)0)),
//   field_type
   session_id(__internal_get_default((std::string*)0)),
//   field_type
   description(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

req_logout::req_logout (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   request_info(__internal_get_default((mtk::msg::sub_request_info*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

req_change_password::req_change_password (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   request_info(__internal_get_default((mtk::msg::sub_request_info*)0)),
//   field_type
   user_name(__internal_get_default((std::string*)0)),
//   field_type
   key(__internal_get_default((std::string*)0)),
//   field_type
   old_password(__internal_get_default((std::string*)0)),
//   field_type
   new_password(__internal_get_default((mtk::list<int32_t >*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

res_change_password::res_change_password (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   response_info(__internal_get_default((mtk::msg::sub_r_response*)0)),
//   IN_SUB_MSG
   change_password_info(__internal_get_default((res_change_password::IC_change_password_info*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

res_change_password::IC_change_password_info::IC_change_password_info (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   accepted(__internal_get_default((bool*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }
mtk::t_qpid_filter  req_login_key::get_in_subject (const std::string& request_info_process_info_location_broker_code)
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << request_info_process_info_location_broker_code << ".ACS.RQK"));
    }
    mtk::t_qpid_filter  req_login_key::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << this->request_info.process_info.location.broker_code << ".ACS.RQK"));
    }
    /*static*/  mtk::t_qpid_address  req_login_key::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  req_login_key::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  res_login_key::get_in_subject (const std::string& response_info_request_info_process_info_location_broker_code,const std::string& response_info_request_info_process_info_location_machine,const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_session_id,const std::string& response_info_request_info_req_id_req_code)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << response_info_request_info_process_info_location_broker_code << "." << response_info_request_info_process_info_location_machine << "." << response_info_request_info_process_info_process_uuid << "." << response_info_request_info_req_id_session_id << "." << response_info_request_info_req_id_req_code << ".RSK"));
    }
    mtk::t_qpid_filter  res_login_key::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->response_info.request_info.process_info.location.broker_code << "." << this->response_info.request_info.process_info.location.machine << "." << this->response_info.request_info.process_info.process_uuid << "." << this->response_info.request_info.req_id.session_id << "." << this->response_info.request_info.req_id.req_code << ".RSK"));
    }
    /*static*/  mtk::t_qpid_address  res_login_key::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  res_login_key::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  req_login::get_in_subject (const std::string& request_info_process_info_location_broker_code)
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << request_info_process_info_location_broker_code << ".ACS.RQL"));
    }
    mtk::t_qpid_filter  req_login::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << this->request_info.process_info.location.broker_code << ".ACS.RQL"));
    }
    /*static*/  mtk::t_qpid_address  req_login::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  req_login::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  res_login::get_in_subject (const std::string& response_info_request_info_process_info_location_broker_code,const std::string& response_info_request_info_process_info_location_machine,const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_session_id,const std::string& response_info_request_info_req_id_req_code)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << response_info_request_info_process_info_location_broker_code << "." << response_info_request_info_process_info_location_machine << "." << response_info_request_info_process_info_process_uuid << "." << response_info_request_info_req_id_session_id << "." << response_info_request_info_req_id_req_code << ".RESLOGIN"));
    }
    mtk::t_qpid_filter  res_login::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->response_info.request_info.process_info.location.broker_code << "." << this->response_info.request_info.process_info.location.machine << "." << this->response_info.request_info.process_info.process_uuid << "." << this->response_info.request_info.req_id.session_id << "." << this->response_info.request_info.req_id.req_code << ".RESLOGIN"));
    }
    /*static*/  mtk::t_qpid_address  res_login::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  res_login::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  conf_logout::get_in_subject (const std::string& location_broker_code,const std::string& location_machine,const std::string& session_id)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << location_broker_code << "." << location_machine << "." << session_id << ".CONFLOGOUT"));
    }
    mtk::t_qpid_filter  conf_logout::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->location.broker_code << "." << this->location.machine << "." << this->session_id << ".CONFLOGOUT"));
    }
    /*static*/  mtk::t_qpid_address  conf_logout::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  conf_logout::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  req_logout::get_in_subject (const std::string& request_info_process_info_location_broker_code)
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << request_info_process_info_location_broker_code << ".ACS.RQLO"));
    }
    mtk::t_qpid_filter  req_logout::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << this->request_info.process_info.location.broker_code << ".ACS.RQLO"));
    }
    /*static*/  mtk::t_qpid_address  req_logout::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  req_logout::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  req_change_password::get_in_subject (const std::string& request_info_process_info_location_broker_code)
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << request_info_process_info_location_broker_code << ".ACS.RQCP"));
    }
    mtk::t_qpid_filter  req_change_password::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << this->request_info.process_info.location.broker_code << ".ACS.RQCP"));
    }
    /*static*/  mtk::t_qpid_address  req_change_password::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  req_change_password::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  res_change_password::get_in_subject (const std::string& response_info_request_info_process_info_location_broker_code,const std::string& response_info_request_info_process_info_location_machine,const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_session_id,const std::string& response_info_request_info_req_id_req_code)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << response_info_request_info_process_info_location_broker_code << "." << response_info_request_info_process_info_location_machine << "." << response_info_request_info_process_info_process_uuid << "." << response_info_request_info_req_id_session_id << "." << response_info_request_info_req_id_req_code << ".RESLCP"));
    }
    mtk::t_qpid_filter  res_change_password::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->response_info.request_info.process_info.location.broker_code << "." << this->response_info.request_info.process_info.location.machine << "." << this->response_info.request_info.process_info.process_uuid << "." << this->response_info.request_info.req_id.session_id << "." << this->response_info.request_info.req_id.req_code << ".RESLCP"));
    }
    /*static*/  mtk::t_qpid_address  res_change_password::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  res_change_password::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    

};   //namespace mtk {
};   //namespace acs {
};   //namespace msg {


