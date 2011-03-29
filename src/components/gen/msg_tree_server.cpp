
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_tree_server.h"

namespace mtk { 
namespace gen { 
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


sub_tree_item::sub_tree_item (   const std::string&  _branch,   const std::string&  _user_name,   const mtk::nullable<mtk::msg::sub_product_code>&  _product_code)
    :     branch(_branch),   user_name(_user_name),   product_code(_product_code) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string sub_tree_item::check_recomended(void) const
{
    std::string result;

    return result;
}



req_tree_items::req_tree_items (   const mtk::msg::sub_request_info&  _request_info,   const std::string&  _branch)
    :     request_info(_request_info),   branch(_branch) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string req_tree_items::check_recomended(void) const
{
    std::string result;

    return result;
}



res_tree_items::res_tree_items (   const mtk::msg::sub_r_response&  _response_info,   const sub_tree_item&  _item)
    :     response_info(_response_info),   item(_item) 
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE,
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string res_tree_items::check_recomended(void) const
{
    std::string result;

    return result;
}


std::ostream& operator<< (std::ostream& o, const sub_tree_item & c)
{
    o << "{ "

        << "branch:"<<   c.branch << "  "        << "user_name:"<<   c.user_name << "  "        << "product_code:"<< c.product_code<<"  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const req_tree_items & c)
{
    o << "{ "

        << "request_info:"<< c.request_info<<"  "        << "branch:"<<   c.branch << "  "
        << " }";
    return o;
};



std::ostream& operator<< (std::ostream& o, const res_tree_items & c)
{
    o << "{ "

        << "response_info:"<< c.response_info<<"  "        << "item:"<< c.item<<"  "
        << " }";
    return o;
};



bool operator== (const sub_tree_item& a, const sub_tree_item& b)
{
    return (          a.branch ==  b.branch  &&          a.user_name ==  b.user_name  &&          a.product_code ==  b.product_code  &&   true  );
};

bool operator!= (const sub_tree_item& a, const sub_tree_item& b)
{
    return !(a==b);
};



bool operator== (const req_tree_items& a, const req_tree_items& b)
{
    return (          a.request_info ==  b.request_info  &&          a.branch ==  b.branch  &&   true  );
};

bool operator!= (const req_tree_items& a, const req_tree_items& b)
{
    return !(a==b);
};



bool operator== (const res_tree_items& a, const res_tree_items& b)
{
    return (          a.response_info ==  b.response_info  &&          a.item ==  b.item  &&   true  );
};

bool operator!= (const res_tree_items& a, const res_tree_items& b)
{
    return !(a==b);
};




//void  __internal_qpid_fill (sub_tree_item& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (sub_tree_item& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("b");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field branch on message sub_tree_item::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.branch, it->second);
                        //c.branch = it->second;
//   field_type

                    it = mv.find("un");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field user_name on message sub_tree_item::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.user_name, it->second);
                        //c.user_name = it->second;
//   sub_msg_type

                    it = mv.find("pc");
                    if (it!= mv.end())
                        copy(c.product_code, it->second);
                        //__internal_qpid_fill(c.product_code, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const sub_tree_item& a)
{
    

//  field_type
        __internal_add2map(map, a.branch, std::string("b"));
//  field_type
        __internal_add2map(map, a.user_name, std::string("un"));
if (a.product_code.HasValue())
//  sub_msg_type
        __internal_add2map(map, a.product_code, std::string("pc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<sub_tree_item>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (req_tree_items& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (req_tree_items& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("ri");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field request_info on message req_tree_items::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.request_info, it->second);
                        //__internal_qpid_fill(c.request_info, it->second.asMap());
//   field_type

                    it = mv.find("br");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field branch on message req_tree_items::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.branch, it->second);
                        //c.branch = it->second;

    }


void __internal_add2map (qpid::types::Variant::Map& map, const req_tree_items& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.request_info, std::string("ri"));
//  field_type
        __internal_add2map(map, a.branch, std::string("br"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<req_tree_items>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





//void  __internal_qpid_fill (res_tree_items& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (res_tree_items& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();

        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   sub_msg_type

                    it = mv.find("ri");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field response_info on message res_tree_items::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.response_info, it->second);
                        //__internal_qpid_fill(c.response_info, it->second.asMap());
//   sub_msg_type

                    it = mv.find("it");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "missing mandatory field item on message res_tree_items::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.item, it->second);
                        //__internal_qpid_fill(c.item, it->second.asMap());

    }


void __internal_add2map (qpid::types::Variant::Map& map, const res_tree_items& a)
{
    

//  sub_msg_type
        __internal_add2map(map, a.response_info, std::string("ri"));
//  sub_msg_type
        __internal_add2map(map, a.item, std::string("it"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<res_tree_items>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}



//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties)

qpid::messaging::Message sub_tree_item::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  field_type
//        content["b"] = this->branch;
        __internal_add2map(content, this->branch, std::string("b"));
//  field_type
//        content["un"] = this->user_name;
        __internal_add2map(content, this->user_name, std::string("un"));
//if (this->product_code.HasValue())
//  sub_msg_type
//        content["pc"] =  qpidmsg_coded_as_qpid_Map(this->product_code);
        __internal_add2map(content, this->product_code, std::string("pc"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message req_tree_items::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["ri"] =  qpidmsg_coded_as_qpid_Map(this->request_info);
        __internal_add2map(content, this->request_info, std::string("ri"));
//  field_type
//        content["br"] = this->branch;
        __internal_add2map(content, this->branch, std::string("br"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




qpid::messaging::Message res_tree_items::qpidmsg_codded_as_qpid_message (void) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;


//  sub_msg_type
//        content["ri"] =  qpidmsg_coded_as_qpid_Map(this->response_info);
        __internal_add2map(content, this->response_info, std::string("ri"));
//  sub_msg_type
//        content["it"] =  qpidmsg_coded_as_qpid_Map(this->item);
        __internal_add2map(content, this->item, std::string("it"));


    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};




    sub_tree_item  __internal_get_default(sub_tree_item*)
    {
        return sub_tree_item(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   sub_msg_type
   mtk::nullable<mtk::msg::sub_product_code>()
            );
    }
    
    req_tree_items  __internal_get_default(req_tree_items*)
    {
        return req_tree_items(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_request_info*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    res_tree_items  __internal_get_default(res_tree_items*)
    {
        return res_tree_items(
//   sub_msg_type
   __internal_get_default((mtk::msg::sub_r_response*)0),
//   sub_msg_type
   __internal_get_default((sub_tree_item*)0)
            );
    }
    

sub_tree_item::sub_tree_item (const qpid::messaging::Message& msg)
    :  //   field_type
   branch(__internal_get_default((std::string*)0)),
//   field_type
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



req_tree_items::req_tree_items (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   request_info(__internal_get_default((mtk::msg::sub_request_info*)0)),
//   field_type
   branch(__internal_get_default((std::string*)0)) 
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



res_tree_items::res_tree_items (const qpid::messaging::Message& msg)
    :  //   sub_msg_type
   response_info(__internal_get_default((mtk::msg::sub_r_response*)0)),
//   sub_msg_type
   item(__internal_get_default((sub_tree_item*)0)) 
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

std::string  req_tree_items::get_in_subject (const std::string& request_info_process_location_location_client_code)
    {
        return MTK_SS("RQ." << request_info_process_location_location_client_code << ".TREE_REQUEST");
    }
    std::string  req_tree_items::get_out_subject (void) const
    {
        return MTK_SS("RQ." << this->request_info.process_location.location.client_code << ".TREE_REQUEST");
    }
    std::string  res_tree_items::get_in_subject (const std::string& response_info_request_info_process_location_location_client_code,const std::string& response_info_request_info_process_location_location_machine,const std::string& response_info_request_info_process_location_process_uuid,const std::string& response_info_request_info_req_id_sess_id,const std::string& response_info_request_info_req_id_req_code)
    {
        return MTK_SS("RS." << response_info_request_info_process_location_location_client_code << "." << response_info_request_info_process_location_location_machine << "." << response_info_request_info_process_location_process_uuid << "." << response_info_request_info_req_id_sess_id << "." << response_info_request_info_req_id_req_code << "");
    }
    std::string  res_tree_items::get_out_subject (void) const
    {
        return MTK_SS("RS." << this->response_info.request_info.process_location.location.client_code << "." << this->response_info.request_info.process_location.location.machine << "." << this->response_info.request_info.process_location.process_uuid << "." << this->response_info.request_info.req_id.sess_id << "." << this->response_info.request_info.req_id.req_code << "");
    }
    

};   //namespace mtk {
};   //namespace gen {
};   //namespace msg {


