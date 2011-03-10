
// generated automatically
// coded last modification:        Thu Mar 10 16:36:01 2011


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_admin.h"

namespace mtk { 
namespace admin { 
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


enter::enter (   const mtk::msg::sub_process_location&  _process_location,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check)
    :     process_location(_process_location),   ka_interval_send(_ka_interval_send),   ka_interval_check(_ka_interval_check) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string enter::check_recomended(void) const
{
    std::string result;

    return result;
}



keep_alive::keep_alive (   const mtk::msg::sub_process_location&  _process_location,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check)
    :     process_location(_process_location),   ka_interval_send(_ka_interval_send),   ka_interval_check(_ka_interval_check) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string keep_alive::check_recomended(void) const
{
    std::string result;

    return result;
}



exit::exit (   const mtk::msg::sub_process_location&  _process_location,   const std::string&  _reason)
    :     process_location(_process_location),   reason(_reason) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string exit::check_recomended(void) const
{
    std::string result;

    return result;
}



alarm::alarm (   const mtk::msg::sub_process_location&  _process_location,   const std::string&  _code_source,   const std::string&  _message,   const mtk::alEnPriority&  _priority,   const mtk::alEnType&  _type,   const mtk::DateTime&  _dateTime_generated,   const int16_t&  _alarm_id)
    :     process_location(_process_location),   code_source(_code_source),   message(_message),   priority(_priority),   type(_type),   dateTime_generated(_dateTime_generated),   alarm_id(_alarm_id) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string alarm::check_recomended(void) const
{
    std::string result;

    return result;
}



command::command (   const mtk::msg::sub_request_info&  _request_info,   const mtk::msg::sub_process_location&  _proc_loc__destination,   const std::string&  _command_line)
    :     request_info(_request_info),   proc_loc__destination(_proc_loc__destination),   command_line(_command_line) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string command::check_recomended(void) const
{
    std::string result;

    return result;
}



sub_command_rd::sub_command_rd (   const std::string&  _text)
    :     text(_text) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_command_rd::check_recomended(void) const
{
    std::string result;

    return result;
}



command_response::command_response (   const mtk::msg::sub_r_response&  _response_info,   const sub_command_rd&  _response_data)
    :     response_info(_response_info),   response_data(_response_data) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string command_response::check_recomended(void) const
{
    std::string result;

    return result;
}



central_keep_alive::central_keep_alive (   const mtk::msg::sub_process_location&  _process_location,   const mtk::dtTimeQuantity&  _ka_interval_send,   const mtk::dtTimeQuantity&  _ka_interval_check)
    :     process_location(_process_location),   ka_interval_send(_ka_interval_send),   ka_interval_check(_ka_interval_check) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string central_keep_alive::check_recomended(void) const
{
    std::string result;

    return result;
}


std::ostream& operator<< (std::ostream& o, const enter & c)
{
    o << "{ "

        << "process_location:"<< c.process_location<<"  "        << "ka_interval_send:"<<   c.ka_interval_send << "  "        << "ka_interval_check:"<<   c.ka_interval_check << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const keep_alive & c)
{
    o << "{ "

        << "process_location:"<< c.process_location<<"  "        << "ka_interval_send:"<<   c.ka_interval_send << "  "        << "ka_interval_check:"<<   c.ka_interval_check << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const exit & c)
{
    o << "{ "

        << "process_location:"<< c.process_location<<"  "        << "reason:"<<   c.reason << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const alarm & c)
{
    o << "{ "

        << "process_location:"<< c.process_location<<"  "        << "code_source:"<<   c.code_source << "  "        << "message:"<<   c.message << "  "        << "priority:"<< c.priority<<"  "        << "type:"<< c.type<<"  "        << "dateTime_generated:"<<   c.dateTime_generated << "  "        << "alarm_id:"<<   c.alarm_id << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const command & c)
{
    o << "{ "

        << "request_info:"<< c.request_info<<"  "        << "proc_loc__destination:"<< c.proc_loc__destination<<"  "        << "command_line:"<<   c.command_line << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const sub_command_rd & c)
{
    o << "{ "

        << "text:"<<   c.text << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const command_response & c)
{
    o << "{ "

        << "response_info:"<< c.response_info<<"  "        << "response_data:"<< c.response_data<<"  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const central_keep_alive & c)
{
    o << "{ "

        << "process_location:"<< c.process_location<<"  "        << "ka_interval_send:"<<   c.ka_interval_send << "  "        << "ka_interval_check:"<<   c.ka_interval_check << "  "
        << " }";
    return o;
};



bool operator== (const enter& a, const enter& b)
{
    return (          a.process_location ==  b.process_location  &&          a.ka_interval_send ==  b.ka_interval_send  &&          a.ka_interval_check ==  b.ka_interval_check  &&   true  );
};

bool operator!= (const enter& a, const enter& b)
{
    return !(a==b);
};



bool operator== (const keep_alive& a, const keep_alive& b)
{
    return (          a.process_location ==  b.process_location  &&          a.ka_interval_send ==  b.ka_interval_send  &&          a.ka_interval_check ==  b.ka_interval_check  &&   true  );
};

bool operator!= (const keep_alive& a, const keep_alive& b)
{
    return !(a==b);
};



bool operator== (const exit& a, const exit& b)
{
    return (          a.process_location ==  b.process_location  &&          a.reason ==  b.reason  &&   true  );
};

bool operator!= (const exit& a, const exit& b)
{
    return !(a==b);
};



bool operator== (const alarm& a, const alarm& b)
{
    return (          a.process_location ==  b.process_location  &&          a.code_source ==  b.code_source  &&          a.message ==  b.message  &&          a.priority ==  b.priority  &&          a.type ==  b.type  &&          a.dateTime_generated ==  b.dateTime_generated  &&          a.alarm_id ==  b.alarm_id  &&   true  );
};

bool operator!= (const alarm& a, const alarm& b)
{
    return !(a==b);
};



bool operator== (const command& a, const command& b)
{
    return (          a.request_info ==  b.request_info  &&          a.proc_loc__destination ==  b.proc_loc__destination  &&          a.command_line ==  b.command_line  &&   true  );
};

bool operator!= (const command& a, const command& b)
{
    return !(a==b);
};



bool operator== (const sub_command_rd& a, const sub_command_rd& b)
{
    return (          a.text ==  b.text  &&   true  );
};

bool operator!= (const sub_command_rd& a, const sub_command_rd& b)
{
    return !(a==b);
};



bool operator== (const command_response& a, const command_response& b)
{
    return (          a.response_info ==  b.response_info  &&          a.response_data ==  b.response_data  &&   true  );
};

bool operator!= (const command_response& a, const command_response& b)
{
    return !(a==b);
};



bool operator== (const central_keep_alive& a, const central_keep_alive& b)
{
    return (          a.process_location ==  b.process_location  &&          a.ka_interval_send ==  b.ka_interval_send  &&          a.ka_interval_check ==  b.ka_interval_check  &&   true  );
};

bool operator!= (const central_keep_alive& a, const central_keep_alive& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (enter& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (enter& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field process_location on message enter::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_location, it->second);
                        //__internal_qpid_fill(c.process_location, it->second.asMap());
//   field_type

                    it = mv.find("ks");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field ka_interval_send on message enter::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.ka_interval_send, it->second);
                        //c.ka_interval_send = it->second;
//   field_type

                    it = mv.find("kc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field ka_interval_check on message enter::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.ka_interval_check, it->second);
                        //c.ka_interval_check = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const enter& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.process_location, std::string("pl"));
//  field_type
        __internal_add2map(map, a.ka_interval_send, std::string("ks"));
//  field_type
        __internal_add2map(map, a.ka_interval_check, std::string("kc"));


};





//void  __internal_qpid_fill (keep_alive& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (keep_alive& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field process_location on message keep_alive::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_location, it->second);
                        //__internal_qpid_fill(c.process_location, it->second.asMap());
//   field_type

                    it = mv.find("ks");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field ka_interval_send on message keep_alive::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.ka_interval_send, it->second);
                        //c.ka_interval_send = it->second;
//   field_type

                    it = mv.find("kc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field ka_interval_check on message keep_alive::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.ka_interval_check, it->second);
                        //c.ka_interval_check = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const keep_alive& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.process_location, std::string("pl"));
//  field_type
        __internal_add2map(map, a.ka_interval_send, std::string("ks"));
//  field_type
        __internal_add2map(map, a.ka_interval_check, std::string("kc"));


};





//void  __internal_qpid_fill (exit& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (exit& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field process_location on message exit::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_location, it->second);
                        //__internal_qpid_fill(c.process_location, it->second.asMap());
//   field_type

                    it = mv.find("r");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field reason on message exit::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reason, it->second);
                        //c.reason = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const exit& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.process_location, std::string("pl"));
//  field_type
        __internal_add2map(map, a.reason, std::string("r"));


};





//void  __internal_qpid_fill (alarm& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (alarm& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field process_location on message alarm::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_location, it->second);
                        //__internal_qpid_fill(c.process_location, it->second.asMap());
//   field_type

                    it = mv.find("cs");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field code_source on message alarm::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.code_source, it->second);
                        //c.code_source = it->second;
//   field_type

                    it = mv.find("ms");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field message on message alarm::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.message, it->second);
                        //c.message = it->second;
//   sub_msg_type

                    it = mv.find("p");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field priority on message alarm::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.priority, it->second);
                        //__internal_qpid_fill(c.priority, it->second.asMap());
//   sub_msg_type

                    it = mv.find("t");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field type on message alarm::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.type, it->second);
                        //__internal_qpid_fill(c.type, it->second.asMap());
//   field_type

                    it = mv.find("dt");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field dateTime_generated on message alarm::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.dateTime_generated, it->second);
                        //c.dateTime_generated = it->second;
//   field_type

                    it = mv.find("ai");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field alarm_id on message alarm::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.alarm_id, it->second);
                        //c.alarm_id = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const alarm& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.process_location, std::string("pl"));
//  field_type
        __internal_add2map(map, a.code_source, std::string("cs"));
//  field_type
        __internal_add2map(map, a.message, std::string("ms"));
//  sub_msg_type
        __internal_add2map(map, a.priority, std::string("p"));
//  sub_msg_type
        __internal_add2map(map, a.type, std::string("t"));
//  field_type
        __internal_add2map(map, a.dateTime_generated, std::string("dt"));
//  field_type
        __internal_add2map(map, a.alarm_id, std::string("ai"));


};





//void  __internal_qpid_fill (command& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (command& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("ri");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field request_info on message command::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_info, it->second);
                        //__internal_qpid_fill(c.request_info, it->second.asMap());
//   sub_msg_type

                    it = mv.find("pd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field proc_loc__destination on message command::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.proc_loc__destination, it->second);
                        //__internal_qpid_fill(c.proc_loc__destination, it->second.asMap());
//   field_type

                    it = mv.find("c");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field command_line on message command::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.command_line, it->second);
                        //c.command_line = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const command& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.request_info, std::string("ri"));
//  sub_msg_type
        __internal_add2map(map, a.proc_loc__destination, std::string("pd"));
//  field_type
        __internal_add2map(map, a.command_line, std::string("c"));


};





//void  __internal_qpid_fill (sub_command_rd& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_command_rd& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("t");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field text on message sub_command_rd::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.text, it->second);
                        //c.text = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_command_rd& a)
{
    

//  field_type
        __internal_add2map(map, a.text, std::string("t"));


};





//void  __internal_qpid_fill (command_response& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (command_response& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("ri");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field response_info on message command_response::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.response_info, it->second);
                        //__internal_qpid_fill(c.response_info, it->second.asMap());
//   sub_msg_type

                    it = mv.find("rd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field response_data on message command_response::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.response_data, it->second);
                        //__internal_qpid_fill(c.response_data, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const command_response& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.response_info, std::string("ri"));
//  sub_msg_type
        __internal_add2map(map, a.response_data, std::string("rd"));


};





//void  __internal_qpid_fill (central_keep_alive& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (central_keep_alive& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("pl");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field process_location on message central_keep_alive::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.process_location, it->second);
                        //__internal_qpid_fill(c.process_location, it->second.asMap());
//   field_type

                    it = mv.find("ks");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field ka_interval_send on message central_keep_alive::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.ka_interval_send, it->second);
                        //c.ka_interval_send = it->second;
//   field_type

                    it = mv.find("kc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field ka_interval_check on message central_keep_alive::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.ka_interval_check, it->second);
                        //c.ka_interval_check = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const central_keep_alive& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.process_location, std::string("pl"));
//  field_type
        __internal_add2map(map, a.ka_interval_send, std::string("ks"));
//  field_type
        __internal_add2map(map, a.ka_interval_check, std::string("kc"));


};



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)

qpid::messaging::Message enter::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["pl"] =  qpidmsg_coded_as_qpid_Map(this->process_location);
        __internal_add2map(content, this->process_location, std::string("pl"));
//  field_type
//        content["ks"] = this->ka_interval_send;
        __internal_add2map(content, this->ka_interval_send, std::string("ks"));
//  field_type
//        content["kc"] = this->ka_interval_check;
        __internal_add2map(content, this->ka_interval_check, std::string("kc"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message keep_alive::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["pl"] =  qpidmsg_coded_as_qpid_Map(this->process_location);
        __internal_add2map(content, this->process_location, std::string("pl"));
//  field_type
//        content["ks"] = this->ka_interval_send;
        __internal_add2map(content, this->ka_interval_send, std::string("ks"));
//  field_type
//        content["kc"] = this->ka_interval_check;
        __internal_add2map(content, this->ka_interval_check, std::string("kc"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message exit::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["pl"] =  qpidmsg_coded_as_qpid_Map(this->process_location);
        __internal_add2map(content, this->process_location, std::string("pl"));
//  field_type
//        content["r"] = this->reason;
        __internal_add2map(content, this->reason, std::string("r"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message alarm::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["pl"] =  qpidmsg_coded_as_qpid_Map(this->process_location);
        __internal_add2map(content, this->process_location, std::string("pl"));
//  field_type
//        content["cs"] = this->code_source;
        __internal_add2map(content, this->code_source, std::string("cs"));
//  field_type
//        content["ms"] = this->message;
        __internal_add2map(content, this->message, std::string("ms"));
//  sub_msg_type
//        content["p"] =  qpidmsg_coded_as_qpid_Map(this->priority);
        __internal_add2map(content, this->priority, std::string("p"));
//  sub_msg_type
//        content["t"] =  qpidmsg_coded_as_qpid_Map(this->type);
        __internal_add2map(content, this->type, std::string("t"));
//  field_type
//        content["dt"] = this->dateTime_generated;
        __internal_add2map(content, this->dateTime_generated, std::string("dt"));
//  field_type
//        content["ai"] = this->alarm_id;
        __internal_add2map(content, this->alarm_id, std::string("ai"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message command::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["ri"] =  qpidmsg_coded_as_qpid_Map(this->request_info);
        __internal_add2map(content, this->request_info, std::string("ri"));
//  sub_msg_type
//        content["pd"] =  qpidmsg_coded_as_qpid_Map(this->proc_loc__destination);
        __internal_add2map(content, this->proc_loc__destination, std::string("pd"));
//  field_type
//        content["c"] = this->command_line;
        __internal_add2map(content, this->command_line, std::string("c"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message sub_command_rd::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  field_type
//        content["t"] = this->text;
        __internal_add2map(content, this->text, std::string("t"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message command_response::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["ri"] =  qpidmsg_coded_as_qpid_Map(this->response_info);
        __internal_add2map(content, this->response_info, std::string("ri"));
//  sub_msg_type
//        content["rd"] =  qpidmsg_coded_as_qpid_Map(this->response_data);
        __internal_add2map(content, this->response_data, std::string("rd"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message central_keep_alive::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["pl"] =  qpidmsg_coded_as_qpid_Map(this->process_location);
        __internal_add2map(content, this->process_location, std::string("pl"));
//  field_type
//        content["ks"] = this->ka_interval_send;
        __internal_add2map(content, this->ka_interval_send, std::string("ks"));
//  field_type
//        content["kc"] = this->ka_interval_check;
        __internal_add2map(content, this->ka_interval_check, std::string("kc"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




    enter  __internal_get_default(enter*)
    {
        return enter(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_location*)0),
//   field_type
   __internal_get_default ((mtk::dtTimeQuantity*)0),
//   field_type
   __internal_get_default ((mtk::dtTimeQuantity*)0)
            );
    }
    
    keep_alive  __internal_get_default(keep_alive*)
    {
        return keep_alive(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_location*)0),
//   field_type
   __internal_get_default ((mtk::dtTimeQuantity*)0),
//   field_type
   __internal_get_default ((mtk::dtTimeQuantity*)0)
            );
    }
    
    exit  __internal_get_default(exit*)
    {
        return exit(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_location*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    alarm  __internal_get_default(alarm*)
    {
        return alarm(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_location*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   __internal_get_default((mtk::alEnPriority*)0),
//   sub_msg_type
   __internal_get_default((mtk::alEnType*)0),
//   field_type
   __internal_get_default ((mtk::DateTime*)0),
//   field_type
   __internal_get_default ((int16_t*)0)
            );
    }
    
    command  __internal_get_default(command*)
    {
        return command(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_request_info*)0),
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_location*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    sub_command_rd  __internal_get_default(sub_command_rd*)
    {
        return sub_command_rd(
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    command_response  __internal_get_default(command_response*)
    {
        return command_response(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_r_response*)0),
//   sub_msg_type
   __internal_get_default((sub_command_rd*)0)
            );
    }
    
    central_keep_alive  __internal_get_default(central_keep_alive*)
    {
        return central_keep_alive(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_process_location*)0),
//   field_type
   __internal_get_default ((mtk::dtTimeQuantity*)0),
//   field_type
   __internal_get_default ((mtk::dtTimeQuantity*)0)
            );
    }
    

enter::enter (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   process_location(__internal_get_default((mtk::msg::sub_process_location*)0)),
//   field_type
   ka_interval_send(__internal_get_default((mtk::dtTimeQuantity*)0)),
//   field_type
   ka_interval_check(__internal_get_default((mtk::dtTimeQuantity*)0)) 
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



keep_alive::keep_alive (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   process_location(__internal_get_default((mtk::msg::sub_process_location*)0)),
//   field_type
   ka_interval_send(__internal_get_default((mtk::dtTimeQuantity*)0)),
//   field_type
   ka_interval_check(__internal_get_default((mtk::dtTimeQuantity*)0)) 
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



exit::exit (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   process_location(__internal_get_default((mtk::msg::sub_process_location*)0)),
//   field_type
   reason(__internal_get_default((std::string*)0)) 
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



alarm::alarm (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   process_location(__internal_get_default((mtk::msg::sub_process_location*)0)),
//   field_type
   code_source(__internal_get_default((std::string*)0)),
//   field_type
   message(__internal_get_default((std::string*)0)),
//   sub_msg_type
   priority(__internal_get_default((mtk::alEnPriority*)0)),
//   sub_msg_type
   type(__internal_get_default((mtk::alEnType*)0)),
//   field_type
   dateTime_generated(__internal_get_default((mtk::DateTime*)0)),
//   field_type
   alarm_id(__internal_get_default((int16_t*)0)) 
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



command::command (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   request_info(__internal_get_default((mtk::msg::sub_request_info*)0)),
//   sub_msg_type
   proc_loc__destination(__internal_get_default((mtk::msg::sub_process_location*)0)),
//   field_type
   command_line(__internal_get_default((std::string*)0)) 
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



sub_command_rd::sub_command_rd (const qpid::messaging::Message& msg)
    :  //   field_type
   text(__internal_get_default((std::string*)0)) 
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



command_response::command_response (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   response_info(__internal_get_default((mtk::msg::sub_r_response*)0)),
//   sub_msg_type
   response_data(__internal_get_default((sub_command_rd*)0)) 
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



central_keep_alive::central_keep_alive (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   process_location(__internal_get_default((mtk::msg::sub_process_location*)0)),
//   field_type
   ka_interval_send(__internal_get_default((mtk::dtTimeQuantity*)0)),
//   field_type
   ka_interval_check(__internal_get_default((mtk::dtTimeQuantity*)0)) 
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

std::string  enter::get_in_subject ()
    {
        return MTK_SS("ADM.CIMD.ENTER");
    }
    std::string  enter::get_out_subject (void) const
    {
        return MTK_SS("ADM.CIMD.ENTER");
    }
    std::string  keep_alive::get_in_subject ()
    {
        return MTK_SS("ADM.CIMD.KA");
    }
    std::string  keep_alive::get_out_subject (void) const
    {
        return MTK_SS("ADM.CIMD.KA");
    }
    std::string  exit::get_in_subject ()
    {
        return MTK_SS("ADM.CIMD.EXIT");
    }
    std::string  exit::get_out_subject (void) const
    {
        return MTK_SS("ADM.CIMD.EXIT");
    }
    std::string  alarm::get_in_subject ()
    {
        return MTK_SS("ADM.CIMD.ALARMS");
    }
    std::string  alarm::get_out_subject (void) const
    {
        return MTK_SS("ADM.CIMD.ALARMS");
    }
    std::string  command::get_in_subject (const std::string& proc_loc__destination_location,const std::string& proc_loc__destination_machine,const std::string& proc_loc__destination_process_name,const std::string& proc_loc__destination_process_uuid)
    {
        return MTK_SS("ADM." << proc_loc__destination_location << "." << proc_loc__destination_machine << "." << proc_loc__destination_process_name << "." << proc_loc__destination_process_uuid << ".COMMAND");
    }
    std::string  command::get_out_subject (void) const
    {
        return MTK_SS("ADM." << this->proc_loc__destination.location << "." << this->proc_loc__destination.machine << "." << this->proc_loc__destination.process_name << "." << this->proc_loc__destination.process_uuid << ".COMMAND");
    }
    std::string  command_response::get_in_subject (const std::string& response_info_request_info_process_location_location)
    {
        return MTK_SS("ADM.CIMD.COMMRES." << response_info_request_info_process_location_location << "");
    }
    std::string  command_response::get_out_subject (void) const
    {
        return MTK_SS("ADM.CIMD.COMMRES." << this->response_info.request_info.process_location.location << "");
    }
    std::string  central_keep_alive::get_in_subject ()
    {
        return MTK_SS("ADM.ALL.KA");
    }
    std::string  central_keep_alive::get_out_subject (void) const
    {
        return MTK_SS("ADM.ALL.KA");
    }
    

};   //namespace mtk {
};   //namespace admin {
};   //namespace msg {


