
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_prices.h"

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


sub_price_level::sub_price_level (   const mtk::FixedNumber&  _price,   const mtk::FixedNumber&  _quantity)
    :     price(_price),   quantity(_quantity) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_price_level::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_price_level::before_send(void) const
{

}




sub_price_deph5::sub_price_deph5 (   const sub_price_level&  _level0,   const sub_price_level&  _level1,   const sub_price_level&  _level2,   const sub_price_level&  _level3,   const sub_price_level&  _level4)
    :     level0(_level0),   level1(_level1),   level2(_level2),   level3(_level3),   level4(_level4) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_price_deph5::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_price_deph5::before_send(void) const
{

}




sub_best_prices::sub_best_prices (   const sub_price_deph5&  _bids,   const sub_price_deph5&  _asks)
    :     bids(_bids),   asks(_asks) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_best_prices::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_best_prices::before_send(void) const
{

}




pub_best_prices::pub_best_prices (   const mtk::msg::sub_product_code&  _product_code,   const sub_best_prices&  _best_prices,   const mtk::msg::sub_control_fluct&  _orig_control_fluct)
    :     product_code(_product_code),   best_prices(_best_prices),   orig_control_fluct(_orig_control_fluct) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string pub_best_prices::check_recomended(void) const
{
    std::string result;

    return result;
}

void pub_best_prices::before_send(void) const
{

}




pub_new_products::pub_new_products (   const std::string&  _market)
    :     market(_market) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string pub_new_products::check_recomended(void) const
{
    std::string result;

    return result;
}

void pub_new_products::before_send(void) const
{

}




sub_full_product_info::sub_full_product_info (   const mtk::msg::sub_product_code&  _product_code,   const sub_best_prices&  _best_prices)
    :     product_code(_product_code),   best_prices(_best_prices) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_full_product_info::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_full_product_info::before_send(void) const
{

}




sub_full_product_info_optionals::sub_full_product_info_optionals (   const bool&  _initialized,   const mtk::msg::sub_product_code&  _product_code,   const mtk::nullable<sub_best_prices>&  _best_prices)
    :     initialized(_initialized),   product_code(_product_code),   best_prices(_best_prices) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_full_product_info_optionals::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_full_product_info_optionals::before_send(void) const
{

}




req_product_info::req_product_info (   const mtk::msg::sub_request_info&  _request_info,   const mtk::msg::sub_product_code&  _product_code)
    :     request_info(_request_info),   product_code(_product_code) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string req_product_info::check_recomended(void) const
{
    std::string result;

    return result;
}

void req_product_info::before_send(void) const
{

}




res_product_info::res_product_info (   const mtk::msg::sub_r_response&  _response_info,   const IC_response&  _response)
    :     response_info(_response_info),   response(_response) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string res_product_info::check_recomended(void) const
{
    std::string result;

    return result;
}

void res_product_info::before_send(void) const
{

}




res_product_info::IC_response::IC_response (   const sub_full_product_info&  _full_product_info)
    :     full_product_info(_full_product_info) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string res_product_info::IC_response::check_recomended(void) const
{
    std::string result;

    return result;
}

void res_product_info::IC_response::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const sub_price_level & c)
{
    o << "{ "

        << "price:"<<   c.price << "  "        << "quantity:"<<   c.quantity << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_price_level & c)
{
    o << YAML::BeginMap

        << YAML::Key << "price"  << YAML::Value <<   c.price        << YAML::Key << "quantity"  << YAML::Value <<   c.quantity
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_price_level & c)
{


        node["price"]  >> c.price;
        node["quantity"]  >> c.quantity;


};


std::ostream& operator<< (std::ostream& o, const sub_price_deph5 & c)
{
    o << "{ "

        << "level0:"<< c.level0<<"  "        << "level1:"<< c.level1<<"  "        << "level2:"<< c.level2<<"  "        << "level3:"<< c.level3<<"  "        << "level4:"<< c.level4<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_price_deph5 & c)
{
    o << YAML::BeginMap

        << YAML::Key << "level0"  << YAML::Value << c.level0        << YAML::Key << "level1"  << YAML::Value << c.level1        << YAML::Key << "level2"  << YAML::Value << c.level2        << YAML::Key << "level3"  << YAML::Value << c.level3        << YAML::Key << "level4"  << YAML::Value << c.level4
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_price_deph5 & c)
{


        node["level0"]  >> c.level0;
        node["level1"]  >> c.level1;
        node["level2"]  >> c.level2;
        node["level3"]  >> c.level3;
        node["level4"]  >> c.level4;


};


std::ostream& operator<< (std::ostream& o, const sub_best_prices & c)
{
    o << "{ "

        << "bids:"<< c.bids<<"  "        << "asks:"<< c.asks<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_best_prices & c)
{
    o << YAML::BeginMap

        << YAML::Key << "bids"  << YAML::Value << c.bids        << YAML::Key << "asks"  << YAML::Value << c.asks
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_best_prices & c)
{


        node["bids"]  >> c.bids;
        node["asks"]  >> c.asks;


};


std::ostream& operator<< (std::ostream& o, const pub_best_prices & c)
{
    o << "{ "

        << "product_code:"<< c.product_code<<"  "        << "best_prices:"<< c.best_prices<<"  "        << "orig_control_fluct:"<< c.orig_control_fluct<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const pub_best_prices & c)
{
    o << YAML::BeginMap

        << YAML::Key << "product_code"  << YAML::Value << c.product_code        << YAML::Key << "best_prices"  << YAML::Value << c.best_prices        << YAML::Key << "orig_control_fluct"  << YAML::Value << c.orig_control_fluct
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, pub_best_prices & c)
{


        node["product_code"]  >> c.product_code;
        node["best_prices"]  >> c.best_prices;
        node["orig_control_fluct"]  >> c.orig_control_fluct;


};


std::ostream& operator<< (std::ostream& o, const pub_new_products & c)
{
    o << "{ "

        << "market:"<<   c.market << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const pub_new_products & c)
{
    o << YAML::BeginMap

        << YAML::Key << "market"  << YAML::Value <<   c.market
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, pub_new_products & c)
{


        node["market"]  >> c.market;


};


std::ostream& operator<< (std::ostream& o, const sub_full_product_info & c)
{
    o << "{ "

        << "product_code:"<< c.product_code<<"  "        << "best_prices:"<< c.best_prices<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_full_product_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "product_code"  << YAML::Value << c.product_code        << YAML::Key << "best_prices"  << YAML::Value << c.best_prices
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_full_product_info & c)
{


        node["product_code"]  >> c.product_code;
        node["best_prices"]  >> c.best_prices;


};


std::ostream& operator<< (std::ostream& o, const sub_full_product_info_optionals & c)
{
    o << "{ "

        << "initialized:"<< c.initialized<<"  "        << "product_code:"<< c.product_code<<"  "        << "best_prices:"<< c.best_prices<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_full_product_info_optionals & c)
{
    o << YAML::BeginMap

        << YAML::Key << "initialized"  << YAML::Value << c.initialized        << YAML::Key << "product_code"  << YAML::Value << c.product_code        << YAML::Key << "best_prices"  << YAML::Value << c.best_prices
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_full_product_info_optionals & c)
{


        node["initialized"]  >> c.initialized;
        node["product_code"]  >> c.product_code;
        node["best_prices"]  >> c.best_prices;


};


std::ostream& operator<< (std::ostream& o, const req_product_info & c)
{
    o << "{ "

        << "request_info:"<< c.request_info<<"  "        << "product_code:"<< c.product_code<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const req_product_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "request_info"  << YAML::Value << c.request_info        << YAML::Key << "product_code"  << YAML::Value << c.product_code
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, req_product_info & c)
{


        node["request_info"]  >> c.request_info;
        node["product_code"]  >> c.product_code;


};


std::ostream& operator<< (std::ostream& o, const res_product_info::IC_response & c)
{
    o << "{ "

        << "full_product_info:"<< c.full_product_info<<"  "
        << " }";
    return o;
};


std::ostream& operator<< (std::ostream& o, const res_product_info & c)
{
    o << "{ "

        << "response_info:"<< c.response_info<<"  "        << "response:"<< c.response<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const res_product_info::IC_response & c)
{
    o << YAML::BeginMap

        << YAML::Key << "full_product_info"  << YAML::Value << c.full_product_info
        << YAML::EndMap;
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const res_product_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "response_info"  << YAML::Value << c.response_info        << YAML::Key << "response"   << YAML::Value << c.response
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, res_product_info::IC_response & c)
{


        node["full_product_info"]  >> c.full_product_info;


};



void  operator >> (const YAML::Node& node, res_product_info & c)
{


        node["response_info"]  >> c.response_info;
            node["response"] >>  c.response;


};


bool operator== (const sub_price_level& a, const sub_price_level& b)
{
    return (          a.price ==  b.price  &&          a.quantity ==  b.quantity  &&   true  );
};

bool operator!= (const sub_price_level& a, const sub_price_level& b)
{
    return !(a==b);
};



bool operator== (const sub_price_deph5& a, const sub_price_deph5& b)
{
    return (          a.level0 ==  b.level0  &&          a.level1 ==  b.level1  &&          a.level2 ==  b.level2  &&          a.level3 ==  b.level3  &&          a.level4 ==  b.level4  &&   true  );
};

bool operator!= (const sub_price_deph5& a, const sub_price_deph5& b)
{
    return !(a==b);
};



bool operator== (const sub_best_prices& a, const sub_best_prices& b)
{
    return (          a.bids ==  b.bids  &&          a.asks ==  b.asks  &&   true  );
};

bool operator!= (const sub_best_prices& a, const sub_best_prices& b)
{
    return !(a==b);
};



bool operator== (const pub_best_prices& a, const pub_best_prices& b)
{
    return (          a.product_code ==  b.product_code  &&          a.best_prices ==  b.best_prices  &&          a.orig_control_fluct ==  b.orig_control_fluct  &&   true  );
};

bool operator!= (const pub_best_prices& a, const pub_best_prices& b)
{
    return !(a==b);
};



bool operator== (const pub_new_products& a, const pub_new_products& b)
{
    return (          a.market ==  b.market  &&   true  );
};

bool operator!= (const pub_new_products& a, const pub_new_products& b)
{
    return !(a==b);
};



bool operator== (const sub_full_product_info& a, const sub_full_product_info& b)
{
    return (          a.product_code ==  b.product_code  &&          a.best_prices ==  b.best_prices  &&   true  );
};

bool operator!= (const sub_full_product_info& a, const sub_full_product_info& b)
{
    return !(a==b);
};



bool operator== (const sub_full_product_info_optionals& a, const sub_full_product_info_optionals& b)
{
    return (          a.initialized ==  b.initialized  &&          a.product_code ==  b.product_code  &&          a.best_prices ==  b.best_prices  &&   true  );
};

bool operator!= (const sub_full_product_info_optionals& a, const sub_full_product_info_optionals& b)
{
    return !(a==b);
};



bool operator== (const req_product_info& a, const req_product_info& b)
{
    return (          a.request_info ==  b.request_info  &&          a.product_code ==  b.product_code  &&   true  );
};

bool operator!= (const req_product_info& a, const req_product_info& b)
{
    return !(a==b);
};



bool operator== (const res_product_info::IC_response& a, const res_product_info::IC_response& b)
{
    return (          a.full_product_info ==  b.full_product_info  &&   true  );
};

bool operator!= (const res_product_info::IC_response& a, const res_product_info::IC_response& b)
{
    return !(a==b);
};



bool operator== (const res_product_info& a, const res_product_info& b)
{
    return (          a.response_info ==  b.response_info  &&          a.response  ==  b.response  &&   true  );
};

bool operator!= (const res_product_info& a, const res_product_info& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (sub_price_level& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_price_level& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("pri");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field price on message sub_price_level::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.price, it->second);
                        //c.price = it->second;
//   field_type

                    it = mv.find("qt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field quantity on message sub_price_level::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.quantity, it->second);
                        //c.quantity = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_price_level& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.price, std::string("pri"));
//  field_type
        __internal_add2map(map, a.quantity, std::string("qt"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_price_level>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_price_deph5& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_price_deph5& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("b0");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field level0 on message sub_price_deph5::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.level0, it->second);
                        //__internal_qpid_fill(c.level0, it->second.asMap());
//   sub_msg_type

                    it = mv.find("b1");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field level1 on message sub_price_deph5::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.level1, it->second);
                        //__internal_qpid_fill(c.level1, it->second.asMap());
//   sub_msg_type

                    it = mv.find("b2");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field level2 on message sub_price_deph5::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.level2, it->second);
                        //__internal_qpid_fill(c.level2, it->second.asMap());
//   sub_msg_type

                    it = mv.find("b3");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field level3 on message sub_price_deph5::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.level3, it->second);
                        //__internal_qpid_fill(c.level3, it->second.asMap());
//   sub_msg_type

                    it = mv.find("b4");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field level4 on message sub_price_deph5::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.level4, it->second);
                        //__internal_qpid_fill(c.level4, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_price_deph5& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.level0, std::string("b0"));
//  sub_msg_type
        __internal_add2map(map, a.level1, std::string("b1"));
//  sub_msg_type
        __internal_add2map(map, a.level2, std::string("b2"));
//  sub_msg_type
        __internal_add2map(map, a.level3, std::string("b3"));
//  sub_msg_type
        __internal_add2map(map, a.level4, std::string("b4"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_price_deph5>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_best_prices& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_best_prices& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("bids");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field bids on message sub_best_prices::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.bids, it->second);
                        //__internal_qpid_fill(c.bids, it->second.asMap());
//   sub_msg_type

                    it = mv.find("asks");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field asks on message sub_best_prices::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.asks, it->second);
                        //__internal_qpid_fill(c.asks, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_best_prices& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.bids, std::string("bids"));
//  sub_msg_type
        __internal_add2map(map, a.asks, std::string("asks"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_best_prices>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (pub_best_prices& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (pub_best_prices& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field product_code on message pub_best_prices::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.product_code, it->second);
                        //__internal_qpid_fill(c.product_code, it->second.asMap());
//   sub_msg_type

                    it = mv.find("bp");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field best_prices on message pub_best_prices::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.best_prices, it->second);
                        //__internal_qpid_fill(c.best_prices, it->second.asMap());
//   sub_msg_type

                    it = mv.find("ocf");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field orig_control_fluct on message pub_best_prices::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.orig_control_fluct, it->second);
                        //__internal_qpid_fill(c.orig_control_fluct, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const pub_best_prices& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.product_code, std::string("pc"));
//  sub_msg_type
        __internal_add2map(map, a.best_prices, std::string("bp"));
//  sub_msg_type
        __internal_add2map(map, a.orig_control_fluct, std::string("ocf"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_best_prices>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (pub_new_products& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (pub_new_products& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("mk");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field market on message pub_new_products::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.market, it->second);
                        //c.market = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const pub_new_products& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.market, std::string("mk"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_new_products>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_full_product_info& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_full_product_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field product_code on message sub_full_product_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.product_code, it->second);
                        //__internal_qpid_fill(c.product_code, it->second.asMap());
//   sub_msg_type

                    it = mv.find("bp");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field best_prices on message sub_full_product_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.best_prices, it->second);
                        //__internal_qpid_fill(c.best_prices, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_full_product_info& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.product_code, std::string("pc"));
//  sub_msg_type
        __internal_add2map(map, a.best_prices, std::string("bp"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_full_product_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_full_product_info_optionals& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_full_product_info_optionals& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("init");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field initialized on message sub_full_product_info_optionals::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.initialized, it->second);
                        //__internal_qpid_fill(c.initialized, it->second.asMap());
//   sub_msg_type

                    it = mv.find("pc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field product_code on message sub_full_product_info_optionals::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.product_code, it->second);
                        //__internal_qpid_fill(c.product_code, it->second.asMap());
//   sub_msg_type

                    it = mv.find("bp");
                    if (it!= mv.end())
                        copy(c.best_prices, it->second);
                        //__internal_qpid_fill(c.best_prices, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_full_product_info_optionals& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.initialized, std::string("init"));
//  sub_msg_type
        __internal_add2map(map, a.product_code, std::string("pc"));
if (a.best_prices.HasValue())
//  sub_msg_type
        __internal_add2map(map, a.best_prices, std::string("bp"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_full_product_info_optionals>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (req_product_info& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (req_product_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rqi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_info on message req_product_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_info, it->second);
                        //__internal_qpid_fill(c.request_info, it->second.asMap());
//   sub_msg_type

                    it = mv.find("pc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field product_code on message req_product_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.product_code, it->second);
                        //__internal_qpid_fill(c.product_code, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const req_product_info& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.request_info, std::string("rqi"));
//  sub_msg_type
        __internal_add2map(map, a.product_code, std::string("pc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_product_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (res_product_info& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (res_product_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rsi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field response_info on message res_product_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.response_info, it->second);
                        //__internal_qpid_fill(c.response_info, it->second.asMap());
//   IN_SUB_MSG

                    it = mv.find("rs");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field response on message res_product_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.response, it->second);
                        //__internal_qpid_fill(c.response, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const res_product_info& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.response_info, std::string("rsi"));
//  IN_SUB_MSG
//        map["rs"] =  qpidmsg_coded_as_qpid_Map(a.response);
        __internal_add2map(map, a.response);


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_product_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (res_product_info::IC_response& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (res_product_info::IC_response& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("bp");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field full_product_info on message res_product_info::IC_response::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.full_product_info, it->second);
                        //__internal_qpid_fill(c.full_product_info, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const res_product_info::IC_response& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.full_product_info, std::string("bp"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_product_info::IC_response>& a, const std::string& field)
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

qpid::messaging::Message pub_best_prices::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["pc"] =  qpidmsg_coded_as_qpid_Map(this->product_code);
        __internal_add2map(content, this->product_code, std::string("pc"));
//  sub_msg_type
//        content["bp"] =  qpidmsg_coded_as_qpid_Map(this->best_prices);
        __internal_add2map(content, this->best_prices, std::string("bp"));
//  sub_msg_type
//        content["ocf"] =  qpidmsg_coded_as_qpid_Map(this->orig_control_fluct);
        __internal_add2map(content, this->orig_control_fluct, std::string("ocf"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message pub_new_products::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
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




qpid::messaging::Message req_product_info::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["rqi"] =  qpidmsg_coded_as_qpid_Map(this->request_info);
        __internal_add2map(content, this->request_info, std::string("rqi"));
//  sub_msg_type
//        content["pc"] =  qpidmsg_coded_as_qpid_Map(this->product_code);
        __internal_add2map(content, this->product_code, std::string("pc"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message res_product_info::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["rsi"] =  qpidmsg_coded_as_qpid_Map(this->response_info);
        __internal_add2map(content, this->response_info, std::string("rsi"));
//  IN_SUB_MSG
//        content["rs"] =  qpidmsg_coded_as_qpid_Map(this->response);
        __internal_add2map(content, this->response, std::string("rs"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




    sub_price_level  __internal_get_default(sub_price_level*)
    {
        return sub_price_level(
//   field_type
   __internal_get_default ((mtk::FixedNumber*)0),
//   field_type
   __internal_get_default ((mtk::FixedNumber*)0)
            );
    }
    
    sub_price_deph5  __internal_get_default(sub_price_deph5*)
    {
        return sub_price_deph5(
//   sub_msg_type
   __internal_get_default((sub_price_level*)0),
//   sub_msg_type
   __internal_get_default((sub_price_level*)0),
//   sub_msg_type
   __internal_get_default((sub_price_level*)0),
//   sub_msg_type
   __internal_get_default((sub_price_level*)0),
//   sub_msg_type
   __internal_get_default((sub_price_level*)0)
            );
    }
    
    sub_best_prices  __internal_get_default(sub_best_prices*)
    {
        return sub_best_prices(
//   sub_msg_type
   __internal_get_default((sub_price_deph5*)0),
//   sub_msg_type
   __internal_get_default((sub_price_deph5*)0)
            );
    }
    
    pub_best_prices  __internal_get_default(pub_best_prices*)
    {
        return pub_best_prices(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_product_code*)0),
//   sub_msg_type
   __internal_get_default((sub_best_prices*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_control_fluct*)0)
            );
    }
    
    pub_new_products  __internal_get_default(pub_new_products*)
    {
        return pub_new_products(
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    sub_full_product_info  __internal_get_default(sub_full_product_info*)
    {
        return sub_full_product_info(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_product_code*)0),
//   sub_msg_type
   __internal_get_default((sub_best_prices*)0)
            );
    }
    
    sub_full_product_info_optionals  __internal_get_default(sub_full_product_info_optionals*)
    {
        return sub_full_product_info_optionals(
//   sub_msg_type
   __internal_get_default((bool*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_product_code*)0),
//   sub_msg_type
   mtk::nullable<sub_best_prices>()
            );
    }
    
    req_product_info  __internal_get_default(req_product_info*)
    {
        return req_product_info(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_request_info*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_product_code*)0)
            );
    }
    
    res_product_info  __internal_get_default(res_product_info*)
    {
        return res_product_info(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_r_response*)0),
//   IN_SUB_MSG
   __internal_get_default((res_product_info::IC_response*)0)
            );
    }
    
    res_product_info::IC_response  __internal_get_default(res_product_info::IC_response*)
    {
        return res_product_info::IC_response(
//   sub_msg_type
   __internal_get_default((sub_full_product_info*)0)
            );
    }
    

sub_price_level::sub_price_level (const qpid::messaging::Message& msg)
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



sub_price_deph5::sub_price_deph5 (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   level0(__internal_get_default((sub_price_level*)0)),
//   sub_msg_type
   level1(__internal_get_default((sub_price_level*)0)),
//   sub_msg_type
   level2(__internal_get_default((sub_price_level*)0)),
//   sub_msg_type
   level3(__internal_get_default((sub_price_level*)0)),
//   sub_msg_type
   level4(__internal_get_default((sub_price_level*)0)) 
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



sub_best_prices::sub_best_prices (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   bids(__internal_get_default((sub_price_deph5*)0)),
//   sub_msg_type
   asks(__internal_get_default((sub_price_deph5*)0)) 
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



pub_best_prices::pub_best_prices (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   product_code(__internal_get_default((mtk::msg::sub_product_code*)0)),
//   sub_msg_type
   best_prices(__internal_get_default((sub_best_prices*)0)),
//   sub_msg_type
   orig_control_fluct(__internal_get_default((mtk::msg::sub_control_fluct*)0)) 
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



pub_new_products::pub_new_products (const qpid::messaging::Message& msg)
    :  //   field_type
   market(__internal_get_default((std::string*)0)) 
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



sub_full_product_info::sub_full_product_info (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   product_code(__internal_get_default((mtk::msg::sub_product_code*)0)),
//   sub_msg_type
   best_prices(__internal_get_default((sub_best_prices*)0)) 
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



sub_full_product_info_optionals::sub_full_product_info_optionals (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   initialized(__internal_get_default((bool*)0)),
//   sub_msg_type
   product_code(__internal_get_default((mtk::msg::sub_product_code*)0)) 
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



req_product_info::req_product_info (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   request_info(__internal_get_default((mtk::msg::sub_request_info*)0)),
//   sub_msg_type
   product_code(__internal_get_default((mtk::msg::sub_product_code*)0)) 
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



res_product_info::res_product_info (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   response_info(__internal_get_default((mtk::msg::sub_r_response*)0)),
//   IN_SUB_MSG
   response(__internal_get_default((res_product_info::IC_response*)0)) 
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



res_product_info::IC_response::IC_response (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   full_product_info(__internal_get_default((sub_full_product_info*)0)) 
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

mtk::t_qpid_filter  pub_best_prices::get_in_subject (const std::string& product_code_market,const std::string& product_code_product)
    {
        return mtk::t_qpid_filter(MTK_SS("BP." << product_code_market << "." << product_code_product << ""));
    }
    mtk::t_qpid_filter  pub_best_prices::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("BP." << this->product_code.market << "." << this->product_code.product << ""));
    }
    mtk::t_qpid_filter  pub_new_products::get_in_subject (const std::string& market)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI.ALL." << market << ".NP"));
    }
    mtk::t_qpid_filter  pub_new_products::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI.ALL." << this->market << ".NP"));
    }
    mtk::t_qpid_filter  req_product_info::get_in_subject (const std::string& request_info_process_info_location_client_code,const std::string& product_code_market)
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << request_info_process_info_location_client_code << "." << product_code_market << ".REQPI"));
    }
    mtk::t_qpid_filter  req_product_info::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("GS." << this->request_info.process_info.location.client_code << "." << this->product_code.market << ".REQPI"));
    }
    mtk::t_qpid_filter  res_product_info::get_in_subject (const std::string& response_info_request_info_process_info_location_client_code,const std::string& response_info_request_info_process_info_location_machine,const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_session_id,const std::string& response_info_request_info_req_id_req_code)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << response_info_request_info_process_info_location_client_code << "." << response_info_request_info_process_info_location_machine << "." << response_info_request_info_process_info_process_uuid << "." << response_info_request_info_req_id_session_id << "." << response_info_request_info_req_id_req_code << ".PRC.RESPI"));
    }
    mtk::t_qpid_filter  res_product_info::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->response_info.request_info.process_info.location.client_code << "." << this->response_info.request_info.process_info.location.machine << "." << this->response_info.request_info.process_info.process_uuid << "." << this->response_info.request_info.req_id.session_id << "." << this->response_info.request_info.req_id.req_code << ".PRC.RESPI"));
    }
    

};   //namespace mtk {
};   //namespace prices {
};   //namespace msg {


