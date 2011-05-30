#include "msg_common_support.h"
#include "msg_common.h"

#include "support/alarm.h"
 
namespace mtk {
      namespace msg {

          
          
bool is_valid (const sub_request_info& req_info)
{
    if (req_info.req_id.session_id ==""  ||  req_info.req_id.req_code==""  ||  req_info.process_info.location.client_code =="")
        return false;
    return true;
}

bool is_valid (const sub_product_code& pc)
{
    if (pc.market ==""  ||  pc.product =="")
        return false;
    return true;
}


bool operator< (const sub_product_code& p1, const sub_product_code& p2)
{
    if      (p1.market < p2.market)
        return true;
    else if (p1.market == p2.market  &&  p1.product < p2.product)
        return true;
    return false;
}




      };   //namespace msg {
};  //namespace mtk {
