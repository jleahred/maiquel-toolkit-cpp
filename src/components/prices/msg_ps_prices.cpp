
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_ps_prices.h"

namespace mtk { 
namespace prices { 
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


ps_req_product_info::ps_req_product_info ( const req_product_info&  parent,   const std::string&  _from)
    :  req_product_info(parent),   from(_from) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string ps_req_product_info::check_recomended(void) const
{
    std::string result;

    return result;
}

void ps_req_product_info::before_send(void) const
{

}




ps_pub_prod_info_mtk_ready::ps_pub_prod_info_mtk_ready (   const std::string&  _market)
    :     market(_market) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string ps_pub_prod_info_mtk_ready::check_recomended(void) const
{
    std::string result;

    return result;
}

void ps_pub_prod_info_mtk_ready::before_send(void) const
{

}




ps_req_init_prod_info::ps_req_init_prod_info (   const std::string&  _market,   const mtk::msg::sub_process_info&  _process_info)
    :     market(_market),   process_info(_process_info) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string ps_req_init_prod_info::check_recomended(void) const
{
    std::string result;

    return result;
}

void ps_req_init_prod_info::before_send(void) const
{

}




ps_conf_full_product_info_init::ps_conf_full_product_info_init (   const std::string&  _market,   const mtk::msg::sub_process_info&  _to_process_info)
    :     market(_market),   to_process_info(_to_process_info) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string ps_conf_full_product_info_init::check_recomended(void) const
{
    std::string result;

    return result;
}

void ps_conf_full_product_info_init::before_send(void) const
{

}




ps_conf_full_product_info::ps_conf_full_product_info (   const sub_full_product_info&  _full_prod_info,   const mtk::msg::sub_process_info&  _to_process_info,   const int&  _seq_number)
    :     full_prod_info(_full_prod_info),   to_process_info(_to_process_info),   seq_number(_seq_number) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string ps_conf_full_product_info::check_recomended(void) const
{
    std::string result;

    return result;
}

void ps_conf_full_product_info::before_send(void) const
{

}




ps_pub_prod_info_mtk_ready__from_publisher::ps_pub_prod_info_mtk_ready__from_publisher ( const ps_pub_prod_info_mtk_ready&  parent)
    :  ps_pub_prod_info_mtk_ready(parent) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string ps_pub_prod_info_mtk_ready__from_publisher::check_recomended(void) const
{
    std::string result;

    return result;
}

void ps_pub_prod_info_mtk_ready__from_publisher::before_send(void) const
{

}




ps_req_init_prod_info__to_publisher::ps_req_init_prod_info__to_publisher ( const ps_req_init_prod_info&  parent)
    :  ps_req_init_prod_info(parent) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string ps_req_init_prod_info__to_publisher::check_recomended(void) const
{
    std::string result;

    return result;
}

void ps_req_init_prod_info__to_publisher::before_send(void) const
{

}




ps_conf_full_product_info_init__from_publisher::ps_conf_full_product_info_init__from_publisher ( const ps_conf_full_product_info_init&  parent)
    :  ps_conf_full_product_info_init(parent) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string ps_conf_full_product_info_init__from_publisher::check_recomended(void) const
{
    std::string result;

    return result;
}

void ps_conf_full_product_info_init__from_publisher::before_send(void) const
{

}




ps_conf_full_product_info__from_publisher::ps_conf_full_product_info__from_publisher ( const ps_conf_full_product_info&  parent)
    :  ps_conf_full_product_info(parent) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string ps_conf_full_product_info__from_publisher::check_recomended(void) const
{
    std::string result;

    return result;
}

void ps_conf_full_product_info__from_publisher::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const ps_req_product_info & c)
{
    o << "{ "
    << "("  <<  static_cast<const req_product_info&>(c)  << ")" 
        << "from:"<<   c.from << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const ps_req_product_info & c)
{
    o << YAML::BeginMap
    << YAML::Key << "req_product_info" <<  YAML::Value << static_cast<const req_product_info&>(c)  
        << YAML::Key << "from"  << YAML::Value <<   c.from
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, ps_req_product_info & c)
{

    node["req_product_info"]   >>   static_cast<req_product_info&>(c)  ;

        node["from"]  >> c.from;


};


std::ostream& operator<< (std::ostream& o, const ps_pub_prod_info_mtk_ready & c)
{
    o << "{ "

        << "market:"<<   c.market << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const ps_pub_prod_info_mtk_ready & c)
{
    o << YAML::BeginMap

        << YAML::Key << "market"  << YAML::Value <<   c.market
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, ps_pub_prod_info_mtk_ready & c)
{


        node["market"]  >> c.market;


};


std::ostream& operator<< (std::ostream& o, const ps_req_init_prod_info & c)
{
    o << "{ "

        << "market:"<<   c.market << "  "        << "process_info:"<< c.process_info<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const ps_req_init_prod_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "market"  << YAML::Value <<   c.market        << YAML::Key << "process_info"  << YAML::Value << c.process_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, ps_req_init_prod_info & c)
{


        node["market"]  >> c.market;
        node["process_info"]  >> c.process_info;


};


std::ostream& operator<< (std::ostream& o, const ps_conf_full_product_info_init & c)
{
    o << "{ "

        << "market:"<<   c.market << "  "        << "to_process_info:"<< c.to_process_info<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const ps_conf_full_product_info_init & c)
{
    o << YAML::BeginMap

        << YAML::Key << "market"  << YAML::Value <<   c.market        << YAML::Key << "to_process_info"  << YAML::Value << c.to_process_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, ps_conf_full_product_info_init & c)
{


        node["market"]  >> c.market;
        node["to_process_info"]  >> c.to_process_info;


};


std::ostream& operator<< (std::ostream& o, const ps_conf_full_product_info & c)
{
    o << "{ "

        << "full_prod_info:"<< c.full_prod_info<<"  "        << "to_process_info:"<< c.to_process_info<<"  "        << "seq_number:"<< c.seq_number<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const ps_conf_full_product_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "full_prod_info"  << YAML::Value << c.full_prod_info        << YAML::Key << "to_process_info"  << YAML::Value << c.to_process_info        << YAML::Key << "seq_number"  << YAML::Value << c.seq_number
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, ps_conf_full_product_info & c)
{


        node["full_prod_info"]  >> c.full_prod_info;
        node["to_process_info"]  >> c.to_process_info;
        node["seq_number"]  >> c.seq_number;


};


std::ostream& operator<< (std::ostream& o, const ps_pub_prod_info_mtk_ready__from_publisher & c)
{
    o << "{ "
    << "("  <<  static_cast<const ps_pub_prod_info_mtk_ready&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const ps_pub_prod_info_mtk_ready__from_publisher & c)
{
    o << YAML::BeginMap
    << YAML::Key << "ps_pub_prod_info_mtk_ready" <<  YAML::Value << static_cast<const ps_pub_prod_info_mtk_ready&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, ps_pub_prod_info_mtk_ready__from_publisher & c)
{

    node["ps_pub_prod_info_mtk_ready"]   >>   static_cast<ps_pub_prod_info_mtk_ready&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const ps_req_init_prod_info__to_publisher & c)
{
    o << "{ "
    << "("  <<  static_cast<const ps_req_init_prod_info&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const ps_req_init_prod_info__to_publisher & c)
{
    o << YAML::BeginMap
    << YAML::Key << "ps_req_init_prod_info" <<  YAML::Value << static_cast<const ps_req_init_prod_info&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, ps_req_init_prod_info__to_publisher & c)
{

    node["ps_req_init_prod_info"]   >>   static_cast<ps_req_init_prod_info&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const ps_conf_full_product_info_init__from_publisher & c)
{
    o << "{ "
    << "("  <<  static_cast<const ps_conf_full_product_info_init&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const ps_conf_full_product_info_init__from_publisher & c)
{
    o << YAML::BeginMap
    << YAML::Key << "ps_conf_full_product_info_init" <<  YAML::Value << static_cast<const ps_conf_full_product_info_init&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, ps_conf_full_product_info_init__from_publisher & c)
{

    node["ps_conf_full_product_info_init"]   >>   static_cast<ps_conf_full_product_info_init&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const ps_conf_full_product_info__from_publisher & c)
{
    o << "{ "
    << "("  <<  static_cast<const ps_conf_full_product_info&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const ps_conf_full_product_info__from_publisher & c)
{
    o << YAML::BeginMap
    << YAML::Key << "ps_conf_full_product_info" <<  YAML::Value << static_cast<const ps_conf_full_product_info&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, ps_conf_full_product_info__from_publisher & c)
{

    node["ps_conf_full_product_info"]   >>   static_cast<ps_conf_full_product_info&>(c)  ;



};


bool operator== (const ps_req_product_info& a, const ps_req_product_info& b)
{
    return ( (static_cast<const req_product_info&>(a)   ==  static_cast<const req_product_info&>(b))  &&           a.from ==  b.from  &&   true  );
};

bool operator!= (const ps_req_product_info& a, const ps_req_product_info& b)
{
    return !(a==b);
};



bool operator== (const ps_pub_prod_info_mtk_ready& a, const ps_pub_prod_info_mtk_ready& b)
{
    return (          a.market ==  b.market  &&   true  );
};

bool operator!= (const ps_pub_prod_info_mtk_ready& a, const ps_pub_prod_info_mtk_ready& b)
{
    return !(a==b);
};



bool operator== (const ps_req_init_prod_info& a, const ps_req_init_prod_info& b)
{
    return (          a.market ==  b.market  &&          a.process_info ==  b.process_info  &&   true  );
};

bool operator!= (const ps_req_init_prod_info& a, const ps_req_init_prod_info& b)
{
    return !(a==b);
};



bool operator== (const ps_conf_full_product_info_init& a, const ps_conf_full_product_info_init& b)
{
    return (          a.market ==  b.market  &&          a.to_process_info ==  b.to_process_info  &&   true  );
};

bool operator!= (const ps_conf_full_product_info_init& a, const ps_conf_full_product_info_init& b)
{
    return !(a==b);
};



bool operator== (const ps_conf_full_product_info& a, const ps_conf_full_product_info& b)
{
    return (          a.full_prod_info ==  b.full_prod_info  &&          a.to_process_info ==  b.to_process_info  &&          a.seq_number ==  b.seq_number  &&   true  );
};

bool operator!= (const ps_conf_full_product_info& a, const ps_conf_full_product_info& b)
{
    return !(a==b);
};



bool operator== (const ps_pub_prod_info_mtk_ready__from_publisher& a, const ps_pub_prod_info_mtk_ready__from_publisher& b)
{
    return ( (static_cast<const ps_pub_prod_info_mtk_ready&>(a)   ==  static_cast<const ps_pub_prod_info_mtk_ready&>(b))  &&    true  );
};

bool operator!= (const ps_pub_prod_info_mtk_ready__from_publisher& a, const ps_pub_prod_info_mtk_ready__from_publisher& b)
{
    return !(a==b);
};



bool operator== (const ps_req_init_prod_info__to_publisher& a, const ps_req_init_prod_info__to_publisher& b)
{
    return ( (static_cast<const ps_req_init_prod_info&>(a)   ==  static_cast<const ps_req_init_prod_info&>(b))  &&    true  );
};

bool operator!= (const ps_req_init_prod_info__to_publisher& a, const ps_req_init_prod_info__to_publisher& b)
{
    return !(a==b);
};



bool operator== (const ps_conf_full_product_info_init__from_publisher& a, const ps_conf_full_product_info_init__from_publisher& b)
{
    return ( (static_cast<const ps_conf_full_product_info_init&>(a)   ==  static_cast<const ps_conf_full_product_info_init&>(b))  &&    true  );
};

bool operator!= (const ps_conf_full_product_info_init__from_publisher& a, const ps_conf_full_product_info_init__from_publisher& b)
{
    return !(a==b);
};



bool operator== (const ps_conf_full_product_info__from_publisher& a, const ps_conf_full_product_info__from_publisher& b)
{
    return ( (static_cast<const ps_conf_full_product_info&>(a)   ==  static_cast<const ps_conf_full_product_info&>(b))  &&    true  );
};

bool operator!= (const ps_conf_full_product_info__from_publisher& a, const ps_conf_full_product_info__from_publisher& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (ps_req_product_info& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (ps_req_product_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<req_product_info&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message ps_req_product_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const ps_req_product_info& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const req_product_info&>(a));

//  field_type
        __internal_add2map(map, a.from, std::string("from"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_req_product_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (ps_pub_prod_info_mtk_ready& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (ps_pub_prod_info_mtk_ready& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("mk");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field market on message ps_pub_prod_info_mtk_ready::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.market, it->second);
                        //c.market = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const ps_pub_prod_info_mtk_ready& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.market, std::string("mk"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_pub_prod_info_mtk_ready>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (ps_req_init_prod_info& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (ps_req_init_prod_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("mk");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field market on message ps_req_init_prod_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.market, it->second);
                        //c.market = it->second;
//   sub_msg_type

                    it = mv.find("pi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field process_info on message ps_req_init_prod_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_info, it->second);
                        //__internal_qpid_fill(c.process_info, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const ps_req_init_prod_info& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.market, std::string("mk"));
//  sub_msg_type
        __internal_add2map(map, a.process_info, std::string("pi"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_req_init_prod_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (ps_conf_full_product_info_init& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (ps_conf_full_product_info_init& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("mk");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field market on message ps_conf_full_product_info_init::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.market, it->second);
                        //c.market = it->second;
//   sub_msg_type

                    it = mv.find("tpi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field to_process_info on message ps_conf_full_product_info_init::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.to_process_info, it->second);
                        //__internal_qpid_fill(c.to_process_info, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const ps_conf_full_product_info_init& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.market, std::string("mk"));
//  sub_msg_type
        __internal_add2map(map, a.to_process_info, std::string("tpi"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_conf_full_product_info_init>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (ps_conf_full_product_info& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (ps_conf_full_product_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("fpi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field full_prod_info on message ps_conf_full_product_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.full_prod_info, it->second);
                        //__internal_qpid_fill(c.full_prod_info, it->second.asMap());
//   sub_msg_type

                    it = mv.find("tpi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field to_process_info on message ps_conf_full_product_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.to_process_info, it->second);
                        //__internal_qpid_fill(c.to_process_info, it->second.asMap());
//   sub_msg_type

                    it = mv.find("sqn");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field seq_number on message ps_conf_full_product_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.seq_number, it->second);
                        //__internal_qpid_fill(c.seq_number, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const ps_conf_full_product_info& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.full_prod_info, std::string("fpi"));
//  sub_msg_type
        __internal_add2map(map, a.to_process_info, std::string("tpi"));
//  sub_msg_type
        __internal_add2map(map, a.seq_number, std::string("sqn"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_conf_full_product_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (ps_pub_prod_info_mtk_ready__from_publisher& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (ps_pub_prod_info_mtk_ready__from_publisher& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<ps_pub_prod_info_mtk_ready&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const ps_pub_prod_info_mtk_ready__from_publisher& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const ps_pub_prod_info_mtk_ready&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_pub_prod_info_mtk_ready__from_publisher>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (ps_req_init_prod_info__to_publisher& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (ps_req_init_prod_info__to_publisher& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<ps_req_init_prod_info&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const ps_req_init_prod_info__to_publisher& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const ps_req_init_prod_info&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_req_init_prod_info__to_publisher>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (ps_conf_full_product_info_init__from_publisher& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (ps_conf_full_product_info_init__from_publisher& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<ps_conf_full_product_info_init&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const ps_conf_full_product_info_init__from_publisher& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const ps_conf_full_product_info_init&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_conf_full_product_info_init__from_publisher>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (ps_conf_full_product_info__from_publisher& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (ps_conf_full_product_info__from_publisher& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<ps_conf_full_product_info&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const ps_conf_full_product_info__from_publisher& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const ps_conf_full_product_info&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<ps_conf_full_product_info__from_publisher>& a, const std::string& field)
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

qpid::messaging::Message ps_req_product_info::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const req_product_info&>(*this));

//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message ps_pub_prod_info_mtk_ready::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  field_type
//        content["mk"] = this->market;
        __internal_add2map(content, this->market, std::string("mk"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message ps_req_init_prod_info::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  field_type
//        content["mk"] = this->market;
        __internal_add2map(content, this->market, std::string("mk"));
//  sub_msg_type
//        content["pi"] =  qpidmsg_coded_as_qpid_Map(this->process_info);
        __internal_add2map(content, this->process_info, std::string("pi"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message ps_conf_full_product_info_init::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  field_type
//        content["mk"] = this->market;
        __internal_add2map(content, this->market, std::string("mk"));
//  sub_msg_type
//        content["tpi"] =  qpidmsg_coded_as_qpid_Map(this->to_process_info);
        __internal_add2map(content, this->to_process_info, std::string("tpi"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message ps_conf_full_product_info::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["fpi"] =  qpidmsg_coded_as_qpid_Map(this->full_prod_info);
        __internal_add2map(content, this->full_prod_info, std::string("fpi"));
//  sub_msg_type
//        content["tpi"] =  qpidmsg_coded_as_qpid_Map(this->to_process_info);
        __internal_add2map(content, this->to_process_info, std::string("tpi"));
//  sub_msg_type
//        content["sqn"] =  qpidmsg_coded_as_qpid_Map(this->seq_number);
        __internal_add2map(content, this->seq_number, std::string("sqn"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message ps_pub_prod_info_mtk_ready__from_publisher::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const ps_pub_prod_info_mtk_ready&>(*this));



    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message ps_req_init_prod_info__to_publisher::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const ps_req_init_prod_info&>(*this));



    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message ps_conf_full_product_info_init__from_publisher::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const ps_conf_full_product_info_init&>(*this));



    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message ps_conf_full_product_info__from_publisher::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const ps_conf_full_product_info&>(*this));



    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




    ps_req_product_info  __internal_get_default(ps_req_product_info*)
    {
        return ps_req_product_info(
__internal_get_default((req_product_info*)0), //   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    ps_pub_prod_info_mtk_ready  __internal_get_default(ps_pub_prod_info_mtk_ready*)
    {
        return ps_pub_prod_info_mtk_ready(
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    ps_req_init_prod_info  __internal_get_default(ps_req_init_prod_info*)
    {
        return ps_req_init_prod_info(
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_info*)0)
            );
    }
    
    ps_conf_full_product_info_init  __internal_get_default(ps_conf_full_product_info_init*)
    {
        return ps_conf_full_product_info_init(
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_info*)0)
            );
    }
    
    ps_conf_full_product_info  __internal_get_default(ps_conf_full_product_info*)
    {
        return ps_conf_full_product_info(
//   sub_msg_type
   __internal_get_default((sub_full_product_info*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_info*)0),
//   sub_msg_type
   __internal_get_default((int*)0)
            );
    }
    
    ps_pub_prod_info_mtk_ready__from_publisher  __internal_get_default(ps_pub_prod_info_mtk_ready__from_publisher*)
    {
        return ps_pub_prod_info_mtk_ready__from_publisher(
__internal_get_default((ps_pub_prod_info_mtk_ready*)0)
            );
    }
    
    ps_req_init_prod_info__to_publisher  __internal_get_default(ps_req_init_prod_info__to_publisher*)
    {
        return ps_req_init_prod_info__to_publisher(
__internal_get_default((ps_req_init_prod_info*)0)
            );
    }
    
    ps_conf_full_product_info_init__from_publisher  __internal_get_default(ps_conf_full_product_info_init__from_publisher*)
    {
        return ps_conf_full_product_info_init__from_publisher(
__internal_get_default((ps_conf_full_product_info_init*)0)
            );
    }
    
    ps_conf_full_product_info__from_publisher  __internal_get_default(ps_conf_full_product_info__from_publisher*)
    {
        return ps_conf_full_product_info__from_publisher(
__internal_get_default((ps_conf_full_product_info*)0)
            );
    }
    

ps_req_product_info::ps_req_product_info (const qpid::types::Variant::Map&  mv)
    :  req_product_info(mv), //   field_type
   from(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



ps_pub_prod_info_mtk_ready::ps_pub_prod_info_mtk_ready (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   market(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



ps_req_init_prod_info::ps_req_init_prod_info (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   market(__internal_get_default((std::string*)0)),
//   sub_msg_type
   process_info(__internal_get_default((mtk::msg::sub_process_info*)0)) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



ps_conf_full_product_info_init::ps_conf_full_product_info_init (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   market(__internal_get_default((std::string*)0)),
//   sub_msg_type
   to_process_info(__internal_get_default((mtk::msg::sub_process_info*)0)) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



ps_conf_full_product_info::ps_conf_full_product_info (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   full_prod_info(__internal_get_default((sub_full_product_info*)0)),
//   sub_msg_type
   to_process_info(__internal_get_default((mtk::msg::sub_process_info*)0)),
//   sub_msg_type
   seq_number(__internal_get_default((int*)0)) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



ps_pub_prod_info_mtk_ready__from_publisher::ps_pub_prod_info_mtk_ready__from_publisher (const qpid::types::Variant::Map&  mv)
    :  ps_pub_prod_info_mtk_ready(mv) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



ps_req_init_prod_info__to_publisher::ps_req_init_prod_info__to_publisher (const qpid::types::Variant::Map&  mv)
    :  ps_req_init_prod_info(mv) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



ps_conf_full_product_info_init__from_publisher::ps_conf_full_product_info_init__from_publisher (const qpid::types::Variant::Map&  mv)
    :  ps_conf_full_product_info_init(mv) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



ps_conf_full_product_info__from_publisher::ps_conf_full_product_info__from_publisher (const qpid::types::Variant::Map&  mv)
    :  ps_conf_full_product_info(mv) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }

mtk::t_qpid_filter  ps_req_product_info::get_in_subject (const std::string& product_code_market,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << product_code_market << ".REQ.PI." << from << ""));
    }
    mtk::t_qpid_filter  ps_req_product_info::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << this->product_code.market << ".REQ.PI." << this->from << ""));
    }
    /*static*/  mtk::t_qpid_address  ps_req_product_info::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  ps_req_product_info::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  ps_pub_prod_info_mtk_ready::get_in_subject (const std::string& market)
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << market << ".PS.START_INIT"));
    }
    mtk::t_qpid_filter  ps_pub_prod_info_mtk_ready::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << this->market << ".PS.START_INIT"));
    }
    /*static*/  mtk::t_qpid_address  ps_pub_prod_info_mtk_ready::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  ps_pub_prod_info_mtk_ready::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  ps_req_init_prod_info::get_in_subject (const std::string& market)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.PS." << market << ".RQINIT"));
    }
    mtk::t_qpid_filter  ps_req_init_prod_info::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.PS." << this->market << ".RQINIT"));
    }
    /*static*/  mtk::t_qpid_address  ps_req_init_prod_info::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  ps_req_init_prod_info::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  ps_conf_full_product_info_init::get_in_subject (const std::string& market,const std::string& to_process_info_process_name,const std::string& to_process_info_process_uuid)
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << market << ".PS.START_INIT." << to_process_info_process_name << "." << to_process_info_process_uuid << ".CONFFULLPI"));
    }
    mtk::t_qpid_filter  ps_conf_full_product_info_init::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << this->market << ".PS.START_INIT." << this->to_process_info.process_name << "." << this->to_process_info.process_uuid << ".CONFFULLPI"));
    }
    /*static*/  mtk::t_qpid_address  ps_conf_full_product_info_init::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  ps_conf_full_product_info_init::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  ps_conf_full_product_info::get_in_subject (const std::string& full_prod_info_product_code_market,const std::string& to_process_info_process_name,const std::string& to_process_info_process_uuid)
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << full_prod_info_product_code_market << ".PS.FPI." << to_process_info_process_name << "." << to_process_info_process_uuid << ".CONFPI"));
    }
    mtk::t_qpid_filter  ps_conf_full_product_info::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << this->full_prod_info.product_code.market << ".PS.FPI." << this->to_process_info.process_name << "." << this->to_process_info.process_uuid << ".CONFPI"));
    }
    /*static*/  mtk::t_qpid_address  ps_conf_full_product_info::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  ps_conf_full_product_info::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  ps_pub_prod_info_mtk_ready__from_publisher::get_in_subject (const std::string& market)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.PS." << market << ".START_INIT.PUBLISHER"));
    }
    mtk::t_qpid_filter  ps_pub_prod_info_mtk_ready__from_publisher::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.PS." << this->market << ".START_INIT.PUBLISHER"));
    }
    /*static*/  mtk::t_qpid_address  ps_pub_prod_info_mtk_ready__from_publisher::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  ps_pub_prod_info_mtk_ready__from_publisher::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  ps_req_init_prod_info__to_publisher::get_in_subject (const std::string& market)
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << market << ".PS.RQINIT.PUBLISHER"));
    }
    mtk::t_qpid_filter  ps_req_init_prod_info__to_publisher::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << this->market << ".PS.RQINIT.PUBLISHER"));
    }
    /*static*/  mtk::t_qpid_address  ps_req_init_prod_info__to_publisher::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  ps_req_init_prod_info__to_publisher::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_filter  ps_conf_full_product_info_init__from_publisher::get_in_subject (const std::string& market,const std::string& to_process_info_process_name,const std::string& to_process_info_process_uuid)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.PS." << market << "." << to_process_info_process_name << "." << to_process_info_process_uuid << ".START_INIT.PUBLISHER"));
    }
    mtk::t_qpid_filter  ps_conf_full_product_info_init__from_publisher::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.PS." << this->market << "." << this->to_process_info.process_name << "." << this->to_process_info.process_uuid << ".START_INIT.PUBLISHER"));
    }
    /*static*/  mtk::t_qpid_address  ps_conf_full_product_info_init__from_publisher::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  ps_conf_full_product_info_init__from_publisher::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  ps_conf_full_product_info__from_publisher::get_in_subject (const std::string& full_prod_info_product_code_market,const std::string& to_process_info_process_name,const std::string& to_process_info_process_uuid)
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << full_prod_info_product_code_market << ".PS.FPI." << to_process_info_process_name << "." << to_process_info_process_uuid << ".CONFFPI_FMK"));
    }
    mtk::t_qpid_filter  ps_conf_full_product_info__from_publisher::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << this->full_prod_info.product_code.market << ".PS.FPI." << this->to_process_info.process_name << "." << this->to_process_info.process_uuid << ".CONFFPI_FMK"));
    }
    /*static*/  mtk::t_qpid_address  ps_conf_full_product_info__from_publisher::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  ps_conf_full_product_info__from_publisher::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    

};   //namespace mtk {
};   //namespace prices {
};   //namespace msg {


