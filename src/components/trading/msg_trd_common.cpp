
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


sub_order_id::sub_order_id ( const mtk::msg::sub_request_id&  parent)
    :  mtk::msg::sub_request_id(parent) 
       
    {  
    }



void  sub_order_id::check_recomended(void) const
{

}

void sub_order_id::before_send(void) const
{

}




sub_exec_conf::sub_exec_conf (   const std::string&  _exec_id,   const mtk::FixedNumber&  _price,   const mtk::FixedNumber&  _quantity)
    :     exec_id(_exec_id),   price(_price),   quantity(_quantity) 
       
    {  
    }



void  sub_exec_conf::check_recomended(void) const
{

}

void sub_exec_conf::before_send(void) const
{

}




sub_total_executions::sub_total_executions (   const mtk::Double&  _sum_price_by_qty,   const mtk::FixedNumber&  _acc_quantity,   const mtk::FixedNumber&  _remaining_qty)
    :     sum_price_by_qty(_sum_price_by_qty),   acc_quantity(_acc_quantity),   remaining_qty(_remaining_qty) 
       
    {  
    }



void  sub_total_executions::check_recomended(void) const
{

}

void sub_total_executions::before_send(void) const
{

}




sub_account_info::sub_account_info (   const std::string&  _name,   const std::string&  _client_code)
    :     name(_name),   client_code(_client_code) 
       
    {  
    }



void  sub_account_info::check_recomended(void) const
{

}

void sub_account_info::before_send(void) const
{

}




sub_invariant_order_info::sub_invariant_order_info (   const sub_order_id&  _order_id,   const mtk::msg::sub_product_code&  _product_code,   const enBuySell&  _side,   const sub_account_info&  _account,   const std::string&  _time_in_force,   const bool&  _automatic)
    :     order_id(_order_id),   product_code(_product_code),   side(_side),   account(_account),   time_in_force(_time_in_force),   automatic(_automatic) 
       
    {  
    }



void  sub_invariant_order_info::check_recomended(void) const
{

}

void sub_invariant_order_info::before_send(void) const
{

}




RQ_XX::RQ_XX (   const sub_invariant_order_info&  _invariant,   const mtk::msg::sub_request_info&  _request_info,   const mtk::msg::sub_control_fluct&  _orig_control_fluct)
    :     invariant(_invariant),   request_info(_request_info),   orig_control_fluct(_orig_control_fluct) 
       
    {  
    }



void  RQ_XX::check_recomended(void) const
{

}

void RQ_XX::before_send(void) const
{

}




CF_XX::CF_XX (   const sub_invariant_order_info&  _invariant,   const std::string&  _market_order_id,   const mtk::msg::sub_request_id&  _req_id,   const sub_total_executions&  _total_execs,   const std::string&  _description,   const mtk::msg::sub_control_fluct&  _orig_control_fluct)
    :     invariant(_invariant),   market_order_id(_market_order_id),   req_id(_req_id),   total_execs(_total_execs),   description(_description),   orig_control_fluct(_orig_control_fluct) 
       
    {  
    }



void  CF_XX::check_recomended(void) const
{

}

void CF_XX::before_send(void) const
{

}




RQ_ORDERS_STATUS::RQ_ORDERS_STATUS (   const mtk::msg::sub_request_info&  _request_info,   const std::string&  _market,   const sub_account_info&  _account)
    :     request_info(_request_info),   market(_market),   account(_account) 
       , __internal_warning_control_fields(0)
    {  
    }



void  RQ_ORDERS_STATUS::check_recomended(void) const
{

}

void RQ_ORDERS_STATUS::before_send(void) const
{

}




CF_EXLK::CF_EXLK ( const CF_XX&  parent,   const sub_exec_conf&  _executed_pos)
    :  CF_XX(parent),   executed_pos(_executed_pos) 
       , __internal_warning_control_fields(0)
    {  
    }



void  CF_EXLK::check_recomended(void) const
{

}

void CF_EXLK::before_send(void) const
{

}




CF_ST_EX::CF_ST_EX ( const CF_EXLK&  parent,   const mtk::msg::sub_gen_response_location&  _gen_response_location)
    :  CF_EXLK(parent),   gen_response_location(_gen_response_location) 
       , __internal_warning_control_fields(0)
    {  
    }



void  CF_ST_EX::check_recomended(void) const
{

}

void CF_ST_EX::before_send(void) const
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

        << "exec_id:"<<   c.exec_id << "  "        << "price:"<<   c.price << "  "        << "quantity:"<<   c.quantity << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_exec_conf & c)
{
    o << YAML::BeginMap

        << YAML::Key << "exec_id"  << YAML::Value <<   c.exec_id        << YAML::Key << "price"  << YAML::Value <<   c.price        << YAML::Key << "quantity"  << YAML::Value <<   c.quantity
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_exec_conf & c)
{


        node["exec_id"]  >> c.exec_id;
        node["price"]  >> c.price;
        node["quantity"]  >> c.quantity;


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

        << "name:"<<   c.name << "  "        << "client_code:"<<   c.client_code << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_account_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "name"  << YAML::Value <<   c.name        << YAML::Key << "client_code"  << YAML::Value <<   c.client_code
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_account_info & c)
{


        node["name"]  >> c.name;
        node["client_code"]  >> c.client_code;


};


std::ostream& operator<< (std::ostream& o, const sub_invariant_order_info & c)
{
    o << "{ "

        << "order_id:"<< c.order_id<<"  "        << "product_code:"<< c.product_code<<"  "        << "side:"<< c.side<<"  "        << "account:"<< c.account<<"  "        << "time_in_force:"<<   c.time_in_force << "  "        << "automatic:"<< c.automatic<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_invariant_order_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "order_id"  << YAML::Value << c.order_id        << YAML::Key << "product_code"  << YAML::Value << c.product_code        << YAML::Key << "side"  << YAML::Value << c.side        << YAML::Key << "account"  << YAML::Value << c.account        << YAML::Key << "time_in_force"  << YAML::Value <<   c.time_in_force        << YAML::Key << "automatic"  << YAML::Value << c.automatic
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_invariant_order_info & c)
{


        node["order_id"]  >> c.order_id;
        node["product_code"]  >> c.product_code;
        node["side"]  >> c.side;
        node["account"]  >> c.account;
        node["time_in_force"]  >> c.time_in_force;
        node["automatic"]  >> c.automatic;


};


std::ostream& operator<< (std::ostream& o, const RQ_XX & c)
{
    o << "{ "

        << "invariant:"<< c.invariant<<"  "        << "request_info:"<< c.request_info<<"  "        << "orig_control_fluct:"<< c.orig_control_fluct<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RQ_XX & c)
{
    o << YAML::BeginMap

        << YAML::Key << "invariant"  << YAML::Value << c.invariant        << YAML::Key << "request_info"  << YAML::Value << c.request_info        << YAML::Key << "orig_control_fluct"  << YAML::Value << c.orig_control_fluct
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RQ_XX & c)
{


        node["invariant"]  >> c.invariant;
        node["request_info"]  >> c.request_info;
        node["orig_control_fluct"]  >> c.orig_control_fluct;


};


std::ostream& operator<< (std::ostream& o, const CF_XX & c)
{
    o << "{ "

        << "invariant:"<< c.invariant<<"  "        << "market_order_id:"<<   c.market_order_id << "  "        << "req_id:"<< c.req_id<<"  "        << "total_execs:"<< c.total_execs<<"  "        << "description:"<<   c.description << "  "        << "orig_control_fluct:"<< c.orig_control_fluct<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const CF_XX & c)
{
    o << YAML::BeginMap

        << YAML::Key << "invariant"  << YAML::Value << c.invariant        << YAML::Key << "market_order_id"  << YAML::Value <<   c.market_order_id        << YAML::Key << "req_id"  << YAML::Value << c.req_id        << YAML::Key << "total_execs"  << YAML::Value << c.total_execs        << YAML::Key << "description"  << YAML::Value <<   c.description        << YAML::Key << "orig_control_fluct"  << YAML::Value << c.orig_control_fluct
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, CF_XX & c)
{


        node["invariant"]  >> c.invariant;
        node["market_order_id"]  >> c.market_order_id;
        node["req_id"]  >> c.req_id;
        node["total_execs"]  >> c.total_execs;
        node["description"]  >> c.description;
        node["orig_control_fluct"]  >> c.orig_control_fluct;


};


std::ostream& operator<< (std::ostream& o, const RQ_ORDERS_STATUS & c)
{
    o << "{ "

        << "request_info:"<< c.request_info<<"  "        << "market:"<<   c.market << "  "        << "account:"<< c.account<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const RQ_ORDERS_STATUS & c)
{
    o << YAML::BeginMap

        << YAML::Key << "request_info"  << YAML::Value << c.request_info        << YAML::Key << "market"  << YAML::Value <<   c.market        << YAML::Key << "account"  << YAML::Value << c.account
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, RQ_ORDERS_STATUS & c)
{


        node["request_info"]  >> c.request_info;
        node["market"]  >> c.market;
        node["account"]  >> c.account;


};


std::ostream& operator<< (std::ostream& o, const CF_EXLK & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_XX&>(c)  << ")" 
        << "executed_pos:"<< c.executed_pos<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const CF_EXLK & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_XX" <<  YAML::Value << static_cast<const CF_XX&>(c)  
        << YAML::Key << "executed_pos"  << YAML::Value << c.executed_pos
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, CF_EXLK & c)
{

    node["CF_XX"]   >>   static_cast<CF_XX&>(c)  ;

        node["executed_pos"]  >> c.executed_pos;


};


std::ostream& operator<< (std::ostream& o, const CF_ST_EX & c)
{
    o << "{ "
    << "("  <<  static_cast<const CF_EXLK&>(c)  << ")" 
        << "gen_response_location:"<< c.gen_response_location<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const CF_ST_EX & c)
{
    o << YAML::BeginMap
    << YAML::Key << "CF_EXLK" <<  YAML::Value << static_cast<const CF_EXLK&>(c)  
        << YAML::Key << "gen_response_location"  << YAML::Value << c.gen_response_location
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, CF_ST_EX & c)
{

    node["CF_EXLK"]   >>   static_cast<CF_EXLK&>(c)  ;

        node["gen_response_location"]  >> c.gen_response_location;


};


bool operator< (const sub_account_info& a, const sub_account_info& b)
{
    if (false)   return true;
    else if (true)
    {
        auto ca = mtk::make_tuple( 0          , a.name       , a.client_code );
        auto cb = mtk::make_tuple( 0          , b.name       , b.client_code );
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
    return (          a.exec_id ==  b.exec_id  &&          a.price ==  b.price  &&          a.quantity ==  b.quantity  &&   true  );
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
    return (          a.name ==  b.name  &&          a.client_code ==  b.client_code  &&   true  );
};

bool operator!= (const sub_account_info& a, const sub_account_info& b)
{
    return !(a==b);
};



bool operator== (const sub_invariant_order_info& a, const sub_invariant_order_info& b)
{
    return (          a.order_id ==  b.order_id  &&          a.product_code ==  b.product_code  &&          a.side ==  b.side  &&          a.account ==  b.account  &&          a.time_in_force ==  b.time_in_force  &&          a.automatic ==  b.automatic  &&   true  );
};

bool operator!= (const sub_invariant_order_info& a, const sub_invariant_order_info& b)
{
    return !(a==b);
};



bool operator== (const RQ_XX& a, const RQ_XX& b)
{
    return (          a.invariant ==  b.invariant  &&          a.request_info ==  b.request_info  &&          a.orig_control_fluct ==  b.orig_control_fluct  &&   true  );
};

bool operator!= (const RQ_XX& a, const RQ_XX& b)
{
    return !(a==b);
};



bool operator== (const CF_XX& a, const CF_XX& b)
{
    return (          a.invariant ==  b.invariant  &&          a.market_order_id ==  b.market_order_id  &&          a.req_id ==  b.req_id  &&          a.total_execs ==  b.total_execs  &&          a.description ==  b.description  &&          a.orig_control_fluct ==  b.orig_control_fluct  &&   true  );
};

bool operator!= (const CF_XX& a, const CF_XX& b)
{
    return !(a==b);
};



bool operator== (const RQ_ORDERS_STATUS& a, const RQ_ORDERS_STATUS& b)
{
    return (          a.request_info ==  b.request_info  &&          a.market ==  b.market  &&          a.account ==  b.account  &&   true  );
};

bool operator!= (const RQ_ORDERS_STATUS& a, const RQ_ORDERS_STATUS& b)
{
    return !(a==b);
};



bool operator== (const CF_EXLK& a, const CF_EXLK& b)
{
    return ( (static_cast<const CF_XX&>(a)   ==  static_cast<const CF_XX&>(b))  &&           a.executed_pos ==  b.executed_pos  &&   true  );
};

bool operator!= (const CF_EXLK& a, const CF_EXLK& b)
{
    return !(a==b);
};



bool operator== (const CF_ST_EX& a, const CF_ST_EX& b)
{
    return ( (static_cast<const CF_EXLK&>(a)   ==  static_cast<const CF_EXLK&>(b))  &&           a.gen_response_location ==  b.gen_response_location  &&   true  );
};

bool operator!= (const CF_ST_EX& a, const CF_ST_EX& b)
{
    return !(a==b);
};




void  copy (sub_order_id& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<mtk::msg::sub_request_id&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_order_id& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const mtk::msg::sub_request_id&>(a));



};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_order_id>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





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

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_exec_conf& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.exec_id, std::string("eid"));
//  field_type
        __internal_add2map(map, a.price, std::string("pri"));
//  field_type
        __internal_add2map(map, a.quantity, std::string("qt"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_exec_conf>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





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

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_total_executions& a)
{

    a.before_send();
    a.check_recomended();

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





void  copy (sub_account_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("nm");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field name on message sub_account_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.name, it->second);
                        //c.name = it->second;
//   field_type

                    it = mv.find("cc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field client_code on message sub_account_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.client_code, it->second);
                        //c.client_code = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_account_info& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.name, std::string("nm"));
//  field_type
        __internal_add2map(map, a.client_code, std::string("cc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_account_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





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
//   field_type

                    it = mv.find("tf");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field time_in_force on message sub_invariant_order_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.time_in_force, it->second);
                        //c.time_in_force = it->second;
//   sub_msg_type

                    it = mv.find("au");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field automatic on message sub_invariant_order_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.automatic, it->second);
                        //__internal_qpid_fill(c.automatic, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_invariant_order_info& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.order_id, std::string("oid"));
//  sub_msg_type
        __internal_add2map(map, a.product_code, std::string("pc"));
//  sub_msg_type
        __internal_add2map(map, a.side, std::string("sd"));
//  sub_msg_type
        __internal_add2map(map, a.account, std::string("acc"));
//  field_type
        __internal_add2map(map, a.time_in_force, std::string("tf"));
//  sub_msg_type
        __internal_add2map(map, a.automatic, std::string("au"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_invariant_order_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





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

                    it = mv.find("rqi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_info on message RQ_XX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_info, it->second);
                        //__internal_qpid_fill(c.request_info, it->second.asMap());
//   sub_msg_type

                    it = mv.find("ocf");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field orig_control_fluct on message RQ_XX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.orig_control_fluct, it->second);
                        //__internal_qpid_fill(c.orig_control_fluct, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const RQ_XX& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.invariant, std::string("inv"));
//  sub_msg_type
        __internal_add2map(map, a.request_info, std::string("rqi"));
//  sub_msg_type
        __internal_add2map(map, a.orig_control_fluct, std::string("ocf"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_XX>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





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
//   sub_msg_type

                    it = mv.find("ext");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field total_execs on message CF_XX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.total_execs, it->second);
                        //__internal_qpid_fill(c.total_execs, it->second.asMap());
//   field_type

                    it = mv.find("desc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field description on message CF_XX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.description, it->second);
                        //c.description = it->second;
//   sub_msg_type

                    it = mv.find("ocf");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field orig_control_fluct on message CF_XX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.orig_control_fluct, it->second);
                        //__internal_qpid_fill(c.orig_control_fluct, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const CF_XX& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.invariant, std::string("inv"));
//  field_type
        __internal_add2map(map, a.market_order_id, std::string("moi"));
//  sub_msg_type
        __internal_add2map(map, a.req_id, std::string("rqid"));
//  sub_msg_type
        __internal_add2map(map, a.total_execs, std::string("ext"));
//  field_type
        __internal_add2map(map, a.description, std::string("desc"));
//  sub_msg_type
        __internal_add2map(map, a.orig_control_fluct, std::string("ocf"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_XX>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (RQ_ORDERS_STATUS& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rqi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_info on message RQ_ORDERS_STATUS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_info, it->second);
                        //__internal_qpid_fill(c.request_info, it->second.asMap());
//   field_type

                    it = mv.find("mk");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field market on message RQ_ORDERS_STATUS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.market, it->second);
                        //c.market = it->second;
//   sub_msg_type

                    it = mv.find("acc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field account on message RQ_ORDERS_STATUS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.account, it->second);
                        //__internal_qpid_fill(c.account, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const RQ_ORDERS_STATUS& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.request_info, std::string("rqi"));
//  field_type
        __internal_add2map(map, a.market, std::string("mk"));
//  sub_msg_type
        __internal_add2map(map, a.account, std::string("acc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<RQ_ORDERS_STATUS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (CF_EXLK& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_XX&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("exp");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field executed_pos on message CF_EXLK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.executed_pos, it->second);
                        //__internal_qpid_fill(c.executed_pos, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const CF_EXLK& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const CF_XX&>(a));

//  sub_msg_type
        __internal_add2map(map, a.executed_pos, std::string("exp"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_EXLK>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (CF_ST_EX& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<CF_EXLK&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("grl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field gen_response_location on message CF_ST_EX::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.gen_response_location, it->second);
                        //__internal_qpid_fill(c.gen_response_location, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const CF_ST_EX& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const CF_EXLK&>(a));

//  sub_msg_type
        __internal_add2map(map, a.gen_response_location, std::string("grl"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<CF_ST_EX>& a, const std::string& field)
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

qpid::types::Variant::Map   RQ_ORDERS_STATUS::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;


//  sub_msg_type
//        content["rqi"] =  qpidmsg_coded_as_qpid_Map(this->request_info);
        __internal_add2map(content, this->request_info, std::string("rqi"));
//  field_type
//        content["mk"] = this->market;
        __internal_add2map(content, this->market, std::string("mk"));
//  sub_msg_type
//        content["acc"] =  qpidmsg_coded_as_qpid_Map(this->account);
        __internal_add2map(content, this->account, std::string("acc"));



    
    return content;
};




qpid::types::Variant::Map   CF_EXLK::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const CF_XX&>(*this));

//  sub_msg_type
//        content["exp"] =  qpidmsg_coded_as_qpid_Map(this->executed_pos);
        __internal_add2map(content, this->executed_pos, std::string("exp"));



    
    return content;
};




qpid::types::Variant::Map   CF_ST_EX::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const CF_EXLK&>(*this));

//  sub_msg_type
//        content["grl"] =  qpidmsg_coded_as_qpid_Map(this->gen_response_location);
        __internal_add2map(content, this->gen_response_location, std::string("grl"));



    
    return content;
};




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
   __internal_get_default ((mtk::FixedNumber*)0)
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
   __internal_get_default((sub_account_info*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((bool*)0)
            );
    }
    
    RQ_XX  __internal_get_default(RQ_XX*)
    {
        return RQ_XX(
//   sub_msg_type
   __internal_get_default((sub_invariant_order_info*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_request_info*)0),
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
//   sub_msg_type
   __internal_get_default((sub_total_executions*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_control_fluct*)0)
            );
    }
    
    RQ_ORDERS_STATUS  __internal_get_default(RQ_ORDERS_STATUS*)
    {
        return RQ_ORDERS_STATUS(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_request_info*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((sub_account_info*)0)
            );
    }
    
    CF_EXLK  __internal_get_default(CF_EXLK*)
    {
        return CF_EXLK(
__internal_get_default((CF_XX*)0), //   sub_msg_type
   __internal_get_default((sub_exec_conf*)0)
            );
    }
    
    CF_ST_EX  __internal_get_default(CF_ST_EX*)
    {
        return CF_ST_EX(
__internal_get_default((CF_EXLK*)0), //   sub_msg_type
   __internal_get_default((mtk::msg::sub_gen_response_location*)0)
            );
    }
    
sub_order_id::sub_order_id (const qpid::types::Variant::Map&  mv)
    :  mtk::msg::sub_request_id(mv) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

sub_exec_conf::sub_exec_conf (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   exec_id(__internal_get_default((std::string*)0)),
//   field_type
   price(__internal_get_default((mtk::FixedNumber*)0)),
//   field_type
   quantity(__internal_get_default((mtk::FixedNumber*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

sub_total_executions::sub_total_executions (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   sum_price_by_qty(__internal_get_default((mtk::Double*)0)),
//   field_type
   acc_quantity(__internal_get_default((mtk::FixedNumber*)0)),
//   field_type
   remaining_qty(__internal_get_default((mtk::FixedNumber*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

sub_account_info::sub_account_info (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   name(__internal_get_default((std::string*)0)),
//   field_type
   client_code(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

sub_invariant_order_info::sub_invariant_order_info (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   order_id(__internal_get_default((sub_order_id*)0)),
//   sub_msg_type
   product_code(__internal_get_default((mtk::msg::sub_product_code*)0)),
//   sub_msg_type
   side(__internal_get_default((enBuySell*)0)),
//   sub_msg_type
   account(__internal_get_default((sub_account_info*)0)),
//   field_type
   time_in_force(__internal_get_default((std::string*)0)),
//   sub_msg_type
   automatic(__internal_get_default((bool*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

RQ_XX::RQ_XX (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   invariant(__internal_get_default((sub_invariant_order_info*)0)),
//   sub_msg_type
   request_info(__internal_get_default((mtk::msg::sub_request_info*)0)),
//   sub_msg_type
   orig_control_fluct(__internal_get_default((mtk::msg::sub_control_fluct*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

CF_XX::CF_XX (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   invariant(__internal_get_default((sub_invariant_order_info*)0)),
//   field_type
   market_order_id(__internal_get_default((std::string*)0)),
//   sub_msg_type
   req_id(__internal_get_default((mtk::msg::sub_request_id*)0)),
//   sub_msg_type
   total_execs(__internal_get_default((sub_total_executions*)0)),
//   field_type
   description(__internal_get_default((std::string*)0)),
//   sub_msg_type
   orig_control_fluct(__internal_get_default((mtk::msg::sub_control_fluct*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

RQ_ORDERS_STATUS::RQ_ORDERS_STATUS (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   request_info(__internal_get_default((mtk::msg::sub_request_info*)0)),
//   field_type
   market(__internal_get_default((std::string*)0)),
//   sub_msg_type
   account(__internal_get_default((sub_account_info*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

CF_EXLK::CF_EXLK (const qpid::types::Variant::Map&  mv)
    :  CF_XX(mv), //   sub_msg_type
   executed_pos(__internal_get_default((sub_exec_conf*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

CF_ST_EX::CF_ST_EX (const qpid::types::Variant::Map&  mv)
    :  CF_EXLK(mv), //   sub_msg_type
   gen_response_location(__internal_get_default((mtk::msg::sub_gen_response_location*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }
mtk::t_qpid_filter  RQ_ORDERS_STATUS::get_in_subject (const std::string& account_client_code,const std::string& market)
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << account_client_code << "." << market << ".RQORDST"));
    }
    mtk::t_qpid_filter  RQ_ORDERS_STATUS::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << this->account.client_code << "." << this->market << ".RQORDST"));
    }
    /*static*/  mtk::t_qpid_address  RQ_ORDERS_STATUS::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  RQ_ORDERS_STATUS::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  CF_EXLK::get_in_subject (const std::string& invariant_account_client_code,const std::string& invariant_product_code_market,const std::string& invariant_account_name)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << invariant_account_client_code << "." << invariant_product_code_market << "." << invariant_account_name << ".TRD"));
    }
    mtk::t_qpid_filter  CF_EXLK::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->invariant.account.client_code << "." << this->invariant.product_code.market << "." << this->invariant.account.name << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  CF_EXLK::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  CF_EXLK::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  CF_ST_EX::get_in_subject (const std::string& gen_response_location_broker_code,const std::string& gen_response_location_session_id)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << gen_response_location_broker_code << "." << gen_response_location_session_id << ".STATUS_EX"));
    }
    mtk::t_qpid_filter  CF_ST_EX::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->gen_response_location.broker_code << "." << this->gen_response_location.session_id << ".STATUS_EX"));
    }
    /*static*/  mtk::t_qpid_address  CF_ST_EX::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  CF_ST_EX::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {


