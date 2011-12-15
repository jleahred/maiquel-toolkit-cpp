
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_structs.h"

namespace mon { 
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


sub_rule::sub_rule (   const std::string&  _re_rule,   const mtk::dtTimeQuantity&  _frequency,   const int&  _n_received,   const std::string&  _description,   const mtk::dtTimeQuantity&  _start_time,   const mtk::dtTimeQuantity&  _end_time,   const mtk::DateTime&  _last_notified)
    :     re_rule(_re_rule),   frequency(_frequency),   n_received(_n_received),   description(_description),   start_time(_start_time),   end_time(_end_time),   last_notified(_last_notified) 
       
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_rule::check_recomended(void) const
{
    std::string result;

    return result;
}

void sub_rule::before_send(void) const
{

}



std::ostream& operator<< (std::ostream& o, const sub_rule & c)
{
    o << "{ "

        << "re_rule:"<<   c.re_rule << "  "        << "frequency:"<<   c.frequency << "  "        << "n_received:"<< c.n_received<<"  "        << "description:"<<   c.description << "  "        << "start_time:"<<   c.start_time << "  "        << "end_time:"<<   c.end_time << "  "        << "last_notified:"<<   c.last_notified << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const sub_rule & c)
{
    o << YAML::BeginMap

        << YAML::Key << "re_rule"  << YAML::Value <<   c.re_rule        << YAML::Key << "frequency"  << YAML::Value <<   c.frequency        << YAML::Key << "n_received"  << YAML::Value << c.n_received        << YAML::Key << "description"  << YAML::Value <<   c.description        << YAML::Key << "start_time"  << YAML::Value <<   c.start_time        << YAML::Key << "end_time"  << YAML::Value <<   c.end_time        << YAML::Key << "last_notified"  << YAML::Value <<   c.last_notified
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, sub_rule & c)
{


        node["re_rule"]  >> c.re_rule;
        node["frequency"]  >> c.frequency;
        node["n_received"]  >> c.n_received;
        node["description"]  >> c.description;
        node["start_time"]  >> c.start_time;
        node["end_time"]  >> c.end_time;
        node["last_notified"]  >> c.last_notified;


};


bool operator== (const sub_rule& a, const sub_rule& b)
{
    return (          a.re_rule ==  b.re_rule  &&          a.frequency ==  b.frequency  &&          a.n_received ==  b.n_received  &&          a.description ==  b.description  &&          a.start_time ==  b.start_time  &&          a.end_time ==  b.end_time  &&          a.last_notified ==  b.last_notified  &&   true  );
};

bool operator!= (const sub_rule& a, const sub_rule& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (sub_rule& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_rule& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rer");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field re_rule on message sub_rule::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.re_rule, it->second);
                        //c.re_rule = it->second;
//   field_type

                    it = mv.find("fr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field frequency on message sub_rule::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.frequency, it->second);
                        //c.frequency = it->second;
//   sub_msg_type

                    it = mv.find("nr");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field n_received on message sub_rule::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.n_received, it->second);
                        //__internal_qpid_fill(c.n_received, it->second.asMap());
//   field_type

                    it = mv.find("desc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field description on message sub_rule::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.description, it->second);
                        //c.description = it->second;
//   field_type

                    it = mv.find("st");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field start_time on message sub_rule::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.start_time, it->second);
                        //c.start_time = it->second;
//   field_type

                    it = mv.find("et");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field end_time on message sub_rule::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.end_time, it->second);
                        //c.end_time = it->second;
//   field_type

                    it = mv.find("lnot");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field last_notified on message sub_rule::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.last_notified, it->second);
                        //c.last_notified = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_rule& a)
{

    a.before_send();


//  field_type
        __internal_add2map(map, a.re_rule, std::string("rer"));
//  field_type
        __internal_add2map(map, a.frequency, std::string("fr"));
//  sub_msg_type
        __internal_add2map(map, a.n_received, std::string("nr"));
//  field_type
        __internal_add2map(map, a.description, std::string("desc"));
//  field_type
        __internal_add2map(map, a.start_time, std::string("st"));
//  field_type
        __internal_add2map(map, a.end_time, std::string("et"));
//  field_type
        __internal_add2map(map, a.last_notified, std::string("lnot"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_rule>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)

    sub_rule  __internal_get_default(sub_rule*)
    {
        return sub_rule(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((mtk::dtTimeQuantity*)0),
//   sub_msg_type
   __internal_get_default((int*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((mtk::dtTimeQuantity*)0),
//   field_type
   __internal_get_default ((mtk::dtTimeQuantity*)0),
//   field_type
   __internal_get_default ((mtk::DateTime*)0)
            );
    }
    

sub_rule::sub_rule (const qpid::types::Variant::Map&  mv)
    :  //   field_type
   re_rule(__internal_get_default((std::string*)0)),
//   field_type
   frequency(__internal_get_default((mtk::dtTimeQuantity*)0)),
//   sub_msg_type
   n_received(__internal_get_default((int*)0)),
//   field_type
   description(__internal_get_default((std::string*)0)),
//   field_type
   start_time(__internal_get_default((mtk::dtTimeQuantity*)0)),
//   field_type
   end_time(__internal_get_default((mtk::dtTimeQuantity*)0)),
//   field_type
   last_notified(__internal_get_default((mtk::DateTime*)0)) 
    {
        copy(*this, mv);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }



};   //namespace mon {
};   //namespace msg {


