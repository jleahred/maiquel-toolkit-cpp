
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "test_messages.h"

namespace testing { 







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


LimitPosition::LimitPosition (   const mtk::nullable<std::string>&  _buy_sell,   const mtk::nullable<mtk::FixedNumber>&  _price,   const mtk::FixedNumber&  _quantity)
    :     buy_sell(_buy_sell),   price(_price),   quantity(_quantity) 
       
    {  
    }



void  LimitPosition::check_recomended(void) const
{

    if (price.HasValue() == false)
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(10)) // I know it's for all instances
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_recomended", MTK_SS("sub_full_product_info::check_recomended  missing recomended field **price** on LimitPosition  " << *this), mtk::alPriorError));
        MTK_END_EXEC_MAX_FREC

}

void LimitPosition::before_send(void) const
{

}




RQ_NW_LS::RQ_NW_LS (   const std::string&  _order_id,   const std::string&  _cli_ref,   const LimitPosition&  _position,   const LimitPosition&  _positionnn,   const IC_control_fields_&  _control_fields_,   const IC_product_code&  _product_code,   const mtk::list<std::string >&  _names,   const mtk::list<LimitPosition >&  _postitions)
    :     order_id(_order_id),   cli_ref(_cli_ref),   position(_position),   positionnn(_positionnn),   control_fields_(_control_fields_),   product_code(_product_code),   names(_names),   postitions(_postitions) 
       , __internal_warning_control_fields(0)
    {  
    }



void  RQ_NW_LS::check_recomended(void) const
{

}

void RQ_NW_LS::before_send(void) const
{

}




RQ_NW_LS::IC_control_fields_::IC_control_fields_ (   const mtk::DateTime&  _clock_id,   const int32_t&  _secuence)
    :     clock_id(_clock_id),   secuence(_secuence) 
       
    {  
    }



void  RQ_NW_LS::IC_control_fields_::check_recomended(void) const
{

}

void RQ_NW_LS::IC_control_fields_::before_send(void) const
{

}




RQ_NW_LS::IC_product_code::IC_product_code (   const std::string&  _market,   const std::string&  _product_code,   const std::string&  _aditional_code)
    :     market(_market),   product_code(_product_code),   aditional_code(_aditional_code) 
       
    {  
    }



void  RQ_NW_LS::IC_product_code::check_recomended(void) const
{

}

void RQ_NW_LS::IC_product_code::before_send(void) const
{

}




LimitPositionChild::LimitPositionChild ( const LimitPosition&  parent,   const std::string&  _new_field)
    :  LimitPosition(parent),   new_field(_new_field) 
       
    {  
    }



void  LimitPositionChild::check_recomended(void) const
{

}

void LimitPositionChild::before_send(void) const
{
  std::cout  << "#send " << this->new_field << std::endl; 
}



std::ostream& operator<< (std::ostream& o, const LimitPosition & c)
{
    o << "{ "

        << "buy_sell:"<<   c.buy_sell << "  "        << "price:"<<   c.price << "  "        << "quantity:"<<   c.quantity << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const LimitPosition & c)
{
    o << YAML::BeginMap

        << YAML::Key << "buy_sell"  << YAML::Value <<   c.buy_sell        << YAML::Key << "price"  << YAML::Value <<   c.price        << YAML::Key << "quantity"  << YAML::Value <<   c.quantity
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, LimitPosition & c)
{


        node["buy_sell"]  >> c.buy_sell;
        node["price"]  >> c.price;
        node["quantity"]  >> c.quantity;


};


std::ostream& operator<< (std::ostream& o, const RQ_NW_LS::IC_control_fields_ & c)
{
    o << "{ "

        << "clock_id:"<<   c.clock_id << "  "        << "secuence:"<<   c.secuence << "  "
        << " }";
    return o;
};


std::ostream& operator<< (std::ostream& o, const RQ_NW_LS::IC_product_code & c)
{
    o << "{ "

        << "market:"<<   c.market << "  "        << "product_code:"<<   c.product_code << "  "        << "aditional_code:"<<   c.aditional_code << "  "
        << " }";
    return o;
};


std::ostream& operator<< (std::ostream& o, const RQ_NW_LS & c)
{
    o << "{ "

        << "order_id:"<<   c.order_id << "  "        << "cli_ref:"<<   c.cli_ref << "  "        << "position:"<< c.position<<"  "        << "positionnn:"<< c.positionnn<<"  "        << "control_fields_:"<< c.control_fields_<<"  "        << "product_code:"<< c.product_code<<"  "        << "names:"<<   c.names << "  "        << "postitions:"<< c.postitions<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RQ_NW_LS::IC_control_fields_ & c)
{
    o << YAML::BeginMap

        << YAML::Key << "clock_id"  << YAML::Value <<   c.clock_id        << YAML::Key << "secuence"  << YAML::Value <<   c.secuence
        << YAML::EndMap;
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RQ_NW_LS::IC_product_code & c)
{
    o << YAML::BeginMap

        << YAML::Key << "market"  << YAML::Value <<   c.market        << YAML::Key << "product_code"  << YAML::Value <<   c.product_code        << YAML::Key << "aditional_code"  << YAML::Value <<   c.aditional_code
        << YAML::EndMap;
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RQ_NW_LS & c)
{
    o << YAML::BeginMap

        << YAML::Key << "order_id"  << YAML::Value <<   c.order_id        << YAML::Key << "cli_ref"  << YAML::Value <<   c.cli_ref        << YAML::Key << "position"  << YAML::Value << c.position        << YAML::Key << "positionnn"    << YAML::Value << c.positionnn        << YAML::Key << "control_fields_"   << YAML::Value << c.control_fields_        << YAML::Key << "product_code"   << YAML::Value << c.product_code        << YAML::Key << "names"  << YAML::Value <<   c.names        << YAML::Key << "postitions"  << YAML::Value << c.postitions
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RQ_NW_LS::IC_control_fields_ & c)
{


        node["clock_id"]  >> c.clock_id;
        node["secuence"]  >> c.secuence;


};



void  operator >> (const YAML::Node& node, RQ_NW_LS::IC_product_code & c)
{


        node["market"]  >> c.market;
        node["product_code"]  >> c.product_code;
        node["aditional_code"]  >> c.aditional_code;


};



void  operator >> (const YAML::Node& node, RQ_NW_LS & c)
{


        node["order_id"]  >> c.order_id;
        node["cli_ref"]  >> c.cli_ref;
        node["position"]  >> c.position;
        node["positionnn"]  >> c.positionnn;
            node["control_fields_"]   >> c.control_fields_;
            node["product_code"] >>  c.product_code;
        node["names"]  >> c.names;
        node["postitions"]  >> c.postitions;


};


std::ostream& operator<< (std::ostream& o, const LimitPositionChild & c)
{
    o << "{ "
    << "("  <<  static_cast<const LimitPosition&>(c)  << ")" 
        << "new_field:"<<   c.new_field << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const LimitPositionChild & c)
{
    o << YAML::BeginMap
    << YAML::Key << "LimitPosition" <<  YAML::Value << static_cast<const LimitPosition&>(c)  
        << YAML::Key << "new_field"  << YAML::Value <<   c.new_field
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, LimitPositionChild & c)
{

    node["LimitPosition"]   >>   static_cast<LimitPosition&>(c)  ;

        node["new_field"]  >> c.new_field;


};


bool operator== (const LimitPosition& a, const LimitPosition& b)
{
    return (          a.buy_sell ==  b.buy_sell  &&          a.price ==  b.price  &&          a.quantity ==  b.quantity  &&   true  );
};

bool operator!= (const LimitPosition& a, const LimitPosition& b)
{
    return !(a==b);
};



bool operator== (const RQ_NW_LS::IC_control_fields_& a, const RQ_NW_LS::IC_control_fields_& b)
{
    return (          a.clock_id ==  b.clock_id  &&          a.secuence ==  b.secuence  &&   true  );
};

bool operator!= (const RQ_NW_LS::IC_control_fields_& a, const RQ_NW_LS::IC_control_fields_& b)
{
    return !(a==b);
};



bool operator== (const RQ_NW_LS::IC_product_code& a, const RQ_NW_LS::IC_product_code& b)
{
    return (          a.market ==  b.market  &&          a.product_code ==  b.product_code  &&          a.aditional_code ==  b.aditional_code  &&   true  );
};

bool operator!= (const RQ_NW_LS::IC_product_code& a, const RQ_NW_LS::IC_product_code& b)
{
    return !(a==b);
};



bool operator== (const RQ_NW_LS& a, const RQ_NW_LS& b)
{
    return (          a.order_id ==  b.order_id  &&          a.cli_ref ==  b.cli_ref  &&          a.position ==  b.position  &&          a.positionnn ==  b.positionnn  &&          a.control_fields_ ==  b.control_fields_  &&          a.product_code  ==  b.product_code  &&          a.names ==  b.names  &&          a.postitions ==  b.postitions  &&   true  );
};

bool operator!= (const RQ_NW_LS& a, const RQ_NW_LS& b)
{
    return !(a==b);
};



bool operator== (const LimitPositionChild& a, const LimitPositionChild& b)
{
    return ( (static_cast<const LimitPosition&>(a)   ==  static_cast<const LimitPosition&>(b))  &&           a.new_field ==  b.new_field  &&   true  );
};

bool operator!= (const LimitPositionChild& a, const LimitPositionChild& b)
{
    return !(a==b);
};




void  copy (LimitPosition& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("bs");
                    if (it!= mv.end())
                        copy(c.buy_sell, it->second);
                        //c.buy_sell = it->second;
//   field_type

                    it = mv.find("pr");
                    if (it!= mv.end())
                        copy(c.price, it->second);
                        //c.price = it->second;
//   field_type

                    it = mv.find("qt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field quantity on message LimitPosition::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.quantity, it->second);
                        //c.quantity = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const LimitPosition& a)
{

    a.before_send();
    a.check_recomended();

if (a.buy_sell.HasValue())
//  field_type
        __internal_add2map(map, a.buy_sell, std::string("bs"));
if (a.price.HasValue())
//  field_type
        __internal_add2map(map, a.price, std::string("pr"));
//  field_type
        __internal_add2map(map, a.quantity, std::string("qt"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<LimitPosition>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (RQ_NW_LS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("oid");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field order_id on message RQ_NW_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.order_id, it->second);
                        //c.order_id = it->second;
//   field_type

                    it = mv.find("cr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field cli_ref on message RQ_NW_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.cli_ref, it->second);
                        //c.cli_ref = it->second;
//   sub_msg_type

                    it = mv.find("pos");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field position on message RQ_NW_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.position, it->second);
                        //__internal_qpid_fill(c.position, it->second.asMap());
//   sub_msg_type_not_nested

                copy(c.positionnn, mv);
                //__internal_qpid_fill(c.positionnn, mv);
//   IN_MSG

                copy(c.control_fields_, mv);
                //__internal_qpid_fill(c.control_fields_, mv);
//   IN_SUB_MSG

                    it = mv.find("pc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field product_code on message RQ_NW_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.product_code, it->second);
                        //__internal_qpid_fill(c.product_code, it->second.asMap());
//   field_type

                    it = mv.find("ns");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field names on message RQ_NW_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.names, it->second);
                        //c.names = it->second;
//   sub_msg_type

                    it = mv.find("poss");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field postitions on message RQ_NW_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.postitions, it->second);
                        //__internal_qpid_fill(c.postitions, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const RQ_NW_LS& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.order_id, std::string("oid"));
//  field_type
        __internal_add2map(map, a.cli_ref, std::string("cr"));
//  sub_msg_type
        __internal_add2map(map, a.position, std::string("pos"));
//  sub_msg_type_not_nested
        __internal_add2map(map, a.positionnn);
//  IN_MSG
        __internal_add2map(map, a.control_fields_);
//  IN_SUB_MSG
//        map["pc"] =  qpidmsg_coded_as_qpid_Map(a.product_code);
        __internal_add2map(map, a.product_code);
//  field_type
        __internal_add2map(map, a.names, std::string("ns"));
//  sub_msg_type
        __internal_add2map(map, a.postitions, std::string("poss"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_NW_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (RQ_NW_LS::IC_control_fields_& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("ci");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field clock_id on message RQ_NW_LS::IC_control_fields_::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.clock_id, it->second);
                        //c.clock_id = it->second;
//   field_type

                    it = mv.find("sec");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field secuence on message RQ_NW_LS::IC_control_fields_::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.secuence, it->second);
                        //c.secuence = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const RQ_NW_LS::IC_control_fields_& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.clock_id, std::string("ci"));
//  field_type
        __internal_add2map(map, a.secuence, std::string("sec"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_NW_LS::IC_control_fields_>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (RQ_NW_LS::IC_product_code& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("mk");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field market on message RQ_NW_LS::IC_product_code::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.market, it->second);
                        //c.market = it->second;
//   field_type

                    it = mv.find("pr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field product_code on message RQ_NW_LS::IC_product_code::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.product_code, it->second);
                        //c.product_code = it->second;
//   field_type

                    it = mv.find("ac");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field aditional_code on message RQ_NW_LS::IC_product_code::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.aditional_code, it->second);
                        //c.aditional_code = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const RQ_NW_LS::IC_product_code& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.market, std::string("mk"));
//  field_type
        __internal_add2map(map, a.product_code, std::string("pr"));
//  field_type
        __internal_add2map(map, a.aditional_code, std::string("ac"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_NW_LS::IC_product_code>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (LimitPositionChild& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<LimitPosition&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("nf");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field new_field on message LimitPositionChild::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.new_field, it->second);
                        //c.new_field = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const LimitPositionChild& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const LimitPosition&>(a));

//  field_type
        __internal_add2map(map, a.new_field, std::string("nf"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<LimitPositionChild>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)

qpid::types::Variant::Map   RQ_NW_LS::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;


//  field_type
//        content["oid"] = this->order_id;
        __internal_add2map(content, this->order_id, std::string("oid"));
//  field_type
//        content["cr"] = this->cli_ref;
        __internal_add2map(content, this->cli_ref, std::string("cr"));
//  sub_msg_type
//        content["pos"] =  qpidmsg_coded_as_qpid_Map(this->position);
        __internal_add2map(content, this->position, std::string("pos"));
//  sub_msg_type_not_nested
        __internal_add2map(content, this->positionnn);
//  IN_MSG
        __internal_add2map(content, this->control_fields_);
//  IN_SUB_MSG
//        content["pc"] =  qpidmsg_coded_as_qpid_Map(this->product_code);
        __internal_add2map(content, this->product_code, std::string("pc"));
//  field_type
//        content["ns"] = this->names;
        __internal_add2map(content, this->names, std::string("ns"));
//  sub_msg_type
//        content["poss"] =  qpidmsg_coded_as_qpid_Map(this->postitions);
        __internal_add2map(content, this->postitions, std::string("poss"));



    
    return content;
};




    LimitPosition  __internal_get_default(LimitPosition*)
    {
        return LimitPosition(
//   field_type
   mtk::nullable<std::string>(),
//   field_type
   mtk::nullable<mtk::FixedNumber>(),
//   field_type
   __internal_get_default ((mtk::FixedNumber*)0)
            );
    }
    
    RQ_NW_LS  __internal_get_default(RQ_NW_LS*)
    {
        return RQ_NW_LS(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((LimitPosition*)0),
//   sub_msg_type_not_nested
   __internal_get_default((LimitPosition*)0),
//   IN_MSG
   __internal_get_default((RQ_NW_LS::IC_control_fields_*)0),
//   IN_SUB_MSG
   __internal_get_default((RQ_NW_LS::IC_product_code*)0),
//   field_type
   __internal_get_default ((mtk::list<std::string >*)0),
//   sub_msg_type
   __internal_get_default((mtk::list<LimitPosition >*)0)
            );
    }
    
    RQ_NW_LS::IC_control_fields_  __internal_get_default(RQ_NW_LS::IC_control_fields_*)
    {
        return RQ_NW_LS::IC_control_fields_(
//   field_type
   __internal_get_default ((mtk::DateTime*)0),
//   field_type
   __internal_get_default ((int32_t*)0)
            );
    }
    
    RQ_NW_LS::IC_product_code  __internal_get_default(RQ_NW_LS::IC_product_code*)
    {
        return RQ_NW_LS::IC_product_code(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    LimitPositionChild  __internal_get_default(LimitPositionChild*)
    {
        return LimitPositionChild(
__internal_get_default((LimitPosition*)0), //   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
LimitPosition::LimitPosition (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   quantity(__internal_get_default((mtk::FixedNumber*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

RQ_NW_LS::RQ_NW_LS (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   order_id(__internal_get_default((std::string*)0)),
//   field_type
   cli_ref(__internal_get_default((std::string*)0)),
//   sub_msg_type
   position(__internal_get_default((LimitPosition*)0)),
//   sub_msg_type_not_nested
   positionnn(__internal_get_default((LimitPosition*)0)),
//   IN_MSG
   control_fields_(__internal_get_default((RQ_NW_LS::IC_control_fields_*)0)),
//   IN_SUB_MSG
   product_code(__internal_get_default((RQ_NW_LS::IC_product_code*)0)),
//   field_type
   names(__internal_get_default((mtk::list<std::string >*)0)),
//   sub_msg_type
   postitions(__internal_get_default((mtk::list<LimitPosition >*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

RQ_NW_LS::IC_control_fields_::IC_control_fields_ (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   clock_id(__internal_get_default((mtk::DateTime*)0)),
//   field_type
   secuence(__internal_get_default((int32_t*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

RQ_NW_LS::IC_product_code::IC_product_code (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   market(__internal_get_default((std::string*)0)),
//   field_type
   product_code(__internal_get_default((std::string*)0)),
//   field_type
   aditional_code(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

LimitPositionChild::LimitPositionChild (const qpid::types::Variant::Map&  mv)
    :  LimitPosition(mv), //   field_type
   new_field(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }
mtk::t_qpid_filter  RQ_NW_LS::get_in_subject ()
    {
        return mtk::t_qpid_filter(MTK_SS("hola.pajaarito"));
    }
    mtk::t_qpid_filter  RQ_NW_LS::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("hola.pajaarito"));
    }
    /*static*/  mtk::t_qpid_address  RQ_NW_LS::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("testing"));
    }
    mtk::t_qpid_address  RQ_NW_LS::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("testing"));
    }
    

};   //namespace testing {


