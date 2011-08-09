
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_users_manager.h"

namespace users_manager { 







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


sub_user_info::sub_user_info (   const std::string&  _name,   const std::string&  _client_code,   const std::string&  _requested_by,   const std::string&  _notes)
    :     name(_name),   client_code(_client_code),   requested_by(_requested_by),   notes(_notes) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_user_info::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_user_info::before_send(void) const
{

}




sub_user_acs_info::sub_user_acs_info (   const sub_user_info&  _user_info,   const std::string&  _passwordcrc32,   const mtk::DateTime&  _created_on,   const mtk::DateTime&  _last_access,   const int&  _check_pass_ok,   const int&  _check_pass_wrong)
    :     user_info(_user_info),   passwordcrc32(_passwordcrc32),   created_on(_created_on),   last_access(_last_access),   check_pass_ok(_check_pass_ok),   check_pass_wrong(_check_pass_wrong) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_user_acs_info::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_user_acs_info::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const sub_user_info & c)
{
    o << "{ "

        << "name:"<<   c.name << "  "        << "client_code:"<<   c.client_code << "  "        << "requested_by:"<<   c.requested_by << "  "        << "notes:"<<   c.notes << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_user_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "name"  << YAML::Value <<   c.name        << YAML::Key << "client_code"  << YAML::Value <<   c.client_code        << YAML::Key << "requested_by"  << YAML::Value <<   c.requested_by        << YAML::Key << "notes"  << YAML::Value <<   c.notes
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_user_info & c)
{


        node["name"]  >> c.name;
        node["client_code"]  >> c.client_code;
        node["requested_by"]  >> c.requested_by;
        node["notes"]  >> c.notes;


};


std::ostream& operator<< (std::ostream& o, const sub_user_acs_info & c)
{
    o << "{ "

        << "user_info:"<< c.user_info<<"  "        << "passwordcrc32:"<<   c.passwordcrc32 << "  "        << "created_on:"<<   c.created_on << "  "        << "last_access:"<<   c.last_access << "  "        << "check_pass_ok:"<< c.check_pass_ok<<"  "        << "check_pass_wrong:"<< c.check_pass_wrong<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_user_acs_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "user_info"  << YAML::Value << c.user_info        << YAML::Key << "passwordcrc32"  << YAML::Value <<   c.passwordcrc32        << YAML::Key << "created_on"  << YAML::Value <<   c.created_on        << YAML::Key << "last_access"  << YAML::Value <<   c.last_access        << YAML::Key << "check_pass_ok"  << YAML::Value << c.check_pass_ok        << YAML::Key << "check_pass_wrong"  << YAML::Value << c.check_pass_wrong
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_user_acs_info & c)
{


        node["user_info"]  >> c.user_info;
        node["passwordcrc32"]  >> c.passwordcrc32;
        node["created_on"]  >> c.created_on;
        node["last_access"]  >> c.last_access;
        node["check_pass_ok"]  >> c.check_pass_ok;
        node["check_pass_wrong"]  >> c.check_pass_wrong;


};


bool operator== (const sub_user_info& a, const sub_user_info& b)
{
    return (          a.name ==  b.name  &&          a.client_code ==  b.client_code  &&          a.requested_by ==  b.requested_by  &&          a.notes ==  b.notes  &&   true  );
};

bool operator!= (const sub_user_info& a, const sub_user_info& b)
{
    return !(a==b);
};



bool operator== (const sub_user_acs_info& a, const sub_user_acs_info& b)
{
    return (          a.user_info ==  b.user_info  &&          a.passwordcrc32 ==  b.passwordcrc32  &&          a.created_on ==  b.created_on  &&          a.last_access ==  b.last_access  &&          a.check_pass_ok ==  b.check_pass_ok  &&          a.check_pass_wrong ==  b.check_pass_wrong  &&   true  );
};

bool operator!= (const sub_user_acs_info& a, const sub_user_acs_info& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (sub_user_info& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_user_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("nm");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field name on message sub_user_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.name, it->second);
                        //c.name = it->second;
//   field_type

                    it = mv.find("cc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field client_code on message sub_user_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.client_code, it->second);
                        //c.client_code = it->second;
//   field_type

                    it = mv.find("rb");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field requested_by on message sub_user_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.requested_by, it->second);
                        //c.requested_by = it->second;
//   field_type

                    it = mv.find("nt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field notes on message sub_user_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.notes, it->second);
                        //c.notes = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_user_info& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.name, std::string("nm"));
//  field_type
        __internal_add2map(map, a.client_code, std::string("cc"));
//  field_type
        __internal_add2map(map, a.requested_by, std::string("rb"));
//  field_type
        __internal_add2map(map, a.notes, std::string("nt"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_user_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_user_acs_info& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_user_acs_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("ui");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field user_info on message sub_user_acs_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.user_info, it->second);
                        //__internal_qpid_fill(c.user_info, it->second.asMap());
//   field_type

                    it = mv.find("pw32");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field passwordcrc32 on message sub_user_acs_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.passwordcrc32, it->second);
                        //c.passwordcrc32 = it->second;
//   field_type

                    it = mv.find("dtc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field created_on on message sub_user_acs_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.created_on, it->second);
                        //c.created_on = it->second;
//   field_type

                    it = mv.find("dt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field last_access on message sub_user_acs_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.last_access, it->second);
                        //c.last_access = it->second;
//   sub_msg_type

                    it = mv.find("cpok");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field check_pass_ok on message sub_user_acs_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.check_pass_ok, it->second);
                        //__internal_qpid_fill(c.check_pass_ok, it->second.asMap());
//   sub_msg_type

                    it = mv.find("cpwr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field check_pass_wrong on message sub_user_acs_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.check_pass_wrong, it->second);
                        //__internal_qpid_fill(c.check_pass_wrong, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_user_acs_info& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.user_info, std::string("ui"));
//  field_type
        __internal_add2map(map, a.passwordcrc32, std::string("pw32"));
//  field_type
        __internal_add2map(map, a.created_on, std::string("dtc"));
//  field_type
        __internal_add2map(map, a.last_access, std::string("dt"));
//  sub_msg_type
        __internal_add2map(map, a.check_pass_ok, std::string("cpok"));
//  sub_msg_type
        __internal_add2map(map, a.check_pass_wrong, std::string("cpwr"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_user_acs_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)

    sub_user_info  __internal_get_default(sub_user_info*)
    {
        return sub_user_info(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    sub_user_acs_info  __internal_get_default(sub_user_acs_info*)
    {
        return sub_user_acs_info(
//   sub_msg_type
   __internal_get_default((sub_user_info*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((mtk::DateTime*)0),
//   field_type
   __internal_get_default ((mtk::DateTime*)0),
//   sub_msg_type
   __internal_get_default((int*)0),
//   sub_msg_type
   __internal_get_default((int*)0)
            );
    }
    

sub_user_info::sub_user_info (const qpid::messaging::Message& msg)
    :  //   field_type
   name(__internal_get_default((std::string*)0)),
//   field_type
   client_code(__internal_get_default((std::string*)0)),
//   field_type
   requested_by(__internal_get_default((std::string*)0)),
//   field_type
   notes(__internal_get_default((std::string*)0)) 
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



sub_user_acs_info::sub_user_acs_info (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   user_info(__internal_get_default((sub_user_info*)0)),
//   field_type
   passwordcrc32(__internal_get_default((std::string*)0)),
//   field_type
   created_on(__internal_get_default((mtk::DateTime*)0)),
//   field_type
   last_access(__internal_get_default((mtk::DateTime*)0)),
//   sub_msg_type
   check_pass_ok(__internal_get_default((int*)0)),
//   sub_msg_type
   check_pass_wrong(__internal_get_default((int*)0)) 
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



};   //namespace users_manager {


