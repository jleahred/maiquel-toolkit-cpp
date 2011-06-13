
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


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


sub_order_id::sub_order_id ( const mtk::msg::sub_request_id&  parent)
    :  mtk::msg::sub_request_id(parent) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_order_id::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_order_id::before_send(void) const
{

}




sub_exec_conf::sub_exec_conf (   const std::string&  _exec_id,   const mtk::FixedNumber&  _price,   const mtk::FixedNumber&  _quantity,   const enBuySell&  _side)
    :     exec_id(_exec_id),   price(_price),   quantity(_quantity),   side(_side) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_exec_conf::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_exec_conf::before_send(void) const
{

}




sub_total_executions::sub_total_executions (   const mtk::Double&  _sum_price_by_qty,   const mtk::FixedNumber&  _acc_quantity,   const mtk::FixedNumber&  _remaining_qty)
    :     sum_price_by_qty(_sum_price_by_qty),   acc_quantity(_acc_quantity),   remaining_qty(_remaining_qty) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_total_executions::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_total_executions::before_send(void) const
{

}




sub_account_info::sub_account_info (   const std::string&  _client_code,   const std::string&  _name)
    :     client_code(_client_code),   name(_name) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_account_info::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_account_info::before_send(void) const
{

}




sub_invariant_order_info::sub_invariant_order_info (   const sub_order_id&  _order_id,   const mtk::msg::sub_product_code&  _product_code,   const enBuySell&  _side,   const sub_account_info&  _account)
    :     order_id(_order_id),   product_code(_product_code),   side(_side),   account(_account) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_invariant_order_info::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_invariant_order_info::before_send(void) const
{

}




RQ_XX::RQ_XX (   const sub_invariant_order_info&  _invariant,   const mtk::msg::sub_request_info&  _req_info,   const std::string&  _cli_ref,   const mtk::msg::sub_control_fluct&  _orig_control_fluct)
    :     invariant(_invariant),   req_info(_req_info),   cli_ref(_cli_ref),   orig_control_fluct(_orig_control_fluct) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string RQ_XX::check_recomended(void) const
{
    std::string result;

    return result;
}

void RQ_XX::before_send(void) const
{

}




CF_XX::CF_XX (   const sub_invariant_order_info&  _invariant,   const std::string&  _market_order_id,   const mtk::msg::sub_request_id&  _req_id,   const std::string&  _cli_ref,   const sub_total_executions&  _total_execs,   const mtk::msg::sub_control_fluct&  _orig_control_fluct)
    :     invariant(_invariant),   market_order_id(_market_order_id),   req_id(_req_id),   cli_ref(_cli_ref),   total_execs(_total_execs),   orig_control_fluct(_orig_control_fluct) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string CF_XX::check_recomended(void) const
{
    std::string result;

    return result;
}

void CF_XX::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const sub_order_id & c)
{
    o << "{ "
    << "("  <<  static_cast<const mtk::msg::sub_request_id&>(c)  << ")" 

        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_order_id & c)
{
    o << YAML::BeginMap
    << YAML::Key << "mtk::msg::sub_request_id" <<  YAML::Value << static_cast<const mtk::msg::sub_request_id&>(c)  

        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_order_id & c)
{

    node["mtk::msg::sub_request_id"]   >>   static_cast<mtk::msg::sub_request_id&>(c)  ;



};


std::ostream& operator<< (std::ostream& o, const sub_exec_conf & c)
{
    o << "{ "

        << "exec_id:"<<   c.exec_id << "  "        << "price:"<<   c.price << "  "        << "quantity:"<<   c.quantity << "  "        << "side:"<< c.side<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_exec_conf & c)
{
    o << YAML::BeginMap

        << YAML::Key << "exec_id"  << YAML::Value <<   c.exec_id        << YAML::Key << "price"  << YAML::Value <<   c.price        << YAML::Key << "quantity"  << YAML::Value <<   c.quantity        << YAML::Key << "side"  << YAML::Value << c.side
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_exec_conf & c)
{


        node["exec_id"]  >> c.exec_id;
        node["price"]  >> c.price;
        node["quantity"]  >> c.quantity;
        node["side"]  >> c.side;


};


std::ostream& operator<< (std::ostream& o, const sub_total_executions & c)
{
    o << "{ "

        << "sum_price_by_qty:"<<   c.sum_price_by_qty << "  "        << "acc_quantity:"<<   c.acc_quantity << "  "        << "remaining_qty:"<<   c.remaining_qty << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_total_executions & c)
{
    o << YAML::BeginMap

        << YAML::Key << "sum_price_by_qty"  << YAML::Value <<   c.sum_price_by_qty        << YAML::Key << "acc_quantity"  << YAML::Value <<   c.acc_quantity        << YAML::Key << "remaining_qty"  << YAML::Value <<   c.remaining_qty
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_total_executions & c)
{


        node["sum_price_by_qty"]  >> c.sum_price_by_qty;
        node["acc_quantity"]  >> c.acc_quantity;
        node["remaining_qty"]  >> c.remaining_qty;


};


std::ostream& operator<< (std::ostream& o, const sub_account_info & c)
{
    o << "{ "

        << "client_code:"<<   c.client_code << "  "        << "name:"<<   c.name << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_account_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "client_code"  << YAML::Value <<   c.client_code        << YAML::Key << "name"  << YAML::Value <<   c.name
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_account_info & c)
{


        node["client_code"]  >> c.client_code;
        node["name"]  >> c.name;


};


std::ostream& operator<< (std::ostream& o, const sub_invariant_order_info & c)
{
    o << "{ "

        << "order_id:"<< c.order_id<<"  "        << "product_code:"<< c.product_code<<"  "        << "side:"<< c.side<<"  "        << "account:"<< c.account<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_invariant_order_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "order_id"  << YAML::Value << c.order_id        << YAML::Key << "product_code"  << YAML::Value << c.product_code        << YAML::Key << "side"  << YAML::Value << c.side        << YAML::Key << "account"  << YAML::Value << c.account
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_invariant_order_info & c)
{


        node["order_id"]  >> c.order_id;
        node["product_code"]  >> c.product_code;
        node["side"]  >> c.side;
        node["account"]  >> c.account;


};


std::ostream& operator<< (std::ostream& o, const RQ_XX & c)
{
    o << "{ "

        << "invariant:"<< c.invariant<<"  "        << "req_info:"<< c.req_info<<"  "        << "cli_ref:"<<   c.cli_ref << "  "        << "orig_control_fluct:"<< c.orig_control_fluct<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RQ_XX & c)
{
    o << YAML::BeginMap

        << YAML::Key << "invariant"  << YAML::Value << c.invariant        << YAML::Key << "req_info"  << YAML::Value << c.req_info        << YAML::Key << "cli_ref"  << YAML::Value <<   c.cli_ref        << YAML::Key << "orig_control_fluct"  << YAML::Value << c.orig_control_fluct
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RQ_XX & c)
{


        node["invariant"]  >> c.invariant;
        node["req_info"]  >> c.req_info;
        node["cli_ref"]  >> c.cli_ref;
        node["orig_control_fluct"]  >> c.orig_control_fluct;


};


std::ostream& operator<< (std::ostream& o, const CF_XX & c)
{
    o << "{ "

        << "invariant:"<< c.invariant<<"  "        << "market_order_id:"<<   c.market_order_id << "  "        << "req_id:"<< c.req_id<<"  "        << "cli_ref:"<<   c.cli_ref << "  "        << "total_execs:"<< c.total_execs<<"  "        << "orig_control_fluct:"<< c.orig_control_fluct<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const CF_XX & c)
{
    o << YAML::BeginMap

        << YAML::Key << "invariant"  << YAML::Value << c.invariant        << YAML::Key << "market_order_id"  << YAML::Value <<   c.market_order_id        << YAML::Key << "req_id"  << YAML::Value << c.req_id        << YAML::Key << "cli_ref"  << YAML::Value <<   c.cli_ref        << YAML::Key << "total_execs"  << YAML::Value << c.total_execs        << YAML::Key << "orig_control_fluct"  << YAML::Value << c.orig_control_fluct
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, CF_XX & c)
{


        node["invariant"]  >> c.invariant;
        node["market_order_id"]  >> c.market_order_id;
        node["req_id"]  >> c.req_id;
        node["cli_ref"]  >> c.cli_ref;
        node["total_execs"]  >> c.total_execs;
        node["orig_control_fluct"]  >> c.orig_control_fluct;


};


bool operator< (const sub_account_info& a, const sub_account_info& b)
{
    if (false)   return true;
    else if (true)
    {
        auto ca = mtk::make_tuple( 0          , a.client_code       , a.name );
        auto cb = mtk::make_tuple( 0          , b.client_code       , b.name );
        return ca < cb;
    }
    else
        return false;
};


bool operator== (const sub_order_id& a, const sub_order_id& b)
{
    return ( (static_cast<const mtk::msg::sub_request_id&>(a)   ==  static_cast<const mtk::msg::sub_request_id&>(b))  &&    true  );
};

bool operator!= (const sub_order_id& a, const sub_order_id& b)
{
    return !(a==b);
};



bool operator== (const sub_exec_conf& a, const sub_exec_conf& b)
{
    return (          a.exec_id ==  b.exec_id  &&          a.price ==  b.price  &&          a.quantity ==  b.quantity  &&          a.side ==  b.side  &&   true  );
};

bool operator!= (const sub_exec_conf& a, const sub_exec_conf& b)
{
    return !(a==b);
};



bool operator== (const sub_total_executions& a, const sub_total_executions& b)
{
    return (          a.sum_price_by_qty ==  b.sum_price_by_qty  &&          a.acc_quantity ==  b.acc_quantity  &&          a.remaining_qty ==  b.remaining_qty  &&   true  );
};

bool operator!= (const sub_total_executions& a, const sub_total_executions& b)
{
    return !(a==b);
};



bool operator== (const sub_account_info& a, const sub_account_info& b)
{
    return (          a.client_code ==  b.client_code  &&          a.name ==  b.name  &&   true  );
};

bool operator!= (const sub_account_info& a, const sub_account_info& b)
{
    return !(a==b);
};



bool operator== (const sub_invariant_order_info& a, const sub_invariant_order_info& b)
{
    return (          a.order_id ==  b.order_id  &&          a.product_code ==  b.product_code  &&          a.side ==  b.side  &&          a.account ==  b.account  &&   true  );
};

bool operator!= (const sub_invariant_order_info& a, const sub_invariant_order_info& b)
{
    return !(a==b);
};



bool operator== (const RQ_XX& a, const RQ_XX& b)
{
    return (          a.invariant ==  b.invariant  &&          a.req_info ==  b.req_info  &&          a.cli_ref ==  b.cli_ref  &&          a.orig_control_fluct ==  b.orig_control_fluct  &&   true  );
};

bool operator!= (const RQ_XX& a, const RQ_XX& b)
{
    return !(a==b);
};



bool operator== (const CF_XX& a, const CF_XX& b)
{
    return (          a.invariant ==  b.invariant  &&          a.market_order_id ==  b.market_order_id  &&          a.req_id ==  b.req_id  &&          a.cli_ref ==  b.cli_ref  &&          a.total_execs ==  b.total_execs  &&          a.orig_control_fluct ==  b.orig_control_fluct  &&   true  );
};

bool operator!= (const CF_XX& a, const CF_XX& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (sub_order_id& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_order_id& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<mtk::msg::sub_request_id&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_order_id& a)
{

    a.before_send();

//  parent
__internal_add2map(map, static_cast<const mtk::msg::sub_request_id&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_order_id>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_exec_conf& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_exec_conf& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("eid");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field exec_id on message sub_exec_conf::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.exec_id, it->second);
                        //c.exec_id = it->second;
//   field_type

                    it = mv.find("pri");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field price on message sub_exec_conf::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.price, it->second);
                        //c.price = it->second;
//   field_type

                    it = mv.find("qt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field quantity on message sub_exec_conf::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.quantity, it->second);
                        //c.quantity = it->second;
//   sub_msg_type

                    it = mv.find("sd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field side on message sub_exec_conf::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.side, it->second);
                        //__internal_qpid_fill(c.side, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_exec_conf& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.exec_id, std::string("eid"));
//  field_type
        __internal_add2map(map, a.price, std::string("pri"));
//  field_type
        __internal_add2map(map, a.quantity, std::string("qt"));
//  sub_msg_type
        __internal_add2map(map, a.side, std::string("sd"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_exec_conf>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_total_executions& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_total_executions& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("spq");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field sum_price_by_qty on message sub_total_executions::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.sum_price_by_qty, it->second);
                        //c.sum_price_by_qty = it->second;
//   field_type

                    it = mv.find("aqt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field acc_quantity on message sub_total_executions::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.acc_quantity, it->second);
                        //c.acc_quantity = it->second;
//   field_type

                    it = mv.find("rmq");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field remaining_qty on message sub_total_executions::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.remaining_qty, it->second);
                        //c.remaining_qty = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_total_executions& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.sum_price_by_qty, std::string("spq"));
//  field_type
        __internal_add2map(map, a.acc_quantity, std::string("aqt"));
//  field_type
        __internal_add2map(map, a.remaining_qty, std::string("rmq"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_total_executions>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_account_info& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_account_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("cc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field client_code on message sub_account_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.client_code, it->second);
                        //c.client_code = it->second;
//   field_type

                    it = mv.find("nm");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field name on message sub_account_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.name, it->second);
                        //c.name = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_account_info& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.client_code, std::string("cc"));
//  field_type
        __internal_add2map(map, a.name, std::string("nm"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_account_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_invariant_order_info& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_invariant_order_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("oid");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field order_id on message sub_invariant_order_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.order_id, it->second);
                        //__internal_qpid_fill(c.order_id, it->second.asMap());
//   sub_msg_type

                    it = mv.find("pc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field product_code on message sub_invariant_order_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.product_code, it->second);
                        //__internal_qpid_fill(c.product_code, it->second.asMap());
//   sub_msg_type

                    it = mv.find("sd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field side on message sub_invariant_order_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.side, it->second);
                        //__internal_qpid_fill(c.side, it->second.asMap());
//   sub_msg_type

                    it = mv.find("acc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field account on message sub_invariant_order_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.account, it->second);
                        //__internal_qpid_fill(c.account, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_invariant_order_info& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.order_id, std::string("oid"));
//  sub_msg_type
        __internal_add2map(map, a.product_code, std::string("pc"));
//  sub_msg_type
        __internal_add2map(map, a.side, std::string("sd"));
//  sub_msg_type
        __internal_add2map(map, a.account, std::string("acc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_invariant_order_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (RQ_XX& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (RQ_XX& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("inv");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field invariant on message RQ_XX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.invariant, it->second);
                        //__internal_qpid_fill(c.invariant, it->second.asMap());
//   sub_msg_type

                    it = mv.find("rqin");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field req_info on message RQ_XX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.req_info, it->second);
                        //__internal_qpid_fill(c.req_info, it->second.asMap());
//   field_type

                    it = mv.find("clr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field cli_ref on message RQ_XX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.cli_ref, it->second);
                        //c.cli_ref = it->second;
//   sub_msg_type

                    it = mv.find("ocf");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field orig_control_fluct on message RQ_XX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.orig_control_fluct, it->second);
                        //__internal_qpid_fill(c.orig_control_fluct, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const RQ_XX& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.invariant, std::string("inv"));
//  sub_msg_type
        __internal_add2map(map, a.req_info, std::string("rqin"));
//  field_type
        __internal_add2map(map, a.cli_ref, std::string("clr"));
//  sub_msg_type
        __internal_add2map(map, a.orig_control_fluct, std::string("ocf"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_XX>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (CF_XX& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (CF_XX& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("inv");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field invariant on message CF_XX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.invariant, it->second);
                        //__internal_qpid_fill(c.invariant, it->second.asMap());
//   field_type

                    it = mv.find("moi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field market_order_id on message CF_XX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.market_order_id, it->second);
                        //c.market_order_id = it->second;
//   sub_msg_type

                    it = mv.find("rqid");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field req_id on message CF_XX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.req_id, it->second);
                        //__internal_qpid_fill(c.req_id, it->second.asMap());
//   field_type

                    it = mv.find("clr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field cli_ref on message CF_XX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.cli_ref, it->second);
                        //c.cli_ref = it->second;
//   sub_msg_type

                    it = mv.find("ext");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field total_execs on message CF_XX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.total_execs, it->second);
                        //__internal_qpid_fill(c.total_execs, it->second.asMap());
//   sub_msg_type

                    it = mv.find("ocf");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field orig_control_fluct on message CF_XX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.orig_control_fluct, it->second);
                        //__internal_qpid_fill(c.orig_control_fluct, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const CF_XX& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.invariant, std::string("inv"));
//  field_type
        __internal_add2map(map, a.market_order_id, std::string("moi"));
//  sub_msg_type
        __internal_add2map(map, a.req_id, std::string("rqid"));
//  field_type
        __internal_add2map(map, a.cli_ref, std::string("clr"));
//  sub_msg_type
        __internal_add2map(map, a.total_execs, std::string("ext"));
//  sub_msg_type
        __internal_add2map(map, a.orig_control_fluct, std::string("ocf"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_XX>& a, const std::string& field)
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

    sub_order_id  __internal_get_default(sub_order_id*)
    {
        return sub_order_id(
__internal_get_default((mtk::msg::sub_request_id*)0)
            );
    }
    
    sub_exec_conf  __internal_get_default(sub_exec_conf*)
    {
        return sub_exec_conf(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((mtk::FixedNumber*)0),
//   field_type
   __internal_get_default ((mtk::FixedNumber*)0),
//   sub_msg_type
   __internal_get_default((enBuySell*)0)
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
    
    sub_account_info  __internal_get_default(sub_account_info*)
    {
        return sub_account_info(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    sub_invariant_order_info  __internal_get_default(sub_invariant_order_info*)
    {
        return sub_invariant_order_info(
//   sub_msg_type
   __internal_get_default((sub_order_id*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_product_code*)0),
//   sub_msg_type
   __internal_get_default((enBuySell*)0),
//   sub_msg_type
   __internal_get_default((sub_account_info*)0)
            );
    }
    
    RQ_XX  __internal_get_default(RQ_XX*)
    {
        return RQ_XX(
//   sub_msg_type
   __internal_get_default((sub_invariant_order_info*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_request_info*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_control_fluct*)0)
            );
    }
    
    CF_XX  __internal_get_default(CF_XX*)
    {
        return CF_XX(
//   sub_msg_type
   __internal_get_default((sub_invariant_order_info*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_request_id*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((sub_total_executions*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_control_fluct*)0)
            );
    }
    

sub_order_id::sub_order_id (const qpid::messaging::Message& msg)
    :  mtk::msg::sub_request_id(msg) 
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



sub_exec_conf::sub_exec_conf (const qpid::messaging::Message& msg)
    :  //   field_type
   exec_id(__internal_get_default((std::string*)0)),
//   field_type
   price(__internal_get_default((mtk::FixedNumber*)0)),
//   field_type
   quantity(__internal_get_default((mtk::FixedNumber*)0)),
//   sub_msg_type
   side(__internal_get_default((enBuySell*)0)) 
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



sub_total_executions::sub_total_executions (const qpid::messaging::Message& msg)
    :  //   field_type
   sum_price_by_qty(__internal_get_default((mtk::Double*)0)),
//   field_type
   acc_quantity(__internal_get_default((mtk::FixedNumber*)0)),
//   field_type
   remaining_qty(__internal_get_default((mtk::FixedNumber*)0)) 
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



sub_account_info::sub_account_info (const qpid::messaging::Message& msg)
    :  //   field_type
   client_code(__internal_get_default((std::string*)0)),
//   field_type
   name(__internal_get_default((std::string*)0)) 
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



sub_invariant_order_info::sub_invariant_order_info (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   order_id(__internal_get_default((sub_order_id*)0)),
//   sub_msg_type
   product_code(__internal_get_default((mtk::msg::sub_product_code*)0)),
//   sub_msg_type
   side(__internal_get_default((enBuySell*)0)),
//   sub_msg_type
   account(__internal_get_default((sub_account_info*)0)) 
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



RQ_XX::RQ_XX (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   invariant(__internal_get_default((sub_invariant_order_info*)0)),
//   sub_msg_type
   req_info(__internal_get_default((mtk::msg::sub_request_info*)0)),
//   field_type
   cli_ref(__internal_get_default((std::string*)0)),
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



CF_XX::CF_XX (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   invariant(__internal_get_default((sub_invariant_order_info*)0)),
//   field_type
   market_order_id(__internal_get_default((std::string*)0)),
//   sub_msg_type
   req_id(__internal_get_default((mtk::msg::sub_request_id*)0)),
//   field_type
   cli_ref(__internal_get_default((std::string*)0)),
//   sub_msg_type
   total_execs(__internal_get_default((sub_total_executions*)0)),
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



};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {


