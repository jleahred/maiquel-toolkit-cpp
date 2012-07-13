#ifndef PRICE_MANAGER_H
#define PRICE_MANAGER_H


/*      A better name would be product_manager
 *
 *      request for load prices
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





class  internal_price_manager__factory;



//  if you need best prices for product M::A, just create an instance of price_manager for this product,
//  connect to signal_best_prices_update  call get_best_prices to get the current value (if exists) and
//  generate the suscripcion (if necessary)



//  Calling get_best_prices
//  if doesn't exist a previus instance on this product
//      it will create a factory one
//
//  now exist almost an instance on this product
//
//  if there is no previsus call to gest_best_prices
//      it will generate a suscription to best_prices updates
//      it will request a full product info
//      it will return a null
//  else  exist a previsus suscription to get_best_prices
//      it will return the current best_prices



mtk::CountPtr<mtk::Signal<> >   get_signal_too_many_subscriptions_best_prices       (void);
mtk::CountPtr<mtk::Signal<>  >  get_signal_too_many_subscriptions_last_ex_mk_ticker (void);




class price_manager :  public mtk::SignalReceptor
{
public:
	price_manager(const mtk::msg::sub_product_code&  product_code);
    ~price_manager() {}


    mtk::msg::sub_product_code                                                                          get_product_code (void) const;

    mtk::nullable<mtk::prices::msg::sub_best_prices>                                                    get_best_prices  (void);
    mtk::Signal<const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_best_prices&>            signal_best_prices_update;

    mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>                                           get_last_mk_execs_ticker (void);
    mtk::Signal<const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_last_mk_execs_ticker&>   signal_last_mk_execs_ticker;

    mtk::nullable<mtk::prices::msg::sub_additional_info>                                                get_additional_info (void);
    mtk::Signal<const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_additional_info&>        signal_additional_info_update;

private:
    mtk::CountPtr<internal_price_manager__factory>  ptr;

    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ppc> >                    handle_best_prices_suscrp;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ppc> >                    handle_last_mk_execs_ticker;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::pub_additional_info> >    handle_addtional_info;
};








//------------------------------------------------------------------------------------------------------
//  class internal_price_manager__factory        INTERNAL
class internal_price_manager__factory :  public mtk::SignalReceptor
{
public:
	internal_price_manager__factory(const mtk::msg::sub_product_code&  product_code);
	~internal_price_manager__factory();

    const mtk::msg::sub_product_code                                                                    get_product_code(void) const { return product_code; }



    mtk::nullable<mtk::prices::msg::sub_best_prices>                                                    get_best_prices(void);
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ppc> >                        get_best_prices_suscrp_handle(void);
    mtk::Signal<const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_best_prices&>            signal_best_prices_update;


    mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker>                                           get_last_mk_execs_ticker(void);
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ppc> >                        get_mk_last_ex_ticker_suscrp_handle(void);
    mtk::Signal<const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_last_mk_execs_ticker&>   signal_last_mk_execs_ticker;


    mtk::nullable<mtk::prices::msg::sub_additional_info>                                                get_additional_info (void);
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::pub_additional_info> >        get_addtional_info_suscrp_handle(void);
    mtk::Signal<const mtk::msg::sub_product_code&, const mtk::prices::msg::sub_additional_info&>        signal_additional_info_update;


private:
    const mtk::msg::sub_product_code                    product_code;
    mtk::prices::msg::sub_full_product_info_optionals   full_prod_info;
    mtk::DateTime                                       full_prod_info_last_request;


    //mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::pub_best_prices> > h_best_prices;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ppc> > h_best_prices;
    void on_price_update(const mtk::prices::msg::ppc& msg);


    //mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::pub_last_mk_execs_ticker> > h_last_mk_execs_ticker;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::ppc> > h_last_mk_execs_ticker;
    void on_last_mk_execs_ticker_update(const mtk::prices::msg::ppc& msg);


    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::prices::msg::pub_additional_info> > h_additional_info;
    void on_addtional_info_update(const mtk::prices::msg::pub_additional_info& msg);


    void on_res_product_info(const mtk::list<mtk::prices::msg::res_product_info>& res_pi);

    void request_full_prod_info(void);
};

//  class internal_price_manager__factory
//------------------------------------------------------------------------------------------------------



}   //  namespace prices



}   //  namespace mtk

#endif // PRICE_MANAGER_H
