
#ifndef  __msg_trd_common_support__
#define  __msg_trd_common_support__



namespace mtk {

   namespace trd {

       namespace msg {

       

        enum enBuySell { buy, sell };


        class sub_order_id;


        bool is_valid (const sub_order_id& ord_id);

        bool operator<(const sub_order_id& p1, const sub_order_id& p2);




inline std::ostream& operator<< (std::ostream& os, const enBuySell& d)

{

    if      (d==buy)    os << "buy";

    else if (d==sell)   os << "sell";

    else                os << "ERROR";

    return os;

}



inline enBuySell  __internal_get_default (enBuySell*)
{
    return buy;
}
inline void  copy(enBuySell& result, const qpid::types::Variant& v)
{
    result = enBuySell(v.asInt8());
}
inline void __internal_add2map (qpid::types::Variant::Map& map, enBuySell a, const std::string& key)
{
    map[key] = int8_t(a);
}



        };   //namespace msg {

   };  //namespace trd {

};  //namespace mtk {



#endif
