
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_trd_cli_ls.h"

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


	template <typename T>
	inline void  operator >> (const YAML::Node& seq, mtk::list <T>& v) 
    {
        for(unsigned i=0; i<seq.size(); ++i)
        {
            T t = __internal_get_default((T*)0);
            seq[i] >> t;
            v.push_back(t);
        }
	}

	template <typename T>
	inline void  operator >> (const YAML::Node& n, mtk::nullable <T>& nv) 
    {
        if(n.size()!=0)
        {
            T t = __internal_get_default((T*)0);
            n >> t;
            nv = t;
        }
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


sub_position_ls::sub_position_ls (   const mtk::FixedNumber&  _price,   const mtk::FixedNumber&  _quantity)
    :     price(_price),   quantity(_quantity) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_position_ls::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_position_ls::before_send(void) const
{

}




RQ_XX_LS::RQ_XX_LS ( const RQ_XX&  parent,   const sub_position_ls&  _request_pos)
    :  RQ_XX(parent),   request_pos(_request_pos) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string RQ_XX_LS::check_recomended(void) const
{
    std::string result;

    return result;
}

void RQ_XX_LS::before_send(void) const
{

}




RQ_NW_LS::RQ_NW_LS ( const RQ_XX_LS&  parent)
    :  RQ_XX_LS(parent) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string RQ_NW_LS::check_recomended(void) const
{
    std::string result;

    return result;
}

void RQ_NW_LS::before_send(void) const
{

}




RQ_MD_LS::RQ_MD_LS ( const RQ_XX_LS&  parent)
    :  RQ_XX_LS(parent) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string RQ_MD_LS::check_recomended(void) const
{
    std::string result;

    return result;
}

void RQ_MD_LS::before_send(void) const
{

}




RQ_CC_LS::RQ_CC_LS ( const RQ_XX_LS&  parent)
    :  RQ_XX_LS(parent) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string RQ_CC_LS::check_recomended(void) const
{
    std::string result;

    return result;
}

void RQ_CC_LS::before_send(void) const
{

}




CF_XX_LS::CF_XX_LS ( const CF_XX&  parent,   const sub_position_ls&  _market_pos)
    :  CF_XX(parent),   market_pos(_market_pos) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string CF_XX_LS::check_recomended(void) const
{
    std::string result;

    return result;
}

void CF_XX_LS::before_send(void) const
{

}




CF_NW_LS::CF_NW_LS ( const CF_XX_LS&  parent)
    :  CF_XX_LS(parent) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string CF_NW_LS::check_recomended(void) const
{
    std::string result;

    return result;
}

void CF_NW_LS::before_send(void) const
{

}




CF_MD_LS::CF_MD_LS ( const CF_XX_LS&  parent)
    :  CF_XX_LS(parent) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string CF_MD_LS::check_recomended(void) const
{
    std::string result;

    return result;
}

void CF_MD_LS::before_send(void) const
{

}




CF_CC_LS::CF_CC_LS ( const CF_XX_LS&  parent)
    :  CF_XX_LS(parent) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string CF_CC_LS::check_recomended(void) const
{
    std::string result;

    return result;
}

void CF_CC_LS::before_send(void) const
{

}




CF_EX_LS::CF_EX_LS ( const CF_XX_LS&  parent,   const sub_exec_conf&  _executed_pos)
    :  CF_XX_LS(parent),   executed_pos(_executed_pos) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string CF_EX_LS::check_recomended(void) const
{
    std::string result;

    return result;
}

void CF_EX_LS::before_send(void) const
{

}




RJ_NW_LS::RJ_NW_LS ( const CF_XX_LS&  parent,   const std::string&  _reject_description)
    :  CF_XX_LS(parent),   reject_description(_reject_description) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string RJ_NW_LS::check_recomended(void) const
{
    std::string result;

    return result;
}

void RJ_NW_LS::before_send(void) const
{

}




RJ_MD_LS::RJ_MD_LS ( const CF_XX_LS&  parent,   const std::string&  _reject_description)
    :  CF_XX_LS(parent),   reject_description(_reject_description) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string RJ_MD_LS::check_recomended(void) const
{
    std::string result;

    return result;
}

void RJ_MD_LS::before_send(void) const
{

}




RJ_CC_LS::RJ_CC_LS ( const CF_XX_LS&  parent,   const std::string&  _reject_description)
    :  CF_XX_LS(parent),   reject_description(_reject_description) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string RJ_CC_LS::check_recomended(void) const
{
    std::string result;

    return result;
}

void RJ_CC_LS::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const sub_position_ls & c)
{
    o << "{ "

        << "price:"<<   c.price << "  "        << "quantity:"<<   c.quantity << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_position_ls & c)
{
    o << YAML::BeginMap

        << YAML::Key << "price"  << YAML::Value <<   c.price        << YAML::Key << "quantity"  << YAML::Value <<   c.quantity
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_position_ls & c)
{


        node["price"]  >> c.price;
        node["quantity"]  >> c.quantity;


};


std::ostream& operator<< (std::ostream& o, const RQ_XX_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_XX&>(c)  << ")" 
        << "request_pos:"<< c.request_pos<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RQ_XX_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_XX" <<  YAML::Value << static_cast<const RQ_XX&>(c)  
        << YAML::Key << "request_pos"  << YAML::Value << c.request_pos
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RQ_XX_LS & c)
{

    node["RQ_XX"]   >>   static_cast<RQ_XX&>(c)  ;

        node["request_pos"]  >> c.request_pos;


};


std::ostream& operator<< (std::ostream& o, const RQ_NW_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_XX_LS&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RQ_NW_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_XX_LS" <<  YAML::Value << static_cast<const RQ_XX_LS&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RQ_NW_LS & c)
{

    node["RQ_XX_LS"]   >>   static_cast<RQ_XX_LS&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const RQ_MD_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_XX_LS&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RQ_MD_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_XX_LS" <<  YAML::Value << static_cast<const RQ_XX_LS&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RQ_MD_LS & c)
{

    node["RQ_XX_LS"]   >>   static_cast<RQ_XX_LS&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const RQ_CC_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_XX_LS&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RQ_CC_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_XX_LS" <<  YAML::Value << static_cast<const RQ_XX_LS&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RQ_CC_LS & c)
{

    node["RQ_XX_LS"]   >>   static_cast<RQ_XX_LS&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const CF_XX_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX&>(c)  << ")" 
        << "market_pos:"<< c.market_pos<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const CF_XX_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX" <<  YAML::Value << static_cast<const CF_XX&>(c)  
        << YAML::Key << "market_pos"  << YAML::Value << c.market_pos
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, CF_XX_LS & c)
{

    node["CF_XX"]   >>   static_cast<CF_XX&>(c)  ;

        node["market_pos"]  >> c.market_pos;


};


std::ostream& operator<< (std::ostream& o, const CF_NW_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX_LS&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const CF_NW_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX_LS" <<  YAML::Value << static_cast<const CF_XX_LS&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, CF_NW_LS & c)
{

    node["CF_XX_LS"]   >>   static_cast<CF_XX_LS&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const CF_MD_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX_LS&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const CF_MD_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX_LS" <<  YAML::Value << static_cast<const CF_XX_LS&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, CF_MD_LS & c)
{

    node["CF_XX_LS"]   >>   static_cast<CF_XX_LS&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const CF_CC_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX_LS&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const CF_CC_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX_LS" <<  YAML::Value << static_cast<const CF_XX_LS&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, CF_CC_LS & c)
{

    node["CF_XX_LS"]   >>   static_cast<CF_XX_LS&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const CF_EX_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX_LS&>(c)  << ")" 
        << "executed_pos:"<< c.executed_pos<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const CF_EX_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX_LS" <<  YAML::Value << static_cast<const CF_XX_LS&>(c)  
        << YAML::Key << "executed_pos"  << YAML::Value << c.executed_pos
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, CF_EX_LS & c)
{

    node["CF_XX_LS"]   >>   static_cast<CF_XX_LS&>(c)  ;

        node["executed_pos"]  >> c.executed_pos;


};


std::ostream& operator<< (std::ostream& o, const RJ_NW_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX_LS&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RJ_NW_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX_LS" <<  YAML::Value << static_cast<const CF_XX_LS&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RJ_NW_LS & c)
{

    node["CF_XX_LS"]   >>   static_cast<CF_XX_LS&>(c)  ;

        node["reject_description"]  >> c.reject_description;


};


std::ostream& operator<< (std::ostream& o, const RJ_MD_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX_LS&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RJ_MD_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX_LS" <<  YAML::Value << static_cast<const CF_XX_LS&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RJ_MD_LS & c)
{

    node["CF_XX_LS"]   >>   static_cast<CF_XX_LS&>(c)  ;

        node["reject_description"]  >> c.reject_description;


};


std::ostream& operator<< (std::ostream& o, const RJ_CC_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX_LS&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RJ_CC_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX_LS" <<  YAML::Value << static_cast<const CF_XX_LS&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RJ_CC_LS & c)
{

    node["CF_XX_LS"]   >>   static_cast<CF_XX_LS&>(c)  ;

        node["reject_description"]  >> c.reject_description;


};


bool operator== (const sub_position_ls& a, const sub_position_ls& b)
{
    return (          a.price ==  b.price  &&          a.quantity ==  b.quantity  &&   true  );
};

bool operator!= (const sub_position_ls& a, const sub_position_ls& b)
{
    return !(a==b);
};



bool operator== (const RQ_XX_LS& a, const RQ_XX_LS& b)
{
    return ( (static_cast<const RQ_XX&>(a)   ==  static_cast<const RQ_XX&>(b))  &&           a.request_pos ==  b.request_pos  &&   true  );
};

bool operator!= (const RQ_XX_LS& a, const RQ_XX_LS& b)
{
    return !(a==b);
};



bool operator== (const RQ_NW_LS& a, const RQ_NW_LS& b)
{
    return ( (static_cast<const RQ_XX_LS&>(a)   ==  static_cast<const RQ_XX_LS&>(b))  &&    true  );
};

bool operator!= (const RQ_NW_LS& a, const RQ_NW_LS& b)
{
    return !(a==b);
};



bool operator== (const RQ_MD_LS& a, const RQ_MD_LS& b)
{
    return ( (static_cast<const RQ_XX_LS&>(a)   ==  static_cast<const RQ_XX_LS&>(b))  &&    true  );
};

bool operator!= (const RQ_MD_LS& a, const RQ_MD_LS& b)
{
    return !(a==b);
};



bool operator== (const RQ_CC_LS& a, const RQ_CC_LS& b)
{
    return ( (static_cast<const RQ_XX_LS&>(a)   ==  static_cast<const RQ_XX_LS&>(b))  &&    true  );
};

bool operator!= (const RQ_CC_LS& a, const RQ_CC_LS& b)
{
    return !(a==b);
};



bool operator== (const CF_XX_LS& a, const CF_XX_LS& b)
{
    return ( (static_cast<const CF_XX&>(a)   ==  static_cast<const CF_XX&>(b))  &&           a.market_pos ==  b.market_pos  &&   true  );
};

bool operator!= (const CF_XX_LS& a, const CF_XX_LS& b)
{
    return !(a==b);
};



bool operator== (const CF_NW_LS& a, const CF_NW_LS& b)
{
    return ( (static_cast<const CF_XX_LS&>(a)   ==  static_cast<const CF_XX_LS&>(b))  &&    true  );
};

bool operator!= (const CF_NW_LS& a, const CF_NW_LS& b)
{
    return !(a==b);
};



bool operator== (const CF_MD_LS& a, const CF_MD_LS& b)
{
    return ( (static_cast<const CF_XX_LS&>(a)   ==  static_cast<const CF_XX_LS&>(b))  &&    true  );
};

bool operator!= (const CF_MD_LS& a, const CF_MD_LS& b)
{
    return !(a==b);
};



bool operator== (const CF_CC_LS& a, const CF_CC_LS& b)
{
    return ( (static_cast<const CF_XX_LS&>(a)   ==  static_cast<const CF_XX_LS&>(b))  &&    true  );
};

bool operator!= (const CF_CC_LS& a, const CF_CC_LS& b)
{
    return !(a==b);
};



bool operator== (const CF_EX_LS& a, const CF_EX_LS& b)
{
    return ( (static_cast<const CF_XX_LS&>(a)   ==  static_cast<const CF_XX_LS&>(b))  &&           a.executed_pos ==  b.executed_pos  &&   true  );
};

bool operator!= (const CF_EX_LS& a, const CF_EX_LS& b)
{
    return !(a==b);
};



bool operator== (const RJ_NW_LS& a, const RJ_NW_LS& b)
{
    return ( (static_cast<const CF_XX_LS&>(a)   ==  static_cast<const CF_XX_LS&>(b))  &&           a.reject_description ==  b.reject_description  &&   true  );
};

bool operator!= (const RJ_NW_LS& a, const RJ_NW_LS& b)
{
    return !(a==b);
};



bool operator== (const RJ_MD_LS& a, const RJ_MD_LS& b)
{
    return ( (static_cast<const CF_XX_LS&>(a)   ==  static_cast<const CF_XX_LS&>(b))  &&           a.reject_description ==  b.reject_description  &&   true  );
};

bool operator!= (const RJ_MD_LS& a, const RJ_MD_LS& b)
{
    return !(a==b);
};



bool operator== (const RJ_CC_LS& a, const RJ_CC_LS& b)
{
    return ( (static_cast<const CF_XX_LS&>(a)   ==  static_cast<const CF_XX_LS&>(b))  &&           a.reject_description ==  b.reject_description  &&   true  );
};

bool operator!= (const RJ_CC_LS& a, const RJ_CC_LS& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (sub_position_ls& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_position_ls& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("pr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field price on message sub_position_ls::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.price, it->second);
                        //c.price = it->second;
//   field_type

                    it = mv.find("qt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field quantity on message sub_position_ls::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.quantity, it->second);
                        //c.quantity = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_position_ls& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.price, std::string("pr"));
//  field_type
        __internal_add2map(map, a.quantity, std::string("qt"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_position_ls>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (RQ_XX_LS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (RQ_XX_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RQ_XX&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rp");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_pos on message RQ_XX_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_pos, it->second);
                        //__internal_qpid_fill(c.request_pos, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const RQ_XX_LS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const RQ_XX&>(a));

//  sub_msg_type
        __internal_add2map(map, a.request_pos, std::string("rp"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_XX_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (RQ_NW_LS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (RQ_NW_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RQ_XX_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const RQ_NW_LS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const RQ_XX_LS&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_NW_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (RQ_MD_LS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (RQ_MD_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RQ_XX_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const RQ_MD_LS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const RQ_XX_LS&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_MD_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (RQ_CC_LS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (RQ_CC_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RQ_XX_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const RQ_CC_LS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const RQ_XX_LS&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_CC_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (CF_XX_LS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (CF_XX_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("mp");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field market_pos on message CF_XX_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.market_pos, it->second);
                        //__internal_qpid_fill(c.market_pos, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const CF_XX_LS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const CF_XX&>(a));

//  sub_msg_type
        __internal_add2map(map, a.market_pos, std::string("mp"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_XX_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (CF_NW_LS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (CF_NW_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const CF_NW_LS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const CF_XX_LS&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_NW_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (CF_MD_LS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (CF_MD_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const CF_MD_LS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const CF_XX_LS&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_MD_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (CF_CC_LS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (CF_CC_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const CF_CC_LS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const CF_XX_LS&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_CC_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (CF_EX_LS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (CF_EX_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("exc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field executed_pos on message CF_EX_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.executed_pos, it->second);
                        //__internal_qpid_fill(c.executed_pos, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const CF_EX_LS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const CF_XX_LS&>(a));

//  sub_msg_type
        __internal_add2map(map, a.executed_pos, std::string("exc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_EX_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (RJ_NW_LS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (RJ_NW_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message RJ_NW_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const RJ_NW_LS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const CF_XX_LS&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rd"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_NW_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (RJ_MD_LS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (RJ_MD_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message RJ_MD_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const RJ_MD_LS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const CF_XX_LS&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rd"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_MD_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (RJ_CC_LS& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (RJ_CC_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message RJ_CC_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const RJ_CC_LS& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const CF_XX_LS&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rd"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_CC_LS>& a, const std::string& field)
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
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)

qpid::messaging::Message RQ_NW_LS::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const RQ_XX_LS&>(*this));



    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message RQ_MD_LS::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const RQ_XX_LS&>(*this));



    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message RQ_CC_LS::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const RQ_XX_LS&>(*this));



    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message CF_NW_LS::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const CF_XX_LS&>(*this));



    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message CF_MD_LS::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const CF_XX_LS&>(*this));



    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message CF_CC_LS::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const CF_XX_LS&>(*this));



    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message CF_EX_LS::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const CF_XX_LS&>(*this));

//  sub_msg_type
//        content["exc"] =  qpidmsg_coded_as_qpid_Map(this->executed_pos);
        __internal_add2map(content, this->executed_pos, std::string("exc"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message RJ_NW_LS::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const CF_XX_LS&>(*this));

//  field_type
//        content["rd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rd"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message RJ_MD_LS::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const CF_XX_LS&>(*this));

//  field_type
//        content["rd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rd"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message RJ_CC_LS::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const CF_XX_LS&>(*this));

//  field_type
//        content["rd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rd"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




    sub_position_ls  __internal_get_default(sub_position_ls*)
    {
        return sub_position_ls(
//   field_type
   __internal_get_default ((mtk::FixedNumber*)0),
//   field_type
   __internal_get_default ((mtk::FixedNumber*)0)
            );
    }
    
    RQ_XX_LS  __internal_get_default(RQ_XX_LS*)
    {
        return RQ_XX_LS(
__internal_get_default((RQ_XX*)0), //   sub_msg_type
   __internal_get_default((sub_position_ls*)0)
            );
    }
    
    RQ_NW_LS  __internal_get_default(RQ_NW_LS*)
    {
        return RQ_NW_LS(
__internal_get_default((RQ_XX_LS*)0)
            );
    }
    
    RQ_MD_LS  __internal_get_default(RQ_MD_LS*)
    {
        return RQ_MD_LS(
__internal_get_default((RQ_XX_LS*)0)
            );
    }
    
    RQ_CC_LS  __internal_get_default(RQ_CC_LS*)
    {
        return RQ_CC_LS(
__internal_get_default((RQ_XX_LS*)0)
            );
    }
    
    CF_XX_LS  __internal_get_default(CF_XX_LS*)
    {
        return CF_XX_LS(
__internal_get_default((CF_XX*)0), //   sub_msg_type
   __internal_get_default((sub_position_ls*)0)
            );
    }
    
    CF_NW_LS  __internal_get_default(CF_NW_LS*)
    {
        return CF_NW_LS(
__internal_get_default((CF_XX_LS*)0)
            );
    }
    
    CF_MD_LS  __internal_get_default(CF_MD_LS*)
    {
        return CF_MD_LS(
__internal_get_default((CF_XX_LS*)0)
            );
    }
    
    CF_CC_LS  __internal_get_default(CF_CC_LS*)
    {
        return CF_CC_LS(
__internal_get_default((CF_XX_LS*)0)
            );
    }
    
    CF_EX_LS  __internal_get_default(CF_EX_LS*)
    {
        return CF_EX_LS(
__internal_get_default((CF_XX_LS*)0), //   sub_msg_type
   __internal_get_default((sub_exec_conf*)0)
            );
    }
    
    RJ_NW_LS  __internal_get_default(RJ_NW_LS*)
    {
        return RJ_NW_LS(
__internal_get_default((CF_XX_LS*)0), //   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    RJ_MD_LS  __internal_get_default(RJ_MD_LS*)
    {
        return RJ_MD_LS(
__internal_get_default((CF_XX_LS*)0), //   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    RJ_CC_LS  __internal_get_default(RJ_CC_LS*)
    {
        return RJ_CC_LS(
__internal_get_default((CF_XX_LS*)0), //   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    

sub_position_ls::sub_position_ls (const qpid::messaging::Message& msg)
    :  //   field_type
   price(__internal_get_default((mtk::FixedNumber*)0)),
//   field_type
   quantity(__internal_get_default((mtk::FixedNumber*)0)) 
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



RQ_XX_LS::RQ_XX_LS (const qpid::messaging::Message& msg)
    :  RQ_XX(msg), //   sub_msg_type
   request_pos(__internal_get_default((sub_position_ls*)0)) 
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



RQ_NW_LS::RQ_NW_LS (const qpid::messaging::Message& msg)
    :  RQ_XX_LS(msg) 
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



RQ_MD_LS::RQ_MD_LS (const qpid::messaging::Message& msg)
    :  RQ_XX_LS(msg) 
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



RQ_CC_LS::RQ_CC_LS (const qpid::messaging::Message& msg)
    :  RQ_XX_LS(msg) 
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



CF_XX_LS::CF_XX_LS (const qpid::messaging::Message& msg)
    :  CF_XX(msg), //   sub_msg_type
   market_pos(__internal_get_default((sub_position_ls*)0)) 
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



CF_NW_LS::CF_NW_LS (const qpid::messaging::Message& msg)
    :  CF_XX_LS(msg) 
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



CF_MD_LS::CF_MD_LS (const qpid::messaging::Message& msg)
    :  CF_XX_LS(msg) 
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



CF_CC_LS::CF_CC_LS (const qpid::messaging::Message& msg)
    :  CF_XX_LS(msg) 
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



CF_EX_LS::CF_EX_LS (const qpid::messaging::Message& msg)
    :  CF_XX_LS(msg), //   sub_msg_type
   executed_pos(__internal_get_default((sub_exec_conf*)0)) 
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



RJ_NW_LS::RJ_NW_LS (const qpid::messaging::Message& msg)
    :  CF_XX_LS(msg), //   field_type
   reject_description(__internal_get_default((std::string*)0)) 
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



RJ_MD_LS::RJ_MD_LS (const qpid::messaging::Message& msg)
    :  CF_XX_LS(msg), //   field_type
   reject_description(__internal_get_default((std::string*)0)) 
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



RJ_CC_LS::RJ_CC_LS (const qpid::messaging::Message& msg)
    :  CF_XX_LS(msg), //   field_type
   reject_description(__internal_get_default((std::string*)0)) 
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

std::string  RQ_NW_LS::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_product_code_product)
    {
        return MTK_SS("RQ." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_product_code_product << "");
    }
    std::string  RQ_NW_LS::get_out_subject (void) const
    {
        return MTK_SS("RQ." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "");
    }
    std::string  RQ_MD_LS::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_product_code_product)
    {
        return MTK_SS("RQ." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_product_code_product << "");
    }
    std::string  RQ_MD_LS::get_out_subject (void) const
    {
        return MTK_SS("RQ." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "");
    }
    std::string  RQ_CC_LS::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_product_code_product)
    {
        return MTK_SS("RQ." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_product_code_product << "");
    }
    std::string  RQ_CC_LS::get_out_subject (void) const
    {
        return MTK_SS("RQ." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "");
    }
    std::string  CF_NW_LS::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name,const std::string& invariant_product_code_product)
    {
        return MTK_SS("CONF." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << "." << invariant_product_code_product << "");
    }
    std::string  CF_NW_LS::get_out_subject (void) const
    {
        return MTK_SS("CONF." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << "." << this->invariant.product_code.product << "");
    }
    std::string  CF_MD_LS::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name,const std::string& invariant_product_code_product)
    {
        return MTK_SS("CONF." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << "." << invariant_product_code_product << "");
    }
    std::string  CF_MD_LS::get_out_subject (void) const
    {
        return MTK_SS("CONF." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << "." << this->invariant.product_code.product << "");
    }
    std::string  CF_CC_LS::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name,const std::string& invariant_product_code_product)
    {
        return MTK_SS("CONF." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << "." << invariant_product_code_product << "");
    }
    std::string  CF_CC_LS::get_out_subject (void) const
    {
        return MTK_SS("CONF." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << "." << this->invariant.product_code.product << "");
    }
    std::string  CF_EX_LS::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name,const std::string& invariant_product_code_product)
    {
        return MTK_SS("CONF." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << "." << invariant_product_code_product << "");
    }
    std::string  CF_EX_LS::get_out_subject (void) const
    {
        return MTK_SS("CONF." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << "." << this->invariant.product_code.product << "");
    }
    std::string  RJ_NW_LS::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name,const std::string& invariant_product_code_product)
    {
        return MTK_SS("CONF." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << "." << invariant_product_code_product << "");
    }
    std::string  RJ_NW_LS::get_out_subject (void) const
    {
        return MTK_SS("CONF." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << "." << this->invariant.product_code.product << "");
    }
    std::string  RJ_MD_LS::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name,const std::string& invariant_product_code_product)
    {
        return MTK_SS("CONF." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << "." << invariant_product_code_product << "");
    }
    std::string  RJ_MD_LS::get_out_subject (void) const
    {
        return MTK_SS("CONF." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << "." << this->invariant.product_code.product << "");
    }
    std::string  RJ_CC_LS::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name,const std::string& invariant_product_code_product)
    {
        return MTK_SS("CONF." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << "." << invariant_product_code_product << "");
    }
    std::string  RJ_CC_LS::get_out_subject (void) const
    {
        return MTK_SS("CONF." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << "." << this->invariant.product_code.product << "");
    }
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {


