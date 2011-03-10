#include "msg_common_support.h"
#include "msg_common.h"

#include "support/alarm.h"
 
namespace mtk {
      namespace msg {

          
          
bool is_valid (const sub_request_info& req_info)
{
    if (req_info.req_id.sess_id ==""  ||  req_info.req_id.req_code==""  ||  req_info.process_location.location =="")
        return false;
    return true;
}

bool is_valid (const sub_product_code& pc)
{
    if (pc.sys_code.market ==""  ||  pc.sys_code.product =="")
        return false;
    return true;
}


bool operator< (const sub_single_product_code& p1, const sub_single_product_code& p2)
{
    if (p1.code.HasValue()  ||  p2.code.HasValue())
        throw mtk::Alarm(MTK_HERE, "it isn't valid with not null code", mtk::alPriorError, mtk::alTypeNoPermisions);
    
    if      (p1.market < p2.market)
        return true;
    else if (p1.market == p2.market  &&  p1.product < p2.product)
        return true;
    return false;
}



      };   //namespace msg {
};  //namespace mtk {
