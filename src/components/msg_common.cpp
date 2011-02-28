
// generated automatically
// coded last modification:        Mon Jan 17 22:34:28 2011


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
    inline int8_t __internal_get_default_int8_t(int8_t*)
    {
        return 0;
    }
    inline int16_t  __internal_get_default_int16_t(int16_t*)
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

inline void copy(int32_t& result, const qpid::types::Variant& v)
{
    result =  v.asInt32();
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


sub_single_product_code::sub_single_product_code (   const std::string&  _market,   const std::string&  _product,   const mtk::nullable<std::string>&  _code)
    :     market(_market),   product(_product),   code(_code) 
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



sub_product_code::sub_product_code (   const sub_single_product_code&  _sys_code,   const mtk::nullable<sub_single_product_code>&  _aditional_code,   const mtk::nullable<std::string>&  _description)
    :     sys_code(_sys_code),   aditional_code(_aditional_code),   description(_description) 
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



sub_order_id::sub_order_id ( const sub_request_id&  parent)
    :  sub_request_id(parent) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_order_id::check_recomended(void) const
{
    std::string result;

    return result;
}



sub_request_info::sub_request_info (   const sub_request_id&  _req_id,   const std::string&  _client)
    :     req_id(_req_id),   client(_client) 
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


std::ostream& operator<< (std::ostream& o, const sub_single_product_code & c)
{
    o << "{ "

        << "market:"<<   c.market << "  "        << "product:"<<   c.product << "  "        << "code:"<<   c.code << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const sub_product_code & c)
{
    o << "{ "

        << "sys_code:"<< c.sys_code<<"  "        << "aditional_code:"<< c.aditional_code<<"  "        << "description:"<<   c.description << "  "
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



std::ostream& operator<< (std::ostream& o, const sub_order_id & c)
{
    o << "{ "
    << "("  <<  static_cast<const sub_request_id&>(c)  << ")" 

        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const sub_request_info & c)
{
    o << "{ "

        << "req_id:"<< c.req_id<<"  "        << "client:"<<   c.client << "  "
        << " }";
    return o;
};



bool operator== (const sub_single_product_code& a, const sub_single_product_code& b)
{
    return (          a.market ==  b.market  &&          a.product ==  b.product  &&          a.code ==  b.code  &&   true  );
};

bool operator!= (const sub_single_product_code& a, const sub_single_product_code& b)
{
    return !(a==b);
};



bool operator== (const sub_product_code& a, const sub_product_code& b)
{
    return (          a.sys_code ==  b.sys_code  &&          a.aditional_code ==  b.aditional_code  &&          a.description ==  b.description  &&   true  );
};

bool operator!= (const sub_product_code& a, const sub_product_code& b)
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



bool operator== (const sub_order_id& a, const sub_order_id& b)
{
    return ( (static_cast<const sub_request_id&>(a)   ==  static_cast<const sub_request_id&>(b))  &&    true  );
};

bool operator!= (const sub_order_id& a, const sub_order_id& b)
{
    return !(a==b);
};



bool operator== (const sub_request_info& a, const sub_request_info& b)
{
    return (          a.req_id ==  b.req_id  &&          a.client ==  b.client  &&   true  );
};

bool operator!= (const sub_request_info& a, const sub_request_info& b)
{
    return !(a==b);
};




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
//   field_type

                    it = mv.find("cd");
                    if (it!= mv.end())
                        copy(c.code, it->second);
                        //c.code = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_single_product_code& a)
{
    

//  field_type
        __internal_add2map(map, a.market, std::string("mk"));
//  field_type
        __internal_add2map(map, a.product, std::string("pr"));
if (a.code.HasValue())
//  field_type
        __internal_add2map(map, a.code, std::string("cd"));


};





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
//   field_type

                    it = mv.find("des");
                    if (it!= mv.end())
                        copy(c.description, it->second);
                        //c.description = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_product_code& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.sys_code, std::string("spc"));
if (a.aditional_code.HasValue())
//  sub_msg_type
        __internal_add2map(map, a.aditional_code, std::string("apc"));
if (a.description.HasValue())
//  field_type
        __internal_add2map(map, a.description, std::string("des"));


};





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





//void  __internal_qpid_fill (sub_order_id& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_order_id& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
copy(static_cast<sub_request_id&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_order_id& a)
{
    
//  parent
__internal_add2map(map, static_cast<const sub_request_id&>(a));



};





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
//   field_type

                    it = mv.find("cli");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field client on message sub_request_info::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.client, it->second);
                        //c.client = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_request_info& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.req_id, std::string("rid"));
//  field_type
        __internal_add2map(map, a.client, std::string("cli"));


};



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)

qpid::messaging::Message sub_single_product_code::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message message;
    qpid::types::Variant::Map content;


//  field_type
//        content["mk"] = this->market;
        __internal_add2map(content, this->market, std::string("mk"));
//  field_type
//        content["pr"] = this->product;
        __internal_add2map(content, this->product, std::string("pr"));
//if (this->code.HasValue())
//  field_type
//        content["cd"] = this->code;
        __internal_add2map(content, this->code, std::string("cd"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, message);
    return message;
};




qpid::messaging::Message sub_product_code::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["spc"] =  qpidmsg_coded_as_qpid_Map(this->sys_code);
        __internal_add2map(content, this->sys_code, std::string("spc"));
//if (this->aditional_code.HasValue())
//  sub_msg_type
//        content["apc"] =  qpidmsg_coded_as_qpid_Map(this->aditional_code);
        __internal_add2map(content, this->aditional_code, std::string("apc"));
//if (this->description.HasValue())
//  field_type
//        content["des"] = this->description;
        __internal_add2map(content, this->description, std::string("des"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, message);
    return message;
};




qpid::messaging::Message sub_request_id::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message message;
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

    
    qpid::messaging::encode(content, message);
    return message;
};




qpid::messaging::Message sub_order_id::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message message;
    qpid::types::Variant::Map content;

//  parent
__internal_add2map(content, static_cast<const sub_request_id&>(*this));



    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, message);
    return message;
};




qpid::messaging::Message sub_request_info::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["rid"] =  qpidmsg_coded_as_qpid_Map(this->req_id);
        __internal_add2map(content, this->req_id, std::string("rid"));
//  field_type
//        content["cli"] = this->client;
        __internal_add2map(content, this->client, std::string("cli"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, message);
    return message;
};




    sub_single_product_code  __internal_get_default(sub_single_product_code*)
    {
        return sub_single_product_code(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   mtk::nullable<std::string>()
            );
    }
    
    sub_product_code  __internal_get_default(sub_product_code*)
    {
        return sub_product_code(
//   sub_msg_type
   __internal_get_default((sub_single_product_code*)0),
//   sub_msg_type
   mtk::nullable<sub_single_product_code>(),
//   field_type
   mtk::nullable<std::string>()
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
    
    sub_order_id  __internal_get_default(sub_order_id*)
    {
        return sub_order_id(
__internal_get_default((sub_request_id*)0)
            );
    }
    
    sub_request_info  __internal_get_default(sub_request_info*)
    {
        return sub_request_info(
//   sub_msg_type
   __internal_get_default((sub_request_id*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
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



sub_product_code::sub_product_code (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   sys_code(__internal_get_default((sub_single_product_code*)0)) 
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



sub_order_id::sub_order_id (const qpid::messaging::Message& msg)
    :  sub_request_id(msg) 
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
//   field_type
   client(__internal_get_default((std::string*)0)) 
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


