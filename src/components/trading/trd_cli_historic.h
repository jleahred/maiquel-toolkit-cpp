#ifndef __TRD_CLI_HISTORIC_ITEM__
#define __TRD_CLI_HISTORIC_ITEM__




#include "components/msg_common.h"
#include "support/fixed_number.h"
#include "support/date_time.h"
#include "support/basic_types.hpp"


namespace  mtk {
namespace  trd {
namespace  hist {


enum en_trans_type  {  tt_rq_pending,  tt_rq_confirmated, tt_rq_not_pending, tt_cf,  tt_rj  };
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
          std::string                         market_code;      //  order code or execid
          std::string                         remarks;
};




class  order_historic_dangerous_not_signal_warped
{
    mtk::non_copyable nc;
public:

        //  add_item will return  the error message, empty if there is no error
    std::string                                         add_item(const order_historic_item&  item);
    mtk::CountPtr<mtk::list<order_historic_item> >      get_items_list(void) const   { return list_historic_item;  };

    mtk::Signal<const order_historic_item&>             signal_new_item_added;
    mtk::Signal<int, const order_historic_item&>        signal_modified_item;



    std::string   get_lasttr_rjdescr (void)  const;

    order_historic_dangerous_not_signal_warped(void);

private:
    mtk::CountPtr<mtk::list<order_historic_item> >            list_historic_item;

};


class  order_historic2
{
    mtk::non_copyable nc;
public:

        //  add_item will return  the error message, empty if there is no error
    std::string                                         add_item(const order_historic_item&  item)  {  return  ptr->add_item(item);  }
    mtk::CountPtr<mtk::list<order_historic_item> >      get_items_list(void) const   { return   ptr->get_items_list();    }

    mtk::Signal<const order_historic_item&>             signal_new_item_added;
    mtk::Signal<int, const order_historic_item&>        signal_modified_item;

    std::string   get_lasttr_rjdescr (void)  const  {  return ptr->get_lasttr_rjdescr();    }



    explicit  order_historic2(const mtk::CountPtr<order_historic_dangerous_not_signal_warped> _ptr) : ptr(_ptr)
    {
        try
        {
            ptr->signal_modified_item.connect (&signal_modified_item);
            ptr->signal_new_item_added.connect(&signal_new_item_added);
        } MTK_CATCH_RETHROW("order_historic2","connecting signals")
    }

private:
    mtk::CountPtr<order_historic_dangerous_not_signal_warped>   ptr;
};


inline  mtk::CountPtr<order_historic2>   order_historic2_sig_wp_cptr(const mtk::CountPtr<order_historic_dangerous_not_signal_warped>  oh)
{
    return mtk::make_cptr(new order_historic2(oh));
}



};      //  namespace  mtk
};      //  namespace  hist {
};      //  namespace  trd

#endif // __TRD_CLI_HISTORIC_ITEM__
