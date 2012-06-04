#ifndef __trd_cli_prod_pos__
#define __trd_cli_prod_pos__


#include "support/alarm.h"
#include "support/signalslot.hpp"
#include "trd_cli_ord_book.h"




namespace mtk{namespace trd{



    namespace  cli_pos_prod {

        struct  level
        {
            mtk::FixedNumber   price;
            mtk::FixedNumber   quantity;

            //level()=delete;       it doesn't work  (almost on gcc4.6)
        };



        //  INPUT


        //  OUTPUT
        mtk::Signal<const mtk::msg::sub_product_code&, const mtk::list<mtk::trd::cli_pos_prod::level>& >&         get_sig_product_updated     (void);


        //  ACCESS
        mtk::list<mtk::trd::cli_pos_prod::level>         get_product_levels        (const mtk::msg::sub_product_code& );





    };  //  namespace  cli_pos_prod {


};   //  namespace mtk
};   //  namespace trd


#endif      // __trd_cli_prod_pos__



