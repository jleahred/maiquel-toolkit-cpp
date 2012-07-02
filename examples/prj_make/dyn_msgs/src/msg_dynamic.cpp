
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_dynamic.h"

namespace testing { 
namespace dynamic { 







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


sub_levels::sub_levels (   const mtk::nullable<int32_t>&  _price0,   const mtk::nullable<int32_t>&  _quantity0,   const mtk::nullable<int32_t>&  _price1,   const mtk::nullable<int32_t>&  _quantity1,   const mtk::nullable<int32_t>&  _price2,   const mtk::nullable<int32_t>&  _quantity2,   const mtk::nullable<int32_t>&  _price3,   const mtk::nullable<int32_t>&  _quantity3,   const mtk::nullable<int32_t>&  _price4,   const mtk::nullable<int32_t>&  _quantity4,   const mtk::nullable<int32_t>&  _price5,   const mtk::nullable<int32_t>&  _quantity5)
    :     price0(_price0),   quantity0(_quantity0),   price1(_price1),   quantity1(_quantity1),   price2(_price2),   quantity2(_quantity2),   price3(_price3),   quantity3(_quantity3),   price4(_price4),   quantity4(_quantity4),   price5(_price5),   quantity5(_quantity5) 
       
    {  
    }



void  sub_levels::check_recomended(void) const
{

}

void sub_levels::before_send(void) const
{

}




pub_dynamic::pub_dynamic (   const std::string&  _product_name,   const bool&  _processed,   const mtk::nullable<mtk::DateTime>&  _value_date,   const mtk::nullable<int16_t>&  _num_legs,   const mtk::nullable<std::string>&  _testing,   const mtk::nullable<sub_levels>&  _bids,   const mtk::nullable<sub_levels__qpid_map>&  _asks)
    :     product_name(_product_name),   processed(_processed),   value_date(_value_date),   num_legs(_num_legs),   testing(_testing),   bids(_bids),   asks(_asks) 
       , __internal_warning_control_fields(0)
    {  
    }



void  pub_dynamic::check_recomended(void) const
{

}

void pub_dynamic::before_send(void) const
{

}



    //    generate_class_qpid_variant_in_impl
    
sub_levels__qpid_map::sub_levels__qpid_map ()
      :  m_static( 
   mtk::nullable<int32_t> {},
   mtk::nullable<int32_t> {},
   mtk::nullable<int32_t> {},
   mtk::nullable<int32_t> {},
   mtk::nullable<int32_t> {},
   mtk::nullable<int32_t> {},
   mtk::nullable<int32_t> {},
   mtk::nullable<int32_t> {},
   mtk::nullable<int32_t> {},
   mtk::nullable<int32_t> {},
   mtk::nullable<int32_t> {},
   mtk::nullable<int32_t> {}) 
    {  
    }



    //    generate_class_qpid_variant_in_impl
    
pub_dynamic__qpid_map::pub_dynamic__qpid_map (   const std::string&  _product_name,   const bool&  _processed)
      :  m_static( 
   _product_name,
   _processed,
   mtk::nullable<mtk::DateTime> {},
   mtk::nullable<int16_t> {},
   mtk::nullable<std::string> {},
   mtk::nullable<sub_levels> {},
   mtk::nullable<sub_levels__qpid_map> {}) 
    {  
    }



    qpid::types::Variant::Map   pub_dynamic__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

std::ostream& operator<< (std::ostream& o, const sub_levels & c)
{
    o << "{ "

        << "price0:"<<   c.price0 << "  "        << "quantity0:"<<   c.quantity0 << "  "        << "price1:"<<   c.price1 << "  "        << "quantity1:"<<   c.quantity1 << "  "        << "price2:"<<   c.price2 << "  "        << "quantity2:"<<   c.quantity2 << "  "        << "price3:"<<   c.price3 << "  "        << "quantity3:"<<   c.quantity3 << "  "        << "price4:"<<   c.price4 << "  "        << "quantity4:"<<   c.quantity4 << "  "        << "price5:"<<   c.price5 << "  "        << "quantity5:"<<   c.quantity5 << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_levels & c)
{
    o << YAML::BeginMap

        << YAML::Key << "price0"  << YAML::Value <<   c.price0        << YAML::Key << "quantity0"  << YAML::Value <<   c.quantity0        << YAML::Key << "price1"  << YAML::Value <<   c.price1        << YAML::Key << "quantity1"  << YAML::Value <<   c.quantity1        << YAML::Key << "price2"  << YAML::Value <<   c.price2        << YAML::Key << "quantity2"  << YAML::Value <<   c.quantity2        << YAML::Key << "price3"  << YAML::Value <<   c.price3        << YAML::Key << "quantity3"  << YAML::Value <<   c.quantity3        << YAML::Key << "price4"  << YAML::Value <<   c.price4        << YAML::Key << "quantity4"  << YAML::Value <<   c.quantity4        << YAML::Key << "price5"  << YAML::Value <<   c.price5        << YAML::Key << "quantity5"  << YAML::Value <<   c.quantity5
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_levels & c)
{


        node["price0"]  >> c.price0;
        node["quantity0"]  >> c.quantity0;
        node["price1"]  >> c.price1;
        node["quantity1"]  >> c.quantity1;
        node["price2"]  >> c.price2;
        node["quantity2"]  >> c.quantity2;
        node["price3"]  >> c.price3;
        node["quantity3"]  >> c.quantity3;
        node["price4"]  >> c.price4;
        node["quantity4"]  >> c.quantity4;
        node["price5"]  >> c.price5;
        node["quantity5"]  >> c.quantity5;


};


std::ostream& operator<< (std::ostream& o, const pub_dynamic & c)
{
    o << "{ "

        << "product_name:"<<   c.product_name << "  "        << "processed:"<< c.processed<<"  "        << "value_date:"<<   c.value_date << "  "        << "num_legs:"<<   c.num_legs << "  "        << "testing:"<<   c.testing << "  "        << "bids:"<< c.bids<<"  "        << "asks:"<< c.asks<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const pub_dynamic & c)
{
    o << YAML::BeginMap

        << YAML::Key << "product_name"  << YAML::Value <<   c.product_name        << YAML::Key << "processed"  << YAML::Value << c.processed        << YAML::Key << "value_date"  << YAML::Value <<   c.value_date        << YAML::Key << "num_legs"  << YAML::Value <<   c.num_legs        << YAML::Key << "testing"  << YAML::Value <<   c.testing        << YAML::Key << "bids"  << YAML::Value << c.bids        << YAML::Key << "asks"  << YAML::Value << c.asks
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, pub_dynamic & c)
{


        node["product_name"]  >> c.product_name;
        node["processed"]  >> c.processed;
        node["value_date"]  >> c.value_date;
        node["num_legs"]  >> c.num_legs;
        node["testing"]  >> c.testing;
        node["bids"]  >> c.bids;
        node["asks"]  >> c.asks;


};


bool operator== (const sub_levels& a, const sub_levels& b)
{
    return (          a.price0 ==  b.price0  &&          a.quantity0 ==  b.quantity0  &&          a.price1 ==  b.price1  &&          a.quantity1 ==  b.quantity1  &&          a.price2 ==  b.price2  &&          a.quantity2 ==  b.quantity2  &&          a.price3 ==  b.price3  &&          a.quantity3 ==  b.quantity3  &&          a.price4 ==  b.price4  &&          a.quantity4 ==  b.quantity4  &&          a.price5 ==  b.price5  &&          a.quantity5 ==  b.quantity5  &&   true  );
};

bool operator!= (const sub_levels& a, const sub_levels& b)
{
    return !(a==b);
};



bool operator== (const pub_dynamic& a, const pub_dynamic& b)
{
    return (          a.product_name ==  b.product_name  &&          a.processed ==  b.processed  &&          a.value_date ==  b.value_date  &&          a.num_legs ==  b.num_legs  &&          a.testing ==  b.testing  &&          a.bids ==  b.bids  &&          a.asks ==  b.asks  &&   true  );
};

bool operator!= (const pub_dynamic& a, const pub_dynamic& b)
{
    return !(a==b);
};




void  copy (sub_levels& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("price0");
                    if (it!= mv.end())
                        copy(c.price0, it->second);
                        //c.price0 = it->second;
//   field_type

                    it = mv.find("quantity0");
                    if (it!= mv.end())
                        copy(c.quantity0, it->second);
                        //c.quantity0 = it->second;
//   field_type

                    it = mv.find("price0");
                    if (it!= mv.end())
                        copy(c.price1, it->second);
                        //c.price1 = it->second;
//   field_type

                    it = mv.find("quantity0");
                    if (it!= mv.end())
                        copy(c.quantity1, it->second);
                        //c.quantity1 = it->second;
//   field_type

                    it = mv.find("price0");
                    if (it!= mv.end())
                        copy(c.price2, it->second);
                        //c.price2 = it->second;
//   field_type

                    it = mv.find("quantity0");
                    if (it!= mv.end())
                        copy(c.quantity2, it->second);
                        //c.quantity2 = it->second;
//   field_type

                    it = mv.find("price0");
                    if (it!= mv.end())
                        copy(c.price3, it->second);
                        //c.price3 = it->second;
//   field_type

                    it = mv.find("quantity0");
                    if (it!= mv.end())
                        copy(c.quantity3, it->second);
                        //c.quantity3 = it->second;
//   field_type

                    it = mv.find("price0");
                    if (it!= mv.end())
                        copy(c.price4, it->second);
                        //c.price4 = it->second;
//   field_type

                    it = mv.find("quantity0");
                    if (it!= mv.end())
                        copy(c.quantity4, it->second);
                        //c.quantity4 = it->second;
//   field_type

                    it = mv.find("price0");
                    if (it!= mv.end())
                        copy(c.price5, it->second);
                        //c.price5 = it->second;
//   field_type

                    it = mv.find("quantity0");
                    if (it!= mv.end())
                        copy(c.quantity5, it->second);
                        //c.quantity5 = it->second;

        c.check_recomended ();
    }


void  copy (sub_levels__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const sub_levels& a)
{

    a.before_send();
    a.check_recomended();

if (a.price0.HasValue())
//  field_type
        __internal_add2map(map, a.price0, std::string("price0"));
if (a.quantity0.HasValue())
//  field_type
        __internal_add2map(map, a.quantity0, std::string("quantity0"));
if (a.price1.HasValue())
//  field_type
        __internal_add2map(map, a.price1, std::string("price0"));
if (a.quantity1.HasValue())
//  field_type
        __internal_add2map(map, a.quantity1, std::string("quantity0"));
if (a.price2.HasValue())
//  field_type
        __internal_add2map(map, a.price2, std::string("price0"));
if (a.quantity2.HasValue())
//  field_type
        __internal_add2map(map, a.quantity2, std::string("quantity0"));
if (a.price3.HasValue())
//  field_type
        __internal_add2map(map, a.price3, std::string("price0"));
if (a.quantity3.HasValue())
//  field_type
        __internal_add2map(map, a.quantity3, std::string("quantity0"));
if (a.price4.HasValue())
//  field_type
        __internal_add2map(map, a.price4, std::string("price0"));
if (a.quantity4.HasValue())
//  field_type
        __internal_add2map(map, a.quantity4, std::string("quantity0"));
if (a.price5.HasValue())
//  field_type
        __internal_add2map(map, a.price5, std::string("price0"));
if (a.quantity5.HasValue())
//  field_type
        __internal_add2map(map, a.quantity5, std::string("quantity0"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const sub_levels__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_levels>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_levels__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (pub_dynamic& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("procut_name");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field product_name on message pub_dynamic::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.product_name, it->second);
                        //c.product_name = it->second;
//   sub_msg_type

                    it = mv.find("pm");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field processed on message pub_dynamic::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.processed, it->second);
                        //__internal_qpid_fill(c.processed, it->second.asMap());
//   field_type

                    it = mv.find("value_date");
                    if (it!= mv.end())
                        copy(c.value_date, it->second);
                        //c.value_date = it->second;
//   field_type

                    it = mv.find("num_legs");
                    if (it!= mv.end())
                        copy(c.num_legs, it->second);
                        //c.num_legs = it->second;
//   field_type

                    it = mv.find("testing");
                    if (it!= mv.end())
                        copy(c.testing, it->second);
                        //c.testing = it->second;
//   sub_msg_type

                    it = mv.find("bids");
                    if (it!= mv.end())
                        copy(c.bids, it->second);
                        //__internal_qpid_fill(c.bids, it->second.asMap());
//   sub_msg_type

                    it = mv.find("asks");
                    if (it!= mv.end())
                        copy(c.asks, it->second);
                        //__internal_qpid_fill(c.asks, it->second.asMap());

        c.check_recomended ();
    }


void  copy (pub_dynamic__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const pub_dynamic& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.product_name, std::string("procut_name"));
//  sub_msg_type
        __internal_add2map(map, a.processed, std::string("pm"));
if (a.value_date.HasValue())
//  field_type
        __internal_add2map(map, a.value_date, std::string("value_date"));
if (a.num_legs.HasValue())
//  field_type
        __internal_add2map(map, a.num_legs, std::string("num_legs"));
if (a.testing.HasValue())
//  field_type
        __internal_add2map(map, a.testing, std::string("testing"));
if (a.bids.HasValue())
//  sub_msg_type
        __internal_add2map(map, a.bids, std::string("bids"));
if (a.asks.HasValue())
//  sub_msg_type
        __internal_add2map(map, a.asks, std::string("asks"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const pub_dynamic__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_dynamic>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_dynamic__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)

qpid::types::Variant::Map   pub_dynamic::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;


//  field_type
//        content["procut_name"] = this->product_name;
        __internal_add2map(content, this->product_name, std::string("procut_name"));
//  sub_msg_type
//        content["pm"] =  qpidmsg_coded_as_qpid_Map(this->processed);
        __internal_add2map(content, this->processed, std::string("pm"));
//if (this->value_date.HasValue())
//  field_type
//        content["value_date"] = this->value_date;
        __internal_add2map(content, this->value_date, std::string("value_date"));
//if (this->num_legs.HasValue())
//  field_type
//        content["num_legs"] = this->num_legs;
        __internal_add2map(content, this->num_legs, std::string("num_legs"));
//if (this->testing.HasValue())
//  field_type
//        content["testing"] = this->testing;
        __internal_add2map(content, this->testing, std::string("testing"));
//if (this->bids.HasValue())
//  sub_msg_type
//        content["bids"] =  qpidmsg_coded_as_qpid_Map(this->bids);
        __internal_add2map(content, this->bids, std::string("bids"));
//if (this->asks.HasValue())
//  sub_msg_type
//        content["asks"] =  qpidmsg_coded_as_qpid_Map(this->asks);
        __internal_add2map(content, this->asks, std::string("asks"));



    
    return content;
};




    sub_levels  __internal_get_default(sub_levels*)
    {
        return sub_levels(
//   field_type
   mtk::nullable<int32_t>(),
//   field_type
   mtk::nullable<int32_t>(),
//   field_type
   mtk::nullable<int32_t>(),
//   field_type
   mtk::nullable<int32_t>(),
//   field_type
   mtk::nullable<int32_t>(),
//   field_type
   mtk::nullable<int32_t>(),
//   field_type
   mtk::nullable<int32_t>(),
//   field_type
   mtk::nullable<int32_t>(),
//   field_type
   mtk::nullable<int32_t>(),
//   field_type
   mtk::nullable<int32_t>(),
//   field_type
   mtk::nullable<int32_t>(),
//   field_type
   mtk::nullable<int32_t>()
            );
    }
    
    pub_dynamic  __internal_get_default(pub_dynamic*)
    {
        return pub_dynamic(
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((bool*)0),
//   field_type
   mtk::nullable<mtk::DateTime>(),
//   field_type
   mtk::nullable<int16_t>(),
//   field_type
   mtk::nullable<std::string>(),
//   sub_msg_type
   mtk::nullable<sub_levels>(),
//   sub_msg_type
   mtk::nullable<sub_levels__qpid_map>()
            );
    }
    
sub_levels::sub_levels (const qpid::types::Variant::Map&  mv)
     
    {
        copy(*this, mv);
        check_recomended ();  
    }


sub_levels__qpid_map::sub_levels__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

pub_dynamic::pub_dynamic (const qpid::types::Variant::Map&  mv)
     : //   field_type
   product_name(__internal_get_default((std::string*)0)),
//   sub_msg_type
   processed(__internal_get_default((bool*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


pub_dynamic__qpid_map::pub_dynamic__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    
mtk::t_qpid_filter  pub_dynamic::get_in_subject ()
    {
        return mtk::t_qpid_filter(MTK_SS("testing.DYNAMIC"));
    }
    mtk::t_qpid_filter  pub_dynamic::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("testing.DYNAMIC"));
    }
    /*static*/  mtk::t_qpid_address  pub_dynamic::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("testing"));
    }
    mtk::t_qpid_address  pub_dynamic::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("testing"));
    }
    

};   //namespace testing {
};   //namespace dynamic {


