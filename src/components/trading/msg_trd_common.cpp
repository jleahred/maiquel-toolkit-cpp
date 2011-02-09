
// generated automatically
// coded last modification:        Mon Jan 17 22:34:07 2011
// pythonscript last modification: Mon Jan 24 10:23:48 2011


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_trd_common.h"

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
    inline int8_t __internal_get_default_int8_t(int8_t*)
    {
        return 0;
    }
    inline int16_t  __internal_get_default_int16_t(int16_t*)
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



inline void  copy(mtk::FixedNumber& result, const qpid::messaging::Variant& v)
{
    result = ({   std::map<qpid::messaging::MapView::key_type, qpid::messaging::Variant> ifn = /*it->second*/v.asMap();
                    mtk::FixedNumber(mtk::fnIntCode(ifn["n"].asInt32()), mtk::fnDec(ifn["d"].asInt8()), mtk::fnInc(ifn["i"].asInt8()));
            });
}

inline void   copy(std::string& result, const qpid::messaging::Variant& v)
{
    result = v.asString();
}



inline void   copy(char& result, const qpid::messaging::Variant& v)
{
    result = v.asInt8();
}


inline void copy(mtk::DateTime& result, const qpid::messaging::Variant& v)
{
    result =  WARNING_do_not_use_it__I_coul_kill_you_for_it__get_DateTime_from_time_quantity(mtk::dtTimeQuantity(mtk::dtTimeQuantitySerialNumber(v.asDouble())));
}

inline void copy(int32_t& result, const qpid::messaging::Variant& v)
{
    result =  v.asInt32();
}

inline void copy(mtk::Double& result, const qpid::messaging::Variant& v)
{
    result =  v.asDouble();
}


template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::messaging::Variant& v)
{
    T temp(__internal_get_default((T*)0));
    copy(temp, v);
    result = temp;
}


template<typename T>
void  copy (mtk::list<T>& result, const qpid::messaging::Variant& v)
{
    const qpid::messaging::Variant::List& l = v.asList();
    std::list<qpid::messaging::Variant>::const_iterator it = l.begin();
    while (it!= l.end())
    {
        T temp(__internal_get_default((T*)0));
        copy(temp, *it);
        result.push_back(temp);
        ++it;
    }
}



    inline void __internal_add2map (qpid::messaging::Variant::Map& map, const std::string& a, const std::string& key)
    {
        map[key] = a;
    }
    inline void __internal_add2map (qpid::messaging::MapContent& map, const std::string& a, const std::string& key)
    {
        map[key] = a;
    }

    inline void __internal_add2map (qpid::messaging::Variant::Map& map, const mtk::FixedNumber& a, const std::string& key)
    {
        map[key] = QPID_DESCOMPOSE_FIXED_NUMBER(a);
    }
    inline void __internal_add2map (qpid::messaging::MapContent& map, const mtk::FixedNumber& a, const std::string& key)
    {
        map[key] = QPID_DESCOMPOSE_FIXED_NUMBER(a);
    }

    inline void __internal_add2map (qpid::messaging::Variant::Map& map, const mtk::Double& a, const std::string& key)
    {
        map[key] = a.get()._0;
    }
    inline void __internal_add2map (qpid::messaging::MapContent& map, const mtk::Double& a, const std::string& key)
    {
        map[key] = a.get()._0;
    }


    #define REGISTER_LIST_BASIC_TYPE(__TYPE__)         inline void  __internal_add2map  (qpid::messaging::Variant::Map& map, const mtk::list<__TYPE__>& l, const std::string& key)            {                qpid::messaging::Variant::List list;                                mtk::list<__TYPE__>::const_iterator it = l.begin();                while (it != l.end())                {                    list.push_back(*it);                    ++it;                }                                map[key] = list;            }            inline void  __internal_add2map  (qpid::messaging::MapContent& map, const mtk::list<__TYPE__>& l, const std::string& key)            {                qpid::messaging::Variant::List list;                                mtk::list<__TYPE__>::const_iterator it = l.begin();                while (it != l.end())                {                    list.push_back(*it);                    ++it;                }                                map[key] = list;            }    

    REGISTER_LIST_BASIC_TYPE(std::string)
    
    
    template<typename T>
    void  __internal_add2map  (qpid::messaging::Variant::Map& map, const mtk::list<T>& l, const std::string& key)
    {
        qpid::messaging::Variant::List list;
        
        typename mtk::list<T>::const_iterator it = l.begin();
        while (it != l.end())
        {
            qpid::messaging::Variant::Map m;
            __internal_add2map(m, *it);
            list.push_back(m);
            ++it;
        }
        
        map[key] = list;
    }
    template<typename T>
    void  __internal_add2map  (qpid::messaging::MapContent& map, const mtk::list<T>& l, const std::string& key)
    {
        qpid::messaging::Variant::List list;
        
        typename mtk::list<T>::const_iterator it = l.begin();
        while (it != l.end())
        {
            qpid::messaging::Variant::Map m;
            __internal_add2map(m, *it);
            list.push_back(m);
            ++it;
        }
        
        map[key] = list;
    }

    template<typename T>
    void  __internal_add2map  (qpid::messaging::Variant::Map& map, const mtk::nullable<T>& n, const std::string& key)
    {
        if (n.HasValue())
            __internal_add2map(map, n.Get(), key);
    }

    template<typename T>
    void  __internal_add2map  (qpid::messaging::MapContent& map, const mtk::nullable<T>& n, const std::string& key)
    {
        if (n.HasValue())
            __internal_add2map(map, n.Get(), key);
    }

    inline void __internal_add2map (qpid::messaging::Variant::Map& map, const mtk::DateTime& a, const std::string& key)
    {
        map[key] = double(a.__WARNING_NOT_CALL_IT_internal_use_GetTimeQuantitySerialNumber().WarningDontDoThisGetInternal());
    }
    inline void __internal_add2map (qpid::messaging::MapContent& map, const mtk::DateTime& a, const std::string& key)
    {
        map[key] = double(a.__WARNING_NOT_CALL_IT_internal_use_GetTimeQuantitySerialNumber().WarningDontDoThisGetInternal());
    }

    inline void __internal_add2map (qpid::messaging::Variant::Map& map, const int32_t& a, const std::string& key)
    {
        map[key] = int32_t(a);
    }
    inline void __internal_add2map (qpid::messaging::MapContent& map, const int32_t& a, const std::string& key)
    {
        map[key] = int32_t(a);
    }

    inline void __internal_add2map (qpid::messaging::Variant::Map& map, const int16_t& a, const std::string& key)
    {
        map[key] = int16_t(a);
    }
    inline void __internal_add2map (qpid::messaging::MapContent& map, const int16_t& a, const std::string& key)
    {
        map[key] = int16_t(a);
    }

    inline void __internal_add2map (qpid::messaging::Variant::Map& map, const int8_t& a, const std::string& key)
    {
        map[key] = int8_t(a);
    }
    inline void __internal_add2map (qpid::messaging::MapContent& map, const int8_t& a, const std::string& key)
    {
        map[key] = int8_t(a);
    }
    inline void __internal_add2map (qpid::messaging::Variant::Map& map, const int64_t& a, const std::string& key)
    {
        map[key] = int64_t(a);
    }
    inline void __internal_add2map (qpid::messaging::MapContent& map, const int64_t& a, const std::string& key)
    {
        map[key] = int64_t(a);
    }


    template<typename T>
    void  __internal_add2map(qpid::messaging::MapContent& map, const T& t, const std::string& key)
    {
        qpid::messaging::Variant::Map m;
        __internal_add2map(m, t);
        map[key] = m;
    }
    template<typename T>
    void  __internal_add2map(qpid::messaging::Variant::Map& map, const T& t, const std::string& key)
    {
        qpid::messaging::Variant::Map m;
        __internal_add2map(m, t);
        map[key] = m;
    }




//========================================================================
//------------------------------------------------------------------------
//  I M P L E M E N T A T I O N
//  internal fordward declarations


sub_order_id::sub_order_id ( const mtk::msg::sub_request_id&  parent)
    :  mtk::msg::sub_request_id(parent) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_order_id::check_recomended(void) const
{
    std::string result;

    return result;
}



sub_total_executions::sub_total_executions (   const mtk::Double&  _sum_price_by_qty,   const mtk::FixedNumber&  _quantity,   const mtk::FixedNumber&  _remaining_qty)
    :     sum_price_by_qty(_sum_price_by_qty),   quantity(_quantity),   remaining_qty(_remaining_qty) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_total_executions::check_recomended(void) const
{
    std::string result;

    return result;
}


std::ostream& operator<< (std::ostream& o, const sub_order_id & c)
{
    o << "{ "
    << "("  <<  static_cast<const mtk::msg::sub_request_id&>(c)  << ")" 

        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const sub_total_executions & c)
{
    o << "{ "

        << "sum_price_by_qty:"<<   c.sum_price_by_qty << "  "        << "quantity:"<<   c.quantity << "  "        << "remaining_qty:"<<   c.remaining_qty << "  "
        << " }";
    return o;
};



bool operator== (const sub_order_id& a, const sub_order_id& b)
{
    return ( (static_cast<const mtk::msg::sub_request_id&>(a)   ==  static_cast<const mtk::msg::sub_request_id&>(b))  &&    true  );
};

bool operator!= (const sub_order_id& a, const sub_order_id& b)
{
    return !(a==b);
};



bool operator== (const sub_total_executions& a, const sub_total_executions& b)
{
    return (          a.sum_price_by_qty ==  b.sum_price_by_qty  &&          a.quantity ==  b.quantity  &&          a.remaining_qty ==  b.remaining_qty  &&   true  );
};

bool operator!= (const sub_total_executions& a, const sub_total_executions& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (sub_order_id& c, std::map<qpid::messaging::MapView::key_type, qpid::messaging::Variant> mv)
void  copy (sub_order_id& c, const qpid::messaging::Variant& v)
    {  
        const std::map<qpid::messaging::MapView::key_type, qpid::messaging::Variant> mv = v.asMap();
copy(static_cast<mtk::msg::sub_request_id&>(c), v);
        std::map<qpid::messaging::MapView::key_type, qpid::messaging::Variant>::const_iterator it;

    }


void __internal_add2map (qpid::messaging::Variant::Map& map, const sub_order_id& a)
{
    
//  parent
__internal_add2map(map, static_cast<const mtk::msg::sub_request_id&>(a));



};




void __internal_add2map (qpid::messaging::MapContent& map, const sub_order_id& a)
{
    
//  parent
__internal_add2map(map, static_cast<const mtk::msg::sub_request_id&>(a));



};





//void  __internal_qpid_fill (sub_total_executions& c, std::map<qpid::messaging::MapView::key_type, qpid::messaging::Variant> mv)
void  copy (sub_total_executions& c, const qpid::messaging::Variant& v)
    {  
        const std::map<qpid::messaging::MapView::key_type, qpid::messaging::Variant> mv = v.asMap();

        std::map<qpid::messaging::MapView::key_type, qpid::messaging::Variant>::const_iterator it;
//   field_type

                    it = mv.find("spq");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field sum_price_by_qty on message sub_total_executions::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.sum_price_by_qty, it->second);
                        //c.sum_price_by_qty = it->second;
//   field_type

                    it = mv.find("aqt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field quantity on message sub_total_executions::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.quantity, it->second);
                        //c.quantity = it->second;
//   field_type

                    it = mv.find("rq");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field remaining_qty on message sub_total_executions::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.remaining_qty, it->second);
                        //c.remaining_qty = it->second;

    }


void __internal_add2map (qpid::messaging::Variant::Map& map, const sub_total_executions& a)
{
    

//  field_type
        __internal_add2map(map, a.sum_price_by_qty, std::string("spq"));
//  field_type
        __internal_add2map(map, a.quantity, std::string("aqt"));
//  field_type
        __internal_add2map(map, a.remaining_qty, std::string("rq"));


};




void __internal_add2map (qpid::messaging::MapContent& map, const sub_total_executions& a)
{
    

//  field_type
        __internal_add2map(map, a.sum_price_by_qty, std::string("spq"));
//  field_type
        __internal_add2map(map, a.quantity, std::string("aqt"));
//  field_type
        __internal_add2map(map, a.remaining_qty, std::string("rq"));


};



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)

qpid::messaging::Message sub_order_id::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message message;
    qpid::messaging::MapContent content(message);

//  parent
__internal_add2map(content, static_cast<const mtk::msg::sub_request_id&>(*this));



    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    content.encode();
    return message;
};




qpid::messaging::Message sub_total_executions::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message message;
    qpid::messaging::MapContent content(message);


//  field_type
//        content["spq"] = this->sum_price_by_qty;
        __internal_add2map(content, this->sum_price_by_qty, std::string("spq"));
//  field_type
//        content["aqt"] = this->quantity;
        __internal_add2map(content, this->quantity, std::string("aqt"));
//  field_type
//        content["rq"] = this->remaining_qty;
        __internal_add2map(content, this->remaining_qty, std::string("rq"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    content.encode();
    return message;
};




    sub_order_id  __internal_get_default(sub_order_id*)
    {
        return sub_order_id(
__internal_get_default((mtk::msg::sub_request_id*)0)
            );
    }
    
    sub_total_executions  __internal_get_default(sub_total_executions*)
    {
        return sub_total_executions(
//   field_type
   __internal_get_default ((mtk::Double*)0),
//   field_type
   __internal_get_default ((mtk::FixedNumber*)0),
//   field_type
   __internal_get_default ((mtk::FixedNumber*)0)
            );
    }
    

sub_order_id::sub_order_id (const qpid::messaging::Message& msg)
    :  mtk::msg::sub_request_id(msg) 
    {  
        qpid::messaging::MapView mv(msg);
        std::map<qpid::messaging::MapView::key_type, qpid::messaging::Variant> map = mv.asMap();
        copy(*this, map);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



sub_total_executions::sub_total_executions (const qpid::messaging::Message& msg)
    :  //   field_type
   sum_price_by_qty(__internal_get_default((mtk::Double*)0)),
//   field_type
   quantity(__internal_get_default((mtk::FixedNumber*)0)),
//   field_type
   remaining_qty(__internal_get_default((mtk::FixedNumber*)0)) 
    {  
        qpid::messaging::MapView mv(msg);
        std::map<qpid::messaging::MapView::key_type, qpid::messaging::Variant> map = mv.asMap();
        copy(*this, map);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {


