 #include "msg_trd_common.h"
 
namespace mtk {

   namespace trd {

       namespace msg {

           
           
           
           
           
bool is_valid (const sub_order_id& ord_id)
{
    if (ord_id.session_id ==""  ||  ord_id.req_code=="")
        return false;
    return true;
}
           
           
bool operator< (const sub_order_id& p1, const sub_order_id& p2)
{
    if      (p1.session_id< p2.session_id)
        return true;
    else if (p1.session_id==p2.session_id  &&  p1.req_code<p2.req_code)
        return true;
    else
        return false;
}





std::ostream& operator<< (std::ostream& os, const enBuySell& d)
{

    if      (d==buy)    os << "buy";

    else if (d==sell)   os << "sell";

    else                os << "ERROR";

    return os;

}

YAML::Emitter& operator<< (YAML::Emitter& o, const enBuySell& s)
{

    if      (s==buy)    o << "buy";

    else if (s==sell)   o << "sell";

    else                o << "ERROR";

    return o;

}



void   operator>> (const YAML::Node& n, enBuySell& bs)
{

    std::string sbs;
    
    n >> sbs;
    
    if      (sbs=="buy")        bs = buy;
    else if (sbs=="sell")       bs = sell;
    else    throw "PENDING";
}




enBuySell  __internal_get_default (enBuySell*)
{
    return buy;
}
void  copy(enBuySell& result, const qpid::types::Variant& v)
{
    result = enBuySell(v.asInt8());
}
void __internal_add2map (qpid::types::Variant::Map& map, enBuySell a, const std::string& key)
{
    map[key] = int8_t(a);
}

           
           
           
           
           
       };   //namespace msg {

   };  //namespace trd {

};  //namespace mtk {
