
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_account_manager.h"

namespace mtk { 
namespace trd { 
namespace account { 
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


sub_grant::sub_grant (   const IC_key&  _key,   const std::string&  _type)
    :     key(_key),   type(_type) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_grant::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_grant::before_send(void) const
{

}




sub_grant::IC_key::IC_key (   const std::string&  _market,   const mtk::trd::msg::sub_account_info&  _account)
    :     market(_market),   account(_account) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_grant::IC_key::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_grant::IC_key::before_send(void) const
{

}




rq_accounts::rq_accounts (   const mtk::msg::sub_request_info&  _request_info)
    :     request_info(_request_info) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string rq_accounts::check_recomended(void) const
{
    std::string result;

    return result;
}

void rq_accounts::before_send(void) const
{

}




conf_add_accounts::conf_add_accounts (   const mtk::msg::sub_gen_response_location&  _gen_response_location,   const mtk::list<sub_grant >&  _grant_list)
    :     gen_response_location(_gen_response_location),   grant_list(_grant_list) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string conf_add_accounts::check_recomended(void) const
{
    std::string result;

    return result;
}

void conf_add_accounts::before_send(void) const
{

}




pub_accmgr_init::pub_accmgr_init (   const mtk::msg::sub_process_info&  _process_info,   const std::string&  _request_sufix_subjetc)
    :     process_info(_process_info),   request_sufix_subjetc(_request_sufix_subjetc) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string pub_accmgr_init::check_recomended(void) const
{
    std::string result;

    return result;
}

void pub_accmgr_init::before_send(void) const
{

}




rq_accounts_oninit::rq_accounts_oninit (   const mtk::msg::sub_request_info&  _request_info,   const std::string&  _request_sufix_subjetc)
    :     request_info(_request_info),   request_sufix_subjetc(_request_sufix_subjetc) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string rq_accounts_oninit::check_recomended(void) const
{
    std::string result;

    return result;
}

void rq_accounts_oninit::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const sub_grant::IC_key & c)
{
    o << "{ "

        << "market:"<<   c.market << "  "        << "account:"<< c.account<<"  "
        << " }";
    return o;
};


std::ostream& operator<< (std::ostream& o, const sub_grant & c)
{
    o << "{ "

        << "key:"<< c.key<<"  "        << "type:"<<   c.type << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_grant::IC_key & c)
{
    o << YAML::BeginMap

        << YAML::Key << "market"  << YAML::Value <<   c.market        << YAML::Key << "account"  << YAML::Value << c.account
        << YAML::EndMap;
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_grant & c)
{
    o << YAML::BeginMap

        << YAML::Key << "key"   << YAML::Value << c.key        << YAML::Key << "type"  << YAML::Value <<   c.type
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_grant::IC_key & c)
{


        node["market"]  >> c.market;
        node["account"]  >> c.account;


};



void  operator >> (const YAML::Node& node, sub_grant & c)
{


            node["key"]   >> c.key;
        node["type"]  >> c.type;


};


std::ostream& operator<< (std::ostream& o, const rq_accounts & c)
{
    o << "{ "

        << "request_info:"<< c.request_info<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const rq_accounts & c)
{
    o << YAML::BeginMap

        << YAML::Key << "request_info"  << YAML::Value << c.request_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, rq_accounts & c)
{


        node["request_info"]  >> c.request_info;


};


std::ostream& operator<< (std::ostream& o, const conf_add_accounts & c)
{
    o << "{ "

        << "gen_response_location:"<< c.gen_response_location<<"  "        << "grant_list:"<< c.grant_list<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const conf_add_accounts & c)
{
    o << YAML::BeginMap

        << YAML::Key << "gen_response_location"  << YAML::Value << c.gen_response_location        << YAML::Key << "grant_list"  << YAML::Value << c.grant_list
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, conf_add_accounts & c)
{


        node["gen_response_location"]  >> c.gen_response_location;
        node["grant_list"]  >> c.grant_list;


};


std::ostream& operator<< (std::ostream& o, const pub_accmgr_init & c)
{
    o << "{ "

        << "process_info:"<< c.process_info<<"  "        << "request_sufix_subjetc:"<<   c.request_sufix_subjetc << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const pub_accmgr_init & c)
{
    o << YAML::BeginMap

        << YAML::Key << "process_info"  << YAML::Value << c.process_info        << YAML::Key << "request_sufix_subjetc"  << YAML::Value <<   c.request_sufix_subjetc
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, pub_accmgr_init & c)
{


        node["process_info"]  >> c.process_info;
        node["request_sufix_subjetc"]  >> c.request_sufix_subjetc;


};


std::ostream& operator<< (std::ostream& o, const rq_accounts_oninit & c)
{
    o << "{ "

        << "request_info:"<< c.request_info<<"  "        << "request_sufix_subjetc:"<<   c.request_sufix_subjetc << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const rq_accounts_oninit & c)
{
    o << YAML::BeginMap

        << YAML::Key << "request_info"  << YAML::Value << c.request_info        << YAML::Key << "request_sufix_subjetc"  << YAML::Value <<   c.request_sufix_subjetc
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, rq_accounts_oninit & c)
{


        node["request_info"]  >> c.request_info;
        node["request_sufix_subjetc"]  >> c.request_sufix_subjetc;


};


bool operator< (const sub_grant::IC_key& a, const sub_grant::IC_key& b)
{
    if (false)   return true;
    else if (true)
    {
        auto ca = mtk::make_tuple( 0          , a.market       , a.account );
        auto cb = mtk::make_tuple( 0          , b.market       , b.account );
        return ca < cb;
    }
    else
        return false;
};


bool operator== (const sub_grant::IC_key& a, const sub_grant::IC_key& b)
{
    return (          a.market ==  b.market  &&          a.account ==  b.account  &&   true  );
};

bool operator!= (const sub_grant::IC_key& a, const sub_grant::IC_key& b)
{
    return !(a==b);
};



bool operator== (const sub_grant& a, const sub_grant& b)
{
    return (          a.key ==  b.key  &&          a.type ==  b.type  &&   true  );
};

bool operator!= (const sub_grant& a, const sub_grant& b)
{
    return !(a==b);
};



bool operator== (const rq_accounts& a, const rq_accounts& b)
{
    return (          a.request_info ==  b.request_info  &&   true  );
};

bool operator!= (const rq_accounts& a, const rq_accounts& b)
{
    return !(a==b);
};



bool operator== (const conf_add_accounts& a, const conf_add_accounts& b)
{
    return (          a.gen_response_location ==  b.gen_response_location  &&          a.grant_list ==  b.grant_list  &&   true  );
};

bool operator!= (const conf_add_accounts& a, const conf_add_accounts& b)
{
    return !(a==b);
};



bool operator== (const pub_accmgr_init& a, const pub_accmgr_init& b)
{
    return (          a.process_info ==  b.process_info  &&          a.request_sufix_subjetc ==  b.request_sufix_subjetc  &&   true  );
};

bool operator!= (const pub_accmgr_init& a, const pub_accmgr_init& b)
{
    return !(a==b);
};



bool operator== (const rq_accounts_oninit& a, const rq_accounts_oninit& b)
{
    return (          a.request_info ==  b.request_info  &&          a.request_sufix_subjetc ==  b.request_sufix_subjetc  &&   true  );
};

bool operator!= (const rq_accounts_oninit& a, const rq_accounts_oninit& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (sub_grant& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_grant& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   IN_MSG

                copy(c.key, mv);
                //__internal_qpid_fill(c.key, mv);
//   field_type

                    it = mv.find("ty");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field type on message sub_grant::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.type, it->second);
                        //c.type = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_grant& a)
{

    a.before_send();


//  IN_MSG
        __internal_add2map(map, a.key);
//  field_type
        __internal_add2map(map, a.type, std::string("ty"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_grant>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_grant::IC_key& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_grant::IC_key& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("mk");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field market on message sub_grant::IC_key::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.market, it->second);
                        //c.market = it->second;
//   sub_msg_type

                    it = mv.find("acc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field account on message sub_grant::IC_key::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.account, it->second);
                        //__internal_qpid_fill(c.account, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_grant::IC_key& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.market, std::string("mk"));
//  sub_msg_type
        __internal_add2map(map, a.account, std::string("acc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_grant::IC_key>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (rq_accounts& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (rq_accounts& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rqi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_info on message rq_accounts::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_info, it->second);
                        //__internal_qpid_fill(c.request_info, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const rq_accounts& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.request_info, std::string("rqi"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<rq_accounts>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (conf_add_accounts& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (conf_add_accounts& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("grl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field gen_response_location on message conf_add_accounts::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.gen_response_location, it->second);
                        //__internal_qpid_fill(c.gen_response_location, it->second.asMap());
//   sub_msg_type

                    it = mv.find("gl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field grant_list on message conf_add_accounts::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.grant_list, it->second);
                        //__internal_qpid_fill(c.grant_list, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const conf_add_accounts& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.gen_response_location, std::string("grl"));
//  sub_msg_type
        __internal_add2map(map, a.grant_list, std::string("gl"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<conf_add_accounts>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (pub_accmgr_init& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (pub_accmgr_init& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field process_info on message pub_accmgr_init::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_info, it->second);
                        //__internal_qpid_fill(c.process_info, it->second.asMap());
//   field_type

                    it = mv.find("rss");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_sufix_subjetc on message pub_accmgr_init::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_sufix_subjetc, it->second);
                        //c.request_sufix_subjetc = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const pub_accmgr_init& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.process_info, std::string("pi"));
//  field_type
        __internal_add2map(map, a.request_sufix_subjetc, std::string("rss"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_accmgr_init>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (rq_accounts_oninit& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (rq_accounts_oninit& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rqi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_info on message rq_accounts_oninit::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_info, it->second);
                        //__internal_qpid_fill(c.request_info, it->second.asMap());
//   field_type

                    it = mv.find("rss");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_sufix_subjetc on message rq_accounts_oninit::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_sufix_subjetc, it->second);
                        //c.request_sufix_subjetc = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const rq_accounts_oninit& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.request_info, std::string("rqi"));
//  field_type
        __internal_add2map(map, a.request_sufix_subjetc, std::string("rss"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<rq_accounts_oninit>& a, const std::string& field)
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

qpid::messaging::Message rq_accounts::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["rqi"] =  qpidmsg_coded_as_qpid_Map(this->request_info);
        __internal_add2map(content, this->request_info, std::string("rqi"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message conf_add_accounts::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["grl"] =  qpidmsg_coded_as_qpid_Map(this->gen_response_location);
        __internal_add2map(content, this->gen_response_location, std::string("grl"));
//  sub_msg_type
//        content["gl"] =  qpidmsg_coded_as_qpid_Map(this->grant_list);
        __internal_add2map(content, this->grant_list, std::string("gl"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message pub_accmgr_init::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["pi"] =  qpidmsg_coded_as_qpid_Map(this->process_info);
        __internal_add2map(content, this->process_info, std::string("pi"));
//  field_type
//        content["rss"] = this->request_sufix_subjetc;
        __internal_add2map(content, this->request_sufix_subjetc, std::string("rss"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message rq_accounts_oninit::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["rqi"] =  qpidmsg_coded_as_qpid_Map(this->request_info);
        __internal_add2map(content, this->request_info, std::string("rqi"));
//  field_type
//        content["rss"] = this->request_sufix_subjetc;
        __internal_add2map(content, this->request_sufix_subjetc, std::string("rss"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




    sub_grant  __internal_get_default(sub_grant*)
    {
        return sub_grant(
//   IN_MSG
   __internal_get_default((sub_grant::IC_key*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    sub_grant::IC_key  __internal_get_default(sub_grant::IC_key*)
    {
        return sub_grant::IC_key(
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((mtk::trd::msg::sub_account_info*)0)
            );
    }
    
    rq_accounts  __internal_get_default(rq_accounts*)
    {
        return rq_accounts(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_request_info*)0)
            );
    }
    
    conf_add_accounts  __internal_get_default(conf_add_accounts*)
    {
        return conf_add_accounts(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_gen_response_location*)0),
//   sub_msg_type
   __internal_get_default((mtk::list<sub_grant >*)0)
            );
    }
    
    pub_accmgr_init  __internal_get_default(pub_accmgr_init*)
    {
        return pub_accmgr_init(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_info*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    rq_accounts_oninit  __internal_get_default(rq_accounts_oninit*)
    {
        return rq_accounts_oninit(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_request_info*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    

sub_grant::sub_grant (const qpid::types::Variant::Map&  mv)
    :  //   IN_MSG
   key(__internal_get_default((sub_grant::IC_key*)0)),
//   field_type
   type(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



sub_grant::IC_key::IC_key (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   market(__internal_get_default((std::string*)0)),
//   sub_msg_type
   account(__internal_get_default((mtk::trd::msg::sub_account_info*)0)) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



rq_accounts::rq_accounts (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   request_info(__internal_get_default((mtk::msg::sub_request_info*)0)) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



conf_add_accounts::conf_add_accounts (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   gen_response_location(__internal_get_default((mtk::msg::sub_gen_response_location*)0)),
//   sub_msg_type
   grant_list(__internal_get_default((mtk::list<sub_grant >*)0)) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



pub_accmgr_init::pub_accmgr_init (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   process_info(__internal_get_default((mtk::msg::sub_process_info*)0)),
//   field_type
   request_sufix_subjetc(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



rq_accounts_oninit::rq_accounts_oninit (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   request_info(__internal_get_default((mtk::msg::sub_request_info*)0)),
//   field_type
   request_sufix_subjetc(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }

mtk::t_qpid_filter  rq_accounts::get_in_subject (const std::string& request_info_process_info_location_broker_code)
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << request_info_process_info_location_broker_code << ".ALL.ACCOUNT.RQGRANTS"));
    }
    mtk::t_qpid_filter  rq_accounts::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << this->request_info.process_info.location.broker_code << ".ALL.ACCOUNT.RQGRANTS"));
    }
    /*static*/  mtk::t_qpid_address  rq_accounts::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  rq_accounts::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  conf_add_accounts::get_in_subject (const std::string& gen_response_location_broker_code,const std::string& gen_response_location_session_id)
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << gen_response_location_broker_code << "." << gen_response_location_session_id << ".CONF_ADD_ACOUNTS"));
    }
    mtk::t_qpid_filter  conf_add_accounts::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI." << this->gen_response_location.broker_code << "." << this->gen_response_location.session_id << ".CONF_ADD_ACOUNTS"));
    }
    /*static*/  mtk::t_qpid_address  conf_add_accounts::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  conf_add_accounts::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  pub_accmgr_init::get_in_subject ()
    {
        return mtk::t_qpid_filter(MTK_SS("CLI.ALL.ACCMGRINIT"));
    }
    mtk::t_qpid_filter  pub_accmgr_init::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("CLI.ALL.ACCMGRINIT"));
    }
    /*static*/  mtk::t_qpid_address  pub_accmgr_init::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  pub_accmgr_init::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  rq_accounts_oninit::get_in_subject (const std::string& request_info_process_info_location_broker_code,const std::string& request_sufix_subjetc)
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << request_info_process_info_location_broker_code << ".ALL." << request_sufix_subjetc << ".ACCOUNTS.RQINIT"));
    }
    mtk::t_qpid_filter  rq_accounts_oninit::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK." << this->request_info.process_info.location.broker_code << ".ALL." << this->request_sufix_subjetc << ".ACCOUNTS.RQINIT"));
    }
    /*static*/  mtk::t_qpid_address  rq_accounts_oninit::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  rq_accounts_oninit::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace account {
};   //namespace msg {


