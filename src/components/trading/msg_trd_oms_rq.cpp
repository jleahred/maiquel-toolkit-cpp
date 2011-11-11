
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_trd_oms_rq.h"

namespace mtk { 
namespace trd { 
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


oms_RQ_NW_LS::oms_RQ_NW_LS ( const RQ_NW_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from)
    :  RQ_NW_LS(parent),   reject_description(_reject_description),   from(_from) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string oms_RQ_NW_LS::check_recomended(void) const
{
    std::string result;

    return result;
}

void oms_RQ_NW_LS::before_send(void) const
{

}




oms_RQ_MD_LS::oms_RQ_MD_LS ( const RQ_MD_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from)
    :  RQ_MD_LS(parent),   reject_description(_reject_description),   from(_from) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string oms_RQ_MD_LS::check_recomended(void) const
{
    std::string result;

    return result;
}

void oms_RQ_MD_LS::before_send(void) const
{

}




oms_RQ_CC_LS::oms_RQ_CC_LS ( const RQ_CC_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from)
    :  RQ_CC_LS(parent),   reject_description(_reject_description),   from(_from) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string oms_RQ_CC_LS::check_recomended(void) const
{
    std::string result;

    return result;
}

void oms_RQ_CC_LS::before_send(void) const
{

}




oms_RQ_NW_MK::oms_RQ_NW_MK ( const RQ_NW_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from)
    :  RQ_NW_MK(parent),   reject_description(_reject_description),   from(_from) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string oms_RQ_NW_MK::check_recomended(void) const
{
    std::string result;

    return result;
}

void oms_RQ_NW_MK::before_send(void) const
{

}




oms_RQ_MD_MK::oms_RQ_MD_MK ( const RQ_MD_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from)
    :  RQ_MD_MK(parent),   reject_description(_reject_description),   from(_from) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string oms_RQ_MD_MK::check_recomended(void) const
{
    std::string result;

    return result;
}

void oms_RQ_MD_MK::before_send(void) const
{

}




oms_RQ_CC_MK::oms_RQ_CC_MK ( const RQ_CC_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from)
    :  RQ_CC_MK(parent),   reject_description(_reject_description),   from(_from) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string oms_RQ_CC_MK::check_recomended(void) const
{
    std::string result;

    return result;
}

void oms_RQ_CC_MK::before_send(void) const
{

}




oms_RQ_ORDERS_STATUS::oms_RQ_ORDERS_STATUS ( const RQ_ORDERS_STATUS&  parent,   const std::string&  _reject_description,   const std::string&  _from)
    :  RQ_ORDERS_STATUS(parent),   reject_description(_reject_description),   from(_from) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string oms_RQ_ORDERS_STATUS::check_recomended(void) const
{
    std::string result;

    return result;
}

void oms_RQ_ORDERS_STATUS::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_NW_LS&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_NW_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_NW_LS" <<  YAML::Value << static_cast<const RQ_NW_LS&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_NW_LS & c)
{

    node["RQ_NW_LS"]   >>   static_cast<RQ_NW_LS&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_MD_LS&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_MD_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_MD_LS" <<  YAML::Value << static_cast<const RQ_MD_LS&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_MD_LS & c)
{

    node["RQ_MD_LS"]   >>   static_cast<RQ_MD_LS&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_CC_LS&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_CC_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_CC_LS" <<  YAML::Value << static_cast<const RQ_CC_LS&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_CC_LS & c)
{

    node["RQ_CC_LS"]   >>   static_cast<RQ_CC_LS&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_MK & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_NW_MK&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_NW_MK & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_NW_MK" <<  YAML::Value << static_cast<const RQ_NW_MK&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_NW_MK & c)
{

    node["RQ_NW_MK"]   >>   static_cast<RQ_NW_MK&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_MK & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_MD_MK&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_MD_MK & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_MD_MK" <<  YAML::Value << static_cast<const RQ_MD_MK&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_MD_MK & c)
{

    node["RQ_MD_MK"]   >>   static_cast<RQ_MD_MK&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_MK & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_CC_MK&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_CC_MK & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_CC_MK" <<  YAML::Value << static_cast<const RQ_CC_MK&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_CC_MK & c)
{

    node["RQ_CC_MK"]   >>   static_cast<RQ_CC_MK&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_ORDERS_STATUS & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_ORDERS_STATUS&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_ORDERS_STATUS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_ORDERS_STATUS" <<  YAML::Value << static_cast<const RQ_ORDERS_STATUS&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_ORDERS_STATUS & c)
{

    node["RQ_ORDERS_STATUS"]   >>   static_cast<RQ_ORDERS_STATUS&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;


};


bool operator== (const oms_RQ_NW_LS& a, const oms_RQ_NW_LS& b)
{
    return ( (static_cast<const RQ_NW_LS&>(a)   ==  static_cast<const RQ_NW_LS&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&   true  );
};

bool operator!= (const oms_RQ_NW_LS& a, const oms_RQ_NW_LS& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_MD_LS& a, const oms_RQ_MD_LS& b)
{
    return ( (static_cast<const RQ_MD_LS&>(a)   ==  static_cast<const RQ_MD_LS&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&   true  );
};

bool operator!= (const oms_RQ_MD_LS& a, const oms_RQ_MD_LS& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_CC_LS& a, const oms_RQ_CC_LS& b)
{
    return ( (static_cast<const RQ_CC_LS&>(a)   ==  static_cast<const RQ_CC_LS&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&   true  );
};

bool operator!= (const oms_RQ_CC_LS& a, const oms_RQ_CC_LS& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_NW_MK& a, const oms_RQ_NW_MK& b)
{
    return ( (static_cast<const RQ_NW_MK&>(a)   ==  static_cast<const RQ_NW_MK&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&   true  );
};

bool operator!= (const oms_RQ_NW_MK& a, const oms_RQ_NW_MK& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_MD_MK& a, const oms_RQ_MD_MK& b)
{
    return ( (static_cast<const RQ_MD_MK&>(a)   ==  static_cast<const RQ_MD_MK&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&   true  );
};

bool operator!= (const oms_RQ_MD_MK& a, const oms_RQ_MD_MK& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_CC_MK& a, const oms_RQ_CC_MK& b)
{
    return ( (static_cast<const RQ_CC_MK&>(a)   ==  static_cast<const RQ_CC_MK&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&   true  );
};

bool operator!= (const oms_RQ_CC_MK& a, const oms_RQ_CC_MK& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_ORDERS_STATUS& a, const oms_RQ_ORDERS_STATUS& b)
{
    return ( (static_cast<const RQ_ORDERS_STATUS&>(a)   ==  static_cast<const RQ_ORDERS_STATUS&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&   true  );
};

bool operator!= (const oms_RQ_ORDERS_STATUS& a, const oms_RQ_ORDERS_STATUS& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (oms_RQ_NW_LS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (oms_RQ_NW_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RQ_NW_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_NW_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_NW_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_LS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const RQ_NW_LS&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (oms_RQ_MD_LS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (oms_RQ_MD_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RQ_MD_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_MD_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_MD_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_LS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const RQ_MD_LS&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (oms_RQ_CC_LS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (oms_RQ_CC_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RQ_CC_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_CC_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_CC_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_LS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const RQ_CC_LS&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (oms_RQ_NW_MK& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (oms_RQ_NW_MK& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RQ_NW_MK&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_NW_MK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_NW_MK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_MK& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const RQ_NW_MK&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_MK>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (oms_RQ_MD_MK& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (oms_RQ_MD_MK& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RQ_MD_MK&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_MD_MK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_MD_MK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_MK& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const RQ_MD_MK&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_MK>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (oms_RQ_CC_MK& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (oms_RQ_CC_MK& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RQ_CC_MK&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_CC_MK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_CC_MK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_MK& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const RQ_CC_MK&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_MK>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (oms_RQ_ORDERS_STATUS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (oms_RQ_ORDERS_STATUS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RQ_ORDERS_STATUS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_ORDERS_STATUS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_ORDERS_STATUS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_ORDERS_STATUS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const RQ_ORDERS_STATUS&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_ORDERS_STATUS>& a, const std::string& field)
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

qpid::messaging::Message oms_RQ_NW_LS::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const RQ_NW_LS&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message oms_RQ_MD_LS::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const RQ_MD_LS&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message oms_RQ_CC_LS::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const RQ_CC_LS&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message oms_RQ_NW_MK::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const RQ_NW_MK&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message oms_RQ_MD_MK::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const RQ_MD_MK&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message oms_RQ_CC_MK::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const RQ_CC_MK&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message oms_RQ_ORDERS_STATUS::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const RQ_ORDERS_STATUS&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




    oms_RQ_NW_LS  __internal_get_default(oms_RQ_NW_LS*)
    {
        return oms_RQ_NW_LS(
__internal_get_default((RQ_NW_LS*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_MD_LS  __internal_get_default(oms_RQ_MD_LS*)
    {
        return oms_RQ_MD_LS(
__internal_get_default((RQ_MD_LS*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_CC_LS  __internal_get_default(oms_RQ_CC_LS*)
    {
        return oms_RQ_CC_LS(
__internal_get_default((RQ_CC_LS*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_NW_MK  __internal_get_default(oms_RQ_NW_MK*)
    {
        return oms_RQ_NW_MK(
__internal_get_default((RQ_NW_MK*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_MD_MK  __internal_get_default(oms_RQ_MD_MK*)
    {
        return oms_RQ_MD_MK(
__internal_get_default((RQ_MD_MK*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_CC_MK  __internal_get_default(oms_RQ_CC_MK*)
    {
        return oms_RQ_CC_MK(
__internal_get_default((RQ_CC_MK*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_ORDERS_STATUS  __internal_get_default(oms_RQ_ORDERS_STATUS*)
    {
        return oms_RQ_ORDERS_STATUS(
__internal_get_default((RQ_ORDERS_STATUS*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    

oms_RQ_NW_LS::oms_RQ_NW_LS (const qpid::messaging::Message& msg)
    :  RQ_NW_LS(msg), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)) 
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



oms_RQ_MD_LS::oms_RQ_MD_LS (const qpid::messaging::Message& msg)
    :  RQ_MD_LS(msg), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)) 
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



oms_RQ_CC_LS::oms_RQ_CC_LS (const qpid::messaging::Message& msg)
    :  RQ_CC_LS(msg), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)) 
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



oms_RQ_NW_MK::oms_RQ_NW_MK (const qpid::messaging::Message& msg)
    :  RQ_NW_MK(msg), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)) 
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



oms_RQ_MD_MK::oms_RQ_MD_MK (const qpid::messaging::Message& msg)
    :  RQ_MD_MK(msg), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)) 
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



oms_RQ_CC_MK::oms_RQ_CC_MK (const qpid::messaging::Message& msg)
    :  RQ_CC_MK(msg), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)) 
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



oms_RQ_ORDERS_STATUS::oms_RQ_ORDERS_STATUS (const qpid::messaging::Message& msg)
    :  RQ_ORDERS_STATUS(msg), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)) 
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

mtk::t_qpid_filter  oms_RQ_NW_LS::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_NW_LS::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_NW_LS::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_NW_LS::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_MD_LS::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_MD_LS::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_MD_LS::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_MD_LS::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_CC_LS::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_CC_LS::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_CC_LS::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_CC_LS::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_NW_MK::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_NW_MK::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_NW_MK::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_NW_MK::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_MD_MK::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_MD_MK::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_MD_MK::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_MD_MK::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_CC_MK::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_CC_MK::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_CC_MK::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_CC_MK::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_ORDERS_STATUS::get_in_subject (const std::string& market,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << market << "." << from << ".RQORDST"));
    }
    mtk::t_qpid_filter  oms_RQ_ORDERS_STATUS::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->market << "." << this->from << ".RQORDST"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_ORDERS_STATUS::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_ORDERS_STATUS::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {


