#ifndef msg_admin_support_h
#define msg_admin_support_h


#include "support/alarm.h"
#include "qpid/types/Variant.h"





namespace mtk
{

    
inline std::ostream& operator<< (std::ostream& os, const mtk::alEnPriority& p)

{

    switch (p)
    {
        case (mtk::alPriorCritic):          os << "critic" ;         break;
        case (mtk::alPriorError):           os << "error"  ;         break;
        case (mtk::alPriorStats):           os << "stats"  ;         break;
        case (mtk::alPriorWarning):         os << "warning";         break;
        case (mtk::alPriorDebug):           os << "debug"  ;         break;
        default:                            os << "???";
    }
    return os;
}



inline mtk::alEnPriority  __internal_get_default (mtk::alEnPriority*)
{
    return mtk::alPriorCritic;
}
inline void  copy(mtk::alEnPriority& result, const qpid::types::Variant& v)
{
    result = mtk::alEnPriority(v.asInt8());
}
inline void __internal_add2map (qpid::types::Variant::Map& map, mtk::alEnPriority a, const std::string& key)
{
    map[key] = int8_t(a);
}


inline std::ostream& operator<< (std::ostream& os, const mtk::alEnType& p)

{

    switch (p)
    {
        case (mtk::alTypeNoPermisions):     os << "no_permisions";         break;
        case (mtk::alTypeOverflow):         os << "overflow"     ;         break;
        case (mtk::alTypeRealTime):         os << "realtime"     ;         break;
        case (mtk::alTypeUnknown):          os << "unknown"      ;         break;
        case (mtk::alTypeLogicError):       os << "logicerror"   ;         break;
        default:                            os << "???";
    }
    return os;
}



inline mtk::alEnType  __internal_get_default (mtk::alEnType*)
{
    return mtk::alTypeNoPermisions;
}
inline void  copy(mtk::alEnType& result, const qpid::types::Variant& v)
{
    result = mtk::alEnType(v.asInt8());
}
inline void __internal_add2map (qpid::types::Variant::Map& map, mtk::alEnType a, const std::string& key)
{
    map[key] = int8_t(a);
}

    

};  //namespace mtk

#endif // msg_admin_support_h
