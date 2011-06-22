#ifndef __TRD_CLI_HISTORIC_ITEM__
#define __TRD_CLI_HISTORIC_ITEM__




#include "components/msg_common.h"
#include "support/fixed_number.h"
#include "support/date_time.h"
#include "support/basic_types.hpp"


namespace  mtk {
namespace  trd {
namespace  hist {
    

enum en_trans_type  {  tt_rq_pending,  tt_rq_confirmed,   tt_cf,  tt_rj  };
enum en_trans_type2 {  tt2_nw,      tt2_md,     tt2_cc,     tt2_ex  };



struct  order_historic_item
{
          bool                                error;
          en_trans_type                       type;
    const en_trans_type2                      type2;
    const mtk::DateTime                       date_time;
          mtk::dtTimeQuantity                 confirmation_delay;
    const mtk::msg::sub_request_id            request_id;
    const mtk::nullable<mtk::FixedNumber>     price;
    const mtk::FixedNumber                    quantity;
    const std::string                         cli_ref;
    const std::string                         aditional_code;
          std::string                         remarks;
};




class  order_historic
{
    mtk::non_copyable nc;
public:
    
        //  add_item will return  the error message, empty if there is no error
    std::string                                         add_item(const order_historic_item&  item);
    mtk::CountPtr<mtk::list<order_historic_item> >      get_items_list(void) const   { return list_historic_item;  };
    
    mtk::Signal<const order_historic_item&>             signal_new_item_added;
    mtk::Signal<int, const order_historic_item&>        signal_modified_item;
    
    
    order_historic(void);
        
private:
    mtk::CountPtr<mtk::list<order_historic_item> >            list_historic_item;
    
};
    
    

};      //  namespace  mtk
};      //  namespace  hist {
};      //  namespace  trd

#endif // __TRD_CLI_HISTORIC_ITEM__
