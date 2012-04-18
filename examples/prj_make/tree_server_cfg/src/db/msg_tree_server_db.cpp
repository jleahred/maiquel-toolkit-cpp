
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_tree_server_db.h"

namespace tree_server2 { 
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


sub_path_grants::sub_path_grants (   const IC_paths&  _paths,   const mtk::list<std::string >&  _users)
    :     paths(_paths),   users(_users) 
       
    {  
    }



void  sub_path_grants::check_recomended(void) const
{

}

void sub_path_grants::before_send(void) const
{

}




sub_path_grants::IC_paths::IC_paths (   const std::string&  _re_path,   const std::string&  _re_child)
    :     re_path(_re_path),   re_child(_re_child) 
       
    {  
    }



void  sub_path_grants::IC_paths::check_recomended(void) const
{

}

void sub_path_grants::IC_paths::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const sub_path_grants::IC_paths & c)
{
    o << "{ "

        << "re_path:"<<   c.re_path << "  "        << "re_child:"<<   c.re_child << "  "
        << " }";
    return o;
};


std::ostream& operator<< (std::ostream& o, const sub_path_grants & c)
{
    o << "{ "

        << "paths:"<< c.paths<<"  "        << "users:"<<   c.users << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_path_grants::IC_paths & c)
{
    o << YAML::BeginMap

        << YAML::Key << "re_path"  << YAML::Value <<   c.re_path        << YAML::Key << "re_child"  << YAML::Value <<   c.re_child
        << YAML::EndMap;
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_path_grants & c)
{
    o << YAML::BeginMap

        << YAML::Key << "paths"   << YAML::Value << c.paths        << YAML::Key << "users"  << YAML::Value <<   c.users
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_path_grants::IC_paths & c)
{


        node["re_path"]  >> c.re_path;
        node["re_child"]  >> c.re_child;


};



void  operator >> (const YAML::Node& node, sub_path_grants & c)
{


            node["paths"]   >> c.paths;
        node["users"]  >> c.users;


};


bool operator< (const sub_path_grants::IC_paths& a, const sub_path_grants::IC_paths& b)
{
    if (false)   return true;
    else if (true)
    {
        auto ca = mtk::make_tuple( 0          , a.re_path       , a.re_child );
        auto cb = mtk::make_tuple( 0          , b.re_path       , b.re_child );
        return ca < cb;
    }
    else
        return false;
};


bool operator== (const sub_path_grants::IC_paths& a, const sub_path_grants::IC_paths& b)
{
    return (          a.re_path ==  b.re_path  &&          a.re_child ==  b.re_child  &&   true  );
};

bool operator!= (const sub_path_grants::IC_paths& a, const sub_path_grants::IC_paths& b)
{
    return !(a==b);
};



bool operator== (const sub_path_grants& a, const sub_path_grants& b)
{
    return (          a.paths ==  b.paths  &&          a.users ==  b.users  &&   true  );
};

bool operator!= (const sub_path_grants& a, const sub_path_grants& b)
{
    return !(a==b);
};




void  copy (sub_path_grants& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   IN_MSG

                copy(c.paths, mv);
                //__internal_qpid_fill(c.paths, mv);
//   field_type

                    it = mv.find("users");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field users on message sub_path_grants::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.users, it->second);
                        //c.users = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_path_grants& a)
{

    a.before_send();
    a.check_recomended();

//  IN_MSG
        __internal_add2map(map, a.paths);
//  field_type
        __internal_add2map(map, a.users, std::string("users"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_path_grants>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (sub_path_grants::IC_paths& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("path");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field re_path on message sub_path_grants::IC_paths::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.re_path, it->second);
                        //c.re_path = it->second;
//   field_type

                    it = mv.find("child");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field re_child on message sub_path_grants::IC_paths::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.re_child, it->second);
                        //c.re_child = it->second;

        c.check_recomended ();
    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_path_grants::IC_paths& a)
{

    a.before_send();
    a.check_recomended();

//  field_type
        __internal_add2map(map, a.re_path, std::string("path"));
//  field_type
        __internal_add2map(map, a.re_child, std::string("child"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_path_grants::IC_paths>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)

    sub_path_grants  __internal_get_default(sub_path_grants*)
    {
        return sub_path_grants(
//   IN_MSG
   __internal_get_default((sub_path_grants::IC_paths*)0),
//   field_type
   __internal_get_default ((mtk::list<std::string >*)0)
            );
    }
    
    sub_path_grants::IC_paths  __internal_get_default(sub_path_grants::IC_paths*)
    {
        return sub_path_grants::IC_paths(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
sub_path_grants::sub_path_grants (const qpid::types::Variant::Map&  mv)
    :  //   IN_MSG
   paths(__internal_get_default((sub_path_grants::IC_paths*)0)),
//   field_type
   users(__internal_get_default((mtk::list<std::string >*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }

sub_path_grants::IC_paths::IC_paths (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   re_path(__internal_get_default((std::string*)0)),
//   field_type
   re_child(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


};   //namespace tree_server2 {
};   //namespace msg {


