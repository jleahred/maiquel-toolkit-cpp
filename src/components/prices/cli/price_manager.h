#ifndef PRICE_MANAGER_H
#define PRICE_MANAGER_H


/*      request for load prices
 *      signal modifications
 *      receive invalidation of market or product
 * 
 * 
 */ 



#include "components/msg_common.h"
#include "components/prices/msg_prices.h"
#include "support/signalslot.hpp"



namespace mtk
{

    

namespace prices
{
   
    
    
class price_manager :  public mtk::SignalReceptor
{
    typedef  price_manager  CLASS_NAME;

public:
	price_manager(const mtk::msg::sub_product_code&  product_code);
	~price_manager();
    
    const mtk::msg::sub_product_code                        get_product_code(void) const { return product_code; }
    const mtk::prices::msg::pub_best_prices&                get_best_prices(void) const  { return best_prices; }
    mtk::Signal<const mtk::prices::msg::pub_best_prices&>   signal_best_prices_update;

private:
    const mtk::msg::sub_product_code  product_code;
    
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::pub_best_prices> > h_best_prices;
    mtk::prices::msg::pub_best_prices  best_prices;    
    void on_price_update(const mtk::prices::msg::pub_best_prices& msg);
    
};



}   //  namespace prices


    template<>
    inline mtk::CountPtr< mtk::prices::price_manager > create_instance_for_factory(const mtk::msg::sub_product_code&  key, mtk::CountPtr<mtk::prices::price_manager> result)
    {
        result = mtk::make_cptr(new mtk::prices::price_manager(key));
        return result;
    }

}   //  namespace mtk

#endif // PRICE_MANAGER_H
