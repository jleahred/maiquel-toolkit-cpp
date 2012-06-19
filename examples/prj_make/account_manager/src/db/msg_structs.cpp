
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_structs.h"

namespace accmgr { 
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


sub_user_info::sub_user_info (   const std::string&  _name,   const mtk::DateTime&  _created,   const std::string&  _client_code,   const mtk::list<mtk::trd::account::msg::sub_grant >&  _grant_list)
    :     name(_name),   created(_created),   client_code(_client_code),   grant_list(_grant_list) 
       
    {  
    }



void  sub_user_info::check_recomended(void) const
{

}

void sub_user_info::before_send(void) const
{

}




sub_oms_account_info::sub_oms_account_info (   const mtk::trd::msg::sub_account_info&  _account,   const std::string&  _oms_additional_info)
    :     account(_account),   oms_additional_info(_oms_additional_info) 
       
    {  
    }



void  sub_oms_account_info::check_recomended(void) const
{

}

void sub_oms_account_info::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const sub_user_info & c)
{
    o << "{ "

        << "name:"<<   c.name << "  "        << "created:"<<   c.created << "  "        << "client_code:"<<   c.client_code << "  "        << "grant_list:"<< c.grant_list<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_user_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "name"  << YAML::Value <<   c.name        << YAML::Key << "created"  << YAML::Value <<   c.created        << YAML::Key << "client_code"  << YAML::Value <<   c.client_code        << YAML::Key << "grant_list"  << YAML::Value << c.grant_list
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_user_info & c)
{


        node["name"]  >> c.name;
        node["created"]  >> c.created;
        node["client_code"]  >> c.client_code;
        node["grant_list"]  >> c.grant_list;


};


std::ostream& operator<< (std::ostream& o, const sub_oms_account_info & c)
{
    o << "{ "

        << "account:"<< c.account<<"  "        << "oms_additional_info:"<<   c.oms_additional_info << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_oms_account_info & c)
{
    o << YAML::BeginMap

        << YAML::Key << "account"  << YAML::Value << c.account        << YAML::Key << "oms_additional_info"  << YAML::Value <<   c.oms_additional_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_oms_account_info & c)
{


        node["account"]  >> c.account;
        node["oms_additional_info"]  >> c.oms_additional_info;


};


bool operator== (const sub_user_info& a, const sub_user_info& b)
{
    return (          a.name ==  b.name  &&          a.created ==  b.created  &&          a.client_code ==  b.client_code  &&          a.grant_list ==  b.grant_list  &&   true  );
};

bool operator!= (const sub_user_info& a, const sub_user_info& b)
{
    return !(a==b);
};



bool operator== (const sub_oms_account_info& a, const sub_oms_account_info& b)
{
    return (          a.account ==  b.account  &&          a.oms_additional_info ==  b.oms_additional_info  &&   true  );
};

bool operator!= (const sub_oms_account_info& a, const sub_oms_account_info& b)
{
    return !(a==b);
};




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

                    it = mv.find("gl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field grant_list on message sub_user_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.grant_list, it->second);
                        //__internal_qpid_fill(c.grant_list, it->second.asMap());

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_user_info& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.name, std::string("nm"));
//  field_type
        __internal_add2map(map, a.created, std::string("cdt"));
//  field_type
        __internal_add2map(map, a.client_code, std::string("cc"));
//  sub_msg_type
        __internal_add2map(map, a.grant_list, std::string("gl"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_user_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (sub_oms_account_info& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("acc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field account on message sub_oms_account_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.account, it->second);
                        //__internal_qpid_fill(c.account, it->second.asMap());
//   field_type

                    it = mv.find("oai");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field oms_additional_info on message sub_oms_account_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.oms_additional_info, it->second);
                        //c.oms_additional_info = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_oms_account_info& a)
{

    a.before_send();
    a.check_recomended();

//  sub_msg_type
        __internal_add2map(map, a.account, std::string("acc"));
//  field_type
        __internal_add2map(map, a.oms_additional_info, std::string("oai"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_oms_account_info>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)

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
   __internal_get_default((mtk::list<mtk::trd::account::msg::sub_grant >*)0)
            );
    }
    
    sub_oms_account_info  __internal_get_default(sub_oms_account_info*)
    {
        return sub_oms_account_info(
//   sub_msg_type
   __internal_get_default((mtk::trd::msg::sub_account_info*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
sub_user_info::sub_user_info (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   name(__internal_get_default((std::string*)0)),
//   field_type
   created(__internal_get_default((mtk::DateTime*)0)),
//   field_type
   client_code(__internal_get_default((std::string*)0)),
//   sub_msg_type
   grant_list(__internal_get_default((mtk::list<mtk::trd::account::msg::sub_grant >*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

sub_oms_account_info::sub_oms_account_info (const qpid::types::Variant::Map&  mv)
    :  //   sub_msg_type
   account(__internal_get_default((mtk::trd::msg::sub_account_info*)0)),
//   field_type
   oms_additional_info(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


};   //namespace accmgr {
};   //namespace msg {


