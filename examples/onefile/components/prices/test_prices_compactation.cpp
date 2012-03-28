#include <iostream>

#include "components/prices/msg_prices.h"
#include "support/integer_compactor.h"


mtk::prices::msg::sub_best_prices               generate_random_best_prices(void);
mtk::prices::msg::sub_last_mk_execs_ticker      generate_random_last_mk_execs_ticker(void);



namespace  mtk{ namespace  prices{ namespace  publ {
    extern std::string  compacted_prices(const mtk::prices::msg::sub_best_prices& best_prices, const mtk::prices::msg::sub_last_mk_execs_ticker&  last_mk_execs_ticker);
    extern std::string  compacted_prices(const mtk::prices::msg::sub_best_prices& best_prices);
    extern std::string  compacted_prices(const mtk::prices::msg::sub_last_mk_execs_ticker&  last_mk_execs_ticker);

    extern mtk::tuple<mtk::nullable<mtk::prices::msg::sub_best_prices>, mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker> >
    decompact_prices(const std::string& compacted_prices);
}; }; };




int main(void)
{
    std::cout << std::endl  <<   "sending just best prices---------------------------------" << std::endl;
    for(int i=0; i<50000; ++i)
    {
        mtk::prices::msg::sub_best_prices             best_prices           = generate_random_best_prices();

        std::string  cp = mtk::prices::publ::compacted_prices(best_prices);

        mtk::tuple<mtk::nullable<mtk::prices::msg::sub_best_prices>, mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker> >    prices = mtk::prices::publ::decompact_prices(cp);

        if(prices._0.Get() != best_prices)
        {
            std::cout << "error" << std::endl;
            std::cout << best_prices << std::endl;
            std::cout << prices._0.Get() << std::endl;
            return -1;
        }
        else
        {
            if(i%100==0)
                std::cout << "." << std::flush;
        }
    }

    std::cout << std::endl  <<   "sending just last---------------------------------" << std::endl;
    for(int i=0; i<50000; ++i)
    {
        mtk::prices::msg::sub_last_mk_execs_ticker    last_mk_execs_ticker  = generate_random_last_mk_execs_ticker();


        std::string  cp = mtk::prices::publ::compacted_prices(last_mk_execs_ticker);

        mtk::tuple<mtk::nullable<mtk::prices::msg::sub_best_prices>, mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker> >    prices = mtk::prices::publ::decompact_prices(cp);

        if(prices._1.Get() != last_mk_execs_ticker)
        {
            std::cout << "error" << std::endl;
            std::cout << last_mk_execs_ticker << std::endl;
            std::cout << prices._1.Get() << std::endl;
            return -1;
        }
        else
        {
            if(i%100==0)
                std::cout << "." << std::flush;
        }
    }

    std::cout << std::endl  <<   "sending best and last---------------------------------" << std::endl;
    for(int i=0; i<50000; ++i)
    {
        mtk::prices::msg::sub_best_prices             best_prices           = generate_random_best_prices();
        mtk::prices::msg::sub_last_mk_execs_ticker    last_mk_execs_ticker  = generate_random_last_mk_execs_ticker();


        std::string  cp = mtk::prices::publ::compacted_prices(best_prices, last_mk_execs_ticker);

        mtk::tuple<mtk::nullable<mtk::prices::msg::sub_best_prices>, mtk::nullable<mtk::prices::msg::sub_last_mk_execs_ticker> >    prices = mtk::prices::publ::decompact_prices(cp);

        if(prices._0.Get() != best_prices)
        {
            std::cout << "error" << std::endl;
            std::cout << best_prices << std::endl;
            std::cout << prices._0.Get() << std::endl;
            return -1;
        }
        else if(prices._1.Get() != last_mk_execs_ticker)
        {
            std::cout << "error" << std::endl;
            std::cout << last_mk_execs_ticker << std::endl;
            std::cout << prices._1.Get() << std::endl;
            return -1;
        }
        else
        {
            if(i%100==0)
                std::cout << "." << std::flush;
        }
    }

    return 0;
}




















mtk::prices::msg::sub_best_prices  generate_random_best_prices(void)
{
    static mtk::FixedNumber ref_price (mtk::fnDouble(100.), mtk::fnDec(2), mtk::fnInc(5));
    static mtk::FixedNumber ref_qty (mtk::fnDouble(10.), mtk::fnDec(0), mtk::fnInc(1));


    static int counter;
    ++counter;
    counter %= 5;
    int offset = mtk::rand()%20;
    mtk::prices::msg::sub_price_deph5 bids(     mtk::prices::msg::sub_price_level(ref_price - mtk::fnTicks(counter+1 + offset ), ref_qty + mtk::fnTicks(mtk::rand()%20)),
                                                mtk::prices::msg::sub_price_level(ref_price - mtk::fnTicks(counter+2 + offset ), ref_qty + mtk::fnTicks(mtk::rand()%20)),
                                                mtk::prices::msg::sub_price_level(ref_price - mtk::fnTicks(counter+3 + offset ), ref_qty + mtk::fnTicks(mtk::rand()%20)),
                                                mtk::prices::msg::sub_price_level(ref_price - mtk::fnTicks(counter+4 + offset ), ref_qty + mtk::fnTicks(mtk::rand()%20)),
                                                mtk::prices::msg::sub_price_level(ref_price - mtk::fnTicks(counter+5 + offset ), ref_qty + mtk::fnTicks(mtk::rand()%20))
                                        );
    mtk::prices::msg::sub_price_deph5 asks(     mtk::prices::msg::sub_price_level(ref_price + mtk::fnTicks(counter+1 + offset ), ref_qty + mtk::fnTicks(mtk::rand()%20)),
                                                mtk::prices::msg::sub_price_level(ref_price + mtk::fnTicks(counter+2 + offset ), ref_qty + mtk::fnTicks(mtk::rand()%20)),
                                                mtk::prices::msg::sub_price_level(ref_price + mtk::fnTicks(counter+3 + offset ), ref_qty + mtk::fnTicks(mtk::rand()%20)),
                                                mtk::prices::msg::sub_price_level(ref_price + mtk::fnTicks(counter+4 + offset ), ref_qty + mtk::fnTicks(mtk::rand()%20)),
                                                mtk::prices::msg::sub_price_level(ref_price + mtk::fnTicks(counter+5 + offset ), ref_qty + mtk::fnTicks(mtk::rand()%20))
                                        );
    return  mtk::prices::msg::sub_best_prices (bids, asks);
}


mtk::prices::msg::sub_last_mk_execs_ticker      generate_random_last_mk_execs_ticker(void)
{
    static mtk::FixedNumber ref_price (mtk::fnDouble(100.), mtk::fnDec(2), mtk::fnInc(5));
    static mtk::FixedNumber ref_qty (mtk::fnDouble(10.), mtk::fnDec(0), mtk::fnInc(1));


    static int counter;
    ++counter;
    counter %= 5;

    mtk::FixedNumber  last_price(ref_price + mtk::fnTicks(counter+1 + mtk::rand()%40 -20 ));
    mtk::FixedNumber  last_quantity(ref_qty + mtk::fnTicks(counter+1 + mtk::rand()%10000 ));

    mtk::FixedNumber  max_last_price(last_price + mtk::fnTicks(counter+1 + mtk::rand()%40 ));
    mtk::FixedNumber  min_last_price(last_price + mtk::fnTicks(counter+1 - mtk::rand()%40 ));


    return mtk::prices::msg::sub_last_mk_execs_ticker(last_price, last_quantity, max_last_price, min_last_price, ref_price);
}
