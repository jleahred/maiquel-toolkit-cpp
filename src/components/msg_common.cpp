
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
            //qpid::types::Variant::Map m;
            //__internal_add2map(m, *it);
            list.push_back(*it);
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


sub_location::sub_location (   const std::string&  _client_code,   const std::string&  _machine)
    :     client_code(_client_code),   machine(_machine) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_location::check_recomended(void) const
{
    std::string result;

    return result;
}



sub_process_location::sub_process_location (   const sub_location&  _location,   const std::string&  _process_name,   const std::string&  _process_uuid)
    :     location(_location),   process_name(_process_name),   process_uuid(_process_uuid) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_process_location::check_recomended(void) const
{
    std::string result;

    return result;
}



sub_process_info::sub_process_info (   const sub_process_location&  _process_location,   const std::string&  _version)
    :     process_location(_process_location),   version(_version) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_process_info::check_recomended(void) const
{
    std::string result;

    return result;
}



sub_request_id::sub_request_id (   const std::string&  _sess_id,   const std::string&  _req_code)
    :     sess_id(_sess_id),   req_code(_req_code) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_request_id::check_recomended(void) const
{
    std::string result;

    return result;
}



sub_request_info::sub_request_info (   const sub_request_id&  _req_id,   const sub_process_location&  _process_location)
    :     req_id(_req_id),   process_location(_process_location) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_request_info::check_recomended(void) const
{
    std::string result;

    return result;
}



sub_r_response::sub_r_response (   const sub_request_info&  _request_info,   const int16_t&  _sec_number,   const bool&  _is_last_response)
    :     request_info(_request_info),   sec_number(_sec_number),   is_last_response(_is_last_response) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_r_response::check_recomended(void) const
{
    std::string result;

    return result;
}



sub_single_product_code::sub_single_product_code (   const std::string&  _market,   const std::string&  _product)
    :     market(_market),   product(_product) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_single_product_code::check_recomended(void) const
{
    std::string result;

    return result;
}



sub_sys_product_code::sub_sys_product_code ( const sub_single_product_code&  parent,   const std::string&  _user_name)
    :  sub_single_product_code(parent),   user_name(_user_name) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_sys_product_code::check_recomended(void) const
{
    std::string result;

    return result;
}



sub_adic_product_code::sub_adic_product_code ( const sub_single_product_code&  parent,   const std::string&  _aditional_code_type)
    :  sub_single_product_code(parent),   aditional_code_type(_aditional_code_type) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_adic_product_code::check_recomended(void) const
{
    std::string result;

    return result;
}



sub_product_code::sub_product_code (   const sub_sys_product_code&  _sys_code,   const mtk::nullable<sub_adic_product_code>&  _aditional_code)
    :     sys_code(_sys_code),   aditional_code(_aditional_code) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_product_code::check_recomended(void) const
{
    std::string result;

    return result;
}


std::ostream& operator<< (std::ostream& o, const sub_location & c)
{
    o << "{ "

        << "client_code:"<<   c.client_code << "  "        << "machine:"<<   c.machine << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const sub_process_location & c)
{
    o << "{ "

        << "location:"<< c.location<<"  "        << "process_name:"<<   c.process_name << "  "        << "process_uuid:"<<   c.process_uuid << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const sub_process_info & c)
{
    o << "{ "

        << "process_location:"<< c.process_location<<"  "        << "version:"<<   c.version << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const sub_request_id & c)
{
    o << "{ "

        << "sess_id:"<<   c.sess_id << "  "        << "req_code:"<<   c.req_code << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const sub_request_info & c)
{
    o << "{ "

        << "req_id:"<< c.req_id<<"  "        << "process_location:"<< c.process_location<<"  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const sub_r_response & c)
{
    o << "{ "

        << "request_info:"<< c.request_info<<"  "        << "sec_number:"<<   c.sec_number << "  "        << "is_last_response:"<< c.is_last_response<<"  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const sub_single_product_code & c)
{
    o << "{ "

        << "market:"<<   c.market << "  "        << "product:"<<   c.product << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const sub_sys_product_code & c)
{
    o << "{ "
    << "("  <<  static_cast<const sub_single_product_code&>(c)  << ")" 
        << "user_name:"<<   c.user_name << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const sub_adic_product_code & c)
{
    o << "{ "
    << "("  <<  static_cast<const sub_single_product_code&>(c)  << ")" 
        << "aditional_code_type:"<<   c.aditional_code_type << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const sub_product_code & c)
{
    o << "{ "

        << "sys_code:"<< c.sys_code<<"  "        << "aditional_code:"<< c.aditional_code<<"  "
        << " }";
    return o;
};



bool operator== (const sub_location& a, const sub_location& b)
{
    return (          a.client_code ==  b.client_code  &&          a.machine ==  b.machine  &&   true  );
};

bool operator!= (const sub_location& a, const sub_location& b)
{
    return !(a==b);
};



bool operator== (const sub_process_location& a, const sub_process_location& b)
{
    return (          a.location ==  b.location  &&          a.process_name ==  b.process_name  &&          a.process_uuid ==  b.process_uuid  &&   true  );
};

bool operator!= (const sub_process_location& a, const sub_process_location& b)
{
    return !(a==b);
};



bool operator== (const sub_process_info& a, const sub_process_info& b)
{
    return (          a.process_location ==  b.process_location  &&          a.version ==  b.version  &&   true  );
};

bool operator!= (const sub_process_info& a, const sub_process_info& b)
{
    return !(a==b);
};



bool operator== (const sub_request_id& a, const sub_request_id& b)
{
    return (          a.sess_id ==  b.sess_id  &&          a.req_code ==  b.req_code  &&   true  );
};

bool operator!= (const sub_request_id& a, const sub_request_id& b)
{
    return !(a==b);
};



bool operator== (const sub_request_info& a, const sub_request_info& b)
{
    return (          a.req_id ==  b.req_id  &&          a.process_location ==  b.process_location  &&   true  );
};

bool operator!= (const sub_request_info& a, const sub_request_info& b)
{
    return !(a==b);
};



bool operator== (const sub_r_response& a, const sub_r_response& b)
{
    return (          a.request_info ==  b.request_info  &&          a.sec_number ==  b.sec_number  &&          a.is_last_response ==  b.is_last_response  &&   true  );
};

bool operator!= (const sub_r_response& a, const sub_r_response& b)
{
    return !(a==b);
};



bool operator== (const sub_single_product_code& a, const sub_single_product_code& b)
{
    return (          a.market ==  b.market  &&          a.product ==  b.product  &&   true  );
};

bool operator!= (const sub_single_product_code& a, const sub_single_product_code& b)
{
    return !(a==b);
};



bool operator== (const sub_sys_product_code& a, const sub_sys_product_code& b)
{
    return ( (static_cast<const sub_single_product_code&>(a)   ==  static_cast<const sub_single_product_code&>(b))  &&           a.user_name ==  b.user_name  &&   true  );
};

bool operator!= (const sub_sys_product_code& a, const sub_sys_product_code& b)
{
    return !(a==b);
};



bool operator== (const sub_adic_product_code& a, const sub_adic_product_code& b)
{
    return ( (static_cast<const sub_single_product_code&>(a)   ==  static_cast<const sub_single_product_code&>(b))  &&           a.aditional_code_type ==  b.aditional_code_type  &&   true  );
};

bool operator!= (const sub_adic_product_code& a, const sub_adic_product_code& b)
{
    return !(a==b);
};



bool operator== (const sub_product_code& a, const sub_product_code& b)
{
    return (          a.sys_code ==  b.sys_code  &&          a.aditional_code ==  b.aditional_code  &&   true  );
};

bool operator!= (const sub_product_code& a, const sub_product_code& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (sub_location& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_location& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("cc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field client_code on message sub_location::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.client_code, it->second);
                        //c.client_code = it->second;
//   field_type

                    it = mv.find("mc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field machine on message sub_location::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.machine, it->second);
                        //c.machine = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_location& a)
{
    

//  field_type
        __internal_add2map(map, a.client_code, std::string("cc"));
//  field_type
        __internal_add2map(map, a.machine, std::string("mc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_location>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_process_location& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_process_location& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("l");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field location on message sub_process_location::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.location, it->second);
                        //__internal_qpid_fill(c.location, it->second.asMap());
//   field_type

                    it = mv.find("pn");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field process_name on message sub_process_location::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_name, it->second);
                        //c.process_name = it->second;
//   field_type

                    it = mv.find("pi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field process_uuid on message sub_process_location::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_uuid, it->second);
                        //c.process_uuid = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_process_location& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.location, std::string("l"));
//  field_type
        __internal_add2map(map, a.process_name, std::string("pn"));
//  field_type
        __internal_add2map(map, a.process_uuid, std::string("pi"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_process_location>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_process_info& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_process_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field process_location on message sub_process_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_location, it->second);
                        //__internal_qpid_fill(c.process_location, it->second.asMap());
//   field_type

                    it = mv.find("pv");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field version on message sub_process_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.version, it->second);
                        //c.version = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_process_info& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.process_location, std::string("pl"));
//  field_type
        __internal_add2map(map, a.version, std::string("pv"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_process_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_request_id& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_request_id& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("sid");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field sess_id on message sub_request_id::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.sess_id, it->second);
                        //c.sess_id = it->second;
//   field_type

                    it = mv.find("rqc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field req_code on message sub_request_id::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.req_code, it->second);
                        //c.req_code = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_request_id& a)
{
    

//  field_type
        __internal_add2map(map, a.sess_id, std::string("sid"));
//  field_type
        __internal_add2map(map, a.req_code, std::string("rqc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_request_id>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_request_info& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_request_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rid");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field req_id on message sub_request_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.req_id, it->second);
                        //__internal_qpid_fill(c.req_id, it->second.asMap());
//   sub_msg_type

                    it = mv.find("pl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field process_location on message sub_request_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_location, it->second);
                        //__internal_qpid_fill(c.process_location, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_request_info& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.req_id, std::string("rid"));
//  sub_msg_type
        __internal_add2map(map, a.process_location, std::string("pl"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_request_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_r_response& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_r_response& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("ri");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field request_info on message sub_r_response::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_info, it->second);
                        //__internal_qpid_fill(c.request_info, it->second.asMap());
//   field_type

                    it = mv.find("sq");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field sec_number on message sub_r_response::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.sec_number, it->second);
                        //c.sec_number = it->second;
//   sub_msg_type

                    it = mv.find("lr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field is_last_response on message sub_r_response::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.is_last_response, it->second);
                        //__internal_qpid_fill(c.is_last_response, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_r_response& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.request_info, std::string("ri"));
//  field_type
        __internal_add2map(map, a.sec_number, std::string("sq"));
//  sub_msg_type
        __internal_add2map(map, a.is_last_response, std::string("lr"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_r_response>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_single_product_code& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_single_product_code& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("mk");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field market on message sub_single_product_code::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.market, it->second);
                        //c.market = it->second;
//   field_type

                    it = mv.find("pr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field product on message sub_single_product_code::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.product, it->second);
                        //c.product = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_single_product_code& a)
{
    

//  field_type
        __internal_add2map(map, a.market, std::string("mk"));
//  field_type
        __internal_add2map(map, a.product, std::string("pr"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_single_product_code>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_sys_product_code& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_sys_product_code& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<sub_single_product_code&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("un");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field user_name on message sub_sys_product_code::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.user_name, it->second);
                        //c.user_name = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_sys_product_code& a)
{
    
//  parent
__internal_add2map(map, static_cast<const sub_single_product_code&>(a));

//  field_type
        __internal_add2map(map, a.user_name, std::string("un"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_sys_product_code>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_adic_product_code& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_adic_product_code& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<sub_single_product_code&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("act");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field aditional_code_type on message sub_adic_product_code::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.aditional_code_type, it->second);
                        //c.aditional_code_type = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_adic_product_code& a)
{
    
//  parent
__internal_add2map(map, static_cast<const sub_single_product_code&>(a));

//  field_type
        __internal_add2map(map, a.aditional_code_type, std::string("act"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_adic_product_code>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_product_code& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_product_code& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("spc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field sys_code on message sub_product_code::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.sys_code, it->second);
                        //__internal_qpid_fill(c.sys_code, it->second.asMap());
//   sub_msg_type

                    it = mv.find("apc");
                    if (it!= mv.end())
                        copy(c.aditional_code, it->second);
                        //__internal_qpid_fill(c.aditional_code, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_product_code& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.sys_code, std::string("spc"));
if (a.aditional_code.HasValue())
//  sub_msg_type
        __internal_add2map(map, a.aditional_code, std::string("apc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_product_code>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)

qpid::messaging::Message sub_location::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  field_type
//        content["cc"] = this->client_code;
        __internal_add2map(content, this->client_code, std::string("cc"));
//  field_type
//        content["mc"] = this->machine;
        __internal_add2map(content, this->machine, std::string("mc"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message sub_process_location::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["l"] =  qpidmsg_coded_as_qpid_Map(this->location);
        __internal_add2map(content, this->location, std::string("l"));
//  field_type
//        content["pn"] = this->process_name;
        __internal_add2map(content, this->process_name, std::string("pn"));
//  field_type
//        content["pi"] = this->process_uuid;
        __internal_add2map(content, this->process_uuid, std::string("pi"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message sub_process_info::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["pl"] =  qpidmsg_coded_as_qpid_Map(this->process_location);
        __internal_add2map(content, this->process_location, std::string("pl"));
//  field_type
//        content["pv"] = this->version;
        __internal_add2map(content, this->version, std::string("pv"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message sub_request_id::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  field_type
//        content["sid"] = this->sess_id;
        __internal_add2map(content, this->sess_id, std::string("sid"));
//  field_type
//        content["rqc"] = this->req_code;
        __internal_add2map(content, this->req_code, std::string("rqc"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message sub_request_info::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["rid"] =  qpidmsg_coded_as_qpid_Map(this->req_id);
        __internal_add2map(content, this->req_id, std::string("rid"));
//  sub_msg_type
//        content["pl"] =  qpidmsg_coded_as_qpid_Map(this->process_location);
        __internal_add2map(content, this->process_location, std::string("pl"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message sub_r_response::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["ri"] =  qpidmsg_coded_as_qpid_Map(this->request_info);
        __internal_add2map(content, this->request_info, std::string("ri"));
//  field_type
//        content["sq"] = this->sec_number;
        __internal_add2map(content, this->sec_number, std::string("sq"));
//  sub_msg_type
//        content["lr"] =  qpidmsg_coded_as_qpid_Map(this->is_last_response);
        __internal_add2map(content, this->is_last_response, std::string("lr"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message sub_single_product_code::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  field_type
//        content["mk"] = this->market;
        __internal_add2map(content, this->market, std::string("mk"));
//  field_type
//        content["pr"] = this->product;
        __internal_add2map(content, this->product, std::string("pr"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message sub_sys_product_code::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const sub_single_product_code&>(*this));

//  field_type
//        content["un"] = this->user_name;
        __internal_add2map(content, this->user_name, std::string("un"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message sub_adic_product_code::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const sub_single_product_code&>(*this));

//  field_type
//        content["act"] = this->aditional_code_type;
        __internal_add2map(content, this->aditional_code_type, std::string("act"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message sub_product_code::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["spc"] =  qpidmsg_coded_as_qpid_Map(this->sys_code);
        __internal_add2map(content, this->sys_code, std::string("spc"));
//if (this->aditional_code.HasValue())
//  sub_msg_type
//        content["apc"] =  qpidmsg_coded_as_qpid_Map(this->aditional_code);
        __internal_add2map(content, this->aditional_code, std::string("apc"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




    sub_location  __internal_get_default(sub_location*)
    {
        return sub_location(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    sub_process_location  __internal_get_default(sub_process_location*)
    {
        return sub_process_location(
//   sub_msg_type
   __internal_get_default((sub_location*)0),
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
   __internal_get_default((sub_process_location*)0),
//   field_type
   __internal_get_default ((std::string*)0)
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
   __internal_get_default((sub_process_location*)0)
            );
    }
    
    sub_r_response  __internal_get_default(sub_r_response*)
    {
        return sub_r_response(
//   sub_msg_type
   __internal_get_default((sub_request_info*)0),
//   field_type
   __internal_get_default ((int16_t*)0),
//   sub_msg_type
   __internal_get_default((bool*)0)
            );
    }
    
    sub_single_product_code  __internal_get_default(sub_single_product_code*)
    {
        return sub_single_product_code(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    sub_sys_product_code  __internal_get_default(sub_sys_product_code*)
    {
        return sub_sys_product_code(
__internal_get_default((sub_single_product_code*)0), //   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    sub_adic_product_code  __internal_get_default(sub_adic_product_code*)
    {
        return sub_adic_product_code(
__internal_get_default((sub_single_product_code*)0), //   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    sub_product_code  __internal_get_default(sub_product_code*)
    {
        return sub_product_code(
//   sub_msg_type
   __internal_get_default((sub_sys_product_code*)0),
//   sub_msg_type
   mtk::nullable<sub_adic_product_code>()
            );
    }
    

sub_location::sub_location (const qpid::messaging::Message& msg)
    :  //   field_type
   client_code(__internal_get_default((std::string*)0)),
//   field_type
   machine(__internal_get_default((std::string*)0)) 
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



sub_process_location::sub_process_location (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   location(__internal_get_default((sub_location*)0)),
//   field_type
   process_name(__internal_get_default((std::string*)0)),
//   field_type
   process_uuid(__internal_get_default((std::string*)0)) 
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



sub_process_info::sub_process_info (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   process_location(__internal_get_default((sub_process_location*)0)),
//   field_type
   version(__internal_get_default((std::string*)0)) 
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



sub_request_id::sub_request_id (const qpid::messaging::Message& msg)
    :  //   field_type
   sess_id(__internal_get_default((std::string*)0)),
//   field_type
   req_code(__internal_get_default((std::string*)0)) 
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



sub_request_info::sub_request_info (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   req_id(__internal_get_default((sub_request_id*)0)),
//   sub_msg_type
   process_location(__internal_get_default((sub_process_location*)0)) 
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



sub_r_response::sub_r_response (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   request_info(__internal_get_default((sub_request_info*)0)),
//   field_type
   sec_number(__internal_get_default((int16_t*)0)),
//   sub_msg_type
   is_last_response(__internal_get_default((bool*)0)) 
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



sub_single_product_code::sub_single_product_code (const qpid::messaging::Message& msg)
    :  //   field_type
   market(__internal_get_default((std::string*)0)),
//   field_type
   product(__internal_get_default((std::string*)0)) 
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



sub_sys_product_code::sub_sys_product_code (const qpid::messaging::Message& msg)
    :  sub_single_product_code(msg), //   field_type
   user_name(__internal_get_default((std::string*)0)) 
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



sub_adic_product_code::sub_adic_product_code (const qpid::messaging::Message& msg)
    :  sub_single_product_code(msg), //   field_type
   aditional_code_type(__internal_get_default((std::string*)0)) 
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



sub_product_code::sub_product_code (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   sys_code(__internal_get_default((sub_sys_product_code*)0)) 
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



};   //namespace mtk {
};   //namespace msg {


