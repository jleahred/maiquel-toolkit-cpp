
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_trd_cli_sl.h"

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


sub_position_sl::sub_position_sl (   const mtk::FixedNumber&  _stop_price,   const mtk::FixedNumber&  _price,   const mtk::FixedNumber&  _quantity,   const std::string&  _cli_ref)
    :     stop_price(_stop_price),   price(_price),   quantity(_quantity),   cli_ref(_cli_ref) 
       
    {  
    }



void  sub_position_sl::check_recomended(void) const
{

}

void sub_position_sl::before_send(void) const
{

}




RQ_XX_SL::RQ_XX_SL ( const RQ_XX&  parent,   const sub_position_sl&  _request_pos)
    :  RQ_XX(parent),   request_pos(_request_pos) 
       
    {  
    }



void  RQ_XX_SL::check_recomended(void) const
{

}

void RQ_XX_SL::before_send(void) const
{

}




RQ_NW_SL::RQ_NW_SL ( const RQ_XX_SL&  parent)
    :  RQ_XX_SL(parent) 
       , __internal_warning_control_fields(0)
    {  
    }



void  RQ_NW_SL::check_recomended(void) const
{

}

void RQ_NW_SL::before_send(void) const
{

}




RQ_MD_SL::RQ_MD_SL ( const RQ_XX_SL&  parent)
    :  RQ_XX_SL(parent) 
       , __internal_warning_control_fields(0)
    {  
    }



void  RQ_MD_SL::check_recomended(void) const
{

}

void RQ_MD_SL::before_send(void) const
{

}




RQ_CC_SL::RQ_CC_SL ( const RQ_XX_SL&  parent)
    :  RQ_XX_SL(parent) 
       , __internal_warning_control_fields(0)
    {  
    }



void  RQ_CC_SL::check_recomended(void) const
{

}

void RQ_CC_SL::before_send(void) const
{

}




CF_XX_SL::CF_XX_SL ( const CF_XX&  parent,   const sub_position_sl&  _market_pos)
    :  CF_XX(parent),   market_pos(_market_pos) 
       
    {  
    }



void  CF_XX_SL::check_recomended(void) const
{

}

void CF_XX_SL::before_send(void) const
{

}




CF_NW_SL::CF_NW_SL ( const CF_XX_SL&  parent)
    :  CF_XX_SL(parent) 
       , __internal_warning_control_fields(0)
    {  
    }



void  CF_NW_SL::check_recomended(void) const
{

}

void CF_NW_SL::before_send(void) const
{

}




CF_MD_SL::CF_MD_SL ( const CF_XX_SL&  parent)
    :  CF_XX_SL(parent) 
       , __internal_warning_control_fields(0)
    {  
    }



void  CF_MD_SL::check_recomended(void) const
{

}

void CF_MD_SL::before_send(void) const
{

}




CF_CC_SL::CF_CC_SL ( const CF_XX_SL&  parent)
    :  CF_XX_SL(parent) 
       , __internal_warning_control_fields(0)
    {  
    }



void  CF_CC_SL::check_recomended(void) const
{

}

void CF_CC_SL::before_send(void) const
{

}




CF_TR_SL::CF_TR_SL ( const CF_XX_SL&  parent)
    :  CF_XX_SL(parent) 
       , __internal_warning_control_fields(0)
    {  
    }



void  CF_TR_SL::check_recomended(void) const
{

}

void CF_TR_SL::before_send(void) const
{

}




RJ_XX_SL::RJ_XX_SL ( const CF_XX_SL&  parent,   const sub_position_sl&  _request_pos)
    :  CF_XX_SL(parent),   request_pos(_request_pos) 
       
    {  
    }



void  RJ_XX_SL::check_recomended(void) const
{

}

void RJ_XX_SL::before_send(void) const
{

}




RJ_NW_SL::RJ_NW_SL ( const RJ_XX_SL&  parent)
    :  RJ_XX_SL(parent) 
       , __internal_warning_control_fields(0)
    {  
    }



void  RJ_NW_SL::check_recomended(void) const
{

}

void RJ_NW_SL::before_send(void) const
{

}




RJ_MD_SL::RJ_MD_SL ( const RJ_XX_SL&  parent)
    :  RJ_XX_SL(parent) 
       , __internal_warning_control_fields(0)
    {  
    }



void  RJ_MD_SL::check_recomended(void) const
{

}

void RJ_MD_SL::before_send(void) const
{

}




RJ_CC_SL::RJ_CC_SL ( const RJ_XX_SL&  parent)
    :  RJ_XX_SL(parent) 
       , __internal_warning_control_fields(0)
    {  
    }



void  RJ_CC_SL::check_recomended(void) const
{

}

void RJ_CC_SL::before_send(void) const
{

}




CF_ST_SL::CF_ST_SL ( const CF_XX_SL&  parent,   const mtk::msg::sub_gen_response_location&  _gen_response_location)
    :  CF_XX_SL(parent),   gen_response_location(_gen_response_location) 
       , __internal_warning_control_fields(0)
    {  
    }



void  CF_ST_SL::check_recomended(void) const
{

}

void CF_ST_SL::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const sub_position_sl & c)
{
    o << "{ "

        << "stop_price:"<<   c.stop_price << "  "        << "price:"<<   c.price << "  "        << "quantity:"<<   c.quantity << "  "        << "cli_ref:"<<   c.cli_ref << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_position_sl & c)
{
    o << YAML::BeginMap

        << YAML::Key << "stop_price"  << YAML::Value <<   c.stop_price        << YAML::Key << "price"  << YAML::Value <<   c.price        << YAML::Key << "quantity"  << YAML::Value <<   c.quantity        << YAML::Key << "cli_ref"  << YAML::Value <<   c.cli_ref
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_position_sl & c)
{


        node["stop_price"]  >> c.stop_price;
        node["price"]  >> c.price;
        node["quantity"]  >> c.quantity;
        node["cli_ref"]  >> c.cli_ref;


};


std::ostream& operator<< (std::ostream& o, const RQ_XX_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_XX&>(c)  << ")" 
        << "request_pos:"<< c.request_pos<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RQ_XX_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_XX" <<  YAML::Value << static_cast<const RQ_XX&>(c)  
        << YAML::Key << "request_pos"  << YAML::Value << c.request_pos
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RQ_XX_SL & c)
{

    node["RQ_XX"]   >>   static_cast<RQ_XX&>(c)  ;

        node["request_pos"]  >> c.request_pos;


};


std::ostream& operator<< (std::ostream& o, const RQ_NW_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_XX_SL&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RQ_NW_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_XX_SL" <<  YAML::Value << static_cast<const RQ_XX_SL&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RQ_NW_SL & c)
{

    node["RQ_XX_SL"]   >>   static_cast<RQ_XX_SL&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const RQ_MD_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_XX_SL&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RQ_MD_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_XX_SL" <<  YAML::Value << static_cast<const RQ_XX_SL&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RQ_MD_SL & c)
{

    node["RQ_XX_SL"]   >>   static_cast<RQ_XX_SL&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const RQ_CC_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_XX_SL&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RQ_CC_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_XX_SL" <<  YAML::Value << static_cast<const RQ_XX_SL&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RQ_CC_SL & c)
{

    node["RQ_XX_SL"]   >>   static_cast<RQ_XX_SL&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const CF_XX_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX&>(c)  << ")" 
        << "market_pos:"<< c.market_pos<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const CF_XX_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX" <<  YAML::Value << static_cast<const CF_XX&>(c)  
        << YAML::Key << "market_pos"  << YAML::Value << c.market_pos
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, CF_XX_SL & c)
{

    node["CF_XX"]   >>   static_cast<CF_XX&>(c)  ;

        node["market_pos"]  >> c.market_pos;


};


std::ostream& operator<< (std::ostream& o, const CF_NW_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX_SL&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const CF_NW_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX_SL" <<  YAML::Value << static_cast<const CF_XX_SL&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, CF_NW_SL & c)
{

    node["CF_XX_SL"]   >>   static_cast<CF_XX_SL&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const CF_MD_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX_SL&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const CF_MD_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX_SL" <<  YAML::Value << static_cast<const CF_XX_SL&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, CF_MD_SL & c)
{

    node["CF_XX_SL"]   >>   static_cast<CF_XX_SL&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const CF_CC_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX_SL&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const CF_CC_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX_SL" <<  YAML::Value << static_cast<const CF_XX_SL&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, CF_CC_SL & c)
{

    node["CF_XX_SL"]   >>   static_cast<CF_XX_SL&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const CF_TR_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX_SL&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const CF_TR_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX_SL" <<  YAML::Value << static_cast<const CF_XX_SL&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, CF_TR_SL & c)
{

    node["CF_XX_SL"]   >>   static_cast<CF_XX_SL&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const RJ_XX_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX_SL&>(c)  << ")" 
        << "request_pos:"<< c.request_pos<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RJ_XX_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX_SL" <<  YAML::Value << static_cast<const CF_XX_SL&>(c)  
        << YAML::Key << "request_pos"  << YAML::Value << c.request_pos
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RJ_XX_SL & c)
{

    node["CF_XX_SL"]   >>   static_cast<CF_XX_SL&>(c)  ;

        node["request_pos"]  >> c.request_pos;


};


std::ostream& operator<< (std::ostream& o, const RJ_NW_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const RJ_XX_SL&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RJ_NW_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RJ_XX_SL" <<  YAML::Value << static_cast<const RJ_XX_SL&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RJ_NW_SL & c)
{

    node["RJ_XX_SL"]   >>   static_cast<RJ_XX_SL&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const RJ_MD_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const RJ_XX_SL&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RJ_MD_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RJ_XX_SL" <<  YAML::Value << static_cast<const RJ_XX_SL&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RJ_MD_SL & c)
{

    node["RJ_XX_SL"]   >>   static_cast<RJ_XX_SL&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const RJ_CC_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const RJ_XX_SL&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RJ_CC_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RJ_XX_SL" <<  YAML::Value << static_cast<const RJ_XX_SL&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RJ_CC_SL & c)
{

    node["RJ_XX_SL"]   >>   static_cast<RJ_XX_SL&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const CF_ST_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX_SL&>(c)  << ")" 
        << "gen_response_location:"<< c.gen_response_location<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const CF_ST_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX_SL" <<  YAML::Value << static_cast<const CF_XX_SL&>(c)  
        << YAML::Key << "gen_response_location"  << YAML::Value << c.gen_response_location
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, CF_ST_SL & c)
{

    node["CF_XX_SL"]   >>   static_cast<CF_XX_SL&>(c)  ;

        node["gen_response_location"]  >> c.gen_response_location;


};


bool operator== (const sub_position_sl& a, const sub_position_sl& b)
{
    return (          a.stop_price ==  b.stop_price  &&          a.price ==  b.price  &&          a.quantity ==  b.quantity  &&          a.cli_ref ==  b.cli_ref  &&   true  );
};

bool operator!= (const sub_position_sl& a, const sub_position_sl& b)
{
    return !(a==b);
};



bool operator== (const RQ_XX_SL& a, const RQ_XX_SL& b)
{
    return ( (static_cast<const RQ_XX&>(a)   ==  static_cast<const RQ_XX&>(b))  &&           a.request_pos ==  b.request_pos  &&   true  );
};

bool operator!= (const RQ_XX_SL& a, const RQ_XX_SL& b)
{
    return !(a==b);
};



bool operator== (const RQ_NW_SL& a, const RQ_NW_SL& b)
{
    return ( (static_cast<const RQ_XX_SL&>(a)   ==  static_cast<const RQ_XX_SL&>(b))  &&    true  );
};

bool operator!= (const RQ_NW_SL& a, const RQ_NW_SL& b)
{
    return !(a==b);
};



bool operator== (const RQ_MD_SL& a, const RQ_MD_SL& b)
{
    return ( (static_cast<const RQ_XX_SL&>(a)   ==  static_cast<const RQ_XX_SL&>(b))  &&    true  );
};

bool operator!= (const RQ_MD_SL& a, const RQ_MD_SL& b)
{
    return !(a==b);
};



bool operator== (const RQ_CC_SL& a, const RQ_CC_SL& b)
{
    return ( (static_cast<const RQ_XX_SL&>(a)   ==  static_cast<const RQ_XX_SL&>(b))  &&    true  );
};

bool operator!= (const RQ_CC_SL& a, const RQ_CC_SL& b)
{
    return !(a==b);
};



bool operator== (const CF_XX_SL& a, const CF_XX_SL& b)
{
    return ( (static_cast<const CF_XX&>(a)   ==  static_cast<const CF_XX&>(b))  &&           a.market_pos ==  b.market_pos  &&   true  );
};

bool operator!= (const CF_XX_SL& a, const CF_XX_SL& b)
{
    return !(a==b);
};



bool operator== (const CF_NW_SL& a, const CF_NW_SL& b)
{
    return ( (static_cast<const CF_XX_SL&>(a)   ==  static_cast<const CF_XX_SL&>(b))  &&    true  );
};

bool operator!= (const CF_NW_SL& a, const CF_NW_SL& b)
{
    return !(a==b);
};



bool operator== (const CF_MD_SL& a, const CF_MD_SL& b)
{
    return ( (static_cast<const CF_XX_SL&>(a)   ==  static_cast<const CF_XX_SL&>(b))  &&    true  );
};

bool operator!= (const CF_MD_SL& a, const CF_MD_SL& b)
{
    return !(a==b);
};



bool operator== (const CF_CC_SL& a, const CF_CC_SL& b)
{
    return ( (static_cast<const CF_XX_SL&>(a)   ==  static_cast<const CF_XX_SL&>(b))  &&    true  );
};

bool operator!= (const CF_CC_SL& a, const CF_CC_SL& b)
{
    return !(a==b);
};



bool operator== (const CF_TR_SL& a, const CF_TR_SL& b)
{
    return ( (static_cast<const CF_XX_SL&>(a)   ==  static_cast<const CF_XX_SL&>(b))  &&    true  );
};

bool operator!= (const CF_TR_SL& a, const CF_TR_SL& b)
{
    return !(a==b);
};



bool operator== (const RJ_XX_SL& a, const RJ_XX_SL& b)
{
    return ( (static_cast<const CF_XX_SL&>(a)   ==  static_cast<const CF_XX_SL&>(b))  &&           a.request_pos ==  b.request_pos  &&   true  );
};

bool operator!= (const RJ_XX_SL& a, const RJ_XX_SL& b)
{
    return !(a==b);
};



bool operator== (const RJ_NW_SL& a, const RJ_NW_SL& b)
{
    return ( (static_cast<const RJ_XX_SL&>(a)   ==  static_cast<const RJ_XX_SL&>(b))  &&    true  );
};

bool operator!= (const RJ_NW_SL& a, const RJ_NW_SL& b)
{
    return !(a==b);
};



bool operator== (const RJ_MD_SL& a, const RJ_MD_SL& b)
{
    return ( (static_cast<const RJ_XX_SL&>(a)   ==  static_cast<const RJ_XX_SL&>(b))  &&    true  );
};

bool operator!= (const RJ_MD_SL& a, const RJ_MD_SL& b)
{
    return !(a==b);
};



bool operator== (const RJ_CC_SL& a, const RJ_CC_SL& b)
{
    return ( (static_cast<const RJ_XX_SL&>(a)   ==  static_cast<const RJ_XX_SL&>(b))  &&    true  );
};

bool operator!= (const RJ_CC_SL& a, const RJ_CC_SL& b)
{
    return !(a==b);
};



bool operator== (const CF_ST_SL& a, const CF_ST_SL& b)
{
    return ( (static_cast<const CF_XX_SL&>(a)   ==  static_cast<const CF_XX_SL&>(b))  &&           a.gen_response_location ==  b.gen_response_location  &&   true  );
};

bool operator!= (const CF_ST_SL& a, const CF_ST_SL& b)
{
    return !(a==b);
};




void  copy (sub_position_sl& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("spr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field stop_price on message sub_position_sl::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.stop_price, it->second);
                        //c.stop_price = it->second;
//   field_type

                    it = mv.find("pri");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field price on message sub_position_sl::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.price, it->second);
                        //c.price = it->second;
//   field_type

                    it = mv.find("qt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field quantity on message sub_position_sl::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.quantity, it->second);
                        //c.quantity = it->second;
//   field_type

                    it = mv.find("clr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field cli_ref on message sub_position_sl::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.cli_ref, it->second);
                        //c.cli_ref = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_position_sl& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.stop_price, std::string("spr"));
//  field_type
        __internal_add2map(map, a.price, std::string("pri"));
//  field_type
        __internal_add2map(map, a.quantity, std::string("qt"));
//  field_type
        __internal_add2map(map, a.cli_ref, std::string("clr"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_position_sl>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (RQ_XX_SL& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RQ_XX&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rqp");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_pos on message RQ_XX_SL::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_pos, it->second);
                        //__internal_qpid_fill(c.request_pos, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const RQ_XX_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_XX&>(a));

//  sub_msg_type
        __internal_add2map(map, a.request_pos, std::string("rqp"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_XX_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (RQ_NW_SL& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RQ_XX_SL&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const RQ_NW_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_XX_SL&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_NW_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (RQ_MD_SL& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RQ_XX_SL&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const RQ_MD_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_XX_SL&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_MD_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (RQ_CC_SL& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RQ_XX_SL&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const RQ_CC_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_XX_SL&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_CC_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (CF_XX_SL& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("mkp");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field market_pos on message CF_XX_SL::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.market_pos, it->second);
                        //__internal_qpid_fill(c.market_pos, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const CF_XX_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const CF_XX&>(a));

//  sub_msg_type
        __internal_add2map(map, a.market_pos, std::string("mkp"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_XX_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (CF_NW_SL& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX_SL&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const CF_NW_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const CF_XX_SL&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_NW_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (CF_MD_SL& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX_SL&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const CF_MD_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const CF_XX_SL&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_MD_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (CF_CC_SL& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX_SL&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const CF_CC_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const CF_XX_SL&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_CC_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (CF_TR_SL& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX_SL&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const CF_TR_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const CF_XX_SL&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_TR_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (RJ_XX_SL& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX_SL&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rqp");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_pos on message RJ_XX_SL::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_pos, it->second);
                        //__internal_qpid_fill(c.request_pos, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const RJ_XX_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const CF_XX_SL&>(a));

//  sub_msg_type
        __internal_add2map(map, a.request_pos, std::string("rqp"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_XX_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (RJ_NW_SL& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RJ_XX_SL&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const RJ_NW_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RJ_XX_SL&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_NW_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (RJ_MD_SL& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RJ_XX_SL&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const RJ_MD_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RJ_XX_SL&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_MD_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (RJ_CC_SL& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<RJ_XX_SL&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const RJ_CC_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RJ_XX_SL&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RJ_CC_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (CF_ST_SL& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX_SL&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("grl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field gen_response_location on message CF_ST_SL::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.gen_response_location, it->second);
                        //__internal_qpid_fill(c.gen_response_location, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const CF_ST_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const CF_XX_SL&>(a));

//  sub_msg_type
        __internal_add2map(map, a.gen_response_location, std::string("grl"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_ST_SL>& a, const std::string& field)
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
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)

qpid::types::Variant::Map   RQ_NW_SL::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_XX_SL&>(*this));




    
    return content;
};




qpid::types::Variant::Map   RQ_MD_SL::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_XX_SL&>(*this));




    
    return content;
};




qpid::types::Variant::Map   RQ_CC_SL::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_XX_SL&>(*this));




    
    return content;
};




qpid::types::Variant::Map   CF_NW_SL::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const CF_XX_SL&>(*this));




    
    return content;
};




qpid::types::Variant::Map   CF_MD_SL::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const CF_XX_SL&>(*this));




    
    return content;
};




qpid::types::Variant::Map   CF_CC_SL::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const CF_XX_SL&>(*this));




    
    return content;
};




qpid::types::Variant::Map   CF_TR_SL::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const CF_XX_SL&>(*this));




    
    return content;
};




qpid::types::Variant::Map   RJ_NW_SL::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RJ_XX_SL&>(*this));




    
    return content;
};




qpid::types::Variant::Map   RJ_MD_SL::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RJ_XX_SL&>(*this));




    
    return content;
};




qpid::types::Variant::Map   RJ_CC_SL::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RJ_XX_SL&>(*this));




    
    return content;
};




qpid::types::Variant::Map   CF_ST_SL::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const CF_XX_SL&>(*this));

//  sub_msg_type
//        content["grl"] =  qpidmsg_coded_as_qpid_Map(this->gen_response_location);
        __internal_add2map(content, this->gen_response_location, std::string("grl"));



    
    return content;
};




    sub_position_sl  __internal_get_default(sub_position_sl*)
    {
        return sub_position_sl(
//   field_type
   __internal_get_default ((mtk::FixedNumber*)0),
//   field_type
   __internal_get_default ((mtk::FixedNumber*)0),
//   field_type
   __internal_get_default ((mtk::FixedNumber*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    RQ_XX_SL  __internal_get_default(RQ_XX_SL*)
    {
        return RQ_XX_SL(
__internal_get_default((RQ_XX*)0), //   sub_msg_type
   __internal_get_default((sub_position_sl*)0)
            );
    }
    
    RQ_NW_SL  __internal_get_default(RQ_NW_SL*)
    {
        return RQ_NW_SL(
__internal_get_default((RQ_XX_SL*)0)
            );
    }
    
    RQ_MD_SL  __internal_get_default(RQ_MD_SL*)
    {
        return RQ_MD_SL(
__internal_get_default((RQ_XX_SL*)0)
            );
    }
    
    RQ_CC_SL  __internal_get_default(RQ_CC_SL*)
    {
        return RQ_CC_SL(
__internal_get_default((RQ_XX_SL*)0)
            );
    }
    
    CF_XX_SL  __internal_get_default(CF_XX_SL*)
    {
        return CF_XX_SL(
__internal_get_default((CF_XX*)0), //   sub_msg_type
   __internal_get_default((sub_position_sl*)0)
            );
    }
    
    CF_NW_SL  __internal_get_default(CF_NW_SL*)
    {
        return CF_NW_SL(
__internal_get_default((CF_XX_SL*)0)
            );
    }
    
    CF_MD_SL  __internal_get_default(CF_MD_SL*)
    {
        return CF_MD_SL(
__internal_get_default((CF_XX_SL*)0)
            );
    }
    
    CF_CC_SL  __internal_get_default(CF_CC_SL*)
    {
        return CF_CC_SL(
__internal_get_default((CF_XX_SL*)0)
            );
    }
    
    CF_TR_SL  __internal_get_default(CF_TR_SL*)
    {
        return CF_TR_SL(
__internal_get_default((CF_XX_SL*)0)
            );
    }
    
    RJ_XX_SL  __internal_get_default(RJ_XX_SL*)
    {
        return RJ_XX_SL(
__internal_get_default((CF_XX_SL*)0), //   sub_msg_type
   __internal_get_default((sub_position_sl*)0)
            );
    }
    
    RJ_NW_SL  __internal_get_default(RJ_NW_SL*)
    {
        return RJ_NW_SL(
__internal_get_default((RJ_XX_SL*)0)
            );
    }
    
    RJ_MD_SL  __internal_get_default(RJ_MD_SL*)
    {
        return RJ_MD_SL(
__internal_get_default((RJ_XX_SL*)0)
            );
    }
    
    RJ_CC_SL  __internal_get_default(RJ_CC_SL*)
    {
        return RJ_CC_SL(
__internal_get_default((RJ_XX_SL*)0)
            );
    }
    
    CF_ST_SL  __internal_get_default(CF_ST_SL*)
    {
        return CF_ST_SL(
__internal_get_default((CF_XX_SL*)0), //   sub_msg_type
   __internal_get_default((mtk::msg::sub_gen_response_location*)0)
            );
    }
    
sub_position_sl::sub_position_sl (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   stop_price(__internal_get_default((mtk::FixedNumber*)0)),
//   field_type
   price(__internal_get_default((mtk::FixedNumber*)0)),
//   field_type
   quantity(__internal_get_default((mtk::FixedNumber*)0)),
//   field_type
   cli_ref(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

RQ_XX_SL::RQ_XX_SL (const qpid::types::Variant::Map&  mv)
    :  RQ_XX(mv), //   sub_msg_type
   request_pos(__internal_get_default((sub_position_sl*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

RQ_NW_SL::RQ_NW_SL (const qpid::types::Variant::Map&  mv)
    :  RQ_XX_SL(mv) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

RQ_MD_SL::RQ_MD_SL (const qpid::types::Variant::Map&  mv)
    :  RQ_XX_SL(mv) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

RQ_CC_SL::RQ_CC_SL (const qpid::types::Variant::Map&  mv)
    :  RQ_XX_SL(mv) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

CF_XX_SL::CF_XX_SL (const qpid::types::Variant::Map&  mv)
    :  CF_XX(mv), //   sub_msg_type
   market_pos(__internal_get_default((sub_position_sl*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

CF_NW_SL::CF_NW_SL (const qpid::types::Variant::Map&  mv)
    :  CF_XX_SL(mv) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

CF_MD_SL::CF_MD_SL (const qpid::types::Variant::Map&  mv)
    :  CF_XX_SL(mv) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

CF_CC_SL::CF_CC_SL (const qpid::types::Variant::Map&  mv)
    :  CF_XX_SL(mv) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

CF_TR_SL::CF_TR_SL (const qpid::types::Variant::Map&  mv)
    :  CF_XX_SL(mv) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

RJ_XX_SL::RJ_XX_SL (const qpid::types::Variant::Map&  mv)
    :  CF_XX_SL(mv), //   sub_msg_type
   request_pos(__internal_get_default((sub_position_sl*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

RJ_NW_SL::RJ_NW_SL (const qpid::types::Variant::Map&  mv)
    :  RJ_XX_SL(mv) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

RJ_MD_SL::RJ_MD_SL (const qpid::types::Variant::Map&  mv)
    :  RJ_XX_SL(mv) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

RJ_CC_SL::RJ_CC_SL (const qpid::types::Variant::Map&  mv)
    :  RJ_XX_SL(mv) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

CF_ST_SL::CF_ST_SL (const qpid::types::Variant::Map&  mv)
    :  CF_XX_SL(mv), //   sub_msg_type
   gen_response_location(__internal_get_default((mtk::msg::sub_gen_response_location*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }
mtk::t_qpid_filter  RQ_NW_SL::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name,const std::string& invariant_product_code_product)
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << "." << invariant_product_code_product << ".TRD"));
    }
    mtk::t_qpid_filter  RQ_NW_SL::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << "." << this->invariant.product_code.product << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  RQ_NW_SL::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  RQ_NW_SL::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  RQ_MD_SL::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name,const std::string& invariant_product_code_product)
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << "." << invariant_product_code_product << ".TRD"));
    }
    mtk::t_qpid_filter  RQ_MD_SL::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << "." << this->invariant.product_code.product << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  RQ_MD_SL::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  RQ_MD_SL::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  RQ_CC_SL::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name,const std::string& invariant_product_code_product)
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << "." << invariant_product_code_product << ".TRD"));
    }
    mtk::t_qpid_filter  RQ_CC_SL::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << "." << this->invariant.product_code.product << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  RQ_CC_SL::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  RQ_CC_SL::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  CF_NW_SL::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << ".TRD"));
    }
    mtk::t_qpid_filter  CF_NW_SL::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  CF_NW_SL::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  CF_NW_SL::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  CF_MD_SL::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << ".TRD"));
    }
    mtk::t_qpid_filter  CF_MD_SL::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  CF_MD_SL::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  CF_MD_SL::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  CF_CC_SL::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << ".TRD"));
    }
    mtk::t_qpid_filter  CF_CC_SL::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  CF_CC_SL::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  CF_CC_SL::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  CF_TR_SL::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << ".TRD"));
    }
    mtk::t_qpid_filter  CF_TR_SL::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  CF_TR_SL::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  CF_TR_SL::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  RJ_NW_SL::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << ".TRD"));
    }
    mtk::t_qpid_filter  RJ_NW_SL::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  RJ_NW_SL::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  RJ_NW_SL::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  RJ_MD_SL::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << ".TRD"));
    }
    mtk::t_qpid_filter  RJ_MD_SL::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  RJ_MD_SL::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  RJ_MD_SL::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  RJ_CC_SL::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << ".TRD"));
    }
    mtk::t_qpid_filter  RJ_CC_SL::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  RJ_CC_SL::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  RJ_CC_SL::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  CF_ST_SL::get_in_subject (const std::string& gen_response_location_broker_code,const std::string& gen_response_location_session_id)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << gen_response_location_broker_code << "." << gen_response_location_session_id << ".STATUS_CF"));
    }
    mtk::t_qpid_filter  CF_ST_SL::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->gen_response_location.broker_code << "." << this->gen_response_location.session_id << ".STATUS_CF"));
    }
    /*static*/  mtk::t_qpid_address  CF_ST_SL::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  CF_ST_SL::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {

