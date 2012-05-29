#include <iostream>

#include "components/admin/admin.h"
#include "support/call_later.h"
#include "components/fb/fbinsert.h"
#include "components/fb/fbcompsupport.h"
#include "support/nullable.hpp"
#include "components/trading/msg_trd_oms_rq.h"



namespace
{

    const char*   APP_NAME          = "HIST_EXECS";
    const char*   APP_VER           = "2012-05-28 f";
    const char*   APP_DESCRIPTION   = "Send execs from previus days\n"
                                      "";

    const char*   APP_MODIFICATIONS =   "           2012-05-28     first version\n"
                                        ;

}




void     susbcribe_oms_RQ_EXECS_HISTORIC(void);




int main(int argc, char ** argv)
{
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);



        susbcribe_oms_RQ_EXECS_HISTORIC();




        mtk::start_timer_wait_till_end();


        std::cout << "FIN..... " << std::endl;
        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION (std::cout<< , "main", "nothing more")

    std::cout << "MAL..... " << std::endl;
    #include "support/release_on_exit.hpp"
    return -1;

}




std::string   generate_sql(const  mtk::trd::msg::oms_RQ_EXECS_HISTORIC&  rq)
{
    std::string   result;
    result =
            "SELECT first 500  a.ID_TRADING, a.DB_TIME, a.REC_TIME, a.SENT_TIME, a.ORDER_TYPE, a.MARKET_ORDER_ID, \n"
                    "a.OID_SESSION_ID, a.OID_RQ_CODE, a.PC_MARKET, a.PC_PRODUCT_CODE, a.SIDE, a.ACCOUNT_CC, a.ACCOUNT_NAME, a.RID_SESSION_ID, \n"
                    "a.RID_RQ_CODE, a.CLI_REF, a.CFLUCT_KEY, a.CFLUCT_DATE_TIME, a.RQ_POS_PRICE, a.RQ_POS_PRICE_DEC, a.RQ_POS_PRICE_INC, \n"
                    "a.RQ_POS_QUANTITY, a.RQ_POS_QUANTITY_DEC, a.RQ_POS_QUANTITY_INC, a.CF_POS_PRICE, a.CF_POS_PRICE_DEC, a.CF_POS_PRICE_INC, \n"
                    "a.CF_POS_QUANTITY, a.CF_POS_QUANTITY_DEC, a.CF_POS_QUANTITY_INC, a.EXCF_EXEC_ID, a.EXCF_POS_PRICE, a.EXCF_POS_PRICE_DEC, \n"
                    "a.EXCF_POS_PRICE_INC, a.EXCF_POS_QUANTITY, a.EXCF_POS_QUANTITY_DEC, a.EXCF_POS_QUANTITY_INC, a.TEX_SUM_PRICE_QTY, a.TEX_ACC_QTY, \n"
                    "a.TEX_ACC_QTY_DEC, a.TEX_ACC_QTY_INC, a.TEX_REM_QTY, a.TEX_REM_QTY_DEC, a.TEX_REM_QTY_INC, a.DESCRIPTION, a.REMARKS, a.AUTOMATIC, a.TIME_IN_FORCE\n"
            "FROM TRADING a \n"
            "\n";


    result +=  MTK_SS(
            "where a.DB_TIME > cast('"   <<  rq.date  << "' as date)  and   a.DB_TIME < cast('" <<   rq.date   <<  "' as date)+1 \n");


    result +=  MTK_SS("and    a.PC_MARKET = '"  <<  rq.market  << "' \n");

    result +=  "and a.ORDER_TYPE like 'CF_EX%' \n"
            "\n"
            "AND \n"
            "( \n";

    std::string  account_filter;
    for(auto it= rq.list_accounts.begin(); it!= rq.list_accounts.end(); ++it)
    {
        if(account_filter!="")
        {
            account_filter +=
                "    or \n"
                "    \n";
        }

        const mtk::trd::msg::sub_account_info&    account_info = *it;        //  I know it's dangerous
        account_filter += MTK_SS(
                "    ( \n"
                "    a.ACCOUNT_CC = '"  <<   account_info.client_code   << "'  and a.ACCOUNT_NAME = '"  <<  account_info.name  <<  "' \n"
                "    ) \n"
                "    \n"
                );

    }
    result += account_filter;

    result +=
            " \n"
            ") \n";

    return result;
}



std::string   get_string(const IBPP::Statement&   st, const std::string&  field_name)
{
    std::string  result;
    try {
        st->Get(field_name, result);
    } MTK_CATCH_RETHROW("get_db", MTK_SS("reading... " << field_name))
    return result;
}

int  get_int(const IBPP::Statement&   st, const std::string&  field_name)
{
    int  result;
    try {
        st->Get(field_name, result);
    } MTK_CATCH_RETHROW("get_db", MTK_SS("reading... " << field_name))
    return result;
}

mtk::FixedNumber  get_fixed_number(const IBPP::Statement&   st, const std::string&  name_int, const std::string&  name_inc, const std::string&  name_dec)
{
    int  value=0;
    int  dec=0;
    int  inc=0;


    try {
        st->Get(name_int, value);
        st->Get(name_inc, dec);
        st->Get(name_dec, inc);
    } MTK_CATCH_RETHROW("get_db", MTK_SS("reading... " << name_int))

    return  mtk::FixedNumber(mtk::fnIntCode(value), mtk::fnDec(dec), mtk::fnInc(inc));
}

mtk::nullable<mtk::DateTime>  get_date_time(const IBPP::Statement&   st, const std::string&  name)
{
    mtk::nullable<mtk::DateTime> result;
    try {
        st->Get(name, result);
    } MTK_CATCH_RETHROW("get_db", MTK_SS("reading... " << name))
    return  result;
}

void  send_execs(const std::string&  sql, const  mtk::trd::msg::oms_RQ_EXECS_HISTORIC&  rq)
{
    //  exec select
    //  iterate all records
        //  build message
        //  send message


    try
    {
        IBPP::Database 	db  =  mtk::fbDatabaseFromConfig("DB_TRADING");

        db->Connect();
        IBPP::Transaction tr = IBPP::TransactionFactory(db);
        tr->Start();

            IBPP::Statement st = IBPP::StatementFactory(db, tr);
            st->Execute(sql);
            while (st->Fetch())
            {
                std::string                                 exec_id                 (get_string(st, "EXCF_EXEC_ID"));
                mtk::FixedNumber                            exec_price              (get_fixed_number(st, "EXCF_POS_PRICE", "EXCF_POS_PRICE_DEC", "EXCF_POS_PRICE_INC"));
                mtk::FixedNumber                            exec_quantity           (get_fixed_number(st, "EXCF_POS_QUANTITY", "EXCF_POS_QUANTITY_DEC", "EXCF_POS_QUANTITY_INC"));
                mtk::msg::sub_product_code                  product_code            (get_string(st, "PC_MARKET"), get_string(st, "PC_PRODUCT_CODE"));


                std::string                                 sside                   (get_string(st, "SIDE"));
                mtk::trd::msg::enBuySell                    side                    (mtk::trd::msg::buy);
                if      (sside == "sell")     side = mtk::trd::msg::sell;
                else if (sside == "buy" )     side = mtk::trd::msg::buy;
                else
                    throw mtk::Alarm(MTK_HERE, "reading exec db", MTK_SS("invalid side value " << sside), mtk::alPriorError);


                mtk::trd::msg::sub_account_info             account_info            (get_string(st, "ACCOUNT_NAME"), get_string(st, "ACCOUNT_CC"));
                mtk::msg::sub_request_id                    req_id_nw               (get_string(st, "OID_SESSION_ID"), get_string(st, "OID_RQ_CODE"));
                mtk::trd::msg::sub_order_id                 order_id                (req_id_nw);

                std::string                                 sautomatic              (get_string(st, "AUTOMATIC"));
                bool                                        automatic               (sautomatic == "N" ?  false : true);

                mtk::trd::msg::sub_invariant_order_info     invariant               (order_id, product_code, side, account_info, get_string(st, "TIME_IN_FORCE"), automatic);

                mtk::FixedNumber                            rem_quantity            (get_fixed_number(st, "TEX_REM_QTY", "TEX_REM_QTY_DEC", "TEX_REM_QTY_INC"));
                rem_quantity.SetIntCode(0);
                mtk::trd::msg::sub_total_executions         total_execs             (exec_price.GetDouble() * exec_quantity.GetDouble(), exec_quantity, rem_quantity);
                mtk::msg::sub_control_fluct                 orig_control_fluct      (get_string(st, "CFLUCT_KEY"), get_date_time(st, "CFLUCT_DATE_TIME").Get());
                mtk::trd::msg::CF_XX                        cf_xx                   (invariant, "market_order_id", req_id_nw, total_execs, "", orig_control_fluct);

                mtk::trd::msg::sub_exec_conf                executed_pos            (exec_id, exec_price, exec_quantity);
                mtk::trd::msg::CF_EXLK                      cf_exlk                 (cf_xx, executed_pos);
                mtk::msg::sub_gen_response_location2        gen_response_location2  (rq.request_info.req_id, rq.request_info.process_info.location.broker_code);
                mtk::trd::msg::CF_EX_HIST                   cf_ex_hist              (cf_exlk, gen_response_location2);

                if(rq.request_info.process_info.location.broker_code != "CIMD")
                {
                    if(account_info.client_code  !=  rq.request_info.process_info.location.broker_code)
                        throw mtk::Alarm(MTK_HERE, "sending execs hist", MTK_SS("sending to " << rq.request_info.process_info.location.broker_code
                                        <<  " an account from "  << account_info.client_code << "  aborted"), mtk::alPriorError, mtk::alTypeNoPermisions);
                }

                mtk_send_message("client", cf_ex_hist);
            }


        tr->Commit();
        db->Disconnect();
    }
    MTK_CATCH_RETHROW("main", "reading error")
}



void  on_rq_execs_hist  (const  mtk::trd::msg::oms_RQ_EXECS_HISTORIC&  rq)
{
    std::string   sql = generate_sql(rq);

    send_execs(sql, rq);
}

void     susbcribe_oms_RQ_EXECS_HISTORIC(void)
{
    static mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::oms_RQ_EXECS_HISTORIC> >    handle;
    MTK_QPID_RECEIVER_CONNECT_F(
                            handle,
                            mtk::admin::get_url("client"),
                            mtk::trd::msg::oms_RQ_EXECS_HISTORIC::get_in_subject(),
                            mtk::trd::msg::oms_RQ_EXECS_HISTORIC,
                            on_rq_execs_hist)
}
