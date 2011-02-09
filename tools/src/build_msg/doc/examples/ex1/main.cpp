#include "test_messages.h"


int main (void)
{
    testing::LimitPosition lp(     mtk::make_nullable(std::string("b")),
                                mtk::make_nullable(mtk::FixedNumber(mtk::fnDouble(1.88), mtk::fnDec(2), mtk::fnInc(1))),
                                mtk::FixedNumber(mtk::fnDouble(2.66), mtk::fnDec(2), mtk::fnInc(1)));

    mtk::list<std::string> names;
    names.push_back("john");
    names.push_back("peter");

    mtk::list<testing::LimitPosition>  positions;
    positions.push_back(lp);


    testing::RQ_NW_LS rq(   "order_id",
                            "cli_ref",
                            lp,
                            lp,
                            testing::RQ_NW_LS::IC_control_fields_(mtk::DateTime(mtk::dtYear(2011), mtk::dtMonth(1), mtk::dtDay(20)), 123),
                            testing::RQ_NW_LS::IC_product_code("market", "product", "aditional code"),
                            names,
                            positions);


    std::cout << rq << std::endl;
    return 0;
}


void mtk::AlarmMsg(const mtk::Alarm& error)
{
    std::cout << error << std::endl;
}
