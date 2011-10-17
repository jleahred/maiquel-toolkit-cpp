
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_acs_server.h"

namespace mtk { 
namespace acs_server { 
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


pub_add_user::pub_add_user (   const mtk::acs::msg::res_login::IC_session_info&  _login_confirmation)
    :     login_confirmation(_login_confirmation) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string pub_add_user::check_recomended(void) const
{
    std::string result;

    return result;
}

void pub_add_user::before_send(void) const
{

}




pub_del_user::pub_del_user (   const mtk::acs::msg::res_login::IC_session_info&  _login_confirmation)
    :     login_confirmation(_login_confirmation) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string pub_del_user::check_recomended(void) const
{
    std::string result;

    return result;
}

void pub_del_user::before_send(void) const
{

}




req_session_id_conf::req_session_id_conf (   const std::string&  _session_id,   const mtk::msg::sub_process_info&  _from)
    :     session_id(_session_id),   from(_from) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string req_session_id_conf::check_recomended(void) const
{
    std::string result;

    return result;
}

void req_session_id_conf::before_send(void) const
{

}




pub_partial_user_list_acs2serv::pub_partial_user_list_acs2serv (   const mtk::list<mtk::acs::msg::res_login::IC_session_info >&  _list_login_confirmation)
    :     list_login_confirmation(_list_login_confirmation) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string pub_partial_user_list_acs2serv::check_recomended(void) const
{
    std::string result;

    return result;
}

void pub_partial_user_list_acs2serv::before_send(void) const
{

}




pub_partial_user_list_serv2acs::pub_partial_user_list_serv2acs (   const mtk::list<mtk::acs::msg::res_login::IC_session_info >&  _list_login_confirmation)
    :     list_login_confirmation(_list_login_confirmation) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string pub_partial_user_list_serv2acs::check_recomended(void) const
{
    std::string result;

    return result;
}

void pub_partial_user_list_serv2acs::before_send(void) const
{

}




req_user_list::req_user_list (   const mtk::msg::sub_request_info&  _request_info)
    :     request_info(_request_info) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string req_user_list::check_recomended(void) const
{
    std::string result;

    return result;
}

void req_user_list::before_send(void) const
{

}




res_user_list::res_user_list (   const mtk::msg::sub_r_response&  _response_info,   const mtk::list<mtk::acs::msg::res_login::IC_session_info >&  _list_login_confirmation)
    :     response_info(_response_info),   list_login_confirmation(_list_login_confirmation) 
       , __internal_warning_control_fields(0)
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string res_user_list::check_recomended(void) const
{
    std::string result;

    return result;
}

void res_user_list::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const pub_add_user & c)
{
    o << "{ "

        << "login_confirmation:"<< c.login_confirmation<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const pub_add_user & c)
{
    o << YAML::BeginMap

        << YAML::Key << "login_confirmation"  << YAML::Value << c.login_confirmation
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, pub_add_user & c)
{


        node["login_confirmation"]  >> c.login_confirmation;


};


std::ostream& operator<< (std::ostream& o, const pub_del_user & c)
{
    o << "{ "

        << "login_confirmation:"<< c.login_confirmation<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const pub_del_user & c)
{
    o << YAML::BeginMap

        << YAML::Key << "login_confirmation"  << YAML::Value << c.login_confirmation
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, pub_del_user & c)
{


        node["login_confirmation"]  >> c.login_confirmation;


};


std::ostream& operator<< (std::ostream& o, const req_session_id_conf & c)
{
    o << "{ "

        << "session_id:"<<   c.session_id << "  "        << "from:"<< c.from<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const req_session_id_conf & c)
{
    o << YAML::BeginMap

        << YAML::Key << "session_id"  << YAML::Value <<   c.session_id        << YAML::Key << "from"  << YAML::Value << c.from
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, req_session_id_conf & c)
{


        node["session_id"]  >> c.session_id;
        node["from"]  >> c.from;


};


std::ostream& operator<< (std::ostream& o, const pub_partial_user_list_acs2serv & c)
{
    o << "{ "

        << "list_login_confirmation:"<< c.list_login_confirmation<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const pub_partial_user_list_acs2serv & c)
{
    o << YAML::BeginMap

        << YAML::Key << "list_login_confirmation"  << YAML::Value << c.list_login_confirmation
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, pub_partial_user_list_acs2serv & c)
{


        node["list_login_confirmation"]  >> c.list_login_confirmation;


};


std::ostream& operator<< (std::ostream& o, const pub_partial_user_list_serv2acs & c)
{
    o << "{ "

        << "list_login_confirmation:"<< c.list_login_confirmation<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const pub_partial_user_list_serv2acs & c)
{
    o << YAML::BeginMap

        << YAML::Key << "list_login_confirmation"  << YAML::Value << c.list_login_confirmation
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, pub_partial_user_list_serv2acs & c)
{


        node["list_login_confirmation"]  >> c.list_login_confirmation;


};


std::ostream& operator<< (std::ostream& o, const req_user_list & c)
{
    o << "{ "

        << "request_info:"<< c.request_info<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const req_user_list & c)
{
    o << YAML::BeginMap

        << YAML::Key << "request_info"  << YAML::Value << c.request_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, req_user_list & c)
{


        node["request_info"]  >> c.request_info;


};


std::ostream& operator<< (std::ostream& o, const res_user_list & c)
{
    o << "{ "

        << "response_info:"<< c.response_info<<"  "        << "list_login_confirmation:"<< c.list_login_confirmation<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const res_user_list & c)
{
    o << YAML::BeginMap

        << YAML::Key << "response_info"  << YAML::Value << c.response_info        << YAML::Key << "list_login_confirmation"  << YAML::Value << c.list_login_confirmation
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, res_user_list & c)
{


        node["response_info"]  >> c.response_info;
        node["list_login_confirmation"]  >> c.list_login_confirmation;


};


bool operator== (const pub_add_user& a, const pub_add_user& b)
{
    return (          a.login_confirmation ==  b.login_confirmation  &&   true  );
};

bool operator!= (const pub_add_user& a, const pub_add_user& b)
{
    return !(a==b);
};



bool operator== (const pub_del_user& a, const pub_del_user& b)
{
    return (          a.login_confirmation ==  b.login_confirmation  &&   true  );
};

bool operator!= (const pub_del_user& a, const pub_del_user& b)
{
    return !(a==b);
};



bool operator== (const req_session_id_conf& a, const req_session_id_conf& b)
{
    return (          a.session_id ==  b.session_id  &&          a.from ==  b.from  &&   true  );
};

bool operator!= (const req_session_id_conf& a, const req_session_id_conf& b)
{
    return !(a==b);
};



bool operator== (const pub_partial_user_list_acs2serv& a, const pub_partial_user_list_acs2serv& b)
{
    return (          a.list_login_confirmation ==  b.list_login_confirmation  &&   true  );
};

bool operator!= (const pub_partial_user_list_acs2serv& a, const pub_partial_user_list_acs2serv& b)
{
    return !(a==b);
};



bool operator== (const pub_partial_user_list_serv2acs& a, const pub_partial_user_list_serv2acs& b)
{
    return (          a.list_login_confirmation ==  b.list_login_confirmation  &&   true  );
};

bool operator!= (const pub_partial_user_list_serv2acs& a, const pub_partial_user_list_serv2acs& b)
{
    return !(a==b);
};



bool operator== (const req_user_list& a, const req_user_list& b)
{
    return (          a.request_info ==  b.request_info  &&   true  );
};

bool operator!= (const req_user_list& a, const req_user_list& b)
{
    return !(a==b);
};



bool operator== (const res_user_list& a, const res_user_list& b)
{
    return (          a.response_info ==  b.response_info  &&          a.list_login_confirmation ==  b.list_login_confirmation  &&   true  );
};

bool operator!= (const res_user_list& a, const res_user_list& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (pub_add_user& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (pub_add_user& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("lgc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field login_confirmation on message pub_add_user::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.login_confirmation, it->second);
                        //__internal_qpid_fill(c.login_confirmation, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const pub_add_user& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.login_confirmation, std::string("lgc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_add_user>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (pub_del_user& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (pub_del_user& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("lgc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field login_confirmation on message pub_del_user::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.login_confirmation, it->second);
                        //__internal_qpid_fill(c.login_confirmation, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const pub_del_user& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.login_confirmation, std::string("lgc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_del_user>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (req_session_id_conf& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (req_session_id_conf& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("sid");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field session_id on message req_session_id_conf::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.session_id, it->second);
                        //c.session_id = it->second;
//   sub_msg_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message req_session_id_conf::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //__internal_qpid_fill(c.from, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const req_session_id_conf& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.session_id, std::string("sid"));
//  sub_msg_type
        __internal_add2map(map, a.from, std::string("from"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_session_id_conf>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (pub_partial_user_list_acs2serv& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (pub_partial_user_list_acs2serv& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("slc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field list_login_confirmation on message pub_partial_user_list_acs2serv::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.list_login_confirmation, it->second);
                        //__internal_qpid_fill(c.list_login_confirmation, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const pub_partial_user_list_acs2serv& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.list_login_confirmation, std::string("slc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_partial_user_list_acs2serv>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (pub_partial_user_list_serv2acs& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (pub_partial_user_list_serv2acs& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("slc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field list_login_confirmation on message pub_partial_user_list_serv2acs::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.list_login_confirmation, it->second);
                        //__internal_qpid_fill(c.list_login_confirmation, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const pub_partial_user_list_serv2acs& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.list_login_confirmation, std::string("slc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<pub_partial_user_list_serv2acs>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (req_user_list& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (req_user_list& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rqi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field request_info on message req_user_list::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_info, it->second);
                        //__internal_qpid_fill(c.request_info, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const req_user_list& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.request_info, std::string("rqi"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_user_list>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (res_user_list& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (res_user_list& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("rsi");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field response_info on message res_user_list::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.response_info, it->second);
                        //__internal_qpid_fill(c.response_info, it->second.asMap());
//   sub_msg_type

                    it = mv.find("slc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field list_login_confirmation on message res_user_list::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.list_login_confirmation, it->second);
                        //__internal_qpid_fill(c.list_login_confirmation, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const res_user_list& a)
{

    a.before_send();


//  sub_msg_type
        __internal_add2map(map, a.response_info, std::string("rsi"));
//  sub_msg_type
        __internal_add2map(map, a.list_login_confirmation, std::string("slc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_user_list>& a, const std::string& field)
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

qpid::messaging::Message pub_add_user::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["lgc"] =  qpidmsg_coded_as_qpid_Map(this->login_confirmation);
        __internal_add2map(content, this->login_confirmation, std::string("lgc"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message pub_del_user::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["lgc"] =  qpidmsg_coded_as_qpid_Map(this->login_confirmation);
        __internal_add2map(content, this->login_confirmation, std::string("lgc"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message req_session_id_conf::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  field_type
//        content["sid"] = this->session_id;
        __internal_add2map(content, this->session_id, std::string("sid"));
//  sub_msg_type
//        content["from"] =  qpidmsg_coded_as_qpid_Map(this->from);
        __internal_add2map(content, this->from, std::string("from"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message pub_partial_user_list_acs2serv::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["slc"] =  qpidmsg_coded_as_qpid_Map(this->list_login_confirmation);
        __internal_add2map(content, this->list_login_confirmation, std::string("slc"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message pub_partial_user_list_serv2acs::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["slc"] =  qpidmsg_coded_as_qpid_Map(this->list_login_confirmation);
        __internal_add2map(content, this->list_login_confirmation, std::string("slc"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message req_user_list::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
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




qpid::messaging::Message res_user_list::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["rsi"] =  qpidmsg_coded_as_qpid_Map(this->response_info);
        __internal_add2map(content, this->response_info, std::string("rsi"));
//  sub_msg_type
//        content["slc"] =  qpidmsg_coded_as_qpid_Map(this->list_login_confirmation);
        __internal_add2map(content, this->list_login_confirmation, std::string("slc"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




    pub_add_user  __internal_get_default(pub_add_user*)
    {
        return pub_add_user(
//   sub_msg_type
   __internal_get_default((mtk::acs::msg::res_login::IC_session_info*)0)
            );
    }
    
    pub_del_user  __internal_get_default(pub_del_user*)
    {
        return pub_del_user(
//   sub_msg_type
   __internal_get_default((mtk::acs::msg::res_login::IC_session_info*)0)
            );
    }
    
    req_session_id_conf  __internal_get_default(req_session_id_conf*)
    {
        return req_session_id_conf(
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_info*)0)
            );
    }
    
    pub_partial_user_list_acs2serv  __internal_get_default(pub_partial_user_list_acs2serv*)
    {
        return pub_partial_user_list_acs2serv(
//   sub_msg_type
   __internal_get_default((mtk::list<mtk::acs::msg::res_login::IC_session_info >*)0)
            );
    }
    
    pub_partial_user_list_serv2acs  __internal_get_default(pub_partial_user_list_serv2acs*)
    {
        return pub_partial_user_list_serv2acs(
//   sub_msg_type
   __internal_get_default((mtk::list<mtk::acs::msg::res_login::IC_session_info >*)0)
            );
    }
    
    req_user_list  __internal_get_default(req_user_list*)
    {
        return req_user_list(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_request_info*)0)
            );
    }
    
    res_user_list  __internal_get_default(res_user_list*)
    {
        return res_user_list(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_r_response*)0),
//   sub_msg_type
   __internal_get_default((mtk::list<mtk::acs::msg::res_login::IC_session_info >*)0)
            );
    }
    

pub_add_user::pub_add_user (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   login_confirmation(__internal_get_default((mtk::acs::msg::res_login::IC_session_info*)0)) 
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



pub_del_user::pub_del_user (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   login_confirmation(__internal_get_default((mtk::acs::msg::res_login::IC_session_info*)0)) 
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



req_session_id_conf::req_session_id_conf (const qpid::messaging::Message& msg)
    :  //   field_type
   session_id(__internal_get_default((std::string*)0)),
//   sub_msg_type
   from(__internal_get_default((mtk::msg::sub_process_info*)0)) 
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



pub_partial_user_list_acs2serv::pub_partial_user_list_acs2serv (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   list_login_confirmation(__internal_get_default((mtk::list<mtk::acs::msg::res_login::IC_session_info >*)0)) 
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



pub_partial_user_list_serv2acs::pub_partial_user_list_serv2acs (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   list_login_confirmation(__internal_get_default((mtk::list<mtk::acs::msg::res_login::IC_session_info >*)0)) 
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



req_user_list::req_user_list (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   request_info(__internal_get_default((mtk::msg::sub_request_info*)0)) 
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



res_user_list::res_user_list (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   response_info(__internal_get_default((mtk::msg::sub_r_response*)0)),
//   sub_msg_type
   list_login_confirmation(__internal_get_default((mtk::list<mtk::acs::msg::res_login::IC_session_info >*)0)) 
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

std::string  pub_add_user::get_in_subject ()
    {
        return MTK_SS("SYS.SRV.ACS_SYNC.AU");
    }
    std::string  pub_add_user::get_out_subject (void) const
    {
        return MTK_SS("SYS.SRV.ACS_SYNC.AU");
    }
    std::string  pub_del_user::get_in_subject ()
    {
        return MTK_SS("SYS.SRV.ACS_SYNC.DU");
    }
    std::string  pub_del_user::get_out_subject (void) const
    {
        return MTK_SS("SYS.SRV.ACS_SYNC.DU");
    }
    std::string  req_session_id_conf::get_in_subject ()
    {
        return MTK_SS("GS.ACS.ASK_SESSID");
    }
    std::string  req_session_id_conf::get_out_subject (void) const
    {
        return MTK_SS("GS.ACS.ASK_SESSID");
    }
    std::string  pub_partial_user_list_acs2serv::get_in_subject ()
    {
        return MTK_SS("SYS.SRV.ACS_SYNC.PUL");
    }
    std::string  pub_partial_user_list_acs2serv::get_out_subject (void) const
    {
        return MTK_SS("SYS.SRV.ACS_SYNC.PUL");
    }
    std::string  pub_partial_user_list_serv2acs::get_in_subject ()
    {
        return MTK_SS("SYS.ACS.ACS_SYNC.PUL");
    }
    std::string  pub_partial_user_list_serv2acs::get_out_subject (void) const
    {
        return MTK_SS("SYS.ACS.ACS_SYNC.PUL");
    }
    std::string  req_user_list::get_in_subject ()
    {
        return MTK_SS("GS.ACS.RQ_USER_LIST");
    }
    std::string  req_user_list::get_out_subject (void) const
    {
        return MTK_SS("GS.ACS.RQ_USER_LIST");
    }
    std::string  res_user_list::get_in_subject (const std::string& response_info_request_info_process_info_location_client_code,const std::string& response_info_request_info_process_info_location_machine,const std::string& response_info_request_info_process_info_process_uuid,const std::string& response_info_request_info_req_id_session_id,const std::string& response_info_request_info_req_id_req_code)
    {
        return MTK_SS("SYS.SRV.ACS." << response_info_request_info_process_info_location_client_code << "." << response_info_request_info_process_info_location_machine << "." << response_info_request_info_process_info_process_uuid << "." << response_info_request_info_req_id_session_id << "." << response_info_request_info_req_id_req_code << ".RSUL");
    }
    std::string  res_user_list::get_out_subject (void) const
    {
        return MTK_SS("SYS.SRV.ACS." << this->response_info.request_info.process_info.location.client_code << "." << this->response_info.request_info.process_info.location.machine << "." << this->response_info.request_info.process_info.process_uuid << "." << this->response_info.request_info.req_id.session_id << "." << this->response_info.request_info.req_id.req_code << ".RSUL");
    }
    

};   //namespace mtk {
};   //namespace acs_server {
};   //namespace msg {


