
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "msg_trd_oms_rq.h"

namespace mtk { 
namespace trd { 
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


oms_RQ_NW_LS::oms_RQ_NW_LS ( const RQ_NW_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
    :  RQ_NW_LS(parent),   reject_description(_reject_description),   from(_from),   oms_additional_info(_oms_additional_info) 
       , __internal_warning_control_fields(0)
    {  
    }



void  oms_RQ_NW_LS::check_recomended(void) const
{

}

void oms_RQ_NW_LS::before_send(void) const
{

}




oms_RQ_MD_LS::oms_RQ_MD_LS ( const RQ_MD_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
    :  RQ_MD_LS(parent),   reject_description(_reject_description),   from(_from),   oms_additional_info(_oms_additional_info) 
       , __internal_warning_control_fields(0)
    {  
    }



void  oms_RQ_MD_LS::check_recomended(void) const
{

}

void oms_RQ_MD_LS::before_send(void) const
{

}




oms_RQ_CC_LS::oms_RQ_CC_LS ( const RQ_CC_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
    :  RQ_CC_LS(parent),   reject_description(_reject_description),   from(_from),   oms_additional_info(_oms_additional_info) 
       , __internal_warning_control_fields(0)
    {  
    }



void  oms_RQ_CC_LS::check_recomended(void) const
{

}

void oms_RQ_CC_LS::before_send(void) const
{

}




oms_RQ_NW_MK::oms_RQ_NW_MK ( const RQ_NW_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
    :  RQ_NW_MK(parent),   reject_description(_reject_description),   from(_from),   oms_additional_info(_oms_additional_info) 
       , __internal_warning_control_fields(0)
    {  
    }



void  oms_RQ_NW_MK::check_recomended(void) const
{

}

void oms_RQ_NW_MK::before_send(void) const
{

}




oms_RQ_MD_MK::oms_RQ_MD_MK ( const RQ_MD_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
    :  RQ_MD_MK(parent),   reject_description(_reject_description),   from(_from),   oms_additional_info(_oms_additional_info) 
       , __internal_warning_control_fields(0)
    {  
    }



void  oms_RQ_MD_MK::check_recomended(void) const
{

}

void oms_RQ_MD_MK::before_send(void) const
{

}




oms_RQ_CC_MK::oms_RQ_CC_MK ( const RQ_CC_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
    :  RQ_CC_MK(parent),   reject_description(_reject_description),   from(_from),   oms_additional_info(_oms_additional_info) 
       , __internal_warning_control_fields(0)
    {  
    }



void  oms_RQ_CC_MK::check_recomended(void) const
{

}

void oms_RQ_CC_MK::before_send(void) const
{

}




oms_RQ_NW_SM::oms_RQ_NW_SM ( const RQ_NW_SM&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
    :  RQ_NW_SM(parent),   reject_description(_reject_description),   from(_from),   oms_additional_info(_oms_additional_info) 
       , __internal_warning_control_fields(0)
    {  
    }



void  oms_RQ_NW_SM::check_recomended(void) const
{

}

void oms_RQ_NW_SM::before_send(void) const
{

}




oms_RQ_MD_SM::oms_RQ_MD_SM ( const RQ_MD_SM&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
    :  RQ_MD_SM(parent),   reject_description(_reject_description),   from(_from),   oms_additional_info(_oms_additional_info) 
       , __internal_warning_control_fields(0)
    {  
    }



void  oms_RQ_MD_SM::check_recomended(void) const
{

}

void oms_RQ_MD_SM::before_send(void) const
{

}




oms_RQ_CC_SM::oms_RQ_CC_SM ( const RQ_CC_SM&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
    :  RQ_CC_SM(parent),   reject_description(_reject_description),   from(_from),   oms_additional_info(_oms_additional_info) 
       , __internal_warning_control_fields(0)
    {  
    }



void  oms_RQ_CC_SM::check_recomended(void) const
{

}

void oms_RQ_CC_SM::before_send(void) const
{

}




oms_RQ_NW_SL::oms_RQ_NW_SL ( const RQ_NW_SL&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
    :  RQ_NW_SL(parent),   reject_description(_reject_description),   from(_from),   oms_additional_info(_oms_additional_info) 
       , __internal_warning_control_fields(0)
    {  
    }



void  oms_RQ_NW_SL::check_recomended(void) const
{

}

void oms_RQ_NW_SL::before_send(void) const
{

}




oms_RQ_MD_SL::oms_RQ_MD_SL ( const RQ_MD_SL&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
    :  RQ_MD_SL(parent),   reject_description(_reject_description),   from(_from),   oms_additional_info(_oms_additional_info) 
       , __internal_warning_control_fields(0)
    {  
    }



void  oms_RQ_MD_SL::check_recomended(void) const
{

}

void oms_RQ_MD_SL::before_send(void) const
{

}




oms_RQ_CC_SL::oms_RQ_CC_SL ( const RQ_CC_SL&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
    :  RQ_CC_SL(parent),   reject_description(_reject_description),   from(_from),   oms_additional_info(_oms_additional_info) 
       , __internal_warning_control_fields(0)
    {  
    }



void  oms_RQ_CC_SL::check_recomended(void) const
{

}

void oms_RQ_CC_SL::before_send(void) const
{

}




oms_RQ_ORDERS_STATUS::oms_RQ_ORDERS_STATUS ( const RQ_ORDERS_STATUS&  parent,   const std::string&  _reject_description,   const std::string&  _from)
    :  RQ_ORDERS_STATUS(parent),   reject_description(_reject_description),   from(_from) 
       , __internal_warning_control_fields(0)
    {  
    }



void  oms_RQ_ORDERS_STATUS::check_recomended(void) const
{

}

void oms_RQ_ORDERS_STATUS::before_send(void) const
{

}




oms_RQ_EXECS_HISTORIC::oms_RQ_EXECS_HISTORIC ( const RQ_EXECS_HISTORIC&  parent,   const std::string&  _market,   const mtk::DateTime&  _date,   const mtk::list<mtk::trd::msg::sub_account_info >&  _list_accounts)
    :  RQ_EXECS_HISTORIC(parent),   market(_market),   date(_date),   list_accounts(_list_accounts) 
       , __internal_warning_control_fields(0)
    {  
    }



void  oms_RQ_EXECS_HISTORIC::check_recomended(void) const
{

}

void oms_RQ_EXECS_HISTORIC::before_send(void) const
{

}



    //    generate_class_qpid_variant_in_impl
    
oms_RQ_NW_LS__qpid_map::oms_RQ_NW_LS__qpid_map ( const RQ_NW_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
      :  m_static( 
parent,
   _reject_description,
   _from,
   _oms_additional_info) 
    {  
    }



    qpid::types::Variant::Map   oms_RQ_NW_LS__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
oms_RQ_MD_LS__qpid_map::oms_RQ_MD_LS__qpid_map ( const RQ_MD_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
      :  m_static( 
parent,
   _reject_description,
   _from,
   _oms_additional_info) 
    {  
    }



    qpid::types::Variant::Map   oms_RQ_MD_LS__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
oms_RQ_CC_LS__qpid_map::oms_RQ_CC_LS__qpid_map ( const RQ_CC_LS&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
      :  m_static( 
parent,
   _reject_description,
   _from,
   _oms_additional_info) 
    {  
    }



    qpid::types::Variant::Map   oms_RQ_CC_LS__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
oms_RQ_NW_MK__qpid_map::oms_RQ_NW_MK__qpid_map ( const RQ_NW_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
      :  m_static( 
parent,
   _reject_description,
   _from,
   _oms_additional_info) 
    {  
    }



    qpid::types::Variant::Map   oms_RQ_NW_MK__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
oms_RQ_MD_MK__qpid_map::oms_RQ_MD_MK__qpid_map ( const RQ_MD_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
      :  m_static( 
parent,
   _reject_description,
   _from,
   _oms_additional_info) 
    {  
    }



    qpid::types::Variant::Map   oms_RQ_MD_MK__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
oms_RQ_CC_MK__qpid_map::oms_RQ_CC_MK__qpid_map ( const RQ_CC_MK&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
      :  m_static( 
parent,
   _reject_description,
   _from,
   _oms_additional_info) 
    {  
    }



    qpid::types::Variant::Map   oms_RQ_CC_MK__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
oms_RQ_NW_SM__qpid_map::oms_RQ_NW_SM__qpid_map ( const RQ_NW_SM&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
      :  m_static( 
parent,
   _reject_description,
   _from,
   _oms_additional_info) 
    {  
    }



    qpid::types::Variant::Map   oms_RQ_NW_SM__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
oms_RQ_MD_SM__qpid_map::oms_RQ_MD_SM__qpid_map ( const RQ_MD_SM&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
      :  m_static( 
parent,
   _reject_description,
   _from,
   _oms_additional_info) 
    {  
    }



    qpid::types::Variant::Map   oms_RQ_MD_SM__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
oms_RQ_CC_SM__qpid_map::oms_RQ_CC_SM__qpid_map ( const RQ_CC_SM&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
      :  m_static( 
parent,
   _reject_description,
   _from,
   _oms_additional_info) 
    {  
    }



    qpid::types::Variant::Map   oms_RQ_CC_SM__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
oms_RQ_NW_SL__qpid_map::oms_RQ_NW_SL__qpid_map ( const RQ_NW_SL&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
      :  m_static( 
parent,
   _reject_description,
   _from,
   _oms_additional_info) 
    {  
    }



    qpid::types::Variant::Map   oms_RQ_NW_SL__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
oms_RQ_MD_SL__qpid_map::oms_RQ_MD_SL__qpid_map ( const RQ_MD_SL&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
      :  m_static( 
parent,
   _reject_description,
   _from,
   _oms_additional_info) 
    {  
    }



    qpid::types::Variant::Map   oms_RQ_MD_SL__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
oms_RQ_CC_SL__qpid_map::oms_RQ_CC_SL__qpid_map ( const RQ_CC_SL&  parent,   const std::string&  _reject_description,   const std::string&  _from,   const std::string&  _oms_additional_info)
      :  m_static( 
parent,
   _reject_description,
   _from,
   _oms_additional_info) 
    {  
    }



    qpid::types::Variant::Map   oms_RQ_CC_SL__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
oms_RQ_ORDERS_STATUS__qpid_map::oms_RQ_ORDERS_STATUS__qpid_map ( const RQ_ORDERS_STATUS&  parent,   const std::string&  _reject_description,   const std::string&  _from)
      :  m_static( 
parent,
   _reject_description,
   _from) 
    {  
    }



    qpid::types::Variant::Map   oms_RQ_ORDERS_STATUS__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

    //    generate_class_qpid_variant_in_impl
    
oms_RQ_EXECS_HISTORIC__qpid_map::oms_RQ_EXECS_HISTORIC__qpid_map ( const RQ_EXECS_HISTORIC&  parent,   const std::string&  _market,   const mtk::DateTime&  _date,   const mtk::list<mtk::trd::msg::sub_account_info >&  _list_accounts)
      :  m_static( 
parent,
   _market,
   _date,
   _list_accounts) 
    {  
    }



    qpid::types::Variant::Map   oms_RQ_EXECS_HISTORIC__qpid_map::qpidmsg_codded_as_qpid_map (void) const
    {   qpid::types::Variant::Map result;  __internal_add2map(result, *this);  return result;  }

std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_NW_LS&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "        << "oms_additional_info:"<<   c.oms_additional_info << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_NW_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_NW_LS" <<  YAML::Value << static_cast<const RQ_NW_LS&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from        << YAML::Key << "oms_additional_info"  << YAML::Value <<   c.oms_additional_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_NW_LS & c)
{

    node["RQ_NW_LS"]   >>   static_cast<RQ_NW_LS&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;
        node["oms_additional_info"]  >> c.oms_additional_info;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_MD_LS&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "        << "oms_additional_info:"<<   c.oms_additional_info << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_MD_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_MD_LS" <<  YAML::Value << static_cast<const RQ_MD_LS&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from        << YAML::Key << "oms_additional_info"  << YAML::Value <<   c.oms_additional_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_MD_LS & c)
{

    node["RQ_MD_LS"]   >>   static_cast<RQ_MD_LS&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;
        node["oms_additional_info"]  >> c.oms_additional_info;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_LS & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_CC_LS&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "        << "oms_additional_info:"<<   c.oms_additional_info << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_CC_LS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_CC_LS" <<  YAML::Value << static_cast<const RQ_CC_LS&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from        << YAML::Key << "oms_additional_info"  << YAML::Value <<   c.oms_additional_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_CC_LS & c)
{

    node["RQ_CC_LS"]   >>   static_cast<RQ_CC_LS&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;
        node["oms_additional_info"]  >> c.oms_additional_info;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_MK & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_NW_MK&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "        << "oms_additional_info:"<<   c.oms_additional_info << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_NW_MK & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_NW_MK" <<  YAML::Value << static_cast<const RQ_NW_MK&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from        << YAML::Key << "oms_additional_info"  << YAML::Value <<   c.oms_additional_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_NW_MK & c)
{

    node["RQ_NW_MK"]   >>   static_cast<RQ_NW_MK&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;
        node["oms_additional_info"]  >> c.oms_additional_info;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_MK & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_MD_MK&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "        << "oms_additional_info:"<<   c.oms_additional_info << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_MD_MK & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_MD_MK" <<  YAML::Value << static_cast<const RQ_MD_MK&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from        << YAML::Key << "oms_additional_info"  << YAML::Value <<   c.oms_additional_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_MD_MK & c)
{

    node["RQ_MD_MK"]   >>   static_cast<RQ_MD_MK&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;
        node["oms_additional_info"]  >> c.oms_additional_info;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_MK & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_CC_MK&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "        << "oms_additional_info:"<<   c.oms_additional_info << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_CC_MK & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_CC_MK" <<  YAML::Value << static_cast<const RQ_CC_MK&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from        << YAML::Key << "oms_additional_info"  << YAML::Value <<   c.oms_additional_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_CC_MK & c)
{

    node["RQ_CC_MK"]   >>   static_cast<RQ_CC_MK&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;
        node["oms_additional_info"]  >> c.oms_additional_info;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_SM & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_NW_SM&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "        << "oms_additional_info:"<<   c.oms_additional_info << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_NW_SM & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_NW_SM" <<  YAML::Value << static_cast<const RQ_NW_SM&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from        << YAML::Key << "oms_additional_info"  << YAML::Value <<   c.oms_additional_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_NW_SM & c)
{

    node["RQ_NW_SM"]   >>   static_cast<RQ_NW_SM&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;
        node["oms_additional_info"]  >> c.oms_additional_info;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_SM & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_MD_SM&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "        << "oms_additional_info:"<<   c.oms_additional_info << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_MD_SM & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_MD_SM" <<  YAML::Value << static_cast<const RQ_MD_SM&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from        << YAML::Key << "oms_additional_info"  << YAML::Value <<   c.oms_additional_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_MD_SM & c)
{

    node["RQ_MD_SM"]   >>   static_cast<RQ_MD_SM&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;
        node["oms_additional_info"]  >> c.oms_additional_info;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_SM & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_CC_SM&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "        << "oms_additional_info:"<<   c.oms_additional_info << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_CC_SM & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_CC_SM" <<  YAML::Value << static_cast<const RQ_CC_SM&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from        << YAML::Key << "oms_additional_info"  << YAML::Value <<   c.oms_additional_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_CC_SM & c)
{

    node["RQ_CC_SM"]   >>   static_cast<RQ_CC_SM&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;
        node["oms_additional_info"]  >> c.oms_additional_info;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_NW_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_NW_SL&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "        << "oms_additional_info:"<<   c.oms_additional_info << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_NW_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_NW_SL" <<  YAML::Value << static_cast<const RQ_NW_SL&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from        << YAML::Key << "oms_additional_info"  << YAML::Value <<   c.oms_additional_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_NW_SL & c)
{

    node["RQ_NW_SL"]   >>   static_cast<RQ_NW_SL&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;
        node["oms_additional_info"]  >> c.oms_additional_info;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_MD_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_MD_SL&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "        << "oms_additional_info:"<<   c.oms_additional_info << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_MD_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_MD_SL" <<  YAML::Value << static_cast<const RQ_MD_SL&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from        << YAML::Key << "oms_additional_info"  << YAML::Value <<   c.oms_additional_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_MD_SL & c)
{

    node["RQ_MD_SL"]   >>   static_cast<RQ_MD_SL&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;
        node["oms_additional_info"]  >> c.oms_additional_info;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_CC_SL & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_CC_SL&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "        << "oms_additional_info:"<<   c.oms_additional_info << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_CC_SL & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_CC_SL" <<  YAML::Value << static_cast<const RQ_CC_SL&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from        << YAML::Key << "oms_additional_info"  << YAML::Value <<   c.oms_additional_info
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_CC_SL & c)
{

    node["RQ_CC_SL"]   >>   static_cast<RQ_CC_SL&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;
        node["oms_additional_info"]  >> c.oms_additional_info;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_ORDERS_STATUS & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_ORDERS_STATUS&>(c)  << ")" 
        << "reject_description:"<<   c.reject_description << "  "        << "from:"<<   c.from << "  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_ORDERS_STATUS & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_ORDERS_STATUS" <<  YAML::Value << static_cast<const RQ_ORDERS_STATUS&>(c)  
        << YAML::Key << "reject_description"  << YAML::Value <<   c.reject_description        << YAML::Key << "from"  << YAML::Value <<   c.from
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_ORDERS_STATUS & c)
{

    node["RQ_ORDERS_STATUS"]   >>   static_cast<RQ_ORDERS_STATUS&>(c)  ;

        node["reject_description"]  >> c.reject_description;
        node["from"]  >> c.from;


};


std::ostream& operator<< (std::ostream& o, const oms_RQ_EXECS_HISTORIC & c)
{
    o << "{ "
    << "("  <<  static_cast<const RQ_EXECS_HISTORIC&>(c)  << ")" 
        << "market:"<<   c.market << "  "        << "date:"<<   c.date << "  "        << "list_accounts:"<< c.list_accounts<<"  "
        << " }";
    return o;
};



YAML::Emitter& operator << (YAML::Emitter& o, const oms_RQ_EXECS_HISTORIC & c)
{
    o << YAML::BeginMap
    << YAML::Key << "RQ_EXECS_HISTORIC" <<  YAML::Value << static_cast<const RQ_EXECS_HISTORIC&>(c)  
        << YAML::Key << "market"  << YAML::Value <<   c.market        << YAML::Key << "date"  << YAML::Value <<   c.date        << YAML::Key << "list_accounts"  << YAML::Value << c.list_accounts
        << YAML::EndMap;
    return o;
};



void  operator >> (const YAML::Node& node, oms_RQ_EXECS_HISTORIC & c)
{

    node["RQ_EXECS_HISTORIC"]   >>   static_cast<RQ_EXECS_HISTORIC&>(c)  ;

        node["market"]  >> c.market;
        node["date"]  >> c.date;
        node["list_accounts"]  >> c.list_accounts;


};


bool operator== (const oms_RQ_NW_LS& a, const oms_RQ_NW_LS& b)
{
    return ( (static_cast<const RQ_NW_LS&>(a)   ==  static_cast<const RQ_NW_LS&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&          a.oms_additional_info ==  b.oms_additional_info  &&   true  );
};

bool operator!= (const oms_RQ_NW_LS& a, const oms_RQ_NW_LS& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_MD_LS& a, const oms_RQ_MD_LS& b)
{
    return ( (static_cast<const RQ_MD_LS&>(a)   ==  static_cast<const RQ_MD_LS&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&          a.oms_additional_info ==  b.oms_additional_info  &&   true  );
};

bool operator!= (const oms_RQ_MD_LS& a, const oms_RQ_MD_LS& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_CC_LS& a, const oms_RQ_CC_LS& b)
{
    return ( (static_cast<const RQ_CC_LS&>(a)   ==  static_cast<const RQ_CC_LS&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&          a.oms_additional_info ==  b.oms_additional_info  &&   true  );
};

bool operator!= (const oms_RQ_CC_LS& a, const oms_RQ_CC_LS& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_NW_MK& a, const oms_RQ_NW_MK& b)
{
    return ( (static_cast<const RQ_NW_MK&>(a)   ==  static_cast<const RQ_NW_MK&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&          a.oms_additional_info ==  b.oms_additional_info  &&   true  );
};

bool operator!= (const oms_RQ_NW_MK& a, const oms_RQ_NW_MK& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_MD_MK& a, const oms_RQ_MD_MK& b)
{
    return ( (static_cast<const RQ_MD_MK&>(a)   ==  static_cast<const RQ_MD_MK&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&          a.oms_additional_info ==  b.oms_additional_info  &&   true  );
};

bool operator!= (const oms_RQ_MD_MK& a, const oms_RQ_MD_MK& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_CC_MK& a, const oms_RQ_CC_MK& b)
{
    return ( (static_cast<const RQ_CC_MK&>(a)   ==  static_cast<const RQ_CC_MK&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&          a.oms_additional_info ==  b.oms_additional_info  &&   true  );
};

bool operator!= (const oms_RQ_CC_MK& a, const oms_RQ_CC_MK& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_NW_SM& a, const oms_RQ_NW_SM& b)
{
    return ( (static_cast<const RQ_NW_SM&>(a)   ==  static_cast<const RQ_NW_SM&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&          a.oms_additional_info ==  b.oms_additional_info  &&   true  );
};

bool operator!= (const oms_RQ_NW_SM& a, const oms_RQ_NW_SM& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_MD_SM& a, const oms_RQ_MD_SM& b)
{
    return ( (static_cast<const RQ_MD_SM&>(a)   ==  static_cast<const RQ_MD_SM&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&          a.oms_additional_info ==  b.oms_additional_info  &&   true  );
};

bool operator!= (const oms_RQ_MD_SM& a, const oms_RQ_MD_SM& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_CC_SM& a, const oms_RQ_CC_SM& b)
{
    return ( (static_cast<const RQ_CC_SM&>(a)   ==  static_cast<const RQ_CC_SM&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&          a.oms_additional_info ==  b.oms_additional_info  &&   true  );
};

bool operator!= (const oms_RQ_CC_SM& a, const oms_RQ_CC_SM& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_NW_SL& a, const oms_RQ_NW_SL& b)
{
    return ( (static_cast<const RQ_NW_SL&>(a)   ==  static_cast<const RQ_NW_SL&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&          a.oms_additional_info ==  b.oms_additional_info  &&   true  );
};

bool operator!= (const oms_RQ_NW_SL& a, const oms_RQ_NW_SL& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_MD_SL& a, const oms_RQ_MD_SL& b)
{
    return ( (static_cast<const RQ_MD_SL&>(a)   ==  static_cast<const RQ_MD_SL&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&          a.oms_additional_info ==  b.oms_additional_info  &&   true  );
};

bool operator!= (const oms_RQ_MD_SL& a, const oms_RQ_MD_SL& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_CC_SL& a, const oms_RQ_CC_SL& b)
{
    return ( (static_cast<const RQ_CC_SL&>(a)   ==  static_cast<const RQ_CC_SL&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&          a.oms_additional_info ==  b.oms_additional_info  &&   true  );
};

bool operator!= (const oms_RQ_CC_SL& a, const oms_RQ_CC_SL& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_ORDERS_STATUS& a, const oms_RQ_ORDERS_STATUS& b)
{
    return ( (static_cast<const RQ_ORDERS_STATUS&>(a)   ==  static_cast<const RQ_ORDERS_STATUS&>(b))  &&           a.reject_description ==  b.reject_description  &&          a.from ==  b.from  &&   true  );
};

bool operator!= (const oms_RQ_ORDERS_STATUS& a, const oms_RQ_ORDERS_STATUS& b)
{
    return !(a==b);
};



bool operator== (const oms_RQ_EXECS_HISTORIC& a, const oms_RQ_EXECS_HISTORIC& b)
{
    return ( (static_cast<const RQ_EXECS_HISTORIC&>(a)   ==  static_cast<const RQ_EXECS_HISTORIC&>(b))  &&           a.market ==  b.market  &&          a.date ==  b.date  &&          a.list_accounts ==  b.list_accounts  &&   true  );
};

bool operator!= (const oms_RQ_EXECS_HISTORIC& a, const oms_RQ_EXECS_HISTORIC& b)
{
    return !(a==b);
};




void  copy (oms_RQ_NW_LS& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<RQ_NW_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_NW_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_NW_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;
//   field_type

                    it = mv.find("oai");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field oms_additional_info on message oms_RQ_NW_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.oms_additional_info, it->second);
                        //c.oms_additional_info = it->second;

        c.check_recomended ();
    }


void  copy (oms_RQ_NW_LS__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_LS& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_NW_LS&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));
//  field_type
        __internal_add2map(map, a.oms_additional_info, std::string("oai"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_LS__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_LS__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (oms_RQ_MD_LS& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<RQ_MD_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_MD_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_MD_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;
//   field_type

                    it = mv.find("oai");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field oms_additional_info on message oms_RQ_MD_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.oms_additional_info, it->second);
                        //c.oms_additional_info = it->second;

        c.check_recomended ();
    }


void  copy (oms_RQ_MD_LS__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_LS& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_MD_LS&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));
//  field_type
        __internal_add2map(map, a.oms_additional_info, std::string("oai"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_LS__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_LS__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (oms_RQ_CC_LS& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<RQ_CC_LS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_CC_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_CC_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;
//   field_type

                    it = mv.find("oai");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field oms_additional_info on message oms_RQ_CC_LS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.oms_additional_info, it->second);
                        //c.oms_additional_info = it->second;

        c.check_recomended ();
    }


void  copy (oms_RQ_CC_LS__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_LS& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_CC_LS&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));
//  field_type
        __internal_add2map(map, a.oms_additional_info, std::string("oai"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_LS__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_LS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_LS__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (oms_RQ_NW_MK& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<RQ_NW_MK&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_NW_MK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_NW_MK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;
//   field_type

                    it = mv.find("oai");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field oms_additional_info on message oms_RQ_NW_MK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.oms_additional_info, it->second);
                        //c.oms_additional_info = it->second;

        c.check_recomended ();
    }


void  copy (oms_RQ_NW_MK__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_MK& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_NW_MK&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));
//  field_type
        __internal_add2map(map, a.oms_additional_info, std::string("oai"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_MK__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_MK>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_MK__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (oms_RQ_MD_MK& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<RQ_MD_MK&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_MD_MK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_MD_MK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;
//   field_type

                    it = mv.find("oai");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field oms_additional_info on message oms_RQ_MD_MK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.oms_additional_info, it->second);
                        //c.oms_additional_info = it->second;

        c.check_recomended ();
    }


void  copy (oms_RQ_MD_MK__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_MK& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_MD_MK&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));
//  field_type
        __internal_add2map(map, a.oms_additional_info, std::string("oai"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_MK__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_MK>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_MK__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (oms_RQ_CC_MK& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<RQ_CC_MK&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_CC_MK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_CC_MK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;
//   field_type

                    it = mv.find("oai");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field oms_additional_info on message oms_RQ_CC_MK::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.oms_additional_info, it->second);
                        //c.oms_additional_info = it->second;

        c.check_recomended ();
    }


void  copy (oms_RQ_CC_MK__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_MK& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_CC_MK&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));
//  field_type
        __internal_add2map(map, a.oms_additional_info, std::string("oai"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_MK__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_MK>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_MK__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (oms_RQ_NW_SM& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<RQ_NW_SM&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_NW_SM::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_NW_SM::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;
//   field_type

                    it = mv.find("oai");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field oms_additional_info on message oms_RQ_NW_SM::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.oms_additional_info, it->second);
                        //c.oms_additional_info = it->second;

        c.check_recomended ();
    }


void  copy (oms_RQ_NW_SM__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_SM& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_NW_SM&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));
//  field_type
        __internal_add2map(map, a.oms_additional_info, std::string("oai"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_SM__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_SM>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_SM__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (oms_RQ_MD_SM& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<RQ_MD_SM&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_MD_SM::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_MD_SM::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;
//   field_type

                    it = mv.find("oai");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field oms_additional_info on message oms_RQ_MD_SM::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.oms_additional_info, it->second);
                        //c.oms_additional_info = it->second;

        c.check_recomended ();
    }


void  copy (oms_RQ_MD_SM__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_SM& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_MD_SM&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));
//  field_type
        __internal_add2map(map, a.oms_additional_info, std::string("oai"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_SM__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_SM>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_SM__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (oms_RQ_CC_SM& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<RQ_CC_SM&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_CC_SM::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_CC_SM::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;
//   field_type

                    it = mv.find("oai");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field oms_additional_info on message oms_RQ_CC_SM::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.oms_additional_info, it->second);
                        //c.oms_additional_info = it->second;

        c.check_recomended ();
    }


void  copy (oms_RQ_CC_SM__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_SM& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_CC_SM&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));
//  field_type
        __internal_add2map(map, a.oms_additional_info, std::string("oai"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_SM__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_SM>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_SM__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (oms_RQ_NW_SL& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<RQ_NW_SL&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_NW_SL::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_NW_SL::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;
//   field_type

                    it = mv.find("oai");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field oms_additional_info on message oms_RQ_NW_SL::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.oms_additional_info, it->second);
                        //c.oms_additional_info = it->second;

        c.check_recomended ();
    }


void  copy (oms_RQ_NW_SL__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_NW_SL&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));
//  field_type
        __internal_add2map(map, a.oms_additional_info, std::string("oai"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_NW_SL__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_NW_SL__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (oms_RQ_MD_SL& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<RQ_MD_SL&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_MD_SL::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_MD_SL::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;
//   field_type

                    it = mv.find("oai");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field oms_additional_info on message oms_RQ_MD_SL::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.oms_additional_info, it->second);
                        //c.oms_additional_info = it->second;

        c.check_recomended ();
    }


void  copy (oms_RQ_MD_SL__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_MD_SL&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));
//  field_type
        __internal_add2map(map, a.oms_additional_info, std::string("oai"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_MD_SL__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_MD_SL__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (oms_RQ_CC_SL& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<RQ_CC_SL&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_CC_SL::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_CC_SL::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;
//   field_type

                    it = mv.find("oai");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field oms_additional_info on message oms_RQ_CC_SL::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.oms_additional_info, it->second);
                        //c.oms_additional_info = it->second;

        c.check_recomended ();
    }


void  copy (oms_RQ_CC_SL__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_SL& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_CC_SL&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));
//  field_type
        __internal_add2map(map, a.oms_additional_info, std::string("oai"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_CC_SL__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_SL>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_CC_SL__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (oms_RQ_ORDERS_STATUS& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<RQ_ORDERS_STATUS&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("rjd");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field reject_description on message oms_RQ_ORDERS_STATUS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.reject_description, it->second);
                        //c.reject_description = it->second;
//   field_type

                    it = mv.find("from");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field from on message oms_RQ_ORDERS_STATUS::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.from, it->second);
                        //c.from = it->second;

        c.check_recomended ();
    }


void  copy (oms_RQ_ORDERS_STATUS__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_ORDERS_STATUS& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_ORDERS_STATUS&>(a));

//  field_type
        __internal_add2map(map, a.reject_description, std::string("rjd"));
//  field_type
        __internal_add2map(map, a.from, std::string("from"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_ORDERS_STATUS__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_ORDERS_STATUS>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_ORDERS_STATUS__qpid_map>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}





void  copy (oms_RQ_EXECS_HISTORIC& c, const qpid::types::Variant& v)
    {
        qpid::types::Variant::Map  mv = v.asMap();
copy(static_cast<RQ_EXECS_HISTORIC&>(c), v);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
//   field_type

                    it = mv.find("mk");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field market on message oms_RQ_EXECS_HISTORIC::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.market, it->second);
                        //c.market = it->second;
//   field_type

                    it = mv.find("date");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field date on message oms_RQ_EXECS_HISTORIC::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.date, it->second);
                        //c.date = it->second;
//   sub_msg_type

                    it = mv.find("lacc");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field list_accounts on message oms_RQ_EXECS_HISTORIC::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.list_accounts, it->second);
                        //__internal_qpid_fill(c.list_accounts, it->second.asMap());

        c.check_recomended ();
    }


void  copy (oms_RQ_EXECS_HISTORIC__qpid_map& c, const qpid::types::Variant& v)
    {
        copy(c.m_static, v);
        c.m_qpid_map = v.asMap();
    }

void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_EXECS_HISTORIC& a)
{

    a.before_send();
    a.check_recomended();
//  parent
__internal_add2map(map, static_cast<const RQ_EXECS_HISTORIC&>(a));

//  field_type
        __internal_add2map(map, a.market, std::string("mk"));
//  field_type
        __internal_add2map(map, a.date, std::string("date"));
//  sub_msg_type
        __internal_add2map(map, a.list_accounts, std::string("lacc"));


};


void __internal_add2map (qpid::types::Variant::Map& map, const oms_RQ_EXECS_HISTORIC__qpid_map& a)
{
    a.m_static.before_send();
    a.m_static.check_recomended();

    __internal_add2map(map, a.m_static);
    mtk::merge__keep_destination(map, a.m_qpid_map);
};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_EXECS_HISTORIC>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}

void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<oms_RQ_EXECS_HISTORIC__qpid_map>& a, const std::string& field)
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
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)
//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)

qpid::types::Variant::Map   oms_RQ_NW_LS::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_NW_LS&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));
//  field_type
//        content["oai"] = this->oms_additional_info;
        __internal_add2map(content, this->oms_additional_info, std::string("oai"));



    
    return content;
};




qpid::types::Variant::Map   oms_RQ_MD_LS::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_MD_LS&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));
//  field_type
//        content["oai"] = this->oms_additional_info;
        __internal_add2map(content, this->oms_additional_info, std::string("oai"));



    
    return content;
};




qpid::types::Variant::Map   oms_RQ_CC_LS::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_CC_LS&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));
//  field_type
//        content["oai"] = this->oms_additional_info;
        __internal_add2map(content, this->oms_additional_info, std::string("oai"));



    
    return content;
};




qpid::types::Variant::Map   oms_RQ_NW_MK::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_NW_MK&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));
//  field_type
//        content["oai"] = this->oms_additional_info;
        __internal_add2map(content, this->oms_additional_info, std::string("oai"));



    
    return content;
};




qpid::types::Variant::Map   oms_RQ_MD_MK::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_MD_MK&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));
//  field_type
//        content["oai"] = this->oms_additional_info;
        __internal_add2map(content, this->oms_additional_info, std::string("oai"));



    
    return content;
};




qpid::types::Variant::Map   oms_RQ_CC_MK::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_CC_MK&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));
//  field_type
//        content["oai"] = this->oms_additional_info;
        __internal_add2map(content, this->oms_additional_info, std::string("oai"));



    
    return content;
};




qpid::types::Variant::Map   oms_RQ_NW_SM::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_NW_SM&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));
//  field_type
//        content["oai"] = this->oms_additional_info;
        __internal_add2map(content, this->oms_additional_info, std::string("oai"));



    
    return content;
};




qpid::types::Variant::Map   oms_RQ_MD_SM::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_MD_SM&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));
//  field_type
//        content["oai"] = this->oms_additional_info;
        __internal_add2map(content, this->oms_additional_info, std::string("oai"));



    
    return content;
};




qpid::types::Variant::Map   oms_RQ_CC_SM::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_CC_SM&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));
//  field_type
//        content["oai"] = this->oms_additional_info;
        __internal_add2map(content, this->oms_additional_info, std::string("oai"));



    
    return content;
};




qpid::types::Variant::Map   oms_RQ_NW_SL::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_NW_SL&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));
//  field_type
//        content["oai"] = this->oms_additional_info;
        __internal_add2map(content, this->oms_additional_info, std::string("oai"));



    
    return content;
};




qpid::types::Variant::Map   oms_RQ_MD_SL::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_MD_SL&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));
//  field_type
//        content["oai"] = this->oms_additional_info;
        __internal_add2map(content, this->oms_additional_info, std::string("oai"));



    
    return content;
};




qpid::types::Variant::Map   oms_RQ_CC_SL::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_CC_SL&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));
//  field_type
//        content["oai"] = this->oms_additional_info;
        __internal_add2map(content, this->oms_additional_info, std::string("oai"));



    
    return content;
};




qpid::types::Variant::Map   oms_RQ_ORDERS_STATUS::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_ORDERS_STATUS&>(*this));

//  field_type
//        content["rjd"] = this->reject_description;
        __internal_add2map(content, this->reject_description, std::string("rjd"));
//  field_type
//        content["from"] = this->from;
        __internal_add2map(content, this->from, std::string("from"));



    
    return content;
};




qpid::types::Variant::Map   oms_RQ_EXECS_HISTORIC::qpidmsg_codded_as_qpid_map (void) const
{
    qpid::types::Variant::Map   content;

//  parent
__internal_add2map(content, static_cast<const RQ_EXECS_HISTORIC&>(*this));

//  field_type
//        content["mk"] = this->market;
        __internal_add2map(content, this->market, std::string("mk"));
//  field_type
//        content["date"] = this->date;
        __internal_add2map(content, this->date, std::string("date"));
//  sub_msg_type
//        content["lacc"] =  qpidmsg_coded_as_qpid_Map(this->list_accounts);
        __internal_add2map(content, this->list_accounts, std::string("lacc"));



    
    return content;
};




    oms_RQ_NW_LS  __internal_get_default(oms_RQ_NW_LS*)
    {
        return oms_RQ_NW_LS(
__internal_get_default((RQ_NW_LS*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_MD_LS  __internal_get_default(oms_RQ_MD_LS*)
    {
        return oms_RQ_MD_LS(
__internal_get_default((RQ_MD_LS*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_CC_LS  __internal_get_default(oms_RQ_CC_LS*)
    {
        return oms_RQ_CC_LS(
__internal_get_default((RQ_CC_LS*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_NW_MK  __internal_get_default(oms_RQ_NW_MK*)
    {
        return oms_RQ_NW_MK(
__internal_get_default((RQ_NW_MK*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_MD_MK  __internal_get_default(oms_RQ_MD_MK*)
    {
        return oms_RQ_MD_MK(
__internal_get_default((RQ_MD_MK*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_CC_MK  __internal_get_default(oms_RQ_CC_MK*)
    {
        return oms_RQ_CC_MK(
__internal_get_default((RQ_CC_MK*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_NW_SM  __internal_get_default(oms_RQ_NW_SM*)
    {
        return oms_RQ_NW_SM(
__internal_get_default((RQ_NW_SM*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_MD_SM  __internal_get_default(oms_RQ_MD_SM*)
    {
        return oms_RQ_MD_SM(
__internal_get_default((RQ_MD_SM*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_CC_SM  __internal_get_default(oms_RQ_CC_SM*)
    {
        return oms_RQ_CC_SM(
__internal_get_default((RQ_CC_SM*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_NW_SL  __internal_get_default(oms_RQ_NW_SL*)
    {
        return oms_RQ_NW_SL(
__internal_get_default((RQ_NW_SL*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_MD_SL  __internal_get_default(oms_RQ_MD_SL*)
    {
        return oms_RQ_MD_SL(
__internal_get_default((RQ_MD_SL*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_CC_SL  __internal_get_default(oms_RQ_CC_SL*)
    {
        return oms_RQ_CC_SL(
__internal_get_default((RQ_CC_SL*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_ORDERS_STATUS  __internal_get_default(oms_RQ_ORDERS_STATUS*)
    {
        return oms_RQ_ORDERS_STATUS(
__internal_get_default((RQ_ORDERS_STATUS*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    oms_RQ_EXECS_HISTORIC  __internal_get_default(oms_RQ_EXECS_HISTORIC*)
    {
        return oms_RQ_EXECS_HISTORIC(
__internal_get_default((RQ_EXECS_HISTORIC*)0), //   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((mtk::DateTime*)0),
//   sub_msg_type
   __internal_get_default((mtk::list<mtk::trd::msg::sub_account_info >*)0)
            );
    }
    
oms_RQ_NW_LS::oms_RQ_NW_LS (const qpid::types::Variant::Map&  mv)
     : RQ_NW_LS(mv), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)),
//   field_type
   oms_additional_info(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


oms_RQ_NW_LS__qpid_map::oms_RQ_NW_LS__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

oms_RQ_MD_LS::oms_RQ_MD_LS (const qpid::types::Variant::Map&  mv)
     : RQ_MD_LS(mv), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)),
//   field_type
   oms_additional_info(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


oms_RQ_MD_LS__qpid_map::oms_RQ_MD_LS__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

oms_RQ_CC_LS::oms_RQ_CC_LS (const qpid::types::Variant::Map&  mv)
     : RQ_CC_LS(mv), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)),
//   field_type
   oms_additional_info(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


oms_RQ_CC_LS__qpid_map::oms_RQ_CC_LS__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

oms_RQ_NW_MK::oms_RQ_NW_MK (const qpid::types::Variant::Map&  mv)
     : RQ_NW_MK(mv), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)),
//   field_type
   oms_additional_info(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


oms_RQ_NW_MK__qpid_map::oms_RQ_NW_MK__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

oms_RQ_MD_MK::oms_RQ_MD_MK (const qpid::types::Variant::Map&  mv)
     : RQ_MD_MK(mv), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)),
//   field_type
   oms_additional_info(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


oms_RQ_MD_MK__qpid_map::oms_RQ_MD_MK__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

oms_RQ_CC_MK::oms_RQ_CC_MK (const qpid::types::Variant::Map&  mv)
     : RQ_CC_MK(mv), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)),
//   field_type
   oms_additional_info(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


oms_RQ_CC_MK__qpid_map::oms_RQ_CC_MK__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

oms_RQ_NW_SM::oms_RQ_NW_SM (const qpid::types::Variant::Map&  mv)
     : RQ_NW_SM(mv), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)),
//   field_type
   oms_additional_info(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


oms_RQ_NW_SM__qpid_map::oms_RQ_NW_SM__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

oms_RQ_MD_SM::oms_RQ_MD_SM (const qpid::types::Variant::Map&  mv)
     : RQ_MD_SM(mv), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)),
//   field_type
   oms_additional_info(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


oms_RQ_MD_SM__qpid_map::oms_RQ_MD_SM__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

oms_RQ_CC_SM::oms_RQ_CC_SM (const qpid::types::Variant::Map&  mv)
     : RQ_CC_SM(mv), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)),
//   field_type
   oms_additional_info(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


oms_RQ_CC_SM__qpid_map::oms_RQ_CC_SM__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

oms_RQ_NW_SL::oms_RQ_NW_SL (const qpid::types::Variant::Map&  mv)
     : RQ_NW_SL(mv), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)),
//   field_type
   oms_additional_info(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


oms_RQ_NW_SL__qpid_map::oms_RQ_NW_SL__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

oms_RQ_MD_SL::oms_RQ_MD_SL (const qpid::types::Variant::Map&  mv)
     : RQ_MD_SL(mv), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)),
//   field_type
   oms_additional_info(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


oms_RQ_MD_SL__qpid_map::oms_RQ_MD_SL__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

oms_RQ_CC_SL::oms_RQ_CC_SL (const qpid::types::Variant::Map&  mv)
     : RQ_CC_SL(mv), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)),
//   field_type
   oms_additional_info(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


oms_RQ_CC_SL__qpid_map::oms_RQ_CC_SL__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

oms_RQ_ORDERS_STATUS::oms_RQ_ORDERS_STATUS (const qpid::types::Variant::Map&  mv)
     : RQ_ORDERS_STATUS(mv), //   field_type
   reject_description(__internal_get_default((std::string*)0)),
//   field_type
   from(__internal_get_default((std::string*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


oms_RQ_ORDERS_STATUS__qpid_map::oms_RQ_ORDERS_STATUS__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    

oms_RQ_EXECS_HISTORIC::oms_RQ_EXECS_HISTORIC (const qpid::types::Variant::Map&  mv)
     : RQ_EXECS_HISTORIC(mv), //   field_type
   market(__internal_get_default((std::string*)0)),
//   field_type
   date(__internal_get_default((mtk::DateTime*)0)),
//   sub_msg_type
   list_accounts(__internal_get_default((mtk::list<mtk::trd::msg::sub_account_info >*)0)) 
    {
        copy(*this, mv);
        check_recomended ();  
    }


oms_RQ_EXECS_HISTORIC__qpid_map::oms_RQ_EXECS_HISTORIC__qpid_map (const qpid::types::Variant::Map&  mv)
    :  m_static(mv), m_qpid_map(mv)
    {
    }
    
mtk::t_qpid_filter  oms_RQ_NW_LS::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_NW_LS::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_NW_LS::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_NW_LS::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_MD_LS::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_MD_LS::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_MD_LS::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_MD_LS::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_CC_LS::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_CC_LS::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_CC_LS::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_CC_LS::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_NW_MK::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_NW_MK::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_NW_MK::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_NW_MK::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_MD_MK::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_MD_MK::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_MD_MK::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_MD_MK::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_CC_MK::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_CC_MK::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_CC_MK::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_CC_MK::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_NW_SM::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_NW_SM::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_NW_SM::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_NW_SM::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_MD_SM::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_MD_SM::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_MD_SM::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_MD_SM::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_CC_SM::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_CC_SM::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_CC_SM::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_CC_SM::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_NW_SL::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_NW_SL::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_NW_SL::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_NW_SL::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_MD_SL::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_MD_SL::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_MD_SL::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_MD_SL::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_CC_SL::get_in_subject (const std::string& invariant_product_code_market,const std::string& invariant_product_code_product,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << invariant_product_code_market << "." << invariant_product_code_product << "." << from << ".TRD"));
    }
    mtk::t_qpid_filter  oms_RQ_CC_SL::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->invariant.product_code.market << "." << this->invariant.product_code.product << "." << this->from << ".TRD"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_CC_SL::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_CC_SL::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_ORDERS_STATUS::get_in_subject (const std::string& market,const std::string& from)
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << market << "." << from << ".RQORDST"));
    }
    mtk::t_qpid_filter  oms_RQ_ORDERS_STATUS::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("MK.OMS." << this->market << "." << this->from << ".RQORDST"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_ORDERS_STATUS::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_address  oms_RQ_ORDERS_STATUS::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("CLI_MK"));
    }
    mtk::t_qpid_filter  oms_RQ_EXECS_HISTORIC::get_in_subject ()
    {
        return mtk::t_qpid_filter(MTK_SS("GS.omsRQEXHIST"));
    }
    mtk::t_qpid_filter  oms_RQ_EXECS_HISTORIC::get_out_subject (void) const
    {
        return mtk::t_qpid_filter(MTK_SS("GS.omsRQEXHIST"));
    }
    /*static*/  mtk::t_qpid_address  oms_RQ_EXECS_HISTORIC::static_get_qpid_address ()
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    mtk::t_qpid_address  oms_RQ_EXECS_HISTORIC::get_qpid_address (void) const
    {
        return mtk::t_qpid_address(MTK_SS("ALL_GS"));
    }
    

};   //namespace mtk {
};   //namespace trd {
};   //namespace msg {


