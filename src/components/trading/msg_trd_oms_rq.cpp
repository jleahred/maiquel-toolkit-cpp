
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
            //list.push_back(*it);
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


oms_RQ_NW_LS::oms_RQ_NW_LS ( const RQ_NW_LS&  parent,   const std::string&  _reject_descr)
    :  RQ_NW_LS(parent),   reject_descr(_reject_descr) 
       
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



oms_RQ_MD_LS::oms_RQ_MD_LS ( const RQ_MD_LS&  parent,   const std::string&  _reject_descr)
    :  RQ_MD_LS(parent),   reject_descr(_reject_descr) 
       
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



oms_RQ_CC_LS::oms_RQ_CC_LS ( const RQ_CC_LS&  parent,   const std::string&  _reject_descr)
    :  RQ_CC_LS(parent),   reject_descr(_reject_descr) 
       
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


std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_NW_LS&>(c)  << ")" 
        << "reject_descr:"<<   c.reject_descr << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_MD_LS&>(c)  << ")" 
        << "reject_descr:"<<   c.reject_descr << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_CC_LS&>(c)  << ")" 
        << "reject_descr:"<<   c.reject_descr << "  "
        << " }";
    return o;
};



bool operator== (const oms_RQ_NW_LS& a, const oms_RQ_NW_LS& b)
{
    return ( (static_cast<const RQ_NW_LS&>(a)   ==  static_cast<const RQ_NW_LS&>(b))  &&           a.reject_descr ==  b.reject_descr  &&   true  );
};

bool operator!= (const oms_RQ_NW_LS& a, const oms_RQ_NW_LS& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_MD_LS& a, const oms_RQ_MD_LS& b)
{
    return ( (static_cast<const RQ_MD_LS&>(a)   ==  static_cast<const RQ_MD_LS&>(b))  &&           a.reject_descr ==  b.reject_descr  &&   true  );
};

bool operator!= (const oms_RQ_MD_LS& a, const oms_RQ_MD_LS& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_CC_LS& a, const oms_RQ_CC_LS& b)
{
    return ( (static_cast<const RQ_CC_LS&>(a)   ==  static_cast<const RQ_CC_LS&>(b))  &&           a.reject_descr ==  b.reject_descr  &&   true  );
};

bool operator!= (const oms_RQ_CC_LS& a, const oms_RQ_CC_LS& b)
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

                    it = mv.find("rd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_descr on message oms_RQ_NW_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_descr, it->second);
                        //c.reject_descr = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_LS& a)
{
    
//  parent
__internal_add2map(map, static_cast<const RQ_NW_LS&>(a));

//  field_type
        __internal_add2map(map, a.reject_descr, std::string("rd"));


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

                    it = mv.find("rd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_descr on message oms_RQ_MD_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_descr, it->second);
                        //c.reject_descr = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_LS& a)
{
    
//  parent
__internal_add2map(map, static_cast<const RQ_MD_LS&>(a));

//  field_type
        __internal_add2map(map, a.reject_descr, std::string("rd"));


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

                    it = mv.find("rd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_descr on message oms_RQ_CC_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_descr, it->second);
                        //c.reject_descr = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_LS& a)
{
    
//  parent
__internal_add2map(map, static_cast<const RQ_CC_LS&>(a));

//  field_type
        __internal_add2map(map, a.reject_descr, std::string("rd"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)

    oms_RQ_NW_LS  __internal_get_default(oms_RQ_NW_LS*)
    {
        return oms_RQ_NW_LS(
__internal_get_default((RQ_NW_LS*)0), //   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_MD_LS  __internal_get_default(oms_RQ_MD_LS*)
    {
        return oms_RQ_MD_LS(
__internal_get_default((RQ_MD_LS*)0), //   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_CC_LS  __internal_get_default(oms_RQ_CC_LS*)
    {
        return oms_RQ_CC_LS(
__internal_get_default((RQ_CC_LS*)0), //   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    

oms_RQ_NW_LS::oms_RQ_NW_LS (const qpid::messaging::Message& msg)
    :  RQ_NW_LS(msg), //   field_type
   reject_descr(__internal_get_default((std::string*)0)) 
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
   reject_descr(__internal_get_default((std::string*)0)) 
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
   reject_descr(__internal_get_default((std::string*)0)) 
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



};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {


