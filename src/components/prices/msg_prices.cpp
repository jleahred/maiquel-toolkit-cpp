
// generated automatically
// coded last modification:        Wed Mar 16 18:34:38 2011


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
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_price_level::check_recomended(void) const
{
    std::string result;

    return result;
}



sub_price_deph5::sub_price_deph5 (   const sub_price_level&  _level0,   const sub_price_level&  _level1,   const sub_price_level&  _level2,   const sub_price_level&  _level3,   const sub_price_level&  _level4)
    :     level0(_level0),   level1(_level1),   level2(_level2),   level3(_level3),   level4(_level4) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_price_deph5::check_recomended(void) const
{
    std::string result;

    return result;
}



pub_best_prices::pub_best_prices (   const mtk::msg::sub_product_code&  _product_code,   const sub_price_deph5&  _bids,   const sub_price_deph5&  _asks)
    :     product_code(_product_code),   bids(_bids),   asks(_asks) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string pub_best_prices::check_recomended(void) const
{
    std::string result;

    return result;
}


std::ostream& operator<< (std::ostream& o, const sub_price_level & c)
{
    o << "{ "

        << "price:"<<   c.price << "  "        << "quantity:"<<   c.quantity << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const sub_price_deph5 & c)
{
    o << "{ "

        << "level0:"<< c.level0<<"  "        << "level1:"<< c.level1<<"  "        << "level2:"<< c.level2<<"  "        << "level3:"<< c.level3<<"  "        << "level4:"<< c.level4<<"  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const pub_best_prices & c)
{
    o << "{ "

        << "product_code:"<< c.product_code<<"  "        << "bids:"<< c.bids<<"  "        << "asks:"<< c.asks<<"  "
        << " }";
    return o;
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



bool operator== (const pub_best_prices& a, const pub_best_prices& b)
{
    return (          a.product_code ==  b.product_code  &&          a.bids ==  b.bids  &&          a.asks ==  b.asks  &&   true  );
};

bool operator!= (const pub_best_prices& a, const pub_best_prices& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (sub_price_level& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_price_level& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("pr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field price on message sub_price_level::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.price, it->second);
                        //c.price = it->second;
//   field_type

                    it = mv.find("qt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field quantity on message sub_price_level::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.quantity, it->second);
                        //c.quantity = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_price_level& a)
{
    

//  field_type
        __internal_add2map(map, a.price, std::string("pr"));
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
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field level0 on message sub_price_deph5::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.level0, it->second);
                        //__internal_qpid_fill(c.level0, it->second.asMap());
//   sub_msg_type

                    it = mv.find("b1");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field level1 on message sub_price_deph5::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.level1, it->second);
                        //__internal_qpid_fill(c.level1, it->second.asMap());
//   sub_msg_type

                    it = mv.find("b2");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field level2 on message sub_price_deph5::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.level2, it->second);
                        //__internal_qpid_fill(c.level2, it->second.asMap());
//   sub_msg_type

                    it = mv.find("b3");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field level3 on message sub_price_deph5::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.level3, it->second);
                        //__internal_qpid_fill(c.level3, it->second.asMap());
//   sub_msg_type

                    it = mv.find("b4");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field level4 on message sub_price_deph5::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.level4, it->second);
                        //__internal_qpid_fill(c.level4, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_price_deph5& a)
{
    

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





//void  __internal_qpid_fill (pub_best_prices& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (pub_best_prices& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field product_code on message pub_best_prices::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.product_code, it->second);
                        //__internal_qpid_fill(c.product_code, it->second.asMap());
//   sub_msg_type

                    it = mv.find("bid");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field bids on message pub_best_prices::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.bids, it->second);
                        //__internal_qpid_fill(c.bids, it->second.asMap());
//   sub_msg_type

                    it = mv.find("ask");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field asks on message pub_best_prices::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.asks, it->second);
                        //__internal_qpid_fill(c.asks, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const pub_best_prices& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.product_code, std::string("pc"));
//  sub_msg_type
        __internal_add2map(map, a.bids, std::string("bid"));
//  sub_msg_type
        __internal_add2map(map, a.asks, std::string("ask"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_best_prices>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)

qpid::messaging::Message sub_price_level::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  field_type
//        content["pr"] = this->price;
        __internal_add2map(content, this->price, std::string("pr"));
//  field_type
//        content["qt"] = this->quantity;
        __internal_add2map(content, this->quantity, std::string("qt"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message sub_price_deph5::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["b0"] =  qpidmsg_coded_as_qpid_Map(this->level0);
        __internal_add2map(content, this->level0, std::string("b0"));
//  sub_msg_type
//        content["b1"] =  qpidmsg_coded_as_qpid_Map(this->level1);
        __internal_add2map(content, this->level1, std::string("b1"));
//  sub_msg_type
//        content["b2"] =  qpidmsg_coded_as_qpid_Map(this->level2);
        __internal_add2map(content, this->level2, std::string("b2"));
//  sub_msg_type
//        content["b3"] =  qpidmsg_coded_as_qpid_Map(this->level3);
        __internal_add2map(content, this->level3, std::string("b3"));
//  sub_msg_type
//        content["b4"] =  qpidmsg_coded_as_qpid_Map(this->level4);
        __internal_add2map(content, this->level4, std::string("b4"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message pub_best_prices::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["pc"] =  qpidmsg_coded_as_qpid_Map(this->product_code);
        __internal_add2map(content, this->product_code, std::string("pc"));
//  sub_msg_type
//        content["bid"] =  qpidmsg_coded_as_qpid_Map(this->bids);
        __internal_add2map(content, this->bids, std::string("bid"));
//  sub_msg_type
//        content["ask"] =  qpidmsg_coded_as_qpid_Map(this->asks);
        __internal_add2map(content, this->asks, std::string("ask"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
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
    
    pub_best_prices  __internal_get_default(pub_best_prices*)
    {
        return pub_best_prices(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_product_code*)0),
//   sub_msg_type
   __internal_get_default((sub_price_deph5*)0),
//   sub_msg_type
   __internal_get_default((sub_price_deph5*)0)
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
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
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
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



pub_best_prices::pub_best_prices (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   product_code(__internal_get_default((mtk::msg::sub_product_code*)0)),
//   sub_msg_type
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
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                MTK_SS(cr<<*this), mtk::alPriorError));
    }

std::string  pub_best_prices::get_in_subject (const std::string& product_code_sys_code_market,const std::string& product_code_sys_code_product)
    {
        return MTK_SS("PUB." << product_code_sys_code_market << "." << product_code_sys_code_product << "");
    }
    std::string  pub_best_prices::get_out_subject (void) const
    {
        return MTK_SS("PUB." << this->product_code.sys_code.market << "." << this->product_code.sys_code.product << "");
    }
    

};   //namespace mtk {
};   //namespace prices {
};   //namespace msg {


