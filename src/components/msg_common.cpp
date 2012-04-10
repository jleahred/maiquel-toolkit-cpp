
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_common.h"

namespace mtk { 
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


sub_location::sub_location (   const std::string&  _broker_code,   const std::string&  _machine)
    :     broker_code(_broker_code),   machine(_machine) 
       
    {  
    }



void  sub_location::check_recomended(void) const
{

}

void sub_location::before_send(void) const
{

}




sub_process_info::sub_process_info (   const sub_location&  _location,   const std::string&  _process_name,   const std::string&  _process_uuid,   const std::string&  _version,   const mtk::nullable<std::string>&  _cli_srv)
    :     location(_location),   process_name(_process_name),   process_uuid(_process_uuid),   version(_version),   cli_srv(_cli_srv) 
       
    {  
    }



void  sub_process_info::check_recomended(void) const
{

    if (cli_srv.HasValue() == false)
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(10)) // I know it's for all instances
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_recomended", "sub_full_product_info::check_recomended  missing recomended field **cli_srv** on sub_process_info", mtk::alPriorError));
        MTK_END_EXEC_MAX_FREC

}

void sub_process_info::before_send(void) const
{

}




sub_control_fluct::sub_control_fluct (   const std::string&  _key,   const mtk::DateTime&  _datetime)
    :     key(_key),   datetime(_datetime) 
       
    {  
    }



void  sub_control_fluct::check_recomended(void) const
{

}

void sub_control_fluct::before_send(void) const
{

}




sub_request_id::sub_request_id (   const std::string&  _session_id,   const std::string&  _req_code)
    :     session_id(_session_id),   req_code(_req_code) 
       
    {  
    }



void  sub_request_id::check_recomended(void) const
{

}

void sub_request_id::before_send(void) const
{

}




sub_request_info::sub_request_info (   const sub_request_id&  _req_id,   const sub_process_info&  _process_info)
    :     req_id(_req_id),   process_info(_process_info) 
       
    {  
    }



void  sub_request_info::check_recomended(void) const
{

}

void sub_request_info::before_send(void) const
{

}




sub_r_response::sub_r_response (   const sub_process_info&  _process_info,   const sub_request_info&  _request_info,   const int16_t&  _seq_number,   const bool&  _is_last_response)
    :     process_info(_process_info),   request_info(_request_info),   seq_number(_seq_number),   is_last_response(_is_last_response) 
       
    {  
    }



void  sub_r_response::check_recomended(void) const
{

}

void sub_r_response::before_send(void) const
{

}




sub_gen_response_location::sub_gen_response_location (   const std::string&  _session_id,   const std::string&  _broker_code)
    :     session_id(_session_id),   broker_code(_broker_code) 
       
    {  
    }



void  sub_gen_response_location::check_recomended(void) const
{

}

void sub_gen_response_location::before_send(void) const
{

}




sub_product_code::sub_product_code (   const std::string&  _market,   const std::string&  _product)
    :     market(_market),   product(_product) 
       
    {  
    }



void  sub_product_code::check_recomended(void) const
{

}

void sub_product_code::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const sub_location & c)
{
    o << "{ "

        << "broker_code:"<<   c.broker_code << "  "        << "machine:"<<   c.machine << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_location & c)
{
    o << YAML::BeginMap

        << YAML::Key << "broker_code"  << YAML::Value <<   c.broker_code        << YAML::Key << "machine"  << YAML::Value <<   c.machine
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_location & c)
{


        node["broker_code"]  >> c.broker_code;
        node["machine"]  >> c.machine;


};


std::ostream& operator<< (std::ostream& o, const sub_process_info & c)
{
    o << "{ "

        << "location:"<< c.location<<"  "        << "process_name:"<<   c.process_name << "  "        << "process_uuid:"<<   c.process_uuid << "  "        << "version:"<<   c.version << "  "        << "cli_srv:"<<   c.cli_srv << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_process_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "location"  << YAML::Value << c.location        << YAML::Key << "process_name"  << YAML::Value <<   c.process_name        << YAML::Key << "process_uuid"  << YAML::Value <<   c.process_uuid        << YAML::Key << "version"  << YAML::Value <<   c.version        << YAML::Key << "cli_srv"  << YAML::Value <<   c.cli_srv
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_process_info & c)
{


        node["location"]  >> c.location;
        node["process_name"]  >> c.process_name;
        node["process_uuid"]  >> c.process_uuid;
        node["version"]  >> c.version;
        node["cli_srv"]  >> c.cli_srv;


};


std::ostream& operator<< (std::ostream& o, const sub_control_fluct & c)
{
    o << "{ "

        << "key:"<<   c.key << "  "        << "datetime:"<<   c.datetime << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_control_fluct & c)
{
    o << YAML::BeginMap

        << YAML::Key << "key"  << YAML::Value <<   c.key        << YAML::Key << "datetime"  << YAML::Value <<   c.datetime
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_control_fluct & c)
{


        node["key"]  >> c.key;
        node["datetime"]  >> c.datetime;


};


std::ostream& operator<< (std::ostream& o, const sub_request_id & c)
{
    o << "{ "

        << "session_id:"<<   c.session_id << "  "        << "req_code:"<<   c.req_code << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_request_id & c)
{
    o << YAML::BeginMap

        << YAML::Key << "session_id"  << YAML::Value <<   c.session_id        << YAML::Key << "req_code"  << YAML::Value <<   c.req_code
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_request_id & c)
{


        node["session_id"]  >> c.session_id;
        node["req_code"]  >> c.req_code;


};


std::ostream& operator<< (std::ostream& o, const sub_request_info & c)
{
    o << "{ "

        << "req_id:"<< c.req_id<<"  "        << "process_info:"<< c.process_info<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_request_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "req_id"  << YAML::Value << c.req_id        << YAML::Key << "process_info"  << YAML::Value << c.process_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_request_info & c)
{


        node["req_id"]  >> c.req_id;
        node["process_info"]  >> c.process_info;


};


std::ostream& operator<< (std::ostream& o, const sub_r_response & c)
{
    o << "{ "

        << "process_info:"<< c.process_info<<"  "        << "request_info:"<< c.request_info<<"  "        << "seq_number:"<<   c.seq_number << "  "        << "is_last_response:"<< c.is_last_response<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_r_response & c)
{
    o << YAML::BeginMap

        << YAML::Key << "process_info"  << YAML::Value << c.process_info        << YAML::Key << "request_info"  << YAML::Value << c.request_info        << YAML::Key << "seq_number"  << YAML::Value <<   c.seq_number        << YAML::Key << "is_last_response"  << YAML::Value << c.is_last_response
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_r_response & c)
{


        node["process_info"]  >> c.process_info;
        node["request_info"]  >> c.request_info;
        node["seq_number"]  >> c.seq_number;
        node["is_last_response"]  >> c.is_last_response;


};


std::ostream& operator<< (std::ostream& o, const sub_gen_response_location & c)
{
    o << "{ "

        << "session_id:"<<   c.session_id << "  "        << "broker_code:"<<   c.broker_code << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_gen_response_location & c)
{
    o << YAML::BeginMap

        << YAML::Key << "session_id"  << YAML::Value <<   c.session_id        << YAML::Key << "broker_code"  << YAML::Value <<   c.broker_code
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_gen_response_location & c)
{


        node["session_id"]  >> c.session_id;
        node["broker_code"]  >> c.broker_code;


};


std::ostream& operator<< (std::ostream& o, const sub_product_code & c)
{
    o << "{ "

        << "market:"<<   c.market << "  "        << "product:"<<   c.product << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_product_code & c)
{
    o << YAML::BeginMap

        << YAML::Key << "market"  << YAML::Value <<   c.market        << YAML::Key << "product"  << YAML::Value <<   c.product
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_product_code & c)
{


        node["market"]  >> c.market;
        node["product"]  >> c.product;


};


bool operator< (const sub_request_id& a, const sub_request_id& b)
{
    if (false)   return true;
    else if (true)
    {
        auto ca = mtk::make_tuple( 0          , a.session_id       , a.req_code );
        auto cb = mtk::make_tuple( 0          , b.session_id       , b.req_code );
        return ca < cb;
    }
    else
        return false;
};


bool operator== (const sub_location& a, const sub_location& b)
{
    return (          a.broker_code ==  b.broker_code  &&          a.machine ==  b.machine  &&   true  );
};

bool operator!= (const sub_location& a, const sub_location& b)
{
    return !(a==b);
};



bool operator== (const sub_process_info& a, const sub_process_info& b)
{
    return (          a.location ==  b.location  &&          a.process_name ==  b.process_name  &&          a.process_uuid ==  b.process_uuid  &&          a.version ==  b.version  &&          a.cli_srv ==  b.cli_srv  &&   true  );
};

bool operator!= (const sub_process_info& a, const sub_process_info& b)
{
    return !(a==b);
};



bool operator== (const sub_control_fluct& a, const sub_control_fluct& b)
{
    return (          a.key ==  b.key  &&          a.datetime ==  b.datetime  &&   true  );
};

bool operator!= (const sub_control_fluct& a, const sub_control_fluct& b)
{
    return !(a==b);
};



bool operator== (const sub_request_id& a, const sub_request_id& b)
{
    return (          a.session_id ==  b.session_id  &&          a.req_code ==  b.req_code  &&   true  );
};

bool operator!= (const sub_request_id& a, const sub_request_id& b)
{
    return !(a==b);
};



bool operator== (const sub_request_info& a, const sub_request_info& b)
{
    return (          a.req_id ==  b.req_id  &&          a.process_info ==  b.process_info  &&   true  );
};

bool operator!= (const sub_request_info& a, const sub_request_info& b)
{
    return !(a==b);
};



bool operator== (const sub_r_response& a, const sub_r_response& b)
{
    return (          a.process_info ==  b.process_info  &&          a.request_info ==  b.request_info  &&          a.seq_number ==  b.seq_number  &&          a.is_last_response ==  b.is_last_response  &&   true  );
};

bool operator!= (const sub_r_response& a, const sub_r_response& b)
{
    return !(a==b);
};



bool operator== (const sub_gen_response_location& a, const sub_gen_response_location& b)
{
    return (          a.session_id ==  b.session_id  &&          a.broker_code ==  b.broker_code  &&   true  );
};

bool operator!= (const sub_gen_response_location& a, const sub_gen_response_location& b)
{
    return !(a==b);
};



bool operator== (const sub_product_code& a, const sub_product_code& b)
{
    return (          a.market ==  b.market  &&          a.product ==  b.product  &&   true  );
};

bool operator!= (const sub_product_code& a, const sub_product_code& b)
{
    return !(a==b);
};




void  copy (sub_location& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("bc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field broker_code on message sub_location::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.broker_code, it->second);
                        //c.broker_code = it->second;
//   field_type

                    it = mv.find("mc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field machine on message sub_location::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.machine, it->second);
                        //c.machine = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_location& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.broker_code, std::string("bc"));
//  field_type
        __internal_add2map(map, a.machine, std::string("mc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_location>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (sub_process_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("lc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field location on message sub_process_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.location, it->second);
                        //__internal_qpid_fill(c.location, it->second.asMap());
//   field_type

                    it = mv.find("pn");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field process_name on message sub_process_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_name, it->second);
                        //c.process_name = it->second;
//   field_type

                    it = mv.find("pui");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field process_uuid on message sub_process_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_uuid, it->second);
                        //c.process_uuid = it->second;
//   field_type

                    it = mv.find("ver");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field version on message sub_process_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.version, it->second);
                        //c.version = it->second;
//   field_type

                    it = mv.find("c_s");
                    if (it!= mv.end())
                        copy(c.cli_srv, it->second);
                        //c.cli_srv = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_process_info& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.location, std::string("lc"));
//  field_type
        __internal_add2map(map, a.process_name, std::string("pn"));
//  field_type
        __internal_add2map(map, a.process_uuid, std::string("pui"));
//  field_type
        __internal_add2map(map, a.version, std::string("ver"));
if (a.cli_srv.HasValue())
//  field_type
        __internal_add2map(map, a.cli_srv, std::string("c_s"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_process_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (sub_control_fluct& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("k");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field key on message sub_control_fluct::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.key, it->second);
                        //c.key = it->second;
//   field_type

                    it = mv.find("dt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field datetime on message sub_control_fluct::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.datetime, it->second);
                        //c.datetime = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_control_fluct& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.key, std::string("k"));
//  field_type
        __internal_add2map(map, a.datetime, std::string("dt"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_control_fluct>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (sub_request_id& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("sid");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field session_id on message sub_request_id::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.session_id, it->second);
                        //c.session_id = it->second;
//   field_type

                    it = mv.find("rqc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field req_code on message sub_request_id::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.req_code, it->second);
                        //c.req_code = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_request_id& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.session_id, std::string("sid"));
//  field_type
        __internal_add2map(map, a.req_code, std::string("rqc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_request_id>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (sub_request_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rqid");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field req_id on message sub_request_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.req_id, it->second);
                        //__internal_qpid_fill(c.req_id, it->second.asMap());
//   sub_msg_type

                    it = mv.find("pi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field process_info on message sub_request_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_info, it->second);
                        //__internal_qpid_fill(c.process_info, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_request_info& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.req_id, std::string("rqid"));
//  sub_msg_type
        __internal_add2map(map, a.process_info, std::string("pi"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_request_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (sub_r_response& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field process_info on message sub_r_response::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_info, it->second);
                        //__internal_qpid_fill(c.process_info, it->second.asMap());
//   sub_msg_type

                    it = mv.find("rqi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_info on message sub_r_response::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_info, it->second);
                        //__internal_qpid_fill(c.request_info, it->second.asMap());
//   field_type

                    it = mv.find("sqn");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field seq_number on message sub_r_response::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.seq_number, it->second);
                        //c.seq_number = it->second;
//   sub_msg_type

                    it = mv.find("lr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field is_last_response on message sub_r_response::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.is_last_response, it->second);
                        //__internal_qpid_fill(c.is_last_response, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_r_response& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.process_info, std::string("pi"));
//  sub_msg_type
        __internal_add2map(map, a.request_info, std::string("rqi"));
//  field_type
        __internal_add2map(map, a.seq_number, std::string("sqn"));
//  sub_msg_type
        __internal_add2map(map, a.is_last_response, std::string("lr"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_r_response>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (sub_gen_response_location& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("sid");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field session_id on message sub_gen_response_location::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.session_id, it->second);
                        //c.session_id = it->second;
//   field_type

                    it = mv.find("bc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field broker_code on message sub_gen_response_location::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.broker_code, it->second);
                        //c.broker_code = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_gen_response_location& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.session_id, std::string("sid"));
//  field_type
        __internal_add2map(map, a.broker_code, std::string("bc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_gen_response_location>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (sub_product_code& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("mk");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field market on message sub_product_code::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.market, it->second);
                        //c.market = it->second;
//   field_type

                    it = mv.find("pr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field product on message sub_product_code::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.product, it->second);
                        //c.product = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_product_code& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.market, std::string("mk"));
//  field_type
        __internal_add2map(map, a.product, std::string("pr"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_product_code>& a, const std::string& field)
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

    sub_location  __internal_get_default(sub_location*)
    {
        return sub_location(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    sub_process_info  __internal_get_default(sub_process_info*)
    {
        return sub_process_info(
//   sub_msg_type
   __internal_get_default((sub_location*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   mtk::nullable<std::string>()
            );
    }
    
    sub_control_fluct  __internal_get_default(sub_control_fluct*)
    {
        return sub_control_fluct(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((mtk::DateTime*)0)
            );
    }
    
    sub_request_id  __internal_get_default(sub_request_id*)
    {
        return sub_request_id(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    sub_request_info  __internal_get_default(sub_request_info*)
    {
        return sub_request_info(
//   sub_msg_type
   __internal_get_default((sub_request_id*)0),
//   sub_msg_type
   __internal_get_default((sub_process_info*)0)
            );
    }
    
    sub_r_response  __internal_get_default(sub_r_response*)
    {
        return sub_r_response(
//   sub_msg_type
   __internal_get_default((sub_process_info*)0),
//   sub_msg_type
   __internal_get_default((sub_request_info*)0),
//   field_type
   __internal_get_default ((int16_t*)0),
//   sub_msg_type
   __internal_get_default((bool*)0)
            );
    }
    
    sub_gen_response_location  __internal_get_default(sub_gen_response_location*)
    {
        return sub_gen_response_location(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    sub_product_code  __internal_get_default(sub_product_code*)
    {
        return sub_product_code(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
sub_location::sub_location (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   broker_code(__internal_get_default((std::string*)0)),
//   field_type
   machine(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

sub_process_info::sub_process_info (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   location(__internal_get_default((sub_location*)0)),
//   field_type
   process_name(__internal_get_default((std::string*)0)),
//   field_type
   process_uuid(__internal_get_default((std::string*)0)),
//   field_type
   version(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

sub_control_fluct::sub_control_fluct (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   key(__internal_get_default((std::string*)0)),
//   field_type
   datetime(__internal_get_default((mtk::DateTime*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

sub_request_id::sub_request_id (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   session_id(__internal_get_default((std::string*)0)),
//   field_type
   req_code(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

sub_request_info::sub_request_info (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   req_id(__internal_get_default((sub_request_id*)0)),
//   sub_msg_type
   process_info(__internal_get_default((sub_process_info*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

sub_r_response::sub_r_response (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   process_info(__internal_get_default((sub_process_info*)0)),
//   sub_msg_type
   request_info(__internal_get_default((sub_request_info*)0)),
//   field_type
   seq_number(__internal_get_default((int16_t*)0)),
//   sub_msg_type
   is_last_response(__internal_get_default((bool*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

sub_gen_response_location::sub_gen_response_location (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   session_id(__internal_get_default((std::string*)0)),
//   field_type
   broker_code(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

sub_product_code::sub_product_code (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   market(__internal_get_default((std::string*)0)),
//   field_type
   product(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


};   //namespace mtk {
};   //namespace msg {


