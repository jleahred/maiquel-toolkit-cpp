
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_structs.h"

namespace qfmgr { 
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


sub_product::sub_product (   const std::string&  _gen_product_name,   const std::string&  _market,   const std::string&  _re_product_code)
    :     gen_product_name(_gen_product_name),   market(_market),   re_product_code(_re_product_code) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_product::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_product::before_send(void) const
{

}




sub_filter_info::sub_filter_info (   const std::string&  _gen_product_name,   const int&  _quantity)
    :     gen_product_name(_gen_product_name),   quantity(_quantity) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_filter_info::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_filter_info::before_send(void) const
{

}




sub_client_info::sub_client_info (   const std::string&  _name,   const mtk::DateTime&  _created,   const mtk::list<sub_filter_info >&  _filter_list)
    :     name(_name),   created(_created),   filter_list(_filter_list) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_client_info::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_client_info::before_send(void) const
{

}




sub_user_info::sub_user_info (   const std::string&  _name,   const mtk::DateTime&  _created,   const std::string&  _client_code,   const mtk::list<sub_filter_info >&  _filter_list)
    :     name(_name),   created(_created),   client_code(_client_code),   filter_list(_filter_list) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_user_info::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_user_info::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const sub_product & c)
{
    o << "{ "

        << "gen_product_name:"<<   c.gen_product_name << "  "        << "market:"<<   c.market << "  "        << "re_product_code:"<<   c.re_product_code << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_product & c)
{
    o << YAML::BeginMap

        << YAML::Key << "gen_product_name"  << YAML::Value <<   c.gen_product_name        << YAML::Key << "market"  << YAML::Value <<   c.market        << YAML::Key << "re_product_code"  << YAML::Value <<   c.re_product_code
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_product & c)
{


        node["gen_product_name"]  >> c.gen_product_name;
        node["market"]  >> c.market;
        node["re_product_code"]  >> c.re_product_code;


};


std::ostream& operator<< (std::ostream& o, const sub_filter_info & c)
{
    o << "{ "

        << "gen_product_name:"<<   c.gen_product_name << "  "        << "quantity:"<< c.quantity<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_filter_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "gen_product_name"  << YAML::Value <<   c.gen_product_name        << YAML::Key << "quantity"  << YAML::Value << c.quantity
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_filter_info & c)
{


        node["gen_product_name"]  >> c.gen_product_name;
        node["quantity"]  >> c.quantity;


};


std::ostream& operator<< (std::ostream& o, const sub_client_info & c)
{
    o << "{ "

        << "name:"<<   c.name << "  "        << "created:"<<   c.created << "  "        << "filter_list:"<< c.filter_list<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_client_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "name"  << YAML::Value <<   c.name        << YAML::Key << "created"  << YAML::Value <<   c.created        << YAML::Key << "filter_list"  << YAML::Value << c.filter_list
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_client_info & c)
{


        node["name"]  >> c.name;
        node["created"]  >> c.created;
        node["filter_list"]  >> c.filter_list;


};


std::ostream& operator<< (std::ostream& o, const sub_user_info & c)
{
    o << "{ "

        << "name:"<<   c.name << "  "        << "created:"<<   c.created << "  "        << "client_code:"<<   c.client_code << "  "        << "filter_list:"<< c.filter_list<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_user_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "name"  << YAML::Value <<   c.name        << YAML::Key << "created"  << YAML::Value <<   c.created        << YAML::Key << "client_code"  << YAML::Value <<   c.client_code        << YAML::Key << "filter_list"  << YAML::Value << c.filter_list
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_user_info & c)
{


        node["name"]  >> c.name;
        node["created"]  >> c.created;
        node["client_code"]  >> c.client_code;
        node["filter_list"]  >> c.filter_list;


};


bool operator== (const sub_product& a, const sub_product& b)
{
    return (          a.gen_product_name ==  b.gen_product_name  &&          a.market ==  b.market  &&          a.re_product_code ==  b.re_product_code  &&   true  );
};

bool operator!= (const sub_product& a, const sub_product& b)
{
    return !(a==b);
};



bool operator== (const sub_filter_info& a, const sub_filter_info& b)
{
    return (          a.gen_product_name ==  b.gen_product_name  &&          a.quantity ==  b.quantity  &&   true  );
};

bool operator!= (const sub_filter_info& a, const sub_filter_info& b)
{
    return !(a==b);
};



bool operator== (const sub_client_info& a, const sub_client_info& b)
{
    return (          a.name ==  b.name  &&          a.created ==  b.created  &&          a.filter_list ==  b.filter_list  &&   true  );
};

bool operator!= (const sub_client_info& a, const sub_client_info& b)
{
    return !(a==b);
};



bool operator== (const sub_user_info& a, const sub_user_info& b)
{
    return (          a.name ==  b.name  &&          a.created ==  b.created  &&          a.client_code ==  b.client_code  &&          a.filter_list ==  b.filter_list  &&   true  );
};

bool operator!= (const sub_user_info& a, const sub_user_info& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (sub_product& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_product& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("gpn");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field gen_product_name on message sub_product::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.gen_product_name, it->second);
                        //c.gen_product_name = it->second;
//   field_type

                    it = mv.find("mk");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field market on message sub_product::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.market, it->second);
                        //c.market = it->second;
//   field_type

                    it = mv.find("repc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field re_product_code on message sub_product::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.re_product_code, it->second);
                        //c.re_product_code = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_product& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.gen_product_name, std::string("gpn"));
//  field_type
        __internal_add2map(map, a.market, std::string("mk"));
//  field_type
        __internal_add2map(map, a.re_product_code, std::string("repc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_product>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_filter_info& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_filter_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("gpn");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field gen_product_name on message sub_filter_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.gen_product_name, it->second);
                        //c.gen_product_name = it->second;
//   sub_msg_type

                    it = mv.find("qt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field quantity on message sub_filter_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.quantity, it->second);
                        //__internal_qpid_fill(c.quantity, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_filter_info& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.gen_product_name, std::string("gpn"));
//  sub_msg_type
        __internal_add2map(map, a.quantity, std::string("qt"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_filter_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_client_info& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_client_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("nm");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field name on message sub_client_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.name, it->second);
                        //c.name = it->second;
//   field_type

                    it = mv.find("cdt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field created on message sub_client_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.created, it->second);
                        //c.created = it->second;
//   sub_msg_type

                    it = mv.find("fl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field filter_list on message sub_client_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.filter_list, it->second);
                        //__internal_qpid_fill(c.filter_list, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_client_info& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.name, std::string("nm"));
//  field_type
        __internal_add2map(map, a.created, std::string("cdt"));
//  sub_msg_type
        __internal_add2map(map, a.filter_list, std::string("fl"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_client_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (sub_user_info& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_user_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("nm");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field name on message sub_user_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.name, it->second);
                        //c.name = it->second;
//   field_type

                    it = mv.find("cdt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field created on message sub_user_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.created, it->second);
                        //c.created = it->second;
//   field_type

                    it = mv.find("cc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field client_code on message sub_user_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.client_code, it->second);
                        //c.client_code = it->second;
//   sub_msg_type

                    it = mv.find("fl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field filter_list on message sub_user_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.filter_list, it->second);
                        //__internal_qpid_fill(c.filter_list, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_user_info& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.name, std::string("nm"));
//  field_type
        __internal_add2map(map, a.created, std::string("cdt"));
//  field_type
        __internal_add2map(map, a.client_code, std::string("cc"));
//  sub_msg_type
        __internal_add2map(map, a.filter_list, std::string("fl"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_user_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)

    sub_product  __internal_get_default(sub_product*)
    {
        return sub_product(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    sub_filter_info  __internal_get_default(sub_filter_info*)
    {
        return sub_filter_info(
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((int*)0)
            );
    }
    
    sub_client_info  __internal_get_default(sub_client_info*)
    {
        return sub_client_info(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((mtk::DateTime*)0),
//   sub_msg_type
   __internal_get_default((mtk::list<sub_filter_info >*)0)
            );
    }
    
    sub_user_info  __internal_get_default(sub_user_info*)
    {
        return sub_user_info(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((mtk::DateTime*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((mtk::list<sub_filter_info >*)0)
            );
    }
    

sub_product::sub_product (const qpid::messaging::Message& msg)
    :  //   field_type
   gen_product_name(__internal_get_default((std::string*)0)),
//   field_type
   market(__internal_get_default((std::string*)0)),
//   field_type
   re_product_code(__internal_get_default((std::string*)0)) 
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



sub_filter_info::sub_filter_info (const qpid::messaging::Message& msg)
    :  //   field_type
   gen_product_name(__internal_get_default((std::string*)0)),
//   sub_msg_type
   quantity(__internal_get_default((int*)0)) 
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



sub_client_info::sub_client_info (const qpid::messaging::Message& msg)
    :  //   field_type
   name(__internal_get_default((std::string*)0)),
//   field_type
   created(__internal_get_default((mtk::DateTime*)0)),
//   sub_msg_type
   filter_list(__internal_get_default((mtk::list<sub_filter_info >*)0)) 
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



sub_user_info::sub_user_info (const qpid::messaging::Message& msg)
    :  //   field_type
   name(__internal_get_default((std::string*)0)),
//   field_type
   created(__internal_get_default((mtk::DateTime*)0)),
//   field_type
   client_code(__internal_get_default((std::string*)0)),
//   sub_msg_type
   filter_list(__internal_get_default((mtk::list<sub_filter_info >*)0)) 
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



};   //namespace qfmgr {
};   //namespace msg {


