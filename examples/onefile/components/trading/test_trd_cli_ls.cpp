#include "support/mtk_string.h"
#include "components/trading/trd_cli_ls.h"



namespace
{

    const char*   APP_NAME          = "ex_admin";
    const char*   APP_VER           = "2011-03-16";
    const char*   APP_DESCRIPTION   = "small example of admin component";
    const char*   APP_MODIFICATIONS = "example, no modifications info";
}





namespace mtk{  namespace msg  { 
    
sub_process_location  get_process_location(void)
{
    return mtk::msg::sub_process_location(mtk::msg::sub_location("CLIENT", "MACHINE"), "PROCESS_NAME", "UUID");
}
sub_request_info   get_request_info (void)
{
    static int i=0;
    return sub_request_info (sub_request_id("pending", MTK_SS("pending"<<i)), get_process_location());
}

};};  //namespace mkt{  namespace msg  { 





void request_new(const mtk::trd::msg::RQ_NW_LS& rq)
{
    std::cout << "request_new " << std::endl << rq << std::endl << std::endl;
}

void request_modif(const mtk::trd::msg::RQ_MD_LS& rq)
{
    std::cout << "request_modif " << std::endl << rq << std::endl << std::endl;
}

void request_canc(const mtk::trd::msg::RQ_CC_LS& rq)
{
    std::cout << "request_canc " << std::endl << rq << std::endl << std::endl;
}

void reject_new(const mtk::trd::msg::RJ_NW_LS& rj)
{
    std::cout << "reject_new " << std::endl << rj << std::endl << std::endl;
}

void reject_modif(const mtk::trd::msg::RJ_MD_LS& rj)
{
    std::cout << "reject_modif " << std::endl << rj << std::endl << std::endl;
}

void reject_canc(const mtk::trd::msg::RJ_CC_LS& rj)
{
    std::cout << "reject_canc " << std::endl << rj << std::endl << std::endl;
}


void confirm_new(const mtk::trd::msg::CF_NW_LS& cf)
{
    std::cout << "confirm_new " << std::endl << cf << std::endl << std::endl;
}

void confirm_modif(const mtk::trd::msg::CF_MD_LS& cf)
{
    std::cout << "confirm_modif " << std::endl << cf << std::endl << std::endl;
}

void confirm_canc(const mtk::trd::msg::CF_CC_LS& cf)
{
    std::cout << "confirm_canc " << std::endl << cf << std::endl << std::endl;
}

void confirm_exec(const mtk::trd::msg::CF_EX_LS& ex)
{
    std::cout << "confirm_exec " << std::endl << ex << std::endl << std::endl;
}





int main(void)
{
    try{
        mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
      
      
        mtk::trd::msg::sub_order_id         ord_id(mtk::msg::get_request_info().req_id);
        mtk::msg::sub_product_code pc (mtk::msg::sub_sys_product_code(mtk::msg::sub_single_product_code("market", "product"), "product"), 
                                    mtk::nullable<mtk::msg::sub_adic_product_code>());


        mtk::trd::trd_cli_ls  order_ls;
        
        order_ls.sig_rq_nw.connect(request_new);
        order_ls.sig_rq_md.connect(request_modif);
        order_ls.sig_rq_cc.connect(request_canc);
        
        order_ls.sig_rj_nw.connect(reject_new);
        order_ls.sig_rj_md.connect(reject_modif);
        order_ls.sig_rj_cc.connect(reject_canc);

        order_ls.sig_cf_nw.connect(confirm_new);
        order_ls.sig_cf_md.connect(confirm_modif);
        order_ls.sig_cf_cc.connect(confirm_canc);

        order_ls.sig_cf_ex.connect(confirm_exec);

        
        //  we receive a request new...
        order_ls.rq_nw (mtk::trd::msg::RQ_NW_LS (mtk::trd::msg::RQ_XX_LS(
                                  mtk::msg::sub_request_info(mtk::msg::sub_request_id(ord_id.sess_id, 
                                                              ord_id.req_code), 
                                                 mtk::msg::get_process_location())
                                  ,  ord_id
                                  , pc
                                  , mtk::trd::msg::sub_position_ls(
                                                   mtk::FixedNumber(mtk::fnDouble(100.123),  mtk::fnDec(3),  mtk::fnInc(1))
                                                   , mtk::FixedNumber(mtk::fnDouble(30)   ,  mtk::fnDec(0),  mtk::fnInc(1))
                                                   , mtk::trd::msg::buy)
                                  , "cli_ref"
                                  , mtk::msg::sub_control_fluct("A", mtk::dtNowLocal()))));


        //  receiving a cf_nw
        order_ls.cf_nw(mtk::trd::msg::CF_NW_LS( mtk::trd::msg::CF_XX_LS(     
                                                                    mtk::msg::sub_request_info(mtk::msg::sub_request_id(ord_id.sess_id, ord_id.req_code), mtk::msg::get_process_location())
                                                                  , mtk::trd::msg::sub_order_ls_confirmated(     
                                                                                                  ord_id
                                                                                                , pc
                                                                                                , mtk::trd::msg::sub_position_ls(
                                                                                                          mtk::FixedNumber(mtk::fnDouble(100.123),  mtk::fnDec(3),  mtk::fnInc(1))
                                                                                                        , mtk::FixedNumber(mtk::fnDouble(30)     ,  mtk::fnDec(0),  mtk::fnInc(1))
                                                                                                        , mtk::trd::msg::buy)
                                                                                                , mtk::trd::msg::sub_total_executions(
                                                                                                          0.
                                                                                                        , mtk::FixedNumber(mtk::fnDouble(0) ,  mtk::fnDec(0),  mtk::fnInc(1))
                                                                                                        , mtk::FixedNumber(mtk::fnDouble(30),  mtk::fnDec(0),  mtk::fnInc(1)))
                                                                                                , "cli_ref")
                                                                    , mtk::msg::sub_control_fluct("A", mtk::dtNowLocal()))));

        //  we receive a request modification
        order_ls.rq_md(mtk::trd::msg::RQ_MD_LS(mtk::trd::msg::RQ_XX_LS( 
                                                                  mtk::msg::get_request_info()
                                                                , ord_id
                                                                , pc
                                                                , mtk::trd::msg::sub_position_ls(
                                                                          mtk::FixedNumber(mtk::fnDouble(100.333),  mtk::fnDec(3),  mtk::fnInc(1))
                                                                        , mtk::FixedNumber(mtk::fnDouble(30)     ,  mtk::fnDec(0),  mtk::fnInc(1))
                                                                        , mtk::trd::msg::buy)
                                                                , "cli_ref"
                                                                , mtk::msg::sub_control_fluct("A", mtk::dtNowLocal()))));


        //  receiving a cf_md
        order_ls.cf_md(mtk::trd::msg::CF_MD_LS(mtk::trd::msg::CF_XX_LS(
                                                                    order_ls.last_request().Get().req_info
                                                                  , mtk::trd::msg::sub_order_ls_confirmated(     
                                                                                                  order_ls.last_request().Get().order_id
                                                                                                , order_ls.last_request().Get().product_code
                                                                                                , order_ls.last_request().Get().request_pos
                                                                                                , order_ls.last_confirmation().Get().confirmated_info.total_execs
                                                                                                , order_ls.last_request().Get().cli_ref)
                                                                  , mtk::msg::sub_control_fluct("A", mtk::dtNowLocal()))));

        //  receiving a modification with no modifications
        order_ls.rq_md(mtk::trd::msg::RQ_MD_LS(mtk::trd::msg::RQ_XX_LS( 
                                                                  mtk::msg::get_request_info()
                                                                , ord_id
                                                                , pc
                                                                , mtk::trd::msg::sub_position_ls(
                                                                          mtk::FixedNumber(mtk::fnDouble(100.333),  mtk::fnDec(3),  mtk::fnInc(1))
                                                                        , mtk::FixedNumber(mtk::fnDouble(30)     ,  mtk::fnDec(0),  mtk::fnInc(1))
                                                                        , mtk::trd::msg::buy)
                                                                , "cli_ref"
                                                                , mtk::msg::sub_control_fluct("A", mtk::dtNowLocal()))));

        //  receiving a non requested cf_md
        order_ls.cf_md(mtk::trd::msg::CF_MD_LS(mtk::trd::msg::CF_XX_LS(
                                                                  mtk::msg::get_request_info()
                                                                  , mtk::trd::msg::sub_order_ls_confirmated(     
                                                                                                  order_ls.last_confirmation().Get().confirmated_info.order_id
                                                                                                , order_ls.last_confirmation().Get().confirmated_info.product_code
                                                                                                , mtk::trd::msg::sub_position_ls(
                                                                                                          mtk::FixedNumber(mtk::fnDouble(101.222),  mtk::fnDec(3),  mtk::fnInc(1))
                                                                                                        , mtk::FixedNumber(mtk::fnDouble(45)     ,  mtk::fnDec(0),  mtk::fnInc(1))
                                                                                                        , mtk::trd::msg::buy)
                                                                                                , order_ls.last_confirmation().Get().confirmated_info.total_execs
                                                                                                , order_ls.last_request().Get().cli_ref)
                                                                  , mtk::msg::sub_control_fluct("A", mtk::dtNowLocal()))));



        //  receiving a cf_ex
        order_ls.cf_ex(mtk::trd::msg::CF_EX_LS(
                                                    mtk::trd::msg::CF_XX_LS(
                                                                      mtk::msg::get_request_info()
                                                                    , mtk::trd::msg::sub_order_ls_confirmated(     
                                                                                                  order_ls.last_confirmation().Get().confirmated_info.order_id
                                                                                                , order_ls.last_confirmation().Get().confirmated_info.product_code
                                                                                                , mtk::trd::msg::sub_position_ls(
                                                                                                          mtk::FixedNumber(mtk::fnDouble(101.222),  mtk::fnDec(3),  mtk::fnInc(1))
                                                                                                        , mtk::FixedNumber(mtk::fnDouble(40)     ,  mtk::fnDec(0),  mtk::fnInc(1))
                                                                                                        , mtk::trd::msg::buy)
                                                                                                , order_ls.last_confirmation().Get().confirmated_info.total_execs
                                                                                                , order_ls.last_request().Get().cli_ref)
                                                                    , mtk::msg::sub_control_fluct("A", mtk::dtNowLocal()))
                                                    //  executed
                                                    , mtk::trd::msg::sub_position_ls(
                                                              mtk::FixedNumber(mtk::fnDouble(101.222),  mtk::fnDec(3),  mtk::fnInc(1))
                                                            , mtk::FixedNumber(mtk::fnDouble(5)      ,  mtk::fnDec(0),  mtk::fnInc(1))
                                                            , mtk::trd::msg::buy)
                                                                                                ));


        //  receiving a rq_cc
        order_ls.rq_cc(mtk::trd::msg::RQ_CC_LS(mtk::trd::msg::RQ_XX_LS( order_ls.last_request().Get())));


        //  receiving a cf_cc  requested
        order_ls.cf_cc(mtk::trd::msg::CF_CC_LS(mtk::trd::msg::CF_XX_LS(
                                                                    order_ls.last_request().Get().req_info
                                                                  , mtk::trd::msg::sub_order_ls_confirmated(     
                                                                                                  order_ls.last_confirmation().Get().confirmated_info.order_id
                                                                                                , order_ls.last_confirmation().Get().confirmated_info.product_code
                                                                                                , mtk::trd::msg::sub_position_ls(
                                                                                                          mtk::FixedNumber(mtk::fnDouble(101.222),  mtk::fnDec(3),  mtk::fnInc(1))
                                                                                                        , mtk::FixedNumber(mtk::fnDouble(40)     ,  mtk::fnDec(0),  mtk::fnInc(1))
                                                                                                        , mtk::trd::msg::buy)
                                                                                                , order_ls.last_confirmation().Get().confirmated_info.total_execs
                                                                                                , order_ls.last_request().Get().cli_ref)
                                                                  , mtk::msg::sub_control_fluct("A", mtk::dtNowLocal()))));

        std::cout << "FIN..... " << std::endl;
        #include "support/release_on_exit.hpp"
        return 0;
    } MTK_CATCH_CALLFUNCION(std::cout << , "main", "nm")
    
    std::cout << std::endl;
    return -1;
}


