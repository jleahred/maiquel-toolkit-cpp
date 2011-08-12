
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_prodinfo_grant_db.h"

namespace prodinfo_grant { 
namespace db { 
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


    template<typename T>
    void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::nullable<T>& n, const std::string& key)
    {
        if (n.HasValue())
            __internal_add2map(map, n.Get(), key);
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


sub_pattern_users_grants::sub_pattern_users_grants (   const std::string&  _user_pattern,   const mtk::list<mtk::msg::sub_product_code >&  _re_product_code_list,   const mtk::DateTime&  _last_applied_rule)
    :     user_pattern(_user_pattern),   re_product_code_list(_re_product_code_list),   last_applied_rule(_last_applied_rule) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_pattern_users_grants::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_pattern_users_grants::before_send(void) const
{

}




sub_client__pattern_users::sub_client__pattern_users (   const std::string&  _client_code,   const mtk::list<sub_pattern_users_grants >&  _users_pattern)
    :     client_code(_client_code),   users_pattern(_users_pattern) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_client__pattern_users::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_client__pattern_users::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const sub_pattern_users_grants & c)
{
    o << "{ "

        << "user_pattern:"<<   c.user_pattern << "  "        << "re_product_code_list:"<< c.re_product_code_list<<"  "        << "last_applied_rule:"<<   c.last_applied_rule << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_pattern_users_grants & c)
{
    o << YAML::BeginMap

        << YAML::Key << "user_pattern"  << YAML::Value <<   c.user_pattern        << YAML::Key << "re_product_code_list"  << YAML::Value << c.re_product_code_list        << YAML::Key << "last_applied_rule"  << YAML::Value <<   c.last_applied_rule
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_pattern_users_grants & c)
{


        node["user_pattern"]  >> c.user_pattern;
        node["re_product_code_list"]  >> c.re_product_code_list;
        node["last_applied_rule"]  >> c.last_applied_rule;


};


std::ostream& operator<< (std::ostream& o, const sub_client__pattern_users & c)
{
    o << "{ "

        << "client_code:"<<   c.client_code << "  "        << "users_pattern:"<< c.users_pattern<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_client__pattern_users & c)
{
    o << YAML::BeginMap

        << YAML::Key << "client_code"  << YAML::Value <<   c.client_code        << YAML::Key << "users_pattern"  << YAML::Value << c.users_pattern
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_client__pattern_users & c)
{


        node["client_code"]  >> c.client_code;
        node["users_pattern"]  >> c.users_pattern;


};


bool operator== (const sub_pattern_users_grants& a, const sub_pattern_users_grants& b)
{
    return (          a.user_pattern ==  b.user_pattern  &&          a.re_product_code_list ==  b.re_product_code_list  &&          a.last_applied_rule ==  b.last_applied_rule  &&   true  );
};

bool operator!= (const sub_pattern_users_grants& a, const sub_pattern_users_grants& b)
{
    return !(a==b);
};



bool operator== (const sub_client__pattern_users& a, const sub_client__pattern_users& b)
{
    return (          a.client_code ==  b.client_code  &&          a.users_pattern ==  b.users_pattern  &&   true  );
};

bool operator!= (const sub_client__pattern_users& a, const sub_client__pattern_users& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (sub_pattern_users_grants& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_pattern_users_grants& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("reu");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field user_pattern on message sub_pattern_users_grants::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.user_pattern, it->second);
                        //c.user_pattern = it->second;
//   sub_msg_type

                    it = mv.find("pcl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field re_product_code_list on message sub_pattern_users_grants::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.re_product_code_list, it->second);
                        //__internal_qpid_fill(c.re_product_code_list, it->second.asMap());
//   field_type

                    it = mv.find("lar");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field last_applied_rule on message sub_pattern_users_grants::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.last_applied_rule, it->second);
                        //c.last_applied_rule = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_pattern_users_grants& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.user_pattern, std::string("reu"));
//  sub_msg_type
        __internal_add2map(map, a.re_product_code_list, std::string("pcl"));
//  field_type
        __internal_add2map(map, a.last_applied_rule, std::string("lar"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_pattern_users_grants>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_client__pattern_users& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_client__pattern_users& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("cc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field client_code on message sub_client__pattern_users::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.client_code, it->second);
                        //c.client_code = it->second;
//   sub_msg_type

                    it = mv.find("up");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field users_pattern on message sub_client__pattern_users::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.users_pattern, it->second);
                        //__internal_qpid_fill(c.users_pattern, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_client__pattern_users& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.client_code, std::string("cc"));
//  sub_msg_type
        __internal_add2map(map, a.users_pattern, std::string("up"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_client__pattern_users>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)

    sub_pattern_users_grants  __internal_get_default(sub_pattern_users_grants*)
    {
        return sub_pattern_users_grants(
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((mtk::list<mtk::msg::sub_product_code >*)0),
//   field_type
   __internal_get_default ((mtk::DateTime*)0)
            );
    }
    
    sub_client__pattern_users  __internal_get_default(sub_client__pattern_users*)
    {
        return sub_client__pattern_users(
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((mtk::list<sub_pattern_users_grants >*)0)
            );
    }
    

sub_pattern_users_grants::sub_pattern_users_grants (const qpid::messaging::Message& msg)
    :  //   field_type
   user_pattern(__internal_get_default((std::string*)0)),
//   sub_msg_type
   re_product_code_list(__internal_get_default((mtk::list<mtk::msg::sub_product_code >*)0)),
//   field_type
   last_applied_rule(__internal_get_default((mtk::DateTime*)0)) 
    {
        qpid::types::Variant::Map mv;
        qpid::messaging::decode(msg, mv);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> map = mv;
        copy(*this, map);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



sub_client__pattern_users::sub_client__pattern_users (const qpid::messaging::Message& msg)
    :  //   field_type
   client_code(__internal_get_default((std::string*)0)),
//   sub_msg_type
   users_pattern(__internal_get_default((mtk::list<sub_pattern_users_grants >*)0)) 
    {
        qpid::types::Variant::Map mv;
        qpid::messaging::decode(msg, mv);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> map = mv;
        copy(*this, map);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



};   //namespace prodinfo_grant {
};   //namespace db {
};   //namespace msg {


