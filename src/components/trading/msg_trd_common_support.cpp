 #include "msg_trd_common.h"
 
namespace mtk {

   namespace trd {

       namespace msg {

           
           
           
           
           
bool is_valid (const sub_order_id& ord_id)
{
    if (ord_id.sess_id ==""  ||  ord_id.req_code=="")
        return false;
    return true;
}
           
           
bool operator< (const sub_order_id& p1, const sub_order_id& p2)
{
    if      (p1.sess_id< p2.sess_id)
        return true;
    else if (p1.sess_id==p2.sess_id  &&  p1.req_code<p2.req_code)
        return true;
    else
        return false;
}

           
           
           
           
           
       };   //namespace msg {

   };  //namespace trd {

};  //namespace mtk {
